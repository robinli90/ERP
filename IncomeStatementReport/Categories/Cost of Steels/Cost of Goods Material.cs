using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Cost_of_Goods_Material : Group
    {
        public Cost_of_Goods_Material(int fiscalYear, int fiscalMonth)
        {
            name = "COGS MATERIAL";
            // add accounts
            plant01.accountList.Add(new Account("100", "332100"));
            plant01.accountList.Add(new Account("100", "340300"));
            plant03.accountList.Add(new Account("300", "340300"));
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
