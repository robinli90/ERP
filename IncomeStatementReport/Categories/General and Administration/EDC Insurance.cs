using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class EDC_Insurance : Group
    {
        public EDC_Insurance(int fiscalYear, int fiscalMonth)
        {
            name = "EDC INSURANCE";
            // add accounts
            plant01.accountList.Add(new Account("100", "612500"));
            plant03.accountList.Add(new Account("300", "612500"));
            plant05.accountList.Add(new Account("500", "612500"));
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
