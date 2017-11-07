using System;
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
    public partial class Yes_No_Dialog : Form
    {


        protected override void OnClosing(CancelEventArgs e)
        {
            parent.Activate();
            base.OnClosing(e);
        }

        Main parent;
        Size Start_Size = new Size();

        public string ReturnValue1 { get; set; }
        //public string ReturnValue2 { get; set; }

        public Yes_No_Dialog(Main _parent, string Dialog_Message, string Title, string no_button_text = "No", string yes_button_text = "Yes", int grow_height = 0, Point g = new Point(), Size s = new Size())
        {
            //this.Location = spawn_location;
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Start_Size = this.Size;
            Set_Form_Color(parent.Frame_Color);
            no_button.Text = no_button_text;
            yes_button.Text = yes_button_text;
            label1.Text = Dialog_Message;
            label5.Text = Title;

            if (Dialog_Message.Contains("Continuing will reset your current receipt"))
            {
                this.Height += 10;
                close_button.Visible = false;
            }

            if (Dialog_Message.Contains("Are you sure you wish to remove this order?"))
            {
                close_button.Visible = false;
            }
            else
            {
                //this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);
            }

            this.Height += grow_height;

            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
        }

        private void Receipt_Load(object sender, EventArgs e)
        {
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
            //minimize_button.ForeColor = randomColor;
            //close_button.ForeColor = randomColor;
            textBox1.BackColor = randomColor;
            textBox2.BackColor = randomColor;
            textBox3.BackColor = randomColor;
            textBox4.BackColor = randomColor;
        }

        private void yes_button_Click(object sender, EventArgs e)
        {
            this.ReturnValue1 = "1";
            //this.ReturnValue2 = DateTime.Now.ToString(); //example
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void no_button_Click(object sender, EventArgs e)
        {
            this.ReturnValue1 = "0";
            //this.ReturnValue2 = DateTime.Now.ToString(); //example
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
