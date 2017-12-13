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

            Console.WriteLine("painting...");

            Delete_Item_Buttons.ForEach(button => button.Image.Dispose());
            Delete_Item_Buttons.ForEach(button => button.Dispose());
            Delete_Item_Buttons.ForEach(button => this.Controls.Remove(button));
            Delete_Item_Buttons = new List<Button>();

            int data_height = 20;
            int start_height = orderNum.Height + orderNum.Top + 15;
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
                    delete_button.Location = new Point(start_margin, start_height + height_offset + (row_count * data_height) - 2);
                    delete_button.Name = "del" + count;
                    delete_button.Text = "";
                    delete_button.Click += new EventHandler(this.dynamic_button_click);
                    Delete_Item_Buttons.Add(delete_button);
                    Controls.Add(delete_button);

                    e.Graphics.DrawString(GetFileName(filePath), f_small, WritingBrush, start_margin + 20, start_height + height_offset + (row_count * data_height));
                    row_count++;
                }
            }
            else
            {
                e.Graphics.DrawString("No files to upload", f_italic, WritingBrush, start_margin + 30, start_height + height_offset + (row_count * data_height));
            }

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
        private void addSolidButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.Title = "Upload File(s)";
            file.Multiselect = true;
            if (file.ShowDialog() == DialogResult.OK)
            {
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
                string archivePath = Path.Combine(@"\\10.0.0.8\cache\", orderNum.Text);

                if (!Directory.Exists(archivePath))
                    Directory.CreateDirectory(archivePath);

                foreach (var file in FileList)
                {
                    // Copy file
                    File.Copy(file, Path.Combine(archivePath, Path.GetFileName(file)), true);
                }

                FileList = new List<string>();
                Refresh();
            }
            else
            {
                orderNum.BackColor = Color.Maroon;
            }
        }
    }
}
