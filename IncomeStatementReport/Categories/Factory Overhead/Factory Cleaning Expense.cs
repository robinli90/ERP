using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Cleaning_Expense : Group
    {
        public Factory_Cleaning_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY CLEANING EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "421000"));
            plant03.accountList.Add(new Account("300", "421000"));
            plant05.accountList.Add(new Account("500", "421000"));
            plant04.accountList.Add(new Account("473", "950110"));
            plant41.accountList.Add(new Account("4173", "950110"));
            plant48.accountList.Add(new Account("4873", "950110"));
            plant49.accountList.Add(new Account("4973", "950110"));
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
