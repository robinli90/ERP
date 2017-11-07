using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace ExcoUtility.Plant
{
    public class PlantColombia : ExcoPlant
    {
        #region Functions Definition
        // constructor
        public PlantColombia()
        {
            // set default currency
            sCurrency = "CP";
            // set plant id
            iPlantID = 4;
        }

        // get account data for a certain period
        public override void GetAccounts(int iFiscalYear)
        {
            // make sure stores 2-digit year number
            if (iFiscalYear > 2000)
            {
                iFiscalYear -= 2000;
            }
            this.iFiscalYear = iFiscalYear;
            // account map
            Dictionary<int, ExcoAccount> accountMap = new Dictionary<int, ExcoAccount>();

            #region plant 41
            // build query string for the given year
            string query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt01+aj4ob01, aj4tt02+aj4ob02-(aj4tt01+aj4ob01), aj4tt03+aj4ob03-(aj4tt02+aj4ob02), aj4tt04+aj4ob04-(aj4tt03+aj4ob03), aj4tt05+aj4ob05-(aj4tt04+aj4ob04), aj4tt06+aj4ob06-(aj4tt05+aj4ob05), aj4tt07+aj4ob07-(aj4tt06+aj4ob06), aj4tt08+aj4ob08-(aj4tt07+aj4ob07), aj4tt09+aj4ob09-(aj4tt08+aj4ob08), aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4tt11+aj4ob11-(aj4tt10+aj4ob10), aj4tt12+aj4ob12-(aj4tt11+aj4ob11), aj4cb01, aj4cb02, aj4cb03, aj4cb04, aj4cb05, aj4cb06, aj4cb07, aj4cb08, aj4cb09, aj4cb10, aj4cb11, aj4cb12 from cmsdat.glmt left join cmsdat.mast on aj4comp=41 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + iFiscalYear;
            // run query
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader["aj4gl#1"]) % 100;
                int iGLNo2 = Convert.ToInt32(reader["aj4gl#2"]);
                string sTitle = reader["aztitl"].ToString();
                int iYear = Convert.ToInt32(reader["aj4ccyy"]) - 2000;
                // determine if a mapped account
                ExcoAccount account;
                bool bIsNewAccount = false;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 12; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual41[i] = new ExcoMoney(calendar, Convert.ToDouble(reader["aj4tt" + (i + 1).ToString("D2")]), sCurrency);
                    account.budget41[i] = new ExcoMoney(calendar, Convert.ToDouble(reader["aj4cb" + (i + 1).ToString("D2")]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            #endregion

            #region plant 49
            // build query string for the given year
            query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt01+aj4ob01, aj4tt02+aj4ob02-(aj4tt01+aj4ob01), aj4tt03+aj4ob03-(aj4tt02+aj4ob02), aj4tt04+aj4ob04-(aj4tt03+aj4ob03), aj4tt05+aj4ob05-(aj4tt04+aj4ob04), aj4tt06+aj4ob06-(aj4tt05+aj4ob05), aj4tt07+aj4ob07-(aj4tt06+aj4ob06), aj4tt08+aj4ob08-(aj4tt07+aj4ob07), aj4tt09+aj4ob09-(aj4tt08+aj4ob08), aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4tt11+aj4ob11-(aj4tt10+aj4ob10), aj4tt12+aj4ob12-(aj4tt11+aj4ob11), aj4cb01, aj4cb02, aj4cb03, aj4cb04, aj4cb05, aj4cb06, aj4cb07, aj4cb08, aj4cb09, aj4cb10, aj4cb11, aj4cb12 from cmsdat.glmt left join cmsdat.mast on aj4comp=49 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + iFiscalYear;
            // run query
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader["aj4gl#1"]) % 100;
                int iGLNo2 = Convert.ToInt32(reader["aj4gl#2"]);
                string sTitle = reader["aztitl"].ToString();
                int iYear = Convert.ToInt32(reader["aj4ccyy"]) - 2000;
                // determine if a mapped account
                ExcoAccount account;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                bool bIsNewAccount = false;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 12; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual49[i] = new ExcoMoney(calendar, Convert.ToDouble(reader["aj4tt" + (i + 1).ToString("D2")]), sCurrency);
                    account.budget49[i] = new ExcoMoney(calendar, Convert.ToDouble(reader["aj4cb" + (i + 1).ToString("D2")]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            #endregion

            #region plant 04
            // build query string for the given year
            query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt01+aj4ob01, aj4tt02+aj4ob02-(aj4tt01+aj4ob01), aj4tt03+aj4ob03-(aj4tt02+aj4ob02), aj4tt04+aj4ob04-(aj4tt03+aj4ob03), aj4tt05+aj4ob05-(aj4tt04+aj4ob04), aj4tt06+aj4ob06-(aj4tt05+aj4ob05), aj4tt07+aj4ob07-(aj4tt06+aj4ob06), aj4tt08+aj4ob08-(aj4tt07+aj4ob07), aj4tt09+aj4ob09-(aj4tt08+aj4ob08), aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4cb01, aj4cb02, aj4cb03, aj4cb04, aj4cb05, aj4cb06, aj4cb07, aj4cb08, aj4cb09, aj4cb10 from cmsdat.glmt left join cmsdat.mast on aj4comp=4 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + iFiscalYear;
            // run query
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader[1]);
                int iGLNo2 = Convert.ToInt32(reader[2]);
                string sTitle = reader[3].ToString();
                int iYear = Convert.ToInt32(reader[0]) - 2000;
                // determine if this is a mapped account
                ExcoAccount account;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                bool bIsNewAccount = false;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 9; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual04[i + 3] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 4]), sCurrency);
                    account.budget04[i + 3] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 14]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            // build query string for the previous year
            query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4tt11+aj4ob11-(aj4tt10+aj4ob10), aj4tt12+aj4ob12-(aj4tt11+aj4ob11), aj4cb10, aj4cb11, aj4cb12 from cmsdat.glmt left join cmsdat.mast on aj4comp=4 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + (iFiscalYear - 1);
            // run query
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader[1]);
                int iGLNo2 = Convert.ToInt32(reader[2]);
                string sTitle = reader[3].ToString();
                int iYear = Convert.ToInt32(reader[0]) - 2000;
                // determine if this is a mapped account
                ExcoAccount account;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                bool bIsNewAccount = false;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 3; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual04[i] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 4]), sCurrency);
                    account.budget04[i] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 7]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            #endregion

            #region plant 48
            // build query string for the given year
            query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt01+aj4ob01, aj4tt02+aj4ob02-(aj4tt01+aj4ob01), aj4tt03+aj4ob03-(aj4tt02+aj4ob02), aj4tt04+aj4ob04-(aj4tt03+aj4ob03), aj4tt05+aj4ob05-(aj4tt04+aj4ob04), aj4tt06+aj4ob06-(aj4tt05+aj4ob05), aj4tt07+aj4ob07-(aj4tt06+aj4ob06), aj4tt08+aj4ob08-(aj4tt07+aj4ob07), aj4tt09+aj4ob09-(aj4tt08+aj4ob08), aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4cb01, aj4cb02, aj4cb03, aj4cb04, aj4cb05, aj4cb06, aj4cb07, aj4cb08, aj4cb09, aj4cb10 from cmsdat.glmt left join cmsdat.mast on aj4comp=48 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + iFiscalYear;
            // run query
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader[1]);
                int iGLNo2 = Convert.ToInt32(reader[2]);
                string sTitle = reader[3].ToString();
                int iYear = Convert.ToInt32(reader[0]) - 2000;
                // determine if this is a mapped account
                ExcoAccount account;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                bool bIsNewAccount = false;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 9; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual48[i + 3] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 4]), sCurrency);
                    account.budget48[i + 3] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 14]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            // build query string for the previous year
            query = "select aj4ccyy, aj4gl#1, aj4gl#2, aztitl, aj4tt10+aj4ob10-(aj4tt09+aj4ob09), aj4tt11+aj4ob11-(aj4tt10+aj4ob10), aj4tt12+aj4ob12-(aj4tt11+aj4ob11), aj4cb10, aj4cb11, aj4cb12 from cmsdat.glmt left join cmsdat.mast on aj4comp=48 and azcomp=aj4comp and azgl#1=aj4gl#1 and aj4gl#1>400 and aj4gl#2=azgl#2 and aj4ccyy=20" + (iFiscalYear - 1);
            // run query
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                int iGLNo1 = Convert.ToInt32(reader[1]);
                int iGLNo2 = Convert.ToInt32(reader[2]);
                string sTitle = reader[3].ToString();
                int iYear = Convert.ToInt32(reader[0]) - 2000;
                // determine if this is a mapped account
                ExcoAccount account;
                int iKey = iGLNo1 * 1000000 + iGLNo2;
                bool bIsNewAccount = false;
                if (99999999 == iKey)
                {
                    continue;
                }
                if (accountMap.ContainsKey(iKey))
                {
                    account = accountMap[iKey];
                }
                else
                {
                    account = new ExcoAccount(iGLNo1, iGLNo2, sTitle, iFiscalYear);
                    bIsNewAccount = true;
                }
                // get data
                for (int i = 0; i < 3; i++)
                {
                    ExcoCalendar calendar = new ExcoCalendar(iYear, i + 1, true, iPlantID);
                    account.actual48[i] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 4]), sCurrency);
                    account.budget48[i] = new ExcoMoney(calendar, Convert.ToDouble(reader[i + 7]), sCurrency);
                }
                // add to map if this is a new account
                if (bIsNewAccount)
                {
                    accountMap.Add(iKey, account);
                }
            }
            reader.Close();
            #endregion
        }

        // get customer data for a certain period
        public override void GetCustomers(int iFiscalYear)
        {
            this.iFiscalYear = iFiscalYear;
        }
        #endregion
    }
}