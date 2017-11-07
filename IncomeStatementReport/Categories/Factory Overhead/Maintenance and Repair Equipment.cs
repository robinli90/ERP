using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Maintenance_and_Repair_Equipment : Group
    {
        public Maintenance_and_Repair_Equipment(int fiscalYear, int fiscalMonth)
        {
            name = "MAINTENANCE AND REPAIR EQUIPMENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "412000"));
            plant03.accountList.Add(new Account("300", "412000"));
            plant05.accountList.Add(new Account("500", "412000"));
            plant04.accountList.Add(new Account("473", "40101"));
            plant04.accountList.Add(new Account("473", "40102"));
            plant04.accountList.Add(new Account("473", "40108"));
            plant04.accountList.Add(new Account("473", "40190"));
            plant41.accountList.Add(new Account("4173", "40101"));
            plant41.accountList.Add(new Account("4173", "40102"));
            plant41.accountList.Add(new Account("4173", "40108"));
            plant41.accountList.Add(new Account("4173", "40190"));
            plant48.accountList.Add(new Account("4873", "40101"));
            plant48.accountList.Add(new Account("4873", "40102"));
            plant48.accountList.Add(new Account("4873", "40108"));
            plant48.accountList.Add(new Account("4873", "40190"));
            plant49.accountList.Add(new Account("4973", "40101"));
            plant49.accountList.Add(new Account("4973", "40102"));
            plant49.accountList.Add(new Account("4973", "40108"));
            plant49.accountList.Add(new Account("4973", "40190"));
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
