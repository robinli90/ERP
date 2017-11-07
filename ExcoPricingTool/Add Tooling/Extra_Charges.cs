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
    public partial class Extra_Charges : Form
    {

        protected override void OnClosing(CancelEventArgs e)
        {
            this.DialogResult = DialogResult.OK;
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
        /*
         * Resizing form
         * 
        private const int cGrip = 16;      // Grip size
        private const int cCaption = 32;   // Caption bar height;

        protected override void OnPaint(PaintEventArgs e) {
            Rectangle rc = new Rectangle(this.ClientSize.Width - cGrip, this.ClientSize.Height - cGrip, cGrip, cGrip);
            ControlPaint.DrawSizeGrip(e.Graphics, this.BackColor, rc);
            rc = new Rectangle(0, 0, this.ClientSize.Width, cCaption);
            //e.Graphics.FillRectangle(Brushes.DarkBlue, rc);
        }

        protected override void WndProc(ref Message m) 
        {
            if (m.Msg == 0x84) {  // Trap WM_NCHITTEST
                Point pos = new Point(m.LParam.ToInt32() & 0xffff, m.LParam.ToInt32() >> 16);
                pos = this.PointToClient(pos);
                if (pos.Y < cCaption) {
                    m.Result = (IntPtr)2;  // HTCAPTION
                    return;
                }
                if (pos.X >= this.ClientSize.Width - cGrip && pos.Y >= this.ClientSize.Height - cGrip) {
                    m.Result = (IntPtr)17; // HTBOTTOMRIGHT
                    return;
                }
            }
            base.WndProc(ref m);
        }
        */
        DieType Cur_DieType;
        double Cur_BasePrice;
        Main parent;
        public List<DieCharge> Ref_List = new List<DieCharge>();
        public List<DieCharge> Transferred_List = new List<DieCharge>();

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public Extra_Charges(Main _parent, List<DieCharge> ref_list, DieType dt, double BasePrice, Point g = new Point(), Size s = new Size())
        {
            Cur_DieType = dt;
            Cur_BasePrice = BasePrice;
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            Transferred_List = ref_list;
            this.Location = new Point(g.X + 10, g.Y + 10);

            // Create charge list
            foreach (DieCharge dC in parent.Charge_Dictionary[dt])
            {
                Ref_List.Add(dC.Clone());
            }

        }

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

            int count = 0;
            // Set existing charges
            foreach (DieCharge DC in Ref_List)
            {
                DieCharge Ref_DC = Transferred_List.FirstOrDefault(x => x.Name == DC.Name);

                if (Ref_DC != null)
                {
                    DC.Notes = Ref_DC.Notes;
                    DC.Quantity = Ref_DC.Quantity;
                }

                Create_Charge_Entry(DC, count++);
            }
            if (count <= 6) this.Width = this.Width / 2;
            this.Width = this.Width - 20;

            TFLP.Size = new Size(this.Width - 2, this.Height - 2);
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

        List<Label> Label_List = new List<Label>();

        private void Create_Charge_Entry(DieCharge Charge, int Charge_Index)
        {
            if (parent.Charge_Dictionary[Cur_DieType].Count(x => x.Name == Charge.Name) > 0)
            {
                // Define panel
                Panel main = new Panel() { Size = new Size(458, 22) };

                // Define label
                Label title = new Label()
                {
                    Name = "t" + Charge_Index,
                    Text = Charge.Name,
                    BackColor = this.BackColor,
                    ForeColor = Color.White,
                    Location = new Point(4, 3),
                    Size = new Size(185, 18),
                    Font = new Font(this.Font.FontFamily, 9, FontStyle.Regular)
                };

                // define first notes box
                TextBox tB1 = new TextBox()
                {
                    Name = "n" + Charge_Index,
                    BorderStyle = BorderStyle.FixedSingle,
                    Text = Charge.Notes,
                    BackColor = this.BackColor,
                    ForeColor = Color.White,
                    Font = new Font(this.Font.FontFamily, 9, FontStyle.Regular),
                    Size = new Size(126, 20),
                    Location = new Point(201, 1)
                };

                // define first qty box
                TextBox tB2 = new TextBox()
                {
                    Name = "q" + Charge_Index,
                    BorderStyle = BorderStyle.FixedSingle,
                    Text = Charge.Quantity.ToString(),
                    BackColor = this.BackColor,
                    ForeColor = Color.White,
                    Font = new Font(this.Font.FontFamily, 9, FontStyle.Regular),
                    Size = new Size(51, 20),
                    Location = new Point(332, 1),
                    MaxLength = 3
                };

                tB1.TextChanged += tB1_TextChanged;
                tB2.TextChanged += tB2_TextChanged;

                // Define price label
                Label price = new Label()
                {
                    Name = "p" + Charge_Index,
                    Text = "$" + (Charge.Quantity > 0 ? String.Format("{0:0.00}", Charge.Quantity * Charge.GetAdditionalCost(Cur_BasePrice)) : "0"),
                    BackColor = this.BackColor,
                    ForeColor = Charge.Quantity > 0 ? Color.LightGreen : Color.White,
                    Location = new Point(390, 3),
                    AutoSize = true,
                    Font = new Font(this.Font.FontFamily, 8, FontStyle.Regular)
                };

                Label_List.Add(price);

                main.Controls.Add(title);
                main.Controls.Add(tB1);
                main.Controls.Add(tB2);
                main.Controls.Add(price);
                flowLayoutPanel1.Controls.Add(main);

                if (Charge_Index % 2 == 1 && Charge_Index > 2)
                {
                    this.Height += 28;
                    TFLP.Size = new Size(this.Width - 2, this.Height - 2);
                }
            }
            else
            {
                Console.WriteLine("Invalid charge name detected");
            }
        }

        private void tB1_TextChanged(object sender, EventArgs e)
        {
            TextBox RefBox = (TextBox)sender;
            DieCharge RefCharge = Ref_List[Convert.ToInt32(RefBox.Name.Substring(1))];
            RefCharge.Notes = RefBox.Text;
        }

        private void tB2_TextChanged(object sender, EventArgs e)
        {
            TextBox RefBox = (TextBox)sender;
            try
            {
                DieCharge RefCharge = Ref_List[Convert.ToInt32(RefBox.Name.Substring(1))];
                RefCharge.Quantity = Convert.ToInt32(RefBox.Text);

                Label RefLabel = Label_List.First(x => x.Name == "p" + RefBox.Name.Substring(1));

                RefLabel.Text = "$" + String.Format("{0:0.00}", parent.Charge_Dictionary[Cur_DieType].FirstOrDefault(x => x.Name == RefCharge.Name).GetAdditionalCost(Cur_BasePrice) * RefCharge.Quantity);

                if (RefLabel.Text == "$0")
                {
                    RefLabel.ForeColor = Color.White;
                }
                else
                {
                    RefLabel.ForeColor = Color.LightGreen;
                }
            }
            catch
            {
                if (RefBox.Text.Length > 0)
                {
                    Grey_Out();
                    Form_Message_Box FMB = new Form_Message_Box(parent, "Invalid Quantity", true, -20, this.Location, this.Size);
                    FMB.ShowDialog();
                    Grey_In();
                    RefBox.Text = "";
                }
            }
        }



    }
}
