using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class WIP_Adjustment_Overhead : Group
    {
        public WIP_Adjustment_Overhead(int fiscalYear, int fiscalMonth)
        {
            name = "WIP ADJUSTMENT OVERHEAD";
            // add accounts
            plant01.accountList.Add(new Account("100", "503300"));
            plant03.accountList.Add(new Account("300", "503300"));
            plant05.accountList.Add(new Account("500", "503300"));
            plant04.accountList.Add(new Account("473", "960101"));
            plant41.accountList.Add(new Account("4173", "960101"));
            plant48.accountList.Add(new Account("4873", "960101"));
            plant49.accountList.Add(new Account("4973", "960101"));
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
