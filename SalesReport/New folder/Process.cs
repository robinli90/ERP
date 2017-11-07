using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;
using Excel = Microsoft.Office.Interop.Excel;

namespace SalesReport
{
    class Process
    {
        public List<Customer> custList = new List<Customer>();
        public int year = DateTime.Now.Year - 2000;

        public void Run()
        {
            // get data
            List<ExcoCustomer> allCustList = ExcoCustomerTable.Instance.GetAllCustomers();

            foreach (ExcoCustomer excoCust in allCustList)
            {
                Customer cust = new Customer(excoCust);
                custList.Add(cust);
            }

            // create excel object
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet micSheet = book.Worksheets[1];
            micSheet.Name = "Michigan 2013";
            Excel.Worksheet texSheet = book.Worksheets[2];
            texSheet.Name = "Texas 2013";
            Excel.Worksheet colSheet = book.Worksheets[3];
            colSheet.Name = "Colombia 2013";
            Excel.Worksheet marSheet = book.Worksheets.Add();
            marSheet.Name = "Markham 2013";
            Excel.Worksheet cbaSheet = book.Worksheets.Add();
            cbaSheet.Name = "Consolidate (order by actual)";
            Excel.Worksheet cbbSheet = book.Worksheets.Add();
            cbbSheet.Name = "Consolidate (order by budget)";
            // write to sheet
            FillSheet(marSheet, 1);
            FillSheet(micSheet, 3);
            FillSheet(texSheet, 5);
            FillSheet(colSheet, 4);
            custList.Sort(SortCba);
            FillSheetCon(cbaSheet);
            custList.Sort(SortCbb);
            FillSheetCon(cbbSheet);
            // output to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Sales Report 2013.xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }

        private void FillSheet(Excel.Worksheet sheet, int plant)
        {
            // insert title
            sheet.Cells[1, 1] = sheet.Name + " Sales Report (Without Surcharge)";
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            // build header
            int row = 3;
            int col = 1;
            sheet.Cells[row, col++] = "Cust #";
            sheet.Cells[row, col++] = "Cust Name";
            sheet.Cells[row, col++] = "Territory";
            sheet.Cells[row, col++] = "Currency";
            sheet.Cells[row, col++] = "2014 Budget";
            sheet.Cells[row, col++] = "Yearly 2013";
            sheet.Cells[row, col++] = "Jan";
            sheet.Cells[row, col++] = "Feb";
            sheet.Cells[row, col++] = "Mar";
            sheet.Cells[row, col++] = "Apr";
            sheet.Cells[row, col++] = "May";
            sheet.Cells[row, col++] = "Jun";
            sheet.Cells[row, col++] = "Jul";
            sheet.Cells[row, col++] = "Aug";
            sheet.Cells[row, col++] = "Sep";
            sheet.Cells[row, col++] = "Oct";
            sheet.Cells[row, col++] = "Nov";
            sheet.Cells[row, col++] = "Dec";
            Excel.Range headerRange = sheet.Cells.get_Range("A" + row.ToString(), "R" + row.ToString());
            headerRange.Font.Bold = true;
            headerRange.Cells.Interior.ColorIndex = 40;
            headerRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
            // write content
            Plant caTotal = new Plant();
            caTotal.curr = "CA";
            Plant usTotal = new Plant();
            usTotal.curr = "US";
            Plant cpTotal = new Plant();
            cpTotal.curr = "CP";
            foreach (Customer cust in custList)
            {
                if ((1 == plant && 0.0 == cust.mar.actualTotal) || (3 == plant && 0.0 == cust.mic.actualTotal) || (5 == plant && 0.0 == cust.tex.actualTotal) || (4 == plant && 0.0 == cust.col.actualTotal))
                {
                    continue;
                }
                col = 1;
                sheet.Cells[row, col].NumberFormat = "@";
                sheet.Cells[row, col++] = cust.id;
                sheet.Cells[row, col++] = cust.name;
                sheet.Cells[row, col++] = cust.terr;
                sheet.Cells[row, col++] = cust.curr;
                col++;
                if (1 == plant)
                {
                    WritePlant(sheet, cust.mar, row, col);
                    if (0 == cust.curr.CompareTo("CA"))
                    {
                        caTotal += cust.mar;
                    }
                    else if (0 == cust.curr.CompareTo("US"))
                    {
                        usTotal += cust.mar;
                    }
                    else if (0 == cust.curr.CompareTo("CP"))
                    {
                        cpTotal += cust.mar;
                    }
                }
                else if (3 == plant)
                {
                    WritePlant(sheet, cust.mic, row, col);
                    if (0 == cust.curr.CompareTo("CA"))
                    {
                        caTotal += cust.mic;
                    }
                    else if (0 == cust.curr.CompareTo("US"))
                    {
                        usTotal += cust.mic;
                    }
                    else if (0 == cust.curr.CompareTo("CP"))
                    {
                        cpTotal += cust.mic;
                    }
                }
                else if (5 == plant)
                {
                    WritePlant(sheet, cust.tex, row, col);
                    if (0 == cust.curr.CompareTo("CA"))
                    {
                        caTotal += cust.tex;
                    }
                    else if (0 == cust.curr.CompareTo("US"))
                    {
                        usTotal += cust.tex;
                    }
                    else if (0 == cust.curr.CompareTo("CP"))
                    {
                        cpTotal += cust.tex;
                    }
                }
                else if (4 == plant)
                {
                    WritePlant(sheet, cust.col, row, col);
                    if (0 == cust.curr.CompareTo("CA"))
                    {
                        caTotal += cust.col;
                    }
                    else if (0 == cust.curr.CompareTo("US"))
                    {
                        usTotal += cust.col;
                    }
                    else if (0 == cust.curr.CompareTo("CP"))
                    {
                        cpTotal += cust.col;
                    }
                }
                row += 2;
            }
            // write summary
            if (caTotal.actualTotal > 0.0)
            {
                WriteTotal(sheet, caTotal, row);
                row += 3;
            }
            if (usTotal.actualTotal > 0.0)
            {
                WriteTotal(sheet, usTotal, row);
                row += 3;
            }
            if (cpTotal.actualTotal > 0.0)
            {
                WriteTotal(sheet, cpTotal, row++);
                row += 3;
            }
            // write PESO summary
            if (4 == plant)
            {
                row++;
                col = 4;
                sheet.Cells[row, col++] = "Grand Total (CP):";
                col++;
                // totals in peso
                double[] grandTotal = new double[13];
                for (int i = 0; i < 13; i++)
                {
                    grandTotal[i] = 0.0;
                }
                for (int i = 0; i < 12; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(13, i + 1, false, plant);
                    grandTotal[i + 1] = ExcoExRate.GetToPESORate(calendar, "US") * usTotal.actual[i] + cpTotal.actual[i];
                    grandTotal[0] += grandTotal[i + 1];
                }
                for (int i = 0; i < 13; i++)
                {
                    sheet.Cells[row, col++] = grandTotal[i].ToString("C2");
                }
                // summary style
                Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            }
            // write CAD summary
            if (1 == plant)
            {
                row++;
                col = 4;
                sheet.Cells[row, col++] = "Grand Total (CA):";
                col++;
                // totals in CAD
                double[] grandTotal = new double[13];
                for (int i = 0; i < 13; i++)
                {
                    grandTotal[i] = 0.0;
                }
                for (int i = 0; i < 12; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(13, i + 1, false, plant);
                    grandTotal[i + 1] = ExcoExRate.GetToCADRate(calendar, "US") * usTotal.actual[i] + caTotal.actual[i];
                    grandTotal[0] += grandTotal[i + 1];
                }
                for (int i = 0; i < 13; i++)
                {
                    sheet.Cells[row, col++] = grandTotal[i].ToString("C2");
                }
                // summary style
                Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            }
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
        }

        private void WriteTotal(Excel.Worksheet sheet, Plant plant, int row)
        {
            row++;
            int col = 4;
            sheet.Cells[row, col++] = "TOTAL (" + plant.curr + "):";
            col++;
            WritePlant(sheet, plant, row, col);
        }

        private void WriteConTotal(Excel.Worksheet sheet, Plant plant, int row)
        {
            row++;
            int col = 5;
            sheet.Cells[row, col++] = "TOTAL (" + plant.curr + "):";
            col++;
            WriteConPlant(sheet, plant, row, col);
        }

        private void WritePlant(Excel.Worksheet sheet, Plant plant, int row, int col, bool needUnd = true)
        {
            // actual line
            sheet.Cells[row, col++] = plant.actualTotal.ToString("C2");
            for (int i = 0; i < 12; i++)
            {
                sheet.Cells[row, col++] = plant.actual[i].ToString("C2");
            }
            // budget line
            row++;
            col = 5;
            sheet.Cells[row, col++] = "Budget:";
            sheet.Cells[row, col++] = plant.budgetTotal.ToString("C2");
            for (int i = 0; i < 12; i++)
            {
                sheet.Cells[row, col++] = plant.budget[i].ToString("C2");
            }
            // adjust style
            Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            if (needUnd)
            {
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            }
        }

        private void WriteConPlant(Excel.Worksheet sheet, Plant plant, int row, int col, bool needUnd = true)
        {
            // actual line
            sheet.Cells[row, col++] = plant.actualTotal.ToString("C2");
            for (int i = 0; i < 12; i++)
            {
                sheet.Cells[row, col++] = plant.actual[i].ToString("C2");
            }
            // budget line
            row++;
            col = 6;
            sheet.Cells[row, col++] = "Budget:";
            sheet.Cells[row, col++] = plant.budgetTotal.ToString("C2");
            for (int i = 0; i < 12; i++)
            {
                sheet.Cells[row, col++] = plant.budget[i].ToString("C2");
            }
            // adjust style
            Excel.Range range = sheet.get_Range("A" + row.ToString(), "S" + row.ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            if (needUnd)
            {
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            }
        }

        private static int SortCba(Customer a, Customer b)
        {
            if (a.sum.actualTotalCAD == b.sum.actualTotalCAD)
            {
                return 0;
            }

            else if (a.sum.actualTotalCAD > b.sum.actualTotalCAD)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        private static int SortCbb(Customer a, Customer b)
        {
            if (a.sum.budgetTotalCAD == b.sum.budgetTotalCAD)
            {
                return 0;
            }

            else if (a.sum.budgetTotalCAD > b.sum.budgetTotalCAD)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        private void FillSheetCon(Excel.Worksheet sheet)
        {
            // insert title
            sheet.Cells[1, 1] = sheet.Name + " Sales Report (Without Surcharge)";
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            // build header
            int row = 3;
            int col = 1;
            sheet.Cells[row, col++] = "Cust #";
            sheet.Cells[row, col++] = "Cust Name";
            sheet.Cells[row, col++] = "Territory";
            sheet.Cells[row, col++] = "Currency";
            sheet.Cells[row, col++] = "Plant";
            sheet.Cells[row, col++] = "2014 Budget";
            sheet.Cells[row, col++] = "Yearly 2013";
            sheet.Cells[row, col++] = "Jan";
            sheet.Cells[row, col++] = "Feb";
            sheet.Cells[row, col++] = "Mar";
            sheet.Cells[row, col++] = "Apr";
            sheet.Cells[row, col++] = "May";
            sheet.Cells[row, col++] = "Jun";
            sheet.Cells[row, col++] = "Jul";
            sheet.Cells[row, col++] = "Aug";
            sheet.Cells[row, col++] = "Sep";
            sheet.Cells[row, col++] = "Oct";
            sheet.Cells[row, col++] = "Nov";
            sheet.Cells[row, col++] = "Dec";
            Excel.Range headerRange = sheet.Cells.get_Range("A" + row.ToString(), "S" + row.ToString());
            headerRange.Font.Bold = true;
            headerRange.Cells.Interior.ColorIndex = 40;
            headerRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
            // write content
            Plant caTotal = new Plant();
            caTotal.curr = "CA";
            Plant usTotal = new Plant();
            usTotal.curr = "US";
            Plant cpTotal = new Plant();
            cpTotal.curr = "CP";
            foreach (Customer cust in custList)
            {
                col = 1;
                sheet.Cells[row, col].NumberFormat = "@";
                sheet.Cells[row, col++] = cust.id;
                sheet.Cells[row, col++] = cust.name;
                sheet.Cells[row, col++] = cust.terr;
                sheet.Cells[row, col++] = cust.curr;
                sheet.Cells[row, col++] = "Total:";
                col++;
                WriteConPlant(sheet, cust.sum, row, col, false);
                row += 2;
                if (0 == cust.curr.CompareTo("CA"))
                {
                    caTotal += cust.sum;
                }
                else if (0 == cust.curr.CompareTo("US"))
                {
                    usTotal += cust.sum;
                }
                else if (0 == cust.curr.CompareTo("CP"))
                {
                    cpTotal += cust.sum;
                }
                if (cust.mar.actualTotal > 0.0 || cust.mar.budgetTotal > 0.0)
                {
                    col = 5;
                    sheet.Cells[row, col] = "Markham:";
                    col += 2;
                    WriteConPlant(sheet, cust.mar, row, col, false);
                    row += 2;
                }
                if (cust.mic.actualTotal > 0.0 || cust.mic.budgetTotal > 0.0)
                {
                    col = 5;
                    sheet.Cells[row, col] = "Michigan:";
                    col += 2;
                    WriteConPlant(sheet, cust.mic, row, col, false);
                    row += 2;
                }
                if (cust.tex.actualTotal > 0.0 || cust.tex.budgetTotal > 0.0)
                {
                    col = 5;
                    sheet.Cells[row, col] = "Texas:";
                    col += 2;
                    WriteConPlant(sheet, cust.tex, row, col, false);
                    row += 2;
                }
                if (cust.col.actualTotal > 0.0 || cust.col.budgetTotal > 0.0)
                {
                    col = 5;
                    sheet.Cells[row, col] = "Colombia";
                    col += 2;
                    WriteConPlant(sheet, cust.col, row, col, false);
                    row += 2;
                }
                sheet.get_Range("A" + (row - 1).ToString(), "S" + (row - 1).ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            }
            // write summary
            if (caTotal.actualTotal > 0.0)
            {
                WriteConTotal(sheet, caTotal, row);
                row += 3;
            }
            if (usTotal.actualTotal > 0.0)
            {
                WriteConTotal(sheet, usTotal, row);
                row += 3;
            }
            if (cpTotal.actualTotal > 0.0)
            {
                WriteConTotal(sheet, cpTotal, row++);
                row += 3;
            }
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
        }
    }
}
