using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Group_Insurance_Sales : Group
    {
        public Group_Insurance_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "GROUP INSURANCE SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "510100"));
            plant03.accountList.Add(new Account("300", "510100"));
            plant05.accountList.Add(new Account("500", "510100"));
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
