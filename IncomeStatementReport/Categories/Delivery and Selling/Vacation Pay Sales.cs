using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Vacation_Pay_Sales : Group
    {
        public Vacation_Pay_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "VACATION PAY SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "510300"));
            plant03.accountList.Add(new Account("300", "510300"));
            plant05.accountList.Add(new Account("500", "510300"));
            plant04.accountList.Add(new Account("452", "53901"));
            plant41.accountList.Add(new Account("4152", "53901"));
            plant48.accountList.Add(new Account("4852", "53901"));
            plant49.accountList.Add(new Account("4952", "53901"));
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
