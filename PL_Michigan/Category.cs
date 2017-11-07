using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace PL_Michigan
{
    public class Category
    {
        public List<Group> groupList = new List<Group>();
        public Group total = new Group();

        public void AddGroup(string name, string groupID)
        {
            Group group = new Group();
            group.name = name;
            group.groupID = groupID;
            groupList.Add(group);
        }

        public void GetRatio(Group salesTotal)
        {
            foreach (Group group in groupList)
            {
                if (Math.Abs(salesTotal.tpActual.amountUS) > 0.001)
                {
                    group.tpActualRatio = -1.0 * (group.tpActual / salesTotal.tpActual);
                    total.tpActualRatio += group.tpActualRatio;
                }
                if (Math.Abs(salesTotal.tpBudget.amountUS) > 0.001)
                {
                    group.tpBudgetRatio = -1.0 * (group.tpBudget / salesTotal.tpBudget);
                    total.tpBudgetRatio += group.tpBudgetRatio;
                }
                if (Math.Abs(salesTotal.ytdActual.amountUS) > 0.001)
                {
                    group.ytdActualRatio = -1.0 * (group.ytdActual / salesTotal.ytdActual);
                    total.ytdActualRatio += group.ytdActualRatio;
                }
                if (Math.Abs(salesTotal.ytdBudget.amountUS) > 0.001)
                {
                    group.ytdBudgetRatio = -1.0 * (group.ytdBudget / salesTotal.ytdBudget);
                    total.ytdBudgetRatio += group.ytdBudgetRatio;
                }
            }
        }
    }
}