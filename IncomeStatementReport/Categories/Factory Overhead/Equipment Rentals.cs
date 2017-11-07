using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Equipment_Rentals : Group
    {
        public Equipment_Rentals(int fiscalYear, int fiscalMonth)
        {
            name = "EQUIPMENT RENTALS";
            // add accounts
            plant01.accountList.Add(new Account("100", "407000"));
            plant03.accountList.Add(new Account("300", "407000"));
            plant03.accountList.Add(new Account("300", "407100"));
            plant05.accountList.Add(new Account("500", "407000"));
            plant05.accountList.Add(new Account("500", "407100"));
            plant04.accountList.Add(new Account("473", "80101"));
            plant41.accountList.Add(new Account("4173", "80101"));
            plant48.accountList.Add(new Account("4873", "80101"));
            plant49.accountList.Add(new Account("4973", "80101"));
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
