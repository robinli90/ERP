using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Cash_Discounts_Earned : Group
    {
        public Cash_Discounts_Earned(int fiscalYear, int fiscalMonth)
        {
            name = "CASH DISCOUNTS EARNED";
            // add accounts
            plant01.accountList.Add(new Account("100", "709000"));
            plant03.accountList.Add(new Account("300", "709000"));
            plant05.accountList.Add(new Account("500", "709000"));
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
