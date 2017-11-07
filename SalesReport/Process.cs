using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;
using System.Net.Mail;
using System.Net;
using Excel = Microsoft.Office.Interop.Excel;

namespace SalesReport
{
    #region Initializer Variables
    // NOTE:
    // All four plants starts from Oct to September next year
    // Markham, Michigan and Texas follow fiscal period
    // Colombia breaks fiscal period


    //Modification By Gary 20140428
    //Add title name for each customer in all 3 rows
    /*  Change from 
     *      sheet.Cells[row, col].NumberFormat = "@";
            sheet.Cells[row, col++] = cust.excoCustomer.BillToID;
            sheet.Cells[row, col++] = cust.excoCustomer.Name;
            sheet.Cells[row, col++] = cust.excoCustomer.Territory;
            sheet.Cells[row, col++] = cust.excoCustomer.Currency;

     *  to
            sheet.Cells[row, col].NumberFormat = "@";
            sheet.Cells[row, col++] = cust.excoCustomer.BillToID;
            sheet.Cells[row+1, col-1].NumberFormat = "@";
            sheet.Cells[row+1, col-1] = cust.excoCustomer.BillToID;
            sheet.Cells[row+2, col-1].NumberFormat = "@";
            sheet.Cells[row+2, col-1] = cust.excoCustomer.BillToID;
            sheet.Cells[row, col++] = cust.excoCustomer.Name;
            sheet.Cells[row+1, col-1] = cust.excoCustomer.Name;
            sheet.Cells[row+2, col-1] = cust.excoCustomer.Name;
            sheet.Cells[row, col++] = cust.excoCustomer.Territory;
            sheet.Cells[row+1, col-1] = cust.excoCustomer.Territory;
            sheet.Cells[row+2, col-1] = cust.excoCustomer.Territory;
            sheet.Cells[row, col++] = cust.excoCustomer.Currency;
            sheet.Cells[row+1, col-1] = cust.excoCustomer.Currency;
            sheet.Cells[row+2, col-1] = cust.excoCustomer.Currency;
     */
    public class Process
    {
        public Plant marPlant = new Plant(1, "CA");
        public Plant micPlant = new Plant(3, "US");
        public Plant texPlant = new Plant(5, "US");
        public Plant colPlant = new Plant(4, "CP");
        public int[] solidCount = new int[12];
        public int[] hollowCount = new int[12];
        public int[] ncrCount = new int[12];

        private double Markham_Surcharge_Budget_Adj = 1.08; // 8% increase
        private double Other_Surcharge_Budget_Adj = 1.07; // 8% increase

        // invoice map
        public Dictionary<int, Invoice> invoiceMap = new Dictionary<int, Invoice>();
        // customer bill-to map
        public Dictionary<string, ExcoCustomer> customerBillToMap = new Dictionary<string, ExcoCustomer>();
        // customer ship-to map
        public Dictionary<string, ExcoCustomer> customerShipToMap = new Dictionary<string, ExcoCustomer>();
        // customer silly map
        public Dictionary<string, ExcoCustomer> customerSillyMap = new Dictionary<string, ExcoCustomer>();
        // markham budget map
        public Dictionary<string, List<ExcoMoney>> markhamBudgetMap = new Dictionary<string, List<ExcoMoney>>();
        // michigan budget map
        public Dictionary<string, List<ExcoMoney>> michiganBudgetMap = new Dictionary<string, List<ExcoMoney>>();
        // texas budget map
        public Dictionary<string, List<ExcoMoney>> texasBudgetMap = new Dictionary<string, List<ExcoMoney>>();
        // colombia budget map
        public Dictionary<string, List<ExcoMoney>> colombiaBudgetMap = new Dictionary<string, List<ExcoMoney>>();
        // markham order and parts map
        public Dictionary<int, List<string>> partMarkhamMap = new Dictionary<int, List<string>>();
        // michigan order and parts map
        public Dictionary<int, List<string>> partMichiganMap = new Dictionary<int, List<string>>();
        // texas order and parts map
        public Dictionary<int, List<string>> partTexasMap = new Dictionary<int, List<string>>();
        // colombia order and parts map
        public Dictionary<int, List<string>> partColombiaMap = new Dictionary<int, List<string>>();
        // flags of including steel surcharge
        public bool doesIncludeSurcharge = false;
        // fiscal year
        public int fiscalYear = 18;
        // file path
        public string filePath = string.Empty;
        // receiver address
        public string receiver = "rwieseler@etsdies.com";
        // sender address
        public string sender = "report@etsdies.com";
        // sender password
        public string password = "";
        // smtp address
        public string smtpAddress = "smtp.pathcom.com";
        // smtp port
        public int port = 587;
    #endregion


        // constructor
        public Process()
        {
            // get list of customers
            List<ExcoCustomer> customerList = ExcoCustomerTable.Instance.GetAllCustomers();
            Console.WriteLine("Get All Customers Done");
            // fill bill-to map and ship-to map
            foreach (ExcoCustomer customer in customerList)
            {
                customerBillToMap.Add(customer.BillToID, customer);
                customerShipToMap.Add(customer.ShipToID, customer);
                customerSillyMap.Add(customer.SillyID, customer);
            }
        }
        

        // Get Yearly static exchange rate
        private double GET_BUDGET_EXCHANGE_RATE(int fiscal_year, string plant)
        {
            if (plant.Contains("4"))
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1750;
                    case 11:
                        return 1750;
                    case 12:
                        return 1750;
                    case 13:
                        return 1750;
                    case 14:
                        return 1750;
                    case 15:
                        return 1750;
                    case 16:
                        return 1900;
                    case 17:
                        return 3000;
                    case 18:
                        return 2730;
                    default:
                        return 1750;
                }
            }
            else if (plant == "3" || plant == "5")
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1.11;
                    case 11:
                        return 1.11;
                    case 12:
                        return 1.11;
                    case 13:
                        return 1.11;
                    case 14:
                        return 1.11;
                    case 15:
                        return 1.11;
                    case 16:
                        return 1.11;
                    case 17:
                        return 1.11;
                    default:
                        return 1.11;
                }
            }
            else // Markham
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1.2;
                    case 11:
                        return 1.2;
                    case 12:
                        return 1.2;
                    case 13:
                        return 1.2;
                    case 14:
                        return 1.2;
                    case 15:
                        return 1.2;
                    case 16:
                        return 1.2;
                    case 17:
                        return 1.2;
                    case 18:
                        return 1.3;
                    default:
                        return 1.3;
                }
            }
        }

        public string PartsQuery(int plantID, int m, int year, string partsType)
        { //Robin added to simplify query controls to reduce redundancy
            #region Initializers for date control
            int fiscYear = year - 1;
            int month = m;
            if (month > 12)
            {
                month = month - 12;
                fiscYear++;
            }
            string query = "";
            #endregion
            if (partsType == "hollow")
            {
                #region Hollow Query
                query = "select count(*) as count from d_order, d_orderitem " +
                "where month(invoicedate) = '" + month.ToString() + "' and year(invoicedate) = '20" + fiscYear.ToString() + "' " +
                "and d_order.ordernumber = d_orderitem.ordernumber " +
                "and d_orderitem.line = 1 and d_orderitem.dienumber is not NULL " +
                "and (d_orderitem.prefix='BD' OR d_orderitem.prefix='HO' OR d_orderitem.prefiX='HE' OR d_orderitem.prefix='HI' " +
                "or d_orderitem.prefix='HN' OR d_orderitem.prefix='HT' OR d_orderitem.prefix='MA' OR d_orderitem.prefix='PL') ";      
                #endregion
            }
            else if (partsType == "solid")
            {
                #region Solid Query
                query = "select count(*) as count from d_order, d_orderitem " +
                "where month(invoicedate) = '" + month.ToString() + "' and year(invoicedate) = '20" + fiscYear.ToString() + "' " +
                "and d_order.ordernumber = d_orderitem.ordernumber " +
                "and d_orderitem.line = 1 and d_orderitem.dienumber is not NULL " +
                "and d_orderitem.prefix<>'BD' AND d_orderitem.prefix<>'BO' AND d_orderitem.prefix<>'HO' AND d_orderitem.prefix<>'HE' " +
                "and d_orderitem.prefix<>'HI' AND d_orderitem.prefix<>'HN' AND d_orderitem.prefix<>'HT' AND d_orderitem.prefix<>'MA' " +
                "and d_orderitem.prefix<>'PL' " +
                "and (d_orderitem.suffix LIKE 'I00%' or d_orderitem.suffix LIKE 'M0%') and d_orderitem.prefix<>'MI' ";
                #endregion
            }
            else if (partsType == "misc")
            {
                #region MISC Query (Includes Bolster and Ring)
                query = "select count(*) as count from d_order, d_orderitem " +
                "where month(invoicedate) = '" + month.ToString() + "' and year(invoicedate) = '20" + fiscYear.ToString() + "' " +
                "and d_order.ordernumber = d_orderitem.ordernumber " +
                "and d_orderitem.line = 1 and d_orderitem.dienumber is not NULL " +
                "and (d_orderitem.prefix='BO' or d_orderitem.prefix='RI' or d_orderitem.prefix='MI')";
                #endregion
            }
            else if (partsType == "ncr")
            {
                #region NCR Query
                if (!(plantID == 4))
                {
                    query = "SELECT count(*) from (" +
                        "select DISTINCT customercode, d_order.ordernumber, customerpo, orderdate,invoicedate, description,	" +
                        "d_orderitem.dienumber " +
                        "FROM d_order, d_orderitem, d_task as task " +
                        "WHERE d_order.ordernumber = d_orderitem.ordernumber " +
                        "AND customerpo not like '%cancel%' " +
                        "AND d_order.ordernumber = task.ordernumber " +
                        "AND (sales = 0 or d_order.discountontotal ='1') " +
                        "AND total='0' AND shipdate <> '' AND invoicedate <> '' " +
                        "AND exists (select * from d_orderitem where (description <> '' " +
                        "OR (note not like '%cancel%' and note not like '%duplicat%')) " +
                        "AND d_orderitem.ordernumber = d_order.ordernumber) " +
                        "AND month(invoicedate) = '" + month.ToString() + "' and year(invoicedate) = '20" + fiscYear.ToString() + "' " +
                        "AND (ncrs=0 or ncrs is null) AND cor=0 AND wr=0 " +
                        ") as count1 ";
                }
                else
                { //Different query for Colombia
                    query = "SELECT count(*) from (" +
                        "select DISTINCT customercode, d_order.ordernumber, customerpo, orderdate,invoicedate, description,	" +
                        "d_orderitem.dienumber " +
                        "FROM d_order, d_orderitem, d_task as task " +
                        "WHERE d_order.ordernumber = d_orderitem.ordernumber " +
                        "AND customerpo not like '%cancel%' " +
                        "AND d_order.ordernumber = task.ordernumber " +
                        "AND (sales = 0 or d_order.discountontotal ='1') " +
                        "AND total='0' AND shipdate <> '' AND invoicedate <> '' " +
                        "AND exists (select * from d_orderitem where (description <> '' " +
                        "OR (note not like '%cancel%' and note not like '%duplicat%')) " +
                        "AND d_orderitem.ordernumber = d_order.ordernumber) " +
                        "AND month(invoicedate) = '" + month.ToString() + "' and year(invoicedate) = '20" + fiscYear.ToString() + "' " +
                        "AND (ncr=1 or ncrs=1) " +
                        ") as count1 ";
                }
            #endregion
            }
        return query;
        }

        public void Run(bool isNeedSurcharge)
        {

            doesIncludeSurcharge = isNeedSurcharge;
            // get customer, currency, territory, plant and year/period
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            // ORIGINAL string query = "select dhinv#, dhbcs#, dhscs#, dhcurr, dhterr, dhplnt, dhidat, dhord#, dhincr from cmsdat.oih where dhpost='Y' and dharyr>=" + (fiscalYear - 2).ToString();
            //OUR CURRENT ONE 
            string query = "select  dhinv#, dhbcs#, dhscs#, dhcurr, dhterr, dhplnt, dhidat, dhord#, dhincr from cmsdat.oih where DHBCS# not like '000265S%' and dhpost='Y' and dharyr>=" + (fiscalYear - 2).ToString();

            //string query = "select dhinv#, dhbcs#, dhscs#, dhcurr, dhterr, dhplnt, dhidat, dhord#, dhincr  from cmsdat.oih where DHBNAM like '%Old%' and dhpost='Y' and dharyr = 16";
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                int invNum = Convert.ToInt32(reader["dhinv#"]);
                int soNum = Convert.ToInt32(reader["dhord#"]);
                string billTo = reader["dhbcs#"].ToString().Trim();
                string shipTo = reader["dhscs#"].ToString().Trim();
                string currency = reader["dhcurr"].ToString().Trim();
                string territory = reader["dhterr"].ToString().Trim();
                int plant = Convert.ToInt32(reader["dhplnt"]);
                int invoiceYear = Convert.ToDateTime(reader["dhidat"]).Year - 2000;
                int invoiceMonth = Convert.ToDateTime(reader["dhidat"]).Month;
                char creditNote = Convert.ToChar(reader["dhincr"]);
                ExcoCustomer customer;
                if (customerBillToMap.ContainsKey(billTo))
                {
                    customer = customerBillToMap[billTo];
                }
                else if (customerShipToMap.ContainsKey(billTo))
                {
                    customer = customerShipToMap[billTo];
                }
                else if (customerSillyMap.ContainsKey(billTo))
                {
                    customer = customerSillyMap[billTo];
                }
                else if (customerBillToMap.ContainsKey(shipTo))
                {
                    customer = customerBillToMap[shipTo];
                }
                else if (customerShipToMap.ContainsKey(shipTo))
                {
                    customer = customerShipToMap[shipTo];
                }
                else if (customerSillyMap.ContainsKey(shipTo))
                {
                    customer = customerSillyMap[shipTo];
                }
                else
                {
                    throw new Exception("Unknown customer: " + billTo + " " + shipTo + " invoice#:" + invNum.ToString());
                }
                Invoice invoice = new Invoice();
                invoice.orderNum = soNum;
                invoice.invoiceNum = invNum;
                invoice.customer = customer;
                invoice.currency = currency;
                invoice.territory = territory;
                invoice.plant = plant;
                invoice.creditNote = creditNote;
                invoice.calendar = new ExcoCalendar(invoiceYear, invoiceMonth, false, plant);
                invoiceMap.Add(invNum, invoice);
            }
            reader.Close();
            Console.WriteLine("Get Invoice Details Done");
            // get sales
            query = "select diinv#, coalesce(sum(dipric*(max(diqtso,diqtsp))), 0.0) as sale from cmsdat.oid where diglcd='SAL' group by diinv#";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int invNum = Convert.ToInt32(reader[0]);
                if (invoiceMap.ContainsKey(invNum))
                {
                    invoiceMap[invNum].sale += Convert.ToDouble(reader
[1]);
                }
            }
            reader.Close();
            Console.WriteLine("Get Sales Map Done");
            // get discount map
            query = "select flinv#, coalesce(sum(fldext), 0.0) from cmsdat.ois where fldisc like 'D%' or fldisc like 'M%' group by flinv#";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int invNum = Convert.ToInt32(reader[0]);
                if (invoiceMap.ContainsKey(invNum))
                {
                    invoiceMap[invNum].discount += Convert.ToDouble(reader[1]);
                }
            }
            reader.Close();
            Console.WriteLine("Get Discount Map Done");
            // get fast track map
            query = "select flinv#, coalesce(sum(fldext), 0.0) from cmsdat.ois where fldisc like 'F%' group by flinv#";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int invNum = Convert.ToInt32(reader[0]);
                if (invoiceMap.ContainsKey(invNum))
                {
                    invoiceMap[invNum].fastTrack += Convert.ToDouble(reader[1]);
                }
            }
            reader.Close();
            Console.WriteLine("Get Fast Track Map Done");
            // get steel surcharge map
            query = "select flinv#, coalesce(sum(fldext), 0.0) from cmsdat.ois where fldisc like 'S%' or fldisc like 'P%' group by flinv#";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int invNum = Convert.ToInt32(reader[0]);
                if (invoiceMap.ContainsKey(invNum))
                {
                    invoiceMap[invNum].surcharge += Convert.ToDouble(reader[1]);
                }
            }
            reader.Close();
            Console.WriteLine("Get Steel Surcharge Done");
            // adjust credit note
            foreach (Invoice invoice in invoiceMap.Values)
            {
                if ('C' == invoice.creditNote)
                {
                    if (invoice.sale > 0.0)
                    {
                        invoice.discount *= -1.0;
                        invoice.fastTrack *= -1.0;
                        invoice.sale *= -1.0;
                        invoice.surcharge *= -1.0;
                    }
                }
            }
            // get markham budgets
            database.Open(Database.DECADE_MARKHAM);
            query = "select CustomerID, Currency, Period01, Period02, Period03, Period04, Period05, Period06, Period07, Period08, Period09, Period10, Period11, Period12 from tiger.dbo.Markham_Budget where Year=20" + fiscalYear.ToString();
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string currency = reader[1].ToString();
                List<ExcoMoney> budgetList = new List<ExcoMoney>();
                for (int i = 0; i < 12; i++)
                {
                    ExcoMoney budget = new ExcoMoney(new ExcoCalendar(fiscalYear, i + 1, true, 1), Convert.ToDouble(reader[i + 2]) * (doesIncludeSurcharge ? Markham_Surcharge_Budget_Adj : 1), currency);
                    budgetList.Add(budget);
                }
                markhamBudgetMap.Add(reader[0].ToString().Trim(), budgetList);
            }
            reader.Close();
            Console.WriteLine("Get Markham Budget Map Done");
            // get colombia budgets
            query = "select CustomerID, Currency, Period01, Period02, Period03, Period04, Period05, Period06, Period07, Period08, Period09, Period10, Period11, Period12 from tiger.dbo.Colombia_Budget where Year=20" + fiscalYear.ToString();
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string currency = reader[1].ToString();
                List<ExcoMoney> budgetList = new List<ExcoMoney>();
                for (int i = 0; i < 12; i++)
                {
                    ExcoMoney budget = new ExcoMoney(new ExcoCalendar(fiscalYear, i + 1, true, 1), Convert.ToDouble(reader[i + 2]) * (doesIncludeSurcharge ? Other_Surcharge_Budget_Adj : 1), currency);
                    budgetList.Add(budget);
                }
                colombiaBudgetMap.Add(reader[0].ToString().Trim(), budgetList);
            }
            reader.Close();
            Console.WriteLine("Get Colombia Budget Map Done");
            // get michigan budgets
            query = "select CustomerID, Currency, Period01, Period02, Period03, Period04, Period05, Period06, Period07, Period08, Period09, Period10, Period11, Period12 from tiger.dbo.Michigan_Budget where Year=20" + fiscalYear.ToString();
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string currency = reader[1].ToString();
                List<ExcoMoney> budgetList = new List<ExcoMoney>();
                for (int i = 0; i < 12; i++)
                {
                    ExcoMoney budget = new ExcoMoney(new ExcoCalendar(fiscalYear, i + 1, true, 3), Convert.ToDouble(reader[i + 2]) * (doesIncludeSurcharge ? Other_Surcharge_Budget_Adj : 1), currency);
                    budgetList.Add(budget);
                }
                michiganBudgetMap.Add(reader[0].ToString().Trim(), budgetList);
            }
            reader.Close();
            Console.WriteLine("Get Michigan Budget Map Done");
            // get texas budgets
            query = "select CustomerID, Currency, Period01, Period02, Period03, Period04, Period05, Period06, Period07, Period08, Period09, Period10, Period11, Period12 from tiger.dbo.Texas_Budget where Year=20" + fiscalYear.ToString();
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string currency = reader[1].ToString();
                List<ExcoMoney> budgetList = new List<ExcoMoney>();
                for (int i = 0; i < 12; i++)
                {
                    ExcoMoney budget = new ExcoMoney(new ExcoCalendar(fiscalYear, i + 1, true, 5), Convert.ToDouble(reader[i + 2]) * (doesIncludeSurcharge ? Other_Surcharge_Budget_Adj : 1), currency);
                    budgetList.Add(budget);
                }
                texasBudgetMap.Add(reader[0].ToString().Trim(), budgetList);
            }
            reader.Close();
            Console.WriteLine("Get Texas Budget Map Done");
            // get parts in Markham
            database.Open(Database.CMSDAT);
            query = "select diord#, dimajr, didesc, dipart from cmsdat.oid where distkl='001PRD'";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["diord#"]);
                string part = reader["dipart"].ToString().Trim();
                string desc = reader["didesc"].ToString().Trim();
                string type = reader["dimajr"].ToString().Trim();
                if (desc.Contains("NCR ") || part.Contains("NCR "))
                {
                    type = "NCR";
                }
                if (partMarkhamMap.ContainsKey(soNum))
                {
                    partMarkhamMap[soNum].Add(type);
                }
                else
                {
                    List<string> typeList = new List<string>();
                    typeList.Add(type);
                    partMarkhamMap.Add(soNum, typeList);
                }
            }
            reader.Close();
            Console.WriteLine("Get Parts in Markham Map Done");
            // get parts in Michigan
            database.Open(Database.CMSDAT);
            query = "select diord#, dimajr, didesc, dipart from cmsdat.oid where distkl='003PRD'";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["diord#"]);
                string part = reader["dipart"].ToString().Trim();
                string desc = reader["didesc"].ToString().Trim();
                string type = reader["dimajr"].ToString().Trim();
                if (desc.Contains("NCR ") || part.Contains("NCR "))
                {
                    type = "NCR";
                }
                if (partMichiganMap.ContainsKey(soNum))
                {
                    partMichiganMap[soNum].Add(type);
                }
                else
                {
                    List<string> typeList = new List<string>();
                    typeList.Add(type);
                    partMichiganMap.Add(soNum, typeList);
                }
            }
            reader.Close();
            Console.WriteLine("Get Parts in Michigan Map Done");
            // get parts in Texas
            database.Open(Database.CMSDAT);
            query = "select diord#, dimajr, didesc, dipart from cmsdat.oid where distkl='005PRD'";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["diord#"]);
                string part = reader["dipart"].ToString().Trim();
                string desc = reader["didesc"].ToString().Trim();
                string type = reader["dimajr"].ToString().Trim();
                if (desc.Contains("NCR ") || part.Contains("NCR "))
                {
                    type = "NCR";
                }
                if (partTexasMap.ContainsKey(soNum))
                {
                    partTexasMap[soNum].Add(type);
                }
                else
                {
                    List<string> typeList = new List<string>();
                    typeList.Add(type);
                    partTexasMap.Add(soNum, typeList);
                }
            }
            reader.Close();
            Console.WriteLine("Get Parts in Texas Map Done");
            // get parts in Colombia
            database.Open(Database.CMSDAT);
            query = "select diord#, dimajr, didesc, dipart from cmsdat.oid where distkl='004PRD'";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int soNum = Convert.ToInt32(reader["diord#"]);
                string part = reader["dipart"].ToString().Trim();
                string desc = reader["didesc"].ToString().Trim();
                string type = reader["dimajr"].ToString().Trim();
                if (desc.Contains("NCR ") || part.Contains("NCR "))
                {
                    type = "NCR";
                }
                if (partColombiaMap.ContainsKey(soNum))
                {
                    partColombiaMap[soNum].Add(type);
                }
                else
                {
                    List<string> typeList = new List<string>();
                    typeList.Add(type);
                    partColombiaMap.Add(soNum, typeList);
                }
            }
            reader.Close();
            Console.WriteLine("Get Parts in Colombia Map Done");
            // build plant data structure
            foreach (ExcoCustomer customer in customerBillToMap.Values)
            {
                marPlant.AddCustomer(customer, invoiceMap, fiscalYear, doesIncludeSurcharge, markhamBudgetMap, partMarkhamMap);
                micPlant.AddCustomer(customer, invoiceMap, fiscalYear, doesIncludeSurcharge, michiganBudgetMap, partMichiganMap);
                texPlant.AddCustomer(customer, invoiceMap, fiscalYear, doesIncludeSurcharge, texasBudgetMap, partTexasMap);
                colPlant.AddCustomer(customer, invoiceMap, fiscalYear, doesIncludeSurcharge, colombiaBudgetMap, partColombiaMap);
                Console.WriteLine("Get Customer Details Done: " + customer.Name);
            }
            marPlant.GetSurcharge();
            marPlant.CountParts();
            micPlant.GetSurcharge();
            micPlant.CountParts();
            texPlant.GetSurcharge();
            texPlant.CountParts();
            colPlant.GetSurcharge();
            colPlant.CountParts();
            // create excel object
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            //[1],[2],[3]
            Excel.Worksheet micSheet = book.Worksheets.Add();
            micSheet.Name = "Michigan 20" + fiscalYear.ToString();
            Excel.Worksheet texSheet = book.Worksheets.Add();
            texSheet.Name = "Texas 20" + fiscalYear.ToString();
            Excel.Worksheet colSheet = book.Worksheets.Add();
            colSheet.Name = "Colombia 20" + fiscalYear.ToString();
            Excel.Worksheet marSheet = book.Worksheets.Add();
            marSheet.Name = "Markham 20" + fiscalYear.ToString();

            #region Michigan plant aggregation
            // Aggregate michigan accounts 0003020S to 0003030S (astrex ca to astrex us)
            // Aggregate michigan accounts 00006800 to 0003025S (signature ca to signature us)

            //foreach (Customer customer in plant.custList)
            for (int j = 0; j < micPlant.custList.Count; j++)
            {
                Customer customer = micPlant.custList[j];

                if (customer.excoCustomer.BillToID == "0003020S")
                {
                    Customer c = micPlant.custList.First(x => x.excoCustomer.BillToID == "0003030S");

                    if (c == null) continue;

                    for (int i = 1; i <= 12; i++)
                    {
                        c.actualList[i] += customer.actualList[i];
                        c.budgetList[i] += customer.budgetList[i];
                        c.actualListLastYear[i] += customer.actualListLastYear[i];
                    }
                    micPlant.custList.RemoveAt(j);
                }
                else if (customer.excoCustomer.BillToID == "00006800")
                {
                    Customer c = micPlant.custList.First(x => x.excoCustomer.BillToID == "0003025S");

                    if (c == null) continue;

                    for (int i = 1; i <= 12; i++)
                    {
                        c.actualList[i] += customer.actualList[i];
                        c.budgetList[i] += customer.budgetList[i];
                        c.actualListLastYear[i] += customer.actualListLastYear[i];
                    }
                    micPlant.custList.RemoveAt(j);
                }
            }
            #endregion

            // write to sheet
            FillSheet(marSheet, marPlant);
            Console.WriteLine("Write Markham Sheet Done");
            FillSheet(micSheet, micPlant);
            Console.WriteLine("Write Michigan Sheet Done");
            FillSheet(texSheet, texPlant);
            Console.WriteLine("Write Texas Sheet Done");
            FillSheet(colSheet, colPlant);
            Console.WriteLine("Write Colombia Sheet Done");
            // output to file
            filePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Sales Report 20" + fiscalYear.ToString() + " generated at " + DateTime.Today.ToString("MM-dd-yyyy") + ".xlsx");
            File.Delete(filePath);
            book.SaveAs(filePath, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(filePath);
        }

        public void SendFileViaEmail()
        {
            // email body
            MailMessage mailmsg = new MailMessage();
            mailmsg.To.Add(receiver);
            mailmsg.From = new MailAddress(sender);
            mailmsg.Subject = "Sales Report of Last Month";
            mailmsg.Attachments.Add(new Attachment(filePath));
            // smtp client
            SmtpClient client = new SmtpClient(smtpAddress, port);
            client.Credentials = new NetworkCredential(sender, password);
            client.Send(mailmsg);
        }

        private void FillSheet(Excel.Worksheet sheet, Plant plant)
        {
            #region Fill Sheet
            // insert title
            string title = sheet.Name + " Sales Report ";
            if (doesIncludeSurcharge)
            {
                title += "(With Surcharge)";
            }
            else
            {
                title += "(Without Surcharge)";
            }
            sheet.Cells[1, 1] = title;
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            // build header
            int row = 3;
            int col = 1;
            sheet.Cells[row, col++] = "Cust #";
            sheet.Cells[row, col++] = "Cust Name";
            sheet.Cells[row, col++] = "Territory";
            sheet.Cells[row, col++] = "Currency";
            sheet.Cells[row, col++] = "";
            sheet.Cells[row, col++] = "Oct";
            sheet.Cells[row, col++] = "Nov";
            sheet.Cells[row, col++] = "Dec";
            sheet.Cells[row, col++] = "Jan";
            sheet.Cells[row, col++] = "Feb";
            sheet.Cells[row, col++] = "Mar";
            sheet.Cells[row, col++] = "Apr";
            sheet.Cells[row, col++] = "May";
            sheet.Cells[row, col++] = "Jun";
            sheet.Cells[row, col++] = "Jul";
            sheet.Cells[row, col++] = "Aug";
            sheet.Cells[row, col++] = "Sep";
            sheet.Cells[row, col++] = "Yearly Total";
            Excel.Range headerRange = sheet.Cells.get_Range("A" + row.ToString(), "R" + row.ToString());
            headerRange.Font.Bold = true;
            headerRange.Cells.Interior.ColorIndex = 40;
            headerRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
            // 
            // check currency
            bool needCAD = false;
            bool needPESO = false;
            bool needUSD = false;
            foreach (Customer cust in plant.custList)
            {
                // skip inactive customer
                if (cust.actualTotal.IsZero() && cust.budgetTotal.IsZero() && cust.actualTotalLastYear.IsZero() && cust.actualTotalLastYear.IsZero())
                {
                   continue;
                }
                if (cust.excoCustomer.Currency.Contains("CA"))
                {
                    needCAD = true;
                }
                if (cust.excoCustomer.Currency.Contains("CP"))
                {
                    needPESO = true;
                }
                if (cust.excoCustomer.Currency.Contains("US"))
                {
                    needUSD = true;
                }
            }
            // write content in CAD
            int cadSumRow = 0;
            int usdSumRow = 0;
            int cpSumRow = 0;

            string currentTerritory = "";
            int territoryRow = 3;

            Dictionary<string, List<int>> indexDict = new Dictionary<string, List<int>>();
            
            
            if (needCAD)
            {
                int custCount = 0;
                int cadStartRow = row;
                foreach (Customer cust in plant.custList)
                {

                    // skip inactive customer
                    if (cust.actualTotal.IsZero() && cust.budgetTotal.IsZero() && cust.actualTotalLastYear.IsZero())
                    {
                        continue;
                    }

                    // write CAD
                    if (cust.excoCustomer.Currency.Contains("CA"))
                    {
                        custCount++;

                        #region Check if new territory
                        if (cust.excoCustomer.Territory != currentTerritory && currentTerritory != "") // if new territory, calculate previous balances
                        {
                            WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + cust.excoCustomer.Currency, indexDict[currentTerritory + "-" + cust.excoCustomer.Currency]);
                            row += 3;
                            territoryRow = row;
                        }
                        else // if not new territory
                        {
                        }

                        // add territory index
                        if (indexDict.ContainsKey(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency))
                        {
                            indexDict[cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency].Add(row);
                        }
                        else
                        {
                            indexDict.Add(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency, new List<int>() { row });
                        }

                        // add currency index
                        if (indexDict.ContainsKey("CAD"))
                        {
                            indexDict["CAD"].Add(row);
                        }
                        else
                        {
                            indexDict.Add("CAD", new List<int>() { row });
                        }

                        currentTerritory = cust.excoCustomer.Territory;
                        #endregion

                        col = 1;
                        sheet.Cells[row, col].NumberFormat = "@";
                        sheet.Cells[row, col++] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+1, col-1].NumberFormat = "@";
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+2, col-1].NumberFormat = "@";
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row, col++] = cust.excoCustomer.Name;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row, col++] = cust.excoCustomer.Territory;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row, col++] = cust.excoCustomer.Currency;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Currency;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Currency;
                        WriteCustomer(sheet, cust, row, col);
                        row += 3;

                    }
                }

                // last customer in list. print out territory
                WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + "CA", indexDict[currentTerritory + "-" + "CA"]);
                row += 1;
                territoryRow = row;

                cadSumRow = WriteCurrencySummary(sheet, cadStartRow, ref row, "CAD", indexDict["CAD"]) - 2;
                row += 5;
            }
            if (needPESO)
            {
                currentTerritory = "";
                int custCount = 0;
                int pesoStartRow = row;
                // write content in PESO
                foreach (Customer cust in plant.custList)
                {
                    // skip inactive customer
                    if (cust.actualTotal.IsZero() && cust.budgetTotal.IsZero() && cust.actualTotalLastYear.IsZero())
                    {
                        continue;
                    }
                    // write CAD
                    if (cust.excoCustomer.Currency.Contains("CP"))
                    {
                        custCount++;

                        #region Check if new territory
                        if (cust.excoCustomer.Territory != currentTerritory && currentTerritory != "") // if new territory, calculate previous balances
                        {
                            WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + cust.excoCustomer.Currency, indexDict[currentTerritory + "-" + cust.excoCustomer.Currency]);
                            row += 3;
                            territoryRow = row;
                        }
                        else // if not new territory
                        {
                        }

                        // add territory index
                        if (indexDict.ContainsKey(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency))
                        {
                            indexDict[cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency].Add(row);
                        }
                        else
                        {
                            indexDict.Add(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency, new List<int>() { row });
                        }

                        // add currency index
                        if (indexDict.ContainsKey("PESO"))
                        {
                            indexDict["PESO"].Add(row);
                        }
                        else
                        {
                            indexDict.Add("PESO", new List<int>() { row });
                        }

                        currentTerritory = cust.excoCustomer.Territory;
                        #endregion

                        col = 1;
                        sheet.Cells[row, col].NumberFormat = "@";
                        sheet.Cells[row, col++] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+1, col-1].NumberFormat = "@";
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+2, col-1].NumberFormat = "@";
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row, col++] = cust.excoCustomer.Name;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row, col++] = cust.excoCustomer.Territory;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row, col++] = cust.excoCustomer.Currency;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Currency;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Currency;
                        WriteCustomer(sheet, cust, row, col);
                        row += 3;
                    }
                }

                // last customer in list. print out territory
                WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + "CP", indexDict[currentTerritory + "-" + "CP"]);
                row += 1;
                territoryRow = row;

                cpSumRow = WriteCurrencySummary(sheet, pesoStartRow, ref row, "PESO", indexDict["PESO"]) - 2;
                row += 5;
            }
            if (needUSD)
            {
                currentTerritory = "";
                int custCount = 0;
                // write content in USD
                int usdStartRow = row;
                foreach (Customer cust in plant.custList)
                {
                    // skip inactive customer
                    if (cust.actualTotal.IsZero() && cust.budgetTotal.IsZero() && cust.actualTotalLastYear.IsZero())
                    {
                        continue;
                    }
                    // write USD
                    if (cust.excoCustomer.Currency.Contains("US"))
                    {
                        custCount++;

                        #region Check if new territory
                        if (cust.excoCustomer.Territory != currentTerritory && currentTerritory != "") // if new territory, calculate previous balances
                        {
                            WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + cust.excoCustomer.Currency, indexDict[currentTerritory + "-" + cust.excoCustomer.Currency]);
                            row += 3;
                            territoryRow = row;
                        }
                        else // if not new territory
                        {
                        }

                        // add territory index
                        if (indexDict.ContainsKey(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency))
                        {
                            indexDict[cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency].Add(row);
                        }
                        else
                        {
                            indexDict.Add(cust.excoCustomer.Territory + "-" + cust.excoCustomer.Currency, new List<int>() { row });
                        }

                        // add currency index
                        if (indexDict.ContainsKey("USD"))
                        {
                            indexDict["USD"].Add(row);
                        }
                        else
                        {
                            indexDict.Add("USD", new List<int>() { row });
                        }

                        currentTerritory = cust.excoCustomer.Territory;
                        #endregion

                        col = 1;
                        sheet.Cells[row, col].NumberFormat = "@";
                        sheet.Cells[row, col++] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+1, col-1].NumberFormat = "@";
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row+2, col-1].NumberFormat = "@";
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.BillToID;
                        sheet.Cells[row, col++] = cust.excoCustomer.Name;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Name;
                        sheet.Cells[row, col++] = cust.excoCustomer.Territory;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Territory;
                        sheet.Cells[row, col++] = cust.excoCustomer.Currency;
                        sheet.Cells[row+1, col-1] = cust.excoCustomer.Currency;
                        sheet.Cells[row+2, col-1] = cust.excoCustomer.Currency;
                        WriteCustomer(sheet, cust, row, col);
                        row += 3;
                    }
                }

                // last customer in list. print out territory
                WriteTerritorySummary(sheet, territoryRow, ref row, currentTerritory + "-" + "USD", indexDict[currentTerritory + "-" + "US"]);
                row += 1;
                territoryRow = row;

                WriteCurrencySummary(sheet, usdStartRow, ref row, "USD", indexDict["USD"]);
                row += 2;
                // convert usd to cad for markham
                if (1 == plant.plantID)
                {
                    List<string> rateListThisYear = new List<string>();
                    List<string> rateListLastYear = new List<string>();
                    for (int period = 1; period <= 12; period++)
                    {
                        rateListThisYear.Add(ExcoExRate.GetToCADRate(new ExcoCalendar(fiscalYear, period, true, 1), "US").ToString("F3"));
                        rateListLastYear.Add(ExcoExRate.GetToCADRate(new ExcoCalendar(fiscalYear - 1, period, true, 1), "US").ToString("F3"));
                    }
                    // write convert rate
                    int column = 4;
                    sheet.Cells[row, column++] = "Convert to CAD";
                    sheet.Cells[row, column++] = "Rate:";
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++] = rateListThisYear[i];
                    }
                    row++;
                    // write actual
                    int index = 0;
                    column = 4;
                    sheet.Cells[row, column++] = "Total (USD):";
                    sheet.Cells[row, column++] = "Actual:";
                    char colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListThisYear[index++];
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    usdSumRow = row;
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write budget
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Budget:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        //sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListThisYear[index++];
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + GET_BUDGET_EXCHANGE_RATE(fiscalYear, "1");
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write last year
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Last Year:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListLastYear[index++];
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    // adjust style
                    Excel.Range range = sheet.get_Range("E" + (row - 2).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("E" + (row - 4).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                    range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.NumberFormat = "$#,##0";

                    // write consolidate data
                    row += 2;
                    column = 4;
                    sheet.Cells[row, column++] = "Consolidated (CAD):";
                    // write actual
                    sheet.Cells[row, column++] = "Actual:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + cadSumRow.ToString() + "+" + colCode + usdSumRow.ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write budget
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Budget:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (cadSumRow + 1).ToString() + "+" + colCode + (usdSumRow + 1).ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write last year
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Last Year:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (cadSumRow + 2).ToString() + "+" + colCode + (usdSumRow + 2).ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();

                    // adjust style
                    range = sheet.get_Range("E" + (row - 2).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("F" + (row - 1).ToString(), "R" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                    range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.NumberFormat = "$#,##0";
                }
                // convert usd to peso
                else if (4 == plant.plantID)
                {
                    List<string> rateListThisYear = new List<string>();
                    List<string> rateListLastYear = new List<string>();
                    for (int period = 1; period <= 12; period++)
                    {
                        //Console.WriteLine("CURRENT YEAR" + ExcoExRate.GetToPESORate(new ExcoCalendar(fiscalYear, period, true, 1), "US").ToString("F2"));
                        //Console.WriteLine("LAST YEAR" + ExcoExRate.GetToPESORate(new ExcoCalendar(fiscalYear - 1, period, true, 1), "US").ToString("F2"));
                        rateListThisYear.Add(ExcoExRate.GetToPESORate(new ExcoCalendar(fiscalYear, period, true, 1), "US").ToString("F2"));
                        rateListLastYear.Add(ExcoExRate.GetToPESORate(new ExcoCalendar(fiscalYear - 1, period, true, 1), "US").ToString("F2"));
                    }
                    // write convert rate
                    int column = 4;
                    sheet.Cells[row, column++] = "Convert to PESO";
                    sheet.Cells[row, column++] = "Rate:";
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++] = rateListThisYear[i];
                    }
                    row++;
                    // write actual
                    int index = 0;
                    column = 4;
                    sheet.Cells[row, column++] = "Total (USD):";
                    sheet.Cells[row, column++] = "Actual:";
                    char colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListThisYear[index++];
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    usdSumRow = row;
                    row++;
                    // write budget
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Budget:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        //sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListThisYear[index++];
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + GET_BUDGET_EXCHANGE_RATE(fiscalYear, "4");
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write last year
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Last Year:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (row - 5).ToString() + "*" + rateListLastYear[index++];
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    // adjust style
                    Excel.Range range = sheet.get_Range("E" + (row - 2).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("E" + (row - 4).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                    range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.NumberFormat = "$#,##0";

                    // write consolidate data
                    row += 2;
                    column = 4;
                    sheet.Cells[row, column++] = "Consolidated (PESO):";
                    // write actual
                    sheet.Cells[row, column++] = "Actual:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + cpSumRow.ToString() + "+" + colCode + usdSumRow.ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write budget
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Budget:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (cpSumRow + 1).ToString() + "+" + colCode + (usdSumRow + 1).ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                    row++;
                    // write last year
                    index = 0;
                    column = 5;
                    sheet.Cells[row, column++] = "Last Year:";
                    colCode = 'F';
                    for (int i = 0; i < 12; i++)
                    {
                        sheet.Cells[row, column++].Formula = "=" + colCode + (cpSumRow + 2).ToString() + "+" + colCode + (usdSumRow + 2).ToString();
                        colCode = Convert.ToChar(Convert.ToInt16(colCode) + 1);
                    }
                    sheet.Cells[row, column++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();


                    // adjust style
                    range = sheet.get_Range("E" + (row - 2).ToString(), "E" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("F" + (row - 1).ToString(), "R" + row.ToString());
                    range.Font.Size = 9;
                    range.Font.ColorIndex = 16;
                    range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                    range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                    range = sheet.get_Range("F" + (row - 2).ToString(), "R" + row.ToString());
                    range.NumberFormat = "$#,##0";
                }
                row += 2;
            }
            // write reconsolidate for Colombia
            if (4 == plant.plantID)
            {
                double[] amount = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

                /*
                #region this year
                // get colombia sales data from database
                // 04
                string query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206010 and aj4ccyy=2014 and aj4comp=4";
                ExcoODBC solarsoft = ExcoODBC.Instance;
                solarsoft.Open(Database.CMSDAT);
                OdbcDataReader reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206010 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206010 and aj4ccyy=2014 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 4;

                sheet.Cells[row, col++] = "Sales rec to P&L";
                sheet.Cells[row, col++] = "Sales Colombia";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // get colombia steels data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206011 and aj4ccyy=2014 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206011 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206011 and aj4ccyy=2014 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 5;
                sheet.Cells[row, col++] = "Sales Co steel";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // total
                col = 5;
                sheet.Cells[row, col++] = "Total";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=sum(" + c + (row - 2).ToString() + ":" + c + (row - 1).ToString();
                }
                row++;
                // diff
                col = 5;
                sheet.Cells[row, col++] = "Diff (COP$)";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    if (Math.Abs(amount[i]) > 0.000001)
                    {
                        sheet.Cells[row, col++].Formula = "=" + c + (row - 1).ToString() + "-" + c + cpSumRow.ToString();
                    }
                    else
                    {
                        sheet.Cells[row, col++] = 0.0;
                    }
                }
                row++;
                // get export sales data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                row++;
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206015 and aj4ccyy=2014 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206015 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206015 and aj4ccyy=2014 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 5;
                sheet.Cells[row, col++] = "Sales Export";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // get colombia steels data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206016 and aj4ccyy=2014 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206016 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206016 and aj4ccyy=2014 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 5;
                sheet.Cells[row, col++] = "Sales export steel";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // total
                col = 5;
                sheet.Cells[row, col++] = "Total";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=sum(" + c + (row - 2).ToString() + ":" + c + (row - 1).ToString();
                }
                row++;
                // rate
                col = 5;
                sheet.Cells[row, col++] = "Rate:";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=" + c + (usdSumRow - 5).ToString() + "/" + c + (row - 1).ToString();
                }
                row++;
                #endregion

                #region last year
                // get colombia sales data from database
                row += 3;
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206010 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206010 and aj4ccyy=2012 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206010 and aj4ccyy=2013 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 4;
                sheet.Cells[row, col++] = "Sales rec to P&L";
                sheet.Cells[row, col++] = "Sales Colombia";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // get colombia steels data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206011 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206011 and aj4ccyy=2012 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206011 and aj4ccyy=2013 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 4;
                sheet.Cells[row, col++] = "Last Year";
                sheet.Cells[row, col++] = "Sales Co steel";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // total
                col = 5;
                sheet.Cells[row, col++] = "Total";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=sum(" + c + (row - 2).ToString() + ":" + c + (row - 1).ToString();
                }
                row++;
                // diff
                col = 5;
                sheet.Cells[row, col++] = "Diff (COP$)";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    if (Math.Abs(amount[i]) > 0.000001)
                    {
                        sheet.Cells[row, col++].Formula = "=" + c + (row - 1).ToString() + "-" + c + (cpSumRow + 2).ToString();
                    }
                    else
                    {
                        sheet.Cells[row, col++] = 0.0;
                    }
                }
                row++;
                // get export sales data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                row++;
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206015 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206015 and aj4ccyy=2012 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206015 and aj4ccyy=2013 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 5;
                sheet.Cells[row, col++] = "Sales Export";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // get colombia steels data from database
                for (int i = 0; i < 12; i++)
                {
                    amount[i] = 0.0;
                }
                // 04
                query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206016 and aj4ccyy=2013 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 3; i < 12; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i - 3]);
                    }
                }
                reader.Close();
                query = "select aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=441 and aj4gl#2=206016 and aj4ccyy=2012 and aj4comp=4";
                reader = solarsoft.RunQuery(query);
                while (reader.HasRows && reader.Read())
                {
                    for (int i = 0; i < 3; i++)
                    {
                        amount[i] -= Convert.ToDouble(reader[i]);
                    }
                }
                reader.Close();
                //// 41
                //query = "select aj4tt01, aj4tt02, aj4tt03, aj4tt04, aj4tt05, aj4tt06, aj4tt07, aj4tt08, aj4tt09, aj4tt10, aj4tt11, aj4tt12 from cmsdat.glmt where aj4gl#1=4141 and aj4gl#2=206016 and aj4ccyy=2013 and aj4comp=41";
                //reader = solarsoft.RunQuery(query);
                //while (reader.HasRows && reader.Read())
                //{
                //    for (int i = 0; i < 12; i++)
                //    {
                //        amount[i] -= Convert.ToDouble(reader[i]);
                //    }
                //}
                //reader.Close();
                col = 5;
                sheet.Cells[row, col++] = "Sales export steel";
                for (int i = 0; i < 12; i++)
                {
                    sheet.Cells[row, col++] = amount[i].ToString("C2");
                }
                row++;
                // total
                col = 5;
                sheet.Cells[row, col++] = "Total";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=sum(" + c + (row - 2).ToString() + ":" + c + (row - 1).ToString();
                }
                row++;
                // rate
                col = 5;
                sheet.Cells[row, col++] = "Rate:";
                for (int i = 0; i < 12; i++)
                {
                    char c = Convert.ToChar(Convert.ToInt32('A') + col - 1);
                    sheet.Cells[row, col++].Formula = "=" + c + (usdSumRow - 3).ToString() + "/" + c + (row - 1).ToString();
                }
                row += 3;
                #endregion
                */
            }
            // write surcharge percentage
            col = 5;
            title = "Surcharge (";
            switch (plant.currency)
            {
                case "CA":
                    title += "CAD";
                    break;
                case "US":
                    title += "USD";
                    break;
                case "CP":
                    title += "PESO";
                    break;
            }
            title += "): ";
            sheet.Cells[row, col++] = title;
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = plant.surchargeList[i].GetAmount(plant.currency).ToString("C0");
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
            row++;
            col = 5;
            sheet.Cells[row, col++] = "Percentage:";
            ExcoMoney saleTotal = new ExcoMoney();
            for (int i = 1; i <= 12; i++)
            {
                saleTotal += plant.saleList[i];
                if (plant.saleList[i].GetAmount(plant.currency) < 0.001)
                {
                    sheet.Cells[row, col++] = "0%";
                }
                else
                {
                    sheet.Cells[row, col++] = (plant.surchargeList[i].GetAmount(plant.currency) / plant.saleList[i].GetAmount(plant.currency)).ToString("P2");
                }
            }
            sheet.Cells[row, col].Formula = "=R" + (row - 1).ToString() + "/" + saleTotal.GetAmount(plant.currency);
            sheet.get_Range("R" + row.ToString()).NumberFormat = "0.00%";
            row += 3;
            // write parts count
            col = 5;
#endregion

            #region Robin's 2015/01/14 Edits DECADE DB RETRIEVE INSTEAD OF SOLARSOFT
            if (true) //Removes reader conflict from rest of this function
            {
                #region Tiger's Code
                /* retrieves from array preset under solarsoft instead of decade
            sheet.Cells[row, col++] = "Solid:";
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = plant.solidList[i].ToString();
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
            row++;
            col = 5;
            sheet.Cells[row, col++] = "Hollow:";
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = plant.hollowList[i].ToString();
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
            row++;
            col = 5;
            sheet.Cells[row, col++] = "OTHER:";
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = plant.ncrList[i].ToString();
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
            row++;
            */
                #endregion
                #region DATABASE SELECTION 
                ExcoODBC database = ExcoODBC.Instance;
                OdbcDataReader reader;
                if (plant.plantID == 1)
                {
                    database.Open(Database.DECADE_MARKHAM);
                }
                else if (plant.plantID == 3)
                {
                    database.Open(Database.DECADE_MICHIGAN);
                }
                else if (plant.plantID == 5)
                {
                    database.Open(Database.DECADE_TEXAS);
                }
                else if (plant.plantID == 4)
                {
                    database.Open(Database.DECADE_COLOMBIA);
                }
                Console.WriteLine("DB Selection DONE");
                #endregion
                #region SOLID
                sheet.Cells[row, col++] = "Solid:";
                for (int i = 10; i <= 21; i++)
                {
                    reader = database.RunQuery(PartsQuery(plant.plantID,i,fiscalYear,"solid"));
                    while (reader.Read())
                    {

                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                }
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;
                col = 5;
                Console.WriteLine("Solid Query done for plant: " + plant.plantID.ToString());
                #endregion
                #region HOLLOW
                sheet.Cells[row, col++] = "Hollow:";
                for (int i = 10; i <= 21; i++)
                {
                    reader = database.RunQuery(PartsQuery(plant.plantID, i, fiscalYear, "hollow"));
                    while (reader.Read())
                    {

                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                }
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;
                col = 5;
                Console.WriteLine("Hollow Query done for plant: " + plant.plantID.ToString());
                #endregion
                #region OTHER (MISC)
                sheet.Cells[row, col++] = "Other:";
                for (int i = 10; i <= 21; i++)
                {
                    reader = database.RunQuery(PartsQuery(plant.plantID, i, fiscalYear, "misc"));
                    while (reader.Read())
                    {

                        sheet.Cells[row, col++] = reader[0].ToString();
                    }

                    Excel.Range range2 = sheet.get_Range("E" + row.ToString(), "R" + row.ToString());
                    range2.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                }
                Console.WriteLine("Other Query done for plant: " + plant.plantID.ToString());
                #endregion
                #region Bottom row add
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;
                col = 5;
                sheet.Cells[row, col++] = "TOTAL:";
                sheet.Cells[row, col++].Formula = "=sum(F" + (row - 3).ToString() + ":F" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(G" + (row - 3).ToString() + ":G" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(H" + (row - 3).ToString() + ":H" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(I" + (row - 3).ToString() + ":I" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(J" + (row - 3).ToString() + ":J" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(K" + (row - 3).ToString() + ":K" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(L" + (row - 3).ToString() + ":L" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(M" + (row - 3).ToString() + ":M" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(N" + (row - 3).ToString() + ":N" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(O" + (row - 3).ToString() + ":O" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(P" + (row - 3).ToString() + ":P" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(Q" + (row - 3).ToString() + ":Q" + (row - 1).ToString();
                sheet.Cells[row, col++].Formula = "=sum(R" + (row - 3).ToString() + ":R" + (row - 1).ToString();
                Excel.Range range23 = sheet.get_Range("E" + row.ToString(), "R" + row.ToString());
                range23.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                row++;
                row++;
                col = 5;
                sheet.Cells[row, col++] = "Zero Dollar Inv.:";
                #endregion 
                #region ROBIN'S OLD COLOMBIA QUERY ONLY
                /*
            if (plant.plantID == 4) 
            {
                
                //PULL FROM decade database for colombia ONLY
                
                ExcoODBC database = ExcoODBC.Instance;
                string query = "";
                OdbcDataReader reader;
                database.Open(Database.DECADE_COLOMBIA);
                sheet.Cells[row, col++] = "Solid:";
                for (int i = 1; i <= 12; i++)
                {
                    if (i <= 3)
                    {
                        #region QUERY (OCT-DEC)
                        query = "select count(*) from d_order, d_orderitem where month(orderdate) = '" + (9 + i).ToString() + "' and year(orderdate) = '20" + (fiscalYear - 1).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber AND d_order.ncr <> 1 AND d_orderitem.line = 1 AND d_orderitem.dienumber is not NULL AND d_orderitem.prefix<>'BO' AND d_orderitem.prefix<>'HO' AND d_orderitem.prefix<>'PL'";
                        #endregion
                    }
                    else
                    {
                        #region QUERY (JAN-SEPT)
                        query = "select count(*) from d_order, d_orderitem where month(orderdate) = '" + (i - 3).ToString() + "' and year(orderdate) = '20" + (fiscalYear).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber AND d_order.ncr <> 1 AND d_orderitem.line = 1 AND d_orderitem.dienumber is not NULL AND d_orderitem.prefix<>'BO' AND d_orderitem.prefix<>'HO' AND d_orderitem.prefix<>'PL'";
                        #endregion
                    }
                    reader = database.RunQuery(query);
                    while (reader.Read())
                    {

                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                }
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;
                col = 5;
                sheet.Cells[row, col++] = "Hollow:";
                for (int i = 1; i <= 12; i++)
                {
                    if (i <= 3)
                    {
                        #region QUERY (OCT-DEC)
                        query = "select (select count(*) from d_order where month(orderdate) = '" + (9 + i).ToString() + "' and year(orderdate) = '20" + (fiscalYear - 1).ToString() + "' and ncr <> '1') - (select count(*) from d_order, d_orderitem where month(orderdate) = '" + (9 + i).ToString() + "' and year(orderdate) = '20" + (fiscalYear - 1).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber AND d_order.ncr <> 1 AND d_orderitem.line = 1 AND d_orderitem.dienumber is not NULL AND d_orderitem.prefix<>'BO' AND d_orderitem.prefix<>'HO' AND d_orderitem.prefix<>'PL')";
                        #endregion
                    }
                    else
                    {
                        #region QUERY (JAN-SEPT)
                        query = "select (select count(*) from d_order where month(orderdate) = '" + (i - 3).ToString() + "' and year(orderdate) = '20" + (fiscalYear).ToString() + "' and ncr <> '1') - (select count(*) from d_order, d_orderitem where month(orderdate) = '" + (i - 3).ToString() + "' and year(orderdate) = '20" + (fiscalYear).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber AND d_order.ncr <> 1 AND d_orderitem.line = 1 AND d_orderitem.dienumber is not NULL AND d_orderitem.prefix<>'BO' AND d_orderitem.prefix<>'HO' AND d_orderitem.prefix<>'PL')";
                        #endregion
                    }
                    reader = database.RunQuery(query);
                    while (reader.Read())
                    {
                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                }
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;
                col = 5;
                sheet.Cells[row, col++] = "NCR:";
                for (int i = 1; i <= 12; i++)
                {
                    if (i <= 3)
                    {
                        #region QUERY (OCT-DEC)
                        query = "select count(*) from d_order, d_orderitem where month(orderdate) = '" + (9 + i).ToString() + "' and year(orderdate) = '20" + (fiscalYear - 1).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber and ncr='1'";
                        #endregion
                    }
                    else
                    {
                        #region QUERY (JAN-SEPT)
                        query = "select count(*) from d_order, d_orderitem where month(orderdate) = '" + (i - 3).ToString() + "' and year(orderdate) = '20" + (fiscalYear).ToString() + "' and d_order.ordernumber = d_orderitem.ordernumber and ncr='1'";
                        #endregion
                    }
                    reader = database.RunQuery(query);
                    while (reader.Read())
                    {
                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                    
                }
                sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString();
                row++;

            }
            */
                #endregion
                #region NCR Totals
                for (int i = 10; i <= 21; i++)
                {
                    reader = database.RunQuery(PartsQuery(plant.plantID, i, fiscalYear, "ncr"));
                    while (reader.Read())
                    {
                        sheet.Cells[row, col++] = reader[0].ToString();
                    }
                }
                Console.WriteLine("NCR Query done for plant: " + plant.plantID.ToString());
                col = 5;
                row++;
                sheet.Cells[row, col++] = "(incl. in above)";
#endregion
            }
            #endregion
        }

        //public void SummarizeColumn(Excel.Worksheet sheet, int row, int startRow, int endRow, string title, List<int> listIndex)
        public void SummarizeColumn(Excel.Worksheet sheet, int row, string title, List<int> listIndex, int rowOffset = 0)
        {
            int col = 5;
            sheet.Cells[row, col++] = title;
            char colCode = 'F';


            listIndex.Distinct().OrderBy(x => x);

            for (int i = 0; i < 12; i++)
            {
                /*
                string formula = "=" + colCode + startRow.ToString();
                int tempRow = startRow + 3;
                while (tempRow <= endRow)
                {
                    formula += "+" + colCode + tempRow.ToString();
                    tempRow += 3;
                }
                sheet.Cells[row, col++].Formula = formula;
                colCode = Convert.ToChar(Convert.ToInt32(colCode) + 1);
                */
                List<int> temp = listIndex;

                if (listIndex.Count > 0)
                {
                    string formula = "=" + colCode + (listIndex[0] + rowOffset).ToString();


                    foreach (int index in listIndex.GetRange(1, listIndex.Count - 1))
                    {
                        formula += "+" + colCode + (index + rowOffset).ToString();
                    }

                    sheet.Cells[row, col++].Formula = formula;
                    colCode = Convert.ToChar(Convert.ToInt32(colCode) + 1);
                }
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString() + ")";
        }

        public int WriteCurrencySummary(Excel.Worksheet sheet, int startRow, ref int row, string currency, List<int> listIndex)
        {
            if (listIndex.Count > 0)
            {
                int summaryRow = 0;
                // actual
                int endRow = row - 3;
                row += 2;
                int col = 4;
                sheet.Cells[row, col++] = "TOTAL (" + currency + "):";
                //SummarizeColumn(sheet, row, startRow, endRow, "Actual:");
                SummarizeColumn(sheet, row, "Actual:", listIndex, 0);
                summaryRow = row;
                row++;
                // budget
                //SummarizeColumn(sheet, row, startRow + 1, endRow + 1, "Budget:");
                SummarizeColumn(sheet, row, "Budget:", listIndex, 1);
                Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                row++;
                // last year
                //SummarizeColumn(sheet, row, startRow + 2, endRow + 2, "Last Year:");
                SummarizeColumn(sheet, row, "Last Year:", listIndex, 2);
                range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                range = sheet.get_Range("E" + (row - 2).ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
            }
            return row;
        }


        public int WriteTerritorySummary(Excel.Worksheet sheet, int startRow, ref int row, string territory, List<int> listIndex)
        {
            if (listIndex.Count > 0)
            {
                int summaryRow = 0;
                // actual
                int endRow = row - 3;
                row += 2;
                int col = 4;
                sheet.Cells[row, col++] = "TERRITORY TOTAL (" + territory + "):";
                //SummarizeColumn(sheet, row, startRow, endRow, "Actual:");
                SummarizeColumn(sheet, row, "Actual:", listIndex, 0);
                summaryRow = row;
                row++;
                // budget
                //SummarizeColumn(sheet, row, startRow + 1, endRow + 1, "Budget:");
                SummarizeColumn(sheet, row, "Budget:", listIndex, 1);
                Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                row++;
                // last year
                //SummarizeColumn(sheet, row, startRow + 2, endRow + 2, "Last Year:");
                SummarizeColumn(sheet, row, "Last Year:", listIndex, 2);
                range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
                range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
                range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
                range = sheet.get_Range("E" + (row - 2).ToString());
                range.Font.Size = 9;
                range.Font.ColorIndex = 16;
            }
            return row;
        }

        /*
        public int WriteTerritorySummary(Excel.Worksheet sheet, int startRow, ref int row, string territory, List<int> listIndex)
        {
            int summaryRow = 0;
            // actual
            int endRow = row - 3;
            row += 1;
            int col = 4;
            sheet.Cells[row, col++] = "TOTAL (" + territory + "):";
            //SummarizeColumn(sheet, row, startRow, endRow, "Actual:");
            summaryRow = row;
            row++;
            // budget
            //SummarizeColumn(sheet, row, startRow + 1, endRow + 1, "Budget:");
            Excel.Range range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            row++;
            // last year
            //SummarizeColumn(sheet, row, startRow + 2, endRow + 2, "Last Year:");
            range = sheet.get_Range("A" + row.ToString(), "R" + row.ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            range = sheet.get_Range("D" + row.ToString(), "R" + row.ToString());
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            range = sheet.get_Range("E" + (row - 2).ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            return row;
        }

         * 
         */ 

        private void WriteCustomer(Excel.Worksheet sheet, Customer customer, int row, int col)
        {
            // temp budget line
            //sheet.Cells[row, col++] = "Budget 2017:";
            //for (int i = 1; i <= 12; i++)
            //{
            //    sheet.Cells[row, col++] = "";
            //}
            //row++;
            //col = 5;

            // actual line
            sheet.Cells[row, col++] = "Actual:";
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = customer.actualList[i].GetAmount(customer.excoCustomer.Currency).ToString("C0");
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString() + ")";
            // budget line
            row++;
            col = 5;
            sheet.Cells[row, col++] = "Budget:";
            for (int i = 1; i <= 12; i++)
            {
                sheet.Cells[row, col++] = customer.budgetList[i].GetAmount(customer.excoCustomer.Currency).ToString("C0");
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString() + ")";
            // last year line
            row++;
            col = 5;
            sheet.Cells[row, col++] = "Last Year:";
            for (int i = 1; i <= 12; i++)
            {
                double adjustment = 0;

                if (i == 2 && customer.excoCustomer.Name.Trim() == "Cuprum Mexico City" && fiscalYear == 18)
                    adjustment = 50488;  // see frank, correction for nov 30, 2016 entry from delivery revenue

                sheet.Cells[row, col++] = (customer.actualListLastYear[i].GetAmount(customer.excoCustomer.Currency) - adjustment).ToString("C0");
            }
            sheet.Cells[row, col++].Formula = "=sum(F" + row.ToString() + ":Q" + row.ToString() + ")";
            // adjust style
            Excel.Range range = sheet.get_Range("A" + (row - 1).ToString(), "R" + row.ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            range = sheet.get_Range("E" + (row - 2).ToString());
            range.Font.Size = 9;
            range.Font.ColorIndex = 16;
        }
    }
}
