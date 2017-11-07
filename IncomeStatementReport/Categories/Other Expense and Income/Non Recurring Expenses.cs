using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Non_Recurring_Expenses : Group
    {
        public Non_Recurring_Expenses(int fiscalYear, int fiscalMonth)
        {
            name = "NON RECURRING EXPENSES";
            // add accounts
            plant01.accountList.Add(new Account("100", "706000"));
            plant03.accountList.Add(new Account("300", "706000"));
            plant05.accountList.Add(new Account("500", "706000"));
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
