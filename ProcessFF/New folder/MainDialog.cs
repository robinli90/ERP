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
    // @brief Main dialog class.
    // It interacts with users, manages the working thread and
    // displays outputs from the thread.
    // @note This is the main part of the software. It should
    // be called directly from Program.Main().
    public partial class MainDialog : Form
    {
        // target folder path
        internal const string targetFolder = "Q:\\RTEBOMP1\\";
        // ff folder path        
#if DEBUG
        internal const string sourceFolder = "C:\\CMS\\errrs\\";
#else
        internal const string sourceFolder = "T:\\ACCT\\FF\\";
#endif
        // rerun folder path
        internal const string rerunFolder = "T:\\ACCT\\ReRun\\";
        // error folder path
        internal const string errorFolder = "T:\\ACCT\\FFerrs\\";
        // archive folder path
        internal const string archiveFolder = "C:\\cms\\FFdone\\";
        // backup folder path
        internal const string backupFolder = "C:\\cms\\ff\\";
        // file name in target folder
        internal const string targetFileName = "FF.TXT";
        // target file full path
        internal const string targetPath = targetFolder + targetFileName;
        // Thread start/stop flag.
        // @b true: default. thread runs normally
        // @b false: request a thread to stop
        internal bool isRunningThread = true;
        // rerun file flag.
        // @b true: default. FF file is not a rerun one.
        // @b false: FF file is a rerun one.
        internal bool isRerunFile = false;
        // Stopwatch. It uses to count elapsed seconds since
        // a FF file had been moved into target folder.
        internal Stopwatch stopWatch = new Stopwatch();
        // The Working thread.
        // This thread intends to process ff files.
        // Output will be written into richEditBox.
        internal Thread thread;
        // The file cache of target file in target folder.
        // Each element stores a single update or a set of 
        // BOM updates.
        internal List<string> fileCache = new List<string>();
        // The process main class
        internal Process process = new Process();
        // wait time in minutes for processing target file
        internal double waitTime = 25.0;

        // Default constructor. It initializes dialog, enables
        // start button and disables stop button.
        public MainDialog()
        {
            InitializeComponent();
            // enable start button
            buttonStart.Enabled = true;
            // disable stop button
            buttonStop.Enabled = false;
            // initialize process object
            process.targetFolder = targetFolder;
            process.sourceFolder = sourceFolder;
            process.rerunFolder = rerunFolder;
            process.errorFolder = errorFolder;
            process.archiveFolder = archiveFolder;
            process.backupFolder = backupFolder;
            process.targetFileName = targetFileName;
            process.targetPath = targetPath;
        }

        // Start button click event handler.
        // It contains these features:
        // 1. disable start button
        // 2. enable stop button
        // 3. start work thread and make sure it works
        // @param[in] sender event sender
        // @param[in] e event argument
        internal void buttonStart_Click(object sender, EventArgs e)
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

        // Stop button click event handler.
        // It contains these features:
        // 1. enable start button
        // 2. disable stop button
        // 3. request to terminate the work thread
        // @param[in] sender event sender
        // @param[in] e event argument
        internal void buttonStop_Click(object sender, EventArgs e)
        {
            // request the thread to stop
            isRunningThread = false;
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
            if (richTextBox.Text.Length > 4000)
            {
                ClearTextBoxContent();
            }
            richTextBox.AppendText(value);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
        }

        // Get text content from richTextBox. It enables
        // communication between work thread and dialog thread.
        // @return string content of the richTextBox
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

        // process when rerun failed
        internal void ProcessWhenRerunFailed()
        {
            AppendTextBox("dump " + targetPath + " to " + errorFolder + Environment.NewLine);
            // dump to error folder
            process.WriteCacheIntoFiles(errorFolder);
            // remove target file name in target folder
            if (true == File.Exists(targetPath))
            {
                File.Delete(targetPath);
            }
            stopWatch.Stop();
            stopWatch.Reset();
        }

        // process when first try failed
        internal void ProcessWhenFirstTryFailed()
        {
            if (0 == fileCache.Count)
            {
                while (false == File.Exists(targetPath))
                {
                    AppendTextBox("Could not open " + targetPath + Environment.NewLine);
                    Thread.Sleep(1000);
                }
                AppendTextBox("read target file into cache" + Environment.NewLine);
                process.ReadFileIntoCache(targetPath);
            }
            AppendTextBox("dump cache to rerun" + Environment.NewLine);
            // dump to rerun
            process.WriteCacheIntoFiles(rerunFolder);
            // remove target file name in target folder
            if (true == File.Exists(targetPath))
            {
                File.Delete(targetPath);
            }
            stopWatch.Stop();
            stopWatch.Reset();
        }

        // process rerun file
        // It will process first file in the rerun folder.
        internal void ProcessRerunFile()
        {
            while (!Directory.Exists(sourceFolder))
            {
                AppendTextBox("Could not access " + sourceFolder);
            }
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
                process.ReadFileIntoCache(filesName[0]);
                // move a file from rerun into rtebomp1
                if (File.Exists(filesName[0]))
                {
                    File.Move(filesName[0], targetPath);
                }
                isRerunFile = true;
                // start count
                stopWatch.Reset();
                stopWatch.Start();
                AppendTextBox("wait to process " + targetPath + " at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            }
        }

        // process source folder
        // It will package all files in the source folder
        // into file cache, then put into target folder.
        internal void ProcessSourceFiles()
        {
            AppendTextBox("process files in " + sourceFolder + Environment.NewLine);
            // process all files in source folder
            process.ProcessSourceFolder();
            if (fileCache.Count > 0)
            {
                isRerunFile = false;
                stopWatch.Reset();
                stopWatch.Start();
                AppendTextBox("wait for processing " + targetPath + " at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            }
        }

        // process when target folder is empty
        internal void ProcessWhenTargetEmpty()
        {
            // dump file cache to ffdone
            if (fileCache.Count > 0)
            {
                AppendTextBox("dump cache to " + archiveFolder + Environment.NewLine);
                process.WriteCacheIntoFiles(process.archiveFolder + DateTime.Now.ToString("yyyyMM") + "\\");
            }
            if (Directory.EnumerateFileSystemEntries(sourceFolder).Any())
            {
                ProcessSourceFiles();
            }
            else
            {
                ProcessRerunFile();
            }
        }

        // process when target folder is not empty
        internal void ProcessWhenTargetFull()
        {
            if (false == stopWatch.IsRunning)
            {
                AppendTextBox("wait for processing " + targetPath + " at " + DateTime.Now.ToShortTimeString() + Environment.NewLine);
                stopWatch.Reset();
                stopWatch.Start();
            }
            // check if time elapse exceeds designated waiting time
            if (stopWatch.Elapsed.TotalMinutes < waitTime)
            {
                Thread.Sleep(1000);
            }
            else if (true == isRerunFile)
            {
                ProcessWhenRerunFailed();
            }
            else
            {
                ProcessWhenFirstTryFailed();
            }
        }

        // Create Processor object and implement loop.
        // @note This is the main function of the working
        // thread.
        internal void Run()
        {
            AppendTextBox("thread start" + Environment.NewLine);
            while (isRunningThread)
            {
                if (!Directory.Exists(targetFolder))
                {
                    AppendTextBox("Couldn't access " + targetFolder + Environment.NewLine);
                    Thread.Sleep(1000);
                    continue;
                }
                if (Directory.EnumerateFiles(targetFolder).Any())
                {
                    ProcessWhenTargetFull();
                }
                else
                {
                    ProcessWhenTargetEmpty();
                }
            }
            AppendTextBox("thread stop" + Environment.NewLine);
        }
    }
}