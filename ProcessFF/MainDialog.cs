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
using ExcoUtility;
using System.Data.Odbc;

namespace ProcessFF
{
    /// @brief Main dialog class.
    /// It interacts with users, manages the working thread and
    /// displays outputs from the thread.
    /// @note This is the main part of the software. It should
    /// be called directly from Program.Main().
    public partial class MainDialog : Form
    {
        /// rtebomp1 folder path
        internal const string rtebomp1Folder = "Q:\\RTEBOMP1\\";

        /// ff folder path        
#if DEBUG
        internal const string ffFolder = "C:\\CMS\\errrs\\";
#else
        internal const string ffFolder = "T:\\ACCT\\FF\\";
#endif

        /// rerun folder path
        internal const string rerunFolder = "T:\\ACCT\\ReRun\\";

        /// fferrs folder path
        internal const string fferrsFolder = "T:\\ACCT\\FFerrs\\";
        /// ffdone folder path
        internal const string ffdoneFolder = "C:\\cms\\FFdone\\";
        /// backup folder path
        internal const string backupFolder = "C:\\cms\\ff\\";

        /// file name in rtebomp1
        internal const string fileNameRtebomp1 = "FF.TXT";

        /// Thread start/stop flag.\n
        /// @b true: default. thread runs normally\n
        /// @b false: request a thread to stop
        internal bool isRunningThread = true;

        /// FF rerun file flag.\n
        /// @b true: default. FF file is not a rerun one.\n
        /// @b false: FF file is a rerun one.
        internal bool isRerunFile = false;

        /// Stopwatch. It uses to count elapsed seconds since
        /// a FF file had been moved into rtebomp1.
        internal Stopwatch stopWatch = new Stopwatch();

        /// The Working thread.
        /// This thread intends to process ff files.
        /// Output will be written into richEditBox.
        internal Thread thread;

        /// The file cache of FF.TXT in rtebomp1.
        /// Each element stores a single update or a set of 
        /// BOM updates.
        internal List<string> fileCache = new List<string>();

        /// Default constructor. It initializes dialog, enables
        /// start button and disables stop button.
        public MainDialog()
        {
            InitializeComponent();
            // enable start button
            buttonStart.Enabled = true;
            // disable stop button
            buttonStop.Enabled = false;
        }

        /// Start button click event handler.
        /// It contains these features:
        /// 1. disable start button
        /// 2. enable stop button
        /// 3. start work thread and make sure it works
        /// @param[in] sender event sender
        /// @param[in] e event argument
        internal void buttonStart_Click(object sender, EventArgs e)
        {
            // disable start
            buttonStart.Enabled = false;
            // enable stop
            buttonStop.Enabled = true;
            // start thread
            isRunningThread = true;
            thread = new Thread(Process);
            thread.Start();
            // make sure thread works
            while (!thread.IsAlive) ;
        }

        /// Stop button click event handler.
        /// It contains these features:
        /// 1. enable start button
        /// 2. disable stop button
        /// 3. request to terminate the work thread
        /// @param[in] sender event sender
        /// @param[in] e event argument
        internal void buttonStop_Click(object sender, EventArgs e)
        {
            // request the thread to stop
            isRunningThread = false;
            // enable start
            buttonStart.Enabled = true;
            // disable stop
            buttonStop.Enabled = false;
        }

        /// Append text to the richTextBox. It enables
        /// communication between work thread and dialog thread.
        /// @param[in] value text to be appended
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
            richTextBox.AppendText(value);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
        }

        /// Get text content from richTextBox. It enables
        /// communication between work thread and dialog thread.
        /// @return string content of the richTextBox
        internal string GetTextBoxContent()
        {
            return (string)richTextBox.Invoke(new Func<string>(() => richTextBox.Text));
        }

        /// Clear text content from richTextBox. It enables
        /// communication between work thread and dialog thread.
        internal void ClearTextBoxContent()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(ClearTextBoxContent));
                return;
            }
            richTextBox.Clear();
        }

        /// Read file content into fileCache. It enables update
        /// modification and storage.
        /// @param[in] filePath file path
        internal void ReadFileIntoCache(string filePath)
        {
            string[] lines = new string[0];
            bool isRetry = true;
            while (isRetry)
            {
                try
                {
                    if (File.Exists(filePath))
                    {
                        lines = File.ReadAllLines(filePath);
                    }
                    isRetry = false;
                }
                catch (IOException e)
                {
                    AppendTextBox(e.Message + Environment.NewLine);
                    isRetry = true;
                    Thread.Sleep(1000);
                }
            }
            string update = string.Empty;
            string workOrder = string.Empty;
            foreach (string line in lines)
            {
                if (line.Length > 1)
                {
                    // check if work order exists
                    ExcoODBC solarsoft = ExcoODBC.Instance;
                    OdbcDataReader reader;
                    string query = "select * from cmsdat.cjobh where dnjob='" + line.Substring(0, 7) + "'";
                    solarsoft.Open(Database.CMSDAT);
                    reader = solarsoft.RunQuery(query);
                    if (!reader.Read() || !reader.HasRows)
                    {
                        reader.Close();
                        continue;
                    }
                    reader.Close();
                    // a part of a BOM update set
                    if (line[0] != '0' && line[1] != '4')
                    {
                        update += Environment.NewLine + line;
                    }
                    // same work order
                    else if (0 == workOrder.CompareTo(line.Substring(0, 7)) && line.Contains("BOM"))
                    {
                        update += Environment.NewLine + line;
                    }
                    else
                    {
                        if (update.Length > 0)
                        {
                            fileCache.Add(update);
                        }
                        update = line;
                        workOrder = line.Substring(0, 7);
                    }
                }
            }
            if (update.Length > 0)
            {
                if ('\r' == update[update.Length - 2] && '\n' == update[update.Length - 1])
                {
                    update = update.Substring(0, update.Length - 2);
                }
                fileCache.Add(update);
            }
        }

        /// Dump fileCache content into a file.
        /// @param[in] folderPath output folder path
        internal void WriteCacheIntoDone(string folderPath)
        {
            // build folder
            string folderName = DateTime.Now.ToString("yyyyMM");
            if (!Directory.Exists(folderPath + folderName))
            {
                Directory.CreateDirectory(folderPath + folderName);
            }
            // build file
            foreach (string update in fileCache)
            {
                string workOrder = update.Substring(0, 7);
                string salesOrder = "NULL";
                ExcoODBC solarsoft = ExcoODBC.Instance;
                OdbcDataReader reader;
                string query = "select dnord# from cmsdat.cjobh where dnjob='" + workOrder + "'";
                solarsoft.Open(Database.CMSDAT);
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && reader[0] != DBNull.Value)
                {
                    salesOrder = reader[0].ToString();
                }
                reader.Close();
                StreamWriter writer = File.CreateText(folderPath + folderName + "\\" + salesOrder + "_" + workOrder + " " + DateTime.Now.ToString("HH-mm-ss") + ".txt");
                writer.Write(update);
                writer.Close();
                Thread.Sleep(1500);
            }
            fileCache.Clear();
        }

        /// Dump fileCache content into fferrs or rerun.
        /// @param[in] folderPath output folder path
        internal void WriteCacheIntoErrorOrRerun(string folderPath)
        {
            // build file
            foreach (string update in fileCache)
            {
                string workOrder = update.Substring(0, 7);
                StreamWriter writer = File.CreateText(folderPath + workOrder + " " + DateTime.Now.ToString("HH-mm-ss") + ".txt");
                writer.Write(update);
                writer.Close();
                Thread.Sleep(1500);
            }
            fileCache.Clear();
        }

        /// Dump fileCache content into rtebomp1.
        internal void WriteCacheIntoRtebomp1()
        {
            if (fileCache.Count > 0)
            {
                // build file
                StreamWriter writer = File.CreateText(rtebomp1Folder + fileNameRtebomp1);
                for (int i = 0; i < fileCache.Count; i++)
                {
                    if (i < fileCache.Count - 1)
                    {
                        writer.WriteLine(fileCache[i]);
                    }
                    else
                    {
                        writer.Write(fileCache[i]);
                    }
                }
                writer.Close();
            }
        }

        /// Read files in ff and fill fileCache. Then delete
        /// those files.
        internal void ProcessFFFolder()
        {
            while (!Directory.Exists(ffFolder))
            {
                AppendTextBox("Could not access " + ffFolder);
            }
            IEnumerable<string> files = Directory.EnumerateFiles(ffFolder);
            // wait to make sure these files are completed
            Thread.Sleep(500);
            foreach (string fileName in files)
            {
                ReadFileIntoCache(fileName);
            }
            // process ZZTMPYY tag
            int bomIndex = 1;
            for (int i = 0; i < fileCache.Count; i++)
            {
                if (-1 != fileCache[i].IndexOf("ZZTMPYY1"))
                {
                    string tempWO = "TMP";
                    tempWO += bomIndex.ToString();
                    while (tempWO.Length != "ZZTMPYY1".Length)
                    {
                        tempWO += " ";
                    }
                    fileCache[i] = fileCache[i].Replace("ZZTMPYY1", tempWO);
                    bomIndex++;
                }
                if (-1 != fileCache[i].IndexOf("ZZTMPYY2"))
                {
                    string tempWO = "TMP";
                    tempWO += bomIndex.ToString();
                    while (tempWO.Length != "ZZTMPYY2".Length)
                    {
                        tempWO += " ";
                    }
                    fileCache[i] = fileCache[i].Replace("ZZTMPYY2", tempWO);
                    bomIndex++;
                }
                if (-1 != fileCache[i].IndexOf("ZZTMPYY3"))
                {
                    string tempWO = "TMP";
                    tempWO += bomIndex.ToString();
                    while (tempWO.Length != "ZZTMPYY3".Length)
                    {
                        tempWO += " ";
                    }
                    fileCache[i] = fileCache[i].Replace("ZZTMPYY3", tempWO);
                    bomIndex++;
                }
            }

            // eliminate invalid records
            for (int i = 0; i < fileCache.Count; i++)
            {
                // process to eliminate duplicated records
                int count = 0;
                foreach (string line in fileCache)
                {
                    if (fileCache[i].Contains(line) || line.Contains(fileCache[i]))
                    {
                        count++;
                    }
                }
                if (count > 1)
                {
                    fileCache.RemoveAt(i);
                    i--;
                    continue;
                }
                if (fileCache[i].Contains("BOM"))
                {
                    string wo = fileCache[i].Substring(0, 7);
                    bool needTag = false;
                    string tag = string.Empty;
                    int index = fileCache[i].IndexOf("TMP");
                    if (index > -1)
                    {
                        needTag = true;
                        tag = fileCache[i].Substring(index, 5);
                    }
                    // check if routine is an invalid delete
                    string query;
                    ExcoODBC solarsoft = ExcoODBC.Instance;
                    OdbcDataReader reader;
                    index = fileCache[i].IndexOf("BOM3800");
                    if (index > -1)
                    {
                        query = "select * from cmsdat.cjobdm where efjob#='" + wo + "' and eflin#=" + fileCache[i][index + 10];
                        solarsoft.Open(Database.CMSDAT);
                        reader = solarsoft.RunQuery(query);
                        if (!reader.Read() || reader[0] == DBNull.Value)
                        {
                            if (fileCache[i].Length > 187)
                            {
                                fileCache[i] = fileCache[i].Remove(index - 10, 187);
                            }
                            else
                            {
                                fileCache.RemoveAt(i);
                                i--;
                            }
                            reader.Close();
                            continue;
                        }
                        reader.Close();
                    }

                    // check if routine has nitride
                    query = "select * from cmsdat.cjobdr where edjob#='" + wo + "' and edseq#=790";
                    bool isRoutineHasNitride = false;
                    solarsoft = ExcoODBC.Instance;
                    solarsoft.Open(Database.CMSDAT);
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        isRoutineHasNitride = true;
                    }
                    reader.Close();
                    bool isFeatureHasNitride = false;
                    // check if feature has nitride
                    query = "select r0fcde, r0ocde from cmsdat.food where r0lstn='" + wo + "'";
                    reader = solarsoft.RunQuery(query);
                    while (reader.Read())
                    {
                        if (reader[0].ToString().Contains("NITR") && reader[1].ToString().Contains("NITR"))
                        {
                            isFeatureHasNitride = true;
                        }
                    }
                    reader.Close();
                    // if feature has nitride, delete all nitride delete record
                    if (isFeatureHasNitride)
                    {
                        for (int j = 0; j < fileCache.Count; j++)
                        {
                            if (fileCache[j].Length > 2 && fileCache[j][fileCache[j].Length - 2] == '\r' && fileCache[j][fileCache[j].Length - 1] == '\n')
                            {
                                fileCache[j] = fileCache[j].Substring(0, fileCache[j].Length - 2);
                            }
                            int indexNitride = fileCache[j].IndexOf("RTE3790");
                            if (indexNitride >= 0)
                            {
                                if (fileCache[j].Contains(wo) || (needTag && fileCache[j].Contains(tag)))
                                {
                                    if (fileCache[j].Length > indexNitride + 176 && fileCache[j][indexNitride + 175] == '\r' && fileCache[j][indexNitride + 176] == '\n')
                                    {
                                        fileCache[j] = fileCache[j].Remove(indexNitride - 10, 187);
                                    }
                                    else
                                    {
                                        fileCache[j] = fileCache[j].Remove(indexNitride - 10, 185);
                                    }
                                    if (fileCache[j].Length == 0)
                                    {
                                        fileCache.RemoveAt(j);
                                    }
                                    j--;
                                }
                            }
                        }
                    }
                    // if routine has nitride
                    if (isRoutineHasNitride)
                    {
                        // if feature has nitride, eliminate nitride delete record
                        if (!isFeatureHasNitride)
                        {
                            // if feature doesn't have nitride, add nitride elimination record
                            bool hasElimination = false;
                            for (int j = 0; j < fileCache.Count; j++)
                            {
                                if (fileCache[j].Contains("RTE3790"))
                                {
                                    if (fileCache[j].Contains(wo) || (needTag && fileCache[j].Contains(tag)))
                                    {
                                        hasElimination = true;
                                        break;
                                    }
                                }
                            }
                            if (!hasElimination)
                            {
                                string record = wo;
                                if (needTag)
                                {
                                    record = tag + "  ";
                                }
                                record += "   RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000" + Environment.NewLine;
                                fileCache.Add(record);
                            }
                        }
                    }
                }
                else
                {
                    int index = fileCache[i].IndexOf("RTE3");
                    if (index > -1)
                    {
                        string seq = fileCache[i].Substring(index + 4, 3);
                        string wo = fileCache[i].Substring(0, 7);
                        if ('0' != wo[0])
                        {
                            foreach (string line in fileCache)
                            {
                                if (line.Contains(wo))
                                {
                                    wo = line.Substring(0, 7);
                                    break;
                                }
                            }
                        }
                        // check solarsoft
                        string query = "select * from cmsdat.cjobdr where edjob#='" + wo + "' and edseq#=" + seq;
                        ExcoODBC solarsoft = ExcoODBC.Instance;
                        solarsoft.Open(Database.CMSDAT);
                        OdbcDataReader reader = solarsoft.RunQuery(query);
                        if (!reader.Read() || reader[0] == DBNull.Value)
                        {
                            fileCache.RemoveAt(i);
                            i--;
                        }
                        reader.Close();
                    }
                }
            }
            // dump to rtebomp1
            WriteCacheIntoRtebomp1();
            foreach (string fileName in files)
            {
                if (File.Exists(fileName))
                {
#if DEBUG
                    File.Move(fileName, fileName.Replace("C:\\cms\\errrs\\", "C:\\cms\\ff\\"));
#else
                    File.Move(fileName, fileName.Replace("T:\\ACCT", "C:\\cms"));
#endif
                }
            }
        }

        /// Create Processor object and implement loop.
        /// @note This is the main function of the working
        /// thread.
        internal void Process()
        {
            AppendTextBox("thread start" + Environment.NewLine);
            while (isRunningThread)
            {
                if (!Directory.Exists(rtebomp1Folder))
                {
                    AppendTextBox("Couldn't open " + rtebomp1Folder + Environment.NewLine);
                    Thread.Sleep(1000);
                    continue;
                }
                if (Directory.EnumerateFiles(rtebomp1Folder).Any())
                {
                    if (stopWatch.Elapsed.TotalMinutes == 0.0)
                    {
                        AppendTextBox("wait to process rtebomp1 at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        stopWatch.Reset();
                        stopWatch.Start();
                    }
                    // check if time elapse exceeds 25 mins
                    if (stopWatch.Elapsed.TotalMinutes < 25.0)
                    {
                        Thread.Sleep(1000);
                    }
                    else if (isRerunFile)
                    {
                        AppendTextBox("dump cache to fferrs" + Environment.NewLine);
                        // dump to fferrs
                        WriteCacheIntoErrorOrRerun(fferrsFolder);
                        // remove ff.txt in rtebomp1
                        File.Delete(rtebomp1Folder + fileNameRtebomp1);
                        stopWatch.Stop();
                        stopWatch.Reset();
                    }
                    else
                    {
                        if (0 == fileCache.Count)
                        {
                            AppendTextBox("read rtebomp1/ff.txt into cache" + Environment.NewLine);
                            ReadFileIntoCache(rtebomp1Folder + fileNameRtebomp1);
                        }
                        AppendTextBox("dump cache to rerun" + Environment.NewLine);
                        // dump to rerun
                        WriteCacheIntoErrorOrRerun(rerunFolder);
                        // remove ff.txt in rtebomp1
                        File.Delete(rtebomp1Folder + fileNameRtebomp1);
                        stopWatch.Stop();
                        stopWatch.Reset();
                    }
                }
                else
                {
                    // dump file cache to ffdone
                    if (fileCache.Count > 0)
                    {
                        AppendTextBox("dump cache to ffdone" + Environment.NewLine);
                        WriteCacheIntoDone(ffdoneFolder);
                    }
                    if (Directory.EnumerateFileSystemEntries(ffFolder).Any())
                    {
                        AppendTextBox("process files in ff" + Environment.NewLine);
                        // process all files in ff folder
                        ProcessFFFolder();
                        if (fileCache.Count > 0)
                        {
                            isRerunFile = false;
                            stopWatch.Reset();
                            stopWatch.Start();
                            AppendTextBox("wait to process rtebomp1 at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        }
                    }
                    else
                    {
                        string[] filesName = Directory.GetFiles(rerunFolder);
                        if (0 == filesName.Length)
                        {
                            AppendTextBox("nothing to do. wait" + Environment.NewLine);
                            Thread.Sleep(1000);
                        }
                        else
                        {
                            AppendTextBox("process rerun file " + filesName[0] + Environment.NewLine);
                            // read file content into cache
                            ReadFileIntoCache(filesName[0]);
                            // move a file from rerun into rtebomp1
                            if (File.Exists(filesName[0]))
                            {
                                File.Move(filesName[0], rtebomp1Folder + fileNameRtebomp1);
                            }
                            isRerunFile = true;
                            // start count
                            stopWatch.Reset();
                            stopWatch.Start();
                            AppendTextBox("wait to process rtebomp1 at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                        }
                    }
                }
            }
            AppendTextBox("thread stop" + Environment.NewLine);
        }
    }
}