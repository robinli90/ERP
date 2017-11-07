using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace AR_Report
{
    class Customer
    {
        public string csCustID = "";
        public string csCustName = "";
        public string csCustTerr = "";
        public string csPlant = "";
        public string csCurrency = "";
        public double dTotal = 0.0;
        public double dCurrent = 0.0;
        public double dOver30 = 0.0;
        public double dOver60 = 0.0;
        public double dOver90 = 0.0;
        public double dOver120 = 0.0;

        public void GetDetails(DateTime now)
        {
            // get current
            string query = "select coalesce(sum(asduam), 0.0) from cmsdat.arop where ascomp=" + csPlant + " and ascust='" + csCustID + "' and (asidat>='" + now.Subtract(TimeSpan.FromDays(30)).ToString("yyyy-MM-dd") + "')";
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            OdbcDataReader reader = solarsoft.RunQuery(query);
            if (reader.Read())
            {
                dCurrent = Convert.ToDouble(reader[0]);
            }
            reader.Close();
            // get over 30
            query = "select coalesce(sum(asduam), 0.0) from cmsdat.arop where ascomp=" + csPlant + " and ascust='" + csCustID + "' and (asidat<'" + now.Subtract(TimeSpan.FromDays(30)).ToString("yyyy-MM-dd") + "' and asidat>='" + now.Subtract(TimeSpan.FromDays(60)).ToString("yyyy-MM-dd") + "')";
            solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            reader = solarsoft.RunQuery(query);
            if (reader.Read())
            {
                dOver30 = Convert.ToDouble(reader[0]);
            }
            reader.Close();
            // get over 60
            query = "select coalesce(sum(asduam), 0.0) from cmsdat.arop where ascomp=" + csPlant + " and ascust='" + csCustID + "' and (asidat<'" + now.Subtract(TimeSpan.FromDays(60)).ToString("yyyy-MM-dd") + "' and asidat>='" + now.Subtract(TimeSpan.FromDays(90)).ToString("yyyy-MM-dd") + "')";
            solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            reader = solarsoft.RunQuery(query);
            if (reader.Read())
            {
                dOver60 = Convert.ToDouble(reader[0]);
            }
            reader.Close();
            // get over 90
            query = "select coalesce(sum(asduam), 0.0) from cmsdat.arop where ascomp=" + csPlant + " and ascust='" + csCustID + "' and (asidat<'" + now.Subtract(TimeSpan.FromDays(90)).ToString("yyyy-MM-dd") + "' and asidat>='" + now.Subtract(TimeSpan.FromDays(120)).ToString("yyyy-MM-dd") + "')";
            solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            reader = solarsoft.RunQuery(query);
            if (reader.Read())
            {
                dOver90 = Convert.ToDouble(reader[0]);
            }
            reader.Close();
            // get over 120
            query = "select coalesce(sum(asduam), 0.0) from cmsdat.arop where ascomp=" + csPlant + " and ascust='" + csCustID + "' and (asidat<'" + now.Subtract(TimeSpan.FromDays(120)).ToString("yyyy-MM-dd") + "')";
            solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            reader = solarsoft.RunQuery(query);
            if (reader.Read())
            {
                dOver120 = Convert.ToDouble(reader[0]);
            }
            reader.Close();
        }

        public static Customer operator +(Customer c1, Customer c2)
        {
            Customer result = new Customer();
            result.dTotal = c1.dTotal + c2.dTotal;
            result.dCurrent = c1.dCurrent + c2.dCurrent;
            result.dOver30 = c1.dOver30 + c2.dOver30;
            result.dOver60 = c1.dOver60 + c2.dOver60;
            result.dOver90 = c1.dOver90 + c2.dOver90;
            result.dOver120 = c1.dOver120 + c2.dOver120;
            return result;
        }
    }
}