using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ExcoUtility;
using System.Data.Odbc;

namespace CAMCheckOut
{
    public partial class FormCAMCheckOut : Form
    {
        // id file location
        string idFile = "S:\\USRID\\CAMSTATION.txt";
        // employee file location
        string empFile = "C:\\cms\\emp.ini";
        // machine id
        string machineID = string.Empty;
        // employee number
        string empNum = string.Empty;

        public FormCAMCheckOut()
        {
            try
            {
                InitializeComponent();
                // get machine id
                if (File.Exists(empFile))
                {
                    string[] fileContent = File.ReadAllLines(empFile);
                    if (2 != fileContent.Length)
                    {
                        throw new Exception("Invalid employee file!");
                    }
                    else
                    {
                        empNum = fileContent[0].Trim();
                        machineID = fileContent[1].Trim();
                    }
                    // submit check in to decade
                    ExcoODBC database = ExcoODBC.Instance;
                    database.Open(Database.DECADE);
                    string query = "insert into dbo.d_task values (999999, " + empNum + ", 'OO', 'X', 'X', '" + machineID + "', CURRENT_TIMESTAMP, 0, 0)";
                    if (1 != database.RunQueryWithoutReader(query))
                    {
                        throw new Exception("Failed to update decade!");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonCheckOut_Click(object sender, EventArgs e)
        {
            try
            {
                empNum = textEmpNum.Text.Trim();
                // check if employee number is right
                string[] fileContent = File.ReadAllLines(idFile);
                int index = -1;
                foreach (string line in fileContent)
                {
                    if (line.Contains(empNum))
                    {
                        index = line.IndexOf("CM");
                        if (-1 == index)
                        {
                            index = line.IndexOf("DS");
                            if (-1 == index)
                            {
                                throw new Exception("CAM STATION file format error!");
                            }
                        }
                        machineID = line.Substring(index, 4);
                        break;
                    }
                }
                if (-1 == index)
                {
                    throw new Exception("Employee number " + empNum + " is invalid, please retype!");
                }
                // submit check out to decade
                ExcoODBC database = ExcoODBC.Instance;
                database.Open(Database.DECADE);
                string query = "insert into dbo.d_task values (999999, " + empNum + ", 'II', 'X', 'X', '" + machineID + "', CURRENT_TIMESTAMP, 0, 0)";
                if (1 == database.RunQueryWithoutReader(query))
                {
                    // update employee number file
                    File.WriteAllText(empFile, empNum + Environment.NewLine + machineID);
                    Application.Exit();
                }
                else
                {
                    throw new Exception("Failed to update decade!");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                textEmpNum.Clear();
            }
        }
    }
}