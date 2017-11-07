using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Training_and_Development : Group
    {
        public Training_and_Development(int fiscalYear, int fiscalMonth)
        {
            name = "TRAINING AND DEVELOPMENT";
            // add accounts
            plant03.accountList.Add(new Account("300", "424000"));
            plant03.accountList.Add(new Account("300", "424000"));
            plant05.accountList.Add(new Account("500", "424000"));
            plant04.accountList.Add(new Account("473", "750101"));
            plant41.accountList.Add(new Account("4173", "750101"));
            plant48.accountList.Add(new Account("4873", "750101"));
            plant49.accountList.Add(new Account("4973", "750101"));
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
