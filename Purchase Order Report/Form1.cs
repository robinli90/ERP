using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;

namespace Purchase_Order_Report
{
    public partial class Form1 : Form
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
        
        public Form1()
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

        private void buttonStop_Click(object sender, EventArgs e)
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
            if (richTextBoxLog.Text.Length > 4000)
            {
                ClearLogContent();
            }
            richTextBoxLog.AppendText(value);
            richTextBoxLog.SelectionStart = richTextBoxLog.Text.Length;
            richTextBoxLog.ScrollToCaret();
            richTextBoxLog.Refresh();
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
            richTextBoxLog.Clear();
        }

        // Create Processor object and implement loop.
        // @note This is the main function of the working
        // thread.
        internal void Run()
        {
            AppendLog("thread start" + Environment.NewLine);
            while (isRunningThread)
            {
                try
                {
                    Process process = new Process();
                    //process.Run(monthCalendarStartDate.sel
                }
                catch (Exception e)
                {
                    AppendLog(e.Message + Environment.NewLine);
                }
            }
            AppendLog("thread stop" + Environment.NewLine);
        }
    }
}