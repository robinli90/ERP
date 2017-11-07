using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Depreciation_Software : Group
    {
        public Depreciation_Software(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION SOFTWARE";
            // add accounts
            plant04.accountList.Add(new Account("473", "60402"));
            plant41.accountList.Add(new Account("4173", "60402"));
            plant48.accountList.Add(new Account("4873", "60402"));
            plant49.accountList.Add(new Account("4973", "60402"));
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
