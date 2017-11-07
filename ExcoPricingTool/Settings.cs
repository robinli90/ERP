using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO.Compression;
using System.Drawing;
using System.Data.Odbc;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using Microsoft.Win32;
using Excel = Microsoft.Office.Interop.Excel;
using System.DirectoryServices.AccountManagement;


namespace ExcoPricingTool
{
    public partial class Settings : Form
    {
        Database masterDB = Database.DECADE_MARKHAM;

        protected override void OnClosing(CancelEventArgs e)
        {
            parent.Activate();
            base.OnClosing(e);
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

            // Dispose all objects
            Grey_Pen.Dispose();
            GreyBrush.Dispose();
            base.OnPaint(e);
            base.OnPaint(e);

        }

        Main parent;
        public bool showWelcome = false;

        /// <summary>
        /// Spawn in dead center (dialog convection)
        /// </summary>
        /// <param name="_parent"></param>
        /// <param name="g"></param>
        /// <param name="s"></param>
        public Settings(Main _parent, Point g = new Point(), Size s = new Size(), bool showWelcome_ = false)
        {
            this.AutoScaleMode = AutoScaleMode.Font; InitializeComponent(); 
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            parent = _parent;
            Set_Form_Color(parent.Frame_Color);
            this.Location = new Point(g.X + (s.Width / 2) - (this.Width / 2), g.Y + (s.Height / 2) - (this.Height / 2) - 30);

            showWelcome = showWelcome_;
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

            this.Height = 250;

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

            units.Items.Add("Imperial (in)");
            units.Items.Add("Metric (mm)");

            freight.Text = "$" + parent.freightRate.ToString();
            surcharge.Text = "$" + parent.surchargeRate.ToString();
            nitrideRate.Text = "$" + parent.nitrideRate.ToString();

            if (parent.isMetric) units.SelectedIndex = 1;
            else units.SelectedIndex = 0;

            if (parent.ShowOdds)
            {
                label19.Left += 3;
                label19.Text = "HIDE";
            }
            
            // Refresh
            Application.DoEvents();

            if (showWelcome)
            {
                Grey_Out();
                Form_Message_Box FMB = new Form_Message_Box(parent, "This is EXCO's pricing tool. Please import the provided .epl file provided alongside this application to get started!", true, 20, this.Location, this.Size);
                FMB.ShowDialog();
                Grey_In();
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

        private void helpButton_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Form_Message_Box FMB = new Form_Message_Box(parent, "A customer ID should be provided to you with this program. If not, please contact us and we will provide you with this information. Sorry about the inconvenience", true, 35, this.Location, this.Size);
            FMB.ShowDialog();
            Grey_In();
        }

        private void close_button_Click_1(object sender, EventArgs e)
        {
            this.Dispose();
            this.Close();
        }

        private void freight_TextChanged(object sender, EventArgs e)
        {
            parent.textBoxTextChanged(sender, e);
        }

        private void surcharge_TextChanged(object sender, EventArgs e)
        {
            parent.textBoxTextChanged(sender, e);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (freight.Text.Length > 1 && surcharge.Text.Length > 1 && nitrideRate.Text.Length > 1)
            {
                parent.freightRate = Convert.ToDouble(freight.Text.Substring(1));
                parent.surchargeRate = Convert.ToDouble(surcharge.Text.Substring(1));
                parent.isMetric = units.SelectedIndex == 1;
                parent.nitrideRate = Convert.ToDouble(nitrideRate.Text.Substring(1));
                this.Close();
            }
        }


        public List<Customer> Customer_List = new List<Customer>();
        List<baseCharges> baseCharge_List = new List<baseCharges>();
        List<itemCharges> itemCharge_List = new List<itemCharges>();
        List<holeCharges> holeCharge_List = new List<holeCharges>();


        string Ref_PLCode = "";
        string Ref_Nitride = "";
        string Ref_CustCode = "";
        public bool allCustomers = false;

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
            using (var DBS = new DatabaseSelector(parent, Customer_List, "Select Customer", this.Location, this.Size, true, "EXPORT"))
            {
                var returnv = DBS.ShowDialog();

                // If database valid
                if (returnv == DialogResult.OK && DBS.dbName.Length > 0)
                {
                    if (DBS.dbName == "All Customers")
                    {
                        allCustomers = true;
                    }
                    else
                    {
                        Ref_CustCode = DBS.dbName.Substring(DBS.dbName.Length - 7, 6);
                    }
                }
            }
        }

        private bool Generate_Pricelist(string exportPath, string packagingFilePath = "")
        {

            ExcoODBC instance = ExcoODBC.Instance;

            string custName = "";

            #region Get Ref PL Code
            string query = "select pricelist, nitridecost, name from d_customer where customercode = '" + Ref_CustCode + "'";
            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                Ref_PLCode = reader[0].ToString().Trim();
                Ref_Nitride = reader[1].ToString().Trim();
                custName = reader[2].ToString().Trim().Length > 20 ? reader[2].ToString().Trim().Substring(0, 20) : reader[2].ToString().Trim();
            }
            reader.Close();
            #endregion

            #region Get All base item charges
            baseCharge_List = new List<baseCharges>();
            query = "select plcode, prefix, suffix, price from d_pricelistbaseitems where plcode = '" + Ref_PLCode + "'";
            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                baseCharges bc = new baseCharges();
                bc.Prefix = reader[1].ToString().Trim();
                bc.Diameter = getDimension(reader[2].ToString().Trim());
                bc.Thickness = getDimension(reader[2].ToString().Trim(), false);
                if (bc.Prefix == "RI")
                {
                    bc.InnerDiameter = getDimension(reader[2].ToString().Trim(), false, true);
                    bc.Get_Ring_Price();
                }
                bc.Price = Convert.ToDouble(reader[3].ToString().Trim());
                baseCharge_List.Add(bc);
            }
            reader.Close();
            #endregion

            /* MANUAL
            #region Get All item charges
            itemCharge_List = new List<itemCharges>();
            query = "select plcode, prefix, chargename, chargeprice, chargepercentage, maxqty from d_pricelistitemcharges where plcode = '" + Ref_PLCode + "'";
            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                itemCharges ic = new itemCharges();
                ic.Prefix = reader[1].ToString().Trim();
                ic.chargeName = reader[2].ToString().Trim();
                ic.flatPrice = Convert.ToDouble(reader[3].ToString().Trim());
                ic.percPrice = Convert.ToDouble(reader[4].ToString().Trim());
                ic.maxQty = Convert.ToInt32(reader[5].ToString().Trim());
                itemCharge_List.Add(ic);
            }
            reader.Close();
            #endregion
            */

            #region Get All hole charges
            holeCharge_List = new List<holeCharges>();
            query = "select plcode, prefix, suffix, holeqty, holeprice from d_pricelistholecharges where plcode = '" + Ref_PLCode + "'";
            instance.Open(masterDB);
            reader = instance.RunQuery(query);
            while (reader.Read())
            {
                holeCharges hc = new holeCharges();
                hc.Prefix = reader[1].ToString().Trim();
                hc.Diameter = getDimension(reader[2].ToString().Trim());
                hc.Thickness = getDimension(reader[2].ToString().Trim(), false);
                hc.holeQty = Convert.ToInt32(reader[3].ToString().Trim());
                hc.Price = Convert.ToDouble(reader[4].ToString().Trim());
                holeCharge_List.Add(hc);
            }
            reader.Close();
            #endregion

            // Sort by dimensions first before
            baseCharge_List = baseCharge_List.OrderBy(x => x.Diameter).ThenBy(y => y.Thickness).ToList();



            #region Save all information in file!
            List<string> Lines = new List<string>();

            // Save customers
            foreach (Customer c in Customer_List.Where(x => x.custCode == Ref_CustCode).ToList())
            {
                Lines.Add("CU" +
                    "|[N]=" + c.Name +
                    "|[C]=" + c.custCode +
                    "|[T]=" + Ref_Nitride +
                    "|[P]=" + c.PLCode);
            }

            //save base item charges
            foreach (baseCharges bC in baseCharge_List)
            {
                Lines.Add("BC" +
                    "|[C]=" + bC.Price +
                    "|[D]=" + bC.Diameter +
                    "|[T]=" + bC.Thickness +
                    "|[I]=" + bC.InnerDiameter +
                    "|[R]=" + bC.Prefix);
            }

            //save item charges
            foreach (itemCharges iC in itemCharge_List)
            {
                Lines.Add("IC" +
                    "|[N]=" + iC.chargeName +
                    "|[F]=" + iC.flatPrice +
                    "|[E]=" + iC.percPrice +
                    "|[Q]=" + iC.maxQty +
                    "|[R]=" + iC.Prefix);
            }

            //save hole charges
            foreach (holeCharges hC in holeCharge_List)
            {
                Lines.Add("HC" +
                    "|[C]=" + hC.Price +
                    "|[D]=" + hC.Diameter +
                    "|[T]=" + hC.Thickness +
                    "|[I]=" + hC.InnerDiameter +
                    "|[R]=" + hC.Prefix +
                    "|[Q]=" + hC.holeQty);
            }

            #region Check if pre-existing charge dictionary exists
            string rootPath = "EPT-" + Ref_CustCode + "-" + custName + ".ecf";

            // Remove illegal path characters
            string invalid = new string(Path.GetInvalidFileNameChars()) + new string(Path.GetInvalidPathChars());

            foreach (char c in invalid)
            {
                rootPath = rootPath.Replace(c.ToString(), "");
            }

            string combRootPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool\\" + rootPath;

            Dictionary<DieType, List<DieCharge>> ComparingDict = new Dictionary<DieType, List<DieCharge>>();

            if (File.Exists(combRootPath))
            {
                List<string> Lines2 = new List<string>();

                var text = File.ReadAllText(combRootPath).Trim();
                text = parent.Decrypt_Line(text);
                Lines2 = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();// Save customers

                foreach (string line in Lines2)
                {
                    if (line.StartsWith("DC"))
                    {
                        DieType dieType = (DieType)System.Enum.Parse(typeof(DieType), parent.Parse_Line_Information(line, "D"));

                        // Add entry if does not exist
                        if (!ComparingDict.ContainsKey(dieType))
                        {
                            ComparingDict.Add(dieType, new List<DieCharge>());
                        }

                        ComparingDict[dieType].Add(new DieCharge(dieType)
                        {
                            Name = parent.Parse_Line_Information(line, "N"),
                            Formula = parent.Parse_Line_Information(line, "F")
                        });
                    }
                }
            }
            #endregion

            bool isSame = true;
            #region Check if existing charge dictionary is different; if so prompt user if they wish to use this one instead

            if (ComparingDict.Count > 0)
            {
                foreach (DieType dt in Enum.GetValues(typeof(DieType)))
                {
                    // Must have same charge count to be the same
                    try
                    {
                        if (ComparingDict[dt].Count == parent.Charge_Dictionary[dt].Count)
                        {
                            for (int i = 0; i < ComparingDict[dt].Count; i++)
                            {
                                DieCharge refDC = parent.Charge_Dictionary[dt].FirstOrDefault(x => x.Name == ComparingDict[dt][i].Name);

                                if (refDC != null)
                                {
                                    if (refDC.Formula != ComparingDict[dt][i].Formula)
                                    {
                                        isSame = false;
                                        break;
                                    }
                                }
                                else
                                {
                                    isSame = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            isSame = false;
                        }

                        if (!isSame)
                            break;
                    }
                    catch (Exception n)
                    {
                        Console.WriteLine("FATAL ERROR W/ EXPORTED CHARGE FILE; KEY DOES NOT EXIST: " + n);
                    }
                }
            }
            #endregion

            bool useExisting = false;

            Grey_Out();
            if (!isSame && !allCustomers)
            {
                using (var form = new Yes_No_Dialog(parent, "We found an existing saved charge file for this customer that is different from your current charges. Do you wish to use it instead?", "Warning", "No", "Yes", 45, this.Location, this.Size))
                {
                    if (secondThreadFormHandle != IntPtr.Zero)
                        PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                    var result = form.ShowDialog();
                    if (result == DialogResult.OK && form.ReturnValue1 == "1")
                    {
                        useExisting = true;
                    }
                }
            }

            // ********* "ALL CUSTOMERS" AUTOMATICALLY USED THEIR RESPECTIVE SAVED CHARGE FILE (IF EXISTS) 

            //save charges
            foreach (KeyValuePair<DieType, List<DieCharge>> Die_KVP in (useExisting || allCustomers ? ComparingDict : parent.Charge_Dictionary))
            {
                if (useExisting || allCustomers) Console.WriteLine("USING EXISTING CHARGE FILE INSTEAD.........");

                foreach (DieCharge DC in Die_KVP.Value)
                {
                    Lines.Add("DC" +
                        "|[D]=" + DC.Dietype +
                        "|[N]=" + DC.Name +
                        "|[F]=" + DC.Formula);
                }
            }

            rootPath = "EPT-" + Ref_CustCode + "-" + custName + ".epl";

            
            // Remove illegal path characters
            invalid = new string(Path.GetInvalidFileNameChars()) + new string(Path.GetInvalidPathChars());

            foreach (char c in invalid)
            {
                rootPath = rootPath.Replace(c.ToString(), ""); 
            }

            combRootPath = exportPath + "\\" + rootPath;
            // Try and delete existing file
            try
            {
                File.Delete(combRootPath);
            } catch { }

            //File.WriteAllLines(rootPath, Lines);
            File.WriteAllText(combRootPath, parent.Encrypt_Line(String.Join(Environment.NewLine, Lines)));
            #endregion

            #region If Zipping file
            if (packagingFilePath.Length > 0)
            {
                // Try and delete combination folder
                try
                {
                    File.Delete(exportPath + "\\ExcoPricingTool");
                }
                catch
                {
                    Console.WriteLine("Unable to delete zip folder");
                }
                Directory.CreateDirectory(exportPath + "\\ExcoPricingTool");
                File.Copy(packagingFilePath, exportPath + "\\ExcoPricingTool\\ExcoPricingTool.exe", true);
                File.Move(combRootPath, exportPath + "\\ExcoPricingTool\\" + rootPath);

                // Validate only two files in folder before zipping (prevent extra price list) and validate file names
                string[] File_in_dir = Directory.GetFiles( exportPath + "\\ExcoPricingTool\\", "*");

                if (File_in_dir.Count() == 2 && File_in_dir.Count(x => x.Contains(Ref_CustCode)) == 1 && File_in_dir.Count(x => x.Contains(".exe")) == 1)
                {
                    // Try and delete old zip folder
                    try
                    {
                        File.Delete(exportPath + "\\" + rootPath + ".zip");
                    }
                    catch
                    {
                        Console.WriteLine("Unable to delete zip folder");
                    }
                    ZipFile.CreateFromDirectory(exportPath + "\\ExcoPricingTool", exportPath + "\\" + rootPath + ".zip", CompressionLevel.Fastest, true);
                    // Delete new temp folder
                    try
                    {
                        Directory.Delete(exportPath + "\\ExcoPricingTool", true);
                    }
                    catch
                    {
                        Console.WriteLine("Unable to delete temp folder");
                    }
                }
                else
                {
                    Directory.Delete(exportPath + "\\ExcoPricingTool", true);
                    Grey_Out();
                    Form_Message_Box FMB = new Form_Message_Box(parent, "Export file generated has some errors. Please try again.", true, 0, this.Location, this.Size);
                    FMB.ShowDialog();
                    Grey_In();
                    return false;
                }
                #endregion
            }
            else
            {
                recentlyExportedPath = combRootPath;
            }
            return true;
        }

        private double getDimension(string line, bool getDiameter = true, bool getInnerDiameter = false)
        {
            line = line.Substring(2).ToUpper();

            /// Special parsing for RI prefix where there's inner and outer diameter
            if (!line.Contains("-") || getDiameter)
            {
                if (getDiameter) return Convert.ToDouble(line.Split(new string[] { "X" }, StringSplitOptions.None)[0]);
                else return Convert.ToDouble(line.Split(new string[] { "X" }, StringSplitOptions.None)[1]);
            }
            else
            {
                if (getInnerDiameter) return Convert.ToDouble(line.Split(new string[] { "X" }, StringSplitOptions.None)[1].Split(new string[] { "-" }, StringSplitOptions.None)[1]);
                else return Convert.ToDouble(line.Split(new string[] { "X" }, StringSplitOptions.None)[1].Split(new string[] { "-" }, StringSplitOptions.None)[0]);
            }
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

        string recentlyExportedPath = "";

        private void addHollowButton_Click(object sender, EventArgs e)
        {
            allCustomers = false;

            Grey_Out();
            using (var form = new Yes_No_Dialog(parent, "This will generate the master price list for selected customer. It will take a bit of time. Continue?", "Warning", "No", "Yes", 11, this.Location, this.Size))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    Grey_Out();

                    string folderPath = "";

                    FolderBrowserDialog fbd = new FolderBrowserDialog();
                    fbd.Description = "Select the directory you wish to export price list(s) to:";

                    DialogResult result4 = fbd.ShowDialog();

                    if (result == DialogResult.OK)
                    {
                        if (!string.IsNullOrWhiteSpace(fbd.SelectedPath))
                        {
                            folderPath = fbd.SelectedPath;
                        }
                    }

                    string packagingFilePath = "";

                    using (var form45 = new Yes_No_Dialog(parent, "Would you like to package price list with setup files for customer?", "Warning", "No", "Yes", -0, this.Location, this.Size))
                    {
                        var result45 = form45.ShowDialog();
                        if (result45 == DialogResult.OK && form45.ReturnValue1 == "1")
                        {
                            string exePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool.exe";

                            bool getFile = false;
                            if (File.Exists(exePath))
                            {
                                using (var form9 = new Yes_No_Dialog(parent, "We found a setup file for this program. Do you wish to use this?", "Warning", "No", "Yes", 11, this.Location, this.Size))
                                {
                                    var result9 = form9.ShowDialog();
                                    if (result9 == DialogResult.OK && form9.ReturnValue1 == "1")
                                    {
                                        packagingFilePath = exePath;
                                    }
                                    else
                                    {
                                        getFile = true;
                                    }
                                }
                            }
                            else
                            {
                                getFile = true;
                            }

                            if (getFile)
                            {
                                OpenFileDialog file = new OpenFileDialog();
                                file.Title = "Select setup file";
                                file.Multiselect = false;
                                file.DefaultExt = ".exe";
                                file.Filter = "Exco Pricing Setup File (*.exe)|*.exe";

                                if (file.ShowDialog() == DialogResult.OK && file.FileName.Length > 0)
                                {
                                    packagingFilePath = file.FileName;
                                    File.Copy(file.FileName, exePath, true); // overwrite
                                }
                            }
                        }
                    }

                    // Select database
                    using (var DBS = new DatabaseSelector(parent, null, "Select Database", this.Location, this.Size, true, "EXPORT"))
                    {
                        var returnv = DBS.ShowDialog(); 

                        // If database valid
                        if (returnv == DialogResult.OK && DBS.dbName.Length > 0)
                        {
                            setDatabase(DBS.dbName);// Force form to redraw
                            Application.DoEvents();

                            // Get customer
                            Get_Customers();

                            Cursor.Current = Cursors.WaitCursor;


                            // Check if really want to generate all customers
                            if (allCustomers)
                            {

                                using (var form45 = new Yes_No_Dialog(parent, "Are you sure you wish to generate for all customers? This might take a couple of hours. Continue?", "Warning", "No", "Yes", 10, this.Location, this.Size))
                                {
                                    var result45 = form45.ShowDialog();
                                    if (result45 == DialogResult.OK && form45.ReturnValue1 == "1")
                                    {
                                        if (secondThreadFormHandle == IntPtr.Zero)
                                        {
                                            Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "GENERATING", "PRICE LIST")
                                            {
                                            };
                                            form2.HandleCreated += SecondFormHandleCreated;
                                            form2.HandleDestroyed += SecondFormHandleDestroyed;
                                            form2.RunInNewThread(false);
                                        }

                                        foreach (Customer c in Customer_List)
                                        {
                                            Ref_CustCode = c.custCode;
                                            Generate_Pricelist(folderPath, packagingFilePath);
                                        }

                                        if (secondThreadFormHandle != IntPtr.Zero)
                                            PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                                        Form_Message_Box FMB = new Form_Message_Box(parent, "Export Successful!", true, -28, this.Location, this.Size);
                                        FMB.ShowDialog();
                                    }
                                }
                            }
                            else
                            {
                                if (secondThreadFormHandle == IntPtr.Zero)
                                {
                                    Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "GENERATING", "PRICE LIST")
                                    {
                                    };
                                    form2.HandleCreated += SecondFormHandleCreated;
                                    form2.HandleDestroyed += SecondFormHandleDestroyed;
                                    form2.RunInNewThread(false);
                                }


                                // Generate price list
                                if (Generate_Pricelist(folderPath, packagingFilePath))
                                {
                                    if (secondThreadFormHandle != IntPtr.Zero)
                                        PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                                    Form_Message_Box FMB = new Form_Message_Box(parent, "Export Successful!", true, -28, this.Location, this.Size);
                                    FMB.ShowDialog();
                                }
                                else
                                {
                                    if (secondThreadFormHandle != IntPtr.Zero)
                                        PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                                }
                            }

                            Grey_In();
                        }
                    }
                }
            }
            Grey_In();
        }

        private void addSolidButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();

            string filePath = "";
            
            if (recentlyExportedPath.Length > 0)
            {
                Grey_Out();
                using (var form45 = new Yes_No_Dialog(parent, "You recently exported a pricelist. Do you want to import it?", "Warning", "No", "Yes", 0, this.Location, this.Size))
                {
                    var result45 = form45.ShowDialog();
                    if (result45 == DialogResult.OK && form45.ReturnValue1 == "1")
                    {
                        filePath = recentlyExportedPath;
                    }
                }
                Grey_In();
            }

            if (filePath.Length == 0)
            {
                file.Title = "Import information file";
                file.Multiselect = false;
                file.DefaultExt = ".epl";
                file.Filter = "Exco Pricing File (*.epl)|*.epl";
                if (file.ShowDialog() == DialogResult.OK)
                    filePath = file.FileName;
            }

            if (filePath.Length > 0)
            {
                Grey_Out();
                Application.DoEvents();

                Cursor.Current = Cursors.WaitCursor;

                if (secondThreadFormHandle == IntPtr.Zero)
                {
                    Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "IMPORTING", "INFORMATION")
                    {
                    };
                    form2.HandleCreated += SecondFormHandleCreated;
                    form2.HandleDestroyed += SecondFormHandleDestroyed;
                    form2.RunInNewThread(false);
                }

                parent.Load_Information(filePath);

                if (secondThreadFormHandle != IntPtr.Zero)
                    PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                
                // create appData directory
                if (!Directory.Exists(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool"))
                {
                    Directory.CreateDirectory(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool");
                }

                File.Copy(filePath, Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ExcoPricingTool" + "\\temp.epl", true);
                try
                {
                    File.Delete(filePath);
                    Form_Message_Box FMB = new Form_Message_Box(parent, "Import Successful!", true, -28, this.Location, this.Size);
                    FMB.ShowDialog();
                    Grey_In();
                    parent.ThreadProcSafe();
                }
                catch
                {
                }

                this.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Grey_Out();

            using (var form = new Yes_No_Dialog(parent, "Choose which price list style to export:", "", "Entire PL", "Historical PL", -0, this.Location, this.Size))
            {
                if (secondThreadFormHandle != IntPtr.Zero)
                    PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                var result = form.ShowDialog();
                if (result == DialogResult.OK && form.ReturnValue1 == "1")
                {
                    garyAddition = false;
                }
                else if (result == DialogResult.OK && form.ReturnValue1 == "0")
                {
                    garyAddition = true;
                }
                else
                {
                    goto End;
                }
            }

            Application.DoEvents();

            if (secondThreadFormHandle == IntPtr.Zero)
            {
                Loading_Form form2 = new Loading_Form(parent, this.Location, this.Size, "GENERATING", "EXCEL P.L.")
                {
                };
                form2.HandleCreated += SecondFormHandleCreated;
                form2.HandleDestroyed += SecondFormHandleDestroyed;
                form2.RunInNewThread(false);
            }

            Write_Excel();

            if (secondThreadFormHandle != IntPtr.Zero)
                PostMessage(secondThreadFormHandle, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

            End: ;
            Grey_In();

        }

        #region Excel export temporary

        private void Write_Excel()
        {

            // create excel object
            Excel.Application excel = new Excel.Application();
            object misValue = System.Reflection.Missing.Value;
            Excel.Workbook book = excel.Workbooks.Add(misValue);

            // Void pre-existing pages
            while (book.Worksheets.Count > 1)
            {
                ((Excel.Worksheet)(book.Worksheets[1])).Delete();
            }
            Excel.Worksheet sheet = book.Worksheets[1];
            sheet.Name = "Price List Report";

            int row = 1;

            // insert title
            sheet.Cells[1, 1] = "Price List Report";
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 56;
            sheet.Cells.get_Range("A1", "N1").Merge();
            row++;
            sheet.Cells[2, 1] = "Built for " + parent.Current_Customer.Name + " (" + parent.Current_Customer.custCode + ")";
            sheet.Cells.get_Range("A2").Font.Italic = true;
            sheet.Cells.get_Range("A2").Font.Size = 10;
            sheet.Cells.get_Range("A2").Font.ColorIndex = 56;
            sheet.Cells.get_Range("A2", "N2").Merge();
            row++;
            row++;

            // write header
            WriteHeader(ref sheet, ref row);

            // adjust alignment first before changing specific cells
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;

            // write information
            WriteSpreadsheet(ref sheet, ref row);

            // adjust style
            sheet.Cells.Columns.AutoFit();

            // Fix first row
            sheet.Application.ActiveWindow.SplitRow = 4;
            //sheet.Application.ActiveWindow.SplitColumn = 2;
            sheet.Application.ActiveWindow.FreezePanes = true;

            // Now apply autofilter
            Excel.Range firstRow = (Excel.Range)sheet.Rows[4];


            string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "Price List Report (gen. on " + DateTime.Now.ToString("MM-dd-yyyy HH-mm") + ").xlsx");
            try
            {
                try
                {
                    if (File.Exists(path)) File.Delete(path);
                    book.SaveAs(path, Excel.XlFileFormat.xlOpenXMLWorkbook);
                }
                catch
                {
                }
                excel.Quit();
                Marshal.ReleaseComObject(sheet);
                Marshal.ReleaseComObject(book);
                Marshal.ReleaseComObject(excel);
                sheet = null;
                book = null;
                excel = null;
                // Garbage collection
                System.GC.GetTotalMemory(false);
                System.GC.Collect();
                System.GC.WaitForPendingFinalizers();
                System.GC.Collect();
                System.GC.GetTotalMemory(true);
                System.Diagnostics.Process.Start(path);
            }
            catch
            {
            }
        }

        private void WriteHeader(ref Excel.Worksheet sheet, ref int row)
        {
            // header
            int col = 1;

            sheet.Cells[row, col++] = "Prefix";
            sheet.Cells[row, col++] = "Dia";
            sheet.Cells[row, col++] = "Thk";
            sheet.Cells[row, col++] = "Freight Wght";
            sheet.Cells[row, col++] = "Surcharge Wght";
            sheet.Cells[row, col++] = "1 Hole";
            sheet.Cells[row, col++] = "2 Hole";
            sheet.Cells[row, col++] = "3 Hole";
            sheet.Cells[row, col++] = "4 Hole";
            sheet.Cells[row, col++] = "5 Hole";
            sheet.Cells[row, col++] = "6 Hole";
            sheet.Cells[row, col++] = "8 Hole";
            sheet.Cells[row, col++] = "10 Hole";
            sheet.Cells[row, col++] = "12 Hole";

            Excel.Range range = sheet.Cells.get_Range("A" + row.ToString(), Get_Column_Letter(col) + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 13;
            range.Font.ColorIndex = 48;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            row++;
        }

        bool garyAddition = true;

        private void WriteSpreadsheet(ref Excel.Worksheet sheet, ref int row)
        {

            int col = 1;

            List<string> Error_Log = new List<string>();

            ExcoODBC instance = ExcoODBC.Instance;

            string query;

            if (!garyAddition)
            {
                query = @"select distinct b.description from d_order as a inner join d_orderitem as b on a.ordernumber = b.ordernumber where a.customercode = '" + parent.Current_Customer.custCode + "' and "
                + @"(b.description like 'BACKER%' OR "
                + @"b.description like 'SOLID%' OR "
                + @"b.description like 'HOLLOW%' OR "
                + @"b.description like 'FEEDER%' OR "
                + @"b.description like 'BOLSTER%' OR "
                + @"b.description like 'SUB%')";
            }
            else
            {
                //get the Whole price list instead
                query = @"select * from d_pricelistbaseitems where plcode='DFT' and suffix like 'I%'";// and prefix='DI'";
            }

            instance.Open(masterDB);
            OdbcDataReader reader = instance.RunQuery(query);
            while (reader.Read())
            {
                try
                {
                    DieType refDieType;
                    double refDia;
                    double refThk;

                    if (!garyAddition)
                    {
                        string description = reader[0].ToString().Trim();
                        switch (description.Substring(0, 6))
                        {
                            case "BACKER":
                                refDieType = DieType.Backer;
                                break;
                            case "SOLID ":
                                refDieType = DieType.Solid;
                                break;
                            case "HOLLOW":
                                refDieType = DieType.Hollow;
                                break;
                            case "FEEDER":
                                refDieType = DieType.Feeder;
                                break;
                            case "BOLSTE":
                                refDieType = DieType.Bolster;
                                break;
                            default:
                                refDieType = DieType.Subbolster;
                                break;
                        }
                        refDia = Convert.ToDouble(description.Split(new string[] { " " }, StringSplitOptions.None)[(refDieType == DieType.Solid ||
                                        refDieType == DieType.Hollow) ? 2 : 1]);

                        refThk = Convert.ToDouble(description.Split(new string[] { " " }, StringSplitOptions.None)[(refDieType == DieType.Solid ||
                                        refDieType == DieType.Hollow) ? 4 : 3]);
                    }
                    else
                    {
                       // get the Whole price list instead
                       string description = reader[2].ToString().Trim();
                       switch (description)
                       {
                           case "BA":
                               refDieType = DieType.Backer;
                               break;
                           case "DI":
                               refDieType = DieType.Solid;
                               break;
                           case "HO":
                               refDieType = DieType.Hollow;
                               break;
                           case "FE":
                               refDieType = DieType.Feeder;
                               break;
                           case "BO":
                               refDieType = DieType.Bolster;
                               break;
                           default:
                               refDieType = DieType.Subbolster;
                               break;
                       }
                       string suffix = reader[3].ToString().Trim();

                       refDia = Convert.ToDouble(suffix.Substring(2,6));
                       refThk = Convert.ToDouble(suffix.Substring(11,6));
                    }

                    baseCharges RefBC = parent.baseCharge_List.FirstOrDefault(x => x.Prefix == parent.Get_Die_Prefix(refDieType) &&
                                                                          x.Diameter == refDia && x.Thickness == refThk);

                    if (RefBC != null)
                    {
                        int cavity = 1;
                        holeCharges refHoleCharges = null;

                        col = 1;
                        sheet.Cells[row, col++] = parent.Get_Die_Prefix(refDieType);
                        sheet.Cells[row, col++] = refDia;
                        sheet.Cells[row, col++] = refThk;
                        sheet.Cells[row, col++] = Math.Round(parent.GetFreightWeight(parent.Current_Customer.custCode, refDieType, refDia, refThk, 0), 2);
                        sheet.Cells[row, col++] = Math.Round(parent.GetSurchargeWeight(0, refDieType, refDia, refThk, 1, 0), 2);

                        sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price);
                        try
                        {
                            cavity = 2;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 3;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 4;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 5;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 6;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 8;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 10;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        try
                        {
                            cavity = 12;
                            refHoleCharges = parent.holeCharge_List.FirstOrDefault(x => (x.holeQty == cavity) && x.Diameter == refDia && x.Thickness == refThk && x.Prefix == parent.Get_Die_Prefix(refDieType));
                            sheet.Cells[row, col++] = "$" + String.Format("{0:0.00}", RefBC.Price + refHoleCharges.Price * cavity);
                        }
                        catch
                        {
                            sheet.Cells[row, col++] = "N/A";
                        }
                        row++;
                    }
                    else
                    {
                        Error_Log.Add("Die Size Found for Customer: " + refDieType + " @ " + refDia + " x " + refThk + " (but no base charge exists for size)");
                    }
                }
                catch
                {
                }
            }

            row += 2; col = 1;
            sheet.Cells.get_Range("A" + row.ToString()).Font.Bold = true;
            sheet.Cells[row++, col] = "Errors:";
            foreach (string line in Error_Log)
            {
                sheet.Cells.get_Range("A" + row.ToString()).Font.Italic = true;
                sheet.Cells.get_Range("A" + row.ToString()).Font.Size = 10;
                sheet.Cells.get_Range("A" + row.ToString()).Font.ColorIndex = 56;
                sheet.Cells.get_Range("A" + row.ToString(), "G" + row.ToString()).Merge();
                sheet.Cells[row++, col] = line;
            }
            
            reader.Close();
            
            /*
            foreach (baseCharges bC in parent.baseCharge_List)//.Where(x => x.Prefix == "RI").ToList())
            {
                col = 1;
                sheet.Cells[row, col++] = bC.Prefix;
                sheet.Cells[row, col++] = bC.Diameter;
                sheet.Cells[row, col++] = bC.InnerDiameter;
                sheet.Cells[row, col++] = bC.Thickness;
                sheet.Cells[row, col++] = Format_Currency(bC.Price);
                //sheet.Cells[row, col++] = Format_Currency(bC.MWPrice);
                row++;
            }
            */
        }

        private string Get_Column_Letter(int columnNumber)
        {
            int dividend = columnNumber;
            string columnName = String.Empty;
            int modulo;

            while (dividend > 0)
            {
                modulo = (dividend - 1) % 26;
                columnName = Convert.ToChar(65 + modulo).ToString() + columnName;
                dividend = (int)((dividend - modulo) / 26);
            }

            return columnName;
        }

        private string Format_Currency(double amt, bool Special_Format = false)
        {
            if (Special_Format) return "-";
            return "$" + String.Format("{0:0.00}", amt);
        }

        private string Format_Percentage(double percent, bool Special_Format = false)
        {
            if (Special_Format) return "-";
            else if (Double.IsNaN(percent)) return "0.00%";
            else if (Double.IsInfinity(percent)) return "-%"; // Infinite increase x/0
            else return percent.ToString("P2");
        }
        #endregion

        private void button3_Click(object sender, EventArgs e)
        {
            if (parent.Solid_List.Count + parent.Hollow_List.Count + parent.Support_List.Count == 0)
            {
                freight.Enabled = true;
                surcharge.Enabled = true;
                units.Enabled = true;
                nitrideRate.Enabled = true;
            }
            else
            {
                Grey_Out();
                Form_Message_Box FMB = new Form_Message_Box(parent, "You cannot make changes to rates while you have a die in your cart", true, 5, this.Location, this.Size);
                FMB.ShowDialog();
                Grey_In();
            }
        }


        private void button4_Click(object sender, EventArgs e)
        {
            parent.ShowOdds = !parent.ShowOdds;


            if (parent.ShowOdds)
            {
                label19.Left += 3;
                label19.Text = "HIDE";
            }
            else
            {
                label19.Left -= 3;
                label19.Text = "SHOW";
            }
        }

        private void nitrideRate_TextChanged(object sender, EventArgs e)
        {
            parent.textBoxTextChanged(sender, e);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            bool authenticationError = false;

            if (System.Net.NetworkInformation.IPGlobalProperties.GetIPGlobalProperties().DomainName.ToLower().Contains("exco130spy"))
            {
                List<string> Valid_Users = new List<string>() { "clarke", "administrator", "rli", "jxu", "jamie", "gluo", "orders" };
                if (Valid_Users.Contains(Environment.UserName.ToLower()))
                {
                    if (this.Height == 321)
                    {
                        this.Height = 248;
                    }
                    else
                    {
                        this.Height = 321;
                    }
                    TFLP.Size = new Size(this.Width - 2, this.Height - 2);
                }
                else
                {
                    authenticationError = true;
                }
            }
            else
            {
                authenticationError = true;
            }

            if (authenticationError)
            {
                Grey_Out();
                Form_Message_Box FMB = new Form_Message_Box(parent, "Error: You are not an administrator!", true, -10, this.Location, this.Size);
                FMB.ShowDialog();
                Grey_In();
            }
        }


        private void button6_Click(object sender, EventArgs e)
        {
            Grey_Out();
            Charge_Settings CS = new Charge_Settings(parent, this.Location, this.Size);
            CS.ShowDialog();
            Grey_In();
        }

        private void units_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }

    internal static class FormExtensions
    {
        private static void ApplicationRunProc(object state)
        {
            Application.Run(state as Form);
        }

        public static void RunInNewThread(this Form form, bool isBackground)
        {
            if (form == null)
                throw new ArgumentNullException("form");
            if (form.IsHandleCreated)
                throw new InvalidOperationException("Form is already running.");
            Thread thread = new Thread(ApplicationRunProc);
            thread.SetApartmentState(ApartmentState.STA);
            thread.IsBackground = isBackground;
            thread.Start(form);
        }
    }
}
