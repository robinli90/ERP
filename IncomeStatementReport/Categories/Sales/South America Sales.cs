using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class South_America_Sales : Group
    {
        public South_America_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "SOUTH AMERICA SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "305000"));
            plant03.accountList.Add(new Account("300", "305000"));
            plant04.accountList.Add(new Account("441", "206015"));
            plant41.accountList.Add(new Account("4141", "206015"));
            plant48.accountList.Add(new Account("4841", "206015"));
            plant49.accountList.Add(new Account("4941", "206015"));
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
