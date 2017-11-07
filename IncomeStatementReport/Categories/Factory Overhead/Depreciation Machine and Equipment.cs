using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Factory_Overhead
{
    public class Depreciation_Machine_and_Equipment : Group
    {
        public Depreciation_Machine_and_Equipment(int fiscalYear, int fiscalMonth)
        {
            name = "DEPRECIATION MACHINE AND EQUIPMENT";
            // add accounts
            plant01.accountList.Add(new Account("100", "402000"));
            plant01.accountList.Add(new Account("100", "402001"));
            plant01.accountList.Add(new Account("100", "402009"));
            plant01.accountList.Add(new Account("100", "402003"));
            plant01.accountList.Add(new Account("100", "402005"));
            plant01.accountList.Add(new Account("100", "402011"));
            plant01.accountList.Add(new Account("100", "402004"));
            plant01.accountList.Add(new Account("100", "402006"));
            plant01.accountList.Add(new Account("100", "402007"));
            plant01.accountList.Add(new Account("100", "402002"));
            plant01.accountList.Add(new Account("100", "402008"));
            plant01.accountList.Add(new Account("100", "402013"));
            plant01.accountList.Add(new Account("100", "402012"));
            plant01.accountList.Add(new Account("100", "402010"));

            plant03.accountList.Add(new Account("300", "402000"));
            plant03.accountList.Add(new Account("300", "402001"));
            plant03.accountList.Add(new Account("300", "402002"));
            plant03.accountList.Add(new Account("300", "402003"));
            plant03.accountList.Add(new Account("300", "402004"));
            plant03.accountList.Add(new Account("300", "402005"));
            plant03.accountList.Add(new Account("300", "402006"));
            plant03.accountList.Add(new Account("300", "402007"));
            plant03.accountList.Add(new Account("300", "402008"));
            plant03.accountList.Add(new Account("300", "402009"));
            plant03.accountList.Add(new Account("300", "402010"));
            plant03.accountList.Add(new Account("300", "402011"));
            plant03.accountList.Add(new Account("300", "402012"));
            plant03.accountList.Add(new Account("300", "402013"));
            plant03.accountList.Add(new Account("300", "402014"));

            plant05.accountList.Add(new Account("500", "402000"));
            plant05.accountList.Add(new Account("500", "402002"));
            plant05.accountList.Add(new Account("500", "402003"));
            plant05.accountList.Add(new Account("500", "402004"));
            plant05.accountList.Add(new Account("500", "402005"));
            plant05.accountList.Add(new Account("500", "402006"));
            plant05.accountList.Add(new Account("500", "402007"));
            plant05.accountList.Add(new Account("500", "402008"));
            plant05.accountList.Add(new Account("500", "402009"));
            plant05.accountList.Add(new Account("500", "402010"));
            plant05.accountList.Add(new Account("500", "402011"));
            plant05.accountList.Add(new Account("500", "402012"));
            plant05.accountList.Add(new Account("500", "402013"));
            plant05.accountList.Add(new Account("500", "402014"));

            plant04.accountList.Add(new Account("473", "60301"));
            plant04.accountList.Add(new Account("473", "60302"));
            plant04.accountList.Add(new Account("473", "60303"));
            plant04.accountList.Add(new Account("473", "60304"));
            plant04.accountList.Add(new Account("473", "60305"));
            plant04.accountList.Add(new Account("473", "60306"));
            plant04.accountList.Add(new Account("473", "60307"));
            plant04.accountList.Add(new Account("473", "60308"));
            plant04.accountList.Add(new Account("473", "60309"));
            plant04.accountList.Add(new Account("473", "60310"));
            plant04.accountList.Add(new Account("473", "60311"));
            plant04.accountList.Add(new Account("473", "60312"));
            plant04.accountList.Add(new Account("473", "60313"));
            plant04.accountList.Add(new Account("473", "60395"));

            plant41.accountList.Add(new Account("4173", "60301"));
            plant41.accountList.Add(new Account("4173", "60302"));
            plant41.accountList.Add(new Account("4173", "60303"));
            plant41.accountList.Add(new Account("4173", "60304"));
            plant41.accountList.Add(new Account("4173", "60305"));
            plant41.accountList.Add(new Account("4173", "60306"));
            plant41.accountList.Add(new Account("4173", "60307"));
            plant41.accountList.Add(new Account("4173", "60308"));
            plant41.accountList.Add(new Account("4173", "60309"));
            plant41.accountList.Add(new Account("4173", "60310"));
            plant41.accountList.Add(new Account("4173", "60311"));
            plant41.accountList.Add(new Account("4173", "60312"));
            plant41.accountList.Add(new Account("4173", "60313"));
            plant41.accountList.Add(new Account("4173", "60395"));

            plant48.accountList.Add(new Account("4873", "60301"));
            plant48.accountList.Add(new Account("4873", "60302"));
            plant48.accountList.Add(new Account("4873", "60303"));
            plant48.accountList.Add(new Account("4873", "60304"));
            plant48.accountList.Add(new Account("4873", "60305"));
            plant48.accountList.Add(new Account("4873", "60306"));
            plant48.accountList.Add(new Account("4873", "60307"));
            plant48.accountList.Add(new Account("4873", "60308"));
            plant48.accountList.Add(new Account("4873", "60309"));
            plant48.accountList.Add(new Account("4873", "60310"));
            plant48.accountList.Add(new Account("4873", "60311"));
            plant48.accountList.Add(new Account("4873", "60312"));
            plant48.accountList.Add(new Account("4873", "60313"));
            plant48.accountList.Add(new Account("4873", "60395"));

            plant49.accountList.Add(new Account("4973", "60301"));
            plant49.accountList.Add(new Account("4973", "60302"));
            plant49.accountList.Add(new Account("4973", "60303"));
            plant49.accountList.Add(new Account("4973", "60304"));
            plant49.accountList.Add(new Account("4973", "60305"));
            plant49.accountList.Add(new Account("4973", "60306"));
            plant49.accountList.Add(new Account("4973", "60307"));
            plant49.accountList.Add(new Account("4973", "60308"));
            plant49.accountList.Add(new Account("4973", "60309"));
            plant49.accountList.Add(new Account("4973", "60310"));
            plant49.accountList.Add(new Account("4973", "60311"));
            plant49.accountList.Add(new Account("4973", "60312"));
            plant49.accountList.Add(new Account("4973", "60313"));
            plant49.accountList.Add(new Account("4973", "60395"));
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
