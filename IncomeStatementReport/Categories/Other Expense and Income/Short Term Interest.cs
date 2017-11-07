using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Short_Term_Interest : Group
    {
        public Short_Term_Interest(int fiscalYear, int fiscalMonth)
        {
            name = "SHORT TERM INTEREST";
            // add accounts
            plant01.accountList.Add(new Account("100", "701000"));
            plant03.accountList.Add(new Account("300", "701000"));
            plant05.accountList.Add(new Account("500", "701000"));
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
