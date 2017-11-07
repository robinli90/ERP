using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;
using Excel = Microsoft.Office.Interop.Excel;

namespace PL_Michigan
{
    public partial class MainDialog : Form
    {
        // cost of sales
        public Category cs = new Category();
        // delivery selling
        public Category ds = new Category();
        // factory overhead
        public Category fo = new Category();
        // general admin
        public Category ga = new Category();
        // other expense
        public Category oe = new Category();
        // sales
        public Category ss = new Category();
        // direct labour
        public Category dl = new Category();
        // calendar
        public ExcoCalendar calendar = new ExcoCalendar();

        public MainDialog()
        {
            InitializeComponent();
        }

        private void buttonRun_Click(object sender, EventArgs e)
        {
            if (radioButtonAllMonth.Checked)
            {
                int i = 1;
                while (i <= 12)
                {
                    cs = new Category();
                    ds = new Category();
                    fo = new Category();
                    ga = new Category();
                    oe = new Category();
                    ss = new Category();
                    dl = new Category();
                    calendar = new ExcoCalendar(14, i, true, 3);
                    BuildCategories();
                    // get ratio
                    cs.GetRatio(ss.total);
                    ds.GetRatio(ss.total);
                    fo.GetRatio(ss.total);
                    ga.GetRatio(ss.total);
                    oe.GetRatio(ss.total);
                    dl.GetRatio(ss.total);
                    ss.GetRatio(ss.total);
                    // create excel object
                    Excel.Application excel = new Excel.Application();
                    object misValue = System.Reflection.Missing.Value;
                    Excel.Workbook book = excel.Workbooks.Add(misValue);
                    Excel.Worksheet sheet = book.Worksheets[1];
                    sheet.Name = "Michigan at " + calendar.GetFiscalMonth().ToString("D2") + "-" + calendar.GetFiscalYear().ToString("D2");
                    // write to excel object
                    WriteAccounts(sheet);
                    // write to file
                    string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Michigan Income Statement Report at " + calendar.GetFiscalMonth().ToString("D2") + "-" + calendar.GetFiscalYear().ToString("D2") + ".xlsx");
                    File.Delete(path);
                    book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
                    excel.Quit();
                    System.Diagnostics.Process.Start(path);
                    i++;
                }
            }
            else
            {
                int i = Convert.ToInt32(comboBoxPeriod.Text);
                calendar = new ExcoCalendar(14, i, true, 3);
                BuildCategories();
                // get ratio
                cs.GetRatio(ss.total);
                ds.GetRatio(ss.total);
                fo.GetRatio(ss.total);
                ga.GetRatio(ss.total);
                oe.GetRatio(ss.total);
                dl.GetRatio(ss.total);
                ss.GetRatio(ss.total);
                // create excel object
                Excel.Application excel = new Excel.Application();
                object misValue = System.Reflection.Missing.Value;
                Excel.Workbook book = excel.Workbooks.Add(misValue);
                Excel.Worksheet sheet = book.Worksheets[1];
                sheet.Name = "Michigan at " + calendar.GetFiscalMonth().ToString("D2") + "-" + calendar.GetFiscalYear().ToString("D2");
                // write to excel object
                WriteAccounts(sheet);
                // write to file
                string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Michigan Income Statement Report at " + calendar.GetFiscalMonth().ToString("D2") + "-" + calendar.GetFiscalYear().ToString("D2") + ".xlsx");
                File.Delete(path);
                book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
                excel.Quit();
                System.Diagnostics.Process.Start(path);
            }
        }

        private void WriteGroup(Excel.Worksheet sheet, ref int row, Group group)
        {
            int col = 1;
            sheet.Cells[row, col++] = group.name;
            sheet.Cells[row, col++] = group.tpActual.amountUS.ToString("C2");
            sheet.Cells[row, col++] = group.tpActualRatio.ToString("P2");
            sheet.Cells[row, col++] = group.tpBudget.amountUS.ToString("C2");
            sheet.Cells[row, col++] = group.tpBudgetRatio.ToString("P2");
            sheet.Cells[row, col++] = group.ytdActual.amountUS.ToString("C2");
            sheet.Cells[row, col++] = group.ytdActualRatio.ToString("P2");
            sheet.Cells[row, col++] = group.ytdBudget.amountUS.ToString("C2");
            sheet.Cells[row, col++] = group.ytdBudgetRatio.ToString("P2");
            row++;
        }

        private void WriteHeader(Excel.Worksheet sheet, ref int row)
        {
            // header
            sheet.Cells[row, 1] = "Name";
            sheet.Cells[row, 2] = "Period " + calendar.GetFiscalMonth().ToString("D2") + " Actual";
            sheet.Cells[row, 4] = "Period " + calendar.GetFiscalMonth().ToString("D2") + " Budget";
            sheet.Cells[row, 6] = "Y-T-D Actual";
            sheet.Cells[row, 8] = "Y-T-D Budget";
            Excel.Range range = sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 14;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
        }

        private void WriteAccounts(Excel.Worksheet sheet)
        {
            // insert title
            sheet.Cells[1, 1] = "Michigan Income Statement at " + calendar.GetFiscalMonth().ToString("D2") + "-" + calendar.GetFiscalYear().ToString("D2") + " (USD)";
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
            foreach (Group group in ss.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            ss.total.name = "TOTAL SALES :";
            WriteGroup(sheet, ref row, ss.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // cost of sales
            sheet.Cells[row, 1] = "COST OF SALES";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in cs.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            cs.total.name = "TOTAL COST OF SALES :";
            WriteGroup(sheet, ref row, cs.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // direct labour
            sheet.Cells[row, 1] = "DIRECT LABOUR";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in dl.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            dl.total.name = "TOTAL DIRECT LABOUR:";
            WriteGroup(sheet, ref row, dl.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // factory overhead
            sheet.Cells[row, 1] = "FACTORY OVERHEAD";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in fo.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            fo.total.name = "TOTAL FACTORY OVERHEAD:";
            WriteGroup(sheet, ref row, fo.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // cost of goods
            int col = 1;
            sheet.Cells[row, col++] = "TOTAL COST OF GOODS:";
            sheet.Cells[row, col++] = (cs.total.tpActual + dl.total.tpActual + fo.total.tpActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (cs.total.tpActualRatio + dl.total.tpActualRatio + fo.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (cs.total.tpBudget + dl.total.tpBudget + fo.total.tpBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (cs.total.tpBudgetRatio + dl.total.tpBudgetRatio + fo.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (cs.total.ytdActual + dl.total.ytdActual + fo.total.ytdActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (cs.total.ytdActualRatio + dl.total.ytdActualRatio + fo.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (cs.total.ytdBudget + dl.total.ytdBudget + fo.total.ytdBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (cs.total.ytdBudgetRatio + dl.total.ytdBudgetRatio + fo.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // gross margin
            col = 1;
            sheet.Cells[row, col++] = "TOTAL GROSS MARGIN:";
            sheet.Cells[row, col++] = (ss.total.tpActual + cs.total.tpActual + dl.total.tpActual + fo.total.tpActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.tpActualRatio + cs.total.tpActualRatio + dl.total.tpActualRatio + fo.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.tpBudget + cs.total.tpBudget + dl.total.tpBudget + fo.total.tpBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.tpBudgetRatio + cs.total.tpBudgetRatio + dl.total.tpBudgetRatio + fo.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.ytdActual + cs.total.ytdActual + dl.total.ytdActual + fo.total.ytdActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.ytdActualRatio + cs.total.ytdActualRatio + dl.total.ytdActualRatio + fo.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.ytdBudget + cs.total.ytdBudget + dl.total.ytdBudget + fo.total.ytdBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.ytdBudgetRatio + cs.total.ytdBudgetRatio + dl.total.ytdBudgetRatio + fo.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // Delivery and selling
            sheet.Cells[row, 1] = "DELIVERY AND SELLING";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in ds.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            ds.total.name = "TOTAL DELIVERY AND SELLING:";
            WriteGroup(sheet, ref row, ds.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // general and administration
            sheet.Cells[row, 1] = "GENERAL AND ADMINISTRATION";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in ga.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            ga.total.name = "TOTAL GENERAL AND ADMINISTRATION:";
            WriteGroup(sheet, ref row, ga.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // other expenses and income
            sheet.Cells[row, 1] = "OTHER EXPENSES AND INCOME";
            sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            foreach (Group group in oe.groupList)
            {
                WriteGroup(sheet, ref row, group);
            }
            oe.total.name = "TOTAL OTHER EXPENSES AND INCOME:";
            WriteGroup(sheet, ref row, oe.total);
            row--;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // expenses
            col = 1;
            sheet.Cells[row, col++] = "TOTAL EXPENSES:";
            sheet.Cells[row, col++] = (ds.total.tpActual + ga.total.tpActual + oe.total.tpActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ds.total.tpActualRatio + ga.total.tpActualRatio + oe.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ds.total.tpBudget + ga.total.tpBudget + oe.total.tpBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ds.total.tpBudgetRatio + ga.total.tpBudgetRatio + oe.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (ds.total.ytdActual + ga.total.ytdActual + oe.total.ytdActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ds.total.ytdActualRatio + ga.total.ytdActualRatio + oe.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ds.total.ytdBudget + ga.total.ytdBudget + oe.total.ytdBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ds.total.ytdBudgetRatio + ga.total.ytdBudgetRatio + oe.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 2;
            // net income
            col = 1;
            sheet.Cells[row, col++] = "TOTAL NET INCOME:";
            sheet.Cells[row, col++] = (ss.total.tpActual + cs.total.tpActual + dl.total.tpActual + fo.total.tpActual + ds.total.tpActual + ga.total.tpActual + oe.total.tpActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.tpActualRatio + cs.total.tpActualRatio + dl.total.tpActualRatio + fo.total.tpActualRatio + ds.total.tpActualRatio + ga.total.tpActualRatio + oe.total.tpActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.tpBudget + cs.total.tpBudget + dl.total.tpBudget + fo.total.tpBudget + ds.total.tpBudget + ga.total.tpBudget + oe.total.tpBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.tpBudgetRatio + cs.total.tpBudgetRatio + dl.total.tpBudgetRatio + fo.total.tpBudgetRatio + ds.total.tpBudgetRatio + ga.total.tpBudgetRatio + oe.total.tpBudgetRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.ytdActual + cs.total.ytdActual + dl.total.ytdActual + fo.total.ytdActual + ds.total.ytdActual + ga.total.ytdActual + oe.total.ytdActual).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.ytdActualRatio + cs.total.ytdActualRatio + dl.total.ytdActualRatio + fo.total.ytdActualRatio + ds.total.ytdActualRatio + ga.total.ytdActualRatio + oe.total.ytdActualRatio).ToString("P2");
            sheet.Cells[row, col++] = (ss.total.ytdBudget + cs.total.ytdBudget + dl.total.ytdBudget + fo.total.ytdBudget + ds.total.ytdBudget + ga.total.ytdBudget + oe.total.ytdBudget).amountUS.ToString("C2");
            sheet.Cells[row, col++] = (ss.total.ytdBudgetRatio + cs.total.ytdBudgetRatio + dl.total.ytdBudgetRatio + fo.total.ytdBudgetRatio + ds.total.ytdBudgetRatio + ga.total.ytdBudgetRatio + oe.total.ytdBudgetRatio).ToString("P2");
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
        }

        private void BuildCategories()
        {
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl, bq1lvl from cmsdat.fgrp where bq1comp='03' and (bq1lvl='A' or bq1lvl='B')";
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                string name = reader["bq1titl"].ToString().Trim();
                string groupID = reader["bq1grp"].ToString().Trim();
                char level = Convert.ToChar(reader["bq1lvl"]);
                int category = Convert.ToInt32(groupID[0].ToString());
                if (category >= 4)
                {
                    // skip level A after sales
                    if ('A' == level && category > 4)
                    {
                        continue;
                    }
                    if (4 == category)
                    {
                        ss.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("501"))
                    {
                        cs.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("502"))
                    {
                        dl.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("503"))
                    {
                        fo.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("6DS"))
                    {
                        ds.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("6GA"))
                    {
                        ga.AddGroup(name, groupID);
                    }
                    else if (groupID.Contains("6OT"))
                    {
                        oe.AddGroup(name, groupID);
                    }
                    else
                    {
                        throw new Exception("Unknown category " + groupID + " " + name);
                    }
                }
            }
            reader.Close();
            // get detailed information
            GetGroupDetailsInCategory(ss);
            GetGroupDetailsInCategory(cs);
            GetGroupDetailsInCategory(dl);
            GetGroupDetailsInCategory(fo);
            GetGroupDetailsInCategory(ds);
            GetGroupDetailsInCategory(ga);
            GetGroupDetailsInCategory(oe);
        }

        public void GetGroupDetailsInCategory(Category category)
        {
            foreach (Group group in category.groupList)
            {
                group.GetInfo(calendar);
                category.total.tpActual += group.tpActual;
                category.total.tpBudget += group.tpBudget;
                category.total.ytdActual += group.ytdActual;
                category.total.ytdBudget += group.ytdBudget;
            }
        }
    }
}
