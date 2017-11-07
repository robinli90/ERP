using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class CAD_and_CAM_Supplies : Group
    {
        public CAD_and_CAM_Supplies(int fiscalYear, int fiscalMonth)
        {
            name = "CAD and CAM SUPPLIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "401000"));
            plant03.accountList.Add(new Account("300", "401000"));
            plant05.accountList.Add(new Account("500", "401000"));
            plant04.accountList.Add(new Account("473", "50102"));
            plant41.accountList.Add(new Account("4173", "50102"));
            plant48.accountList.Add(new Account("4873", "50102"));
            plant49.accountList.Add(new Account("4973", "50102"));
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
