using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExcoPricingTool
{
    public enum ExcoChargeFunction
    {
        FlatRate,
        BaseMultiple
    }

    public class DieCharge
    {
        public DieCharge Clone()
        {
            return System.MemberwiseClone.Copy(this);
        }

        public DieType Dietype { get; set; }
        public string Name { get; set; }
        public string Notes { get; set; }
        public int Quantity { get; set; }
        public string Formula { get; set; }

        public DieCharge(DieType dt)
        {
            Dietype = dt;
            Name = "";
            Notes = "";
            Quantity = 0;
            Formula = "";
        }

        public void SetFormula(ExcoChargeFunction ECF, double amount)
        {
            switch (ECF)
            {
                case ExcoChargeFunction.FlatRate:
                    Formula = "F" + amount;
                    break;
                case ExcoChargeFunction.BaseMultiple:
                    Formula = "B" + amount;
                    break;
                default:
                    Formula = "";
                    break;
            }
        }

        public override string ToString()
        {
            //  DCListTemp.Add(new DieCharge(DieType.Ring) { Formula = "", Name = "" });

            return "DCListTemp.Add(new Diecharge(DieType." + Dietype + ") { Formula = \"" + Formula + "\", Name = \"" + Name + "\" });";
        }

        /// <summary>
        ///  Return formulaic cost
        /// </summary>
        /// <param name="basePrice"></param>
        /// <returns></returns>
        public double GetAdditionalCost(double basePrice)
        {
            if (Formula.StartsWith("F"))
            {
                return Convert.ToDouble(Formula.Substring(1));
            }
            else if (Formula.StartsWith("B"))
            {
                return Convert.ToDouble(Formula.Substring(1)) * basePrice;
            }
            return 0;
        }

        public string GetFormula()
        {
            return Formula;
        }
    }
}
