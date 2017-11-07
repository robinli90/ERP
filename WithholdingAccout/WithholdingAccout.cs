using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;
using Excel = Microsoft.Office.Interop.Excel;

namespace WithholdingAccout
{
    class WithholdingAccout
    {
        public struct AccountName
        {
            public string id;
            public string name;
        }

        static void Main(string[] args)
        {
            List<Account> accountList = new List<Account>();
            // get account
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select azftcd, aztitl from cmsdat.mast where azcomp=4";
            OdbcDataReader reader = database.RunQuery(query);
            List<AccountName> accountNameList = new List<AccountName>();
            while (reader.Read())
            {
                AccountName accountName = new AccountName();
                accountName.id = "4" + reader[0].ToString().Trim();
                accountName.name = reader[1].ToString().Trim();
                accountNameList.Add(accountName);
            }
            reader.Close();
            // build account
            foreach (AccountName accountName in accountNameList)
            {
                accountList.Add(new Account(accountName.id, accountName.name));
            }
            // create excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet sheet = book.Worksheets[1];
            // build header
            sheet.Cells[1, 1] = "Date";
            sheet.Cells[1, 2] = "Source";
            sheet.Cells[1, 3] = "Vendor";
            sheet.Cells[1, 4] = "TaxID";
            sheet.Cells[1, 5] = "Amount";
            sheet.Cells[1, 6] = "Created By";
            sheet.Cells[1, 7] = "Transaction Date";
            sheet.Cells[1, 8] = "Post Date";
            sheet.Cells.get_Range("A1", "H1").Font.Bold = true;
            sheet.Cells.get_Range("A1", "H1").Font.Size = 12;            sheet.Cells.get_Range("A1", "H1").Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            int row = 2;
            int column = 1;
            foreach (Account account in accountList)
            {
                // display account
                sheet.Cells[row, 1] = account.ID;
                sheet.Cells[row, 2] = account.Name;
                sheet.Cells.get_Range("A" + row.ToString(), "B" + row.ToString()).Font.Bold = true;
                sheet.Cells.get_Range("A" + row.ToString(), "B" + row.ToString()).Font.ColorIndex = 3;
                // display transactions
                row++;
                foreach (Transaction trans in account.transList)
                {
                    column = 1;
                    sheet.Cells[row, column++] = trans.date;
                    sheet.Cells[row, column++] = trans.type;
                    sheet.Cells[row, column++] = trans.venderOrCustomer;
                    sheet.Cells[row, column++] = trans.taxID;
                    sheet.Cells[row, column++] = trans.amount;
                    sheet.Cells[row, column++] = trans.user;
                    sheet.Cells[row, column++] = trans.tDate;
                    sheet.Cells[row, column++] = trans.pDate;
                    row++;
                }
                row++;
            }
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "cc.xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
        }
    }
}