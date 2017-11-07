using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Realty_Tax : Group
    {
        public Realty_Tax(int fiscalYear, int fiscalMonth)
        {
            name = "REALTY TAX";
            // add accounts
            plant01.accountList.Add(new Account("100", "417000"));
            plant03.accountList.Add(new Account("300", "417000"));
            plant05.accountList.Add(new Account("500", "417000"));
            plant04.accountList.Add(new Account("473", "90102"));
            plant41.accountList.Add(new Account("4173", "90102"));
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
