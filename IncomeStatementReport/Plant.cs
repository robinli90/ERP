using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace IncomeStatementReport
{
    public class Plant
    {
        public int plantID = 0;
        // cost of sales
        public Category cs;
        // delivery selling
        public Category ds;
        // factory overhead
        public Category fo;
        // general admin
        public Category ga;
        // other expense
        public Category oe;
        // sales
        public Category ss;
        // direct labour
        public Category dl;
        // currency
        public string currency = string.Empty;

        // calendar
        public ExcoCalendar calendar = new ExcoCalendar();

        public Plant(ExcoCalendar calendar, int plantID, bool needCAD)
        {
            this.calendar = calendar;
            this.plantID = plantID;
            switch (plantID)
            {
                case 1:
                    currency = "CA";
                    break;
                case 3:
                case 5:
                    currency = "US";
                    break;
                case 4:
                    currency = "CP";
                    break;
            }
            cs = new Category(calendar, plantID, needCAD);
            ds = new Category(calendar, plantID, needCAD);
            fo = new Category(calendar, plantID, needCAD);
            ga = new Category(calendar, plantID, needCAD);
            oe = new Category(calendar, plantID, needCAD);
            ss = new Category(calendar, plantID, needCAD);
            dl = new Category(calendar, plantID, needCAD);
            // build category
            BuildCostOfSales();
            BuildDeliverySelling();
            BuildDirectLabour();
            BuildFactoryOverhead();
            BuildGeneralAdmin();
            BuildOtherExpense();
            BuildSales();
            // get ratio
            ss.GetRatio(ss);
            cs.GetRatio(ss);
            ds.GetRatio(ss);
            fo.GetRatio(ss);
            ga.GetRatio(ss);
            oe.GetRatio(ss);
            dl.GetRatio(ss);
        }

        public void BuildSales()
        {
            // add non-grouped accounts
            ss.AddAccount("NON GROUPED", "4");
            // add normal accounts
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='A' and bq1grp like '4%' and bq1comp='" + plantID.ToString("D2") + "'";
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                ss.AddAccount(groupNameList[i], groupIDList[i]);
            }

            //GetNonGroupedAccounts(4, ss);
        }

        public void GetNonGroupedAccounts(int groupID, Category category)
        {
            Group group = new Group();
            group.name = "NON GROUPED";
            group.plantID = plantID;
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            int fp = calendar.GetFiscalMonth();
            int fy = calendar.GetFiscalYear();
            int cp = calendar.GetCalendarMonth();
            int cy = calendar.GetCalendarYear();
            if (4 != plantID)
            {
                // this year
                string query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "), 0.0), coalesce(sum(aj4cb" + fp.ToString("D2") + "), 0.0), coalesce(sum(";
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
                        query += "), 0.0) from cmsdat.glmt left join cmsdat.mast on aj4comp=" + plantID + " and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy.ToString("D2") + " where azgrop='" + groupID + "'";
                    }
                }
                OdbcDataReader reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    group.tpActual = Convert.ToDouble(reader[0]);
                    group.tpBudget = Convert.ToDouble(reader[1]);
                    group.ytdActual = Convert.ToDouble(reader[2]);
                    group.ytdBudget = Convert.ToDouble(reader[3]);
                }
                reader.Close();
                // last year
                fy -= 1;
                query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "), 0.0) from cmsdat.glmt left join cmsdat.mast on aj4comp=" + plantID + " and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy.ToString("D2") + " where azgrop='" + groupID + "'";
                reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    group.tpLyActual = Convert.ToDouble(reader[0]);
                }
                reader.Close();
            }
            else
            {
                string query;
                // plant 4 and 48
                if (calendar.GetCalendarMonth() > 1)
                {
                    query = "select coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "-aj4tt" + (cp - 1).ToString("D2") + "-aj4ob" + (cp - 1).ToString("D2") + "), 0.0) as tpActual, coalesce(sum(aj4cb" + cp.ToString("D2") + "),0.0) as tpBudget, coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "), 0.0) as ytdActual, coalesce(sum(";
                    int iPeriod = Convert.ToInt32(cp);
                    if (iPeriod > 9)
                    {
                        while (iPeriod > 9)
                        {
                            query += "aj4cb" + iPeriod.ToString("D2");
                            iPeriod--;
                            if (iPeriod > 9)
                            {
                                query += "+";
                            }
                        }
                    }
                    query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on (aj4comp=4 or aj4comp=48) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + cy + " where (aj4comp=4 or aj4comp=48) and azgrop='" + groupID + "'";
                    OdbcDataReader reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpActual = Convert.ToDouble(reader[0]);
                        group.tpBudget = Convert.ToDouble(reader[1]);
                        group.ytdActual = Convert.ToDouble(reader[2]);
                        group.ytdBudget = Convert.ToDouble(reader[3]);
                    }
                    reader.Close();
                    // last year
                    query = "select coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "-aj4tt" + (cp - 1).ToString("D2") + "-aj4ob" + (cp - 1).ToString("D2") + "), 0.0) as tpActual from cmsdat.glmt left join cmsdat.mast on (aj4comp=4 or aj4comp=48) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + (cy - 1) + " where (aj4comp=4 or aj4comp=48) and azgrop='" + groupID + "'";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpLyActual = Convert.ToDouble(reader[0]);
                    }
                    reader.Close();
                }
                else
                {
                    query = "select coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "), 0.0) as tpActual, coalesce(sum(aj4cb" + cp.ToString("D2") + "),0.0) as tpBudget, coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "), 0.0) as ytdActual, coalesce(sum(";
                    int iPeriod = Convert.ToInt32(cp);
                    while (iPeriod > 9)
                    {
                        query += "aj4cb" + iPeriod.ToString("D2");
                        iPeriod--;
                        if (iPeriod > 9)
                        {
                            query += "+";
                        }
                    }
                    query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on (aj4comp=4 or aj4comp=48) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + cy + " where (aj4comp=4 or aj4comp=48) and azgrop='" + groupID + "'";
                    OdbcDataReader reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpActual = Convert.ToDouble(reader[0]);
                        group.tpBudget = Convert.ToDouble(reader[1]);
                        group.ytdActual = Convert.ToDouble(reader[2]);
                        group.ytdBudget = Convert.ToDouble(reader[3]);
                    }
                    reader.Close();
                    // last year
                    query = "select coalesce(sum(aj4tt" + cp.ToString("D2") + "+aj4ob" + cp.ToString("D2") + "), 0.0) as tpActual from cmsdat.glmt left join cmsdat.mast on (aj4comp=4 or aj4comp=48) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + (cy - 1) + " where (aj4comp=4 or aj4comp=48) and azgrop='" + groupID + "'";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpLyActual = Convert.ToDouble(reader[0]);
                    }
                    reader.Close();
                }
                // plant 41 and 49
                // calendar period
                ExcoCalendar calendarTemp = new ExcoCalendar(calendar.GetCalendarYear(), calendar.GetCalendarMonth(), false, 1);
                fp = calendarTemp.GetFiscalMonth();
                // calendar year
                fy = calendarTemp.GetFiscalYear();
                if (calendarTemp.GetFiscalMonth() > 1)
                {
                    query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "-aj4tt" + (fp - 1).ToString("D2") + "-aj4ob" + (fp - 1).ToString("D2") + "), 0.0) as tpActual, coalesce(sum(aj4cb" + fp.ToString("D2") + "), 0.0) as tpBudget, coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "),0.0) as ytdActual, coalesce(sum(";
                    int iPeriod = Convert.ToInt32(fp);
                    while (iPeriod > 0)
                    {
                        query += "aj4cb" + iPeriod.ToString("D2");
                        iPeriod--;
                        if (iPeriod > 0)
                        {
                            query += "+";
                        }
                    }
                    query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on (aj4comp=41 or aj4comp=49) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where (aj4comp=41 or aj4comp=49) and azgrop='" + groupID + "'";
                    OdbcDataReader reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpActual += Convert.ToDouble(reader[0]);
                        group.tpBudget += Convert.ToDouble(reader[1]);
                        group.ytdActual += Convert.ToDouble(reader[2]);
                        group.ytdBudget += Convert.ToDouble(reader[3]);
                    }
                    reader.Close();
                    // last year
                    query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "-aj4tt" + (fp - 1).ToString("D2") + "-aj4ob" + (fp - 1).ToString("D2") + "), 0.0) as tpActual from cmsdat.glmt left join cmsdat.mast on (aj4comp=41 or aj4comp=49) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + (fy - 1) + " where (aj4comp=41 or aj4comp=49) and azgrop='" + groupID + "'";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpLyActual += Convert.ToDouble(reader[0]);
                    }
                    reader.Close();
                }
                else
                {
                    query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "), 0.0) as tpActual, coalesce(sum(aj4cb" + fp + "), 0.0) as tpBudget, coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "),0.0) as ytdActual, coalesce(sum(";
                    int iPeriod = Convert.ToInt32(fp);
                    while (iPeriod > 0)
                    {
                        query += "aj4cb" + iPeriod.ToString("D2");
                        iPeriod--;
                        if (iPeriod > 0)
                        {
                            query += "+";
                        }
                    }
                    query += "), 0.0) as ytdBudget from cmsdat.glmt left join cmsdat.mast on (aj4comp=41 or aj4comp=49) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where (aj4comp=41 or aj4comp=49) and azgrop='" + groupID + "'";
                    OdbcDataReader reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpActual += Convert.ToDouble(reader[0]);
                        group.tpBudget += Convert.ToDouble(reader[1]);
                        group.ytdActual += Convert.ToDouble(reader[2]);
                        group.ytdBudget += Convert.ToDouble(reader[3]);
                    }
                    reader.Close();
                    // last year
                    query = "select coalesce(sum(aj4tt" + fp.ToString("D2") + "+aj4ob" + fp.ToString("D2") + "), 0.0) as tpActual from cmsdat.glmt left join cmsdat.mast on (aj4comp=41 or aj4comp=49) and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#2=azgl#2 and aj4ccyy=20" + fy + " where (aj4comp=41 or aj4comp=49) and azgrop='" + groupID + "'";
                    reader = solarsoft.RunQuery(query);
                    if (reader.Read())
                    {
                        group.tpLyActual += Convert.ToDouble(reader[0]);
                    }
                    reader.Close();
                }
            }
            category.groupList.Insert(0, group);
        }

        public void BuildCostOfSales()
        {
            // add non-grouped accounts
            cs.AddAccount("NON GROUPED", "5");
            // add normal accounts
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '501%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '510%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                cs.AddAccount(groupNameList[i], groupIDList[i]);
            }
            // get non-grouped accounts
            //GetNonGroupedAccounts(5, cs);
        }

        public void BuildDeliverySelling()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6DS%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '610%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                ds.AddAccount(groupNameList[i], groupIDList[i]);
            }
        }

        public void BuildFactoryOverhead()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '503%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '530%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                fo.AddAccount(groupNameList[i], groupIDList[i]);
            }
        }

        public void BuildGeneralAdmin()
        {
            // add non-grouped accounts
            ga.AddAccount("NON GROUPED", "6");
            // add normal accounts
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6GA%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '620%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                ga.AddAccount(groupNameList[i], groupIDList[i]);
            }
            // get non-grouped accounts
            //GetNonGroupedAccounts(6, ga);
        }

        public void BuildOtherExpense()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6OT%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '630%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                oe.AddAccount(groupNameList[i], groupIDList[i]);
            }
        }

        public void BuildDirectLabour()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = string.Empty;
            switch (plantID)
            {
                case 1:
                case 3:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '502%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
                case 5:
                case 4:
                    query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '520%' and bq1comp='" + plantID.ToString("D2") + "'";
                    break;
            }
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                groupNameList.Add(reader["bq1titl"].ToString().Trim());
                groupIDList.Add(reader["bq1grp"].ToString().Trim());
            }
            reader.Close();
            for (int i = 0; i < groupIDList.Count; i++)
            {
                dl.AddAccount(groupNameList[i], groupIDList[i]);
            }
        }
    }
}
