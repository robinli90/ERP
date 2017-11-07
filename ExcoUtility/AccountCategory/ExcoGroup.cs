using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class ExcoGroup
    {
        #region Variables Definition
        // actual amount this year
        protected ExcoMoney[] actualThisYear = new ExcoMoney[12];
        public ExcoMoney[] ActualThisYear
        {
            get
            {
                return actualThisYear;
            }
        }

        // actual amount ratio this year
        protected double[] actualRatioThisYear = new double[12];
        public double[] ActualRatioThisYear
        {
            get
            {
                return actualRatioThisYear;
            }
        }

        // budget amount this year
        protected ExcoMoney[] budgetThisYear = new ExcoMoney[12];
        public ExcoMoney[] BudgetThisYear
        {
            get
            {
                return budgetThisYear;
            }
        }

        // budget amount ratio this year
        protected double[] budgetRatioThisYear = new double[12];
        public double[] BudgetRatioThisYear
        {
            get
            {
                return budgetRatioThisYear;
            }
        }

        // actual amount last year
        protected ExcoMoney[] actualLastYear = new ExcoMoney[12];
        public ExcoMoney[] ActualLastYear
        {
            get
            {
                return actualLastYear;
            }
        }

        // actual amount ratio last year
        protected double[] actualRatioLastYear = new double[12];
        public double[] ActualRatioLastYear
        {
            get
            {
                return actualRatioLastYear;
            }
        }

        // the name of the group
        protected string sGroupName = string.Empty;
        public string GroupName
        {
            get
            {
                return sGroupName;
            }
        }

        // map of accounts within this group
        protected Dictionary<int, ExcoAccount> groupAccountMap = new Dictionary<int, ExcoAccount>();
        public Dictionary<int, ExcoAccount> GroupAccountList
        {
            get
            {
                return groupAccountMap;
            }
        }
        #endregion

        #region Functions Definition
        // default constructor
        public ExcoGroup(string sGroupName)
        {
            this.sGroupName = sGroupName;
            for (int i = 0; i < 12; i++)
            {
                actualThisYear[i] = new ExcoMoney();
                actualRatioThisYear[i] = 0.0;
                budgetThisYear[i] = new ExcoMoney();
                budgetRatioThisYear[i] = 0.0;
                actualLastYear[i] = new ExcoMoney();
                actualRatioLastYear[i] = 0.0;
            }
        }

        // add account to group for Markham/Michigan/Texas
        public void AddAccountThisYear(int iGLNo1, int iGLNo2, Dictionary<int, ExcoAccount> allAccountThisYearMap)
        {
            int iKey = iGLNo1 * 1000000 + iGLNo2;
            if (allAccountThisYearMap.ContainsKey(iKey))
            {
                ExcoAccount account = allAccountThisYearMap[iKey];
                groupAccountMap.Add(iKey, account);
                for (int i = 0; i < 12; i++)
                {
                    actualThisYear[i] += account.actual[i];
                    budgetThisYear[i] += account.budget[i];
                }
            }
            else
            {
                throw new Exception("Could not find account " + iKey);
            }
        }

        // add account to group for Colombia
        public void AddAccountColombiaThisYear(int iGLNo1, int iGLNo2, Dictionary<int, ExcoAccount> allAccountThisYearMap)
        {
            int iKey = iGLNo1 * 1000000 + iGLNo2;
            if (allAccountThisYearMap.ContainsKey(iKey))
            {
                ExcoAccount account = allAccountThisYearMap[iKey];
                groupAccountMap.Add(iKey, account);
                for (int i = 0; i < 12; i++)
                {
                    actualThisYear[i] += account.actual04[i];
                    actualThisYear[i] += account.actual41[i];
                    actualThisYear[i] += account.actual48[i];
                    actualThisYear[i] += account.actual49[i];
                    budgetThisYear[i] += account.budget04[i];
                    budgetThisYear[i] += account.budget41[i];
                    budgetThisYear[i] += account.budget48[i];
                    budgetThisYear[i] += account.budget49[i];
                }
            }
            else
            {
                throw new Exception("Could not find account " + iKey);
            }
        }

        // get data at last year for Markham/Michigan/Texas
        public void GetLastYearData(Dictionary<int, ExcoAccount> allAccountLastYearMap)
        {
            foreach (ExcoAccount account in groupAccountMap.Values)
            {
                int iKey = account.GLNo1 * 1000000 + account.GLNo2;
                if (allAccountLastYearMap.ContainsKey(iKey))
                {
                    ExcoAccount accountLastYear = allAccountLastYearMap[iKey];
                    for (int i = 0; i < 12; i++)
                    {
                        actualLastYear[i] += accountLastYear.actual[i];
                    }
                }
                else
                {
                    throw new Exception("Could not find account " + iKey + " at last year");
                }
            }
        }

        // get data at last year for Colombia
        public void GetLastYearDataColombia(Dictionary<int, ExcoAccount> allAccountLastYearMap)
        {
            foreach (ExcoAccount account in groupAccountMap.Values)
            {
                int iKey = account.GLNo1 * 1000000 + account.GLNo2;
                if (allAccountLastYearMap.ContainsKey(iKey))
                {
                    ExcoAccount accountLastYear = allAccountLastYearMap[iKey];
                    for (int i = 0; i < 12; i++)
                    {
                        actualLastYear[i] += accountLastYear.actual04[i];
                        actualLastYear[i] += accountLastYear.actual41[i];
                        actualLastYear[i] += accountLastYear.actual48
[i];
                        actualLastYear[i] += accountLastYear.actual49[i];
                    }
                }
                else
                {
                    throw new Exception("Could not find account " + iKey + " at last year");
                }
            }
        }

        // calculate ratio for Markham/Michigan/Texas
        public void CalculateRatio(ExcoCategory salesCategory)
        {
            foreach (ExcoAccount account in groupAccountMap.Values)
            {
                for (int i = 0; i < 12; i++)
                {
                    account.actualRatio[i] = (account.actual[i] / salesCategory.ActualThisYear[i]) * -1.0;
                    account.budgetRatio[i] = (account.budget[i] / salesCategory.BudgetThisYear[i]) * -1.0;
                }
            }
        }

        // calculate ratio for Colombia
        public void CalculateRatioColombia(ExcoCategory salesCategory)
        {
            foreach (ExcoAccount account in groupAccountMap.Values)
            {
                for (int i = 0; i < 12; i++)
                {
                    account.actualRatio04[i] = (account.actual04[i] / salesCategory.ActualThisYear[i]) * -1.0;
                    account.budgetRatio04[i] = (account.budget04[i] / salesCategory.BudgetThisYear[i]) * -1.0;
                    account.actualRatio41[i] = (account.actual41[i] / salesCategory.ActualThisYear[i]) * -1.0;
                    account.budgetRatio41[i] = (account.budget41[i] / salesCategory.BudgetThisYear[i]) * -1.0;
                    account.actualRatio48[i] = (account.actual48[i] / salesCategory.ActualThisYear[i]) * -1.0;
                    account.budgetRatio48[i] = (account.budget48[i] / salesCategory.BudgetThisYear[i]) * -1.0;
                    account.actualRatio49[i] = (account.actual49[i] / salesCategory.ActualThisYear[i]) * -1.0;
                    account.budgetRatio49[i] = (account.budget49[i] / salesCategory.BudgetThisYear[i]) * -1.0;
                }
            }
        }

        #endregion
    }
}
