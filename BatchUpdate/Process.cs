using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.IO;
using System.Data.Odbc;

namespace BatchUpdate
{
    public struct Scrap
    {
        public string wo;
        public int seq;
        public DateTime time;
    }

    public struct SeqTemplate
    {
        // sequence number
        public int seqNum;
        // routine runtime
        public double runtime;
        // completed quantity
        public int compQuant;
    }

    public class Process
    {
        // date for latest tasks
        public DateTime date = new DateTime();
        // batch submit program path
        public string batchSubmitProgram = "\\\\10.0.0.6\\ShopData\\Development\\tiger\\BatchUpdate\\BatchUpdate_Submit.exe";
        // batch file path
        public string batchFilePath = "Q:\\JOHN\\BATCH.TXT";
        // batch file path after process
        public string batchFilePathAfterProcess = "Q:\\JOHN\\BATCH.001";
        // archive file folder
        public string archiveFolderPath = "C:\\CMS\\BATCHDONE\\" + DateTime.Now.ToString("yyyyMM") + "\\";
        // die map
        public Dictionary<int, Die> dieMap = new Dictionary<int, Die>();
        // piece list which need to be processed
        public List<Piece> pieceList = new List<Piece>();
        // batch upload cache, will dump to batch file
        public Dictionary<string, List<string>> cacheMap = new Dictionary<string, List<string>>();
        // scrap dictionary
        public Dictionary<string, Scrap> scrapMap = new Dictionary<string, Scrap>();
        // spark runtime dictionary
        public Dictionary<int, List<Task>> sparkMap = new Dictionary<int, List<Task>>();
        // wire runtime dictionary
        public Dictionary<int, List<Task>> wireMap = new Dictionary<int, List<Task>>();
        // predicted NC mill runtime dictionary
        public Dictionary<int, Dictionary<string, double>> predictedRuntimeMap = new Dictionary<int, Dictionary<string, double>>();
        // sequence template dictionary
        public Dictionary<string, Dictionary<int, SeqTemplate>> seqTemplateMap = new Dictionary<string, Dictionary<int, SeqTemplate>>();
        // sequence template dictionary for history
        public Dictionary<string, SeqTemplate> seq20HJOBHMap = new Dictionary<string, SeqTemplate>();
        public Dictionary<string, SeqTemplate> seq30HJOBHMap = new Dictionary<string, SeqTemplate>();
        // latest decade activity
        public Dictionary<int, List<string>> decadeTasks = new Dictionary<int, List<string>>();
        // decade assembly finish dictionary
        public Dictionary<string, bool> assemblyFinishMap = new Dictionary<string, bool>();
        // database
        Database database;
        // minimum so#
        public int minimumSO = 9999999;
        // maximum so#
        public int maximumSO = -99999999;

        // constructor
        public Process(Database database, DateTime date)
        {
            this.database = database;
            this.date = date;
        }

        // get decade assembly finish dictionary
        public void BuildAssemblyFinishDictionary()
        {
            string query = "select distinct ordernumber, part from dbo.[d_task] where ordernumber>=" + minimumSO.ToString() + " and ordernumber<=" + maximumSO.ToString() + " and task='IZ' and tasktime<='" + date.ToString("yyyy-MM-dd 23:59:59") + "'";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(Database.DECADE_MARKHAM);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["ordernumber"]);
                char type = Convert.ToChar(reader["part"]);
                if (dieMap.ContainsKey(soNum))
                {
                    foreach (Piece piece in dieMap[soNum].pieceList)
                    {
                        if (type == piece.type)
                        {
                            assemblyFinishMap.Add(piece.wo, true);
                        }
                    }
                }
            }
            reader.Close();
        }

        // get latest decade activity
        public void BuildLatestDecadeActivity()
        {
            string query = "select ordernumber, part, subpart, task, tasktime from dbo.[d_task] where ordernumber>=" + minimumSO.ToString() + " and ordernumber<=" + maximumSO.ToString() + " order by ordernumber, tasktime desc";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(Database.DECADE_MARKHAM);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["ordernumber"]);
                char type = Convert.ToChar(reader["part"]);
                string part = reader["part"].ToString().Trim() + reader["subpart"].ToString().Trim();
                string taskCode = reader["task"].ToString().Trim();
                DateTime taskTime = Convert.ToDateTime(reader["tasktime"]);
                string task = taskCode + " " + part + " " + taskTime.ToString("MM-dd HH:mm");
                if (dieMap.ContainsKey(soNum))
                {
                    if (decadeTasks.ContainsKey(soNum))
                    {
                        if (decadeTasks[soNum].Count < 4)
                        {
                            decadeTasks[soNum].Add(task);
                        }
                    }
                    else
                    {
                        List<string> taskList = new List<string>();
                        taskList.Add(task);
                        decadeTasks.Add(soNum, taskList);
                    }
                }
            }
            reader.Close();
        }

        // get predicted NC mill runtime
        public void BuildPredictedRuntimeDictionary()
        {
            string query = "select ordernumber, prtcode, [MachineTime] from dbo.[d_CNCMachineTime] order by [InsertTime] desc";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(Database.DECADE_MARKHAM);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                int so = Convert.ToInt32(reader["ordernumber"]) + 200000;
                string partCode = reader["prtcode"].ToString();
                double runtime = Convert.ToDouble(reader["MachineTime"]) / 60.0;
                if (predictedRuntimeMap.ContainsKey(so))
                {
                    if (predictedRuntimeMap[so].ContainsKey(partCode))
                    {
                        predictedRuntimeMap[so][partCode] = runtime;
                    }
                    else
                    {
                        predictedRuntimeMap[so].Add(partCode, runtime);
                    }
                }
                else
                {
                    Dictionary<string, double> newDieMap = new Dictionary<string, double>();
                    newDieMap.Add(partCode, runtime);
                    predictedRuntimeMap.Add(so, newDieMap);
                }
            }
            reader.Close();
        }

        // get predefined sequence template for current orders
        public void GetSequenceTemplateCurrent()
        {
            string query = "select edjob#, edseq#, edruns, edcomq from cmsdat.cjobdr order by edjob#, edseq#";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                string wo = reader[0].ToString().Trim();
                SeqTemplate seqTemplate = new SeqTemplate();
                seqTemplate.seqNum = Convert.ToInt32(reader[1]);
                seqTemplate.runtime = Convert.ToDouble(reader[2]);
                seqTemplate.compQuant = Convert.ToInt32(reader[3]);
                if (seqTemplateMap.ContainsKey(wo))
                {
                    seqTemplateMap[wo].Add(seqTemplate.seqNum, seqTemplate);
                }
                else
                {
                    Dictionary<int, SeqTemplate> newSeqTemplateMap = new Dictionary<int, SeqTemplate>();
                    newSeqTemplateMap.Add(seqTemplate.seqNum, seqTemplate);
                    seqTemplateMap.Add(wo, newSeqTemplateMap);
                }
            }
            reader.Close();
        }

        // get predefined sequence template for history orders
        public void GetSequenceTemplateHistory()
        {
            string query = "select edjob#, edseq#, edruns, edcomq from cmsdat.hjobdr where edseq#=20 order by edjob#, edseq#";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                string wo = reader[0].ToString().Trim();
                SeqTemplate seqTemplate = new SeqTemplate();
                seqTemplate.seqNum = Convert.ToInt32(reader[1]);
                seqTemplate.runtime = Convert.ToDouble(reader[2]);
                seqTemplate.compQuant = Convert.ToInt32(reader[3]);
                if (!seq20HJOBHMap.ContainsKey(wo))
                {
                    seq20HJOBHMap.Add(wo, seqTemplate);
                }
            }
            reader.Close();
            query = "select edjob#, edseq#, edruns, edcomq from cmsdat.hjobdr where edseq#=30 order by edjob#, edseq#";
            reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                string wo = reader[0].ToString().Trim();
                SeqTemplate seqTemplate = new SeqTemplate();
                seqTemplate.seqNum = Convert.ToInt32(reader[1]);
                seqTemplate.runtime = Convert.ToDouble(reader[2]);
                seqTemplate.compQuant = Convert.ToInt32(reader[3]);
                if (!seq30HJOBHMap.ContainsKey(wo))
                {
                    seq30HJOBHMap.Add(wo, seqTemplate);
                }
            }
            reader.Close();
        }

        // build scrap dictionary
        public void BuildScrapDictionary()
        {
            string query = "select oejob#, oeseq#, oecdat, oectim from cmsdat.rprp order by oecdat, oectim";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                Scrap scrap = new Scrap();
                scrap.wo = reader[0].ToString().Trim();
                scrap.seq = Convert.ToInt32(reader[1]);
                scrap.time = Convert.ToDateTime(Convert.ToDateTime(reader[2]).ToShortDateString() + " " + reader[3].ToString().Trim());
                if (!scrapMap.ContainsKey(scrap.wo))
                {
                    scrapMap.Add(scrap.wo, scrap);
                }
            }
            reader.Close();
        }

        // build spark and edm dictionary
        public void BuildRuntimeDictionary()
        {
            string query = "select tasktime, empnum, prtcode, task, station, r1, sonum, station from cmsdat.excotask where (station='SPKC' or station='WOUT') and rtype='RTM' and (flags is null or flags<1) and (tasktime<='" + date.ToString("yyyy-MM-dd 23:59:59") + "' and tasktime>'" + date.AddMonths(-3).ToString("yyyy-MM-dd 00:00:00") + "') order by tasktime";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                int so = Convert.ToInt32(reader[6]);
                if (0 == reader[7].ToString().Trim().CompareTo("SPKC"))
                {
                    Task task = new Task(so, Convert.ToInt32(reader[1]), reader[2].ToString()[0], reader[2].ToString()[1], reader[3].ToString(), Convert.ToDateTime(reader[0]), reader[4].ToString(), 460);
                    task.runTime = Convert.ToDouble(reader[5]);
                    if (sparkMap.ContainsKey(so))
                    {
                        sparkMap[so].Add(task);
                    }
                    else
                    {
                        List<Task> newTask = new List<Task>();
                        newTask.Add(task);
                        sparkMap.Add(so, newTask);
                    }
                }
                else
                {
                    Task task = new Task(so, Convert.ToInt32(reader[1]), reader[2].ToString()[0], reader[2].ToString()[1], reader[3].ToString(), Convert.ToDateTime(reader[0]), reader[4].ToString(), 470);
                    task.runTime = Convert.ToDouble(reader[5]);
                    if (wireMap.ContainsKey(so))
                    {
                        wireMap[so].Add(task);
                    }
                    else
                    {
                        List<Task> newTask = new List<Task>();
                        newTask.Add(task);
                        wireMap.Add(so, newTask);
                    }
                }
            }
            reader.Close();
        }

        // write cache content into batch file
        public void WriteToBatchFile()
        {
            while (File.Exists(batchFilePath))
            {
                File.Delete(batchFilePath);
            }
            StreamWriter writer = File.CreateText(batchFilePath);
            foreach (List<string> cache in cacheMap.Values)
            {
                if (cache.Count > 0)
                {
                    writer.WriteLine(WriteHeader());
                    foreach (string line in cache)
                    {
                        writer.WriteLine(line);
                    }
                }
            }
            writer.Close();
        }

        // write header record
        public string WriteHeader()
        {
            HeaderRecord header = new HeaderRecord();
            ExcoCalendar calendar = new ExcoCalendar(date.Year - 2000, date.Month, false, 1);
            header.date.SetString(calendar.GetCalendarMonth().ToString("D2") + date.Day.ToString("D2") + calendar.GetCalendarYear().ToString("D2"));
            header.fiscalPeriod.SetString(calendar.GetFiscalYear().ToString("D2") + calendar.GetFiscalMonth().ToString("D2"));
            return header.BuildString();
        }

        // move batch file to archive folder
        public void MoveToArchive()
        {
            if (!Directory.Exists(archiveFolderPath))
            {
                Directory.CreateDirectory(archiveFolderPath);
            }
            string archiveFilePath = archiveFolderPath + DateTime.Now.ToString("yyyy-MM-dd HH-mm-ss") + ".txt";
            File.Move(batchFilePathAfterProcess, archiveFilePath);
        }

        // back flush previous sequences if they are empty
        public void BackFlush(DateTime datetime)
        {
            foreach (Piece piece in pieceList)
            {
                piece.BackFlush(datetime, assemblyFinishMap);
            }
        }


        // if a hollow die are finished, add 800 sequence to its parent piece
        // A piece is finished but needs to complete when:
        // 1. if a parent piece
        // 2. all subparts have been completed, and the parent piece itself has no unprocessed tasks and only has sequence 800 left
        public void CompleteFinishedPieces()
        {
            foreach (Die die in dieMap.Values)
            {
                // hollow die
                if (die.isHollow)
                {
                    bool isSubPartsFinished = true;
                    // if no sub part, skip
                    bool hasSubParts = false;
                    for (int i = 0; i < die.pieceList.Count; i++)
                    {
                        if (die.pieceList[i].wo.Length > 8)
                        {
                            hasSubParts = true;
                            break;
                        }
                    }
                    if (!hasSubParts)
                    {
                        string query = "select dnjob from cmsdat.hjobh where dnord#=" + die.so.ToString();
                        ExcoODBC odbcConnection = ExcoODBC.Instance;
                        odbcConnection.Open(database);
                        OdbcDataReader reader = odbcConnection.RunQuery(query);
                        while (reader.Read())
                        {
                            if (reader["dnjob"].ToString().Trim().Length > 8)
                            {
                                hasSubParts = true;
                                break;
                            }
                        }
                        reader.Close();
                    }
                    for (int i = 0; i < die.pieceList.Count; i++)
                    {
                        if (i != die.parentIndex)
                        {
                            if (!die.pieceList[i].hasCompleted && die.pieceList[i].wo.Length > 8)
                            {
                                isSubPartsFinished = false;
                                break;
                            }
                        }
                    }
                    if (isSubPartsFinished && die.parentIndex > -1 && hasSubParts)
                    {
                        Piece parent = die.pieceList[die.parentIndex];
                        parent.Complete(date);
                    }
                }
            }
        }

        // if pieces are completed, mark it
        public void MarkCompletedPieces()
        {
            for (int i = 0; i < pieceList.Count; i++)
            {
                pieceList[i].hasCompleted = pieceList[i].IsCompleted();
            }
        }

        // get all unprocessed tasks
        public void GetAllTasks()
        {
            // first we get so list from cmsdat.cjobh
#if DEBUG
            //string query = "select distinct dnord#, dnjob, dnpart from cmsdat.cjobh where dnord#=280893 order by dnord#";
            string query = "select distinct dnord#, dnjob, dnpart from cmsdat.cjobh order by dnord#";
#else
            string query = "select distinct dnord#, dnjob, dnpart from cmsdat.cjobh order by dnord#";
#endif
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader[0]);
                string desc = reader[2].ToString().Trim();
                if (!desc.Contains("MISC") && !desc.Contains("REWORK"))
                {
                    Piece piece = new Piece(reader[1].ToString().Trim(), desc, GetPieceType(desc), Convert.ToInt32(reader[0]));
                    pieceList.Add(piece);
                    // if a new die
                    if (!dieMap.ContainsKey(soNum))
                    {
                        Die die = new Die(soNum);
                        die.pieceList.Add(piece);
                        dieMap.Add(soNum, die);
                    }
                    // if exsiting die
                    else
                    {
                        dieMap[soNum].pieceList.Add(piece);
                    }
                    if (soNum < minimumSO && soNum > 200000)
                    {
                        minimumSO = soNum;
                    }
                    if (soNum > maximumSO)
                    {
                        maximumSO = soNum;
                    }
                }
            }
            reader.Close();
        }


        // find if a die is a hollow die and which part is parent
        public void ProcessDie()
        {
            foreach (Die die in dieMap.Values)
            {
                die.DetermineIsHollow();
                die.FindParentIfHollow(database);
            }
        }

        // get decade style piece type
        public char GetPieceType(string part)
        {
            if (part.Contains("BA"))
            {
                return 'B';
            }
            else if (part.Contains("BO"))
            {
                return 'O';
            }
            else if (part.Contains("FD"))
            {
                return 'F';
            }
            else if (part.Contains("RI"))
            {
                return 'R';
            }
            else if (part.Contains("SB"))
            {
                return 'S';
            }
            else if (part.Contains("SD") || part.Contains("PL"))
            {
                return 'P';
            }
            else if (part.Contains("MA"))
            {
                return 'M';
            }
            else if (part.Contains("HD"))
            {
                return 'G';
            }
            else
            {
                throw new Exception("Invalid part: " + part);
            }
        }

        // fill sequences with standard time if no sls time and
        // a. 20/30 runtime is less than 15min
        // b. 210 runtime is less than 15min
        // c. 780 runtime is less than 15min
        // d. 230 runtime is less than 15min
        public void FillWithStdTime()
        {
            foreach (Piece piece in pieceList)
            {
                foreach (Seq seq in piece.seqList)
                {
                    if (20 == seq.seqNum || 30 == seq.seqNum || 780 == seq.seqNum || 210 == seq.seqNum || 230 == seq.seqNum)
                    {
                        foreach (RunTime runtime in seq.runtimeList)
                        {
                            if (runtime.taskList.Count > 0 && runtime.runTime < 0.25 && !runtime.hasSolarsoftTime)
                            {
                                runtime.runTime = runtime.stdTime;
                            }
                        }
                    }
                }
            }
        }

        // ask solarsoft to process batch file
        public void RequestProcessBatchFile()
        {
            if (!File.Exists(batchSubmitProgram))
            {
                throw new Exception("Could not find batch submit program at " + batchSubmitProgram);
            }
            System.Diagnostics.Process shell = new System.Diagnostics.Process();
            shell.StartInfo = new System.Diagnostics.ProcessStartInfo(batchSubmitProgram);
            shell.Start();
            shell.WaitForExit();
            switch (shell.ExitCode)
            {
                case -1:
                    throw new Exception("CREATE_SYSTEM_FAIL");
                case -2:
                    throw new Exception("SET_USER_ID_FAIL");
                case -3:
                    throw new Exception("SET_PASSWORD_FAIL");
                case -4:
                    throw new Exception("START_SYSTEM_FAIL");
                case -5:
                    throw new Exception("RUN_ADDLIBLE_CMSPD_FAILD");
                case -6:
                    throw new Exception("RUN_ADDLIBLE_CMSSYSTEM_FAILD");
                case -7:
                    throw new Exception("RUN_ADDLIBLE_CMSMAIN_FAILD");
                case -8:
                    throw new Exception("RUN_ADDLIBLE_CMSINV_FAILD");
                case -9:
                    throw new Exception("RUN_ADDLIBLE_CMSNOE_FAILD");
                case -10:
                    throw new Exception("RUN_CHGCURLIB_CMSDAT_FAILD");
                case -11:
                    throw new Exception("RUN_CHGPLNT_001_FAILD");
                case -12:
                    throw new Exception("RUN_BATCH_COMMAND_FAILD");
                case -13:
                    throw new Exception("STOP_SYSTEM_FAILD");
                case -14:
                    throw new Exception("DELETE_SYSTEM_FAILD");
            }
        }

        // adjust records for 180/190 and scarp
        public void AjustRecords()
        {
            // adjust mill side
            foreach (Piece piece in pieceList)
            {
                for (int i = 0; i < piece.seqList.Count; i++)
                {
                    Seq seq = piece.seqList[i];
                    if (180 == seq.seqNum)
                    {
                        char firstSide = '\0';
                        string query = "select top 1 subpart from dbo.d_task where ordernumber=" + seq.soNum.ToString() + " and part='" + seq.type + "' and (task='N1' or task='N0') order by tasktime";
                        ExcoODBC odbcConnection = ExcoODBC.Instance;
                        odbcConnection.Open(Database.DECADE_MARKHAM);
                        OdbcDataReader reader = odbcConnection.RunQuery(query);
                        if (reader.Read())
                        {
                            firstSide = Convert.ToChar(reader[0]);
                        }
                        reader.Close();
                        // adjust standard time
                        if (predictedRuntimeMap.ContainsKey(piece.so))
                        {
                            if (predictedRuntimeMap[piece.so].ContainsKey(piece.type.ToString() + firstSide.ToString()))
                            {
                                foreach (RunTime runtime in seq.runtimeList)
                                {
                                    runtime.stdTime = predictedRuntimeMap[piece.so][piece.type.ToString() + firstSide.ToString()];
                                    if (predictedRuntimeMap[piece.so].ContainsKey("TB") && 'M' == piece.type && 'B' == firstSide)
                                    {
                                        runtime.stdTime += predictedRuntimeMap[piece.so]["TB"];
                                    }
                                }
                            }
                            char secondSide = '\0';
                            if ('F' == firstSide)
                            {
                                secondSide = 'B';
                            }
                            else if ('B' == firstSide)
                            {
                                secondSide = 'F';
                            }
                            if (predictedRuntimeMap[piece.so].ContainsKey(piece.type.ToString() + secondSide.ToString()))
                            {
                                foreach (RunTime runtime in (piece.seqList[i + 1]).runtimeList)
                                {
                                    runtime.stdTime = predictedRuntimeMap[piece.so][piece.type.ToString() + secondSide.ToString()];
                                    if (predictedRuntimeMap[piece.so].ContainsKey("TB") && 'M' == piece.type && 'B' == secondSide)
                                    {
                                        runtime.stdTime += predictedRuntimeMap[piece.so]["TB"];
                                    }
                                }
                            }
                        }
                        if (seq.taskList.Count > 0)
                        {
                            for (int j = 0; j < seq.taskList.Count; j++)
                            {
                                Task task = seq.taskList[j];
                                // move to 190
                                if (firstSide != task.side)
                                {
                                    piece.seqList[i + 1].taskList.Add(task);
                                    piece.seqList[i + 1].runtimeList[0].taskList.Add(task);
                                    seq.taskList.RemoveAt(j);
                                    j--;
                                }
                                // move to 180
                                else
                                {
                                    seq.runtimeList[0].taskList.Add(task);
                                }
                            }
                            // add stop if 180 doesn't have a stop
                            if (seq.taskList.Count > 0 && seq.taskList[seq.taskList.Count - 1].isStart)
                            {
                                DateTime taskTime = seq.taskList[seq.taskList.Count - 1].taskTime;
                                foreach (Task task in piece.seqList[i + 1].runtimeList[0].taskList)
                                {
                                    if (task.taskTime > taskTime)
                                    {
                                        // add a system generated stop
                                        Task stop = new Task();
                                        stop.isSystemGenerated = true;
                                        stop.isStop = true;
                                        stop.taskTime = task.taskTime;
                                        seq.taskList.Add(stop);
                                        seq.runtimeList[0].taskList.Add(stop);
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
            // assign tasks to runtime and adjust tasks based on scarp time
            foreach (Piece piece in pieceList)
            {
                piece.AssignTasksToRuntime();
                if (scrapMap.ContainsKey(piece.wo))
                {
                    piece.AdjustScrap(scrapMap[piece.wo]);
                }
            }
        }

        // generate cache content for batch update
        public void GenerateBatchCache(List<RunTime> runtimeList)
        {
            foreach (RunTime runtime in runtimeList)
            {
                if (runtime.runTime > 0.00001 || runtime.actualTime > 0.0001)
                {
                    try
                    {
                        // process station and resource
                        runtime.ProcessStationAndResource();
                        // process employee number
                        runtime.ProcessEmployeeNumber(database);
                        if (!cacheMap.ContainsKey(runtime.resCode))
                        {
                            cacheMap.Add(runtime.resCode, runtime.GenerateBatchString(database));
                        }
                        else
                        {
                            cacheMap[runtime.resCode].AddRange(runtime.GenerateBatchString(database));
                        }
                    }
                    catch (Exception e)
                    {
                        throw new Exception(e.Message + "so: " + runtime.soNum.ToString() + " wo: " + runtime.woNum + " seq: " + runtime.seqNum);
                    }
                }
            }
        }
    }
}