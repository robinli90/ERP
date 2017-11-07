#include "stdafx.h"
#include <assert.h>
#include <cmath>
#include "CMSBOMRTE.h"


const char* BASERTE = 
"0000049   RTE1200001INEMPL INS000000000000010000000100C100000000010001010000000000000001Y000000000C                                        0000000000000000000000000000000000000000000000" ; 

const char *BASEBOM = 
"          BOM21800001HD 9 X 5 PLATE      00010000EA 000100RYYPRDY0001                                                                                                                    " ; 


// Copies the src string to dst for a maximum of count characters. If 
// src is less than count characters then dst is filled with blanks until
// count characters are copied. There is no terminating character. 
void StrCpyBlankFill(char *dst, const char *src, int count) 
{
    while (count && *src)
    {
        *dst++ = *src++ ; 
        count-- ; 
    }

    while (count)
    {
        *dst++ = 0x20 ; // space fill
        count-- ; 
    }
}

void StrCpyBlankFillRight(char *dst, const char *src, int count) 
{
    int n = (int)strlen(src) ; 
    if (n >= count)
        n = count ; 
    if (n < 0)
        n = 0 ; 
    while (count && n)
    {
        dst[count-1] = src[n-1] ; 
        count-- ; 
        n-- ; 
    }

    while (count)
    {
        dst[count-1] = 0x20 ; // space fill
        count-- ; 
    }
}


// The integer value is right justify into the string position at dst. The final
// output value is count characters long. No trailing characters are added and 
// there is no terminator. The value is padded in the front with 0's
// No checking is done to make sure the number fits into the space provided. 
void ZeroPadInt(char *dst, int val, int count) 
{
    char numstr[32] ; 
    sprintf(numstr, "%012d", abs(val)) ;
    size_t ix = strlen(numstr) ;
    ix-- ; // offset top last character
    dst += count - 1; 
    while (count)
    {
        count-- ; 
        *dst-- = numstr[ix--] ; 
    }
    if (val < 0)
    {
        dst++ ; // need to overwrite the first character
        *dst = '-' ; 
    }
}

// The floating point value is zero padded on the left and right based on the 
// number of integer characters and the decimal characters. The decimal is not
// output and is assumed to come exactly after the intcount position. 
void ZeroPadDbl(char *dst, double val, int intcount, int deccount)
{
    double w, f ; 
    int m, n, r ; 
    f = modf(fabs(val), &w) ; 
    
    // convert the whole number portion to an int
    m = (int)w ; 

    // convert decimal portion to an int (with rounding). 
    double decmult = pow(10.0, deccount) ; 
    int idecmult = (int)decmult ; 
    n = (int)(f * decmult) ; 
    r = (int)(f * pow(10.0, deccount+1)) ; 
    if (r - (n * 10) >= 5)
        n += 1 ; 
    if (n >= idecmult)
    {   // 0.99x rounded up to 100
        n = n % idecmult ; 
        m += 1 ; 
    }

    // Now fill in the two integers
    ZeroPadInt(dst, m, intcount) ; 
    ZeroPadInt(dst+intcount, n, deccount) ; 

    if (val < 0)
        *dst = '-' ; 
}
