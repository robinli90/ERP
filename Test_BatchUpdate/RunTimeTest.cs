using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BatchUpdate;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ExcoUtility;
using System.Data.Odbc;

namespace Test_BatchUpdate
{
    [TestClass]
    public class RunTimeTest
    {
        RunTime runtime = new RunTime();

        public RunTimeTest()
        {
            ResetRuntime();
        }

        public void ResetRuntime()
        {
            runtime = new RunTime();
            runtime.empNum = 10229;
            runtime.depCode = "CD";
            runtime.slsTime = 0.1;
            runtime.runTime = 0.1;
            runtime.stdTime = 0.05;
            runtime.actualTime = runtime.runTime;
            runtime.type = 'B';
        }

        [TestMethod]
        public void TestConstructor()
        {
            // test default constructor
            runtime = new RunTime();
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(0.0, runtime.actualTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            Assert.AreEqual(0, runtime.seqNum);
            Assert.AreEqual('\0', runtime.type);
            Assert.AreEqual(0, runtime.part.Length);
            Assert.AreEqual(0, runtime.woNum.Length);
            Assert.AreEqual(0, runtime.empNum);
            Assert.AreEqual(0, runtime.depCode.Length);
            Assert.AreEqual(0, runtime.resCode.Length);
            Assert.AreEqual(0, runtime.soNum);
            Assert.AreEqual(0.0, runtime.stdTime);
            Assert.AreEqual(0.0, runtime.slsTime);
            Assert.IsFalse(runtime.hasSolarsoftTime);
            Assert.AreEqual(0, runtime.taskList.Count);
            Assert.IsFalse(runtime.isUsingStdTime);
            Assert.AreEqual(0, runtime.quantity);
        }

        [TestMethod]
        public void TestDeepCopy()
        {
            runtime.woNum = "0412313";
            runtime.stopTime = DateTime.Now;
            runtime.stdTime = 0.1;
            runtime.startTime = DateTime.Now;
            runtime.soNum = 213131;
            runtime.slsTime = 1.1;
            runtime.seqNum = 55;
            runtime.runTime = 2.2;
            runtime.actualTime = 3.3;
            runtime.resCode = "AA";
            runtime.part = "HDddddd";
            runtime.isUsingStdTime = true;
            runtime.hasSolarsoftTime = true;
            runtime.empNum = 99999;
            runtime.depCode = "CCC";
            runtime.type = 'P';
            runtime.taskList.Add(new Task());
            runtime.quantity = 1;
            RunTime replica = runtime.DeepCopy();
            Assert.AreEqual(runtime.runTime, replica.runTime);
            Assert.AreEqual(runtime.actualTime, replica.actualTime);
            Assert.AreEqual(runtime.startTime, replica.startTime);
            Assert.AreEqual(runtime.stopTime, replica.stopTime);
            Assert.AreEqual(runtime.seqNum, replica.seqNum);
            Assert.AreEqual(runtime.type, replica.type);
            Assert.AreEqual(runtime.part, replica.part);
            Assert.AreEqual(runtime.woNum, replica.woNum);
            Assert.AreEqual(runtime.empNum, replica.empNum);
            Assert.AreEqual(runtime.depCode, replica.depCode);
            Assert.AreEqual(runtime.resCode, replica.resCode);
            Assert.AreEqual(runtime.soNum, replica.soNum);
            Assert.AreEqual(runtime.stdTime, replica.stdTime);
            Assert.AreEqual(runtime.slsTime, replica.slsTime);
            Assert.IsTrue(replica.hasSolarsoftTime);
            Assert.AreEqual(0, replica.taskList.Count);
            Assert.AreEqual(1, runtime.taskList.Count);
            Assert.IsTrue(replica.isUsingStdTime);
            Assert.AreEqual(0, replica.quantity);
            Assert.AreEqual(1, runtime.quantity);
            ResetRuntime();
        }

        [TestMethod]
        public void TestProcessEmployeeNumber()
        {
            // empty employee number
            runtime.empNum = 0;
            runtime.ProcessEmployeeNumber(Database.CMSDAT);
            Assert.AreEqual(99999, runtime.empNum);
            ResetRuntime();
            // invalid department code
            runtime.depCode = "X1";
            runtime.ProcessEmployeeNumber(Database.CMSDAT);
            Assert.AreEqual(99999, runtime.empNum);
            // employee number is not in the department
            ResetRuntime();
            runtime.empNum = 10000;
            runtime.ProcessEmployeeNumber(Database.CMSDAT);
            Assert.AreEqual(99999, runtime.empNum);
            // valid employee number
            ResetRuntime();
            Assert.AreEqual(10229, runtime.empNum);
        }

        [TestMethod]
        public void TestIsException()
        {
            // no task
            Assert.IsFalse(runtime.IsException());
            // has task
            runtime.taskList.Add(new Task());
            Assert.IsTrue(runtime.IsException());
            // standard time is low
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.stdTime = 0.01;
            Assert.IsTrue(runtime.IsException());
            // standard time is normal
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.stdTime = 0.1;
            Assert.IsFalse(runtime.IsException());
            // actual time is low
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.actualTime = 0.01;
            Assert.IsFalse(runtime.IsException());
            // actual time is normal
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.actualTime = 0.9;
            Assert.IsTrue(runtime.IsException());
            // sls time is low
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.slsTime = 0.01;
            Assert.IsFalse(runtime.IsException());
            // sls time is normal
            ResetRuntime();
            runtime.taskList.Add(new Task());
            runtime.slsTime = 0.9;
            Assert.IsTrue(runtime.IsException());
        }

        private void CaseProByRes(string oldResCode, string newResCode, string newDepCode)
        {
            ResetRuntime();
            runtime.resCode = oldResCode;
            runtime.ProcessByResCode();
            Assert.AreEqual(newResCode, runtime.resCode);
            Assert.AreEqual(newDepCode, runtime.depCode);
        }

        [TestMethod]
        public void TestProcessByResCode()
        {
            CaseProByRes("LA01", "L6", runtime.depCode);
            CaseProByRes("LA06", "L6", runtime.depCode);
            CaseProByRes("LA08", "L8", runtime.depCode);
            CaseProByRes("LA09", "L10", runtime.depCode);
            CaseProByRes("MC1", "MC1", "M1");
            CaseProByRes("MC4", "MC4", "M1");
            CaseProByRes("MC6", "MC6", "M1");
            CaseProByRes("MC9", "MC9", "M1");
            CaseProByRes("MC20", "MC20", "M1");
            CaseProByRes("MC21", "MC21", "M1");
            CaseProByRes("MC25", "MC25", "M1");
            CaseProByRes("MC26", "MC26", "M1");
            CaseProByRes("MC27", "MC27", "M1");
            CaseProByRes("MC28", "MC28", "M1");
            CaseProByRes("MC29", "MC29", "M1");
            CaseProByRes("MC30", "MC30", "M1");
            CaseProByRes("MC31", "MC31", "M1");
            CaseProByRes("MC32", "MC32", "M1");
            CaseProByRes("MC33", "MC33", "M1");
            CaseProByRes("MC34", "MC34", "M1");
            CaseProByRes("MC35", "MC35", "M1");
            CaseProByRes("MC36", "MC36", "M1");
            CaseProByRes("MC38", "MC38", "M1");
            CaseProByRes("MC39", "MC39", "M1");
            CaseProByRes("MC40", "MC40", "M1");
            CaseProByRes("MC41", "MC41", "M1");
            CaseProByRes("NK", "MCNK", "M1");
            CaseProByRes("NM-1", "MCNM", "M1");
            CaseProByRes("NN", "MCNN", "M1");
            CaseProByRes("NP", "MCNP", "M1");
            CaseProByRes("MC22", "MC22", "M2");
            CaseProByRes("MC23", "MC23", "M2");
            CaseProByRes("CG23", "CG23", "M2");
            CaseProByRes("MC24", "MC24", "M2");
        }

        private void CaseProBySeq(string oldResCode, string oldDepCode, int seq, char type, string newResCode, string newDepCode)
        {
            ResetRuntime();
            runtime.depCode = oldDepCode;
            runtime.type = type;
            runtime.seqNum = seq;
            runtime.resCode = oldResCode;
            runtime.ProcessBySeqNum();
            Assert.AreEqual(newResCode, runtime.resCode);
            Assert.AreEqual(newDepCode, runtime.depCode);
        }

        [TestMethod]
        public void TestProcessBySeqNum()
        {
            CaseProBySeq(runtime.resCode, runtime.depCode, 10, runtime.type, "EMPL", "CD");
            CaseProBySeq(runtime.resCode, runtime.depCode, 20, runtime.type, "EMPL", "CD");
            CaseProBySeq(runtime.resCode, runtime.depCode, 30, runtime.type, "EMPL", "CM");
            CaseProBySeq(runtime.resCode, runtime.depCode, 100, runtime.type, "AS1", "SW");
            CaseProBySeq(runtime.resCode, runtime.depCode, 160, runtime.type, runtime.resCode, runtime.depCode);
            CaseProBySeq(string.Empty, runtime.depCode, 160, runtime.type, "L8", runtime.depCode);
            CaseProBySeq(runtime.resCode, string.Empty, 160, runtime.type, runtime.resCode, "L1");
            CaseProBySeq(runtime.resCode, runtime.depCode, 180, runtime.type, runtime.resCode, runtime.depCode);
            CaseProBySeq(string.Empty, runtime.depCode, 180, runtime.type, "MC1", runtime.depCode);
            CaseProBySeq(runtime.resCode, string.Empty, 180, runtime.type, runtime.resCode, "M1");
            CaseProBySeq(runtime.resCode, runtime.depCode, 190, runtime.type, runtime.resCode, runtime.depCode);
            CaseProBySeq(string.Empty, runtime.depCode, 190, runtime.type, "MC1", runtime.depCode);
            CaseProBySeq(runtime.resCode, string.Empty, 190, runtime.type, runtime.resCode, "M1");
            CaseProBySeq(runtime.resCode, runtime.depCode, 173, runtime.type, "EMPL", "L1");
            CaseProBySeq(runtime.resCode, runtime.depCode, 210, runtime.type, "MM1", "MM");
            CaseProBySeq(runtime.resCode, runtime.depCode, 230, runtime.type, "EMPL", "DU");
            CaseProBySeq(runtime.resCode, runtime.depCode, 240, runtime.type, "DP2", "DS");
            CaseProBySeq(runtime.resCode, runtime.depCode, 310, runtime.type, "RKLF", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 320, runtime.type, "FB1", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 330, runtime.type, "FB3", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 340, runtime.type, "CY6", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 350, runtime.type, "CY6", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 360, runtime.type, "CY6", "HT");
            CaseProBySeq(runtime.resCode, runtime.depCode, 410, runtime.type, "L7", "L2");
            CaseProBySeq(runtime.resCode, runtime.depCode, 420, runtime.type, "MM4", "MM");
            CaseProBySeq(runtime.resCode, runtime.depCode, 500, runtime.type, "MM4", "MM");
            CaseProBySeq(runtime.resCode, runtime.depCode, 430, runtime.type, runtime.resCode, "M2");
            CaseProBySeq(runtime.resCode, runtime.depCode, 430, 'F', "L7", "L2");
            CaseProBySeq(string.Empty, runtime.depCode, 430, 'B', "MC22", "M2");
            CaseProBySeq(runtime.resCode, runtime.depCode, 460, runtime.type, "S1", "ED");
            CaseProBySeq(runtime.resCode, runtime.depCode, 470, runtime.type, "WE3", "WI");
            CaseProBySeq(runtime.resCode, runtime.depCode, 490, runtime.type, "MC11", "M2");
            CaseProBySeq(runtime.resCode, runtime.depCode, 780, runtime.type, "EMPL", "IN");
            CaseProBySeq(runtime.resCode, runtime.depCode, 800, runtime.type, "EMPL", "IN");
            CaseProBySeq(runtime.resCode, runtime.depCode, 790, runtime.type, "N1", "NI");
        }

        [TestMethod]
        public void TestElapsedHours()
        {
            DateTime start = new DateTime(1, 1, 1, 1, 30, 0);
            DateTime stop = new DateTime(1, 1, 1, 3, 0, 0);
            Assert.AreEqual(1.5, runtime.ElapsedHours(start, stop));
        }

        [TestMethod]
        public void TestDeleteLastTaskIfStart()
        {
            // case 1: only start
            runtime.taskList.Clear();
            Task task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            runtime.DeleteLastTaskIfStart();
            Assert.AreEqual(0, runtime.taskList.Count);
            // case 2: stop start start
            runtime.taskList.Clear();
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            runtime.DeleteLastTaskIfStart();
            Assert.AreEqual(1, runtime.taskList.Count);
            Assert.IsTrue(runtime.taskList[0].isStop);
            // case 3: start start stop
            runtime.taskList.Clear();
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            runtime.taskList.Add(task);
            runtime.DeleteLastTaskIfStart();
            Assert.AreEqual(3, runtime.taskList.Count);
            Assert.IsTrue(runtime.taskList[0].isStart);
            Assert.IsTrue(runtime.taskList[1].isStart);
            Assert.IsTrue(runtime.taskList[2].isStop);
            // case 4: start start stop start
            runtime.taskList.Clear();
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            runtime.DeleteLastTaskIfStart();
            Assert.AreEqual(3, runtime.taskList.Count);
            Assert.IsTrue(runtime.taskList[0].isStart);
            Assert.IsTrue(runtime.taskList[1].isStart);
            Assert.IsTrue(runtime.taskList[2].isStop);
        }

        [TestMethod]
        public void TestGetStandardCost()
        {
            // case 1: only one task
            ResetRuntime();
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            Task task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 0);
            runtime.taskList.Add(task);
            runtime.GetStandardCost();
            Assert.AreEqual(runtime.runTime, runtime.stdTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 1, 45, 0), runtime.startTime);
            Assert.AreEqual(1, runtime.stopTime.Year);
            // case 2: duplicated tasks within std run time
            ResetRuntime();
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 1);
            runtime.taskList.Add(task);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 2);
            runtime.taskList.Add(task);
            runtime.GetStandardCost();
            Assert.AreEqual(runtime.runTime, runtime.stdTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 1, 45, 0), runtime.startTime);
            Assert.AreEqual(1, runtime.stopTime.Year);
            // case 3: duplicated tasks
            ResetRuntime();
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 1, 45, 1);
            runtime.taskList.Add(task);
            task = new Task();
            task.taskTime = new DateTime(2013, 9, 3, 2, 45, 0);
            runtime.taskList.Add(task);
            runtime.GetStandardCost();
            Assert.AreEqual(runtime.runTime, runtime.stdTime * 2.0);
            Assert.AreEqual(new DateTime(2013, 9, 3, 1, 45, 0), runtime.startTime);
            Assert.AreEqual(1, runtime.stopTime.Year);
        }

        [TestMethod]
        public void TestStartStop()
        {
            // case 1: only start
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            Task task = new Task();
            task.isStart = true;
            task.isStop = false;
            runtime.taskList.Add(task);
            runtime.CalculateStartStop(Database.DECADE_MARKHAM);
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            Assert.AreEqual(0, runtime.taskList.Count);
            // case 2: only stop
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            Assert.AreEqual(0.0, runtime.runTime);
            Assert.AreEqual(1, runtime.startTime.Year);
            Assert.AreEqual(1, runtime.stopTime.Year);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            task.station = "NP";
            task.taskTime = new DateTime(2013, 9, 3, 21, 45, 0);
            runtime.taskList.Add(task);
            runtime.CalculateStartStop(Database.DECADE_MARKHAM);
            Assert.IsTrue(Math.Abs(runtime.runTime - 2.76583) < 0.001);
            Assert.AreEqual(new DateTime(2013, 9, 3, 18, 59, 3), runtime.startTime);
            Assert.AreEqual(task.taskTime, runtime.stopTime);
            // case 3: start start stop start
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 3, 21, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 3, 22, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            task.taskTime = new DateTime(2013, 9, 3, 23, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 4, 0, 45, 0);
            runtime.taskList.Add(task);
            runtime.CalculateStartStop(Database.DECADE_MARKHAM);
            Assert.IsTrue(Math.Abs(runtime.runTime - 2.0) < 0.001);
            Assert.AreEqual(new DateTime(2013, 9, 3, 21, 45, 0), runtime.startTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 23, 45, 0), runtime.stopTime);
            Assert.AreEqual(3, runtime.taskList.Count);
            // case 4: start stop start stop
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 3, 21, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            task.taskTime = new DateTime(2013, 9, 3, 22, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 3, 23, 45, 0);
            runtime.taskList.Add(task);
            runtime.CalculateStartStop(Database.DECADE_MARKHAM);
            Assert.IsTrue(Math.Abs(runtime.runTime - 1.0) < 0.001);
            Assert.AreEqual(new DateTime(2013, 9, 3, 21, 45, 0), runtime.startTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 22, 45, 0), runtime.stopTime);
            Assert.AreEqual(2, runtime.taskList.Count);
            Assert.AreEqual(new DateTime(2013, 9, 3, 21, 45, 0), runtime.taskList[0].taskTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 22, 45, 0), runtime.taskList[1].taskTime);
            // case 5: start stop stop
            runtime.taskList.Clear();
            runtime.runTime = 0.0;
            task = new Task();
            task.isStart = true;
            task.isStop = false;
            task.taskTime = new DateTime(2013, 9, 3, 21, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            task.taskTime = new DateTime(2013, 9, 3, 22, 45, 0);
            runtime.taskList.Add(task);
            task = new Task();
            task.isStart = false;
            task.isStop = true;
            task.taskTime = new DateTime(2013, 9, 3, 23, 45, 0);
            runtime.taskList.Add(task);
            runtime.CalculateStartStop(Database.DECADE_MARKHAM);
            Assert.IsTrue(Math.Abs(runtime.runTime - 2.0) < 0.001);
            Assert.AreEqual(new DateTime(2013, 9, 3, 21, 45, 0), runtime.startTime);
            Assert.AreEqual(new DateTime(2013, 9, 3, 23, 45, 0), runtime.stopTime);
            Assert.AreEqual(3, runtime.taskList.Count);
        }




        //[TestMethod]
        //public void TestGenerateMaterialBatch()
        //{
        //    RunTime runtime = new RunTime();
        //    runtime.runTime = 2.2;
        //    runtime.startTime = new DateTime(2013, 1, 1, 1, 1, 1);
        //    runtime.seqNum = 100;
        //    runtime.part = "SD 9 X 2";
        //    runtime.woNum = "0466225";
        //    runtime.empNum = 12345;
        //    runtime.depCode = "XX";
        //    runtime.resCode = "AAA";
        //    List<string> batch = runtime.GenerateMaterialBatch(Database.PRODTEST);
        //    Assert.AreEqual(4, batch.Count);
        //    Assert.AreEqual("HDR01011311304    001", batch[0]);
        //    Assert.AreEqual("DTLRXXAAA  SD 9 X 2            100          02120466225           ", batch[1]);
        //    Assert.AreEqual("PRTSD 9 X 2            000000000100000000000000000000EA   XX12345       Y                                                                                                                                                                                   ", batch[2]);
        //    Assert.AreEqual("MATH-13 9 DIA          STLRY000000000238000IN                                    N", batch[3]);
        //    // todo
        //}

        //[TestMethod]
        //public void TestGenerateProductionBatch()
        //{
        //    RunTime runtime = new RunTime();
        //    runtime.runTime = 2.2;
        //    runtime.startTime = new DateTime(2013, 1, 1, 1, 1, 1);
        //    runtime.seqNum = 100;
        //    runtime.part = "HD 10 X 2.427 BACKER";
        //    runtime.woNum = "0320165";
        //    runtime.empNum = 12345;
        //    runtime.depCode = "XX";
        //    runtime.resCode = "AAA";
        //    List<string> batch = runtime.GenerateProductionBatch();
        //    Assert.AreEqual(3, batch.Count);
        //    Assert.AreEqual("HDR01011311304    001", batch[0]);
        //    Assert.AreEqual("DTLRXXAAA  HD 10 X 2.427 BACKER100          02200320165           ", batch[1]);
        //    Assert.AreEqual("PRTHD 10 X 2.427 BACKER000000000100000000000000000000EA   XX12345       N                                                                                                                                                                                   ", batch[2]);
        //}

        //[TestMethod]
        //public void TestGenerateBatchString()
        //{
        //    // if a material batch
        //    RunTime runtime = new RunTime();
        //    runtime.runTime = 2.2;
        //    runtime.startTime = new DateTime(2013, 1, 1, 1, 1, 1);
        //    runtime.seqNum = 100;
        //    runtime.part = "HD 10 X 2.427 BACKER";
        //    runtime.woNum = "0320165";
        //    runtime.empNum = 12345;
        //    runtime.depCode = "XX";
        //    runtime.resCode = "AAA";
        //    List<string> batch = runtime.GenerateBatchString(Database.PRODTEST);
        //    Assert.AreEqual(4, batch.Count);
        //    Assert.AreEqual("HDR01011311304    001", batch[0]);
        //    Assert.AreEqual("DTLRXXAAA  HD 10 X 2.427 BACKER100          02200320165           ", batch[1]);
        //    Assert.AreEqual("PRTHD 10 X 2.427 BACKER000000000100000000000000000000EA   XX12345       Y                                                                                                                                                                                   ", batch[2]);
        //    Assert.AreEqual("MATH-13 9 DIA          STLRY000000000288000IN                                    N", batch[3]);
        //    // if a production batch
        //    runtime.seqNum = 200;
        //    batch = runtime.GenerateBatchString(Database.PRODTEST);
        //    Assert.AreEqual(3, batch.Count);
        //    Assert.AreEqual("HDR01011311304    001", batch[0]);
        //    Assert.AreEqual("DTLRXXAAA  HD 10 X 2.427 BACKER200          02200320165           ", batch[1]);
        //    Assert.AreEqual("PRTHD 10 X 2.427 BACKER000000000100000000000000000000EA   XX12345       N                                                                                                                                                                                   ", batch[2]);
        //}
    }
}