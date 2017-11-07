using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Depreciation_Automobile:Group
    {
                public Depreciation_Automobile(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION AUTOMOBILE";
            // add accounts
            plant01.accountList.Add(new Account("100", "505500"));
            plant03.accountList.Add(new Account("300", "505500"));
            plant05.accountList.Add(new Account("500", "505500"));

            //depriciation automobile
            plant04.accountList.Add(new Account("473", "60601"));
            plant41.accountList.Add(new Account("4173", "60601"));

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
