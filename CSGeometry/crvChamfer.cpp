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
// crvChamfer.cpp

// Creates - Segment to Segment chamfer lines

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)     a
#else
#define CS_DEBUG(a)
#endif


int CS_Curve::Chamfer(CS_SegPtr psna, double dista, double distb) 
{
    CS_SegPtr psnb ; 
    if (!psna)
        return -1 ; 
    
    if (Closed())
        psnb = Next(psna) ; 
    else 
        psnb = psna->next ; 

    if (!psnb)
        return -2 ; 

    // Now have the two segments that need to be chamfered
    double uabrk, ubbrk ; // the two chamfer break points

    if (distb == 0.0)
        distb = dista ; 

    uabrk = 1.0 - (dista / psna->ArcLength()) ; 
    ubbrk = distb / psnb->ArcLength() ; 

    // Need to trim the end off of psna
    psna->TrimEnd(uabrk) ; 

    // Need to trim the start off of psnb 
    psnb->TrimStart(ubbrk) ; 

    // Add a line segment to fill in where the chamfer was. 
    CS_LineSeg *pls = new CS_LineSeg(psna->EndPoint(), psnb->StartPoint()) ; 
    InsertAfter(psna, pls, CS_NOENDPOINTADJUSTMENT) ; 

    return 0 ; 
}
