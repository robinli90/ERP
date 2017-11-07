using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Non_Deductible_Expense_Golf : Group
    {
        public Non_Deductible_Expense_Golf(int fiscalYear, int fiscalMonth)
        {
            name = "NON DEDUCTIBLE EXPENSE GOLF";
            // add accounts
            plant01.accountList.Add(new Account("100", "505800"));
            plant03.accountList.Add(new Account("300", "505800"));
            plant05.accountList.Add(new Account("500", "505800"));
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
