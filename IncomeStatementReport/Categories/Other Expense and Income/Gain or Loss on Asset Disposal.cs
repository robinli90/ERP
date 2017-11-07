using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Gain_or_Loss_on_Asset_Disposal : Group
    {
        public Gain_or_Loss_on_Asset_Disposal(int fiscalYear, int fiscalMonth)
        {
            name = "GAIN OR LOSS ON ASSET DISPOSAL";
            // add accounts
            plant01.accountList.Add(new Account("100", "703500"));
            plant03.accountList.Add(new Account("300", "703500"));
            plant05.accountList.Add(new Account("500", "703500"));
            plant04.accountList.Add(new Account("453", "51001"));
            plant41.accountList.Add(new Account("4153", "51001"));
            plant48.accountList.Add(new Account("4853", "51001"));
            plant49.accountList.Add(new Account("4953", "51001"));
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
