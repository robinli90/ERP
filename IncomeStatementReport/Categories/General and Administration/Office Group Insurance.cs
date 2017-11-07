using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Group_Insurance : Group
    {
        public Office_Group_Insurance(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE GROUP INSURANCE";
            // add accounts
            plant01.accountList.Add(new Account("100", "604000"));
            plant03.accountList.Add(new Account("300", "604000"));
            plant05.accountList.Add(new Account("500", "604000"));
            plant04.accountList.Add(new Account("451", "52401"));
            plant41.accountList.Add(new Account("4151", "52401"));
            plant48.accountList.Add(new Account("4851", "52401"));
            plant49.accountList.Add(new Account("4951", "52401"));
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
