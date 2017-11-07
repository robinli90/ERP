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
using System.Diagnostics;
using System.IO;

namespace ExcoPricingTool
{
    public partial class History : Form
    {

        protected override void OnClosing(CancelEventArgs e)
        {
            parent.Activate();
            base.OnClosing(e);
        }

        private int Entries_Per_Page = 9;
        int Pages_Required = 0;
        int Current_Page = 0;

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
        
        List<Button> Delete_Item_Buttons = new List<Button>();
        List<string> Checked_Items = new List<string>();

        protected override void OnPaint(PaintEventArgs e)
        {
            Delete_Item_Buttons.ForEach(button => button.Image.Dispose());
            Delete_Item_Buttons.ForEach(button => button.Dispose());
            Delete_Item_Buttons.ForEach(button => this.Controls.Remove(button));
            Delete_Item_Buttons = new List<Button>();

            int data_height = 20;
            int start_height = 60;
            int start_margin = 50;              // Item
            int margin1 = start_margin + 105;
            int margin2 = margin1 + 90;
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
            Font f_header = new Font("MS Reference Sans Serif", 9, FontStyle.Bold | FontStyle.Underline);
            Font f_italic = new Font("MS Reference Sans Serif", 7, FontStyle.Italic);

            double Order_Total = 0;
            int count = 0;

            //Draw header
            e.Graphics.DrawString("Order Date", f_header, WritingBrush, start_margin, start_height + height_offset + (row_count * data_height));
            //e.Graphics.DrawString("# of Parts", f_header, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
            e.Graphics.DrawString("PO#", f_header, WritingBrush, margin1 + 20, start_height + height_offset + (row_count * data_height));
            e.Graphics.DrawString("Order Total", f_header, WritingBrush, margin2 + 7, start_height + height_offset + (row_count * data_height));
            row_count++;
            height_offset += 5;

            if (parent.Order_List.Count > 0)
            {
                foreach (Order o in parent.Order_List.GetRange(Current_Page * Entries_Per_Page, (parent.Order_List.Count - Entries_Per_Page * Current_Page) >= Entries_Per_Page ? Entries_Per_Page : (parent.Order_List.Count % Entries_Per_Page)))
                {
                    ToolTip ToolTip1 = new ToolTip();
                    ToolTip1.InitialDelay = 1;
                    ToolTip1.ReshowDelay = 1;

                    Button delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = Checked_Items.Contains(o.ID) ? global::ExcoPricingTool.Properties.Resources.ck : global::ExcoPricingTool.Properties.Resources.unck;
                    delete_button.Visible = true;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(start_margin - 30, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "c" + o.ID;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, (Checked_Items.Contains(o.ID) ? "Deselect" : "Select") + " this order");
                    this.Controls.Add(delete_button);

                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.view;
                    delete_button.Visible = true;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(this.Width - 80, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "v" + o.ID;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "View this order");
                    this.Controls.Add(delete_button);

                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.load;
                    delete_button.Visible = true;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(this.Width - 60, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = o.ID;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Load this order");
                    this.Controls.Add(delete_button);
                    
                    delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ExcoPricingTool.Properties.Resources.del;
                    delete_button.Visible = true;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(this.Width - 40, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "d" + o.ID;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    ToolTip1.SetToolTip(delete_button, "Delete this order");
                    this.Controls.Add(delete_button);

                    e.Graphics.DrawString(o.Date.ToShortDateString(), f, WritingBrush, start_margin + 7, start_height + height_offset + (row_count * data_height));
                    //e.Graphics.DrawString(o.DieQty.ToString(), f, WritingBrush, margin1 + 30 - (o.DieQty > 9 ? 7 : 0), start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString(o.PO, f, WritingBrush, margin1, start_height + height_offset + (row_count * data_height));
                    e.Graphics.DrawString("$" + String.Format("{0:0.00}", o.Total), f, WritingBrush, margin2 + 15, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
            }

            // Draw gray footer line
            e.Graphics.DrawLine(Grey_Pen, 8, clearPartsButton.Top - 8, this.Width - 8, clearPartsButton.Top - 8);

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
            if (b.Name.StartsWith("d")) //delete
            {
                using (var form = new Yes_No_Dialog(parent, "Are you sure you want to delete this order? Action cannot be undone. Continue?", "Warning", "No", "Yes", 10, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        parent.Order_List = parent.Order_List.Where(x => x.ID != b.Name.Substring(1)).ToList();
                        Invalidate();
                        parent.Background_Save();

                        if (parent.Order_List.Count == 0)
                            this.Close();
                    }
                }
            }
            else if (b.Name.StartsWith("v")) //view
            {
                // save current header information
                string h1 = parent.Req;
                string h2 = parent.Auth;
                string h3 = parent.PO;
                string h4 = parent.Due;

                View_Current_Order H = new View_Current_Order(parent, this.Location, this.Size, false, b.Name.Substring(1));
                H.ShowDialog();

                // Restore to original
                parent.Req = h1;
                parent.Auth = h2;
                parent.PO = h3;
                parent.Due = h4;
            }
            else if (b.Name.StartsWith("c")) //check/uncheck
            {
                if (Checked_Items.Contains(b.Name.Substring(1)))
                {
                    Checked_Items.Remove(b.Name.Substring(1));
                }
                else
                {
                    if (!Checked_Items.Contains(b.Name.Substring(1)))
                        Checked_Items.Add(b.Name.Substring(1));
                }
                Invalidate();
            }
            else
            {
                using (var form = new Yes_No_Dialog(parent, "Are you sure you want to load this order? If you haven't created the PO for your current order, it will be lost. Continue?", "Warning", "No", "Yes", 33, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        Order Ref_Order = parent.Order_List.First(x => x.ID == b.Name);
                        parent.Req = Ref_Order.Requisitioner;
                        parent.Auth = Ref_Order.Authorizer;
                        parent.PO = Ref_Order.PO;
                        parent.Due = Ref_Order.Due;
                        parent.CurrentID = b.Name;
                        parent.Solid_List = parent.Solid_List_History.Where(x => x.OrderID == b.Name).ToList();
                        parent.Hollow_List = parent.Hollow_List_History.Where(x => x.OrderID == b.Name).ToList();
                        parent.Support_List = parent.Support_List_History.Where(x => x.OrderID == b.Name).ToList();
                        parent.Invalidate();
                        parent.DisableEdit = true;
                        this.Close();
                    }
                }
            }
            Grey_In();
        }
        
        Main parent;

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public History(Main _parent, Point g = new Point(), Size s = new Size())
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2));
        }


        private void Form_Load(object sender, EventArgs e)
        {
            // Mousedown anywhere to drag
            //this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

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

            parent.Order_List = parent.Order_List.OrderByDescending(x => x.Date).ToList();
            Pages_Required = Convert.ToInt32(Math.Ceiling((decimal)parent.Order_List.Count() / (decimal)Entries_Per_Page));
            next_page_button.Visible = Pages_Required > 1;
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

        private void next_page_button_Click(object sender, EventArgs e)
        {
            if (Current_Page + 1 < Pages_Required)
            {
                Current_Page++;
                back_page_button.Visible = true;
                this.Invalidate();
                if (Pages_Required == Current_Page + 1) next_page_button.Visible = false;
            }
        }

        private void back_page_button_Click(object sender, EventArgs e)
        {
            if (Current_Page >= 1)
            {
                Current_Page--;
                next_page_button.Visible = true;
                this.Invalidate();
                if (0 == Current_Page) back_page_button.Visible = false;
            }
        }

        private void clearPartsButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            using (var form = new Yes_No_Dialog(parent, "Are you sure you want to clear history? This action is irreversable. Continue?", "Warning", "No", "Yes", 10, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    parent.Order_List = new List<Order>();
                    Invalidate();
                    parent.Background_Save();
                    this.Close();
                }
            }
            Grey_In();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Grey_Out();
            if (Checked_Items.Count > 0)
            {
                Application.DoEvents();

                using (var form = new Yes_No_Dialog(parent, "Are you sure you want to create " + Checked_Items.Count + " purchase order PDF(s)?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        if (secondThreadFormHandle == IntPtr.Zero)
                        {
                            Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "GENERATING", "PDF(s)")
                            {
                            };
                            form2.HandleCreated += SecondFormHandleCreated;
                            form2.HandleDestroyed += SecondFormHandleDestroyed;
                            form2.RunInNewThread(false);
                        }

                        Checked_Items.ForEach(x => new PDFGenerator(parent, x, true));
                        //PDFGenerator PDFG = new PDFGenerator(parent, parent.CurrentID, false);

                        if (secondThreadFormHandle != IntPtr.Zero)
                            PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                        deselectAll.PerformClick();
                    }
                }
            }
            else
            {
                Form_Message_Box FMB = new Form_Message_Box(parent, "No orders selected", true, -25, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }

        private void selectALL_Click(object sender, EventArgs e)
        {
            Checked_Items = new List<string>();
            parent.Order_List.Select(x => x.ID).Distinct().ToList().ForEach(y => Checked_Items.Add(y));
            Invalidate();
        }

        private void deselectAll_Click(object sender, EventArgs e)
        {
            Checked_Items = new List<string>();
            Invalidate();
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
            if (Checked_Items.Count > 0)
            {
                Application.DoEvents();

                using (var form = new Yes_No_Dialog(parent, "Are you sure you want to print " + Checked_Items.Count + " purchase order PDF(s)?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                {
                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        if (secondThreadFormHandle == IntPtr.Zero)
                        {
                            Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "PRINTING", "PDF(s)")
                            {
                            };
                            form2.HandleCreated += SecondFormHandleCreated;
                            form2.HandleDestroyed += SecondFormHandleDestroyed;
                            form2.RunInNewThread(false);
                        }

                        foreach (string g in Checked_Items)
                        {
                            PDFGenerator PDFG = new PDFGenerator(parent, g, true, g);

                            string pdfPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), g + ".pdf");

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
                        }

                        if (secondThreadFormHandle != IntPtr.Zero)
                            PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                        deselectAll.PerformClick();
                    }
                }
            }
            else
            {
                Form_Message_Box FMB = new Form_Message_Box(parent, "No orders selected", true, -25, this.Location, this.Size);
                FMB.ShowDialog();
            }
            Grey_In();
        }
    }
}
