using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace ExcoPricingTool
{

    public class AdvancedComboBox : ComboBox
    {
        new public System.Windows.Forms.DrawMode DrawMode { get; set; }
        public Color HighlightColor { get; set; }
        public Color FrameColor { get; set; }

        public AdvancedComboBox()
        {
            //this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.FrameColor = SystemColors.HotTrack;
            base.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.HighlightColor = Color.Gray;
            this.DrawItem += new DrawItemEventHandler(AdvancedComboBox_DrawItem);
        }

        void AdvancedComboBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index < 0)
                return;

            ComboBox combo = sender as ComboBox;

            if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
                e.Graphics.FillRectangle(new SolidBrush(HighlightColor),
                                         e.Bounds);
            else
                e.Graphics.FillRectangle(new SolidBrush(combo.BackColor),
                                         e.Bounds);

            e.Graphics.DrawString(combo.Items[e.Index].ToString(), e.Font,
                                  new SolidBrush(combo.ForeColor),
                                  new Point(e.Bounds.X, e.Bounds.Y));

            //e.Graphics.DrawString(combo.Items[e.Index].ToString(), e.Font, brush, e.Bounds, new StringFormat(StringFormatFlags.DirectionRightToLeft));

            //e.Graphics.DrawRectangle(new Pen(FrameColor, 2), 0, 0,
            //  this.Width - 2, this.Items.Count * 20);

            // Draw the rectangle around the drop-down list
            //if (combo.DroppedDown)
            if (false)
            {
                SolidBrush ArrowBrush = new SolidBrush(SystemColors.HighlightText);

                Rectangle dropDownBounds = new Rectangle(0, 0, combo.Width - 2, combo.Items.Count * combo.ItemHeight);
                //ControlPaint.DrawBorder(g, dropDownBounds, _borderColor, _borderStyle);
                ControlPaint.DrawBorder(e.Graphics, dropDownBounds,
                    FrameColor, 1, ButtonBorderStyle.Solid,
                    FrameColor, 1, ButtonBorderStyle.Solid,
                    FrameColor, 1, ButtonBorderStyle.Solid,
                    FrameColor, 1, ButtonBorderStyle.Solid);
            }
            e.DrawFocusRectangle();
        }

    }
}
