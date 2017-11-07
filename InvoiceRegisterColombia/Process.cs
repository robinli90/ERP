using System;
using System.Net;
using System.Net.Mail;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;
using System.Threading;
using Excel = Microsoft.Office.Interop.Excel;

namespace InvoiceRegisterColombia
{
    class Process
    {
        private struct Invoice
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
            public double scrapSale;
            public double totalSale;
            public double ret35;
            public double ivaRet8;
            public double iva16;
            public double invoiceTotal;
            public string posted;
        };

        public string filePath = string.Empty;

        private void WriteYear(int year, ref Excel.Workbook book)
        {
            List<Invoice> invoiceList = new List<Invoice>();
            // build connection
            string query = "select dhincr, dhinv#, dhidat, dhbnam, dhbcs#, dhord#, dhterr, dhcurr, dhpost, dhtoti from cmsdat.oih where dhplnt='004' and (dhidat>'" + (year - 1) + "-12-31' and dhidat<'" + (year + 1) + "-01-01') order by dhinv#";
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
            // total sale
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                invoice.totalSale = invoice.dieSale + invoice.surcharge + invoice.fastTrack + invoice.freight + invoice.discount;
                invoiceList[i] = invoice;
            }
            // scarp sale
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                query = "select sum(dipric*diqtsp) as scr from cmsdat.oid where diglcd='SCR' and diinv#=" + invoice.invoiceNumber.ToString();
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && string.Empty != reader["scr"].ToString())
                {
                    invoice.scrapSale = Convert.ToDouble(reader["scr"]);
                }
                else
                {
                    invoice.scrapSale = 0.0;
                }
                reader.Close();
                invoiceList[i] = invoice;
            }
            // tax
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                if ("CP" == invoice.currency)
                {
                    // RET 3.5%
                    query = "select notxam from cmsdat.oix where noinv#=" + invoice.invoiceNumber.ToString() + " and notxtp=105";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read() && string.Empty != reader["notxam"].ToString().Trim())
                    {
                        invoice.ret35 = Convert.ToDouble(reader["notxam"]);
                    }
                    else
                    {
                        invoice.ret35 = 0.0;
                    }
                    reader.Close();
                    // IVA RET 8%
                    query = "select notxam from cmsdat.oix where noinv#=" + invoice.invoiceNumber.ToString() + " and notxtp=102";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read() && string.Empty != reader["notxam"].ToString().Trim())
                    {
                        invoice.ivaRet8 = Convert.ToDouble(reader["notxam"]);
                    }
                    else
                    {
                        invoice.ivaRet8 = 0.0;
                    }
                    reader.Close();
                    // IVA 16%
                    query = "select notxam from cmsdat.oix where noinv#=" + invoice.invoiceNumber.ToString() + " and notxtp=101";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read() && string.Empty != reader["notxam"].ToString().Trim())
                    {
                        invoice.iva16 = Convert.ToDouble(reader["notxam"]);
                    }
                    else
                    {
                        invoice.iva16 = 0.0;
                    }
                    reader.Close();
                    invoiceList[i] = invoice;
                }
            }
            // adjust credit orders
            for (int i = 0; i < invoiceList.Count; i++)
            {
                Invoice invoice = invoiceList[i];
                if (invoice.creditNote.Contains("C"))
                {
                    if (invoice.dieSale > 0.0)
                    {
                        invoice.dieSale *= -1.0;
                        invoice.discount *= -1.0;
                        invoice.fastTrack *= -1.0;
                        invoice.freight *= -1.0;
                        invoice.invoiceTotal *= -1.0;
                        invoice.iva16 *= -1.0;
                        invoice.ivaRet8 *= -1.0;
                        invoice.ret35 *= -1.0;
                        invoice.scrapSale *= -1.0;
                        invoice.surcharge *= -1.0;
                        invoice.totalSale *= -1.0;
                    }
                }
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
            List<Invoice> janListPESO = new List<Invoice>();
            List<Invoice> febListPESO = new List<Invoice>();
            List<Invoice> marListPESO = new List<Invoice>();
            List<Invoice> aprListPESO = new List<Invoice>();
            List<Invoice> mayListPESO = new List<Invoice>();
            List<Invoice> junListPESO = new List<Invoice>();
            List<Invoice> julListPESO = new List<Invoice>();
            List<Invoice> augListPESO = new List<Invoice>();
            List<Invoice> sepListPESO = new List<Invoice>();
            List<Invoice> octListPESO = new List<Invoice>();
            List<Invoice> novListPESO = new List<Invoice>();
            List<Invoice> decListPESO = new List<Invoice>();
            List<Invoice> janListUSD = new List<Invoice>();
            List<Invoice> febListUSD = new List<Invoice>();
            List<Invoice> marListUSD = new List<Invoice>();
            List<Invoice> aprListUSD = new List<Invoice>();
            List<Invoice> mayListUSD = new List<Invoice>();
            List<Invoice> junListUSD = new List<Invoice>();
            List<Invoice> julListUSD = new List<Invoice>();
            List<Invoice> augListUSD = new List<Invoice>();
            List<Invoice> sepListUSD = new List<Invoice>();
            List<Invoice> octListUSD = new List<Invoice>();
            List<Invoice> novListUSD = new List<Invoice>();
            List<Invoice> decListUSD = new List<Invoice>();
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
                            janListPESO.Add(invoice);
                            break;
                        case 11:
                            janListUSD.Add(invoice);
                            break;
                        case 20:
                            febListPESO.Add(invoice);
                            break;
                        case 21:
                            febListUSD.Add(invoice);
                            break;
                        case 30:
                            marListPESO.Add(invoice);
                            break;
                        case 31:
                            marListUSD.Add(invoice);
                            break;
                        case 40:
                            aprListPESO.Add(invoice);
                            break;
                        case 41:
                            aprListUSD.Add(invoice);
                            break;
                        case 50:
                            mayListPESO.Add(invoice);
                            break;
                        case 51:
                            mayListUSD.Add(invoice);
                            break;
                        case 60:
                            junListPESO.Add(invoice);
                            break;
                        case 61:
                            junListUSD.Add(invoice);
                            break;
                        case 70:
                            julListPESO.Add(invoice);
                            break;
                        case 71:
                            julListUSD.Add(invoice);
                            break;
                        case 80:
                            augListPESO.Add(invoice);
                            break;
                        case 81:
                            augListUSD.Add(invoice);
                            break;
                        case 90:
                            sepListPESO.Add(invoice);
                            break;
                        case 91:
                            sepListUSD.Add(invoice);
                            break;
                        case 100:
                            octListPESO.Add(invoice);
                            break;
                        case 101:
                            octListUSD.Add(invoice);
                            break;
                        case 110:
                            novListPESO.Add(invoice);
                            break;
                        case 111:
                            novListUSD.Add(invoice);
                            break;
                        case 120:
                            decListPESO.Add(invoice);
                            break;
                        case 121:
                            decListUSD.Add(invoice);
                            break;
                    }
                }
                else
                {
                    // valid invoice
                    if (1 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            janListPESO.Add(invoice);
                            list = 10;
                        }
                        else
                        {
                            janListUSD.Add(invoice);
                            list = 11;
                        }
                    }
                    else if (2 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            febListPESO.Add(invoice);
                            list = 20;
                        }
                        else
                        {
                            febListUSD.Add(invoice);
                            list = 21;
                        }
                    }
                    else if (3 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            marListPESO.Add(invoice);
                            list = 30;
                        }
                        else
                        {
                            marListUSD.Add(invoice);
                            list = 31;
                        }
                    }
                    else if (4 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            aprListPESO.Add(invoice);
                            list = 40;
                        }
                        else
                        {
                            aprListUSD.Add(invoice);
                            list = 41;
                        }
                    }
                    else if (5 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            mayListPESO.Add(invoice);
                            list = 50;
                        }
                        else
                        {
                            mayListUSD.Add(invoice);
                            list = 51;
                        }
                    }
                    else if (6 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            junListPESO.Add(invoice);
                            list = 60;
                        }
                        else
                        {
                            junListUSD.Add(invoice);
                            list = 61;
                        }
                    }
                    else if (7 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            julListPESO.Add(invoice);
                            list = 70;
                        }
                        else
                        {
                            julListUSD.Add(invoice);
                            list = 71;
                        }
                    }
                    else if (8 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            augListPESO.Add(invoice);
                            list = 80;
                        }
                        else
                        {
                            augListUSD.Add(invoice);
                            list = 81;
                        }
                    }
                    else if (9 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            sepListPESO.Add(invoice);
                            list = 90;
                        }
                        else
                        {
                            sepListUSD.Add(invoice);
                            list = 91;
                        }
                    }
                    else if (10 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            octListPESO.Add(invoice);
                            list = 100;
                        }
                        else
                        {
                            octListUSD.Add(invoice);
                            list = 101;
                        }
                    }
                    else if (11 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            novListPESO.Add(invoice);
                            list = 110;
                        }
                        else
                        {
                            novListUSD.Add(invoice);
                            list = 111;
                        }
                    }
                    else if (12 == invoice.invoiceDate.Month)
                    {
                        if ("CP" == invoice.currency)
                        {
                            decListPESO.Add(invoice);
                            list = 120;
                        }
                        else
                        {
                            decListUSD.Add(invoice);
                            list = 121;
                        }
                    }
                }
            }

            // write to excel
            Excel.Worksheet decSheet = book.Worksheets.Add();
            decSheet.Name = "December " + year.ToString();
            Excel.Worksheet novSheet = book.Worksheets.Add();
            novSheet.Name = "November " + year.ToString();
            Excel.Worksheet octSheet = book.Worksheets.Add();
            octSheet.Name = "October " + year.ToString();
            Excel.Worksheet sepSheet = book.Worksheets.Add();
            sepSheet.Name = "September " + year.ToString();
            Excel.Worksheet augSheet = book.Worksheets.Add();
            augSheet.Name = "August " + year.ToString();
            Excel.Worksheet julSheet = book.Worksheets.Add();
            julSheet.Name = "July " + year.ToString();
            Excel.Worksheet junSheet = book.Worksheets.Add();
            junSheet.Name = "June " + year.ToString();
            Excel.Worksheet maySheet = book.Worksheets.Add();
            maySheet.Name = "May " + year.ToString();
            Excel.Worksheet aprSheet = book.Worksheets.Add();
            aprSheet.Name = "April " + year.ToString();
            Excel.Worksheet marSheet = book.Worksheets.Add();
            marSheet.Name = "March " + year.ToString();
            Excel.Worksheet febSheet = book.Worksheets.Add();
            febSheet.Name = "Feburary " + year.ToString();
            Excel.Worksheet janSheet = book.Worksheets.Add();
            janSheet.Name = "January " + year.ToString();
            // fill sheet
            FillSheet(1, year, janSheet, janListPESO, janListUSD);
            FillSheet(2, year, febSheet, febListPESO, febListUSD);
            FillSheet(3, year, marSheet, marListPESO, marListUSD);
            FillSheet(4, year, aprSheet, aprListPESO, aprListUSD);
            FillSheet(5, year, maySheet, mayListPESO, mayListUSD);
            FillSheet(6, year, junSheet, junListPESO, junListUSD);
            FillSheet(7, year, julSheet, julListPESO, julListUSD);
            FillSheet(8, year, augSheet, augListPESO, augListUSD);
            FillSheet(9, year, sepSheet, sepListPESO, sepListUSD);
            FillSheet(10, year, octSheet, octListPESO, octListUSD);
            FillSheet(11, year, novSheet, novListPESO, novListUSD);
            FillSheet(12, year, decSheet, decListPESO, decListUSD);
        }

        public void Run()
        {
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            WriteYear(DateTime.Now.Year, ref book);
            WriteYear(DateTime.Now.Year - 1, ref book);
            // select active sheet
            Excel.Worksheet activeSheet = book.Worksheets[DateTime.Now.Month + 12];
            activeSheet.Select();
            // save to file
            filePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Invoice Register Colombia " + DateTime.Today.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(filePath);
            book.SaveAs(filePath, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
        }

        public void SendEmail()
        {
            // email body
            MailMessage mailmsg = new MailMessage();
            string query = "select [Address] from tiger.dbo.[Invoice_Register_Colombia_Recipient]";
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.DECADE_MARKHAM);
            OdbcDataReader reader = solarsoft.RunQuery(query);
            // get main data
            while (reader.Read())
            {
                mailmsg.To.Add(reader[0].ToString().Trim());
            }
            reader.Close();
            MailAddress from = new MailAddress("office@etsdies.com");
            mailmsg.From = from;
            mailmsg.Subject = "invoice register for Colombia at " + DateTime.Now.ToString("MMMM dd yyyy");
            mailmsg.Attachments.Add(new Attachment(filePath));
            mailmsg.Body = "Today’s Colombia invoice register report.";
            // smtp client
            SmtpClient client = new SmtpClient("mass-smtp.pathcom.com", 25);
            NetworkCredential credential = new NetworkCredential("office@etsdies.com", "5Zh2P8k4@2");
            client.Credentials = credential;
            client.Send(mailmsg);
            mailmsg.Attachments.Clear();
        }

        private void FillSheet(int month, int year, Excel.Worksheet sheet, List<Invoice> peso, List<Invoice> usd)
        {
            // insert image
            Excel.Range imageRange = sheet.get_Range("A1");
            //sheet.Shapes.AddPicture("D:\\workspace\\erp\\InvoiceRegisterColombia\\logo.png", Microsoft.Office.Core.MsoTriState.msoFalse, Microsoft.Office.Core.MsoTriState.msoCTrue, 0, 0, 266, 66);
            sheet.Cells.get_Range("A1", "E5").Merge();
            // insert title
            int row = 6;
            sheet.Cells[row, 1] = "Colombia Invoice Register at " + month.ToString() + "/" + year + " (PESO)";
            sheet.Cells.get_Range("A" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString()).Font.Size = 20;
            sheet.Cells.get_Range("A" + row.ToString()).Font.ColorIndex = 3;
            sheet.Cells.get_Range("A" + row.ToString(), "H" + row.ToString()).Merge();
            // insert legend
            row += 3;
            sheet.Cells[row++, 1] = "Legend";
            Excel.Range legendRange = sheet.Cells.get_Range("A" + row.ToString(), "B" + row.ToString());
            legendRange.Cells.Interior.ColorIndex = 33;
            legendRange.Merge();
            sheet.Cells[row, 3] = "Posted before this month.";
            legendRange = sheet.Cells.get_Range("C" + row.ToString(), "E" + row.ToString());
            legendRange.Merge();
            row++;
            legendRange = sheet.Cells.get_Range("A" + row.ToString(), "B" + row.ToString());
            legendRange.Cells.Interior.ColorIndex = 22;
            legendRange.Merge();
            sheet.Cells[row, 3] = "Not posted yet.";
            legendRange = sheet.Cells.get_Range("C" + row.ToString(), "E" + row.ToString());
            legendRange.Merge();
            row++;
            legendRange = sheet.Cells.get_Range("C" + row.ToString(), "E" + row.ToString()); legendRange = sheet.Cells.get_Range("A" + row.ToString(), "B" + row.ToString());
            legendRange.Cells.Interior.ColorIndex = 36;
            legendRange.Merge();
            sheet.Cells[row, 3] = "Empty invoice.";
            legendRange = sheet.Cells.get_Range("C" + row.ToString(), "E" + row.ToString());
            legendRange.Merge();
            row += 3;
            // build header
            int column = 1;
            sheet.Cells[row, column++] = "Credit Note";
            sheet.Cells[row, column++] = "Inv#";
            sheet.Cells[row, column++] = "Inv Date";
            sheet.Cells[row, column++] = "so#";
            sheet.Cells[row, column++] = "Cust Name";
            sheet.Cells[row, column++] = "Cust Id";
            sheet.Cells[row, column++] = "Currency";
            sheet.Cells[row, column++] = "Die Sale";
            sheet.Cells[row, column++] = "Surcharge";
            sheet.Cells[row, column++] = "Fast Track";
            sheet.Cells[row, column++] = "Freight";
            sheet.Cells[row, column++] = "Discount";
            sheet.Cells[row, column++] = "Total Sale";
            sheet.Cells[row, column++] = "Scrap Sale";
            sheet.Cells[row, column++] = "RET 3.5%";
            sheet.Cells[row, column++] = "IVA RET 8%";
            sheet.Cells[row, column++] = "IVA 16%";
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
            double totalSaleTotal = 0.0;
            double scarpSaleTotal = 0.0;
            double ret35Total = 0.0;
            double ivaRet8Total = 0.0;
            double iva16Total = 0.0;
            double invoiceTotalTotal = 0.0;
            row++;
            column = 1;
            foreach (Invoice invoice in peso)
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
                    sheet.Cells[row, column++] = invoice.surcharge.ToString("C2");
                    surchargeTotal += invoice.surcharge;
                    sheet.Cells[row, column++] = invoice.fastTrack.ToString("C2");
                    fastTrackTotal += invoice.fastTrack;
                    sheet.Cells[row, column++] = invoice.freight.ToString("C2");
                    freightTotal += invoice.freight;
                    sheet.Cells[row, column++] = invoice.discount.ToString("C2");
                    discountTotal += invoice.discount;
                    sheet.Cells[row, column++] = invoice.totalSale.ToString("C2");
                    totalSaleTotal += invoice.totalSale;
                    sheet.Cells[row, column++] = invoice.scrapSale.ToString("C2");
                    scarpSaleTotal += invoice.scrapSale;
                    sheet.Cells[row, column++] = invoice.ret35.ToString("C2");
                    ret35Total += invoice.ret35;
                    sheet.Cells[row, column++] = invoice.ivaRet8.ToString("C2");
                    ivaRet8Total += invoice.ivaRet8;
                    sheet.Cells[row, column++] = invoice.iva16.ToString("C2");
                    iva16Total += invoice.iva16;
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
            sheet.Cells[row, column++] = surchargeTotal.ToString("C2");
            sheet.Cells[row, column++] = fastTrackTotal.ToString("C2");
            sheet.Cells[row, column++] = freightTotal.ToString("C2");
            sheet.Cells[row, column++] = discountTotal.ToString("C2");
            sheet.Cells[row, column++] = totalSaleTotal.ToString("C2");
            sheet.Cells[row, column++] = scarpSaleTotal.ToString("C2");
            sheet.Cells[row, column++] = ret35Total.ToString("C2");
            sheet.Cells[row, column++] = ivaRet8Total.ToString("C2");
            sheet.Cells[row, column++] = iva16Total.ToString("C2");
            sheet.Cells[row, column++] = invoiceTotalTotal.ToString("C2");
            summaryRange = sheet.Cells.get_Range("G" + row.ToString(), "R" + row.ToString());
            summaryRange.Font.Bold = true;


            column = 1;
            row += 4;
            sheet.Cells[row, 1] = "Colombia Invoice Register at " + month.ToString() + "/" + year + " (USD)";
            sheet.Cells.get_Range("A" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString()).Font.Size = 20;
            sheet.Cells.get_Range("A" + row.ToString()).Font.ColorIndex = 3;
            sheet.Cells.get_Range("A" + row.ToString(), "H" + row.ToString()).Merge();
            row++;
            sheet.Cells[row, column++] = "Credit Note";
            sheet.Cells[row, column++] = "Inv#";
            sheet.Cells[row, column++] = "Inv Date";
            sheet.Cells[row, column++] = "so#";
            sheet.Cells[row, column++] = "Cust Name";
            sheet.Cells[row, column++] = "Cust Id";
            sheet.Cells[row, column++] = "Currency";
            sheet.Cells[row, column++] = "Die Sale";
            sheet.Cells[row, column++] = "Surcharge";
            sheet.Cells[row, column++] = "Fast Track";
            sheet.Cells[row, column++] = "Freight";
            sheet.Cells[row, column++] = "Discount";
            sheet.Cells[row, column++] = "Total Sale";
            sheet.Cells[row, column++] = "Scrap Sale";
            sheet.Cells[row, column++] = "RET 3.5%";
            sheet.Cells[row, column++] = "IVA RET 8%";
            sheet.Cells[row, column++] = "IVA 16%";
            sheet.Cells[row, column++] = "Inv Total";
            sheet.Cells[row, column++] = "Post";
            summaryRange = sheet.Cells.get_Range("A" + row.ToString(), "S" + row.ToString());
            summaryRange.Font.Bold = true;
            summaryRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row += 1;
            column = 1;
            dieSaleTotal = 0.0;
            surchargeTotal = 0.0;
            fastTrackTotal = 0.0;
            freightTotal = 0.0;
            discountTotal = 0.0;
            totalSaleTotal = 0.0;
            scarpSaleTotal = 0.0;
            ret35Total = 0.0;
            ivaRet8Total = 0.0;
            iva16Total = 0.0;
            invoiceTotalTotal = 0.0;
            foreach (Invoice invoice in usd)
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
                    sheet.Cells[row, column++] = invoice.customerID;
                    sheet.Cells[row, column++] = invoice.currency;
                    sheet.Cells[row, column++] = invoice.dieSale.ToString("C2");
                    dieSaleTotal += invoice.dieSale;
                    sheet.Cells[row, column++] = invoice.surcharge.ToString("C2");
                    surchargeTotal += invoice.surcharge;
                    sheet.Cells[row, column++] = invoice.fastTrack.ToString("C2");
                    fastTrackTotal += invoice.fastTrack;
                    sheet.Cells[row, column++] = invoice.freight.ToString("C2");
                    freightTotal += invoice.freight;
                    sheet.Cells[row, column++] = invoice.discount.ToString("C2");
                    discountTotal += invoice.discount;
                    sheet.Cells[row, column++] = invoice.totalSale.ToString("C2");
                    totalSaleTotal += invoice.totalSale;
                    sheet.Cells[row, column++] = invoice.scrapSale.ToString("C2");
                    scarpSaleTotal += invoice.scrapSale;
                    sheet.Cells[row, column++] = invoice.ret35.ToString("C2");
                    ret35Total += invoice.ret35;
                    sheet.Cells[row, column++] = invoice.ivaRet8.ToString("C2");
                    ivaRet8Total += invoice.ivaRet8;
                    sheet.Cells[row, column++] = invoice.iva16.ToString("C2");
                    iva16Total += invoice.iva16;
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
            sheet.Cells[row, column++] = surchargeTotal.ToString("C2");
            sheet.Cells[row, column++] = fastTrackTotal.ToString("C2");
            sheet.Cells[row, column++] = freightTotal.ToString("C2");
            sheet.Cells[row, column++] = discountTotal.ToString("C2");
            sheet.Cells[row, column++] = totalSaleTotal.ToString("C2");
            sheet.Cells[row, column++] = scarpSaleTotal.ToString("C2");
            sheet.Cells[row, column++] = ret35Total.ToString("C2");
            sheet.Cells[row, column++] = ivaRet8Total.ToString("C2");
            sheet.Cells[row, column++] = iva16Total.ToString("C2");
            sheet.Cells[row, column++] = invoiceTotalTotal.ToString("C2");
            summaryRange = sheet.Cells.get_Range("G" + row.ToString(), "R" + row.ToString());
            summaryRange.Font.Bold = true;

            // adjust style
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
        }
    }
}
