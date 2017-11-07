using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace IncomeStatementReportFrank
{
    public class Group
    {
        public ExcoMoney tpActual = new ExcoMoney();
        public double tpActualRatio = 0.0;
        public ExcoMoney tpBudget = new ExcoMoney();
        public double tpBudgetRatio = 0.0;
        public ExcoMoney lpActual = new ExcoMoney();
        public double lpActualRatio = 0.0;
        public ExcoMoney ytdActual = new ExcoMoney();
        public double ytdActualRatio = 0.0;
        public ExcoMoney ytdBudget = new ExcoMoney();
        public double ytdBudgetRatio = 0.0;
        public string name = "";
        public string id = "";
        public string currency = "CA";

        public Group(string groupName, string groupID)
        {
            name = groupName;
            id = groupID;
        }

        public Group()
        {

        }

        public void GetInfo(ExcoCalendar calendar, string groupID)
        {
            // fiscal period
            string fp = calendar.GetFiscalMonth().ToString("D2");
            // fiscal year
            string fy = calendar.GetFiscalYear().ToString("D2");
            // last period
            string lp = (calendar.GetFiscalMonth()-1).ToString("D2");

            // get data
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            if (lp != "00")
            {
                string query = "select coalesce(sum(aj4tt" + fp + "), 0.0) as tpActual, coalesce(sum(aj4cb" + fp + "), 0.0) as tpBudget, coalesce(sum(aj4tt" + lp + "), 0.0) as lpActual, coalesce(sum(";
                int iPeriod = Convert.ToInt32(fp);
                while (iPeriod > 0)
                {
                    query += "aj4tt" + iPeriod.ToString("D2");
                    iPeriod--;
                    if (iPeriod > 0)
                    {
                        query += "+";
                    }
                    else
                    {
                        query += "), 0.0) as ytdActual, coalesce(sum(";
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
                        query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on aj4comp=1 and aj4gl#1=100 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where azgrop like '" + id + "%'";
                    }
                }
                OdbcDataReader reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    tpActual = new ExcoMoney(calendar, Convert.ToDouble(reader["tpActual"]), currency);
                    lpActual = new ExcoMoney(calendar, Convert.ToDouble(reader["lpActual"]), currency);
                    tpBudget = new ExcoMoney(calendar, Convert.ToDouble(reader["tpBudget"]), currency);
                    ytdActual = new ExcoMoney(calendar, Convert.ToDouble(reader["ytdActual"]), currency);
                    ytdBudget = new ExcoMoney(calendar, Convert.ToDouble(reader["ytdBudget"]), currency);
                }
                reader.Close();
            }
            else 
            {
                string query = "select coalesce(sum(aj4tt" + fp + "), 0.0) as tpActual, coalesce(sum(aj4cb" + fp + "), 0.0) as tpBudget, coalesce(sum(";
                int iPeriod = Convert.ToInt32(fp);
                while (iPeriod > 0)
                {
                    query += "aj4tt" + iPeriod.ToString("D2");
                    iPeriod--;
                    if (iPeriod > 0)
                    {
                        query += "+";
                    }
                    else
                    {
                        query += "), 0.0) as ytdActual, coalesce(sum(";
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
                        query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on aj4comp=1 and aj4gl#1=100 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where azgrop like '" + id + "%'";
                    }
                }
                OdbcDataReader reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    tpActual = new ExcoMoney(calendar, Convert.ToDouble(reader["tpActual"]), currency);
                    //lpActual = new ExcoMoney(calendar, Convert.ToDouble(reader["lpActual"]), currency);
                    tpBudget = new ExcoMoney(calendar, Convert.ToDouble(reader["tpBudget"]), currency);
                    ytdActual = new ExcoMoney(calendar, Convert.ToDouble(reader["ytdActual"]), currency);
                    ytdBudget = new ExcoMoney(calendar, Convert.ToDouble(reader["ytdBudget"]), currency);
                }
                reader.Close();

                //get last fiscal year period data                 
                lp = "12";
                fy = (calendar.GetFiscalYear()-1).ToString("D2");
                query = "select coalesce(sum(aj4tt" + lp + "), 0.0) as lpActual from cmsdat.glmt left join cmsdat.mast on aj4comp=1 and aj4gl#1=100 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where azgrop like '" + id + "%'";

                reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    lpActual = new ExcoMoney(calendar, Convert.ToDouble(reader["lpActual"]), currency);         
                }
                reader.Close();   
            }
        }
    }
}