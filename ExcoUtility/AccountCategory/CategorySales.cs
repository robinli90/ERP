using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class GroupSales : ExcoCategory
    {
        #region Functions Definition
        // constructor
        public GroupSales()
        {
            sCategoryName = "SALES";
        }

        // add group into category for Markham/Michigan/Texas
        protected override void AddGroup()
        {
            // sales canada
            ExcoGroup group = new ExcoGroup("SALES CANADA");
            groupList.Add(group);
            // sales canada steelsurcharge
            // sales usa
            // sales usa steel surcharge
            // sales south america
            // sales sth amer steel surcharge
            // sales europe
            // sales europe steel surcharge
            // sales pacific rim
            // sales pac rim steel surcharge
            // sales mexico
            // sales mexico steel surcharge
            // sales interdivision
            // sales interdiv steel surcharge
            // cash and volume discounts
            // delivery revenue
            // scrap sales
        }

        // add group into category for Colombia
        protected override void AddGroupColombia()
        {
            // sales canada
            ExcoGroup group = new ExcoGroup("SALES CANADA");
            groupList.Add(group);
            // sales canada steelsurcharge
            // sales usa
            // sales usa steel surcharge
            // sales south america
            // sales sth amer steel surcharge
            // sales europe
            // sales europe steel surcharge
            // sales pacific rim
            // sales pac rim steel surcharge
            // sales mexico
            // sales mexico steel surcharge
            // sales interdivision
            // sales interdiv steel surcharge
            // cash and volume discounts
            // delivery revenue
            // scrap sales
        }
        #endregion
    }
}
