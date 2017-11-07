using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories.Direct_Labour
{
    public class CAM_Salaries : Group
    {
        public CAM_Salaries(int fiscalYear, int fiscalMonth)
        {
            name = "CAM SALARIES";
            // add accounts
            plant01.accountList.Add(new Account("100", "351000"));
            plant01.accountList.Add(new Account("100", "351001"));
            plant01.accountList.Add(new Account("100", "351002"));
            plant03.accountList.Add(new Account("300", "351000"));
            plant03.accountList.Add(new Account("300", "351001"));
            plant03.accountList.Add(new Account("300", "351002"));
            plant05.accountList.Add(new Account("500", "351001"));
            plant05.accountList.Add(new Account("500", "351002"));
            plant04.accountList.Add(new Account("472", "11601"));
            plant04.accountList.Add(new Account("472", "11602"));
            plant04.accountList.Add(new Account("472", "970101"));
            plant41.accountList.Add(new Account("4172", "11601"));
            plant41.accountList.Add(new Account("4172", "11602"));
            plant41.accountList.Add(new Account("4172", "970101"));
            plant48.accountList.Add(new Account("4872", "11601"));
            plant48.accountList.Add(new Account("4872", "11602"));
            plant48.accountList.Add(new Account("4872", "970101"));
            plant49.accountList.Add(new Account("4972", "11601"));
            plant49.accountList.Add(new Account("4972", "11602"));
            plant49.accountList.Add(new Account("4972", "970101"));
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
