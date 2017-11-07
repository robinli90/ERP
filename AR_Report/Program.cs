using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace AR_Report
{
    class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new ARForm());
        }
    }
}
