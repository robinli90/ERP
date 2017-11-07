using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Cost_of_Steels_Reclass : Group
    {
        public Cost_of_Steels_Reclass(int fiscalYear, int fiscalMonth)
        {
            name = "COST OF STEELS RECLASS";
            // add accounts
            plant04.accountList.Add(new Account("461", "209501"));
            plant04.accountList.Add(new Account("473", "970101"));
            plant04.accountList.Add(new Account("471", "970101"));
            plant41.accountList.Add(new Account("4161", "209501"));
            plant41.accountList.Add(new Account("4171", "970101"));
            plant41.accountList.Add(new Account("4173", "970101"));
            plant48.accountList.Add(new Account("4861", "209501"));
            plant48.accountList.Add(new Account("4871", "970101"));
            plant48.accountList.Add(new Account("4873", "970101"));
            plant49.accountList.Add(new Account("4961", "209501"));
            plant49.accountList.Add(new Account("4971", "970101"));
            plant49.accountList.Add(new Account("4973", "970101"));
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
