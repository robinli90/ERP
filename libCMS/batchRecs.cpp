// batchRecs.cpp


#include "CMSBOMRTE.h"
#include "batchData.h"

int monmap[] = 
{
    4,        // 0 
    4,        // 1 
    5,        // 2 
    6,        // 3 
    7,        // 4 
    8,        // 5 
    9,        // 6  
    10,       // 7 
    11,       // 8 
    12,       // 9 
    1,        // 10 
    2,        // 11 
    3         // 12 
} ; 

int BatchHeader::SetString(char *buf) 
{
    memset(buf, 0x20, BATCH_HDR_LENGTH) ; 

    char tmpstr[64] ;
    StrCpyBlankFill(buf, "HDR", 3) ; 
    
    sprintf(tmpstr, "%02d%02d%02d", 
            reportdate.m_nMonth, 
            reportdate.m_nDay, 
            reportdate.m_nYear % 100) ; 
    
    StrCpyBlankFill(buf+3, tmpstr, 6) ; 
    buf[9] = '1' ; // always shift 1

    // Fiscal period is year an month where 
    // OCT=1, NOV=2, DEC=3, JAN=4, ....., SEP=12
    
    if (fiscYear == 0)
    {
        CDate date ;
        date.SetNow() ; 
        date.m_nMonth = monmap[date.m_nMonth] ; 
        int year = date.m_nYear ; 
        if (date.m_nMonth <= 3)
            year++ ; 
        sprintf(tmpstr, "%02d%02d", (year % 100), date.m_nMonth) ; 
    }
    else
        sprintf(tmpstr, "%02d%02d", fiscYear, fiscMonth) ; 
    StrCpyBlankFill(buf+10, tmpstr, 4) ; 

    StrCpyBlankFill(buf+18, "001", 3) ; 
    buf[21] = 0x0d ; 
    buf[22] = 0x0a ; 
    buf[23] = 0 ;

    return BATCH_HDR_LENGTH + 2 ; 
}


int BatchDetail::SetString(char *buf) 
{
    memset(buf, 0x20, BATCH_DTL_LENGTH) ; 

    StrCpyBlankFill(buf, "DTL", 3) ; 
    buf[3] = 'R' ; // RUN
    StrCpyBlankFill(buf+4,  dept+3,     2) ; // dept is PPPDD format (leading plant prefix)
    StrCpyBlankFill(buf+6,  resource,   5) ; 
    StrCpyBlankFill(buf+11, part,       20) ; 
    StrCpyBlankFill(buf+31, seqnum,     3) ; 
    StrCpyBlankFill(buf+34, indcode,    10) ; // should be blank
   
    int h ; 
    int m ; 

    double x, y, d;

    x = fabs(machtime) ; // Divide x into its fractional 
    y = modf( x, &d );     /* and integer parts            */

    h = (int)d ; 
    if (h > 99)
        h = 99 ; 
    m = (int)(y * 60.0) ; // convert to minutes
    if (m > 59)
        m = 59 ; 
    ZeroPadInt(buf+44,  h, 2) ; 
    ZeroPadInt(buf+46,  m, 2) ; 

    if (machtime < 0)
        buf[60] = 'Y' ; 

    StrCpyBlankFill(buf+48, orderNum,   10) ; 
    buf[66] = 0x0d ; 
    buf[67] = 0x0a ; 
    buf[68] = 0 ; 

    return BATCH_DTL_LENGTH + 2 ; 
}

int BatchPart::SetString(char *buf) 
{
    memset(buf, 0x20, BATCH_PRT_LENGTH) ; 

    char tmpstr[64] ; 
    StrCpyBlankFill(buf, "PRT", 3) ; 
    StrCpyBlankFill(buf+3,  partnum,    20) ; 
    ZeroPadDbl(buf+23,      fabs(qtygood),  10, 5) ; // quantity is always 1
    ZeroPadDbl(buf+38,      fabs(qtyscrap), 10, 5) ; // not used
    StrCpyBlankFill(buf+53, "EA",     3) ; // units
    StrCpyBlankFill(buf+56,  reason, 2) ; 
    StrCpyBlankFill(buf+58,  empdept, 2) ; 
    sprintf(tmpstr, "%5d", empnum) ; 
    StrCpyBlankFill(buf+60,  tmpstr,  5) ; 
    StrCpyBlankFill(buf+65,  chargedept, 2) ; 
    StrCpyBlankFill(buf+67,  chargeresc, 5) ; 

    if (qtygood < 0 || qtyscrap < 0)
        buf[72] = 'Y' ;  // reversing

    buf[89] = createserial ;
    StrCpyBlankFill(buf+90,  outlib,  10) ;   
    StrCpyBlankFill(buf+100,  queuename,  10) ;   
    StrCpyBlankFill(buf+110,  usr1,  20) ;   
    StrCpyBlankFill(buf+130, usr2,  20) ;   
    StrCpyBlankFill(buf+150, usr3,  20) ;   
    // voiding serial 170 for 11
    // product serial 181 for 30
    // No backflush   211 for 1    (set to Y if required)   
    buf[211] = nobackflush ; 
    // Scan ID        212 for 40  
    buf[252] = 0x0d ; 
    buf[253] = 0x0a ; 
    buf[254] = 0 ; 

    return BATCH_PRT_LENGTH + 2 ; 

}

int BatchMaterial::SetString(char *buf) 
{
    memset(buf, 0x20, BATCH_MAT_LENGTH) ; 

    char tmpstr[64] ;
    StrCpyBlankFill(buf, "MAT", 3) ; 
    StrCpyBlankFill(buf+3,  matpart,    20) ; 
    StrCpyBlankFill(buf+23, stockroom,  3) ; 
    buf[26] = reqmode ; 
    buf[27] = backflush ; 
    ZeroPadDbl(buf+28,      qty, 10, 5) ; 
    StrCpyBlankFill(buf+43, units,  3) ; 

    if (transdate.m_nYear)
    {
        sprintf(tmpstr, "%02d%02d%02d", 
                transdate.m_nMonth, 
                transdate.m_nDay, 
                transdate.m_nYear % 100) ; 
    }
    else
    {
        memset(tmpstr, 0x020, 16) ; 
    }
    StrCpyBlankFill(buf+46, tmpstr,  6) ; // set to blank so default is used

    StrCpyBlankFill(buf+52,  seqnum, 3) ; 
    StrCpyBlankFill(buf+55,  lotnum, 15) ; 
    ZeroPadInt(buf+70,       sernum, 11) ; 
    buf[81] = isScrap ; 
    buf[82] = 0x0d ; 
    buf[83] = 0x0a ; 
    buf[84] = 0 ; 

    return BATCH_MAT_LENGTH + 2 ; 

}


