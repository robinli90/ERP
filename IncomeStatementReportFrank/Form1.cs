using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace IncomeStatementReportFrank
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void buttonRun_Click(object sender, EventArgs e)
        {
            int fiscalYear = Convert.ToInt32(textBoxYear.Text);
            int fiscalMonth = Convert.ToInt32(textBoxPeriod.Text);
            Process process = new Process(fiscalMonth,fiscalYear);
            process.Run();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //textBoxYear.Text = (DateTime.Now.AddYears(1)).Year.ToString().Substring(2);
            //textBoxPeriod.Text = "01";
            //buttonRun.PerformClick();
        }

        private void textBoxYear_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBoxPeriod_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
