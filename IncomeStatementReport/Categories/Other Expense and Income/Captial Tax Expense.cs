using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Captial_Tax_Expense : Group
    {
        public Captial_Tax_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "CAPITAL TAX EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "705000"));
            plant01.accountList.Add(new Account("100", "709300"));
            // wealth tax
            plant04.accountList.Add(new Account("454", "51501"));
            plant41.accountList.Add(new Account("4154", "51501"));
            plant48.accountList.Add(new Account("4854", "51501"));
            plant49.accountList.Add(new Account("4954", "51501"));

            plant04.accountList.Add(new Account("453", "159501"));
            plant41.accountList.Add(new Account("4153", "159501"));
            plant48.accountList.Add(new Account("4853", "159501"));
            plant49.accountList.Add(new Account("4953", "159501"));
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
