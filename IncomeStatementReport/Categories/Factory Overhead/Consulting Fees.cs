using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Consulting_Fees : Group
    {
        public Consulting_Fees(int fiscalYear, int fiscalMonth)
        {
            name = "CONSULTING FEES";
            // add accounts
            plant01.accountList.Add(new Account("100", "401100"));
            plant03.accountList.Add(new Account("300", "401100"));
            plant05.accountList.Add(new Account("500", "401100"));
            plant04.accountList.Add(new Account("473", "800101"));
            plant41.accountList.Add(new Account("4173", "800101"));
            plant48.accountList.Add(new Account("4873", "800101"));
            plant49.accountList.Add(new Account("4973", "800101"));
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
