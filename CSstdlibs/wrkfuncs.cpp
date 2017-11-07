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

// wrkfuncs.cpp - general functions


#include "wrkfuncs.h"

#include <io.h>

// See Notes MISC-01RR Pg 41

//////////////////////////////////////////////////////////////////////
// Reverse read line.
// read the next string in the file going backwards
// DO TO - make this more efficient by reading blocks and buffering
// the blocks etc...
// No newlines are returned in the result string
// WARNING: read the NT specific note below about buffer issues
// when reading long lines and fseek()
char *fgetsrev(char *buf, int buflen, FILE *fp)
{
    if (!fp)
        return 0 ; 

    int i, br ; 
    buf[buflen-1] = '\0' ; // NULL term temp string
    if (buflen < 2)
        return 0 ; // can't do anything since no room for data

    i = buflen - 2 ; // stuff bytes into buffer starting at the end
    buf[i] = 0 ; 
    // Read characters from the end and sutff into back end of buffer until
    // a new line is read. Then stop


    // If newline is the first character read then read backwards from there
    // until the next newline, and then leave the file pointer on the newline
    // character since we jump backwards 2 characters for every character 
    // that is read. 

    // Newlines are scanned intelligently in UNIX, NT is broken since 
    // it does CRLF mapping during reads, but an fseek treats them as
    // separate characters. Pain in the but

#ifdef UNIX
    if (fseek(fp, -2, SEEK_CUR)) // move back one
        return 0 ; 

    do {
        br = fread(&buf[i], 1, 1, fp) ; 
        if ((br == 0) || (buf[i] == '\n'))
            break ; // beginning of file, or newline
        if (fseek(fp, -2, SEEK_CUR)) // move back one
            break ; 
    } while (--i >= 0) ; 
#else
    /////////////////////////////////////////////////////////////
    // NT Specific NT Specific NT Specific NT Specific
    /////////////////////////////////////////////////////////////
    // The assumption here is that we always enter the routine
    // after just having read a newline character. Thus we start
    // one past a CRLF pair (in DOS text files only) and so we
    // have to jump back two characters. If a partial line is
    // read and the routine exits without just having read a 
    // newline, then two characters will be missed later on
    // IMPORTANT - when reading in reverse in NT make sure that the 
    // file is opened in binary mode, otherwise the fseek() does 
    // strange things.
    int fileHandle = _fileno(fp);

    if (_lseeki64(fileHandle, (__int64)(-3), SEEK_CUR) == (_int64)-1 )
        return 0 ; 


    // if (fseek(fp, -3, SEEK_CUR))
    //     return 0 ; 
    
    do {
        br = (int)fread(&buf[i], 1, 1, fp) ; 
        if ((br == 0) || (buf[i] == '\n'))
            break ; // beginning/end of file or newline
        if (_lseeki64(fileHandle, (__int64)(-3), SEEK_CUR) == (_int64)-1 )
            break ; // hit beginning of file
    } while (--i >= 0) ; 

#endif 

    if (buf[i] == '\n')
        ++i ; 

    if (i > 0)
    {   // Then we have to move the memory
        for (int j=0; i < buflen; ++i, ++j)
            buf[j] = buf[i] ; 
    }

    return buf ; 
}
