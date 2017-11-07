using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace BatchUpdate
{
    // this class represents a single runtime event
    public class RunTime
    {
        // run time
        public double runTime = -0.000001;
        // actual time after adjustment
        public double actualTime = 0.0;
        // start time
        public DateTime startTime = new DateTime();
        // stop time
        public DateTime stopTime = new DateTime();
        // sequence number
        public int seqNum = 0;
        // piece type
        public char type = new char();
        // part description
        public string part = string.Empty;
        // work order
        public string woNum = string.Empty;
        // employee number
        public int empNum = 0;
        // department code
        public string depCode = string.Empty;
        // resource code
        public string resCode = string.Empty;
        // shop order number
        public int soNum = 0;
        // standard time
        public double stdTime = 0.0;
        // solarsoft time
        public double slsTime = 0.0;
        // has Solarsoft time
        public bool hasSolarsoftTime = false;
        // tasks belonging to this sequence
        public List<Task> taskList = new List<Task>();
        // indicate if using stanadard time
        public bool isUsingStdTime = false;
        // quantity required
        public int quantity = 0;
        // solarsoft updated date
        public DateTime slsDate = new DateTime();

        public void ProcessEmployeeNumber(Database database)
        {
            if (0 == empNum)
            {
                empNum = 99999;
            }
            else
            {
                string query = "select * from cmsdat.resrp where acplnt=1 and acresc=" + empNum.ToString() + " and acdept='001" + depCode + "' order by acresc";
                ExcoODBC odbcConnection = ExcoODBC.Instance;
                odbcConnection.Open(database);
                OdbcDataReader reader = odbcConnection.RunQuery(query);
                if (!reader.Read())
                {
                    empNum = 99999;
                }
                reader.Close();
            }
        }

        // determine if this is an exception
        public bool IsException()
        {
            if (actualTime < 0.000001)
            {
                return false;
            }
            // more than 3 x std hour
            else if (actualTime >= 0.000001 && actualTime + slsTime > stdTime * 3.0 && taskList.Count > 0)
            {
                return true;
            }
            // less than 0.05 hour
            else if (actualTime + slsTime < 0.05 && taskList.Count > 0 && !hasSolarsoftTime)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void ProcessByResCode()
        {
            if (0 == resCode.CompareTo("LA01") || 0 == resCode.CompareTo("LA06"))
            {
                resCode = "L6";
            }
            else if (0 == resCode.CompareTo("LA08"))
            {
                resCode = "L8";
            }
            else if (0 == resCode.CompareTo("LA09"))
            {
                resCode = "L10";
            }
            else if (0 == resCode.CompareTo("MC1") || 0 == resCode.CompareTo("MC4") || 0 == resCode.CompareTo("MC6") || 0 == resCode.CompareTo("MC9") || 0 == resCode.CompareTo("MC20") || 0 == resCode.CompareTo("MC21") || 0 == resCode.CompareTo("MC25") || 0 == resCode.CompareTo("MC26") || 0 == resCode.CompareTo("MC27") || 0 == resCode.CompareTo("MC28") || 0 == resCode.CompareTo("MC29") || 0 == resCode.CompareTo("MC30") || 0 == resCode.CompareTo("MC31") || 0 == resCode.CompareTo("MC32") || 0 == resCode.CompareTo("MC33") || 0 == resCode.CompareTo("MC34") || 0 == resCode.CompareTo("MC35") || 0 == resCode.CompareTo("MC36") || 0 == resCode.CompareTo("MC38") || 0 == resCode.CompareTo("MC39") || 0 == resCode.CompareTo("MC40") || 0 == resCode.CompareTo("MC41"))
            {
                depCode = "M1";
            }
            else if (resCode.Contains("NK") || resCode.Contains("NM") || resCode.Contains("NN") || resCode.Contains("NP"))
            {
                depCode = "M1";
                resCode = "MC" + resCode.Substring(0, 2);
            }
            else if (0 == resCode.CompareTo("MC22") || 0 == resCode.CompareTo("MC23") || 0 == resCode.CompareTo("CG23") || 0 == resCode.CompareTo("MC24"))
            {
                depCode = "M2";
            }
        }

        public void ProcessBySeqNum()
        {
            if (10 == seqNum || 20 == seqNum)
            {
                depCode = "CD";
                resCode = "EMPL";
            }
            else if (30 == seqNum)
            {
                depCode = "CM";
                resCode = "EMPL";
            }
            else if (100 == seqNum)
            {
                depCode = "SW";
                resCode = "AS1";
            }
            else if (160 == seqNum)
            {
                if (0 == depCode.Trim().Length)
                {
                    depCode = "L1";
                }
                if (0 == resCode.Trim().Length)
                {
                    resCode = "L8";
                }
            }
            else if (180 == seqNum || 190 == seqNum)
            {
                if (0 == depCode.Trim().Length)
                {
                    depCode = "M1";
                }
                if (0 == resCode.Trim().Length)
                {
                    resCode = "MC1";
                }
            }
            else if (173 == seqNum)
            {
                depCode = "L1";
                resCode = "EMPL";
            }
            else if (210 == seqNum)
            {
                depCode = "MM";
                resCode = "MM1";
            }
            else if (230 == seqNum)
            {
                depCode = "DU";
                resCode = "EMPL";
            }
            else if (240 == seqNum)
            {
                depCode = "DS";
                resCode = "DP2";
            }
            else if (310 == seqNum)
            {
                depCode = "HT";
                resCode = "RKLF";
            }
            else if (320 == seqNum)
            {
                depCode = "HT";
                resCode = "FB1";
            }
            else if (330 == seqNum)
            {
                depCode = "HT";
                resCode = "FB3";
            }
            else if (340 == seqNum || 350 == seqNum || 360 == seqNum)
            {
                depCode = "HT";
                resCode = "CY6";
            }
            else if (410 == seqNum)
            {
                depCode = "L2";
                resCode = "L7";
            }
            else if (420 == seqNum || 500 == seqNum)
            {
                depCode = "MM";
                resCode = "MM4";
            }
            else if (430 == seqNum)
            {
                if ('F' == type)
                {
                    depCode = "L2";
                    resCode = "L7";
                }
                else
                {
                    depCode = "M2";
                    if (0 == resCode.Trim().Length)
                    {
                        resCode = "MC22";
                    }
                }
            }
            else if (440 == seqNum)
            {
                depCode = "LM";
                resCode = "ML3";
            }
            else if (460 == seqNum)
            {
                depCode = "ED";
                resCode = "S1";
            }
            else if (470 == seqNum)
            {
                depCode = "WI";
                resCode = "WE3";
            }
            else if (490 == seqNum)
            {
                depCode = "M2";
                resCode = "MC11";
            }
            else if (500 == seqNum)
            {
                depCode = "MM";
                resCode = "MM4";
            }
            else if (770 == seqNum)
            {
                depCode = "L2";
                resCode = "L7";
            }
            else if (780 == seqNum || 800 == seqNum)
            {
                depCode = "IN";
                resCode = "EMPL";
            }
            else if (790 == seqNum)
            {
                depCode = "NI";
                resCode = "N1";
            }
        }

        public void ProcessStationAndResource()
        {
            ProcessByResCode();
            ProcessBySeqNum();
        }

        // generate batch string
        // use startTime to get period information
        public List<string> GenerateBatchString(Database database)
        {
            List<string> batchList = new List<string>();
            if (quantity > 0)
            {
                if (100 != seqNum)
                {
                    batchList.AddRange(GenerateUpdateBatch());
                }
            }
            else
            {
                if (100 == seqNum)
                {
                    batchList.AddRange(GenerateMaterialBatch(database));
                }
                else
                {
                    batchList.AddRange(GenerateProductionBatch());
                }
            }
            return batchList;
        }

        // generate batch string to update existing time
        public List<string> GenerateUpdateBatch()
        {
            List<string> batch = new List<string>();
            // add detail record
            DetailRecord detail = new DetailRecord();
            detail.department.SetString(depCode);
            detail.resource.SetString(resCode);
            detail.part.SetString(part);
            detail.workOrder.SetString(woNum);
            detail.seq.SetString(seqNum.ToString("D3"));
            if (actualTime > 99.0)
            {
                actualTime = 99.0;
            }
            string hours = ((int)actualTime).ToString("D2");
            string minutes = (((int)(actualTime * 100.0) % 100) * 60 / 100).ToString("D2");
            detail.totalMachTime.SetString(hours + minutes);
            batch.Add(detail.BuildString());
            return batch;
        }


        // generate material batch string
        public List<string> GenerateMaterialBatch(Database database)
        {
            List<string> batch = new List<string>();
            // add detail record
            DetailRecord detail = new DetailRecord();
            detail.department.SetString(depCode);
            detail.resource.SetString(resCode);
            detail.part.SetString(part);
            detail.workOrder.SetString(woNum);
            detail.seq.SetString(seqNum.ToString("D3"));
            string hours = ((int)actualTime).ToString("D2");
            string minutes = (((int)(actualTime * 100.0) % 100) * 60 / 100).ToString("D2");
            detail.totalMachTime.SetString(hours + minutes);
            batch.Add(detail.BuildString());
            // add production record
            ProductionRecord product = new ProductionRecord();
            product.part.SetString(part);
            product.quaGood.SetString("0000000001");
            product.units.SetString("EA");
            product.empDep.SetString(depCode);
            product.empNum.SetString((empNum % 100000).ToString());
            product.noBackFlush.SetString("Y");
            batch.Add(product.BuildString());
            // add material steel record
            MaterialRecord matSteel = new MaterialRecord();
            string query = "select efmtlp, efqppc from cmsdat.cjobdm where efjob#='" + woNum + "'";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(database);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            if (reader.Read())
            {
                matSteel.part.SetString(reader[0].ToString().Trim());
                matSteel.quantity.SetString(Convert.ToInt32((Convert.ToDouble(reader[1]) * 100000.0)).ToString("D15"));
            }
            reader.Close();
            matSteel.stoRoom.SetString("STL");
            matSteel.required.SetString("R");
            matSteel.backFlush.SetString("Y");
            matSteel.matScr.SetString("N");
            matSteel.units.SetString("IN");
            batch.Add(matSteel.BuildString());
            // add material production record
            query = "select * from cmsdat.cjobdr where edjob#='" + woNum + "' and edseq#=30";
            reader = odbcConnection.RunQuery(query);
            if (reader.Read())
            {
                MaterialRecord matProd = new MaterialRecord();
                matProd.part.SetString(part);
                matProd.quantity.SetString("000000000100000");
                matProd.stoRoom.SetString("PRD");
                matProd.required.SetString("R");
                matProd.backFlush.SetString("Y");
                matProd.matScr.SetString("N");
                matProd.units.SetString("EA");
                matProd.seqNum.SetString("030");
                batch.Add(matProd.BuildString());
            }
            reader.Close();
            return batch;
        }

        // generate production batch string
        public List<string> GenerateProductionBatch()
        {
            List<string> batch = new List<string>();
            // add detail record
            DetailRecord detail = new DetailRecord();
            detail.department.SetString(depCode);
            detail.resource.SetString(resCode);
            detail.part.SetString(part);
            detail.workOrder.SetString(woNum);
            detail.seq.SetString(seqNum.ToString("D3"));
            if (actualTime > 99.0)
            {
                actualTime = 99.0;
            }
            string hours = ((int)actualTime).ToString("D2");
            string minutes = (((int)(actualTime * 100.0) % 100) * 60 / 100).ToString("D2");
            detail.totalMachTime.SetString(hours + minutes);
            batch.Add(detail.BuildString());
            // add production record
            ProductionRecord product = new ProductionRecord();
            product.part.SetString(part);
            product.quaGood.SetString("0000000001");
            product.units.SetString("EA");
            product.empDep.SetString(depCode);
            product.empNum.SetString((empNum % 100000).ToString());
            product.reversing.SetString("N");
            batch.Add(product.BuildString());
            return batch;
        }

        // calculate run time
        public void CalcualteRunTime(Database database, DateTime date)
        {
            // write default runtime
            if (taskList.Count > 0)
            {
                empNum = taskList[0].empNum;
                resCode = taskList[0].station;
                switch (seqNum)
                {
                    // use standard time
                    case 10:
                    case 100:
                    case 173:
                    case 240:
                    case 310:
                    case 410:
                    case 420:
                    case 430:
                    case 440:
                    case 490:
                    case 500:
                    case 770:
                    case 790:
                        GetStandardCost();
                        break;
                    // calculate run time
                    case 160:
                    case 180:
                    case 190:
                    case 210:
                    case 230:
                    case 780:
                        CalculateStartStop(database);
                        break;
                    // get run time from cmsdat.excotask
                    case 460:
                    case 470:
                        startTime = taskList[0].taskTime;
                        foreach (Task task in taskList)
                        {
                            runTime += task.runTime;
                        }
                        break;
                }
            }
            // get heat number if no saw
            else if (100 == seqNum && !hasSolarsoftTime)
            {
                string query = "select cuttime from dbo.d_steel where ordernumber=" + soNum.ToString() + " and part='" + type + "' and cuttime<='" + date.ToString("yyyy-MM-dd 23:59:59") + "'order by cuttime desc";
                ExcoODBC odbcConnection = ExcoODBC.Instance;
                odbcConnection.Open(Database.DECADE_MARKHAM);
                OdbcDataReader reader = odbcConnection.RunQuery(query);
                if (reader.Read())
                {
                    Task task = new Task();
                    task.isSystemGenerated = true;
                    task.taskCode = "SW";
                    task.taskTime = Convert.ToDateTime(reader["cuttime"]);
                    taskList.Add(task);
                    runTime = stdTime;
                    startTime = task.taskTime;
                }
                reader.Close();
            }
        }

        // eliminate last task if it is a start
        public void GetStandardCost()
        {
            isUsingStdTime = true;
            startTime = taskList
[0].taskTime;
            DateTime time = new DateTime();
            foreach (Task task in taskList)
            {
                // here if tasks happen within standard run time we only count once
                if ((task.taskTime - time).TotalHours > stdTime)
                {
                    runTime += stdTime;
                    time = task.taskTime;
                }
            }
        }

        // eliminate last task if it is a start
        public void DeleteLastTaskIfStart()
        {
            for (int i = taskList.Count - 1; i >= 0; i--)
            {
                if (taskList[i].isStart)
                {
                    taskList.RemoveAt(i);
                    DeleteLastTaskIfStart();
                    i = taskList.Count;
                }
                else
                {
                    break;
                }
            }
        }

        // calculate run time by using start/stop tags
        // if no start, search for the last activity at the same machine as the start
        // if see multiple starts, use last one as start
        public void CalculateStartStop(Database database)
        {
            DeleteLastTaskIfStart();
            DateTime start = new DateTime();
            DateTime stop = new DateTime();
            for (int i = 0; i < taskList.Count; i++)
            {
                Task task = taskList[i];
                if (Math.Abs((task.taskTime - start).TotalMilliseconds) < 0.01 || Math.Abs((task.taskTime - stop).TotalMilliseconds) < 0.01)
                {
                    continue;
                }
                if (task.isStart)
                {
                    if (1 == start.Year)
                    {
                        startTime = task.taskTime;
                    }
                    start = task.taskTime;
                }
                else if (task.isStop)
                {
                    if (start > stop)
                    {
                        runTime += ElapsedHours(start, task.taskTime);
                        stop = task.taskTime;
                        stopTime = stop;
                    }
                    else if (1 == start.Year)
                    {
                        string query = "select top 1 tasktime from dbo.d_task where tasktime<'" + task.taskTime.ToString("yyyy-MM-dd HH:mm:ss") + "' and station='" + task.station + "' order by tasktime desc";
                        ExcoODBC odbcConnection = ExcoODBC.Instance;
                        odbcConnection.Open(Database.DECADE_MARKHAM);
                        OdbcDataReader reader = odbcConnection.RunQuery(query);
                        if (reader.Read())
                        {
                            DateTime lastTime = Convert.ToDateTime(reader[0]);
                            runTime += ElapsedHours(lastTime, task.taskTime);
                            start = Convert.ToDateTime(lastTime);
                            if (1 == startTime.Year)
                            {
                                startTime = start;
                            }
                            stop = task.taskTime;
                            stopTime = stop;
                        }
                        reader.Close();
                    }
                }
            }
        }

        // calculate elapsed hours
        public double ElapsedHours(DateTime start, DateTime stop)
        {
            TimeSpan elapsedTime = stop - start;
            return elapsedTime.TotalMinutes / 60.0;
        }

        // deep copy
        public RunTime DeepCopy()
        {
            RunTime runtime = new RunTime();
            runtime.woNum = woNum;
            runtime.stopTime = stopTime;
            runtime.stdTime = stdTime;
            runtime.startTime = startTime;
            runtime.soNum = soNum;
            runtime.slsTime = slsTime;
            runtime.seqNum = seqNum;
            runtime.runTime = runTime;
            runtime.actualTime = actualTime;
            runtime.resCode = resCode;
            runtime.part = part;
            runtime.isUsingStdTime = isUsingStdTime;
            runtime.hasSolarsoftTime = hasSolarsoftTime;
            runtime.empNum = empNum;
            runtime.depCode = depCode;
            runtime.type = type;
            runtime.slsDate = slsDate;
            return runtime;
        }
    }
}