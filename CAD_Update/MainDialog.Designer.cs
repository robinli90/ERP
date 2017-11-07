namespace CAD_Update
{
    partial class MainDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxSO = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxNumOfCavs = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxReqDate = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxOrderDate = new System.Windows.Forms.TextBox();
            this.groupBoxOrderInfo = new System.Windows.Forms.GroupBox();
            this.richTextBoxPart = new System.Windows.Forms.RichTextBox();
            this.groupBoxFeeder = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelFeeder = new System.Windows.Forms.ComboBox();
            this.textBoxThkFeeder = new System.Windows.Forms.TextBox();
            this.textBoxDiaFeeder = new System.Windows.Forms.TextBox();
            this.checkBoxFeeder = new System.Windows.Forms.CheckBox();
            this.groupBoxMandrel = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelMandrel = new System.Windows.Forms.ComboBox();
            this.textBoxThkMandrel = new System.Windows.Forms.TextBox();
            this.textBoxDiaMandrel = new System.Windows.Forms.TextBox();
            this.checkBoxMandrel = new System.Windows.Forms.CheckBox();
            this.groupBoxPlate = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelPlate = new System.Windows.Forms.ComboBox();
            this.textBoxThkPlate = new System.Windows.Forms.TextBox();
            this.textBoxDiaPlate = new System.Windows.Forms.TextBox();
            this.checkBoxPlate = new System.Windows.Forms.CheckBox();
            this.groupBoxBacker = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelBacker = new System.Windows.Forms.ComboBox();
            this.textBoxThkBacker = new System.Windows.Forms.TextBox();
            this.textBoxDiaBacker = new System.Windows.Forms.TextBox();
            this.checkBoxBacker = new System.Windows.Forms.CheckBox();
            this.groupBoxSubBolster = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelSubBolster = new System.Windows.Forms.ComboBox();
            this.textBoxThkSubBoster = new System.Windows.Forms.TextBox();
            this.textBoxDiaSubBolster = new System.Windows.Forms.TextBox();
            this.checkBoxSubBolster = new System.Windows.Forms.CheckBox();
            this.groupBoxBolster = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelBolster = new System.Windows.Forms.ComboBox();
            this.textBoxThkBolster = new System.Windows.Forms.TextBox();
            this.textBoxDiaBolster = new System.Windows.Forms.TextBox();
            this.checkBoxBolster = new System.Windows.Forms.CheckBox();
            this.groupBoxDieRing = new System.Windows.Forms.GroupBox();
            this.comboBoxSteelDieRing = new System.Windows.Forms.ComboBox();
            this.textBoxThkDieRing = new System.Windows.Forms.TextBox();
            this.textBoxDiaDieRing = new System.Windows.Forms.TextBox();
            this.checkBoxDieRing = new System.Windows.Forms.CheckBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.richTextBoxFeaturesAndOptions = new System.Windows.Forms.RichTextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.groupBoxOrderInfo.SuspendLayout();
            this.groupBoxFeeder.SuspendLayout();
            this.groupBoxMandrel.SuspendLayout();
            this.groupBoxPlate.SuspendLayout();
            this.groupBoxBacker.SuspendLayout();
            this.groupBoxSubBolster.SuspendLayout();
            this.groupBoxBolster.SuspendLayout();
            this.groupBoxDieRing.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxSO
            // 
            this.textBoxSO.Location = new System.Drawing.Point(101, 19);
            this.textBoxSO.MaxLength = 6;
            this.textBoxSO.Name = "textBoxSO";
            this.textBoxSO.Size = new System.Drawing.Size(100, 26);
            this.textBoxSO.TabIndex = 0;
            this.textBoxSO.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBoxSO_Input);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(18, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Order #";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(19, 146);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "# Cavs";
            // 
            // textBoxNumOfCavs
            // 
            this.textBoxNumOfCavs.Enabled = false;
            this.textBoxNumOfCavs.Location = new System.Drawing.Point(101, 142);
            this.textBoxNumOfCavs.MaxLength = 6;
            this.textBoxNumOfCavs.Name = "textBoxNumOfCavs";
            this.textBoxNumOfCavs.Size = new System.Drawing.Size(100, 26);
            this.textBoxNumOfCavs.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Black;
            this.label3.Location = new System.Drawing.Point(9, 105);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "Req\'d Date";
            // 
            // textBoxReqDate
            // 
            this.textBoxReqDate.Enabled = false;
            this.textBoxReqDate.Location = new System.Drawing.Point(101, 101);
            this.textBoxReqDate.MaxLength = 6;
            this.textBoxReqDate.Name = "textBoxReqDate";
            this.textBoxReqDate.Size = new System.Drawing.Size(100, 26);
            this.textBoxReqDate.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Black;
            this.label4.Location = new System.Drawing.Point(10, 64);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(88, 20);
            this.label4.TabIndex = 7;
            this.label4.Text = "Order Date";
            // 
            // textBoxOrderDate
            // 
            this.textBoxOrderDate.Enabled = false;
            this.textBoxOrderDate.Location = new System.Drawing.Point(101, 60);
            this.textBoxOrderDate.MaxLength = 6;
            this.textBoxOrderDate.Name = "textBoxOrderDate";
            this.textBoxOrderDate.Size = new System.Drawing.Size(100, 26);
            this.textBoxOrderDate.TabIndex = 6;
            // 
            // groupBoxOrderInfo
            // 
            this.groupBoxOrderInfo.Controls.Add(this.richTextBoxPart);
            this.groupBoxOrderInfo.Controls.Add(this.textBoxNumOfCavs);
            this.groupBoxOrderInfo.Controls.Add(this.label4);
            this.groupBoxOrderInfo.Controls.Add(this.textBoxSO);
            this.groupBoxOrderInfo.Controls.Add(this.textBoxOrderDate);
            this.groupBoxOrderInfo.Controls.Add(this.label1);
            this.groupBoxOrderInfo.Controls.Add(this.label3);
            this.groupBoxOrderInfo.Controls.Add(this.label2);
            this.groupBoxOrderInfo.Controls.Add(this.textBoxReqDate);
            this.groupBoxOrderInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxOrderInfo.ForeColor = System.Drawing.Color.Red;
            this.groupBoxOrderInfo.Location = new System.Drawing.Point(12, 12);
            this.groupBoxOrderInfo.Name = "groupBoxOrderInfo";
            this.groupBoxOrderInfo.Size = new System.Drawing.Size(675, 177);
            this.groupBoxOrderInfo.TabIndex = 8;
            this.groupBoxOrderInfo.TabStop = false;
            this.groupBoxOrderInfo.Text = "Order Info";
            // 
            // richTextBoxPart
            // 
            this.richTextBoxPart.Location = new System.Drawing.Point(216, 13);
            this.richTextBoxPart.Name = "richTextBoxPart";
            this.richTextBoxPart.ReadOnly = true;
            this.richTextBoxPart.Size = new System.Drawing.Size(441, 152);
            this.richTextBoxPart.TabIndex = 9;
            this.richTextBoxPart.Text = "";
            // 
            // groupBoxFeeder
            // 
            this.groupBoxFeeder.Controls.Add(this.comboBoxSteelFeeder);
            this.groupBoxFeeder.Controls.Add(this.textBoxThkFeeder);
            this.groupBoxFeeder.Controls.Add(this.textBoxDiaFeeder);
            this.groupBoxFeeder.Controls.Add(this.checkBoxFeeder);
            this.groupBoxFeeder.Enabled = false;
            this.groupBoxFeeder.Location = new System.Drawing.Point(13, 33);
            this.groupBoxFeeder.Name = "groupBoxFeeder";
            this.groupBoxFeeder.Size = new System.Drawing.Size(450, 53);
            this.groupBoxFeeder.TabIndex = 9;
            this.groupBoxFeeder.TabStop = false;
            // 
            // comboBoxSteelFeeder
            // 
            this.comboBoxSteelFeeder.FormattingEnabled = true;
            this.comboBoxSteelFeeder.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelFeeder.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelFeeder.Name = "comboBoxSteelFeeder";
            this.comboBoxSteelFeeder.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelFeeder.TabIndex = 3;
            // 
            // textBoxThkFeeder
            // 
            this.textBoxThkFeeder.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkFeeder.Name = "textBoxThkFeeder";
            this.textBoxThkFeeder.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkFeeder.TabIndex = 2;
            // 
            // textBoxDiaFeeder
            // 
            this.textBoxDiaFeeder.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaFeeder.Name = "textBoxDiaFeeder";
            this.textBoxDiaFeeder.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaFeeder.TabIndex = 1;
            // 
            // checkBoxFeeder
            // 
            this.checkBoxFeeder.AutoSize = true;
            this.checkBoxFeeder.ForeColor = System.Drawing.Color.Black;
            this.checkBoxFeeder.Location = new System.Drawing.Point(7, 20);
            this.checkBoxFeeder.Name = "checkBoxFeeder";
            this.checkBoxFeeder.Size = new System.Drawing.Size(69, 17);
            this.checkBoxFeeder.TabIndex = 0;
            this.checkBoxFeeder.Text = "FEEDER";
            this.checkBoxFeeder.UseVisualStyleBackColor = true;
            // 
            // groupBoxMandrel
            // 
            this.groupBoxMandrel.Controls.Add(this.comboBoxSteelMandrel);
            this.groupBoxMandrel.Controls.Add(this.textBoxThkMandrel);
            this.groupBoxMandrel.Controls.Add(this.textBoxDiaMandrel);
            this.groupBoxMandrel.Controls.Add(this.checkBoxMandrel);
            this.groupBoxMandrel.Enabled = false;
            this.groupBoxMandrel.Location = new System.Drawing.Point(13, 91);
            this.groupBoxMandrel.Name = "groupBoxMandrel";
            this.groupBoxMandrel.Size = new System.Drawing.Size(450, 53);
            this.groupBoxMandrel.TabIndex = 10;
            this.groupBoxMandrel.TabStop = false;
            // 
            // comboBoxSteelMandrel
            // 
            this.comboBoxSteelMandrel.FormattingEnabled = true;
            this.comboBoxSteelMandrel.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelMandrel.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelMandrel.Name = "comboBoxSteelMandrel";
            this.comboBoxSteelMandrel.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelMandrel.TabIndex = 3;
            // 
            // textBoxThkMandrel
            // 
            this.textBoxThkMandrel.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkMandrel.Name = "textBoxThkMandrel";
            this.textBoxThkMandrel.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkMandrel.TabIndex = 2;
            // 
            // textBoxDiaMandrel
            // 
            this.textBoxDiaMandrel.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaMandrel.Name = "textBoxDiaMandrel";
            this.textBoxDiaMandrel.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaMandrel.TabIndex = 1;
            // 
            // checkBoxMandrel
            // 
            this.checkBoxMandrel.AutoSize = true;
            this.checkBoxMandrel.ForeColor = System.Drawing.Color.Black;
            this.checkBoxMandrel.Location = new System.Drawing.Point(7, 20);
            this.checkBoxMandrel.Name = "checkBoxMandrel";
            this.checkBoxMandrel.Size = new System.Drawing.Size(79, 17);
            this.checkBoxMandrel.TabIndex = 0;
            this.checkBoxMandrel.Text = "MANDREL";
            this.checkBoxMandrel.UseVisualStyleBackColor = true;
            // 
            // groupBoxPlate
            // 
            this.groupBoxPlate.Controls.Add(this.comboBoxSteelPlate);
            this.groupBoxPlate.Controls.Add(this.textBoxThkPlate);
            this.groupBoxPlate.Controls.Add(this.textBoxDiaPlate);
            this.groupBoxPlate.Controls.Add(this.checkBoxPlate);
            this.groupBoxPlate.Enabled = false;
            this.groupBoxPlate.Location = new System.Drawing.Point(13, 149);
            this.groupBoxPlate.Name = "groupBoxPlate";
            this.groupBoxPlate.Size = new System.Drawing.Size(450, 53);
            this.groupBoxPlate.TabIndex = 10;
            this.groupBoxPlate.TabStop = false;
            // 
            // comboBoxSteelPlate
            // 
            this.comboBoxSteelPlate.FormattingEnabled = true;
            this.comboBoxSteelPlate.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelPlate.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelPlate.Name = "comboBoxSteelPlate";
            this.comboBoxSteelPlate.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelPlate.TabIndex = 3;
            // 
            // textBoxThkPlate
            // 
            this.textBoxThkPlate.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkPlate.Name = "textBoxThkPlate";
            this.textBoxThkPlate.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkPlate.TabIndex = 2;
            // 
            // textBoxDiaPlate
            // 
            this.textBoxDiaPlate.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaPlate.Name = "textBoxDiaPlate";
            this.textBoxDiaPlate.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaPlate.TabIndex = 1;
            // 
            // checkBoxPlate
            // 
            this.checkBoxPlate.AutoSize = true;
            this.checkBoxPlate.ForeColor = System.Drawing.Color.Black;
            this.checkBoxPlate.Location = new System.Drawing.Point(7, 20);
            this.checkBoxPlate.Name = "checkBoxPlate";
            this.checkBoxPlate.Size = new System.Drawing.Size(60, 17);
            this.checkBoxPlate.TabIndex = 0;
            this.checkBoxPlate.Text = "PLATE";
            this.checkBoxPlate.UseVisualStyleBackColor = true;
            // 
            // groupBoxBacker
            // 
            this.groupBoxBacker.Controls.Add(this.comboBoxSteelBacker);
            this.groupBoxBacker.Controls.Add(this.textBoxThkBacker);
            this.groupBoxBacker.Controls.Add(this.textBoxDiaBacker);
            this.groupBoxBacker.Controls.Add(this.checkBoxBacker);
            this.groupBoxBacker.Enabled = false;
            this.groupBoxBacker.Location = new System.Drawing.Point(13, 207);
            this.groupBoxBacker.Name = "groupBoxBacker";
            this.groupBoxBacker.Size = new System.Drawing.Size(450, 53);
            this.groupBoxBacker.TabIndex = 10;
            this.groupBoxBacker.TabStop = false;
            // 
            // comboBoxSteelBacker
            // 
            this.comboBoxSteelBacker.FormattingEnabled = true;
            this.comboBoxSteelBacker.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelBacker.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelBacker.Name = "comboBoxSteelBacker";
            this.comboBoxSteelBacker.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelBacker.TabIndex = 3;
            // 
            // textBoxThkBacker
            // 
            this.textBoxThkBacker.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkBacker.Name = "textBoxThkBacker";
            this.textBoxThkBacker.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkBacker.TabIndex = 2;
            // 
            // textBoxDiaBacker
            // 
            this.textBoxDiaBacker.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaBacker.Name = "textBoxDiaBacker";
            this.textBoxDiaBacker.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaBacker.TabIndex = 1;
            // 
            // checkBoxBacker
            // 
            this.checkBoxBacker.AutoSize = true;
            this.checkBoxBacker.ForeColor = System.Drawing.Color.Black;
            this.checkBoxBacker.Location = new System.Drawing.Point(7, 20);
            this.checkBoxBacker.Name = "checkBoxBacker";
            this.checkBoxBacker.Size = new System.Drawing.Size(69, 17);
            this.checkBoxBacker.TabIndex = 0;
            this.checkBoxBacker.Text = "BACKER";
            this.checkBoxBacker.UseVisualStyleBackColor = true;
            // 
            // groupBoxSubBolster
            // 
            this.groupBoxSubBolster.Controls.Add(this.comboBoxSteelSubBolster);
            this.groupBoxSubBolster.Controls.Add(this.textBoxThkSubBoster);
            this.groupBoxSubBolster.Controls.Add(this.textBoxDiaSubBolster);
            this.groupBoxSubBolster.Controls.Add(this.checkBoxSubBolster);
            this.groupBoxSubBolster.Enabled = false;
            this.groupBoxSubBolster.Location = new System.Drawing.Point(13, 323);
            this.groupBoxSubBolster.Name = "groupBoxSubBolster";
            this.groupBoxSubBolster.Size = new System.Drawing.Size(450, 53);
            this.groupBoxSubBolster.TabIndex = 10;
            this.groupBoxSubBolster.TabStop = false;
            // 
            // comboBoxSteelSubBolster
            // 
            this.comboBoxSteelSubBolster.FormattingEnabled = true;
            this.comboBoxSteelSubBolster.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelSubBolster.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelSubBolster.Name = "comboBoxSteelSubBolster";
            this.comboBoxSteelSubBolster.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelSubBolster.TabIndex = 3;
            // 
            // textBoxThkSubBoster
            // 
            this.textBoxThkSubBoster.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkSubBoster.Name = "textBoxThkSubBoster";
            this.textBoxThkSubBoster.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkSubBoster.TabIndex = 2;
            // 
            // textBoxDiaSubBolster
            // 
            this.textBoxDiaSubBolster.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaSubBolster.Name = "textBoxDiaSubBolster";
            this.textBoxDiaSubBolster.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaSubBolster.TabIndex = 1;
            // 
            // checkBoxSubBolster
            // 
            this.checkBoxSubBolster.AutoSize = true;
            this.checkBoxSubBolster.ForeColor = System.Drawing.Color.Black;
            this.checkBoxSubBolster.Location = new System.Drawing.Point(7, 20);
            this.checkBoxSubBolster.Name = "checkBoxSubBolster";
            this.checkBoxSubBolster.Size = new System.Drawing.Size(89, 17);
            this.checkBoxSubBolster.TabIndex = 0;
            this.checkBoxSubBolster.Text = "SUB_BLSTR";
            this.checkBoxSubBolster.UseVisualStyleBackColor = true;
            // 
            // groupBoxBolster
            // 
            this.groupBoxBolster.Controls.Add(this.comboBoxSteelBolster);
            this.groupBoxBolster.Controls.Add(this.textBoxThkBolster);
            this.groupBoxBolster.Controls.Add(this.textBoxDiaBolster);
            this.groupBoxBolster.Controls.Add(this.checkBoxBolster);
            this.groupBoxBolster.Enabled = false;
            this.groupBoxBolster.Location = new System.Drawing.Point(13, 265);
            this.groupBoxBolster.Name = "groupBoxBolster";
            this.groupBoxBolster.Size = new System.Drawing.Size(450, 53);
            this.groupBoxBolster.TabIndex = 10;
            this.groupBoxBolster.TabStop = false;
            // 
            // comboBoxSteelBolster
            // 
            this.comboBoxSteelBolster.FormattingEnabled = true;
            this.comboBoxSteelBolster.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelBolster.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelBolster.Name = "comboBoxSteelBolster";
            this.comboBoxSteelBolster.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelBolster.TabIndex = 3;
            // 
            // textBoxThkBolster
            // 
            this.textBoxThkBolster.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkBolster.Name = "textBoxThkBolster";
            this.textBoxThkBolster.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkBolster.TabIndex = 2;
            // 
            // textBoxDiaBolster
            // 
            this.textBoxDiaBolster.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaBolster.Name = "textBoxDiaBolster";
            this.textBoxDiaBolster.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaBolster.TabIndex = 1;
            // 
            // checkBoxBolster
            // 
            this.checkBoxBolster.AutoSize = true;
            this.checkBoxBolster.ForeColor = System.Drawing.Color.Black;
            this.checkBoxBolster.Location = new System.Drawing.Point(7, 20);
            this.checkBoxBolster.Name = "checkBoxBolster";
            this.checkBoxBolster.Size = new System.Drawing.Size(76, 17);
            this.checkBoxBolster.TabIndex = 0;
            this.checkBoxBolster.Text = "BOLSTER";
            this.checkBoxBolster.UseVisualStyleBackColor = true;
            // 
            // groupBoxDieRing
            // 
            this.groupBoxDieRing.Controls.Add(this.comboBoxSteelDieRing);
            this.groupBoxDieRing.Controls.Add(this.textBoxThkDieRing);
            this.groupBoxDieRing.Controls.Add(this.textBoxDiaDieRing);
            this.groupBoxDieRing.Controls.Add(this.checkBoxDieRing);
            this.groupBoxDieRing.Enabled = false;
            this.groupBoxDieRing.Location = new System.Drawing.Point(13, 381);
            this.groupBoxDieRing.Name = "groupBoxDieRing";
            this.groupBoxDieRing.Size = new System.Drawing.Size(450, 53);
            this.groupBoxDieRing.TabIndex = 10;
            this.groupBoxDieRing.TabStop = false;
            // 
            // comboBoxSteelDieRing
            // 
            this.comboBoxSteelDieRing.FormattingEnabled = true;
            this.comboBoxSteelDieRing.Items.AddRange(new object[] {
            "H-13",
            "DIVAR",
            "W360"});
            this.comboBoxSteelDieRing.Location = new System.Drawing.Point(349, 20);
            this.comboBoxSteelDieRing.Name = "comboBoxSteelDieRing";
            this.comboBoxSteelDieRing.Size = new System.Drawing.Size(86, 28);
            this.comboBoxSteelDieRing.TabIndex = 3;
            // 
            // textBoxThkDieRing
            // 
            this.textBoxThkDieRing.Location = new System.Drawing.Point(242, 20);
            this.textBoxThkDieRing.Name = "textBoxThkDieRing";
            this.textBoxThkDieRing.Size = new System.Drawing.Size(100, 26);
            this.textBoxThkDieRing.TabIndex = 2;
            // 
            // textBoxDiaDieRing
            // 
            this.textBoxDiaDieRing.Location = new System.Drawing.Point(136, 20);
            this.textBoxDiaDieRing.Name = "textBoxDiaDieRing";
            this.textBoxDiaDieRing.Size = new System.Drawing.Size(100, 26);
            this.textBoxDiaDieRing.TabIndex = 1;
            // 
            // checkBoxDieRing
            // 
            this.checkBoxDieRing.AutoSize = true;
            this.checkBoxDieRing.ForeColor = System.Drawing.Color.Black;
            this.checkBoxDieRing.Location = new System.Drawing.Point(7, 20);
            this.checkBoxDieRing.Name = "checkBoxDieRing";
            this.checkBoxDieRing.Size = new System.Drawing.Size(74, 17);
            this.checkBoxDieRing.TabIndex = 0;
            this.checkBoxDieRing.Text = "DIE RING";
            this.checkBoxDieRing.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.label7);
            this.groupBox8.Controls.Add(this.label6);
            this.groupBox8.Controls.Add(this.label5);
            this.groupBox8.Controls.Add(this.groupBoxFeeder);
            this.groupBox8.Controls.Add(this.groupBoxMandrel);
            this.groupBox8.Controls.Add(this.groupBoxDieRing);
            this.groupBox8.Controls.Add(this.groupBoxPlate);
            this.groupBox8.Controls.Add(this.groupBoxSubBolster);
            this.groupBox8.Controls.Add(this.groupBoxBacker);
            this.groupBox8.Controls.Add(this.groupBoxBolster);
            this.groupBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox8.ForeColor = System.Drawing.Color.Red;
            this.groupBox8.Location = new System.Drawing.Point(12, 195);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(467, 442);
            this.groupBox8.TabIndex = 11;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Features";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.Color.Black;
            this.label7.Location = new System.Drawing.Point(379, 20);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(46, 20);
            this.label7.TabIndex = 13;
            this.label7.Text = "Steel";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.Color.Black;
            this.label6.Location = new System.Drawing.Point(266, 20);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(75, 20);
            this.label6.TabIndex = 12;
            this.label6.Text = "Thk (mm)";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Black;
            this.label5.Location = new System.Drawing.Point(161, 20);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(76, 20);
            this.label5.TabIndex = 11;
            this.label5.Text = "Dia (inch)";
            // 
            // richTextBoxFeaturesAndOptions
            // 
            this.richTextBoxFeaturesAndOptions.Location = new System.Drawing.Point(486, 248);
            this.richTextBoxFeaturesAndOptions.Name = "richTextBoxFeaturesAndOptions";
            this.richTextBoxFeaturesAndOptions.ReadOnly = true;
            this.richTextBoxFeaturesAndOptions.Size = new System.Drawing.Size(201, 389);
            this.richTextBoxFeaturesAndOptions.TabIndex = 12;
            this.richTextBoxFeaturesAndOptions.Text = "";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.Red;
            this.label8.Location = new System.Drawing.Point(506, 215);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(163, 20);
            this.label8.TabIndex = 14;
            this.label8.Text = "Features and Options";
            // 
            // buttonSave
            // 
            this.buttonSave.Enabled = false;
            this.buttonSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSave.ForeColor = System.Drawing.Color.Red;
            this.buttonSave.Location = new System.Drawing.Point(161, 669);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(160, 52);
            this.buttonSave.TabIndex = 15;
            this.buttonSave.Text = "SAVE";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonCancel.ForeColor = System.Drawing.Color.Red;
            this.buttonCancel.Location = new System.Drawing.Point(374, 669);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(160, 52);
            this.buttonCancel.TabIndex = 16;
            this.buttonCancel.Text = "CANCEL";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // MainDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(699, 742);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.richTextBoxFeaturesAndOptions);
            this.Controls.Add(this.groupBox8);
            this.Controls.Add(this.groupBoxOrderInfo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainDialog";
            this.Text = "CAD Update";
            this.groupBoxOrderInfo.ResumeLayout(false);
            this.groupBoxOrderInfo.PerformLayout();
            this.groupBoxFeeder.ResumeLayout(false);
            this.groupBoxFeeder.PerformLayout();
            this.groupBoxMandrel.ResumeLayout(false);
            this.groupBoxMandrel.PerformLayout();
            this.groupBoxPlate.ResumeLayout(false);
            this.groupBoxPlate.PerformLayout();
            this.groupBoxBacker.ResumeLayout(false);
            this.groupBoxBacker.PerformLayout();
            this.groupBoxSubBolster.ResumeLayout(false);
            this.groupBoxSubBolster.PerformLayout();
            this.groupBoxBolster.ResumeLayout(false);
            this.groupBoxBolster.PerformLayout();
            this.groupBoxDieRing.ResumeLayout(false);
            this.groupBoxDieRing.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxSO;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxNumOfCavs;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxReqDate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxOrderDate;
        private System.Windows.Forms.GroupBox groupBoxOrderInfo;
        private System.Windows.Forms.RichTextBox richTextBoxPart;
        private System.Windows.Forms.GroupBox groupBoxFeeder;
        private System.Windows.Forms.ComboBox comboBoxSteelFeeder;
        private System.Windows.Forms.TextBox textBoxThkFeeder;
        private System.Windows.Forms.TextBox textBoxDiaFeeder;
        private System.Windows.Forms.CheckBox checkBoxFeeder;
        private System.Windows.Forms.GroupBox groupBoxMandrel;
        private System.Windows.Forms.ComboBox comboBoxSteelMandrel;
        private System.Windows.Forms.TextBox textBoxThkMandrel;
        private System.Windows.Forms.TextBox textBoxDiaMandrel;
        private System.Windows.Forms.CheckBox checkBoxMandrel;
        private System.Windows.Forms.GroupBox groupBoxPlate;
        private System.Windows.Forms.ComboBox comboBoxSteelPlate;
        private System.Windows.Forms.TextBox textBoxThkPlate;
        private System.Windows.Forms.TextBox textBoxDiaPlate;
        private System.Windows.Forms.CheckBox checkBoxPlate;
        private System.Windows.Forms.GroupBox groupBoxBacker;
        private System.Windows.Forms.ComboBox comboBoxSteelBacker;
        private System.Windows.Forms.TextBox textBoxThkBacker;
        private System.Windows.Forms.TextBox textBoxDiaBacker;
        private System.Windows.Forms.CheckBox checkBoxBacker;
        private System.Windows.Forms.GroupBox groupBoxSubBolster;
        private System.Windows.Forms.ComboBox comboBoxSteelSubBolster;
        private System.Windows.Forms.TextBox textBoxThkSubBoster;
        private System.Windows.Forms.TextBox textBoxDiaSubBolster;
        private System.Windows.Forms.CheckBox checkBoxSubBolster;
        private System.Windows.Forms.GroupBox groupBoxBolster;
        private System.Windows.Forms.ComboBox comboBoxSteelBolster;
        private System.Windows.Forms.TextBox textBoxThkBolster;
        private System.Windows.Forms.TextBox textBoxDiaBolster;
        private System.Windows.Forms.CheckBox checkBoxBolster;
        private System.Windows.Forms.GroupBox groupBoxDieRing;
        private System.Windows.Forms.ComboBox comboBoxSteelDieRing;
        private System.Windows.Forms.TextBox textBoxThkDieRing;
        private System.Windows.Forms.TextBox textBoxDiaDieRing;
        private System.Windows.Forms.CheckBox checkBoxDieRing;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.RichTextBox richTextBoxFeaturesAndOptions;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonCancel;
    }
}

