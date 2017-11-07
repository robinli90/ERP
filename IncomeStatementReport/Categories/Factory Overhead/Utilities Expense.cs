using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Utilities_Expense : Group
    {
        public Utilities_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "UTILITIES EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "408000"));
            plant01.accountList.Add(new Account("100", "408001"));
            plant01.accountList.Add(new Account("100", "408002"));
            plant01.accountList.Add(new Account("100", "408003"));
            plant01.accountList.Add(new Account("100", "408004"));
            plant03.accountList.Add(new Account("300", "408000"));
            plant03.accountList.Add(new Account("300", "408001"));
            plant03.accountList.Add(new Account("300", "408002"));
            plant03.accountList.Add(new Account("300", "408003"));
            plant03.accountList.Add(new Account("300", "408004"));
            plant05.accountList.Add(new Account("500", "408000"));
            plant05.accountList.Add(new Account("500", "408001"));
            plant05.accountList.Add(new Account("500", "408002"));
            plant05.accountList.Add(new Account("500", "408003"));
            plant05.accountList.Add(new Account("500", "408004"));
            plant04.accountList.Add(new Account("473", "70101"));
            plant04.accountList.Add(new Account("473", "70102"));
            plant04.accountList.Add(new Account("473", "70301"));
            plant04.accountList.Add(new Account("473", "70401"));
            plant41.accountList.Add(new Account("4173", "70101"));
            plant41.accountList.Add(new Account("4173", "70102"));
            plant41.accountList.Add(new Account("4173", "70301"));
            plant41.accountList.Add(new Account("4173", "70401"));
            plant48.accountList.Add(new Account("4873", "70101"));
            plant48.accountList.Add(new Account("4873", "70102"));
            plant48.accountList.Add(new Account("4873", "70301"));
            plant48.accountList.Add(new Account("4873", "70401"));
            plant49.accountList.Add(new Account("4973", "70101"));
            plant49.accountList.Add(new Account("4973", "70102"));
            plant49.accountList.Add(new Account("4973", "70301"));
            plant49.accountList.Add(new Account("4973", "70401"));
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
