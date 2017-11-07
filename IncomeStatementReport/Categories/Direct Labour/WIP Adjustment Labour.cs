using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Direct_Labour
{
    public class WIP_Adjustment_Labour : Group
    {
        public WIP_Adjustment_Labour(int fiscalYear, int fiscalMonth)
        {
            name = "WIP ADJUSTMENT LABOUR";
            // add accounts
            plant01.accountList.Add(new Account("100", "353300"));
            plant03.accountList.Add(new Account("300", "353300"));
            plant05.accountList.Add(new Account("500", "353300"));
            plant04.accountList.Add(new Account("472", "12001"));
            plant41.accountList.Add(new Account("4172", "12001"));
            plant48.accountList.Add(new Account("4872", "12001"));
            plant49.accountList.Add(new Account("4972", "12001"));
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
