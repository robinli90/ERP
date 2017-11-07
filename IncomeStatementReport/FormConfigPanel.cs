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
using ExcoUtility;

namespace IncomeStatementReport
{
    public partial class FormConfigPanel : Form
    {
        public FormConfigPanel()
        {
            InitializeComponent();
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
            if (richTextBoxLog.Text.Length > 8000)
            {
                ClearTextBoxContent();
            }
            richTextBoxLog.AppendText(value);
            richTextBoxLog.SelectionStart = richTextBoxLog.Text.Length;
            richTextBoxLog.ScrollToCaret();
            richTextBoxLog.Refresh();
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
            richTextBoxLog.Clear();
        }

        // enable go button
        internal void EnableButtonGo()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(EnableButtonGo));
                return;
            }
            buttonRun.Enabled = true;
        }

        internal void buttonRun_Click(object sender, EventArgs e)
        {
            buttonRun.Enabled = false;
            Thread thread = new Thread(Run);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }

        // @note This is the main function of the working
        // thread.
        void Run()
        {
            //bool test=false;
            bool test=false;
            AppendTextBox("thread start" + Environment.NewLine);
            try
            {
                if (!test)
                {
                    int fiscalYear = Convert.ToInt32(textBoxYear.Text);
                    int fiscalMonth = Convert.ToInt32(textBoxPeriod.Text);
                    Process process = new Process(fiscalYear, fiscalMonth);
                    // create excel object
                    ExcelWriter excelWriter = new ExcelWriter(process);
                    excelWriter.FillSheets();
                    // write to file
                    string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx");
                    //string path = "C:\\Sales Report\\Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx";
                    File.Delete(path);
                    excelWriter.OutputToFile(path);
                    System.Diagnostics.Process.Start(path);
                }
                else
                {
                    int fiscalYear = Convert.ToInt32(textBoxYear.Text);
                    int fiscalMonth = 10;
                    for (int i = 0; i < 12; i++)
                    {
                        if (fiscalMonth > 12) fiscalMonth = 1;
                        Process process = new Process((fiscalMonth > 9 ? fiscalYear - 1 : fiscalYear), fiscalMonth);
                        // create excel object
                        ExcelWriter excelWriter = new ExcelWriter(process);
                        excelWriter.FillSheets();
                        // write to file
                        string path = "";
                        if (!test)
                        {
                            path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx");
                        }
                        else
                        {
                            path = "C:\\Sales Report\\Income Statement Report at " + process.fiscalMonth + "-" + process.fiscalYear + ".xlsx";
                        }
                        File.Delete(path);
                        excelWriter.OutputToFile(path);
                        //System.Diagnostics.Process.Start(path);
                        fiscalMonth++;
                    }
                }










                //int year = Convert.ToInt32(textBoxYear.Text);
                //int period = Convert.ToInt32(textBoxPeriod.Text);
                //process.yr = year;
                //process.tp = period;
                //ExcoCalendar calendar = new ExcoCalendar(year, period, true, 1);
                //process.markham = new Plant(calendar, 1, checkBoxCAD.Checked);
                //AppendTextBox("Procssing Markham done" + Environment.NewLine);
                //calendar = new ExcoCalendar(year, period, true, 3);
                //process.michigan = new Plant(calendar, 3, checkBoxCAD.Checked);
                //AppendTextBox("Procssing Michigan done" + Environment.NewLine);
                //calendar = new ExcoCalendar(year, period, true, 5);
                //process.texas = new Plant(calendar, 5, checkBoxCAD.Checked);
                //AppendTextBox("Procssing Texas done" + Environment.NewLine);
                //calendar = new ExcoCalendar(calendar.GetCalendarYear(), calendar.GetCalendarMonth(), false, 4);
                //process.colombia = new Plant(calendar, 4, checkBoxCAD.Checked);
                //AppendTextBox("Procssing Colombia done" + Environment.NewLine);
                //// create excel object
                //Excel.Application excel = new Excel.Application();
                //object misValue = System.Reflection.Missing.Value;
                //Excel.Workbook book = excel.Workbooks.Add(misValue);
                //Excel.Worksheet micSheet = book.Worksheets[1];
                //micSheet.Name = "Michigan at " + process.tp + "-" + process.yr;
                //Excel.Worksheet texSheet = book.Worksheets[2];
                //texSheet.Name = "Texas at " + process.tp + "-" + process.yr;
                //Excel.Worksheet colSheet = book.Worksheets[3];
                //colSheet.Name = "Colombia at " + process.tp + "-" + process.yr;
                //Excel.Worksheet marSheet = book.Worksheets.Add();
                //marSheet.Name = "Markham at " + process.tp + "-" + process.yr;
                //// write to excel object
                //process.WritePlant(marSheet, process.markham);
                //AppendTextBox("Output Markham done" + Environment.NewLine);
                //process.WritePlant(micSheet, process.michigan);
                //AppendTextBox("Output Michigan done" + Environment.NewLine); 
                //process.WritePlant(texSheet, process.texas);
                //AppendTextBox("Output Texas done" + Environment.NewLine); 
                //process.WritePlant(colSheet, process.colombia);
                //AppendTextBox("Output Colombia done" + Environment.NewLine);
                //// write to file
                //string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Income Statement Report at " + process.tp + "-" + process.yr + ".xlsx");
                //File.Delete(path);
                //book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
                //excel.Quit();
                //System.Diagnostics.Process.Start(path);
            }
            catch (Exception e)
            {
                AppendTextBox(e.Message + Environment.NewLine);
            }
            AppendTextBox("Output done" + Environment.NewLine);
            AppendTextBox("thread stop" + Environment.NewLine + Environment.NewLine + Environment.NewLine + Environment.NewLine);
            EnableButtonGo();
        }
    }
}