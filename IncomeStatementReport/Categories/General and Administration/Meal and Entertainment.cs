using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Meal_and_Entertainment : Group
    {
        public Meal_and_Entertainment(int fiscalYear, int fiscalMonth)
        {
            name = "MEAL AND ENTERTAINMENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "623000"));
            plant03.accountList.Add(new Account("300", "623000"));
            plant05.accountList.Add(new Account("500", "623000"));
            plant04.accountList.Add(new Account("451", "559501"));
            plant04.accountList.Add(new Account("451", "559502"));
            plant41.accountList.Add(new Account("4151", "559501"));
            plant48.accountList.Add(new Account("4851", "559501"));
            plant49.accountList.Add(new Account("4951", "559501"));
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
