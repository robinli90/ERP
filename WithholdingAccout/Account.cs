using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace WithholdingAccout
{
    class Account
    {
        public string ID { get; set; }
        public string Name { get; set; }
        public List<Transaction> transList = new List<Transaction>();

        public Account(string id, string name)
        {
            ID = id;
            Name = name;
            GetAccounts();
        }

        public void GetAccounts()
        {
            ExcoODBC solarsoft = ExcoODBC.Instance;
            solarsoft.Open(Database.CMSDAT);
            // get amount
            string query = "select dktdat, dksrce, dkamt, dkkeyn, dkrefd, dkaddd, dkfut4, dktdat, dkpdat from cmsdat.gtran where dkacc#='" + ID.Replace("-", "") + "' and (dkfsyr=20 and dkfsyy=14 and dkfspr<=6) order by dktdat";
            OdbcDataReader reader = solarsoft.RunQuery(query);
            while (reader.Read())
            {
                Transaction trans = new Transaction(reader[0].ToString().Trim(), reader[1].ToString().Trim(), reader[2].ToString().Trim(), reader[3].ToString().Trim(), reader[4].ToString().Trim(), reader[5].ToString().Trim(), reader[6].ToString().Trim(), reader[7].ToString().Trim(), reader[8].ToString().Trim());
                transList.Add(trans);
            }
            reader.Close();
            // get vender
            foreach (Transaction trans in transList)
            {
                if (trans.voucherID.Length == 0)
                {
                    trans.venderOrCustomer = "CLOSING ENTRIES";
                }
                else if (!trans.type.Contains("AR"))
                {
                    if (trans.voucherID.Trim().Length > 0)
                    {
                        trans.GetVenderOrCustomer();
                    }
                }
            }
        }
    }
}
