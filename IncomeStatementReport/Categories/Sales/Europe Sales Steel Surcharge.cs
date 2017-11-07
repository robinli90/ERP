using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Sales
{
    public class Europe_Sales_Steel_Surcharge : Group
    {
        public Europe_Sales_Steel_Surcharge(int fiscalYear, int fiscalMonth)
        {
            name = "EUROPE SALES STEEL SURCHARGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "303301"));
            plant03.accountList.Add(new Account("300", "303301"));
            plant04.accountList.Add(new Account("441", "206021"));
            plant05.accountList.Add(new Account("500", "303301"));
            plant41.accountList.Add(new Account("4141", "206021"));
            plant48.accountList.Add(new Account("4841", "206021"));
            plant49.accountList.Add(new Account("4941", "206021"));
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
