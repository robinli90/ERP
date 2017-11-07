using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace PL_Michigan
{
    public class Group
    {
        public ExcoMoney tpActual = new ExcoMoney();
        public double tpActualRatio = 0.0;
        public ExcoMoney tpBudget = new ExcoMoney();
        public double tpBudgetRatio = 0.0;
        public ExcoMoney ytdActual = new ExcoMoney();
        public double ytdActualRatio = 0.0;
        public ExcoMoney ytdBudget = new ExcoMoney();
        public double ytdBudgetRatio = 0.0;
        public string name = "";
        public string groupID = "";
        public int plant = 3;
        public string currency = "US";

        public Group()
        {
        }

        public bool IsEmptyAccount()
        {
            if (tpActual.IsZero() && tpBudget.IsZero() && ytdActual.IsZero() && ytdBudget.IsZero())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void GetInfo(ExcoCalendar calendar)
        {
            // fiscal period
            string fp = calendar.GetFiscalMonth().ToString("D2");
            // fiscal year
            string fy = calendar.GetFiscalYear().ToString("D2");
            if (name.Length > 0)
            {
                ExcoODBC solarsoft = ExcoODBC.Instance;
                solarsoft.Open(Database.CMSDAT);
                string query = "select coalesce(sum(aj4tt" + fp + "), 0.0), coalesce(sum(aj4cb" + fp + "), 0.0), coalesce(sum(";
                int iPeriod = Convert.ToInt32(fp);
                while (iPeriod > 0)
                {
                    query += "aj4tt" + iPeriod.ToString("D2") + "+aj4ob" + iPeriod.ToString("D2"); ;
                    iPeriod--;
                    if (iPeriod > 0)
                    {
                        query += "+";
                    }
                    else
                    {
                        query += "), 0.0), coalesce(sum(";
                    }
                }
                iPeriod = Convert.ToInt32(fp);
                while (iPeriod > 0)
                {
                    query += "aj4cb" + iPeriod.ToString("D2");
                    iPeriod--;
                    if (iPeriod > 0)
                    {
                        query += "+";
                    }
                    else
                    {
                        query += "), 0.0) from cmsdat.glmt left join cmsdat.mast on aj4comp=" + plant + " and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where azgrop like '" + groupID + "%'";
                    }
                }
                OdbcDataReader reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    tpActual = new ExcoMoney(calendar, Convert.ToDouble(reader[0]), currency);
                    tpBudget = new ExcoMoney(calendar, Convert.ToDouble(reader[1]), currency);
                    ytdActual = new ExcoMoney(calendar, Convert.ToDouble(reader[2]), currency);
                    ytdBudget = new ExcoMoney(calendar, Convert.ToDouble(reader[3]), currency);
                }
                reader.Close();
            }
        }
    }
}
