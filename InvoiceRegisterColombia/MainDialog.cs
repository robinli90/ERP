using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using System.Diagnostics;

namespace InvoiceRegisterColombia
{
    public partial class MainDialog : Form
    {
        // Thread start/stop flag.
        // @b true: default. thread runs normally
        // @b false: request a thread to stop
        internal bool isRunningThread = true;
        // The Working thread.
        // This thread intends to process ff files.
        // Output will be written into richEditBox.
        internal Thread thread;
        // The process main class
        internal Process process = new Process();
        // wait time in minutes for processing target file
        internal double waitTime = 25.0;

        public MainDialog()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
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
            // request the thread to stop
            isRunningThread = false;
            // enable start
            buttonStart.Enabled = true;
            // disable stop
            buttonStop.Enabled = false;
        }

        // Append text to the richTextLog. It enables
        // communication between work thread and dialog thread.
        // @param[in] value text to be appended
        internal void AppendLog(string value)
        {
            if (InvokeRequired)
            {
                Invoke(new Action<string>(AppendLog), new object[] { value });
                return;
            }
            if (richTextLog.Text.Length > 4000)
            {
                ClearLogContent();
            }
            richTextLog.AppendText(value);
            richTextLog.SelectionStart = richTextLog.Text.Length;
            richTextLog.ScrollToCaret();
            richTextLog.Refresh();
        }

        // Clear text content from richTextLog. It enables
        // communication between work thread and dialog thread.
        internal void ClearLogContent()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(ClearLogContent));
                return;
            }
            richTextLog.Clear();
        }

        // Create Processor object and implement loop.
        // @note This is the main function of the working
        // thread.
        internal void Run()
        {
            AppendLog("V4 thread start" + Environment.NewLine);
            while (isRunningThread)
            {
                try
                {
                    //if (true)
                    if (DateTime.Now.DayOfWeek != DayOfWeek.Saturday && DateTime.Now.DayOfWeek != DayOfWeek.Sunday && DateTime.Now.Hour == 13)
                    {
                        AppendLog("V2Robin 03/05/16" + Environment.NewLine);
                        AppendLog("start process at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        Process process = new Process();
                        process.Run();
                        AppendLog("send email at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        process.SendEmail();
                        // delete file
                        AppendLog("done at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        //AppendLog("sleep 2 hours - V1" + Environment.NewLine);
                        Thread.Sleep(new TimeSpan(2, 0, 0));
                        AppendLog("wait until next 1pm" + Environment.NewLine);
                    }
                    else
                    {
                        Thread.Sleep(new TimeSpan(0, 0, 1));
                    }
                }
                catch (Exception e)
                {
                    AppendLog(e.Message + Environment.NewLine);
                }
            }
            AppendLog("thread stop" + Environment.NewLine);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                AppendLog("V2Robin 03/05/16" + Environment.NewLine);
                AppendLog("start process at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                Process process = new Process();
                process.Run();
                AppendLog("send email at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                process.SendEmail();
                // delete file
                AppendLog("done at " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                //AppendLog("sleep 2 hours - V1" + Environment.NewLine);
                Thread.Sleep(new TimeSpan(2, 0, 0));
                AppendLog("wait until next 1pm" + Environment.NewLine);
            }
            catch (Exception ez)
            {
                AppendLog(ez.Message + Environment.NewLine);
            }
        }
    }
}
