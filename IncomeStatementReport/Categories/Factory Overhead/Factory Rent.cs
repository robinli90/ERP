using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Rent : Group
    {
        public Factory_Rent(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY RENT";
            // add accounts
            plant05.accountList.Add(new Account("500", "413000"));
            plant05.accountList.Add(new Account("500", "413001"));
            plant04.accountList.Add(new Account("473", "80102"));
            plant04.accountList.Add(new Account("473", "80103"));
            plant41.accountList.Add(new Account("4173", "80102"));
            plant41.accountList.Add(new Account("4173", "80103"));
            plant48.accountList.Add(new Account("4873", "80102"));
            plant48.accountList.Add(new Account("4873", "80103"));
            plant49.accountList.Add(new Account("4973", "80102"));
            plant49.accountList.Add(new Account("4973", "80103"));
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
