using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;
using System;

namespace Test_ExcoUtility
{
    /// <summary>
    ///This is a test class for ExRateTest and is intended
    ///to contain all ExcoBudget Unit Tests
    ///</summary>
    [TestClass()]
    public class ExcoBudgetTest
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

        [TestMethod()]
        [DeploymentItem("ExcoUtility.dll")]
        public void MarkhamBudgetTest()
        {
            ExcoBudget budget = ExcoBudget.Instance;
            string[] lines = File.ReadAllLines("D:\\workspace\\ERP\\ExcoUtility\\Markham_Budget.txt");
            foreach (string line in lines)
            {
                int indexComma = line.IndexOf(',');
                double amount = Convert.ToDouble(line.Substring(0, indexComma - 1));
                string custID = line.Substring(indexComma + 1, line.Length - indexComma - 1);
                Assert.AreEqual(amount / 12.0, budget.GetMonthlyBudget(custID, 1));
            }
        }

        [TestMethod()]
        [DeploymentItem("ExcoUtility.dll")]
        public void MichiganBudgetTest()
        {
            ExcoBudget budget = ExcoBudget.Instance;
            string[] lines = File.ReadAllLines("D:\\workspace\\ERP\\ExcoUtility\\USA_Budget.txt");
            foreach (string line in lines)
            {
                int indexComma = line.IndexOf(',');
                double amount = Convert.ToDouble(line.Substring(0, indexComma - 1));
                string custID = line.Substring(indexComma + 1, line.Length - indexComma - 1);
                Assert.AreEqual(amount / 12.0, budget.GetMonthlyBudget(custID, 3));
            }
        }
    }
}