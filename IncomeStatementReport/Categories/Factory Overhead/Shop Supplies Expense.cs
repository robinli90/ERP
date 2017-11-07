using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shop_Supplies_Expense : Group
    {
        public Shop_Supplies_Expense(int fiscalYear, int fiscalMonth)
        {
            name = "SHOP SUPPLIES EXPENSE";
            // add accounts
            plant01.accountList.Add(new Account("100", "414000"));
            plant03.accountList.Add(new Account("300", "414000"));
            plant03.accountList.Add(new Account("300", "414500"));
            plant05.accountList.Add(new Account("500", "414000"));
            plant05.accountList.Add(new Account("500", "414500"));
            plant04.accountList.Add(new Account("473", "50101"));
            plant04.accountList.Add(new Account("473", "50105"));
            plant04.accountList.Add(new Account("473", "50106"));
            plant04.accountList.Add(new Account("473", "50190"));
            plant41.accountList.Add(new Account("4173", "50101"));
            plant41.accountList.Add(new Account("4173", "50105"));
            plant41.accountList.Add(new Account("4173", "50106"));
            plant41.accountList.Add(new Account("4173", "50190"));
            plant48.accountList.Add(new Account("4873", "50101"));
            plant48.accountList.Add(new Account("4873", "50105"));
            plant48.accountList.Add(new Account("4873", "50106"));
            plant48.accountList.Add(new Account("4873", "50190"));
            plant49.accountList.Add(new Account("4973", "50101"));
            plant49.accountList.Add(new Account("4973", "50105"));
            plant49.accountList.Add(new Account("4973", "50106"));
            plant49.accountList.Add(new Account("4973", "50190"));
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
