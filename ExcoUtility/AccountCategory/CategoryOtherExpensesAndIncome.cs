using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class GroupOtherExpensesAndIncome : ExcoCategory
    {
        #region Functions Definition
        // constructor
        public GroupOtherExpensesAndIncome()
        {
            sCategoryName = "OTHER EXPENSES AND INCOME";
        }

        // add group into category for Markham/Michigan/Texas
        protected override void AddGroup()
        {
            // bad debt expense
            // bank charges
            // cash discounts earned
            // exchange gain/loss
            // gain/loss on asset disposal
            // incentive bonus expense
            // misc income/expense
            // non recurring expense
            // provision for income tax
            // reorg/severence costs
            // short term interest
        }

        // add group into category for Colombia
        protected override void AddGroupColombia()
        {
            // bad debt expense
            // bank charges
            // cash discounts earned
            // exchange gain/loss
            // gain/loss on asset disposal
            // incentive bonus expense
            // misc income/expense
            // non recurring expense
            // provision for income tax
            // reorg/severence costs
            // short term interest
        }
        #endregion
    }
}
