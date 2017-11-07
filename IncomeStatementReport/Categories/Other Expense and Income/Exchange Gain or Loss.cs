using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Other_Expense_and_Income
{
    public class Exchange_Gain_or_Loss : Group
    {
        public Exchange_Gain_or_Loss(int fiscalYear, int fiscalMonth)
        {
            name = "EXCHANGE GAIN OR LOSS";
            // add accounts
            plant01.accountList.Add(new Account("100", "704000"));
            plant04.accountList.Add(new Account("442", "102001"));
            plant04.accountList.Add(new Account("453", "52501"));
            plant41.accountList.Add(new Account("4142", "102001"));
            plant41.accountList.Add(new Account("4153", "52501"));
            plant48.accountList.Add(new Account("4853", "52501"));
            plant49.accountList.Add(new Account("4953", "52501"));
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
