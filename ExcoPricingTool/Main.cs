using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ExcoPricingTool
{
    public partial class Main : Form
    {

        #region Drag anywhere
        // Main color
        public Color Frame_Color = Color.Red;

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
        #endregion

        // Add tolerance variable to get next biggest die size for metric only
        public double metricTolerance = 0.1; // 0 - no tolerance

        public bool DisableEdit = false;
        public string Encrypt_Key = "EXCO130SPYCANADA";
        public bool ShowOdds = false;
        int Initializing_Height = 0;
        FadeControl TFLP;
        bool Saving_In_Process = false;
        public double Current_Order_Total = 0;

        private List<Button> Delete_Item_Buttons = new List<Button>();
        public Dictionary<DieType, List<DieCharge>> Charge_Dictionary = new Dictionary<DieType, List<DieCharge>>();
        public Dictionary<DieType, List<DieCharge>> Charge_Dictionary_Copy = new Dictionary<DieType, List<DieCharge>>();

        protected override void OnPaint(PaintEventArgs e)
        {

            Delete_Item_Buttons.ForEach(button => button.Image.Dispose());
            Delete_Item_Buttons.ForEach(button => button.Dispose());
            Delete_Item_Buttons.ForEach(button => this.Controls.Remove(button));
            Delete_Item_Buttons = new List<Button>();

            int data_height = 20;
            int start_height = pictureBox2.Height + pictureBox2.Top + 25;
            int start_margin = 35;              // Item
            int margin1 = start_margin + 90;
            int margin2 = margin1 + 90 + (isMetric ? 30 : 0);
            int margin3 = margin1 + 270;
            int height_offset = 0;
            int row_count = 0;

            Color DrawForeColor = Color.White;
            Color BackColor = Color.FromArgb(64, 64, 64);
            Color HighlightColor = Color.FromArgb(76, 76, 76);

            SolidBrush WritingBrush = new SolidBrush(DrawForeColor);
            SolidBrush GreyBrush = new SolidBrush(Color.FromArgb(88, 88, 88));
            SolidBrush GreyBrushIcon = new SolidBrush(SystemColors.ButtonShadow);
            SolidBrush RedBrush = new SolidBrush(Color.LightPink);
            SolidBrush GreenBrush = new SolidBrush(Color.LightGreen);
            Pen p = new Pen(WritingBrush, 1);
            Pen Grey_Pen = new Pen(GreyBrush, 2);
            Pen Grey_Pen_Icon = new Pen(GreyBrush, 1);

            Font f_asterisk = new Font("MS Reference Sans Serif", 8, FontStyle.Regular);
            Font f = new Font("MS Reference Sans Serif", 9, FontStyle.Regular);
            Font f_strike = new Font("MS Reference Sans Serif", 9, FontStyle.Strikeout);
            Font f_total = new Font("MS Reference Sans Serif", 9, FontStyle.Bold);
            Font f_header = new Font("MS Reference Sans Serif", 10, FontStyle.Bold);
            Font f_italic = new Font("MS Reference Sans Serif", 7, FontStyle.Italic);

            double Order_Total = 0;
            int count = 0;

            //unit of measure
            string unit = isMetric ? " mm" : " in";

            // Draw gray header line
            e.Graphics.DrawLine(Grey_Pen, 8, start_height - 15, this.Width - 8, start_height - 15);

            // Draw Solids
            e.Graphics.DrawString("Solid Dies:", f_header, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            row_count++;
            if (Solid_List.Count > 0)
            {
                foreach (Solid s in Solid_List)
                {
                    ToolTip ToolTip1 = new ToolTip();
                    ToolTip1.InitialDelay = 1;
                    ToolTip1.ReshowDelay = 1;

                    Button delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.del;
                    delete_button.Visible = !DisableEdit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 49, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "ds" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Delete " + s.DieNo);
                    this.Controls.Add(delete_button);

                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Visible = true;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.edit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 29, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "es" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Edit " + s.DieNo);
                    this.Controls.Add(delete_button);

                    e.Graphics.DrawString(s.DieNo, f, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(Math.Round(s.Diameter * (isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (isMetric ? 25.4 : 1), 2) + unit, f, WritingBrush, margin2, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString((s.BasePrice > 0 ? "$" + String.Format("{0:0.00}", s.BasePrice) : "Call for quote"), f, WritingBrush, margin3, start_height + height_offset + (row_count * data_height));
                    row_count++; count++;
                    Order_Total += s.BasePrice;

                }
                count = 0;
            }
            else
            {
                e.Graphics.DrawString("There are no solid dies in this order", f, WritingBrush, margin1 - 40, start_height + height_offset + (row_count * data_height));
                row_count++;
            }

            // Draw Hollows
            height_offset += 5;
            e.Graphics.DrawString("Hollow Dies:", f_header, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            row_count++;
            if (Hollow_List.Count > 0)
            {
                foreach (Hollow s in Hollow_List)
                {
                    ToolTip ToolTip1 = new ToolTip();
                    ToolTip1.InitialDelay = 1;
                    ToolTip1.ReshowDelay = 1;

                    Button delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.del;
                    delete_button.Visible = !DisableEdit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 49, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "dh" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Delete " + s.DieNo);
                    this.Controls.Add(delete_button);

                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Visible = true;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.edit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 29, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "eh" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Edit " + s.DieNo);
                    this.Controls.Add(delete_button);

                    e.Graphics.DrawString(s.DieNo, f, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(Math.Round(s.Diameter * (isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (isMetric ? 25.4 : 1), 2) + unit, f, WritingBrush, margin2, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString((s.BasePrice > 0 ? "$" + String.Format("{0:0.00}", s.BasePrice) : "Call for quote"), f, WritingBrush, margin3, start_height + height_offset + (row_count * data_height));
                    row_count++; count++;
                    Order_Total += s.BasePrice;

                }
                count = 0;
            }
            else
            {
                e.Graphics.DrawString("There are no hollow dies in this order", f, WritingBrush, margin1 - 40, start_height + height_offset + (row_count * data_height));
                row_count++;
            }

            // Draw Tooling
            height_offset += 5;
            e.Graphics.DrawString("Support Tooling:", f_header, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            row_count++;
            if (Support_List.Count > 0)
            {
                foreach (Support s in Support_List)
                {
                    ToolTip ToolTip1 = new ToolTip();
                    ToolTip1.InitialDelay = 1;
                    ToolTip1.ReshowDelay = 1;

                    Button delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.del;
                    delete_button.Visible = !DisableEdit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 49, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "dp" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Delete " + s.DieNo);
                    this.Controls.Add(delete_button);

                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Visible = true;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.edit;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(margin1 - 29, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "ep" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Edit " + s.DieNo);
                    this.Controls.Add(delete_button);

                    e.Graphics.DrawString(s.DieNo, f, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(Math.Round(s.Diameter * (isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (isMetric ? 25.4 : 1), 2) + unit, f, WritingBrush, margin2, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString((s.BasePrice > 0 ? "$" + String.Format("{0:0.00}", s.BasePrice) : "Call for quote"), f, WritingBrush, margin3, start_height + height_offset + (row_count * data_height));
                    height_offset += 15;
                    e.Graphics.DrawString("(" + s.DieType + (s.DieType == DieType.Ring ? ": I.D.: " + Math.Round(s.InnerDiameter * (isMetric ? 25.4 : 1), 2) + unit : "") + ")", f_asterisk, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
                    row_count++; count++;
                    Order_Total += s.BasePrice;

                }
                count = 0;
            }
            else
            {
                e.Graphics.DrawString("There are no support tooling in this order", f, WritingBrush, margin1 - 40, start_height + height_offset + (row_count * data_height));
                row_count++;
            }

            // Get total shipment weight ()
            double shipment_weight = 0;
            //Solid_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.OddDiameter, x.OddThickness, 0));
            //Hollow_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.OddDiameter, x.OddThickness, 0));
            //Support_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.OddDiameter, x.OddThickness, 0));
            Solid_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.Diameter, x.Thickness, 0));
            Hollow_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.Diameter, x.Thickness, 0));
            Support_List.ForEach(x => x.Weight = GetFreightWeight("", DieType.Solid, x.Diameter, x.Thickness, 0));

            shipment_weight = Solid_List.Sum(x => x.Weight) + Hollow_List.Sum(x => x.Weight) + Support_List.Sum(x => x.Weight);

            // Add Freight Line
            height_offset += 15;
            e.Graphics.DrawString("Freight Total: $" + String.Format("{0:0.00}", Math.Round(shipment_weight * freightRate, 2)) + " (" + Math.Round(shipment_weight, 2) + " lbs @ $" + String.Format("{0:0.00}", Math.Round(freightRate, 2)) + ")", f, WritingBrush, 20, start_height + height_offset + (row_count * data_height));
            currentFreightCost = Math.Round(shipment_weight * freightRate, 2);
            height_offset += data_height / 2;

            // Add Total Line
            height_offset += 9;
            e.Graphics.DrawString("Order Total: $" + String.Format("{0:0.00}", Math.Round(Order_Total + Math.Round(shipment_weight * freightRate, 2), 2)), f, WritingBrush, 29, start_height + height_offset + (row_count * data_height));
            height_offset += data_height / 2;

            Current_Order_Total = Math.Round(Order_Total + Math.Round(shipment_weight * freightRate, 2), 2);


            // Adjust new height
            this.Height = Initializing_Height + height_offset + (++row_count) * data_height;// +QL_Height_Factor;
            TFLP.Size = new Size(this.Width - 2, this.Height - 2);

            // Draw gray footer line
            e.Graphics.DrawLine(Grey_Pen, 8, addSolidButton.Top - 8, this.Width - 8, addSolidButton.Top - 8);

            // Draw gray separation line
            e.Graphics.DrawLine(Grey_Pen, settingsButton.Left - 12, addSolidButton.Top - 8, settingsButton.Left - 12, this.Height - 8);

            // Disable edit 
            if (DisableEdit) addHollowButton.Enabled = addSolidButton.Enabled = addSupportButton.Enabled = createPOButton.Enabled = false;
            else addHollowButton.Enabled = addSolidButton.Enabled = addSupportButton.Enabled = createPOButton.Enabled = true;

            // Dispose all objects
            p.Dispose();
            Grey_Pen.Dispose();
            Grey_Pen_Icon.Dispose();
            GreenBrush.Dispose();
            RedBrush.Dispose();
            GreyBrush.Dispose();
            GreyBrushIcon.Dispose();
            WritingBrush.Dispose();
            f_asterisk.Dispose();
            f.Dispose();
            f_strike.Dispose();
            f_total.Dispose();
            f_header.Dispose();
            f_italic.Dispose();
            base.OnPaint(e);

        }

        private void dynamic_button_click(object sender, EventArgs e)
        {
            Button b = (Button)sender;

            Grey_Out();
            if (b.Name.StartsWith("d")) // delete
            {
                if (b.Name[1] == 's') // If solid
                {
                    using (var form = new Yes_No_Dialog(this, "Are you sure you wish to delete " + Solid_List[Convert.ToInt32(b.Name.Substring(2))].DieNo + "?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                    {
                        var result = form.ShowDialog();
                        if (result == DialogResult.OK && form.ReturnValue1 == "1")
                        {
                            Solid_List.RemoveAt(Convert.ToInt32(b.Name.Substring(2)));
                        }
                    }
                }
                if (b.Name[1] == 'h') // If hollow
                {
                    using (var form = new Yes_No_Dialog(this, "Are you sure you wish to delete " + Hollow_List[Convert.ToInt32(b.Name.Substring(2))].DieNo + "?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                    {
                        var result = form.ShowDialog();
                        if (result == DialogResult.OK && form.ReturnValue1 == "1")
                        {
                            Hollow_List.RemoveAt(Convert.ToInt32(b.Name.Substring(2)));
                        }
                    }
                }
                if (b.Name[1] == 'p') // If support
                {
                    using (var form = new Yes_No_Dialog(this, "Are you sure you wish to delete " + Support_List[Convert.ToInt32(b.Name.Substring(2))].DieNo + "?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                    {
                        var result = form.ShowDialog();
                        if (result == DialogResult.OK && form.ReturnValue1 == "1")
                        {
                            Support_List.RemoveAt(Convert.ToInt32(b.Name.Substring(2)));
                        }
                    }
                }
            }
            else if (b.Name.StartsWith("e")) // edit
            {
                if (b.Name[1] == 's') // If solid
                {
                    Add_Solid AS = new Add_Solid(this, this.Location, this.Size, Solid_List[(Convert.ToInt32(b.Name.Substring(2)))]);
                    AS.ShowDialog();
                }
                if (b.Name[1] == 'h') // If solid
                {
                    Add_Hollow AH = new Add_Hollow(this, this.Location, this.Size, Hollow_List[(Convert.ToInt32(b.Name.Substring(2)))]);
                    AH.ShowDialog();
                }
                if (b.Name[1] == 'p') // If solid
                {
                    Support Ref_Support = Support_List[(Convert.ToInt32(b.Name.Substring(2)))];
                    switch (Ref_Support.DieType)
                    {
                        case DieType.Feeder:
                            Add_Feeder AF = new Add_Feeder(this, this.Location, this.Size, Ref_Support);
                            AF.ShowDialog();
                            break;
                        case DieType.Backer:
                            Add_Backer AB = new Add_Backer(this, this.Location, this.Size, Ref_Support);
                            AB.ShowDialog();
                            break;
                        case DieType.Bolster:
                            Add_Bolster AL = new Add_Bolster(this, this.Location, this.Size, Ref_Support);
                            AL.ShowDialog();
                            break;
                        case DieType.Subbolster:
                            Add_Sub AS = new Add_Sub(this, this.Location, this.Size, Ref_Support);
                            AS.ShowDialog();
                            break;
                        case DieType.Ring:
                            Add_Ring AR = new Add_Ring(this, this.Location, this.Size, Ref_Support);
                            AR.ShowDialog();
                            break;
                        default:
                            break;
                    }
                }
            }

            Grey_In();
            Invalidate();
        }

        #region Public Parameters
        public Customer Current_Customer = new Customer();
        public List<Solid> Solid_List = new List<Solid>();
        public List<Order> Order_List = new List<Order>();
        public List<Hollow> Hollow_List = new List<Hollow>();
        public List<Support> Support_List = new List<Support>();
        public List<baseCharges> baseCharge_List = new List<baseCharges>();
        public List<itemCharges> itemCharge_List = new List<itemCharges>();
        public List<holeCharges> holeCharge_List = new List<holeCharges>();

        // Historical digits
        public List<Solid> Solid_List_History = new List<Solid>();
        public List<Hollow> Hollow_List_History = new List<Hollow>();
        public List<Support> Support_List_History = new List<Support>();

        public double freightRate = 0;
        public double surchargeRate = 0;
        public double nitrideRate = 0;
        public bool isMetric = false;
        #endregion

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
        }

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public Main(Point g = new Point(), Size s = new Size())
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent();   
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            Set_Form_Color(Frame_Color);
            Initializing_Height = this.Size.Height;
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
        }

        public void Background_Save()
        {
            if (!Saving_In_Process)
            {
                Task.Run(() =>
                {
                    Saving_In_Process = true;
                    Console.WriteLine("Saving.... ");
                    Save_Information();
                    Invalidate();
                    Console.WriteLine("Done Saving!");
                    Saving_In_Process = false;
                });
            }
        }

        private List<string> Save_History()
        {
            List<string> Lines = new List<string>();

            string charge_Str = "";

            foreach (Order o in Order_List)
            {
                Lines.Add("[OrderDate]=" + o.Date + "|"
                + "[ID]=" + o.ID + "|"
                + "[FreightCost]=" + o.FreightCost + "|"
                + "[Total]=" + o.Total + "|"
                + "[Authorizer]=" + o.Authorizer + "|"
                + "[PO]=" + o.PO + "|"
                + "[Requisitioner]=" + o.Requisitioner + "|"
                + "[Due]=" + o.Due + "|"
                + "[Quantity]=" + o.DieQty);
            }

            foreach (Solid s in Solid_List_History)
            {
                charge_Str = "";
                s.Charge_List.Where(y => y.Quantity > 0).ToList().ForEach(x => charge_Str += ",,," + x.Name + "```" + x.Notes + "```" + x.Quantity + "```" + x.Formula);
                Lines.Add("[A]=" + s.DieType+ "|"
                + "[B]=" + s.OrderID+ "|"
                + "[C]=" + s.isMetric+ "|"
                + "[D]=" + s.Diameter+ "|"
                + "[E]=" + s.Thickness+ "|"
                + "[F]=" + s.BasePrice+ "|"
                + "[G]=" + s.Weight+ "|"
                + "[H]=" + s.DieNo+ "|"
                + "[I]=" + s.Location+ "|"
                + "[J]=" + s.HoleCount+ "|"
                + "[K]=" + s.Nitride+ "|"
                + "[L]=" + s.Pocket+ "|"
                + "[M]=" + s.Notes+ "|"
                + "[N]=" + s.OddDiameter+ "|"
                + "[O]=" + s.OddThickness+ "|"
                + "[CA]=" + s.CavityPrice+ "|"
                + "[P]=" + s.FE_Backer_No+ "|"
                + "[Q]=" + s.FE_Backer_Loc+ "|"
                + "[R]=" + s.FE_Feeder_No+ "|"
                + "[S]=" + s.FE_Feeder_Loc+ "|"
                + "[T]=" + s.FE_Bolster_No+ "|"
                + "[SC]=" + s.SurchargePrice+ "|"
                + "[U]=" + s.FE_Bolster_Loc+ "|"
                + "[V]=" + s.FE_SubBol_No+ "|"
                + "[W]=" + s.FE_SubBol_Loc + "|"
                + "[X]=" + (charge_Str.Length > 3 ? charge_Str.Substring(3) : ""));
            }

            foreach (Hollow s in Hollow_List_History)
            {
                charge_Str = "";
                s.Charge_List.Where(y => y.Quantity > 0).ToList().ForEach(x => charge_Str += ",,," + x.Name + "```" + x.Notes + "```" + x.Quantity + "```" + x.Formula);
                Lines.Add("[A]=" + s.DieType+ "|"
                + "[B]=" + s.OrderID+ "|"
                + "[C]=" + s.isMetric+ "|"
                + "[D]=" + s.Diameter+ "|"
                + "[E]=" + s.Thickness+ "|"
                + "[F]=" + s.BasePrice+ "|"
                + "[G]=" + s.Weight + "|"
                + "[SC]=" + s.SurchargePrice + "|"
                + "[H]=" + s.DieNo+ "|"
                + "[I]=" + s.Location+ "|"
                + "[J]=" + s.HoleCount+ "|"
                + "[K]=" + s.Nitride+ "|"
                + "[L]=" + s.Plate_Only+ "|"
                + "[M]=" + s.Mandrel_Only + "|"
                + "[CA]=" + s.CavityPrice + "|"
                + "[N]=" + s.No_Backer+ "|"
                + "[O]=" + s.Notes+ "|"
                + "[P]=" + s.OddDiameter+ "|"
                + "[Q]=" + s.OddThickness+ "|"
                + "[R]=" + s.FE_Backer_No+ "|"
                + "[S]=" + s.FE_Backer_Loc+ "|"
                + "[T]=" + s.FE_Feeder_No+ "|"
                + "[U]=" + s.FE_Feeder_Loc+ "|"
                + "[V]=" + s.FE_Bolster_No+ "|"
                + "[W]=" + s.FE_Bolster_Loc+ "|"
                + "[X]=" + s.FE_SubBol_No+ "|"
                + "[Y]=" + s.FE_SubBol_Loc+ "|"
                + "[Z]=" + (charge_Str.Length > 3 ? charge_Str.Substring(3) : ""));
            }

            foreach (Support s in Support_List_History)
            {
                charge_Str = "";
                s.Charge_List.Where(y => y.Quantity > 0).ToList().ForEach(x => charge_Str += ",,," + x.Name + "```" + x.Notes + "```" + x.Quantity + "```" + x.Formula);
                Lines.Add("[A]=" + s.DieType + "|"
                + "[B]=" + s.OrderID+ "|"
                + "[C]=" + s.isMetric+ "|"
                + "[D]=" + s.Diameter+ "|"
                + "[E]=" + s.InnerDiameter+ "|"
                + "[F]=" + s.Thickness+ "|"
                + "[G]=" + s.BasePrice + "|"
                + "[SC]=" + s.SurchargePrice + "|"
                + "[H]=" + s.Weight+ "|"
                + "[I]=" + s.DieNo + "|"
                + "[CA]=" + s.CavityPrice + "|"
                + "[J]=" + s.Location+ "|"
                + "[K]=" + s.HoleCount+ "|"
                + "[L]=" + s.Notes+ "|"
                + "[M]=" + s.OddDiameter+ "|"
                + "[N]=" + s.OddThickness+ "|"
                + "[O]=" + s.OddInnerDiameter+ "|"
                + "[P]=" + (charge_Str.Length > 3 ? charge_Str.Substring(3) : ""));
            }
            return Lines;
        }

        public void Save_Information()
        {
            List<string> Lines = new List<string>();

            // Save personal settings
            Lines.Add("[FWR]=" + freightRate);
            Lines.Add("[SSR]=" + surchargeRate);
            Lines.Add("[NTR]=" + nitrideRate);
            Lines.Add("[UNI]=" + (isMetric ? "1" : "0"));
            Lines.Add("[SOW]=" + (ShowOdds ? "1" : "0"));

            // Save history
            Lines.AddRange(Save_History());

            // Save config file
            string configPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"  + "\\EPT.config";

            // Try and delete existing file
            try
            {
                File.Delete(configPath);
            }
            catch { }

            File.WriteAllText(configPath, Encrypt_Line(String.Join(Environment.NewLine, Lines)));

            //Encrypt_File(configPath);
        }

        // Get Random Order ID
        Random OrderID_Gen = new Random();
        public string randomID = "";
        public string CurrentID = "";
        public string Req = "";
        public string Auth = "";
        public string PO = "";
        public string Due = "";

        private void Form_Load(object sender, EventArgs e)
        {

            // Mousedown anywhere to drag
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

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

            // Load price list information
            if (File.Exists(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"  + "\\temp.epl"))
            {
                Task.Run(() =>
                {
                    Console.WriteLine("Loading.... ");
                    Load_Information(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"  + "\\temp.epl");
                    Load_Config();
                    Console.WriteLine("Done Loading!");
                    ThreadProcSafe();
                });
            }
            else // else no settings yet
            {
                if (System.Net.NetworkInformation.IPGlobalProperties.GetIPGlobalProperties().DomainName.ToLower().Contains("exco130spy"))
                {
                        this.InvokeEx(f => f.viewHistoryButton.Enabled = true);
                        this.InvokeEx(f => f.viewCurrentOrderButton.Enabled = true);
                        this.InvokeEx(f => f.settingsButton.Enabled = true);
                }
                else // If external use, prompt new window
                {
                    Grey_Out();
                    // Cross thread activation
                    this.InvokeEx(f => f.viewHistoryButton.Enabled = true);
                    this.InvokeEx(f => f.viewCurrentOrderButton.Enabled = true);
                    this.InvokeEx(f => f.settingsButton.Enabled = true);
                    this.InvokeEx(f => companyText.Text = ("").ToUpper());
                    this.InvokeEx(f => companyText.Visible = true);
                    this.InvokeEx(f => Label_Adjust());

                    Settings S = new Settings(this, this.Location, this.Size, true);
                    S.ShowDialog();
                    while (baseCharge_List.Count == 0)
                    {
                        S = new Settings(this, this.Location, this.Size);
                        S.ShowDialog();
                    }
                    Background_Save();
                    Invalidate();
                    Grey_In();
                }
            }

            // Instantiate dictionary
            Charge_Dictionary = new Dictionary<DieType, List<DieCharge>>();

            foreach (DieType dt in Enum.GetValues(typeof(DieType)))
            {
                Charge_Dictionary.Add(dt, new List<DieCharge>());
            }

            // Generate random order only once
            randomID = OrderID_Gen.Next(100000000, 999999999).ToString();
            CurrentID = randomID;
        }


        // This method is executed on the worker thread and makes  
        // a thread-safe call on the TextBox control.  
        public void ThreadProcSafe()
        {
            // Cross thread activation
            this.InvokeEx(f => f.viewHistoryButton.Enabled = true);
            this.InvokeEx(f => f.viewCurrentOrderButton.Enabled = true);
            this.InvokeEx(f => f.settingsButton.Enabled = true);
            this.InvokeEx(f => companyText.Text = ("BUILT FOR " + Current_Customer.Name).ToUpper());
            this.InvokeEx(f => companyText.Visible = true);
            this.InvokeEx(f => Label_Adjust());

            //PDFGenerator PDFG = new PDFGenerator(this, Order_List[0].ID);
        }

        private void Label_Adjust()
        {
            companyText.Left = this.Width + 5000;
            if (companyText.Right > this.Width)
                companyText.Left = this.Width - companyText.Width - 5;
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


        public void Load_Config()
        {
            // Save config file
            string configPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"  + "\\EPT.config";

            if (!File.Exists(configPath))
            {
                File.WriteAllText(configPath, "");
            }


            List<string> Lines = new List<string>();

            var text = File.ReadAllText(configPath).Trim();
            if (text.Length > 0)
            {
                text = Decrypt_Line(text);
            }
            Lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();// Save customers

            foreach (string line in Lines)
            {
                if (line.StartsWith("[FWR"))
                {
                    freightRate = Convert.ToDouble(Parse_Line_Information(line, "FWR"));
                }
                else if (line.StartsWith("[SSR"))
                {
                    surchargeRate = Convert.ToDouble(Parse_Line_Information(line, "SSR"));
                }
                else if (line.StartsWith("[UNI"))
                {
                    isMetric = Parse_Line_Information(line, "UNI") == "1";
                }
                else if (line.StartsWith("[SOW"))
                {
                    ShowOdds = Parse_Line_Information(line, "SOW") == "1";
                }
                else if (line.StartsWith("[NTR"))
                {
                    nitrideRate = Convert.ToDouble(Parse_Line_Information(line, "NTR"));
                }
                else if (line.StartsWith("[OrderDate]="))
                {
                    Order o = new Order()
                    {
                        Date = Convert.ToDateTime(Parse_Line_Information(line, "OrderDate")),
                        ID = Parse_Line_Information(line, "ID"),
                        Total = Convert.ToDouble(Parse_Line_Information(line, "Total")),
                        DieQty = Convert.ToInt32(Parse_Line_Information(line, "Quantity")),
                        FreightCost = Convert.ToDouble(Parse_Line_Information(line, "FreightCost", "|", "0")),
                        Authorizer = Parse_Line_Information(line, "Authorizer"),
                        PO = Parse_Line_Information(line, "PO"),
                        Requisitioner = Parse_Line_Information(line, "Requisitioner"),
                        Due = Parse_Line_Information(line, "Due"),
                    };
                    Order_List.Add(o);
                }
                else if (line.StartsWith("[A]=Solid"))
                {
                    Solid s = new Solid()
                    {
                        OrderID = Parse_Line_Information(line, "B"),
                        DieType = Get_DieType(Parse_Line_Information(line, "A")),
                        isMetric = Parse_Line_Information(line, "C") == "true",
                        Diameter = Convert.ToDouble(Parse_Line_Information(line, "D")),
                        Thickness = Convert.ToDouble(Parse_Line_Information(line, "E")),
                        BasePrice = Convert.ToDouble(Parse_Line_Information(line, "F")),
                        Weight = Convert.ToDouble(Parse_Line_Information(line, "G")),
                        DieNo = Parse_Line_Information(line, "H"),
                        Location = Parse_Line_Information(line, "I"),
                        HoleCount = Convert.ToInt32(Parse_Line_Information(line, "J")),
                        Nitride = Parse_Line_Information(line, "K") == "true",
                        Pocket = Parse_Line_Information(line, "L") == "true",
                        Notes = Parse_Line_Information(line, "M"),
                        OddDiameter = Convert.ToDouble(Parse_Line_Information(line, "N")),
                        CavityPrice = Convert.ToDouble(Parse_Line_Information(line, "CA", "|", "0")),
                        OddThickness = Convert.ToDouble(Parse_Line_Information(line, "O")),
                        FE_Backer_No = Parse_Line_Information(line, "P"),
                        SurchargePrice = Convert.ToDouble(Parse_Line_Information(line, "SC", "|", "0")),
                        FE_Backer_Loc = Parse_Line_Information(line, "Q"),
                        FE_Feeder_No = Parse_Line_Information(line, "R"),
                        FE_Feeder_Loc = Parse_Line_Information(line, "S"),
                        FE_Bolster_No = Parse_Line_Information(line, "T"),
                        FE_Bolster_Loc = Parse_Line_Information(line, "U"),
                        FE_SubBol_No = Parse_Line_Information(line, "V"),
                        FE_SubBol_Loc = Parse_Line_Information(line, "W")
                    };
                    if (Parse_Line_Information(line, "X").Length > 5)
                    {
                        List<string> Temp_DC_List = Parse_Line_Information(line, "X").Split(new string[] { ",,," }, StringSplitOptions.None).ToList();
                        if (Temp_DC_List.Count > 0)
                        {
                            Temp_DC_List.ForEach(x => s.Charge_List.Add(new DieCharge(s.DieType)
                            {
                                Name = x.Split(new string[] { "```" }, StringSplitOptions.None)[0],
                                Notes = x.Split(new string[] { "```" }, StringSplitOptions.None)[1],
                                Quantity = Convert.ToInt32(x.Split(new string[] { "```" }, StringSplitOptions.None)[2]),
                                Dietype = s.DieType,
                                Formula = x.Split(new string[] { "```" }, StringSplitOptions.None)[3]
                            }));
                        }
                    }
                    Solid_List_History.Add(s);
                }
                else if (line.StartsWith("[A]=Hollow"))
                {
                    Hollow s = new Hollow()
                    {
                        OrderID = Parse_Line_Information(line, "B"),
                        DieType = Get_DieType(Parse_Line_Information(line, "A")),
                        isMetric = Parse_Line_Information(line, "C") == "true",
                        Diameter = Convert.ToDouble(Parse_Line_Information(line, "D")),
                        Thickness = Convert.ToDouble(Parse_Line_Information(line, "E")),
                        BasePrice = Convert.ToDouble(Parse_Line_Information(line, "F")),
                        Weight = Convert.ToDouble(Parse_Line_Information(line, "G")),
                        DieNo = Parse_Line_Information(line, "H"),
                        Location = Parse_Line_Information(line, "I"),
                        HoleCount = Convert.ToInt32(Parse_Line_Information(line, "J")),
                        Nitride = Parse_Line_Information(line, "K") == "true",
                        Plate_Only = Parse_Line_Information(line, "L") == "true",
                        Mandrel_Only = Parse_Line_Information(line, "M") == "true",
                        No_Backer = Parse_Line_Information(line, "N") == "true",
                        CavityPrice = Convert.ToDouble(Parse_Line_Information(line, "CA", "|", "0")),
                        Notes = Parse_Line_Information(line, "O"),
                        OddDiameter = Convert.ToDouble(Parse_Line_Information(line, "P")),
                        OddThickness = Convert.ToDouble(Parse_Line_Information(line, "Q")),
                        FE_Backer_No = Parse_Line_Information(line, "R"),
                        FE_Backer_Loc = Parse_Line_Information(line, "S"),
                        SurchargePrice = Convert.ToDouble(Parse_Line_Information(line, "SC", "|", "0")),
                        FE_Feeder_No = Parse_Line_Information(line, "T"),
                        FE_Feeder_Loc = Parse_Line_Information(line, "U"),
                        FE_Bolster_No = Parse_Line_Information(line, "V"),
                        FE_Bolster_Loc = Parse_Line_Information(line, "W"),
                        FE_SubBol_No = Parse_Line_Information(line, "X"),
                        FE_SubBol_Loc = Parse_Line_Information(line, "Y")
                    };
                    if (Parse_Line_Information(line, "Z").Length > 5)
                    {
                        List<string> Temp_DC_List = Parse_Line_Information(line, "Z").Split(new string[] { ",,," }, StringSplitOptions.None).ToList();
                        if (Temp_DC_List.Count > 0)
                        {
                            Temp_DC_List.ForEach(x => s.Charge_List.Add(new DieCharge(s.DieType)
                            {
                                Name = x.Split(new string[] { "```" }, StringSplitOptions.None)[0],
                                Notes = x.Split(new string[] { "```" }, StringSplitOptions.None)[1],
                                Quantity = Convert.ToInt32(x.Split(new string[] { "```" }, StringSplitOptions.None)[2]),
                                Dietype = s.DieType,
                                Formula = x.Split(new string[] { "```" }, StringSplitOptions.None)[3]
                            }));
                        }
                    }
                    Hollow_List_History.Add(s);
                }
                else if (line.StartsWith("[A]="))
                {
                    Support s = new Support()
                    {
                        OrderID = Parse_Line_Information(line, "B"),
                        DieType = Get_DieType(Parse_Line_Information(line, "A")),
                        isMetric = Parse_Line_Information(line, "C") == "true",
                        Diameter = Convert.ToDouble(Parse_Line_Information(line, "D")),
                        InnerDiameter = Convert.ToDouble(Parse_Line_Information(line, "E")),
                        Thickness = Convert.ToDouble(Parse_Line_Information(line, "F")),
                        BasePrice = Convert.ToDouble(Parse_Line_Information(line, "G")),
                        Weight = Convert.ToDouble(Parse_Line_Information(line, "H")),
                        DieNo = Parse_Line_Information(line, "I"),
                        CavityPrice = Convert.ToDouble(Parse_Line_Information(line, "CA", "|", "0")),
                        Location = Parse_Line_Information(line, "J"),
                        HoleCount = Convert.ToInt32(Parse_Line_Information(line, "K")),
                        Notes = Parse_Line_Information(line, "L"),
                        OddDiameter = Convert.ToDouble(Parse_Line_Information(line, "M")),
                        SurchargePrice = Convert.ToDouble(Parse_Line_Information(line, "SC", "|", "0")),
                        OddThickness = Convert.ToDouble(Parse_Line_Information(line, "N")),
                        OddInnerDiameter = Convert.ToDouble(Parse_Line_Information(line, "O")),
                    };
                    List<string> Temp_DC_List = Parse_Line_Information(line, "P").Split(new string[] { ",,," }, StringSplitOptions.None).ToList();
                    if (Parse_Line_Information(line, "P").Length > 5)
                    {
                        if (Temp_DC_List.Count > 0)
                        {
                            Temp_DC_List.ForEach(x => s.Charge_List.Add(new DieCharge(s.DieType)
                            {
                                Name = x.Split(new string[] { "```" }, StringSplitOptions.None)[0],
                                Notes = x.Split(new string[] { "```" }, StringSplitOptions.None)[1],
                                Quantity = Convert.ToInt32(x.Split(new string[] { "```" }, StringSplitOptions.None)[2]),
                                Dietype = s.DieType,
                                Formula = x.Split(new string[] { "```" }, StringSplitOptions.None)[3]
                            }));
                        }
                    }
                    Support_List_History.Add(s);
                }
            }
        }

        public void Load_Information(string filePath)
        {
            List<string> Lines = new List<string>();

            // Reset parameters
            foreach (DieType dt in Enum.GetValues(typeof(DieType)))
            {
                Charge_Dictionary[dt] = new List<DieCharge>();
            }

            baseCharge_List = new List<baseCharges>();
            itemCharge_List = new List<itemCharges>();
            holeCharge_List = new List<holeCharges>();

            if (File.Exists(filePath))
            {
                // Reset parameters
                baseCharge_List = new List<baseCharges>();
                itemCharge_List = new List<itemCharges>();
                holeCharge_List = new List<holeCharges>();

                var text = File.ReadAllText(filePath).Trim();
                text = Decrypt_Line(text);
                Lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();// Save customers

                foreach (string line in Lines)
                {
                    if (line.StartsWith("CU"))
                    {
                        Current_Customer = new Customer()
                        {
                            custCode = Parse_Line_Information(line, "C"),
                            Name = Parse_Line_Information(line, "N"),
                            PLCode = Parse_Line_Information(line, "P")
                        };
                        
                        try
                        {
                            nitrideRate = Convert.ToDouble(Parse_Line_Information(line, "T"));
                        }
                        catch
                        {
                            nitrideRate = 0.65;
                        }
                       //}
                    }
                    else if (line.StartsWith("BC"))
                    {
                        baseCharges bC = new baseCharges()
                        {
                            Price = Convert.ToDouble(Parse_Line_Information(line, "C")),
                            Diameter = Convert.ToDouble(Parse_Line_Information(line, "D")),
                            InnerDiameter = Convert.ToDouble(Parse_Line_Information(line, "I")),
                            Thickness = Convert.ToDouble(Parse_Line_Information(line, "T")),
                            Prefix = Parse_Line_Information(line, "R")
                        };
                        bC.Get_Ring_Price();
                        baseCharge_List.Add(bC);
                    }
                        /*
                    else if (line.StartsWith("IC"))
                    {
                        itemCharge_List.Add(new itemCharges()
                        {
                            flatPrice = Convert.ToDouble(Parse_Line_Information(line, "F")),
                            percPrice = Convert.ToDouble(Parse_Line_Information(line, "E")),
                            chargeName = Parse_Line_Information(line, "N"),
                            Prefix = Parse_Line_Information(line, "R"),
                            maxQty = Convert.ToInt32(Parse_Line_Information(line, "Q"))
                        });
                    }*/
                    else if (line.StartsWith("HC"))
                    {
                        holeCharge_List.Add(new holeCharges()
                        {
                            Price = Convert.ToDouble(Parse_Line_Information(line, "C")),
                            Diameter = Convert.ToDouble(Parse_Line_Information(line, "D")),
                            InnerDiameter = Convert.ToDouble(Parse_Line_Information(line, "I")),
                            Thickness = Convert.ToDouble(Parse_Line_Information(line, "T")),
                            Prefix = Parse_Line_Information(line, "R"),
                            holeQty = Convert.ToInt32(Parse_Line_Information(line, "Q"))
                        });
                    }
                    else if (line.StartsWith("DC"))
                    {
                        DieType dieType = (DieType)System.Enum.Parse(typeof(DieType), Parse_Line_Information(line, "D"));

                        // Add entry if does not exist
                        if (!Charge_Dictionary.ContainsKey(dieType))
                        {
                            Charge_Dictionary.Add(dieType, new List<DieCharge>());
                        }

                        Charge_Dictionary[dieType].Add(new DieCharge(dieType)
                        {
                            Name = Parse_Line_Information(line, "N"),
                            Formula = Parse_Line_Information(line, "F")
                        });
                    }
                }
            }
            else
            {
                Grey_Out();
                Form_Message_Box FMB = new Form_Message_Box(this, "The loaded pricelist is not a valid price list. Please import the correct one", true, 0, this.Location, this.Size);
                FMB.ShowDialog();
                Grey_In();
            }
        }

        public string Parse_Line_Information(string input, string output, string parse_token = "|", string default_string = "")
        {
            string[] Split_Layer_1 = input.Split(new string[] { parse_token }, StringSplitOptions.None);

            foreach (string Info_Pair in Split_Layer_1)
            {
                if (Info_Pair.Contains("[" + output + "]"))
                {
                    return Info_Pair.Split(new string[] { "=" }, StringSplitOptions.None)[1];
                }
            }
            //Console.WriteLine("Potential error with Parse Line info for output: " + output);
            return default_string;
        }

        private void Grey_Out()
        {
            TFLP.Location = new Point(1, 1);
        }

        private void Grey_In()
        {
            TFLP.Location = new Point(1000, 1000);
        }

        private void minimize_button_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void close_button_Click(object sender, EventArgs e)
        {
            this.Dispose();
            this.Close();
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
            //Background_Save();
            if (Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0)
            {
                Grey_Out();
                using (var form = new Yes_No_Dialog(this, "Are you sure you to wish to terminate program?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        this.Close();
                    }
                }
                Grey_In();
            }
            else
            {
                this.Close();
            }
        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Form_Message_Box FMB = new Form_Message_Box(this, "About Exco Pricing Tool:" + Environment.NewLine + Environment.NewLine + "Created by Exco to help you estimate the prices for tooling. Please contact us by phone at 1-(905) 477-1208 ext. 5530", true, 35, this.Location, this.Size);
            FMB.ShowDialog();
            Grey_In();
        }

        private void clearPartsButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if (Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0)
            {
                using (var form = new Yes_No_Dialog(this, "Are you sure you want to clear all parts?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        Solid_List = new List<Solid>();
                        Hollow_List = new List<Hollow>();
                        Support_List = new List<Support>();
                        Invalidate();
                        DisableEdit = false;
                        Req = Auth = PO = Due = "";

                        // Generate random order only once
                        randomID = OrderID_Gen.Next(100000000, 999999999).ToString();
                        CurrentID = randomID;
                    }
                }
            }
            else
            {
                Form_Message_Box FMB = new Form_Message_Box(this, "Error: There are no dies in current order.", true, -15, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }

        private void settingsButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Settings S = new Settings(this, this.Location, this.Size);
            S.ShowDialog();
            Grey_In();
            Background_Save();
            Invalidate();
        }

        // Money text only
        public void textBoxTextChanged(object sender, EventArgs e)
        {
            TextBox Ref_Box = (TextBox)sender;

            if (!(Ref_Box.Text.StartsWith("$")))
            {
                if (Get_Char_Count(Ref_Box.Text, Convert.ToChar("$")) == 1)
                {
                    string temp = Ref_Box.Text;
                    Ref_Box.Text = temp.Substring(1) + temp[0];
                    Ref_Box.SelectionStart = Ref_Box.Text.Length;
                    Ref_Box.SelectionLength = 0;
                }
                else
                {
                    Ref_Box.Text = "$" + Ref_Box.Text;
                }
            }
            else if ((Ref_Box.Text.Length > 1) && ((Get_Char_Count(Ref_Box.Text, Convert.ToChar(".")) > 1) || (Ref_Box.Text[1].ToString() == ".") || (Get_Char_Count(Ref_Box.Text, Convert.ToChar("$")) > 1) || (!((Ref_Box.Text.Substring(Ref_Box.Text.Length - 1).All(char.IsDigit))) && !(Ref_Box.Text[Ref_Box.Text.Length - 1].ToString() == "."))))
            {
                Ref_Box.TextChanged -= new System.EventHandler(textBoxTextChanged);
                Ref_Box.Text = Ref_Box.Text.Substring(0, Ref_Box.Text.Length - 1);
                Ref_Box.SelectionStart = Ref_Box.Text.Length;
                Ref_Box.SelectionLength = 0;
                Ref_Box.TextChanged += new System.EventHandler(textBoxTextChanged);
            }
        }

        // Decimal text only
        public void textBoxTextChanged2(object sender, EventArgs e)
        {
            TextBox Ref_Box = (TextBox)sender;

            if ((Ref_Box.Text.Length > 0) && ((Get_Char_Count(Ref_Box.Text, Convert.ToChar(".")) > 1) || (!((Ref_Box.Text.Substring(Ref_Box.Text.Length - 1).All(char.IsDigit))) && !(Ref_Box.Text[Ref_Box.Text.Length - 1].ToString() == "."))))
            {
                Ref_Box.TextChanged -= new System.EventHandler(textBoxTextChanged2);
                Ref_Box.Text = Ref_Box.Text.Substring(0, Ref_Box.Text.Length - 1);
                Ref_Box.SelectionStart = Ref_Box.Text.Length;
                Ref_Box.SelectionLength = 0;
                Ref_Box.TextChanged += new System.EventHandler(textBoxTextChanged2);
            }
        }

        // Return the token count within string given token
        public int Get_Char_Count(string comparison_text, char reference_char)
        {
            int count = 0;
            foreach (char c in comparison_text)
            {
                if (c == reference_char)
                {
                    count++;
                }
            }
            return count;
        }

        private void addSolidButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Add_Solid AS = new Add_Solid(this, this.Location, this.Size);
            AS.ShowDialog();
            Grey_In();
            Invalidate();
        }


        /// <summary>
        ///     Gets the freight weight.
        /// </summary>
        /// <param name="customercode">The customercode.</param>
        /// <param name="dieType">Type of the die.</param>
        /// <param name="diameter">The diameter.</param>
        /// <param name="thickness">The thickness.</param>
        /// <param name="innerDia">The inner dia.</param>
        /// <param name="weight">The weight.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        public double GetFreightWeight(string customercode, DieType dieType, double diameter, double thickness,
                                             double innerDia)
        {
            //ChangeUnits(ref diameter, ref thickness, ref innerDia);

            double weight = diameter * diameter * thickness * .224;

            if (dieType == DieType.Ring)
                weight -= innerDia * innerDia * thickness * .224;

            return weight;
        }

        public double currentFreightCost = 0;

        private void createPOButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if ((Auth == "" || Req == "" || Due == "" || PO == "") && (Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0))
            {
                Form_Message_Box FMB = new Form_Message_Box(this, "Error: Missing header information", true, -15, this.Location, this.Size);
                FMB.ShowDialog();
                View_Current_Order H = new View_Current_Order(this, this.Location, this.Size, true);
                H.ShowDialog();

            }
            else if (Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0)
            {
                using (var form = new Yes_No_Dialog(this, "Once generated, you are not able to make any changes to the order. Continue?", "Warning", "No", "Yes", 10, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        // Create order
                        Order o = new Order()
                        {
                            Date = DateTime.Now,
                            Total = Current_Order_Total,
                            DieQty = Solid_List.Count + Hollow_List.Count + Support_List.Count,
                            ID = randomID,
                            Authorizer = Auth,
                            PO = PO,
                            Requisitioner = Req,
                            FreightCost = currentFreightCost,
                            Due = Due
                        };

                        // Set order date to now
                        Solid_List.ForEach(x => x.OrderDate = DateTime.Now);
                        Hollow_List_History.ForEach(x => x.OrderDate = DateTime.Now);
                        Support_List_History.ForEach(x => x.OrderDate = DateTime.Now);

                        // Transfer to historical values
                        Solid_List_History.AddRange(Solid_List);
                        Hollow_List_History.AddRange(Hollow_List);
                        Support_List_History.AddRange(Support_List);

                        Order_List.Add(o);

                        // Save
                        Save_Information();

                        createPOButton.Enabled = false;
                        DisableEdit = true;
                        Background_Save();
                        Invalidate();
                    }
                }
            }
            else if (!(Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0))
            {
                Form_Message_Box FMB = new Form_Message_Box(this, "Error: There are no dies in this order.", true, -15, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }

        #region Function dump
        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }
        #endregion

        private void addHollowButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Add_Hollow AH = new Add_Hollow(this, this.Location, this.Size);
            AH.ShowDialog();
            Grey_In();
            Invalidate();
        }

        private void addSupportButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Support_Selector SS = new Support_Selector(this, this.Location, this.Size);
            SS.ShowDialog();
            Grey_In();
        }

        public DieType Get_DieType(string dt)
        {
            return (DieType)System.Enum.Parse(typeof(DieType), dt);
        }

        public string Get_Die_Prefix(DieType dt)
        {
            switch (dt)
            {
                case DieType.Solid:
                    return "DI";
                case DieType.Hollow:
                    return "HO";
                case DieType.Feeder:
                    return "FE";
                case DieType.Bolster:
                    return "BO";
                case DieType.Subbolster:
                    return "SB";
                case DieType.Ring:
                    return "RI";
                case DieType.Backer:
                    return "BA";
                default:
                    return "DI";
            }
        }

        private void viewHistoryButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if (Order_List.Count > 0)
            {
                History H = new History(this, this.Location, this.Size);
                H.ShowDialog();
            }
            else
            {
                Form_Message_Box FMB = new Form_Message_Box(this, "Error: You do not have any order history available.", true, -15, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }

        private void viewCurrentOrderButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if (Hollow_List.Count > 0 || Solid_List.Count > 0 || Support_List.Count > 0)
            {
                View_Current_Order H = new View_Current_Order(this, this.Location, this.Size);
                H.ShowDialog();
            }
            else
            {
                Form_Message_Box FMB = new Form_Message_Box(this, "Error: There are no dies in current order.", true, -15, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }

        private void label22_Click(object sender, EventArgs e)
        {

        }

        private void label19_Click(object sender, EventArgs e)
        {

        }

        public string Encrypt_Line(string line)
        {
            try
            {
                return AESGCM.SimpleEncryptWithPassword(line, "EXCO130SPYaes");
            }
            catch
            {
                Console.WriteLine("Encrypt error");
                return "";
            }
        }

        public string Decrypt_Line(string line)
        {
            try
            {
                return AESGCM.SimpleDecryptWithPassword(line, "EXCO130SPYaes");
            }
            catch
            {
                Console.WriteLine("Decrypt error");
                return "";
            }
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
        public double GetSurchargeWeight(byte weightType, DieType dieType, double diameter, double thickness,
                                               int pieceCount, double weight_)
        {
            double weight = weight_;

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

            return weight;
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
    }

    public static class ISynchronizeInvokeExtensions
    {
        public static void InvokeEx<T>(this T @this, Action<T> action) where T : ISynchronizeInvoke
        {
            if (@this.InvokeRequired)
            {
                @this.Invoke(action, new object[] { @this });
            }
            else
            {
                action(@this);
            }
        }
    }
}
