using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ExcoUtility;
using System.Data.Odbc;

namespace Cross_Check_v2._0
{
    public partial class FormCrossCheck : Form
    {
        // so
        public string so = string.Empty;
        // inv
        public string inv = string.Empty;
        // wo
        public string wo = string.Empty;

        public FormCrossCheck()
        {
            InitializeComponent();
            radioButtonSO.Checked = true;
            ActiveControl = textBoxInput;
            KeyUp += new KeyEventHandler(EnterPressed);
            textBoxInput.KeyUp += new KeyEventHandler(EnterPressed);
        }

        private void EnterPressed(object sender, KeyEventArgs e)
        {
            if (Keys.Enter == e.KeyCode)
            {
                buttonCheck_Click(sender, e);
            }
            else if (Keys.Escape == e.KeyCode)
            {
                buttonExit_Click(sender, e);
            }
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buttonCheck_Click(object sender, EventArgs e)
        {
            // erase old data
            richTextBox.Clear();
            so = "";
            inv = "";
            wo = "";

            if (radioButtonSO.Checked)
            {
                so = textBoxInput.Text.Trim();
                GetINV();
                GetWO();
            }
            else if (radioButtonINV.Checked)
            {
                inv = textBoxInput.Text.Trim();
                GetSO();
                GetWO();
            }
            else if (radioButtonWORK.Checked)
            {
                // check cjobh
                string query = "select dnord# from cmsdat.cjobh where dnjob='" + textBoxInput.Text.Trim() + "'";
                ExcoODBC database = ExcoODBC.Instance;
                database.Open(Database.CMSDAT);
                OdbcDataReader reader = database.RunQuery(query);
                if (reader.Read())
                {
                    so = reader[0].ToString().Trim();
                }
                reader.Close();
                // check hjobh
                query = "select dnord# from cmsdat.hjobh where dnjob='" + textBoxInput.Text.Trim() + "'";
                reader = database.RunQuery(query);
                if (reader.Read())
                {
                    so = reader[0].ToString().Trim();
                }
                reader.Close();
                GetINV();
                GetWO();
            }
            // write to editbox
            richTextBox.Text = "sales order number:" + Environment.NewLine + so + Environment.NewLine + Environment.NewLine;
            richTextBox.Text += "invoice number:" + Environment.NewLine + inv + Environment.NewLine + Environment.NewLine;
            richTextBox.Text += "work orders:" + Environment.NewLine + wo + Environment.NewLine;
            // reset
            textBoxInput.Clear();
            textBoxInput.Focus();
        }

        private void GetSO()
        {
            string query = "select dhord# from cmsdat.oih where dhinv#=" + inv;
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            if (reader.Read())
            {
                so = reader[0].ToString().Trim();
            }
            reader.Close();
        }

        private void GetINV()
        {
            string query = "select dhinv# from cmsdat.oih where dhord#=" + so;
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            if (reader.Read())
            {
                inv = reader[0].ToString().Trim();
            }
            reader.Close();
        }

        private void GetWO()
        {
            wo = string.Empty;
            // check cjobh
            string query = "select dnjob, dnpart from cmsdat.cjobh where dnord#=" + so;
            ExcoODBC database = ExcoODBC.Instance;
            database.Open(Database.CMSDAT);
            OdbcDataReader reader = database.RunQuery(query);
            while (reader.Read())
            {
                string piece = reader[0].ToString().Trim() + "\t" + reader[1].ToString().Trim() + Environment.NewLine;
                wo += piece;
            }
            reader.Close();
            // check hjobh
            query = "select dnjob, dnpart from cmsdat.hjobh where dnord#=" + so;
            reader = database.RunQuery(query);
            while (reader.Read())
            {
                string piece = reader[0].ToString().Trim() + "\t" + reader[1].ToString().Trim() + Environment.NewLine;
                wo += piece;
            }
            reader.Close();
        }
    }
}
