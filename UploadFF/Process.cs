using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Data.Odbc;
using System.IO;
using System.Threading;
using ExcoUtility;

namespace UploadFF
{
    public class Process
    {
        // rtebomp1 folder path
#if DEBUG
        public string targetFolder = string.Empty;
#else
        internal string targetFolder = string.Empty;
#endif
        // ff folder path        
#if DEBUG
        public string sourceFolder = string.Empty;
#else
        internal string sourceFolder = string.Empty;
#endif
        // rerun folder path
#if DEBUG
        public string rerunFolder = string.Empty;
#else
        internal string rerunFolder = string.Empty;
#endif
        // fferrs folder path
#if DEBUG
        public string errorFolder = string.Empty;
#else
        internal string errorFolder = string.Empty;
#endif
        // ffdone folder path
#if DEBUG
        public string archiveFolder = string.Empty;
#else
        internal string archiveFolder = string.Empty;
#endif
        // backup folder path
#if DEBUG
        public string backupFolder = string.Empty;
#else
        internal string backupFolder = string.Empty;
#endif
        // file name in target folder
#if DEBUG
        public string targetFileName = string.Empty;
#else
        internal string targetFileName = string.Empty;
#endif
        // target file full path
#if DEBUG
        public string targetPath = string.Empty;
#else
        internal string targetPath = string.Empty;
#endif
        // Thread start/stop flag
#if DEBUG
        public bool isRunningThread = true;
#else
        internal bool isRunningThread = true;
#endif
        // FF rerun file flag
#if DEBUG
        public bool isRerunFile = false;
#else
        internal bool isRerunFile = false;
#endif
        // Stopwatch. It uses to count elapsed seconds since
        // a FF file had been moved into rtebomp1.
#if DEBUG
        public Stopwatch stopWatch = new Stopwatch();
#else
        internal Stopwatch stopWatch = new Stopwatch();
#endif
        // The file cache of FF.TXT in rtebomp1.
        // Each element stores a single update or a set of 
        // BOM updates.
#if DEBUG
        public List<string> fileCache = new List<string>();
#else
        internal List<string> fileCache = new List<string>();
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

            // adjust end of line symbols
            // ignore records if it's not long enough
            if (update.Length >= 185)
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

        // replace ZZTMPYY tag in BOM with TMP
#if DEBUG
        public void ProcessBOMTag()
#else
        internal void ProcessBOMTag()
#endif
        {
            int index = 1;
            for (int i = 0; i < fileCache.Count; i++)
            {
                if (fileCache[i].Contains("BOM"))
                {
                    if (fileCache[i].Contains("ZZTMPYY1"))
                    {
                        fileCache[i] = fileCache[i].Replace("ZZTMPYY1", "TMP" + index.ToString("D2") + "   ");
                        index++;
                    }
                    if (fileCache[i].Contains("ZZTMPYY2"))
                    {
                        fileCache[i] = fileCache[i].Replace("ZZTMPYY2", "TMP" + index.ToString("D2") + "   ");
                        index++;
                    }
                    if (fileCache[i].Contains("ZZTMPYY3"))
                    {
                        fileCache[i] = fileCache[i].Replace("ZZTMPYY3", "TMP" + index.ToString("D2") + "   ");
                        index++;
                    }
                }
            }
        }

        // remove duplicated records in fileCache
        // remove a record if a previous one exists
#if DEBUG
        public void RemoveDuplicatedRecords()
#else
        internal void RemoveDuplicatedRecords()
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                int count = 0;
                foreach (string line in fileCache)
                {
                    if (0 == line.CompareTo(fileCache[i]))
                    {
                        count++;
                    }
                }
                if (count > 1)
                {
                    fileCache.RemoveAt(i);
                    i--;
                }
            }
        }

        // remove invalid BOM deletion in fileCache
        // we assume it as delete backer when create sub parts
#if DEBUG
        public void RemoveInvalidBOMDeletion(Database database = Database.CMSDAT)
#else
        internal void RemoveInvalidBOMDeletion(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                string wo = fileCache[i].Substring(0, 7);
                // check if bom backer deletion is valid
                if (0 == fileCache[i].Substring(10, 4).CompareTo("BOM3"))
                {
                    ExcoODBC odbcConnection = ExcoODBC.Instance;
                    odbcConnection.Open(database);
                    string query = "select * from cmsdat.cjobdm where efjob#='" + wo + "' and efmtlp like '%BAC%'";
                    OdbcDataReader reader = odbcConnection.RunQuery(query);
                    if (!reader.HasRows)
                    {
                        if (fileCache[i].Length > 187)
                        {
                            fileCache[i] = fileCache[i].Substring(187, fileCache[i].Length - 187);
                        }
                        else
                        {
                            fileCache.RemoveAt(i);
                            i--;
                        }
                    }
                    reader.Close();
                }
            }
        }

        // remove BOM if sub parts have already been created
#if DEBUG
        public void RemoveProcessedBOM(Database database = Database.CMSDAT)
#else
        internal void RemoveProcessedBOM(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                string wo = fileCache[i].Substring(0, 7);
                // check if sub parts have been processed
                if (fileCache[i].Contains("BOM2"))
                {
                    ExcoODBC odbcConnection = ExcoODBC.Instance;
                    odbcConnection.Open(database);
                    string query = "select dnjob from cmsdat.cjobh where dnord#=(select dnord# from cmsdat.cjobh where dnjob='" + wo + "')";
                    OdbcDataReader reader = odbcConnection.RunQuery(query);
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
                }
            }
        }

        // remove invalid sequence deletion records
#if DEBUG
        public void RemoveInvalidRTERecords(Database database = Database.CMSDAT)
#else
        internal void RemoveInvalidRTERecords(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                string wo = fileCache[i].Substring(0, 7);
                // check if rte seqence exists
                if (0 == fileCache[i].Substring(10, 3).CompareTo("RTE"))
                {
                    ExcoODBC odbcConnection = ExcoODBC.Instance;
                    odbcConnection.Open(database);
                    string query;
                    OdbcDataReader reader;
                    // check if nitride deletion is valid for solid
                    if ('0' == wo[0])
                    {
                        bool isNitrideDeletionValid = true;
                        query = "select r0fcde, r0ocde from cmsdat.food where r0lstn='" + wo + "'";
                        reader = odbcConnection.RunQuery(query);
                        while (reader.Read())
                        {
                            if (reader[0].ToString().Contains("NITR") && reader[1].ToString().Contains("NITR"))
                            {
                                isNitrideDeletionValid = false;
                                break;
                            }
                        }
                        reader.Close();
                        if (!isNitrideDeletionValid)
                        {
                            fileCache.RemoveAt(i);
                            i--;
                            continue;
                        }
                    }
                    query = "select * from cmsdat.cjobdr where edjob#='" + wo + "' and edcomq<1.0 and edseq#=" + fileCache[i].Substring(14, 3);
                    reader = odbcConnection.RunQuery(query);
                    // check delete/update validity
                    if (!reader.HasRows && (fileCache[i].Contains("RTE2") || fileCache[i].Contains("RTE3")))
                    {
                        fileCache.RemoveAt(i);
                        i--;
                    }
                    // check add validity
                    else if (reader.HasRows && fileCache[i].Contains("RTE1"))
                    {
                        fileCache.RemoveAt(i);
                        i--;
                    }
                    reader.Close();
                }
            }
        }

        // process nitride featuers in BOM
        // delete unwanted, add missed
#if DEBUG
        public void ProcessBOMNitride(Database database = Database.CMSDAT)
#else
        internal void ProcessBOMNitride(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                if (fileCache[i].Contains("BOM2"))
                {
                    // records which reprensets each line of bom
                    List<string> records = new List<string>();
                    string temp = fileCache[i].Replace("\r\n", "");
                    int numRecords = temp.Length / 185;
                    for (int j = 0; j < numRecords; j++)
                    {
                        records.Add(temp.Substring(j * 185, 185));
                    }
                    // delete all nitride related lines
                    for (int j = 0; j < records.Count; j++)
                    {
                        if (records[j].Contains("RTE3") && records[j][0] != '0')
                        {
                            records.RemoveAt(j);
                            j--;
                        }
                    }
                    // process nitride feature
                    string wo = fileCache[i].Substring(0, 7);
                    string part = fileCache[i].Substring(21, 20).Trim();
                    bool hasPlateFeature = false;
                    bool hasMandrelFeature = false;
                    // check if has nitride feature
                    ExcoODBC odbcConnection = ExcoODBC.Instance;
                    odbcConnection.Open(database);
                    string query = "select r0fcde, r0ocde from cmsdat.food where r0lstn='" + wo + "'";
                    OdbcDataReader reader = odbcConnection.RunQuery(query);
                    while (reader.Read())
                    {
                        if (reader[0].ToString().Contains("NITR") && reader[1].ToString().Contains("NITR"))
                        {
                            hasPlateFeature = true;
                            hasMandrelFeature = true;
                        }
                        else if (reader[1].ToString().Contains("NITR"))
                        {
                            if (reader[1].ToString().Contains("PLATE"))
                            {
                                hasPlateFeature = true;
                            }
                            else if (reader[1].ToString().Contains("MANDRE"))
                            {
                                hasMandrelFeature = true;
                            }
                        }
                    }
                    reader.Close();
                    // delete nitride if required
                    if (!hasPlateFeature || !hasMandrelFeature)
                    {
                        List<int> woLines = new List<int>();
                        for (int j = 0; j < records.Count; j++)
                        {
                            if ('0' == records[j][0] && !records[j].Contains("BAC") && !records[j].Contains("BOM3"))
                            {
                                woLines.Add(j);
                            }
                        }
                        for (int j = 0; j < woLines.Count; j++)
                        {
                            string newLine = string.Empty;
                            // solid die BOM
                            if (records[woLines[j]].Contains("BOM210") && '0' == records[woLines[j]][0])
                            {
                                // if need to delete nitride
                                query = "select * from cmsdat.cjobdr where edseq#=790 and edjob#='" + records[woLines[j]].Substring(0, 7) + "'";
                                reader = odbcConnection.RunQuery(query);
                                if (!reader.HasRows)
                                {
                                    reader.Close();
                                    continue;
                                }
                                reader.Close();
                                newLine = records[woLines[j]].Substring(0, 10) + "RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
                                fileCache.Add(newLine);
                            }
                            // hollow die BOM
                            else
                            {
                                if ((!hasPlateFeature && records[woLines[j]].Contains("PLA")) || (!hasMandrelFeature && records[woLines[j]].Contains("MA")))
                                {
                                    newLine = records[woLines[j]].Substring(69, 10) + "RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
                                    records.Add(newLine);
                                }
                            }
                        }
                    }
                    // write back to fileCache
                    string bomLine = string.Empty;
                    for (int j = 0; j < records.Count - 1; j++)
                    {
                        bomLine += records[j] + Environment.NewLine;
                    }
                    bomLine += records[records.Count - 1];
                    fileCache[i] = bomLine;
                }
            }
        }

        // remove records if wo or so is invalid or not in cjobh
#if DEBUG
        public void RemoveInvalidRecords(Database database = Database.CMSDAT)
#else
        internal void RemoveInvalidRecords(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                string wo = fileCache[i].Substring(0, 7);
                // check if wo is valid
                ExcoODBC odbcConnection = ExcoODBC.Instance;
                odbcConnection.Open(database);
                string query = "select dnord# from cmsdat.cjobh where dnjob='" + wo + "'";
                OdbcDataReader reader = odbcConnection.RunQuery(query);
                if (!reader.HasRows)
                {
                    fileCache.RemoveAt(i);
                    i--;
                }
                else
                {
                    if (reader.Read())
                    {
                        if (Convert.ToInt32(reader[0]) < 1)
                        {
                            fileCache.RemoveAt(i);
                            i--;
                        }
                    }
                }
                reader.Close();
            }
        }

        // read source files into file cache
        // single RTE holds one line
        // BOMs with same wo holds one line
#if DEBUG
        public void ReadSourceFiles()
#else
        internal void ReadSourceFiles()
#endif
        {
            IEnumerable<string> files = Directory.EnumerateFiles(sourceFolder);
            // wait and try accessing to make sure these files are completed
            Thread.Sleep(500);
            foreach (string fileName in files)
            {
                FileStream stream = File.Open(fileName, FileMode.Open, FileAccess.ReadWrite, FileShare.None);
                if (stream != null)
                {
                    stream.Close();
                }
            }
            foreach (string fileName in files)
            {
                FileStream stream = File.Open(fileName, FileMode.Open, FileAccess.ReadWrite, FileShare.None);
                if (stream != null)
                {
                    stream.Close();
                }
                ReadFileIntoCache(fileName);
            }
            // move source files into archive
            foreach (string fileName in files)
            {
                if (File.Exists(fileName))
                {
                    if (!File.Exists(backupFolder + Path.GetFileName(fileName)))
                    {
                        File.Move(fileName, backupFolder + Path.GetFileName(fileName));
                    }
                    else
                    {
                        File.Delete(fileName);
                    }
                }
            }
        }

        // adjust BOM steel diameter
        // if diameter is 9.5" or 10", check part description
        // if actual diameter is less than 9.06", use 9"
        // else, use 10"
#if DEBUG
        public void AdjustBOMSteelDiameter(Database database = Database.CMSDAT)
#else
        internal void AdjustBOMSteelDiameter(Database database = Database.CMSDAT)
#endif
        {
            for (int i = 0; i < fileCache.Count; i++)
            {
                if (fileCache[i].Contains("BOM2"))
                {
                    // get wo
                    string wo = fileCache[i].Substring(0, 7);
                    // check diameter
                    if (fileCache[i].Contains("H-13 9.5 DIA") || fileCache[i].Contains("H-13 10 DIA"))
                    {
                        // check part description
                        ExcoODBC odbcConnection = ExcoODBC.Instance;
                        odbcConnection.Open(database);
                        string query = "select dnpart from cmsdat.cjobh where dnjob='" + wo + "'";
                        OdbcDataReader reader = odbcConnection.RunQuery(query);
                        if (reader.Read())
                        {
                            string part = reader[0].ToString();
                            // try to extract diameter
                            int indexSpace = part.IndexOf(' ');
                            int indexX = part.IndexOf('X');
                            double dia = Convert.ToDouble(part.Substring(indexSpace + 1, indexX - indexSpace - 1));
                            if (dia > 9.06)
                            {
                                fileCache[i] = fileCache[i].Replace("H-13 9.5 DIA", "H-13 10 DIA ");
                            }
                            else
                            {
                                fileCache[i] = fileCache[i].Replace("H-13 10 DIA", "H-13 9 DIA ");
                                fileCache[i] = fileCache[i].Replace("H-13 9.5 DIA", "H-13 9 DIA  ");
                            }
                        }
                        reader.Close();

                    }
                }
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
            // read source files into cache
            ReadSourceFiles();
            // remove duplicated records
            RemoveDuplicatedRecords();
            // remove invalid records
            RemoveInvalidRecords();
            // remove invalid sequence deletion records
            RemoveInvalidRTERecords();
            // remove invalid BOM deletion records
            RemoveInvalidBOMDeletion();
            // remove BOM if sub parts have already been created
            RemoveProcessedBOM();
            // adjust steel diameter for BOM records
            AdjustBOMSteelDiameter();
            // process nitride features in BOM
            ProcessBOMNitride();
            // remove duplicated records
            RemoveDuplicatedRecords();
            // process BOM tags, replaced with TMPxx
            ProcessBOMTag();
            // dump fileCache into target folder
            WriteCacheIntoTargetFolder();
        }
    }
}