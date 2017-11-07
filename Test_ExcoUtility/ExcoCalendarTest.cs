using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace Test_ExcoUtility
{    
    /// <summary>
    ///This is a test class for ExcoCalendarTest and is intended
    ///to contain all ExcoCalendarTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ExcoCalendarTest
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

        private static ExcoCalendar plant01Fis;
        private static ExcoCalendar plant01Cal;
        private static ExcoCalendar plant02Fis;
        private static ExcoCalendar plant02Cal;
        private static ExcoCalendar plant03Fis;
        private static ExcoCalendar plant03Cal;
        private static ExcoCalendar plant04Fis;
        private static ExcoCalendar plant04Cal;
        // Use ClassInitialize to run code before running the first test in the class
        [ClassInitialize()]
        public static void MyClassInitialize(TestContext testContext)
        {
            int year = 10;
            int month = 2;
            int plantID = 1;
            plant01Cal = new ExcoCalendar(year, month, false, plantID);
            plant01Fis = new ExcoCalendar(year, month, true, plantID);
            year = 13;
            month = 10;
            plantID = 4;
            plant04Cal = new ExcoCalendar(year, month, false, plantID);
            plant04Fis = new ExcoCalendar(year, month, true, plantID);
            year = 12;
            month = 12;
            plantID = 2;
            plant02Cal = new ExcoCalendar(year, month, false, plantID);
            plant02Fis = new ExcoCalendar(year, month, true, plantID);
            year = 11;
            month = 1;
            plantID = 3;
            plant03Cal = new ExcoCalendar(year, month, false, plantID);
            plant03Fis = new ExcoCalendar(year, month, true, plantID);
        }
        
        // Use ClassCleanup to run code after all tests in a class have run
        [ClassCleanup()]
        public static void MyClassCleanup()
        {
        }
        

        //Use TestInitialize to run code before running each test
        [TestInitialize()]
        public void MyTestInitialize()
        {

        }

        //Use TestCleanup to run code after each test has run
        [TestCleanup()]
        public void MyTestCleanup()
        {
        }
        
        #endregion

        /// <summary>
        ///A test for ExcoCalendar Constructor
        ///</summary>
        [TestMethod()]
        public void ExcoCalendarConstructorTest()
        {
            // plant 01 fiscal year
            Assert.AreEqual(9, plant01Fis.year);
            Assert.AreEqual(11, plant01Fis.month);
            Assert.AreEqual(1, plant01Fis.plantID);
            // plant 01 calendar year
            Assert.AreEqual(10, plant01Cal.year);
            Assert.AreEqual(2, plant01Cal.month);
            Assert.AreEqual(1, plant01Cal.plantID);
            // plant 04 fiscal year
            Assert.AreEqual(13, plant04Fis.year);
            Assert.AreEqual(10, plant04Fis.month);
            Assert.AreEqual(4, plant04Fis.plantID);
            // plant 04 calendar year
            Assert.AreEqual(13, plant04Cal.year);
            Assert.AreEqual(10, plant04Cal.month);
            Assert.AreEqual(4, plant04Cal.plantID);
        }

        /// <summary>
        ///A test for GetCalendarMonth
        ///</summary>
        [TestMethod()]
        public void GetCalendarMonthTest()
        {
            // plant 01 fiscal year
            Assert.AreEqual(11, plant01Fis.GetCalendarMonth());
            // plant 01 calendar year
            Assert.AreEqual(2, plant01Cal.GetCalendarMonth());
            // plant 04 fiscal year
            Assert.AreEqual(10, plant04Fis.GetCalendarMonth());
            // plant 04 calendar year
            Assert.AreEqual(10, plant04Cal.GetCalendarMonth());
        }

        /// <summary>
        ///A test for GetCalendarYear
        ///</summary>
        [TestMethod()]
        public void GetCalendarYearTest()
        {
            // plant 01 fiscal year
            Assert.AreEqual(9, plant01Fis.GetCalendarYear());
            // plant 01 calendar year
            Assert.AreEqual(10, plant01Cal.GetCalendarYear());
            // plant 04 fiscal year
            Assert.AreEqual(13, plant04Fis.GetCalendarYear());
            // plant 04 calendar year
            Assert.AreEqual(13, plant04Cal.GetCalendarYear());
        }

        /// <summary>
        ///A test for GetFiscalMonth
        ///</summary>
        [TestMethod()]
        public void GetFiscalMonthTest()
        {
            // plant 01 fiscal year
            Assert.AreEqual(2, plant01Fis.GetFiscalMonth());
            // plant 01 calendar year
            Assert.AreEqual(5, plant01Cal.GetFiscalMonth());
            // plant 04 fiscal year
            Assert.AreEqual(10, plant04Fis.GetFiscalMonth());
            // plant 04 calendar year
            Assert.AreEqual(10, plant04Cal.GetFiscalMonth());
        }

        /// <summary>
        ///A test for GetFiscalYear
        ///</summary>
        [TestMethod()]
        public void GetFiscalYearTest()
        {
            // plant 01 fiscal year
            Assert.AreEqual(10, plant01Fis.GetFiscalYear());
            // plant 01 calendar year
            Assert.AreEqual(10, plant01Cal.GetFiscalYear());
            // plant 04 fiscal year
            Assert.AreEqual(13, plant04Fis.GetFiscalYear());
            // plant 04 calendar year
            Assert.AreEqual(13, plant04Cal.GetFiscalYear());
        }

        /// <summary>
        ///A test for GetLastFiscalMonth
        ///</summary>
        [TestMethod()]
        public void GetLastFiscalMonthTest()
        {
            // plant 02 fiscal
            Assert.AreEqual(11, plant02Fis.GetLastFiscalMonth().month);
            Assert.AreEqual(12, plant02Fis.GetLastFiscalMonth().year);
            // plant 02 calendar
            Assert.AreEqual(2, plant02Cal.GetLastFiscalMonth().month);
            Assert.AreEqual(13, plant02Cal.GetLastFiscalMonth().year);           
            // plant 03 fiscal
            Assert.AreEqual(12, plant03Fis.GetLastFiscalMonth().month);
            Assert.AreEqual(10, plant03Fis.GetLastFiscalMonth().year);            
            // plant 03 calendar
            Assert.AreEqual(3, plant03Cal.GetLastFiscalMonth().month);
            Assert.AreEqual(11, plant03Cal.GetLastFiscalMonth().year);
        }

        /// <summary>
        ///A test for GetNextFiscalYear
        ///</summary>
        [TestMethod()]
        public void GetNextFiscalMonthTest()
        {
            // plant 02 fiscal
            Assert.AreEqual(1, plant02Fis.GetNextFiscalMonth().month);
            Assert.AreEqual(13, plant02Fis.GetNextFiscalMonth().year);
            // plant 02 calendar
            Assert.AreEqual(4, plant02Cal.GetNextFiscalMonth().month);
            Assert.AreEqual(13, plant02Cal.GetNextFiscalMonth().year);
            // plant 03 fiscal
            Assert.AreEqual(2, plant03Fis.GetNextFiscalMonth().month);
            Assert.AreEqual(11, plant03Fis.GetNextFiscalMonth().year);
            // plant 03 calendar
            Assert.AreEqual(5, plant03Cal.GetNextFiscalMonth().month);
            Assert.AreEqual(11, plant03Cal.GetNextFiscalMonth().year);
        }
    }
}