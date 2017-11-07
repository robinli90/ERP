using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Data.Odbc;
using ExcelWriter = Microsoft.Office.Interop.Excel;

namespace InvoiceGenerator
{
    public partial class Terry_Weekly_Report : Form
    {
        Size Start_Size = new Size();
        public Database masterDB = Database.DECADE_MARKHAM;
        public Database tigerDB = Database.TIGER_MARKHAM;
        private Dictionary<string, string> Price_List = new Dictionary<string, string>();

        public Terry_Weekly_Report()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            Start_Size = this.Size;
        }

        private List<Invoice> Invoice_List = new List<Invoice>();

        private void Receipt_Load(object sender, EventArgs e)
        {
            // Mousedown anywhere to drag
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

            for (int i = 1; i < 13; i++)
            {
                from_month.Items.Add(i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.AddMonths(-1).Month.ToString("D2");


            for (int i = 10; i <= Convert.ToInt32(DateTime.Now.Year.ToString().Substring(2, 2)); i++)
            {
                from_year.Items.Add("20" + i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.Month.ToString("D2");
            from_year.Text = DateTime.Now.Year.ToString();

            // Memo Tooltip (Hover)
            ToolTip ToolTip1 = new ToolTip();
            ToolTip1.InitialDelay = 1;
            ToolTip1.ReshowDelay = 1;
            ToolTip1.SetToolTip(Add_button, "Generate");

            plant_box.Items.Add("MARKHAM");
            plant_box.Items.Add("MICHIGAN");
            plant_box.Items.Add("TEXAS");
            plant_box.Items.Add("COLOMBIA");

            plant_box.SelectedIndex = 0;
        }

        private void minimize_button_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void close_button_Click(object sender, EventArgs e)
        {
            this.Dispose();
            this.Close();
        }

        public void Set_Form_Color(Color randomColor)
        {
            //minimize_button.ForeColor = randomColor;
            //close_button.ForeColor = randomColor;
            textBox1.BackColor = randomColor;
            textBox2.BackColor = randomColor;
            textBox3.BackColor = randomColor;
            textBox4.BackColor = randomColor;
        }

        private object misValue = System.Reflection.Missing.Value;
        private ExcelWriter.Worksheet Invoices;
        private ExcelWriter.Workbook workBook;
        private ExcelWriter.Application excel = new ExcelWriter.Application();
        private string plant_name = "";
        public int Search_Days = 0;
        public int YTD_Workdays = 0;

        public List<Customer> Cust_List = new List<Customer>();

        public Customer Get_Customer(string Cust_Code)
        {
            return Cust_List.FirstOrDefault(x => x.Code == Cust_Code);
        }

        public bool[,] Holidays = new bool[12,31];

        public void Get_Holidays()
        {
            Holidays = new bool[12, 31]; 
        }

        public int Get_Work_Days(DateTime from, DateTime to)
        {
            DateTime ref_Date = from;
            int days = 0;
            while (ref_Date.ToShortDateString() != to.ToShortDateString())
            {
                if (ref_Date.DayOfWeek != DayOfWeek.Saturday && ref_Date.DayOfWeek != DayOfWeek.Sunday && !Holidays[ref_Date.Month - 1, ref_Date.Day - 1])
                {
                    days++;
                }
                ref_Date = ref_Date.AddDays(1);
            }
            return days;
        }

        public int Get_Work_Days_In_Month()
        {
            DateTime ref_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            return Get_Work_Days(ref_Date, ref_Date.AddMonths(1));
        }

        public int Get_Work_Days_In_Year()
        {
            DateTime ref_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            return Get_Work_Days(new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1), new DateTime(Convert.ToInt32(from_year.Text), 10, 1));
        }

        public void Generate_Sales(int period = -1)
        {
            if (period >= 0)
            {
                from_month.Text = period.ToString("D2");
            }

            Get_Holidays(); 

            excel = new ExcelWriter.Application();
            misValue = System.Reflection.Missing.Value;
            
            ExcoODBC instance = ExcoODBC.Instance;

            DateTime from_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            DateTime to_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 
                                DateTime.Now.Month == Convert.ToInt32(from_month.Text) && DateTime.Now.Year == Convert.ToInt32(from_year.Text) ? DateTime.Now.Day : 1);

            if (DateTime.Now.Month != Convert.ToInt32(from_month.Text) || DateTime.Now.Year != Convert.ToInt32(from_year.Text)) { to_Date = to_Date.AddMonths(1); } else { to_Date = to_Date.AddDays(1); }

            // Change dates if search by entire year instead
            if (by_year.Checked)
            {
                from_Date = new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1);
                to_Date = from_Date.AddYears(1);
            }

            Search_Days = Get_Work_Days(from_Date, to_Date);
            YTD_Workdays = Get_Work_Days(new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1), to_Date); // start of fiscal to now


            #region Get master accounts
            string query = "select d_customer.customercode, d_customer.accountset, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount" + (exTax.Checked ? "-d_order.gst" : "") +") " +
                           "as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode " +
                           "and hasnitridecomputedline = 0 group by d_customer.customercode, d_customer.accountset, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.accountset, d_customer.name, count(d_customer.customercode) " +
                           "as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' " +
                           "and d_order.customercode = d_customer.customercode and hasnitridecomputedline = 1 group by d_customer.customercode, d_customer.accountset, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.accountset, d_customer.name, 0 as count1, 0 as sales,territory from d_order, d_customer where not exists " +
                           "(select * from d_order where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode ) " +
                           "group by d_customer.customercode, d_customer.accountset, d_customer.name, territory order by territory, sales desc, count1 desc,d_customer.customercode, d_customer.name";

            Cust_List = new List<Customer>();
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            Customer c = new Customer();
            while (reader.Read())
            { 
                c = new Customer();
                c.Code = reader[0].ToString().Trim();
                c.Currency = reader[1].ToString().Trim();
                c.Name = reader[2].ToString().Trim();
                c.Count = Convert.ToInt32(reader[3].ToString().Trim());
                c.Sales = Convert.ToDouble(reader[4].ToString().Trim());
                c.Territory = reader[5].ToString().Trim();
                Cust_List.Add(c);
            }

            reader.Close();
            #endregion

            #region Get Last year sales figures

            from_Date = from_Date.AddYears(-1);
            to_Date = to_Date.AddYears(-1);

            query = "select d_customer.customercode, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount) " +
                           "as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode " +
                           "and hasnitridecomputedline = 0 group by d_customer.customercode, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.name, count(d_customer.customercode) " +
                           "as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' " +
                           "and d_order.customercode = d_customer.customercode and hasnitridecomputedline = 1 group by d_customer.customercode, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.name, 0 as count1, 0 as sales,territory from d_order, d_customer where not exists " +
                           "(select * from d_order where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode ) " +
                           "group by d_customer.customercode, d_customer.name, territory order by territory, sales desc, count1 desc,d_customer.customercode, d_customer.name";



            from_Date = from_Date.AddYears(1);
            to_Date = to_Date.AddYears(1);

            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                //if (Convert.ToDouble(reader[3].ToString().Trim()) > 0) Console.WriteLine(Convert.ToDouble(reader[3].ToString().Trim()));
                Cust_List.FirstOrDefault(x => x.Code == reader[0].ToString().Trim()).LastYearSales = Convert.ToDouble(reader[3].ToString().Trim());
                //if (c.Name.Contains("awneer") && c.Name.Contains("(AR)")) Console.WriteLine("");
            }

            reader.Close();
            #endregion
            
            int budgetMonth = Convert.ToInt32(from_month.Text);
            int budgetFromYear = Convert.ToInt32(from_year.Text) + (budgetMonth >= 10 ? 0 : -1);
            int budgetToYear = budgetFromYear + 1;

            #region Get YTD totals
            foreach (Customer cc in Cust_List)
            {
                query = "select d_customer.customercode, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount) as " +
                        "sales,territory from d_order, d_customer where orderdate >= '10/1/" + budgetFromYear + " 12:00 AM' and orderdate < '10/1/" + budgetToYear + " 12:00 AM' and hasnitridecomputedline = 0 and d_order.customercode = " +
                        "'" + cc.Code + "' and d_customer.customercode = '" + cc.Code + "' group by d_customer.customercode, d_customer.name, territory UNION select d_customer.customercode, d_customer.name, " +
                        "count(d_customer.customercode) as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where " +
                        "orderdate >= '10/1/" + budgetFromYear + " 12:00 AM' and orderdate < '10/1/" + budgetToYear + " 12:00 AM' and hasnitridecomputedline = 1 and d_order.customercode = '" + cc.Code + "' " +
                        "and d_customer.customercode = '" + cc.Code + "' group by d_customer.customercode, d_customer.name, territory ";

                instance.Open(masterDB);
                reader = instance.RunQuery(query);
                while (reader.Read())
                {
                    cc.YTD_Sales = Convert.ToDouble(reader[3].ToString().Trim());
                }
                reader.Close();
            }
            #endregion

            #region Get customer cms to decade mapping in dictionary (cmsNumber, decadeCode)
            Dictionary<string, string> Cust_Map = new Dictionary<string, string>();
            query = "select * from d_customermapping";
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    Cust_Map.Add(reader[0].ToString().Trim(), reader[1].ToString().Trim());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Dictionary already has cust key: " + e.ToString());
                }
            }
            reader.Close();
            #endregion

            #region Get Budget per plant
            query = "Select * from [tiger].[dbo].[" + plant_name + "_Budget] where Year = '" + (Convert.ToInt32(from_month.Text) > 9 ? (Convert.ToInt32(from_year.Text) + 1).ToString() : from_year.Text) + "'";
            
            instance.Open(tigerDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    string cmsNo = reader[1].ToString().Trim();

                    // Store budget values for 12 periods
                    for (int i = 0; i < 12; i++)
                        Get_Customer(Cust_Map[cmsNo]).Budgets[i] = Convert.ToDouble(reader[5 + i].ToString().Trim());
                }
                catch
                { }
            }
            reader.Close();

            #endregion

            Cust_List = Cust_List.OrderBy(x => x.Territory).ToList();
            /*
            foreach (Invoice inv2 in Invoice_List)
            {
                ExcoODBC solarsoft = ExcoODBC.Instance;
                string query2 = "select * from cmsdat.CODE where A2 = 'KK' and A9 like '%" + inv2.Customer_Class + "%' and A9 not like '%X%'";
                solarsoft.Open(Database.CMSDAT);
                OdbcDataReader reader2 = solarsoft.RunQuery(query2);
                // get main data
                while (reader2.Read())
                {
                    inv2.Customer_Class_Desc = reader2["A30"].ToString().Trim();
                }
                reader2.Close();
            }*/

            workBook = excel.Workbooks.Add(misValue);
            Invoices = workBook.Worksheets.Add();
            Invoices.Name = plant_name + " Orders";// from " + from_Date.ToShortDateString() + " to " + to_Date.ToShortDateString();

            int excel_row = 1;

            // title
            excel_row = WriteSheetHeader(Invoices.Name + " from " + from_Date.ToShortDateString() + " to " + to_Date.AddDays(-1).ToShortDateString(), Invoices);   
            excel_row++;
            excel_row = WriteHeader(Invoices, excel_row);
            excel_row++;
            excel_row = WriteLines(Invoices, excel_row);
            excel_row++;
            AdjustSheetStyle(Invoices, excel_row);


            Invoices.Columns[6].Hidden = true;
            Invoices.Columns[5].Hidden = true;
            Invoices.Columns[8].Hidden = true;

            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Orders " + plant_box.Text + "-" + from_month.Text + "-" + from_year.Text + " (Generated on " + DateTime.Now.Day + "_" + DateTime.Now.Month + ").xlsx");
            File.Delete(path);
            workBook.SaveAs(path, ExcelWriter.XlFileFormat.xlOpenXMLWorkbook);
            _MARSHAL_KILL_EXCEL(path, period == -1);

        }


        private int WriteLines(ExcelWriter.Worksheet sheet, int g)
        {
            int row = g;
            double[] row_totals = new double[14];

            List<string> firstTerritory = Cust_List
                .Where(x => x.Sales > 0 || x.YTD_Sales > 0 || x.Get_Budget_Total() > 0).ToList()
                .OrderBy(x => x.Territory).Select(x => x.Territory).ToList();


            string territory_name = firstTerritory[0];

            int relative_count = Cust_List.Where(x => x.Sales > 0 || x.YTD_Sales > 0 || x.Get_Budget_Total() > 0).ToList().Count;
            int row_count = 0;

            foreach (Customer c in Cust_List.Where(x => x.Sales > 0 || x.YTD_Sales > 0 || x.Get_Budget_Total() > 0).ToList())
            {

                int col = 1;
                // Summarize all but USA
                if (c.Territory != territory_name && row > 3)
                {
                    sheet.Cells[row, col++] = "                                              " + territory_name + " Territory Total:";
                    sheet.Cells[row, col++] = row_totals[2];
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    col++;
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    StyleTotal(sheet, row + 1, true);
                    territory_name = c.Territory;
                    row_totals = new double[14];
                    row++;
                    row++;
                }
                //5, 174

                double mo = Get_Work_Days_In_Month();
                double refractor_amt = Search_Days / mo;
                double yr = Get_Work_Days_In_Year();
                double refractor_amt_yr = YTD_Workdays / yr;

                col = 1;
                sheet.Cells[row, col++] = c.Code + "  " + c.Name;
                sheet.Cells[row, col++] = c.Count;
                row_totals[col] += c.Count;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Sales);
                row_totals[col] += c.Sales;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt));
                row_totals[col] += (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt);
                sheet.Cells[row, col++] = Search_Days;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.LastYearSales);
                row_totals[col] += c.LastYearSales;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Sales - (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt));
                row_totals[col] += c.Sales - (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt);
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text))));
                row_totals[col] += c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text));
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.YTD_Sales));
                row_totals[col] += c.YTD_Sales;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_Total(true, Convert.ToInt32(from_month.Text)) * refractor_amt_yr));
                row_totals[col] += c.Get_Budget_Total(true, Convert.ToInt32(from_month.Text)) * refractor_amt_yr;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.YTD_Sales) - (c.Get_Budget_Total(true, Convert.ToInt32(from_month.Text)) * refractor_amt_yr));
                row_totals[col] += (c.YTD_Sales) - (c.Get_Budget_Total(true, Convert.ToInt32(from_month.Text)) * refractor_amt_yr);
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Get_Budget_Total());
                row_totals[col] += c.Get_Budget_Total();
                sheet.Cells[row, col++] = c.Currency;
                //sheet.Cells[row, 12] = c.Territory;

                if (c.Sales < (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt)) sheet.Cells.get_Range("C" + row.ToString()).Interior.Color = Color.LightPink;
                if (c.YTD_Sales < (c.Get_Budget_Total(true, Convert.ToInt32(from_month.Text)) * refractor_amt_yr)) sheet.Cells.get_Range("J" + row.ToString()).Interior.Color = Color.LightPink;

                row++; 
                col = 1;

                // Summarize USA
                if (relative_count == row_count + 1)
                {
                    sheet.Cells[row, col++] = "                                              " + territory_name + " Territory Total:";
                    sheet.Cells[row, col++] = row_totals[2];
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    col++;
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    StyleTotal(sheet, row + 1, true);
                    territory_name = c.Territory;
                    row_totals = new double[14];
                    row++;
                    row++;
                }

                row_count++;
            }
            return row;
        }

        private int WriteSheetHeader(string title, ExcelWriter.Worksheet sheet)
        {
            int row = 1;
            sheet.Cells[row, 1] = title;
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "L1").Merge();
            return row;

        }

        private int WriteHeader(ExcelWriter.Worksheet sheet, int row)
        {
            int col = 1;
            sheet.Cells[row, col++] = "Customer";
            sheet.Cells[row, col++] = "# Orders";
            sheet.Cells[row, col++] = "MTD Total" + (exTax.Checked ? "-Tax" : "");
            //sheet.Cells[row, col++] = "Budget vs. Sales Mo.";
            sheet.Cells[row, col++] = "MTD Budget";
            sheet.Cells[row, col++] = "# Days";
            sheet.Cells[row, col++] = "Last Year Same Period";
            sheet.Cells[row, col++] = "MTD Diff";
            sheet.Cells[row, col++] = "Month Budget";
            sheet.Cells[row, col++] = "YTD Total" + (exTax.Checked ? "inc. Tax" : "");
            sheet.Cells[row, col++] = "YTD Budget";
            sheet.Cells[row, col++] = "YTD Diff";
            sheet.Cells[row, col++] = "Year Budget";
            ExcelWriter.Range range = sheet.Cells.get_Range("A" + row.ToString(), "L" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 12;
            range.ColumnWidth = 18;
            range.Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeBottom].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;

            range = sheet.Cells.get_Range("D" + row.ToString(), "D" + row.ToString());
            range.ColumnWidth = 30;
            range = sheet.Cells.get_Range("O" + row.ToString(), "O" + row.ToString());
            range.ColumnWidth = 25;

            return row;
        }

        private void Add_button_Click(object sender, EventArgs e)
        {
            /*
            foreach (string item in plant_box.Items)
            {
                plant_box.Text = item;
                from_year.Text = (Convert.ToInt32(from_year.Text) - 1).ToString();
                //Generate_Invoice_Register();
                int month = 10;

                for (int i = 1; i < 13; i++)
                {
                    if (month > 12)
                    {
                        month = 1;
                        from_year.Text = (Convert.ToInt32(from_year.Text) + 1).ToString();
                    }
                    if (plant_box.Text.Contains("MARKHAM"))Generate_Sales(month);
                    month++;
                }
            }
            */
            Console.Write("DSFSDF");
            Generate_Sales();
        }


        private void _MARSHAL_KILL_EXCEL(string path, bool open = true)
        {
            try
            {
                //workBook.Close(false, System.Reflection.Missing.Value, System.Reflection.Missing.Value);
                workBook.Close();
            }
            catch
            {
                Console.WriteLine("Error disposing EXCEL files");
            }
            excel.Quit();
            Marshal.ReleaseComObject(Invoices);
            Marshal.ReleaseComObject(workBook);
            Marshal.ReleaseComObject(excel);
            Invoices = null;
            workBook = null;
            excel = null;
            GC.GetTotalMemory(false);
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
            GC.GetTotalMemory(true);
            if (open) System.Diagnostics.Process.Start(path);
        }


        private void StyleOfSummary(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
        }

        private void StyleTotal(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + (row - 1).ToString(), "L" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("B" + (row - 1).ToString(), "L" + (row - 1).ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
            sheet.Cells.get_Range("B" + row.ToString(), "L" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
        }

        private void StyleOfSummary2(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
        }

        private void AdjustSheetStyle(ExcelWriter.Worksheet sheet, int row)
        {
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignCenter;
            sheet.Cells.get_Range("A2", "A" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignLeft;
            sheet.Cells.get_Range("B2", "V" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignRight;
        }

        private void from_month_SelectedIndexChanged(object sender, EventArgs e)
        {
        }


        private void from_year_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void plant_box_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void plant_box_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            if (plant_box.Text == "MARKHAM") masterDB = Database.DECADE_MARKHAM;
            else if (plant_box.Text == "MICHIGAN") masterDB = Database.DECADE_MICHIGAN;
            else if (plant_box.Text == "TEXAS") masterDB = Database.DECADE_TEXAS;
            else if (plant_box.Text == "COLOMBIA") masterDB = Database.DECADE_COLOMBIA;

            TextInfo myTI = new CultureInfo("en-US", false).TextInfo;
            Console.WriteLine(myTI.ToTitleCase(plant_box.Text.ToLower()));
            plant_name = myTI.ToTitleCase(plant_box.Text.ToLower());
        }

        private void by_year_CheckedChanged(object sender, EventArgs e)
        {
            from_month.Enabled = !by_year.Checked;
        }
    }

    public class Customer
    {
        public string Code { get; set; }
        public string Currency { get; set; }
        public string Name { get; set; }
        public string Territory { get; set; }
        public int Count { get; set; }
        public double Sales { get; set; }
        public double LastYearSales { get; set; }
        public double YTD_Sales { get; set; }
        public double[] Budgets { get; set; }

        public Customer()
        {
            double[] temp = new double[12];
            for (int i = 0; i < 12; i++)
            {
                temp[i] = 0;
            }
            Budgets = temp;
        }

        public double Get_Budget_For_Month(int month)
        {
            // convert month number to period number
            int convert_month_to_period = month + 3 - 1;
            return Budgets[convert_month_to_period > 11 ? convert_month_to_period - 12 : convert_month_to_period];
        }

        public double Get_Budget_Total(bool ifUpToCurrentPeriod = false, int fromMonth = 1)
        {
            if (ifUpToCurrentPeriod)
            {
                int refMonth = fromMonth + 3;
                double onGoingBudgetSum = 0;

                if (refMonth > 12)
                    refMonth -= 12;

                for (int i = 0; i < refMonth; i++)
                {
                    onGoingBudgetSum += Budgets[i];
                }

                return RoundOff(onGoingBudgetSum);

            }

            return RoundOff(Budgets.Sum());
        }

        public double RoundOff(double i)
        {
            return ((double)Math.Round(i / 10.0)) * 10;
        }

    }
}

/*
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Data.Odbc;
using ExcelWriter = Microsoft.Office.Interop.Excel;

namespace InvoiceGenerator
{
    public partial class Terry_Weekly_Report : Form
    {
        Size Start_Size = new Size();
        public Database masterDB = Database.DECADE_MARKHAM;
        public Database tigerDB = Database.TIGER_MARKHAM;
        private Dictionary<string, string> Price_List = new Dictionary<string, string>();

        public Terry_Weekly_Report()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            Start_Size = this.Size;
        }

        private List<Invoice> Invoice_List = new List<Invoice>();

        private void Receipt_Load(object sender, EventArgs e)
        {
            // Mousedown anywhere to drag
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

            for (int i = 1; i < 13; i++)
            {
                from_month.Items.Add(i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.AddMonths(-1).Month.ToString("D2");


            for (int i = 10; i <= Convert.ToInt32(DateTime.Now.Year.ToString().Substring(2, 2)); i++)
            {
                from_year.Items.Add("20" + i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.Month.ToString("D2");
            from_year.Text = DateTime.Now.Year.ToString();

            // Memo Tooltip (Hover)
            ToolTip ToolTip1 = new ToolTip();
            ToolTip1.InitialDelay = 1;
            ToolTip1.ReshowDelay = 1;
            ToolTip1.SetToolTip(Add_button, "Generate");

            plant_box.Items.Add("MARKHAM");
            plant_box.Items.Add("MICHIGAN");
            plant_box.Items.Add("TEXAS");
            plant_box.Items.Add("COLOMBIA");

            plant_box.SelectedIndex = 0;
        }

        private void minimize_button_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void close_button_Click(object sender, EventArgs e)
        {
            this.Dispose();
            this.Close();
        }

        public void Set_Form_Color(Color randomColor)
        {
            //minimize_button.ForeColor = randomColor;
            //close_button.ForeColor = randomColor;
            textBox1.BackColor = randomColor;
            textBox2.BackColor = randomColor;
            textBox3.BackColor = randomColor;
            textBox4.BackColor = randomColor;
        }

        private object misValue = System.Reflection.Missing.Value;
        private ExcelWriter.Worksheet Invoices;
        private ExcelWriter.Workbook workBook;
        private ExcelWriter.Application excel = new ExcelWriter.Application();
        private string plant_name = "";
        public int Search_Days = 0;
        public int YTD_Workdays = 0;

        public List<Customer> Cust_List = new List<Customer>();

        public Customer Get_Customer(string Cust_Code)
        {
            return Cust_List.FirstOrDefault(x => x.Code == Cust_Code);
        }

        public bool[,] Holidays = new bool[12,31];

        public void Get_Holidays()
        {
            Holidays = new bool[12, 31]; 
        }

        public int Get_Work_Days(DateTime from, DateTime to)
        {
            DateTime ref_Date = from;
            int days = 0;
            while (ref_Date.ToShortDateString() != to.ToShortDateString())
            {
                if (ref_Date.DayOfWeek != DayOfWeek.Saturday && ref_Date.DayOfWeek != DayOfWeek.Sunday && !Holidays[ref_Date.Month - 1, ref_Date.Day - 1])
                {
                    days++;
                }
                ref_Date = ref_Date.AddDays(1);
            }
            return days;
        }

        public int Get_Work_Days_In_Month()
        {
            DateTime ref_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            return Get_Work_Days(ref_Date, ref_Date.AddMonths(1));
        }

        public int Get_Work_Days_In_Year()
        {
            DateTime ref_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            return Get_Work_Days(new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1), new DateTime(Convert.ToInt32(from_year.Text), 10, 1));
        }

        public void Generate_Sales(int period = -1)
        {
            if (period >= 0)
            {
                from_month.Text = period.ToString("D2");
            }

            Get_Holidays(); 

            excel = new ExcelWriter.Application();
            misValue = System.Reflection.Missing.Value;
            
            ExcoODBC instance = ExcoODBC.Instance;

            DateTime from_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 1);
            DateTime to_Date = new DateTime(Convert.ToInt32(from_year.Text), Convert.ToInt32(from_month.Text), 
                                DateTime.Now.Month == Convert.ToInt32(from_month.Text) && DateTime.Now.Year == Convert.ToInt32(from_year.Text) ? DateTime.Now.Day : 1);

            if (DateTime.Now.Month != Convert.ToInt32(from_month.Text) || DateTime.Now.Year != Convert.ToInt32(from_year.Text)) { to_Date = to_Date.AddMonths(1); } else { to_Date = to_Date.AddDays(1); }

            // Change dates if search by entire year instead
            if (by_year.Checked)
            {
                from_Date = new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1);
                to_Date = from_Date.AddYears(1);
            }

            Search_Days = Get_Work_Days(from_Date, to_Date);
            YTD_Workdays = Get_Work_Days(new DateTime(Convert.ToInt32(from_year.Text) - 1, 10, 1), to_Date); // start of fiscal to now


            #region Get master accounts
            string query = "select d_customer.customercode, d_customer.accountset, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount" + (exTax.Checked ? "-d_order.gst" : "") +") " +
                           "as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode " +
                           "and hasnitridecomputedline = 0 group by d_customer.customercode, d_customer.accountset, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.accountset, d_customer.name, count(d_customer.customercode) " +
                           "as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' " +
                           "and d_order.customercode = d_customer.customercode and hasnitridecomputedline = 1 group by d_customer.customercode, d_customer.accountset, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.accountset, d_customer.name, 0 as count1, 0 as sales,territory from d_order, d_customer where not exists " +
                           "(select * from d_order where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode ) " +
                           "group by d_customer.customercode, d_customer.accountset, d_customer.name, territory order by territory, sales desc, count1 desc,d_customer.customercode, d_customer.name";

            Cust_List = new List<Customer>();
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            Customer c = new Customer();
            while (reader.Read())
            { 
                c = new Customer();
                c.Code = reader[0].ToString().Trim();
                c.Currency = reader[1].ToString().Trim();
                c.Name = reader[2].ToString().Trim();
                c.Count = Convert.ToInt32(reader[3].ToString().Trim());
                c.Sales = Convert.ToDouble(reader[4].ToString().Trim());
                c.Territory = reader[5].ToString().Trim();
                Cust_List.Add(c);
            }

            reader.Close();
            #endregion

            #region Get Last year sales figures

            from_Date = from_Date.AddYears(-1);
            to_Date = to_Date.AddYears(-1);

            query = "select d_customer.customercode, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount) " +
                           "as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode " +
                           "and hasnitridecomputedline = 0 group by d_customer.customercode, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.name, count(d_customer.customercode) " +
                           "as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' " +
                           "and d_order.customercode = d_customer.customercode and hasnitridecomputedline = 1 group by d_customer.customercode, d_customer.name, territory " +
                           "UNION select d_customer.customercode, d_customer.name, 0 as count1, 0 as sales,territory from d_order, d_customer where not exists " +
                           "(select * from d_order where orderdate >= '" + from_Date.ToString() + "' and orderdate < '" + to_Date.ToString() + "' and d_order.customercode = d_customer.customercode ) " +
                           "group by d_customer.customercode, d_customer.name, territory order by territory, sales desc, count1 desc,d_customer.customercode, d_customer.name";



            from_Date = from_Date.AddYears(1);
            to_Date = to_Date.AddYears(1);

            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                //if (Convert.ToDouble(reader[3].ToString().Trim()) > 0) Console.WriteLine(Convert.ToDouble(reader[3].ToString().Trim()));
                Cust_List.FirstOrDefault(x => x.Code == reader[0].ToString().Trim()).LastYearSales = Convert.ToDouble(reader[3].ToString().Trim());
                //if (c.Name.Contains("awneer") && c.Name.Contains("(AR)")) Console.WriteLine("");
            }

            reader.Close();
            #endregion

            #region Get YTD totals
            foreach (Customer cc in Cust_List)
            {
                query = "select d_customer.customercode, d_customer.name, count(d_customer.customercode) as count1, sum(sales+nitride+steelsurcharge-discountamount) as " +
                        "sales,territory from d_order, d_customer where orderdate >= '10/1/" + (Convert.ToInt32(from_year.Text) - 1).ToString() + " 12:00 AM' and orderdate < '10/1/" + from_year.Text + " 12:00 AM' and hasnitridecomputedline = 0 and d_order.customercode = " +
                        "'" + cc.Code + "' and d_customer.customercode = '" + cc.Code + "' group by d_customer.customercode, d_customer.name, territory UNION select d_customer.customercode, d_customer.name, " +
                        "count(d_customer.customercode) as count1, sum(sales+steelsurcharge-discountamount) as sales,territory from d_order, d_customer where " +
                        "orderdate >= '10/1/" + (Convert.ToInt32(from_year.Text) - 1).ToString() + " 12:00 AM' and orderdate < '10/1/" + from_year.Text + " 12:00 AM' and hasnitridecomputedline = 1 and d_order.customercode = '" + cc.Code + "' " +
                        "and d_customer.customercode = '" + cc.Code + "' group by d_customer.customercode, d_customer.name, territory ";

                instance.Open(masterDB);
                reader = instance.RunQuery(query);
                while (reader.Read())
                {
                    cc.YTD_Sales = Convert.ToDouble(reader[3].ToString().Trim());
                }
                reader.Close();
            }
            #endregion

            #region Get customer cms to decade mapping in dictionary (cmsNumber, decadeCode)
            Dictionary<string, string> Cust_Map = new Dictionary<string, string>();
            query = "select * from d_customermapping";
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    Cust_Map.Add(reader[0].ToString().Trim(), reader[1].ToString().Trim());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Dictionary already has cust key: " + e.ToString());
                }
            }
            reader.Close();
            #endregion

            #region Get Markham Budget per plant
            query = "Select * from [tiger].[dbo].[" + plant_name + "_Budget] where Year = '" + (Convert.ToInt32(from_month.Text) > 9 ? (Convert.ToInt32(from_year.Text) + 1).ToString() : from_year.Text) + "'";
            
            instance.Open(tigerDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    string cmsNo = reader[1].ToString().Trim();

                    // Store budget values for 12 periods
                    for (int i = 0; i < 12; i++)
                        Get_Customer(Cust_Map[cmsNo]).Budgets[i] = Convert.ToDouble(reader[5 + i].ToString().Trim());
                }
                catch
                { }
            }
            reader.Close();

            #endregion

            Cust_List = Cust_List.OrderBy(x => x.Territory).ToList();

            workBook = excel.Workbooks.Add(misValue);
            Invoices = workBook.Worksheets.Add();
            Invoices.Name = plant_name + " Orders";// from " + from_Date.ToShortDateString() + " to " + to_Date.ToShortDateString();

            int excel_row = 1;

            // title
            excel_row = WriteSheetHeader(Invoices.Name + " from " + from_Date.ToShortDateString() + " to " + to_Date.ToShortDateString(), Invoices);   
            excel_row++;
            excel_row = WriteHeader(Invoices, excel_row);
            excel_row++;
            excel_row = WriteLines(Invoices, excel_row);
            excel_row++;
            AdjustSheetStyle(Invoices, excel_row);


            Invoices.Columns[6].Hidden = true;
            Invoices.Columns[9].Hidden = true;

            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Orders " + plant_box.Text + "-" + from_month.Text + "-" + from_year.Text + " (Generated on " + DateTime.Now.Day + "_" + DateTime.Now.Month + ").xlsx");
            File.Delete(path);
            workBook.SaveAs(path, ExcelWriter.XlFileFormat.xlOpenXMLWorkbook);
            _MARSHAL_KILL_EXCEL(path, period == -1);

        }


        private int WriteLines(ExcelWriter.Worksheet sheet, int g)
        {
            int row = g;
            double[] row_totals = new double[12];
            string territory_name = "ASA";

            int rel ative_count = Cust_List.Where(x => x.Sales > 0 || x.YTD_Sales > 0 || x.Get_Budget_Total() > 0).ToList().Count;
            int row_count = 0;

            foreach (Customer c in Cust_List.Where(x => x.Sales > 0 || x.YTD_Sales > 0 || x.Get_Budget_Total() > 0).ToList())
            {

                int col = 1;
                // Summarize all but USA
                if (c.Territory != territory_name && row > 3)
                {
                    sheet.Cells[row, col++] = "                                              " + territory_name + " Territory Total:";
                    sheet.Cells[row, col++] = row_totals[2];
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    col++;
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    StyleTotal(sheet, row + 1, true);
                    territory_name = c.Territory;
                    row_totals = new double[12];
                    row++;
                    row++;
                }

                double mo = Get_Work_Days_In_Month();
                double refractor_amt = Search_Days / mo;
                double yr = Get_Work_Days_In_Year();
                double refractor_amt_yr = YTD_Workdays / yr;

                col = 1;
                sheet.Cells[row, col++] = c.Code + "  " + c.Name;
                sheet.Cells[row, col++] = c.Count;
                row_totals[col] += c.Count;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Sales);
                row_totals[col] += c.Sales;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.LastYearSales);
                row_totals[col] += c.LastYearSales;
                sheet.Cells[row, col++] = Search_Days;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt));
                row_totals[col] += (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt);
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Sales - (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt));
                row_totals[col] += c.Sales - (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt);
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text))));
                row_totals[col] += c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text));
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.Get_Budget_Total() * refractor_amt_yr));
                row_totals[col] += c.Get_Budget_Total() * refractor_amt_yr;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.YTD_Sales));
                row_totals[col] += c.YTD_Sales;
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", (c.YTD_Sales) - (c.Get_Budget_Total() * refractor_amt_yr));
                sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", c.Get_Budget_Total());
                sheet.Cells[row, col++] = c.Currency;
                //sheet.Cells[row, 12] = c.Territory;


                if (c.Sales < (c.Get_Budget_For_Month(Convert.ToInt32(from_month.Text)) * refractor_amt)) sheet.Cells.get_Range("C" + row.ToString()).Interior.Color = Color.LightPink;
                if (c.YTD_Sales < (c.Get_Budget_Total() * refractor_amt_yr)) sheet.Cells.get_Range("I" + row.ToString()).Interior.Color = Color.LightPink;

                row++; 
                col = 1;

                // Summarize USA
                if (relative_count == row_count + 1)
                {
                    sheet.Cells[row, col++] = "                                              " + territory_name + " Territory Total:";
                    sheet.Cells[row, col++] = row_totals[2];
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    col++;
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", row_totals[col]);
                    StyleTotal(sheet, row + 1, true);
                    territory_name = c.Territory;
                    row_totals = new double[12];
                    row++;
                    row++;
                }

                row_count++;
            }
            return row;
        }

        private int WriteSheetHeader(string title, ExcelWriter.Worksheet sheet)
        {
            int row = 1;
            sheet.Cells[row, 1] = title;
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "L1").Merge();
            return row;

        }

        private int WriteHeader(ExcelWriter.Worksheet sheet, int row)
        {
            int col = 1;
            sheet.Cells[row, col++] = "Customer";
            sheet.Cells[row, col++] = "# Orders";
            sheet.Cells[row, col++] = "Total" + (exTax.Checked ? "-Tax" : "");
            sheet.Cells[row, col++] = "Last Year Same Period";
            sheet.Cells[row, col++] = "# Days";
            sheet.Cells[row, col++] = "Budget vs. Sales Mo.";
            sheet.Cells[row, col++] = "Budget vs. Sales Mo. Diff (C-F)";
            sheet.Cells[row, col++] = "Month Budget";
            sheet.Cells[row, col++] = "Budget vs. Sales Yr."; 
            sheet.Cells[row, col++] = "YTD Total" + (exTax.Checked ? "inc. Tax" : "");
            sheet.Cells[row, col++] = "Budget vs. Sales Yr. Diff (J-I)";
            sheet.Cells[row, col++] = "Year Budget";
            ExcelWriter.Range range = sheet.Cells.get_Range("A" + row.ToString(), "L" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 12;
            range.ColumnWidth = 18;
            range.Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeBottom].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;

            range = sheet.Cells.get_Range("D" + row.ToString(), "D" + row.ToString());
            range.ColumnWidth = 30;
            range = sheet.Cells.get_Range("O" + row.ToString(), "O" + row.ToString());
            range.ColumnWidth = 25;

            return row;
        }

        private void Add_button_Click(object sender, EventArgs e)
        {
            Generate_Sales();
        }


        private void _MARSHAL_KILL_EXCEL(string path, bool open = true)
        {
            try
            {
                //workBook.Close(false, System.Reflection.Missing.Value, System.Reflection.Missing.Value);
                workBook.Close();
            }
            catch
            {
                Console.WriteLine("Error disposing EXCEL files");
            }
            excel.Quit();
            Marshal.ReleaseComObject(Invoices);
            Marshal.ReleaseComObject(workBook);
            Marshal.ReleaseComObject(excel);
            Invoices = null;
            workBook = null;
            excel = null;
            GC.GetTotalMemory(false);
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
            GC.GetTotalMemory(true);
            if (open) System.Diagnostics.Process.Start(path);
        }


        private void StyleOfSummary(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
        }

        private void StyleTotal(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + (row - 1).ToString(), "J" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("B" + (row - 1).ToString(), "J" + (row - 1).ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
            sheet.Cells.get_Range("B" + row.ToString(), "J" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
        }

        private void StyleOfSummary2(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
        }

        private void AdjustSheetStyle(ExcelWriter.Worksheet sheet, int row)
        {
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignCenter;
            sheet.Cells.get_Range("A2", "A" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignLeft;
            sheet.Cells.get_Range("B2", "V" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignRight;
        }

        private void from_month_SelectedIndexChanged(object sender, EventArgs e)
        {
        }


        private void from_year_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void plant_box_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void plant_box_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            if (plant_box.Text == "MARKHAM") masterDB = Database.DECADE_MARKHAM;
            else if (plant_box.Text == "MICHIGAN") masterDB = Database.DECADE_MICHIGAN;
            else if (plant_box.Text == "TEXAS") masterDB = Database.DECADE_TEXAS;
            else if (plant_box.Text == "COLOMBIA") masterDB = Database.DECADE_COLOMBIA;

            TextInfo myTI = new CultureInfo("en-US", false).TextInfo;
            Console.WriteLine(myTI.ToTitleCase(plant_box.Text.ToLower()));
            plant_name = myTI.ToTitleCase(plant_box.Text.ToLower());
        }

        private void by_year_CheckedChanged(object sender, EventArgs e)
        {
            from_month.Enabled = !by_year.Checked;
        }
    }

    public class Customer
    {
        public string Code { get; set; }
        public string Currency { get; set; }
        public string Name { get; set; }
        public string Territory { get; set; }
        public int Count { get; set; }
        public double Sales { get; set; }
        public double LastYearSales { get; set; }
        public double YTD_Sales { get; set; }
        public double[] Budgets { get; set; }

        public Customer()
        {
            double[] temp = new double[12];
            for (int i = 0; i < 12; i++)
            {
                temp[i] = 0;
            }
            Budgets = temp;
        }

        public double Get_Budget_For_Month(int month)
        {
            // convert month number to period number
            int convert_month_to_period = month + 2;
            return Budgets[convert_month_to_period > 11 ? convert_month_to_period - 12 : convert_month_to_period];
        }

        public double Get_Budget_Total()
        {
            return RoundOff(Budgets.Sum());
        }

        public double RoundOff(double i)
        {
            return ((double)Math.Round(i / 10.0)) * 10;
        }

    }
}
*/