using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Direct_Labour
{
    public class Direct_Labour_Shop : Group
    {
        public Direct_Labour_Shop(int fiscalYear, int fiscalMonth)
        {
            name = "DIRECT LABOUR SHOP";
            // add accounts
            plant01.accountList.Add(new Account("100", "350014"));
            plant01.accountList.Add(new Account("100", "350013"));
            plant01.accountList.Add(new Account("100", "350016"));
            plant01.accountList.Add(new Account("100", "350015"));
            plant01.accountList.Add(new Account("100", "350017"));
            plant01.accountList.Add(new Account("100", "350018"));
            plant01.accountList.Add(new Account("100", "350020"));
            plant01.accountList.Add(new Account("100", "350019"));
            plant01.accountList.Add(new Account("100", "350021"));
            plant01.accountList.Add(new Account("100", "350022"));
            plant01.accountList.Add(new Account("100", "350024"));
            plant01.accountList.Add(new Account("100", "350023"));
            plant01.accountList.Add(new Account("100", "350002"));
            plant01.accountList.Add(new Account("100", "350003"));
            plant01.accountList.Add(new Account("100", "350004"));
            plant01.accountList.Add(new Account("100", "350005"));
            plant01.accountList.Add(new Account("100", "350006"));
            plant01.accountList.Add(new Account("100", "350007"));
            plant01.accountList.Add(new Account("100", "350008"));
            plant01.accountList.Add(new Account("100", "350009"));
            plant01.accountList.Add(new Account("100", "350010"));
            plant01.accountList.Add(new Account("100", "350011"));
            plant01.accountList.Add(new Account("100", "350012"));
            plant01.accountList.Add(new Account("100", "350202"));
            plant01.accountList.Add(new Account("100", "350000"));
            plant01.accountList.Add(new Account("100", "350001"));
            plant01.accountList.Add(new Account("100", "350200"));
            plant01.accountList.Add(new Account("100", "350201"));
            plant01.accountList.Add(new Account("100", "350028"));
            plant01.accountList.Add(new Account("100", "350027"));
            plant03.accountList.Add(new Account("300", "350200"));
            plant03.accountList.Add(new Account("300", "350201"));
            plant03.accountList.Add(new Account("300", "350202"));
            plant03.accountList.Add(new Account("300", "350300"));
            plant03.accountList.Add(new Account("300", "350002"));
            plant03.accountList.Add(new Account("300", "350004"));
            plant03.accountList.Add(new Account("300", "350006"));
            plant03.accountList.Add(new Account("300", "350008"));
            plant03.accountList.Add(new Account("300", "350010"));
            plant03.accountList.Add(new Account("300", "350012"));
            plant03.accountList.Add(new Account("300", "350014"));
            plant03.accountList.Add(new Account("300", "350016"));
            plant03.accountList.Add(new Account("300", "350018"));
            plant03.accountList.Add(new Account("300", "350020"));
            plant03.accountList.Add(new Account("300", "350022"));
            plant03.accountList.Add(new Account("300", "350024"));
            plant03.accountList.Add(new Account("300", "350028"));
            plant03.accountList.Add(new Account("300", "350000"));
            plant03.accountList.Add(new Account("300", "350001"));
            plant03.accountList.Add(new Account("300", "350003"));
            plant03.accountList.Add(new Account("300", "350005"));
            plant03.accountList.Add(new Account("300", "350007"));
            plant03.accountList.Add(new Account("300", "350009"));
            plant03.accountList.Add(new Account("300", "350011"));
            plant03.accountList.Add(new Account("300", "350013"));
            plant03.accountList.Add(new Account("300", "350015"));
            plant03.accountList.Add(new Account("300", "350017"));
            plant03.accountList.Add(new Account("300", "350019"));
            plant03.accountList.Add(new Account("300", "350021"));
            plant03.accountList.Add(new Account("300", "350023"));
            plant03.accountList.Add(new Account("300", "350027"));
            plant05.accountList.Add(new Account("500", "350001"));
            plant05.accountList.Add(new Account("500", "350002"));

            plant05.accountList.Add(new Account("500", "350003"));
            plant05.accountList.Add(new Account("500", "350004"));
            plant05.accountList.Add(new Account("500", "350005"));
            plant05.accountList.Add(new Account("500", "350006"));
            plant05.accountList.Add(new Account("500", "350007"));
            plant05.accountList.Add(new Account("500", "350008"));
            plant05.accountList.Add(new Account("500", "350009"));
            plant05.accountList.Add(new Account("500", "350010"));
            plant05.accountList.Add(new Account("500", "350011"));
            plant05.accountList.Add(new Account("500", "350012"));
            plant05.accountList.Add(new Account("500", "350013"));
            plant05.accountList.Add(new Account("500", "350014"));
            plant05.accountList.Add(new Account("500", "350015"));
            plant05.accountList.Add(new Account("500", "350016"));
            plant05.accountList.Add(new Account("500", "350017"));
            plant05.accountList.Add(new Account("500", "350018"));
            plant05.accountList.Add(new Account("500", "350019"));
            plant05.accountList.Add(new Account("500", "350020"));
            plant05.accountList.Add(new Account("500", "350021"));
            plant05.accountList.Add(new Account("500", "350022"));
            plant05.accountList.Add(new Account("500", "350023"));
            plant05.accountList.Add(new Account("500", "350024"));
            plant05.accountList.Add(new Account("500", "350025"));
            plant05.accountList.Add(new Account("500", "350026"));
            plant05.accountList.Add(new Account("500", "350027"));
            plant05.accountList.Add(new Account("500", "350028"));
            plant05.accountList.Add(new Account("500", "350201"));
            plant05.accountList.Add(new Account("500", "350202"));

            plant05.accountList.Add(new Account("500", "350300"));
            plant04.accountList.Add(new Account("472", "10101"));
            plant04.accountList.Add(new Account("472", "10102"));
            plant41.accountList.Add(new Account("4172", "10101"));
            plant41.accountList.Add(new Account("4172", "10102"));
            plant48.accountList.Add(new Account("4872", "10101"));
            plant48.accountList.Add(new Account("4872", "10102"));
            plant49.accountList.Add(new Account("4972", "10101"));
            plant49.accountList.Add(new Account("4972", "10102"));
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
