using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExcoPricingTool
{
    public class Hollow
    {
        // Internal Reference Information
        public string OrderID { get; set; }
        public DateTime OrderDate = new DateTime();

        // Base information
        public DieType DieType = DieType.Hollow;
        public bool isMetric { get; set; }
        public double Diameter { get; set; }
        public double Thickness { get; set; }
        public double BasePrice { get; set; }
        public double Weight { get; set; }
        public double SurchargePrice { get; set; }
        public string DieNo { get; set; }
        public string Location { get; set; }
        public int HoleCount { get; set; }
        public double CavityPrice { get; set; }
        public bool Nitride { get; set; }
        public bool Plate_Only { get; set; }
        public bool Mandrel_Only { get; set; }
        public bool No_Backer { get; set; }
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

        public Hollow()
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
