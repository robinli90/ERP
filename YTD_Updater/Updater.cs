using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ExcoUtility;
using IncomeStatementReport.Categories;
using System.IO;
using System.Runtime.InteropServices;
using IncomeStatementReport;
using System.Data.Odbc;
using Excel;
using ExcelWriter = Microsoft.Office.Interop.Excel;

namespace YTD_Updater
{
    public class Updater
    {

        // YTD Excel spreadsheet generator for Frank Parisi (EXCO Controller)
        // This generates the past 12 periods in sequential order from the selected period. The program will not automatically regenerate the data for the current period unless
        // Manually done. It is important to keep the values updated as the application needs to update.

        private ExcelWriter.Application excel = new ExcelWriter.Application();
        private object misValue = System.Reflection.Missing.Value;
        private ExcelWriter.Workbook workBook;
        // work sheets
        private ExcelWriter.Worksheet consolidatedIS;
        string currency_string = string.Empty;

        string[,] WORKSHEET_ARRAY = new string[200, 20];
        string[,] ANNUAL_DATA = new string[12, 400];
        string[,] ANNUAL_PERCENTAGE = new string[12, 400];
        string[,] BUDGET_CURRENT_PERIOD = new string[2, 400];
        string[,] YTD_BUDGET_CURRENT_PERIOD = new string[2, 400];
        string plant = "MICH"; //COL/TEX/MICH/CAD
        string fiscal_year = "15";
        string fiscal_month = "";
        string[] PERIOD_VALUES = new string[12];
        bool generate_files = false;
        int total_found_on_row = 0;
        bool native_currency = true;
        //bool generate_files = true;

        //public void Run()
        //{

        //}


        private double GET_BUDGET_EXCHANGE_RATE(int fiscal_year)
        {
            if (plant == "COL")
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1750;
                    case 11:
                        return 1750;
                    case 12:
                        return 1750;
                    case 13:
                        return 1750;
                    case 14:
                        return 1750;
                    case 15:
                        return 1750;
                    case 16:
                        return 1900;
                    default:
                        return 3000;
                }
            }
            else if (plant == "MICH" || plant == "TEX")
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1 / 1.111;
                    case 11:
                        return 1 / 1.111;
                    case 12:
                        return 1 / 1.111;
                    case 13:
                        return 1 / 1.111;
                    case 14:
                        return 1 / 1.111;
                    case 15:
                        return 1 / 1.111;
                    case 16:
                        return 1 / 1.111;
                    case 17:
                        return 1 / 1.25;
                }
            }
            return 1;
        }



        public void _SET_CURRENCY(bool _native_currency)
        {
            native_currency = _native_currency;
        }


        public void _GENERATE_FILES()
        {
            generate_files = true;
        }

        public void _SET_PLANT(string _plant)
        {
            plant = _plant;
        }

        public void _SET_FISCAL_YEAR(string _fiscal_year)
        {
            fiscal_year = _fiscal_year;
        }

        public void _SET_FISCAL_MONTH(string _fiscal_month)
        {
            fiscal_month = _fiscal_month;
        }

        public void Process()
        {
            
            int fiscalYear = Convert.ToInt32(fiscal_year);
            int fiscalMonth = 10;
            if (generate_files)
            {
                for (int i = 1; i < 13; i++)
                {
                    Console.Write("Retrieving information for period... " + (i).ToString() + "...");
                    //if (fiscalMonth > 12) fiscalMonth = 1;
                    //Process process = new Process((fiscalMonth > 9 ? fiscalYear - 1 : fiscalYear), fiscalMonth);
                    Process process = new Process(fiscalYear, i);
                    // create excel object
                    IncomeStatementReport.ExcelWriter excelWriter = new IncomeStatementReport.ExcelWriter(process);
                    excelWriter.FillSheets();
                    // write to file
                    string path = "";
                    path = "\\\\10.0.0.6\\shopdata\\Development\\Robin\\test\\New folder\\Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx";
                    File.Delete(path);
                    excelWriter.OutputToFile(path);
                    fiscalMonth++;
                    excel.Quit();
                    Console.WriteLine("Done");
                    Console.WriteLine("");
                }
                //}
            }

            Update(fiscalYear.ToString());
        }

        public void REGENERATE_DATA()
        {
            //if (DateTime.Now.Year == Convert.ToInt32("20" + fiscal_year))
            //{
            //for (int i = 1; i < 13; i++)
            //{
                int i = Convert.ToInt32(fiscal_month);//DateTime.Now.Month;
                Console.Write("Retrieving required information...");//d " + (i + 1).ToString() + "...");
                Process process = new Process(Convert.ToInt32(fiscal_year), i);
                // create excel object
                IncomeStatementReport.ExcelWriter excelWriter = new IncomeStatementReport.ExcelWriter(process);
                excelWriter.FillSheets();
                // write to file
                string path = "";
                path = "\\\\10.0.0.6\\shopdata\\Development\\Robin\\test\\New folder\\Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx";
                File.Delete(path);
                excelWriter.OutputToFile(path);
                Console.WriteLine("Done");
            //}

            //}
        }

        public void Update(string fiscalYear)
        {
            string plant_name = "";
            int workbook_number = 10;
            if (plant == "COL")
            {
                workbook_number = 10;
                plant_name = "Colombia";
                currency_string = "PESO";
            }
            else if (plant == "TEX")
            {
                workbook_number = 8;
                plant_name = "Texas";
                currency_string = "USD";
            }
            else if (plant == "MICH")
            {
                workbook_number = 6;
                plant_name = "Michigan";
                currency_string = "USD";
            }
            else if (plant == "MAR")
            {
                workbook_number = 4;
                plant_name = "Markham";
                currency_string = "CAD";
            }
            if (native_currency) workbook_number--;
            else currency_string = "CAD";


            for (int i = 0; i < 200; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    WORKSHEET_ARRAY[i, j] = "0";
                }
            }

            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 400; j++)
                {
                    ANNUAL_DATA[i, j] = "";
                    ANNUAL_PERCENTAGE[i, j] = "";
                }
            }


            //while (true)
            //{
            int month = Convert.ToInt32(fiscal_month);
            int year =  Convert.ToInt32(fiscal_year);
            double current_period_exch_rate = 0;
            for (int i = 1; i < 13; i++)
            {
                Console.WriteLine("Processing period: " + month.ToString() + "/" + year.ToString());// + "C:\\Sales Report\\Income Statement Report at " + i.ToString() + "-15.xlsx");
                 
                int Worksheet_NO = 1;

                string fileName = @"\\10.0.0.6\shopdata\Development\Robin\test\New folder\Income Statement Report at " +
                                  month.ToString() + "-" + year.ToString() + ".xlsx";

                //foreach (var worksheet in Workbook.Worksheets(@"C:\Sales Report\Income Statement Report at " + i.ToString() + "-" + fiscalYear.ToString() + ".xlsx"))
                foreach (var worksheet in Workbook.Worksheets(fileName))
                {
                    int row_count = 0;
                    int column_count = 0;

                    if (worksheet.Rows.Length > 0 && worksheet.Rows[0].Cells[0].Text.Contains(plant_name) && 
                        (
                            native_currency && worksheet.Rows[0].Cells[0].Text.Contains(currency_string) ||
                            !native_currency && worksheet.Rows[0].Cells[0].Text.Contains("CAD")
                        ))
                    {
                        foreach (var row in worksheet.Rows)
                            //for (int iz = 0; iz < 200; iz++)
                        {
                            row_count++;
                            column_count = 0;
                            foreach (var cell in row.Cells)
                            {
                                column_count++;
                                if (column_count < 4 || (i == 1 && (column_count == 6 || column_count == 7)) ||
                                    ((column_count == 6 || column_count == 10 ||
                                      column_count == 11))) //name/ actual/ percentage
                                    //if (column_count < 4 || (i == 1 && (column_count == 6 || column_count == 7)) || (i == 1 && (column_count == 10 || column_count == 11))) //name/ actual/ percentage
                                {
                                    if (column_count < 4)
                                    {
                                        if (total_found_on_row == 0 && cell.Text.Contains("TOTAL") &&
                                            !cell.Text.Contains("SALES") &&
                                            !cell.Text.Contains("SURCHARGE"))
                                        {
                                            total_found_on_row = row_count;
                                        }

                                        double a; double b;

                                        if (double.TryParse(WORKSHEET_ARRAY[row_count, column_count], out a) &&
                                            double.TryParse(cell.Text, out b))
                                        {
                                            /*
                                            a = Convert.ToDouble(
                                                WORKSHEET_ARRAY[row_count, column_count]);
                                            b = Convert.ToDouble(cell.Text);*/
                                            if (row_count == 2) // Get exchange rate
                                            {
                                                ANNUAL_DATA[i - 1, row_count] =
                                                    cell.Value.Length > 4 ? cell.Value : cell.Value;
                                                if (plant == "COL" && native_currency)
                                                    current_period_exch_rate = Convert.ToDouble(cell.Value);
                                                else if (native_currency)
                                                    current_period_exch_rate = 1;
                                                //Log.Append("    Current Exchange rate: " + current_period_exch_rate);
                                            }
                                            else if (column_count == 2)
                                            {
                                                ANNUAL_DATA[i - 1, row_count] = cell.Text;
                                                if (month <= Convert.ToInt32(fiscal_month))
                                                    WORKSHEET_ARRAY[row_count, column_count] =
                                                        (a + b).ToString();
                                            }
                                            else
                                            {
                                                ANNUAL_PERCENTAGE[i - 1, row_count] =
                                                    (Convert.ToDouble(cell.Value)).ToString("P2");
                                            }
                                        }
                                        else
                                        {
                                            WORKSHEET_ARRAY[row_count, column_count] = cell.Text;
                                        }
                                    }

                                    // Store budget information for current period
                                    if (i == 1 && column_count == 6)
                                    {
                                        BUDGET_CURRENT_PERIOD[0, row_count] =
                                            (Convert.ToDouble(cell.Value))
                                            .ToString(); /// current_period_exch_rate).ToString();
                                    }
                                    if (i == 1 && column_count == 7)
                                    {
                                        BUDGET_CURRENT_PERIOD[1, row_count] =
                                            (Convert.ToDouble(cell.Value)).ToString("P2");
                                    }

                                    // Store Y-T-D budget information for current period
                                    if (column_count == 6 && row_count > 4)
                                        //if (column_count == 10 && row_count > 4)
                                        //if (i == 1 && column_count == 10 && row_count > 4)
                                    {
                                        //YTD_BUDGET_CURRENT_PERIOD[0, row_count] = cell.Text;//add
                                        //if (Convert.ToDouble(cell.Text) > 1)
                                        if (month <= Convert.ToInt32(fiscal_month))
                                            //YTD_BUDGET_CURRENT_PERIOD[0, row_count] = (Convert.ToDouble(YTD_BUDGET_CURRENT_PERIOD[0, row_count]) + (Convert.ToDouble(cell.Text) / current_period_exch_rate)).ToString(); // ADD
                                            YTD_BUDGET_CURRENT_PERIOD[0, row_count] =
                                            (Convert.ToDouble(YTD_BUDGET_CURRENT_PERIOD[0, row_count]) +
                                             Convert.ToDouble(cell.Text)).ToString(); // ADD
                                        //if (row_count < 26)
                                        //Log.Append("    Ongoing total: " + YTD_BUDGET_CURRENT_PERIOD[0, row_count]);
                                    }
                                    if (i == 1 && column_count == 11 && row_count > 4) //get percentage
                                    {
                                        YTD_BUDGET_CURRENT_PERIOD[1, row_count] =
                                            (Convert.ToDouble(cell.Value)).ToString("P2");
                                    }
                                }
                            }
                        }
                        Console.WriteLine();
                    }

                    Worksheet_NO++;
                }
                
                // Adjust to last year
                PERIOD_VALUES[i - 1] = month.ToString();
                month--;
                if (month == 0)
                {
                    month = 12;
                    year--;
                }
            }
            //}

            Console.WriteLine("Summarizing information...");
            Console.WriteLine("Generating Excel file...");
            // EXCEL WRITE
            workBook = excel.Workbooks.Add(misValue);
            // create work sheets
            //consolidatedIS = workBook.Worksheets[3];
            consolidatedIS = workBook.Worksheets.Add();
            consolidatedIS.Name = "12-month " + plant_name + " (" + currency_string + ")";
            consolidatedIS.Columns[2].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[3].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[4].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[5].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[6].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[7].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[8].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[9].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[10].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[11].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[12].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[13].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[14].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[15].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[16].NumberFormat = "$#,##0.00;([Red]$#,##0.00)"; 
            //consolidatedIS.Columns[17].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[18].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[19].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[20].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[21].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[22].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[23].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[24].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[25].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[26].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            //consolidatedIS.Columns[25].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[28].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";
            consolidatedIS.Columns[29].NumberFormat = "##0.00%;-##0.00%";
            consolidatedIS.Columns[30].NumberFormat = "$#,##0.00;([Red]$#,##0.00)";

            if (workbook_number == 8) // If colombia
                consolidatedIS.Rows[3].NumberFormat = "0.000###";
            else
                consolidatedIS.Rows[3].NumberFormat = "0.###";



            int excel_row = 1;
            // title
            excel_row = WriteSheetHeader("Annual Summarized Income Statement for " + plant_name + " in " + currency_string + " (20" + fiscal_year + ")", consolidatedIS);
            // header
            excel_row++;
            excel_row = WriteHeader(consolidatedIS, excel_row);
            excel_row++;
            excel_row = WriteLines(consolidatedIS, excel_row);
            excel_row++;
            AdjustSheetStyle(consolidatedIS, excel_row);
            
            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Annual_Income_Statement_20" + fiscal_year + "(" + plant_name + ")_" + DateTime.Now.Hour.ToString() + "-" + DateTime.Now.Minute.ToString() + ".xlsx");
            File.Delete(path);
            workBook.SaveAs(path, ExcelWriter.XlFileFormat.xlOpenXMLWorkbook);
            //workBook.Close();
            //excel.Quit();
            _MARSHAL_KILL_EXCEL(path);
        }

        // Kills all excel 32-bit processes and opens Excel
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
            Marshal.ReleaseComObject(consolidatedIS);
            Marshal.ReleaseComObject(workBook);
            Marshal.ReleaseComObject(excel);
            consolidatedIS = null;
            workBook = null;
            excel = null;
            GC.GetTotalMemory(false);
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
            GC.GetTotalMemory(true);
            System.Diagnostics.Process.Start(path);
        }


        private int WriteSheetHeader(string title, ExcelWriter.Worksheet sheet)
        {
            int row = 1;
            sheet.Cells[row, 1] = title;
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "AE1").Merge();
            return row;

        }


        private int WriteHeader(ExcelWriter.Worksheet sheet, int row)
        {
            sheet.Cells[row, 1] = "Name";
            sheet.Cells[row, 2] = "Actual Per. " + PERIOD_VALUES[0];
            sheet.Cells[row, 4] = "Budget Per. " + PERIOD_VALUES[0];
            sheet.Cells[row, 6] = "Actual Per. " + PERIOD_VALUES[1];
            sheet.Cells[row, 8] = "Actual Per. " + PERIOD_VALUES[2];
            sheet.Cells[row, 10] = "Actual Per. " + PERIOD_VALUES[3];
            sheet.Cells[row, 12] = "Actual Per. " + PERIOD_VALUES[4];
            sheet.Cells[row, 14] = "Actual Per. " + PERIOD_VALUES[5];
            sheet.Cells[row, 16] = "Actual Per. " + PERIOD_VALUES[6];
            sheet.Cells[row, 18] = "Actual Per. " + PERIOD_VALUES[7];
            sheet.Cells[row, 20] = "Actual Per. " + PERIOD_VALUES[8];
            sheet.Cells[row, 22] = "Actual Per. " + PERIOD_VALUES[9];
            sheet.Cells[row, 24] = "Actual Per. " + PERIOD_VALUES[10];
            sheet.Cells[row, 26] = "Actual Per. " + PERIOD_VALUES[11];
            sheet.Cells[row, 28] = "Y-T-D Actual";
            sheet.Cells[row, 30] = "Y-T-D Budget";
            ExcelWriter.Range range = sheet.Cells.get_Range("A" + row.ToString(), "AE" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 12;
            range.Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeBottom].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
            return row;
        }

        private int WriteLines(ExcelWriter.Worksheet sheet, int g)
        {
            int other_sales_row = 9999;
            int Provision_Income_Tax = -1;
            int row = g;
            for (int i = 2; i < 199; i++)
            {
                if (!(WORKSHEET_ARRAY[i, 1] == "Name") && !(WORKSHEET_ARRAY[i, 1] == "0"))
                {
                    if (WORKSHEET_ARRAY[i, 1] == "PROVISION FOR INCOME TAX")
                    {
                        Provision_Income_Tax = i; // set index
                    }
                    if (WORKSHEET_ARRAY[i, 1] == "OTHER SALES")
                    {
                        other_sales_row = row;
                        sheet.Rows[row-1].Hidden = true;
                        sheet.Cells[row, 1] = "OTHER SALES";
                        row++;
                        goto Finish;
                    }
                    if (WORKSHEET_ARRAY[i, 1] == "PRODUCTION SALES")
                    {
                        sheet.Cells[row, 1] = "PRODUCTION SALES";
                        row++;
                        goto Finish;
                    }
                    if (WORKSHEET_ARRAY[i, 1].Contains("STEEL SURCHARGE") && row < other_sales_row)
                    {
                        sheet.Rows[row].Hidden = true;
                    }
                    sheet.Cells[row, 1] = WORKSHEET_ARRAY[i, 1].TrimEnd(":".ToCharArray()); //name
                    sheet.Cells[row, 2] = ANNUAL_DATA[0, i];
                    sheet.Cells[row, 3] = ANNUAL_PERCENTAGE[0, i];
                    if (!((WORKSHEET_ARRAY[i, 1] == "SALES") ||
                        (WORKSHEET_ARRAY[i, 1] == "") ||
                        (WORKSHEET_ARRAY[i, 1].Length < 5) ||
                        (WORKSHEET_ARRAY[i, 1] == null) ||
                        (WORKSHEET_ARRAY[i, 1] == "COST OF STEELS") ||
                        (WORKSHEET_ARRAY[i, 1] == "DIRECT LABOUR") ||
                        (WORKSHEET_ARRAY[i, 1] == "FACTORY OVERHEAD") ||
                        (WORKSHEET_ARRAY[i, 1] == "DELIVERY AND SELLING") ||
                        (WORKSHEET_ARRAY[i, 1] == "GENERAL AND ADMINISTRATION") ||
                        (WORKSHEET_ARRAY[i, 1] == "OTHER EXPENSE AND INCOME") ||
                        (i < 4)
                    ))
                        sheet.Cells[row, 4] = (Convert.ToDouble(BUDGET_CURRENT_PERIOD[0, i])); /// GET_BUDGET_EXCHANGE_RATE(Convert.ToInt32(fiscal_year))).ToString(); // BUDGET VALUE
                        //sheet.Cells[row, 4] = ((Convert.ToDouble(BUDGET_CURRENT_PERIOD[0, i])) / GET_BUDGET_EXCHANGE_RATE(Convert.ToInt32(fiscal_year))).ToString(); // BUDGET VALUE
                    sheet.Cells[row, 5] = BUDGET_CURRENT_PERIOD[1, i]; // BUDGET PERCENTAGE
                    sheet.Cells[row, 6] = ANNUAL_DATA[1, i];
                    sheet.Cells[row, 7] = ANNUAL_PERCENTAGE[1, i];
                    sheet.Cells[row, 8] = ANNUAL_DATA[2, i];
                    sheet.Cells[row, 9] = ANNUAL_PERCENTAGE[2, i];
                    sheet.Cells[row, 10] = ANNUAL_DATA[3, i];
                    sheet.Cells[row, 11] = ANNUAL_PERCENTAGE[3, i];
                    sheet.Cells[row, 12] = ANNUAL_DATA[4, i];
                    sheet.Cells[row, 13] = ANNUAL_PERCENTAGE[4, i];
                    sheet.Cells[row, 14] = ANNUAL_DATA[5, i];
                    sheet.Cells[row, 15] = ANNUAL_PERCENTAGE[5, i];
                    sheet.Cells[row, 16] = ANNUAL_DATA[6, i];
                    sheet.Cells[row, 17] = ANNUAL_PERCENTAGE[6, i];
                    sheet.Cells[row, 18] = ANNUAL_DATA[7, i];
                    sheet.Cells[row, 19] = ANNUAL_PERCENTAGE[7, i];
                    sheet.Cells[row, 20] = ANNUAL_DATA[8, i];
                    sheet.Cells[row, 21] = ANNUAL_PERCENTAGE[8, i];
                    sheet.Cells[row, 22] = ANNUAL_DATA[9, i];
                    sheet.Cells[row, 23] = ANNUAL_PERCENTAGE[9, i];
                    sheet.Cells[row, 24] = ANNUAL_DATA[10, i];
                    sheet.Cells[row, 25] = ANNUAL_PERCENTAGE[10, i];
                    sheet.Cells[row, 26] = ANNUAL_DATA[11, i];
                    sheet.Cells[row, 27] = ANNUAL_PERCENTAGE[11, i];
                    /*if (!((WORKSHEET_ARRAY[i, 1] == "SALES") ||
                        (WORKSHEET_ARRAY[i, 1] == "") ||
                        (WORKSHEET_ARRAY[i, 1].Length < 5) ||
                        (WORKSHEET_ARRAY[i, 1] == null) ||
                        (WORKSHEET_ARRAY[i, 1] == "COST OF STEELS") ||
                        (WORKSHEET_ARRAY[i, 1] == "DIRECT LABOUR") ||
                        (WORKSHEET_ARRAY[i, 1] == "FACTORY OVERHEAD") ||
                        (WORKSHEET_ARRAY[i, 1] == "DELIVERY AND SELLING") ||
                        (WORKSHEET_ARRAY[i, 1] == "GENERAL AND ADMINISTRATION") ||
                        (WORKSHEET_ARRAY[i, 1] == "OTHER EXPENSE AND INCOME") ||
                        (i < 4)
                    ))*/
                    sheet.Cells[row, 30] = YTD_BUDGET_CURRENT_PERIOD[0, i]; // YTD BUDGET VALUE
                    //sheet.Cells[row, 30] = (Convert.ToDouble(YTD_BUDGET_CURRENT_PERIOD[0, i]) / GET_BUDGET_EXCHANGE_RATE(Convert.ToInt32(fiscal_year))).ToString(); // YTD BUDGET VALUE

                    sheet.Cells[row, 31] = YTD_BUDGET_CURRENT_PERIOD[1, i]; // YTD BUDGET PERCENTAGE
                    if (!(WORKSHEET_ARRAY[i, 1].Contains("xchange")))
                        sheet.Cells[row, 28] = WORKSHEET_ARRAY[i, 2];

                    if (!((WORKSHEET_ARRAY[i, 1] == "SALES") || 
                        (WORKSHEET_ARRAY[i, 1] == "") || 
                        (WORKSHEET_ARRAY[i, 1].Length < 5) || 
                        (WORKSHEET_ARRAY[i, 1] == null) || 
                        (WORKSHEET_ARRAY[i, 1] == "COST OF STEELS")|| 
                        (WORKSHEET_ARRAY[i, 1] == "DIRECT LABOUR") || 
                        (WORKSHEET_ARRAY[i, 1] == "FACTORY OVERHEAD") || 
                        (WORKSHEET_ARRAY[i, 1] == "DELIVERY AND SELLING") || 
                        (WORKSHEET_ARRAY[i, 1] == "GENERAL AND ADMINISTRATION") || 
                        (WORKSHEET_ARRAY[i, 1] == "OTHER EXPENSE AND INCOME") || 
                        (i < 4)
                    ))
                    {
                        sheet.Cells[row, 29] = "=(AB" + (i).ToString() + "/AB" + total_found_on_row.ToString() + ")";
                    }

                    row++;

                    if (i == 162)
                        Console.WriteLine("");

                    if (WORKSHEET_ARRAY[i, 1].Contains("Exchange Rate")) //style last row
                    {
                        StyleOfSummary(sheet, row - 1);
                        StyleOfSummary(sheet, row, false);
                    }
                    else if (WORKSHEET_ARRAY[i, 1].Contains("TOTAL NET INCOME")) //end of document
                    {
                        StyleOfSummary(sheet, row-1, true);
                        StyleOfSummary2(sheet, row, true);
                        //if (plant != "MAR") all plants sept 11
                        //{
                            /*
                            row++;
                            sheet.Cells[row, 1] = "Addback: Provision for Income Taxes";
                            for (int r = 2; r < 32; r++) // r = rows
                            {
                                sheet.Cells[row, r] = "=" + GECN(r) + Provision_Income_Tax.ToString();//sheet.Cells[Provision_Income_Tax, r];
                            }
                            row++;
                            row++;
                            sheet.Cells[row, 1] = "Net Income Before Income Taxes";
                            for (int r = 2; r < 32; r++) // r = rows
                            {
                                try
                                {
                                    sheet.Cells[row, r] = "=(" + GECN(r) + (row - 4).ToString() + "-" + GECN(r) + (row - 2).ToString() + ")";

                                }
                                catch
                                {
                                }
                            }*/
                            //StyleOfSummary(sheet, row, true);
                            row++;
                            //StyleOfSummary2(sheet, row, true);
                            row++;
                            sheet.Cells[row, 1] = "Total Depreciation";
                            for (int r = 2; r < 32; r++) // r = rows
                            {
                                try
                                {
                                    if (native_currency || plant == "MAR")
                                    {
                                        string gg = "=SUM(" + GECN(r) + "58:" + GECN(r) + "60)+" +
                                            GECN(r) + "80+" + GECN(r) + "87+" + GECN(r) + "99+" + GECN(r) + "115+" + GECN(r) + "128";
                                        sheet.Cells[row, r] = gg;
                                    }
                                    else
                                    {
                                        string gg = "=SUM(" + GECN(r) + "59:" + GECN(r) + "61)+" +
                                            GECN(r) + "81+" + GECN(r) + "88+" + GECN(r) + "100+" + GECN(r) + "116+" + GECN(r) + "129";
                                        sheet.Cells[row, r] = gg;
                                    }
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e.ToString());
                                }
                            }
                            if (plant != "MAR") row = row + 500; //END OF FILE FOR NON-MARKHAM
                        //}
                        //else
                        if (plant == "MAR")
                        {
                            row += 3;
                            sheet.Cells[row, 1] = "Freight Recovery Rate";
                            for (int r = 2; r < 32; r++) // r = rows
                            {
                                if (r % 2 == 0)
                                {
                                    string gg = "=ABS(" + GECN(r) + "30/" + GECN(r) + "69*100)";
                                    sheet.Cells[row, r] = gg;
                                }
                            }
                            consolidatedIS.Rows[row].NumberFormat = "00\\%";

                            row ++;
                            sheet.Cells[row, 1] = "Net Freight Cost";
                            for (int r = 2; r < 32; r++) // r = rows
                            {
                                if (r % 2 == 0)
                                {
                                    string gg = "=" + GECN(r) + "30+" + GECN(r) + "69";
                                    sheet.Cells[row, r] = gg;
                                }
                            }
                            //consolidatedIS.Rows[row].NumberFormat = "00\\%";
                            row = row + 500;
                        }

                    }
                    else if (WORKSHEET_ARRAY[i, 1].Contains("TOTAL"))// && !(WORKSHEET_ARRAY[i, 1].Contains("TOTAL NET INCOME"))) //style last row
                    {
                        StyleOfSummary(sheet, row - 1);
                    }
                    else if (WORKSHEET_ARRAY[i, 1].Contains("TOTAL NET INCOME"))
                    {
                    }
                    else if (WORKSHEET_ARRAY[i, 1] == "SALES" ||
                                WORKSHEET_ARRAY[i, 1] == "COST OF STEELS" ||
                                WORKSHEET_ARRAY[i, 1] == "DIRECT LABOUR" ||
                                WORKSHEET_ARRAY[i, 1] == "FACTORY OVERHEAD" ||
                                WORKSHEET_ARRAY[i, 1] == "DELIVERY AND SELLING" ||
                                WORKSHEET_ARRAY[i, 1] == "GENERAL AND ADMINISTRATION" ||
                                WORKSHEET_ARRAY[i, 1] == "OTHER EXPENSE AND INCOME"
                            )
                    {
                        sheet.Cells.get_Range("A" + (row - 1).ToString()).Interior.ColorIndex = 27;
                    }
                    Finish: ;
                }
            }
            return row;
        }

        private void StyleOfSummary(ExcelWriter.Worksheet sheet, int row, bool bold=true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "AE" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "AE" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlContinuous;
        }


        private void StyleOfSummary2(ExcelWriter.Worksheet sheet, int row, bool bold = true)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "AE" + row.ToString()).Font.Bold = bold;
            sheet.Cells.get_Range("A" + row.ToString(), "AE" + row.ToString()).Cells.Borders[ExcelWriter.XlBordersIndex.xlEdgeTop].LineStyle = ExcelWriter.XlLineStyle.xlDouble;
        }

        private void AdjustSheetStyle(ExcelWriter.Worksheet sheet, int row)
        {
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignCenter;
            sheet.Cells.get_Range("A2", "A" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignLeft;
            sheet.Cells.get_Range("B2", "AE" + row.ToString()).HorizontalAlignment = ExcelWriter.XlHAlign.xlHAlignRight;
        }

        /// <summary>
        /// GET EXCEL COLUMN NAME
        /// </summary>
        /// <param name="columnNumber"></param>
        /// <returns></returns>
        private string GECN(int columnNumber) 
        {
            int dividend = columnNumber;
            string columnName = String.Empty;
            int modulo;

            while (dividend > 0)
            {
                modulo = (dividend - 1) % 26;
                columnName = Convert.ToChar(65 + modulo).ToString() + columnName;
                dividend = (int)((dividend - modulo) / 26);
            }

            return columnName;
        }
    }
}

/* OLD UPDATER

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ExcoUtility;
using IncomeStatementReport.Categories;
using IncomeStatementReport;
using System.Data.Odbc;

namespace YTD_Updater
{
    public class Updater
    {

        Dictionary<string, double> Aggregate_Acc_Totals = new Dictionary<string, double>();

        public void Update(int fiscalYear, int plantID)
        //public void Update(int plantID)
        {
            Plant plant = new Plant(plantID, "US");
            string plantNAME = "";
            string account_name = "";

            //Console.WriteLine("=================================================================");
            //Console.WriteLine("Analyzing for period: " + fiscalPeriod + ", 20" +(fiscalPeriod >= 10 ? fiscalYear - 1 : fiscalYear).ToString());

            //Console.WriteLine("=================================================================");
                
            Process new_process = new Process(fiscalYear, 10);
            List<Category> Cat_List = new List<Category>();

            Cat_List.Add(new_process.cs);
            Cat_List.Add(new_process.ds);
            Cat_List.Add(new_process.fo);
            Cat_List.Add(new_process.ga);
            Cat_List.Add(new_process.oe);
            Cat_List.Add(new_process.ss);
            Cat_List.Add(new_process.dl);
            Cat_List.Add(new_process.ng);

            foreach (Category category in Cat_List)
            {
                foreach (Group group in category.groupList)
                {

                    string curr = "US";

                    if (plantID == 3)
                    {
                        plant = group.plant03;
                        plantNAME = "mich";
                    }
                    else if (plantID == 5)
                    {
                        plant = group.plant05;
                        plantNAME = "tex";
                    }/*
                    else if (plantID == 4 || plantID == 48)
                    {
                        plant = group.plant04;
                        plantNAME = "col";
                        curr = "CP";
                    }
                    else
                        throw new Exception("Invalid plant " + plantID);

                    //curr = "CA";

                    account_name = group.name;

                    if (group.name.Contains("'"))
                    {
                        string temp_str = "";
                        foreach (char c in account_name)
                        {
                            temp_str = temp_str + c;
                            if (c.ToString() == "'")
                                temp_str = temp_str + "'";
                        }
                        account_name = temp_str;
                    }

                    if (account_name.Length > 0)
                    {
                        //foreach period in fiscal year//
                        for (int fiscalPeriod = 1; fiscalPeriod < 13; fiscalPeriod++)
                        //for (int fiscalYear = 12; fiscalYear < 18; fiscalYear++)
                        {
                            if (fiscalPeriod > 12) fiscalPeriod = 1;
                            if (Aggregate_Acc_Totals.ContainsKey(account_name))
                            {
                                Aggregate_Acc_Totals[account_name] = Aggregate_Acc_Totals[account_name] + plant.actualThisYearList[fiscalPeriod].GetAmount(curr);
                            }
                            else
                            {
                                Aggregate_Acc_Totals.Add(account_name, plant.actualThisYearList[fiscalPeriod].GetAmount(curr));
                            }
                            if (true)//(account_name.Contains("COLOMBIA SALES") && !account_name.Contains("SURCHARGE"))
                            {
                                Console.WriteLine("Plant: " + plant.plantID.ToString() + " for period: " + fiscalPeriod + ", " + (fiscalPeriod >= 10 ? fiscalYear - 1 : fiscalYear));
                                //Console.WriteLine("       " + account_name + " :US: " + plant.actualThisYearList[fiscalPeriod].GetAmount("US"));
                                Console.WriteLine("       " + account_name + " :CA: " + plant.actualThisYearList[fiscalPeriod].GetAmount("CA"));
                                //Console.WriteLine("       " + account_name + " :CP: " + plant.actualThisYearList[fiscalPeriod].GetAmount("CP"));
                                Console.WriteLine("       " + "AGG_TOTAL = " + Aggregate_Acc_Totals[account_name]);
                            }
                            fiscalPeriod++;
                        }
                    }
                }
            }

            // Insert final sum after loop
            foreach (KeyValuePair<string, double> account in Aggregate_Acc_Totals)
            {
                //Console.WriteLine("Checking account name: " + account.Key.ToString() + "___ with aggregate sum of: " + account.Value.ToString());
                string query = "";//update YTD_Values set " + plantNAME + "20" + fiscalYear + " = '" +
                // plant.actualThisYearList[fiscalPeriod].GetAmount("US").ToString() + "' where acc_name = '" + account_name + "'";

                ExcoODBC database = ExcoODBC.Instance;
                OdbcDataReader reader;
                database.Open(Database.DECADE_MARKHAM);
                try
                {
                    
                    query = "select top 1 * from YTD_Values where acc_name = '" + account_name + "'";
                    reader = database.RunQuery(query); 
                    Console.WriteLine(query);
                    string g = reader[0].ToString();
                     * 
                    query = "insert into YTD_Values (acc_name, " + plantNAME + "20" + fiscalYear + ") values ('" + account.Key.ToString() + "', '" +
                            Math.Round(account.Value, 2).ToString() + "')";
                    //Console.WriteLine(query);
                    reader = database.RunQuery(query);
                    reader.Close();
                }
                catch // acc name doesn't exist, insert new account
                {
                    query = "update YTD_Values set " + plantNAME + "20" + fiscalYear + " = '" +
                                Math.Round(account.Value, 2).ToString() + "' where acc_name = '" + account.Key.ToString()
 + "'";
                    reader = database.RunQuery(query);

                    reader.Close();
                }
            }
            while(true ){}

        }

    }
}

*/

