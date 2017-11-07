using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Cost_of_Steels
{
    public class Raw_Material_Steel_Usage : Group
    {
        public Raw_Material_Steel_Usage(int fiscalYear, int fiscalMonth)
        {
            name = "RAW MATERIAL STEEL USAGE";
            // add accounts
            plant01.accountList.Add(new Account("100", "311000"));
            plant01.accountList.Add(new Account("100", "311001"));
            plant01.accountList.Add(new Account("100", "332000"));
            plant01.accountList.Add(new Account("100", "333100"));
            plant01.accountList.Add(new Account("100", "333300"));
            plant01.accountList.Add(new Account("100", "340100"));
            plant01.accountList.Add(new Account("100", "340200"));
            plant03.accountList.Add(new Account("300", "310200"));
            plant03.accountList.Add(new Account("300", "333300"));
            plant03.accountList.Add(new Account("300", "310201"));
            plant03.accountList.Add(new Account("300", "311000"));
            plant03.accountList.Add(new Account("300", "311001"));
            plant03.accountList.Add(new Account("300", "318000"));
            plant03.accountList.Add(new Account("300", "332000"));
            plant03.accountList.Add(new Account("300", "332100"));
            plant03.accountList.Add(new Account("300", "332500"));
            plant03.accountList.Add(new Account("300", "333100"));
            plant05.accountList.Add(new Account("500", "333100"));
            plant05.accountList.Add(new Account("500", "311000"));
            plant05.accountList.Add(new Account("500", "311001"));
            plant05.accountList.Add(new Account("500", "332100"));
            plant05.accountList.Add(new Account("500", "332500"));
            plant05.accountList.Add(new Account("500", "333300"));
            plant04.accountList.Add(new Account("471", "10101"));
            plant04.accountList.Add(new Account("471", "10201"));
            plant41.accountList.Add(new Account("4171", "10101"));
            plant41.accountList.Add(new Account("4171", "10201"));
            plant48.accountList.Add(new Account("4871", "10101"));
            plant48.accountList.Add(new Account("4871", "10201"));
            plant49.accountList.Add(new Account("4971", "10101"));
            plant49.accountList.Add(new Account("4971", "10201"));

            // Cost of goods burden
            plant01.accountList.Add(new Account("100", "333200"));
            plant01.accountList.Add(new Account("100", "333202"));
            plant01.accountList.Add(new Account("100", "333201"));
            plant01.accountList.Add(new Account("100", "333213"));
            plant01.accountList.Add(new Account("100", "333212"));
            plant01.accountList.Add(new Account("100", "333216"));
            plant01.accountList.Add(new Account("100", "333215"));
            plant01.accountList.Add(new Account("100", "333203"));
            plant01.accountList.Add(new Account("100", "333204"));
            plant01.accountList.Add(new Account("100", "333205"));
            plant01.accountList.Add(new Account("100", "333206"));
            plant01.accountList.Add(new Account("100", "333207"));
            plant01.accountList.Add(new Account("100", "333208"));
            plant01.accountList.Add(new Account("100", "333209"));
            plant01.accountList.Add(new Account("100", "333210"));
            plant01.accountList.Add(new Account("100", "333211"));
            plant01.accountList.Add(new Account("100", "333214"));
            plant01.accountList.Add(new Account("100", "333217"));
            plant01.accountList.Add(new Account("100", "333218"));
            plant01.accountList.Add(new Account("100", "333219"));
            plant01.accountList.Add(new Account("100", "333220"));
            plant01.accountList.Add(new Account("100", "333221"));
            plant01.accountList.Add(new Account("100", "333222"));
            plant03.accountList.Add(new Account("300", "333200"));
            plant05.accountList.Add(new Account("500", "333200"));

            //costs of material
            plant01.accountList.Add(new Account("100", "332100"));
            plant01.accountList.Add(new Account("100", "340300"));
            plant03.accountList.Add(new Account("300", "340300"));

            //cost of steels reclass
            plant04.accountList.Add(new Account("461", "209501"));
            plant04.accountList.Add(new Account("473", "970101"));
            plant04.accountList.Add(new Account("471", "970101"));
            plant41.accountList.Add(new Account("4161", "209501"));
            plant41.accountList.Add(new Account("4171", "970101"));
            plant41.accountList.Add(new Account("4173", "970101"));
            plant48.accountList.Add(new Account("4861", "209501"));
            plant48.accountList.Add(new Account("4871", "970101"));
            plant48.accountList.Add(new Account("4873", "970101"));
            plant49.accountList.Add(new Account("4961", "209501"));
            plant49.accountList.Add(new Account("4971", "970101"));
            plant49.accountList.Add(new Account("4973", "970101"));

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
