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
    }
}
