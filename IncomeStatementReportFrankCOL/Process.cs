using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ExcoUtility;
using Excel = Microsoft.Office.Interop.Excel;

namespace IncomeStatementReportFrank
{
    class Process
    {
        // colombia
        public Plant Colombia;

        // period
        public int tp = 0;
        public int lp = 0;
        public int yr = 0;

        public Process(int period, int year)
        {
            tp = period;
            lp = period - 1;
            yr = year;
            ExcoCalendar calendar = new ExcoCalendar(yr, tp, true, 4);
            Colombia = new Plant(calendar, 4);
        }

        public void Run()
        {
            // create excel object
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            while (book.Worksheets.Count > 1)
            {
                ((Excel.Worksheet)(book.Worksheets[1])).Delete();
            }
            Excel.Worksheet colSheet = book.Worksheets[1];
            colSheet.Name = "Colombia at " + tp + "-" + yr;
            // write to excel object
            WritePlant(colSheet, Colombia);
            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Income Statement Report Colombia at " + tp + "-" + yr + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }

        private void WriteGroup(Excel.Worksheet sheet, ref int row, Group group)
        {
            int col = 1;
            sheet.Cells[row, col++] = group.name;
            sheet.Cells[row, col++] = group.tpActual.amountCA.ToString("C2");
            sheet.Cells[row, col++] = group.tpActualRatio.ToString("P2");
            sheet.Cells[row, col++] = group.lpActual.amountCA.ToString("C2");
            sheet.Cells[row, col++] = group.lpActualRatio.ToString("P2");
            sheet.Cells[row, col++] = group.tpBudget.amountCA.ToString("C2");
            sheet.Cells[row, col++] = group.tpBudgetRatio.ToString("P2");
            sheet.Cells[row, col++] = group.ytdActual.amountCA.ToString("C2");
            sheet.Cells[row, col++] = group.ytdActualRatio.ToString("P2");
            sheet.Cells[row, col++] = group.ytdBudget.amountCA.ToString("C2");
            sheet.Cells[row, col++] = group.ytdBudgetRatio.ToString("P2");
            row++;
        }

        private void WriteHeader(Excel.Worksheet sheet, ref int row)
        {
            // header
            sheet.Cells[row, 1] = "Name";
            sheet.Cells[row, 2] = "Period " + tp + " Actual";
            if (lp == 0)
            {
                sheet.Cells[row, 4] = "Last Period 12 Actual";
            }
            else
            {
                sheet.Cells[row, 4] = "Period " + lp + " Actual";
            }
            sheet.Cells[row, 6] = "Period " + tp + " Budget";
            sheet.Cells[row, 8] = "Y-T-D Actual";
            sheet.Cells[row, 10] = "Y-T-D Budget";
            Excel.Range range = sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 14;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
        }

        private void WritePlant(Excel.Worksheet sheet, Plant plant)
        {
            // insert title
            sheet.Cells[1, 1] = "Colombia Income Statement at " + tp + "-" + yr + " (CAD)";
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            // build header
            int row = 2;
            WriteHeader(sheet, ref row);
            // sales
            sheet.Cells[row, 1] = "SALES";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.ss.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.ss.total.name = "TOTAL SALES :";
            WriteGroup(sheet, ref row, plant.ss.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // cost of sales
            sheet.Cells[row, 1] = "COST OF SALES";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.cs.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.cs.total.name = "TOTAL COST OF SALES :";
            WriteGroup(sheet, ref row, plant.cs.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // direct labour
            sheet.Cells[row, 1] = "DIRECT LABOUR";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.dl.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.dl.total.name = "TOTAL DIRECT LABOUR:";
            WriteGroup(sheet, ref row, plant.dl.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // factory overhead
            sheet.Cells[row, 1] = "FACTORY OVERHEAD";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.fo.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.fo.total.name = "TOTAL FACTORY OVERHEAD:";
            WriteGroup(sheet, ref row, plant.fo.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // cost of goods
            int col = 1;
            sheet.Cells[row, col++] = "TOTAL COST OF GOODS:";
            sheet.Cells[row, col++] = (plant.cs.total.tpActual + plant.dl.total.tpActual + plant.fo.total.tpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.cs.total.tpActualRatio + plant.dl.total.tpActualRatio + plant.fo.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.cs.total.lpActual + plant.dl.total.lpActual + plant.fo.total.lpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.cs.total.lpActualRatio + plant.dl.total.lpActualRatio + plant.fo.total.lpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.cs.total.tpBudget + plant.dl.total.tpBudget + plant.fo.total.tpBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.cs.total.tpBudgetRatio + plant.dl.total.tpBudgetRatio + plant.fo.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.cs.total.ytdActual + plant.dl.total.ytdActual + plant.fo.total.ytdActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.cs.total.ytdActualRatio + plant.dl.total.ytdActualRatio + plant.fo.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.cs.total.ytdBudget + plant.dl.total.ytdBudget + plant.fo.total.ytdBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.cs.total.ytdBudgetRatio + plant.dl.total.ytdBudgetRatio + plant.fo.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // gross margin
            col = 1;
            sheet.Cells[row, col++] = "TOTAL GROSS MARGIN:";
            sheet.Cells[row, col++] = (plant.ss.total.tpActual + plant.cs.total.tpActual + plant.dl.total.tpActual + plant.fo.total.tpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.tpActualRatio + plant.cs.total.tpActualRatio + plant.dl.total.tpActualRatio + plant.fo.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.lpActual + plant.cs.total.lpActual + plant.dl.total.lpActual + plant.fo.total.lpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.lpActualRatio + plant.cs.total.lpActualRatio + plant.dl.total.lpActualRatio + plant.fo.total.lpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.tpBudget + plant.cs.total.tpBudget + plant.dl.total.tpBudget + plant.fo.total.tpBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.tpBudgetRatio + plant.cs.total.tpBudgetRatio + plant.dl.total.tpBudgetRatio + plant.fo.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdActual + plant.cs.total.ytdActual + plant.dl.total.ytdActual + plant.fo.total.ytdActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdActualRatio + plant.cs.total.ytdActualRatio + plant.dl.total.ytdActualRatio + plant.fo.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdBudget + plant.cs.total.ytdBudget + plant.dl.total.ytdBudget + plant.fo.total.ytdBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdBudgetRatio + plant.cs.total.ytdBudgetRatio + plant.dl.total.ytdBudgetRatio + plant.fo.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // Delivery and selling
            sheet.Cells[row, 1] = "DELIVERY AND SELLING";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.ds.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.ds.total.name = "TOTAL DELIVERY AND SELLING:";
            WriteGroup(sheet, ref row, plant.ds.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // general and administration
            sheet.Cells[row, 1] = "GENERAL AND ADMINISTRATION";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.ga.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.ga.total.name = "TOTAL GENERAL AND ADMINISTRATION:";
            WriteGroup(sheet, ref row, plant.ga.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // other expenses and income
            sheet.Cells[row, 1] = "OTHER EXPENSES AND INCOME";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in plant.oe.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            plant.oe.total.name = "TOTAL OTHER EXPENSES AND INCOME:";
            WriteGroup(sheet, ref row, plant.oe.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // expenses
            col = 1;
            sheet.Cells[row, col++] = "TOTAL EXPENSES:";
            sheet.Cells[row, col++] = (plant.ds.total.tpActual + plant.ga.total.tpActual + plant.oe.total.tpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ds.total.tpActualRatio + plant.ga.total.tpActualRatio + plant.oe.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ds.total.lpActual + plant.ga.total.lpActual + plant.oe.total.lpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ds.total.lpActualRatio + plant.ga.total.lpActualRatio + plant.oe.total.lpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ds.total.tpBudget + plant.ga.total.tpBudget + plant.oe.total.tpBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ds.total.tpBudgetRatio + plant.ga.total.tpBudgetRatio + plant.oe.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ds.total.ytdActual + plant.ga.total.ytdActual + plant.oe.total.ytdActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ds.total.ytdActualRatio + plant.ga.total.ytdActualRatio + plant.oe.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ds.total.ytdBudget + plant.ga.total.ytdBudget + plant.oe.total.ytdBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ds.total.ytdBudgetRatio + plant.ga.total.ytdBudgetRatio + plant.oe.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // net income
            col = 1;
            sheet.Cells[row, col++] = "TOTAL NET INCOME:";
            sheet.Cells[row, col++] = (plant.ss.total.tpActual + plant.cs.total.tpActual + plant.dl.total.tpActual + plant.fo.total.tpActual + plant.ds.total.tpActual + plant.ga.total.tpActual + plant.oe.total.tpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.tpActualRatio + plant.cs.total.tpActualRatio + plant.dl.total.tpActualRatio + plant.fo.total.tpActualRatio + plant.ds.total.tpActualRatio + plant.ga.total.tpActualRatio + plant.oe.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.lpActual + plant.cs.total.lpActual + plant.dl.total.lpActual + plant.fo.total.lpActual + plant.ds.total.lpActual + plant.ga.total.lpActual + plant.oe.total.lpActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.lpActualRatio + plant.cs.total.lpActualRatio + plant.dl.total.lpActualRatio + plant.fo.total.lpActualRatio + plant.ds.total.lpActualRatio + plant.ga.total.lpActualRatio + plant.oe.total.lpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.tpBudget + plant.cs.total.tpBudget + plant.dl.total.tpBudget + plant.fo.total.tpBudget + plant.ds.total.tpBudget + plant.ga.total.tpBudget + plant.oe.total.tpBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.tpBudgetRatio + plant.cs.total.tpBudgetRatio + plant.dl.total.tpBudgetRatio + plant.fo.total.tpBudgetRatio + plant.ds.total.tpBudgetRatio + plant.ga.total.tpBudgetRatio + plant.oe.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdActual + plant.cs.total.ytdActual + plant.dl.total.ytdActual + plant.fo.total.ytdActual + plant.ds.total.ytdActual + plant.ga.total.ytdActual + plant.oe.total.ytdActual).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdActualRatio + plant.cs.total.ytdActualRatio + plant.dl.total.ytdActualRatio + plant.fo.total.ytdActualRatio + plant.ds.total.ytdActualRatio + plant.ga.total.ytdActualRatio + plant.oe.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdBudget + plant.cs.total.ytdBudget + plant.dl.total.ytdBudget + plant.fo.total.ytdBudget + plant.ds.total.ytdBudget + plant.ga.total.ytdBudget + plant.oe.total.ytdBudget).amountCA.ToString("C2");
            sheet.Cells[row, col++] = (plant.ss.total.ytdBudgetRatio + plant.cs.total.ytdBudgetRatio + plant.dl.total.ytdBudgetRatio + plant.fo.total.ytdBudgetRatio + plant.ds.total.ytdBudgetRatio + plant.ga.total.ytdBudgetRatio + plant.oe.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            sheet.Cells.get_Range("A2", "A" + row.ToString()).HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;
            sheet.Cells.get_Range("B2", "K" + row.ToString()).HorizontalAlignment = Excel.XlHAlign.xlHAlignRight;
        }
    }
}