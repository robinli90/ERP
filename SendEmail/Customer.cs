using ExcoUtility;
using System.IO;
using System.Data;
using System.Data.Odbc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Mail;
using System.IO.Compression;
using System.Threading;


// Added auto mail confirmations (Robin Edit March 2015)

namespace SendEmail
{
    public class Customer 
    {
        public string mailAdd = string.Empty;
        public List<string> fileList = new List<string>();
        public string[,] entries = new string[20,5];
        static Dictionary<string, List<string>> Email_List = new Dictionary<string, List<string>>();
        static Dictionary<string, List<string>> Order_List = new Dictionary<string, List<string>>();
        static Dictionary<string, List<string>> Ship_List  = new Dictionary<string, List<string>>();

        /*
        // Get Customer email information (key = customercode, value = emails) and populate Email_List dictionary
        void GetEmails()
        {
            //string query = "select * from [dbo].[d_mailinglist] where confirmations = 1 order by customercode";
            string query = "select * from d_testcustomersmail order by customercode";
            ExcoODBC database = ExcoODBC.Instance;
            OdbcDataReader reader;
            database.Open(Database.DECADE_MARKHAM);
            // Get Extra charges
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                List<string> list;
                if (!Email_List.TryGetValue(reader[0].ToString().Trim(), out list))
                {
                    Email_List.Add(reader[0].ToString().Trim(), list = new List<string>());
                    list = Email_List[reader[0].ToString().Trim()];
                    list.Add(reader[1].ToString().Trim());
                    list.Add(reader[2].ToString().Trim());
                    Email_List[reader[0].ToString().Trim()] = list;
                }
                else
                {
                    list = Email_List[reader[0].ToString().Trim()];
                    list.Add(reader[1].ToString().Trim());
                    list.Add(reader[2].ToString().Trim());
                    Email_List[reader[0].ToString().Trim()] = list;
                }
            }
            reader.Close();
        }

        // Get all the orders associated with a certain order date and populate Order_List dictionary
        void GetOrders(string orderdate)
        {
            string query = "select distinct c.CustomerCode as CustomerCode, c.dienumber as JobNumber, c.ordernumber as Ordernumber, c.customerpo " +
                           "as CustomerPO from (select a.ordernumber, b.customerpo, b.customercode as CustomerCode, a.dienumber "  +
                           "from d_orderitem as a, d_order as b where a.ordernumber = b.ordernumber and " +
                           "(b.orderdate between '" + GetDate(orderdate) + "' and '" + GetDate(orderdate, 1) + "') and b.ordernumber is not null)c " +
                           "where c.dienumber is not null order by customercode, ordernumber ";

            ExcoODBC database = ExcoODBC.Instance;
            OdbcDataReader reader;
            database.Open(Database.DECADE_MARKHAM);
            // Get Extra charges
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                List<string> list;
                if (!Order_List.TryGetValue(reader[0].ToString().Trim(), out list))
                {
                    Order_List.Add(reader[0].ToString().Trim(), list = new List<string>());
                    list = Order_List[reader[0].ToString().Trim()];
                    list.Add(reader[2].ToString().Trim()); // Shop order number
                    list.Add(reader[1].ToString().Trim()); // Job number
                    list.Add(reader[3].ToString().Trim()); // Customer PO
                    Order_List[reader[0].ToString().Trim()] = list;
                }
                else
                {
                    list = Order_List[reader[0].ToString().Trim()];
                    list.Add(reader[2].ToString().Trim());
                    list.Add(reader[1].ToString().Trim());
                    list.Add(reader[3].ToString().Trim());
                    Order_List[reader[0].ToString().Trim()] = list;
                }
            }
            reader.Close();
        }

        // Get all the orders associated with a certain shipping date and populate Order_List dictionary (yesterday 8AM till today 8AM)
        void GetShip(string shipdate)
        {
            DateTime morning_date_orig = Convert.ToDateTime(shipdate);
            DateTime evening_date_orig = Convert.ToDateTime(shipdate);
            morning_date_orig = morning_date_orig.AddDays(-1);
            DateTime morning_date = new DateTime(morning_date_orig.Year, morning_date_orig.Month, morning_date_orig.Day, 5, 0, 0);
            DateTime evening_date = new DateTime(evening_date_orig.Year, evening_date_orig.Month, evening_date_orig.Day, 5, 0, 0);

            string query = "select a.customercode as CustomerCode, b.dienumber as JobNumber, a.customerpo as CustomerPO " +
                           ", a.expreceiveddate as DeliveryDate, a.trackingnumber as TrackingNumber, a.fasttrack as FastTrack from d_order as a" + 
                           ", d_orderitem as b where a.ordernumber = b.ordernumber and a.shipdate " +  
                           "between '" + morning_date.ToString("yyyy-MM-dd") +"' and '" + evening_date.ToString("yyyy-MM-dd") + 
                           "' and a.customerpo not like '%cancel%' order by DeliveryDate asc";
            Console.WriteLine("Query: " + query);
            ExcoODBC database = ExcoODBC.Instance;
            OdbcDataReader reader;
            database.Open(Database.DECADE_MARKHAM);
            // Get Extra charges
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                List<string> list;
                if (!Ship_List.TryGetValue(reader[0].ToString().Trim(), out list))
                {
                    Ship_List.Add(reader[0].ToString().Trim(), list = new List<string>());
                    list = Ship_List[reader[0].ToString().Trim()];
                    list.Add(reader[1].ToString().Trim());              // Job Number
                    if (reader.IsDBNull(2)) { list.Add("<Pending>"); }  
                    else { list.Add(reader[2].ToString().Trim()); }     // Customer PO
                    list.Add(reader[3].ToString().Trim());              // Delivery Date
                    list.Add(reader[4].ToString().Trim());              // Tracking Number
                    list.Add(reader[5].ToString().Trim());              // Fastrack bool
                    Ship_List[reader[0].ToString().Trim()] = list;
                }
                else
                {
                    list = Ship_List[reader[0].ToString().Trim()];
                    list.Add(reader[1].ToString().Trim());              // Job Number
                    if (reader.IsDBNull(2)) { list.Add("<Pending>"); }  // PO is pending if null
                    else { list.Add(reader[2].ToString().Trim()); }     // Customer PO}
                    list.Add(reader[3].ToString().Trim());              // Delivery Date
                    list.Add(reader[4].ToString().Trim());              // Tracking Number
                    list.Add(reader[5].ToString().Trim());              // Fastrack bool
                    Ship_List[reader[0].ToString().Trim()] = list;
                }
            }
            reader.Close();
        }

        // Return the date and ignore weekends/holidays
        static string GetDate(string date_str, int AddDate=0)
        {
            DateTime date = Convert.ToDateTime(date_str);
            date = date.AddDays(AddDate); // Add extra days required
            while (date.DayOfWeek == DayOfWeek.Saturday || date.DayOfWeek == DayOfWeek.Sunday)
            {
                date = date.AddDays(1);
            }
            return date.ToString("yyyy-MM-dd");
        }

        // Return the names of the customers in customercode; return in "firstname lastname, firstname lastname, firstname lastname, ... "
        static string Get_Names(string customercode) {

            int count = 0;
            string names = "";
            string prev_name = "";
            if (Email_List.ContainsKey(customercode))
            {
                foreach (string element in Email_List[customercode].ToList())
                {
                    if (!(element.ToString() == prev_name)) {
                        if (count % 2 == 0)
                        {
                            names = names + element.ToString() + ", ";
                            prev_name = element.ToString();
                        }
                    }
                    count++;
                }
            }
            return names;
        }

        // Process all shop order numbers associated with customer code
        static string Process_Jobs(string customercode)
        {
            string current_SO = "";
            int count = 0;
            string jobs = "";
            if (Email_List.ContainsKey(customercode) && Order_List.ContainsKey(customercode))
            {
                foreach (string element in Order_List[customercode].ToList())
                {

                    if (count % 3 == 0)
                    {
                        if (!(Order_List[customercode][count].ToString() == current_SO))
                        {
                            jobs = jobs + Get_Jobs(Order_List[customercode][count + 1].ToString(), Order_List[customercode][count].ToString(), Order_List[customercode][count + 2].ToString());
                        }
                        current_SO = Order_List[customercode][count].ToString();
                    }
                    count++;
                }
            }
            return jobs;
        }

        // Process all shop order numbers associated with customer code
        static string Process_Shipping(string customercode)
        {
            int count = 0;
            string jobs = "";
            if (Email_List.ContainsKey(customercode) && Ship_List.ContainsKey(customercode))
            {
                foreach (string element in Ship_List[customercode].ToList())
                {

                    if (count % 5 == 0)
                    {
                        jobs = jobs + "<tr colspan=4>" +
                            "<td rowspan=1><center>" + Ship_List[customercode][count].ToString() + "</center></td>" +
                            "<td rowspan=1><center>" + Ship_List[customercode][count + 1].ToString() + "</center></td>";
                        if (Ship_List[customercode][count + 4].ToString() == "True") // If fast track, do NOT add a day
                        { 
                            jobs = jobs + "<td rowspan=1><center>" + GetDate(Ship_List[customercode][count + 2].ToString()) + "</center></td>";
                        }
                        else
                        {
                            jobs = jobs + "<td rowspan=1><center>" + GetDate(Ship_List[customercode][count + 2].ToString(), 1) + "</center></td>";
                        }
                        jobs = jobs + "<td rowspan=1><center>" + Ship_List[customercode][count + 3].ToString() + "</center></td></tr>";
                    }
                    count++;
                }
            }
            return jobs;
        }

        // Return the HTML string for entries
        static string Get_Entries(string die_number, string ordernumber) {
            int count = 0, count2 = 0;
            // Base headers per entry
            string entries_string = "<table><td style=\"border:0\"><center><b><u>Die#</u></b></center></td>" +
                                    "<td style=\"border:0\"><b><u>Description</u></b></td>" +
                                    "<td style=\"border:0\"><center><b><u>Qty</u></b><center></td>" +
                                    "<td style=\"border:0\"><center><b><u>Unit</u></b></center></td>" +
                                    "<td style=\"border:0\"><b><u>Extended</u></b></td></tr><tr cellpadding=100;>" ;
            string[,] charges = new string[10,5];
            for (int i=0; i<10; i++) charges[i,0] = "X"; // Reset charge entries
            string query = "select line, chargename, CONVERT(varchar, cast(price as money), 1), " +
                           "qty, chargeprice from d_orderitemcharges where ordernumber =" + ordernumber;
            ExcoODBC database = ExcoODBC.Instance;
            OdbcDataReader reader;
            database.Open(Database.DECADE_MARKHAM);
            // Get Extra charges
            reader = database.RunQuery(query);
            while (reader.Read()) {
                charges[count2,0] = reader[0].ToString();
                charges[count2,1] = reader[1].ToString();
                charges[count2,2] = reader[2].ToString();
                charges[count2,3] = reader[3].ToString();
                charges[count2,4] = reader[4].ToString();
                count2++;
            }
            reader.Close();
            // Get dies
            query = "select line, qty, description, CONVERT(varchar, cast(baseprice as money), 1),  CONVERT(varchar, " +
            "cast(price as money), 1), dienumber from d_orderitem where ordernumber = " + ordernumber + " order by ordernumber desc";
            reader = database.RunQuery(query);
            while (reader.Read()) {
                // Only print Die# once
                entries_string = entries_string + "<td style=\"border:0\">" + reader[5].ToString() + "</td>"; 
                count++;
                entries_string = entries_string + "<td style=\"border:0\">" + reader[2].ToString() + "</td>" +
                                "<td style=\"border:0\"><center>" + reader[1].ToString() + "</center></td>" +
                                "<td align=right style=\"border:0\">$" + reader[3].ToString() + " </td>" +
                                "<td align=right style=\"border:0\">$" + reader[4].ToString() + "</td></tr><tr>";
                for (int i=0; i<10; i++) {
                    if (!(charges[i, 0] == "X") && charges[i, 0] == count.ToString()) {
                        entries_string = entries_string + "<td style=\"border:0\"></td>" +
                                    "<td style=\"border:0\">" + charges[i, 1] + "</td>" +
                                    "<td style=\"border:0\"><center>" + charges[i, 3] + "</center></td>" +
                                    "<td align=right style=\"border:0\">" + string.Format("{0:C2}", float.Parse(charges[i,4])) + "</td>" +
                                    "<td align=right style=\"border:0\">$" + charges[i, 2] + "</td></tr><tr>";
                    }
                }
            }
            reader.Close();
            return entries_string;
        }

        // Extra charges like freight, gst, fastrack, discount
        static string Get_Extra(string freight, string gst, string fasttrack, string discount)
        {
            string extra = "";
            if (Convert.ToDouble(freight) > 0)
            {
                extra = extra + "<td style=\"border:0\"></td>" +
                "<td style=\"border:0\"></td>" +
                "<td style=\"border:0\"></td>" +
                "<td align=right style=\"border:0\"><b><u>Freight</u></b></td>" +
                "<td align=right style=\"border:0\">" + string.Format("{0:C2}", float.Parse(freight)) + "</td></tr><tr>";
            }
            
            if (Convert.ToDouble(gst) > 0)
            {
                extra = extra + "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td align=right style=\"border:0\"><b><u>GST</u></b></td>" +
                    "<td align=right style=\"border:0\">$" + gst + "</td></tr><tr>";
            }
            if (Convert.ToDouble(fasttrack) > 0)
            {
                extra = extra + "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td align=right style=\"border:0\"><b><u>Fast Track</u></b></td>" +
                    "<td align=right style=\"border:0\">$" + fasttrack + "</td></tr><tr>";
            }
            if (Convert.ToDouble(discount) > 0)
            {
                extra = extra + "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td style=\"border:0\"></td>" +
                    "<td align=right style=\"border:0\"><b><u>Discount</u></b></td>" +
                    "<td align=right style=\"border:0\">$" + discount + "</td></tr><tr>";
            }
            return extra;
        }

        // Get associated jobs with SHOP ORDER NUMBER ONLY
        static string Get_Jobs(string job_number, string SO_number, string customerPO) 
        {
            string query = "select substring(cast(expreceiveddate as char(12)),0,112) as DeliveryDate, steelsurcharge as Surcharge, " +
                           "freight as Freight, total as Total, gst as GST, fasttrackcharge as FastTrack, discountamount as Discount " + 
                           "from d_order where ordernumber = " + SO_number;
            string deliveryDate = "", surcharge = "", freight = "", total = "", gst = "", fasttrack = "", discount = "";
            ExcoODBC database = ExcoODBC.Instance;
            OdbcDataReader reader;
            database.Open(Database.DECADE_MARKHAM);
            // Get Extra charges
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                deliveryDate = reader[0].ToString();
                surcharge = reader[1].ToString();
                freight = reader[2].ToString();
                total = reader[3].ToString();
                gst = reader[4].ToString();
                fasttrack = reader[5].ToString();
                discount = reader[6].ToString();
            }
            reader.Close();
            string job_string = "";
            string subtotal = (Convert.ToDecimal(Convert.ToDouble(total) - (Convert.ToDouble(freight) + Convert.ToDouble(surcharge) + Convert.ToDouble(gst) + Convert.ToDouble(fasttrack) - Convert.ToDouble(discount)) + 0.00)).ToString();

            job_string =
                //Job number/PO#/Delivery Date
            "<tr colspan=4>" +
            "<td rowspan=1><center>" + SO_number + "</center></td>" +
            "<td rowspan=1><center>" + customerPO + "</center></td>" +
            "<td rowspan=1><center>" + deliveryDate + "</center></td><td>" +
                //"<td rowspan=1><center>" + GetDate(deliveryDate, 0) + "</center></td><td>" +

            // Get Entries
            Get_Entries(job_number, SO_number) +

            //Sub-total/Surcharge/Freight/Total lines
            #region Totals
            "<td style=\"border:0\"></td>" +
            "<td style=\"border:0\"></td>" +
            "<td align=right colspan=2 style=\"border:0\"><b><u>Sub Total</u></b></td>" +
            "<td  align=right style=\"border:0\">" + string.Format("{0:C2}", float.Parse(subtotal)) + "</td></tr><tr>" +
            "<td style=\"border:0\"></td>" +
            "<td align=right colspan=3 style=\"border:0\"><b><u>Steel Surcharge</u></b></td>" +
            "<td align=right style=\"border:0\">" + string.Format("{0:C2}", float.Parse(surcharge)) + "</td></tr><tr>" +
            Get_Extra(freight, gst, fasttrack, discount) + 
            "<td style=\"border:0\"></td>" +
            "<td style=\"border:0\"></td>" +
            "<td style=\"border:0\"></td>" +
            "<td align=right style=\"border:0\"><b><u>Total</u></b></td>" +
            "<td align=right style=\"border:0\">" + string.Format("{0:C2}", float.Parse(total)) + "</td>" +
            "</td></table></tr>";
            #endregion

            return job_string;
        }

        // Create the HTML mail message FOR SHIPPING with associated names
        static string Get_Mail_Message_Shipping(string date, string customercode)
        {
            return "<br><center><font size=\"5\"><b>Shipping Confirmation</b></center></br>" +
            "<br><font size=\"3\"><b>ATTN: </b>" + Get_Names(customercode) + "</br>" +
            "<br></br>" +
            "<br><b>Shipping Date: " + date + "</b></br>" +
            "<br></br>" +
            "<br></br>" +
            "<br></br>" +
            "<html><head><style>" +

            "table, th, td { max-width: 200px; border: 1px solid black; border-collapse: collapse; padding: 5px; table-layout:fixed}" +
            "</style></head><body><table>" +

            "<tr><th><u>Job Number</u></th>" +
            "<th><u>Customer PO Number</u></th>" +
            "<th><u>Delivery Date</u></th>" +
            "<th><u>Tracking Number</u></th></tr>" +

            Process_Shipping(customercode) +

            "</table></body></html>";
        }

        // Create the HTML mail message with associated names
        static string Get_Mail_Message(string date, string customercode)
        {
            return "<br><center><font size=\"5\"><b>Order Confirmation</b></center></br>" +
            //"<br><font size=\"3\">Sierra Aluminum Co. (F) </br>" +
            "<br><font size=\"3\"><b>ATTN: </b>" + Get_Names(customercode) + "</br>" +
            "<br></br>" +
            "<br><b>Order Date: " + date + "</b></br>" +
            "<br></br>" +
            "<br></br>" +
            "<br></br>" +
            "<html><head><style>" +

            "table, th, td { width: 150px; border: 1px solid black; border-collapse: collapse; padding: 5px; }" +
            "</style></head><body><table>" +

            "<tr><th><u>SO Number</u></th>" +
            "<th><u>Customer PO#</u></th>" +
            "<th><u>Delivery Date</u></th>" +
            "<th colspan=1><u>Pricing Detail</u></th></tr>" +

            Process_Jobs(customercode) + 

            "</table></body></html>";
        }
        */


        // Send the email (Default Tiger's email program that runs at 11PM)
        public void SendEmail(string backersubj = "")
        {
            // email body
            MailMessage mailmsg = new MailMessage();
            while (mailAdd.Contains(' '))
            {
                int spaceIndex = mailAdd.IndexOf(' ');
                mailmsg.To.Add(mailAdd.Substring(0, spaceIndex).Trim());
                mailAdd = mailAdd.Substring(spaceIndex).Trim();
            }
            mailmsg.To.Add(mailAdd);
            //mailmsg.To.Add("rli@etsdies.com");
            MailAddress from = new MailAddress("ipasmenko@etsdies.com");
            mailmsg.From = from;
            mailmsg.Subject = "Designs for Your Records " + (backersubj.Length > 0 ? "(" + backersubj + ")" : "");

            if (fileList.Count == 0)
            {
                goto End;
            }

            foreach (string file in fileList)
            {
                if (File.Exists(file))
                {
                    mailmsg.Attachments.Add(new Attachment(file));
                }
            }
            // smtp client
            //SmtpClient client = new SmtpClient("mass-smtp.pathcom.com", 25); //Updated pathcom
            SmtpClient client = new SmtpClient("smtp.pathcom.com", 587);
            NetworkCredential credential = new NetworkCredential("ipasmenko@etsdies.com", "qvsFxy58C@5");
            client.Credentials = credential;
            bool hasSend = false;
            while (!hasSend)
            {
                try
                {
                    if (fileList.Count > 0 && mailmsg.Attachments.Count > 0)
                    {
                        client.Send(mailmsg);
                    }
                    hasSend = true;
                }
                catch
                {
                    hasSend = false;
                }
            }
            if (hasSend)
            {
                Thread.Sleep(new TimeSpan(0, 0, 15 * mailmsg.Attachments.Count()));
                mailmsg.Attachments.Dispose();
            }

            End:
                ;
        }
        
            /*
        // Send Order Confirmation email
        public void SendOrderEmail()
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd"); //"2015-03-05";
            GetEmails();
            GetOrders(date);

            foreach (KeyValuePair<string, List<string>> pair in Order_List.ToList())
            {
                string custcode = pair.Key.ToString().Trim();
                
                if (Email_List.ContainsKey(custcode) && Order_List.ContainsKey(custcode))
                {
                    string query = "select name from d_customer where customercode = '" + custcode + "'";
                    ExcoODBC database = ExcoODBC.Instance;
                    OdbcDataReader reader2;
                    database.Open(Database.DECADE_MARKHAM);
                    // Get Extra charges
                    reader2 = database.RunQuery(query);
                    string customer_name;
                    try
                    {
                        customer_name = reader2[0].ToString().Trim();
                    }
                    catch { customer_name = ""; }
                    reader2.Close();
                    // email body
                    MailMessage mailmsg = new MailMessage();

                    // Add mail to all recipients associated with customer code
                    #region Mail All with custcode
                    int count = 0;
                    if (Email_List.ContainsKey(custcode))
                    {
                        foreach (string element in Email_List[custcode].ToList())
                        {
                            if (count % 2 == 1)
                            {
                                mailmsg.To.Add(element.ToString());
                            }
                            count++;
                        }
                    }
                    #endregion
                    //mailmsg.To.Add(mailAdd);
                    MailAddress from = new MailAddress("rli@etsdies.com");
                    mailmsg.From = from;
                    mailmsg.Subject = "Order Confirmation (" + customer_name + ")";
                    mailmsg.Body = Get_Mail_Message(date, custcode); 
                    mailmsg.IsBodyHtml = true;
                    // smtp client
                    SmtpClient client = new SmtpClient("mass-smtp.pathcom.com", 25); //Updated pathcom
                    //SmtpClient client = new SmtpClient("smtp.pathcom.com", 587);
                    //NetworkCredential credential = new NetworkCredential("rli@etsdies.com", "5Zh2Pman");
                    //client.Credentials = credential;
                    bool hasSend = false;
                    while (!hasSend)
                    {
                        try
                        {
                            if (fileList.Count > 0)
                            {
                                client.Send(mailmsg);
                            }
                            hasSend = true;
                        }
                        catch
                        {
                            hasSend = false;
                        }
                    }
                    if (hasSend)
                    {
                        Thread.Sleep(new TimeSpan(0, 0, 15 * mailmsg.Attachments.Count()));
                        mailmsg.Attachments.Dispose();
                    }
                }
                else
                {
                    Console.WriteLine("No orders OR email confirmation requested from: " + custcode);
                }

            }

            //Console.WriteLine("Orders: ");
            //foreach (KeyValuePair<string, List<string>> pair2 in Ship_List) {
            //    Console.Write(pair2.Key.ToString() + ":  ");
            //    foreach (string element in pair2.Value)
            //    {
            //        Console.Write(element.ToString() + "  ");
            //    }
            //    Console.WriteLine("");
            //}

        }
        
             * 
        // Send Shipping Confirmation email
        public void SendShipEmail()
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd"); //"2015-03-05";
            GetEmails();
            GetShip(date);

            foreach (KeyValuePair<string, List<string>> pair in Ship_List.ToList())
            {
                string custcode = pair.Key.ToString().Trim();

                if (Email_List.ContainsKey(custcode) && Ship_List.ContainsKey(custcode))
                {

                    string query = "select name from d_customer where customercode = '" + custcode + "'";
                    ExcoODBC database = ExcoODBC.Instance;
                    OdbcDataReader reader;
                    database.Open(Database.DECADE_MARKHAM);
                    // Get Extra charges
                    reader = database.RunQuery(query);
                    string customer_name;
                    try
                    { 
                        customer_name= reader[0].ToString().Trim();
                    }
                    catch { customer_name = ""; }

                    reader.Close();

                    Console.WriteLine("Sending email to: " + custcode);

                    // email body
                    MailMessage mailmsg = new MailMessage();

                    // Add mail to all recipients associated with customer code
                    #region Mail All with custcode
                    int count = 0;
                    if (Email_List.ContainsKey(custcode))
                    {
                        foreach (string element in Email_List[custcode].ToList())
                        {
                            if (count % 2 == 1)
                            {
                                mailmsg.To.Add(element.ToString());
                            }
                            count++;
                        }
                    }
                    #endregion
                    //mailmsg.To.Add(mailAdd);
                    MailAddress from = new MailAddress("rli@etsdies.com");
                    mailmsg.From = from;
                    mailmsg.Subject = "Shipping Confirmation (" + custcode + ")";
                    mailmsg.Body = Get_Mail_Message_Shipping(date, custcode);
                    mailmsg.IsBodyHtml = true;
                    // smtp client
                    SmtpClient client = new SmtpClient("mass-smtp.pathcom.com", 25); //Updated pathcom
                    //SmtpClient client = new SmtpClient("smtp.pathcom.com", 587);
                    //NetworkCredential credential = new NetworkCredential("rli@etsdies.com", "5Zh2Pman");
                    //client.Credentials = credential;
                    bool hasSend = false;
                    while (!hasSend)
                    {
                        try
                        {
                            client.Send(mailmsg);
                            hasSend = true;
                        }
                        catch
                        {
                            hasSend = false;
                        }
                    }
                }
                else
                {
                    Console.WriteLine("No shipping OR email confirmation requested from: " + custcode);
                }
            }


            Console.WriteLine("Email list: ");
            foreach (KeyValuePair<string, List<string>> pair2 in Email_List)
            {
                Console.Write(pair2.Key.ToString() + ":  ");
                foreach (string element in pair2.Value)
                {
                    Console.Write(element.ToString() + "  ");
                }
                Console.WriteLine("");
            }

            Console.WriteLine("Shipping List: ");
            foreach (KeyValuePair<string, List<string>> pair2 in Ship_List)
            {
                Console.Write(pair2.Key.ToString() + ":  ");
                foreach (string element in pair2.Value)
                {
                    Console.Write(element.ToString() + "  ");
                }
                Console.WriteLine("");
            }
        }*/
        //}

        public static void DeleteDirectory(string target_dir)
        {
            string[] files = Directory.GetFiles(target_dir);
            string[] dirs = Directory.GetDirectories(target_dir);

            foreach (string file in files)
            {
                File.SetAttributes(file, FileAttributes.Normal);
                File.Delete(file);
            }

            foreach (string dir in dirs)
            {
                DeleteDirectory(dir);
            }

            Directory.Delete(target_dir, false);
        }

        // Get File list (Original Tiger's file list retriever)
        public void GetFileList(string id)
        {
            bool contains_files = false;
            string[] customer_zip_requests = {"99999"}; // watch out because cannnot support more than one customer at the moment, the zip file will be overwritten everytime
            bool compress_files = false;
            foreach (string parameter in customer_zip_requests)
            {
                if (id.Contains(parameter))
                    compress_files = true;
            }

            //ExcoZip Zip = new ExcoZip();
            string temp_file_directory = @"C:\temp\drawing_files";
            string temp_zip_file = @"C:\temp\dwg_files.zip";

            // Check if compress files to zip
            if (compress_files)
            {
                if (Directory.Exists(temp_file_directory))
                    DeleteDirectory(temp_file_directory);
                if (File.Exists(temp_zip_file))
                    File.Delete(temp_zip_file);
            }

            // cReatE DIRECTOry here
            Directory.CreateDirectory(temp_file_directory);
            //Directory.CreateDirectory(temp_zip_file);

            // inspection folder
            string insFolder = "T:\\curjobs\\Email\\INS\\" + id + "\\";
            if (Directory.Exists(insFolder))
            {
                IEnumerable<string> filesIns = Directory.EnumerateFiles(insFolder, "*", SearchOption.AllDirectories);
                foreach (string file in filesIns)
                {
                    if (file.Contains(".dwg") || file.Contains(".DWG"))
                    {
                        if (compress_files)
                        {
                            File.Copy(file, temp_file_directory + "\\" + Path.GetFileName(file));
                            File.Delete(file);
                            contains_files = true;
                        }
                        else
                            fileList.Add(file);
                    }
                }
            }

            if (compress_files && contains_files)
            {
                ZipFile.CreateFromDirectory(temp_file_directory, temp_zip_file, CompressionLevel.Fastest, true);
                fileList.Add(temp_zip_file);
            }
        }

        // Get File list (Original Tiger's file list retriever)
        public void GetFileListBacker(string id)
        {
            bool contains_files = false;
            string[] customer_zip_requests = {"99999"}; // watch out because cannnot support more than one customer at the moment, the zip file will be overwritten everytime
            bool compress_files = false;
            foreach (string parameter in customer_zip_requests)
            {
                if (id.Contains(parameter))
                    compress_files = true;
            }

            //ExcoZip Zip = new ExcoZip();
            string temp_file_directory = @"C:\temp\drawing_files";
            string temp_zip_file = @"C:\temp\dwg_files.zip";

            // Check if compress files to zip
            if (compress_files)
            {
                if (Directory.Exists(temp_file_directory))
                    DeleteDirectory(temp_file_directory);
                if (File.Exists(temp_zip_file))
                    File.Delete(temp_zip_file);
            }

            // cReatE DIRECTOry here
            Directory.CreateDirectory(temp_file_directory);
            //Directory.CreateDirectory(temp_zip_file);

            // indalex folder
            string indFolder = "T:\\curjobs\\Email\\BKR\\" + id + "\\";
            if (Directory.Exists(indFolder))
            {
                IEnumerable<string> filesInd = Directory.EnumerateFiles(indFolder, "*", SearchOption.AllDirectories);
                foreach (string file in filesInd)
                {
                    if (file.Contains(".dwg") || file.Contains(".DWG"))
                    {
                        if (compress_files)
                        {
                            File.Copy(file, temp_file_directory + "\\" + Path.GetFileName(file));
                            File.Delete(file);
                            contains_files = true;
                        }
                        else
                            fileList.Add(file);
                    }
                }
            }

            if (compress_files && contains_files)
            {
                ZipFile.CreateFromDirectory(temp_file_directory, temp_zip_file, CompressionLevel.Fastest, true);
                fileList.Add(temp_zip_file);
            }
        }

    }
}