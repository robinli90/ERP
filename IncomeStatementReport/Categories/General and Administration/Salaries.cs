using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Salaries : Group
    {
        public Salaries(int fiscalYear, int fiscalMonth)
        {
            name = "SALARIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "600000"));
            plant01.accountList.Add(new Account("100", "601000"));
            plant03.accountList.Add(new Account("300", "600000"));
            plant03.accountList.Add(new Account("300", "601000"));
            plant05.accountList.Add(new Account("500", "600000"));
            plant05.accountList.Add(new Account("500", "601000"));
            plant04.accountList.Add(new Account("451", "50301"));
            plant04.accountList.Add(new Account("451", "50601"));
            plant04.accountList.Add(new Account("451", "51501"));
            plant41.accountList.Add(new Account("4151", "50301"));
            plant41.accountList.Add(new Account("4151", "50601"));
            plant41.accountList.Add(new Account("4151", "51501"));
            plant48.accountList.Add(new Account("4851", "50301"));
            plant48.accountList.Add(new Account("4851", "50601"));
            plant48.accountList.Add(new Account("4851", "51501"));
            plant49.accountList.Add(new Account("4951", "50601"));
            plant49.accountList.Add(new Account("4951", "51501"));
            plant49.accountList.Add(new Account("4951", "50301"));
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
