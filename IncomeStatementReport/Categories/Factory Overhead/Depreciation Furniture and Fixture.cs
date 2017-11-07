using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Depreciation_Furniture_and_Fixture : Group
    {
        public Depreciation_Furniture_and_Fixture(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION FURNITURE AND FIXTURE";
            // add accounts
            plant04.accountList.Add(new Account("473", "60380"));
            plant41.accountList.Add(new Account("4173", "60380"));
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
