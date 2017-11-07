using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Payroll_Taxes : Group
    {
        public Payroll_Taxes(int fiscalYear, int fiscalMonth)
        {
            name = "PAYROLL TAXES";
            // add accounts
            /* grouped with employee benefits
            plant04.accountList.Add(new Account("451", "55901"));
            plant04.accountList.Add(new Account("451", "56901"));
            plant04.accountList.Add(new Account("451", "57201"));
            plant04.accountList.Add(new Account("451", "57501"));
            plant04.accountList.Add(new Account("451", "57801"));
            plant41.accountList.Add(new Account("4151", "55901"));
            plant41.accountList.Add(new Account("4151", "56901"));
            plant41.accountList.Add(new Account("4151", "57201"));
            plant41.accountList.Add(new Account("4151", "57501"));
            plant41.accountList.Add(new Account("4151", "57801"));
            plant48.accountList.Add(new Account("4851", "55901"));
            plant48.accountList.Add(new Account("4851", "56901"));
            plant48.accountList.Add(new Account("4851", "57201"));
            plant48.accountList.Add(new Account("4851", "57501"));
            plant48.accountList.Add(new Account("4851", "57801"));
            plant49.accountList.Add(new Account("4951", "55901"));
            plant49.accountList.Add(new Account("4951", "56901"));
            plant49.accountList.Add(new Account("4951", "57201"));
            plant49.accountList.Add(new Account("4951", "57501"));
            plant49.accountList.Add(new Account("4951", "57801"));
             * */
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
