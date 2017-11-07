using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Windows.Forms;

namespace SendEmail
{
    public partial class MainDialog : Form
    {
        // The Working thread.
        // This thread intends to process ff files.
        // Output will be written into richEditBox.
        public Thread thread;
        public bool isRunningThread = false;
        // The process main class
        public Process process = new Process();
        public Process Order_process = new Process();
        public Process Ship_process = new Process();
        // wait time in minutes for processing target file
        public double waitTime = 25.0;

        // Default constructor. It initializes dialog, enables
        // start button and disables stop button.
        public MainDialog()
        {
            InitializeComponent();
            // enable start button
            buttonStart.Enabled = true; 
            // disable stop button
            buttonStop.Enabled = false;
            // add build time
            Text += " " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString();
        }


        // Start button click event handler.
        // It contains these features:
        // 1. disable start button
        // 2. enable stop button
        // 3. start work thread and make sure it works
        // @param[in] sender event sende
        // @param[in] e event argument
        internal void buttonStart_Click(object sender, EventArgs e)
        {
            // disable start
            buttonStart.Enabled = false;
            // enable stop
            buttonStop.Enabled = true;
            // start thread
            isRunningThread = true;
            thread = new Thread(Run);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }   

        // Stop button click event handler.
        // It contains these features:
        // 1. enable start button
        // 2. disable stop button
        // 3. request to terminate the work thread
        // @param[in] sender event sender
        // @param[in] e event argument
        internal void buttonStop_Click(object sender, EventArgs e)
        {
            //
            
            // request the thread to stop
            isRunningThread = false;
            // enable start
            buttonStart.Enabled = true;
            // disable stop
            buttonStop.Enabled = false;
        }
        // Append text to the richTextBox. It enables
        // communication between work thread and dialog thread.
        // @param[in] value text to be appended
        internal void AppendTextBox(string value)
        {
            if (InvokeRequired)
            {
                Invoke(new Action<string>(AppendTextBox), new object[] { value });
                return;
            }
            if (textBoxLog.Text.Length > 400000)
            {
                ClearTextBoxContent();
            }
            textBoxLog.AppendText(value);
            textBoxLog.SelectionStart = textBoxLog.Text.Length;
            textBoxLog.ScrollToCaret();
            textBoxLog.Refresh();
        }

        // Clear text content from richTextBox. It enables
        // communication between work thread and dialog thread.
        internal void ClearTextBoxContent()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(ClearTextBoxContent));
                return;
            }
            textBoxLog.Clear();
        }

        // Create Processor object and implement loop.
        // @note This is the main function of the working
        // thread.
        internal void Run()
        {
            AppendTextBox("Robin's edited version 1.1.25: 01/03/2017" + Environment.NewLine);
            AppendTextBox("thread start at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            while (isRunningThread)
            {
                try
                {

                    //if (true)
                    if (DateTime.Now.Hour == 3)
                    {
                        AppendTextBox("Hour = >22");
                        AppendTextBox("get customer list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        process.custList.Clear();
                        process.GetCustomerList(false);
                        AppendTextBox("done" + Environment.NewLine);
                        foreach (Customer cust in process.custList)
                        {
                            if (cust.fileList.Count > 0)
                            {
                                AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                                cust.SendEmail();
                                AppendTextBox("done" + Environment.NewLine);
                            }
                            Thread.Sleep(new TimeSpan(0, 1, 0));
                        }
                        //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

                        foreach (Customer cust in process.custList)
                        {
                            AppendTextBox(process.DeleteFile(cust));
                        }
                        
                        AppendTextBox("done" + Environment.NewLine);
                        //AppendTextBox("sleep 8 hours" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(1, 0, 0));
                        //AppendTextBox("wait until 11pm" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);
                    }



                    //if (true)
                    if (DateTime.Now.Hour == 21)
                    {
                        AppendTextBox("Hour = 21");
                        AppendTextBox("get customer list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        process.custList.Clear();
                        process.GetCustomerBackerList(false);
                        AppendTextBox("done" + Environment.NewLine);
                        foreach (Customer cust in process.custList)
                        {
                            if (cust.fileList.Count > 0)
                            {
                                AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                                cust.SendEmail("Backer(s)");
                                AppendTextBox("done" + Environment.NewLine);
                            }
                            Thread.Sleep(new TimeSpan(0, 1, 0));
                        }
                        //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

                        //AppendTextBox(process.DeleteFile());

                        foreach (Customer cust in process.custList)
                        {
                            AppendTextBox(process.DeleteFile(cust));
                        }

                        Thread.Sleep(new TimeSpan(0, 30, 0));
                        AppendTextBox("done" + Environment.NewLine);
                        //AppendTextBox("sleep 8 hours" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(0, 30, 0));
                        //AppendTextBox("wait until 11pm" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);
                    }
                    /*
                    else if (DateTime.Now.Hour == 20) //Robin added to handle shipping invoices to email
                    //else if (true)
                    {
                        AppendTextBox("get order list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        Order_process.GetOrderList();
                        AppendTextBox("done" + Environment.NewLine);
                        AppendTextBox("sending email at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

                        Order_process.custList[0].SendOrderEmail(); // Send only once;; processed differently
                        AppendTextBox("order: sleep 2 hours" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(1, 0, 0));
                        //Thread.Sleep(new TimeSpan(0, 1, 0));
                    }
                    //else if (DateTime.Now.Hour == 08)
                    else if (true)
                     * 
                    {
                        AppendTextBox("get ship list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        Ship_process.GetOrderList();
                        AppendTextBox("done" + Environment.NewLine);
                        AppendTextBox("sending email at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        Ship_process.custList[0].SendShipEmail(); // Send only once;; processed differently
                        AppendTextBox("ship: sleep 11 hours" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(1, 0, 0));
                    }*/
                    else if (DateTime.Now.Hour < 18 && DateTime.Now.Hour > 6)//Sierra every hour only
                    {

                        Thread.Sleep(new TimeSpan(0, 0, 50));
                        //AppendTextBox("Sleeping for 5 minutes... " + Environment.NewLine);
                        AppendTextBox("get sierra list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        process.custList.Clear();
                        process.GetCustomerList(true);
                        AppendTextBox("done" + Environment.NewLine);
                        foreach (Customer cust in process.custList)
                        {
                            if (cust.fileList.Count > 0)
                            {
                                AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                                cust.SendEmail();
                                AppendTextBox("done" + Environment.NewLine);
                            }
                        }
                        Thread.Sleep(new TimeSpan(0, 30, 0));
                        foreach (Customer cust in process.custList)
                        {
                            AppendTextBox(process.DeleteFile(cust));
                        }
                        //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        //AppendTextBox(process.DeleteFile());
                        AppendTextBox("done" + Environment.NewLine);
                        //AppendTextBox("sleep 8 hours" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(0, 30, 0));
                        //AppendTextBox("wait until 11pm" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);

                    }
                    else
                    {
                        Thread.Sleep(new TimeSpan(1, 0, 0));
                    }

                }
                catch (Exception e)
                {
                    AppendTextBox(e.Message + Environment.NewLine);
                }
            }
            AppendTextBox("thread stop at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AppendTextBox("get customer list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            process.custList.Clear();
            process.GetCustomerList(false);
            AppendTextBox("done" + Environment.NewLine);
            foreach (Customer cust in process.custList)
            {
                if (cust.fileList.Count > 0)
                {
                    AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                    //cust.SendEmail();
                    AppendTextBox("done" + Environment.NewLine);
                }
            }
            //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

            Thread.Sleep(new TimeSpan(0, 30, 0));
            foreach (Customer cust in process.custList)
            {
                AppendTextBox(process.DeleteFile(cust));
            }

            AppendTextBox("done" + Environment.NewLine);
            //AppendTextBox("sleep 8 hours" + Environment.NewLine);
            //Thread.Sleep(new TimeSpan(1, 0, 0));
            //AppendTextBox("wait until 11pm" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);

            AppendTextBox("get customer list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            process.custList.Clear();
            process.GetCustomerBackerList(false);
            AppendTextBox("done" + Environment.NewLine);
            foreach (Customer cust in process.custList)
            {
                if (cust.fileList.Count > 0)
                {
                    AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                    //cust.SendEmail("Backer(s)");
                    //AppendTextBox("done" + Environment.NewLine);
                }
            }
            //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

            Thread.Sleep(new TimeSpan(0, 30, 0));
            foreach (Customer cust in process.custList)
            {
                AppendTextBox(process.DeleteFile(cust));
            }
            AppendTextBox("done" + Environment.NewLine);
            //AppendTextBox("sleep 8 hours" + Environment.NewLine);
            //AppendTextBox("wait until 11pm" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
        }

        // Manual send
        private void button3_Click(object sender, EventArgs e)
        {
            AppendTextBox("get customer list at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            process.custList.Clear();
            process.GetCustomerList(false, textBox1.Text);
            AppendTextBox("done" + Environment.NewLine);
            foreach (Customer cust in process.custList)
            {
                if (cust.fileList.Count > 0)
                {
                    AppendTextBox("send email to " + cust.mailAdd + " at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                    cust.SendEmail();
                    AppendTextBox("done" + Environment.NewLine);
                }
            }
            //AppendTextBox("delete files at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);

            Thread.Sleep(new TimeSpan(0, 30, 0));
            foreach (Customer cust in process.custList)
            {
                AppendTextBox(process.DeleteFile(cust));
            }
            AppendTextBox("done" + Environment.NewLine);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
