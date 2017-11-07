using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility.AccountCategory
{
    public class GroupDirectLabour : ExcoCategory
    {
        #region Functions Definition
        // constructor
        public GroupDirectLabour()
        {
            sCategoryName = "DIRECT LABOUR";
        }

        // add group into category for Markham/Michigan/Texas
        protected override void AddGroup()
        {
            // direct labour shop
            // direct labour heat treat
            // cam salaries
            // cad salaries
            // supervisory salaries
            // indirect labour-iso/it/purch
            // employee benefits factory
            // group insurance factory
            // workers compensation
            // vacation pay expense
            // stat holiday
            // (increase)/decrease wip labour
        }

        // add group into category for Colombia
        protected override void AddGroupColombia()
        {
            // direct labour shop
            // direct labour heat treat
            // cam salaries
            // cad salaries
            // supervisory salaries
            // indirect labour-iso/it/purch
            // employee benefits factory
            // group insurance factory
            // workers compensation
            // vacation pay expense
            // stat holiday
            // (increase)/decrease wip labour
        }
        #endregion
    }
}
