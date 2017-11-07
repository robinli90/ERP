using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace SalesReport
{
    public class Plant
    {
        public List<Customer> custList = new List<Customer>();
        public int plantID = 0;
        public List<ExcoMoney> surchargeList = new List<ExcoMoney>();
        public List<ExcoMoney> saleList = new List<ExcoMoney>();
        public List<int> solidList = new List<int>();
        public List<int> hollowList = new List<int>();
        public List<int> ncrList = new List<int>();
        // default currency for this plant
        public string currency = string.Empty;

        // constructor
        public Plant(int plantID, string currency)
        {
            this.plantID = plantID;
            this.currency = currency;
            for (int i = 0; i <= 12; i++)
            {
                surchargeList.Add(new ExcoMoney());
                saleList.Add(new ExcoMoney());

                solidList.Add(0);
                hollowList.Add(0);
                ncrList.Add(0);
            }
        }

        public Plant()
        {
            for (int i = 0; i <= 12; i++)
            {
                surchargeList.Add(new ExcoMoney());
                saleList.Add(new ExcoMoney());
                solidList.Add(0);
                hollowList.Add(0);
                ncrList.Add(0);
            }
        }

        // count parts
        public void CountParts()
        {
            foreach (Customer customer in custList)
            {
                for (int i = 1; i <= 12; i++)
                {   
                    solidList[i] += customer.solidList[i];
                    hollowList[i] += customer.hollowList[i];
                    ncrList[i] += customer.ncrList[i];
                }
            }
        }

        // add customer
        public void AddCustomer(ExcoCustomer excoCust, Dictionary<int, Invoice> invoiceMap, int fiscalYear, bool doesIncludeSurcharge, Dictionary<string, List<ExcoMoney>> budgetMap, Dictionary<int, List<string>> partsMap)
        {
            Customer customer = new Customer(excoCust, plantID);
            customer.GetData(invoiceMap, fiscalYear, doesIncludeSurcharge, budgetMap, partsMap);
            custList.Add(customer);
        }

        // get surcharge list
        public void GetSurcharge()
        {
            foreach (Customer cust in custList)
            {
                for (int i = 1; i < cust.surchargeList.Count; i++)
                {
                    surchargeList[i] += cust.surchargeList[i];
                    saleList[i] += cust.actualList[i];
                }
            }
        }
    }
}