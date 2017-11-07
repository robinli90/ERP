using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExcoPricingTool
{
    public class Support
    {   
        // Internal Reference Information
        public string OrderID { get; set; }
        public DateTime OrderDate = new DateTime();
            
        // Base information
        public DieType DieType = DieType.Solid;
        public bool isMetric { get; set; }
        public double Diameter { get; set; }
        public double InnerDiameter { get; set; }
        public double Thickness { get; set; }
        public double BasePrice { get; set; }
        public double SurchargePrice { get; set; }
        public double Weight { get; set; }
        public string DieNo { get; set; }
        public string Location { get; set; }
        public double CavityPrice { get; set; }
        public int HoleCount { get; set; }
        public string Notes { get; set; }
        public double OddDiameter { get; set; }
        public double OddThickness { get; set; }
        public double OddInnerDiameter { get; set; }

        public List<DieCharge> Charge_List = new List<DieCharge>();

        public Support()
        {
            OddInnerDiameter = 0;
            CavityPrice = 0;
        }

    }
}
