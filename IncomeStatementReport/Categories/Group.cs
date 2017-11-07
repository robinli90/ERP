using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;

namespace IncomeStatementReport.Categories
{
    public class Group
    {
        // markham
        public Plant plant01 = new Plant(1, "CA");
        // michigan
        public Plant plant03 = new Plant(3, "US");
        // texas
        public Plant plant05 = new Plant(5, "US");
        // colombia
        public Plant plant04 = new Plant(4, "CP");
        public Plant plant41 = new Plant(41, "CP");
        public Plant plant48 = new Plant(48, "CP");
        public Plant plant49 = new Plant(49, "CP");

        public string name = "";
        public ExcoCalendar calendar = new ExcoCalendar();
    }
}