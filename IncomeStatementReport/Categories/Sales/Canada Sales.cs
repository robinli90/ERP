using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Canada_Sales : Group
    {
        public Canada_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "CANADA SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "300000"));
            plant03.accountList.Add(new Account("300", "300000"));
            plant04.accountList.Add(new Account("441", "206000"));
            plant41.accountList.Add(new Account("4141", "206000"));
            plant48.accountList.Add(new Account("4841", "206000"));
            plant49.accountList.Add(new Account("4941", "206000"));
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
