using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Supplies : Group
    {
        public Office_Supplies(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE SUPPLIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "607000"));
            plant01.accountList.Add(new Account("100", "612000"));
            plant03.accountList.Add(new Account("300", "607000"));
            plant03.accountList.Add(new Account("300", "612000"));
            plant05.accountList.Add(new Account("500", "607000"));
            plant05.accountList.Add(new Account("500", "612000"));
            plant04.accountList.Add(new Account("451", "202001"));
            plant04.accountList.Add(new Account("451", "452501"));
            plant04.accountList.Add(new Account("451", "953001"));
            plant41.accountList.Add(new Account("4151", "202001"));
            plant41.accountList.Add(new Account("4151", "452501"));
            plant41.accountList.Add(new Account("4151", "953001"));
            plant48.accountList.Add(new Account("4851", "202001"));
            plant48.accountList.Add(new Account("4851", "452501"));
            plant48.accountList.Add(new Account("4851", "953001"));
            plant49.accountList.Add(new Account("4951", "202001"));
            plant49.accountList.Add(new Account("4951", "452501"));
            plant49.accountList.Add(new Account("4951", "953001"));
            plant04.accountList.Add(new Account("451", "109501"));
            plant04.accountList.Add(new Account("451", "109502"));
            plant04.accountList.Add(new Account("451", "109503"));
            plant04.accountList.Add(new Account("451", "351501"));
            plant04.accountList.Add(new Account("451", "409502"));
            plant41.accountList.Add(new Account("4151", "109501"));
            plant41.accountList.Add(new Account("4151", "109502"));
            plant41.accountList.Add(new Account("4151", "109503"));
            plant41.accountList.Add(new Account("4151", "409502"));
            plant48.accountList.Add(new Account("4851", "109501"));
            plant48.accountList.Add(new Account("4851", "109502"));
            plant48.accountList.Add(new Account("4851", "109503"));
            plant48.accountList.Add(new Account("4851", "409502"));
            plant49.accountList.Add(new Account("4951", "109501"));
            plant49.accountList.Add(new Account("4951", "109502"));
            plant49.accountList.Add(new Account("4951", "109503"));
            plant49.accountList.Add(new Account("4951", "409502"));
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
