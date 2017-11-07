using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Commercial_Insurance : Group
    {
        public Commercial_Insurance(int fiscalYear, int fiscalMonth)
        {
            name = "COMMERCIAL INSURANCE";
            // add accounts
            plant04.accountList.Add(new Account("451", "309501"));
            plant41.accountList.Add(new Account("4151", "309501"));
            plant48.accountList.Add(new Account("4851", "309501"));
            plant49.accountList.Add(new Account("4951", "309501"));
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
