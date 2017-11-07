/***************************************************************************
    Copyright (C) 1986-2011 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/
// strings.cpp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "csstrs.h"

#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS     1

// In place modifies the string to strip off leading and 
// trailing white space
void CS_LTrimString(char *str)
{
    char *s = str, *ps ; 
    if (!s)
        return ; // nothing to do, NULL pointer

    while (*s && isspace(*s)) s++ ; 
    
    if (*s)
    {   // Then we are on a non space style character
        // so copy everything back to the start trashing the leading 
        // whitespace
        ps = str ; 
        while (*s) *ps++ = *s++ ; 
        *ps = '\0' ; // NULL terminate the string
    }
    else
    {
        if (s != str)
        {   // Then the entire line was space
            *str = 0 ; // set to NULL string
        }
    }
}

void CS_RTrimString(char *str)
{
    char *s = str ; 
    if (!s)
        return ; // nothing to do, NULL pointer

    int slen = (int)strlen(str) ; 
    if (slen == 0)
        return ; // empty string so exit

    s = &str[slen - 1] ; // set to last character in the string
    while ((s >= str) && isspace(*s)) *s-- = 0 ;
}

void CS_TrimCharString(char *str) 
{
    CS_LTrimString(str) ; 
    CS_RTrimString(str) ; 
}


void CS_StringToUpper(char *ps)
{
    while (*ps) *ps++ = toupper(*ps) ;
}


// Copy only n characters and make sure dest is null terminated
char *CS_trmncpy(char *dst, char *src, int len) 
{
    strncpy(dst, src, len) ;
    dst[len-1] = 0 ; // make sure dest
    return dst ; 
}


// Returns true on success otherwise false and date values are unpredictable
// The date string format expected is 'JUN 10 99' for example
int CS_ExtractDateMMMDDYY(char *datestr, int *year, int *month, int *day)
{
    char wrkstr[16], *ps ; 
    
    CS_trmncpy(wrkstr, datestr, 16) ; 
    CS_StringToUpper(wrkstr) ; 
    
    if (strncmp("JAN", wrkstr, 3) == 0)
        *month = 1 ; 
    else if (strncmp("FEB", wrkstr, 3) == 0)
        *month = 2 ; 
    else if (strncmp("MAR", wrkstr, 3) == 0)
        *month = 3 ; 
    else if (strncmp("APR", wrkstr, 3) == 0)
        *month = 4 ; 
    else if (strncmp("MAY", wrkstr, 3) == 0)
        *month = 5 ; 
    else if (strncmp("JUN", wrkstr, 3) == 0)
        *month = 6 ; 
    else if (strncmp("JUL", wrkstr, 3) == 0)
        *month = 7 ; 
    else if (strncmp("AUG", wrkstr, 3) == 0)
        *month = 8 ; 
    else if (strncmp("SEP", wrkstr, 3) == 0)
        *month = 9 ; 
    else if (strncmp("OCT", wrkstr, 3) == 0)
        *month = 10 ; 
    else if (strncmp("NOV", wrkstr, 3) == 0)
        *month = 11 ; 
    else if (strncmp("DEC", wrkstr, 3) == 0)
        *month = 12 ; 
    else 
        return 0 ; 

    ps = strtok(&wrkstr[3], " ,/-:\\'") ; 

    if (ps) 
    {   // Then this is the day field which 
        *day = atoi(ps) ; 
        ps = strtok(NULL, " ,/-:\\'") ; 
        if (ps)
        {
            *year = atoi(ps) ; 
            return 1 ; 
        }
    }
    return 0 ; // some error occured 
}


