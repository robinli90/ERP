using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class SubContract_Work : Group
    {
        public SubContract_Work(int fiscalYear, int fiscalMonth)
        {
            name = "SUBCONTRACT WORK";
            // add accounts
            plant01.accountList.Add(new Account("100", "319000"));
            plant03.accountList.Add(new Account("300", "319000"));
            plant03.accountList.Add(new Account("300", "319100"));
            plant05.accountList.Add(new Account("500", "319000"));
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
