using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel;

namespace Monthly_Production_Report
{
    public class Piece
    {
        public string wo = string.Empty;
        public string desc = string.Empty;
        public bool hasNitride = false;
        public double niWeight = 0.0;
        public double miTime = 0.0;
        public double laTime = 0.0;
        public double spTime = 0.0;
        public double wiTime = 0.0;
    };

    public class Die
    {
        public List<Piece> pieceList = new List<Piece>();
        public string so = string.Empty;
        public double heWeight = 0.0;
    };

    public class Summary
    {
        List<Die> dieList = new List<Die>();

        public int sbCount = 0;
        public int hbCount = 0;
        public int boCount = 0;
        public int feCount = 0;
        public int spCount = 0;
        public int hpCount = 0;
        public int maCount = 0;
        public int drCount = 0;
        public int hTotal = 0;
        public int sTotal = 0;
        public int suCount = 0;
        public double niPound = 0.0;
        public double hePound = 0.0;
        public double miTime = 0.0;
        public double laTime = 0.0;
        public double spTime = 0.0;
        public double wiTime = 0.0;

        public void GetInfo(int year, int period)
        {
            string query = "select dhord# from cmsdat.oih where dhplnt=1 and dharyr=" + year.ToString() + " and dharpr=" + period.ToString() + " and dhord#>0 order by dhord#";
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            // get order list
            while (reader.Read())
            {
                Die die = new Die();
                die.so = reader[0].ToString().Trim();
                dieList.Add(die);
                Console.WriteLine(die.so);
            }
            reader.Close();
            // get weight
            database.Open(Database.DECADE);
            foreach (Die die in dieList)
            {
                query = "select freightweight from dbo.d_order where ordernumber=" + die.so.ToString();

                reader = database.RunQuery(query);
                // get order list
                if (reader.Read())
                {
                    die.heWeight = Convert.ToDouble(reader[0]);
                    Console.WriteLine(die.so + " heat treat " + die.heWeight.ToString("F2") + " LBS");
                }
                reader.Close();
            }
            // get piece in solarsoft
            database.Open(Database.CMSDAT);
            foreach (Die die in dieList)
            {
                query = "select dnjob, dnpart from cmsdat.cjobh where dnord#=" + die.so;
                reader = database.RunQuery(query);
                while (reader.Read())
                {
                    if ((reader[0].ToString().Trim().Length == 7 && reader[1].ToString().Trim().Contains("HD") && !reader[1].ToString().Contains("PLA") && !reader[1].ToString().Contains("MAN") && !reader[1].ToString().Contains("BAC")) || reader[1].ToString().Trim().Contains("REWORK") || reader[1].ToString().Trim().Contains("MISC"))
                    {
                        continue;
                    }
                    Piece piece = new Piece();
                    piece.wo = reader[0].ToString().Trim();
                    piece.desc = reader[1].ToString().Trim();
                    die.pieceList.Add(piece);
                    Console.WriteLine(die.so + " " + piece.wo + " " + piece.desc);
                }
                reader.Close();
                query = "select dnjob, dnpart from cmsdat.hjobh where dnord#=" + die.so;
                reader = database.RunQuery(query);
                while (reader.Read())
                {
                    if ((reader[0].ToString().Trim().Length == 7 && reader[1].ToString().Trim().Contains("HD") && !reader[1].ToString().Contains("PL") && !reader[1].ToString().Contains("MA") && !reader[1].ToString().Contains("BA")) || reader[1].ToString().Trim().Contains("REWORK") || reader[1].ToString().Trim().Contains("MISC"))
                    {
                        continue;
                    }
                    Piece piece = new Piece();
                    piece.wo = reader[0].ToString().Trim();
                    piece.desc = reader[1].ToString().Trim();
                    die.pieceList.Add(piece);
                    Console.WriteLine(die.so + " " + piece.wo + " " + piece.desc);
                }
                reader.Close();
            }
            // get piece in decade
            database.Open(Database.DECADE);
            foreach (Die die in dieList)
            {
                foreach (Piece piece in die.pieceList)
                {
                    if (piece.desc.Contains("BAH"))
                    {
                        sbCount++;
                        sTotal++;
                    }
                    else if (piece.desc.Contains("BO"))
                    {
                        boCount++;
                        sTotal++;
                    }
                    else if (piece.desc.Contains("FDR"))
                    {
                        feCount++;
                        sTotal++;
                    }
                    else if (piece.desc.Contains("HD") && piece.desc.Contains("BA"))
                    {
                        hbCount++;
                        hTotal++;
                    }
                    else if (piece.desc.Contains("HD") && piece.desc.Contains("PL"))
                    {
                        hpCount++;
                        hTotal++;
                    }
                    else if (piece.desc.Contains("HD") && piece.desc.Contains("MA"))
                    {
                        maCount++;
                        hTotal++;
                    }
                    else if (piece.desc.Contains("RI"))
                    {
                        drCount++;
                        sTotal++;
                    }
                    else if (piece.desc.Contains("SB"))
                    {
                        sbCount++;
                        sTotal++;
                    }
                    else if (piece.desc.Contains("SD"))
                    {
                        spCount++;
                        sTotal++;
                    }
                    else
                    {
                        throw new Exception("Weird part: " + piece.wo + "\t" + piece.desc);
                    }
                }
            }
            // get nitride, mill, lathe, spark, wire
            database.Open(Database.CMSDAT);
            foreach (Die die in dieList)
            {
                for (int i = 0; i < die.pieceList.Count; i++)
                {
                    Piece piece = die.pieceList[i];
                    query = "select fwoseq, fwtime from cmsdat.jcsta where fwjobn='" + piece.wo + "' and (fwoseq=160 or fwoseq=180 or fwoseq=190 or fwoseq=460 or fwoseq=470 or fwoseq=790)";
                    reader = database.RunQuery(query);
                    while (reader.Read())
                    {
                        int seq = Convert.ToInt32(reader[0]);
                        switch (seq)
                        {
                            case 160:
                                piece.laTime += Convert.ToDouble(reader[1]);
                                Console.WriteLine(die.so + " " + piece.wo + " lathe " + piece.laTime.ToString("F2"));
                                break;
                            case 180:
                            case 190:
                                piece.miTime += Convert.ToDouble(reader[1]);
                                Console.WriteLine(die.so + " " + piece.wo + " mill " + piece.miTime.ToString("F2"));
                                break;
                            case 460:
                                piece.spTime += Convert.ToDouble(reader[1]);
                                Console.WriteLine(die.so + " " + piece.wo + " spark " + piece.spTime.ToString("F2"));
                                break;
                            case 470:
                                piece.wiTime += Convert.ToDouble(reader[1]);
                                Console.WriteLine(die.so + " " + piece.wo + " wire " + piece.wiTime.ToString("F2"));
                                break;
                            case 790:
                                piece.hasNitride = true;
                                Console.WriteLine(die.so + " " + piece.wo + " has nitride");
                                break;
                        }
                    }
                    reader.Close();
                }
            }
            // get nitride weight
            database.Open(Database.CMSDAT);
            foreach (Die die in dieList)
            {
                for (int i = 0; i < die.pieceList.Count; i++)
                {
                    Piece piece = die.pieceList[i];
                    if (piece.hasNitride)
                    {
                        query = "select ihcnv2 from cmsdat.punit where ihunt2='NLB' and ihpart='" + piece.desc + "'";
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            piece.niWeight += Convert.ToDouble(reader[0]);
                            Console.WriteLine(die.so + " " + piece.wo + " nitride " + piece.niWeight.ToString("F2") + " LBS");
                        }
                        reader.Close();
                    }
                }
            }
            // summarize
            foreach (Die die in dieList)
            {
                hePound += die.heWeight;
                foreach (Piece piece in die.pieceList)
                {
                    niPound += piece.niWeight;
                    miTime += piece.miTime;
                    laTime += piece.laTime;
                    spTime += piece.spTime;
                    wiTime += piece.wiTime;
                }
            }
        }
    }

    public class Process
    {
        List<Summary> sumList = new List<Summary>();

        public void Run()
        {
            int year = 13;
            // get data
            for (int i = 1; i <= 12; i++)
            {
                Summary summary = new Summary();
                summary.GetInfo(year, i);
                sumList.Add(summary);
            }
            // write to excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet sheet = book.Worksheets[1];
            // fill sheet
            int column = 1;
            int row = 1;
            sheet.Cells[row, column] = "Production report for Markham year " + year.ToString();
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "L1").Merge();
            row = 2;
            sheet.Cells[row++, 1] = "Period";
            sheet.Cells[row++, 1] = "Backer Count";
            sheet.Cells[row++, 1] = "Mandrel Count";
            sheet.Cells[row++, 1] = "Plate Count";
            sheet.Cells[row++, 1] = "Hollow Total";
            row++;
            sheet.Cells[row++, 1] = "Backer Count";
            sheet.Cells[row++, 1] = "Plate Count";
            sheet.Cells[row++, 1] = "Bolster Count";
            sheet.Cells[row++, 1] = "Feeder Count";
            sheet.Cells[row++, 1] = "Sub Bolster Count";
            sheet.Cells[row++, 1] = "Die Ring Count";
            sheet.Cells[row++, 1] = "Solid Total";
            row++;
            sheet.Cells[row++, 1] = "Piece Total";
            row++;
            sheet.Cells[row++, 1] = "Nitride Weight (lb)";
            sheet.Cells[row++, 1] = "Heat Treat Weight (lb)";
            sheet.Cells[row++, 1] = "Mill Time (hour)";
            sheet.Cells[row++, 1] = "Lathe Time (hour)";
            sheet.Cells[row++, 1] = "Spark Time (hour)";
            sheet.Cells[row++, 1] = "Wire Time (hour)";
            sheet.Cells.get_Range("A2", "A" + row.ToString()).Font.Bold = true;
            // write data
            for (int i = 0; i < sumList.Count; i++)
            {
                Summary summary = sumList[i];
                row = 2;
                column++;
                sheet.Cells[row, column].NumberFormat = "@";
                sheet.Cells[row++, column] = (i + 1).ToString("D2");
                sheet.Cells[row++, column] = summary.hbCount.ToString();
                sheet.Cells[row++, column] = summary.maCount.ToString();
                sheet.Cells[row++, column] = summary.hpCount.ToString();
                sheet.Cells[row++, column] = summary.hTotal.ToString();
                row++;
                sheet.Cells[row++, column] = summary.sbCount.ToString();
                sheet.Cells[row++, column] = summary.spCount.ToString();
                sheet.Cells[row++, column] = summary.boCount.ToString();
                sheet.Cells[row++, column] = summary.feCount.ToString();
                sheet.Cells[row++, column] = summary.suCount.ToString();
                sheet.Cells[row++, column] = summary.drCount.ToString();
                sheet.Cells[row++, column] = summary.sTotal.ToString();
                row++;
                sheet.Cells[row++, column] = (summary.sTotal + summary.hTotal).ToString();
                row++;
                sheet.Cells[row++, column] = summary.niPound.ToString("F2");
                sheet.Cells[row++, column] = summary.hePound.ToString("F2");
                sheet.Cells[row++, column] = summary.miTime.ToString("F2");
                sheet.Cells[row++, column] = summary.laTime.ToString("F2");
                sheet.Cells[row++, column] = summary.spTime.ToString("F2");
                sheet.Cells[row++, column] = summary.wiTime.ToString("F2");
            }
            sheet.Cells.get_Range("A6", "M6").Font.Bold = true;
            sheet.Cells.get_Range("A14", "M14").Font.Bold = true;
            sheet.Cells.get_Range("A16", "M16").Font.Bold = true;
            sheet.Cells.get_Range("B2", "M2").Font.Bold = true;
            sheet.Cells.get_Range("A2", "M2").Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Production Summary Markham " + DateTime.Today.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }
    }
}
