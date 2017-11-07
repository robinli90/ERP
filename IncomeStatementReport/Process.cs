

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data.Odbc;
using ExcoUtility;
using IncomeStatementReport.Categories;
using Excel = Microsoft.Office.Interop.Excel;

namespace IncomeStatementReport
{
   public class Process
    {
        // cost of steels
        public Category cs;
        // delivery selling
        public Category ds;
        // factory overhead
        public Category fo;
        // general admin
        public Category ga;
        // other expense
        public Category oe;
        // sales
        public Category ss;
        // direct labour
        public Category dl;
        // non grouped
        public Category ng;
        // pt
        public Category pt;

        // fiscal periods
        public int fiscalYear = 0;
        public int fiscalMonth = 0;
            
        // diagnosis use
        public Dictionary<string, Account> plant01AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant03AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant05AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant04AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant41AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant48AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant49AccountMap = new Dictionary<string, Account>();


        // period
        public Process(int fiscalYear, int fiscalMonth, bool include_provisional=false)
        {
            ExcoExRate.GetExchangeRatesFromFile();

            this.fiscalMonth = fiscalMonth;
            this.fiscalYear = fiscalYear;
            cs = new Category("COST OF STEELS");
            ds = new Category("DELIVERY AND SELLING");
            fo = new Category("FACTORY OVERHEAD");
            ga = new Category("GENERAL AND ADMINISTRATION");
            oe = new Category("OTHER EXPENSE AND INCOME");
            ss = new Category("SALES");
            dl = new Category("DIRECT LABOUR");
            ng = new Category("NON GROUPED");
            pt = new Category("");
            // build category
            BuildCostOfSteels();
            BuildDeliverySelling();
            BuildDirectLabour();
            BuildFactoryOverhead();
            BuildGeneralAdmin();
            BuildOtherExpense(include_provisional);
            BuildSales();
            BuildNonGrouped();
            BuildProvisional();
            // diagnosis
            try
            {
                FindInvalidAccount();
                FindDuplicateAccount();
                FindUnprocessedAccount();
            }
            catch (Exception e)
            {
                string msg = e.Message;
            }
        }

        private void FindUnprocessedAccount()
        {
            // markham
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=1 and azgl#1=100 and azatyp>=4";
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant01AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account markham " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // michigan
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=3 and azgl#1=300 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant03AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account michigan " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // texas
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=5 and azgl#1=500 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant05AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account markham " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // colombia
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=4 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant04AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 04 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=41 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant41AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 41 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close(); 
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=48 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant48AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 48 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close(); 
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=49 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant49AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 49 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
        }

        private void TestAccountValidity(Account account, int plantID)
        {
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select * from cmsdat.mast where azcomp=" + plantID + " and azgl#1=" + account.glNo1 + " and azgl#2=" + account.glNo2 + " and azatyp>=4";
            OdbcDataReader reader = database.RunQuery(query);
            if (!reader.Read() || !reader.HasRows)
            {
                throw new Exception("invalid account " + plantID + " " + account.glNo1 + "-" + account.glNo2);
            }
            reader.Close();
        }

        private void FindInvalidAccountInGroup(Category category)
        {
            foreach (Group group in category.groupList)
            {
                // markham
                foreach (Account account in group.plant01.accountList)
                {
                    TestAccountValidity(account, group.plant01.plantID);
                }
                // michigan
                foreach (Account account in group.plant03.accountList)
                {
                    TestAccountValidity(account, group.plant03.plantID);
                }
                // texas
                foreach (Account account in group.plant05.accountList)
                {
                    TestAccountValidity(account, group.plant05.plantID);
                }
                // colombia
                foreach (Account account in group.plant04.accountList)
                {
                    TestAccountValidity(account, group.plant04.plantID);
                }
                foreach (Account account in group.plant41.accountList)
                {
                    TestAccountValidity(account, group.plant41.plantID);
                }
                foreach (Account account in group.plant48.accountList)
                {
                    TestAccountValidity(account, group.plant48.plantID);
                }
                foreach (Account account in group.plant49.accountList)
                {
                    TestAccountValidity(account, group.plant49.plantID);
                }
            }
        }

        private void FindInvalidAccount()
        {
            FindInvalidAccountInGroup(cs);
            FindInvalidAccountInGroup(ds);
            FindInvalidAccountInGroup(fo);
            FindInvalidAccountInGroup(ga);
            FindInvalidAccountInGroup(oe);
            FindInvalidAccountInGroup(ss);
            FindInvalidAccountInGroup(dl);
            FindInvalidAccountInGroup(ng);
        }

        private void FindDuplicateAccountInGroup(Category category)
        {
            foreach (Group group in category.groupList)
            {
                    // markham
                    foreach (Account account in group.plant01.accountList)
                    {
                        string key = account.glNo1 + "-" + account.glNo2;
                    if (plant01AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account markham " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant01AccountMap.Add(key, account);
                    }
                }
                // michigan
                foreach (Account account in group.plant03.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant03AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account michigan " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant03AccountMap.Add(key, account);
                    }
                }
                // texas
                foreach (Account account in group.plant05.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant05AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account texas " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant05AccountMap.Add(key, account);
                    }
                }
                // colombia
                foreach (Account account in group.plant04.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant04AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 04 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant04AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant41.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant41AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 41 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant41AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant48.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant48AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 48 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant48AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant49.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant49AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 49 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant49AccountMap.Add(key, account);
                    }
                }
            }
        }

        private void FindDuplicateAccount()
        {
            FindDuplicateAccountInGroup(cs);
            FindDuplicateAccountInGroup(ds);
            FindDuplicateAccountInGroup(fo);
            FindDuplicateAccountInGroup(ga);
            FindDuplicateAccountInGroup(oe);
            FindDuplicateAccountInGroup(ss);
            FindDuplicateAccountInGroup(dl);
            FindDuplicateAccountInGroup(ng);
        }

        private void BuildSales()
        {
            ss.groupList.Add(new Categories.Sales.Canada_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.USA_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Colombia_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Europe_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Pacific_Rim_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Mexico_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.South_America_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.InterDivision_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Canada_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.USA_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Colombia_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Europe_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Pacific_Rim_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Mexico_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.South_America_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.InterDivision_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Cash_and__Volume_Discount(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Financial_Income(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Delivery_Revenue(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Scrap_Sales(fiscalYear, fiscalMonth));
        }

        private void BuildCostOfSteels()
        {
            //cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Goods_Burden(fiscalYear, fiscalMonth));
            //cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Goods_Material(fiscalYear, fiscalMonth));
            //cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Steels_Reclass(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Freight_and_Duty_in(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Increase_or_Decrease_WIP(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.InterCompany_Purchases(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Material_Parts_Non_Inventory(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Raw_Material_Steel_Usage(fiscalYear, fiscalMonth));
            //cs.groupList.Add(new Categories.Cost_of_Steels.SubContract_Work(fiscalYear, fiscalMonth));
            //cs.groupList.Add(new Categories.Cost_of_Steels.WIP_Obsolescence(fiscalYear, fiscalMonth));
        }

        private void BuildDeliverySelling()
        {
            ds.groupList.Add(new Categories.Delivery_and_Selling.Advertising_Expense(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Air_Fare(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Auto_Operation_Expense(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Depreciation_Automobile(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Employee_Benefits_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Group_Insurance_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Non_Deductible_Expense_Golf(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Sales_Commissions(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Sales_Salaries(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Selling_and_Travel_Expenses(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Selling_and_Travel_Meals_and_Entertainment(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Statutory_Holiday_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Vacation_Pay_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Workers_Compensation_Sales(fiscalYear, fiscalMonth));
        }

        private void BuildFactoryOverhead()
        {
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_and_CAM_Supplies(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_and_CAM_System_Maintenance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_Salaries(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Consulting_Fees(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Building(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Building_Improvement(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Furniture_and_Fixture(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Machine_and_Equipment(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Software(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Vehicles(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Equipment_Rentals(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Business_Insurance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Business_Tax(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Cleaning_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Employee_Benefits(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Group_Insurance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Rent(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Unclassified_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Freight_and_Duty_out(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Indirect_Labour_ISO_IT_Purchaser(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Maintenance_and_Repair_Building(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Maintenance_and_Repair_Equipment(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Realty_Tax(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Research_and_Development(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shipping_Supplies(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Shop_Air_Fare(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Shop_Meals_and_Entertainment(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Supplies_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Supplies_Heat_Treat(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Shop_Travel(fiscalYear, fiscalMonth));
            //fo.groupList.Add(new Categories.Factory_Overhead.Factory_South_America_Travel(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Statutory_Holiday(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.SubContract(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Supervisory_Salaries(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Tool_Amortization(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Tools_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Training_and_Development(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Utilities_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Vacation_Pay_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.WIP_Adjustment_Overhead(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Workers_Compensation(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Goodwill_Amortization(fiscalYear, fiscalMonth));
        }

        private void BuildGeneralAdmin()
        {
            //ga.groupList.Add(new Categories.General_and_Administration.Office_Air_Fare(fiscalYear, fiscalMonth));
            //ga.groupList.Add(new Categories.General_and_Administration.Business_Tax(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Cell_Phone_Expense(fiscalYear, fiscalMonth));
            //ga.groupList.Add(new Categories.General_and_Administration.Commercial_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Depreciation_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Donations(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.EDC_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Legal_and_Audit(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Salaries(fiscalYear, fiscalMonth));
            //ga.groupList.Add(new Categories.General_and_Administration.Meal_and_Entertainment(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Memberships_and_Subscriptions(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Cleaning(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Employee_Benefits(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Group_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Rent(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Supplies(fiscalYear, fiscalMonth));
            //ga.groupList.Add(new Categories.General_and_Administration.Payroll_Taxes(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Postage(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Recruitment_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Software_Amortization(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_South_America_Travel(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Statutory_Holiday(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Telephone_Expense(fiscalYear, fiscalMonth));
            //ga.groupList.Add(new Categories.General_and_Administration.Travel_Expenses(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Vacation_Pay(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Workers_Compensation(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Other_Expenses(fiscalYear, fiscalMonth));
        }

        private void BuildOtherExpense(bool include_provisional = false)
        {
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Bad_Debt_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Bank_Charges(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Captial_Tax_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Cash_Discounts_Earned(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.DPSP_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Exchange_Gain_or_Loss(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Gain_or_Loss_on_Asset_Disposal(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Incentive_Bonus_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Long_Term_Interest(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Miscellaneous_Income_or_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Non_Recurring_Expenses(fiscalYear, fiscalMonth));
            if (include_provisional)
                oe.groupList.Add(new Categories.Other_Expense_and_Income.Provision_for_Income_Tax(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Reorganization_Costs(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Severance(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Short_Term_Interest(fiscalYear, fiscalMonth));
            //oe.groupList.Add(new Categories.Other_Expense_and_Income.Impuesto_a_La_Riqueza(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Dividend_Interest(fiscalYear, fiscalMonth));
        }

        private void BuildDirectLabour()
        {
            dl.groupList.Add(new Categories.Direct_Labour.CAM_Salaries(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.Direct_Labour_Heat_Treat(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.Direct_Labour_Shop(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.WIP_Adjustment_Labour(fiscalYear, fiscalMonth));
        }

        private void BuildProvisional()
        {
            pt.groupList.Add(new Categories.Other_Expense_and_Income.Provision_for_Income_Tax(fiscalYear, fiscalMonth));
        }

        private void BuildNonGrouped()
        {
            Group group = new Group();
            group.plant01.accountList.Add(new Account("100", "402500"));
            group.plant01.accountList.Add(new Account("100", "508000"));
            group.plant01.accountList.Add(new Account("100", "609100"));
            group.plant03.accountList.Add(new Account("300", "402500"));
            group.plant03.accountList.Add(new Account("300", "508000"));
            group.plant03.accountList.Add(new Account("300", "609100"));
            ng.groupList.Add(group);
        }
    }
}
/*


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data.Odbc;
using ExcoUtility;
using IncomeStatementReport.Categories;
using Excel = Microsoft.Office.Interop.Excel;

namespace IncomeStatementReport
{
   public class Process
    {
        // cost of steels
        public Category cs;
        // delivery selling
        public Category ds;
        // factory overhead
        public Category fo;
        // general admin
        public Category ga;
        // other expense
        public Category oe;
        // sales
        public Category ss;
        // direct labour
        public Category dl;
        // non grouped
        public Category ng;

        // fiscal periods
        public int fiscalYear = 0;
        public int fiscalMonth = 0;

        // diagnosis use
        public Dictionary<string, Account> plant01AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant03AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant05AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant04AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant41AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant48AccountMap = new Dictionary<string, Account>();
        public Dictionary<string, Account> plant49AccountMap = new Dictionary<string, Account>();


        // period
        public Process(int fiscalYear, int fiscalMonth)
        {
            this.fiscalMonth = fiscalMonth;
            this.fiscalYear = fiscalYear;
            cs = new Category("COST OF STEELS");
            ds = new Category("DELIVERY AND SELLING");
            fo = new Category("FACTORY OVERHEAD");
            ga = new Category("GENERAL AND ADMINISTRATION");
            oe = new Category("OTHER EXPENSE AND INCOME");
            ss = new Category("SALES");
            dl = new Category("DIRECT LABOUR");
            ng = new Category("NON GROUPED");
            // build category
            BuildCostOfSteels();
            BuildDeliverySelling();
            BuildDirectLabour();
            BuildFactoryOverhead();
            BuildGeneralAdmin();
            BuildOtherExpense();
            BuildSales();
            BuildNonGrouped();
            // diagnosis
            try
            {
                FindInvalidAccount();
                FindDuplicateAccount();
                FindUnprocessedAccount();
            }
            catch (Exception e)
            {
                string msg = e.Message;
            }
        }

        private void FindUnprocessedAccount()
        {
            // markham
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=1 and azgl#1=100 and azatyp>=4";
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant01AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account markham " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // michigan
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=3 and azgl#1=300 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant03AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account michigan " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // texas
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=5 and azgl#1=500 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant05AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account markham " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            // colombia
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=4 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant04AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 04 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=41 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant41AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 41 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close(); 
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=48 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant48AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 48 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close(); 
            query = "select distinct azgl#1, azgl#2 from cmsdat.mast where azcomp=49 and azatyp>=4";
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string glNo1 = reader["azgl#1"].ToString().Trim();
                string glNo2 = reader["azgl#2"].ToString().Trim();
                string key = glNo1 + "-" + glNo2;
                if (!plant49AccountMap.ContainsKey(key))
                {
                    throw new Exception("unprocessed account colombia 49 " + glNo1 + "-" + glNo2);
                }
            }
            reader.Close();
        }

        private void TestAccountValidity(Account account, int plantID)
        {
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            string query = "select * from cmsdat.mast where azcomp=" + plantID + " and azgl#1=" + account.glNo1 + " and azgl#2=" + account.glNo2 + " and azatyp>=4";
            OdbcDataReader reader = database.RunQuery(query);
            if (!reader.Read() || !reader.HasRows)
            {
                throw new Exception("invalid account " + plantID + " " + account.glNo1 + "-" + account.glNo2);
            }
            reader.Close();
        }

        private void FindInvalidAccountInGroup(Category category)
        {
            foreach (Group group in category.groupList)
            {
                // markham
                foreach (Account account in group.plant01.accountList)
                {
                    TestAccountValidity(account, group.plant01.plantID);
                }
                // michigan
                foreach (Account account in group.plant03.accountList)
                {
                    TestAccountValidity(account, group.plant03.plantID);
                }
                // texas
                foreach (Account account in group.plant05.accountList)
                {
                    TestAccountValidity(account, group.plant05.plantID);
                }
                // colombia
                foreach (Account account in group.plant04.accountList)
                {
                    TestAccountValidity(account, group.plant04.plantID);
                }
                foreach (Account account in group.plant41.accountList)
                {
                    TestAccountValidity(account, group.plant41.plantID);
                }
                foreach (Account account in group.plant48.accountList)
                {
                    TestAccountValidity(account, group.plant48.plantID);
                }
                foreach (Account account in group.plant49.accountList)
                {
                    TestAccountValidity(account, group.plant49.plantID);
                }
            }
        }

        private void FindInvalidAccount()
        {
            FindInvalidAccountInGroup(cs);
            FindInvalidAccountInGroup(ds);
            FindInvalidAccountInGroup(fo);
            FindInvalidAccountInGroup(ga);
            FindInvalidAccountInGroup(oe);
            FindInvalidAccountInGroup(ss);
            FindInvalidAccountInGroup(dl);
            FindInvalidAccountInGroup(ng);
        }

        private void FindDuplicateAccountInGroup(Category category)
        {
            foreach (Group group in category.groupList)
            {
                // markham
                foreach (Account account in group.plant01.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant01AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account markham " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant01AccountMap.Add(key, account);
                    }
                }
                // michigan
                foreach (Account account in group.plant03.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant03AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account michigan " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant03AccountMap.Add(key, account);
                    }
                }
                // texas
                foreach (Account account in group.plant05.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant05AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account texas " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant05AccountMap.Add(key, account);
                    }
                }
                // colombia
                foreach (Account account in group.plant04.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant04AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 04 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant04AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant41.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant41AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 41 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant41AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant48.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant48AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 48 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant48AccountMap.Add(key, account);
                    }
                }
                foreach (Account account in group.plant49.accountList)
                {
                    string key = account.glNo1 + "-" + account.glNo2;
                    if (plant49AccountMap.ContainsKey(key))
                    {
                        throw new Exception("duplicate account colombia 49 " + account.glNo1 + "-" + account.glNo2);
                    }
                    else
                    {
                        plant49AccountMap.Add(key, account);
                    }
                }
            }
        }

        private void FindDuplicateAccount()
        {
            FindDuplicateAccountInGroup(cs);
            FindDuplicateAccountInGroup(ds);
            FindDuplicateAccountInGroup(fo);
            FindDuplicateAccountInGroup(ga);
            FindDuplicateAccountInGroup(oe);
            FindDuplicateAccountInGroup(ss);
            FindDuplicateAccountInGroup(dl);
            FindDuplicateAccountInGroup(ng);
        }

        private void BuildSales()
        {
            ss.groupList.Add(new Categories.Sales.Canada_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Canada_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Cash_and__Volume_Discount(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Colombia_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Colombia_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Delivery_Revenue(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Europe_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Europe_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.InterDivision_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.InterDivision_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Mexico_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Mexico_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Pacific_Rim_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Pacific_Rim_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.Scrap_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.South_America_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.South_America_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.USA_Sales(fiscalYear, fiscalMonth));
            ss.groupList.Add(new Categories.Sales.USA_Sales_Steel_Surcharge(fiscalYear, fiscalMonth));
        }

        private void BuildCostOfSteels()
        {
            cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Goods_Burden(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Goods_Material(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Cost_of_Steels_Reclass(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Freight_and_Duty_in(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Increase_or_Decrease_WIP(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.InterCompany_Purchases(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Material_Parts_Non_Inventory(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.Raw_Material_Steel_Usage(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.SubContract_Work(fiscalYear, fiscalMonth));
            cs.groupList.Add(new Categories.Cost_of_Steels.WIP_Obsolescence(fiscalYear, fiscalMonth));
        }

        private void BuildDeliverySelling()
        {
            ds.groupList.Add(new Categories.Delivery_and_Selling.Advertising_Expense(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Air_Fare(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Auto_Operation_Expense(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Depreciation_Automobile(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Employee_Benefits_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Group_Insurance_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Non_Deductible_Expense_Golf(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Sales_Commissions(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Sales_Salaries(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Selling_and_Travel_Expenses(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Selling_and_Travel_Meals_and_Entertainment(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Statutory_Holiday_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Vacation_Pay_Sales(fiscalYear, fiscalMonth));
            ds.groupList.Add(new Categories.Delivery_and_Selling.Workers_Compensation_Sales(fiscalYear, fiscalMonth));
        }

        private void BuildFactoryOverhead()
        {
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_and_CAM_Supplies(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_and_CAM_System_Maintenance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.CAD_Salaries(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Consulting_Fees(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Building(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Building_Improvement(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Furniture_and_Fixture(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Machine_and_Equipment(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Software(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Depreciation_Vehicles(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Equipment_Rentals(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Business_Insurance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Business_Tax(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Cleaning_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Employee_Benefits(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Group_Insurance(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Rent(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_Unclassified_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Freight_and_Duty_out(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Indirect_Labour_ISO_IT_Purchaser(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Maintenance_and_Repair_Building(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Maintenance_and_Repair_Equipment(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Realty_Tax(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Research_and_Development(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shipping_Supplies(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Air_Fare(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Meals_and_Entertainment(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Supplies_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Supplies_Heat_Treat(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Shop_Travel(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Factory_South_America_Travel(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Statutory_Holiday(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.SubContract(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Supervisory_Salaries(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Tool_Amortization(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Tools_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Training_and_Development(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Utilities_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Vacation_Pay_Expense(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.WIP_Adjustment_Overhead(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Workers_Compensation(fiscalYear, fiscalMonth));
            fo.groupList.Add(new Categories.Factory_Overhead.Goodwill_Amortization(fiscalYear, fiscalMonth));
        }

        private void BuildGeneralAdmin()
        {
            ga.groupList.Add(new Categories.General_and_Administration.Office_Air_Fare(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Business_Tax(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Cell_Phone_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Commercial_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Depreciation_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Donations(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.EDC_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Legal_and_Audit(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Salaries(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Meal_and_Entertainment(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Memberships_and_Subscriptions(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Cleaning(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Employee_Benefits(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Group_Insurance(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Rent(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Supplies(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Payroll_Taxes(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Postage(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Recruitment_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Software_Amortization(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_South_America_Travel(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Statutory_Holiday(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Telephone_Expense(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Travel_Expenses(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Vacation_Pay(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Office_Workers_Compensation(fiscalYear, fiscalMonth));
            ga.groupList.Add(new Categories.General_and_Administration.Other_Expenses(fiscalYear, fiscalMonth));
        }

        private void BuildOtherExpense()
        {
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Bad_Debt_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Bank_Charges(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Captial_Tax_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Cash_Discounts_Earned(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.DPSP_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Exchange_Gain_or_Loss(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Gain_or_Loss_on_Asset_Disposal(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Incentive_Bonus_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Long_Term_Interest(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Miscellaneous_Income_or_Expense(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Non_Recurring_Expenses(fiscalYear, fiscalMonth));
            //oe.groupList.Add(new Categories.Other_Expense_and_Income.Provision_for_Income_Tax(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Reorganization_Costs(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Severance(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Short_Term_Interest(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Impuesto_a_La_Riqueza(fiscalYear, fiscalMonth));
            oe.groupList.Add(new Categories.Other_Expense_and_Income.Dividend_Interest(fiscalYear, fiscalMonth));
        }

        private void BuildDirectLabour()
        {
            dl.groupList.Add(new Categories.Direct_Labour.CAM_Salaries(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.Direct_Labour_Heat_Treat(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.Direct_Labour_Shop(fiscalYear, fiscalMonth));
            dl.groupList.Add(new Categories.Direct_Labour.WIP_Adjustment_Labour(fiscalYear, fiscalMonth));
        }

        private void BuildNonGrouped()
        {
            Group group = new Group();
            group.plant01.accountList.Add(new Account("100", "402500"));
            group.plant01.accountList.Add(new Account("100", "508000"));
            group.plant01.accountList.Add(new Account("100", "609100"));
            group.plant03.accountList.Add(new Account("300", "402500"));
            group.plant03.accountList.Add(new Account("300", "508000"));
            group.plant03.accountList.Add(new Account("300", "609100"));
            ng.groupList.Add(group);
        }
    }
}
*/