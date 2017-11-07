using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Net.Mail;
using System.Net;

namespace SendEmail
{
    public class Process
    {
        public List<Customer> custList = new List<Customer>();

        public void GetCustomerList(bool is_Sierra=false, string Specific_Cust_Code = "")
        {
            string[] lines = File.ReadAllLines(@"\\10.0.0.8\EmailAPI\Documentations\list.txt");
            foreach (string line in lines)
            {
                if (Specific_Cust_Code.Length > 0)
                {
                    if (line.Contains(Specific_Cust_Code))
                    {
                        Customer customer = new Customer();
                        int spaceIndex = line.IndexOf(' ');
                        customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                        customer.GetFileList(line.Substring(0, spaceIndex).Trim());
                        custList.Add(customer);
                        break;
                    }
                }
                else if (!is_Sierra)
                {
                    Customer customer = new Customer();
                    int spaceIndex = line.IndexOf(' ');
                    customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                    customer.GetFileList(line.Substring(0, spaceIndex).Trim());
                    custList.Add(customer);
                }
                else
                {
                    if (line.Contains("92400") || line.Contains("92500"))
                    //if (line.Contains("99999"))
                    {
                        Customer customer = new Customer();
                        int spaceIndex = line.IndexOf(' ');
                        customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                        customer.GetFileList(line.Substring(0, spaceIndex).Trim());
                        custList.Add(customer);
                    }
                }
            }
        }

        public void GetCustomerBackerList(bool is_Sierra=false)
        {
            string[] lines = File.ReadAllLines(@"\\10.0.0.8\EmailAPI\Documentations\list.txt");
            foreach (string line in lines)
            {

                if (!is_Sierra)
                {
                    Customer customer = new Customer();
                    int spaceIndex = line.IndexOf(' ');
                    customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                    customer.GetFileListBacker(line.Substring(0, spaceIndex).Trim());
                    custList.Add(customer);
                }
                else
                {
                    if (line.Contains("92400") || line.Contains("92500"))
                    //if (line.Contains("99999"))
                    {
                        Customer customer = new Customer();
                        int spaceIndex = line.IndexOf(' ');
                        customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                        customer.GetFileListBacker(line.Substring(0, spaceIndex).Trim());
                        custList.Add(customer);
                    }
                }
            }
        }

        public void GetOrderList()
        {
            string[] lines = File.ReadAllLines(@"\\10.0.0.8\EmailAPI\Documentations\list.txt");
            foreach (string line in lines)
            {
                Customer customer = new Customer();
                int spaceIndex = line.IndexOf(' ');
                customer.mailAdd = line.Substring(spaceIndex + 1, line.Length - spaceIndex - 1).Trim();
                customer.GetFileList(line.Substring(0, spaceIndex).Trim());
                custList.Add(customer);
            }
        }

        public string mailAdd = string.Empty;
        int try_count = 5;

        public string DeleteFile(Customer cust)
        {
            string return_str = "";

            foreach (string file in cust.fileList)
            {
                int count = 0;

                while (File.Exists(file) && count < try_count)
                {
                    try
                    {
                        return_str += "Deleting: " + file + Environment.NewLine;
                        File.Delete(file);
                    }
                    catch
                    {
                        return_str += "ERROR DELETING FILE: " + file + Environment.NewLine;

                        // email body
                        MailMessage mailmsg = new MailMessage();
                        mailmsg.To.Add("RLI@ETSDIES.COM");
                        mailmsg.To.Add("GLUO@ETSDIES.COM");
                        MailAddress from = new MailAddress("ipasmenko@etsdies.com");
                        mailmsg.From = from;
                        mailmsg.Subject = "AUTO EMAIL PROGRAM ERROR - CANNOT DELETE FILE";
                        mailmsg.Body = file;
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
                                client.Send(mailmsg);
                                hasSend = true;
                            }
                            catch
                            {
                                hasSend = false;
                            }
                        }
                    }
                    count++;
                    //if (File.Exists(file))
                        //Thread.Sleep(new TimeSpan(0, 0, 10));
                }
            }
            return return_str == "" ? "No files found" + Environment.NewLine : return_str;
        }

        public void SendEmail()
        {

        }
    }
}
