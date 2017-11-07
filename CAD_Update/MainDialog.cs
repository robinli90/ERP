using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ExcoUtility;
using System.IO;
using System.Data.Odbc;

namespace CAD_Update
{
    public partial class MainDialog : Form
    {
        public struct Piece
        {
            public List<string> seqList;
            public string workOrder;
            public string part;
        };

        public string salesOrder = string.Empty;

        public List<Piece> pieceList = new List<Piece>();

        public string customerName = string.Empty;
        public string customerID = string.Empty;

        public struct Data
        {
            public string wo;
            public string so;
            public string steel;
            public double length;
            public string stock;
            public string date;
            public string part;
        };

        public struct SteelData
        {
            public string id;
            public string usage;
        };

        public MainDialog()
        {
            InitializeComponent();
            CancelButton = buttonCancel;
            // temp
            List<SteelData> steelData = new List<SteelData>();
            string query = "select distinct heat from dbo.d_steel where cuttime >= '2013-03-01 00:00:00' order by heat";
            ExcoODBC decade = ExcoODBC.Instance;
            decade.Open(Database.DECADE);
            OdbcDataReader reader = decade.RunQuery(query);
            while (reader.Read())
            {
                SteelData data = new SteelData();
                data.id = reader[0].ToString();
                steelData.Add(data);
            }
            reader.Close();
            for (int i = 0; i < steelData.Count; i++)
            {
                List<string> soList = new List<string>();
                query = "select distinct ordernumber from dbo.d_steel where heat='" + steelData[i].id + "' order by ordernumber";
                decade = ExcoODBC.Instance;
                decade.Open(Database.DECADE);
                reader = decade.RunQuery(query);
                while (reader.Read())
                {
                    soList.Add(reader[0].ToString());
                }
                reader.Close();
                query = "select sum(byqty) from cmsdat.stkt, cmsdat.hjobh where bydref='PRODUCTION BACKFLUSH UTILITY' and bytunt='IN' and byjref=dnjob and (dnord#=";
                foreach (string so in soList)
                {
                    if (so.Contains(soList[soList.Count - 1]))
                    {
                        query += so + ")";
                    }
                    else
                    {
                        query += so + " or dnord#=";
                    }
                }
                double result = 0.0;
                ExcoODBC solarsoft = ExcoODBC.Instance;
                solarsoft.Open(Database.CMSDAT);
                reader = solarsoft.RunQuery(query);
                if (reader.Read() && reader[0]!=DBNull.Value)
                {
                    result += Convert.ToDouble(reader[0]);
                }
                reader.Close();
                query = "select sum(byqty) from cmsdat.stkt, cmsdat.cjobh where bydref='PRODUCTION BACKFLUSH UTILITY' and bytunt='IN'  and byjref=dnjob and (dnord#=";
                foreach (string so in soList)
                {
                    if (so.Contains(soList[soList.Count - 1]))
                    {
                        query += so + ")";
                    }
                    else
                    {
                        query += so + " or dnord#=";
                    }
                }
                reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    if (reader[0] != DBNull.Value)
                    {
                        result += Convert.ToDouble(reader[0]);
                    }
                }
                reader.Close();
                SteelData data = steelData[i];
                data.usage = result.ToString("F2");
                steelData[i] = data;
            }
            StreamWriter writer = File.CreateText("aa.txt");
            foreach (SteelData data in steelData)
            {
                writer.Write(data.id + '\t' + data.usage + Environment.NewLine);
            }
            writer.Close();

            //// get missing wo
            ////for (int i = 1; i < dataList.Count; i++)
            ////{
            ////    Data data = dataList[i];
            ////    if (data.wo.Length == 9)
            ////    {
            ////        while (Convert.ToInt32(dataList[i].wo) - 1 > Convert.ToInt32(dataList[i-1].wo))
            ////        {
            ////            Data newData = new Data();
            ////            newData.wo = "00" + (Convert.ToInt32(dataList[i].wo) - 1).ToString();
            ////            dataList.Insert(i, newData);
            ////        }
            ////    }
            ////    else if (data.wo.Length == 7)
            ////    {
            ////        if (dataList[i - 1].wo.Length != 9)
            ////        {
            ////            while (Convert.ToInt32(dataList[i].wo) - 1 > Convert.ToInt32(dataList[i - 1].wo))
            ////            {
            ////                Data newData = new Data();
            ////                newData.wo = "00" + (Convert.ToInt32(dataList[i].wo) - 1).ToString();
            ////                dataList.Insert(i, newData);
            ////            }
            ////        }
            ////        else
            ////        {
            ////            i++;
            ////        }
            ////    }
            ////}
            //// get so
            ////List<Data> tempData = new List<Data>();
            //for (int i = 0; i < dataList.Count; i++)
            //{
            //    Data data = dataList[i];
            //    query = "select dnord# from cmsdat.cjobh where dnjob='" + dataList[i].wo + "' and dnstat!='N'";
            //    reader = solarsoft.RunQuery(query);
            //    if (reader.Read())
            //    {
            //        data.so = reader[0].ToString();
            //    }
            //    else
            //    {
            //        reader.Close();
            //        query = "select dnord# from cmsdat.hjobh where dnjob='" + dataList[i].wo + "'";
            //        reader = solarsoft.RunQuery(query);
            //        if (reader.Read())
            //        {
            //            data.so = reader[0].ToString();
            //        }
            //        else
            //        {
            //            //data.wo = "NULL";
            //            data.so = "NULL";
            //            //data.steel = "NULL";
            //        }
            //    }
            //    reader.Close();
                //if (!data.wo.Contains("NULL"))
                //{
                //    if (data.steel==null)
                //    {
                //        tempData.Add(data);
                //    }
                //}
            //    dataList[i] = data;
            //}

            //StreamWriter writer = File.CreateText("aa.txt");
            //foreach (Data data in dataList)
            //{
            //    writer.Write(data.wo + '\t' + data.so + '\t' + data.steel + '\t' + data.stock + '\t' + data.length + '\t' + data.part + Environment.NewLine);
            //}
            //writer.Close();
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {

        }

        private void ResetDialog()
        {
            // clear content
            textBoxSO.Clear();
            textBoxNumOfCavs.Clear();
            textBoxOrderDate.Clear();
            textBoxReqDate.Clear();
            textBoxThkBacker.Clear();
            textBoxThkBolster.Clear();
            textBoxThkDieRing.Clear();
            textBoxThkFeeder.Clear();
            textBoxThkMandrel.Clear();
            textBoxThkPlate.Clear();
            textBoxThkSubBoster.Clear();
            textBoxDiaBacker.Clear();
            textBoxDiaBolster.Clear();
            textBoxDiaDieRing.Clear();
            textBoxDiaFeeder.Clear();
            textBoxDiaMandrel.Clear();
            textBoxDiaPlate.Clear();
            textBoxDiaSubBolster.Clear();
            richTextBoxFeaturesAndOptions.Clear();
            richTextBoxPart.Clear();
            // reset enable/disable list
            textBoxSO.Enabled = true;
        }

        private void textBoxSO_Input(object sender, KeyEventArgs e)
        {
            if (Keys.Enter == e.KeyCode && 6 == textBoxSO.TextLength && Convert.ToInt32(textBoxSO.Text) > 200000)
            {
                salesOrder = textBoxSO.Text;
                pieceList.Clear();
                // get created work orders
                string query = "select dnjob, dnpart from cmsdat.cjobh where dnord#=" + salesOrder;
                ExcoODBC solarsoft = ExcoODBC.Instance;
                solarsoft.Open(Database.CMSDAT);
                OdbcDataReader reader = solarsoft.RunQuery(query);
                while (reader.Read())
                {
                    Piece piece = new Piece();
                    piece.workOrder = reader[0].ToString().Trim();
                    piece.part = reader[1].ToString().Trim();
                    pieceList.Add(piece);
                }
                reader.Close();
                // if no pieces, do nothing
                if (0 == pieceList.Count)
                {
                    MessageBox.Show("Not an active order!");
                    return;
                }
                // get order details
                query = "select dcbcus, dcbnam, dcodat, dccdat from cmsdat.ocrh where dcord#=" + salesOrder;
                reader = solarsoft.RunQuery(query);
                if (reader.Read())
                {
                    customerID = reader[0].ToString().Trim();
                    customerName = reader[1].ToString().Trim();
                    textBoxOrderDate.Text = Convert.ToDateTime(reader[2]).ToString("yyyy-MM-dd");
                    textBoxReqDate.Text = Convert.ToDateTime(reader[3]).ToString("yyyy-MM-dd");

                }
                reader.Close();
                // check if sub parts are needed
                foreach (Piece piece in pieceList)
                {
                    if ("HD" == piece.part.Substring(0, 2) && 7 == piece.workOrder.Length)
                    {
                        query = "select efmtlp from cmsdat.cjobdm where efjob#='" + piece.workOrder + "'";
                        reader = solarsoft.RunQuery(query);
                        while (reader.Read())
                        {
                            bool hasSubPart = false;
                            foreach (Piece subPart in pieceList)
                            {
                                if (reader[0].ToString().Trim() == subPart.part)
                                {
                                    hasSubPart = true;
                                    break;
                                }
                            }
                            if (!hasSubPart)
                            {
                                Piece newPiece = new Piece();
                                newPiece.part = reader[0].ToString().Trim();
                                newPiece.workOrder = "New";
                                pieceList.Add(newPiece);
                            }
                        }
                        reader.Close();
                        break;
                    }
                }
                // display in textBoxPart
                richTextBoxPart.Clear();
                richTextBoxPart.Text = customerID + " (" + customerName + ")" + Environment.NewLine;
                foreach (Piece piece in pieceList)
                {
                    richTextBoxPart.Text += piece.workOrder + ", " + piece.part + Environment.NewLine;
                }
                // display in features and options
                richTextBoxFeaturesAndOptions.Clear();
                richTextBoxFeaturesAndOptions.Text = string.Empty;
                foreach (Piece piece in pieceList)
                {
                    if (7 == piece.workOrder.Length)
                    {
                        richTextBoxFeaturesAndOptions.Text += piece.workOrder + ":" + Environment.NewLine;
                        query = "select r0fcde, r0ocde, r0qtyr FROM cmsdat.food where r0lstn='" + piece.workOrder + "'";
                        reader = solarsoft.RunQuery(query);
                        while (reader.Read())
                        {
                            richTextBoxFeaturesAndOptions.Text += reader[0].ToString().Trim() + ", ";
                            richTextBoxFeaturesAndOptions.Text += reader[1].ToString().Trim() + ", ";
                            richTextBoxFeaturesAndOptions.Text += reader[2].ToString().Trim() + Environment.NewLine;
                            // check number of cavities
                            if ("CAVITIES" == reader[0].ToString().Trim() && "HOLES" == reader[1].ToString().Trim())
                            {
                                textBoxNumOfCavs.Text = reader[2].ToString().Trim();
                            }
                        }
                        reader.Close();
                        richTextBoxFeaturesAndOptions.Text += Environment.NewLine;
                    }
                }
                // get details of pieces
                foreach (Piece piece in pieceList)
                {
                    // hollow die sub parts
                    if (8 == piece.workOrder.Length)
                    {
                        // backer
                        if (piece.part.Contains("BAC"))
                        {
                            checkBoxBacker.Checked = true;
                            groupBoxBacker.Enabled = true;
                            query = "select efqppc from cmsdat.cjobdm where efjob#='" + piece.workOrder + "'";
                            reader = solarsoft.RunQuery(query);
                            if (reader.Read())
                            {
                                textBoxThkBacker.Text = (Convert.ToDouble(reader[0]) * 25.4).ToString("F2");
                            }
                            reader.Close();
                        }
                        // plate
                        else if (piece.part.Contains("PLA"))
                        {
                            checkBoxPlate.Checked = true;
                            groupBoxPlate.Enabled = true;
                        }
                        // mandrel
                        else if (piece.part.Contains("MAN"))
                        {
                            checkBoxMandrel.Checked = true;
                            groupBoxMandrel.Enabled = true;
                        }
                        else
                        {
                            throw new Exception("Invalid hollow piece type " + piece.part);
                        }
                    }
                    // parent piece or solid die
                    else
                    {

                    }
                }
            }

            // enable save button
            buttonSave.Enabled = true;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
