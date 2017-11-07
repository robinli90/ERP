using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Odbc;

namespace ExcoPricingTool
{
    public partial class Charge_Settings : Form
    {

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

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public Charge_Settings(Main _parent, Point g = new Point(), Size s = new Size())
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2) - 6);
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

            dataGridView1.KeyUp += dataGridView1_KeyUp;

            dataGridView1.ShowCellToolTips = false;

            dataGridView1.CellClick += new DataGridViewCellEventHandler(dataGridView1_CellContentClick);
            dataGridView1.SelectionChanged += new EventHandler(dataGridView1_SelectionChanged);
            dataGridView1.GridColor = Color.White;
            dataGridView1.RowHeadersDefaultCellStyle.BackColor = Color.FromArgb(98, 110, 110);

            #region Add delete buttons
            DataGridViewButtonColumn buttons = new DataGridViewButtonColumn();
            {
                buttons.HeaderText = "";
                buttons.Text = "X";// "🔍";
                buttons.UseColumnTextForButtonValue = true;
                buttons.AutoSizeMode =
                    DataGridViewAutoSizeColumnMode.None;
                buttons.Width = 23;
                buttons.FlatStyle = FlatStyle.Flat;
                buttons.CellTemplate.Style.BackColor = Color.FromArgb(64, 64, 64);
                buttons.CellTemplate.Style.ForeColor = Color.White;
                buttons.DisplayIndex = 2;
            }
            dataGridView1.Columns.Insert(2, buttons);
            #endregion

            dieTypes.SelectedIndexChanged -= dieTypes_SelectedIndexChanged;

            // Populate dies
            foreach (DieType dt in Enum.GetValues(typeof(DieType)))
            {
                dieTypes.Items.Add(dt);
            }

            dieTypes.SelectedIndex = 0;

            Populate_Charges(dieTypes.Text);
            dieTypes.SelectedIndexChanged += dieTypes_SelectedIndexChanged;
        }


        private void Populate_Charges(string DieType)
        {
            DieType dt = (DieType)System.Enum.Parse(typeof(DieType), DieType);

            List<DieCharge> DC_List = parent.Charge_Dictionary[dt];

            dataGridView1.Rows.Clear();

            foreach (DieCharge DC in DC_List)
            {
                dataGridView1.Rows.Add(DC.Name, DC.GetFormula());
            }

            // Add empty row
            dataGridView1.Rows.Add();

            // Remove last delete button
            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                DataGridViewCellStyle style = new DataGridViewCellStyle();
                style.Padding = new Padding(0, 0, (row == dataGridView1.Rows[dataGridView1.Rows.Count - 1] ? 1000 : 0), 0);
                style.BackColor = Color.FromArgb(76, 76, 76);
                style.ForeColor = Color.White;
                row.Cells[2].Style = style;
            }

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            this.dataGridView1.ClearSelection();

            var senderGrid = (DataGridView)sender;

            if (senderGrid.Columns[e.ColumnIndex] is DataGridViewButtonColumn && e.RowIndex >= 0)
            {
                if (e.ColumnIndex == 2 && e.RowIndex >= 0 && e.RowIndex < dataGridView1.Rows.Count - 1)
                {
                    //Grey_Out();
                    //using (var form = new Yes_No_Dialog(parent, "Are you sure you want to remove this charge?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                    //{
                    //    var result = form.ShowDialog();
                    //    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    //    {
                            dataGridView1.Rows.RemoveAt(e.RowIndex);
                            Save_Charges(dieTypes.Text);
                    //    }
                    //}
                    //Grey_In();
                }
            }
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            this.dataGridView1.ClearSelection();
        }

        private void dataGridView1_KeyUp(object sender, KeyEventArgs e)
        {
            // Check if the KeyCode value has the Keys.Enter flag set
            if ((e.KeyCode & Keys.Enter) == Keys.Enter)
            {
                Save_Charges(dieTypes.Text);

                // Add row only if last row is populated completely
                dataGridView1.Rows.Add();

                // Remove last delete button
                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    DataGridViewCellStyle style = new DataGridViewCellStyle();
                    style.Padding = new Padding(0, 0, (row == dataGridView1.Rows[dataGridView1.Rows.Count - 1] ? 1000 : 0), 0);
                    style.BackColor = Color.FromArgb(76, 76, 76);
                    style.ForeColor = Color.White;
                    row.Cells[2].Style = style;
                }

                dataGridView1.CurrentCell = dataGridView1.Rows[dataGridView1.Rows.Count - 1].Cells[0];

                // Prevent the key event from being passed on to the control
                e.Handled = true;
            }
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

        private void helpButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Form_Message_Box FMB = new Form_Message_Box(parent, "Formula for charges:" + 
                                                                Environment.NewLine + 
                                                                "F65 (Flat rate of 65)" + Environment.NewLine +
                                                                "F45 (Flat rate of 45)" + Environment.NewLine +
                                                                "B-0.23 (-23% of base price)" + Environment.NewLine +
                                                                "B0.73 (73% of base price)" + Environment.NewLine
                                                                , true, 35, this.Location, this.Size);
            FMB.ShowDialog();
            Grey_In();

            //180870875
        }

        string Previous_Selected_DieType = "Solid";

        private void dieTypes_SelectedIndexChanged(object sender, EventArgs e)
        {
            Save_Charges(Previous_Selected_DieType);
            Populate_Charges(dieTypes.Text);
            Previous_Selected_DieType = dieTypes.Text;
        }


        private void Save_Charges(string dieType_)
        {
            DieType dieType = (DieType)System.Enum.Parse(typeof(DieType), dieType_);
            List<DieCharge> DC_List = new List<DieCharge>();

            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                if (dataGridView1.Rows.IndexOf(row) < dataGridView1.Rows.Count)
                {
                    try
                    {
                        DieCharge DC = new DieCharge(dieType);
                        DC.Name = row.Cells[0].Value.ToString();
                        DC.Formula = row.Cells[1].Value.ToString();

                        DC_List.Add(DC);
                    }
                    catch
                    {
                    }
                }
            }

            parent.Charge_Dictionary[dieType] = DC_List;
        }

        List<Customer> Customer_List = new List<Customer>();
        ExcoODBC instance = ExcoODBC.Instance;
        Database masterDB = Database.DECADE_MARKHAM;
        string Ref_PLCode = "";
        string Ref_Nitride = "";
        string Ref_CustCode = "";

        private void addSolidButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            using (var form = new Yes_No_Dialog(parent, "Are you sure you wish to import ALL associated charges for current part? This might include a lot of miscellaneous part charges. Continue?", "Warning", "No", "Yes", 45, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    // Select database
                    using (var DBS = new DatabaseSelector(parent, null, "Select Database", this.Location, this.Size, true))
                    {
                        var returnv = DBS.ShowDialog();

                        // If database valid
                        if (returnv == DialogResult.OK && DBS.dbName.Length > 0)
                        {


                            setDatabase(DBS.dbName);// Force form to redraw

                            #region Get All Customers
                            Customer_List = new List<Customer>();
                            string query = "select customercode, name, pricelist from d_customer";
                            instance.Open(masterDB);
                            OdbcDataReader reader = instance.RunQuery(query);
                            while (reader.Read())
                            {
                                Customer c = new Customer();
                                c.custCode = reader[0].ToString().Trim();
                                c.Name = reader[1].ToString().Trim();
                                c.PLCode = reader[2].ToString().Trim();
                                Customer_List.Add(c);
                            }
                            reader.Close();
                            #endregion

                            Application.DoEvents();

                            // Get customer
                            Get_Customers();

                            Grey_Out();
                            if (secondThreadFormHandle == IntPtr.Zero)
                            {
                                Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "IMPORTING", "DATABASE")
                                {
                                };
                                form2.HandleCreated += SecondFormHandleCreated;
                                form2.HandleDestroyed += SecondFormHandleDestroyed;
                                form2.RunInNewThread(false);
                            }

                            // Generate price list
                            Import_Charges();

                            if (secondThreadFormHandle != IntPtr.Zero)
                                PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                            Form_Message_Box FMB = new Form_Message_Box(parent, "Import Successful!", true, -28, this.Location, this.Size);
                            FMB.ShowDialog();
                            Grey_In();
                        }
                    }
                }
            }
            Grey_In();
        }

        private void setDatabase(string db)
        {
            switch (db)
            {
                case "DECADE_MARKHAM":
                    masterDB = Database.DECADE_MARKHAM;
                    break;
                case "DECADE_MICHIGAN":
                    masterDB = Database.DECADE_MICHIGAN;
                    break;
                case "DECADE_TEXAS":
                    masterDB = Database.DECADE_TEXAS;
                    break;
                case "DECADE_COLOMBIA":
                    masterDB = Database.DECADE_COLOMBIA;
                    break;
                default:
                    masterDB = Database.DECADE_MARKHAM;
                    break;
            }
        }

        private void Get_Customers()
        {
            ExcoODBC instance = ExcoODBC.Instance;

            #region Get All Customers
            Customer_List = new List<Customer>();
            string query = "select customercode, name, pricelist from d_customer";
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                Customer c = new Customer();
                c.custCode = reader[0].ToString().Trim();
                c.Name = reader[1].ToString().Trim();
                c.PLCode = reader[2].ToString().Trim();
                Customer_List.Add(c);
            }
            reader.Close();
            #endregion

            // Select database
            using (var DBS = new DatabaseSelector(parent, Customer_List, "Select Customer", this.Location, this.Size, false))
            {
                var returnv = DBS.ShowDialog();

                // If database valid
                if (returnv == DialogResult.OK && DBS.dbName.Length > 0)
                {
                    Ref_CustCode = DBS.dbName.Substring(DBS.dbName.Length - 7, 6);// Force form to redraw
                }
            }
        }


        private void Import_Charges()
        {
            ExcoODBC instance = ExcoODBC.Instance;

            string custname = "";

            #region Get Ref PL Code
            string query = "select pricelist, name from d_customer where customercode = '" + Ref_CustCode + "'";
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                Ref_PLCode = reader[0].ToString().Trim();
                custname = reader[1].ToString().Trim();
            }
            reader.Close();
            #endregion

            itemCharges ic;

            query = "select plcode, prefix, chargename, chargeprice, chargepercentage, maxqty from d_pricelistitemcharges where prefix like '" + Get_Die_Prefix((DieType)System.Enum.Parse(typeof(DieType), dieTypes.Text)) + "' " +
                    "and plcode = '" + Ref_PLCode + "' " + (custname.ToLower().Contains("sapa") ? "and chargename like '%sapa%'" : "and chargename not like '%sapa%'");

            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                ic = new itemCharges();
                ic.chargeName = reader[2].ToString().Trim();
                ic.flatPrice = Convert.ToDouble(reader[3].ToString().Trim());
                ic.percPrice = Convert.ToDouble(reader[4].ToString().Trim());

                if (ic.percPrice > 0)
                {
                    dataGridView1.Rows.Add(ic.chargeName, "B" + (ic.percPrice / 100));
                }
                else
                {
                    dataGridView1.Rows.Add(ic.chargeName, "F" + ic.flatPrice);
                }
            }
            reader.Close();
            dataGridView1.Rows.Add("");

            // Remove last delete button
            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                DataGridViewCellStyle style = new DataGridViewCellStyle();
                style.Padding = new Padding(0, 0, (row == dataGridView1.Rows[dataGridView1.Rows.Count - 1] ? 1000 : 0), 0);
                style.BackColor = Color.FromArgb(76, 76, 76);
                style.ForeColor = Color.White;
                row.Cells[2].Style = style;
            }

            Save_Charges(dieTypes.Text);
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

        private string Get_Die_Prefix(DieType dt)
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

        //clone
        private void button3_Click(object sender, EventArgs e)
        {
            string filename = "";

            System.Windows.Forms.SaveFileDialog saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            saveFileDialog1.Title = "Export Current Charges to File";
            saveFileDialog1.DefaultExt = ".ecf";
            saveFileDialog1.Filter = "Exco Charges File (*.ecf)|*.ecf";
            DialogResult dr = saveFileDialog1.ShowDialog();
            if (dr == DialogResult.OK && saveFileDialog1.FileName.Length > 0)
            {
                filename = saveFileDialog1.FileName;
                //save file using stream.

                List<string> Lines = new List<string>();

                //save charges
                foreach (KeyValuePair<DieType, List<DieCharge>> Die_KVP in parent.Charge_Dictionary)
                {
                    foreach (DieCharge DC in Die_KVP.Value)
                    {
                        Lines.Add("DC" +
                            "|[D]=" + DC.Dietype +
                            "|[N]=" + DC.Name +
                            "|[F]=" + DC.Formula);
                    }
                }

                File.WriteAllText(filename, parent.Encrypt_Line(String.Join(Environment.NewLine, Lines)));
            }
        }

        // load file
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.Title = "Import charges file";
            file.Multiselect = false;
            file.DefaultExt = ".ecf";
            file.Filter = "Exco Charges File (*.ecf)|*.ecf";

            if (file.ShowDialog() == DialogResult.OK)
            {
                Grey_Out();
                Application.DoEvents();

                if (File.Exists(file.FileName))
                {
                    List<string> Lines = new List<string>();

                    var text = File.ReadAllText(file.FileName).Trim();
                    text = parent.Decrypt_Line(text);
                    Lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();// Save customers

                    // Create new instance
                    parent.Charge_Dictionary = new Dictionary<DieType, List<DieCharge>>();

                    foreach (string line in Lines)
                    {
                        if (line.StartsWith("DC"))
                        {
                            DieType dieType = (DieType)System.Enum.Parse(typeof(DieType), parent.Parse_Line_Information(line, "D"));

                            // Add entry if does not exist
                            if (!parent.Charge_Dictionary.ContainsKey(dieType))
                            {
                                parent.Charge_Dictionary.Add(dieType, new List<DieCharge>());
                            }

                            parent.Charge_Dictionary[dieType].Add(new DieCharge(dieType)
                            {
                                Name = parent.Parse_Line_Information(line, "N"),
                                Formula = parent.Parse_Line_Information(line, "F")
                            });
                        }
                    }

                    Populate_Charges(dieTypes.Text);
                }
                Grey_In();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Grey_Out();
            using (var form = new Yes_No_Dialog(parent, "Are you sure you want to load default charges?", "Warning", "No", "Yes", 0, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    parent.Charge_Dictionary = new Dictionary<DieType, List<DieCharge>>();
                    List<DieCharge> DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F75", Name = "Bolts Hardened H13" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F100", Name = "C Route" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B1", Name = "Hardened Blank" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.5", Name = "Heat Sink 50%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B1", Name = "Heat Sink 100%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F50", Name = "Pocket Charge" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.25", Name = "Shut Off Die - Dovetail" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.15", Name = "Shut Off Die - Normal" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F100", Name = "Special Polish" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F100", Name = "Taper Cut Support" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F150", Name = "Triple Skim Cut" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F100", Name = "Wire Relief" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F100", Name = "Zero Bearing" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.05", Name = "Complexity 5%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.1", Name = "Complexity 10%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.15", Name = "Complexity 15%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.2", Name = "Complexity 20%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "B0.3", Name = "Complexity 30%" });
                    DCListTemp.Add(new DieCharge(DieType.Solid) { Formula = "F150", Name = "Wire Support" });
                    parent.Charge_Dictionary.Add(DieType.Solid, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F75", Name = "Bolts Hardened H13" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F0", Name = "Bridge Feeder" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F400", Name = "Butterfly Design" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "C Route" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.1", Name = "Center Feed Design" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Choke" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.25", Name = "D Rung Die" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F200", Name = "Dome Dies" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.25", Name = "Extended Fixed Mandrel" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.05", Name = "Fake Core 5%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B1", Name = "Hardened Blank" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.5", Name = "Heat Sink 50%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B1", Name = "Heat Sink 100%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.25", Name = "Insert for Mandrel" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "0.25", Name = "Insert for Plate" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Per pc. replaceable Mandrel" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F300", Name = "Micro Bridge Charge" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F500", Name = "Mini-spider Insert" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F60", Name = "Nitrogen Grooves Backer" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.25", Name = "Once-piece die" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F150", Name = "Pin Cores" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.05", Name = "Semi-hollow" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.25", Name = "Shutoff Die - Dovetail" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.15", Name = "Shutoff Die - Normal" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Special Polish" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F200", Name = "Spider-web Design" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Taper Cut Support" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F150", Name = "Triple Skim Cut" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Wire Relief" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F150", Name = "Wire Support" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "F100", Name = "Zero Bearing" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.05", Name = "Complexity 5%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.1", Name = "Complexity 10%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.15", Name = "Complexity 15%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.2", Name = "Complexity 20%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.3", Name = "Complexity 30%" });
                    DCListTemp.Add(new DieCharge(DieType.Hollow) { Formula = "B0.05", Name = "Multi-mandrel" });
                    parent.Charge_Dictionary.Add(DieType.Hollow, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Feeder) { Formula = "F75", Name = "Bolts Hardened H13" });
                    parent.Charge_Dictionary.Add(DieType.Feeder, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Backer) { Formula = "F75", Name = "Bolts Hardened H13" });
                    DCListTemp.Add(new DieCharge(DieType.Backer) { Formula = "F60", Name = "Nitrogen Grooves Backer" });
                    DCListTemp.Add(new DieCharge(DieType.Backer) { Formula = "F200", Name = "Taper Cut Backer" });
                    parent.Charge_Dictionary.Add(DieType.Backer, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Bolster) { Formula = "F75", Name = "Bolts Hardened H13" });
                    DCListTemp.Add(new DieCharge(DieType.Bolster) { Formula = "F100", Name = "Nitrogen Grooves Bolster" });
                    parent.Charge_Dictionary.Add(DieType.Bolster, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Subbolster) { Formula = "F75", Name = "Bolts Hardened H13" });
                    DCListTemp.Add(new DieCharge(DieType.Subbolster) { Formula = "F100", Name = "Nitrogen Grooves Bolster" });
                    parent.Charge_Dictionary.Add(DieType.Subbolster, DCListTemp); DCListTemp = new List<DieCharge>();

                    DCListTemp.Add(new DieCharge(DieType.Ring) { Formula = "F60", Name = "Nitrogen Inlet" });
                    DCListTemp.Add(new DieCharge(DieType.Ring) { Formula = "F100", Name = "Internal Keyway" });
                    parent.Charge_Dictionary.Add(DieType.Ring, DCListTemp); DCListTemp = new List<DieCharge>();

                    Populate_Charges(dieTypes.Text);
                }
            }
            Grey_In();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Grey_Out();
            ExcoODBC instance = ExcoODBC.Instance;

            #region Get All Customers
            Customer_List = new List<Customer>();
            string query = "select customercode, name, pricelist from d_customer";
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                Customer c = new Customer();
                c.custCode = reader[0].ToString().Trim();
                c.Name = reader[1].ToString().Trim();
                c.PLCode = reader[2].ToString().Trim();
                Customer_List.Add(c);
            }
            reader.Close();
            #endregion

            string custName = "";

            // Select database
            using (var DBS = new DatabaseSelector(parent, Customer_List, "Select Customer", this.Location, this.Size, false, "SAVE"))
            {
                var returnv = DBS.ShowDialog();

                // If database valid
                if (returnv == DialogResult.OK && DBS.dbName.Length > 0)
                {
                    Ref_CustCode = DBS.dbName.Substring(DBS.dbName.Length - 7, 6);
                    custName = DBS.dbName.Substring(0, (DBS.dbName.Length - 9)).Length > 20 ? DBS.dbName.Substring(0, (DBS.dbName.Length - 9)).Substring(0, 20) : DBS.dbName.Substring(0, (DBS.dbName.Length - 9));
                }
            }

            #region Background save charges to retain later
            // create appData directory
            if (!Directory.Exists(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"))
            {
                Directory.CreateDirectory(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool");
            }

            string rootPath = "EPT-" + Ref_CustCode + "-" + custName + ".ecf";

            // Remove illegal path characters
            string invalid = new string(Path.GetInvalidFileNameChars()) + new string(Path.GetInvalidPathChars());

            foreach (char c in invalid)
            {
                rootPath = rootPath.Replace(c.ToString(), "");
            }

            string combRootPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool\\" + rootPath;

            // Try and delete existing file
            try
            {
                File.Delete(combRootPath);
            }
            catch { }

            List<string> Lines = new List<string>();

            //save charges
            foreach (KeyValuePair<DieType, List<DieCharge>> Die_KVP in parent.Charge_Dictionary)
            {
                foreach (DieCharge DC in Die_KVP.Value)
                {
                    Lines.Add("DC" +
                        "|[D]=" + DC.Dietype +
                        "|[N]=" + DC.Name +
                        "|[F]=" + DC.Formula);
                }
            }

            //File.WriteAllLines(rootPath, Lines);
            File.WriteAllText(combRootPath, parent.Encrypt_Line(String.Join(Environment.NewLine, Lines)));
            #endregion 

            Grey_In();
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

    }
}
