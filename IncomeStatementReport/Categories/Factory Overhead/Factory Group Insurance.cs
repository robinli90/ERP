using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Group_Insurance : Group
    {
        public Factory_Group_Insurance(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY GROUP INSURANCE";
            // add accounts

            plant05.accountList.Add(new Account("500", "404000"));
            plant05.accountList.Add(new Account("500", "404001"));
            plant05.accountList.Add(new Account("500", "404002"));

            plant03.accountList.Add(new Account("300", "404000"));
            plant03.accountList.Add(new Account("300", "404001"));
            plant03.accountList.Add(new Account("300", "404002"));

            plant01.accountList.Add(new Account("100", "404000"));
            plant01.accountList.Add(new Account("100", "404001"));
            plant01.accountList.Add(new Account("100", "404002"));



            plant04.accountList.Add(new Account("473", "30101"));
            plant04.accountList.Add(new Account("473", "30102"));
            plant04.accountList.Add(new Account("473", "30103"));
            plant04.accountList.Add(new Account("473", "30104"));
            plant04.accountList.Add(new Account("473", "30105"));
            plant04.accountList.Add(new Account("473", "30106"));
            plant04.accountList.Add(new Account("473", "30107"));
            plant04.accountList.Add(new Account("473", "30108"));
            plant04.accountList.Add(new Account("473", "30109"));
            plant04.accountList.Add(new Account("473", "30110"));
            plant04.accountList.Add(new Account("473", "30111"));
            plant04.accountList.Add(new Account("473", "30112"));
            plant41.accountList.Add(new Account("4173", "30101"));
            plant41.accountList.Add(new Account("4173", "30102"));
            plant41.accountList.Add(new Account("4173", "30103"));
            plant41.accountList.Add(new Account("4173", "30104"));
            plant41.accountList.Add(new Account("4173", "30105"));
            plant41.accountList.Add(new Account("4173", "30106"));
            plant41.accountList.Add(new Account("4173", "30107"));
            plant41.accountList.Add(new Account("4173", "30108"));
            plant41.accountList.Add(new Account("4173", "30109"));
            plant41.accountList.Add(new Account("4173", "30110"));
            plant41.accountList.Add(new Account("4173", "30111"));
            plant41.accountList.Add(new Account("4173", "30112"));
            plant48.accountList.Add(new Account("4873", "30101"));
            plant48.accountList.Add(new Account("4873", "30102"));
            plant48.accountList.Add(new Account("4873", "30103"));
            plant48.accountList.Add(new Account("4873", "30104"));
            plant48.accountList.Add(new Account("4873", "30105"));
            plant48.accountList.Add(new Account("4873", "30106"));
            plant48.accountList.Add(new Account("4873", "30107"));
            plant48.accountList.Add(new Account("4873", "30108"));
            plant48.accountList.Add(new Account("4873", "30109"));
            plant48.accountList.Add(new Account("4873", "30110"));
            plant48.accountList.Add(new Account("4873", "30111"));
            plant48.accountList.Add(new Account("4873", "30112"));
            plant49.accountList.Add(new Account("4973", "30101"));
            plant49.accountList.Add(new Account("4973", "30102"));
            plant49.accountList.Add(new Account("4973", "30103"));
            plant49.accountList.Add(new Account("4973", "30104"));
            plant49.accountList.Add(new Account("4973", "30105"));
            plant49.accountList.Add(new Account("4973", "30106"));
            plant49.accountList.Add(new Account("4973", "30107"));
            plant49.accountList.Add(new Account("4973", "30108"));
            plant49.accountList.Add(new Account("4973", "30109"));
            plant49.accountList.Add(new Account("4973", "30110"));
            plant49.accountList.Add(new Account("4973", "30111"));
            plant49.accountList.Add(new Account("4973", "30112"));
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
