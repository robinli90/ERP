using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;
using IncomeStatementReport.Categories;

namespace IncomeStatementReport
{
    public class Plant
    {
        public int plantID = 0;
        // currency
        public string currency = string.Empty;

        // calendar
        public ExcoCalendar calendar = new ExcoCalendar();

        public List<ExcoMoney> actualThisYearList = new List<ExcoMoney>();
        public List<ExcoMoney> budgetThisYearList = new List<ExcoMoney>();
        public List<ExcoMoney> actualLastYearList = new List<ExcoMoney>();

        // account list
        public List<Account> accountList = new List<Account>();

        public Plant(int plantID, string currency)
        {
            this.plantID = plantID;
            this.currency = currency;
            for (int i = 0; i < 13; i++)
            {
                actualThisYearList.Add(new ExcoMoney());
                actualLastYearList.Add(new ExcoMoney());
                budgetThisYearList.Add(new ExcoMoney());
            }
        }

        public void GetAccountsData(int fiscalYear, int fiscalMonth)
        {
            try
            {
                this.calendar = new ExcoCalendar(fiscalYear, fiscalMonth, true, plantID);
                // skip empty account lists
                if (accountList.Count == 0)
                {
                    return;
                }
                if (4 == plantID || 48 == plantID)
                {
                    GetAccountsDataCalendarColombiaPlants();
                }
                else if (41 == plantID || 49 == plantID)
                {
                    GetAccountsDataFiscalColombiaPlants();
                }
                else
                {
                    GetAccountsDataFiscalPlants();
                }
            }
            catch (Exception e)
            {
                string msg = e.Message;
            }
        }

        private void GetAccountsDataFiscalPlants()
        {
            // this year
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select sum(coalesce(aj4tt01,0.0)) as actual01, sum(coalesce(aj4tt02,0.0)) as actual02, sum(coalesce(aj4tt03,0.0)) as actual03, sum(coalesce(aj4tt04,0.0)) as actual04, sum(coalesce(aj4tt05,0.0)) as actual05, sum(coalesce(aj4tt06,0.0)) as actual06, sum(coalesce(aj4tt07,0.0)) as actual07, sum(coalesce(aj4tt08,0.0)) as actual08, sum(coalesce(aj4tt09,0.0)) as actual09, sum(coalesce(aj4tt10,0.0)) as actual10, sum(coalesce(aj4tt11,0.0)) as actual11, sum(coalesce(aj4tt12,0.0)) as actual12, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and aj4gl#1=" + accountList[0].glNo1 + " and (";
            for (int i = 0; i < accountList.Count; i++)
            {
                query += "aj4gl#2=" + accountList[i].glNo2;
                if (i < accountList.Count - 1)
                {
                    query += " or ";
                }
            }
            query += ") and aj4ccyy=20";
            OdbcDataReader reader = solarsoft.RunQuery(query + calendar.GetFiscalYear());
            if (reader.Read() && !reader.IsDBNull(0))
            {
                for (int i = 1; i <= 12; i++)
                {
                    ExcoCalendar tempCalendar = new ExcoCalendar(calendar.GetFiscalYear(), i, true, plantID);
                    actualThisYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    budgetThisYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                }
            }
            reader.Close();
            // last year
            reader = solarsoft.RunQuery(query + calendar.GetFiscalYear() + "- 1");
            if (reader.Read() && !reader.IsDBNull(0))
            {
                for (int i = 1; i <= 12; i++)
                {
                    ExcoCalendar tempCalendar = new ExcoCalendar(calendar.GetFiscalYear() - 1, i, true, plantID);
                    actualLastYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                }
            }
            reader.Close();
        }

        private void GetAccountsDataFiscalColombiaPlants()
        {
            // this year
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            string query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09, sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
            for (int i = 0; i < accountList.Count; i++)
            {
                query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                if (i < accountList.Count - 1)
                {
                    query += " or (";
                }
            }
            query += ") and aj4ccyy=20";
            OdbcDataReader reader = solarsoft.RunQuery(query + calendar.GetFiscalYear());
            if (reader.Read() && !reader.IsDBNull(0))
            {
                for (int i = 1; i <= 12; i++)
                {
                    ExcoCalendar tempCalendar = new ExcoCalendar(calendar.GetFiscalYear(), i, true, plantID);
                    actualThisYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    budgetThisYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                }
            }
            reader.Close();
            // last year
            reader = solarsoft.RunQuery(query + calendar.GetFiscalYear() + "- 1");
            if (reader.Read() && !reader.IsDBNull(0))
            {
                for (int i = 1; i <= 12; i++)
                {
                    ExcoCalendar tempCalendar = new ExcoCalendar(calendar.GetFiscalYear() - 1, i, true, plantID);
                    actualLastYearList[i] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                }
            }
            reader.Close();
        }

        
        private void GetAccountsDataCalendarColombiaPlants()
        {
            // calendar period
            int cp = calendar.GetCalendarMonth();
            int cy = calendar.GetCalendarYear();
            //ExcoCalendar ttt = new ExcoCalendar(calendar.GetCalendarYear(), calendar.GetCalendarMonth(), true, 1);
            //int cp = ttt.GetCalendarMonth();
            //int cy = ttt.GetCalendarYear();
            bool test = false;
            // this year
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            //if (cp > 9)
            //{
                string query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    if (accountList[i].glNo2.Contains("206010")) test = true;
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                OdbcDataReader reader = solarsoft.RunQuery(query + (cy - 1));
                //string g = (query) + (cy - 1);
                //Console.Write(g);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        //if (test) 
                       //     Console.Write("!!");
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                        string gd = Convert.ToDouble(reader["actual" + i.ToString("D2")]).ToString();
                        string ggd = Convert.ToDouble(reader["actual" + i.ToString("D2")]).ToString();
                        //string pp = gd + ggd;
                        //Console.Write(pp);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                // last year
                query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 2));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 2, i, true, plantID);
                        actualLastYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualLastYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
           /* }
            else
            {
                string query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                OdbcDataReader reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy + 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy + 1, i, true, plantID);
                        actualThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                // last year
                query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualLastYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualLastYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
            }*/
        }

        /*OLD
        private void GetAccountsDataCalendarColombiaPlants()
        {
            // calendar period
            int cp = calendar.GetCalendarMonth();
            int cy = calendar.GetCalendarYear();
            //ExcoCalendar ttt = new ExcoCalendar(calendar.GetCalendarYear(), calendar.GetCalendarMonth(), true, 1);
            //int cp = ttt.GetCalendarMonth();
            //int cy = ttt.GetCalendarYear();

            // this year
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            if (cp <= 9)
            {
                string query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                OdbcDataReader reader = solarsoft.RunQuery(query + (cy - 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                // last year
                query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 2));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 2, i, true, plantID);
                        actualLastYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualLastYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
            }
            else
            {
                string query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12, sum(coalesce(aj4cb10,0.0)) as budget10, sum(coalesce(aj4cb11,0.0)) as budget11, sum(coalesce(aj4cb12,0.0)) as budget12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                OdbcDataReader reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09, sum(coalesce(aj4cb01,0.0)) as budget01, sum(coalesce(aj4cb02,0.0)) as budget02, sum(coalesce(aj4cb03,0.0)) as budget03, sum(coalesce(aj4cb04,0.0)) as budget04, sum(coalesce(aj4cb05,0.0)) as budget05, sum(coalesce(aj4cb06,0.0)) as budget06, sum(coalesce(aj4cb07,0.0)) as budget07, sum(coalesce(aj4cb08,0.0)) as budget08, sum(coalesce(aj4cb09,0.0)) as budget09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy + 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy + 1, i, true, plantID);
                        actualThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                        budgetThisYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["budget" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                // last year
                query = "select sum(coalesce(aj4tt10+aj4ob10,0.0)) as actual10, sum(coalesce(aj4tt11+aj4ob11,0.0)) as actual11, sum(coalesce(aj4tt12+aj4ob12,0.0)) as actual12 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + (cy - 1));
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 10; i <= 12; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy - 1, i, true, plantID);
                        actualLastYearList[i - 9] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
                query = "select sum(coalesce(aj4tt01+aj4ob01,0.0)) as actual01, sum(coalesce(aj4tt02+aj4ob02,0.0)) as actual02, sum(coalesce(aj4tt03+aj4ob03,0.0)) as actual03, sum(coalesce(aj4tt04+aj4ob04,0.0)) as actual04, sum(coalesce(aj4tt05+aj4ob05,0.0)) as actual05, sum(coalesce(aj4tt06+aj4ob06,0.0)) as actual06, sum(coalesce(aj4tt07+aj4ob07,0.0)) as actual07, sum(coalesce(aj4tt08+aj4ob08,0.0)) as actual08, sum(coalesce(aj4tt09+aj4ob09,0.0)) as actual09 from cmsdat.glmt where aj4comp=" + plantID + " and ((";
                for (int i = 0; i < accountList.Count; i++)
                {
                    query += "aj4gl#1=" + accountList[i].glNo1 + " and aj4gl#2=" + accountList[i].glNo2 + ")";
                    if (i < accountList.Count - 1)
                    {
                        query += " or (";
                    }
                }
                query += ") and aj4ccyy=20";
                reader = solarsoft.RunQuery(query + cy);
                if (reader.Read() && !reader.IsDBNull(0))
                {
                    for (int i = 1; i <= 9; i++)
                    {
                        ExcoCalendar tempCalendar = new ExcoCalendar(cy, i, true, plantID);
                        actualLastYearList[i + 3] = new ExcoMoney(tempCalendar.GetNextCalendarMonth(), Convert.ToDouble(reader["actual" + i.ToString("D2")]) * -1.0, currency);
                    }
                }
                reader.Close();
            }
        }*/
    }
}
