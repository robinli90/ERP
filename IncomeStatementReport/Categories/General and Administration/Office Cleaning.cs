using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Cleaning : Group
    {
        public Office_Cleaning(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE CLEANING";
            // add accounts
            plant01.accountList.Add(new Account("100", "608000"));
            plant03.accountList.Add(new Account("300", "608000"));
            plant05.accountList.Add(new Account("500", "608000"));
            plant04.accountList.Add(new Account("451", "350501"));
            plant41.accountList.Add(new Account("4151", "350501"));
            plant48.accountList.Add(new Account("4851", "350501"));
            plant49.accountList.Add(new Account("4951", "350501"));
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
