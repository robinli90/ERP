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

// cs_endian.cpp

void LE4toBE1(void *psrc, void *pdst) 
{
    *(unsigned char *)pdst = *(unsigned char *)psrc ; 
}

void LE4toBE2(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 1) = *(unsigned char *)psrc ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 1) ; 
}

void LE4toBE3(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 2) = *(unsigned char *)psrc ; 
    *((unsigned char *)pdst + 1) = *((unsigned char *)psrc + 1) ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 2) ; 
}

void LE4toBE4(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 3) = *(unsigned char *)psrc ; 
    *((unsigned char *)pdst + 2) = *((unsigned char *)psrc + 1) ; 
    *((unsigned char *)pdst + 1) = *((unsigned char *)psrc + 2) ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 3) ; 
}

// Convert Little Endian orderings to Big Endian orderings
void LE2toBE1(void *psrc, void *pdst) 
{
    *(unsigned char *)pdst = *(unsigned char *)psrc ; 
}

void LE2toBE2(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 1) = *(unsigned char *)psrc ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 1) ; 
}

void LE2toBE3(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 2) = 0 ; 
    *((unsigned char *)pdst + 1) = *(unsigned char *)psrc ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 1) ; 
}

void LE2toBE4(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 3) = 0 ; 
    *((unsigned char *)pdst + 2) = 0 ; 
    *((unsigned char *)pdst + 1) = *(unsigned char *)psrc ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 1) ; 
}


/////////////////////////////////////////////////////////////
// Convert Big Endian orderings to Little Endian orderings //
/////////////////////////////////////////////////////////////
///////////////////////
// MOTOROLA -> INTEL //
///////////////////////

void BE4toLE1(void *psrc, void *pdst) 
{
    *(unsigned char *)pdst = *((unsigned char *)psrc + 3) ; 
}

void BE4toLE2(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 1) = *((unsigned char *)psrc + 2) ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 3) ; 
}

void BE4toLE3(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 2) = *((unsigned char *)psrc + 1) ; 
    *((unsigned char *)pdst + 1) = *((unsigned char *)psrc + 2) ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 3) ; 
}

void BE4toLE4(void *psrc, void *pdst) 
{
    *((unsigned char *)pdst + 3) = *(unsigned char *)psrc ; 
    *((unsigned char *)pdst + 2) = *((unsigned char *)psrc + 1) ; 
    *((unsigned char *)pdst + 1) = *((unsigned char *)psrc + 2) ; 
    *(unsigned char *)pdst       = *((unsigned char *)psrc + 3) ; 
}
