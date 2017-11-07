using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Miscellaneous_Income_or_Expense : Group
    {
        public Miscellaneous_Income_or_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "MISCELLANEOUS INCOME OR EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "707000"));
            plant03.accountList.Add(new Account("300", "707000"));
            plant05.accountList.Add(new Account("500", "707000"));
            plant04.accountList.Add(new Account("453", "59501"));
            plant04.accountList.Add(new Account("453", "151501"));
            plant04.accountList.Add(new Account("453", "152001"));
            plant41.accountList.Add(new Account("4153", "59501"));
            plant41.accountList.Add(new Account("4153", "151501"));
            plant41.accountList.Add(new Account("4153", "152001"));
            plant48.accountList.Add(new Account("4853", "59501"));
            plant48.accountList.Add(new Account("4853", "152001"));
            plant49.accountList.Add(new Account("4953", "59501"));
            plant49.accountList.Add(new Account("4953", "152001"));
            plant04.accountList.Add(new Account("4451", "959502"));
            plant41.accountList.Add(new Account("4151", "959502"));
            plant48.accountList.Add(new Account("4851", "959502"));
            plant49.accountList.Add(new Account("4951", "959502"));
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
