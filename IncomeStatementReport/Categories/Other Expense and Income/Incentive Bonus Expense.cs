using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Incentive_Bonus_Expense : Group
    {
        public Incentive_Bonus_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "INCENTIVE BONUS EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "708000"));
            plant03.accountList.Add(new Account("300", "708000"));
            plant05.accountList.Add(new Account("500", "708000"));
            plant04.accountList.Add(new Account("453", "959501"));
            plant41.accountList.Add(new Account("4153", "959501"));
            plant48.accountList.Add(new Account("4853", "959501"));
            plant49.accountList.Add(new Account("4953", "959501"));
            // New incentive account for colombia only
            // process accounts
            plant04.accountList.Add(new Account("442", "503501"));
            plant41.accountList.Add(new Account("4142", "503501"));
            plant48.accountList.Add(new Account("4842", "503501"));
            plant49.accountList.Add(new Account("4942", "503501"));
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
