using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Supervisory_Salaries : Group
    {
        public Supervisory_Salaries(int fiscalYear, int fiscalMonth)
        {
            name = "SUPERVISORY SALARIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "409000"));
            plant03.accountList.Add(new Account("300", "409000"));
            plant05.accountList.Add(new Account("500", "409000"));
            plant04.accountList.Add(new Account("473", "10301"));
            plant41.accountList.Add(new Account("4173", "10301"));
            plant48.accountList.Add(new Account("4873", "10301"));
            plant49.accountList.Add(new Account("4973", "10301"));
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
