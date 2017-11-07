using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class USA_Sales_Steel_Surcharge : Group
    {
        public USA_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "USA SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "304001"));
            plant03.accountList.Add(new Account("300", "304001"));
            plant05.accountList.Add(new Account("500", "304001"));
            plant04.accountList.Add(new Account("441", "206006"));
            plant41.accountList.Add(new Account("4141", "206006"));
            plant48.accountList.Add(new Account("4841", "206006"));
            plant49.accountList.Add(new Account("4941", "206006"));
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
