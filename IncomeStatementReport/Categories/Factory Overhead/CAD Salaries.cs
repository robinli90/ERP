using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class CAD_Salaries : Group
    {
        public CAD_Salaries(int fiscalYear, int fiscalMonth)
        {
            name = "CAD SALARIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "400000"));
            plant01.accountList.Add(new Account("100", "400001"));
            plant01.accountList.Add(new Account("100", "400002"));
            plant03.accountList.Add(new Account("300", "400000"));
            plant03.accountList.Add(new Account("300", "400001"));
            plant03.accountList.Add(new Account("300", "400002"));
            plant05.accountList.Add(new Account("500", "400001"));
            plant05.accountList.Add(new Account("500", "400002"));
            plant04.accountList.Add(new Account("473", "10101"));
            plant04.accountList.Add(new Account("473", "10102"));
            plant41.accountList.Add(new Account("4173", "10101"));
            plant41.accountList.Add(new Account("4173", "10102"));
            plant48.accountList.Add(new Account("4873", "10101"));
            plant48.accountList.Add(new Account("4873", "10102"));
            plant49.accountList.Add(new Account("4973", "10101"));
            plant49.accountList.Add(new Account("4973", "10102"));
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
