using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace BatchUpdate
{
    // sequences are generated from record classs
    public class Seq
    {
        // sequence number
        public int seqNum = 0;
        // standard time
        public double stdTime = 0.0;
        // run time
        public List<RunTime> runtimeList = new List<RunTime>();
        // task lsit
        public List<Task> taskList = new List<Task>();
        // part description
        public string part = string.Empty;
        // work order
        public string woNum = string.Empty;
        // shop order
        public int soNum = 0;
        // piece type
        public char type = new char();

        // constructor
        public Seq() { }
        public Seq(int seqNum, double stdTime, char type, string part, string wo, int so)
        {
            this.seqNum = seqNum;
            this.stdTime = stdTime;
            this.part = part;
            this.woNum = wo;
            this.soNum = so;
            this.type = type;
            runtimeList.Add(new RunTime());
        }

        // get sequence information
        public void GetSeqInfo(Database database, Dictionary<int, List<Task>> sparkMap, Dictionary<int, List<Task>> wireMap, DateTime date)
        {
            // get tasks
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            string query;
            OdbcDataReader reader;
            if (10 == seqNum || 20 == seqNum || 30 == seqNum || 100 == seqNum || 160 == seqNum || 173 == seqNum || 180 == seqNum || 210 == seqNum || 230 == seqNum || 240 == seqNum || 310 == seqNum || 780 == seqNum || 790 == seqNum)
            {
                query = "select distinct employeenumber, task, part, subpart, station, tasktime, id from dbo.d_task where (";
                switch (seqNum)
                {
                    case 10:
                        query += "task='SH'";
                        break;
                    case 20:
                        query += "task='DI' or task='DD' or task='SX'";
                        break;
                    case 30:
                        query += "task='CI' or task='CO'";
                        break;
                    case 100:
                        query += "task='SW'";
                        break;
                    case 160:
                        query += "task='L1' or task='L0'";
                        break;
                    case 173:
                        query += "task='LS'";
                        break;
                    // here we put all mill tasks into 180, then seperate into 180/190 in Process.AjustRecords()
                    case 180:
                        query += "task='N1' or task='N0'";
                        break;
                    case 210:
                        query += "task='MM' or task='M0'";
                        break;
                    case 230:
                        query += "task='U1' or task='U0'";
                        break;
                    case 240:
                        query += "task='DS'";
                        break;
                    case 310:
                        query += "task='RK'";
                        break;
                    case 780:
                        query += "task='IB' or task='IF' or task='IC'";
                        break;
                    case 790:
                        query += "task='NS'";
                        break;
                }
                query += ") and flags=0 and ordernumber=" + soNum.ToString() + " and tasktime<'" + date.ToString("yyyy-MM-dd 23:59:59") + "'";
                if (seqNum < 90)
                {
                    query += " and part='G'";
                }
                else
                {
                    if ('M' == type && (180 == seqNum || 190 == seqNum))
                    {
                        query += " and (part='" + type + "' or part='T')";
                    }
                    else if (780 == seqNum)
                    {
                        query += " and (part='" + type + "' or part='G')";
                    }
                    else
                    {
                        query += " and part='" + type + "'";
                    }
                }
                query += " order by tasktime";
                odbcConnection.Open(Database.DECADE_MARKHAM);
                reader = odbcConnection.RunQuery(query);
                while (reader.Read())
                {
                    int empNum = Convert.ToInt32(reader[0]);
                    string taskCode = reader[1].ToString().Trim();
                    if (reader[2].ToString().Trim().Length < 1)
                    {
                        continue;
                    }
                    char part = reader[2].ToString().Trim()[0];
                    char subPart = ' ';
                    if (reader[3].ToString().Trim().Length > 0)
                    {
                        subPart = reader[3].ToString().Trim()[0];
                    }
                    string station = reader[4].ToString().Trim();
                    DateTime time = Convert.ToDateTime(reader[5]);
                    Task task = new Task(soNum, empNum, part, subPart, taskCode, time, station, seqNum);
                    task.decadeID = Convert.ToInt32(reader[6]);
                    task.DetermineStartStop();
                    taskList.Add(task);
                }
                reader.Close();
            }
            // get tasks spark
            else if (460 == seqNum)
            {
                if (sparkMap.ContainsKey(soNum))
                {
                    taskList.AddRange(sparkMap[soNum]);
                }
                else if (sparkMap.ContainsKey(soNum - 200000))
                {
                    taskList.AddRange(sparkMap[soNum - 200000]);
                }

            }
            // get tasks wire
            else if (470 == seqNum)
            {
                if (wireMap.ContainsKey(soNum))
                {
                    taskList.AddRange(wireMap[soNum]);
                }
                else if (wireMap.ContainsKey(soNum - 200000))
                {
                    taskList.AddRange(wireMap[soNum - 200000]);
                }
            }
            // sort
            taskList.Sort(CompareTask);
        }

        // task sort by task time asc
        public static int CompareTask(Task a, Task b)
        {
            if (a.taskTime > b.taskTime)
            {
                return 1;
            }
            else if (a.taskTime < b.taskTime)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
}