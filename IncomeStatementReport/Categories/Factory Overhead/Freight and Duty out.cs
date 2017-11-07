using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Freight_and_Duty_out : Group
    {
        public Freight_and_Duty_out(int fiscalYear, int fiscalMonth)
        {
            name = "FREIGHT AND DUTY OUT";
            // add accounts
            plant01.accountList.Add(new Account("100", "503000"));
            plant03.accountList.Add(new Account("300", "503000"));
            plant05.accountList.Add(new Account("500", "503000"));
            plant04.accountList.Add(new Account("473", "500101"));
            plant41.accountList.Add(new Account("4173", "500101"));
            plant48.accountList.Add(new Account("4873", "500101"));
            plant49.accountList.Add(new Account("4973", "500101"));
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
