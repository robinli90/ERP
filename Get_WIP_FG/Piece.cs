using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace Get_WIP_FG
{
    class Piece
    {
        public string sID;
        public string sDesc;
        public string sCurrentDate;
        public double dSteelCost = 0.0;
        public bool bHasNitride = false;
        public bool bIsWIP = true;
        public List<Seq> l_Seq = new List<Seq>();

        public void GetSeqList()
        {
            // check if WIP or FG
            if (l_Seq.Count > 0)
            {
                if (bHasNitride)
                {
                    if (Convert.ToInt32(l_Seq[l_Seq.Count - 1].sID) >= 790)
                    {
                        bIsWIP = false;
                    }
                }
                else
                {
                    if (Convert.ToInt32(l_Seq[l_Seq.Count - 1].sID) >= 780)
                    {
                        bIsWIP = false;
                    }
                }
            }
        }
    }
}