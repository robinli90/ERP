using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Depreciation_Building : Group
    {
        public Depreciation_Building(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION BUILDING";
            // add accounts
            plant01.accountList.Add(new Account("100", "401500"));
            plant03.accountList.Add(new Account("300", "401500"));
            plant05.accountList.Add(new Account("500", "401500"));
            plant04.accountList.Add(new Account("473", "60101"));
            plant04.accountList.Add(new Account("473", "60102"));
            plant41.accountList.Add(new Account("4173", "60101"));
            plant41.accountList.Add(new Account("4173", "60102"));
            plant48.accountList.Add(new Account("4873", "60101"));
            plant48.accountList.Add(new Account("4873", "60102"));
            plant49.accountList.Add(new Account("4973", "60101"));
            plant49.accountList.Add(new Account("4973", "60102"));
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
