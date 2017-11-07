using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class GroupDeliveryAndSelling : ExcoCategory
    {
        #region Functions Definition
        // constructor
        public GroupDeliveryAndSelling()
        {
            sCategoryName = "DELIVERY AND SELLING";
        }

        // add group into category for Markham/Michigan/Texas
        protected override void AddGroup()
        {
            // advertising expense
            // air fare
            // auto operating expense
            // employee benefits
            // group insurance
            // non deductible exp golf
            // sales commissions
            // sales salaries
            // selling & travel expenses
            // selling & travel meals & enter
            // stat holiday
            // vacation pay
            // workers compensation
        }

        // add group into category for Colombia
        protected override void AddGroupColombia()
        {
            // advertising expense
            // air fare
            // auto operating expense
            // employee benefits
            // group insurance
            // non deductible exp golf
            // sales commissions
            // sales salaries
            // selling & travel expenses
            // selling & travel meals & enter
            // stat holiday
            // vacation pay
            // workers compensation
        }
        #endregion
    }
}
