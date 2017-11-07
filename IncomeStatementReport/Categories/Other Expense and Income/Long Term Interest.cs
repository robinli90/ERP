using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Long_Term_Interest : Group
    {
        public Long_Term_Interest(int fiscalYear, int fiscalMonth)
        {
            name = "LONG TERM INTEREST";
            // add accounts
            plant01.accountList.Add(new Account("100", "701500"));
            plant03.accountList.Add(new Account("300", "701500"));
            plant05.accountList.Add(new Account("500", "701500"));
            plant04.accountList.Add(new Account("453", "52001"));
            plant04.accountList.Add(new Account("453", "52002"));
            plant41.accountList.Add(new Account("4153", "52001"));
            plant41.accountList.Add(new Account("4153", "52002"));
            plant48.accountList.Add(new Account("4853", "52001"));
            plant48.accountList.Add(new Account("4853", "52002"));
            plant49.accountList.Add(new Account("4953", "52001"));
            plant49.accountList.Add(new Account("4953", "52002"));
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
