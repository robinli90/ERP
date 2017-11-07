namespace PL_Michigan
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
            this.buttonRun = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButtonSingleMonth = new System.Windows.Forms.RadioButton();
            this.radioButtonAllMonth = new System.Windows.Forms.RadioButton();
            this.comboBoxPeriod = new System.Windows.Forms.ComboBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonRun
            // 
            this.buttonRun.Location = new System.Drawing.Point(13, 150);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(75, 23);
            this.buttonRun.TabIndex = 0;
            this.buttonRun.Text = "Run";
            this.buttonRun.UseVisualStyleBackColor = true;
            this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxPeriod);
            this.groupBox1.Controls.Add(this.radioButtonAllMonth);
            this.groupBox1.Controls.Add(this.radioButtonSingleMonth);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // radioButtonSingleMonth
            // 
            this.radioButtonSingleMonth.AutoSize = true;
            this.radioButtonSingleMonth.Checked = true;
            this.radioButtonSingleMonth.Location = new System.Drawing.Point(7, 20);
            this.radioButtonSingleMonth.Name = "radioButtonSingleMonth";
            this.radioButtonSingleMonth.Size = new System.Drawing.Size(105, 17);
            this.radioButtonSingleMonth.TabIndex = 0;
            this.radioButtonSingleMonth.TabStop = true;
            this.radioButtonSingleMonth.Text = "One Month 2014";
            this.radioButtonSingleMonth.UseVisualStyleBackColor = true;
            // 
            // radioButtonAllMonth
            // 
            this.radioButtonAllMonth.AutoSize = true;
            this.radioButtonAllMonth.Location = new System.Drawing.Point(7, 43);
            this.radioButtonAllMonth.Name = "radioButtonAllMonth";
            this.radioButtonAllMonth.Size = new System.Drawing.Size(96, 17);
            this.radioButtonAllMonth.TabIndex = 0;
            this.radioButtonAllMonth.Text = "All Month 2014";
            this.radioButtonAllMonth.UseVisualStyleBackColor = true;
            // 
            // comboBoxPeriod
            // 
            this.comboBoxPeriod.FormattingEnabled = true;
            this.comboBoxPeriod.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12"});
            this.comboBoxPeriod.Location = new System.Drawing.Point(119, 20);
            this.comboBoxPeriod.Name = "comboBoxPeriod";
            this.comboBoxPeriod.Size = new System.Drawing.Size(52, 21);
            this.comboBoxPeriod.TabIndex = 1;
            // 
            // MainDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(332, 836);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonRun);
            this.Name = "MainDialog";
            this.Text = "P&L Michigan";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxPeriod;
        private System.Windows.Forms.RadioButton radioButtonAllMonth;
        private System.Windows.Forms.RadioButton radioButtonSingleMonth;
    }
}

