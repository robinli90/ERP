using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Severance : Group
    {
        public Severance(int fiscalYear, int fiscalMonth)
        {
            name = "SEVERANCE";
            // add accounts
            plant01.accountList.Add(new Account("100", "707100"));
            plant03.accountList.Add(new Account("300", "707100"));
            plant05.accountList.Add(new Account("500", "707100"));
            plant04.accountList.Add(new Account("453", "957501"));
            plant41.accountList.Add(new Account("4153", "957501"));
            plant48.accountList.Add(new Account("4853", "957501"));
            plant49.accountList.Add(new Account("4953", "957501"));
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
