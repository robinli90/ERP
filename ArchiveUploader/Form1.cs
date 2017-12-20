using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArchiveUploader
{
    public partial class ArchiveUploader : Form
    {
        private string designScanPath = @"\\10.0.0.8\ndrive\";

        List<Button> Delete_Item_Buttons = new List<Button>();
        int Initializing_Height = 0;

        #region Drag anywhere
        // Main color
        public Color Frame_Color = Color.Red;

        // Mouse down anywhere to drag
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        private void Form_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }
        #endregion

        protected override void OnPaint(PaintEventArgs e)
        {

            Delete_Item_Buttons.ForEach(button => button.Image.Dispose());
            Delete_Item_Buttons.ForEach(button => button.Dispose());
            Delete_Item_Buttons.ForEach(button => this.Controls.Remove(button));
            Delete_Item_Buttons = new List<Button>();

            int data_height = 20;
            int start_height = dieNum.Height + (checkBox1.Checked ? dieNum.Top : checkBox1.Top + 15) + 10;
            int start_margin = 5;   
            int height_offset = 0;
            int row_count = 0;

            Color DrawForeColor = Color.White;

            SolidBrush WritingBrush = new SolidBrush(DrawForeColor);
            
            Font f_small = new Font("MS Reference Sans Serif", 9, FontStyle.Regular);
            Font f_italic = new Font("MS Reference Sans Serif", 8, FontStyle.Italic);

            double Order_Total = 0;
            int count = 0;
            
            if (FileList.Count > 0)
            {
                foreach (string filePath in FileList)
                {

                    Button delete_button = new Button();
                    delete_button.BackColor = this.BackColor;
                    delete_button.ForeColor = this.BackColor;
                    delete_button.FlatStyle = FlatStyle.Flat;
                    delete_button.Image = global::ArchiveUploader.Properties.Resources.del;
                    delete_button.Size = new Size(21, 21);
                    delete_button.Location = new Point(start_margin + 10, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "del" + count++;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    Controls.Add(delete_button);

                    e.Graphics.DrawString(GetFileName(filePath), f_small, WritingBrush, start_margin + 30, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
            }
            else
            {
                e.Graphics.DrawString("No files to upload...", f_italic, WritingBrush, start_margin + 30, start_height + height_offset + (row_count * data_height));
            }

            if (!checkBox1.Checked)
                row_count = row_count > 3 ? row_count - 3 : 0;

            // Adjust new height
            this.Height = Initializing_Height + height_offset + (++row_count) * data_height;// +QL_Height_Factor;

            // Dispose all objects
            WritingBrush.Dispose();
            f_italic.Dispose();
            f_small.Dispose();

            base.OnPaint(e);

        }



        private void dynamic_button_click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            
            if (b.Name.StartsWith("del")) // delete
            {
                DeleteFile(Convert.ToInt32(b.Name.Substring(3)));
            }
            Invalidate();
        }

        private List<string> FileList = new List<string>();

        private const int MaxFileCount = 15;

        public ArchiveUploader()
        {
            this.AutoScaleMode = AutoScaleMode.Font;
            InitializeComponent();
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);    
        }

        public string GetFileName(string filePath)
        {
            filePath = Path.GetFileName(filePath);

            if (filePath.Length > 20)
            {
                return filePath.Substring(0, 20) + "...";
            }

            return filePath;
        }

        public void UploadFile(string filePath)
        {
            if (FileList.Count < MaxFileCount 
                && !FileList.Contains(filePath))
            {
                FileList.Add(filePath);
            }
        }

        public void DeleteFile(int index)
        {
            if (FileList.Count > 0 && FileList.Count > index)
            {
                FileList.RemoveAt(index);
            }
        }

        private void ArchiveUploader_Load(object sender, EventArgs e)
        {
            // Mousedown anywhere to drag
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form_MouseDown);

            Initializing_Height = this.Size.Height;
        }

        // Add files
        private void addFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.Title = "Upload File(s)";
            file.Multiselect = !checkBox1.Checked;
            if (file.ShowDialog() == DialogResult.OK)
            {
                if (checkBox1.Checked && FileList.Count > 0)
                {
                    FileList = new List<string>();
                    MessageBox.Show("Original file(s) have been removed");
                }

                foreach (string filename in file.FileNames)
                {
                    UploadFile(filename);
                }   

            }
            Refresh();
        }

        // Upload
        private void button1_Click(object sender, EventArgs e)
        {
            if (FileList.Count > 0 && 
                orderNum.Text.Length == 6 && 
                orderNum.Text.All(x => char.IsDigit(x)))
            {

                // Only one file to be copied for design copy
                if (checkBox1.Checked && FileList.Count == 1)
                {
                    if (custNum.Text.Trim().Length <= 0)
                    {
                        MessageBox.Show("Missing customer number");
                        custNum.BackColor = Color.Maroon;
                        return;
                    }
                    if (dieNum.Text.Trim().Length <= 0)
                    {
                        MessageBox.Show("Missing die number");
                        dieNum.BackColor = Color.Maroon;
                        return;
                    }
                    // Try to copy to ndrive, if error, warn and do not continue
                    if (!CopyToNDrive(FileList[0], custNum.Text.Trim(), dieNum.Text.Trim(), orderNum.Text))
                    {
                        MessageBox.Show(String.Format("Customer '{0}' does not exist", custNum.Text.Trim()));
                        custNum.BackColor = Color.Maroon;
                        return;
                    }
                }

                string archivePath = Path.Combine(@"\\10.0.0.8\cache\", orderNum.Text);

                if (!Directory.Exists(archivePath))
                    Directory.CreateDirectory(archivePath);

                foreach (var file in FileList)
                {
                    // Copy file if exists (could be deleted in the interim)
                    if (File.Exists(file))
                    {
                        File.Copy(file, Path.Combine(archivePath, Path.GetFileName(file)), true);
                    }
                }

                Append(String.Format("    {2} Files uploaded to archive from {0}/{1} to SO:{3} {4}", Environment.MachineName, Environment.UserName, FileList.Count, orderNum.Text, 
                    (checkBox1.Checked ? String.Format("(Cust:{0}, DieNo:{1})", custNum.Text, dieNum.Text) : "")
                    ));

                FileList = new List<string>();
                custNum.Text = dieNum.Text = orderNum.Text = "";
                Refresh();


                MessageBox.Show("Upload successful!");
            }
            else if (orderNum.Text.Trim().Length <= 0 || !orderNum.Text.All(x => char.IsDigit(x)))
            {
                orderNum.BackColor = Color.Maroon;
            }
            else
            {
                MessageBox.Show("No files uploaded");
            }
        }

        private bool CopyToNDrive(string sourceFilePath, string custNo, string dieNo, string orderNo)
        {
            string custPath = Path.Combine(designScanPath, custNo);
            string diePath = Path.Combine(custPath, dieNo);

            // Return false if customer does not exist 
            if (!Directory.Exists(custPath)) return false;

            // Create path for die if it does not exist
            if (!Directory.Exists(diePath))
                Directory.CreateDirectory(diePath);

            string filePath = Path.Combine(diePath,
                String.Format("{0}_{1}_{2}-{3}-{4}", dieNo, orderNo, DateTime.Now.Year, DateTime.Now.Month,
                    DateTime.Now.Day));

            int pathAppend = 0;

            while (File.Exists(filePath + (pathAppend > 0 ? "" : pathAppend.ToString())))
            {
                pathAppend++;
            }

            // Copy file to ndrive and append digit if more than one file
            File.Copy(sourceFilePath, filePath + 
                (pathAppend > 0 ? pathAppend.ToString() : "") + 
                Path.GetExtension(sourceFilePath),
                true // not necessarily required but in case?
                );

            return true;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (FileList.Count > 1)
            { 
                MessageBox.Show(
                    "You have more than 1 file added. You can only upload a single file per instance when uploading design files. All files have been removed");
                FileList = new List<string>();
                Refresh();
            }

            label3.Visible = label9.Visible = checkBox1.Checked;
            dieNum.Visible = custNum.Visible = checkBox1.Checked;

            Refresh();
        }

        private void orderNum_TextChanged(object sender, EventArgs e)
        {
            orderNum.BackColor = Color.FromArgb(72, 72, 72);
        }

        private void dieNum_TextChanged(object sender, EventArgs e)
        {
            dieNum.BackColor = Color.FromArgb(72, 72, 72);
        }

        private void custNum_TextChanged(object sender, EventArgs e)
        {
            custNum.BackColor = Color.FromArgb(72, 72, 72);
        }

        public static readonly string logFilePath = @"\\10.0.0.8\EmailAPI\log.txt";


        public static void Append(string logText)
        {
            logText = String.Format("[{3}-{0}:{1}:{2}] - {5} - {4}", DateTime.Now.Hour.ToString("D2"),
                DateTime.Now.Minute.ToString("D2"),
                DateTime.Now.Second.ToString("D2"), DateTime.Now.Date.ToShortDateString(), logText,
                //GetSessionEmail());
                Environment.MachineName);

            while (true)
            {
                try
                {
                    AppendLine(logText + Environment.NewLine);
                    return;
                }
                catch
                {
                    // File in use, try again
                }
            }
        }

        public static void AppendLine(string line)
        {
            while (true)
            {
                try
                {
                    File.AppendAllText(logFilePath, line);
                    return;
                }
                catch
                {
                    // File in use, try again
                }
            }
        }

        private void close_button_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
