using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shop_Air_Fare : Group
    {
        public Shop_Air_Fare(int fiscalYear, int fiscalMonth)
        {
            name = "SHOP AIR FARE";
            // add accounts
            plant03.accountList.Add(new Account("300", "406100"));
            plant05.accountList.Add(new Account("500", "406100"));
            plant04.accountList.Add(new Account("473", "950103"));
            plant41.accountList.Add(new Account("4173", "950103"));
            plant48.accountList.Add(new Account("4873", "950103"));
            plant49.accountList.Add(new Account("4973", "950103"));
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
