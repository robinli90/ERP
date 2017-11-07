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
    public class SeqTest
    {
        [TestMethod]
        public void TestConstructor()
        {
            // test default constructor
            Seq seq = new Seq();
            Assert.AreEqual(0, seq.seqNum);
            Assert.AreEqual(0.0, seq.stdTime);
            Assert.AreEqual(0, seq.runtimeList.Count);
            Assert.AreEqual(0, seq.taskList.Count);
            Assert.AreEqual(0, seq.part.Length);
            Assert.AreEqual(0, seq.soNum);
            Assert.AreEqual(0, seq.woNum.Length);
            Assert.AreEqual('\0', seq.type);
            // test detailed constructor
            seq = new Seq(100, 1.1, 'P', "HD 4 X 5", "0415222", 245454);
            Assert.AreEqual(100, seq.seqNum);
            Assert.AreEqual(1.1, seq.stdTime);
            Assert.AreEqual(1, seq.runtimeList.Count);
            Assert.AreEqual(0, seq.taskList.Count);
            Assert.AreEqual(0, seq.part.CompareTo("HD 4 X 5"));
            Assert.AreEqual(0, seq.woNum.CompareTo("0415222"));
            Assert.AreEqual(245454, seq.soNum);
            Assert.AreEqual('P', seq.type);
        }


        [TestMethod]
        public void TestCompareTask()
        {
            Task a = new Task();
            a.taskTime = DateTime.Now;
            Task b = new Task();
            b.taskTime = a.taskTime + new TimeSpan(10000);
            Task c = new Task();
            c.taskTime = a.taskTime;
            Assert.AreEqual(1, Seq.CompareTask(b, a));
            Assert.AreEqual(-1, Seq.CompareTask(a, b));
            Assert.AreEqual(0, Seq.CompareTask(a, c));
        }


        [TestMethod]
        public void TestGetSeqInfo()
        {
            Dictionary<int, List<Task>> sparkMap = new Dictionary<int, List<Task>>();
            Dictionary<int, List<Task>> wireMap = new Dictionary<int, List<Task>>();
            List<Task> sparkTaskList = new List<Task>();
            sparkTaskList.Add(new Task(254933, 12345, 'P', 'B', "SW", new DateTime(2013, 2, 1, 1, 1, 1), "SAW", 100));
            sparkTaskList.Add(new Task(254933, 54321, 'P', 'B', "SW", new DateTime(2013, 1, 1, 1, 1, 1), "SAW", 100));
            sparkMap.Add(254933, sparkTaskList);
            List<Task> wireTaskList = new List<Task>();
            wireTaskList.Add(new Task(254900, 55555, 'P', 'B', "SW", new DateTime(2013, 1, 1, 1, 1, 1), "SAW", 100));
            wireTaskList.Add(new Task(254900, 99999, 'P', 'B', "SW", new DateTime(2013, 1, 2, 1, 1, 1), "SAW", 100));
            wireMap.Add(254900, wireTaskList);
            // spark
            Seq seq = new Seq(460, 1.1, 'P', "HD 4 X 5", "0415222", 254933);
            Assert.AreEqual(0, seq.taskList.Count);
            seq.GetSeqInfo(Database.DECADE_MARKHAM, sparkMap, wireMap, DateTime.Now);
            Assert.AreEqual(2, seq.taskList.Count);
            Assert.AreEqual(54321, seq.taskList[0].empNum);
            Assert.AreEqual(12345, seq.taskList[1].empNum);
            // wire
            seq = new Seq(470, 1.1, 'P', "HD 4 X 5", "0415222", 254900);
            Assert.AreEqual(0, seq.taskList.Count);
            seq.GetSeqInfo(Database.DECADE_MARKHAM, sparkMap, wireMap, DateTime.Now);
            Assert.AreEqual(2, seq.taskList.Count);
            Assert.AreEqual(55555, seq.taskList[0].empNum);
            Assert.AreEqual(99999, seq.taskList[1].empNum);
            // other tasks
            seq = new Seq(30, 1.1, 'P', "HD 4 X 5", "0415222", 270000);
            Assert.AreEqual(0, seq.taskList.Count);
            seq.GetSeqInfo(Database.DECADE_MARKHAM, sparkMap, wireMap, new DateTime(2013, 11, 6));
            Assert.AreEqual(2, seq.taskList.Count);
            Assert.AreEqual(8195691, seq.taskList[0].decadeID);
            Assert.AreEqual(8195832, seq.taskList[1].decadeID);
        }
    }
}