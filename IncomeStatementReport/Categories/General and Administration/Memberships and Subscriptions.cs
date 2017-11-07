using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Memberships_and_Subscriptions : Group
    {
        public Memberships_and_Subscriptions(int fiscalYear, int fiscalMonth)
        {
            name = "MEMBERSHIPS AND SUBSCRIPTIONS";
            // add accounts
            plant01.accountList.Add(new Account("100", "617000"));
            plant03.accountList.Add(new Account("300", "617000"));
            plant05.accountList.Add(new Account("500", "617000"));
            plant04.accountList.Add(new Account("451", "951001"));
            plant41.accountList.Add(new Account("4151", "951001"));
            plant48.accountList.Add(new Account("4851", "951001"));
            plant49.accountList.Add(new Account("4951", "951001"));
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
