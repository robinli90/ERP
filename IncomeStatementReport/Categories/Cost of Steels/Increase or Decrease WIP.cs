using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Increase_or_Decrease_WIP : Group
    {
        public Increase_or_Decrease_WIP(int fiscalYear, int fiscalMonth)
        {
            name = "INCREASE/DECREASE WIP";
            // add accounts
            plant01.accountList.Add(new Account("100", "333000"));
            plant03.accountList.Add(new Account("300", "333000"));
            plant03.accountList.Add(new Account("300", "340200"));
            plant05.accountList.Add(new Account("500", "333000"));
            plant04.accountList.Add(new Account("471", "10301"));
            plant41.accountList.Add(new Account("4171", "10301"));
            plant48.accountList.Add(new Account("4871", "10301"));
            plant49.accountList.Add(new Account("4971", "10301"));

            //WIP Obselecense
            plant03.accountList.Add(new Account("300", "340100"));

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
