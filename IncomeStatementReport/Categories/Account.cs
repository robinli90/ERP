using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReport.Categories
{
    public class Account
    {
        public string glNo1 = string.Empty;
        public string glNo2 = string.Empty;

        public Account(string glNo1, string glNo2)
        {
            this.glNo1 = glNo1;
            this.glNo2 = glNo2;
        }
    }
}
