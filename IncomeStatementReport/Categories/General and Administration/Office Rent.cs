using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Rent : Group
    {
        public Office_Rent(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE RENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "614000"));
            plant03.accountList.Add(new Account("300", "614000"));
            plant05.accountList.Add(new Account("500", "614000"));
            plant04.accountList.Add(new Account("451", "201001"));
            plant41.accountList.Add(new Account("4151", "201001"));
            plant48.accountList.Add(new Account("4851", "201001"));
            plant49.accountList.Add(new Account("4951", "201001"));
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
