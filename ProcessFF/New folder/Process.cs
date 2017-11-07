using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Data.Odbc;
using System.IO;
using System.Threading;
using ExcoUtility;

namespace ProcessFF
{
    public class Process
    {
        // rtebomp1 folder path
#if DEBUG
        public string targetFolder = string.Empty;
#else
        private string targetFolder = string.Empty;
#endif
        // ff folder path        
#if DEBUG
        public string sourceFolder = string.Empty;
#else
        private string sourceFolder = string.Empty;
#endif
        // rerun folder path
#if DEBUG
        public string rerunFolder = string.Empty;
#else
        private string rerunFolder = string.Empty;
#endif
        // fferrs folder path
#if DEBUG
        public string errorFolder = string.Empty;
#else
        private string errorFolder = string.Empty;
#endif
        // ffdone folder path
#if DEBUG
        public string archiveFolder = string.Empty;
#else
        private string archiveFolder = string.Empty;
#endif
        // backup folder path
#if DEBUG
        public string backupFolder = string.Empty;
#else
        private string backupFolder = string.Empty;
#endif
        // file name in target folder
#if DEBUG
        public string targetFileName = string.Empty;
#else
        private string targetFileName = string.Empty;
#endif
        // target file full path
#if DEBUG
        public string targetPath = string.Empty;
#else
        private string targetPath = string.Empty;
#endif
        // Thread start/stop flag
#if DEBUG
        public bool isRunningThread = true;
#else
        private bool isRunningThread = true;
#endif
        // FF rerun file flag
#if DEBUG
        public bool isRerunFile = false;
#else
        private bool isRerunFile = false;
#endif
        // Stopwatch. It uses to count elapsed seconds since
        // a FF file had been moved into rtebomp1.
#if DEBUG
        public Stopwatch stopWatch = new Stopwatch();
#else
        private Stopwatch stopWatch = new Stopwatch();
#endif
        // The file cache of FF.TXT in rtebomp1.
        // Each element stores a single update or a set of 
        // BOM updates.
#if DEBUG
        public List<string> fileCache = new List<string>();
#else
        private List<string> fileCache = new List<string>();
#endif

        // Read file content into fileCache. It enables update
        // modification and storage.
        // @param[in] filePath file path
#if DEBUG
        public void ReadFileIntoCache(string filePath)
#else
        internal void ReadFileIntoCache(string filePath)
#endif
        {
            string[] lines = new string[0];
            lines = File.ReadAllLines(filePath);
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
            // eliminate duplicated BOM
            for (int i = 0; i < fileCache.Count; i++)
            {
                if (fileCache[i].Contains("BOM"))
                {
                    // eliminate if subparts have already been created
                    ExcoODBC solarsoft = ExcoODBC.Instance;
                    OdbcDataReader reader;
                    string query = "select dnjob from cmsdat.cjobh where dnord#=(select dnord# from cmsdat.cjobh where dnjob='" + fileCache[i].Substring(0, 7) + "')";
                    solarsoft.Open(Database.CMSDAT);
                    reader = solarsoft.RunQuery(query);
                    while (reader.Read())
                    {
                        if (reader[0].ToString().Trim().Length == 9)
                        {
                            fileCache.RemoveAt(i);
                            i--;
                            break;
                        }
                    }
                    reader.Close();
                    // eliminate if file has duplicated BOM
                    string wo = fileCache[i].Substring(0, 7);
                    foreach (string line in fileCache)
                    {
                        if (0 == wo.CompareTo(line.Substring(0, 7)))
                        {
                            fileCache.RemoveAt(i);
                            i--;
                            break;
                        }
                    }
                }
            }
            // adjust end of line symbols
            if (update.Length > 0)
            {
                if ('\r' == update[update.Length - 2] && '\n' == update[update.Length - 1])
                {
                    update = update.Substring(0, update.Length - 2);
                }
                fileCache.Add(update);
            }
        }

        // Dump fileCache content into a file.
#if DEBUG
        public void WriteCacheIntoFiles(string folder, Database database = Database.CMSDAT)
#else
        internal void WriteCacheIntoFiles(string folder, Database database = Database.CMSDAT)
#endif
        {
            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }
            // build file
            foreach (string update in fileCache)
            {
                string workOrder = update.Substring(0, 7);
                string salesOrder = "NULL";
                ExcoODBC solarsoft = ExcoODBC.Instance;
                OdbcDataReader reader;
                string query = "select dnord# from cmsdat.cjobh where dnjob='" + workOrder + "'";
                solarsoft.Open(database);
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && reader[0] != DBNull.Value)
                {
                    salesOrder = reader[0].ToString();
                }
                reader.Close();
                StreamWriter writer = File.CreateText(folder + salesOrder + "_" + workOrder + " " + DateTime.Now.ToString("HH-mm-ss") + ".txt");
                writer.Write(update);
                writer.Close();
                Thread.Sleep(1500);
            }
            fileCache.Clear();
        }

        // Dump fileCache content into target folder.
#if DEBUG
        public void WriteCacheIntoTargetFolder()
#else
        internal void WriteCacheIntoTargetFolder()
#endif
        {
            if (fileCache.Count > 0)
            {
                // build file
                StreamWriter writer = File.CreateText(targetPath);
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

        // Read files in ff and fill fileCache. Then delete
        // those files.
#if DEBUG
        public void ProcessSourceFolder()
#else
        internal void ProcessSourceFolder()
#endif
        {
            IEnumerable<string> files = Directory.EnumerateFiles(sourceFolder);
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
            // dump to target folder
            WriteCacheIntoTargetFolder();
            foreach (string fileName in files)
            {
                if (File.Exists(fileName))
                {
                    File.Move(fileName, fileName.Replace("T:\\ACCT", "C:\\cms"));
                }
            }
        }
    }
}