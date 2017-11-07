using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Sales_Salaries : Group
    {
        public Sales_Salaries(int fiscalYear, int fiscalMonth)
        {
            name = "SALES SALARIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "507000"));
            plant03.accountList.Add(new Account("300", "507000"));
            plant05.accountList.Add(new Account("500", "507000"));
            plant04.accountList.Add(new Account("452", "50301"));
            plant04.accountList.Add(new Account("452", "50601"));
            plant04.accountList.Add(new Account("452", "51501"));
            plant41.accountList.Add(new Account("4152", "50301"));
            plant41.accountList.Add(new Account("4152", "50601"));
            plant41.accountList.Add(new Account("4152", "51501"));
            plant48.accountList.Add(new Account("4852", "50301"));
            plant48.accountList.Add(new Account("4852", "50601"));
            plant48.accountList.Add(new Account("4852", "51501"));
            plant49.accountList.Add(new Account("4952", "50301"));
            plant49.accountList.Add(new Account("4952", "50601"));
            plant49.accountList.Add(new Account("4952", "51501"));
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
