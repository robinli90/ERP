using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.Plant
{
    public abstract class ExcoPlant
    {
        #region Variables Definition
        // plant ID and name
        // 1. Markham
        // 3. Michigan
        // 4. Colombia
        // 5. Texas
        protected int iPlantID = 0;
        int PlantID
        {
            get
            {
                return iPlantID;
            }
        }
        protected string sPlantName = string.Empty;
        string PlantName
        {
            get
            {
                return sPlantName;
            }
        }

        // account map for a plant
        protected Dictionary<int, ExcoAccount> accountMap = new Dictionary<int, ExcoAccount>();
        Dictionary<int, ExcoAccount> AccountMap
        {
            get
            {
                return accountMap;
            }
        }

        // customer list for a plant
        protected List<ExcoCustomer> customerList = new List<ExcoCustomer>();
        List<ExcoCustomer> CustomerList
        {
            get
            {
                return customerList;
            }
        }

        // active fiscal year
        protected int iFiscalYear = 0;
        int FiscalYear
        {
            get
            {
                return iFiscalYear;
            }
        }

        // currency name
        // CA: canadian dollar
        // US: us dollar
        // CP: colombia peso
        protected string sCurrency = string.Empty;
        string Currency
        {
            get
            {
                return sCurrency;
            }
        }
        #endregion

        #region Functions Definition
        // get account data for a certain period
        public abstract void GetAccounts(int iFiscalYear);

        // get customer data for a certain period
        public abstract void GetCustomers(int iFiscalYear);
        #endregion
    }
}
