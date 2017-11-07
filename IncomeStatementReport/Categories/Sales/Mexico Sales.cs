using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Mexico_Sales : Group
    {
        public Mexico_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "MEXICO SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "303000"));
            plant03.accountList.Add(new Account("300", "303000"));
            plant05.accountList.Add(new Account("500", "303000"));
            plant04.accountList.Add(new Account("441", "206030"));
            plant41.accountList.Add(new Account("4141", "206030"));
            plant48.accountList.Add(new Account("4841", "206030"));
            plant49.accountList.Add(new Account("4941", "206030"));
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
