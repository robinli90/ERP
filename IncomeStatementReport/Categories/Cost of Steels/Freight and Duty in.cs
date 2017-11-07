using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Freight_and_Duty_in : Group
    {
        public Freight_and_Duty_in(int fiscalYear, int fiscalMonth)
        {
            name = "FREIGHT AND DUTY IN";
            // add accounts
            plant01.accountList.Add(new Account("100", "316000"));
            plant01.accountList.Add(new Account("100", "316001"));
            plant03.accountList.Add(new Account("300", "316000"));
            plant03.accountList.Add(new Account("300", "316001"));
            plant05.accountList.Add(new Account("500", "316000"));
            plant04.accountList.Add(new Account("471", "40101"));
            plant04.accountList.Add(new Account("471", "40102"));
            plant41.accountList.Add(new Account("4171", "40101"));
            plant41.accountList.Add(new Account("4171", "40102"));
            plant48.accountList.Add(new Account("4871", "40101"));
            plant48.accountList.Add(new Account("4871", "40102"));
            plant49.accountList.Add(new Account("4971", "40101"));
            plant49.accountList.Add(new Account("4971", "40102"));
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
