using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace ExcoUtility
{
    public class ExcoCustomerTable
    {
        // can only have one instance
        // load all customers when created initially
        private static ExcoCustomerTable instance;
        // list contains all customers
        public List<ExcoCustomer> custList = new List<ExcoCustomer>();

        public static ExcoCustomerTable Instance
        {
            get
            {
                if (null == instance)
                {
                    instance = new ExcoCustomerTable();
                }
                return instance;
            }
        }

        private ExcoCustomerTable()
        {
            //string query = "select bvcust, bvname, bvcurr, bvterr from cmsdat.cust order by bvterr, bvname";
            string query = "select bvcust, bvname, bvcurr, bvterr from cmsdat.cust where BVCUST not like '000265S%' order by bvterr, bvname";
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                string id = reader[0].ToString().Trim();
                string name = reader[1].ToString().Trim();
                string curr = reader[2].ToString().Trim();
                string terr = reader[3].ToString().Trim();
                if (custList.Count == 0 || 0 != name.CompareTo(custList[custList.Count - 1].Name) || (0 == name.CompareTo(custList[custList.Count - 1].Name) && id.Contains('S')) || 0 != curr.CompareTo(custList[custList.Count - 1].Currency))
                {
                    ExcoCustomer cust = new ExcoCustomer();
                    cust.ShipToID = id;
                    cust.BillToID = id;
                    cust.SillyID = id;
                    cust.Name = name;
                    cust.Currency = curr;
                    cust.Territory = terr;
                    custList.Add(cust);
                }
                else
                {
                    if (id.Contains("S"))
                    {
                        if (custList[custList.Count - 1].ShipToID.Contains("S"))
                        {
                            custList[custList.Count - 1].SillyID = id;
                        }
                        else
                        {
                            custList[custList.Count - 1].ShipToID = id;
                        }
                    }
                    else
                    {
                        custList[custList.Count - 1].BillToID = id;
                        custList[custList.Count - 1].Territory = terr;
                    }
                }
            }
            reader.Close();
        }

        public ExcoCustomer GetCustomer(string id)
        {
            // search list to find corresponding customer
            foreach (ExcoCustomer cust in custList)
            {
                if (0 == cust.ShipToID.CompareTo(id) || 0 == cust.BillToID.CompareTo(id) || 0 == cust.SillyID.CompareTo(id))
                {
                    return cust;
                }
            }
            // if not found, throw exception
            throw new Exception("Invalid customer id: " + id);
        }

        public List<ExcoCustomer> GetAllCustomers()
        {
            return custList;
        }
    }
}
