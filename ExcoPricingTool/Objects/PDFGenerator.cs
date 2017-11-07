using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using System.Diagnostics;
using System.Threading.Tasks;
using PdfSharp.Drawing;
using PdfSharp.Forms;
using PdfSharp.Pdf;
using PdfSharp.Fonts;
using PdfSharp.Internal;
using PdfSharp.Charting;
using PdfSharp.SharpZipLib;
using PdfSharp.Drawing.Pdf;
using PdfSharp.Drawing.Layout;

namespace ExcoPricingTool
{
    public class PDFGenerator
    {
        Main parent;
        Order Ref_Order;

        int pageCount = 1;

        // Date culture
        System.Globalization.DateTimeFormatInfo mfi = new System.Globalization.DateTimeFormatInfo();

        public int page_width = 586;
        public int start_width = 22;
        public int extension_col = 586 - 120;
        public int itemchg_col = 586 - 200;
        public int page_footer_boundary = 750;
        PdfDocument document = new PdfDocument();

        private bool needsCallQuote = false;
        private bool needsCallQuote2 = false;

        public string CFQ = "Call for Quote";
        int start_height = 125;
        int height_offset = 1;
        int row_count = 0;
        PdfPage page;

        public PDFGenerator(Main parent_, string OrderID, bool GenerateFromHistory = true, string print_name = "")
        {
            parent = parent_;

            if (parent.isMetric)
            {
                MetricFactor = 25.4;
            }

            int data_height = 15;

            Ref_Order = parent.Order_List.FirstOrDefault(x => x.ID == OrderID);

            if (Ref_Order == null)
            {
                Ref_Order = new Order()
                {
                    PO = parent.PO,
                    Authorizer = parent.Auth,
                    Requisitioner = parent.Req,
                    Due = parent.Due,
                    DieQty = parent.Solid_List.Count + parent.Hollow_List.Count + parent.Support_List.Count,
                    Date = DateTime.Now,
                    ID = parent.randomID,
                    FreightCost = parent.currentFreightCost,
                    Total = parent.Current_Order_Total
                };
            }

            string fileName = "EXCO_Purchase_Order" + " (QTY-" + Ref_Order.DieQty + " @ " + DateTime.Now.Year + "-" + DateTime.Now.Month + "-" + DateTime.Now.Day + "_" + DateTime.Now.Hour + "-" + DateTime.Now.Minute +"-" + DateTime.Now.Second + DateTime.Now.Millisecond + ")" ;

            if (print_name.Length > 0)
            {
                fileName = print_name;
            }

            document.Info.Author = "EXCO";
            document.Info.Subject = "Quote-Generating Program";
            document.Info.Title = "Exco Pricing Tool Order";

            page = document.AddPage();
            XGraphics gfx = XGraphics.FromPdfPage(page);
            XFont font = new XFont("MS Reference Sans Serif", 10, XFontStyle.Bold);
            XFont fontreg = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont smallfont = new XFont("MS Reference Sans Serif", 7, XFontStyle.Bold);
            XFont smallfontreg = new XFont("MS Reference Sans Serif", 7, XFontStyle.Regular);
            XFont bigfontbold = new XFont("MS Reference Sans Serif", 25, XFontStyle.Bold);
            XTextFormatter tf = new XTextFormatter(gfx);

            DrawHeader(gfx, page);

            List<Solid> Solid_List = !GenerateFromHistory ? parent.Solid_List : parent.Solid_List_History;
            List<Hollow> Hollow_List = !GenerateFromHistory ? parent.Hollow_List : parent.Hollow_List_History;
            List<Support> Support_List = !GenerateFromHistory ? parent.Support_List : parent.Support_List_History;

            double surcharge_total = 0;

            //unit of measure
            string unit = parent.isMetric ? " mm" : " in";

            #region Solid
            foreach (Solid s in Solid_List.Where(x => x.OrderID == OrderID).ToList())
            {
                baseCharges Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType);

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, ref weight);
                }
                surcharge_total += s.SurchargePrice;

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), s.DieType + " Die (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), needsCallQuote ? CFQ : (Ref_Base.Price + s.CavityPrice).ToString(), needsCallQuote ? CFQ : (s.BasePrice).ToString(), false, !needsCallQuote);

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Part #: " + s.DieNo.Replace("--", "-"), "", "", true, false);

                if (s.Location.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Location: " + s.Location, "", "", true, false);

                if (s.Nitride)
                { 
                    double nitrideprice = parent.GetFreightWeight("", s.DieType, s.Diameter, s.Thickness, 0) * parent.nitrideRate;
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Nitriding", needsCallQuote ? CFQ : nitrideprice.ToString(), "", true, !needsCallQuote);
                }
                
                if (s.Pocket)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Pocketing", needsCallQuote ? CFQ : "50", "", true, !needsCallQuote);

                if (s.FE_Backer_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Backer #: " + s.FE_Backer_No + " at location: " + s.FE_Backer_Loc, "", "", true, false);

                if (s.FE_Feeder_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Feeder #:" + s.FE_Feeder_No + " at location: " + s.FE_Feeder_Loc, "", "", true, false);

                if (s.FE_Bolster_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Bolster #:" + s.FE_Bolster_No + " at location: " + s.FE_Bolster_Loc, "", "", true, false);

                if (s.FE_SubBol_Loc.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Sub Bolster #:" + s.FE_SubBol_No + " at location: " + s.FE_SubBol_Loc, "", "", true, false);

                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Notes: " + note_line[0], "", "", true, false);
                    height_offset -= 2;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "           " + line, "", "", true, false);
                        height_offset -= 2;
                    }
                }

                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), needsCallQuote ? CFQ : (DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price + s.CavityPrice)).ToString(), "", true, !needsCallQuote);
                    }
                }

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Steel Surcharge", needsCallQuote ? CFQ : (s.SurchargePrice).ToString(), "", true, !needsCallQuote);

                if (ifNewPage(start_height + height_offset + (row_count++ * data_height)))
                {
                    row_count = 0;
                    height_offset = 0;
                    NextPage(ref gfx, document);
                }
            }
            #endregion 

            #region Hollow
            foreach (Hollow s in Hollow_List.Where(x => x.OrderID == OrderID).ToList())
            {
                if (s.Plate_Only || s.Mandrel_Only || s.No_Backer)
                {
                    needsCallQuote = true;
                    needsCallQuote2 = true;
                }

                baseCharges Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType);

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, ref weight);
                }
                surcharge_total += s.SurchargePrice;

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), s.DieType + " Die (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), needsCallQuote ? CFQ : (Ref_Base.Price + s.CavityPrice).ToString(), needsCallQuote ? CFQ : (s.BasePrice).ToString(), false, !needsCallQuote);

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Part #: " + s.DieNo.Replace("--", "-"), "", "", true, false);

                if (s.Location.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Location: " + s.Location, "", "", true, false);

                if (s.Plate_Only || s.Mandrel_Only || s.No_Backer)
                {
                    string str = s.Plate_Only ? "Plate Only" : (s.Mandrel_Only ? "Mandrel Only" : "No Backer");
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), str, needsCallQuote ? CFQ : "50", "", true, !needsCallQuote);
                }

                if (s.Nitride)
                {
                    double nitrideprice = parent.GetFreightWeight("", s.DieType, s.Diameter, s.Thickness, 0) * parent.nitrideRate;
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Nitriding", needsCallQuote ? CFQ : nitrideprice.ToString(), "", true, !needsCallQuote);
                }

                if (s.FE_Backer_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Backer #: " + s.FE_Backer_No + " at location: " + s.FE_Backer_Loc, "", "", true, false);

                if (s.FE_Feeder_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Feeder #:" + s.FE_Feeder_No + " at location: " + s.FE_Feeder_Loc, "", "", true, false);

                if (s.FE_Bolster_No.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Bolster #:" + s.FE_Bolster_No + " at location: " + s.FE_Bolster_Loc, "", "", true, false);

                if (s.FE_SubBol_Loc.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "For existing Sub Bolster #:" + s.FE_SubBol_No + " at location: " + s.FE_SubBol_Loc, "", "", true, false);

                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Notes: " + note_line[0], "", "", true, false);
                    height_offset -= 2;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "            " + line, "", "", true, false);
                        height_offset -= 2;
                    }
                }

                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), needsCallQuote ? CFQ : (DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price + s.CavityPrice)).ToString(), "", true, !needsCallQuote);
                    }
                }

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Steel Surcharge", needsCallQuote ? CFQ : (s.SurchargePrice).ToString(), "", true, !needsCallQuote);

                if (ifNewPage(start_height + height_offset + (row_count++ * data_height)))
                {
                    row_count = 0;
                    height_offset = 0;
                    NextPage(ref gfx, document);
                }
            }
            #endregion 
            
            #region Support
            foreach (Support s in Support_List.Where(x => x.OrderID == OrderID).ToList())
            {
                baseCharges Ref_Base;

                if (s.DieType == DieType.Ring)
                {
                    Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.InnerDiameter, s.DieType);
                }
                else
                {
                    Ref_Base = getDiaThk(s.OddDiameter, s.OddThickness, s.DieType);
                }

                // If returns null, invalid dimensions
                needsCallQuote = Ref_Base == null;

                if (needsCallQuote)
                {
                    needsCallQuote2 = true;
                }

                // Get surcharge price 
                double weight = 0;
                if (!needsCallQuote)
                {
                    GetSurchargeWeight(0, s.DieType, Ref_Base.Diameter, Ref_Base.Thickness, 1, ref weight);
                }
                surcharge_total += s.SurchargePrice;

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), s.DieType + " Die (" + Math.Round(s.Diameter * (parent.isMetric ? 25.4 : 1), 2) + unit + " X " + Math.Round(s.Thickness * (parent.isMetric ? 25.4 : 1), 2) + unit + ") - " + s.HoleCount + " Cavit" + (s.HoleCount > 1 ? "ies" : "y"), needsCallQuote ? CFQ : (Ref_Base.Price + s.CavityPrice).ToString(), needsCallQuote ? CFQ : (s.BasePrice).ToString(), false, !needsCallQuote);

                if (s.InnerDiameter > 0)
                {
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Ring Inner Diameter: " + Math.Round(s.InnerDiameter * (parent.isMetric ? 25.4 : 1), 2) + unit, "", "", true, false);
                }

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Part #: " + s.DieNo.Replace("--", "-"), "", "", true, false);

                if (s.Location.Length > 0)
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Location: " + s.Location, "", "", true, false);

                if (s.Notes.Length > 0)
                {
                    List<string> note_line = s.Notes.Split(new string[] { "```" }, StringSplitOptions.None).ToList();
                    DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Notes: " + note_line[0], "", "", true, false);
                    height_offset -= 2;
                    foreach (string line in note_line.GetRange(1, note_line.Count - 1))
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "            " + line, "", "", true, false);
                        height_offset -= 2;
                    }
                }

                foreach (DieCharge DC in s.Charge_List)
                {
                    if (DC.Quantity > 0)
                    {
                        DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), DC.Name + " (" + DC.Quantity + ")" + (DC.Notes.Length > 0 ? ": " + DC.Notes : ""), needsCallQuote ? CFQ : (DC.Quantity * DC.GetAdditionalCost(Ref_Base.Price + s.CavityPrice)).ToString(), "", true, !needsCallQuote);
                    }
                }

                DrawRow(ref gfx, page, start_height + height_offset + (row_count++ * data_height), "Steel Surcharge", needsCallQuote ? CFQ : (s.SurchargePrice).ToString(), "", true, !needsCallQuote);

                if (ifNewPage(start_height + height_offset + (row_count++ * data_height)))
                {
                    row_count = 0;
                    height_offset = 0;
                    NextPage(ref gfx, document);
                }
            }
            #endregion 

            #region Summation line
            row_count++;
            DrawTotal(ref gfx, page, start_height + height_offset + (row_count++ * data_height), Ref_Order, surcharge_total);
            #endregion

            document.Save(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), fileName + ".pdf"));

            // Open only if not printing
            if (print_name.Length == 0)
            {
                Process.Start(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), fileName + ".pdf"));
            }
        }

        private XGraphics NextPage(ref XGraphics gfx, PdfDocument document)
        {
            PdfPage newPage = document.AddPage();
            gfx = XGraphics.FromPdfPage(newPage);
            DrawHeader(gfx, newPage);
            return gfx;
        }

        private void DrawRow(ref XGraphics gfx, PdfPage page, int height, string itemName, string itemchg, string extn, bool reqIndent, bool isNumber = true)
        {
            XFont font = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont fontreg = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont smallfont = new XFont("MS Reference Sans Serif", 7, XFontStyle.Bold);
            XFont smallfontreg = new XFont("MS Reference Sans Serif", 7, XFontStyle.Regular);
            XFont bigfontbold = new XFont("MS Reference Sans Serif", 25, XFontStyle.Bold);
            XTextFormatter tf = new XTextFormatter(gfx);
            XRect rect;

            if (ifNewPage(height))
            {
                rect = new XRect(page_width - 150, page_footer_boundary - 19, 150, 8);
                gfx.DrawRectangle(XBrushes.White, rect);
                tf.Alignment = XParagraphAlignment.Right;
                tf.DrawString("Order continues on next page...", smallfontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

                row_count = 0;
                height_offset = 0;
                NextPage(ref gfx, document);
            }

            if (itemName.Length > 0)
            {
                rect = new XRect(start_width + (reqIndent ? 20 : 0), height, 400, 18);
                gfx.DrawRectangle(XBrushes.White, rect);
                tf.Alignment = XParagraphAlignment.Left;
                tf.DrawString(itemName, font, XBrushes.Black, rect, XStringFormats.TopLeft);

                if (isNumber)
                {
                    if (Convert.ToDouble(itemchg) > 0)
                    {
                        double g = Convert.ToDouble(itemchg);
                        rect = new XRect(itemchg_col - 35, height, 100, 18);
                        gfx.DrawRectangle(XBrushes.White, rect);
                        tf.Alignment = XParagraphAlignment.Right;
                        tf.DrawString("$" + String.Format("{0:0.00}", g), font, XBrushes.Black, rect, XStringFormats.TopLeft);
                    }

                    if (extn.Length > 0 && Convert.ToDouble(extn) > 0)
                    {
                        double g = Convert.ToDouble(extn);
                        rect = new XRect(extension_col, height, 100, 18);
                        gfx.DrawRectangle(XBrushes.White, rect);
                        tf.Alignment = XParagraphAlignment.Right;
                        tf.DrawString("$" + String.Format("{0:0.00}", g), font, XBrushes.Black, rect, XStringFormats.TopLeft);
                    }
                }
                else
                {
                    rect = new XRect(itemchg_col - 35, height, 100, 18);
                    gfx.DrawRectangle(XBrushes.White, rect);
                    tf.Alignment = XParagraphAlignment.Right;
                    tf.DrawString(itemchg, font, XBrushes.Black, rect, XStringFormats.TopLeft);

                    rect = new XRect(extension_col, height, 100, 18);
                    gfx.DrawRectangle(XBrushes.White, rect);
                    tf.Alignment = XParagraphAlignment.Right;
                    tf.DrawString(extn, font, XBrushes.Black, rect, XStringFormats.TopLeft);
                }
            }

        }

        private void DrawTotal(ref XGraphics gfx, PdfPage page, int height, Order RefOrder, double surchargeTotal)
        {
            XFont font = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont fontreg = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont fontitalic = new XFont("MS Reference Sans Serif", 9, XFontStyle.Italic);
            XFont fontbold = new XFont("MS Reference Sans Serif", 10, XFontStyle.Bold);
            XFont smallfont = new XFont("MS Reference Sans Serif", 7, XFontStyle.Bold);
            XFont smallfontreg = new XFont("MS Reference Sans Serif", 7, XFontStyle.Regular);
            XFont bigfontbold = new XFont("MS Reference Sans Serif", 25, XFontStyle.Bold);
            XRect rect;
            XTextFormatter tf = new XTextFormatter(gfx);

            if (ifNewPage(height, 200))
            {
                rect = new XRect(page_width - 150, page_footer_boundary - 19, 150, 8);
                gfx.DrawRectangle(XBrushes.White, rect);
                tf.Alignment = XParagraphAlignment.Right;
                tf.DrawString("Order continues on next page...", smallfontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

                height = start_height + 50;
                gfx = NextPage(ref gfx, document);
                tf = new XTextFormatter(gfx);
            }

            // Accounting lines
            gfx.DrawLine(XPens.Black, itemchg_col, height, itemchg_col + 70, height);
            gfx.DrawLine(XPens.Black, extension_col + 35, height, page_width - 20, height);
            rect = new XRect(start_width, height - 1, 4000, 1);
            gfx.DrawRectangle(XBrushes.White, rect);

            //subtotal
            height += 5;
            rect = new XRect(start_width, height, 400, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("Subtotal (including steel surcharge)", font, XBrushes.Black, rect, XStringFormats.TopLeft);

            double g = Convert.ToDouble(Ref_Order.Total - Ref_Order.FreightCost);
            rect = new XRect(extension_col, height, 100, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Right;
            tf.DrawString(Ref_Order.Total == 0 ? CFQ : "$" + String.Format("{0:0.00}", g), font, XBrushes.Black, rect, XStringFormats.TopLeft);

            //freight
            height += 25;
            rect = new XRect(start_width, height, 400, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("Freight", font, XBrushes.Black, rect, XStringFormats.TopLeft);

            double fr = Convert.ToDouble(Ref_Order.FreightCost);
            rect = new XRect(extension_col, height, 100, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Right;
            tf.DrawString(Ref_Order.Total == 0 ? CFQ : "$" + String.Format("{0:0.00}", fr), font, XBrushes.Black, rect, XStringFormats.TopLeft);

            //final total
            height += 35;
            gfx.DrawLine(XPens.Black, page_width / 2, height, page_width - 20, height);
            rect = new XRect(start_width, height - 1, 4000, 1);
            gfx.DrawRectangle(XBrushes.White, rect);

            height += 5;
            rect = new XRect(page_width / 2, height, 400, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("ORDER TOTAL NET OF TAXES", fontbold, XBrushes.Black, rect, XStringFormats.TopLeft);

            double tr = Convert.ToDouble(Ref_Order.Total);
            rect = new XRect(extension_col, height, 100, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Right;
            tf.DrawString(Ref_Order.Total == 0 ? CFQ : "$" + String.Format("{0:0.00}", tr), fontbold, XBrushes.Black, rect, XStringFormats.TopLeft);

            //surcharge total
            height += 35;
            double sr = Convert.ToDouble(surchargeTotal);
            rect = new XRect(start_width, height, 400, 18);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("Total steel surcharge included: $" + String.Format("{0:0.00}", sr), fontitalic, XBrushes.Black, rect, XStringFormats.TopLeft);
        }

        private bool ifNewPage(int curHeight, int heightBuffer = 55)
        {
            if (curHeight >= (page_footer_boundary - heightBuffer))
            {
                return true;
            }
            else
            {
                return false;;
            }
        }

        void DrawImage(XGraphics gfx, Image jpegSamplePath, int x, int y, int width, int height)
        {
            XImage image = XImage.FromGdiPlusImage(jpegSamplePath);
            gfx.DrawImage(image, x, y, width, height);
        }

        private void DrawHeader(XGraphics gfx, PdfPage page)
        {
            XFont font = new XFont("MS Reference Sans Serif", 10, XFontStyle.Bold);
            XFont fontreg = new XFont("MS Reference Sans Serif", 10, XFontStyle.Regular);
            XFont smallfont = new XFont("MS Reference Sans Serif", 7, XFontStyle.Bold);
            XFont smallfontreg = new XFont("MS Reference Sans Serif", 7, XFontStyle.Regular);
            XFont bigfontbold = new XFont("MS Reference Sans Serif", 25, XFontStyle.Bold);
            XTextFormatter tf = new XTextFormatter(gfx);

            #region Standard Header
            XRect rect = new XRect(20, 20, 100, 100);
            DrawImage(gfx, global::ExcoPricingTool.Properties.Resources.EXCO, 22, 20, 85, 25);
            //gfx.DrawRectangle(XBrushes.White, rect);
            //tf.DrawString("EXCO", bigfontbold, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width, 48, 150, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("EXCO TOOLING SOLUTIONS", smallfont, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(page_width - 96, 44, 150, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("PURCHASE ORDER", font, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(page_width - 96, 60, 96, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Right;
            tf.DrawString("#" + Ref_Order.PO, font, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width, 60, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("From: ", fontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width + 35, 60, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString(parent.Current_Customer.Name, font, XBrushes.Black, rect, XStringFormats.TopLeft);

            string dateStr = Ref_Order.Date.ToString("ddd") + ", " + mfi.GetMonthName(Ref_Order.Date.Month) + " " + Ref_Order.Date.Day + ", " + Ref_Order.Date.Year;

            DateTime date = Convert.ToDateTime(Ref_Order.Due);
            string dateStr2 = date.Date.ToString("ddd") + ", " + mfi.GetMonthName(date.Date.Month) + " " + date.Date.Day + ", " + date.Date.Year;

            rect = new XRect(start_width, 74, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Req. Date: " + dateStr, fontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width, 88, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Due Date: " + dateStr2, fontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(300, 60, 200, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Requested By: " + Ref_Order.Requisitioner, fontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(299, 74, 200, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Authorized By: " + Ref_Order.Authorizer, fontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width, 108, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Item", font, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(itemchg_col, 108, 300, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Item Charge", font, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(extension_col, 108, 100, 100);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Right;
            tf.DrawString("Extension", font, XBrushes.Black, rect, XStringFormats.TopLeft);
            #endregion

            #region Footer
            rect = new XRect(page_width - 96, page_footer_boundary + 3, 96, 50);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.DrawString("Page " + pageCount++, smallfontreg, XBrushes.Black, rect, XStringFormats.TopLeft);

            rect = new XRect(start_width, page_footer_boundary + 3, 300, 10);
            gfx.DrawRectangle(XBrushes.White, rect);
            tf.Alignment = XParagraphAlignment.Left;
            tf.DrawString("Dimensions approximate; to be further specified in drawings. Special steels extra", smallfontreg, XBrushes.Black, rect, XStringFormats.TopLeft);
            #endregion

            XPen g = new XPen(Color.Black, 0.5);

            // primary header
            gfx.DrawLine(XPens.Black, 22, 58, page_width, 58);

            // secondary header
            gfx.DrawLine(XPens.Black, 22, 103, page_width, 103);

            // footer line
            gfx.DrawLine(XPens.Black, 22, page_footer_boundary, page_width, page_footer_boundary);
        }

        double MetricFactor = 1;

        // Return the next biggest
        public baseCharges getDiaThk(double refDia, double refThk, DieType dt, bool isOddDimensions = true)
        {
            if (refDia * refThk == 0) // If either dimensions are based 0, call for quote
            {
                return null;
            }
            baseCharges Ref_Base = parent.baseCharge_List.FirstOrDefault(x => x.Diameter * (isOddDimensions ? 1 : MetricFactor) >= refDia  - (parent.isMetric ? parent.metricTolerance : 0) && x.Thickness * (isOddDimensions ? 1 : MetricFactor) >= refThk  - (parent.isMetric ? parent.metricTolerance : 0) && x.Prefix == parent.Get_Die_Prefix(dt));
            return Ref_Base;
        }

        // Return the next biggest with inner dia (for rings)
        public baseCharges getDiaThk(double refDia, double refThk, double innerDia, DieType dt, bool isOddDimensions = true)
        {
            if (parent.baseCharge_List.Where(x => x.Prefix == parent.Get_Die_Prefix(dt)).Count() == 0)
            {
                baseCharges BC = new baseCharges()
                {
                    Diameter = refDia,
                    Thickness = refThk,
                    InnerDiameter = innerDia,
                };
                BC.Price = BC.Get_Ring_Price();
                return BC;
            }

            baseCharges Ref_Base = parent.baseCharge_List.FirstOrDefault(x => x.Diameter * (isOddDimensions ? 1 : MetricFactor) >= refDia  - (parent.isMetric ? parent.metricTolerance : 0) && x.InnerDiameter * (isOddDimensions ? 1 : MetricFactor) >= innerDia && x.Thickness * (isOddDimensions ? 1 : MetricFactor) >= refThk  - (parent.isMetric ? parent.metricTolerance : 0) && x.Prefix == parent.Get_Die_Prefix(dt));
            return Ref_Base;
        }


        /// <summary>
        ///     Gets the surcharge weight.
        /// </summary>
        /// <param name="weightType">Type of the weight.</param>
        /// <param name="dieType">Type of the die.</param>
        /// <param name="diameter">The diameter.</param>
        /// <param name="thickness">The thickness.</param>
        /// <param name="pieceCount">The piece count.</param>
        /// <param name="weight">The weight.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        public static bool GetSurchargeWeight(byte weightType, DieType dieType, double diameter, double thickness,
                                               int pieceCount, ref double weight)
        {
            weight = 0;

            var steelStockDias = new List<double>();

            /*
            if (!ExcoVars.SteelSurcharge_StockSizes.IsNullOrEmpty(true))
            {
                var tmpSizes = ExcoVars.SteelSurcharge_StockSizes.Split(',');

                foreach (var tmpSize in tmpSizes)
                {
                    double tmp;
                    if (double.TryParse(tmpSize, ref tmp))
                        steelStockDias.Add(tmp);
                }
            }*/

            steelStockDias.Add(14.5);
            steelStockDias.Add(15.5);

            var isStockDia = false;

            //ChangeUnits(ref diameter, ref thickness);

            switch (weightType)
            {
                #region Normal Calculation
                default:


                    #region Get Surcharge Diameter
                    foreach (var curStockSize in steelStockDias)
                    {
                        var tmpMin = Math.Floor(curStockSize);
                        if (diameter > tmpMin && diameter <= curStockSize)
                        {
                            diameter = curStockSize;
                            isStockDia = true;
                        }
                    }

                    if (!isStockDia)
                        diameter = Math.Ceiling(FixSize(diameter));
                    #endregion


                    #region Get Surcharge Thickness
                    if (dieType == DieType.Hollow)
                    {
                        if (diameter <= 8)
                            thickness += 1;
                        else if (diameter <= 10)
                            thickness += 1.4;
                        else if (diameter <= 14)
                            thickness += 2;
                        else if (diameter <= 18)
                            thickness += 2.5;
                        else if (diameter <= 22)
                            thickness += 2.8;
                        else if (diameter > 22)
                            thickness += 3.1;
                    }
                    else
                    {
                        if (diameter <= 10)
                            thickness += .12 * pieceCount;
                        else if (diameter <= 14)
                            thickness += .15 * pieceCount;
                        else if (diameter <= 18)
                            thickness += .18 * pieceCount;
                        else if (diameter <= 22)
                            thickness += .21 * pieceCount;
                        else if (diameter > 22)
                            thickness += .24 * pieceCount;
                    }
                    #endregion


                    weight = diameter * 1.01 * (diameter * 1.01) * thickness * .224;
                    break;
                #endregion


                #region Sapa Calculation
                case 1: // Sapa
                    diameter = Math.Ceiling(diameter);

                    if (dieType == DieType.Hollow)
                        weight = diameter * diameter * thickness * .224 * 1.21;
                    else
                        weight = (diameter + 0.125) * (diameter + 0.125) * (thickness + pieceCount * 0.125) * 0.2223;
                    break;
                #endregion


                #region Brazil Normal Calculation
                case 2: // Brazil Kg (in lbs.)


                    #region Get Surcharge Thickness
                    if (dieType == DieType.Hollow)
                    {
                        if (diameter <= 8)
                            thickness += 1;
                        else if (diameter <= 10)
                            thickness += 1.4;
                        else if (diameter <= 14)
                            thickness += 2;
                        else if (diameter <= 18)
                            thickness += 2.5;
                        else if (diameter <= 22)
                            thickness += 2.8;
                        else if (diameter > 22)
                            thickness += 3.1;
                    }
                    else
                    {
                        if (diameter <= 10)
                            thickness += .12 * pieceCount;
                        else if (diameter <= 14)
                            thickness += .15 * pieceCount;
                        else if (diameter <= 18)
                            thickness += .18 * pieceCount;
                        else if (diameter <= 22)
                            thickness += .21 * pieceCount;
                        else if (diameter > 22)
                            thickness += .24 * pieceCount;
                    }
                    #endregion


                    // Convert imperial sizes to metric for formula
                    var metricDia = diameter * 25.4;
                    var metricThk = thickness * 25.4;

                    weight = metricDia * 1.01 / 20 * (metricDia * 1.01 / 20) * 3.14 * (metricThk / 10) * 7.8 / 1000 * 2.2046;
                    break;
                #endregion
            }

            return true;
        }

        /// <summary>
        ///     Fixes the size.
        /// </summary>
        /// <param name="num">The number.</param>
        /// <returns>System.Double.</returns>
        public static double FixSize(double num)
        {
            // const double tolerance = 0.051;
            const double tolerance = 0.056;
            var numInt = (int)num;
            var numRemain = num - numInt;

            if (numRemain <= tolerance)
                numRemain = 0;
            else if (numRemain <= 0.250 + tolerance)
                numRemain = 0.250;
            else if (numRemain <= 0.500 + tolerance)
                numRemain = 0.500;
            else if (numRemain <= 0.750 + tolerance)
                numRemain = 0.750;
            else
                numRemain = 1;

            return numInt + numRemain;
        }

        public static void SetDoubleBuffered(System.Windows.Forms.Control c)
        {
            if (System.Windows.Forms.SystemInformation.TerminalServerSession)
                return;

            System.Reflection.PropertyInfo aProp =
                  typeof(System.Windows.Forms.Control).GetProperty(
                        "DoubleBuffered",
                        System.Reflection.BindingFlags.NonPublic |
                        System.Reflection.BindingFlags.Instance);

            aProp.SetValue(c, true, null);
        }
    }
}
