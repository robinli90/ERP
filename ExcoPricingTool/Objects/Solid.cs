using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExcoPricingTool
{
    public class Solid 
    {
        // Internal Reference Information
        public string OrderID { get; set; }
        public DateTime OrderDate = new DateTime();

        // Base information
        public DieType DieType = DieType.Solid;
        public bool isMetric { get; set; }
        public double Diameter { get; set; }
        public double Thickness { get; set; }
        public double BasePrice { get; set; }
        public double CavityPrice { get; set; }
        public double SurchargePrice { get; set; }
        public double Weight { get; set; }
        public string DieNo { get; set; }
        public string Location { get; set; }
        public int HoleCount { get; set; }
        public bool Nitride { get; set; }
        public bool Pocket { get; set; }
        public string Notes { get; set; }
        public double OddDiameter { get; set; }
        public double OddThickness { get; set; }

        // Fit existing
        public string FE_Backer_No { get; set; }
        public string FE_Backer_Loc { get; set; }
        public string FE_Feeder_No { get; set; }
        public string FE_Feeder_Loc { get; set; }
        public string FE_Bolster_No { get; set; }
        public string FE_Bolster_Loc { get; set; }
        public string FE_SubBol_No { get; set; }
        public string FE_SubBol_Loc { get; set; }

        public List<DieCharge> Charge_List = new List<DieCharge>();

        public Solid()
        {
            FE_Backer_No = "";
            FE_Backer_Loc = "";
            FE_Feeder_No = "";
            FE_Feeder_Loc = "";
            FE_Bolster_No = "";
            FE_Bolster_Loc = "";
            FE_SubBol_No = "";
            FE_SubBol_Loc = "";
            CavityPrice = 0;
        }
    }

}
