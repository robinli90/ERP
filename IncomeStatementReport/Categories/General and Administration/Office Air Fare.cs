using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Air_Fare : Group
    {
        public Office_Air_Fare(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE AIR FARE";
            // add accounts
            plant03.accountList.Add(new Account("300", "625000"));
            plant05.accountList.Add(new Account("500", "625000"));
            plant04.accountList.Add(new Account("451", "551501"));
            plant04.accountList.Add(new Account("451", "551502"));
            plant41.accountList.Add(new Account("4151", "551501"));
            plant48.accountList.Add(new Account("4851", "551501"));
            plant49.accountList.Add(new Account("4951", "551501"));
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
