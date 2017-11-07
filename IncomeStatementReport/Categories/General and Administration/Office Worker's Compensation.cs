using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Workers_Compensation : Group
    {
        public Office_Workers_Compensation(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE WORKER'S COMPENSATION";
            // add accounts
            plant01.accountList.Add(new Account("100", "622000"));
            plant03.accountList.Add(new Account("300", "622000"));
            plant05.accountList.Add(new Account("500", "622000"));
            plant04.accountList.Add(new Account("451", "56801"));
            plant41.accountList.Add(new Account("4151", "56801"));
            plant48.accountList.Add(new Account("4851", "56801"));
            plant49.accountList.Add(new Account("4951", "56801"));
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
