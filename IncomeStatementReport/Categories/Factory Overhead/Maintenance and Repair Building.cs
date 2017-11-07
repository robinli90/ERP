using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Maintenance_and_Repair_Building : Group
    {
        public Maintenance_and_Repair_Building(int fiscalYear, int fiscalMonth)
        {
            name = "MAINTENANCE AND REPAIR BUILDING";
            // add accounts
            plant01.accountList.Add(new Account("100", "411000"));
            plant03.accountList.Add(new Account("300", "411000"));
            plant05.accountList.Add(new Account("500", "411000"));
            plant04.accountList.Add(new Account("473", "40103"));
            plant41.accountList.Add(new Account("4173", "40103"));
            plant48.accountList.Add(new Account("4873", "40103"));
            plant49.accountList.Add(new Account("4973", "40103"));
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
