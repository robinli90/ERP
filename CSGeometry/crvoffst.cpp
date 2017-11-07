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
// crvoffset.cpp - the CS_Curve offsetting routines


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

#include "cs_offset.h"
#include "cs_offsoval.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif


// This offset simply call each segments basic offset function without
// any consideration given to adjoining segments. A disjoint curve will
// likely result from this operation. Also, the arc length most likely 
// will not be valid after this runs. 
void CS_Curve::Offset1(double delta)
{
    CS_SegPtr pn ;
    pn = pStart ;
    while (pn)
    {
	pn->info &= ~CRV_ARCCONVEX ; // clear the inversion bit
	pn->Offset(delta) ; // so that it set correctly in the offset
	pn = pn->next ;
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;

}






////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// TO DO - clean this up so that we store the tangent vector we need
// and pass in the remaining parameters so that we don't have to do the 
// extra offset operation as well as all the memory allocations.
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// Internal function which calculates the arc to insert into the parent
// curve
// Returns true if an insert arc was generated, else it returns false
// in which case the two offset segments end points are equal
/*
int inline offsetArc2(double delta, CS_SegPtr psega, CS_SegPtr psegb,  
                CS_ArcSeg *piaseg)
{
    CS_VECTOR vtae, vtbs ; // tangent at segment a end and b start
    CS_POINT aoepnt, bospnt ; // A end point and B start point of offset segs
    CS_POINT cpnt ;        // cpnt == end point a == start point b
                           // which is the center of the inserted arc 
    CS_VECTOR vcae, vcbs ; // vector from arc center to the offset points

    double zx ; // tangent vectors cross product Z component
    double sang, eang ; // start and end angle of inserted arc

    vtae = psega->UTangent(1.0) ; // a end point tangent
    vtbs = psegb->UTangent(0.0) ; // b start point tangent
    cpnt = psega->EndPoint() ; 
    zx = ZCross(vtae, vtbs) ; 
    
    // Need the b offset result but we don't want to store it yet so
    // we need to create a temp B object. 
    if (psegb->SegmentType() == LINE_TYPE)
    {
        CS_LineSeg *plnseg = new CS_LineSeg ;
        *plnseg = *((CS_LineSeg *)psegb) ; 
        plnseg->Offset(delta) ; 
        bospnt = plnseg->StartPoint() ;
        delete plnseg ;
    }
    else
    {   // ARC_TYPE 
        CS_ArcSeg *parcseg = new CS_ArcSeg ; 
        *parcseg = *((CS_ArcSeg *)psegb) ; 
        parcseg->Offset(delta) ; 
        if (tcomp_EQZ(parcseg->rad))
        {
            delete parcseg ;
        }
        bospnt = parcseg->StartPoint() ; 
        delete parcseg ; 
    }
    
    psega->Offset(delta) ; // offset the current segment
    if ((psega->SegmentType() == ARC_TYPE) && 
        (tcomp_EQZ(((CS_ArcSeg *)psega)->rad)))
        return 0 ; // can't connect an arc to a zero length segment

    aoepnt = psega->EndPoint() ; 
    if (aoepnt == bospnt)
    {
        // Did have this if in here but realized it wasn't needed
        // if (vtae == vtbs)
        return 0 ; // tangent condition so don't insert arc
    }
    
    vcae = CS_VECTOR(cpnt, aoepnt) ; 
    vcbs = CS_VECTOR(cpnt, bospnt) ; 
    
    sang = vcae.AngleXY() ; 
    eang = vcbs.AngleXY() ; 

    piaseg->ctr = cpnt ; 
    piaseg->rad = fabs(delta) ; 
    piaseg->sa = sang ; 
    
    // Note the iaseg arc inverse flag is 0 at this point
    
    if (zx > 0)
    {
        piaseg->swp = arc_sweep(sang, eang, CCW) ; 
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(piaseg->swp, RADIAN360))
            return 0 ; 
        if (delta < 0)
            piaseg->info |= CRV_ARCCONVEX ; // set the inverse bit
    }
    else
    {
        piaseg->swp = -arc_sweep(sang, eang, CW) ;
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(fabs(piaseg->swp), RADIAN360))
            return 0 ; 

        if (delta > 0)
            piaseg->info |= CRV_ARCCONVEX ; 
    }
    return 1 ; // insert the arc that was calculated
}


// Offset1 followed by arc insertion making the resultant curve continuous
// See notes RR-Vol1 Pgs 130-132
void CS_Curve::Offset2(double delta)
{
    if (tcomp_EQZ(delta) || !pStart)
        return ; // nothing to do

    int wasclosed = Closed() ; // save if the input curve is closed or not

    CS_SegPtr pna ; 
    CS_SegPtr pnb ; // used to be a seg node here
    CS_SegPtr pfirstseg ; // Need to save the first segment

    pna = pStart ;
    // When looping we only offset the current segment and work out the 
    // inserted arc for the second segment. Note we must offset the second
    // segment to work out various parameters, but it cannot be changed
    // until the next offset step is taken

    // Make a copy of the first segment 
    pfirstseg = 0 ; 
    if (pna->pseg->SegmentType() == LINE_TYPE)
    {   
        CS_LineSeg *pls = new CS_LineSeg ; 
        *pls = *((CS_LineSeg *)pna->pseg) ; 
        pfirstseg = pls ; 
    }
    else
    {
        CS_ArcSeg *pas = new CS_ArcSeg ; 
        *pas = *((CS_ArcSeg *)pna->pseg) ; 
        pfirstseg = pas ; 
    }

    while (pna && pna->next)
    {
        CS_ArcSeg *piaseg = new CS_ArcSeg ; // inserted arc segment
        // Calculate the arc to insert
        pnb = pna->next ; 
        if (offsetArc2(delta, pna->pseg, pnb->pseg, piaseg))
            InsertAfter(pna, piaseg, CS_NOENDPOINTADJUSTMENT) ; 
        else
        {
            if (pna->pseg->SegmentType() == ARC_TYPE)
            {   // Check if we created a zero radius arc and
                // delete it if that is the case
                pas = (CS_ArcSeg *)pna->pseg ; 
                if (tcomp_EQZ(pas->rad))
                {
                    Delete(pna) ; 
                }
            }
            delete piaseg ; // free up the arc since not used
        }
        pna = pnb ; 
    }

    // pn will point to the very last segment at this point
    if (wasclosed)
    {   // Then we have to calculate the offset for the last and first segment
        CS_ArcSeg *piaseg = new CS_ArcSeg ; // inserted arc segment

        if (offsetArc2(delta, pna->pseg, pfirstseg, piaseg))
            InsertAfter(pna, piaseg, CS_NOENDPOINTADJUSTMENT) ; 
        else
            delete piaseg ; // free up the arc since not used
    }
    else
    {   // Simply offset the last segment
        pna->pseg->Offset(delta) ; 
    }

    // free copy of the first segment
    delete pfirstseg ; 

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;
}
*/




// Returns 0 if the insert arc cannot be created, (which will 
// occur if the insert arc ends up having zero length) otherwise
// it returns true to indicate that the arc was created and is
// defined in piaseg 

// TO DO - this runs in 2N time since it scans through at the end to remove
// 0 radius arc segments. Could speed this up by deleting zero rad arcs
// on the fly, right now I just can't be bothered.
// This is the preliminary offset called by the main Minkowski sum style
// command Offset()
void CS_Curve::Offset2(double delta)
{
    if (tcomp_EQZ(delta) || !pStart)
        return ; // nothing to do

    int wasclosed = Closed() ; // save if the input curve is closed or not
    
    CS_ArcSeg insertArc ; // temporary work space used to create insert arc
    CS_ArcSeg *pas ;  // used for temporary arc caclulations
    CS_SegPtr pna ;
    CS_SegPtr pnb ;
    CS_VECTOR vtae, vtaetmp, vtbs ; 
    CS_POINT ctrpnt ; 
    int zx ;  // cross product z component
    // A end point and B start point of offset segs
    CS_POINT aoepnt, bospnt ; 

    // When looping we only offset the current segment and work out the 
    // inserted arc for the second segment. Note we must offset the second
    // segment to work out various parameters, but it cannot be changed
    // until the next offset step is taken

    CS_VECTOR vtanstart = pStart->UTangent(0.0) ; 
    CS_POINT  startofspnt, startpnt ; 
    
    // Offset the initial segment
    startpnt = pStart->StartPoint() ; 

    pna = pStart ;
    pnb = pna->next ; 
    vtae = pna->UTangent(1.0) ; 
    pna->Offset(delta) ; 
    // Note if we end up with a zero length arc then the start and
    // end points are returned as the center of the arc so that 
    // we don't have to do any special testing here for that 
    // condition. A final pass to delete all zero length arcs is 
    // done after we've finished offseting
    startofspnt = pna->StartPoint() ; 

    while (pna && pnb)
    {
        vtbs = pnb->UTangent(0.0) ;
        ctrpnt = pnb->StartPoint() ;
        zx = ZXOffsetArcDirection(vtae, vtbs, pna, pnb) ;

        // Save variable we need from B before we offset it
        // Note: we only need to store the tangent vector to handle the 
        // case where we insert an arc inwards and leave it with a zero
        // radius. This would make it impossible to calculate tangent
        // vectors (not really true since all we need are the swp and 
        // start angles)

        vtaetmp = pnb->UTangent(1.0) ; 

        pnb->Offset(delta) ;

        aoepnt = pna->EndPoint() ;
        bospnt = pnb->StartPoint() ;

        if (OffsetInsertArc(&insertArc, ctrpnt, aoepnt, bospnt, delta, zx))
        {   // Add the arc. 
            pas = new CS_ArcSeg(insertArc) ; 
            InsertAfter(pna, pas, CS_NOENDPOINTADJUSTMENT) ;
        }
        
        // Transfer temp variables over
        vtae = vtaetmp ; 

        pna = pnb ;
        pnb = pnb->next ;
    }

    // pn will point to the very last segment at this point
    if (wasclosed)
    {   // Then we have to calculate the offset for the last and first segment
        zx = ZXOffsetArcDirection(vtae, vtanstart, pna, pStart) ;
        aoepnt = pna->EndPoint() ;

        if (OffsetInsertArc(&insertArc,startpnt,aoepnt,startofspnt,delta,zx))
        {   // Add the arc. 
            pas = new CS_ArcSeg(insertArc) ; 
            InsertAfter(pna, pas, CS_NOENDPOINTADJUSTMENT) ;
        }
    }


    // Now rescan and remove zero radius arcs
    pna = pStart ; 
    while (pna) 
    {
        if (pna->SegmentType() == CS_Segment::ARC_TYPE)
        {
            pas = (CS_ArcSeg *)pna ; 
            if (tcomp_EQZ(pas->rad))
            {   // Then delete this segment of the curve
                pnb = pna->next ; 
                Delete(pna) ; 
                pna = pnb ; 
            }
            else
                pna = pna->next ; 
        }
        else
            pna = pna->next ; 
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;
}

//////////////////////////////////////////////////////////////////////////
// Does a basic offset and inserts reflex arcs and marks them as such
// but does not insert convex (inverse arcs)
//////////////////////////////////////////////////////////////////////////
void CS_Curve::OffsetWithReflexArcs(double delta)
{
    if (tcomp_EQZ(delta) || !pStart)
        return ; // nothing to do

    int wasclosed = Closed() ; // save if the input curve is closed or not

    CS_ArcSeg insertArc ; // temporary work space used to create insert arc
    CS_ArcSeg *pas ;  // used for temporary arc caclulations
    CS_SegPtr pna ;
    CS_SegPtr pnb ;
    CS_VECTOR vtae, vtaetmp, vtbs ; 
    CS_POINT ctrpnt ; 
    int zx ;  // cross product z component
    // A end point and B start point of offset segs
    CS_POINT aoepnt, bospnt ; 

    // When looping we only offset the current segment and work out the 
    // inserted arc for the second segment. Note we must offset the second
    // segment to work out various parameters, but it cannot be changed
    // until the next offset step is taken

    CS_VECTOR vtanstart = pStart->UTangent(0.0) ; 
    CS_POINT  startofspnt, startpnt ; 
    
    // Offset the initial segment
    startpnt = pStart->StartPoint() ; 

    pna = pStart ;
    pnb = pna->next ; 
    vtae = pna->UTangent(1.0) ; 
    pna->Offset(delta) ; 
    // Note if we end up with a zero length arc then the start and
    // end points are returned as the center of the arc so that 
    // we don't have to do any special testing here for that 
    // condition. A final pass to delete all zero length arcs is 
    // done after we've finished offseting
    startofspnt = pna->StartPoint() ; 

    while (pna && pnb)
    {
        vtbs = pnb->UTangent(0.0) ;
        ctrpnt = pnb->StartPoint() ;
        zx = ZXOffsetArcDirection(vtae, vtbs, pna, pnb) ;

        // Save variable we need from B before we offset it
        // Note: we only need to store the tangent vector to handle the 
        // case where we insert an arc inwards and leave it with a zero
        // radius. This would make it impossible to calculate tangent
        // vectors (not really true since all we need are the swp and 
        // start angles)

        vtaetmp = pnb->UTangent(1.0) ; 

        pnb->Offset(delta) ;

        aoepnt = pna->EndPoint() ;
        bospnt = pnb->StartPoint() ;

        if (OffsetInsertReflexArc(&insertArc, ctrpnt, aoepnt, bospnt, delta, zx))
        {   // Add the arc. 
            pas = new CS_ArcSeg(insertArc) ; 
            InsertAfter(pna, pas, CS_NOENDPOINTADJUSTMENT) ;
        }
        
        // Transfer temp variables over
        vtae = vtaetmp ; 

        pna = pnb ;
        pnb = pnb->next ;
    }

    // pn will point to the very last segment at this point
    if (wasclosed)
    {   // Then we have to calculate the offset for the last and first segment
        zx = ZXOffsetArcDirection(vtae, vtanstart, pna, pStart) ;
        aoepnt = pna->EndPoint() ;

        if (OffsetInsertReflexArc(&insertArc,startpnt,aoepnt,startofspnt,delta,zx))
        {   // Add the arc. 
            pas = new CS_ArcSeg(insertArc) ; 
            InsertAfter(pna, pas, CS_NOENDPOINTADJUSTMENT) ;
        }
    }


    // Now rescan and remove zero radius arcs
    pna = pStart ; 
    while (pna) 
    {
        if (pna->SegmentType() == CS_Segment::ARC_TYPE)
        {
            pas = (CS_ArcSeg *)pna ; 
            if (tcomp_EQZ(pas->rad))
            {   // Then delete this segment of the curve
                pnb = pna->next ; 
                Delete(pna) ; 
                pna = pnb ; 
            }
            else
                pna = pna->next ; 
        }
        else
            pna = pna->next ; 
    }

    // Clear the following status bits
    statflags &= ~(CS_XY_ARCLENGTH_VALID) ;
}



// Used in the machining offset routine to see if two segment interesections
// are contiguous
int CS_Curve::SequentialSegments(const CS_CrvPnt *ppa, const CS_CrvPnt *ppb, double *compTol)
{
    // For the two segments to be contiguous the (ua,ub) must be (0,1) or (1,0)
    // And the segments must be adjacent
    if (compTol)
    {
        if (tcomp_EQZ(ppa->u, *compTol) && tcomp_EQ(ppb->u, 1.0, *compTol))
        {   // Then test the (0,1) condition
            // thus segment b must lead segment a for this condition to 
            // be true. 
            if (ppb->s->next == ppa->s)
                return 1 ; // they are sequential
            if ((ppb->s == pEnd && ppa->s == pStart) && (statflags & CS_CLOSEDCURVE))
                return 1 ; 
        }
        else if (tcomp_EQZ(ppb->u, *compTol) && tcomp_EQ(ppa->u, 1.0, *compTol))
        {   // test the (1,0) condition
            // thus segment a must lead segment b for this condition to 
            // be true. 
            if (ppa->s->next == ppb->s)
                return 1 ; // they are sequential
            if ((ppa->s == pEnd && ppb->s == pStart) && (statflags & CS_CLOSEDCURVE))
                return 1 ; 
        }
    }
    else
    {
        if (tcomp_EQZ(ppa->u) && tcomp_EQ(ppb->u, 1.0))
        {   // Then test the (0,1) condition
            // thus segment b must lead segment a for this condition to 
            // be true. 
            if (ppb->s->next == ppa->s)
                return 1 ; // they are sequential
            if ((ppb->s == pEnd && ppa->s == pStart) && (statflags & CS_CLOSEDCURVE))
                return 1 ; 
        }
        else if (tcomp_EQZ(ppb->u) && tcomp_EQ(ppa->u, 1.0))
        {   // test the (1,0) condition
            // thus segment a must lead segment b for this condition to 
            // be true. 
            if (ppa->s->next == ppb->s)
                return 1 ; // they are sequential
            if ((ppa->s == pEnd && ppb->s == pStart) && (statflags & CS_CLOSEDCURVE))
                return 1 ; 
        }
    }

    return 0 ; // else false
}


////////////////////////////////////////////////////////////////////////////



