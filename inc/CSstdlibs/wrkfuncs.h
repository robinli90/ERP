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

// wrkfuncs.h - usefull functions to assist general processing etc...

#ifndef __WRKFUNCS_H__

#define __WRKFUNCS_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef WIN32
#define READMODETEXT    "rt"
#define READMODETEXTP   "rt+"
#define READMODEBIN     "rb"
#define READMODEBINP    "rb+"
#define WRITEMODETEXT   "wt"
#define WRITEMODETEXTP  "wt+"
#define WRITEMODEBIN    "wb"
#define WRITEMODEBINP   "wb+"
#define APPENDMODETEXT  "at"
#define APPENDMODETEXTP "at+"
#define APPENDMODEBIN   "ab"
#define APPENDMODEBINP  "ab+"
#else
#define READMODETEXT    "r"
#define READMODETEXTP   "r+"
#define READMODEBIN     "r"
#define READMODEBINP    "r+"
#define WRITEMODETEXT   "w"
#define WRITEMODETEXTP  "w+"
#define WRITEMODEBIN    "w"
#define WRITEMODEBINP   "w+"
#define APPENDMODETEXT  "a"
#define APPENDMODETEXTP "a+"
#define APPENDMODEBIN   "a"
#define APPENDMODEBINP  "a+"
#endif




/**
 This function is used when processing command line arguements. It allows
 parameters to be separated from -X designators with or without a space.
 To make use of it simply call when parsing off the arguement when the 
 -X character has already been extracted. Example

    string stringparm ; 
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {   // Then extract the parameter
            switch(argv[i][1])

            {   
            case 'X' :
                stringparm = GetArgPtr(argv, i, 2) ; 
                    .
                    .
                    .
                break ; 
            .
            .
            .
            .
            }
        }
    }


 */

//! Command line argument next field extractor
/*!
    \param argv the argv variable from int main(int argc, char **argv)
    \param i the current index into argv
    \param ofs the character position after the parameter characters to look at. 
    \return pointer to the next argement data. 

    If for example the command line was 

        samplecmd -ffiletest --Q tmpout -n7

    The following would happen
        for the first parameter you would do:

    \verbatim
    int main(int argc, char *argv[])
    {
        char Qparm[256] ; 
        char testfile[256] ; 
        int count = 0 ; 

        char *parg ; 
        for (int i=1; i < argc; i++)
        {
            swtich(argv[i][0])
            {
                case '-' : 
                    switch(argv[i][1])
                    {
                        case 'f' :
                            strcpy(testfile, GetArgPtr(argv, i, 2)) ; 
                            break ; 
                        case 'n' : 
                            count = atoi(GetArgPtr(argv, i, 2)) ; 
                            break ; 
                        case '-' :
                            swtich(argv[i][2]
                            {
                                case 'Q' :
                                    strcpy(GetARgPtr(argv, i, 3) ; 
                                    break ; 
                            }
                    }
                    break ; 
                default: 
                    // report error
                    break ;
            }
        }
        .
        .
        .
    }

    \endverbatim

    And if a memory fault occurs then a parameter was missing. Better error trapping can
    be done by testing pargs for null. 
    
 */
char *GetArgPtr(char **argv, int &i, int ofs) ;
char *fgetsrev(char *buf, int buflen, FILE *fp) ;



#define CS_NEQ(a,b)   (((a - 0.001) > b) || ((a + 0.001) < b))

inline unsigned long ModuloInc(unsigned long counter, unsigned long length) 
{
    counter++ ; 
    if (length)
    {   // Then must do modulo logic
        if (counter >= length) 
            counter = 0 ; 
    }
    // otherwise the modulo wrap around will occur in the 
    // accumulator of the processor
    return counter ; 
}  

inline unsigned long ModuloDec(unsigned long counter, unsigned long length) 
{
    counter-- ; 
    if (length)
    {   // Then must do modulo logic
        if (counter < 0) 
            counter = length - 1 ; 
    }
    else 
    {
        if (counter < 0)
            counter = 0 ; 
    }
    // otherwise the modulo wrap around will occur in the 
    // accumulator of the processor
    return counter ; 
}  


inline unsigned long ModuloForward(unsigned long counter,
                                   unsigned long MAXCOUNT,
                                   unsigned long offset) 
{
    if (MAXCOUNT)
        return ((counter + offset) % MAXCOUNT) ; 
    // Else length==0 which means the length is the full 
    // maximum representable long value
    return (counter + offset) ; // modulo is automatic
} 

inline unsigned long ModuloBackward(unsigned long counter,
                                    unsigned long MAXCOUNT,
                                    unsigned long offset) 
{

    unsigned long residx ; 

    if (MAXCOUNT)
        residx = counter - offset ; 
    else
        return counter - offset ; 

    // if the subtraction value is greater than 
    if (residx >= MAXCOUNT)
        residx += MAXCOUNT ; // wrapped around
    return residx % MAXCOUNT ; 
}



///////////////////////////////////////////////////////////
// PLATFORM DEPENDENT CODE - 
// Hopefully the compiler doesn't try to get cute when 
// converting an unsigned value whose magnitude is greater
// than the largest representable value in the signed 
// case. What we want to happen is to simply transfer the 
// binary bit pattern from the unsigned to the signed.
// This shouldn't even require a memory operation since it
// is the actual bit pattern. What really neads to be done
// is to code the following in assembler for each platform
// that it is transferred to. 
///////////////////////////////////////////////////////////
// Returns offset count of a from ref, basically the inverse
// of ModuloForward and ModuloBackward. The distance being 
// measured is assumed to be < MAX/2 otherwise a distance
// representing D - MAX/2 will be returned. If MAXcount is
// 0 then the full long word length is assumed to represent
// the max count or 0xffffffff (for 32 bit longs)
// (See MISC NOTES Pgs 56-69)
inline long ModuloDistance(unsigned long i,  // dist to idx
                           unsigned long N,  // reference index
                           unsigned long K)  // max count
{
    if (i == N)
        return 0 ;

    if (K == 0)
    {   // Then we have to
        unsigned long k2 = 0x80000000 ; // max divided by 2
        unsigned long iN ; 
        int negated = 0 ; 
        if (i > N)
            iN = i - N ; 
        else
        {
            iN = N - i ;
            negated = 1 ; // want negative of iN
        }

        if (N <= k2)
        {
            if (iN >= k2)
            {
                return ((long)iN) ; 
            }

            if (negated)
                return -((long)iN) ;
            return (long)iN ; 
        }
        else
        {
            if (iN >= k2)
                return labs((long)iN + 1) ; 
            if (negated)
                return - ((long)iN) ;
            return (long)iN ; 
        }
    }
    else
    {   // We are cheating here actually, the basic 
        // premise is that the functional range is 
        // [0,MAX/2-1] and then MAX itself, we exclude the
        // region where K=[MAX/2, MAX-1] (not sure if that 
        // region will work correctly)
        unsigned long k2 = K >> 1 ; // max divided by 2
        unsigned long iN ; 
        int negated = 0 ; 
        if (i > N)
            iN = i - N ; 
        else
        {
            iN = N - i ;
            negated = 1 ; // want negative of iN
        }

        if (N <= k2)
        {
            if (iN >= k2)
                return iN - K ; 

            if (negated)
                return -((long)iN) ;
            return iN ; 
        }
        else
        {
            if (iN >= k2)
                return K - iN ; 

            if (negated)
                return -((long)iN) ;
            return iN ; 
        }
    }
}


// How many steps it would take to get from fromidx to toidx when 
// incrementing one by one from fromidx point
// See: MISC NOTES Pg 61
inline unsigned long ModuloDistForward(const unsigned long fromidx, 
                                const unsigned long toidx, 
                                const unsigned long MAXCOUNT) 
{
    unsigned long result ; 
    if (MAXCOUNT == 0)
    {
        if (fromidx < toidx)
        {
            result = toidx - fromidx ; // simplest case
        }
        else
        {
            result = ~fromidx ; 
            result++ ; 
            result %= MAXCOUNT ; 
            result += toidx ; 
        }
    }
    else
    {   // modulo math internal to processor
        if (fromidx < toidx)
        {
            result = toidx - fromidx ; // simplest case
        }
        else
        {
            result = MAXCOUNT - fromidx + toidx ; 
        }
    }
    
    // Else we wrap around during the walk
    return result ; 

}

// How many steps it would take to get from fromidx to toidx when 
// incrementing one by one from fromidx point
inline unsigned long ModuloDistBackward(const unsigned long fromidx, 
                                 const unsigned long toidx, 
                                 const unsigned long MAXCOUNT) 
{
    unsigned long result ; 
    if (MAXCOUNT == 0)
    {
        if (toidx < fromidx)
        {
            result = fromidx - toidx ; 
        }
        else 
        {
            result = ~toidx ; 
            result++ ; 
            result %= MAXCOUNT ; 
            result += fromidx ; 
        }
    }
    else
    {   // modulo math internal to processor
        if (toidx < fromidx)
        {
            result = fromidx - toidx ; 
        }
        else 
        {
            result = MAXCOUNT - toidx + fromidx ; 
        }
    }
    return result ; 
}

// make sure N is divisible by four and if not rounds up so that it is
inline unsigned long MemDWordBoundary(const unsigned long n)
{
    unsigned long r = n % 4 ; 
    if (r != 0)
        return n + (4 - r) ; 
    return n ; 
}


inline unsigned short HexCharValue(const char c)
{
    if (c >= 0x30 && c <= 0x39)
        return c - 0x30 ; 
    if (c >= 0x41 && c <= 0x46)
        return c - 0x37 ; 
    return c - 0x57 ;
}

// convert a hex string to unsigned long
inline unsigned long LongHex(const char *s)
{
    unsigned long value = 0 ; 
    while (*s)
    {
        value *= 16 ; // could also do a << 4 here instead
        // not really sure which is faster
        value += HexCharValue(*s++) ;  
    }

    return value ; 
}

inline unsigned short ShortHex(const char *s)
{
    unsigned short value = 0 ; 
    while (*s)
    {
        value *= 16 ; // could also do a << 4 here instead
        // not really sure which is faster
        value += HexCharValue(*s++) ;  
    }

    return value ; 
}


#endif


