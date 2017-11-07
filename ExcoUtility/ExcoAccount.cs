using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace ExcoUtility
{
    public class ExcoAccount
    {
        #region Variables Definition
        private int glNo1 = 0;
        public int GLNo1
        {
            get
            {
                return glNo1;
            }
        }
        private int glNo2 = 0;
        public int GLNo2
        {
            get
            {
                return glNo2;
            }
        }
        private string sTitle = string.Empty;
        public string Title
        {
            get
            {
                return sTitle;
            }
        }
        private int fiscalYear = 0;
        public int FiscalYear
        {
            get
            {
                return fiscalYear;
            }
        }

        #region Markham, Michigan and Texas
        // actual amount this year
        public ExcoMoney[] actual = new ExcoMoney[12];
        public double[] actualRatio = new double[12];
        // budget amount this year
        public ExcoMoney[] budget = new ExcoMoney[12];
        public double[] budgetRatio = new double[12];
        // actual amount last year
        public ExcoMoney[] actualLastYear = new ExcoMoney[12];
        public double[] actualRatioLastYear = new double[12];
        #endregion

        #region Colombia
        // actual amount this year
        public ExcoMoney[] actual04 = new ExcoMoney[12];
        public double[] actualRatio04 = new double[12];
        public ExcoMoney[] actual41 = new ExcoMoney[12];
        public double[] actualRatio41 = new double[12];
        public ExcoMoney[] actual48 = new ExcoMoney[12];
        public double[] actualRatio48 = new double[12];
        public ExcoMoney[] actual49 = new ExcoMoney[12];
        public double[] actualRatio49 = new double[12];
        // budget amount this year
        public ExcoMoney[] budget04 = new ExcoMoney[12];
        public double[] budgetRatio04 = new double[12];
        public ExcoMoney[] budget41 = new ExcoMoney[12];
        public double[] budgetRatio41 = new double[12];
        public ExcoMoney[] budget48 = new ExcoMoney[12];
        public double[] budgetRatio48 = new double[12];
        public ExcoMoney[] budget49 = new ExcoMoney[12];
        public double[] budgetRatio49 = new double[12];
        // actual amount last year
        public ExcoMoney[] actualLastYear04 = new ExcoMoney[12];
        public double[] actualRatioLastYear04 = new double[12];
        public ExcoMoney[] actualLastYear41 = new ExcoMoney[12];
        public double[] actualRatioLastYear41 = new double[12];
        public ExcoMoney[] actualLastYear48 = new ExcoMoney[12];
        public double[] actualRatioLastYear48 = new double[12];
        public ExcoMoney[] actualLastYear49 = new ExcoMoney[12];
        public double[] actualRatioLastYear49 = new double[12];
        #endregion
        #endregion


        #region Functions
        // constructor
        public ExcoAccount(int glNo1, int glNo2, string sTitle, int fiscalYear)
        {
            this.glNo1 = glNo1;
            this.glNo2 = glNo2;
            this.sTitle = sTitle;
            this.fiscalYear = fiscalYear;
            for (int i = 0; i < 12; i++)
            {
                // markham, michigan and texas
                actual[i] = new ExcoMoney();
                actualRatio[i] = 0.0;
                budget[i] = new ExcoMoney();
                budgetRatio[i] = 0.0;
                actualLastYear[i] = new ExcoMoney();
                actualRatioLastYear[i] = 0.0;
                // colombia
                actual04[i] = new ExcoMoney();
                actualRatio04[i] = 0.0;
                budget04[i] = new ExcoMoney();
                budgetRatio04[i] = 0.0;
                actualLastYear04[i] = new ExcoMoney();
                actualRatioLastYear04[i] = 0.0;
                actual41[i] = new ExcoMoney();
                actualRatio41[i] = 0.0;
                budget41[i] = new ExcoMoney();
                budgetRatio41[i] = 0.0;
                actualLastYear41[i] = new ExcoMoney();
                actualRatioLastYear41[i] = 0.0;
                actual48[i] = new ExcoMoney();
                actualRatio48[i] = 0.0;
                budget48[i] = new ExcoMoney();
                budgetRatio48[i] = 0.0;
                actualLastYear48[i] = new ExcoMoney();
                actualRatioLastYear48[i] = 0.0;
                actual49[i] = new ExcoMoney();
                actualRatio49[i] = 0.0;
                budget49[i] = new ExcoMoney();
                budgetRatio49[i] = 0.0;
                actualLastYear49[i] = new ExcoMoney();
                actualRatioLastYear49[i] = 0.0;
            }
        }
        #endregion
    }
}
