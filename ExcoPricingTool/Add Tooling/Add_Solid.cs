using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ExcoPricingTool
{
    public partial class Add_Solid : Form
    {
        DieType dt = DieType.Solid;

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


        protected override void OnPaint(PaintEventArgs e)
        {
            int start_margin = 35;              // Item
            int margin1 = start_margin + 90;
            int margin2 = margin1 + 120;
            int margin3 = margin2 + 120;

            Color DrawForeColor = Color.White;
            Color BackColor = Color.FromArgb(64, 64, 64);
            Color HighlightColor = Color.FromArgb(76, 76, 76);

            SolidBrush GreyBrush = new SolidBrush(Color.FromArgb(88, 88, 88));
            Pen Grey_Pen = new Pen(GreyBrush, 2);

            // Draw gray footer line
            e.Graphics.DrawLine(Grey_Pen, 8, addSolidButton.Top - 8, this.Width - 8, addSolidButton.Top - 8);
            e.Graphics.DrawLine(Grey_Pen, 8, additionalCharges.Top - 8, this.Width - 8, additionalCharges.Top - 8);

            if (totalLabel.Text.Length > 0)
            {
                e.Graphics.DrawLine(Grey_Pen, 8, surchargeLabel.Top - 8, this.Width - 8, surchargeLabel.Top - 8);
            }

            // Dispose all objects
            Grey_Pen.Dispose();
            GreyBrush.Dispose();
            base.OnPaint(e);
            base.OnPaint(e);

        }
        
        Main parent;
        double MetricFactor = 1;
        Solid Ref_Solid;

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public Add_Solid(Main _parent, Point g = new Point(), Size s = new Size(), Solid Ref_Solid_ = null)
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
            
            if (parent.isMetric)
            {
                MetricFactor = 25.4;
                dim1.Text = dim2.Text = "mm";
            }

            if (Ref_Solid_ != null)
            {
                Ref_Solid = Ref_Solid_;
                addSolidButton.Image = global::ExcoPricingTool.Properties.Resources.save;
                label15.Text = "SAVE";

                // Set current values to text
                string[] name = Ref_Solid.DieNo.Split(new string[] { "--" }, StringSplitOptions.None);
                dieNo.Text = name[0];
                if (name.Count() > 1) copy.Text = name[1];

                location.Text = Ref_Solid.Location;
                dia.Text = (Ref_Solid.Diameter * MetricFactor).ToString();
                thk.Text = (Ref_Solid.Thickness * MetricFactor).ToString();

                nitride.Checked = Ref_Solid.Nitride;
                pocket.Checked = Ref_Solid.Pocket;

                cavities.Text = Ref_Solid.HoleCount.ToString();
                notes = Ref_Solid.Notes.ToString();

                exPart_backerCheck.Checked = Ref_Solid.FE_Backer_No.Length > 0;
                exPart_feederCheck.Checked = Ref_Solid.FE_Feeder_No.Length > 0;
                exPart_bolsterCheck.Checked = Ref_Solid.FE_Bolster_No.Length > 0;
                exPart_subbolsterCheck.Checked = Ref_Solid.FE_SubBol_No.Length > 0;

                exPart_backerPartno.Text = Ref_Solid.FE_Backer_No;
                exPart_feederPartno.Text = Ref_Solid.FE_Feeder_No;
                exPart_bolsterPartno.Text = Ref_Solid.FE_Bolster_No;
                exPart_subbolsterPartno.Text = Ref_Solid.FE_SubBol_No;

                exPart_backerLoc.Text = Ref_Solid.FE_Backer_Loc;
                exPart_feederLoc.Text = Ref_Solid.FE_Feeder_Loc;
                exPart_bolsterLoc.Text = Ref_Solid.FE_Bolster_Loc;
                exPart_subbolsterLoc.Text = Ref_Solid.FE_SubBol_Loc;

                DieCharge_List = Ref_Solid.Charge_List;
            }
        }

        private void Form_Load(object sender, EventArgs e)
        {
            // Mousedown anywhere to drag
            //this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);
            label9.MouseClick += label9_MouseClick;
            dia.Click += dia_Click;
            thk.Click += dia_Click;

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

            addSolidButton.Enabled = !parent.DisableEdit;

            cavities.Items.Add("1");
            cavities.Items.Add("2");
            cavities.Items.Add("3");
            cavities.Items.Add("4");
            cavities.Items.Add("5");
            cavities.Items.Add("6");
            cavities.Items.Add("8");
            cavities.Items.Add("10");
            cavities.Items.Add("12");
            
            cavities.SelectedIndex = 0;

            Loaded = true;

            if (Ref_Solid != null)
            {
                Ref_BaseCharge = getDiaThk(Convert.ToDouble(dia.Text), Convert.ToDouble(thk.Text)) ?? new baseCharges();
                Calculate_Die_Price(true);
                cavities.Text = Ref_Solid.HoleCount.ToString();
            }

            showOdds.Visible = parent.ShowOdds;
            showOddThk.Visible = parent.ShowOdds;

            if (exPart_backerCheck.Checked || exPart_feederCheck.Checked || exPart_bolsterCheck.Checked || exPart_subbolsterCheck.Checked)
            {
                button4.PerformClick();
            }

            panel1.Location = new Point(5, 174);
        }

        private void label9_MouseClick(object sender, MouseEventArgs e)
        {
            if (panel1.Visible)
            {
                closeButton.PerformClick();
            }
            else
            {
                button4.PerformClick();
            }
        }

        private void dia_Click(object sender, EventArgs e)
        {
            TextBox refBox = (TextBox)sender;
            refBox.Text = "";
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
            Grey_Out();
            if (Ref_BaseCharge != null && Ref_Solid == null)
            {
                using (var form = new Yes_No_Dialog(parent, "Are you sure you want to close?", "Warning", "No", "Yes", -15, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        this.Dispose();
                        this.Close();
                    }
                }
            }
            else
            {
                this.Dispose();
                this.Close();
            }
            Grey_In();
        }

        public string notes = "";

        private void clearPartsButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            using (var form = new Yes_No_Dialog(parent, "Are you sure you wish to clear form?", "Warning", "No", "Yes", -12, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    foreach (Control c in this.Controls)
                    {
                        if (!(c is Label || c is CheckBox || c is Button))
                        {
                            c.Text = "";
                        }
                        if (c is CheckBox)
                        {
                            ((CheckBox)c).Checked = false;
                        }
                    }
                    foreach (Control c in this.panel1.Controls)
                    {
                        if (!(c is Label || c is CheckBox || c is Button))
                        {
                            c.Text = "";
                        }
                        if (c is CheckBox)
                        {
                            ((CheckBox)c).Checked = false;
                        }
                    }
                    DieCharge_List = new List<DieCharge>();
                    totalLabel.Text = surchargeLabel.Text = notes = "";
                    if (panel1.Visible)
                    {
                        closeButton.PerformClick();
                    }
                    this.Height = 356;
                }
            }
            Grey_In();
        }

        private void addSolidButton_Click(object sender, EventArgs e)
        {
            if (dieNo.Text.Length > 0 && dia.Text.Length > 0 && thk.Text.Length > 0)
            {
                /*
                 * 
                 * 
                 
                current_cav_price = refHoleCharges.Price * refHoleCharges.holeQty;
                    CavityPrice = current_cav_price,
                 */
                Solid solid = new Solid()
                {
                    OrderID = parent.randomID,
                    DieNo = dieNo.Text + (copy.Text.Length > 0 ? "--" + copy.Text : ""),
                    Diameter = Convert.ToDouble(dia.Text) / MetricFactor,
                    Thickness = Convert.ToDouble(thk.Text) / MetricFactor,
                    OddDiameter = Ref_BaseCharge.Diameter,
                    OddThickness = Ref_BaseCharge.Thickness,
                    HoleCount = Convert.ToInt32(cavities.Text),
                    Location = location.Text,
                    SurchargePrice = parent.GetSurchargeWeight(0, dt, Ref_BaseCharge.Diameter, Ref_BaseCharge.Thickness, 1, 0) * parent.surchargeRate,
                    Notes = notes.Replace(Environment.NewLine, "```"),
                    Nitride = nitride.Checked,
                    Charge_List = DieCharge_List,
                    Pocket = pocket.Checked,
                    CavityPrice = current_cav_price,
                    BasePrice = Calculate_Die_Price(),
                    isMetric = Ref_Solid != null ? Ref_Solid.isMetric : parent.isMetric
                };

                if (exPart_backerLoc.Text.Length > 0 && exPart_backerPartno.Text.Length > 0 && exPart_backerCheck.Checked)
                {
                    solid.FE_Backer_No = exPart_backerPartno.Text;
                    solid.FE_Backer_Loc = exPart_backerLoc.Text;
                }
                if (exPart_feederLoc.Text.Length > 0 && exPart_feederPartno.Text.Length > 0 && exPart_feederCheck.Checked)
                {
                    solid.FE_Feeder_No = exPart_feederPartno.Text;
                    solid.FE_Feeder_Loc = exPart_feederLoc.Text;
                }
                if (exPart_bolsterLoc.Text.Length > 0 && exPart_bolsterPartno.Text.Length > 0 && exPart_bolsterCheck.Checked)
                {
                    solid.FE_Bolster_No = exPart_bolsterPartno.Text;
                    solid.FE_Bolster_Loc = exPart_bolsterLoc.Text;
                }
                if (exPart_subbolsterLoc.Text.Length > 0 && exPart_subbolsterPartno.Text.Length > 0 && exPart_subbolsterCheck.Checked)
                {
                    solid.FE_SubBol_No = exPart_subbolsterPartno.Text;
                    solid.FE_SubBol_Loc = exPart_subbolsterLoc.Text;
                }

                if (Ref_Solid != null)
                {
                    parent.Solid_List.Insert(parent.Solid_List.IndexOf(Ref_Solid), solid);
                    parent.Solid_List.Remove(Ref_Solid);
                }
                else
                {
                    parent.Solid_List.Add(solid);
                }
                this.Close();
            }
            else
            {
                Grey_Out();
                string error_message = "";
                if (dieNo.Text == "")
                {
                    error_message = "Error: Missing Die Number";
                }
                else if (dia.Text == "")
                {
                    error_message = "Error: Missing Diameter";
                }
                else if (thk.Text == "")
                {
                    error_message = "Error: Missing Thickness";
                }
                Form_Message_Box FMB = new Form_Message_Box(parent, error_message, true, -25, this.Location, this.Size);
                FMB.ShowDialog();
                Grey_In();
            }
        }

        baseCharges Ref_BaseCharge;
        holeCharges refHoleCharges;
        bool Loaded = false;

        // Return the next biggest
        public baseCharges getDiaThk(double refDia, double refThk)
        {
            baseCharges Ref_Base = parent.baseCharge_List.FirstOrDefault(x => x.Diameter * MetricFactor >= refDia - (parent.isMetric ? parent.metricTolerance : 0) && x.Thickness * MetricFactor >= refThk - (parent.isMetric ? parent.metricTolerance : 0) && x.Prefix == "DI");

            if (Ref_Base != null)
            {
                showOdds.Text = "(Odd Diameter: " + Ref_Base.Diameter + " inches)";
                showOddThk.Text = "(Odd Thickness: " + Ref_Base.Thickness + " inches)";
            }
            return Ref_Base;
        }

        private void dia_TextChanged(object sender, EventArgs e)
        {
            parent.textBoxTextChanged2(sender, e);
            if (dia.Text.Length > 0 && thk.Text.Length > 0)
            {
                Ref_BaseCharge = getDiaThk(Convert.ToDouble(dia.Text), Convert.ToDouble(thk.Text)) ?? new baseCharges();
                Calculate_Die_Price(true);
            }
        }

        private void thk_TextChanged(object sender, EventArgs e)
        {
            parent.textBoxTextChanged2(sender, e);
            if (dia.Text.Length > 0 && thk.Text.Length > 0)
            {
                Ref_BaseCharge = getDiaThk(Convert.ToDouble(dia.Text), Convert.ToDouble(thk.Text)) ?? new baseCharges();
                Calculate_Die_Price(true);
            }
        }


        private void cavities_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Loaded)
            {
                Calculate_Die_Price();
            }
        }

        public double current_cav_price = 0;

        private double Calculate_Die_Price(bool silent = false)
        {
            if (Loaded)
            {
                this.Height = panel1.Visible ? 512 : 412;
                TFLP.Size = new Size(this.Width - 2, this.Height - 2);

                if (!silent)
                {
                    Grey_Out();
                    Application.DoEvents();

                    if (secondThreadFormHandle == IntPtr.Zero)
                    {
                        Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "CALCULATING", "PRICE")
                        {
                        };
                        form2.HandleCreated += SecondFormHandleCreated;
                        form2.HandleDestroyed += SecondFormHandleDestroyed;
                        form2.RunInNewThread(false);
                    }
                }

                bool Error = false;
                bool Rework = false;
                double price = 0;
                double weight = 0;

                try
                {
                    price = Ref_BaseCharge.Price;
                    current_cav_price = 0;

                    // If base price is 0, error
                    if (price == 0) Error = true;

                    Console.WriteLine(Ref_BaseCharge.ToString());

                    // Get hole charge
                    if (cavities.Text != "1" && ((refHoleCharges != null && refHoleCharges.holeQty != Convert.ToInt32(cavities.Text)) || refHoleCharges == null))
                    {
                        refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == Convert.ToInt32(cavities.Text)) && x.Diameter == Ref_BaseCharge.Diameter && x.Thickness == Ref_BaseCharge.Thickness && x.Prefix == parent.Get_Die_Prefix(dt));
                        price += refHoleCharges.Price * refHoleCharges.holeQty;
                        current_cav_price = refHoleCharges.Price * refHoleCharges.holeQty;
                    }
                    else if (cavities.Text != "1")
                    {
                        price += refHoleCharges.Price * refHoleCharges.holeQty;
                        current_cav_price = refHoleCharges.Price * refHoleCharges.holeQty;
                    }

                    // Get special charges
                    additionalCharges.Text = "";
                    string passText = "";
                    foreach (DieCharge DC in DieCharge_List)
                    {
                        if (DC.Name.ToLower().Contains("rework") && DC.Quantity > 0)
                        {
                            Rework = true;
                            price += DC.GetAdditionalCost(Ref_BaseCharge.Price + current_cav_price); // Only allow one quantity of rework
                            passText += ", " + DC.Name + " (" + DC.Quantity + ")";
                        }
                        else if (DC.Quantity > 0)
                        {
                            price += DC.GetAdditionalCost(Ref_BaseCharge.Price + current_cav_price) * DC.Quantity;
                            passText += ", " + DC.Name + " (" + DC.Quantity + ")";
                        }
                    }
                    if (passText.Length > 2) additionalCharges.Text = passText.Substring(2);
                    if (passText.Length > 150) additionalCharges.ScrollBars = ScrollBars.Vertical;

                    Console.WriteLine("Base Price = " + price);

                    // Get surcharge price 
                    GetSurchargeWeight(0, dt, Ref_BaseCharge.Diameter, Ref_BaseCharge.Thickness, 1, out weight);
                    price += parent.surchargeRate * weight;

                    if (nitride.Checked)
                        price += parent.GetFreightWeight("", dt, Convert.ToDouble(dia.Text) / MetricFactor, Convert.ToDouble(thk.Text) / MetricFactor, 0) * parent.nitrideRate;

                    // Nitride cost off actual size instead of odd size
                    // Get Nitride cost if checked
                    //if (nitride.Checked)
                    //    price += parent.GetFreightWeight("", dt, Ref_BaseCharge.Diameter, Ref_BaseCharge.Thickness, 0) * parent.nitrideRate;

                    if (pocket.Checked)
                        price += 50;

                    surchargeLabel.Text = "Steel Surcharge: $" + String.Format("{0:0.00}", parent.surchargeRate * weight) + " (" + Math.Round(weight, 2) + "lbs @ $" + String.Format("{0:0.00}", parent.surchargeRate) + "/lb)";
                    totalLabel.Text = "Total: $" + String.Format("{0:0.00}", price);

                }
                catch
                {
                    Error = true;
                }

                if (!silent)
                {

                    Grey_In();

                    if (secondThreadFormHandle != IntPtr.Zero)
                        PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                }

                if (Error || (!Rework && (price - parent.surchargeRate * weight) == 0))
                {
                    surchargeLabel.Text = "";
                    totalLabel.Text = "Please call in for quote";
                    return 0;
                }
                else
                {
                    Console.WriteLine("Price = " + price);
                    return price;
                }
            }
            return 0;
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (dia.Text.Length > 0 && thk.Text.Length > 0)
            {
                this.Height = panel1.Visible ? 512 : 412;
                TFLP.Size = new Size(this.Width - 2, this.Height - 2);
                Calculate_Die_Price();
                Invalidate();
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

        private void button2_Click(object sender, EventArgs e)
        {
            close_button.PerformClick();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Grey_Out();
            using (var form = new Add_Notes(parent, notes, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.noteStr.Length > 0)
                {
                    notes = form.noteStr;
                }
            }
            Grey_In();
        }

        // Open
        private void button4_Click(object sender, EventArgs e)
        {
            if (dt == DieType.Solid || dt == DieType.Hollow)
            {
                panel1.Visible = true;
                label12.Top = 318;
                addChargesButton.Top = 318;
                label20.Top = 335;
                additionalCharges.Top = 316;
                this.Height = totalLabel.Text.Length > 0 ? 512 : 452;
                TFLP.Size = new Size(this.Width - 2, this.Height - 2);
            }
        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        // Close
        private void helpButton_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
            label12.Top = 218;
            addChargesButton.Top = 218;
            label20.Top = 235;
            additionalCharges.Top = 216;
            this.Height = totalLabel.Text.Length > 0 ? 412 : 356;
            TFLP.Size = new Size(this.Width - 2, this.Height - 2);
        }

        private void nitride_CheckedChanged(object sender, EventArgs e)
        {
            Calculate_Die_Price(true);
        }

        private void pocket_CheckedChanged(object sender, EventArgs e)
        {
            Calculate_Die_Price(true);
        }

        List<DieCharge> DieCharge_List = new List<DieCharge>();

        private void addChargesButton_Click(object sender, EventArgs e)
        {
            if (Ref_BaseCharge != null)
            {
                if (dia.Text.Length > 0 && thk.Text.Length > 0)
                {
                    Ref_BaseCharge = getDiaThk(Convert.ToDouble(dia.Text), Convert.ToDouble(thk.Text)) ?? new baseCharges();
                }
                Grey_Out();
                using (var form = new Extra_Charges(parent, DieCharge_List,dt, Ref_BaseCharge.Price + current_cav_price, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK)
                    {
                        DieCharge_List = form.Ref_List;
                    }
                }
                Calculate_Die_Price(true);
                Grey_In();
            }
        }
    }
}
