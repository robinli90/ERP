using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Business_Tax : Group
    {
        public Business_Tax(int fiscalYear, int fiscalMonth)
        {
            name = "BUSINESS TAX";
            // add accounts
            plant04.accountList.Add(new Account("451", "150501"));
            plant04.accountList.Add(new Account("451", "959501"));
            plant04.accountList.Add(new Account("452", "959501"));
            plant41.accountList.Add(new Account("4151", "150501"));
            plant41.accountList.Add(new Account("4151", "959501"));
            plant41.accountList.Add(new Account("4152", "959501"));
            plant48.accountList.Add(new Account("4851", "150501"));
            plant49.accountList.Add(new Account("4951", "150501"));
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
