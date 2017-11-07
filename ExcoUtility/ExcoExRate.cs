using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ExcoUtility
{
    public enum Currency
    {
        COP,
        COP2, // Special internal cop gov't rate
        USD
    }

    public class ExcoExRate
    {
        public ExcoExRate()
        {
        }

        private static List<CurrencyYear> CurrencyYearList { get; set; }
        

        public static readonly string currPath = @"\\10.0.0.8\EmailAPI\Financials\Exchange Rate\curr.txt";

        public static Currency GetCurrency(string str)
        {
            switch (str)
            {
                case ("COP"):
                {
                    return Currency.COP;
                }
                case ("COP2"):
                {
                    return Currency.COP2;
                }
                case ("USD"):
                {
                    return Currency.USD;
                }
            }
            return Currency.USD;
        }


        public static void Save(string msg, string filePath)
        {

            TextWriter writer = new StreamWriter(filePath);
            StreamToFile(writer, msg);

            if (writer != null)
            {
                writer.Flush();
                writer.Dispose();
                writer.Close();
            }
        }

        public static void StreamToFile(TextWriter sw, string msg)
        {
            sw.Write(msg);
        }

        public static void SaveExchangeRates(List<CurrencyYear> refList)
        {
            StringBuilder str = new StringBuilder();
            if (refList.Count == 0) return;

            foreach (CurrencyYear CY in refList)
            {
                str.Append(CY.CurrencyType + "/" + CY.Year + "/" + String.Join("/", CY.ExchangeRates) + Environment.NewLine);
            }

            Save(str.ToString(), currPath);
        }

        public static void GetExchangeRatesFromFile()
        {
            CurrencyYearList = new List<CurrencyYear>();

            // Load exchange rate array

            var text = File.ReadAllText(currPath);
            string[] lines = text.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

            foreach (string line in lines)
            {
                if (!line.StartsWith("#") && line.Length > 30)
                {
                    string[] lineParam = line.Split(new[] { "/" }, StringSplitOptions.None);
                    CurrencyYear CY = new CurrencyYear(GetCurrency(lineParam[0]), Convert.ToInt32(lineParam[1]));

                    // Add 12 periods
                    for (int i = 0; i < 12; i++)
                    {
                        try
                        {
                            CY.ExchangeRates.Add(Convert.ToDouble(lineParam[i + 2]));
                        }
                        catch
                        {
                        }
                    }

                    CurrencyYearList.Add(CY);
                }
            }

        }

        public static List<CurrencyYear> GetExchangeRatesList()
        {
            CurrencyYearList = new List<CurrencyYear>();

            // Load exchange rate array

            var text = File.ReadAllText(currPath);
            string[] lines = text.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

            foreach (string line in lines)
            {
                if (!line.StartsWith("#") && line.Length > 30)
                {
                    string[] lineParam = line.Split(new[] { "/" }, StringSplitOptions.None);
                    CurrencyYear CY = new CurrencyYear(GetCurrency(lineParam[0]), Convert.ToInt32(lineParam[1]));

                    // Add 12 periods
                    for (int i = 0; i < 12; i++)
                    {
                        try
                        {
                            CY.ExchangeRates.Add(Convert.ToDouble(lineParam[i + 2]));
                        }
                        catch
                        {
                        }
                    }

                    CurrencyYearList.Add(CY);
                }
            }

            return CurrencyYearList;
        }

        // return convert to cad rate
        public static double GetToCADRate(ExcoCalendar calendar, string currency)
        {
            if (0 == currency.CompareTo("CA"))
            {
                return 1.0;
            }
            else if (0 == currency.CompareTo("US"))
            {
                return USDtoCAD(calendar);
            }
            else if (0 == currency.CompareTo("CP"))
            {
                return PESOtoCAD(calendar);
            }
            else
            {
                throw new Exception("Invalid currency " + currency);
            }
        }

        // return convert to usd rate
        public static double GetToUSDRate(ExcoCalendar calendar, string currency)
        {
            if (0 == currency.CompareTo("CA"))
            {
                if (USDtoCAD(calendar) > 0.00000001)
                {
                    return 1.0 / USDtoCAD(calendar);
                }
                else
                {
                    return 0.0;
                }
            }
            else if (0 == currency.CompareTo("US"))
            {
                return 1.0;
            }
            else if (0 == currency.CompareTo("CP"))
            {
                if (USDtoCAD(calendar) > 0.00000001)
                {
                    return PESOtoCAD(calendar) / USDtoCAD(calendar);
                }
                else
                {
                    return 0.0;
                }
            }
            else
            {
                throw new Exception("Invalid currency " + currency);
            }
        }

        // return convert to peso rate
        public static double GetToPESORate(ExcoCalendar calendar, string currency)
        {
            if (0 == currency.CompareTo("CA"))
            {
                if (PESOtoCAD(calendar) > 0.00000001)
                {
                    return 1.0 / PESOtoCAD(calendar);
                }
                else
                {
                    return 0.0;
                }
            }
            else if (0 == currency.CompareTo("US"))
            {
                // Change from corporate rate to col govt rate from FY2017 forward
                if (PESOtoCAD(calendar) > 0.00000001 && calendar.GetFiscalYear() > 16)
                {
                    //Console.WriteLine("FY: " + calendar.GetFiscalYear() + "__FM: " + calendar.GetFiscalMonth());
                    //Console.WriteLine(PESOtoCAD(calendar));
                    //Console.WriteLine(ColGovtPesoToCad(calendar));
                    return ColGovtPesoToCad(calendar);
                }
                else if (PESOtoCAD(calendar) > 0.00000001)
                {
                    return USDtoCAD(calendar) / PESOtoCAD(calendar);
                }
                else
                {
                    return 0.0;
                }
            }
            else if (0 == currency.CompareTo("CP"))
            {
                return 1.0;
            }
            else
            {
                throw new Exception("Invalid currency " + currency);
            }
        }

        // convert rate from 1 USD to x CAD
        // use calendar year/period
        public static double ColGovtPesoToCad(ExcoCalendar calendar)
        {
            int year = calendar.GetCalendarYear();
            int month = calendar.GetCalendarMonth();

            return CurrencyYearList.First(x => x.Year == year + 2000 && x.CurrencyType == Currency.COP2).ExchangeRates[month - 1];

            switch (year)
            {
                case 2016:
                case 16:
                    switch (month)
                    {
                        case 1:
                            return 91;
                        case 2:
                            return 92; //
                        case 3:
                            return 93; //feb
                        case 4:
                            return 94;
                        case 5:
                            return 0;
                        case 6:
                            return 0;
                        case 7:
                            return 0; // June
                        case 8:
                            return 0; // July
                        case 9:
                            return 0;
                        case 10:
                            return 2879.95;
                        case 11:
                            return 2967.66;
                        case 12:
                            return 3165.09;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2017:
                case 17:
                    switch (month)
                    {
                        case 1:
                            return 3000.71;
                        case 2:
                            return 2936.66; //feb
                        case 3:
                            return 2896.27; // mar
                        case 4:
                            return 2880.24; // apr
                        case 5:
                            return 2947.85; // may
                        case 6:
                            return 2920.42;
                        case 7:
                            return 3038.26; // 
                        case 8:
                            return 2995.23; //
                        case 9:
                            return 2937.09;
                        case 10:
                            return 2937.09;
                        case 11:
                            return 2937.09;
                        case 12:
                            return 2937.09;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                default:
                    throw new Exception("Invalid year " + year.ToString());
            }
        }

        // convert rate from 1 USD to x CAD
        // use calendar year/period
        public static double USDtoCAD(ExcoCalendar calendar)
        {
            int year = calendar.GetCalendarYear();
            int month = calendar.GetCalendarMonth();


            return CurrencyYearList.First(x => x.Year == year + 2000 && x.CurrencyType == Currency.USD).ExchangeRates[month - 1];
            /*
            string USD_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\usdexchrate.txt";
            //string COP_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\copexchrate.txt";
            bool got_year = false;
            double exch_rate = 0;

            var text = File.ReadAllText(USD_exch_path);
            string[] lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
            foreach (string line in lines)
            {
                if (line.Length > 1)
                {
                    if (line.Substring(1, 4) == year.ToString())
                    {
                        got_year = true;
                    }
                    if (got_year) //found year, begin getting exchange rate
                    {
                        string[] entries = line.Split(new string[] { ":" }, StringSplitOptions.None);
                        if (entries[0] == month.ToString())
                        {
                            exch_rate = Convert.ToDouble(entries[1]);
                            got_year = false;
                            break;
                        }
                    }
                }
            }

            return exch_rate;
            */

            switch (year)
            {
                case 2010:
                case 10:
                case 2011:
                case 11:
                    return 0.0;
                case 2012:
                case 12:
                    switch (month)
                    {
                        case 1:
                            return 1.02;
                        case 2:
                            return 1.0;
                        case 3:
                            return 0.99;
                        case 4:
                            return 1.0;
                        case 5:
                            return 0.99;
                        case 6:
                            return 1.03;
                        case 7:
                            return 1.02;
                        case 8:
                            return 1.0;
                        case 9:
                            return 0.99;
                        case 10:
                            return 0.98;
                        case 11:
                            return 1.0;
                        case 12:
                            return 0.99;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2013:
                case 13:
                    switch (month)
                    {
                        case 1:
                            return 0.99;
                        case 2:
                            return 1.0;
                        case 3:
                            return 1.03;
                        case 4:
                            return 1.02;
                        case 5:
                            return 1.01;
                        case 6:
                            return 1.04;
                        case 7:
                            return 1.05;
                        case 8:
                            return 1.03;
                        case 9:
                            return 1.05;
                        case 10:
                            return 1.03;
                        case 11:
                            return 1.04;
                        case 12:
                            return 1.06;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2014:
                case 14:
                    switch (month)
                    {
                        case 1:
                            return 1.06;
                        case 2:
                            return 1.11;
                        case 3:
                            return 1.11;
                        case 4:
                            return 1.11;
                        case 5:
                            return 1.10;
                        case 6:
                            return 1.08;
                        case 7:
                            return 1.07;
                        case 8:
                            return 1.09;
                        case 9:
                            return 1.09;
                        case 10:
                            return 1.12;
                        case 11:
                            return 1.13;
                        case 12:
                            return 1.14;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2015:
                case 15:
                    switch (month)
                    {
                        case 1:
                            return 1.16;   //next
                        case 2:
                            return 1.27;
                        case 3:
                            return 1.25;
                        case 4:
                            return 1.27;
                        case 5:
                            return 1.21;
                        case 6:
                            return 1.24;//<--- MAY
                        case 7:
                            return 1.25;
                        case 8:
                            return 1.31;
                        case 9:
                            return 1.32;
                        case 10:
                            return 1.335;
                        case 11:
                            return 1.308; //oct
                        case 12:
                            return 1.335;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2016:
                case 16:
                    switch (month)
                    {
                        case 1:
                            return 1.384;
                        case 2:
                            return 1.401; //
                        case 3:
                            return 1.353; //feb
                        case 4:
                            return 1.299;
                        case 5:
                            return 1.255;
                        case 6:
                            return 1.311;
                        case 7:
                            return 1.2917; // June
                        case 8:
                            return 1.306; // July
                        case 9:
                            return 1.312;
                        case 10:
                            return 1.312;
                        case 11:
                            return 1.341;
                        case 12:
                            return 1.343;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2017:
                case 17:
                    switch (month)
                    {
                        case 1:
                            return 1.343;
                        case 2:
                            return 1.301; //
                        case 3:
                            return 1.328; //feb
                        case 4:
                            return 1.330;
                        case 5:
                            return 1.365;
                        case 6:
                            return 1.35;
                        case 7:
                            return 1.298; // June
                        case 8:
                            return 1.249; // July
                        case 9:
                            return 1.254;
                        case 10:
                            return 1.248;
                        case 11:
                            return 1.248;
                        case 12:
                            return 1.248;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2018:
                case 18:
                    switch (month)
                    {
                        case 1:
                            return 1.343;
                        case 2:
                            return 1.343; //
                        case 3:
                            return 1.343; //feb
                        case 4:
                            return 1.330;
                        case 5:
                            return 1.330;
                        case 6:
                            return 1.330;
                        case 7:
                            return 1.330; // June
                        case 8:
                            return 1.330; // July
                        case 9:
                            return 1.330;
                        case 10:
                            return 1.330;
                        case 11:
                            return 1.330;
                        case 12:
                            return 1.330;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                default:
                    throw new Exception("Invalid year " + year.ToString());
            }

        }

        // convert rate from 1 PESO to x CAD
        public static double PESOtoCAD(ExcoCalendar calendar, int year1 = 0, int month1 = 0)
        {
            int year = 0;
            int month = 0;

            // if not provided
            if (year1 == 0 && month1 == 0)
            {
                year = calendar.GetCalendarYear();
                month = calendar.GetCalendarMonth();
            }
            else
            {
                year = year1 - 1;
                if ((month1 + 10) > 12)
                {
                    month = (month1 + 10) - 12;
                    year = year1++;
                }
                else
                {
                    month = month1 + 10;
                }
            }

            CurrencyYear refCy = CurrencyYearList.First(x => x.Year - 2000 == year && x.CurrencyType == Currency.COP);

            return refCy.ExchangeRates[month - 1];
            /*
            //string USD_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\usdexchrate.txt";
            string COP_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\copexchrate.txt";
            bool got_year = false;
            double exch_rate = 0;

            var text = File.ReadAllText(COP_exch_path);
            string[] lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
            foreach (string line in lines)
            {
                if (line.Length > 1)
                {
                    if (line.Substring(1, 4) == year.ToString())
                    {z
                        got_year = true;
                    }
                    if (got_year) //found year, begin getting exchange rate
                    {
                        string[] entries = line.Split(new string[] { ":" }, StringSplitOptions.None);
                        if (entries[0] == month.ToString())
                        {
                            exch_rate = Convert.ToDouble(entries[1]);
                            got_year = false;
                            break;
                        }
                    }
                }
            }
             * 
            return exch_rate;
        }
             */

            switch (year)
            {
                case 2010:
                case 10:
                case 2011:
                case 11:
                    return 0.0;
                case 2012:
                case 12:
                    switch (month)
                    {
                        case 1:
                            return 0.000525;
                        case 2:
                            return 0.000556;
                        case 3:
                            return 0.000558;
                        case 4:
                            return 0.000557;
                        case 5:
                            return 0.000560;
                        case 6:
                            return 0.000564;
                        case 7:
                            return 0.000571;
                        case 8:
                            return 0.000559;
                        case 9:
                            return 0.000540;
                        case 10:
                            return 0.000546;
                        case 11:
                            return 0.000546;
                        case 12:
                            return 0.000548;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2013:
                case 13:
                    switch (month)
                    {
                        case 1:
                            return 0.000563;
                        case 2:
                            return 0.000562;
                        case 3:
                            return 0.000567;
                        case 4:
                            return 0.000556;
                        case 5:
                            return 0.000551;
                        case 6:
                            return 0.000543;
                        case 7:
                            return 0.000546;
                        case 8:
                            return 0.000542;
                        case 9:
                            return 0.000545;
                        case 10:
                            return 0.000539;
                        case 11:
                            return 0.000552;
                        case 12:
                            return 0.000548;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2014:
                case 14:
                    switch (month)
                    {
                        case 1:
                            return 0.000551;
                        case 2:
                            return 0.000551;
                        case 3:
                            return 0.000541;
                        case 4:
                            return 0.000561;
                        case 5:
                            return 0.000567;
                        case 6:
                            return 0.000572;
                        case 7:
                            return 0.000568;
                        case 8:
                            return 0.000580;
                        case 9:
                            return 0.000567;
                        case 10:
                            return 0.000555;
                        case 11:
                            return 0.000547;
                        case 12:
                            return 0.000515;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2015:
                case 15:
                    switch (month)
                    {
                        case 1:
                            return 0.000486; //next
                        case 2:
                            return 0.000520;
                        case 3:
                            return 0.000520;
                        case 4:
                            return 0.000489;
                        case 5:
                            return 0.000505;
                        case 6:
                            return 0.000492;//<--- MAY
                        case 7:
                            return 0.00048; //<--- JUNE
                        case 8:
                            return 0.000456; //<--- JULY
                        case 9:
                            return 0.000432; //<--- AUG
                        case 10:
                            return 0.000435; //<--- SEPT
                        case 11:
                            return 0.000453; //<--- OCT
                        case 12:
                            return 0.000424; //<--- NOV
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2016:
                case 16:
                    switch (month)
                    {
                        case 1:
                            return 0.000436; // DEC
                        case 2:
                            return 0.000426;
                        case 3:
                            return 0.000407;
                        case 4:
                            return 0.000431;
                        case 5:
                            return 0.000440;
                        case 6:
                            return 0.000424;//<--- MAY
                        case 7:
                            return 0.000445;//<--- JUNE *check income statement
                        case 8:
                            return 0.000425;
                        case 9:
                            return 0.000444;
                        case 10:
                            return 0.000458;
                        case 11:
                            return 0.000447;
                        case 12:
                            return 0.000437;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                case 2017:
                case 17:
                    switch (month)
                    {
                        case 1:
                            return 0.000448; // DEC
                        case 2:
                            return 0.000446;
                        case 3:
                            return 0.000453;
                        case 4:
                            return 0.000462;
                        case 5:
                            return 0.000463;
                        case 6:
                            return 0.000463;//<--- MAY
                        case 7:
                            return 0.000443;//<--- JUNE *check income statement
                        case 8:
                            return 0.000420;
                        case 9:
                            return 0.000424;
                        case 10:
                            return 0.000425;
                        case 11:
                            return 0.000425;
                        case 12:
                            return 0.000425;
                        default:
                            throw new Exception("Invalid month " + month.ToString());
                    }
                default:
                    throw new Exception("Invalid year " + year.ToString());
            }
        }
    }

    public class CurrencyYear
    {
        public Currency CurrencyType { get; set; }
        public List<double> ExchangeRates { get; set; }
        public int Year { get; set; }

        public CurrencyYear(Currency curr, int year)
        {
            CurrencyType = curr;
            Year = year;
            ExchangeRates = new List<double>();
        }
    }
}


//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.IO;
//
//namespace ExcoUtility
//{
//    public class ExcoExRate
//    {
//        private ExcoExRate() { }
//
//
//
//        // return convert to cad rate
//        public static double GetToCADRate(ExcoCalendar calendar, string currency)
//        {
//            if (0 == currency.CompareTo("CA"))
//            {
//                return 1.0;
//            }
//            else if (0 == currency.CompareTo("US"))
//            {
//                return USDtoCAD(calendar);
//            }
//            else if (0 == currency.CompareTo("CP"))
//            {
//                return PESOtoCAD(calendar);
//            }
//            else
//            {
//                throw new Exception("Invalid currency " + currency);
//            }
//        }
//
//        // return convert to usd rate
//        public static double GetToUSDRate(ExcoCalendar calendar, string currency)
//        {
//            if (0 == currency.CompareTo("CA"))
//            {
//                if (USDtoCAD(calendar) > 0.00000001)
//                {
//                    return 1.0 / USDtoCAD(calendar);
//                }
//                else
//                {
//                    return 0.0;
//                }
//            }
//            else if (0 == currency.CompareTo("US"))
//            {
//                return 1.0;
//            }
//            else if (0 == currency.CompareTo("CP"))
//            {
//                if (USDtoCAD(calendar) > 0.00000001)
//                {
//                    return PESOtoCAD(calendar) / USDtoCAD(calendar);
//                }
//                else
//                {
//                    return 0.0;
//                }
//            }
//            else
//            {
//                throw new Exception("Invalid currency " + currency);
//            }
//        }
//
//        // return convert to peso rate
//        public static double GetToPESORate(ExcoCalendar calendar, string currency)
//        {
//            if (0 == currency.CompareTo("CA"))
//            {
//                if (PESOtoCAD(calendar) > 0.00000001)
//                {
//                    return 1.0 / PESOtoCAD(calendar);
//                }
//                else
//                {
//                    return 0.0;
//                }
//            }
//            else if (0 == currency.CompareTo("US"))
//            {
//                // Change from corporate rate to col govt rate from FY2017 forward
//                if (PESOtoCAD(calendar) > 0.00000001 && calendar.GetFiscalYear() > 16)
//                {
//                    //Console.WriteLine("FY: " + calendar.GetFiscalYear() + "__FM: " + calendar.GetFiscalMonth());
//                    //Console.WriteLine(PESOtoCAD(calendar));
//                    //Console.WriteLine(ColGovtPesoToCad(calendar));
//                    return ColGovtPesoToCad(calendar);
//                }
//                else if (PESOtoCAD(calendar) > 0.00000001)
//                {
//                    return USDtoCAD(calendar) / PESOtoCAD(calendar);
//                }
//                else
//                {
//                    return 0.0;
//                }
//            }
//            else if (0 == currency.CompareTo("CP"))
//            {
//                return 1.0;
//            }
//            else
//            {
//                throw new Exception("Invalid currency " + currency);
//            }
//        }
//
//        // convert rate from 1 USD to x CAD
//        // use calendar year/period
//        public static double ColGovtPesoToCad(ExcoCalendar calendar)
//        {
//            int year = calendar.GetCalendarYear();
//            int month = calendar.GetCalendarMonth();
//            switch (year)
//            {
//                case 2016:
//                case 16:
//                    switch (month)
//                    {
//                        case 1:
//                            return 91;
//                        case 2:
//                            return 92; //
//                        case 3:
//                            return 93; //feb
//                        case 4:
//                            return 94;
//                        case 5:
//                            return 0;
//                        case 6:
//                            return 0;
//                        case 7:
//                            return 0; // June
//                        case 8:
//                            return 0; // July
//                        case 9:
//                            return 0;
//                        case 10:
//                            return 2879.95;
//                        case 11:
//                            return 2967.66;
//                        case 12:
//                            return 3165.09;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2017:
//                case 17:
//                    switch (month)
//                    {
//                        case 1:
//                            return 3000.71;
//                        case 2:
//                            return 2936.66; //feb
//                        case 3:
//                            return 2896.27; // mar
//                        case 4:
//                            return 2880.24; // apr
//                        case 5:
//                            return 2947.85; // may
//                        case 6:
//                            return 2920.42;
//                        case 7:
//                            return 3038.26; // 
//                        case 8:
//                            return 2995.23; //
//                        case 9:
//                            return 2937.09;
//                        case 10:
//                            return 2937.09;
//                        case 11:
//                            return 2937.09;
//                        case 12:
//                            return 2937.09;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                default:
//                    throw new Exception("Invalid year " + year.ToString());
//            }
//        }
//
//        // convert rate from 1 USD to x CAD
//        // use calendar year/period
//        public static double USDtoCAD(ExcoCalendar calendar)
//        {
//            int year = calendar.GetCalendarYear();
//            int month = calendar.GetCalendarMonth();
//            /*
//            string USD_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\usdexchrate.txt";
//            //string COP_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\copexchrate.txt";
//            bool got_year = false;
//            double exch_rate = 0;
//
//            var text = File.ReadAllText(USD_exch_path);
//            string[] lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
//            foreach (string line in lines)
//            {
//                if (line.Length > 1)
//                {
//                    if (line.Substring(1, 4) == year.ToString())
//                    {
//                        got_year = true;
//                    }
//                    if (got_year) //found year, begin getting exchange rate
//                    {
//                        string[] entries = line.Split(new string[] { ":" }, StringSplitOptions.None);
//                        if (entries[0] == month.ToString())
//                        {
//                            exch_rate = Convert.ToDouble(entries[1]);
//                            got_year = false;
//                            break;
//                        }
//                    }
//                }
//            }
//
//            return exch_rate;
//            */
//
//            switch (year)
//            {
//                case 2010:
//                case 10:
//                case 2011:
//                case 11:
//                    return 0.0;
//                case 2012:
//                case 12:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.02;
//                        case 2:
//                            return 1.0;
//                        case 3:
//                            return 0.99;
//                        case 4:
//                            return 1.0;
//                        case 5:
//                            return 0.99;
//                        case 6:
//                            return 1.03;
//                        case 7:
//                            return 1.02;
//                        case 8:
//                            return 1.0;
//                        case 9:
//                            return 0.99;
//                        case 10:
//                            return 0.98;
//                        case 11:
//                            return 1.0;
//                        case 12:
//                            return 0.99;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2013:
//                case 13:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.99;
//                        case 2:
//                            return 1.0;
//                        case 3:
//                            return 1.03;
//                        case 4:
//                            return 1.02;
//                        case 5:
//                            return 1.01;
//                        case 6:
//                            return 1.04;
//                        case 7:
//                            return 1.05;
//                        case 8:
//                            return 1.03;
//                        case 9:
//                            return 1.05;
//                        case 10:
//                            return 1.03;
//                        case 11:
//                            return 1.04;
//                        case 12:
//                            return 1.06;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2014:
//                case 14:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.06;
//                        case 2:
//                            return 1.11;
//                        case 3:
//                            return 1.11;
//                        case 4:
//                            return 1.11;
//                        case 5:
//                            return 1.10;
//                        case 6:
//                            return 1.08;
//                        case 7:
//                            return 1.07;
//                        case 8:
//                            return 1.09;
//                        case 9:
//                            return 1.09;
//                        case 10:
//                            return 1.12;
//                        case 11:
//                            return 1.13;
//                        case 12:
//                            return 1.14;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2015:
//                case 15:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.16;   //next
//                        case 2:
//                            return 1.27;
//                        case 3:
//                            return 1.25;
//                        case 4:
//                            return 1.27;
//                        case 5:
//                            return 1.21;
//                        case 6:
//                            return 1.24;//<--- MAY
//                        case 7:
//                            return 1.25;
//                        case 8:
//                            return 1.31;
//                        case 9:
//                            return 1.32;
//                        case 10:
//                            return 1.335;
//                        case 11:
//                            return 1.308; //oct
//                        case 12:
//                            return 1.335;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2016:
//                case 16:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.384;
//                        case 2:
//                            return 1.401; //
//                        case 3:
//                            return 1.353; //feb
//                        case 4:
//                            return 1.299;
//                        case 5:
//                            return 1.255;
//                        case 6:
//                            return 1.311;
//                        case 7:
//                            return 1.2917; // June
//                        case 8:
//                            return 1.306; // July
//                        case 9:
//                            return 1.312;
//                        case 10:
//                            return 1.312;
//                        case 11:
//                            return 1.341;
//                        case 12:
//                            return 1.343;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2017:
//                case 17:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.343;
//                        case 2:
//                            return 1.301; //
//                        case 3:
//                            return 1.328; //feb
//                        case 4:
//                            return 1.330;
//                        case 5:
//                            return 1.365;
//                        case 6:
//                            return 1.35;
//                        case 7:
//                            return 1.298; // June
//                        case 8:
//                            return 1.249; // July
//                        case 9:
//                            return 1.254;
//                        case 10:
//                            return 1.248;
//                        case 11:
//                            return 1.248;
//                        case 12:
//                            return 1.248;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2018:
//                case 18:
//                    switch (month)
//                    {
//                        case 1:
//                            return 1.343;
//                        case 2:
//                            return 1.343; //
//                        case 3:
//                            return 1.343; //feb
//                        case 4:
//                            return 1.330;
//                        case 5:
//                            return 1.330;
//                        case 6:
//                            return 1.330;
//                        case 7:
//                            return 1.330; // June
//                        case 8:
//                            return 1.330; // July
//                        case 9:
//                            return 1.330;
//                        case 10:
//                            return 1.330;
//                        case 11:
//                            return 1.330;
//                        case 12:
//                            return 1.330;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                default:
//                    throw new Exception("Invalid year " + year.ToString());
//            }
//
//        }
//
//        // convert rate from 1 PESO to x CAD
//        public static double PESOtoCAD(ExcoCalendar calendar, int year1 = 0, int month1 = 0)
//        {
//            int year = 0;
//            int month = 0;
//
//            // if not provided
//            if (year1 == 0 && month1 == 0)
//            {
//                year = calendar.GetCalendarYear();
//                month = calendar.GetCalendarMonth();
//            }
//            else
//            {
//                year = year1 - 1;
//                if ((month1 + 10) > 12)
//                {
//                    month = (month1 + 10) - 12;
//                    year = year1++;
//                }
//                else
//                {
//                    month = month1 + 10;
//                }
//            }
//
//            /*
//            //string USD_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\usdexchrate.txt";
//            string COP_exch_path = "\\\\10.0.0.6\\inetpub\\report system\\copexchrate.txt";
//            bool got_year = false;
//            double exch_rate = 0;
//
//            var text = File.ReadAllText(COP_exch_path);
//            string[] lines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
//            foreach (string line in lines)
//            {
//                if (line.Length > 1)
//                {
//                    if (line.Substring(1, 4) == year.ToString())
//                    {z
//                        got_year = true;
//                    }
//                    if (got_year) //found year, begin getting exchange rate
//                    {
//                        string[] entries = line.Split(new string[] { ":" }, StringSplitOptions.None);
//                        if (entries[0] == month.ToString())
//                        {
//                            exch_rate = Convert.ToDouble(entries[1]);
//                            got_year = false;
//                            break;
//                        }
//                    }
//                }
//            }
//             * 
//            return exch_rate;
//        }
//             */
//
//            switch (year)
//            {
//                case 2010:
//                case 10:
//                case 2011:
//                case 11:
//                    return 0.0;
//                case 2012:
//                case 12:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000525;
//                        case 2:
//                            return 0.000556;
//                        case 3:
//                            return 0.000558;
//                        case 4:
//                            return 0.000557;
//                        case 5:
//                            return 0.000560;
//                        case 6:
//                            return 0.000564;
//                        case 7:
//                            return 0.000571;
//                        case 8:
//                            return 0.000559;
//                        case 9:
//                            return 0.000540;
//                        case 10:
//                            return 0.000546;
//                        case 11:
//                            return 0.000546;
//                        case 12:
//                            return 0.000548;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2013:
//                case 13:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000563;
//                        case 2:
//                            return 0.000562;
//                        case 3:
//                            return 0.000567;
//                        case 4:
//                            return 0.000556;
//                        case 5:
//                            return 0.000551;
//                        case 6:
//                            return 0.000543;
//                        case 7:
//                            return 0.000546;
//                        case 8:
//                            return 0.000542;
//                        case 9:
//                            return 0.000545;
//                        case 10:
//                            return 0.000539;
//                        case 11:
//                            return 0.000552;
//                        case 12:
//                            return 0.000548;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2014:
//                case 14:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000551;
//                        case 2:
//                            return 0.000551;
//                        case 3:
//                            return 0.000541;
//                        case 4:
//                            return 0.000561;
//                        case 5:
//                            return 0.000567;
//                        case 6:
//                            return 0.000572;
//                        case 7:
//                            return 0.000568;
//                        case 8:
//                            return 0.000580;
//                        case 9:
//                            return 0.000567;
//                        case 10:
//                            return 0.000555;
//                        case 11:
//                            return 0.000547;
//                        case 12:
//                            return 0.000515;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2015:
//                case 15:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000486; //next
//                        case 2:
//                            return 0.000520;
//                        case 3:
//                            return 0.000520;
//                        case 4:
//                            return 0.000489;
//                        case 5:
//                            return 0.000505;
//                        case 6:
//                            return 0.000492;//<--- MAY
//                        case 7:
//                            return 0.00048; //<--- JUNE
//                        case 8:
//                            return 0.000456; //<--- JULY
//                        case 9:
//                            return 0.000432; //<--- AUG
//                        case 10:
//                            return 0.000435; //<--- SEPT
//                        case 11:
//                            return 0.000453; //<--- OCT
//                        case 12:
//                            return 0.000424; //<--- NOV
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2016:
//                case 16:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000436; // DEC
//                        case 2:
//                            return 0.000426;
//                        case 3:
//                            return 0.000407;
//                        case 4:
//                            return 0.000431;
//                        case 5:
//                            return 0.000440;
//                        case 6:
//                            return 0.000424;//<--- MAY
//                        case 7:
//                            return 0.000445;//<--- JUNE *check income statement
//                        case 8:
//                            return 0.000425;
//                        case 9:
//                            return 0.000444;
//                        case 10:
//                            return 0.000458;
//                        case 11:
//                            return 0.000447;
//                        case 12:
//                            return 0.000437;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                case 2017:
//                case 17:
//                    switch (month)
//                    {
//                        case 1:
//                            return 0.000448; // DEC
//                        case 2:
//                            return 0.000446;
//                        case 3:
//                            return 0.000453;
//                        case 4:
//                            return 0.000462;
//                        case 5:
//                            return 0.000463;
//                        case 6:
//                            return 0.000463;//<--- MAY
//                        case 7:
//                            return 0.000443;//<--- JUNE *check income statement
//                        case 8:
//                            return 0.000420;
//                        case 9:
//                            return 0.000424;
//                        case 10:
//                            return 0.000425;
//                        case 11:
//                            return 0.000425;
//                        case 12:
//                            return 0.000425;
//                        default:
//                            throw new Exception("Invalid month " + month.ToString());
//                    }
//                default:
//                    throw new Exception("Invalid year " + year.ToString());
//            }
//        }
//    }
//}
