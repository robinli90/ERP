using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Factory_Employee_Benefits : Group
    {
        public Factory_Employee_Benefits(int fiscalYear, int fiscalMonth)
        {
            name = "FACTORY EMPLOYEE BENEFITS";
            // add accounts
            plant01.accountList.Add(new Account("100", "403001"));
            plant01.accountList.Add(new Account("100", "403002"));
            plant03.accountList.Add(new Account("300", "403001"));
            plant03.accountList.Add(new Account("300", "403002"));
            plant05.accountList.Add(new Account("500", "403001"));
            plant05.accountList.Add(new Account("500", "403002"));

            plant04.accountList.Add(new Account("473", "20101"));
            plant04.accountList.Add(new Account("473", "20102"));
            plant04.accountList.Add(new Account("473", "20103"));
            plant04.accountList.Add(new Account("473", "20104"));
            plant04.accountList.Add(new Account("473", "20105"));
            plant04.accountList.Add(new Account("473", "20106"));
            plant04.accountList.Add(new Account("473", "20107"));
            plant04.accountList.Add(new Account("473", "20108"));
            plant04.accountList.Add(new Account("473", "20109"));
            plant04.accountList.Add(new Account("473", "20110"));
            plant04.accountList.Add(new Account("473", "20111"));
            plant04.accountList.Add(new Account("473", "20112"));
            plant04.accountList.Add(new Account("473", "20113"));
            plant04.accountList.Add(new Account("473", "20114"));
            plant41.accountList.Add(new Account("4173", "20101"));
            plant41.accountList.Add(new Account("4173", "20102"));
            plant41.accountList.Add(new Account("4173", "20103"));
            plant41.accountList.Add(new Account("4173", "20104"));
            plant41.accountList.Add(new Account("4173", "20105"));
            plant41.accountList.Add(new Account("4173", "20106"));
            plant41.accountList.Add(new Account("4173", "20107"));
            plant41.accountList.Add(new Account("4173", "20108"));
            plant41.accountList.Add(new Account("4173", "20109"));
            plant41.accountList.Add(new Account("4173", "20110"));
            plant41.accountList.Add(new Account("4173", "20111"));
            plant41.accountList.Add(new Account("4173", "20112"));
            plant41.accountList.Add(new Account("4173", "20113"));
            plant41.accountList.Add(new Account("4173", "20114"));
            plant48.accountList.Add(new Account("4873", "20101"));
            plant48.accountList.Add(new Account("4873", "20102"));
            plant48.accountList.Add(new Account("4873", "20103"));
            plant48.accountList.Add(new Account("4873", "20104"));
            plant48.accountList.Add(new Account("4873", "20105"));
            plant48.accountList.Add(new Account("4873", "20106"));
            plant48.accountList.Add(new Account("4873", "20107"));
            plant48.accountList.Add(new Account("4873", "20108"));
            plant48.accountList.Add(new Account("4873", "20109"));
            plant48.accountList.Add(new Account("4873", "20110"));
            plant48.accountList.Add(new Account("4873", "20111"));
            plant48.accountList.Add(new Account("4873", "20112"));
            plant48.accountList.Add(new Account("4873", "20113"));
            plant48.accountList.Add(new Account("4873", "20114"));
            plant49.accountList.Add(new Account("4973", "20101"));
            plant49.accountList.Add(new Account("4973", "20102"));
            plant49.accountList.Add(new Account("4973", "20103"));
            plant49.accountList.Add(new Account("4973", "20104"));
            plant49.accountList.Add(new Account("4973", "20105"));
            plant49.accountList.Add(new Account("4973", "20106"));
            plant49.accountList.Add(new Account("4973", "20107"));
            plant49.accountList.Add(new Account("4973", "20108"));
            plant49.accountList.Add(new Account("4973", "20109"));
            plant49.accountList.Add(new Account("4973", "20110"));
            plant49.accountList.Add(new Account("4973", "20111"));
            plant49.accountList.Add(new Account("4973", "20112"));
            plant49.accountList.Add(new Account("4973", "20113"));
            plant49.accountList.Add(new Account("4973", "20114"));
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
