using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace IncomeStatementReportFrank
{
    public class Category
    {
        public List<Group> groupList = new List<Group>();
        public ExcoCalendar calendar = new ExcoCalendar();

        // group total for this category
        public Group total = new Group();

        public void AddAccount(string groupName, string groupID)
        {
            Group group = new Group(groupName, groupID);
            group.name = groupName;
            if (groupName != "STEEL SURCHARGE" && groupName != "OTHER SALES" && groupName != "PRODUCTION SALES")
            {
                group.GetInfo(calendar, groupID);
                total.tpActual += group.tpActual;
                total.tpActualRatio += group.tpActualRatio;
                total.lpActual += group.lpActual;
                total.lpActualRatio += group.lpActualRatio;
                total.tpBudget += group.tpBudget;
                total.tpBudgetRatio += group.tpBudgetRatio;
                total.ytdActual += group.ytdActual;
                total.ytdActualRatio += group.ytdActualRatio;
                total.ytdBudget += group.ytdBudget;
                total.ytdBudgetRatio += group.ytdBudgetRatio;
            }
            groupList.Add(group);
        }

        public Category ShallowCopy()
        {
            return (Category)MemberwiseClone();
        }

        public Category(ExcoCalendar calendar)
        {
            this.calendar = calendar;
            total.currency = "CA";
        }

        public void GetRatio(Category sales)
        {
            foreach (Group group in groupList)
            {
                group.tpActualRatio = -1.0 * (group.tpActual / sales.total.tpActual);
                group.tpBudgetRatio = -1.0 * (group.tpBudget / sales.total.tpBudget);
                group.lpActualRatio = -1.0 * (group.lpActual / sales.total.lpActual);
                group.ytdActualRatio = -1.0 * (group.ytdActual / sales.total.ytdActual);
                group.ytdBudgetRatio = -1.0 * (group.ytdBudget / sales.total.ytdBudget);
            }
            // get ratio for total group
            total.tpActualRatio = -1.0 * (total.tpActual / sales.total.tpActual);
            total.lpActualRatio = -1.0 * (total.lpActual / sales.total.lpActual);
            total.tpBudgetRatio = -1.0 * (total.tpBudget / sales.total.tpBudget);
            total.ytdActualRatio = -1.0 * (total.ytdActual / sales.total.ytdActual);
            total.ytdBudgetRatio = -1.0 * (total.ytdBudget / sales.total.ytdBudget);
        }
    }
}