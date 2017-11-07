using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class South_America_Sales_Steel_Surcharge : Group
    {
        public South_America_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "SOUTH AMERICA SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "305001"));
            plant03.accountList.Add(new Account("300", "305001"));
            plant04.accountList.Add(new Account("441", "206016"));
            plant41.accountList.Add(new Account("4141", "206016"));
            plant48.accountList.Add(new Account("4841", "206016"));
            plant49.accountList.Add(new Account("4941", "206016"));
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
