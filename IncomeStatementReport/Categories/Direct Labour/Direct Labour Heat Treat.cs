using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Direct_Labour
{
    public class Direct_Labour_Heat_Treat : Group
    {
        public Direct_Labour_Heat_Treat(int fiscalYear, int fiscalMonth)
        {
            name = "DIRECT LABOUR HEAT TREAT";
            // add accounts
            plant01.accountList.Add(new Account("100", "350100"));
            plant01.accountList.Add(new Account("100", "350101"));
            plant01.accountList.Add(new Account("100", "350102"));
            plant03.accountList.Add(new Account("300", "350100"));
            plant03.accountList.Add(new Account("300", "350101"));
            plant03.accountList.Add(new Account("300", "350102"));
            plant04.accountList.Add(new Account("472", "11501"));
            plant04.accountList.Add(new Account("472", "11502"));
            plant41.accountList.Add(new Account("4172", "11501"));
            plant41.accountList.Add(new Account("4172", "11502"));
            plant05.accountList.Add(new Account("500", "350101"));
            plant05.accountList.Add(new Account("500", "350102"));
            plant48.accountList.Add(new Account("4872", "11501"));
            plant48.accountList.Add(new Account("4872", "11502"));
            plant49.accountList.Add(new Account("4972", "11501"));
            plant49.accountList.Add(new Account("4972", "11502"));
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
