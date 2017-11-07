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

// webStringFuncs.cpp

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "csstring.h"

//! URL encode and copy up to maximum characters. Pointer to end of string is returned
/*!
    \param dst output destination string pointer
    \param src source string pointer
    \param maxlen maximum number of output bytes 
    \return pointer to end of destination string

    The output string will always be null terminated with two 0 bytes. 
    Thus only up to maxlen - 2 (and possibly less due URL encoding 
    expansion) characters will be copied to the output string. 
 */
char *CS_URLenccpy(char *dst, const char *src, int maxlen)
{
    if (!src || !src[0])
    {
        dst[0] = 0 ; 
        return (char *)dst ; 
    }

    char *s = (char *)src ; 
    while (*s && maxlen > 2)
    {
        int ul = CS_UTF8StartChar(*s) ;
        if (ul == 1)
        {
            if (isalpha(*s) || isdigit(*s) ||
                *s == '.' || *s == '~' || *s == '-' || *s == '_')
            {   // Standard character, just copy it over
                *dst++ = *s++ ; 
                maxlen-- ; 
            }
            else if (*s == 0x20)
            {   // space character
                *dst++ = '+' ; 
                maxlen-- ; 
            }
            else if (maxlen > 5)
            {   // Must encode in hex %FF format
                *dst++ = '%' ; 
                CS_CharToHex((unsigned char *)s, dst) ; 
                s++ ; 
                dst += 2 ; 
            }
            else
            {   // insufficient space so abort
                break ; 
            }
        }
        else
        {   // This is a UTF8 character so copy it over in hex mode
            if (maxlen > (ul * 3 + 2))
            {   // Then encode it
                for (int i=0; i < ul; i++)
                {
                    *dst++ = '%' ; 
                    CS_CharToHex((unsigned char *)s, dst) ; 
                    s++ ; 
                    dst += 2 ; 
                }
            }
            else
            {
                break ; // insufficient space
            }
        }
    }

    // double null terminate
    dst[0] = 0 ; 
    dst[1] = 0 ; 
    return dst ; 
}
