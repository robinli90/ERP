using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Vacation_Pay_Expense : Group
    {
        public Vacation_Pay_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "VACATION PAY EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "419000"));
            plant01.accountList.Add(new Account("100", "419001"));
            plant01.accountList.Add(new Account("100", "419002"));
            plant01.accountList.Add(new Account("100", "419100"));
            plant03.accountList.Add(new Account("300", "419000"));
            plant03.accountList.Add(new Account("300", "419001"));
            plant03.accountList.Add(new Account("300", "419002"));
            plant05.accountList.Add(new Account("500", "419000"));
            plant05.accountList.Add(new Account("500", "419001"));
            plant05.accountList.Add(new Account("500", "419002"));
            plant04.accountList.Add(new Account("473", "30113"));
            plant41.accountList.Add(new Account("4173", "30113"));
            plant48.accountList.Add(new Account("4873", "30113"));
            plant49.accountList.Add(new Account("4973", "30113"));
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
