using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Depreciation_Building_Improvement : Group
    {
        public Depreciation_Building_Improvement(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION BUILDING IMPROVEMENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "401700"));
            plant03.accountList.Add(new Account("300", "401700"));
            plant05.accountList.Add(new Account("500", "401700"));
            plant04.accountList.Add(new Account("473", "60201"));
            plant41.accountList.Add(new Account("4173", "60201"));
            plant48.accountList.Add(new Account("4873", "60201"));
            plant49.accountList.Add(new Account("4973", "60201"));
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
