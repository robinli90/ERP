using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shop_Supplies_Heat_Treat : Group
    {
        public Shop_Supplies_Heat_Treat(int fiscalYear, int fiscalMonth)
        {
            name = "SHOP SUPPLIES HEAT TREAT";
            // add accounts
            plant01.accountList.Add(new Account("100", "414100"));
            plant03.accountList.Add(new Account("300", "414100"));
            plant05.accountList.Add(new Account("500", "414100"));
            plant04.accountList.Add(new Account("473", "50108"));
            plant41.accountList.Add(new Account("4173", "50108"));
            plant48.accountList.Add(new Account("4873", "50108"));
            plant49.accountList.Add(new Account("4973", "50108"));
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
