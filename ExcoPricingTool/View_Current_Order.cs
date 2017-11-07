using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ExcoPricingTool
{
    public partial class View_Current_Order : Form
    {
        public string CFQ = "Call for Quote";
        public string externalID = "";

        protected override void OnClosing(CancelEventArgs e)
        {
            parent.Activate();
            base.OnClosing(e);
        }

        // Mouse down anywhere to drag
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        private void Form_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            //parent.Background_Save();
            //parent.Activate();
            base.OnFormClosing(e);
        }
        
        Main parent;

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public View_Current_Order(Main _parent, Point g = new Point(), Size s = new Size(), bool Highlight_Error_ = false, string viewID = "")
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            Highlight_Error = Highlight_Error_;
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            externalID = viewID;
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
        }

        // Form paint
        protected override void OnPaint(PaintEventArgs e)
        {
            int start_margin = 15;              // Item
            int start_height = bufferedPanel1.Bottom + 1;
            int main_margin = start_margin + 25;
            int extn_price_col = extn.Left;

            Color DrawForeColor = Color.White;
            SolidBrush WritingBrush = new SolidBrush(DrawForeColor);
            SolidBrush GreyBrush = new SolidBrush(Color.FromArgb(88, 88, 88));
            Pen Grey_Pen = new Pen(GreyBrush, 2);
            Pen p = new Pen(WritingBrush, 1);
            Font f = new Font("MS Reference Sans Serif", 9.5F, FontStyle.Regular);

            // Draw gray header line
            e.Graphics.DrawLine(Grey_Pen, 8, req.Bottom + 8, this.Width - 8, req.Bottom + 8);

            // Draw white footer line
            e.Graphics.DrawLine(p, this.Width / 2 - 30, start_height, this.Width - 30, start_height);
            e.Graphics.DrawString("ORDER TOTAL NET OF TAXES", f, WritingBrush, this.Width / 2 - 30, start_height + 2);
            e.Graphics.DrawString(needsCallQuote2 || ((Ref_Order != null ? Ref_Order.Total : parent.Current_Order_Total) == 0) ? CFQ : "$" + String.Format("{0:0.00}", (Ref_Order != null ? Ref_Order.Total : parent.Current_Order_Total)), f, WritingBrush, extn_price_col, start_height + 2);
                
            // Dispose all objects
            p.Dispose();
            Grey_Pen.Dispose();
            GreyBrush.Dispose();
            WritingBrush.Dispose();
            f.Dispose();
            base.OnPaint(e);

        }

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, Int32 wMsg, bool wParam, Int32 lParam);

        private const int WM_SETREDRAW = 11;

        public static void SuspendDrawing(Control parent)
        {
            SendMessage(parent.Handle, WM_SETREDRAW, false, 0);
        }

        public static void ResumeDrawing(Control parent)
        {
            SendMessage(parent.Handle, WM_SETREDRAW, true, 0);
            parent.Refresh();
        }

        private bool needsCallQuote = false;
        private bool needsCallQuote2 = false;

        // Panel paint
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            //unit of measure
            string unit = parent.isMetric ? " mm" : " in";

            // allow scroll transformation
            e.Graphics.TranslateTransform(bufferedPanel3.AutoScrollPosition.X, bufferedPanel3.AutoScrollPosition.Y);

            var panel = bufferedPanel3;
            int data_height = 16;
            int row_count = 0;
            int height_offset = 1;
            int start_height = 0;
            int start_margin = 15;              // Item
            int item_charge_col = itemchg.Left + 5;
            int extn_price_col = extn.Left;

            int main_margin = start_margin + 25;

            Color DrawForeColor = Color.White;
            Color BackColor = Color.FromArgb(64, 64, 64);
            Color HighlightColor = Color.FromArgb(76, 76, 76);

            SolidBrush WritingBrush = new SolidBrush(DrawForeColor);
            SolidBrush GreyBrush = new SolidBrush(Color.FromArgb(88, 88, 88));
            SolidBrush RedBrush = new SolidBrush(Color.FromArgb(150, 150, 150));
            SolidBrush GreenBrush = new SolidBrush(Color.LightGreen);
            Pen p = new Pen(WritingBrush, 1);
            Pen Grey_Pen = new Pen(GreyBrush, 1);

            Font f_minor = new Font("MS Reference Sans Serif", 8.5F, FontStyle.Regular);
            Font f = new Font("MS Reference Sans Serif", 9.5F, FontStyle.Regular);
            Font f_strike = new Font("MS Reference Sans Serif", 9, FontStyle.Strikeout);
            Font f_total = new Font("MS Reference Sans Serif", 8, FontStyle.Bold);
            Font f_header = new Font("MS Reference Sans Serif", 10, FontStyle.Underline);
            Font f_italic = new Font("MS Reference Sans Serif", 9, FontStyle.Italic);
            Font f_9_bold = new Font("MS Reference Sans Serif", 9, FontStyle.Bold);
            Font f_10_bold = new Font("MS Reference Sans Serif", 10, FontStyle.Bold);
            Font f_10 = new Font("MS Reference Sans Serif", 10, FontStyle.Regular);
            Font f_9 = new Font("MS Reference Sans Serif", 9, FontStyle.Regular);
            Font f_14_bold = new Font("MS Reference Sans Serif", 14, FontStyle.Bold);
            Font f_12_bold = new Font("MS Reference Sans Serif", 11, FontStyle.Bold);

            double surcharge_total = 0;

            List<Solid> Solid_List = externalID.Length > 0 ? parent.Solid_List_History.Where(x => x.OrderID == externalID).ToList() : parent.Solid_List;
            List<Hollow> Hollow_List = externalID.Length > 0 ? parent.Hollow_List_History.Where(x => x.OrderID == externalID).ToList() : parent.Hollow_List;
            List<Support> Support_List = externalID.Length > 0 ? parent.Support_List_History.Where(x => x.OrderID == externalID).ToList() : parent.Support_List;

            if (externalID.Length > 0)
            {
                Ref_Order = parent.Order_List.First(x => x.ID == externalID);
            }

            #region Solid Dies
            foreach (Solid s in Solid_List)
            {
                baseCharges Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType, true);

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, out weight);
                }
                surcharge_total += s.SurchargePrice;

                e.Graphics.DrawString(s.DieType + " Die (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), f, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
                // Base price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", Ref_Base.Price + s.CavityPrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                // Extension price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.BasePrice), f_minor, WritingBrush, extn_price_col, start_height + height_offset + (row_count * data_height));
                row_count++;

                //height_offset += 5;
                e.Graphics.DrawString("Part #: " + s.DieNo.Replace("--", "-"), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                row_count++;
                if (s.Location.Length > 0) 
                {
                    e.Graphics.DrawString("Location: " + s.Location, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Nitride)
                {
                    double nitrideprice = 0;
                    // Nitride cost
                    if (!needsCallQuote)
                        nitrideprice = parent.GetFreightWeight("", s.DieType, s.Diameter, s.Thickness, 0) * parent.nitrideRate;

                    e.Graphics.DrawString("Nitriding", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", nitrideprice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Pocket)
                {
                    // Nitride cost
                    e.Graphics.DrawString("Pocketing", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString("$" + String.Format("{0:0.00}", 50), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Backer_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Backer #: " + s.FE_Backer_No + " at location: " + s.FE_Backer_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Feeder_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Feeder #:" + s.FE_Feeder_No + " at location: " + s.FE_Feeder_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Bolster_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Bolster #:" + s.FE_Bolster_No + " at location: " + s.FE_Bolster_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_SubBol_Loc.Length > 0)
                {
                    e.Graphics.DrawString("For existing Sub Bolster #:" + s.FE_SubBol_No + " at location: " + s.FE_SubBol_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    e.Graphics.DrawString("Notes: " + note_line[0], f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        e.Graphics.DrawString("            " + line, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }
                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        e.Graphics.DrawString(DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price + s.CavityPrice)), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }

                e.Graphics.DrawString("Steel Surcharge", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.SurchargePrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));

                row_count += 3;
            }
            #endregion

            #region Hollow Dies
            foreach (Hollow s in Hollow_List)
            {
                if (s.Plate_Only || s.Mandrel_Only || s.No_Backer)
                {
                    needsCallQuote = true;
                    needsCallQuote2 = true;
                }

                baseCharges Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType, true);

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, out weight);
                }
                surcharge_total += s.SurchargePrice;

                e.Graphics.DrawString(s.DieType + " Die (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), f, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
                // Base price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", Ref_Base.Price + s.CavityPrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                // Extension price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.BasePrice), f_minor, WritingBrush, extn_price_col, start_height + height_offset + (row_count * data_height));
                row_count++;

                //height_offset += 5;
                e.Graphics.DrawString("Part #: " + s.DieNo.Replace("--", "-"), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                row_count++;
                if (s.Location.Length > 0)
                {
                    e.Graphics.DrawString("Location: " + s.Location, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Nitride)
                {
                    double nitrideprice = 0;
                    // Ni   tride cost
                    if (!needsCallQuote)
                        nitrideprice = parent.GetFreightWeight("", s.DieType, s.Diameter, s.Thickness, 0) * parent.nitrideRate;

                    e.Graphics.DrawString("Nitriding", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", nitrideprice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Backer_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Backer #: " + s.FE_Backer_No + " at location: " + s.FE_Backer_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Feeder_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Feeder #:" + s.FE_Feeder_No + " at location: " + s.FE_Feeder_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_Bolster_No.Length > 0)
                {
                    e.Graphics.DrawString("For existing Bolster #:" + s.FE_Bolster_No + " at location: " + s.FE_Bolster_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.FE_SubBol_Loc.Length > 0)
                {
                    e.Graphics.DrawString("For existing Sub Bolster #:" + s.FE_SubBol_No + " at location: " + s.FE_SubBol_Loc, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    e.Graphics.DrawString("Notes: " + note_line[0], f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        e.Graphics.DrawString("      " + line, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }
                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        e.Graphics.DrawString(DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price + s.CavityPrice)), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }

                e.Graphics.DrawString("Steel Surcharge", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.SurchargePrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));

                row_count += 3;
            }
            #endregion

            #region Support Dies
            foreach (Support s in Support_List)
            {
                baseCharges Ref_Base;

                if (s.DieType == DieType.Ring)
                {
                    Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.InnerDiameter, s.DieType, true);
                }
                else
                {
                    Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType, true);
                }

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, out weight);
                }
                surcharge_total += s.SurchargePrice;

                e.Graphics.DrawString(s.DieType + " (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), f, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
                // Base price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", Ref_Base.Price + s.CavityPrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                // Extension price
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.BasePrice), f_minor, WritingBrush, extn_price_col, start_height + height_offset + (row_count * data_height));
                row_count++;

                if (s.InnerDiameter > 0)
                {
                    e.Graphics.DrawString("Ring Inner Diameter: " + Math.Round(s.InnerDiameter * (parent.isMetric ? 25.4 : 1), 2) + unit, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }

                //height_offset += 5;
                e.Graphics.DrawString("Part #: " + s.DieNo.Replace("--", "-"), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                row_count++;
                if (s.Location.Length > 0)
                {
                    e.Graphics.DrawString("Location: " + s.Location, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    e.Graphics.DrawString("Notes: " + note_line[0], f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                    row_count++;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        e.Graphics.DrawString("      " + line, f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }
                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        e.Graphics.DrawString(DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                        e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price)), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));
                        row_count++;
                    }
                }

                e.Graphics.DrawString("Steel Surcharge", f_minor, WritingBrush, main_margin, start_height + height_offset + (row_count * data_height));
                e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", s.SurchargePrice), f_minor, WritingBrush, item_charge_col, start_height + height_offset + (row_count * data_height));

                row_count += 3;
            }
            #endregion

            height_offset -= 3;
            // Draw sub lines header line
            e.Graphics.DrawLine(p, itemchg.Left, start_height + height_offset + (row_count * data_height), itemchg.Right, start_height + height_offset + (row_count * data_height));
            e.Graphics.DrawLine(p, extn.Left, start_height + height_offset + (row_count * data_height), extn.Right, start_height + height_offset + (row_count * data_height));

            // Subtotal
            height_offset += 3;
            e.Graphics.DrawString("Subtotal (including steel surcharge)", f, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            e.Graphics.DrawString(needsCallQuote2 ? CFQ : "$" + String.Format("{0:0.00}", (Ref_Order != null ? (Ref_Order.Total - Ref_Order.FreightCost) : parent.Current_Order_Total - parent.currentFreightCost)), f_minor, WritingBrush, extn_price_col, start_height + height_offset + (row_count * data_height));
            row_count++;
            height_offset += 15;
            e.Graphics.DrawString("Freight", f, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            e.Graphics.DrawString(needsCallQuote ? CFQ : "$" + String.Format("{0:0.00}", (Ref_Order != null ? Ref_Order.FreightCost : parent.currentFreightCost)), f_minor, WritingBrush, extn_price_col, start_height + height_offset + (row_count * data_height));
            row_count++;
            row_count++;
            row_count++;

            // Resize panel
            bufferedPanel1.AutoScrollMinSize = new Size(bufferedPanel3.Width, start_height + height_offset + row_count * data_height);

            // Force resize only if too big
            if (start_height + height_offset + row_count * data_height > bufferedPanel1.Height)
                bufferedPanel3.Height = new Size(bufferedPanel1.Width, start_height + height_offset + row_count * data_height).Height;


            // Adjust surcharge value
            surchargeText.Text = "Total steel surcharge included: " + "$" + String.Format("{0:0.00}", surcharge_total);

            // Dispose all objects
            p.Dispose();
            Grey_Pen.Dispose();
            GreenBrush.Dispose();
            RedBrush.Dispose();
            GreyBrush.Dispose();
            WritingBrush.Dispose();
            f_minor.Dispose();
            f.Dispose();
            f_strike.Dispose();
            f_total.Dispose();
            f_header.Dispose();
            f_italic.Dispose();
            f_10_bold.Dispose();
            f_9_bold.Dispose();
            f_10.Dispose();
            f_9.Dispose();
            f_12_bold.Dispose();
            f_14_bold.Dispose();

            Invalidate();
        }

        Order Ref_Order;
        bool Highlight_Error = false;

        private void Form_Load(object sender, EventArgs e)
        {   
            // set panel scrolling features
            bufferedPanel1.AutoScroll = false;
            bufferedPanel1.HorizontalScroll.Enabled = false;
            bufferedPanel1.HorizontalScroll.Visible = false;
            bufferedPanel1.HorizontalScroll.Maximum = 0;
            bufferedPanel1.AutoScroll = true;

            // Mousedown anywhere to drag
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

            if (parent.isMetric)
            {
                MetricFactor = 25.4;
            }

            #region Fade Box
            TFLP = new FadeControl();
            TFLP.Size = new Size(this.Width - 2, this.Height - 2);
            TFLP.Location = new Point(999, 999);
            TFLP.Visible = true;
            TFLP.BackColor = this.BackColor;
            TFLP.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;

            TFLP.AllowDrop = true;
            TFLP.BringToFront();
            this.Controls.Add(TFLP);
            TFLP.BringToFront();

            TFLP.Opacity = 80;
            #endregion

            foreach (Control c in this.Controls)
            {
                if (c is Button)
                { 
                    Button g = (Button)c;
                    g.TabStop = false;
                    g.FlatStyle = FlatStyle.Flat;
                    g.FlatAppearance.BorderSize = 0;
                    g.FlatAppearance.BorderColor = Color.FromArgb(0, 255, 255, 255); //transparent
                }
            }

            // Set company name
            label6.Text = parent.Current_Customer.Name.ToUpper();


            // Set date
            Ref_Order = parent.Order_List.FirstOrDefault(x => x.ID == (externalID != "" ? externalID : parent.CurrentID));
            label8.Text = Ref_Order == null ? DateTime.Now.ToShortDateString() : Ref_Order.Date.ToShortDateString();

            if (Ref_Order != null)
            {
                req.Text = Ref_Order.Requisitioner;
                auth.Text = Ref_Order.Authorizer;
                dateTimePicker1.Value = Convert.ToDateTime(Ref_Order.Due);
                po.Text = Ref_Order.PO;
            }
            else
            {
                req.Text = parent.Req;
                auth.Text = parent.Auth;
                dateTimePicker1.Value = parent.Due == "" ? DateTime.Now : Convert.ToDateTime(parent.Due); 
                po.Text = parent.PO;
            }

            if (Highlight_Error)
            {
                foreach (Control c in this.Controls)
                {
                    if (c is TextBox)
                    {
                        TextBox temp = (TextBox)c;
                        if (temp.Text == "" && !temp.Name.Contains("ox"))
                        {
                            temp.BackColor = Color.Maroon;
                        }
                    }
                }

                // Show create PO button
                label22.Visible = true;
                createPOButton.Visible = true;
            }

            req.Enabled = auth.Enabled = dateTimePicker1.Enabled = po.Enabled = (!parent.DisableEdit && externalID == "");

            Invalidate();
            bufferedPanel3.Paint += new PaintEventHandler(panel1_Paint);
            bufferedPanel3.Invalidate();
        }


        private void due_MouseClick(object sender, MouseEventArgs e)
        {
            // show date
        }

        FadeControl TFLP;

        private void Grey_Out()
        {
            TFLP.Location = new Point(1, 1);
        }

        private void Grey_In()
        {
            TFLP.Location = new Point(1000, 1000);
        }

        public void Set_Form_Color(Color randomColor)
        {
            textBox1.BackColor = randomColor;
            textBox2.BackColor = randomColor;
            textBox3.BackColor = randomColor;
            textBox4.BackColor = randomColor;
        }

        private void close_button_Click_1(object sender, EventArgs e)
        {
            this.Dispose();
            this.Close();
        }

        private void po_TextChanged(object sender, EventArgs e)
        {
            TextBox T = (TextBox)sender;
            parent.PO = T.Text;
        }

        private void auth_TextChanged(object sender, EventArgs e)
        {
            TextBox T = (TextBox)sender;
            parent.Auth = T.Text;
        }

        private void due_TextChanged(object sender, EventArgs e)
        {
            TextBox T = (TextBox)sender;
            parent.Due = T.Text;
        }

        private void req_TextChanged(object sender, EventArgs e)
        {
            TextBox T = (TextBox)sender;
            parent.Req = T.Text;
        }

        double MetricFactor = 1;

        // Return the next biggest
        public baseCharges getDiaThk(double refDia, double refThk, DieType dt, bool isOddDimensions = false)
        {
            if (refDia * refThk == 0) // If either dimensions are based 0, call for quote
            {
                return null;
            }
            baseCharges Ref_Base = parent.baseCharge_List.FirstOrDefault(x => x.Diameter * (isOddDimensions ? 1 : MetricFactor) >= refDia  - (parent.isMetric ? parent.metricTolerance : 0) && x.Thickness * (isOddDimensions ? 1 : MetricFactor) >= refThk  - (parent.isMetric ? parent.metricTolerance : 0) && x.Prefix == parent.Get_Die_Prefix(dt));
            return Ref_Base;
        }

        // Return the next biggest with inner dia (for rings)
        public baseCharges getDiaThk(double refDia, double refThk, double innerDia, DieType dt, bool isOddDimensions = false)
        {
            if (parent.baseCharge_List.Where(x => x.Prefix == parent.Get_Die_Prefix(dt)).Count() == 0)
            {
                baseCharges BC = new baseCharges()
                {
                    Diameter = refDia,
                    Thickness = refThk,
                    InnerDiameter = innerDia,
                };
                BC.Price = BC.Get_Ring_Price();
                return BC;
            }

            baseCharges Ref_Base = parent.baseCharge_List.FirstOrDefault(x => x.Diameter * (isOddDimensions ? 1 : MetricFactor) >= refDia  - (parent.isMetric ? parent.metricTolerance : 0) && x.InnerDiameter * (isOddDimensions ? 1 : MetricFactor) >= innerDia && x.Thickness * (isOddDimensions ? 1 : MetricFactor) >= refThk  - (parent.isMetric ? parent.metricTolerance : 0) && x.Prefix == parent.Get_Die_Prefix(dt));
            return Ref_Base;
        }


        /// <summary>
        ///     Gets the surcharge weight.
        /// </summary>
        /// <param name="weightType">Type of the weight.</param>
        /// <param name="dieType">Type of the die.</param>
        /// <param name="diameter">The diameter.</param>
        /// <param name="thickness">The thickness.</param>
        /// <param name="pieceCount">The piece count.</param>
        /// <param name="weight">The weight.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        public static bool GetSurchargeWeight(byte weightType, DieType dieType, double diameter, double thickness,
                                               int pieceCount, out double weight)
        {
            weight = 0;

            var steelStockDias = new List<double>();

            /*
            if (!ExcoVars.SteelSurcharge_StockSizes.IsNullOrEmpty(true))
            {
                var tmpSizes = ExcoVars.SteelSurcharge_StockSizes.Split(',');

                foreach (var tmpSize in tmpSizes)
                {
                    double tmp;
                    if (double.TryParse(tmpSize, out tmp))
                        steelStockDias.Add(tmp);
                }
            }*/

            steelStockDias.Add(14.5);
            steelStockDias.Add(15.5);

            var isStockDia = false;

            //ChangeUnits(ref diameter, ref thickness);

            switch (weightType)
            {
                #region Normal Calculation
                default:


                    #region Get Surcharge Diameter
                    foreach (var curStockSize in steelStockDias)
                    {
                        var tmpMin = Math.Floor(curStockSize);
                        if (diameter > tmpMin && diameter <= curStockSize)
                        {
                            diameter = curStockSize;
                            isStockDia = true;
                        }
                    }

                    if (!isStockDia)
                        diameter = Math.Ceiling(FixSize(diameter));
                    #endregion


                    #region Get Surcharge Thickness
                    if (dieType == DieType.Hollow)
                    {
                        if (diameter <= 8)
                            thickness += 1;
                        else if (diameter <= 10)
                            thickness += 1.4;
                        else if (diameter <= 14)
                            thickness += 2;
                        else if (diameter <= 18)
                            thickness += 2.5;
                        else if (diameter <= 22)
                            thickness += 2.8;
                        else if (diameter > 22)
                            thickness += 3.1;
                    }
                    else
                    {
                        if (diameter <= 10)
                            thickness += .12 * pieceCount;
                        else if (diameter <= 14)
                            thickness += .15 * pieceCount;
                        else if (diameter <= 18)
                            thickness += .18 * pieceCount;
                        else if (diameter <= 22)
                            thickness += .21 * pieceCount;
                        else if (diameter > 22)
                            thickness += .24 * pieceCount;
                    }
                    #endregion


                    weight = diameter * 1.01 * (diameter * 1.01) * thickness * .224;
                    break;
                #endregion


                #region Sapa Calculation
                case 1: // Sapa
                    diameter = Math.Ceiling(diameter);

                    if (dieType == DieType.Hollow)
                        weight = diameter * diameter * thickness * .224 * 1.21;
                    else
                        weight = (diameter + 0.125) * (diameter + 0.125) * (thickness + pieceCount * 0.125) * 0.2223;
                    break;
                #endregion


                #region Brazil Normal Calculation
                case 2: // Brazil Kg (in lbs.)


                    #region Get Surcharge Thickness
                    if (dieType == DieType.Hollow)
                    {
                        if (diameter <= 8)
                            thickness += 1;
                        else if (diameter <= 10)
                            thickness += 1.4;
                        else if (diameter <= 14)
                            thickness += 2;
                        else if (diameter <= 18)
                            thickness += 2.5;
                        else if (diameter <= 22)
                            thickness += 2.8;
                        else if (diameter > 22)
                            thickness += 3.1;
                    }
                    else
                    {
                        if (diameter <= 10)
                            thickness += .12 * pieceCount;
                        else if (diameter <= 14)
                            thickness += .15 * pieceCount;
                        else if (diameter <= 18)
                            thickness += .18 * pieceCount;
                        else if (diameter <= 22)
                            thickness += .21 * pieceCount;
                        else if (diameter > 22)
                            thickness += .24 * pieceCount;
                    }
                    #endregion


                    // Convert imperial sizes to metric for formula
                    var metricDia = diameter * 25.4;
                    var metricThk = thickness * 25.4;

                    weight = metricDia * 1.01 / 20 * (metricDia * 1.01 / 20) * 3.14 * (metricThk / 10) * 7.8 / 1000 * 2.2046;
                    break;
                #endregion
            }

            return true;
        }

        /// <summary>
        ///     Fixes the size.
        /// </summary>
        /// <param name="num">The number.</param>
        /// <returns>System.Double.</returns>
        public static double FixSize(double num)
        {
            // const double tolerance = 0.051;
            const double tolerance = 0.056;
            var numInt = (int)num;
            var numRemain = num - numInt;

            if (numRemain <= tolerance)
                numRemain = 0;
            else if (numRemain <= 0.250 + tolerance)
                numRemain = 0.250;
            else if (numRemain <= 0.500 + tolerance)
                numRemain = 0.500;
            else if (numRemain <= 0.750 + tolerance)
                numRemain = 0.750;
            else
                numRemain = 1;

            return numInt + numRemain;
        }

        public static void SetDoubleBuffered(System.Windows.Forms.Control c)
        {
            if (System.Windows.Forms.SystemInformation.TerminalServerSession)
                return;



            System.Reflection.PropertyInfo aProp =
                  typeof(System.Windows.Forms.Control).GetProperty(
                        "DoubleBuffered",
                        System.Reflection.BindingFlags.NonPublic |
                        
                        System.Reflection.BindingFlags.Instance);



            aProp.SetValue(c, true, null);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            PDFGenerator PDFG = new PDFGenerator(parent, externalID.Length > 0 ? externalID : parent.CurrentID, externalID.Length > 0);
        }

        private void Print()
        {
            using (var form = new Yes_No_Dialog(parent, "Are you sure you want to print this purchase order?", "Warning", "No", "Yes", 0, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    if (secondThreadFormHandle == IntPtr.Zero)
                    {
                        Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "PRINTING", "PDF")
                        {
                        };
                        form2.HandleCreated += SecondFormHandleCreated;
                        form2.HandleDestroyed += SecondFormHandleDestroyed;
                        form2.RunInNewThread(false);
                    }

                    PDFGenerator PDFG = new PDFGenerator(parent, externalID.Length > 0 ? externalID : parent.CurrentID, externalID.Length > 0, externalID.Length > 0 ? externalID : parent.CurrentID);

                    string pdfPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), (externalID.Length > 0 ? externalID : parent.CurrentID) + ".pdf");

                    ProcessStartInfo info = new ProcessStartInfo();
                    info.Verb = "print";
                    info.FileName = pdfPath;
                    info.CreateNoWindow = true;
                    info.WindowStyle = ProcessWindowStyle.Hidden;

                    Process p = new Process();
                    p.StartInfo = info;
                    p.Start();

                    p.WaitForInputIdle();
                    System.Threading.Thread.Sleep(3000);
                    if (false == p.CloseMainWindow())
                        p.Kill();

                    try
                    {
                        File.Delete(pdfPath);
                    }
                    catch
                    {
                        Console.WriteLine("Error deleting print image file");
                    }

                    if (secondThreadFormHandle != IntPtr.Zero)
                        PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                }
            }
        }

        #region handler thread

        private IntPtr secondThreadFormHandle;

        void SecondFormHandleCreated(object sender, EventArgs e)
        {
            Control second = sender as Control;
            secondThreadFormHandle = second.Handle;
            second.HandleCreated -= SecondFormHandleCreated;
        }

        void SecondFormHandleDestroyed(object sender, EventArgs e)
        {
            Control second = sender as Control;
            secondThreadFormHandle = IntPtr.Zero;
            second.HandleDestroyed -= SecondFormHandleDestroyed;
        }

        const int WM_CLOSE = 0x0010;
        [DllImport("User32.dll")]
        
        extern static IntPtr PostMessage(IntPtr hWnd, int message, IntPtr wParam, IntPtr lParam);
        #endregion

        private void button2_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Print();
            Grey_In();
        }

        private void createPOButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if (parent.Auth == "" || parent.Req == "" || parent.Due == "" || parent.PO == "")
            {
                Form_Message_Box FMB = new Form_Message_Box(parent, "Error: Missing header information", true, -15, this.Location, this.Size);
                FMB.ShowDialog();

            }
            else
            {
                using (var form = new Yes_No_Dialog(parent, "Once generated, you are not able to make any changes to the order. Continue?", "Warning", "No", "Yes", 10, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        // Create order
                        Order o = new Order()
                        {
                            Date = DateTime.Now,
                            Total = parent.Current_Order_Total,
                            DieQty = parent.Solid_List.Count + parent.Hollow_List.Count + parent.Support_List.Count,
                            ID = parent.randomID,
                            Authorizer = parent.Auth,
                            PO = parent.PO,
                            Requisitioner = parent.Req,
                            FreightCost = parent.currentFreightCost,
                            Due = parent.Due
                        };

                        // Set order date to now
                        parent.Solid_List.ForEach(x => x.OrderDate = DateTime.Now);
                        parent.Hollow_List_History.ForEach(x => x.OrderDate = DateTime.Now);
                        parent.Support_List_History.ForEach(x => x.OrderDate = DateTime.Now);

                        // Transfer to historical values
                        parent.Solid_List_History.AddRange(parent.Solid_List);
                        parent.Hollow_List_History.AddRange(parent.Hollow_List);
                        parent.Support_List_History.AddRange(parent.Support_List);

                        parent.Order_List.Add(o);

                        // Save
                        parent.Save_Information();
                        

                        createPOButton.Enabled = false;
                        parent.DisableEdit = true;
                        parent.Background_Save();
                        parent.Invalidate();
                        this.Close();
                    }
                }
            }
            Grey_In();
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            parent.Due = dateTimePicker1.Value.ToShortDateString();
        }

        private void label11_Click(object sender, EventArgs e)
        {

        }
    }
}
    