using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;
using YTD_Updater;

namespace temp
{
    public class Process
    {
        public void Run()
        {

            //bool generate_files = true;
            Generate g = new Generate();
            g.ShowDialog();

            //Updater g = new Updater();
            //g.Run();
            //g.Update(15, 3);
            //g.Update(5);

        }
    }
}
