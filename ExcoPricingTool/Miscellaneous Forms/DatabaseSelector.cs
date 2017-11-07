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
    public partial class DatabaseSelector : Form
    {

        protected override void OnClosing(CancelEventArgs e)
        {
            parent.Activate();
            base.OnClosing(e);
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
        
        Main parent;
        List<Customer> custList;
        bool hasAllCustomersOption = true;

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public DatabaseSelector(Main _parent, List<Customer> custList_, string Label_Text, Point g = new Point(), Size s = new Size(), bool hasAllCustomersOption_ = true, string buttonName = "IMPORT")
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            hasAllCustomersOption = hasAllCustomersOption_;
            parent = _parent;
            custList = custList_;
            Set_Form_Color(parent.Frame_Color);
            label2.Text = Label_Text;
            if (!label2.Text.Contains("atabase"))
            {
                this.Width += 150;
            }
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
            label16.Text = buttonName;

            label16.Left += (6 - buttonName.Length) * 3;
        }


        private void Form_Load(object sender, EventArgs e)
        {

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

            if (label2.Text.Contains("atabase"))
            {
                foreach (Database plant in Enum.GetValues(typeof(Database)))
                {
                    db.Items.Add(plant.ToString());
                }
            }
            else
            {
                if (hasAllCustomersOption)
                {
                    db.Items.Add("All Customers");
                }
                else
                {
                    //label16.Text = "IMPORT";
                }
                custList.OrderBy(x => x.Name).ToList().ForEach(x => db.Items.Add(x.Name + " (" + x.custCode + ")"));
            }

            db.SelectedIndex = 0;
        }


        FadeControl TFLP;
        public string dbName;

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

        private void export_Click(object sender, EventArgs e)
        {
            dbName = db.Text;
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
