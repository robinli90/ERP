using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;
using System.Net.Mail;
using System.Net;
using Excel = Microsoft.Office.Interop.Excel;

namespace OrdersReport
{
    public class Process
    {
        public string filePath = string.Empty;

        // constructor
        public Process()
        {

        }



        public void Run(bool isNeedSurcharge)
        {

            ExcoODBC database = ExcoODBC.Instance;
            string query = "";

            List<int> orderlist = new List<int>();
            List<string> datelist = new List<string>();
            database.Open(Database.DECADE_MARKHAM);
            query = "select top 100 ordernumber,orderdate from d_order order by ordernumber desc";
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                orderlist.Add(Convert.ToInt32(reader["ordernumber"]));
                datelist.Add(reader["orderdate"].ToString());
            }
            reader.Close();

            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);

            Excel.Worksheet soSheet = book.Worksheets.Add();
            soSheet.Name = "Order List";

            soSheet.Cells[1, 1] = "Order List at November";
            soSheet.Cells.get_Range("A1").Font.Bold = true;
            soSheet.Cells.get_Range("A1").Font.Size = 20;
            soSheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            soSheet.Cells.get_Range("A1", "H1").Merge();

            // build header
            int row = 3;
            int col = 1;
            soSheet.Cells[row, col++] = "Order #";
            soSheet.Cells[row, col++] = "Order Date";
            row++;

            foreach (int so in orderlist)
            {
                col = 1;
                soSheet.Cells[row, col] = so;

                row++;
            }
            soSheet.Cells.Columns.AutoFit();
            soSheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            


            
            
            filePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "OrderList.xlsx");
            File.Delete(filePath);
            book.SaveAs(filePath, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(filePath);
        
        }
    }


}
