using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel; 
using ExcoUtility;

namespace NitrideAndHeatTreatWeight
{
    class Process
    {
        private List<List<Piece>> nitrideList = new List<List<Piece>>();
        private List<List<Piece>> heatTreatList = new List<List<Piece>>();

        public Process()
        {
            for (int i = 0; i < 12; i++)
            {
                nitrideList.Add(new List<Piece>());
                heatTreatList.Add(new List<Piece>());
            }
        }
        public void Run()
        {
            StreamWriter writer = new StreamWriter("D:\\workspace\\ERP\\log.ext");
            string query = string.Empty;
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.DECADE);
            OdbcDataReader reader;
            // get order list from decade
            for (int i = 0; i < 12; i++)
            {
                ExcoCalendar calendar = new ExcoCalendar(13, i+1, true, 1);
                // get nitride part list
                query = "select distinct ordernumber, part from dbo.d_task where (tasktime<'20" + calendar.GetNextCalendarMonth().year.ToString("D2") + "-" + calendar.GetNextCalendarMonth().month.ToString("D2") + "-01 00:00:00' and tasktime>'20" + calendar.GetCalendarYear().ToString("D2") + "-" + calendar.GetCalendarMonth().ToString("D2") + "-01 00:00:00') and (task='NS' or station like 'NTR%') and (d_task.ordernumber>250000 and d_task.ordernumber<350000) order by ordernumber desc";
                reader = database.RunQuery(query);
                while (reader.Read())
                {
                    Piece piece = new Piece();
                    piece.so = reader[0].ToString();
                    piece.type = reader[1].ToString();
                    nitrideList[i].Add(piece);
                }
                reader.Close();
                // get heat treat part list
                query = "select a, count(b), c/count(b) from (select distinct d_order.ordernumber as a, d_task.part as b, freightweight as c from dbo.d_task, dbo.d_order where (tasktime<'20" + calendar.GetNextCalendarMonth().year.ToString("D2") + "-" + calendar.GetNextCalendarMonth().month.ToString("D2") + "-01 00:00:00' and tasktime>'20" + calendar.GetCalendarYear().ToString("D2") + "-" + calendar.GetCalendarMonth().ToString("D2") + "-01 00:00:00') and task='RK' and (d_task.ordernumber>250000 and d_task.ordernumber<350000) and d_task.ordernumber=d_order.ordernumber) as aa group by a, c order by a desc";
                reader = database.RunQuery(query);
                while (reader.Read())
                {
                    int count = Convert.ToInt32(reader[1]);
                    for (int j = 0; j < count; j++)
                    {
                        Piece piece = new Piece();
                        piece.so = reader[0].ToString();
                        piece.weight = Convert.ToDouble(reader[2]);
                        heatTreatList[i].Add(piece);
                    }
                }
                reader.Close();
            }
            // get part description for nitriding
            database.Open(Database.CMSDAT);
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < nitrideList[i].Count; j++)
                {
                    query = "select trim(dnpart) from cmsdat.cjobh where dnord#=" + nitrideList[i][j].so + " and ";
                    switch (nitrideList[i][j].type)
                    {
                        case "P":
                            query += "(dnpart like '%PLA%' or dnpart like 'SD%')";
                            break;
                        case "M":
                            query += "dnpart like '%MAN%'";
                            break;
                        default:
                            writer.WriteLine("Invalid type to nitriding: " + nitrideList[i][j].so + nitrideList[i][j].type);
                            continue;
                    }
                    reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        nitrideList[i][j].part = reader[0].ToString();
                    }
                    else
                    {
                        reader.Close();
                        query = query.Replace("cjobh", "hjobh");
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            nitrideList[i][j].part = reader[0].ToString();
                        }
                        else
                        {
                            writer.WriteLine("Could not find part for order: " + nitrideList[i][j].so);
                            nitrideList[i][j].part = "SUCKS";
                        }
                    }
                    reader.Close();
                }
            }
            // get nitride weight
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < nitrideList[i].Count; j++)
                {
                    if (0 == nitrideList[i][j].part.CompareTo("SUCKS"))
                    {
                        continue;
                    }
                    query = "select ihcnv2 from cmsdat.punit where ihpart like '" + nitrideList[i][j].part + "%'";
                    reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        nitrideList[i][j].weight = Convert.ToDouble(reader[0]);
                    }
                    else
                    {
                        writer.WriteLine("Could not find nitride weight for order: " + nitrideList[i][j].so + " with part " + nitrideList[i][j].part);
                    }
                    reader.Close();
                }
            }
            // write to excel
            // create excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet sheet = book.Worksheets[1];
            // fill sheet
            // insert title
            sheet.Cells[1, 1] = "Nitride Information for 2013";
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            sheet.Cells[6, 1] = "Heat Treat Information for 2013";
            sheet.Cells.get_Range("A6").Font.Bold = true;
            sheet.Cells.get_Range("A6").Font.Size = 20;
            sheet.Cells.get_Range("A6").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A6", "H6").Merge();
            // build header
            int row = 2;
            int column = 2;
            sheet.Cells[row, column++] = "Oct";
            sheet.Cells[row, column++] = "Nov";
            sheet.Cells[row, column++] = "Dec";
            sheet.Cells[row, column++] = "Jan";
            sheet.Cells[row, column++] = "Feb";
            sheet.Cells[row, column++] = "Mar";
            sheet.Cells[row, column++] = "Apr";
            sheet.Cells[row, column++] = "May";
            sheet.Cells[row, column++] = "Jun";
            sheet.Cells[row, column++] = "Jul";
            sheet.Cells[row, column++] = "Aug";
            sheet.Cells[row, column++] = "Sep";
            Excel.Range summaryRange = sheet.Cells.get_Range("B" + row.ToString(), "M" + row.ToString());
            summaryRange.Font.Bold = true;
            summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row = 7;
            column = 2;
            sheet.Cells[row, column++] = "Oct";
            sheet.Cells[row, column++] = "Nov";
            sheet.Cells[row, column++] = "Dec";
            sheet.Cells[row, column++] = "Jan";
            sheet.Cells[row, column++] = "Feb";
            sheet.Cells[row, column++] = "Mar";
            sheet.Cells[row, column++] = "Apr";
            sheet.Cells[row, column++] = "May";
            sheet.Cells[row, column++] = "Jun";
            sheet.Cells[row, column++] = "Jul";
            sheet.Cells[row, column++] = "Aug";
            sheet.Cells[row, column++] = "Sep";
            summaryRange = sheet.Cells.get_Range("B" + row.ToString(), "M" + row.ToString());
            summaryRange.Font.Bold = true;
            summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            // build budy
            row = 3;
            column = 1;
            sheet.Cells[row, column] = "# of Pieces";
            sheet.Cells[row+1, column] = "# of Weight";
            for (int i = 0; i < 12; i++)
            {
                int count = 0;
                double weight = 0.0;
                column++;
                for (int j = 0; j < nitrideList[i].Count; j++)
                {
                    count++;
                    weight += nitrideList[i][j].weight;
                }
                sheet.Cells[row, column] = count.ToString();
                sheet.Cells[row + 1, column] = weight.ToString("F2");
            }
            row = 8;
            column = 1;
            sheet.Cells[row, column] = "# of Pieces";
            sheet.Cells[row + 1, column] = "# of Weight";
            for (int i = 0; i < 12; i++)
            {
                int count = 0;
                double weight = 0.0;
                column++;
                for (int j = 0; j < heatTreatList[i].Count; j++)
                {
                    count++;
                    weight += heatTreatList[i][j].weight;
                }
                sheet.Cells[row, column] = count.ToString();
                sheet.Cells[row + 1, column] = weight.ToString("F2");
            }
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            // run excel file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Nitride and Heat Treat at " + DateTime.Today.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            writer.Close();
            System.Diagnostics.Process.Start(path);
        }
    }
}