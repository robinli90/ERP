using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Business_Tax : Group
    {
        public Factory_Business_Tax(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY BUSINESS TAX";
            // add accounts
            plant01.accountList.Add(new Account("100", "416000"));
            plant03.accountList.Add(new Account("300", "416000"));
            plant05.accountList.Add(new Account("500", "416000"));
            plant04.accountList.Add(new Account("473", "90101"));
            plant04.accountList.Add(new Account("473", "959501"));
            plant41.accountList.Add(new Account("4173", "90101"));
            plant48.accountList.Add(new Account("4873", "90101"));
            plant49.accountList.Add(new Account("4973", "90101"));

            //business tax
            plant04.accountList.Add(new Account("451", "150501"));
            plant04.accountList.Add(new Account("451", "959501"));
            plant04.accountList.Add(new Account("452", "959501"));
            plant41.accountList.Add(new Account("4151", "150501"));
            plant41.accountList.Add(new Account("4151", "959501"));
            plant41.accountList.Add(new Account("4152", "959501"));
            plant48.accountList.Add(new Account("4851", "150501"));
            plant49.accountList.Add(new Account("4951", "150501"));

            //commercial insurance
            plant04.accountList.Add(new Account("451", "309501"));
            plant41.accountList.Add(new Account("4151", "309501"));
            plant48.accountList.Add(new Account("4851", "309501"));
            plant49.accountList.Add(new Account("4951", "309501"));

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
