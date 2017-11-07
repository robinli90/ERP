using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace BatchUpdate
{
    public class Piece
    {
        // part description
        public string part = string.Empty;
        // work order
        public string wo = string.Empty;
        // shop order
        public int so = 0;
        // sequence list
        public List<Seq> seqList = new List<Seq>();
        // piece type
        public char type = new char();
        // flag if it's been completed
        public bool hasCompleted = false;
        // flag if it's a hollow parent need to be finished
        public bool isParentNeedFinished = false;

        // constructor
        public Piece() { }
        public Piece(string wo, string part, char type, int so)
        {
            this.part = part;
            this.type = type;
            this.wo = wo;
            this.so = so;
        }

        // get piece's info
        public void GetInfo(Database database, Dictionary<string, Dictionary<int, SeqTemplate>> seqTemplateMap, Dictionary<string, Scrap> scrapMap, Dictionary<int, List<Task>> sparkMap, Dictionary<int, List<Task>> wireMap, DateTime date)
        {
            if (!seqTemplateMap.ContainsKey(wo))
            {
                return;
            }
            Dictionary<int, SeqTemplate> seqMap = seqTemplateMap[wo];
            foreach (SeqTemplate seqTemplate in seqMap.Values)
            {
                Seq seq = new Seq(seqTemplate.seqNum, seqTemplate.runtime, type, part, wo, so);
                // get description based on sequence number
                seq.GetSeqInfo(database, sparkMap, wireMap, date);
                seq.runtimeList[0].seqNum = seq.seqNum;
                seq.runtimeList[0].part = part;
                seq.runtimeList[0].woNum = wo;
                seq.runtimeList[0].soNum = so;
                seq.runtimeList[0].type = type;
                seq.runtimeList[0].stdTime = seq.stdTime;
                seqList.Add(seq);
            }
            // check scrap
            if (scrapMap.ContainsKey(wo))
            {
                Scrap scrap = scrapMap[wo];
                foreach (Seq seq in seqList)
                {
                    if (seq.seqNum <= scrap.seq)
                    {
                        RunTime runtime = seq.runtimeList[seq.runtimeList.Count - 1].DeepCopy();
                        runtime.taskList.Clear();
                        seq.runtimeList.Add(runtime);
                    }
                }
            }
            // get solarsoft time
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            foreach (Seq seq in seqList)
            {
                if (seq.seqNum != 320 && seq.seqNum != 320 && seq.seqNum != 330 && seq.seqNum != 340 && seq.seqNum != 350 && seq.seqNum != 360)
                {
                    string query = "select fwdept, fwresc, fwtime, fwdate, fwqtyc from cmsdat.jcsta where fwjobn='" + wo + "' and fwoseq=" + seq.seqNum.ToString() + " order by fwdate";
                    OdbcDataReader reader = odbcConnection.RunQuery(query);
                    int i = 0;
                    while (reader.Read())
                    {
                        seq.runtimeList[i].quantity += Convert.ToInt32(reader["fwqtyc"]);
                        seq.runtimeList[i].seqNum = seq.seqNum;
                        seq.runtimeList[i].part = part;
                        seq.runtimeList[i].woNum = wo;
                        seq.runtimeList[i].empNum = 99999;
                        seq.runtimeList[i].depCode = reader["fwdept"].ToString().Trim().Replace("001", ""); ;
                        seq.runtimeList[i].resCode = reader["fwresc"].ToString().Trim(); ;
                        seq.runtimeList[i].soNum = so;
                        seq.runtimeList[i].stdTime = seq.stdTime;
                        seq.runtimeList[i].slsTime += Convert.ToDouble(reader["fwtime"]);
                        seq.runtimeList[i].slsDate = Convert.ToDateTime(reader["fwdate"].ToString().Trim());
                        seq.runtimeList[i].hasSolarsoftTime = true;
                        if (seq.runtimeList.Count > i + 1)
                        {
                            i++;
                        }
                    }
                    reader.Close();
                    // adjust quantity when meets scrap
                    if (seq.runtimeList.Count > 1)
                    {
                        if (seq.runtimeList.Count > 1 && seq.runtimeList[0].quantity > 1)
                        {
                            if (seq.runtimeList[1].quantity < 1)
                            {
                                seq.runtimeList[0].quantity = 1;
                                seq.runtimeList[1].quantity = 1;
                            }
                        }
                    }
                }
                else
                {
                    if (!seqTemplateMap[seq.woNum].ContainsKey(seq.seqNum))
                    {
                        throw new Exception("failed to find sequence number " + seq.seqNum.ToString() + " in sequence template " + wo);
                    }
                    seq.runtimeList[0].quantity = seqTemplateMap[seq.woNum][seq.seqNum].compQuant;
                    seq.runtimeList[0].seqNum = seq.seqNum;
                    seq.runtimeList[0].part = part;
                    seq.runtimeList[0].woNum = wo;
                    seq.runtimeList[0].soNum = so;
                    seq.runtimeList[0].stdTime = seq.stdTime;
                    if (seq.runtimeList[0].quantity > 0)
                    {
                        seq.runtimeList[0].slsTime = seq.runtimeList[0].stdTime;
                        seq.runtimeList[0].hasSolarsoftTime = true;
                    }
                }
            }
        }

        // determine if a piece's been completed
        // A piece is completed when:
        // 1. all seqneces have sls time
        // 2. no unprocessed tasks
        public bool IsCompleted()
        {
            // 1: check if all sequences are processed
            // 2: check if there is any unprocessed task
            foreach (Seq seq in seqList)
            {
                if (seq.seqNum != 320 && seq.seqNum != 330 && seq.seqNum != 340 && seq.seqNum != 350 && seq.seqNum != 360)
                {
                    foreach (RunTime runtime in seq.runtimeList)
                    {
                        if (!runtime.hasSolarsoftTime && runtime.runTime < 0.00001)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        // complete a piece by adding a task to seq 800
        public void Complete(DateTime date)
        {
            Seq seq = seqList[seqList.Count - 1];
            if (800 == seq.seqNum)
            {
                seq.runtimeList[0].startTime = date;
                seq.runtimeList[0].isUsingStdTime = true;
                seq.runtimeList[0].runTime = seq.runtimeList[0].stdTime;
                Task task = new Task();
                task.isSystemGenerated = true;
                seq.runtimeList[0].taskList.Add(task);
            }
        }

        // back flush unprocessed tasks with standard hours
        public void BackFlush(DateTime datetime, Dictionary<string, bool> assemblyFinishMap)
        {
            bool hasHeat = false;
            int lastSequenceIndex = 0;
            foreach (Seq seq in seqList)
            {
                // if has heat treat
                if (310 == seq.seqNum && (seq.runtimeList[0].hasSolarsoftTime || (seq.runtimeList[0].taskList.Count > 0 && seq.runtimeList[0].runTime > 0.0001)))
                {
                    hasHeat = true;
                    break;
                }
            }
            // if has assembly finish after heat treat (310), back flush everything
            if (hasHeat)
            {
                if (assemblyFinishMap.ContainsKey(wo))
                {
                    lastSequenceIndex = seqList.Count;
                }
            }
            // if has assembly finish or inspection finish but no heat treat, skip back flush
            else
            {
                foreach (Seq seq in seqList)
                {
                    if (assemblyFinishMap.ContainsKey(wo) || 780 == seq.seqNum && (seq.runtimeList[0].hasSolarsoftTime || (seq.runtimeList[0].taskList.Count > 0 && seq.runtimeList[0].runTime > 0.0001)))
                    {
                        return;
                    }
                }
            }
            // find last processed sequence
            if (lastSequenceIndex < seqList.Count)
            {
                for (int i = seqList.Count - 1; i >= 0; i--)
                {
                    if (seqList[i].runtimeList[0].runTime > 0.00001 || seqList[i].runtimeList[0].hasSolarsoftTime)
                    {
                        // skip some old issues
                        if ((seqList[i].seqNum != 460 && seqList[i].seqNum != 470) || (seqList[i].runtimeList[0].slsTime > 0.0001 || seqList[i].runtimeList[0].slsTime < -0.000000001 || seqList[i].runtimeList[0].slsDate > new DateTime(2013, 11, 21, 23, 59, 59)))
                        {
                            lastSequenceIndex = i;
                            break;
                        }
                    }
                }
            }
            // back flush previous sequences
            for (int i = 0; i < lastSequenceIndex; i++)
            {
                foreach (RunTime runtime in seqList[i].runtimeList)
                {
                    if ((!runtime.hasSolarsoftTime && runtime.runTime < 0.00001) || (runtime.hasSolarsoftTime && runtime.quantity < 1))
                    {
                        runtime.isUsingStdTime = true;
                        runtime.runTime = runtime.stdTime;
                        runtime.startTime = datetime;
                        Task task = new Task();
                        task.isSystemGenerated = true;
                        runtime.taskList.Add(task);
                    }
                }
            }
        }

        // assign tasks into each runtime
        public void AssignTasksToRuntime()
        {
            foreach (Seq seq in seqList)
            {
                seq.runtimeList[0].taskList = seq.taskList;
            }
        }

        // adjust tasks in runtime when there is any scarp
        public void AdjustScrap(Scrap scrap)
        {
            foreach (Seq seq in seqList)
            {
                if (seq.seqNum <= scrap.seq)
                {
                    for (int i = 0; i < seq.runtimeList[0].taskList.Count; i++)
                    {
                        if (seq.runtimeList[0].taskList[i].taskTime > scrap.time)
                        {
                            seq.runtimeList[1].taskList.Add(seq.runtimeList[0].taskList[i]);
                            seq.runtimeList[0].taskList.RemoveAt(i);
                            i--;
                        }
                    }
                    // check if quantity needs to be adjusted
                    string query;
                    if (seq.seqNum >= 320 && seq.seqNum <= 360)
                    {
                        query = "select coalesce(edcomq, 0.0) from cmsdat.cjobdr where edjob#='" + wo + "' and edseq#=" + seq.seqNum.ToString();
                    }
                    else
                    {
                        query = "select coalesce(sum(fwqtyc), 0.0) from cmsdat.jcsta where fwjobn='" + wo + "' and fwoseq=" + seq.seqNum.ToString();
                    }
                    ExcoODBC odbcConnection = ExcoODBC.Instance;
                    odbcConnection.Open(Database.CMSDAT);
                    OdbcDataReader reader = odbcConnection.RunQuery(query);
                    if (reader.Read())
                    {
                        int quantity = Convert.ToInt32(reader[0]);
                        if (0 == quantity)
                        {
                            seq.runtimeList[0].quantity = 0;
                            seq.runtimeList[1].quantity = 0;
                        }
                        else if (1 == quantity)
                        {
                            seq.runtimeList[0].quantity = 1;
                            seq.runtimeList[1].quantity = 0;
                        }
                        else
                        {
                            seq.runtimeList[0].quantity = 1;
                            seq.runtimeList[1].quantity = 1;
                            if (seq.seqNum >= 320 && seq.seqNum <= 360)
                            {
                                seq.runtimeList[0].hasSolarsoftTime = true;
                                seq.runtimeList[0].slsTime = seq.runtimeList[1].stdTime;
                                seq.runtimeList[1].hasSolarsoftTime = true;
                                seq.runtimeList[1].slsTime = seq.runtimeList[1].stdTime;
                            }
                        }
                    }
                    reader.Close();
                }
            }
        }
    }
}