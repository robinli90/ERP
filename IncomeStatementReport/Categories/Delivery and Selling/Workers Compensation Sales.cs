using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Workers_Compensation_Sales : Group
    {
        public Workers_Compensation_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "WORKERS COMPENSATION SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "510200"));
            plant03.accountList.Add(new Account("300", "510200"));
            plant05.accountList.Add(new Account("500", "510200"));
            plant04.accountList.Add(new Account("452", "56801"));
            plant41.accountList.Add(new Account("4152", "56801"));
            plant48.accountList.Add(new Account("4852", "56801"));
            plant49.accountList.Add(new Account("4952", "56801"));
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
