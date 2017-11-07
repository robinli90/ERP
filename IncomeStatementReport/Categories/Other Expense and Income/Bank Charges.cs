using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Bank_Charges : Group
    {
        public Bank_Charges(int fiscalYear, int fiscalMonth)
        {
            name = "BANK CHARGES";
            // add accounts
            plant01.accountList.Add(new Account("100", "700000"));
            plant03.accountList.Add(new Account("300", "700000"));
            plant05.accountList.Add(new Account("500", "700000"));
            plant04.accountList.Add(new Account("453", "50501"));
            plant04.accountList.Add(new Account("453", "51501"));
            plant41.accountList.Add(new Account("4153", "50501"));
            plant41.accountList.Add(new Account("4153", "51501"));
            plant48.accountList.Add(new Account("4853", "50501"));
            plant48.accountList.Add(new Account("4853", "51501"));
            plant49.accountList.Add(new Account("4953", "50501"));
            plant49.accountList.Add(new Account("4953", "51501"));
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
