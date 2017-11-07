using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Unclassified_Expense : Group
    {
        public Factory_Unclassified_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY UNCLASSIFIED EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "422000"));
            plant03.accountList.Add(new Account("300", "422000"));
            plant05.accountList.Add(new Account("500", "422000"));
            plant04.accountList.Add(new Account("473", "950101"));
            plant04.accountList.Add(new Account("442", "503501"));
            plant04.accountList.Add(new Account("442", "505001"));
            plant41.accountList.Add(new Account("4173", "950101"));
            plant41.accountList.Add(new Account("4142", "503501"));
            plant41.accountList.Add(new Account("4142", "505001"));
            plant48.accountList.Add(new Account("4873", "950101"));
            plant49.accountList.Add(new Account("4973", "950101"));
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
