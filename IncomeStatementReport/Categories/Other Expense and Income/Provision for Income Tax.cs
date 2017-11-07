using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Provision_for_Income_Tax : Group
    {
        public Provision_for_Income_Tax(int fiscalYear, int fiscalMonth)
        {
            name = "PROVISION FOR INCOME TAX";
            // add accounts
            plant03.accountList.Add(new Account("300", "707500"));
            plant05.accountList.Add(new Account("500", "707500"));
            plant04.accountList.Add(new Account("454", "50501"));
            plant04.accountList.Add(new Account("454", "51001"));
            plant41.accountList.Add(new Account("4154", "50501"));
            plant41.accountList.Add(new Account("4154", "51001"));
            plant48.accountList.Add(new Account("4854", "50501"));
            plant49.accountList.Add(new Account("4954", "50501"));
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
