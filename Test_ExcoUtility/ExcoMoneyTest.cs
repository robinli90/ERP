using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Test_ExcoUtility
{
    /// <summary>
    ///This is a test class for ExRateTest and is intended
    ///to contain all ExRateTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ExcoMoneyTest
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

        //Use TestInitialize to run code before running each test
        public ExcoCalendar calendarCA = new ExcoCalendar(13, 3, false, 1);
        public ExcoMoney moneyCA;
        public ExcoCalendar calendarUS = new ExcoCalendar(13, 3, false, 3);
        public ExcoMoney moneyUS;
        public ExcoCalendar calendarCP = new ExcoCalendar(13, 3, false, 4);
        public ExcoMoney moneyCP;
        [TestInitialize()]
        public void MyTestInitialize()
        {
            moneyCA = new ExcoMoney(calendarCA, 1.0, "CA");
            moneyUS = new ExcoMoney(calendarUS, 2.0, "US");
            moneyCP = new ExcoMoney(calendarCP, 3.3, "CP");
        }

        /// <summary>
        ///A test for Constructor
        ///</summary>
        [TestMethod()]
        public void ConstructorTest()
        {
            // cad amount
            Assert.AreEqual(1.0 * ExcoExRate.GetToCADRate(calendarCA, "CA"), moneyCA.amountCA);
            Assert.AreEqual(2.0 * ExcoExRate.GetToCADRate(calendarUS, "US"), moneyUS.amountCA);
            Assert.AreEqual(3.3 * ExcoExRate.GetToCADRate(calendarCP, "CP"), moneyCP.amountCA);
            // usd amount
            Assert.AreEqual(1.0 * ExcoExRate.GetToUSDRate(calendarCA, "CA"), moneyCA.amountUS);
            Assert.AreEqual(2.0 * ExcoExRate.GetToUSDRate(calendarUS, "US"), moneyUS.amountUS);
            Assert.AreEqual(3.3 * ExcoExRate.GetToUSDRate(calendarCP, "CP"), moneyCP.amountUS);
            // peso amount
            Assert.AreEqual(1.0 * ExcoExRate.GetToPESORate(calendarCA, "CA"), moneyCA.amountCP);
            Assert.AreEqual(2.0 * ExcoExRate.GetToPESORate(calendarUS, "US"), moneyUS.amountCP);
            Assert.AreEqual(3.3 * ExcoExRate.GetToPESORate(calendarCP, "CP"), moneyCP.amountCP);
        }

        /// <summary>
        ///A test for operator + overload
        ///</summary>
        [TestMethod()]
        public void OperatorPlusTest()
        {
            ExcoMoney result = new ExcoMoney();
            result = moneyCA + moneyCP + moneyUS;
            Assert.AreEqual(moneyCA.amountCA+moneyCP.amountCA+moneyUS.amountCA, result.amountCA);
            Assert.AreEqual(moneyCA.amountUS + moneyCP.amountUS + moneyUS.amountUS, result.amountUS);
            Assert.AreEqual(moneyCA.amountCP + moneyCP.amountCP + moneyUS.amountCP, result.amountCP);
        }

        /// <summary>
        ///A test for IsZero
        ///</summary>
        [TestMethod()]
        public void IsZeroTest()
        {
            ExcoMoney result = new ExcoMoney();
            Assert.IsFalse(moneyCA.IsZero());
            Assert.IsFalse(moneyUS.IsZero());
            Assert.IsFalse(moneyCP.IsZero());
            Assert.IsTrue(result.IsZero());
        }
    }
}
