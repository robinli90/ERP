using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Statutory_Holiday_Sales : Group
    {
        public Statutory_Holiday_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "STATUTORY HOLIDAY SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "510400"));
            plant03.accountList.Add(new Account("300", "510400"));
            plant05.accountList.Add(new Account("500", "510400"));
            plant04.accountList.Add(new Account("452", "53801"));
            plant41.accountList.Add(new Account("4152", "53801"));
            plant48.accountList.Add(new Account("4852", "53801"));
            plant49.accountList.Add(new Account("4952", "53801"));
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
