using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Software_Amortization : Group
    {
        public Software_Amortization(int fiscalYear, int fiscalMonth)
        {
            name = "SOFTWARE AMORTIZATION";
            // add accounts
            plant01.accountList.Add(new Account("100", "609500"));
            plant03.accountList.Add(new Account("300", "609500"));
            plant05.accountList.Add(new Account("500", "609500"));

            //software depreciation
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
