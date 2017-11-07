using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel;

namespace InvoiceRegisterTexas
{
    class Process
    {
        public struct Invoice
        {
            public string creditNote;
            public int invoiceNumber;
            public DateTime invoiceDate;
            public string salesOrder;
            public string customerName;
            public string customerID;
            public string currency;
            public double dieSale;
            public double surcharge;
            public double fastTrack;
            public double freight;
            public double discount;
            public double invoiceTotal;
            public string posted;
        };

        public void Run()
        {
            List<Invoice> invoiceList = new List<Invoice>();
            ExcoCalendar calendar = new ExcoCalendar(DateTime.Now.Year - 2000, DateTime.Now.Month, false, 5);
            // build connection
            string query = "select dhincr, dhinv#, dhidat, dhbnam, dhbcs#, dhord#, dhterr, dhcurr, dhpost, dhtoti from cmsdat.oih where dhplnt='005' and (dharyr=" + calendar.GetFiscalYear().ToString() + " or (dhidat>='2012-10-01' and dharyr=0 and dharpr=0)) order by dhinv#";
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            OdbcDataReader reader = solarsoft.RunQuery(query);
            // get main data
            while (reader.Read())
            {
                Invoice invoice = new Invoice();
                invoice.invoiceNumber = Convert.ToInt32(reader["dhinv#"]);
                invoice.creditNote = reader["dhincr"].ToString().Trim();
                invoice.invoiceDate = Convert.ToDateTime(reader["dhidat"]);
                invoice.salesOrder = reader["dhord#"].ToString().Trim();
                invoice.customerName = reader["dhbnam"].ToString().Trim();
                invoice.customerID = reader["dhbcs#"].ToString().Trim();
                invoice.currency = reader["dhcurr"].ToString().Trim();
                if (string.Empty == reader["dhtoti"].ToString())
                {
                    invoice.invoiceTotal = 0.0;
                }
                else
                {
                    invoice.invoiceTotal = Convert.ToDouble(reader["dhtoti"]);
                }
                invoice.posted = reader["dhpost"].ToString().Trim();
                invoiceList.Add(invoice);
            }
            reader.Close();
            // die sale
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(dipric*diqtsp) as sale from cmsdat.oid where diglcd='SAL' and diinv#=" + invoice.invoiceNumber.ToString();
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["sale"].ToString())
                {
                    invoice.dieSale = Convert.ToDouble(reader["sale"]);
                }
                else
                {
                    invoice.dieSale = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // discount
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(fldext) as value from cmsdat.ois where flinv#=" + invoice.invoiceNumber.ToString() + " and (fldisc like 'D%' or fldisc like 'M%')";
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["value"].ToString())
                {
                    invoice.discount = Convert.ToDouble(reader["value"]);
                }
                else
                {
                    invoice.discount = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // fast track
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(fldext) as value from cmsdat.ois where flinv#=" + invoice.invoiceNumber.ToString() + " and fldisc like 'F%'";
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["value"].ToString())
                {
                    invoice.fastTrack = Convert.ToDouble(reader["value"]);
                }
                else
                {
                    invoice.fastTrack = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // frieght
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(dipric*diqtsp) as frt from cmsdat.oid where diglcd='FRT' and diinv#=" + invoice.invoiceNumber.ToString();
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["frt"].ToString())
                {
                    invoice.freight = Convert.ToDouble(reader["frt"]);
                }
                else
                {
                    invoice.freight = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // surcharge
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(fldext) as value from cmsdat.ois where flinv#=" + invoice.invoiceNumber.ToString() + " and (fldisc like 'S%' or fldisc like 'P%')";
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["value"].ToString())
                {
                    invoice.surcharge = Convert.ToDouble(reader["value"]);
                }
                else
                {
                    invoice.surcharge = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // check missing invoices
            int prevInvoice = 0;
            for (int i = 1; i < invoiceList.Count; i++)
            {
                if (0 == prevInvoice)
                {
                    prevInvoice = invoiceList[i].invoiceNumber;
                }
                else
                {
                    prevInvoice++;
                    while (invoiceList[i].invoiceNumber != prevInvoice)
                    {
                        Invoice emptyInvoice = new Invoice();
                        emptyInvoice.invoiceNumber = prevInvoice;
                        // check if posted to other year
                        query = "select dhidat from cmsdat.oih where dhinv#=" + prevInvoice.ToString();
                        reader = solarsoft.RunQuery(query);
                        if (reader.Read())
                        {
                            emptyInvoice.invoiceDate = Convert.ToDateTime(reader["dhidat"]);
                        }
                        reader.Close();
                        invoiceList.Insert(i, emptyInvoice);
                        prevInvoice++;
                        i++;
                    }
                }
            }



            // process into monthly lists
            List<Invoice> janList = new List<Invoice>();
            List<Invoice> febList = new List<Invoice>();
            List<Invoice> marList = new List<Invoice>();
            List<Invoice> aprList = new List<Invoice>();
            List<Invoice> mayList = new List<Invoice>();
            List<Invoice> junList = new List<Invoice>();
            List<Invoice> julList = new List<Invoice>();
            List<Invoice> augList = new List<Invoice>();
            List<Invoice> sepList = new List<Invoice>();
            List<Invoice> octList = new List<Invoice>();
            List<Invoice> novList = new List<Invoice>();
            List<Invoice> decList = new List<Invoice>();
            int list = 0;
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                // empty invoice
                if (null == invoice.creditNote)
                {
                    switch (list)
                    {
                        case 10:
                            janList.Add(invoice);
                            break;
                        case 20:
                            febList.Add(invoice);
                            break;
                        case 30:
                            marList.Add(invoice);
                            break;
                        case 40:
                            aprList.Add(invoice);
                            break;
                        case 50:
                            mayList.Add(invoice);
                            break;
                        case 60:
                            junList.Add(invoice);
                            break;
                        case 70:
                            julList.Add(invoice);
                            break;
                        case 80:
                            augList.Add(invoice);
                            break;
                        case 90:
                            sepList.Add(invoice);
                            break;
                        case 100:
                            octList.Add(invoice);
                            break;
                        case 110:
                            novList.Add(invoice);
                            break;
                        case 120:
                            decList.Add(invoice);
                            break;
                    }
                }
                else
                {
                    // valid invoice
                    if (1 == invoice.invoiceDate.Month)
                    {
                        janList.Add(invoice);
                        list = 10;
                    }
                    else if (2 == invoice.invoiceDate.Month)
                    {
                        febList.Add(invoice);
                        list = 20;
                    }
                    else if (3 == invoice.invoiceDate.Month)
                    {
                        marList.Add(invoice);
                        list = 30;
                    }
                    else if (4 == invoice.invoiceDate.Month)
                    {
                        aprList.Add(invoice);
                        list = 40;
                    }
                    else if (5 == invoice.invoiceDate.Month)
                    {
                        mayList.Add(invoice);
                        list = 50;
                    }
                    else if (6 == invoice.invoiceDate.Month)
                    {
                        junList.Add(invoice);
                        list = 60;
                    }
                    else if (7 == invoice.invoiceDate.Month)
                    {
                        julList.Add(invoice);
                        list = 70;
                    }
                    else if (8 == invoice.invoiceDate.Month)
                    {
                        augList.Add(invoice);
                        list = 80;
                    }
                    else if (9 == invoice.invoiceDate.Month)
                    {
                        sepList.Add(invoice);
                        list = 90;
                    }
                    else if (10 == invoice.invoiceDate.Month)
                    {
                        octList.Add(invoice);
                        list = 100;
                    }
                    else if (11 == invoice.invoiceDate.Month)
                    {
                        novList.Add(invoice);
                        list = 110;
                    }
                    else if (12 == invoice.invoiceDate.Month)
                    {
                        decList.Add(invoice);
                        list = 120;
                    }
                }
            }

            // write to excel
            // create excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet julSheet = book.Worksheets[1];
            julSheet.Name = "July " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet augSheet = book.Worksheets[2];
            augSheet.Name = "August " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet sepSheet = book.Worksheets[3];
            sepSheet.Name = "September " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet junSheet = book.Worksheets.Add();
            junSheet.Name = "June " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet maySheet = book.Worksheets.Add();
            maySheet.Name = "May " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet aprSheet = book.Worksheets.Add();
            aprSheet.Name = "April " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet marSheet = book.Worksheets.Add();
            marSheet.Name = "March " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet febSheet = book.Worksheets.Add();
            febSheet.Name = "Feburary " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet janSheet = book.Worksheets.Add();
            janSheet.Name = "January " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet decSheet = book.Worksheets.Add();
            decSheet.Name = "December " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet novSheet = book.Worksheets.Add();
            novSheet.Name = "November " + calendar.GetCalendarYear().ToString();
            Excel.Worksheet octSheet = book.Worksheets.Add();
            octSheet.Name = "October " + calendar.GetCalendarYear().ToString();
            // fill sheet
            FillSheet(1, janSheet, janList);
            FillSheet(2, febSheet, febList);
            FillSheet(3, marSheet, marList);
            FillSheet(4, aprSheet, aprList);
            FillSheet(5, maySheet, mayList);
            FillSheet(6, junSheet, junList);
            FillSheet(7, julSheet, julList);
            FillSheet(8, augSheet, augList);
            FillSheet(9, sepSheet, sepList);
            FillSheet(10, octSheet, octList);
            FillSheet(11, novSheet, novList);
            FillSheet(12, decSheet, decList);
            // select active sheet
            if (1 == DateTime.Now.Month)
            {
                janSheet.Select();
            }
            else if (2 == DateTime.Now.Month)
            {
                febSheet.Select();
            }
            else if (3 == DateTime.Now.Month)
            {
                marSheet.Select();
            }
            else if (4 == DateTime.Now.Month)
            {
                aprSheet.Select();
            }
            else if (5 == DateTime.Now.Month)
            {
                maySheet.Select();
            }
            else if (6 == DateTime.Now.Month)
            {
                junSheet.Select();
            }
            else if (7 == DateTime.Now.Month)
            {
                julSheet.Select();
            }
            else if (8 == DateTime.Now.Month)
            {
                augSheet.Select();
            }
            else if (9 == DateTime.Now.Month)
            {
                sepSheet.Select();
            }
            else if (10 == DateTime.Now.Month)
            {
                octSheet.Select();
            }
            else if (11 == DateTime.Now.Month)
            {
                novSheet.Select();
            }
            else if (12 == DateTime.Now.Month)
            {
                decSheet.Select();
            }
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Invoice Register Texas " + DateTime.Today.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }

        public void FillSheet(int month, Excel.Worksheet sheet, List<Invoice> invoiceList)
        {
            // insert image
            Excel.Range imageRange = sheet.get_Range("A1");
            sheet.Shapes.AddPicture("D:\\workspace\\erp\\InvoiceRegisterTexas\\logo.png", Microsoft.Office.Core.MsoTriState.msoFalse, Microsoft.Office.Core.MsoTriState.msoCTrue, 0, 0, 266, 66);
            sheet.Cells.get_Range("A1", "E5").Merge();
            // insert title
            sheet.Cells[6, 1] = "Texas Invoice Register at " + month.ToString() + "/2014 (USD)";
            sheet.Cells.get_Range("A6").Font.Bold = true;
            sheet.Cells.get_Range("A6").Font.Size = 20;
            sheet.Cells.get_Range("A6").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A6", "H6").Merge();
            // build header
            int row = 7;
            int column = 1;
            sheet.Cells[row, column++] = "Credit Note";
            sheet.Cells[row, column++] = "Inv#";
            sheet.Cells[row, column++] = "Inv Date";
            sheet.Cells[row, column++] = "so#";
            sheet.Cells[row, column++] = "Cust Name";
            sheet.Cells[row, column++] = "Cust Id";
            sheet.Cells[row, column++] = "Currency";
            sheet.Cells[row, column++] = "Die Sale";
            sheet.Cells[row, column++] = "Discount";
            sheet.Cells[row, column++] = "Fast Track";
            sheet.Cells[row, column++] = "Surcharge";
            sheet.Cells[row, column++] = "Freight";
            sheet.Cells[row, column++] = "Inv Total";
            sheet.Cells[row, column++] = "Post";
            Excel.Range summaryRange = sheet.Cells.get_Range("A" + row.ToString(), "S" + row.ToString());
            summaryRange.Font.Bold = true;
            summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            double dieSaleTotal = 0.0;
            double surchargeTotal = 0.0;
            double fastTrackTotal = 0.0;
            double freightTotal = 0.0;
            double discountTotal = 0.0;
            double invoiceTotalTotal = 0.0;
            row++;
            column = 1;
            foreach (Invoice invoice in invoiceList)
            {
                // display invoices
                if (null == invoice.creditNote)
                {
                    sheet.Cells[row, column + 1] = invoice.invoiceNumber.ToString();
                }
                else
                {
                    sheet.Cells[row, column++] = invoice.creditNote;
                    sheet.Cells[row, column++] = invoice.invoiceNumber.ToString();
                    sheet.Cells[row, column++] = invoice.invoiceDate.ToString("MM/dd/yyyy").Trim();
                    sheet.Cells[row, column++] = invoice.salesOrder;
                    sheet.Cells[row, column++] = invoice.customerName;
                    sheet.Cells[row, column].NumberFormat = "@";
                    sheet.Cells[row, column++] = invoice.customerID;
                    sheet.Cells[row, column++] = invoice.currency;
                    sheet.Cells[row, column++] = invoice.dieSale.ToString("C2");
                    dieSaleTotal += invoice.dieSale;
                    sheet.Cells[row, column++] = invoice.discount.ToString("C2");
                    discountTotal += invoice.discount;
                    sheet.Cells[row, column++] = invoice.fastTrack.ToString("C2");
                    fastTrackTotal += invoice.fastTrack;
                    sheet.Cells[row, column++] = invoice.surcharge.ToString("C2");
                    surchargeTotal += invoice.surcharge;
                    sheet.Cells[row, column++] = invoice.freight.ToString("C2");
                    freightTotal += invoice.freight;
                    sheet.Cells[row, column++] = invoice.invoiceTotal.ToString("C2");
                    invoiceTotalTotal += invoice.invoiceTotal;
                    sheet.Cells[row, column++] = invoice.posted;
                }
                // adjust style
                Excel.Range rowRange = sheet.Cells.get_Range("A" + row.ToString());
                if ("N" == invoice.posted)
                {
                    rowRange.EntireRow.Cells.Interior.ColorIndex = 22;
                }
                else if (null == invoice.creditNote)
                {
                    if (invoice.invoiceDate.Year > 2000)
                    {
                        rowRange.EntireRow.Cells.Interior.ColorIndex = 33;
                    }
                    else
                    {
                        rowRange.EntireRow.Cells.Interior.ColorIndex = 36;
                    }
                }
                row++;
                column = 1;
            }
            // summary
            column = 7;
            sheet.Cells[row, column++] = "TOTAL:";
            sheet.Cells[row, column++] = dieSaleTotal.ToString("C2");
            sheet.Cells[row, column++] = discountTotal.ToString("C2");
            sheet.Cells[row, column++] = fastTrackTotal.ToString("C2");
            sheet.Cells[row, column++] = surchargeTotal.ToString("C2");
            sheet.Cells[row, column++] = freightTotal.ToString("C2");
            sheet.Cells[row, column++] = invoiceTotalTotal.ToString("C2");
            summaryRange = sheet.Cells.get_Range("G" + row.ToString(), "R" + row.ToString());
            summaryRange.Font.Bold = true;
            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
        }
    }
}
