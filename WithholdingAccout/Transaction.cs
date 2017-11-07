using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace WithholdingAccout
{
    class Transaction
    {
        public string amount = string.Empty;
        public string date = string.Empty;
        public string type = string.Empty;
        public string voucherID = string.Empty;
        public string venderOrCustomer = string.Empty;
        public string taxID = string.Empty;
        public string user = "";
        public string tDate = "";
        public string pDate = "";

        public Transaction(string date, string type, string amount, string voucherRef, string dkrefd, string dkaddd, string user, string tDate, string pDate)
        {
            this.amount = amount;
            this.date = date;
            this.type = type;
            voucherID = voucherRef;
            this.user = user;
            this.tDate = tDate;
            this.pDate = pDate;
            // extract vendor or customer from dkrefd field
            if (!dkrefd.Contains("AJUSTE") && !dkrefd.Contains("CASH RECEIPT") && !dkrefd.Contains("RECIBO DE CHEQUE") && !dkrefd.Contains("ENTRADA FACTURA MANU") && !dkrefd.Contains("MANUAL INVOICE ENTRY") && !dkrefd.Contains("CLOSING ENTRIES"))
            {
                venderOrCustomer = dkrefd;
            }
            else
            // extract vendor or customer from dkaddd field
            {
                if (dkaddd.Length==0 || '0' != dkaddd[0])
                {
                    venderOrCustomer = dkaddd;
                }
                else
                {
                    venderOrCustomer = dkaddd.Substring(8);
                }
            }
        }

        public void GetVenderOrCustomer()
        {
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            // get vender name and tax id
            string query;
            OdbcDataReader reader;
            if ("AR" == type)
            {
                query = "select bvgstl from cmsdat.cust where bvname like '"+venderOrCustomer+"'";
                reader = solarsoft.RunQuery(query);
                while (reader.Read())
                {
                    if (reader[0].ToString().Trim().Length > 0)
                    {
                        taxID = reader[0].ToString().Trim();
                    }
                }
            }
            else
            {
                query = "select btname, btgstl from cmsdat.vchr, cmsdat.vend where idcom#=4 and idven#=btvend and idvch#='" + voucherID + "'";
                reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    venderOrCustomer = reader[0].ToString().Trim();
                    taxID = reader[1].ToString().Trim();
                }
                reader.Close();
            }
            reader.Close();
        }
    }
}
