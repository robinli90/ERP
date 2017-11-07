using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shop_Meals_and_Entertainment : Group
    {
        public Shop_Meals_and_Entertainment(int fiscalYear, int fiscalMonth)
        {
            name = "SHOP MEALS AND ENTERTAINMENT";
            // add accounts
            plant03.accountList.Add(new Account("300", "406000"));
            plant05.accountList.Add(new Account("500", "406000"));
            plant04.accountList.Add(new Account("473", "950104"));
            plant41.accountList.Add(new Account("4173", "950104"));
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
