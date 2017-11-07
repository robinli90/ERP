using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Canada_Sales_Steel_Surcharge : Group
    {
        public Canada_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "CANADA SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "300001"));
            plant03.accountList.Add(new Account("300", "300001"));
            plant04.accountList.Add(new Account("441", "206001"));
            plant41.accountList.Add(new Account("4141", "206001"));
            plant48.accountList.Add(new Account("4841", "206001"));
            plant49.accountList.Add(new Account("4941", "206001"));
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
