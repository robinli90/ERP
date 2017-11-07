using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Pacific_Rim_Sales : Group
    {
        public Pacific_Rim_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "PACIFIC RIM SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "305500"));
            plant03.accountList.Add(new Account("300", "305500"));
            plant05.accountList.Add(new Account("500", "305500"));
            plant04.accountList.Add(new Account("441", "206025"));
            plant41.accountList.Add(new Account("4141", "206025"));
            plant48.accountList.Add(new Account("4841", "206025"));
            plant49.accountList.Add(new Account("4941", "206025"));
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
