using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Tool_Amortization : Group
    {
        public Tool_Amortization(int fiscalYear, int fiscalMonth)
        {
            name = "TOOL AMORTIZATION";
            // add accounts
            plant01.accountList.Add(new Account("100", "415500"));
            plant03.accountList.Add(new Account("300", "415500"));
            plant04.accountList.Add(new Account("473", "60501"));
            plant41.accountList.Add(new Account("4173", "60501"));
            plant05.accountList.Add(new Account("500", "415500"));
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
