using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Employee_Benefits_Sales:Group
    {
        public Employee_Benefits_Sales(int fiscalYear, int fiscalMonth)
        {
            name = "EMPLOYEE BENEFITS SALES";
            // add accounts
            plant01.accountList.Add(new Account("100", "510000"));
            plant03.accountList.Add(new Account("300", "510000"));
            plant05.accountList.Add(new Account("500", "510000"));
            plant04.accountList.Add(new Account("452", "52401"));
            plant04.accountList.Add(new Account("452", "52701"));
            plant04.accountList.Add(new Account("452", "53001"));
            plant04.accountList.Add(new Account("452", "53301"));
            plant04.accountList.Add(new Account("452", "53601"));
            plant04.accountList.Add(new Account("452", "54201"));
            plant04.accountList.Add(new Account("452", "55901"));
            plant04.accountList.Add(new Account("452", "56901"));
            plant04.accountList.Add(new Account("452", "57201"));
            plant04.accountList.Add(new Account("452", "57501"));
            plant04.accountList.Add(new Account("452", "57801"));
            plant41.accountList.Add(new Account("4152", "52401"));
            plant41.accountList.Add(new Account("4152", "52701"));
            plant41.accountList.Add(new Account("4152", "53001"));
            plant41.accountList.Add(new Account("4152", "53301"));
            plant41.accountList.Add(new Account("4152", "53601"));
            plant41.accountList.Add(new Account("4152", "54201"));
            plant41.accountList.Add(new Account("4152", "55901"));
            plant41.accountList.Add(new Account("4152", "56901"));
            plant41.accountList.Add(new Account("4152", "57201"));
            plant41.accountList.Add(new Account("4152", "57501"));
            plant41.accountList.Add(new Account("4152", "57801"));
            plant48.accountList.Add(new Account("4852", "52401"));
            plant48.accountList.Add(new Account("4852", "52701"));
            plant48.accountList.Add(new Account("4852", "53001"));
            plant48.accountList.Add(new Account("4852", "53301"));
            plant48.accountList.Add(new Account("4852", "53601"));
            plant48.accountList.Add(new Account("4852", "54201"));
            plant48.accountList.Add(new Account("4852", "55901"));
            plant48.accountList.Add(new Account("4852", "56901"));
            plant48.accountList.Add(new Account("4852", "57501"));
            plant48.accountList.Add(new Account("4852", "57801"));
            plant49.accountList.Add(new Account("4952", "52401"));
            plant49.accountList.Add(new Account("4952", "52701"));
            plant49.accountList.Add(new Account("4952", "53001"));
            plant49.accountList.Add(new Account("4952", "53301"));
            plant49.accountList.Add(new Account("4952", "53601"));
            plant49.accountList.Add(new Account("4952", "54201"));
            plant49.accountList.Add(new Account("4952", "55901"));
            plant49.accountList.Add(new Account("4952", "56901"));
            plant49.accountList.Add(new Account("4952", "57501"));
            plant49.accountList.Add(new Account("4952", "57801"));
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
