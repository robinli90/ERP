using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility
{
    // processes money and currency conversion
    public class ExcoMoney
    {
        // money amount in CAD
        public double amountCA = 0.0;
        // money amount in USD
        public double amountUS = 0.0;
        // money amount in PESO
        public double amountCP = 0.0;
        // original currency
        public string currency = string.Empty;

        // constructor
        public ExcoMoney(ExcoCalendar calendar, double amount, string currency)
        {

            double x = 1;
            amountCA = amount * ExcoExRate.GetToCADRate(calendar, currency) * x;
            amountCP = amount * ExcoExRate.GetToPESORate(calendar, currency) * x;
            amountUS = amount * ExcoExRate.GetToUSDRate(calendar, currency) * x;
            this.currency = currency;

        }


        public ExcoMoney()
        {
        }

        // operator + overload
        public static ExcoMoney operator +(ExcoMoney m1, ExcoMoney m2)
        {
            ExcoMoney result = new ExcoMoney();
            result.amountCA = m1.amountCA + m2.amountCA;
            result.amountCP = m1.amountCP + m2.amountCP;
            result.amountUS = m1.amountUS + m2.amountUS;
            return result;
        }

        // operator - overload
        public static ExcoMoney operator -(ExcoMoney m1, ExcoMoney m2)
        {
            ExcoMoney result = new ExcoMoney();
            result.amountCA = m1.amountCA - m2.amountCA;
            result.amountCP = m1.amountCP - m2.amountCP;
            result.amountUS = m1.amountUS - m2.amountUS;
            result.currency = m1.currency;
            return result;
        }

        // operator / overload: m1 / m2
        public static double operator /(ExcoMoney m1, ExcoMoney m2)
        {
            if (Math.Abs(m2.amountUS) < 0.00001)
            {
                return 0.0;
            }
            else
            {
                return m1.amountUS / m2.amountUS;
            }
        }

        // money amount retriever
        public double GetAmount(string currency)
        {
            switch (currency)
            {
                case "CA":
                    return amountCA;
                case "US":
                    return amountUS;
                case "CP":
                    return amountCP;
                default:
                    throw new Exception("Invalid currency type: " + currency);
            }
        }

        // indicate if this money is zero
        public bool IsZero()
        {
            if (Math.Abs(amountCA) < 0.00001 && Math.Abs(amountCP) < 0.00001 && Math.Abs(amountUS) < 0.00001)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
