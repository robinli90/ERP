using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace SalesReport
{
    public class Customer
    {
        // plant id
        public int plantID;
        // budget amount
        public List<ExcoMoney> budgetList = new List<ExcoMoney>();
        // budget total
        public ExcoMoney budgetTotal = new ExcoMoney();
        // actual amount
        public List<ExcoMoney> actualList = new List<ExcoMoney>();
        // actual total
        public ExcoMoney actualTotal = new ExcoMoney();
        // last year actual amount
        public List<ExcoMoney> actualListLastYear = new List<ExcoMoney>();
        // surcharge list
        public List<ExcoMoney> surchargeList = new List<ExcoMoney>();
        // last year actual total
        public ExcoMoney actualTotalLastYear = new ExcoMoney();
        // ExcoCustomer object
        public ExcoCustomer excoCustomer;
        public List<int> solidList = new List<int>();
        public List<int> hollowList = new List<int>();
        public List<int> ncrList = new List<int>();

        // constructor
        public Customer(ExcoCustomer excoCustomer, int plantID)
        {
            this.excoCustomer = excoCustomer;
            this.plantID = plantID;
            for (int i = 0; i <= 12; i++)
            {
                budgetList.Add(new ExcoMoney());
                actualList.Add(new ExcoMoney());
                actualListLastYear.Add(new ExcoMoney());
                surchargeList.Add(new ExcoMoney());
                solidList.Add(0);
                hollowList.Add(0);
                ncrList.Add(0);
            }
        }

        public Customer()
        {
            for (int i = 0; i <= 12; i++)
            {
                budgetList.Add(new ExcoMoney());
                actualList.Add(new ExcoMoney());
                actualListLastYear.Add(new ExcoMoney());
                surchargeList.Add(new ExcoMoney());
                solidList.Add(0);
                hollowList.Add(0);
                ncrList.Add(0);
            }
        }

        public void GetData(Dictionary<int, Invoice> invoiceMap, int fiscalYear, bool doesIncludeSurcharge, Dictionary<string, List<ExcoMoney>> budgetMap, Dictionary<int, List<string>> partsMap)
        {
            // get actual invoice amount
            foreach (Invoice invoice in invoiceMap.Values)
            {
                if (invoice.plant == plantID)
                {
                    if (invoice.customer.ShipToID.Contains(excoCustomer.ShipToID) || invoice.customer.ShipToID.Contains(excoCustomer.BillToID) || invoice.customer.ShipToID.Contains(excoCustomer.SillyID) || invoice.customer.BillToID.Contains(excoCustomer.ShipToID) || invoice.customer.BillToID.Contains(excoCustomer.BillToID) || invoice.customer.BillToID.Contains(excoCustomer.SillyID) || invoice.customer.SillyID.Contains(excoCustomer.ShipToID) || invoice.customer.SillyID.Contains(excoCustomer.BillToID) || invoice.customer.SillyID.Contains(excoCustomer.SillyID))
                    {
                        int month = invoice.calendar.GetFiscalMonth();
                        if (4 != plantID)
                        {
                            // build actual list this year
                            if (invoice.calendar.GetFiscalYear() == fiscalYear)
                            {
                                actualList[month] += invoice.GetAmount(doesIncludeSurcharge);
                                actualTotal += invoice.GetAmount(doesIncludeSurcharge);
                                surchargeList[month] += new ExcoMoney(invoice.calendar, invoice.surcharge, invoice.currency);
                                // count parts
                                if (partsMap.ContainsKey(invoice.orderNum))
                                {
                                    foreach (string part in partsMap[invoice.orderNum])
                                    {
                                        if (0 == part.CompareTo("NCR"))
                                        {
                                            ncrList[month]++;
                                            break;
                                        }
                                        else if (part.Contains("HD") || part.Contains("HU"))
                                        {
                                            hollowList[month]++;
                                            break;
                                        }
                                        else if (part.Contains("BA") || part.Contains("SD") || part.Contains("BO") || part.Contains("FD") || part.Contains("RI") || part.Contains("SO") || part.Contains("BK"))
                                        {
                                            solidList[month]++;
                                            break;
                                        }
                                    }
                                }
                            }
                            // build actual list last year
                            else if (invoice.calendar.GetFiscalYear() == fiscalYear - 1)
                            {
                                actualListLastYear[month] += invoice.GetAmount(doesIncludeSurcharge);
                                actualTotalLastYear += invoice.GetAmount(doesIncludeSurcharge);
                            }
                        }
                        else
                        {
                            // build actual list this year
                            if (invoice.calendar.GetFiscalYear() == fiscalYear && invoice.calendar.GetFiscalMonth() < 10)
                            {
                                actualList[month + 3] += invoice.GetAmount(doesIncludeSurcharge);
                                surchargeList[month + 3] += new ExcoMoney(invoice.calendar, invoice.surcharge, invoice.currency);
                                actualTotal += invoice.GetAmount(doesIncludeSurcharge);
                                // count parts
                                if (partsMap.ContainsKey(invoice.orderNum))
                                {
                                    foreach (string part in partsMap[invoice.orderNum])
                                    {
                                        if (0 == part.CompareTo("NCR"))
                                        {
                                            ncrList[month]++;
                                        }
                                        else if (part.Contains("HD") || part.Contains("HU"))
                                        {
                                            hollowList[month]++;
                                        }
                                        else if (part.Contains("BA") || part.Contains("SD") || part.Contains("BO") || part.Contains("FD") || part.Contains("RI") )//|| part.Contains("SO") || part.Contains("BK"))
                                        {
                                            solidList[month]++;
                                        }
                                    }
                                }
                            }
                            else if (invoice.calendar.GetFiscalYear() == fiscalYear - 1 && invoice.calendar.GetFiscalMonth() > 9)
                            {
                                actualList[month - 9] += invoice.GetAmount(doesIncludeSurcharge);
                                surchargeList[month - 9] += new ExcoMoney(invoice.calendar, invoice.surcharge, invoice.currency); 
                                actualTotal += invoice.GetAmount(doesIncludeSurcharge);
                                // count parts
                                if (partsMap.ContainsKey(invoice.orderNum))
                                {
                                    foreach (string part in partsMap[invoice.orderNum])
                                    {
                                        if (0 == part.CompareTo("NCR"))
                                        {
                                            ncrList[month - 9]++;
                                        }
                                        else if (part.Contains("HD") || part.Contains("HU"))
                                        {
                                            hollowList[month - 9]++;
                                        }
                                        else if (part.Contains("BA") || part.Contains("SD") || part.Contains("BO") || part.Contains("FD") || part.Contains("RI") )//|| part.Contains("SO") || part.Contains("BK"))
                                        {
                                            solidList[month - 9]++;
                                        }
                                    }
                                }
                            }
                            // build actual list last year
                            else if (invoice.calendar.GetFiscalYear() == fiscalYear - 1 && invoice.calendar.GetFiscalMonth() < 10)
                            {
                                actualListLastYear[month + 3] += invoice.GetAmount(doesIncludeSurcharge);
                                actualTotalLastYear += invoice.GetAmount(doesIncludeSurcharge);
                            }
                            else if (invoice.calendar.GetFiscalYear() == fiscalYear - 2 && invoice.calendar.GetFiscalMonth() > 9)
                            {
                                actualListLastYear[month - 9] += invoice.GetAmount(doesIncludeSurcharge);
                                actualTotalLastYear += invoice.GetAmount(doesIncludeSurcharge);
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < 12; i++)
            {
                // get budget data this year
                ExcoCalendar calendar = new ExcoCalendar(fiscalYear, i + 1, true, plantID);
                ExcoMoney budget = new ExcoMoney();
                if (budgetMap.ContainsKey(excoCustomer.ShipToID))
                {
                    budget = budgetMap[excoCustomer.ShipToID][i];
                }
                else if (budgetMap.ContainsKey(excoCustomer.BillToID))
                {
                    budget = budgetMap[excoCustomer.BillToID][i];
                }
                else if (budgetMap.ContainsKey(excoCustomer.SillyID))
                {
                    budget = budgetMap[excoCustomer.SillyID][i];
                }
                budgetTotal += budget;
                budgetList[i + 1] = budget;
            }
        }
    }
}