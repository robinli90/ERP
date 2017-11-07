using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace IncomeStatementReportFrank
{
    public class Plant
    {
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

        // calendar
        public ExcoCalendar calendar = new ExcoCalendar();

        public Plant(ExcoCalendar calendar, int plantID)
        {
            this.calendar = calendar;
            cs = new Category(calendar);
            ds = new Category(calendar);
            fo = new Category(calendar);
            ga = new Category(calendar);
            oe = new Category(calendar);
            ss = new Category(calendar);
            dl = new Category(calendar);
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
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where  bq1lvl like '%%' and bq1grp like '4%' and bq1comp='01'";
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
        }

        public void BuildCostOfSales()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '501%' and bq1comp='01'";
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
        }

        public void BuildDeliverySelling()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6DS%' and bq1comp='01'";
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
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '503%' and bq1comp='01'";
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
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6GA%' and bq1comp='01'";
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
        }

        public void BuildOtherExpense()
        {
            List<string> groupNameList = new List<string>();
            List<string> groupIDList = new List<string>();
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '6OT%' and bq1comp='01'";
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
            string query = "select bq1grp, bq1titl from cmsdat.fgrp where bq1lvl='B' and bq1grp like '502%' and bq1comp='01'";
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