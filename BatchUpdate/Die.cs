using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace BatchUpdate
{
    public class Die
    {
        // shop order number
        public int so = 0;
        // piece list (only show pieces in current job list)
        public List<Piece> pieceList = new List<Piece>();
        // index of parent piece in piece list (hollow die only)
        public int parentIndex = -1;
        // flag of hollow die
        public bool isHollow = false;

        // get piece list
        public Die() { }
        public Die(int soNum)
        {
            this.so = soNum;
        }

        // find parent piece if this is a hollow die
        // parent piece means:
        // 1. 7 digit work order
        // 2. part description contains "HD "
        // 3. last sequence is 800
        // 4. has sub parts in cjobh or hjobh
        public void FindParentIfHollow(Database database)
        {
            if (isHollow)
            {
                for (int i = 0; i < pieceList.Count; i++)
                {
                    if (7 == pieceList[i].wo.Length && pieceList[i].part.Contains("HD ") && pieceList[i].seqList.Count > 0 && 800 == pieceList[i].seqList[pieceList[i].seqList.Count - 1].seqNum)
                    {
                        if (1 == pieceList.Count)
                        {
                            string query = "select * from cmsdat.hjobh where dnord#=" + so.ToString();
                            ExcoODBC odbcConnection = ExcoODBC.Instance;
                            odbcConnection.Open(database);
                            OdbcDataReader reader = odbcConnection.RunQuery(query);
                            if (!reader.Read())
                            {
                                reader.Close();
                                break;
                            }
                            reader.Close();
                        }
                        parentIndex = i;
                        break;
                    }
                }
            }
        }

        // determine if this die is a hollow die
        // a hollow die means if any piece has a "HD " string
        public void DetermineIsHollow()
        {
            foreach (Piece piece in pieceList)
            {
                if (piece.part.Contains("HD "))
                {
                    isHollow = true;
                    break;
                }
            }
        }

        // process sales return in seq 20
        // if a sales return happens after a design start, then set it as design stop
        // if a sales return happens before a design stop, then set it as design start
        // if only sees sales return, delete all tasks
        public void ProcessSalesReturn(List<Task> taskList)
        {
            // if only sales return, clear it
            bool isAllSX = true;
            for (int i = 0; i < taskList.Count; i++)
            {
                if (!taskList[i].taskCode.Contains("SX"))
                {
                    isAllSX = false;
                    break;
                }
                else
                {
                    taskList.RemoveAt(i);
                    i--;
                }
            }
            if (!isAllSX)
            {
                Task prevTask = new Task();
                for (int i = 0; i < taskList.Count; i++)
                {
                    if (taskList[i].taskCode.Contains("SX") && prevTask.taskCode.Contains("DI") && !prevTask.isSystemGenerated)
                    {
                        Task newTask = new Task();
                        newTask.isSystemGenerated = true;
                        newTask.taskCode = "DD";
                        newTask.taskTime = taskList[i].taskTime;
                        newTask.isStop = true;
                        taskList.Insert(i, newTask);
                    }
                    else if (prevTask.taskCode.Contains("SX") && taskList[i].taskCode.Contains("DD") && !prevTask.isSystemGenerated)
                    {
                        Task newTask = new Task();
                        newTask.isSystemGenerated = true;
                        newTask.taskCode = "DI";
                        newTask.taskTime = prevTask.taskTime;
                        newTask.isStart = true;
                        taskList.Insert(i, newTask);
                    }
                    prevTask = taskList[i];
                }
            }
            else
            {
                taskList.Clear();
            }
        }

        // calculate overall run time for an order, then distribute into each sub piece
        public void GetEvenTime(int seqNum, Dictionary<string, Dictionary<int, SeqTemplate>> seqCJOBHMap, Dictionary<string, SeqTemplate> seqHJOBHMap, Database database)
        {
            // process sales return for sequence 20
            if (20 == seqNum)
            {
                foreach (Piece piece in pieceList)
                {
                    foreach (Seq seq in piece.seqList)
                    {
                        if (20 == seqNum)
                        {
                            ProcessSalesReturn(seq.taskList);
                        }
                    }
                }
            }

            bool needProcess = false;
            foreach (Piece piece in pieceList)
            {
                foreach (Seq seq in piece.seqList)
                {
                    if (seqNum == seq.seqNum && seq.taskList.Count > 0)
                    {
                        needProcess = true;
                        break;
                    }
                }
                if (needProcess)
                {
                    break;
                }
            }
            if (needProcess)
            {
                int seqCount = 0;
                foreach (Piece piece in pieceList)
                {
                    if (seqHJOBHMap.ContainsKey(piece.wo))
                    {
                        seqCount++;
                    }
                    if (seqCJOBHMap[piece.wo].ContainsKey(seqNum))
                    {
                        seqCount++;
                    }
                }
                // calculate runtime
                bool seqProcessed = false;
                double seqRuntime = 0.0;
                bool hasSlsTime = false;
                DateTime startTime = new DateTime();
                DateTime stopTime = new DateTime();
                bool isValidRuntime = true;
                foreach (Piece piece in pieceList)
                {
                    foreach (Seq seq in piece.seqList)
                    {
                        if (seqNum == seq.seqNum && seq.taskList.Count > 0)
                        {
                            if (seqProcessed)
                            {
                                seq.taskList.Clear();
                            }
                            if (isValidRuntime)
                            {
                                foreach (RunTime runtime in seq.runtimeList)
                                {
                                    if (seqProcessed)
                                    {
                                        runtime.taskList.Clear();
                                        runtime.runTime = seqRuntime;
                                        runtime.startTime = startTime;
                                        runtime.stopTime = stopTime;
                                        runtime.hasSolarsoftTime = hasSlsTime;
                                        Task task = new Task();
                                        task.taskTime = startTime;
                                        task.isSystemGenerated = true;
                                        runtime.taskList.Add(task);
                                    }
                                    else if (runtime.taskList.Count > 0)
                                    {
                                        runtime.CalculateStartStop(database);
                                        seqProcessed = true;
                                        if (0 == runtime.taskList.Count)
                                        {
                                            isValidRuntime = false;
                                        }
                                        else
                                        {
                                            runtime.runTime = runtime.runTime / (double)seqCount;
                                            seqRuntime = runtime.runTime;
                                            startTime = runtime.startTime;
                                            stopTime = runtime.stopTime;
                                            hasSlsTime = runtime.hasSolarsoftTime;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}