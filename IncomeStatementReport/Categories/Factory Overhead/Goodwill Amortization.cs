using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Goodwill_Amortization : Group
    {
        public Goodwill_Amortization(int fiscalYear, int fiscalMonth)
        {
            name = "GOODWILL AMORTIZATION";
            // add accounts
            plant04.accountList.Add(new Account("473", "69001"));
            plant41.accountList.Add(new Account("4173", "69001"));
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
