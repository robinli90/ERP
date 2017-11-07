using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Reorganization_Costs : Group
    {
        public Reorganization_Costs(int fiscalYear, int fiscalMonth)
        {
            name = "REORGANIZATION COSTS";
            // add accounts
            plant01.accountList.Add(new Account("100", "890000"));
            plant03.accountList.Add(new Account("300", "890000"));
            plant05.accountList.Add(new Account("500", "890000"));
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
