using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class InterDivision_Sales : Group
    {
        public InterDivision_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "INTERDIVISION SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "306000"));
            plant03.accountList.Add(new Account("300", "306000"));
            plant05.accountList.Add(new Account("500", "306000"));
            plant04.accountList.Add(new Account("441", "206095"));
            plant41.accountList.Add(new Account("4141", "206095"));
            plant48.accountList.Add(new Account("4841", "206095"));
            plant49.accountList.Add(new Account("4941", "206095"));
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
