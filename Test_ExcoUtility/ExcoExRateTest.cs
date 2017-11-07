using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace Test_ExcoUtility
{
    /// <summary>
    ///This is a test class for ExRateTest and is intended
    ///to contain all ExRateTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ExcoExRateTest
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

        /// <summary>
        ///A test for GetToCADRate
        ///</summary>
        [TestMethod()]
        public void GetToCADRateTest()
        {
            ExcoCalendar calendar = new ExcoCalendar(12, 3, false, 1);
            Assert.AreEqual(1.0, ExcoExRate.GetToCADRate(calendar, "CA"));
            calendar.month = 2;
            Assert.AreEqual(0.000558, ExcoExRate.GetToCADRate(calendar, "CP"));
            calendar.year = 2012;
            calendar.month = 11;
            Assert.AreEqual(0.99, ExcoExRate.GetToCADRate(calendar, "US"));
            // exception
            try
            {
                ExcoExRate.GetToCADRate(calendar, "UaS");
            }
            catch (Exception e)
            {
                Assert.AreEqual("Invalid currency UaS", e.Message);
            }
        }

        /// <summary>
        ///A test for PESOtoCAD
        ///</summary>
        [TestMethod()]
        [DeploymentItem("ExcoUtility.dll")]
        public void PESOtoCADTest()
        {
            ExcoCalendar calendar = new ExcoCalendar(12, 1, false, 1);
            // short year
            Assert.AreEqual(0.000556, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.000558, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(0.000557, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.000560, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(0.000564, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(0.000571, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.000559, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.000540, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.000546, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.000546, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.000548, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.000563, ExcoExRate.PESOtoCAD(calendar));
            calendar.year = 13;
            calendar.month = 1;
            Assert.AreEqual(0.000562, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.000567, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(0.000556, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.000551, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(0.000543, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(0.000550, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            // long year
            calendar.year = 2012;
            calendar.month = 1;
            Assert.AreEqual(0.000556, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.000558, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(0.000557, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.000560, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(0.000564, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(0.000571, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.000559, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.000540, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.000546, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.000546, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.000548, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.000563, ExcoExRate.PESOtoCAD(calendar));
            calendar.year = 2013;
            calendar.month = 1;
            Assert.AreEqual(0.000562, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.000567, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(0.000556, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.000551, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(0.000543, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(0.000550, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.0, ExcoExRate.PESOtoCAD(calendar));
            // exception
            try
            {
                calendar.year = 11;
                ExcoExRate.PESOtoCAD(calendar);
            }
            catch (Exception e)
            {
                Assert.AreEqual("Invalid year 11", e.Message);
            }
            try
            {
                calendar.year = 12;
                calendar.month = 33;
                ExcoExRate.PESOtoCAD(calendar);
            }
            catch (Exception e)
            {
                Assert.AreEqual("Invalid month 33", e.Message);
            }
        }

        /// <summary>
        ///A test for USDtoCAD
        ///</summary>
        [TestMethod()]
        [DeploymentItem("ExcoUtility.dll")]
        public void USDtoCADTest()
        {
            ExcoCalendar calendar = new ExcoCalendar(12, 1, false, 1);
            // short year
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(1.03, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(1.02, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.98, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.year = 13;
            calendar.month = 1;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(1.03, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(1.02, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(1.01, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(1.04, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(1.01, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            // long year
            calendar.year = 2012;
            calendar.month = 1;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(1.03, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(1.02, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.98, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.99, ExcoExRate.USDtoCAD(calendar));
            calendar.year = 2013;
            calendar.month = 1;
            Assert.AreEqual(1.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 2;
            Assert.AreEqual(1.03, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 3;
            Assert.AreEqual(1.02, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 4;
            Assert.AreEqual(1.01, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 5;
            Assert.AreEqual(1.04, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 6;
            Assert.AreEqual(1.01, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 7;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 8;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 9;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 10;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 11;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            calendar.month = 12;
            Assert.AreEqual(0.0, ExcoExRate.USDtoCAD(calendar));
            // exception
            try
            {
                calendar.year = 11;
                ExcoExRate.USDtoCAD(calendar);
            }
            catch (Exception e)
            {
                Assert.AreEqual("Invalid year 11", e.Message);
            }
            try
            {
                calendar.year = 12;
                calendar.month = 33;
                ExcoExRate.USDtoCAD(calendar);
            }
            catch (Exception e)
            {
                Assert.AreEqual("Invalid month 33", e.Message);
            }
        }
    }
}