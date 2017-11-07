
#include <stdlib.h>
#include <memory.h>
#include <time.h>

int CSQL_ConvertTime(const char *str, struct tm &tmval)
{
    if (!str || !str[0])
    {
        memset(&tmval, 0, sizeof(struct tm)) ; 
        return -1 ; 
    }

    // SQL datetime string returned as follows: 
    //      2007-10-20 17:35:14.920
    //      YYYY-MM-DD HH:MM:SS.SSS
    //      012345678901234567890123
    //                1         2   

    tmval.tm_sec = atoi(str+17) ;     /* seconds after the minute - [0,59] */
    tmval.tm_min = atoi(str+14) ;     /* minutes after the hour - [0,59] */
    tmval.tm_hour = atoi(str+11) ;    /* hours since midnight - [0,23] */
    tmval.tm_mday = atoi(str+8) ;    /* day of the month - [1,31] */
    tmval.tm_mon  = atoi(str+5) - 1 ;  /* months since January - [0,11] */
    tmval.tm_year = atoi(str) - 1900 ;   /* years since 1900 */
    tmval.tm_wday = 0 ;    /* days since Sunday - [0,6] */
    tmval.tm_yday = 0 ;    /* days since January 1 - [0,365] */
    tmval.tm_isdst = 0 ;   /* daylight savings time flag */

    return 0 ; 
}
