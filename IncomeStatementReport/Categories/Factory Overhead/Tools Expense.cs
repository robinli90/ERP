using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Tools_Expense : Group
    {
        public Tools_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "TOOLS EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "415000"));
            plant03.accountList.Add(new Account("300", "415000"));
            plant05.accountList.Add(new Account("500", "415000"));
            plant04.accountList.Add(new Account("451", "991501"));
            plant04.accountList.Add(new Account("473", "50104"));
            plant04.accountList.Add(new Account("473", "50107"));
            plant41.accountList.Add(new Account("4151", "991501"));
            plant41.accountList.Add(new Account("4173", "50104"));
            plant41.accountList.Add(new Account("4173", "50107"));
            plant48.accountList.Add(new Account("4873", "50104"));
            plant48.accountList.Add(new Account("4873", "50107"));
            plant49.accountList.Add(new Account("4973", "50104"));
            plant49.accountList.Add(new Account("4973", "50107"));
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
