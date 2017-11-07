using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class CAD_and_CAM_System_Maintenance : Group
    {
        public CAD_and_CAM_System_Maintenance(int fiscalYear, int fiscalMonth)
        {
            name = "CAD AND CAM SYSTEM MAINTENANCE";
            // add accounts
            plant01.accountList.Add(new Account("100", "400500"));
            plant03.accountList.Add(new Account("300", "400500"));
            plant04.accountList.Add(new Account("473", "950102"));
            plant41.accountList.Add(new Account("4173", "950102"));
            plant05.accountList.Add(new Account("500", "400500"));
            // process accounts
            plant01.GetAccountsData(fiscalYear, fiscalMonth);
            plant03.GetAccountsData(fiscalYear, fiscalMonth);
            plant05.GetAccountsData(fiscalYear, fiscalMonth);
            plant04.GetAccountsData(fiscalYear, fiscalMonth);
            plant41.GetAccountsData(fiscalYear, fiscalMonth);
            plant48.GetAccountsData(fiscalYear, fiscalMonth);
            plant49.GetAccountsData(fiscalYear, fiscalMonth);
            //added
        }

    }
}
