using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shop_Travel : Group
    {
        public Shop_Travel(int fiscalYear, int fiscalMonth)
        {
            name = "SHOP TRAVEL";
            // add accounts
            plant03.accountList.Add(new Account("300", "405900"));
            plant05.accountList.Add(new Account("500", "405900"));
            plant04.accountList.Add(new Account("473", "80104"));
            plant04.accountList.Add(new Account("473", "950102"));
            plant41.accountList.Add(new Account("4173", "80104"));
            plant41.accountList.Add(new Account("4173", "950102"));
            plant48.accountList.Add(new Account("4873", "80104"));
            plant48.accountList.Add(new Account("4873", "950102"));
            plant49.accountList.Add(new Account("4973", "80104"));
            plant49.accountList.Add(new Account("4973", "950102"));
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
