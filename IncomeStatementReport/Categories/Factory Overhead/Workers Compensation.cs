using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Workers_Compensation : Group
    {
        public Workers_Compensation(int fiscalYear, int fiscalMonth)
        {
            name = "WORKERS COMPENSATION";
            // add accounts
            plant01.accountList.Add(new Account("100", "418000"));
            plant01.accountList.Add(new Account("100", "418001"));
            plant01.accountList.Add(new Account("100", "418002"));
            plant03.accountList.Add(new Account("300", "418000"));
            plant03.accountList.Add(new Account("300", "418001"));
            plant03.accountList.Add(new Account("300", "418002"));
            plant05.accountList.Add(new Account("500", "418000"));
            plant05.accountList.Add(new Account("500", "418001"));
            plant05.accountList.Add(new Account("500", "418002"));
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
