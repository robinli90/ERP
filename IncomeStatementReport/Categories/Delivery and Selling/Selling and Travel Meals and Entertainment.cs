using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Selling_and_Travel_Meals_and_Entertainment : Group
    {
        public Selling_and_Travel_Meals_and_Entertainment(int fiscalYear, int fiscalMonth)
        {
            name = "SELLING AND TRAVEL MEALS AND ENTERTAINMENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "505900"));
            plant03.accountList.Add(new Account("300", "505900"));
            plant05.accountList.Add(new Account("500", "505900"));
            plant04.accountList.Add(new Account("452", "559501"));
            plant04.accountList.Add(new Account("452", "559502"));
            plant41.accountList.Add(new Account("4152", "559501"));
            plant41.accountList.Add(new Account("4152", "559502"));
            plant48.accountList.Add(new Account("4852", "559501"));
            plant49.accountList.Add(new Account("4952", "559501"));
            // shop meals
            plant03.accountList.Add(new Account("300", "406000"));
            plant05.accountList.Add(new Account("500", "406000"));
            plant04.accountList.Add(new Account("473", "950104"));
            plant41.accountList.Add(new Account("4173", "950104"));
            // office meals
            plant01.accountList.Add(new Account("100", "623000"));
            plant03.accountList.Add(new Account("300", "623000"));
            plant05.accountList.Add(new Account("500", "623000"));
            plant04.accountList.Add(new Account("451", "559501"));
            plant04.accountList.Add(new Account("451", "559502"));
            plant41.accountList.Add(new Account("4151", "559501"));
            plant41.accountList.Add(new Account("4151", "559502"));
            plant48.accountList.Add(new Account("4851", "559501"));
            plant49.accountList.Add(new Account("4951", "559501"));
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
