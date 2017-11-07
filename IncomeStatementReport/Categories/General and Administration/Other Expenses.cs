using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Other_Expenses : Group
    {
        public Other_Expenses(int fiscalYear, int fiscalMonth)
        {
            name = "OTHER EXPENSES";
            // add accounts
            plant04.accountList.Add(new Account("451", "157001"));
            plant04.accountList.Add(new Account("451", "159501"));
            plant04.accountList.Add(new Account("451", "400501"));
            plant04.accountList.Add(new Account("451", "401001"));
            plant04.accountList.Add(new Account("451", "401501"));
            plant04.accountList.Add(new Account("451", "402001"));
            plant04.accountList.Add(new Account("451", "402501"));
            plant04.accountList.Add(new Account("451", "409501"));
            plant04.accountList.Add(new Account("451", "452001"));
            plant04.accountList.Add(new Account("451", "651501"));
            plant41.accountList.Add(new Account("4151", "157001"));
            plant41.accountList.Add(new Account("4151", "159501"));
            plant41.accountList.Add(new Account("4151", "400501"));
            plant41.accountList.Add(new Account("4151", "401001"));
            plant41.accountList.Add(new Account("4151", "401501"));
            plant41.accountList.Add(new Account("4151", "402001"));
            plant41.accountList.Add(new Account("4151", "402501"));
            plant41.accountList.Add(new Account("4151", "409501"));
            plant41.accountList.Add(new Account("4151", "452001"));
            plant41.accountList.Add(new Account("4151", "651501"));
            plant48.accountList.Add(new Account("4851", "157001"));
            plant48.accountList.Add(new Account("4851", "159501"));
            plant48.accountList.Add(new Account("4851", "400501"));
            plant48.accountList.Add(new Account("4851", "401001"));
            plant48.accountList.Add(new Account("4851", "401501"));
            plant48.accountList.Add(new Account("4851", "402001"));
            plant48.accountList.Add(new Account("4851", "402501"));
            plant48.accountList.Add(new Account("4851", "409501"));
            plant48.accountList.Add(new Account("4851", "452001"));
            plant49.accountList.Add(new Account("4951", "157001"));
            plant49.accountList.Add(new Account("4951", "159501"));
            plant49.accountList.Add(new Account("4951", "400501"));
            plant49.accountList.Add(new Account("4951", "401001"));
            plant49.accountList.Add(new Account("4951", "401501"));
            plant49.accountList.Add(new Account("4951", "402001"));
            plant49.accountList.Add(new Account("4951", "402501"));
            plant49.accountList.Add(new Account("4951", "409501"));
            plant49.accountList.Add(new Account("4951", "452001"));
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
