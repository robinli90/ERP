using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Cell_Phone_Expense : Group
    {
        public Cell_Phone_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "CELL PHONE EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "615100"));
            plant03.accountList.Add(new Account("300", "615100"));
            plant05.accountList.Add(new Account("500", "615100"));
            plant04.accountList.Add(new Account("451", "353502"));
            plant41.accountList.Add(new Account("4151", "353502"));
            plant48.accountList.Add(new Account("4851", "353502"));
            plant49.accountList.Add(new Account("4951", "353502"));
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
