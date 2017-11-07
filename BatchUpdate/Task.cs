using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace BatchUpdate
{
    // raw data from cmsdat.excotask
    public class Task
    {
        // task id in decade
        public int decadeID = 0;
        // shop order number
        public int soNum = 0;
        // employee number
        public int empNum = 0;
        // piece side
        public char side = new char();
        // piece type
        public char type = new char();
        // task code
        public string taskCode = string.Empty;
        // sequence number
        public int seqNum = 0;
        // task time
        public DateTime taskTime = new DateTime();
        // station
        public string station = string.Empty;
        // run time
        public double runTime = 0.0;
        // work order
        public string wo = string.Empty;
        // part description in solarsoft
        public string partDesc = string.Empty;
        // indicate if this is a start event
        public bool isStart = false;
        // indicate if this is a stop event
        public bool isStop = false;
        // flag of system generated task
        public bool isSystemGenerated = false;

        // constructor
        public Task() { }
        public Task(int soNum, int empNum, char type, char side, string taskCode, DateTime taskTime, string station, int seqNum)
        {
            // normal records
            this.soNum = soNum;
            this.empNum = empNum;
            this.taskCode = taskCode;
            this.taskTime = taskTime;
            this.station = station;
            this.type = type;
            this.side = side;
            this.seqNum = seqNum;
        }

        // only write not system generated tasks
        // write to cmsdat.excotask set flags to 1 for spark and emd
        // otherwise write to dbo.d_task set flags to 1
        public void MarkComplete(Database database)
        {
            if (!isSystemGenerated)
            {
                ExcoODBC odbcConnection = ExcoODBC.Instance;
                string query;
                if (460 != seqNum && 470 != seqNum)
                {
                    odbcConnection.Open(Database.DECADE_MARKHAM);
                    query = "update dbo.d_task set flags=1 where id=" + decadeID.ToString();
                    if (1 != odbcConnection.RunQueryWithoutReader(query))
                    {
                        throw new Exception("Faild to run query: " + query);
                    }
                }
                else
                {
                    odbcConnection.Open(database);
                    if (460 == seqNum)
                    {
                        query = "update cmsdat.excotask set flags=1 where sonum=" + soNum.ToString() + " and empnum=" + empNum.ToString() + " and prtcode='" + type + side + "' and task='S0' and tasktime='" + taskTime.ToString("yyyy-MM-dd HH:mm:ss") + "' and station='SPKC' and rtype='RTM'";
                    }
                    else
                    {
                        query = "update cmsdat.excotask set flags=1 where sonum=" + soNum.ToString() + " and empnum=" + empNum.ToString() + " and prtcode='" + type + side + "' and task='W0' and tasktime='" + taskTime.ToString("yyyy-MM-dd HH:mm:ss") + "' and station='WOUT' and rtype='RTM'";
                    }
                    if (1 != odbcConnection.RunQueryWithoutReader(query))
                    {
                        throw new Exception("Faild to run query: " + query);
                    }
                }
            }
        }

        // determine if this task is a start or stop
        public void DetermineStartStop()
        {
            switch (taskCode)
            {
                case "DI":
                case "CI":
                case "L1":
                case "N1":
                case "MM":
                case "U1":
                case "IB":
                    isStart = true;
                    break;
                case "DD":
                case "CO":
                case "L0":
                case "N0":
                case "M0":
                case "U0":
                case "IF":
                case "IC":
                    isStop = true;
                    break;
            }
        }
    }
}