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
// trimcrvs.cpp - segment and CS_Curve trim operations

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
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#else
#define CS_DEBUG(a)
#define CS_DEBUGAL(a)
#define CS_DEBUGCREATE(a)
#endif




void CS_Segment::TrimStart(double u)
{
}

void CS_Segment::TrimEnd(double u)
{
}

void CS_Segment::Trim(double u1, double u2)
{
}


void CS_LINE::TrimStart(double u)
{
    // Set start point to the UPoint at u
    sp = UPoint(u) ;
}

void CS_LINE::TrimEnd(double u)
{
    ep = UPoint(u) ;
}

// Trim out the section of the curve from u1 to u2, u1<u2 must be true
void CS_LINE::Trim(double u1, double u2)
{
    // Have to save temporary points since if we trim one end and then
    // the other, the U point will be in reference to a different length
    // since we will have trimmed one end already.
    CS_POINT tpnt ; // temporary point
    if (tcomp_EQZ(u1))
    {
	TrimEnd(u2) ;
	return ;
    }
    else if (tcomp_EQ(u2, 1.0))
    {
	TrimStart(u1) ;
	return ;
    }

    // Otherwise we are trimming out a center section of the curve
    // Curve is in the forward direction
    tpnt = UPoint(u1) ;
    ep = UPoint(u2) ;
    sp = tpnt ;
}


void CS_ARC::TrimStart(double u)
{
    if (tcomp_EQZ(swp))
	return ; // nothing to do since the arc angle is zero

    // The start angle is going to change and we still have
    // to update the sweep parameter
    double uang ;
    uang = UAngle(u) ; // this is the new start angle 

    // The only thing left to calculate is the new sweep value which
    // will be the delta from [u,1] range. Thus the new sweep is:
    // swp = swp - (swp * u) = swp * (1 - u) ;
    swp = swp * (1.0 - u) ; // the rest of the arc
    sa = mod2PI(uang) ; 
}

void CS_ARC::TrimEnd(double u)
{
    if (tcomp_EQZ(swp))
	return ; // nothing to do since the arc angle is zero

    // The only thing left to calculate is the new sweep value which
    // will be the delta from [0,u] range. Thus the new sweep is:
    swp = swp * u ;
}

void CS_ARC::Trim(double u1, double u2)
{
    // Here we are trimming the start and the end of the arc. First
    // test for the special cases where either u1=0 or u2=1 so that
    // we can call the TrimEnd and TrimStart commands respectively

    if (tcomp_EQZ(u1))
    {
	TrimEnd(u2) ;
	return ;
    }

    if (tcomp_EQ(u2, 1.0))
    {
	TrimStart(u1) ;
	return ;
    }

    // Otherwise we are trimming both ends of the arc
    double ua1 ;
    ua1 = UAngle(u1) ; // this is the new start angle 

    // The only thing left to calculate is the new sweep value which
    // will be the delta from [u1,u2] range. Thus the new sweep is:
    swp = swp * (u2 - u1) ;
    sa = ua1 ; 
}


// For all the curve trim commands we have to search for the segments where
// the actual u values occur, and then work out how to trim the various
// sections off of the CS_Curve after that. We can steal some of the logic
// for doing this from the CS_Curve::UPoint routine.
void CS_Curve::TrimStart(double u)
{
    if (u < 0.0 || u > 1.0)
    {
	// TO DO - may want to call the Reset() curve operation in this case
	return ; // this is a delete entire curve operation and assumed to
		 // be an error so it is ignored
    }

    if (tcomp_EQZ(u))
	return ; // nothing to do

    SetUParameters() ; // make sure all uo parms are valid in CS_Curve
    TrimStart(UCrvPnt(u)) ; 
}

void CS_Curve::TrimStart(const CS_CrvPnt *pcp)
{
    CS_CrvPnt cp(*pcp) ; 

    if (cp.u < 0.0)
        cp.u = 0.0 ; 
    if (cp.u > 1.0)
        cp.u = 1.0 ; 

    if ((cp.s == pStart) && tcomp_EQZ(cp.u))
	return ; // nothing to do

    CS_SegPtr pn ;
    CS_SegPtr pntmp ; 
    if (tcomp_EQZ(cp.u))
    {	// The segment is zero so simply delete everything up to
	// this segment and return
	pn = pStart ;
	while (pn != cp.s)
	{
	    pntmp = pn->next ;
	    Delete(pn) ;
	    pn = pntmp ;
	}
	return ;
    }

    // All parameters required to delete the front section of the curve
    // are set, can delete the front section of the curve now.
    pn = pStart ;
    while (pn != cp.s)
    {
	pntmp = pn->next ;
	Delete(pn) ;
	pn = pntmp ;
    }

    if (tcomp_EQ(cp.u, 1.0))
    {
        Delete(cp.s) ; 
    }
    else
    {
        // Now trim the current curve
        cp.s->TrimStart(cp.u) ;
    }
    
    // Fix up the curve
    Finalize() ;
    // done
}

void CS_Curve::TrimStart(const CS_CrvPnt &cp)
{
    TrimStart(&cp) ; 
}


void CS_Curve::TrimEnd(double u)
{
    if (u < 0.0 || u > 1.0)
    {
	// TO DO - may want to call the Reset() curve operation in this case
	return ; // this is a delete entire curve operation and assumed to
		 // be an error so it is ignored
    }

    if (tcomp_EQ(u, 1.0))
	return ; // nothing to do

    SetUParameters() ; // make sure all uo parms are valid in CS_Curve
    TrimEnd(UCrvPnt(u)) ; 
}


void CS_Curve::TrimEnd(const CS_CrvPnt *pcp)
{
    CS_CrvPnt cp = *pcp ; 
    if (cp.u < 0.0)
        cp.u = 0.0 ; 
    if (cp.u > 1.0)
        cp.u = 1.0 ; 

    if ((cp.s == pEnd) && tcomp_EQ(cp.u, 1.0))
	return ; // nothing to do

    CS_SegPtr pn ;
    CS_SegPtr pntmp ; 
    if (tcomp_EQ(cp.u, 1.0))
    {   // Simply trim everything off the end until this node
        pn = pEnd ;
        while (pn != cp.s)
        {
	    pntmp = pn->next ;
	    Delete(pn) ;
	    pn = pntmp ;
        }
        return ;
    }

    // All parameters required to delete the front section of the curve
    // are set, can delete the front section of the curve now.
    pn = pEnd ;
    while (pn != cp.s)
    {
	pntmp = pn->prev ;
	Delete(pn) ;
	pn = pntmp ;
    }


    // Now trim the actual segment
    if (tcomp_EQZ(cp.u))
    {   // Deleting all of it
        Delete(cp.s) ; 
    }
    else
    {
        // Now trim the current curve
        cp.s->TrimEnd(cp.u) ;
    }

    Finalize() ; // make sure curve is valid
    // done
}

void CS_Curve::TrimEnd(const CS_CrvPnt &cp)
{
    TrimEnd(&cp) ; 
}


void CS_Curve::Trim(double u1, double u2)
{
    // Do this by calling TrimStart() and TrimEnd()
    // the problem is that the TrimStart() will modify the curve parameters
    // such that the TrimEnd() will have to be called with a modified u2
    // parameter to allow for this.
    double u2prm = (u2 - u1) / (1.0 - u1) ;
    TrimStart(u1) ;
    TrimEnd(u2prm) ;
    // done
}

// Note: From < To in terms of the overall curve must hold.
// The ends are trimmed off leaving the middle section of the curve 
void CS_Curve::Trim(const CS_CrvPnt &cpfrom, const CS_CrvPnt &cpto)
{
    Trim(&cpfrom, &cpto) ; 
}

void CS_Curve::Trim(const CS_CrvPnt *cpfrom, const CS_CrvPnt *cpto)
{
    const CS_CrvPnt *pf ;
    const CS_CrvPnt *pt ;
    if (cpfrom->s->uo > cpto->s->uo)
    {   // Reverse them
        pt = cpfrom ; 
        pf = cpto; 
    }
    else
    {
        pf = cpfrom ; 
        pt = cpto; 
    }

    double u2prm = pt->u ; 
    if (pf->s == pt->s) 
    {   // Then we have to work out the modified uTo value 
        // since the psegFrom curve is modified by the Trim 
        // command
        if (tcomp_NEQ(pf->u, 1.0))
        {
            u2prm = (pt->u - pf->u) / (1.0 - pf->u) ;
        }
        else
        {   // For this condition to occur, the trim points are 
            // identical and thus we are effectively trimming away 
            // the entire curve
            Reset() ; 
        }
    }

    CS_CrvPnt cp2nd ; 
    cp2nd.s = pt->s ; 
    cp2nd.u = u2prm ; 

    TrimStart(pf) ; 
    TrimEnd(cp2nd) ; 

}

void CS_Curve::Trim(const CS_IREC &ira, const CS_IREC &irb, int mode)
{
    Trim(&ira, &irb, mode) ; 
}

void CS_Curve::Trim(const CS_IREC *pira, const CS_IREC *pirb, int mode)
{
    const CS_CrvPnt *pcpa, *pcpb ; 
    
    // FROM 
    if (mode & CS_TRIMA_PRI0)
    {
        pcpa = &pira->cpp[0] ; 
    }
    else if (mode & CS_TRIMA_PRI1)
    {
        pcpa = &pira->cpp[1] ; 
    }
    else if (mode & CS_TRIMA_SEC0)
    {
        pcpa = &pira->cps[0] ; 
    }
    else  // CS_TRIMA_SEC1
    {
        pcpa = &pira->cps[1] ; 
    }

    // TO 
    if (mode & CS_TRIMB_PRI0)
    {
        pcpb = &pirb->cpp[0] ; 
    }
    else if (mode & CS_TRIMB_PRI1)
    {
        pcpb = &pirb->cpp[1] ; 
    }
    else if (mode & CS_TRIMB_SEC0)
    {
        pcpb = &pirb->cps[0] ; 
    }
    else  // CS_TRIMB_SEC1
    {
        pcpb = &pirb->cps[1] ; 
    }

    Trim(pcpa, pcpb) ; 
}

void CS_Curve::TrimStart(const CS_IREC &ir, int mode)
{
    TrimStart(&ir, mode) ; 
}

void CS_Curve::TrimStart(const CS_IREC *pir, int mode)
{
    const CS_CrvPnt *pcp ; 
    
    if (mode & CS_TRIMA_PRI0)
    {
        pcp = &pir->cpp[0] ; 
    }
    else if (mode & CS_TRIMA_PRI1)
    {
        pcp = &pir->cpp[1] ; 
    }
    else if (mode & CS_TRIMA_SEC0)
    {
        pcp = &pir->cps[0] ; 
    }
    else  // CS_TRIMA_SEC1
    {
        pcp = &pir->cps[1] ; 
    }

    TrimStart(pcp) ; 
}

void CS_Curve::TrimEnd(const CS_IREC &ir, int mode)
{
    TrimEnd(&ir, mode) ; 
}

void CS_Curve::TrimEnd(const CS_IREC *pir, int mode)
{
    const CS_CrvPnt *pcp ; 
    
    if (mode & CS_TRIMA_PRI0)
    {
        pcp = &pir->cpp[0] ; 
    }
    else if (mode & CS_TRIMA_PRI1)
    {
        pcp = &pir->cpp[1] ; 
    }
    else if (mode & CS_TRIMA_SEC0)
    {
        pcp = &pir->cps[0] ; 
    }
    else  // CS_TRIMA_SEC1
    {
        pcp = &pir->cps[1] ; 
    }

    TrimEnd(pcp) ; 
}

