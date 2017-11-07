using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Scrap_Sales : Group
    {
        public Scrap_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "SCRAP SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "420000"));
            plant03.accountList.Add(new Account("300", "420000"));
            plant05.accountList.Add(new Account("500", "420000"));
            plant04.accountList.Add(new Account("441", "209101"));
            plant41.accountList.Add(new Account("4141", "209101"));
            plant48.accountList.Add(new Account("4841", "209101"));
            plant49.accountList.Add(new Account("4941", "209101"));
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
