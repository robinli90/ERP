/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
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
#include <stdlib.h>
#include <ctype.h>

const char CS_COPYRIGHT_MESSAGE[] = "Copyright 1991-2009, Cadamation Systems, All rights reserved." ; 

#include "csstring.h"

#ifndef min
#define  min(a,b)           (((a) < (b)) ? (a) : (b))
#endif


char *CS_istrstr(char *pstr, char *pkey) 
{
    int n = strlen(pkey) ; 
    while (*pstr)
    {
        if (_strnicmp(pstr, pkey, n) == 0)
            return pstr ; 
        pstr++ ; 
    }
    return 0 ; 
}

// In place modifies the string to strip off leading and 
// trailing white space
void CS_TrimLeftString(char *str)
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
            *str = 0 ; // set to empty string
        }
    }
}

void CS_TrimRightString(char *str)
{
    char *s = str ; 
    if (!s)
        return ; // nothing to do, NULL pointer

    size_t slen = strlen(str) ; 
    if (slen == 0)
        return ; // empty string so exit

    s = &str[slen - 1] ; // set to last character in the string
    while ((s >= str) && isspace(*s)) *s-- = 0 ;
}

void CS_TrimString(char *str) 
{
    CS_TrimLeftString(str) ; 
    CS_TrimRightString(str) ; 
}


void CS_StringToUpper(char *ps)
{
    while (*ps) *ps++ = toupper(*ps) ;
}


// Copy only n characters and make sure dest is null terminated
char *CS_trmncpy(char *dst, char *src, int len) 
{
    strncpy(dst, src, len) ;
    dst[len-1] = 0 ; // make sure dest is null terminated
    return dst ; 
}

// strncpy without padding plus always adds null byte, 
// returns a pointer to the last character in the destination string
// The destination string must be 1 byte longer than maxlen. 
char *CS_strmaxcpy(char *dst, const char *src, int maxlen)
{
    if (!src || !src[0])
    {
        dst[0] = 0 ; 
        return (char *)dst ; 
    }

    char *s = (char *)src ; 
    while (*s && maxlen > 0)
    {
        *dst++ = *s++ ; 
        maxlen-- ; 
    }
    *dst = 0 ; 
    return dst ; 
}

// Same as CS_strmaxcpy except returns the number of bytes copied 
// (not including the terminating null). By adding the int you end 
// up on the terminating NULL from the input dst byte. 
int CS_strmaxcat(char *dst, const char *src, int maxlen)
{
    if (!src || !src[0])
    {
        dst[0] = 0 ; 
        return 0 ; 
    }

    int len = 0 ; 
    char *s = (char *)src ; 
    while (*s && len < maxlen)
    {
        *dst++ = *s++ ; 
        len++ ; 
    }
    *dst = 0 ; 
    return len ; 
}

char *CS_strcpy(char *dst, const char *src)
{
    if (!src || !src[0])
    {
        dst[0] = 0 ; 
        return (char *)dst ; 
    }

    char *s = (char *)src ; 
    while (*s)
        *dst++ = *s++ ; 

    *dst = 0 ; 
    return dst ; 
}

char *CS_strtok(charptr &ps, const char *delim)
{
    if (!ps || !(*ps))
        return 0 ; 
    char *ptok = ps ; 
    char *s = ps ; 
    int n = strlen(delim) ; 
    while (*s && strncmp(s, delim, n) != 0)
        s++ ; 
    if (*s)
    {
        *s = 0 ; 
        ps = s + 1 ; 
    }
    else
    {
        ps = s ; 
    }
    return ptok ; 
}


// Returns true on success otherwise false and date values are unpredictable
// The date string format expected is 'JUN 10 99' for example
int CS_ExtractDateMMMDDYY(char *datestr, int *year, int *month, int *day)
{
    char wrkstr[16], *ps ; 
    
    CS_trmncpy(wrkstr, datestr, 16) ; 
    CS_StringToUpper(wrkstr) ; 
    
    if (strncmp("JAN", datestr, 3) == 0)
        *month = 1 ; 
    else if (strncmp("FEB", datestr, 3) == 0)
        *month = 2 ; 
    else if (strncmp("MAR", datestr, 3) == 0)
        *month = 3 ; 
    else if (strncmp("APR", datestr, 3) == 0)
        *month = 4 ; 
    else if (strncmp("MAY", datestr, 3) == 0)
        *month = 5 ; 
    else if (strncmp("JUN", datestr, 3) == 0)
        *month = 6 ; 
    else if (strncmp("JUL", datestr, 3) == 0)
        *month = 7 ; 
    else if (strncmp("AUG", datestr, 3) == 0)
        *month = 8 ; 
    else if (strncmp("SEP", datestr, 3) == 0)
        *month = 9 ; 
    else if (strncmp("OCT", datestr, 3) == 0)
        *month = 10 ; 
    else if (strncmp("NOV", datestr, 3) == 0)
        *month = 11 ; 
    else if (strncmp("DEC", datestr, 3) == 0)
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


//////////////////////////////////////////////////////////////////////////////
// csString class functions
//////////////////////////////////////////////////////////////////////////////
csString::csString() 
{
    str = 0 ; 
    len = 0 ; 
    idx = 0 ; 
}


// allocate space for string and set to NULL
csString::csString(const int n) 
{
    if (n > 0)
    {   // This is defined for special applications where the user
        // will operate on the internal variables directly
        str = (char *)malloc(n) ;
        str[0] = 0 ;
        idx = 0 ;
        len = 0 ; 
    }
    else
    {
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}


csString::csString(const char c)
{
    if (c)
    {   // Then there is something to do
        len = 1 ; 
        str = (char *)malloc(2) ; 
        if (str)
        {
            str[0] = c ; 
            str[1] = 0 ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}

/*
csString::csString(char *ps)
{
    if (ps && *ps)
    {   // Then there is something to do
        len = strlen(ps) ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, ps) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}
*/

csString::csString(const char *ps)
{
    if (ps && *ps)
    {   // Then there is something to do
        len = (int)strlen(ps) ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, ps) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}


csString::csString(const char c, const int n)
{
    if (n > 0)
    {
        len = n + 1 ; 
        str = (char *)malloc(len + 1) ; 
        int i ;
        for (i=0; i < len; i++)
            str[i] = c ; 
        str[i] = 0  ;
    }
    else
    {   // We're creating a NULL object
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}


csString::csString(const char *ps, const int initlen)
{
    if (ps && *ps && initlen > 0)
    {   // Then there is something to do
        len = min(initlen, (int)strlen(ps)) ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strncpy(str, ps, len) ; 
            str[len] = 0 ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}

// copy constructor
csString::csString(const csString &refstr)
{
    if (refstr.str && *(refstr.str) && refstr.len > 0)
    {   // Then there is something to do
        len = refstr.len ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, refstr.str) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {   // We're creating a NULL object
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
}


// copies the string without allocating new memory if possible
csString &csString::SetString(const char *ps, int inputlen) 
{
    if (ps && *(ps))
    {   // Then there is something to do
        // Free up any memory that is currently used
        int maxlen =  0 ;
        if (inputlen)
            maxlen = inputlen ; 
        else
            maxlen = (int)strlen(ps) ; 

        if (maxlen < len)
        {   // Simply copy over the string
            int i ; 
            for (i=0; i < maxlen && ps[i]; i++)
                str[i] = ps[i] ;
            str[i] = 0 ; 
            len = i ; 
            idx = 0 ;
            return *this ; 
        }

        // Else we're starting from scratch
        if (str)
            free(str) ; 

        len = maxlen ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strncpy(str, ps, maxlen) ; 
            str[maxlen] = 0 ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {   // Setting a NULL string
        if (str)
            free(str) ; 
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }

    return *this ;
}


csString &csString::operator=(const csString &refstr)
{
    if (refstr.str && *(refstr.str) && refstr.len > 0)
    {   // Then there is something to do
        // Free up any memory that is currently used
        if (str)
            free(str) ; 

        len = refstr.len ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, refstr.str) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {   // Setting a NULL string
        if (str)
            free(str) ; 
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }

    return *this ;
}


/*
csString &csString::operator=(char *pstr)
{
    if (pstr && *pstr)
    {   // Then there is something to do
        // Free up any memory that is currently used
        if (str)
            free(str) ; 

        len = strlen(pstr) ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, pstr) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {   // Setting a NULL string
        if (str)
            free(str) ; 
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }

    return *this ;
}
*/

csString &csString::operator=(const char *pstr)
{
    if (pstr && *pstr)
    {   // Then there is something to do
        // Free up any memory that is currently used
        if (str)
            free(str) ; 

        len = (int)strlen(pstr) ; 
        str = (char *)malloc(len + 1) ; 
        if (str)
        {
            strcpy(str, pstr) ; 
            idx = 0 ;
        }
        else
        {
            len = 0 ; 
            idx = 0 ; 
        }
    }
    else
    {   // Setting a NULL string
        if (str)
            free(str) ; 
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }

    return *this ;
}


csString::~csString()
{
    if (str)
    {   // Then we have to de-allocate memory here
        free(str) ; 
    }
}


char &csString::operator[](const int charidx) 
{
    if (charidx < len)
    {
        return str[charidx] ; 
    }
    else
    {   // Return the last character in the string (the NULL terminator)
        if (!str)
        {
            str = (char *)malloc(4) ; // then we have to allocate space for this string
            len = 0 ; 
            str[0] = 0 ; 
        }

        return str[len] ; 
    }
}


void csString::Erase(int startfrom)
{
    if (startfrom == 0)
    {
        if (str)
            free(str) ; 
        str = 0 ; 
        len = 0 ; 
        idx = 0 ; 
    }
    else
    {
        if (startfrom < len)
        {   // Then we can do it
            len = startfrom ; 
            str[len] = 0 ; 
        }
    }
}


char *csString::Remove(int index, int length)
{
    if (index > len)
    {
        if (str)
            return str+len ; 
        return 0 ; 
    }

    if (index + length >= len)
    {
        str[index] = 0 ; 
        len = index ; 
        return str+len ; 
    }
    
    int i ; 
    for (i=index; i < len - length; i++) 
    {
        str[i] = str[i+length] ; 
    }

    str[i] = 0 ; 
    len -= length ; 
    if (len < 0)
    {
        free(str) ; 
        str = 0 ; 
        len = 0 ; 
        return 0 ; 
    }

    return &str[index]; 
}

csString &csString::RemoveSpaces(int index, int maxlen) 
{   
    if (!str)
        return *this ; // nothing to do

    int maxcount = 0 ; 
    char *psrc = str + index ; 
    char *pdst = psrc ; // where we will copy to. 

    do {
        if (isspace(*psrc))
            psrc++ ; 
        else 
            *pdst++ = *psrc++ ; 
        if (maxlen)
        {
            maxcount++ ; 
            if (maxcount >= maxlen)
                break ; 
        }
    } while (*psrc) ; 

    if (*psrc && maxlen && maxcount >= maxlen )
    {   // move the remainder of the string if we need to. 
        while (*psrc) 
            *pdst++ = *psrc ; 
    }

    return *this ; 
}

csString &csString::RemoveChars(char *rmchars, int index, int length)
{
    if (!str || !rmchars || !(*rmchars))
        return *this ; 

    char *psrc = str + index ; 
    char *pdst = psrc ; 
    if (length == 0) length-- ; 

    while (length-- && *psrc)
    {
        char *s = rmchars ; 
        while (*s)
        {
            if (*psrc == *s)
                break ; 
            s++ ; 
        }
        
        if (*s)
        {   // Found match
            psrc++ ; 
            len-- ; 
        }
        else
        {   // copy it over
            *pdst++ = *psrc++ ; 
        }
    }
    *pdst = 0 ; 

    return *this ; 
}


// Removes strings from the string 
csString &csString::RemoveStrings(char *rmstr, int index, int length)
{
    if (!str || !rmstr || !(*rmstr))
        return *this ; 

    char *psrc = str + index ;
    char *pdst = psrc ;
    int n = strlen(rmstr) ; 
    if (length == 0) length-- ;

    while (length-- && *psrc)
    {
        char *s = rmstr ; 
        while (*s)
        {
            if (*psrc != *s)
                break ; 
            s++ ; 
        }
        
        if (*s)
        {   // no match 
            *pdst++ = *psrc++ ; 
        }
        else
        {   // delete out the string
            psrc += n ; 
            length -= n-1 ; 
            len -= n ; 
        }
    }
    *pdst = 0 ; 

    return *this ; 
}

csString &csString::ReplaceStrings(char *srch, char *repl, int index, int length)
{
    if (!str || !srch || !(*srch))
        return *this ; 

    int si = index ;
    int di = si ;
    int srchlen = strlen(srch) ; 
    int repllen = strlen(repl) ; 
    if (length == 0) length-- ;

    while (length-- && str[si])
    {
        char *s = srch ; 
        while (*s)
        {
            if (str[si] != *s)
                break ; 
            s++ ; 
        }
        
        if (*s)
        {   // no match 
            str[di++] = str[si++] ; 
        }
        else
        {   // replace the string
            if (repllen > srchlen)
            {
                s = (char *)realloc(str, len + repllen - srchlen) ; 
                if (!s)
                    return *this ; 
                str = s ; 
                // Now shift the string out to make space
                len += (srchlen-repllen) ; 
                int f = len ; 
                while (f > si)
                {
                    str[f] = str[f-1] ; 
                    f-- ; 
                }
            }
            
            // Copy the replace pattern in
            int i = 0 ; 
            s = repl ;
            while (*s)
                str[di++] = *s++ ; 

            si += repllen ; 
            length -= srchlen-1 ; 

            if (srchlen > repllen)
                len -= srchlen - repllen ; 
        }
    }

    return *this ; 
}


char *csString::Insert(char c, int index)
{
    char *pret = 0 ; 
    if (index > len)
    {
        int n = len ; 
        char *s = (char *)realloc(str, index + 2) ; 
        if (!s)
            return 0 ; 
        str = s ; 
        len = index ;
        while (n < index)
            str[n++] = 0x20 ; 
        str[n++] = c ; 
        str[n] = 0 ; 
        pret = &str[n-1] ; 
    }
    else
    {
        len += 1 ; // adding a character
        char *s = (char *)realloc(str, len + 1) ; 
        if (!s)
            return 0 ; 
        str = s ; 
        int i ; 
        for (i=len-1; i > index; i--)
            str[i] = str[i-1] ; 
        str[i] = c ; 
        pret = &str[i] ; 
    }
    return pret ; 
}

char *csString::Insert(char *ps, int index) 
{
    if (!ps || !(*ps))
        return 0 ; // nothing to do

    char *pret = 0 ; 
    int inslen = (int)strlen(ps) ; 
    if (index > len)    
    {   // Need to pad string
        int n = len ; 
        char *s = (char *)realloc(str, index + inslen + 1) ;
        if (!s)
            return 0 ; 
        str = s ; 
        len = index + inslen ;
        while (n < index)
            str[n++] = 0x20 ; 
        s = &str[n] ; 
        while (*s++ = *ps++ ) ; 
        *s = 0 ; 
    }
    else
    {
        char *s = (char *)realloc(str, len + inslen + 1) ; 
        if (!s)
            return 0 ; 
        str = s ; 
        int i ;
        for (i=len+inslen; i > index; i--)
            str[i] = str[i-inslen] ; 
        len += inslen ; // adding a character
        for (i=index; inslen > 0; i++, inslen--) ; 
            str[index+i] = *ps++ ; 
    }
    return &str[index] ; 
}

char *csString::Insert(csString &rs, int index)
{
    return Insert(rs.str, index) ; 
}

char *csString::Insert(csString *ps, int index) 
{
    return Insert(ps->str, index) ; 
}

// trim white space off both ends
csString &csString::Trim(int n)
{
    TrimLeft(n) ; 
    TrimRight(n) ;
    return *this ; 
}


// trim white space off the right end
csString &csString::TrimRight(int n) 
{
    if (!str)
        return *this ; // nothing to do, NULL pointer

    if (len == 0)
        return *this ; // empty string so exit

    if (n==0)
    {
        while ((len > 0) && isspace(str[len-1]))
            str[--len] = 0 ;
    }
    else
    {
        len -= n ; 
        if (len <= 0)
        {
            if (str)
                free(str) ; 
            str = 0 ; 
            len = 0 ; 
            idx = 0 ; 
        }
        else
            str[len] = 0 ; 
    }

    return *this ; 
}


// trim white space off the left end
csString &csString::TrimLeft(int n) 
{
    char *s = str, *ps ; 
    if (!str)
        return *this ; // nothing to do, NULL pointer

    if (n == 0)
    {
        while (*s && isspace(*s)) s++ ; 
    }
    else
    {
        if (n >= len)
        {
            if (str)
                free(str) ; 
            str = 0 ; 
            len = 0 ; 
            idx = 0 ; 
            return *this ; 
        }
        else
            s += n ; 
    }

    
    if (*s)
    {   // Then we are on a non space style character
        // so copy everything back to the start trashing the leading 
        // whitespace
        ps = str ; 
        len = 0 ; 
        while (*s) 
        {
            *ps++ = *s++ ; 
            len++ ;
        }
        *ps = '\0' ; // NULL terminate the string
    }
    else
    {
        if (s != str)
        {   // Then the entire line was space
            *str = 0 ; // set to NULL string
            len = 0 ; 
        }
    }
    return *this ; 
}


// take left most n characters
csString csString::Left(const int n) const
{
    csString res(str, n) ; 
    return res ; 
}


// take right most n characters
csString csString::Right(const int n) const
{
    csString ret ; 

    if (n >= len)
        ret = *this ; 
    else
        ret = csString(&str[len - n]) ; 

    return ret ;
}

// characters from idx for len 
csString csString::Mid(const int n, const int midlen) const
{
    csString ret ; 

    if (n < len)
    {
        if (midlen > 0)
            ret = csString(&str[n], midlen) ; 
        else if (midlen < 0)
            ret = csString(&str[n]) ; // rest of string from n onwards
    }

    return ret ;
}


bool csString::operator==(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) == 0)
            return 1 ; 
        return 0 ; 
    }

    if (!str && !b.str)
        return 1 ; 
    return 0 ; 
}

bool  csString::operator==(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) == 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (!b && !str)
        return 1 ; 
    return 0 ; 
}

bool  csString::operator!=(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) != 0)
            return 1 ; 
        return 0 ; 
    }

    if (!b.str && !str)
        return 0 ; 
    return 1 ; 
}

bool  csString::operator!=(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) != 0)
            return 1 ; 
        return 0 ; 
    }

    if (!b && !str)
        return 0 ; 
    return 1 ; 
}

bool  csString::operator<(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) < 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str) // then str == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}       

bool  csString::operator<(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) < 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (b) // then str == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}


bool  csString::operator>(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) > 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (str) // then b == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}

bool  csString::operator>(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) > 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (str) // then b == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}


bool  csString::operator<=(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) <= 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (str)
        return 0 ; 
    return 1 ; // both NULL
}

bool  csString::operator<=(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) <= 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (str)
        return 0 ; 
    return 1 ; // both NULL
}


bool  csString::operator>=(const csString &b) 
{
    if (str && b.str)
    {
        if (strcmp(str, b.str) >= 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str)
        return 0 ; 
    return 1 ; 
}

bool  csString::operator>=(const char *b) 
{
    if (str && b)
    {
        if (strcmp(str, b) >= 0)
            return 1 ; 
        return 0 ; 
    }

    if (b)
        return 0 ; 
    return 1 ; 
}



char *csString::FindOneOf(char *ps, int startidx)
{
    int i ; 
    char *tc ; 
    if (startidx >= len)
        return 0 ; 
    
    for (i=startidx; i < len; i++)
    {
        tc = ps ; 
        while (*tc)
        {
            if (*tc == str[i])
                return str+i ; 
            tc++ ; 
        }
    }
    return 0 ; 
}

int csString::FindOneOfIDX(char *ps, int startidx)
{
    char *tc ; 
    tc = FindOneOf(ps, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


char *csString::FindOneOf(csString &b, int startidx)
{
    int i ; 
    char *tc ; 

    if (startidx >= len)
        return 0 ; 

    for (i=startidx; i < len; i++)
    {
        tc = b.str ; 
        while (*tc)
        {
            if (*tc == str[i])
                return str+i ; 
            tc++ ; 
        }
    }
    return 0 ; 
}

int csString::FindOneOfIDX(csString &b, int startidx)
{
    char *tc ; 
    tc = FindOneOf(b, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


char *csString::FindLastOneOf(char *ps, int startidx)
{
    int i ; 
    char *tc ; 

    if (startidx == -1)
        startidx = len - 1 ; 

    for (i=startidx ; i >= 0; i--)
    {
        tc = ps ;
        while (*tc)
        {
            if (*tc == str[i])
                return str+i ;
            tc++ ; 
        }
    }
    return 0 ; 
}

int csString::FindLastOneOfIDX(char *ps, int startidx)
{
    char *tc ; 
    tc = FindLastOneOf(ps, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


char *csString::FindLastOneOf(csString &b, int startidx) 
{
    int i ; 
    char *tc ; 

    if (startidx == -1)
        startidx = len - 1 ; 

    for (i=startidx; i >= 0; i--)
    {
        tc = b.str ;
        while (*tc)
        {
            if (*tc == str[i])
                return str+i ;
            tc++ ; 
        }
    }
    return 0 ; 
}

int csString::FindLastOneOfIDX(csString &b, int startidx) 
{
    char *tc ; 
    tc = FindLastOneOf(b, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}



char *csString::Find(char c, int startidx) 
{
    int i ; 
    for (i=startidx; i < len; i++)
    {
        if (c == str[i])
            return str+i ; 
    }
    return 0 ; 
}

int csString::FindIDX(char c, int startidx)
{
    char *tc ; 
    tc = Find(c, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


char *csString::Find(const char *ps, int startidx)
{
    if (!ps)
        return 0 ; 
    int slen = (int)strlen(ps) ; 
    for (int i=startidx; i < len - slen + 1; i++)
    {
        if (strncmp(&str[i], ps, slen) == 0)
            return &str[i] ;
    }
    return 0 ; 
}

int csString::FindIDX(const char *ps, int startidx)
{
    char *tc ; 
    tc = Find(ps, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


// find first occurence of b in string
char *csString::Find(csString &b, int startidx) 
{
    if (!b.str)
        return 0 ; 
    int slen = (int)strlen(b.str) ; 
    for (int i=startidx; i < len - slen + 1; i++)
    {
        if (strncmp(&str[i], b.str, slen) == 0)
            return &str[i] ;
    }
    return 0 ; 
}

int csString::FindIDX(csString &b, int startidx) 
{
    char *tc ; 
    tc = Find(b, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}



// ------------------------------------------------------------------------
// Ignore case find 
char *csString::icFind(char c, int startidx) 
{
    int i ; 
    for (i=startidx; i < len; i++)
    {
        if (toupper(c) == toupper(str[i]))
            return str+i ; 
    }
    return 0 ; 
}

int csString::icFindIDX(char c, int startidx)
{
    char *tc ; 
    tc = icFind(c, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


char *csString::icFind(const char *ps, int startidx)
{
    if (!ps)
        return 0 ; 
    int slen = (int)strlen(ps) ; 
    for (int i=startidx; i < len - slen + 1; i++)
    {
#ifdef WIN32
        if (_strnicmp(&str[i], ps, slen) == 0)
#else
        if (strncasecmp(&str[i], ps, slen) == 0)
#endif
            return &str[i] ;

    }
    return 0 ; 
}

int csString::icFindIDX(const char *ps, int startidx)
{
    char *tc ; 
    tc = icFind(ps, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


// find first occurence of b in string
char *csString::icFind(const csString &b, int startidx) const
{
    if (!b.str)
        return 0 ; 
    int slen = (int)strlen(b.str) ; 
    for (int i=startidx; i < len - slen + 1; i++)
    {
#ifdef WIN32
        if (_strnicmp(&str[i], b.str, slen) == 0)
#else
        if (strncasecmp(&str[i], b.str, slen) == 0)
#endif
            return &str[i] ;
    }
    return 0 ; 
}

int csString::icFindIDX(const csString &b, int startidx) const
{
    char *tc ; 
    tc = icFind(b, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}

// ------------------------------------------------------------------------

// reverse find
char *csString::FindLast(const char c, int startidx) 
{
    if (!c)
    {
        if (str && len)
            return &str[len] ; 
        return 0 ; 
    }

    if (startidx == -1)
        startidx = len - 1 ; 
    for (int i=startidx; i >=0 ; i--)
    {
        if (str[i] == c)
            return &str[i] ;
    }
    return 0 ; 
}

int csString::FindLastIDX(const char c, int startidx) 
{
    if (!c)
    {
        if (str && len)
            return len ; 
        return -1 ; 
    }

    if (startidx == -1)
        startidx = len - 1 ; 
    for (int i=startidx; i >=0 ; i--)
    {
        if (str[i] == c)
            return i ;
    }
    return -1 ; 
}



char *csString::FindLast(const char *ps, int startidx) 
{
    if (!ps || *ps == 0)
        return 0 ; 

    int slen = (int)strlen(ps) ; 
    if (startidx == -1)
        startidx = len - slen ; 
    else
    {
        if (len - startidx < slen)
            startidx = len - slen ; 
    }

    // 0123456789
    // abcdefghij
    //       cdef

    for (int i=startidx; i >=0 ; i--)
    {
        if (strncmp(&str[i], ps, slen) == 0)
            return &str[i] ;
    }
    return 0 ; 
}

int csString::FindLastIDX(const char *ps, int startidx) 
{
    char *tc ; 
    tc = FindLast(ps, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


// reverse find 
char *csString::FindLast(csString &b, int startidx)
{
    if (!b.str)
        return 0 ; 
    
    int slen = b.len ; 

    if (startidx == -1)
        startidx = len - slen ; 
    else
    {
        if (len - startidx < slen)
            startidx = len - slen ; 
    }

    // 0123456789
    // abcdefghij
    //       cdef

    for (int i=startidx; i >=0 ; i--)
    {
        if (strncmp(&str[i], b.str, slen) == 0)
            return &str[i] ;
    }
    return 0 ; 
}

int csString::FindLastIDX(csString &b, int startidx)
{
    char *tc ; 
    tc = FindLast(b, startidx) ; 
    if (!tc)
        return -1 ; 
    return (int)(tc - str) ; 
}


///////////////////////////////////////////////////////////////////////////
// extract token starting at the
// offset specified, if ofsidx is not -1 then the internal idx pointer is 
// initialized to maintain where we are in the string. If ofsidx == -1 then
// the search starts from the current value of ofsidx. The token is 
// delimited by finding any character. A new csString object is created
// to hold the token and this is returned on the stack
//
// Token search logic is different if ofsidx is specified. 
// If ofsidx is specified, then all delim characters are skipped until a 
// non-delim character is found. Then all characters up to the first delim 
// char (or NULL) are returned as the token. 
// If ofsidx is not specified, then it is assumed we are continuing from 
// a previous call, and in this case characters are copied into the token
// return string until a delim character is found. Thus it is possible
// to get a null token with two delimiter characters one after the other
// For example scanning . scanstr = ',,1,2,3,,5'
// using   
//      s.NextToken(",", 0) 
//      s.NextToken(",") 
//      s.NextToken(",") 
//      s.NextToken(",") 
//      s.NextToken(",") 
// Would return tokens:
//   '1' 
//   '2'
//   '3'
//   ''   (or NULL string)
//   '5'
//
// using   
//      s.idx = 0 ;          
//      s.NextToken(",") 
//      s.NextToken(",") 
//      s.NextToken(",") 
//      s.NextToken(",") 
//      s.NextToken(",") 
// Would return tokens:
//   ''
//   ''
//   '1' 
//   '2'
//   '3'
//   ''   (or NULL string)
//   '5'
//
// using   
//      s.NextToken(",", 0) 
//      s.NextToken(",", s.idx) 
//      s.NextToken(",", s.idx) 
//      s.NextToken(",", s.idx) 
//      s.NextToken(",", s.idx) 
// Would return tokens:
//   '1' 
//   '2'
//   '3'
//   '5'
//  
// When searching for tokens, the first character not in the string ps 
// (or NULL) is the first character of the next token. Then all characters 
// until one of the characters in ps is found (or NULL) are copied to the 
// token result. 
//
csString csString::NextToken(csString csDelims, int ofsidx)
{
    return NextToken(csDelims.str, ofsidx) ; 
}

csString csString::NextToken(char *pdelims, int ofsidx)
{
    csString result ; 
    if (!pdelims)
        return *this ; // simply return the entire string back

    // Else there is something to do
    if (ofsidx != -1)
    {   // Skip all leading delim characters in this situation
        idx = ofsidx ; 

        char *tc ; // pointer to next test character

        int i, keepgoing ; 
    
        // Find first non token character (start of the token)
        for (i=idx; i < len; i++)
        {
            keepgoing = 0 ; 
            tc = pdelims ; 
            while (*tc)
            {
                if (*tc == str[i])
                {
                    keepgoing = 1 ; 
                    break ; 
                }
                tc++ ; 
            }
            if (!keepgoing)
                break ; 
        }

        // Now copy from str[i] to the first delim character into the 
        // token result string
        int tokidx = i ; 
        int delimidx = i ; 

        keepgoing = 1 ; 
        while (i < len && keepgoing)
        {
            tc = pdelims ; 
            while (*tc)
            {
                if (*tc == str[i])
                {
                    keepgoing = 0 ; 
                    delimidx = i ; 
                    i -= 1 ; // we don't want I to increment
                    // but it will anyway since we are only breaking out
                    // of the inner loop and the i++ will happen again
                    break ; 
                }
                tc++ ; 
            }
            if (keepgoing) i++ ; 
        }

        if (i==len)
            delimidx = len ; 
        
        // Test to make sure that there are delimiter characters     
        if (tokidx < delimidx)
        {   // Then there is something to do
            result = csString(&str[tokidx], delimidx - tokidx) ; 
        }
        // else we are returning a NULL token

        idx = delimidx + 1; // update the index for the next delimiter
        if (idx > len)
            idx = len ; // set to the NULL character
    }
    else
    {   // ofsidx not specified
        char *tc ; // pointer to next test character

        int i, founddelim ; 
    
        // Now copy from str[i] to the first delim character into the 
        // token result string
        int delimidx ; 
        int tokidx = idx ; 
        
        founddelim = 0 ; 
        for (i = idx ; i < len ; i++)
        {
            tc = pdelims ; 
            while (*tc)
            {   // Always treat the NULL terminator as a delimiter
                if (*tc == str[i])
                {
                    delimidx = i ; 
                    founddelim = 1 ; 
                    break ; 
                }
                tc++ ; 
            }
            if (founddelim)
                break ;
        }

        if (i==len)
            delimidx = len ; 
        
        // Test to make sure that there are delimiter characters     
        if (tokidx < delimidx)
        {   // Then there is something to do
            result = csString(&str[tokidx], delimidx - tokidx) ; 
        }
        // else we are returning a NULL token

        idx = delimidx + 1; // update the index for the next delimiter
        if (idx > len)
            idx = len ; // set to the NULL character
    }
    return result ;
}


/*!
    This works exactly as above with the exception that a quote is also 
    used as a delimiter character. While scanning if a 
    quote is found, an insideQuotes mode is set, then delimiters
    are ignored until the next quote is detected. Having quotes 
    embedded in the string between quotes is not possible
    Note: do not specify the " character as one of the delimiter characters
    as the results will be unpredictable.
 */
csString csString::NextQuotedToken(char *pdelims, int ofsidx, char qc)
{
    csString result ; 
    if (!pdelims)
        return *this ; // simply return the entire string back


    // Else there is something to do
    int skipdelims ; 

    if (ofsidx == -1)
    {
        skipdelims = 0 ; 
    }
    else
    {
        idx = ofsidx ; 
        skipdelims = 1 ; 
    }

    char *tc ; // pointer to next test character

    int i, keepgoing ; 

    // Find first non token character (start of the token)
    i = idx ; 
    if (skipdelims)
    {
        keepgoing = 1 ; 
        while (keepgoing && i < len)
        {
            keepgoing = 0 ; 
            tc = pdelims ; 
            while (*tc)
            {
                if (*tc == str[i])
                {
                    keepgoing = 1 ; 
                    break ; 
                }
                tc++ ; 
            }
            if (keepgoing)
                i++ ; 
        }
    }

    // Now copy from str[i] to the first delim character into the 
    // token result string
    int tokidx = i ; 
    int delimidx = i ; 
    int insideQuotes = 0 ; 
    
    keepgoing = 1 ; 
    while (i < len && keepgoing)
    {
        if (insideQuotes)
        {
            if (str[i] == qc)
            {
                insideQuotes = 0 ; 
                result += qc ; 
                i++ ; 
            }
            else if (str[i] == '\\' && str[i+1] == qc)
            {
                result += str[i++] ; 
                result += str[i++] ; 
            }
            else
            {
                result += str[i++] ; 
            }
        }
        else
        {   
            tc = pdelims ; 
            while (*tc)
            {
                if (*tc == str[i])
                {
                    keepgoing = 0 ; 
                    delimidx = i ; 
                    break ; 
                }
                tc++ ; 
            }
            
            if (keepgoing) 
            {
                result += str[i] ; 
                if (str[i] == qc)
                    insideQuotes = 1 ; 
                i++ ; 
            }
        }
    }

    if (i==len)
        delimidx = len ; 

    idx = delimidx + 1; // update the index for the next delimiter
    if (idx > len)
        idx = len ; // set to the NULL character

    return result ;
}



// This behaves differently from NextToken in that ofsidx simply 
// defines a starting point and as soon as a non-matching character
// is found the function returns. If ofsidx == -1 then the internal
// idx variable is used as the starting point, otherwise idx is 
// set to ofsidx before proceeding.
csString csString::NextCharsInSetToken(csString csValidChars, int ofsidx)
{
    return NextCharsInSetToken(csValidChars.str, ofsidx) ; 
}

// The string szValidchars must be NULL terminated
csString csString::NextCharsInSetToken(char *szValidChars, int ofsidx)
{
    csString result ; 
    if (!szValidChars)
        return result ; // done, return null string

    if (ofsidx != -1)
    {
        idx = ofsidx ; 
        if (idx > len)
        {
            idx = len ; // want to make sure if we keep calling
                        // next token that idx points to a NULL char
        }
    }
    else
        idx = 0 ; 

    char *tc ; 
    int i ; 

    for (i=idx; i < len; i++)
    {

        tc = szValidChars ; 
        while (*tc)
        {
            if (*tc == str[i])
                break ; 
            tc++ ; 
        }
        // When str[i] doesn't match anything then exit
        if (*tc == 0)
            break ; 

        result += str[i] ; 
    }
    idx = i ; 

    return result ;

}


// Chars: [-+0123456789]
csString csString::NextIntToken(int ofsidx) 
{
    return NextCharsInSetToken("-+0123456789", ofsidx) ; 
}

// Chars: [-+.e0123456789]
csString csString::NextFloatToken(int ofsidx) 
{
    return NextCharsInSetToken("-+.e0123456789", ofsidx) ; 
}


int csString::MoreTokens()
{
    if (idx < len)
        return 1 ; 
    return 0 ; 
}
///////////////////////////////////////////////////////////////////////////

int csString::IsEmpty()
{
    if (len)
        return 0 ; 
    return 1 ; 
}

/*
csString &csString::Append(char *s)
{
    int appendlen = strlen(s) ; 
    if (appendlen > 0)
    {
        char *ptmp = (char *)realloc(str, len + appendlen + 1) ; 
        if (ptmp)
        {
            str = ptmp ; 
            strcpy(&str[len], s) ; 
            len += appendlen ; 
        }
    }
    return *this ; 
}
*/

csString &csString::Append(const char *s)
{
    if (s)
    {
        int appendlen = (int)strlen(s) ; 
        if (appendlen > 0)
        {
            char *ptmp = (char *)realloc(str, len + appendlen + 1) ; 
            if (ptmp)
            {
                str = ptmp ; 
                strcpy(&str[len], s) ; 
                len += appendlen ; 
            }
        }
    }
    return *this ; 
}


csString &csString::Append(const csString &cs) 
{
    if (cs.str == 0)
        return *this ; 

    int appendlen = (int)strlen(cs.str) ; 
    if (appendlen > 0)
    {
        char *ptmp = (char *)realloc(str, len + appendlen + 1) ; 
        if (ptmp)
        {
            str = ptmp ; 
            strcpy(&str[len], cs.str) ; 
            len += appendlen ; 
        }
    }
    return *this ; 
}

csString &csString::Append(const char c)
{
    if (c)
    {   // allocated length is always len+1 so we add 2 here
        char *ptmp = (char *)realloc(str, len + 2) ; 
        if (ptmp)
        {
            str = ptmp ; 
            str[len++] = c ; 
            str[len] = 0 ; 
        }
    }
    return *this ; 
}

csString &csString::operator +=(const csString &a)
{
    Append(a) ; 
    return *this ; 
}

/*
csString &csString::operator +=(char *s)
{
    Append(s) ; 
    return *this ; 
}
*/

csString &csString::operator +=(const char *s)
{
    Append(s) ; 
    return *this ; 
}

csString &csString::operator +=(const char c) 
{
    Append(c) ; 
    return *this ; 
}

csString &csString::ToUpper(int startidx)
{
    if (startidx < len)
    {
        for (int i=startidx ; i < len; i++)
            str[i] = toupper(str[i]) ; 
    }

    return *this ;
}


// returns true if all characters are in the set [A-Za-z]
int csString::IsAlpha(int startidx)
{
    if (len == 0)
        return 0 ; 

    for (int i=startidx ; i < len; i++)
    {
        if (!
            ((str[i] >= 'A' && str[i] <= 'Z') || 
             (str[i] >= 'a' && str[i] <= 'z'))
            )
        {
            return 0 ; // 
        }
    }

    return 1 ;
}


int csString::IsNumeric(int startidx)
{
    if (len == 0)
        return 0 ; 

    for (int i=startidx ; i < len; i++)
    {
        if (!
            ((str[i] >= '0' && str[i] <= '9') || 
             str[i] == '.' || str[i] == '-' || 
             str[i] == '+' || str[i] == 'e') 
            )
        {
            return 0 ; // 
        }
    }

    return 1 ;
}


int csString::IsDigit(int startidx)
{
    if (len == 0)
        return 0 ; 

    for (int i=startidx ; i < len; i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            return 0 ; // 
        }
    }

    return 1 ;
}


unsigned int csString::HexToInt(int startidx, int length)
{
    int i, j ;
    unsigned int hexchar, retvalue ; 
    if (length == -1)
        length = len ; 

    retvalue = 0 ; 
    for (i=startidx, j=0; i < len && j < length; i++, j++)
    {
        hexchar = toupper(str[i]) ; 
        if (hexchar >= '0' && hexchar <= '9')
            hexchar -= '0' ;
        else 
            hexchar = hexchar - 'A' + 10 ;
        if (hexchar > 15)
            hexchar = 0 ; // ignore this character
        retvalue = (retvalue << 4) | hexchar ;
    }
    return retvalue ; 
}

char hextable[256][2] = {
    {'0', '0'},
    {'0', '1'},
    {'0', '2'},
    {'0', '3'},
    {'0', '4'},
    {'0', '5'},
    {'0', '6'},
    {'0', '7'},
    {'0', '8'},
    {'0', '9'},
    {'0', 'A'},
    {'0', 'B'},
    {'0', 'C'},
    {'0', 'D'},
    {'0', 'E'},
    {'0', 'F'},
    {'1', '0'},
    {'1', '1'},
    {'1', '2'},
    {'1', '3'},
    {'1', '4'},
    {'1', '5'},
    {'1', '6'},
    {'1', '7'},
    {'1', '8'},
    {'1', '9'},
    {'1', 'A'},
    {'1', 'B'},
    {'1', 'C'},
    {'1', 'D'},
    {'1', 'E'},
    {'1', 'F'},
    {'2', '0'},
    {'2', '1'},
    {'2', '2'},
    {'2', '3'},
    {'2', '4'},
    {'2', '5'},
    {'2', '6'},
    {'2', '7'},
    {'2', '8'},
    {'2', '9'},
    {'2', 'A'},
    {'2', 'B'},
    {'2', 'C'},
    {'2', 'D'},
    {'2', 'E'},
    {'2', 'F'},
    {'3', '0'},
    {'3', '1'},
    {'3', '2'},
    {'3', '3'},
    {'3', '4'},
    {'3', '5'},
    {'3', '6'},
    {'3', '7'},
    {'3', '8'},
    {'3', '9'},
    {'3', 'A'},
    {'3', 'B'},
    {'3', 'C'},
    {'3', 'D'},
    {'3', 'E'},
    {'3', 'F'},
    {'4', '0'},
    {'4', '1'},
    {'4', '2'},
    {'4', '3'},
    {'4', '4'},
    {'4', '5'},
    {'4', '6'},
    {'4', '7'},
    {'4', '8'},
    {'4', '9'},
    {'4', 'A'},
    {'4', 'B'},
    {'4', 'C'},
    {'4', 'D'},
    {'4', 'E'},
    {'4', 'F'},
    {'5', '0'},
    {'5', '1'},
    {'5', '2'},
    {'5', '3'},
    {'5', '4'},
    {'5', '5'},
    {'5', '6'},
    {'5', '7'},
    {'5', '8'},
    {'5', '9'},
    {'5', 'A'},
    {'5', 'B'},
    {'5', 'C'},
    {'5', 'D'},
    {'5', 'E'},
    {'5', 'F'},
    {'6', '0'},
    {'6', '1'},
    {'6', '2'},
    {'6', '3'},
    {'6', '4'},
    {'6', '5'},
    {'6', '6'},
    {'6', '7'},
    {'6', '8'},
    {'6', '9'},
    {'6', 'A'},
    {'6', 'B'},
    {'6', 'C'},
    {'6', 'D'},
    {'6', 'E'},
    {'6', 'F'},
    {'7', '0'},
    {'7', '1'},
    {'7', '2'},
    {'7', '3'},
    {'7', '4'},
    {'7', '5'},
    {'7', '6'},
    {'7', '7'},
    {'7', '8'},
    {'7', '9'},
    {'7', 'A'},
    {'7', 'B'},
    {'7', 'C'},
    {'7', 'D'},
    {'7', 'E'},
    {'7', 'F'},
    {'8', '0'},
    {'8', '1'},
    {'8', '2'},
    {'8', '3'},
    {'8', '4'},
    {'8', '5'},
    {'8', '6'},
    {'8', '7'},
    {'8', '8'},
    {'8', '9'},
    {'8', 'A'},
    {'8', 'B'},
    {'8', 'C'},
    {'8', 'D'},
    {'8', 'E'},
    {'8', 'F'},
    {'9', '0'},
    {'9', '1'},
    {'9', '2'},
    {'9', '3'},
    {'9', '4'},
    {'9', '5'},
    {'9', '6'},
    {'9', '7'},
    {'9', '8'},
    {'9', '9'},
    {'9', 'A'},
    {'9', 'B'},
    {'9', 'C'},
    {'9', 'D'},
    {'9', 'E'},
    {'9', 'F'},
    {'A', '0'},
    {'A', '1'},
    {'A', '2'},
    {'A', '3'},
    {'A', '4'},
    {'A', '5'},
    {'A', '6'},
    {'A', '7'},
    {'A', '8'},
    {'A', '9'},
    {'A', 'A'},
    {'A', 'B'},
    {'A', 'C'},
    {'A', 'D'},
    {'A', 'E'},
    {'A', 'F'},
    {'B', '0'},
    {'B', '1'},
    {'B', '2'},
    {'B', '3'},
    {'B', '4'},
    {'B', '5'},
    {'B', '6'},
    {'B', '7'},
    {'B', '8'},
    {'B', '9'},
    {'B', 'A'},
    {'B', 'B'},
    {'B', 'C'},
    {'B', 'D'},
    {'B', 'E'},
    {'B', 'F'},
    {'C', '0'},
    {'C', '1'},
    {'C', '2'},
    {'C', '3'},
    {'C', '4'},
    {'C', '5'},
    {'C', '6'},
    {'C', '7'},
    {'C', '8'},
    {'C', '9'},
    {'C', 'A'},
    {'C', 'B'},
    {'C', 'C'},
    {'C', 'D'},
    {'C', 'E'},
    {'C', 'F'},
    {'D', '0'},
    {'D', '1'},
    {'D', '2'},
    {'D', '3'},
    {'D', '4'},
    {'D', '5'},
    {'D', '6'},
    {'D', '7'},
    {'D', '8'},
    {'D', '9'},
    {'D', 'A'},
    {'D', 'B'},
    {'D', 'C'},
    {'D', 'D'},
    {'D', 'E'},
    {'D', 'F'},
    {'E', '0'},
    {'E', '1'},
    {'E', '2'},
    {'E', '3'},
    {'E', '4'},
    {'E', '5'},
    {'E', '6'},
    {'E', '7'},
    {'E', '8'},
    {'E', '9'},
    {'E', 'A'},
    {'E', 'B'},
    {'E', 'C'},
    {'E', 'D'},
    {'E', 'E'},
    {'E', 'F'},
    {'F', '0'},
    {'F', '1'},
    {'F', '2'},
    {'F', '3'},
    {'F', '4'},
    {'F', '5'},
    {'F', '6'},
    {'F', '7'},
    {'F', '8'},
    {'F', '9'},
    {'F', 'A'},
    {'F', 'B'},
    {'F', 'C'},
    {'F', 'D'},
    {'F', 'E'},
    {'F', 'F'}} ; 

char hextableLC[256][2] = {
    {'0', '0'},
    {'0', '1'},
    {'0', '2'},
    {'0', '3'},
    {'0', '4'},
    {'0', '5'},
    {'0', '6'},
    {'0', '7'},
    {'0', '8'},
    {'0', '9'},
    {'0', 'a'},
    {'0', 'b'},
    {'0', 'c'},
    {'0', 'd'},
    {'0', 'e'},
    {'0', 'f'},
    {'1', '0'},
    {'1', '1'},
    {'1', '2'},
    {'1', '3'},
    {'1', '4'},
    {'1', '5'},
    {'1', '6'},
    {'1', '7'},
    {'1', '8'},
    {'1', '9'},
    {'1', 'a'},
    {'1', 'b'},
    {'1', 'c'},
    {'1', 'd'},
    {'1', 'e'},
    {'1', 'f'},
    {'2', '0'},
    {'2', '1'},
    {'2', '2'},
    {'2', '3'},
    {'2', '4'},
    {'2', '5'},
    {'2', '6'},
    {'2', '7'},
    {'2', '8'},
    {'2', '9'},
    {'2', 'a'},
    {'2', 'b'},
    {'2', 'c'},
    {'2', 'd'},
    {'2', 'e'},
    {'2', 'f'},
    {'3', '0'},
    {'3', '1'},
    {'3', '2'},
    {'3', '3'},
    {'3', '4'},
    {'3', '5'},
    {'3', '6'},
    {'3', '7'},
    {'3', '8'},
    {'3', '9'},
    {'3', 'a'},
    {'3', 'b'},
    {'3', 'c'},
    {'3', 'd'},
    {'3', 'e'},
    {'3', 'f'},
    {'4', '0'},
    {'4', '1'},
    {'4', '2'},
    {'4', '3'},
    {'4', '4'},
    {'4', '5'},
    {'4', '6'},
    {'4', '7'},
    {'4', '8'},
    {'4', '9'},
    {'4', 'a'},
    {'4', 'b'},
    {'4', 'c'},
    {'4', 'd'},
    {'4', 'e'},
    {'4', 'f'},
    {'5', '0'},
    {'5', '1'},
    {'5', '2'},
    {'5', '3'},
    {'5', '4'},
    {'5', '5'},
    {'5', '6'},
    {'5', '7'},
    {'5', '8'},
    {'5', '9'},
    {'5', 'a'},
    {'5', 'b'},
    {'5', 'c'},
    {'5', 'd'},
    {'5', 'e'},
    {'5', 'f'},
    {'6', '0'},
    {'6', '1'},
    {'6', '2'},
    {'6', '3'},
    {'6', '4'},
    {'6', '5'},
    {'6', '6'},
    {'6', '7'},
    {'6', '8'},
    {'6', '9'},
    {'6', 'a'},
    {'6', 'b'},
    {'6', 'c'},
    {'6', 'd'},
    {'6', 'e'},
    {'6', 'f'},
    {'7', '0'},
    {'7', '1'},
    {'7', '2'},
    {'7', '3'},
    {'7', '4'},
    {'7', '5'},
    {'7', '6'},
    {'7', '7'},
    {'7', '8'},
    {'7', '9'},
    {'7', 'a'},
    {'7', 'b'},
    {'7', 'c'},
    {'7', 'd'},
    {'7', 'e'},
    {'7', 'f'},
    {'8', '0'},
    {'8', '1'},
    {'8', '2'},
    {'8', '3'},
    {'8', '4'},
    {'8', '5'},
    {'8', '6'},
    {'8', '7'},
    {'8', '8'},
    {'8', '9'},
    {'8', 'a'},
    {'8', 'b'},
    {'8', 'c'},
    {'8', 'd'},
    {'8', 'e'},
    {'8', 'f'},
    {'9', '0'},
    {'9', '1'},
    {'9', '2'},
    {'9', '3'},
    {'9', '4'},
    {'9', '5'},
    {'9', '6'},
    {'9', '7'},
    {'9', '8'},
    {'9', '9'},
    {'9', 'a'},
    {'9', 'b'},
    {'9', 'c'},
    {'9', 'd'},
    {'9', 'e'},
    {'9', 'f'},
    {'a', '0'},
    {'a', '1'},
    {'a', '2'},
    {'a', '3'},
    {'a', '4'},
    {'a', '5'},
    {'a', '6'},
    {'a', '7'},
    {'a', '8'},
    {'a', '9'},
    {'a', 'a'},
    {'a', 'b'},
    {'a', 'c'},
    {'a', 'd'},
    {'a', 'e'},
    {'a', 'f'},
    {'b', '0'},
    {'b', '1'},
    {'b', '2'},
    {'b', '3'},
    {'b', '4'},
    {'b', '5'},
    {'b', '6'},
    {'b', '7'},
    {'b', '8'},
    {'b', '9'},
    {'b', 'a'},
    {'b', 'b'},
    {'b', 'c'},
    {'b', 'd'},
    {'b', 'e'},
    {'b', 'f'},
    {'c', '0'},
    {'c', '1'},
    {'c', '2'},
    {'c', '3'},
    {'c', '4'},
    {'c', '5'},
    {'c', '6'},
    {'c', '7'},
    {'c', '8'},
    {'c', '9'},
    {'c', 'a'},
    {'c', 'b'},
    {'c', 'c'},
    {'c', 'd'},
    {'c', 'e'},
    {'c', 'f'},
    {'d', '0'},
    {'d', '1'},
    {'d', '2'},
    {'d', '3'},
    {'d', '4'},
    {'d', '5'},
    {'d', '6'},
    {'d', '7'},
    {'d', '8'},
    {'d', '9'},
    {'d', 'a'},
    {'d', 'b'},
    {'d', 'c'},
    {'d', 'd'},
    {'d', 'e'},
    {'d', 'f'},
    {'e', '0'},
    {'e', '1'},
    {'e', '2'},
    {'e', '3'},
    {'e', '4'},
    {'e', '5'},
    {'e', '6'},
    {'e', '7'},
    {'e', '8'},
    {'e', '9'},
    {'e', 'a'},
    {'e', 'b'},
    {'e', 'c'},
    {'e', 'd'},
    {'e', 'e'},
    {'e', 'f'},
    {'f', '0'},
    {'f', '1'},
    {'f', '2'},
    {'f', '3'},
    {'f', '4'},
    {'f', '5'},
    {'f', '6'},
    {'f', '7'},
    {'f', '8'},
    {'f', '9'},
    {'f', 'a'},
    {'f', 'b'},
    {'f', 'c'},
    {'f', 'd'},
    {'f', 'e'},
    {'f', 'f'}} ; 

csString &csString::StrToHex(unsigned char *binstr, int binlen)
{
    if (str)
        free(str) ; 
    str = 0 ; 
    len = 0 ; 
    idx = 0 ; 

    str = (char *)malloc(binlen * 2 + 4) ;        
    int j = 0 ; 
    for (int i=0; i < binlen; i++, j+=2)
    {
        str[j]   = hextable[binstr[i]][0] ; 
        str[j+1] = hextable[binstr[i]][1] ; 
        len += 2 ; 
    }
    str[j] = 0 ; 
    str[j+1] = 0 ; 

    return *this ; 
}

// Does a binary string to hex encoding without any memory allocation
// hexstr must be allocated to accept (binlen * 2 + 1) characters 
// where the +1 is for the terminating null byte
void CS_BinToHex(unsigned char *binstr, int binlen, char *hexstr)
{
    int j = 0 ; 
    for (int i=0; i < binlen; i++, j+=2)
    {
        hexstr[j]   = hextable[binstr[i]][0] ; 
        hexstr[j+1] = hextable[binstr[i]][1] ; 
    }
    hexstr[j] = 0 ; 
}

int CS_HexToBin(unsigned char *hexstr, int hexlen, unsigned char *binstr)
{
    int j = 0 ; 
    char h, l ; 
    for (int i=0; i < hexlen; i+=2, j++)
    {
        h = (char)toupper(hexstr[i]) ; 
        l = (char)toupper(hexstr[i+1]) ; 

        if (h < 0x3a)
            h = (h - '0') << 4 ; 
        else
            h = (h - 'A' + 10) << 4 ; 

        if (l < 0x3a)
            l = l - '0' ; 
        else
            l = l - 'A' + 10 ; 

        binstr[j] = (0x00ff) & (h | l) ; 
    }
    return j ; 
}

// Returns 0 OK, else the (offset+1) of the invalid character is returned
// The hex string can be any number of hex bytes up to the size that 
// will fit in an unsigned int. No check is made to ensure that the 
// length will fit. on 32 bit machines the hexlen must be from 1 to 8. 
int CS_HexToInt(unsigned char *hexstr, int hexlen, unsigned int &retvalue)
{
    char hexchar ; 
    retvalue = 0 ;
    for (int i=0; i < hexlen; i++)
    {
        hexchar = toupper(hexstr[i]) ; 
        if (hexchar >= '0' && hexchar <= '9')
            hexchar -= '0' ;
        else 
            hexchar = hexchar - 'A' + 10 ;
        if (hexchar > 15)
            return i+1 ; 
        retvalue = (retvalue << 4) | hexchar ;
    }
    return 0 ; 
}


//! This only works with INTEL type architectures. If ported to BIG ENDIAN type 
//! systems you need to reverse the order of the bytes. 
void CS_IntToHex(int *pint, char *hexstr)
{
    unsigned char *pc = (unsigned char *)pint ; 
    hexstr[0] = hextable[pc[3]][0] ; 
    hexstr[1] = hextable[pc[3]][1] ; 

    hexstr[2] = hextable[pc[2]][0] ; 
    hexstr[3] = hextable[pc[2]][1] ; 

    hexstr[4] = hextable[pc[1]][0] ; 
    hexstr[5] = hextable[pc[1]][1] ; 

    hexstr[6] = hextable[pc[0]][0] ; 
    hexstr[7] = hextable[pc[0]][1] ;
}

// Create a hex string of 4 characters taking only the 0x0000ffff part
// of the integer value. 
void CS_IntToHex2B(int *pint, char *hexstr)
{
    unsigned char *pc = (unsigned char *)pint ; 
    hexstr[0] = hextable[pc[1]][0] ; 
    hexstr[1] = hextable[pc[1]][1] ; 

    hexstr[2] = hextable[pc[0]][0] ; 
    hexstr[3] = hextable[pc[0]][1] ; 
}


void CS_CharToHex(unsigned char *pc, char *hexstr)
{
    hexstr[0] = hextableLC[pc[0]][0] ; 
    hexstr[1] = hextableLC[pc[0]][1] ; 
}


int CS_HexToBin(unsigned char *hexstr, unsigned char *binstr)
{
    int j = 0 ; 
    int i = 0 ; 
    char h, l ; 
    while (hexstr[i] && hexstr[i+1])
    {
        h = (char)toupper(hexstr[i]) ; 
        l = (char)toupper(hexstr[i+1]) ; 

        if (h < 0x3a)
            h = (h - '0') << 4 ; 
        else
            h = (h - 'A' + 10) << 4 ; 

        if (l < 0x3a)
            l = l - '0' ; 
        else
            l = l - 'A' + 10 ; 

        binstr[j] = (0x00ff) & (h | l) ; 
        
        j++ ; 
        i += 2 ; 
    }
    return j ; 
}


//! Convert a hex encoded string into a binary string of bytes
csString &csString::HexToStr(unsigned char *hexstr, int hexlen)
{
    if (str)
        free(str) ; 
    str = 0 ; 
    len = 0 ; 
    idx = 0 ; 

    if (!hexstr || !hexstr[0] || hexlen == 0)
        return *this ; 

    str = (char *)malloc(hexlen / 2 + 1) ; 
    int strlen = CS_HexToBin(hexstr, hexlen, (unsigned char *)str) ; 
    str[len] = 0 ; 

    return *this ; 
}


csString &csString::Format(const char *formatstr, ...) 
{
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
 
    size_t formatlen = strlen(formatstr) ; 
    
    char *ps = (char *)formatstr ;
    int parms = 0 ;
    while (ps && *ps)
    {
        if (*ps++ == '%')
        {
            if (*ps && *ps++ != '%')
                parms++ ; 
        }
    }

    if (str)
        free(str) ; 

    str = (char *)malloc(formatlen + parms * 256) ; 
    str[0] = 0 ; 

    vsprintf(str, formatstr, marker) ;
    va_end(marker) ; 

    len = (int)strlen(str) ; 
    idx = 0 ; 

    return *this ; 
}

csString &csString::FormatSz(int size, const char *formatstr, ...) 
{
    va_list marker;
    va_start(marker, formatstr);     // Initialize variable arguments
 
    if (str)
        free(str) ; 

    str = (char *)malloc(size + 2) ; 
    str[0] = 0 ; 
    
    vsprintf(str, formatstr, marker) ;
    va_end(marker) ; 

    len = (int)strlen(str) ; 
    idx = 0 ; 

    return *this ; 
}


csString &csString::UnicodeToBytes(const char *unicodestr)
{
    if (str)
    {   // Then we have to de-allocate memory here
        free(str) ; 
    }
    len = 0 ; 
    str = 0 ; 
    idx = 0 ; 

    if (!unicodestr) 
        return *this ; 

    char *ps = (char *)unicodestr ; 
    int count = 0 ; 
    while (*ps || *(ps+1))
    {
        ps += 2 ; 
        count++ ; 
    }

    if (count > 0) // allows for up to 2GB strings here
    {
        str = (char *)malloc(count + 1) ; 
        str[0] = 0 ; 

        ps = (char *)unicodestr ; 
        len = count ; 
        count = 0 ; 
        while (count < len)
        {
            str[count] = *ps ; 
            ps += 2 ; 
            count++ ; 
        }
        str[count] = 0 ;
        idx = 0 ; 
    }

    return *this ; 
}


csString &csString::BytesToUnicode(const char *bytestr, int bytelen)
{
    if (str)
    {   // Then we have to de-allocate memory here
        free(str) ; 
    }
    len = 0 ; 
    str = 0 ; 
    idx = 0 ; 

    if (!bytestr) 
        return *this ; 

    char *ps = (char *)bytestr ; 
    int count = 0 ; 
    if (bytelen != 0)
        count = (bytelen) * 2 ; 
    else
    {
        while (*ps || *(ps+1))
        {
            ps++ ; 
            count++ ; 
        }
        count *= 2 ; 
    }

    if (count > 0) // allows for up to 2GB strings here
    {
        str = (char *)malloc(count + 4) ; 
        str[0] = 0 ; 

        ps = (char *)bytestr ; 
        len = count ; 
        count = 0 ; 
        while (count < len)
        {
            
            *((wint_t *)&str[count]) = btowc(*ps) ; 
            ps++ ; 
            count += 2 ; 
        }

        // Do the wide char termination
        str[count] = 0 ;
        str[count+1] = 0 ;
        idx = 0 ; 
    }

    return *this ; 
}




////////////////////////////////////////////////////////////////////////////////
// supporting functions to the class

/*
csString operator+(const char *a, csString &b)  
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}
*/

csString operator+(const csString &a, const csString &b) 
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}

csString operator+(const char *a, const csString &b)  
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}

csString operator+(const csString &a, const char *b)  
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}

csString operator+(const csString &a, const char b) 
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}

csString operator+(const char a, const csString &b) 
{
    csString res(a) ; 
    res.Append(b) ; 
    return res ; 
}

bool operator==(const char *a, const csString &b)
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) == 0)
            return 1 ; 
        return 0 ; 
    }

    if (!a && !b.str)
        return 1 ; 
    return 0 ; 
}

bool operator!=(char *a, csString &b) 
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) != 0)
            return 1 ; 
        return 0 ; 
    }

    if (!a && !b.str)
        return 0 ; 
    return 1 ; 
}

bool operator<(char *a, csString &b) 
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) < 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str)
        return 1 ; 
    return 0 ; // both NULL or a GT 
}

bool operator>(char *a, csString &b) 
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) > 0)
            return 1 ; 
        return 0 ; 
    }

    if (a)
        return 1 ; 
    return 0 ; 
}

bool operator<=(char *a, csString &b) 
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) <= 0)
            return 1 ; 
        return 0 ; 
    }

    if (!a)
        return 1 ; 
    return 0 ; 
}

bool operator>=(char *a, csString &b) 
{
    if (a && b.str)
    {
        if (strcmp(a, b.str) >= 0)
            return 1 ; 
        return 0 ; 
    }

    if (!b.str)
        return 1 ;
    return 0 ; 
}



///////////////////////////////////////////////////////////////
// Required for stl compatibility
bool operator==(const csString &a, const csString &b) 
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) == 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str) // then str == NULL
        return 0 ; 
    return 1 ; // b and str == NULL
}       


bool operator!=(const csString &a, const csString &b) 
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) == 0)
            return 0 ; 
        return 1 ; 
    }

    if (b.str) // then str == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}       


bool operator<(const csString &a, const csString &b)  
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) < 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str) // then str == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}       


bool operator>(const csString &a, const csString &b) 
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) > 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (a.str) // then b == NULL
        return 1 ; 
    return 0 ; // b and str == NULL
}


bool operator<=(const csString &a, const csString &b)
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) <= 0)
            return 1 ; 
        return 0 ; 
    }
    
    if (a.str)
        return 0 ; 
    return 1 ; // both NULL
}


bool operator>=(const csString &a, const csString &b) 
{
    if (a.str && b.str)
    {
        if (strcmp(a.str, b.str) >= 0)
            return 1 ; 
        return 0 ; 
    }

    if (b.str)
        return 0 ; 
    return 1 ; 
}


///////////////////////////////////////////////////////////
// String like utility functions
csString csIntToStr(int i)
{
    char str[16] ; 
    sprintf(str, "%d", i) ; 
    return csString(str) ; 
}

csString csDoubleToStr(double d, char *format)
{
    char str[128] ; 
    sprintf(str, format, d) ; 
    return csString(str) ; 
}


csString csFloatToStr(float d, char *format)
{
    char str[128] ; 
    sprintf(str, format, d) ; 
    return csString(str) ; 
}


//! Creates a string enclosed in double quotes
/*!
    \param str the string to be processed and converted to a quoted delimited string
    \return the quote delimited string

    str is scanned for double quote chraceters and if any are found then an backslash
    is inserted in front of the double quote. Also, and backslash characters found
    will have an additional backslash inserted in front of them so that the character
    following the backslash is not treated as a special character. 

    For example:
            
    Input:    He said, "What was that?".\n
    Output:   "He said, \"What was that?\".\\n"
 */
csString MakeQuotedString(const char *str)
{
    csString result ;
    
    char *pres = (char *)malloc(strlen(str) * 2 + 1) ; 
    char *pc ; 

    // Add the leading quote
    result = '\"' ; 

    char *s = (char *)str ; 
    while (s && *s)
    {
        if (*s == '\"' || *s == '\\')  
        {   //  0x22 double quote character or 0x5c backslash character
            *pc++ = '\\' ;
            *pc++ = *s ; 
        }
        else
        {
            *pc++ = *s ; 
        }
        s++  ;
    }
    
    *pc++ = '\"' ;
    *pc = 0 ; 

    // Add the trailing quote
    result = pres ; 
    free(pres) ; 

    return result ; 
}

//! Extract a string enclosed in double quotes
/*!
    \param str the quoted string to be processed. 
    \return the result string with embedded quotes and double backslashes
    mapped back to what they were when passed in by MakeQuotedString(..)

    For example:
            
    Input:    "He said, \"What was that?\".\\n"
    Output:   He said, "What was that?".\n

 */
csString ExtractQuotedString(const char *str) 
{
    if (!str)
        return csString("") ; 

    char *pres = (char *)malloc(strlen(str) + 1) ; 
    char *ps = (char *)str; 
    char *pr = pres ; 

    // Skip the leading quote if there is one
    if (*ps == '\"')
        ps++ ; 
    
    // Load characters until we hit a quote
    while(*ps && *ps != '\"') 
    {
        if (*ps == '\\')
        {   
            switch(*(ps+1))
            {
                case '\\' :
                case '\"' :
                    ps++ ; 
                    *pr++ = *ps++ ; 
                    break ; 
                case 'n' :
                    *pr++ = 0x0d ; 
                    *pr++ = 0x0a ; 
                    ps += 2 ; 
                    break ; 
                case 't' :
                    *pr++ = 0x09 ; 
                    ps += 2 ; 
                    break ; 
                default:
                    *pr++ = *ps++ ; 
                    break ; 
            }
            // Skip this character and save the next character
        }
        else
        {
            *pr++ = *ps++ ; 
        }
    }

    csString result(pres, 1) ;

    return result ; 
}



csString AddFile2Path(const csString &path, const csString &filename)
{
    csString retfile ;  
    int ifstart = 0 ; 
    if (filename.Left(1) == "\\")
        ifstart = 1 ; // skip the leading backslash

    if (path.len)
    {
        retfile = path ;
        csString lastChar(path.Right(1)) ; 
        if (lastChar != "\\" && lastChar != ":") 
            retfile += "\\" ; // add the trailing backslash 
        retfile += filename.Mid(ifstart) ; 
    }
    else
    {   // There is no path so simply return the actual file
        retfile = filename.Mid(ifstart) ; 
    }
    return retfile ; 
}

csString AddFile2Path(const char *path,     const csString &filename)
{
    return AddFile2Path(csString(path), filename) ;
}

csString AddFile2Path(const csString &path, const char *filename)
{
    return AddFile2Path(path, csString(filename)) ;
}

csString AddFile2Path(const char *path,     const char *filename) 
{
    return AddFile2Path(csString(path), csString(filename)) ;
}



// returns true if string is changed

// The allocated string must have sufficient space to accept the 
// extra trailing character if required
int AddTrailingSlashToPath(char *path)
{
    size_t pathlen = strlen(path) ; 
    if (pathlen == 0)
        return 0 ; // don't do anything with null strings, since 

#ifdef _WIN32
    if (path[pathlen-1] != '\\' && path[pathlen-1] != ':') 
    {
        path[pathlen++] = '\\' ; 
        path[pathlen] = 0 ; 
        return 1 ; 
    }
#else
    if (path[pathlen-1] != '/')
    {
        path[pathlen++] = '/' ; 
        path[pathlen] = 0 ; 
        return 1 ; 
    }
#endif

    return 0 ; 

}

int AddTrailingSlashToPath(csString &path)
{
    if (path.len == 0)
        return 0 ; // don't do anything with null strings, since 
                   // this will likely represent the current directory

#ifdef _WIN32
    if (path.Right(1) != "\\" && path.Right(1) != ':') 
    {
        path += '\\' ; 
        return 1 ; 
    }
#else
    if (path.Right(1) != "/")
    {
        path += '/' ; 
        return 1 ; 
    }
#endif

    return 0 ; 
}


// Returns true if there was a path portion otherwise returns 0
int SplitPathAndFile(csString &fullname, csString &path, csString &file) 
{
    if (fullname.Length() == 0)
    {
        path.Erase() ; 
        file.Erase() ; 
        return 0 ; 
    } 

    int fileIDX = fullname.FindLastIDX("\\") ;
    if (fileIDX == -1)
        fileIDX = fullname.FindLastIDX(":") ; 
    if (fileIDX == -1) 
    {   // Then there is no path portion in the file name
        path.Erase() ; // set to NULL
        file = fullname ; 
        return 0 ;
    }

    // path and file exist
    path = fullname.Left(fileIDX+1) ; 
    file = fullname.Mid(fileIDX+1) ; 
    return 1 ; 
}


int SplitFileAndExtension(csString &fullname, csString &file, csString &ext) 
{
    if (fullname.Length() == 0)
    {
        file.Erase() ; 
        ext.Erase() ; 
        return 0 ; 
    } 

    int fileIDX = fullname.FindLastIDX(".") ;
    if (fileIDX == -1) 
    {   // Then there is no path portion in the file name
        ext.Erase() ; // set to NULL
        file = fullname ; 
        return 0 ;
    }

    // path and file exist
    file = fullname.Left(fileIDX) ; 
    ext = fullname.Mid(fileIDX+1) ; 
    return 1 ; 
}

csString GetPathName(csString &fullname) 
{
    csString path, file ;
    SplitPathAndFile(fullname, path, file) ;
    return path ; 
}

csString GetPathName(const char *fullname)  
{
    csString tmpname(fullname) ;
    return GetPathName(tmpname) ; 
}

csString GetFileName(csString &fullname) 
{
    csString path, file ;
    csString tmpname(fullname) ; 
    SplitPathAndFile(tmpname, path, file) ;
    return file ; 
}

csString GetFileName(const char *fullname)
{
    csString tmpname(fullname) ; 
    return GetFileName(tmpname) ; 
}


int GetNameAndValue(csString &input, csString &nametok, csString &valuetok)
{
    int retval = 0 ; 
    csString wrkstr = input ; 
    nametok = wrkstr.NextToken("=", 0) ; 
    if (!wrkstr.MoreTokens())
    {
        retval |= 0x04 ; 
    }
    else
    {

        valuetok = wrkstr.NextToken(" \t\n\r", wrkstr.idx) ; 
    }

    nametok.Trim() ; 
    valuetok.Trim() ; 

    if (nametok.len == 0)
        retval |= 0x01 ; 
    if (valuetok.len == 0)
        retval |= 0x02 ; 

    // Strip off quotes on the end of the value string
    if (valuetok.Left(1) == "\"") 
    {
        valuetok = valuetok.Mid(1) ; // strip off the left character
        // Also have to grab all remaining characters until the 
        // trailing quote is found
        if (valuetok.Right(1) != "\"")
        {   // Then we have to search for the trailing quote
            valuetok += wrkstr[wrkstr.idx - 1] ; // add delimiter char
            int i = wrkstr.idx ; 
            while (wrkstr[i] != '\"' && i < wrkstr.len)
            {
                if (wrkstr[i] == '\\' && wrkstr[i+1] == '\"')
                {
                    valuetok += '\"' ;
                    i += 2 ; 
                }
                else
                {
                    valuetok += wrkstr[i] ; 
                    i++ ; 
                }
            }
        }

    }
    if (valuetok.Right(1) == "\"")
        valuetok = valuetok.Left(valuetok.len - 1) ; 

    return retval ; 
}


int SubCharacters(char *str, char from, char to)
{
    int count = 0 ; 
    while (*str)
    {
        if (*str == from)
        {
            *str = to ; 
            count++ ; 
        }
        str++ ; 
    }
    return count ; 
}


//! See if the test string matches the wildcard string
//! ** is illegal in the wildcard string (there is no way 
//! to test for the * character currently.
int CS_StringsMatch(char *wild, char *test)
{
    char *w = (char *)wild ; 
    char *t = (char *)test ; 

    while (w && *w)
    {
        if (*w == '*')
        {   // Then skip characters in test until we hit the next character in w
            w++ ; 
            if (*w == 0)
            {   // Then that is the end of the wildcard test string
                // which means everything matches
                return 1 ; 
            }

            while (t && *t && (*t != *w)) t++ ; 

            // Now the characters have to match up.  Since there are more 
            // characters in w but *t = 0 then the match failed.
            if (*t == 0)
                return 0 ; 
        }
        else
        {   // *w is a character which must match the current t value
            if (*w != *t)
                return 0 ; 

            // Else the two matched
            w++ ; 
            t++ ; 
        }
        
    }
    return 1 ; 
}

//! See if the test string starts with the startswith string
//! After the end of the startswith string is reached if the 
//! characters all match then it returns true, else false is returned. 
int CS_StartsWith(char *test, char *startswith)
{
    char *t = (char *)test ; 
    char *s = (char *)startswith ; 

    if (!t)
        return 0 ; 

    while (s && *s)
    {
        if (*t++ != *s++)
            return 0 ; 
    }
    return 1 ; 
}


//! Same as CS_StartsWith but ignore case during compar
int CS_icStartsWith(char *test, char *startswith)
{
    char *t = (char *)test ; 
    char *s = (char *)startswith ; 

    if (!t)
        return 0 ; 

    while (s && *s)
    {
        if (toupper(*t++) != toupper(*s++))
            return 0 ; 
    }
    return 1 ; 
}

bool CS_IsHexChar(const char c) 
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
        return true ;
    return false ; 
}


int CS_StrToInt(const char *str)
{
    if (!str || !str[0])
        return 0 ; 
    return atoi(str) ; 
}

unsigned int CS_StrToUInt(const char *str)
{
    if (!str || !str[0])
        return 0 ; 
    __int64 n = _atoi64(str) ; 
    return (unsigned int)( n & 0x0ffffffff ) ; 
}

long CS_StrToLong(const char *str)
{
    if (!str || !str[0])
        return 0 ; 
    return atol(str) ; 
}

unsigned long CS_StrToULong(const char *str)
{
    if (!str || !str[0])
        return 0 ; 
    __int64 n = _atoi64(str) ; 
    return (unsigned long)( n & 0x0ffffffff ) ; 
}

double CS_StrToDbl(const char *str)
{
    if (!str || !str[0])
        return 0 ; 
    return atof(str) ; 
}


//! skip over floating point value 
char *CS_SkipFloat(char *ps)
{
    if (!ps)
        return 0 ; // nothing to do
    if (*ps == '-' || *ps == '+')
        ps++ ; // skip over the leading sign character
    while(isdigit(*ps))
        ps++ ; 

    if (*ps == '.')
        ps++ ; 

    while (isdigit(*ps))
        ps++ ; 

    return ps ; 
}

// Returns the number of bytes in the UTF8 pattern. 
int CS_UTF8StartChar(unsigned char c)
{
    if (c < 0x80)
        return 1 ; 
    
    if ((c & 0xE0) == 0xC0)
        return 2 ; 

    if ((c & 0xF0) == 0xE0)
        return 3 ; 

    if ((c & 0xF8) == 0xF0)
        return 4 ; 

    return 0 ; 
}

int CS_IsDots(char *filename)
{
    if (filename[0] == '.')
    {
        if (filename[1] == 0)
            return 1 ; 
        if (filename[1] == '.')
        {
            if (filename[2] == 0)
                return 1 ; 
        }
    }
    return 0 ; 
}


