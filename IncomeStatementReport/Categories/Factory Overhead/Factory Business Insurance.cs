using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Business_Insurance : Group
    {
        public Factory_Business_Insurance(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY BUSINESS INSURANCE";
            // add accounts
            plant01.accountList.Add(new Account("100", "410000"));
            plant03.accountList.Add(new Account("300", "410000"));
            plant05.accountList.Add(new Account("500", "410000"));
            plant04.accountList.Add(new Account("473", "100101"));
            plant41.accountList.Add(new Account("4173", "100101"));
            plant48.accountList.Add(new Account("4873", "100101"));
            plant49.accountList.Add(new Account("4973", "100101"));
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
