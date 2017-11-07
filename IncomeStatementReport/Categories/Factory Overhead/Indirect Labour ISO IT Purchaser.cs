using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Indirect_Labour_ISO_IT_Purchaser : Group
    {
        public Indirect_Labour_ISO_IT_Purchaser(int fiscalYear, int fiscalMonth)
        {
            name = "INDIRECT LABOUR ISO IT PURCHASER";
            // add accounts
            plant01.accountList.Add(new Account("100", "400700"));
            plant01.accountList.Add(new Account("100", "400701"));
            plant01.accountList.Add(new Account("100", "400702"));
            plant03.accountList.Add(new Account("300", "400700"));
            plant03.accountList.Add(new Account("300", "400701"));
            plant03.accountList.Add(new Account("300", "400702"));
            plant05.accountList.Add(new Account("500", "400701"));
            plant05.accountList.Add(new Account("500", "400702"));
            plant04.accountList.Add(new Account("473", "10201"));
            plant04.accountList.Add(new Account("473", "10202"));
            plant41.accountList.Add(new Account("4173", "10201"));
            plant41.accountList.Add(new Account("4173", "10202"));
            plant48.accountList.Add(new Account("4873", "10201"));
            plant48.accountList.Add(new Account("4873", "10202"));
            plant49.accountList.Add(new Account("4973", "10201"));
            plant49.accountList.Add(new Account("4973", "10202"));
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
