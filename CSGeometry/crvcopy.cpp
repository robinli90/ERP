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
// crvcopy.cpp - copy sections of curves, allocating memory in process


#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)	
#else
#define CS_DEBUG(a)
#endif

CS_Curve *CS_Curve::CopySection(const CS_CrvPnt &cpstart, 
                                const CS_CrvPnt &cpend,
                                int dir) 
{
    CS_Curve *pcrv ; 
    if (dir != CS_REVERSE)
    {   // Then we are copying in the forward direction 
        // Which means the copy section below can be used
        pcrv = CopySection(cpstart.s, cpend.s, cpstart.u, cpend.u,SEGMENTBASED_UVALUES) ;
    }
    else
    {   // Want a reverse section curve
        // Then the section has to cross the [0,1] boundary, so grab
        // section in reverse, and then reverse the curve
        pcrv = CopySection(cpend.s, cpstart.s, cpend.u, cpstart.u,SEGMENTBASED_UVALUES) ;
        pcrv->Reverse() ; 
    }
    return pcrv ; 
}



// Note the curve parameters must be valid on entry 
// CalcArcLength() and SetuParameters()  or Finalize() must have been 
// called for the curve
// This must also handle the case where we request a curve section 
// such that ua > ub which means take everything from [ua,1][0,ub]
// effectively running through the end/start point of the curve


// TO DO - test if we are copying a start or end section that is zero
// length, in which case we want to ignore those sections (could 
// maybe have Finalize() filter these types out and delete them)
CS_Curve *CS_Curve::CopySection(CS_SegPtr psa, CS_SegPtr psb, 
                                double ua, double ub, int mode) 
{
    double ulen ; 
    CS_SegPtr psegn ; 
    CS_Curve *cpycrv = new CS_Curve ; 
    CS_ArcSeg *parcs ; 
    CS_LineSeg *plines ; 
    int bIsClosed = Closed() ; 

    // TO DO - decide what to do under the following condition
    // if (ua == ub)

    psegn = psa ; 

    // Test if we have to treat the first segment as a special case
    // Make sure this value is adjusted correctly
    if (mode == CURVEBASED_UVALUES)
    {
        if (ua < psa->uo)
            ua = psa->uo ; 
    }
    else
    {   // Then adjust it to the exact start of the segment
        if (ua < 0.0)
            ua = 0.0 ; 
    }

    if (((mode == CURVEBASED_UVALUES) && (ua > psa->uo)) ||
        ((mode == SEGMENTBASED_UVALUES) && (ua > 0.0)))
    {   // Then we have to split a section out of the first segment
        // So we have to work out the overall u length of this segment

        if ((psa == psb) && (ua < ub))
        {   // Then the selection lies on the same segment
            if (psa->SegmentType() == CS_Segment::LINE_TYPE)
            {   // Copy the line segment

                plines = new CS_LineSeg((CS_LineSeg *)psa) ; 
                // Have to convert ua and ub to be realtive to the overall
                // curve
                if (mode == CURVEBASED_UVALUES)
                {
                    ulen = SegmentULength(psa) ;
                    plines->Trim((ua - psa->uo)/ulen, (ub - psa->uo)/ulen) ; 
                }
                else
                {
                    plines->Trim(ua, ub) ; 
                }
                // Add this to the new curve
                if (tcomp_EQZ(plines->ArcLength()))
                    delete plines ; 
                else
                    cpycrv->Append(plines) ; 
            }
            else
            {
                parcs = new CS_ArcSeg((CS_ArcSeg *)psa); 
                // Have to convert ua and ub to be realtive to the overall
                // curve
                if (mode == CURVEBASED_UVALUES)
                {
                    ulen = SegmentULength(psa) ;
                    parcs->Trim((ua - psa->uo)/ulen, (ub - psa->uo)/ulen) ; 
                }
                else
                {
                    parcs->Trim(ua, ub) ; 
                }
                // Add this to the new curve
                if (tcomp_EQZ(parcs->ArcLength()))
                    delete parcs ; 
                else
                    cpycrv->Append(parcs) ; 
            }
            return cpycrv ; // done
        }

        // Trim off the start of the first curve
        if (psa->SegmentType() == CS_Segment::LINE_TYPE)
        {   // Copy the line segment
            plines = new CS_LineSeg((CS_LineSeg *)psa) ; 
            // Have to convert ua and ub to be realtive to the overall curve
            if (mode == CURVEBASED_UVALUES)
            {
                ulen = SegmentULength(psa) ;
                plines->TrimStart((ua - psa->uo)/ulen) ; 
            }
            else
            {
                plines->TrimStart(ua) ; 
            }

            // Add this to the new curve
            if (tcomp_EQZ(plines->ArcLength()))
                delete plines ; 
            else
                cpycrv->Append(plines) ; 
        }
        else
        {
            parcs = new CS_ArcSeg((CS_ArcSeg *)psa); 
            // Have to convert ua and ub to be realtive to the overall curve
            if (mode == CURVEBASED_UVALUES)
            {
                ulen = SegmentULength(psa) ;
                parcs->TrimStart((ua - psa->uo)/ulen) ; 
            }
            else
            {   
                parcs->TrimStart(ua) ; 
            }

            // Add this to the new curve
            if (tcomp_EQZ(parcs->ArcLength()))
                delete parcs ; 
            else
                cpycrv->Append(parcs) ; 
        }
        // set point since already processed the psa segment
        psegn = psa->next ;
        if (!psegn)
        {
            if (bIsClosed)
            {
                psegn = pStart ; 
            }
            else
                return cpycrv ; // nothing left to do
        }
    }
    // else we want the to copy from start of first segment which
    // will be handled below

    while (psegn != psb)
    {   // Copy complete elements over until we reach the end segment
        if (psegn->SegmentType() == CS_Segment::LINE_TYPE)
        {   // Copy the line segment
            plines = new CS_LineSeg((CS_LineSeg *)psegn) ; 
            if (tcomp_EQZ(plines->ArcLength()))
                delete plines ; 
            else
                cpycrv->Append(plines) ;
        }
        else
        {   // Copy the arc segment
            parcs = new CS_ArcSeg((CS_ArcSeg *)psegn); 
            if (tcomp_EQZ(parcs->swp))
                delete parcs ; 
            else
                cpycrv->Append(parcs) ;
        }
        psegn = psegn->next ; 
        if (!psegn)
        {   // Then we've wrapped around past the end of the curve
            // so we want to connect back up to the start
            if (bIsClosed)
            {
                psegn = pStart ; 
            }
            else
                return cpycrv ; // nothing left to do
        }
    }

    // we are now on the last segment that has to be copied to the new
    // curve  (psegn==psb) will be true here
    if (psegn->SegmentType() == CS_Segment::LINE_TYPE)
    {   // Copy the line segment
        plines = new CS_LineSeg((CS_LineSeg *)psegn) ; 
        if (mode == CURVEBASED_UVALUES)
        {
            ulen = SegmentULength(psegn) ;
            plines->TrimEnd((ub - psegn->uo)/ulen) ; 
        }
        else
        {
            plines->TrimEnd(ub) ; 
        }
        // Add this to the new curve
        if (tcomp_EQZ(plines->ArcLength()))
            delete plines ; 
        else
            cpycrv->Append(plines) ; 
    }
    else
    {
        parcs = new CS_ArcSeg((CS_ArcSeg *)psegn); 
        if (mode == CURVEBASED_UVALUES)
        {
            ulen = SegmentULength(psegn) ;
            parcs->TrimEnd((ub - psegn->uo)/ulen) ; 
        }
        else
        {
            parcs->TrimEnd(ub) ; 
        }

        // Add this to the new curve
        if (tcomp_EQZ(parcs->swp))
            delete parcs ; 
        else
            cpycrv->Append(parcs) ; 
    }

    cpycrv->Finalize() ; 
    // Done

    return cpycrv ; 
}


// Same as above but runs slower since it has to work out which 
// sections the ua and ub fall on.
CS_Curve *CS_Curve::CopySection(double ua, double ub)
{
    // Make sure ua and ub are in range
    if (ua < 0.0 && tcomp_EQZ(ua))
        ua = 0.0 ; 
    else if (ua > 1.0 && tcomp_EQ(ua, 1.0))
        ua = 1.0 ; 

    if (ub < 0.0 && tcomp_EQZ(ub))
        ub = 0.0 ; 
    else if (ub > 1.0 && tcomp_EQ(ub, 1.0))
        ub = 1.0 ; 

    CS_SegPtr psa = USegment(ua, CS_SEARCHBYUVALUE) ; 
    CS_SegPtr psb = USegment(ub, CS_SEARCHBYUVALUE) ; 
    return CopySection(psa, psb, ua, ub) ; 
}
