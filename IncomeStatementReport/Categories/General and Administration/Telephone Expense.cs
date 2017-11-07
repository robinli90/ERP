using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Telephone_Expense : Group
    {
        public Telephone_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "TELEPHONE EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "615000"));
            plant03.accountList.Add(new Account("300", "615000"));
            plant05.accountList.Add(new Account("500", "615000"));
            plant04.accountList.Add(new Account("451", "353501"));
            plant04.accountList.Add(new Account("451", "353503"));
            plant04.accountList.Add(new Account("451", "353509"));
            plant41.accountList.Add(new Account("4151", "353501"));
            plant41.accountList.Add(new Account("4151", "353503"));
            plant41.accountList.Add(new Account("4151", "353509"));
            plant48.accountList.Add(new Account("4851", "353501"));
            plant48.accountList.Add(new Account("4851", "353503"));
            plant48.accountList.Add(new Account("4851", "353509"));
            plant49.accountList.Add(new Account("4951", "353501"));
            plant49.accountList.Add(new Account("4951", "353503"));
            plant49.accountList.Add(new Account("4951", "353509"));
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
