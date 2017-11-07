using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using System.IO;
using ExcoUtility;
using Excel = Microsoft.Office.Interop.Excel;

namespace AR_Report
{
    class Process
    {
        private DateTime now = new DateTime();

        public void Run(DateTime now)
        {
            this.now = now;
            // write to excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet sheetMarkham = book.Worksheets.Add();
            sheetMarkham.Name = "AR Markham";
            Excel.Worksheet sheetMichigan = book.Worksheets[2];
            sheetMichigan.Name = "AR Michigan";
            Excel.Worksheet sheetTexas = book.Worksheets[3];
            sheetTexas.Name = "AR Texas";
            Excel.Worksheet sheetColombia = book.Worksheets[4];
            sheetColombia.Name = "AR Colombia";
            // fill data
            FillSheet("001", sheetMarkham);
            FillSheet("003", sheetMichigan);
            FillSheet("005", sheetTexas);
            FillSheet("004", sheetColombia);
            // adjust style
            sheetMarkham.Cells.Columns.AutoFit();
            sheetMarkham.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            sheetMichigan.Cells.Columns.AutoFit();
            sheetMichigan.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            sheetTexas.Cells.Columns.AutoFit();
            sheetTexas.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            sheetColombia.Cells.Columns.AutoFit();
            sheetColombia.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "AR report at " + now.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }

        private void WriteCustomerList(List<Customer> custList, string title, Excel.Worksheet sheet, ref int row)
        {
            if (custList.Count > 0)
            {
                // header
                int column = 1;
                sheet.Cells[row, 1] = "Customers in " + title;
                sheet.Cells.get_Range("A" + row.ToString()).Font.Bold = true;
                sheet.Cells.get_Range("A" + row.ToString()).Font.Size = 15;
                sheet.Cells.get_Range("A" + row.ToString()).Font.ColorIndex = 32;
                sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Merge();
                row++;
                sheet.Cells[row, column++] = "Cust ID";
                sheet.Cells[row, column++] = "Cust Name";
                sheet.Cells[row, column++] = "Currency";
                sheet.Cells[row, column++] = "Total AR";
                sheet.Cells[row, column++] = "Current";
                sheet.Cells[row, column++] = "Over 30";
                sheet.Cells[row, column++] = "Over 60";
                sheet.Cells[row, column++] = "Over 90";
                sheet.Cells[row, column++] = "Over 120";
                Excel.Range headerRange = sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString());
                headerRange.Font.Bold = true;
                headerRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                row++;
                // body
                Customer total = new Customer();
                foreach (Customer cust in custList)
                {
                    column = 1;
                    sheet.Cells[row, column].NumberFormat = "@";
                    sheet.Cells[row, column++] = cust.csCustID;
                    sheet.Cells[row, column++] = cust.csCustName;
                    sheet.Cells[row, column++] = cust.csCurrency;
                    sheet.Cells[row, column++] = cust.dTotal.ToString("C2");
                    sheet.Cells[row, column++] = cust.dCurrent.ToString("C2");
                    sheet.Cells[row, column++] = cust.dOver30.ToString("C2");
                    sheet.Cells[row, column++] = cust.dOver60.ToString("C2");
                    sheet.Cells[row, column++] = cust.dOver90.ToString("C2");
                    sheet.Cells[row, column++] = cust.dOver120.ToString("C2");
                    total += cust;
                    row++;
                }
                // summary
                column = 2;
                sheet.Cells[row, column++] = "TOTALS:";
                column++;
                sheet.Cells[row, column++] = total.dTotal.ToString("C2");
                sheet.Cells[row, column++] = total.dCurrent.ToString("C2");
                sheet.Cells[row, column++] = total.dOver30.ToString("C2");
                sheet.Cells[row, column++] = total.dOver60.ToString("C2");
                sheet.Cells[row, column++] = total.dOver90.ToString("C2");
                sheet.Cells[row, column++] = total.dOver120.ToString("C2");
                Excel.Range summaryRange = sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString());
                summaryRange.Font.Bold = true;
                summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlDouble;
                summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
                row++;
                // percentage
                column = 4;
                sheet.Cells[row, column++] = (total.dTotal / total.dTotal).ToString("P2");
                sheet.Cells[row, column++] = (total.dCurrent / total.dTotal).ToString("P2");
                sheet.Cells[row, column++] = (total.dOver30 / total.dTotal).ToString("P2");
                sheet.Cells[row, column++] = (total.dOver60 / total.dTotal).ToString("P2");
                sheet.Cells[row, column++] = (total.dOver90 / total.dTotal).ToString("P2");
                sheet.Cells[row, column++] = (total.dOver120 / total.dTotal).ToString("P2");
                sheet.Cells.get_Range("A" + row.ToString(), "I" + row.ToString()).Font.Bold = true;
                row++;
                row++;
                row++;
            }
        }

        public void FillSheet(string csPlantCode, Excel.Worksheet sheet)
        {
            List<Customer> l_canada = new List<Customer>();
            List<Customer> l_usa = new List<Customer>();
            List<Customer> l_other = new List<Customer>();
            // get data
            string query = "select ascust, asterr, ascura, bvname, coalesce(sum(asduam), 0.0) from cmsdat.arop, cmsdat.cust where ascomp=" + csPlantCode + " and bvcust=ascust group by ascust, asterr, ascura, bvname order by bvname";
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                Customer cust = new Customer();
                cust.csPlant = csPlantCode;
                cust.csCustID = reader[0].ToString().Trim();
                cust.csCustTerr = reader[1].ToString().Trim();
                cust.csCurrency = reader[2].ToString().Trim();
                cust.csCustName = reader[3].ToString().Trim();
                cust.dTotal = Convert.ToDouble(reader[4]);
                if ("CDN" == cust.csCustTerr || "CUS" == cust.csCustTerr)
                {
                    l_canada.Add(cust);
                }
                else if ("USA" == cust.csCustTerr)
                {
                    l_usa.Add(cust);
                }
                else
                {
                    l_other.Add(cust);
                }
            }
            reader.Close();
            // get details
            foreach (Customer cust in l_canada)
            {
                cust.GetDetails(now);
            }
            foreach (Customer cust in l_usa)
            {
                cust.GetDetails(now);
            }
            foreach (Customer cust in l_other)
            {
                cust.GetDetails(now);
            }
            // write title
            int row = 1;
            sheet.Cells[1, 1] = "AR for plant " + csPlantCode + " at " + now.ToShortDateString();
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            row = 3;
            // write canada
            WriteCustomerList(l_canada, "Canada", sheet, ref row);
            // write usa
            WriteCustomerList(l_usa, "USA", sheet, ref row);
            // write other
            WriteCustomerList(l_other, "other territories", sheet, ref row);
            // TODO: add total by currency feature
        }
    }
}
