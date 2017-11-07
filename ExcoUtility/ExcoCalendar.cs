using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExcoUtility
{
    public class ExcoCalendar
    {
        // here we store year/month in calendar
        // when output fiscal, convert into fiscal
#if DEBUG
        public int year = 0;
#else
        private int year = 0;
#endif
#if DEBUG
        public int month = 0;
#else
        internal int month = 0;
#endif
#if DEBUG
        public int plantID = 0;
#else
        internal int plantID = 0;
#endif

        public ExcoCalendar()
        {

        }

        public ExcoCalendar(int year, int month, bool isFiscal, int plantID)
        {
            this.plantID = plantID;
            if (isFiscal && 4 != plantID && 48 != plantID)
            {
                if (month < 4)
                {
                    this.year = year - 1;
                    this.month = month + 9;
                }
                else
                {
                    this.year = year;
                    this.month = month - 3;
                }
            }
            else
            {
                this.year = year;
                this.month = month;
            }
        }

        // get fiscal year
        public int GetFiscalYear()
        {
            if (4 != plantID && 48 != plantID)
            {
                if (month < 10)
                {
                    return year;
                }
                else
                {
                    return year + 1;
                }
            }
            else
            {
                return year;
            }
        }

        // get fiscal month
        public int GetFiscalMonth()
        {
            if (4 != plantID && 48 != plantID)
            {
                if (month < 10)
                {
                    return month + 3;
                }
                else
                {
                    return month - 9;
                }
            }
            else
            {
                return month;
            }
        }

        // get calendar year
        public int GetCalendarYear()
        {
            return year;
        }

        // get calendar month
        public int GetCalendarMonth()
        {
            return month;
        }

        // get next calendar month
        public ExcoCalendar GetNextCalendarMonth()
        {
            ExcoCalendar calendar = new ExcoCalendar(year, month, false, plantID);
            if (month > 11)
            {
                calendar.month = 1;
                calendar.year += 1;
            }
            else
            {
                calendar.month += 1;
            }
            return calendar;
        }

        // get last calendar month
        public ExcoCalendar GetLastCalendarMonth()
        {
            ExcoCalendar calendar = new ExcoCalendar(year, month, false, plantID);
            if (month < 2)
            {
                calendar.month = 12;
                calendar.year -= 1;
            }
            else
            {
                calendar.month -= 1;
            }
            return calendar;
        }

        // get calendar month at last year
        public ExcoCalendar GetCalendarMonthLastYear()
        {
            ExcoCalendar calendar = new ExcoCalendar(year - 1, month, false, plantID);
            return calendar;
        }
    }
}
