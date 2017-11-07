using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class InterCompany_Purchases : Group
    {
        public InterCompany_Purchases(int fiscalYear, int fiscalMonth)
        {
            name = "INTERCOMPANY PURCHASES";
            // add accounts
            plant01.accountList.Add(new Account("100", "310200"));
            plant01.accountList.Add(new Account("100", "310201"));
            plant01.accountList.Add(new Account("100", "318000"));
            plant01.accountList.Add(new Account("100", "332500"));
            plant05.accountList.Add(new Account("500", "318000"));
            plant04.accountList.Add(new Account("471", "90101"));
            plant41.accountList.Add(new Account("4171", "90101"));
            plant48.accountList.Add(new Account("4871", "90101"));
            plant49.accountList.Add(new Account("4971", "90101"));
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
