using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class SubContract : Group
    {
        public SubContract(int fiscalYear, int fiscalMonth)
        {
            name = "SUB CONTRACT";
            // add accounts
            plant04.accountList.Add(new Account("471", "20101"));
            plant41.accountList.Add(new Account("4171", "20101"));
            plant48.accountList.Add(new Account("4871", "20101"));
            plant49.accountList.Add(new Account("4971", "20101"));

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
