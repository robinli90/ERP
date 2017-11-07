using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace AddSinglePart
{
    class Part
    {
        public HolePrices holePrices { get; set; }
        public string GetPartString()
        {
            return partType + " " + diameter + " X " + thickness;
        }
        public string partType { get; set; }
        public string diameter { get; set; }
        public string thickness { get; set; }

        // to read data from database
        public void GetPart()
        {
            // initialize hole prices
            holePrices = new HolePrices();
            holePrices.Hole1 = "0.00000";
            holePrices.Hole2 = "0.00000";
            holePrices.Hole3 = "0.00000";
            holePrices.Hole4 = "0.00000";
            holePrices.Hole5 = "0.00000";
            holePrices.Hole6 = "0.00000";
            holePrices.Hole8 = "0.00000";
            holePrices.Hole10 = "0.00000";
            holePrices.Hole12 = "0.00000";
            // database
            string connectionString = "Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=JXU;Pwd=qwpo555;";//Uid=ZWANG;Pwd=ZWANG;";
            OdbcConnection connection = new OdbcConnection(connectionString);
            connection.Open();
            string query = "select fides1 from cmsdat.fomo where fiocde = 'HOLES' and fimcde='" + GetPartString() + "'";
            OdbcCommand com = new OdbcCommand(query, connection);
            OdbcDataReader reader = com.ExecuteReader();
            if (!reader.HasRows)
            {
                throw new Exception("No hole category record for part " + GetPartString());
            }
            string id = null;
            while (reader.Read())
            {
                id = reader[0].ToString();
                id = id.Replace("CATEGORY", "CAT");
            }
            reader.Close();
            query = "select jcvoll, jcpric from cmsdat.iprcc where jcpart='" + id + "' and jcplcd='HOLES'";
            com.CommandText = query;
            reader = com.ExecuteReader();
            if (!reader.HasRows)
            {
                throw new Exception("No hole price record for part " + GetPartString());
            }
            int number;
            string price;
            while (reader.Read())
            {
                number = Convert.ToInt32(reader[0]);
                price = reader[1].ToString();
                // update edit
                switch (number)
                {
                    case 0:
                        break;
                    case 1:
                        holePrices.Hole1 = price;
                        break;
                    case 2:
                        holePrices.Hole2 = price;
                        break;
                    case 3:
                        holePrices.Hole3 = price;
                        break;
                    case 4:
                        holePrices.Hole4 = price;
                        break;
                    case 5:
                        holePrices.Hole5 = price;
                        break;
                    case 6:
                        holePrices.Hole6 = price;
                        break;
                    case 8:
                        holePrices.Hole8 = price;
                        break;
                    case 10:
                        holePrices.Hole10 = price;
                        break;
                    case 12:
                        holePrices.Hole12 = price;
                        break;
                    default:
                        throw new Exception("Invalid hole number!");
                }
            }
            reader.Close();
            connection.Close();
        }
    }
}