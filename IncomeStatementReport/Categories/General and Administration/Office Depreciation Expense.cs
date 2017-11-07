using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Depreciation_Expense : Group
    {
        public Office_Depreciation_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE DEPRECIATION EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "609000"));
            plant03.accountList.Add(new Account("300", "609000"));
            plant05.accountList.Add(new Account("500", "609000"));
            plant04.accountList.Add(new Account("451", "600501"));
            plant04.accountList.Add(new Account("451", "601501"));
            plant04.accountList.Add(new Account("451", "602001"));
            plant41.accountList.Add(new Account("4151", "600501"));
            plant41.accountList.Add(new Account("4151", "601501"));
            plant41.accountList.Add(new Account("4151", "602001"));
            plant48.accountList.Add(new Account("4851", "600501"));
            plant48.accountList.Add(new Account("4851", "601501"));
            plant48.accountList.Add(new Account("4851", "602001"));
            plant49.accountList.Add(new Account("4951", "600501"));
            plant49.accountList.Add(new Account("4951", "601501"));
            plant49.accountList.Add(new Account("4951", "602001"));

            //furniture
            plant04.accountList.Add(new Account("473", "60380"));
            plant41.accountList.Add(new Account("4173", "60380"));


            plant49.accountList.Add(new Account("4973", "60401"));
            plant48.accountList.Add(new Account("4873", "60401"));
            plant41.accountList.Add(new Account("4173", "60401"));
            plant04.accountList.Add(new Account("473", "60401"));

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
