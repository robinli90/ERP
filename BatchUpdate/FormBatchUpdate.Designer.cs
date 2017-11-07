using System;

namespace BatchUpdate
{
    partial class FormBatchUpdate
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
            this.buttonLoad = new System.Windows.Forms.Button();
            this.richTextBox = new System.Windows.Forms.RichTextBox();
            this.gridViewRuntimes = new System.Windows.Forms.DataGridView();
            this.buttonSubmit = new System.Windows.Forms.Button();
            this.groupBoxDisplay = new System.Windows.Forms.GroupBox();
            this.buttonShowException = new System.Windows.Forms.Button();
            this.buttonShowNormal = new System.Windows.Forms.Button();
            this.dateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxSearch = new System.Windows.Forms.GroupBox();
            this.buttonGo = new System.Windows.Forms.Button();
            this.radioButtonWO = new System.Windows.Forms.RadioButton();
            this.radioButtonSO = new System.Windows.Forms.RadioButton();
            this.textBoxPieceNum = new System.Windows.Forms.TextBox();
            this.so = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.wo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Part = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.seq = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Start = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Stop = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Runtime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StandardTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.solarsoftTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ActualTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.updateDate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DecadeTasks = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.gridViewRuntimes)).BeginInit();
            this.groupBoxDisplay.SuspendLayout();
            this.groupBoxSearch.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonLoad
            // 
            this.buttonLoad.Font = new System.Drawing.Font("Microsoft Sans Serif", 38F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLoad.ForeColor = System.Drawing.Color.Green;
            this.buttonLoad.Location = new System.Drawing.Point(13, 12);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(189, 86);
            this.buttonLoad.TabIndex = 0;
            this.buttonLoad.Text = "Load";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // richTextBox
            // 
            this.richTextBox.Location = new System.Drawing.Point(698, 12);
            this.richTextBox.Name = "richTextBox";
            this.richTextBox.ReadOnly = true;
            this.richTextBox.Size = new System.Drawing.Size(489, 174);
            this.richTextBox.TabIndex = 2;
            this.richTextBox.Text = "";
            // 
            // gridViewRuntimes
            // 
            this.gridViewRuntimes.AllowUserToAddRows = false;
            this.gridViewRuntimes.AllowUserToDeleteRows = false;
            this.gridViewRuntimes.AllowUserToResizeColumns = false;
            this.gridViewRuntimes.AllowUserToResizeRows = false;
            this.gridViewRuntimes.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridViewRuntimes.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.so,
            this.wo,
            this.Part,
            this.seq,
            this.Start,
            this.Stop,
            this.Runtime,
            this.StandardTime,
            this.solarsoftTime,
            this.ActualTime,
            this.updateDate,
            this.DecadeTasks});
            this.gridViewRuntimes.Location = new System.Drawing.Point(12, 196);
            this.gridViewRuntimes.Name = "gridViewRuntimes";
            this.gridViewRuntimes.RowHeadersVisible = false;
            this.gridViewRuntimes.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.gridViewRuntimes.Size = new System.Drawing.Size(1175, 498);
            this.gridViewRuntimes.TabIndex = 3;
            // 
            // buttonSubmit
            // 
            this.buttonSubmit.Font = new System.Drawing.Font("Microsoft Sans Serif", 30F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSubmit.ForeColor = System.Drawing.Color.Blue;
            this.buttonSubmit.Location = new System.Drawing.Point(12, 104);
            this.buttonSubmit.Name = "buttonSubmit";
            this.buttonSubmit.Size = new System.Drawing.Size(189, 86);
            this.buttonSubmit.TabIndex = 4;
            this.buttonSubmit.Text = "Submit";
            this.buttonSubmit.UseVisualStyleBackColor = true;
            this.buttonSubmit.Click += new System.EventHandler(this.buttonSubmit_Click);
            // 
            // groupBoxDisplay
            // 
            this.groupBoxDisplay.Controls.Add(this.buttonShowException);
            this.groupBoxDisplay.Controls.Add(this.buttonShowNormal);
            this.groupBoxDisplay.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxDisplay.Location = new System.Drawing.Point(209, 13);
            this.groupBoxDisplay.Name = "groupBoxDisplay";
            this.groupBoxDisplay.Size = new System.Drawing.Size(185, 173);
            this.groupBoxDisplay.TabIndex = 5;
            this.groupBoxDisplay.TabStop = false;
            this.groupBoxDisplay.Text = "What to display";
            // 
            // buttonShowException
            // 
            this.buttonShowException.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonShowException.ForeColor = System.Drawing.Color.Red;
            this.buttonShowException.Location = new System.Drawing.Point(6, 111);
            this.buttonShowException.Name = "buttonShowException";
            this.buttonShowException.Size = new System.Drawing.Size(174, 56);
            this.buttonShowException.TabIndex = 0;
            this.buttonShowException.Text = "Exception";
            this.buttonShowException.UseVisualStyleBackColor = true;
            this.buttonShowException.Click += new System.EventHandler(this.buttonShowException_Click);
            // 
            // buttonShowNormal
            // 
            this.buttonShowNormal.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonShowNormal.ForeColor = System.Drawing.Color.Red;
            this.buttonShowNormal.Location = new System.Drawing.Point(6, 33);
            this.buttonShowNormal.Name = "buttonShowNormal";
            this.buttonShowNormal.Size = new System.Drawing.Size(174, 56);
            this.buttonShowNormal.TabIndex = 0;
            this.buttonShowNormal.Text = "All";
            this.buttonShowNormal.UseVisualStyleBackColor = true;
            this.buttonShowNormal.Click += new System.EventHandler(this.buttonShowNormal_Click);
            // 
            // dateTimePicker
            // 
            this.dateTimePicker.Location = new System.Drawing.Point(439, 46);
            this.dateTimePicker.Name = "dateTimePicker";
            this.dateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(478, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 25);
            this.label1.TabIndex = 7;
            this.label1.Text = "Select Date";
            // 
            // groupBoxSearch
            // 
            this.groupBoxSearch.Controls.Add(this.buttonGo);
            this.groupBoxSearch.Controls.Add(this.radioButtonWO);
            this.groupBoxSearch.Controls.Add(this.radioButtonSO);
            this.groupBoxSearch.Controls.Add(this.textBoxPieceNum);
            this.groupBoxSearch.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxSearch.Location = new System.Drawing.Point(439, 72);
            this.groupBoxSearch.Name = "groupBoxSearch";
            this.groupBoxSearch.Size = new System.Drawing.Size(200, 108);
            this.groupBoxSearch.TabIndex = 9;
            this.groupBoxSearch.TabStop = false;
            this.groupBoxSearch.Text = "Search";
            // 
            // buttonGo
            // 
            this.buttonGo.Font = new System.Drawing.Font("Microsoft Sans Serif", 25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonGo.ForeColor = System.Drawing.Color.CadetBlue;
            this.buttonGo.Location = new System.Drawing.Point(114, 20);
            this.buttonGo.Name = "buttonGo";
            this.buttonGo.Size = new System.Drawing.Size(75, 68);
            this.buttonGo.TabIndex = 3;
            this.buttonGo.Text = "Go";
            this.buttonGo.UseVisualStyleBackColor = true;
            this.buttonGo.Click += new System.EventHandler(this.buttonGo_Click);
            // 
            // radioButtonWO
            // 
            this.radioButtonWO.AutoSize = true;
            this.radioButtonWO.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radioButtonWO.Location = new System.Drawing.Point(6, 83);
            this.radioButtonWO.Name = "radioButtonWO";
            this.radioButtonWO.Size = new System.Drawing.Size(51, 21);
            this.radioButtonWO.TabIndex = 2;
            this.radioButtonWO.Text = "wo#";
            this.radioButtonWO.UseVisualStyleBackColor = true;
            this.radioButtonWO.CheckedChanged += new System.EventHandler(this.radioButtonWO_CheckedChanged);
            // 
            // radioButtonSO
            // 
            this.radioButtonSO.AutoSize = true;
            this.radioButtonSO.Checked = true;
            this.radioButtonSO.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radioButtonSO.Location = new System.Drawing.Point(6, 65);
            this.radioButtonSO.Name = "radioButtonSO";
            this.radioButtonSO.Size = new System.Drawing.Size(49, 21);
            this.radioButtonSO.TabIndex = 1;
            this.radioButtonSO.TabStop = true;
            this.radioButtonSO.Text = "so#";
            this.radioButtonSO.UseVisualStyleBackColor = true;
            this.radioButtonSO.CheckedChanged += new System.EventHandler(this.radioButtonSO_CheckedChanged);
            // 
            // textBoxPieceNum
            // 
            this.textBoxPieceNum.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxPieceNum.Location = new System.Drawing.Point(6, 36);
            this.textBoxPieceNum.Name = "textBoxPieceNum";
            this.textBoxPieceNum.Size = new System.Drawing.Size(100, 23);
            this.textBoxPieceNum.TabIndex = 0;
            // 
            // so
            // 
            this.so.Frozen = true;
            this.so.HeaderText = "SO#";
            this.so.Name = "so";
            this.so.ReadOnly = true;
            this.so.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.so.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.so.Width = 80;
            // 
            // wo
            // 
            this.wo.Frozen = true;
            this.wo.HeaderText = "WO#";
            this.wo.Name = "wo";
            this.wo.ReadOnly = true;
            this.wo.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.wo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.wo.Width = 80;
            // 
            // Part
            // 
            this.Part.Frozen = true;
            this.Part.HeaderText = "Part";
            this.Part.Name = "Part";
            this.Part.ReadOnly = true;
            this.Part.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Part.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Part.Width = 150;
            // 
            // seq
            // 
            this.seq.Frozen = true;
            this.seq.HeaderText = "Seq#";
            this.seq.Name = "seq";
            this.seq.ReadOnly = true;
            this.seq.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.seq.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.seq.Width = 39;
            // 
            // Start
            // 
            this.Start.Frozen = true;
            this.Start.HeaderText = "Start";
            this.Start.Name = "Start";
            this.Start.ReadOnly = true;
            this.Start.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Start.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Start.Width = 180;
            // 
            // Stop
            // 
            this.Stop.Frozen = true;
            this.Stop.HeaderText = "Stop";
            this.Stop.Name = "Stop";
            this.Stop.ReadOnly = true;
            this.Stop.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Stop.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Stop.Width = 180;
            // 
            // Runtime
            // 
            this.Runtime.Frozen = true;
            this.Runtime.HeaderText = "Runtime";
            this.Runtime.Name = "Runtime";
            this.Runtime.ReadOnly = true;
            this.Runtime.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Runtime.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Runtime.Width = 52;
            // 
            // StandardTime
            // 
            this.StandardTime.Frozen = true;
            this.StandardTime.HeaderText = "Std Time";
            this.StandardTime.Name = "StandardTime";
            this.StandardTime.ReadOnly = true;
            this.StandardTime.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.StandardTime.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.StandardTime.Width = 55;
            // 
            // solarsoftTime
            // 
            this.solarsoftTime.Frozen = true;
            this.solarsoftTime.HeaderText = "Solarsoft";
            this.solarsoftTime.Name = "solarsoftTime";
            this.solarsoftTime.ReadOnly = true;
            this.solarsoftTime.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.solarsoftTime.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.solarsoftTime.Width = 55;
            // 
            // ActualTime
            // 
            this.ActualTime.Frozen = true;
            this.ActualTime.HeaderText = "Actual";
            this.ActualTime.Name = "ActualTime";
            this.ActualTime.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ActualTime.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.ActualTime.Width = 55;
            // 
            // updateDate
            // 
            this.updateDate.Frozen = true;
            this.updateDate.HeaderText = "Updated Date";
            this.updateDate.Name = "updateDate";
            this.updateDate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.updateDate.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // DecadeTasks
            // 
            this.DecadeTasks.HeaderText = "Decade Tasks";
            this.DecadeTasks.Name = "DecadeTasks";
            this.DecadeTasks.ReadOnly = true;
            this.DecadeTasks.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.DecadeTasks.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.DecadeTasks.Width = 150;
            // 
            // FormBatchUpdate
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1199, 703);
            this.Controls.Add(this.groupBoxSearch);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dateTimePicker);
            this.Controls.Add(this.groupBoxDisplay);
            this.Controls.Add(this.buttonSubmit);
            this.Controls.Add(this.gridViewRuntimes);
            this.Controls.Add(this.richTextBox);
            this.Controls.Add(this.buttonLoad);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "FormBatchUpdate";
            this.Text = "Batch Update V1.4.0 Built at ";
            ((System.ComponentModel.ISupportInitialize)(this.gridViewRuntimes)).EndInit();
            this.groupBoxDisplay.ResumeLayout(false);
            this.groupBoxSearch.ResumeLayout(false);
            this.groupBoxSearch.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.RichTextBox richTextBox;
        private System.Windows.Forms.DataGridView gridViewRuntimes;
        private System.Windows.Forms.Button buttonSubmit;
        private System.Windows.Forms.GroupBox groupBoxDisplay;
        private System.Windows.Forms.Button buttonShowException;
        private System.Windows.Forms.Button buttonShowNormal;
        private System.Windows.Forms.DateTimePicker dateTimePicker;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBoxSearch;
        private System.Windows.Forms.Button buttonGo;
        private System.Windows.Forms.RadioButton radioButtonWO;
        private System.Windows.Forms.RadioButton radioButtonSO;
        private System.Windows.Forms.TextBox textBoxPieceNum;
        private System.Windows.Forms.DataGridViewTextBoxColumn so;
        private System.Windows.Forms.DataGridViewTextBoxColumn wo;
        private System.Windows.Forms.DataGridViewTextBoxColumn Part;
        private System.Windows.Forms.DataGridViewTextBoxColumn seq;
        private System.Windows.Forms.DataGridViewTextBoxColumn Start;
        private System.Windows.Forms.DataGridViewTextBoxColumn Stop;
        private System.Windows.Forms.DataGridViewTextBoxColumn Runtime;
        private System.Windows.Forms.DataGridViewTextBoxColumn StandardTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn solarsoftTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn ActualTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn updateDate;
        private System.Windows.Forms.DataGridViewTextBoxColumn DecadeTasks;
    }
}

