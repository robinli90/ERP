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

// cs_fileblk.cpp - File access in blocks. Useful when reading from binary
//  data files where the size of the required data block is unknown except
//  by looking at the data. 

#include "stdio.h"
#include "memory.h"
#include "cs_fileblk.h"

int CS_FileBlock::LoadBuffer() 
{
    // make sure there's at least 4k 
    if (bEOF)
        return buflen ; 

    if (buflen < minreadthreshold) 
    {
        // Shift existing memory over if requried
        if (buflen > 0)
            memcpy(buf, buf + bufidx, buflen) ; 
        if (buflen < 0)
        {
            bufidx = 0 ; 
            bEOF = 1 ; // this is an error condition
            buflen = 0 ; 
            return 0 ; 
        }
        int bread = (int)fread(buf + buflen, 1, buffersize - buflen, fp) ; 
        if (bread == 0)
            bEOF = 1 ; 
        bufidx = 0 ; 
        buflen += bread ;
    }

    return buflen ;
}


int CS_FileBlock::Skip(int n)  
{
    bufidx += n ; 
    filepos += n ; 
    buflen -= n ; 
    LoadBuffer() ; 
    return buflen ; 
}
