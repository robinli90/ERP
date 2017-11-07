using System;
using System.Text;
using System.Data.Odbc;
using System.Collections.Generic;
using System.Linq;
using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Test_ExcoUtility
{
    [TestClass]
    public class ExcoODBCTest
    {
        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        // 
        //You can use the following additional attributes as you write your tests:
        //
        //Use ClassInitialize to run code before running the first test in the class
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //Use ClassCleanup to run code after all tests in a class have run
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //Use TestInitialize to run code before running each test
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //Use TestCleanup to run code after each test has run
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion
        
        [TestMethod]
        public void DBConnectionTest()
        {
            // cmsdat
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            Assert.AreEqual("Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=ZWANG;Pwd=ZWANG;", database.ConnectionString);
            Assert.AreEqual("cmsdat", database.DbName);
            // prodtest
            database.Open(Database.PRODTEST);
            Assert.AreEqual("Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=ZWANG;Pwd=ZWANG;", database.ConnectionString);
            Assert.AreEqual("prodtest", database.DbName);
            // decade
            database.Open(Database.DECADE);
            Assert.AreEqual("Driver={SQL Server};Server=10.0.0.6;Uid=jamie;Pwd=jamie;", database.ConnectionString);
            Assert.AreEqual("dbo", database.DbName);
        }

        [TestMethod]
        public void RunQueryTest()
        {
            // solarsoft
            string query = "select * from prodtest.cret";
            // get expect
            string connStr = "Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=ZWANG;Pwd=ZWANG;";
            OdbcConnection conn = new OdbcConnection(connStr);
            conn.Open();
            OdbcCommand com = new OdbcCommand(query, conn);
            OdbcDataReader expect = com.ExecuteReader();
            // get target
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.PRODTEST);
            query = "select * from cmsdat.cret";
            OdbcDataReader target = database.RunQuery(query);
            // compare
            Assert.AreEqual(expect.FieldCount, target.FieldCount);
            Assert.AreEqual(expect.HasRows, target.HasRows);
            while (true)
            {
                bool isExpValid = expect.Read();
                bool isTarValid = target.Read();
                Assert.AreEqual(isExpValid, isTarValid);
                if (false == isTarValid)
                {
                    break;
                }
                for (int i = 0; i < expect.FieldCount; i++)
                {
                    Assert.AreEqual(expect[i].ToString(), target[i].ToString());
                }
            }
            // clean up
            conn.Close();
            expect.Close();
            target.Close();
        }

        [TestMethod]
        public void RunQueryWithoutReaderTest()
        {
            // insert 1 row
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.PRODTEST);
            string query = "select count(*) from cmsdat.aprq";
            OdbcDataReader reader = database.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(0, Convert.ToInt32(reader[0]));
            reader.Close();
            query = "insert into cmsdat.aprq (b02comn) values (99)";
            int colChanged = database.RunQueryWithoutReader(query);
            Assert.AreEqual(1, colChanged);
            query = "select count(*) from cmsdat.aprq";
            reader = database.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(1, Convert.ToInt32(reader[0]));
            reader.Close();
            // insert 1 row
            colChanged = 0;
            Assert.AreEqual(0, colChanged);
            query = "insert into cmsdat.aprq (b02comn) values (98)";
            colChanged = database.RunQueryWithoutReader(query);
            Assert.AreEqual(1, colChanged);
            query = "select count(*) from cmsdat.aprq";
            reader = database.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(2, Convert.ToInt32(reader[0]));
            reader.Close();
            // delete 2 rows
            colChanged = 0;
            Assert.AreEqual(0, colChanged);
            query = "delete from cmsdat.aprq where b02comn=98 or b02comn=99";
            colChanged = database.RunQueryWithoutReader(query);
            Assert.AreEqual(2, colChanged);
            query = "select count(*) from cmsdat.aprq";
            reader = database.RunQuery(query);
            Assert.IsTrue(reader.Read());
            Assert.AreEqual(0, Convert.ToInt32(reader[0]));
            reader.Close();
        }
    }
}