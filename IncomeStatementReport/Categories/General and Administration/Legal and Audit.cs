using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Legal_and_Audit : Group
    {
        public Legal_and_Audit(int fiscalYear, int fiscalMonth)
        {
            name = "LEGAL AND AUDIT";
            // add accounts
            plant01.accountList.Add(new Account("100", "611000"));
            plant03.accountList.Add(new Account("300", "611000"));
            plant05.accountList.Add(new Account("500", "611000"));
            plant04.accountList.Add(new Account("442", "503502"));
            plant04.accountList.Add(new Account("451", "101001"));
            plant04.accountList.Add(new Account("451", "101501"));
            plant04.accountList.Add(new Account("451", "102501"));
            plant41.accountList.Add(new Account("4151", "101001"));
            plant41.accountList.Add(new Account("4142", "503502"));
            plant41.accountList.Add(new Account("4151", "101501"));
            plant41.accountList.Add(new Account("4151", "102501"));
            plant48.accountList.Add(new Account("4851", "101001"));
            plant48.accountList.Add(new Account("4851", "101501"));
            plant48.accountList.Add(new Account("4851", "102501"));
            plant49.accountList.Add(new Account("4951", "101001"));
            plant49.accountList.Add(new Account("4951", "101501"));
            plant49.accountList.Add(new Account("4951", "102501"));
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
