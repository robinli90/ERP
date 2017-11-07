using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Pacific_Rim_Sales_Steel_Surcharge : Group
    {
        public Pacific_Rim_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "PACIFIC RIM SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "305501"));
            plant03.accountList.Add(new Account("300", "305501"));
            plant04.accountList.Add(new Account("441", "206026"));
            plant41.accountList.Add(new Account("4141", "206026"));
            plant48.accountList.Add(new Account("4841", "206026"));
            plant49.accountList.Add(new Account("4941", "206026"));
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
