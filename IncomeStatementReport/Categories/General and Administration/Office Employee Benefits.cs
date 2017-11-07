using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.General_and_Administration
{
    public class Office_Employee_Benefits : Group
    {
        public Office_Employee_Benefits(int fiscalYear, int fiscalMonth)
        {
            name = "OFFICE EMPLOYEE BENEFITS";
            // add accounts
            plant01.accountList.Add(new Account("100", "603000"));
            plant03.accountList.Add(new Account("300", "603000"));
            plant05.accountList.Add(new Account("500", "603000"));
            plant04.accountList.Add(new Account("451", "52701"));
            plant04.accountList.Add(new Account("451", "53001"));
            plant04.accountList.Add(new Account("451", "53301"));
            plant04.accountList.Add(new Account("451", "53601"));
            plant04.accountList.Add(new Account("451", "54201"));
            plant41.accountList.Add(new Account("4151", "52701"));
            plant41.accountList.Add(new Account("4151", "53001"));
            plant41.accountList.Add(new Account("4151", "53301"));
            plant41.accountList.Add(new Account("4151", "53601"));
            plant41.accountList.Add(new Account("4151", "54201"));
            plant48.accountList.Add(new Account("4851", "52701"));
            plant48.accountList.Add(new Account("4851", "53001"));
            plant48.accountList.Add(new Account("4851", "53301"));
            plant48.accountList.Add(new Account("4851", "53601"));
            plant48.accountList.Add(new Account("4851", "54201"));
            plant49.accountList.Add(new Account("4951", "52701"));
            plant49.accountList.Add(new Account("4951", "53001"));
            plant49.accountList.Add(new Account("4951", "53301"));
            plant49.accountList.Add(new Account("4951", "53601"));
            plant49.accountList.Add(new Account("4951", "54201"));

            // Payroll taxes
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
