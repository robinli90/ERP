using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Cost_of_Goods_Burden : Group
    {
        public Cost_of_Goods_Burden(int fiscalYear, int fiscalMonth)
        {
            name = "COGS BURDEN";
            // add accounts
            plant01.accountList.Add(new Account("100", "333200"));
            plant01.accountList.Add(new Account("100", "333202"));
            plant01.accountList.Add(new Account("100", "333201"));
            plant01.accountList.Add(new Account("100", "333213"));
            plant01.accountList.Add(new Account("100", "333212"));
            plant01.accountList.Add(new Account("100", "333216"));
            plant01.accountList.Add(new Account("100", "333215"));
            plant01.accountList.Add(new Account("100", "333203"));
            plant01.accountList.Add(new Account("100", "333204"));
            plant01.accountList.Add(new Account("100", "333205"));
            plant01.accountList.Add(new Account("100", "333206"));
            plant01.accountList.Add(new Account("100", "333207"));
            plant01.accountList.Add(new Account("100", "333208"));
            plant01.accountList.Add(new Account("100", "333209"));
            plant01.accountList.Add(new Account("100", "333210"));
            plant01.accountList.Add(new Account("100", "333211"));
            plant01.accountList.Add(new Account("100", "333214"));
            plant01.accountList.Add(new Account("100", "333217"));
            plant01.accountList.Add(new Account("100", "333218"));
            plant01.accountList.Add(new Account("100", "333219"));
            plant01.accountList.Add(new Account("100", "333220"));
            plant01.accountList.Add(new Account("100", "333221"));
            plant01.accountList.Add(new Account("100", "333222"));
            plant03.accountList.Add(new Account("300", "333200"));
            plant05.accountList.Add(new Account("500", "333200"));
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
