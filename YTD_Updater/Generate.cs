using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using YTD_Updater;

namespace YTD_Updater
{
    public partial class Generate : Form
    {

        Updater _UPDATER;

        public Generate()
        {
            _UPDATER = new Updater();

            InitializeComponent();
            comboBox1.Items.Add("MARKHAM");
            comboBox1.Items.Add("MICHIGAN");
            comboBox1.Items.Add("TEXAS");
            comboBox1.Items.Add("COLOMBIA");
            comboBox2.Items.Add("2012");
            comboBox2.Items.Add("2013");
            comboBox2.Items.Add("2014");
            comboBox2.Items.Add("2015");
            comboBox2.Items.Add("2016");
            comboBox2.Items.Add("2017");
            comboBox2.Items.Add("2018");
            comboBox3.Items.Add("01");
            comboBox3.Items.Add("02");
            comboBox3.Items.Add("03");
            comboBox3.Items.Add("04");
            comboBox3.Items.Add("05");
            comboBox3.Items.Add("06");
            comboBox3.Items.Add("07");
            comboBox3.Items.Add("08");
            comboBox3.Items.Add("09");
            comboBox3.Items.Add("10");
            comboBox3.Items.Add("11");
            comboBox3.Items.Add("12");
            comboBox2.SelectedIndex = 5;
            comboBox1.SelectedIndex = 0;
            comboBox3.SelectedIndex = DateTime.Now.Month + 1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _UPDATER._SET_CURRENCY(domestic_check.Checked);
            //this.Size = new Size(301, 618);
            _UPDATER._SET_FISCAL_YEAR(comboBox2.Text.Substring(2,2));
            if (comboBox1.Text == "MICHIGAN")
                _UPDATER._SET_PLANT("MICH");
            else
                _UPDATER._SET_PLANT(comboBox1.Text.Substring(0, 3));
            _UPDATER._SET_FISCAL_MONTH(comboBox3.Text.ToString());
            _UPDATER.Process();
            //this.Close();
            //this.Dispose();
            _UPDATER = new Updater();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button2.ForeColor = Color.Red;
            _UPDATER._GENERATE_FILES();
        }

        // Update file
        private void button4_Click(object sender, EventArgs e)
        {
            _UPDATER._SET_FISCAL_YEAR(comboBox2.Text.Substring(2, 2));
            if (comboBox1.Text == "MICHIGAN")
                _UPDATER._SET_PLANT("MICH");
            else
                _UPDATER._SET_PLANT(comboBox1.Text.Substring(0, 3));
            _UPDATER._SET_FISCAL_MONTH(comboBox3.Text.ToString());
            if (regen_all)
            {
                _UPDATER._GENERATE_FILES();
                _UPDATER.Process();
            }
            else
                _UPDATER.REGENERATE_DATA();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Generate_Load(object sender, EventArgs e)
        {
            //this.Size = new Size(301, 128);
        }

        private void domestic_check_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.Text != "MARKHAM")
            {
                domestic_check.Enabled = true;
            }
            else
            { 
                domestic_check.Enabled = false;
                domestic_check.Checked = false;
            }
        }

        bool regen_all = false;

        private void button3_Click(object sender, EventArgs e)
        {
            regen_all = true;   
        }

        private void RTB_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
