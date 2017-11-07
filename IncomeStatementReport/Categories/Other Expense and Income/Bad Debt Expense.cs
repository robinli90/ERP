using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Bad_Debt_Expense : Group
    {
        public Bad_Debt_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "BAD DEBT EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "704500"));
            plant03.accountList.Add(new Account("300", "704500"));
            plant05.accountList.Add(new Account("500", "704500"));
            plant04.accountList.Add(new Account("451", "991001"));
            plant41.accountList.Add(new Account("4151", "991001"));
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
