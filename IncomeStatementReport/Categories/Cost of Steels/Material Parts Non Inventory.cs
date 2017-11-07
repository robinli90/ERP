using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Material_Parts_Non_Inventory : Group
    {
        public Material_Parts_Non_Inventory(int fiscalYear, int fiscalMonth)
        {
            name = "MATERIAL PARTS NON INVENTORY";
            // add accounts
            plant01.accountList.Add(new Account("100", "310000"));
            plant01.accountList.Add(new Account("100", "310001"));
            plant03.accountList.Add(new Account("300", "310000"));
            plant03.accountList.Add(new Account("300", "310001"));
            plant05.accountList.Add(new Account("500", "310000"));
            plant05.accountList.Add(new Account("500", "310001"));
            plant04.accountList.Add(new Account("471", "30101"));
            plant41.accountList.Add(new Account("4171", "30101"));
            plant48.accountList.Add(new Account("4871", "30101"));
            plant49.accountList.Add(new Account("4971", "30101"));
            // process accounts
            plant01.GetAccountsData(fiscalYear, fiscalMonth);
            plant03.GetAccountsData(fiscalYear, fiscalMonth);
            plant05.GetAccountsData(fiscalYear, fiscalMonth);
            plant04.GetAccountsData(fiscalYear, fiscalMonth);
            plant41.GetAccountsData(fiscalYear, fiscalMonth);
            plant48.GetAccountsData(fiscalYear, fiscalMonth);
            plant49.GetAccountsData(fiscalYear, fiscalMonth);
        }

    }
}
