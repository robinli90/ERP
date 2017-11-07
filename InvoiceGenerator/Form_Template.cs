using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Data.Odbc;
using ExcelWriter = Microsoft.Office.Interop.Excel;

namespace InvoiceGenerator
{
    public partial class Form_Template : Form
    { 
        Size Start_Size = new Size();
        int Start_Location_Offset = 45;
        public Database masterDB = Database.DECADE_MARKHAM;
        private Dictionary<string, string> Price_List = new Dictionary<string, string>();

        public Form_Template()
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
                   to_month.Items.Add(i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.AddMonths(-1).Month.ToString("D2");
            to_month.Text = DateTime.Now.Month.ToString("D2");


            for (int i = 10; i <= Convert.ToInt32(DateTime.Now.Year.ToString().Substring(2, 2)) + 1; i++)
            {
                from_year.Items.Add("20" + i.ToString("D2"));
                to_year.Items.Add("20" + i.ToString("D2"));
            }

            from_month.Text = DateTime.Now.AddMonths(-1).Month.ToString("D2");
            to_month.Text = DateTime.Now.Month.ToString("D2");
            from_year.Text = DateTime.Now.Year.ToString();
            to_year.Text = DateTime.Now.Year.ToString();

            plant_box.Items.Add("MARKHAM");
            plant_box.Items.Add("MICHIGAN");
            plant_box.Items.Add("TEXAS");
            plant_box.Items.Add("COLOMBIA");
            //plant_box.Items.Add("BRASIL");

            plant_box.Text = "MARKHAM";
            plant_name = "MARKHAM";

            // Memo Tooltip (Hover)
            ToolTip ToolTip1 = new ToolTip();
            ToolTip1.InitialDelay = 1;
            ToolTip1.ReshowDelay = 1;
            ToolTip1.SetToolTip(Add_button, "Generate");
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



        public void Generate_Invoice_Register()
        {
            Price_List = new Dictionary<string, string>();
            Invoice_List = new List<Invoice>();
            excel = new ExcelWriter.Application();
            misValue = System.Reflection.Missing.Value;

            string to_date = DateTime.DaysInMonth(Convert.ToInt32(to_year.Text), Convert.ToInt32(to_month.Text)).ToString();
            //if (to_month.Text == from_month.Text) to_date = "31";
            ExcoODBC instance = ExcoODBC.Instance;
            /*
            string query = "select a.ordernumber, a.invoicedate, a.invoicenumber, a.roughweight, a.nitrideweight, c.cmsNumber, b.name, total, pricelist " + 
                            "from d_order as a, d_customer as b, d_customermapping as c where (a.note not like '%cancel%' or a.note is null) and a.customerpo" + 
                            " not like '%cancel%' and invoicedate between '" + from_year.Text + "-" + from_month.Text + "-" + "01' and '" + to_year.Text + "-" + to_month.Text + "-" + to_date +
                            "' and a.customercode = b.customercode and a.customercode = c.decadecode and c.cmsNumber like '%S%' order by accountset desc, a.customercode asc";*/

            string query = "select a.ordernumber, a.invoicedate, a.invoicenumber, a.roughweight, a.nitrideweight, (select top 1 cmsNumber from d_customermapping as c where " +
                            "a.customercode = c.decadecode order by cmsnumber desc) , b.name, total, pricelist from d_order as a, d_customer as b " +
                            "where (a.note not like '%cancel%' or a.note is null) and (a.customerpo not like '%cancel%' or a.customerpo is null) and invoicedate between '" + 
                            from_year.Text + "-" + from_month.Text + "-" + "01' and '" + to_year.Text + "-" + to_month.Text + "-" + to_date + "' " +
                            "and a.customercode = b.customercode" + (bycust.Checked ? " and b.name like '%" + cust_box.Text +"%'" : "") + " order by accountset desc, a.customercode asc";

            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                Invoice inv = new Invoice();
                inv.Order_Number = reader[0].ToString().Trim();
                inv.InvoiceDate = reader[1].ToString().Trim();
                inv.Invoice_Number = reader[2].ToString().Trim();
                inv.SLB = reader[3].ToString().Trim();
                inv.NLB = reader[4].ToString().Trim();
                inv.Customer_Number = reader[5].ToString().Trim().Trim();
                inv.Customer_Name = reader[6].ToString().Trim();
                inv.Total_Amount = reader[7].ToString().Trim();
                inv.Customer_Class = reader[8].ToString().Trim();
                //inv.SubTotal = reader[9].ToString().Trim();
                inv.Plant_Code = plant_name == "MARKHAM" ? "001" : plant_name == "MICHIGAN" ? "002" : plant_name == "TEXAS" ? "005" : "004";
                inv.Invoice_Line_Number = "1";
                inv.RefDB = masterDB;

                Invoice_List.Add(inv);
            }

            reader.Close();

            foreach (Invoice inv3 in Invoice_List)
            {
                inv3.Populate_Parts();
            }


            ExcoODBC solarsoft2 = ExcoODBC.Instance;
            string query23 = "select * from cmsdat.code where A2 = 'KK'";
            solarsoft2.Open(Database.CMSDAT);
            OdbcDataReader reader23 = solarsoft2.RunQuery(query23);
            // get main data
            while (reader23.Read())
            {
                try
                {
                    Price_List.Add(reader23["A9"].ToString().Trim(), reader23["A30"].ToString().Trim());
                }
                catch
                {
                }
            }
            reader23.Close();
            
            foreach (Invoice inv2 in Invoice_List)
            {
                inv2.Customer_Class_Desc = Price_List[inv2.Customer_Class];
            }

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

            foreach (Invoice inv4 in Invoice_List)
            {
                ExcoODBC solarsoft = ExcoODBC.Instance;
                string query2 = "select * from cmsdat.cust where BVCUST = '" + inv4.Customer_Number + "'";
                solarsoft.Open(Database.CMSDAT);
                OdbcDataReader reader2 = solarsoft.RunQuery(query2);
                // get main data
                while (reader2.Read())
                {
                    inv4.Currency_Code = reader2["BVCURR"].ToString().Trim();
                    inv4.Terms_Code = reader2["BVTERM"].ToString().Trim();
                    inv4.FOB_Code = reader2["BVFOBC"].ToString().Trim();
                    inv4.Salesman_Code = reader2["BVSALM"].ToString().Trim();
                    inv4.Prov_State_Code = reader2["BVPRCD"].ToString().Trim();
                    inv4.Country = reader2["BVCTRY"].ToString().Trim();
                    //inv4.Customer_Class_Desc = reader2["A30"].ToString().Trim();
                }
                reader2.Close();
            }

            workBook = excel.Workbooks.Add(misValue);
            Invoices = workBook.Worksheets.Add();
            Invoices.Name = "Invoice Register for " + plant_name;

            int excel_row = 1;

            // title
            excel_row = WriteSheetHeader("Invoice Register for " + plant_name, Invoices);
            excel_row++;
            excel_row = WriteHeader(Invoices, excel_row);
            excel_row++;
            excel_row = WriteLines(Invoices, excel_row);
            excel_row++;
            AdjustSheetStyle(Invoices, excel_row);

            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Invoice Register for " + plant_name + ".xlsx");
            File.Delete(path);
            workBook.SaveAs(path, ExcelWriter.XlFileFormat.xlOpenXMLWorkbook);
            _MARSHAL_KILL_EXCEL(path);

        }


        private int WriteLines(ExcelWriter.Worksheet sheet, int g)
        {
            int row = g;
            foreach (Invoice inv in Invoice_List)
            {
                StyleOfSummary(sheet, row, false);

                foreach (KeyValuePair<int, List<Part>> line in inv.Part_List)
                {
                    foreach (Part inv2 in line.Value)
                    {

                        if (inv2.Part_Desc != "TOTAL")
                        {
                            sheet.Cells[row, 1] = inv.InvoiceDate.Split(new string[] { " " }, StringSplitOptions.None)[0];
                            sheet.Cells[row, 2] = inv.Invoice_Number;
                            sheet.Cells[row, 3] = inv.Invoice_Line_Number;
                            sheet.Cells[row, 4] = inv.Customer_Number;
                            sheet.Cells[row, 5] = inv.Customer_Name;
                            sheet.Cells[row, 6] = inv.Plant_Code;
                            //sheet.Cells[row, 7] = inv;
                            //sheet.Cells[row, 8] = inv;
                            //sheet.Cells[row, 9] = inv;
                            //sheet.Cells[row, 10] = inv;

                            //sheet.Cells[row, 10] = inv.SubTotal;
                            sheet.Cells[row, 12] = inv.Total_Amount;
                            sheet.Cells[row, 13] = inv.SLB;
                            sheet.Cells[row, 14] = inv.NLB;
                            sheet.Cells[row, 15] = inv.Customer_Class_Desc;
                            sheet.Cells[row, 16] = inv.Customer_Class;
                            sheet.Cells[row, 17] = inv.Currency_Code;
                            sheet.Cells[row, 18] = inv.Terms_Code;
                            sheet.Cells[row, 19] = inv.FOB_Code;
                            sheet.Cells[row, 20] = inv.Salesman_Code;
                            sheet.Cells[row, 21] = inv.Prov_State_Code;
                            sheet.Cells[row, 22] = inv.Country;
                        }

                        sheet.Cells[row, 7] = inv2.Part_Number;
                        sheet.Cells[row, 8] = inv2.Part_Desc != "TOTAL" ? inv2.Part_Desc : "";
                        sheet.Cells[row, 9] = inv2.Part_Quantity;
                        sheet.Cells[row, 10] = inv2.Part_SubTotal;
                        sheet.Cells[row, 11] = inv2.Part_Amount;
                        //sheet.Cells[row, 12] = inv;
                        row++;
                    }
                }
                StyleTotal(sheet, row, true);
                row++;
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
            sheet.Cells.get_Range("A1", "V1").Merge();
            return row;

        }

        private int WriteHeader(ExcelWriter.Worksheet sheet, int row)
        {
            sheet.Cells[row, 1] = "Invoice Date";
            sheet.Cells[row, 2] = "Invoice No.";
            sheet.Cells[row, 3] = "Invoice Line No.";
            sheet.Cells[row, 4] = "Customer No. (Bill-To-Code)";
            sheet.Cells[row, 5] = "Customer Name";
            sheet.Cells[row, 6] = "Plant Code";
            sheet.Cells[row, 7] = "Part #";
            sheet.Cells[row, 8] = "Description";
            sheet.Cells[row, 9] = "Quantity";
            sheet.Cells[row, 10] = "Unit Price";
            sheet.Cells[row, 11] = "Amount";
            sheet.Cells[row, 12] = "Total Value";
            sheet.Cells[row, 13] = "SLB";
            sheet.Cells[row, 14] = "NLB";
            sheet.Cells[row, 15] = "Customer Class Desc.";
            sheet.Cells[row, 16] = "Customer Class";
            sheet.Cells[row, 17] = "Currency Code";
            sheet.Cells[row, 18] = "Terms Code";
            sheet.Cells[row, 19] = "FOB Code";
            sheet.Cells[row, 20] = "Salesman Code";
            sheet.Cells[row, 21] = "Prov/State Code";
            sheet.Cells[row, 22] = "Country";
            ExcelWriter.Range range = sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString());
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
            Generate_Invoice_Register();
        }


        private void _MARSHAL_KILL_EXCEL(string path)
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
            System.Diagnostics.Process.Start(path);
        }


        private void StyleOfSummary(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "V" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
        }

        private void StyleTotal(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("K" + row.ToString(), "K" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("K" + (row-1).ToString(), "K" + (row-1).ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
            sheet.Cells.get_Range("K" + row.ToString(), "K" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
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

        private void plant_box_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (plant_box.Text == "MARKHAM") masterDB = Database.DECADE_MARKHAM;
            else if (plant_box.Text == "MICHIGAN") masterDB = Database.DECADE_MICHIGAN;
            else if (plant_box.Text == "TEXAS") masterDB = Database.DECADE_TEXAS;
            else if (plant_box.Text == "COLOMBIA") masterDB = Database.DECADE_COLOMBIA;
            plant_name = plant_box.Text;
        }

        private void from_month_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void to_month_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void cust_box_TextChanged(object sender, EventArgs e)
        {
            bycust.Checked = cust_box.Text.Length > 0;
        }
    }

    public class Invoice
    {
        public string InvoiceDate { get; set; }
        public string Order_Number { get; set; }
        public string Invoice_Number { get; set; }
        public string Invoice_Line_Number { get; set; }
        public string Customer_Number { get; set; }
        public string Customer_Name { get; set; }
        public string Plant_Code { get; set; }
        public string Total_Amount { get; set; }
        public string SubTotal { get; set; }
        public string SLB { get; set; }
        public string NLB { get; set; }
        public string Customer_Class_Desc { get; set; }
        public string Customer_Class { get; set; }
        public string Currency_Code { get; set; }
        public string Terms_Code { get; set; }
        public string FOB_Code { get; set; }
        public string Salesman_Code { get; set; }
        public string Prov_State_Code { get; set; }
        public string Country { get; set; }
        public Dictionary<int, List<Part>> Part_List { get; set; }
        public Database RefDB = Database.NULL;

        public Invoice()
        {
        }

        public void Populate_Parts()
        {
            this.Part_List = new Dictionary<int, List<Part>>();

            #region Get die parts (not including extra charges)
            ExcoODBC instance = ExcoODBC.Instance;
            //string query = "select line, qty, description, CONVERT(varchar, cast(baseprice as money), 1) as amt, dienumber as die# from d_orderitem where ordernumber = '" + Order_Number + "' order by line asc";
            string query = "select a.line, a.qty, a.description, CONVERT(varchar, cast(a.baseprice as money), 1) as amt, a.dienumber as die#, b.price as subtotal from d_orderitem as a, d_orderitem as b where a.description = b.description and a.ordernumber = b.ordernumber and a.ordernumber = '" + Order_Number + "' order by a.line asc";
            instance.Open(RefDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                this.Part_List.Add(Convert.ToInt32(reader[0].ToString().Trim()), new List<Part>() {
                    new Part() {
                        Part_Desc = reader[2].ToString().Trim(), 
                        Part_Quantity = reader[1].ToString().Trim(), 
                        Part_Amount = reader[3].ToString().Trim(), 
                        Part_Number = reader[4].ToString().Trim(),
                        Part_SubTotal = reader[5].ToString().Trim()
                    }
                });
            }
            #endregion
            
            #region Get extra charges
            instance = ExcoODBC.Instance;
            query = "select line, chargename, CONVERT(varchar, cast(price as money), 1), qty from d_orderitemcharges where ordernumber = '" + Order_Number + "' order by line asc";
            instance.Open(RefDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    Part_List[Convert.ToInt32(reader[0].ToString().Trim())].Add(
                        new Part()
                        {
                            Part_Desc = reader[1].ToString().Trim(),
                            Part_Quantity = reader[3].ToString().Trim(),
                            Part_Amount = reader[2].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                catch
                {
                }
            }
            #endregion

            // Add variable line for the end
            Part_List.Add(999, new List<Part>());

            #region Get freight, surcharge, taxes, fasttrack
            instance = ExcoODBC.Instance;
            query = "select freight as Freight, CONVERT(varchar, cast(total as money), 1) as Total, gst as GST, fasttrackcharge as FastTrack, discountamount as Discount, CONVERT(varchar, cast(total-gst-freight-fasttrack+discountamount as money), 1) as subtotal, steelsurcharge as surcharge from d_order where ordernumber = '" + Order_Number + "'";
            instance.Open(RefDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                // Freight 
                if (Convert.ToDouble(reader[0].ToString().Trim()) > 0)
                {
                    Part_List[999].Add(
                        new Part()
                        {
                            Part_Desc = "FREIGHT",
                            Part_Quantity = "",
                            Part_Amount = reader[0].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                // GST 
                if (Convert.ToDouble(reader[2].ToString().Trim()) > 0)
                {
                    Part_List[999].Add(
                        new Part()
                        {
                            Part_Desc = "GST",
                            Part_Quantity = "",
                            Part_Amount = reader[2].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                // Fast track 
                if (Convert.ToDouble(reader[3].ToString().Trim()) > 0)
                {
                    Part_List[999].Add(
                        new Part()
                        {
                            Part_Desc = "FAST TRACK",
                            Part_Quantity = "",
                            Part_Amount = reader[3].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                // Discount 
                if (Convert.ToDouble(reader[4].ToString().Trim()) > 0)
                {
                    Part_List[999].Add(
                        new Part()
                        {
                            Part_Desc = "DISCOUNT",
                            Part_Quantity = "",
                            Part_Amount = "-" + reader[4].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                // Discount 
                if (Convert.ToDouble(reader[6].ToString().Trim()) > 0)
                {
                    Part_List[999].Add(
                        new Part()
                        {
                            Part_Desc = "STEEL SURCHARGE",
                            Part_Quantity = "",
                            Part_Amount = reader[6].ToString().Trim(),
                            Part_Number = "",
                            Part_SubTotal = ""
                        }
                    );
                }
                // Total 
                Part_List[999].Add(
                    new Part()
                    {
                        Part_Desc = "TOTAL",
                        Part_Quantity = "",
                        Part_Amount = reader[1].ToString().Trim(),
                        Part_Number = "",
                        Part_SubTotal = ""
                    }
                );
            }
            #endregion
            reader.Close();
        }
    }

    public class Part
    {
        public string Part_Desc { get; set; }
        public string Part_Number { get; set; }
        public string Part_Quantity { get; set; }
        public string Part_Amount { get; set; }
        public string Part_SubTotal { get; set; }
    }
}
