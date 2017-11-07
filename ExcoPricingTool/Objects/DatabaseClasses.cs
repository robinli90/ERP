using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExcoPricingTool
{
    class DatabaseClasses
    {
    }

    public enum DieType
    {
        Solid,
        Hollow,
        Feeder, 
        Backer,
        Bolster,
        Subbolster,
        Ring
    }

    public class Order
    {
        public DateTime Date { get; set; }
        public string ID { get; set; }
        public string PO { get; set; }
        public string Requisitioner { get; set; }
        public string Authorizer { get; set; }
        public string Due { get; set; }
        public double Total { get; set; }
        public double FreightCost { get; set; }
        public int DieQty { get; set; }
    }

    public class Customer
    {
        public string custCode { get; set; }
        public string Name { get; set; }
        public string PLCode { get; set; }

        public List<holeCharges> Hole_Charge_List { get; set; }
        public List<baseCharges> Item_Charge_List { get; set; }
        public List<itemCharges> Base_Charge_List { get; set; }

        /// <summary>
        /// Initializes base lists
        /// </summary>
        public Customer()
        {
            Hole_Charge_List = new List<holeCharges>();
            Item_Charge_List = new List<baseCharges>();
            Base_Charge_List = new List<itemCharges>();
        }
    }

    public class baseCharges
    {
        public string Prefix { get; set; }
        public double Diameter { get; set; }
        public double Thickness { get; set; }
        public double InnerDiameter { get; set; }
        public double Price { get; set; }
        public double MWPrice { get; set; }

        public override string ToString()
        {
            return Diameter + " x " + Thickness + " (ID=" + InnerDiameter + ", Price=" + Price + ", Prefix=" + Prefix + ")";
        }

        public baseCharges()
        {
            InnerDiameter = 0;
        }

        // MWallace's fall-back RI algorithm
        public double Get_Ring_Price()
        {
            var a = Diameter + Thickness + InnerDiameter;
            double multiplier = 0,
                    steelMultiplier = 0,
                    rate = 0;

            if (Diameter < 15)
            {
                multiplier = 0.30;
                rate = 60;
            }
            else if (Diameter < 19)
            {
                multiplier = 0.360;
                rate = 60;
            }
            else if (Diameter < 23)
            {
                multiplier = 0.425;
                rate = 60;
            }
            else if (Diameter < 27)
            {
                multiplier = 0.487;
                rate = 80;
            }
            else if (Diameter <= 30)
            {
                multiplier = 0.550;
                rate = 80;
            }

            if (Math.Abs(multiplier) > 0.0005 && Math.Abs(rate) > 0.0005)
            {
                var b = a * multiplier;
                var c = b * rate;

                double weight;
                GetSurchargeWeight(0, DieType.Solid, Diameter, Thickness, 1, out weight);
                if (Diameter < 23)
                    steelMultiplier = 1.50;
                else if (Diameter < 27)
                    steelMultiplier = 1.65;
                else if (Diameter <= 30)
                    steelMultiplier = 2.00;

                var d = weight * steelMultiplier;

                return Math.Round(c + d, 0);
            }
            else
            {
                return 0;
            }
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
                                               int pieceCount, out double weight)
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
                    if (double.TryParse(tmpSize, out tmp))
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
    }

    public class holeCharges
    {
        public string Prefix { get; set; }
        public double Diameter { get; set; }
        public double Thickness { get; set; }
        public double InnerDiameter { get; set; }
        public int holeQty { get; set; }
        public double Price { get; set; }

        public holeCharges()
        {
            InnerDiameter = 0;
        }
    }

    public class itemCharges
    {
        public string Prefix { get; set; }
        public string chargeName { get; set; }
        public double flatPrice { get; set; }
        public double percPrice { get; set; }
        public int maxQty { get; set; }
    }
}
