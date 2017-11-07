using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Statutory_Holiday : Group
    {
        public Statutory_Holiday(int fiscalYear, int fiscalMonth)
        {
            name = "STATUTORY HOLIDAY";
            // add accounts
            plant01.accountList.Add(new Account("100", "419003"));
            plant01.accountList.Add(new Account("100", "419004"));
            plant03.accountList.Add(new Account("300", "419003"));
            plant03.accountList.Add(new Account("300", "419004"));
            plant03.accountList.Add(new Account("300", "419100"));
            plant05.accountList.Add(new Account("500", "419003"));
            plant05.accountList.Add(new Account("500", "419004"));
            plant04.accountList.Add(new Account("473", "30114"));
            plant41.accountList.Add(new Account("4173", "30114"));
            plant48.accountList.Add(new Account("4873", "30114"));
            plant49.accountList.Add(new Account("4973", "30114"));
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
