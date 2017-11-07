using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Cash_and__Volume_Discount : Group
    {
        public Cash_and__Volume_Discount(int fiscalYear, int fiscalMonth)
        {
            name = "CASH & VOLUMN DISCOUNTS";
            // add accounts
            plant01.accountList.Add(new Account("100", "308000"));
            plant03.accountList.Add(new Account("300", "308000"));
            plant05.accountList.Add(new Account("500", "308000"));
            plant04.accountList.Add(new Account("441", "750101"));
            plant41.accountList.Add(new Account("4141", "750101"));
            plant48.accountList.Add(new Account("4841", "750101"));
            plant49.accountList.Add(new Account("4941", "750101"));
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
