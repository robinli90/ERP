using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace SalesReport
{
    class Plant
    {
        public double[] budget = new double[12];
        public double[] actual = new double[12];
        public double budgetTotal = 0.0;
        public double budgetTotalCAD = 0.0;
        public double actualTotal = 0.0;
        public double actualTotalCAD = 0.0;

        public int id = 0;
        public string curr = "";
        public int year = DateTime.Now.Year - 2000;
        // fiscal representation of calendar year
        // from January to December
        public int[] fiscalPeriod = new int[12];
        public int[] fiscalYear = new int[12];


        public Plant()
        {
            for (int i = 0; i < 12; i++)
            {
                budget[i] = 0.0;
                actual[i] = 0.0;
                fiscalPeriod[i] = 0;
                fiscalYear[i] = 0;
            }
        }

        public void GetData(int plant, string id, string curr)
        {
            this.curr = curr;
            this.id = plant;
            GetFiscal();
            // get period details
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            for (int i = 0; i < 12; i++)
            {
                double value = 0.0;
                // invoice
                string query = "select coalesce(sum(dipric*(max(diqtso,diqtsp))), 0.0) from cmsdat.oih, cmsdat.oid where dhbcs#='" + id + "' and dhincr='I' and dhpost='Y' and dhinv#=diinv# and diglcd='SAL' and dhplnt='" + plant.ToString("D3") + "' and dharpr=" + fiscalPeriod[i].ToString() + " and dharyr=" + fiscalYear[i].ToString();
                OdbcDataReader reader = database.RunQuery(query);
                if (reader.Read())
                {
                    value = Convert.ToDouble(reader[0]);
                }
                reader.Close();
                // credit
                query = "select coalesce(sum(dipric*(max(diqtso,diqtsp))), 0.0) from cmsdat.oih, cmsdat.oid where dhbcs#='" + id + "' and dhincr='C' and dhpost='Y' and dhinv#=diinv# and diglcd='SAL' and dhplnt='" + plant.ToString("D3") + "' and dharpr=" + fiscalPeriod[i].ToString() + " and dharyr=" + fiscalYear[i].ToString();
                reader = database.RunQuery(query);
                if (reader.Read())
                {
                    value -= Convert.ToDouble(reader[0]);
                }
                reader.Close();
                // discount and fast track
                query = "select coalesce(sum(fldext), 0.0) from cmsdat.oih, cmsdat.ois where dhbcs#='" + id + "' and dhpost='Y' and dhinv#=flinv# and (fldisc like 'D%' or fldisc like 'M%' or fldisc like 'F%') and dhplnt='" + plant.ToString("D3") + "' and dharpr=" + fiscalPeriod[i].ToString() + " and dharyr=" + fiscalYear[i].ToString();
                reader = database.RunQuery(query);
                if (reader.Read())
                {
                    value += Convert.ToDouble(reader[0]);
                }
                reader.Close();
                // net sale
                ExcoCalendar calendar = new ExcoCalendar(year, i + 1, true, plant);
                actual[i] = value;
                actualTotal += actual[i];
                actualTotalCAD += actual[i] * ExcoExRate.GetToCADRate(calendar, curr);
                ExcoBudget excoBudget = ExcoBudget.Instance;
                budget[i] = excoBudget.GetMonthlyBudget(id, plant);
                budgetTotal += budget[i];
                budgetTotalCAD += budget[i] * ExcoExRate.GetToCADRate(calendar, curr);
            }
        }

        private void GetFiscal()
        {
            if (4 == id)
            {
                for (int i = 0; i < 12; i++)
                {
                    fiscalPeriod[i] = i + 1;
                    fiscalYear[i] = 13;
                }
            }
            else
            {
                for (int i = 4; i < 13; i++)
                {
                    fiscalPeriod[i - 4] = i;
                    fiscalYear[i - 4] = year;
                }
                for (int i = 1; i < 4; i++)
                {
                    fiscalPeriod[i + 8] = i;
                    fiscalYear[i + 8] = year + 1;
                }
            }
        }

        public static Plant operator +(Plant a1, Plant a2)
        {
            Plant plant = new Plant();
            if (0 != a1.curr.CompareTo(a2.curr))
            {
                throw new Exception("Currencies are different");
            }
            plant.curr = a1.curr;
            for (int i = 0; i < 12; i++)
            {
                plant.budget[i] = a1.budget[i] + a2.budget[i];
                plant.actual[i] = a1.actual[i] + a2.actual[i];
            }
            plant.budgetTotal = a1.budgetTotal + a2.budgetTotal;
            plant.budgetTotalCAD = a1.budgetTotalCAD + a2.budgetTotalCAD;
            plant.actualTotal = a1.actualTotal + a2.actualTotal;
            plant.actualTotalCAD = a1.actualTotalCAD + a2.actualTotalCAD;
            return plant;
        }
    }
}