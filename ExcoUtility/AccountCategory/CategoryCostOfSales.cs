using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class GroupCostOfSales : ExcoCategory
    {
        #region Functions Definition
        // constructor
        public GroupCostOfSales()
        {
            sCategoryName = "COST OF SALES";
        }

        // add group into category for Markham/Michigan/Texas
        protected override void AddGroup()
        {
            // freight & duty in
            // intercompany purchases
            // matl parts non inventory
            // raw material steel usage
            // subcontract work
            // (increase)/decrease wip steel
        }

        // add group into category for Colombia
        protected override void AddGroupColombia()
        {
            // freight & duty in
            // intercompany purchases
            // matl parts non inventory
            // raw material steel usage
            // subcontract work
            // (increase)/decrease wip steel
        }
        #endregion

    }
}