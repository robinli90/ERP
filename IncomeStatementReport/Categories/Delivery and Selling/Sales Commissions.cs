using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Delivery_and_Selling
{
    public class Sales_Commissions : Group
    {
        public Sales_Commissions(int fiscalYear, int fiscalMonth)
        {
            name = "SALES COMMISSIONS";
            // add accounts
            plant01.accountList.Add(new Account("100", "307000"));
            plant03.accountList.Add(new Account("300", "307000"));
            plant05.accountList.Add(new Account("500", "307000"));
            plant04.accountList.Add(new Account("452", "51801"));
            plant41.accountList.Add(new Account("4152", "51801"));
            plant48.accountList.Add(new Account("4852", "51801"));
            plant49.accountList.Add(new Account("4952", "51801"));
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
