namespace Cross_Check_v2._0
{
    partial class FormCrossCheck
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
            this.radioButtonWORK = new System.Windows.Forms.RadioButton();
            this.radioButtonINV = new System.Windows.Forms.RadioButton();
            this.radioButtonSO = new System.Windows.Forms.RadioButton();
            this.textBoxInput = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonCheck = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.richTextBox = new System.Windows.Forms.RichTextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // radioButtonWORK
            // 
            this.radioButtonWORK.AutoSize = true;
            this.radioButtonWORK.Location = new System.Drawing.Point(115, 55);
            this.radioButtonWORK.Name = "radioButtonWORK";
            this.radioButtonWORK.Size = new System.Drawing.Size(66, 17);
            this.radioButtonWORK.TabIndex = 0;
            this.radioButtonWORK.TabStop = true;
            this.radioButtonWORK.Text = "WORK#";
            this.radioButtonWORK.UseVisualStyleBackColor = true;
            // 
            // radioButtonINV
            // 
            this.radioButtonINV.AutoSize = true;
            this.radioButtonINV.Location = new System.Drawing.Point(63, 55);
            this.radioButtonINV.Name = "radioButtonINV";
            this.radioButtonINV.Size = new System.Drawing.Size(50, 17);
            this.radioButtonINV.TabIndex = 0;
            this.radioButtonINV.TabStop = true;
            this.radioButtonINV.Text = "INV#";
            this.radioButtonINV.UseVisualStyleBackColor = true;
            // 
            // radioButtonSO
            // 
            this.radioButtonSO.AutoSize = true;
            this.radioButtonSO.Location = new System.Drawing.Point(10, 55);
            this.radioButtonSO.Name = "radioButtonSO";
            this.radioButtonSO.Size = new System.Drawing.Size(47, 17);
            this.radioButtonSO.TabIndex = 0;
            this.radioButtonSO.TabStop = true;
            this.radioButtonSO.Text = "SO#";
            this.radioButtonSO.UseVisualStyleBackColor = true;
            // 
            // textBoxInput
            // 
            this.textBoxInput.Location = new System.Drawing.Point(10, 19);
            this.textBoxInput.Name = "textBoxInput";
            this.textBoxInput.Size = new System.Drawing.Size(123, 20);
            this.textBoxInput.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBoxInput);
            this.groupBox1.Controls.Add(this.radioButtonWORK);
            this.groupBox1.Controls.Add(this.radioButtonINV);
            this.groupBox1.Controls.Add(this.radioButtonSO);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 81);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Input";
            // 
            // buttonCheck
            // 
            this.buttonCheck.Location = new System.Drawing.Point(260, 12);
            this.buttonCheck.Name = "buttonCheck";
            this.buttonCheck.Size = new System.Drawing.Size(104, 39);
            this.buttonCheck.TabIndex = 3;
            this.buttonCheck.Text = "Check";
            this.buttonCheck.UseVisualStyleBackColor = true;
            this.buttonCheck.Click += new System.EventHandler(this.buttonCheck_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(260, 56);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(104, 37);
            this.buttonExit.TabIndex = 3;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // richTextBox
            // 
            this.richTextBox.Location = new System.Drawing.Point(12, 100);
            this.richTextBox.Name = "richTextBox";
            this.richTextBox.Size = new System.Drawing.Size(530, 318);
            this.richTextBox.TabIndex = 4;
            this.richTextBox.Text = "";
            // 
            // FormCrossCheck
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(554, 425);
            this.Controls.Add(this.richTextBox);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonCheck);
            this.Controls.Add(this.groupBox1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormCrossCheck";
            this.Text = "Cross Check V2.1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonWORK;
        private System.Windows.Forms.RadioButton radioButtonINV;
        private System.Windows.Forms.RadioButton radioButtonSO;
        private System.Windows.Forms.TextBox textBoxInput;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonCheck;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.RichTextBox richTextBox;
    }
}

