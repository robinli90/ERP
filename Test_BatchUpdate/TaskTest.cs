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
    public class TaskTest
    {
        [TestMethod]
        public void TestConstructor()
        {
            // test detailed constructor
            Task task = new Task(254933, 12345, 'P', 'B', "SW", new DateTime(2013, 1, 1, 1, 1, 1), "SAW", 100);
            Assert.AreEqual(254933, task.soNum);
            Assert.AreEqual(12345, task.empNum);
            Assert.AreEqual('P', task.type);
            Assert.AreEqual('B', task.side);
            Assert.AreEqual("SW", task.taskCode);
            Assert.AreEqual(100, task.seqNum);
            Assert.AreEqual(new DateTime(2013, 1, 1, 1, 1, 1), task.taskTime);
            Assert.AreEqual("SAW", task.station);
            Assert.AreEqual(0.0, task.runTime);
            Assert.AreEqual(0, task.decadeID);
            Assert.AreEqual(0, task.wo.Length);
            Assert.AreEqual(0, task.partDesc.Length);
            Assert.IsFalse(task.isStart);
            Assert.IsFalse(task.isStop);
            Assert.IsFalse(task.isSystemGenerated);
            // test default constructor
            task = new Task();
            Assert.AreEqual(0, task.soNum);
            Assert.AreEqual(0, task.empNum);
            Assert.AreEqual(new char(), task.type);
            Assert.AreEqual(new char(), task.side);
            Assert.AreEqual(0, task.taskCode.Length);
            Assert.AreEqual(0, task.seqNum);
            Assert.AreEqual(new DateTime(), task.taskTime);
            Assert.AreEqual(0, task.station.Length);
            Assert.AreEqual(0.0, task.runTime);
            Assert.AreEqual(0, task.decadeID);
            Assert.AreEqual(0, task.wo.Length);
            Assert.AreEqual(0, task.partDesc.Length);
            Assert.IsFalse(task.isStart);
            Assert.IsFalse(task.isStop);
            Assert.IsFalse(task.isSystemGenerated);
        }

        [TestMethod]
        public void TestMarkComplete()
        {
            // test regular case
            Task task = new Task(238033, 10187, 'F', 'B', "CM", new DateTime(2011, 5, 30, 12, 0, 0), "CM17", 100);
            // at first flags is 0
            string query = "select id, flags from dbo.d_task where ordernumber=" + task.soNum.ToString() + " and employeenumber=" + task.empNum.ToString() + " and part='" + task.type + "' and subpart='" + task.side + "' and task='" + task.taskCode + "' and tasktime='" + task.taskTime.ToString("yyyy-MM-dd HH:mm:ss") + "' and station='" + task.station + "'";
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(Database.DECADE_MARKHAM);
            OdbcDataReader reader = odbcConnection.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(0, Convert.ToInt32(reader["flags"]));
            task.decadeID = Convert.ToInt32(reader["id"]);
            reader.Close();
            // then change to 1
            task.MarkComplete(Database.DECADE_MARKHAM);
            // check if changed to 1
            query = "select flags from dbo.d_task where id=" + task.decadeID;
            reader = odbcConnection.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(1, Convert.ToInt32(reader[0]));
            reader.Close();
            // then change back to 0
            query = "update dbo.d_task set flags=0 where id=" + task.decadeID;
            Assert.AreEqual(1, odbcConnection.RunQueryWithoutReader(query));
            // check if changed back to 0
            query = "select flags from dbo.d_task where id=" + task.decadeID;
            reader = odbcConnection.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(0, Convert.ToInt32(reader[0]));
            reader.Close();
            // test 460

            // test 470
        }

        [TestMethod]
        public void TestDetermineStartStop()
        {
            // start
            TestStartStopFlagGeneration("DI", true, false);
            TestStartStopFlagGeneration("CI", true, false);
            TestStartStopFlagGeneration("L1", true, false);
            TestStartStopFlagGeneration("N1", true, false);
            TestStartStopFlagGeneration("MM", true, false);
            TestStartStopFlagGeneration("U1", true, false);
            TestStartStopFlagGeneration("IB", true, false);
            // stop
            TestStartStopFlagGeneration("DD", false, true);
            TestStartStopFlagGeneration("CO", false, true);
            TestStartStopFlagGeneration("L0", false, true);
            TestStartStopFlagGeneration("N0", false, true);
            TestStartStopFlagGeneration("M0", false, true);
            TestStartStopFlagGeneration("U0", false, true);
            TestStartStopFlagGeneration("IF", false, true);
            // other
            TestStartStopFlagGeneration("NA", false, false);
        }

        private void TestStartStopFlagGeneration(string code, bool isStart, bool isStop)
        {
            Task task = new Task();
            Assert.IsFalse(task.isStart);
            Assert.IsFalse(task.isStop);
            task.taskCode = code;
            task.DetermineStartStop();
            Assert.AreEqual(isStart, task.isStart);
            Assert.AreEqual(isStop, task.isStop);
        }
    }
}
