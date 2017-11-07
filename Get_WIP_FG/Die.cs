using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using ExcoUtility;

namespace Get_WIP_FG
{
    class Die
    {
        public string sID = "";
        public string sCurrentDate = "";
        public string sOrderDate = "";
        public string sCustID = "";
        public string sCustName = "";
        public List<Piece> l_Piece = new List<Piece>();

        public void GetPieceList()
        {
            // get sequence information from each piece
            foreach (Piece piece in l_Piece)
            {
                piece.GetSeqList();
            }
        }
    }
}