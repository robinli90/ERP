using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Dividend_Interest : Group
    {
        public Dividend_Interest(int fiscalYear, int fiscalMonth)
        {
            name = "DIVIDEND INTEREST";
            // add accounts
            plant03.accountList.Add(new Account("300", "701501"));
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
