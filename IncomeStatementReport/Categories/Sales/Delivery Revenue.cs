using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Delivery_Revenue : Group
    {
        public Delivery_Revenue(int fiscalYear, int fiscalMonth)
        {
            name = "DELIVERY REVENUE";
            // add accounts
            plant01.accountList.Add(new Account("100", "309000"));
            plant03.accountList.Add(new Account("300", "309000"));
            plant05.accountList.Add(new Account("500", "309000"));
            plant04.accountList.Add(new Account("441", "459501"));
            plant04.accountList.Add(new Account("442", "351001"));
            plant41.accountList.Add(new Account("4141", "459501"));
            plant48.accountList.Add(new Account("4841", "459501"));
            plant49.accountList.Add(new Account("4941", "459501"));
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
