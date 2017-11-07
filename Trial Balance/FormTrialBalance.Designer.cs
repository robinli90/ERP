namespace Trial_Balance
{
    partial class FormTrialBalance
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
            this.buttonGo = new System.Windows.Forms.Button();
            this.groupBoxSelectPlant = new System.Windows.Forms.GroupBox();
            this.radioButtonColombia = new System.Windows.Forms.RadioButton();
            this.radioButtonTexas = new System.Windows.Forms.RadioButton();
            this.radioButtonMichigan = new System.Windows.Forms.RadioButton();
            this.radioButtonMarkham = new System.Windows.Forms.RadioButton();
            this.textBoxYear = new System.Windows.Forms.TextBox();
            this.textBoxPeriod = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.richTextBoxLog = new System.Windows.Forms.RichTextBox();
            this.groupBoxSelectPlant.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonGo
            // 
            this.buttonGo.Location = new System.Drawing.Point(138, 99);
            this.buttonGo.Name = "buttonGo";
            this.buttonGo.Size = new System.Drawing.Size(75, 23);
            this.buttonGo.TabIndex = 0;
            this.buttonGo.Text = "GO";
            this.buttonGo.UseVisualStyleBackColor = true;
            this.buttonGo.Click += new System.EventHandler(this.buttonGo_Click);
            // 
            // groupBoxSelectPlant
            // 
            this.groupBoxSelectPlant.Controls.Add(this.radioButtonColombia);
            this.groupBoxSelectPlant.Controls.Add(this.radioButtonTexas);
            this.groupBoxSelectPlant.Controls.Add(this.radioButtonMichigan);
            this.groupBoxSelectPlant.Controls.Add(this.radioButtonMarkham);
            this.groupBoxSelectPlant.Location = new System.Drawing.Point(13, 13);
            this.groupBoxSelectPlant.Name = "groupBoxSelectPlant";
            this.groupBoxSelectPlant.Size = new System.Drawing.Size(96, 114);
            this.groupBoxSelectPlant.TabIndex = 1;
            this.groupBoxSelectPlant.TabStop = false;
            this.groupBoxSelectPlant.Text = "Plant";
            // 
            // radioButtonColombia
            // 
            this.radioButtonColombia.AutoSize = true;
            this.radioButtonColombia.Location = new System.Drawing.Point(5, 89);
            this.radioButtonColombia.Name = "radioButtonColombia";
            this.radioButtonColombia.Size = new System.Drawing.Size(68, 17);
            this.radioButtonColombia.TabIndex = 0;
            this.radioButtonColombia.TabStop = true;
            this.radioButtonColombia.Text = "Colombia";
            this.radioButtonColombia.UseVisualStyleBackColor = true;
            // 
            // radioButtonTexas
            // 
            this.radioButtonTexas.AutoSize = true;
            this.radioButtonTexas.Location = new System.Drawing.Point(5, 66);
            this.radioButtonTexas.Name = "radioButtonTexas";
            this.radioButtonTexas.Size = new System.Drawing.Size(54, 17);
            this.radioButtonTexas.TabIndex = 0;
            this.radioButtonTexas.TabStop = true;
            this.radioButtonTexas.Text = "Texas";
            this.radioButtonTexas.UseVisualStyleBackColor = true;
            // 
            // radioButtonMichigan
            // 
            this.radioButtonMichigan.AutoSize = true;
            this.radioButtonMichigan.Location = new System.Drawing.Point(5, 43);
            this.radioButtonMichigan.Name = "radioButtonMichigan";
            this.radioButtonMichigan.Size = new System.Drawing.Size(68, 17);
            this.radioButtonMichigan.TabIndex = 0;
            this.radioButtonMichigan.TabStop = true;
            this.radioButtonMichigan.Text = "Michigan";
            this.radioButtonMichigan.UseVisualStyleBackColor = true;
            // 
            // radioButtonMarkham
            // 
            this.radioButtonMarkham.AutoSize = true;
            this.radioButtonMarkham.Location = new System.Drawing.Point(7, 20);
            this.radioButtonMarkham.Name = "radioButtonMarkham";
            this.radioButtonMarkham.Size = new System.Drawing.Size(69, 17);
            this.radioButtonMarkham.TabIndex = 0;
            this.radioButtonMarkham.TabStop = true;
            this.radioButtonMarkham.Text = "Markham";
            this.radioButtonMarkham.UseVisualStyleBackColor = true;
            // 
            // textBoxYear
            // 
            this.textBoxYear.Location = new System.Drawing.Point(186, 30);
            this.textBoxYear.MaxLength = 4;
            this.textBoxYear.Name = "textBoxYear";
            this.textBoxYear.Size = new System.Drawing.Size(100, 20);
            this.textBoxYear.TabIndex = 2;
            this.textBoxYear.Text = "14";
            this.textBoxYear.WordWrap = false;
            // 
            // textBoxPeriod
            // 
            this.textBoxPeriod.Location = new System.Drawing.Point(186, 65);
            this.textBoxPeriod.MaxLength = 2;
            this.textBoxPeriod.Name = "textBoxPeriod";
            this.textBoxPeriod.Size = new System.Drawing.Size(100, 20);
            this.textBoxPeriod.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(121, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Fiscal Year";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(113, 68);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Fiscal Period";
            // 
            // richTextBoxLog
            // 
            this.richTextBoxLog.Location = new System.Drawing.Point(13, 134);
            this.richTextBoxLog.Name = "richTextBoxLog";
            this.richTextBoxLog.ReadOnly = true;
            this.richTextBoxLog.Size = new System.Drawing.Size(496, 1078);
            this.richTextBoxLog.TabIndex = 4;
            this.richTextBoxLog.Text = "";
            // 
            // FormTrialBalance
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 1224);
            this.Controls.Add(this.richTextBoxLog);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxPeriod);
            this.Controls.Add(this.textBoxYear);
            this.Controls.Add(this.groupBoxSelectPlant);
            this.Controls.Add(this.buttonGo);
            this.Name = "FormTrialBalance";
            this.Text = "Trial Balance V1.0";
            this.groupBoxSelectPlant.ResumeLayout(false);
            this.groupBoxSelectPlant.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonGo;
        private System.Windows.Forms.GroupBox groupBoxSelectPlant;
        private System.Windows.Forms.RadioButton radioButtonColombia;
        private System.Windows.Forms.RadioButton radioButtonTexas;
        private System.Windows.Forms.RadioButton radioButtonMichigan;
        private System.Windows.Forms.RadioButton radioButtonMarkham;
        private System.Windows.Forms.TextBox textBoxYear;
        private System.Windows.Forms.TextBox textBoxPeriod;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox richTextBoxLog;
    }
}

