using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_South_America_Travel : Group
    {
        public Office_South_America_Travel(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE SOUTH AMERICA TRAVEL";
            // add accounts
            plant01.accountList.Add(new Account("100", "623001"));
            plant01.accountList.Add(new Account("100", "623002"));
            plant01.accountList.Add(new Account("100", "624001"));
            plant01.accountList.Add(new Account("100", "624002"));
            plant03.accountList.Add(new Account("300", "623001"));
            plant03.accountList.Add(new Account("300", "623002"));
            plant03.accountList.Add(new Account("300", "624001"));
            plant03.accountList.Add(new Account("300", "624002"));
            plant03.accountList.Add(new Account("300", "625001"));
            plant03.accountList.Add(new Account("300", "625002"));

            // FO sa travel
            plant03.accountList.Add(new Account("300", "405901"));
            plant03.accountList.Add(new Account("300", "405902"));
            plant03.accountList.Add(new Account("300", "406001"));
            plant03.accountList.Add(new Account("300", "406002"));
            plant03.accountList.Add(new Account("300", "406101"));
            plant03.accountList.Add(new Account("300", "406102"));

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
