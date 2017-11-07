using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Postage : Group
    {
        public Postage(int fiscalYear, int fiscalMonth)
        {
            name = "POSTAGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "613000"));
            plant03.accountList.Add(new Account("300", "613000"));
            plant05.accountList.Add(new Account("500", "613000"));
            plant04.accountList.Add(new Account("451", "354001"));
            plant41.accountList.Add(new Account("4151", "354001"));
            plant48.accountList.Add(new Account("4851", "354001"));
            plant49.accountList.Add(new Account("4951", "354001"));
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
