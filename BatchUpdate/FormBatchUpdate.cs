using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Diagnostics;
using System.Data.Odbc;
using ExcoUtility;

namespace BatchUpdate
{
    public partial class FormBatchUpdate : Form
    {
        internal Thread thread;
        // all runtimes
        public List<RunTime> allList = new List<RunTime>();
        // indexes of exception records
        public List<int> exceptionIndexList = new List<int>();
        // indexes of each runtime
        public List<int> runtimeIndexList = new List<int>();
        // if display exception in grid view
        public bool isDisplayException = false;
        // if using shop order number to search
        public bool isSearchBySO = true;
        // database
        public Database database = Database.CMSDAT;
        // process object
        public Process process;

        public FormBatchUpdate()
        {
            InitializeComponent();
#if DEBUG
            Height = 1850;
            gridViewRuntimes.Height = 1600;
#endif
            Text += DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            // set default to show all records
            buttonShowException.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonLoad.Enabled = true;
            buttonSubmit.Enabled = false;
            textBoxPieceNum.Enabled = false;
            buttonGo.Enabled = false;
            radioButtonSO.Enabled = false;
            radioButtonWO.Enabled = false;
            // set event handler
            gridViewRuntimes.CellValueChanged += new DataGridViewCellEventHandler(GridViewValueChanged);
            // speed up
            gridViewRuntimes.DoubleBuffered(true);
        }

        internal void AppendTextBox(string value)
        {
            if (InvokeRequired)
            {
                Invoke(new Action<string>(AppendTextBox), new object[] { value });
                return;
            }
            if (richTextBox.Text.Length > 4000)
            {
                ClearTextBoxContent();
            }
            richTextBox.AppendText(value + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
        }

        internal string GetTextBoxContent()
        {
            return (string)richTextBox.Invoke(new Func<string>(() => richTextBox.Text));
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
            richTextBox.Clear();
        }

        // enable submit button
        internal void EnableSubmitButton()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(EnableSubmitButton));
                return;
            }
            buttonSubmit.Enabled = true;
        }

        // clear grid view content
        internal void ClearGridView()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(ClearGridView));
                return;
            }
            gridViewRuntimes.Rows.Clear();
            allList.Clear();
            exceptionIndexList.Clear();
            buttonSubmit.Enabled = false;
            buttonShowException.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonLoad.Enabled = true;
            // disable search
            textBoxPieceNum.Enabled = false;
            buttonGo.Enabled = false;
            radioButtonSO.Enabled = false;
            radioButtonWO.Enabled = false;
        }

        // clear grid view content on load
        internal void ClearGridViewOnLoad()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(ClearGridViewOnLoad));
                return;
            }
            gridViewRuntimes.Rows.Clear();
            allList.Clear();
            exceptionIndexList.Clear();
            buttonSubmit.Enabled = false;
            buttonShowException.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonLoad.Enabled = false;
            // disable search
            textBoxPieceNum.Enabled = false;
            buttonGo.Enabled = false;
            radioButtonSO.Enabled = false;
            radioButtonWO.Enabled = false;
        }


        private void buttonLoad_Click(object sender, EventArgs e)
        {
            // disable start and submit
            buttonLoad.Enabled = false;
            dateTimePicker.Enabled = false;
            buttonSubmit.Enabled = false;
            // start thread
            thread = new Thread(LoadRecords);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }

        private void LoadRecords()
        {
            AppendTextBox("thread start");
            process = new Process(database, dateTimePicker.Value);
            ClearGridViewOnLoad();
            try
            {
                // build predicted runtime dictionary
                AppendTextBox("trying to build predicted runtime dictionary at " + DateTime.Now.ToLongTimeString());
                process.BuildPredictedRuntimeDictionary();
                AppendTextBox("done");
                // build scrap dictionary
                AppendTextBox("trying to build scrap dictionary at " + DateTime.Now.ToLongTimeString());
                process.BuildScrapDictionary();
                AppendTextBox("done");
                // build spark and edm dictionary
                AppendTextBox("trying to build spark and edm dictionary at " + DateTime.Now.ToLongTimeString());
                process.BuildRuntimeDictionary();
                AppendTextBox("done");
                // get predefined sequence template for current orders
                AppendTextBox("trying to get predefined sequence template for current orders at " + DateTime.Now.ToLongTimeString());
                process.GetSequenceTemplateCurrent();
                AppendTextBox("done");
                // get predefined sequence template for history orders
                AppendTextBox("trying to get predefined sequence template for history orders at " + DateTime.Now.ToLongTimeString());
                process.GetSequenceTemplateHistory();
                AppendTextBox("done");
                // get all tasks
                AppendTextBox("trying to get all tasks at " + DateTime.Now.ToLongTimeString());
                process.GetAllTasks();
                AppendTextBox("done");
                // process piece
                for (int i = 0; i < process.pieceList.Count; i++)
                {
                    Piece piece = process.pieceList[i];
                    try
                    {
                        piece.GetInfo(database, process.seqTemplateMap, process.scrapMap, process.sparkMap, process.wireMap, dateTimePicker.Value);
                        if (0 == piece.seqList.Count)
                        {
                            process.pieceList.RemoveAt(i);
                            i--;
                        }
                        AppendTextBox("Done processing " + piece.wo + " " + piece.part);
                    }
                    catch (Exception e)
                    {
                        throw new Exception(e.Message + " at " + piece.wo);
                    }
                }
                // process die
                AppendTextBox("trying to process all dies at " + DateTime.Now.ToLongTimeString());
                process.ProcessDie();
                AppendTextBox("done");
                // adjust data structure
                AppendTextBox("adjusting data structure at " + DateTime.Now.ToLongTimeString());
                process.AjustRecords();
                AppendTextBox("done");
                // build assembly finish map
                AppendTextBox("building assembly finish map at " + DateTime.Now.ToLongTimeString());
                process.BuildAssemblyFinishDictionary();
                AppendTextBox("done");
                // build latest decade tasks map
                AppendTextBox("building latest decade tasks map at " + DateTime.Now.ToLongTimeString());
                process.BuildLatestDecadeActivity();
                AppendTextBox("done");
                // calculate run time
                AppendTextBox("calculating run time at " + DateTime.Now.ToLongTimeString());
                foreach (Die die in process.dieMap.Values)
                {
                    // calculate overall run time of 20/30 for an order, then distribute into each sub piece
                    die.GetEvenTime(20, process.seqTemplateMap, process.seq20HJOBHMap, database);
                    die.GetEvenTime(30, process.seqTemplateMap, process.seq30HJOBHMap, database);
                    foreach (Piece piece in die.pieceList)
                    {
                        foreach (Seq seq in piece.seqList)
                        {
                            foreach (RunTime runtime in seq.runtimeList)
                            {
                                runtime.CalcualteRunTime(database, dateTimePicker.Value);
                            }
                        }
                    }
                }
                AppendTextBox("done");
                // mark completed pieces
                AppendTextBox("marking completed pieces at " + DateTime.Now.ToLongTimeString());
                process.MarkCompletedPieces();
                AppendTextBox("done");
                // complete finished pieces
                AppendTextBox("completing finished pieces at " + DateTime.Now.ToLongTimeString());
                process.CompleteFinishedPieces();
                AppendTextBox("done");
                // back flush previous sequences if they are empty
                AppendTextBox("back flushing pieces at " + DateTime.Now.ToLongTimeString());
                process.BackFlush(dateTimePicker.Value);
                AppendTextBox("done");
                // fill sequences with std time if runtime fails
                AppendTextBox("filling with standard time at " + DateTime.Now.ToLongTimeString());
                process.FillWithStdTime();
                AppendTextBox("done");
                // write to grid view
                AppendTextBox("writing to grid view at " + DateTime.Now.ToLongTimeString());
                // fill runtime list
                process.pieceList.Sort(CompareWO);
                foreach (Piece piece in process.pieceList)
                {
                    foreach (Seq seq in piece.seqList)
                    {
                        foreach (RunTime runtime in seq.runtimeList)
                        {
                            runtime.actualTime = runtime.runTime;
                            allList.Add(runtime);
                        }
                    }
                }
                for (int i = 0; i < allList.Count; i++)
                {
                    if (allList[i].IsException())
                    {
                        exceptionIndexList.Add(i);
                    }
                }
                // display data
                if (isDisplayException)
                {
                    DisplayException();
                }
                else
                {
                    DisplayAll();
                }
                AppendTextBox("done");
            }
            catch (Exception e)
            {
                AppendTextBox(e.Message + Environment.NewLine);
            }
            AppendTextBox("thread stop");
        }

        private void buttonSubmit_Click(object sender, EventArgs e)
        {
            buttonSubmit.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonShowException.Enabled = false;
            // start thread
            thread = new Thread(SubmitRecords);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }

        // submit modified records into solarsoft
        private void SubmitRecords()
        {
            AppendTextBox("thread start");
            try
            {
                // complete finished pieces
                AppendTextBox("completing finished pieces at " + DateTime.Now.ToLongTimeString());
                process.CompleteFinishedPieces();
                AppendTextBox("done");
                // generate batch cache
                AppendTextBox("generating batch cache content at " + DateTime.Now.ToLongTimeString());
                process.GenerateBatchCache(allList);
                AppendTextBox("done");
                // write to batch file
                AppendTextBox("writing to batch file at " + DateTime.Now.ToLongTimeString());
                process.WriteToBatchFile();
                AppendTextBox("done");
                // request solarsoft to process batch file
                AppendTextBox("requesting solarsoft to process batch file at " + DateTime.Now.ToLongTimeString());
                process.RequestProcessBatchFile();
                // check if file is ok
                int i = 10;
                while (i > 0 && File.Exists(process.batchFilePath))
                {
                    Thread.Sleep(1000);
                    i--;
                }
                if (i <= 0)
                {
                    throw new Exception("Failed to run batchupdate");
                }
                AppendTextBox("done");
                // mark task complete
                AppendTextBox("marking tasks as completed at " + DateTime.Now.ToLongTimeString());
                foreach (RunTime runtime in allList)
                {
                    for (int j = 0; j < runtime.taskList.Count; j++)
                    {
                        runtime.taskList[j].MarkComplete(database);
                        AppendTextBox(runtime.woNum + " " + runtime.taskList[j].taskCode + runtime.taskList[j].taskTime.ToString("yyyy-MM-dd HH:mm:ss"));
                    }
                }
                AppendTextBox("done");
                // move batch file to archive
                AppendTextBox("moving batch file to archive folder at " + DateTime.Now.ToLongTimeString());
                process.MoveToArchive();
                AppendTextBox("done");
                // clear grid view content
                AppendTextBox("clear grid view content at " + DateTime.Now.ToLongTimeString());
                ClearGridView();
                AppendTextBox("done");
            }
            catch (Exception e)
            {
                AppendTextBox(e.Message + Environment.NewLine);
            }
            AppendTextBox("thread stop");
            EnableLoadButton();
        }

        private void EnableLoadButton()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(EnableLoadButton));
                return;
            }
            buttonLoad.Enabled = true;
            dateTimePicker.Enabled = true;
        }

        // display all records in grid view
        private void DisplayAll()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(DisplayAll));
                return;
            }
            runtimeIndexList.Clear();
            gridViewRuntimes.Rows.Clear();
            string wo = string.Empty;
            int decadeTaskCount = 0;
            for (int i = 0; i < allList.Count; i++)
            {
                RunTime runtime = allList[i];
                string[] line = new string[12];
                if (0 != runtime.woNum.CompareTo(wo))
                {
                    if (wo.Length > 0)
                    {
                        runtimeIndexList.Add(-1);
                        gridViewRuntimes.Rows.Add(new string[10]);
                    }
                    wo = runtime.woNum;
                    line[0] = runtime.soNum.ToString();
                    line[1] = runtime.woNum;
                    line[2] = runtime.part;
                    decadeTaskCount = 0;
                }
                line[3] = runtime.seqNum.ToString();
                if (runtime.startTime.Year > 1)
                {
                    line[4] = runtime.startTime.ToString();
                }
                if (runtime.stopTime.Year > 1)
                {
                    line[5] = runtime.stopTime.ToString();
                }
                if (runtime.runTime > 0.0001 || runtime.startTime.Year > 1)
                {
                    line[6] = runtime.runTime.ToString("F2");
                }
                line[7] = runtime.stdTime.ToString("F2");
                if (runtime.hasSolarsoftTime)
                {
                    line[8] = runtime.slsTime.ToString("F2");
                }
                else
                {
                    line[8] = "----";
                }
                if (runtime.actualTime > 0.00001 || runtime.taskList.Count > 0)
                {
                    line[9] = runtime.actualTime.ToString("F2");
                }
                if (runtime.slsDate.Year > 1)
                {
                    line[10] = runtime.slsDate.ToString("yyyy-MM-dd");
                }
                if (decadeTaskCount < 4)
                {
                    if (process.decadeTasks.ContainsKey(runtime.soNum))
                    {
                        if (process.decadeTasks[runtime.soNum].Count > decadeTaskCount)
                        {
                            line[11] = process.decadeTasks[runtime.soNum][decadeTaskCount];
                            decadeTaskCount++;
                            if (process.decadeTasks[runtime.soNum].Count == decadeTaskCount)
                            {
                                decadeTaskCount = 99;
                            }
                        }
                    }
                }
                runtimeIndexList.Add(i);
                gridViewRuntimes.Rows.Add(line);
                // mark scarp as red
                if (process.scrapMap.ContainsKey(wo))
                {
                    gridViewRuntimes.Rows[gridViewRuntimes.Rows.Count - 1].Cells[1].Style.BackColor = Color.Red;
                }
                // adjust exception style
                if (exceptionIndexList.Contains(i))
                {
                    for (int j = 0; j < 10; j++)
                    {
                        gridViewRuntimes.Rows[gridViewRuntimes.Rows.Count - 1].Cells[j].Style.BackColor = Color.Aqua;
                    }
                }
            }
            gridViewRuntimes.Refresh();
            // disable show normal
            buttonShowNormal.Enabled = false;
            buttonShowException.Enabled = true;
            buttonSubmit.Enabled = true;
            // enable search
            textBoxPieceNum.Enabled = true;
            buttonGo.Enabled = true;
            radioButtonSO.Enabled = true;
            radioButtonWO.Enabled = true;
        }

        // wo comparison function
        private static int CompareWO(Piece a, Piece b)
        {
            int woA = int.Parse(a.wo);
            int woB = int.Parse(b.wo);
            if (woA > woB)
            {
                return 1;
            }
            else if (woA < woB)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }

        // display exceptions in grid view
        private void DisplayException()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(DisplayException));
                return;
            }
            gridViewRuntimes.Rows.Clear();
            foreach (int index in exceptionIndexList)
            {
                RunTime runtime = allList[index];
                string[] line = new string[11];
                line[0] = runtime.soNum.ToString();
                line[1] = runtime.woNum;
                line[2] = runtime.part;
                line[3] = runtime.seqNum.ToString();
                if (runtime.startTime.Year > 1)
                {
                    line[4] = runtime.startTime.ToString();
                }
                if (runtime.stopTime.Year > 1)
                {
                    line[5] = runtime.stopTime.ToString();
                }
                if (runtime.runTime > 0.00001)
                {
                    line[6] = runtime.runTime.ToString("F2");
                }
                line[7] = runtime.stdTime.ToString("F2");
                if (runtime.hasSolarsoftTime)
                {
                    line[8] = runtime.slsTime.ToString("F2");
                }
                else
                {
                    line[8] = "----";
                }
                if (runtime.actualTime > 0.00001)
                {
                    line[9] = runtime.actualTime.ToString("F2");
                }
                if (runtime.slsDate.Year > 1)
                {
                    line[10] = runtime.slsDate.ToString("yyyy-MM-dd");
                }
                gridViewRuntimes.Rows.Add(line);
            }
            gridViewRuntimes.Refresh();
            // enable show normal
            buttonShowNormal.Enabled = true;
            buttonShowException.Enabled = false;
            buttonSubmit.Enabled = true;
            // enable search
            textBoxPieceNum.Enabled = true;
            buttonGo.Enabled = true;
            radioButtonSO.Enabled = true;
            radioButtonWO.Enabled = true;
        }

        private void buttonShowNormal_Click(object sender, EventArgs e)
        {
            buttonSubmit.Enabled = false;
            buttonLoad.Enabled = false;
            dateTimePicker.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonShowException.Enabled = false;
            // erase corrected exceptions
            for (int i = 0; i < allList.Count; i++)
            {
                if (allList[i].IsException())
                {
                    if (!exceptionIndexList.Contains(i))
                    {
                        exceptionIndexList.Add(i);
                    }
                }
                else
                {
                    exceptionIndexList.Remove(i);
                }
            }
            // display all
            DisplayAll();
            isDisplayException = false;
        }

        private void buttonShowException_Click(object sender, EventArgs e)
        {
            buttonSubmit.Enabled = false;
            buttonLoad.Enabled = false;
            dateTimePicker.Enabled = false;
            buttonShowNormal.Enabled = false;
            buttonShowException.Enabled = false;
            // display exception
            DisplayException();
            isDisplayException = true;
        }

        // grid view data changed event handler
        private void GridViewValueChanged(
    object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                int index = 0;
                if (isDisplayException)
                {
                    index = exceptionIndexList[e.RowIndex];
                }
                else
                {
                    index = runtimeIndexList[e.RowIndex];
                }
                allList[index].actualTime = Convert.ToDouble(gridViewRuntimes.Rows[e.RowIndex].Cells[9].Value);
                if (0 == allList[index].taskList.Count)
                {
                    allList[index].startTime = dateTimePicker.Value;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Invalid runtime: " + gridViewRuntimes.Rows[e.RowIndex].Cells[9].Value.ToString() + "  reason:" + ex.Message);
                gridViewRuntimes.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = (object)string.Empty;
            }
        }

        private void radioButtonSO_CheckedChanged(object sender, EventArgs e)
        {
            isSearchBySO = true;
        }

        private void radioButtonWO_CheckedChanged(object sender, EventArgs e)
        {
            isSearchBySO = false;
        }

        private void buttonGo_Click(object sender, EventArgs e)
        {
            if (textBoxPieceNum.Text.Length > 5)
            {
                bool hasFound = false;
                int currentRow = gridViewRuntimes.CurrentCell.RowIndex;
                if (isDisplayException)
                {
                    for (int i = currentRow + 1; i < exceptionIndexList.Count; i++)
                    {
                        int index = exceptionIndexList[i];
                        if ((isSearchBySO && allList[index].soNum == Convert.ToInt32(textBoxPieceNum.Text)) || (!isSearchBySO && 0 == allList[index].woNum.CompareTo(textBoxPieceNum.Text)))
                        {
                            gridViewRuntimes.CurrentCell = gridViewRuntimes.Rows[i].Cells[0];
                            hasFound = true;
                            break;
                        }
                    }
                }
                else
                {
                    for (int i = currentRow + 1; i < runtimeIndexList.Count; i++)
                    {
                        string wo = allList[runtimeIndexList[i]].woNum;
                        while (i < runtimeIndexList.Count && (-1 == runtimeIndexList[i] || 0 == wo.CompareTo(allList[runtimeIndexList[i]].woNum)))
                        {
                            i++;
                        }
                        if (i >= runtimeIndexList.Count)
                        {
                            break;
                        }
                        int index = runtimeIndexList[i];
                        if (index >= 0 && ((isSearchBySO && allList[index].soNum == Convert.ToInt32(textBoxPieceNum.Text)) || (!isSearchBySO && 0 == allList[index].woNum.CompareTo(textBoxPieceNum.Text))))
                        {
                            gridViewRuntimes.CurrentCell = gridViewRuntimes.Rows[i].Cells[0];
                            hasFound = true;
                            break;
                        }
                    }
                }
                if (!hasFound)
                {
                    MessageBox.Show("Could not find " + textBoxPieceNum.Text);
                }
            }
        }
    }
}