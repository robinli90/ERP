using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Advertising_Expense : Group
    {
        public Advertising_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "ADVERTISING EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "504000"));
            plant03.accountList.Add(new Account("300", "504000"));
            plant05.accountList.Add(new Account("500", "504000"));
            plant04.accountList.Add(new Account("452", "356001"));
            plant41.accountList.Add(new Account("4152", "356001"));
            plant48.accountList.Add(new Account("4852", "356001"));
            plant49.accountList.Add(new Account("4952", "356001"));
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
