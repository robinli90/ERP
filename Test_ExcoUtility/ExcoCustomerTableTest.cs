using ExcoUtility;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Data.Odbc;
using System;

namespace Test_ExcoUtility
{
    /// <summary>
    ///This is a test class for ExcoCalendarTest and is intended
    ///to contain all ExcoCalendarTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ExcoCustomerTableTest
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

        /// <summary>
        ///A test for ExcoCustomerTable Constructor
        ///</summary>
        [TestMethod()]
        public void ExcoCustomerTableConstructorTest()
        {
            ExcoCustomerTable custTable = ExcoCustomerTable.Instance;
            // test customer number
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select trim(bvcust), trim(upper(bvname)), trim(bvcurr), trim(bvterr) from cmsdat.cust where bvstat='A'";
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                string id = reader[0].ToString();
                ExcoCustomer cust = custTable.GetCustomer(id);
                // test id
                if (false == id.Contains("S"))
                {
                    Assert.AreEqual(id, cust.BillToID);
                }
                else
                {
                    bool isGood = false;
                    if (0 == cust.BillToID.CompareTo(id) || 0 == cust.ShipToID.CompareTo(id) || 0 == cust.SillyID.CompareTo(id))
                    {
                        isGood = true;
                    }
                    Assert.IsTrue(isGood);
                }
                // test name
                Assert.AreEqual(reader[1].ToString(), cust.Name);
                // test currency
                Assert.AreEqual(reader[2].ToString(), cust.Currency);
                // test territory if it's a bill-to order
                if (!reader[3].ToString().Contains("S"))
                {
                    Assert.AreEqual(reader[3].ToString(), cust.Territory);
                }
            }
            reader.Close();
        }
    }
}