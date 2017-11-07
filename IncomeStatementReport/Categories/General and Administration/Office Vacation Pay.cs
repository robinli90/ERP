using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Vacation_Pay : Group
    {
        public Office_Vacation_Pay(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE VACATION PAY";
            // add accounts
            plant01.accountList.Add(new Account("100", "620000"));
            plant03.accountList.Add(new Account("300", "620000"));
            plant05.accountList.Add(new Account("500", "620000"));
            plant04.accountList.Add(new Account("451", "53901"));
            plant41.accountList.Add(new Account("4151", "53901"));
            plant48.accountList.Add(new Account("4851", "53901"));
            plant49.accountList.Add(new Account("4951", "53901"));
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
