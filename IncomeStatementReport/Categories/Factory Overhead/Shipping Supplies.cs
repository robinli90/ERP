using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Shipping_Supplies : Group
    {
        public Shipping_Supplies(int fiscalYear, int fiscalMonth)
        {
            name = "SHIPPING SUPPLIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "500000"));
            plant03.accountList.Add(new Account("300", "500000"));
            plant05.accountList.Add(new Account("500", "500000"));
            plant04.accountList.Add(new Account("473", "50103"));
            plant41.accountList.Add(new Account("4173", "50103"));
            plant48.accountList.Add(new Account("4873", "50103"));
            plant49.accountList.Add(new Account("4973", "50103"));
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
