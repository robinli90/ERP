using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.Odbc;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel;
using ExcoUtility;

namespace Get_WIP_FG
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            monthCalendar.DateSelected += new DateRangeEventHandler(monthCalendar_DateSelected);
            monthCalendar.SelectionStart = DateTime.Now;
        }

        private string sCurrentDate = "";

        private void buttonStart_Click(object sender, EventArgs e)
        {
            List<Die> l_die = new List<Die>();
            // get current date
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            // get die list, for historical records, use cmsdat.ocmh
            richTextBox.AppendText("getting die list at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            string sQuery = "select distinct dcord#, dcodat, dcbcus, dcbnam from cmsdat.ocrh left join cmsdat.oih on dcord#=dhord# where dcplnt='001' and (dhsdat is null and (dhidat>'" + sCurrentDate + "' or (dhidat is null and dcstat<>'C')) or dhsdat>'" + sCurrentDate + "') and dcodat<='" + sCurrentDate + "' order by dcord# desc";
            OdbcDataReader reader = database.RunQuery(sQuery);
            while (reader.Read())
            {
                Die die = new Die();
                die.sID = reader["dcord#"].ToString().Trim();
                die.sCurrentDate = sCurrentDate;
                die.sOrderDate = Convert.ToDateTime(reader["dcodat"]).ToString("MM/dd/yyyy");
                die.sCustID = reader["dcbcus"].ToString().Trim();
                die.sCustName = reader["dcbnam"].ToString().Trim();
                l_die.Add(die);
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // get steel cost
            richTextBox.AppendText("getting steel cost at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            Dictionary<string, double> steelCostMap = new Dictionary<string, double>();
            sQuery = "select fzjobn, coalesce(sum(fztcos),0.0) as cost from cmsdat.jcstt where fzdate<='" + sCurrentDate + "' and fzoseq=100 group by fzjobn";
            reader = database.RunQuery(sQuery);
            while (reader.Read())
            {
                string wo = reader["fzjobn"].ToString().Trim();
                double dSteelCost = Convert.ToDouble(reader["cost"]);
                steelCostMap.Add(wo, dSteelCost);
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // get sequences
            richTextBox.AppendText("getting sequences at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            Dictionary<string, List<Seq>> seqMap = new Dictionary<string, List<Seq>>();
            sQuery = "select fwjobn, fwoseq, fwcost from cmsdat.jcsta where fwdate<='" + sCurrentDate + "' order by fwoseq";
            reader = database.RunQuery(sQuery);
            while (reader.Read())
            {
                string wo = reader["fwjobn"].ToString().Trim();
                Seq seq = new Seq();
                seq.sID = reader["fwoseq"].ToString().Trim();
                seq.dCost = Convert.ToDouble(reader["fwcost"]);
                if (seqMap.ContainsKey(wo))
                {
                    seqMap[wo].Add(seq);
                }
                else
                {
                    List<Seq> seqList = new List<Seq>();
                    seqList.Add(seq);
                    seqMap.Add(wo, seqList);
                }
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // check if it has nitride
            richTextBox.AppendText("checking nitride at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            Dictionary<string, bool> nitrideMap = new Dictionary<string, bool>();
            sQuery = "select edjob# from cmsdat.cjobdr where edseq#=790";
            reader = database.RunQuery(sQuery);
            if (!reader.HasRows)
            {
                reader.Close();
                sQuery = "select edjob# from cmsdat.hjobdr where edseq#=790";
                reader = database.RunQuery(sQuery);
                if (reader.HasRows)
                {
                    nitrideMap.Add(reader["edjob#"].ToString().Trim(), true);
                }
            }
            else
            {
                nitrideMap.Add(reader["edjob#"].ToString().Trim(), true);
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // get piece list from current table
            richTextBox.AppendText("getting piece list CJOBH at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            Dictionary<string, List<Piece>> cjobhMap = new Dictionary<string, List<Piece>>();
            Dictionary<string, List<Piece>> hjobhMap = new Dictionary<string, List<Piece>>();
            sQuery = "select dnord#, dnjob, dnpart from cmsdat.cjobh where dnord#>0";
            reader = database.RunQuery(sQuery);
            while (reader.Read())
            {
                Piece piece = new Piece();
                piece.sCurrentDate = sCurrentDate;
                string so = reader["dnord#"].ToString().Trim();
                piece.sID = reader["dnjob"].ToString().Trim();
                piece.sDesc = reader["dnpart"].ToString().Trim();
                if (nitrideMap.ContainsKey(piece.sID))
                {
                    piece.bHasNitride = true;
                }
                if (seqMap.ContainsKey(piece.sID))
                {
                    piece.l_Seq.AddRange(seqMap[piece.sID]);
                }
                if (steelCostMap.ContainsKey(piece.sID))
                {
                    piece.dSteelCost = steelCostMap[piece.sID];
                }
                if (cjobhMap.ContainsKey(so))
                {
                    cjobhMap[so].Add(piece);
                }
                else
                {
                    List<Piece> pieceList = new List<Piece>();
                    pieceList.Add(piece);
                    cjobhMap.Add(so, pieceList);
                }
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // get piece list from history table
            richTextBox.AppendText("getting die list HJOBH at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            sQuery = "select dnord#, dnjob, dnpart from cmsdat.hjobh where dnord#>0";
            reader = database.RunQuery(sQuery);
            while (reader.Read())
            {
                Piece piece = new Piece();
                piece.sCurrentDate = sCurrentDate;
                string so = reader["dnord#"].ToString().Trim();
                piece.sID = reader["dnjob"].ToString().Trim();
                piece.sDesc = reader["dnpart"].ToString().Trim();
                if (nitrideMap.ContainsKey(piece.sID))
                {
                    piece.bHasNitride = true;
                }
                if (seqMap.ContainsKey(piece.sID))
                {
                    piece.l_Seq.AddRange(seqMap[piece.sID]);
                }
                if (steelCostMap.ContainsKey(piece.sID))
                {
                    piece.dSteelCost = steelCostMap[piece.sID];
                }
                if (hjobhMap.ContainsKey(so))
                {
                    hjobhMap[so].Add(piece);
                }
                else
                {
                    List<Piece> pieceList = new List<Piece>();
                    pieceList.Add(piece);
                    hjobhMap.Add(so, pieceList);
                }
            }
            reader.Close();
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            richTextBox.AppendText("processing all dies at" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            foreach (Die die in l_die)
            {
                if (cjobhMap.ContainsKey(die.sID))
                {
                    die.l_Piece.AddRange(cjobhMap[die.sID]);
                }
                if (hjobhMap.ContainsKey(die.sID))
                {
                    die.l_Piece.AddRange(hjobhMap[die.sID]);
                }

                die.GetPieceList();
                if (richTextBox.Text.Length > 4000)
                {
                    richTextBox.Clear();
                }
            }
            richTextBox.AppendText("done" + DateTime.Now.ToShortTimeString() + Environment.NewLine);
            richTextBox.SelectionStart = richTextBox.Text.Length;
            richTextBox.ScrollToCaret();
            richTextBox.Refresh();
            // write to excel
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);
            Excel.Worksheet wipSheet = book.Worksheets[1];
            wipSheet.Name = "WIP at " + sCurrentDate;
            Excel.Worksheet fgSheet = book.Worksheets[2];
            fgSheet.Name = "FG at " + sCurrentDate;
            // insert title
            wipSheet.Cells[1, 1] = "WIP at " + sCurrentDate;
            wipSheet.Cells.get_Range("A1").Font.Bold = true;
            wipSheet.Cells.get_Range("A1").Font.Size = 20;
            wipSheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            wipSheet.Cells.get_Range("A1", "H1").Merge();
            fgSheet.Cells[1, 1] = "FG at " + sCurrentDate;
            fgSheet.Cells.get_Range("A1").Font.Bold = true;
            fgSheet.Cells.get_Range("A1").Font.Size = 20;
            fgSheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            fgSheet.Cells.get_Range("A1", "H1").Merge();
            // build header
            int row = 2;
            int column = 1;
            wipSheet.Cells[row, column++] = "SO#";
            wipSheet.Cells[row, column++] = "DATE";
            wipSheet.Cells[row, column++] = "CUST#";
            wipSheet.Cells[row, column++] = "CUST";
            wipSheet.Cells[row, column++] = "WO#";
            wipSheet.Cells[row, column++] = "PART";
            wipSheet.Cells[row, column++] = "STEEL";
            wipSheet.Cells[row, column++] = "SEQ";
            wipSheet.Cells[row, column++] = "SEQ COST";
            Excel.Range WIPRange = wipSheet.Cells.get_Range("A2", "S2");
            WIPRange.Font.Bold = true;
            WIPRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            column = 1;
            fgSheet.Cells[row, column++] = "SO#";
            fgSheet.Cells[row, column++] = "DATE";
            fgSheet.Cells[row, column++] = "CUST#";
            fgSheet.Cells[row, column++] = "CUST";
            fgSheet.Cells[row, column++] = "WO#";
            fgSheet.Cells[row, column++] = "PART";
            fgSheet.Cells[row, column++] = "STEEL";
            fgSheet.Cells[row, column++] = "SEQ";
            fgSheet.Cells[row, column++] = "SEQ COST";
            Excel.Range FGRange = fgSheet.Cells.get_Range("A2", "S2");
            FGRange.Font.Bold = true;
            FGRange.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            // fill sheet
            int wipRow = 3;
            int fgRow = 3;
            bool hasWIP = false;
            bool hasFG = false;
            double wipSteel = 0.0;
            double wipBurden = 0.0;
            double fgSteel = 0.0;
            double fgBurden = 0.0;
            for (int i = 0; i < l_die.Count; i++)
            {
                Die die = l_die[i];
                bool outputPieceInfoWIP = false;
                bool outputPieceInfoFG = false;
                for (int j = 0; j < die.l_Piece.Count; j++)
                {
                    Piece piece = die.l_Piece[j];
                    if (0 == piece.l_Seq.Count)
                    {
                        continue;
                    }
                    if (!outputPieceInfoWIP)
                    {
                        // output die info
                        if (piece.bIsWIP && !hasWIP)
                        {
                            wipSheet.Cells[wipRow, 1] = die.sID;
                            wipSheet.Cells[wipRow, 2] = die.sOrderDate;
                            wipSheet.Cells[wipRow, 3].NumberFormat = "@";
                            wipSheet.Cells[wipRow, 3] = die.sCustID;
                            wipSheet.Cells[wipRow, 4] = die.sCustName;
                            hasWIP = true;
                            outputPieceInfoWIP = true;
                        }
                    }
                    if (!outputPieceInfoFG)
                    {
                        if (!piece.bIsWIP && !hasFG)
                        {
                            fgSheet.Cells[fgRow, 1] = die.sID;
                            fgSheet.Cells[fgRow, 2].NumberFormat = "yyyy-MM-dd";
                            fgSheet.Cells[fgRow, 2] = die.sOrderDate;
                            fgSheet.Cells[fgRow, 3].NumberFormat = "@";
                            fgSheet.Cells[fgRow, 3] = die.sCustID;
                            fgSheet.Cells[fgRow, 4] = die.sCustName;
                            outputPieceInfoFG = true;
                            hasFG = true;
                            outputPieceInfoFG = true;
                        }
                    }
                    for (int k = 0; k < piece.l_Seq.Count; k++)
                    {
                        Seq seq = piece.l_Seq[k];
                        // output piece info
                        if (piece.bIsWIP)
                        {
                            if (0 == k)
                            {
                                wipSheet.Cells[wipRow, 5].NumberFormat = "@";
                                wipSheet.Cells[wipRow, 5] = piece.sID;
                                wipSheet.Cells[wipRow, 6] = piece.sDesc;
                                wipSheet.Cells[wipRow, 7] = piece.dSteelCost.ToString("C2");
                                wipSteel += piece.dSteelCost;
                            }
                            wipSheet.Cells[wipRow, 8] = seq.sID;
                            wipSheet.Cells[wipRow, 9] = seq.dCost.ToString("C2");
                            wipBurden += seq.dCost;
                            wipRow++;
                        }
                        else
                        {
                            if (0 == k)
                            {
                                fgSheet.Cells[fgRow, 5].NumberFormat = "@";
                                fgSheet.Cells[fgRow, 5] = piece.sID;
                                fgSheet.Cells[fgRow, 6] = piece.sDesc;
                                fgSheet.Cells[fgRow, 7] = piece.dSteelCost.ToString("C2");
                                fgSteel += piece.dSteelCost;
                            }
                            fgSheet.Cells[fgRow, 8] = seq.sID;
                            fgSheet.Cells[fgRow, 9] = seq.dCost.ToString("C2");
                            fgBurden += seq.dCost;
                            fgRow++;
                        }
                    }
                }
                if (hasWIP)
                {
                    hasWIP = false;
                    wipRow++;
                }
                if (hasFG)
                {
                    hasFG = false;
                    fgRow++;
                }
            }
            // add summary
            wipSheet.Cells[wipRow, 6] = "TOTAL:";
            wipSheet.Cells[wipRow, 7] = wipSteel.ToString("C2");
            wipSheet.Cells[wipRow, 9] = wipBurden.ToString("C2");
            wipSheet.Cells.get_Range("F" + wipRow.ToString(), "I" + wipRow.ToString()).Font.Bold = true;
            fgSheet.Cells[fgRow, 6] = "TOTAL:";
            fgSheet.Cells[fgRow, 7] = fgSteel.ToString("C2");
            fgSheet.Cells[fgRow, 9] = fgBurden.ToString("C2");
            fgSheet.Cells.get_Range("F" + fgRow.ToString(), "I" + fgRow.ToString()).Font.Bold = true;
            // adjust style
            wipSheet.Cells.Columns.AutoFit();
            wipSheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            fgSheet.Cells.Columns.AutoFit();
            fgSheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            // write to file
            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "WIP and FG report at " + sCurrentDate + ".xlsx");
            File.Delete(path);
            book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            System.Diagnostics.Process.Start(path);
        }

        private void monthCalendar_DateSelected(Object sender, DateRangeEventArgs e)
        {
            sCurrentDate = e.Start.ToString("yyyy-MM-dd");
            buttonStart.Enabled = true;
        }
    }
}