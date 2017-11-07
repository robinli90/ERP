using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public abstract class ExcoCategory
    {
        #region Variables Definition
        // actual amount this year (sum of all accounts within)
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

        // budget amount this year (sum of all accounts within)
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

        // actual amount last year (sum of all accounts within)
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

        // the name of the category
        protected string sCategoryName = string.Empty;
        public string CategoryName
        {
            get
            {
                return sCategoryName;
            }
        }

        // list of groups within this category
        protected List<ExcoGroup> groupList = new List<ExcoGroup>();
        public List<ExcoGroup> GroupList
        {
            get
            {
                return groupList;
            }
        }
        #endregion

        #region Functions Definition
        // default constructor
        public ExcoCategory()
        {
            // initialize
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

        // add a group to this category
        protected abstract void AddGroup();
        protected abstract void AddGroupColombia();
        #endregion
    }
}
