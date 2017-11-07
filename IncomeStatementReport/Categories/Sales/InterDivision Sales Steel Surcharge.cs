using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class InterDivision_Sales_Steel_Surcharge : Group
    {
        public InterDivision_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "INTERDIVISION SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "306001"));
            plant03.accountList.Add(new Account("300", "306001"));
            plant04.accountList.Add(new Account("441", "206096"));
            plant41.accountList.Add(new Account("4141", "206096"));
            plant48.accountList.Add(new Account("4841", "206096"));
            plant49.accountList.Add(new Account("4941", "206096"));
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
