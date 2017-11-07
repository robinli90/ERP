using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace OrdersReport
{
    public partial class MainDialog : Form
    {
        public MainDialog()
        {
            InitializeComponent();
            // enable start button
            buttonStart.Enabled = true;
            // disable stop button
            buttonStop.Enabled = false;
            // add build time
            Text += " " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            // disable start
            buttonStart.Enabled = false;
            // enable stop
            buttonStop.Enabled = true;
            Thread thread = new Thread(Run);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
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
            if (textBoxLog.Text.Length > 4000)
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
        // @note This is the main function of the working thread.
        // will work at 10pm of every second day of a month
        internal void Run()
        {
            AppendTextBox("thread start at " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + Environment.NewLine);
            try
            {
                //if (DateTime.Now.Day == 2 && DateTime.Now.Hour == 22)
                {
                    AppendTextBox("generating orders report at " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + Environment.NewLine);
                    // The process main class
                    Process process = new Process();
                    process.Run(checkBoxNeedSurcharge.Checked);
                    AppendTextBox("done" + Environment.NewLine);
                    //AppendTextBox("sending email to " + process.receiver + " at " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + Environment.NewLine);
                    //process.SendFileViaEmail();
                    //AppendTextBox("done" + Environment.NewLine);
                    AppendTextBox("sleep" + Environment.NewLine + Environment.NewLine + Environment.NewLine);
                    //Thread.Sleep(new TimeSpan(2, 0, 0));
                }
                //else
                {
                    //Thread.Sleep(new TimeSpan(1, 0, 0));
                }
            }
            catch (Exception e)
            {
                AppendTextBox(e.Message + Environment.NewLine);
            }
            AppendTextBox("thread stop at " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + Environment.NewLine);
        }
    }
}













