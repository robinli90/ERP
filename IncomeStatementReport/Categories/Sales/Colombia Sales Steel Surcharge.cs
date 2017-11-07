using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Colombia_Sales_Steel_Surcharge : Group
    {
        public Colombia_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "COLOMBIA SALES STEEL SURCHARGE";
            // add accounts
            plant04.accountList.Add(new Account("441", "206011"));
            plant41.accountList.Add(new Account("4141", "206011"));
            plant48.accountList.Add(new Account("4841", "206011"));
            plant49.accountList.Add(new Account("4941", "206011"));
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
