using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AddSinglePart
{
    public partial class MainForm : Form
    {
        private Part part = new Part();

        public MainForm()
        {
            InitializeComponent();
            // add radio check event handler
            radioBAH.Click += new EventHandler(radio_Click);
            radioBOH.Click += new EventHandler(radio_Click);
            radioFDR.Click += new EventHandler(radio_Click);
            radioHB.Click += new EventHandler(radio_Click);
            radioHD.Click += new EventHandler(radio_Click);
            radioHDB.Click += new EventHandler(radio_Click);
            radioHDM.Click += new EventHandler(radio_Click);
            radioHDP.Click += new EventHandler(radio_Click);
            radioRI.Click += new EventHandler(radio_Click);
            radioSBH.Click += new EventHandler(radio_Click);
            radioSD.Click += new EventHandler(radio_Click);
            radioSPC.Click += new EventHandler(radio_Click);
            radioTH.Click += new EventHandler(radio_Click);
            // add part feature edit even hander
            textDiameter.Leave += new EventHandler(text_Leave);
            textThickness.Leave += new EventHandler(text_Leave);
        }

        private void buttonGetPart_Click(object sender, EventArgs e)
        {
            // get part feature
            try
            {
                part.GetPart();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
            // update edit box
            text1HolePrice.Text = part.holePrices.Hole1;
            text2HolePrice.Text = part.holePrices.Hole2;
            text3HolePrice.Text = part.holePrices.Hole3;
            text4HolePrice.Text = part.holePrices.Hole4;
            text5HolePrice.Text = part.holePrices.Hole5;
            text6HolePrice.Text = part.holePrices.Hole6;
            text8HolePrice.Text = part.holePrices.Hole8;
            text10HolePrice.Text = part.holePrices.Hole10;
            text12HolePrice.Text = part.holePrices.Hole12;
            // update part string
            textPart.Text = part.GetPartString();
        }

        private void text_Leave(object sender, EventArgs e)
        {
            switch (((TextBox)sender).Name)
            {
                case "textDiameter":
                    part.diameter = ((TextBox)sender).Text; 
                    break;
                case "textThickness":
                    part.thickness = ((TextBox)sender).Text;
                    break;
                default:
                    throw new Exception("Unwanted " + ((TextBox)sender).Name + " leave event");
            }
            textPart.Text = part.GetPartString();
        }

        private void radio_Click(object sender, EventArgs e)
        {
            string partType = "";
            switch (((RadioButton)sender).Name)
            {
                case "radioBAH":
                    partType = "BAH";
                    break;
                case "radioBOH":
                    partType = "BOH";
                    break;
                case "radioFDR":
                    partType = "FDR";
                    break;
                case "radioHB":
                    partType = "HB";
                    break;
                case "radioHD":
                    partType = "HD";
                    break;
                case "radioHDB":
                    partType = "HDB";
                    break;
                case "radioHDM":
                    partType = "HDM";
                    break;
                case "radioHDP":
                    partType = "HDP";
                    break;
                case "radioRI":
                    partType = "RI";
                    break;
                case "radioSBH":
                    partType = "SBH";
                    break;
                case "radioSD":
                    partType = "SD";
                    break;
                case "radioSPC":
                    partType = "SPC";
                    break;
                case "radioTH":
                    partType = "TH";
                    break;
                default:
                    throw new Exception("Invalid part type!");
            }
            part.partType = partType;
            textPart.Text = part.GetPartString();
        }
    }
}