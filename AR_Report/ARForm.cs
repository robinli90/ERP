using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AR_Report
{
    public partial class ARForm : Form
    {
        public ARForm()
        {
            InitializeComponent();
            monthCalendar.DateSelected += new DateRangeEventHandler(monthCalendar_DateSelected);
            monthCalendar.SelectionStart = DateTime.Now;
        }

        private DateTime now = new DateTime();

        private void buttonStart_Click(object sender, EventArgs e)
        {
            Process process = new Process();
            process.Run(now);
            
        }

        private void monthCalendar_DateSelected(Object sender, DateRangeEventArgs e)
        {
            now = e.Start;
            buttonStart.Enabled = true;
        }
    }
}
