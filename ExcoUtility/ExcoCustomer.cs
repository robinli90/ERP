using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility
{
    public class ExcoCustomer
    {
        // bill-to id
        public string BillToID
        {
            get;
            set;
        }

        // ship-to id
        public string ShipToID
        {
            get;
            set;
        }

        // silly id
        public string SillyID
        {
            get;
            set;
        }


        // customer name
        public string Name
        {
            get;
            set;
        }

        // currency
        public string Currency
        {
            get;
            set;
        }

        // territory
        public string Territory
        {
            get;
            set;
        }
    }
}
