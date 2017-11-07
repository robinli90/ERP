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
// shapeXForm.cpp - works out the transformation to map two 
//      identical shapes onto one another.

#include "cs_geomdefs.h"

#include "cs_geomalgos.h"

#ifdef CSDEBUG
#define CS_DEBUG(a)         a ; 
#else
#define CS_DEBUG(a)
#endif

//! Calculate the transform required to map the first shape to the second
/*!
 Work out the transformation to map curve a onto curve b, 
 This effectively returns the reverse transform. If curve
 a is transformed by the matrix returned in CS_MTX3, then it
 should match curve b. 
 Note, the matrix returned is of the form:
      | a b 0 s |
      | c d 0 t |
      | 0 0 1 0 |
      | 0 0 0 1 |
 where [s,t] represent a 2D translation. and a,b,c,d are a basic
 2D transformation. The Z component is ignored completely when 
 performing this operation.
 
  Input: CS_Curve &ca - curve representing the base shape
         CS_Curve &cb - curve representing the test shape

  Output: MTX4 &rx - the matrix which will transform 
          ca into cb. Thus on return ca.Transform(revXFrom.m)
          will generate cb

  Returns: 0 = success, 
           1 = only singular matrix results were generated 
           2 = some other error occured


  Input:
       CS_POINT *psa - array of three points on shape A
       CS_POINT *psb - array of three matching points on shape B
    Output: 
        CS_MTX4 &rx  - the transformation matrix mapping shape A to B

    returns 1 if no reverse transform solution found. 
    returns 0 on success

 */  
int CS_CalcReverseTransform2D(CS_POINT *psa, CS_POINT *psb, CS_MTX4 &rx)
{
    //   See notes: Geom Algo's RR-VOL3 pgs 150-157

    CS_DEBUG (
        fprintf(fpDebugOut, "Curve A Points\n") ; 
        psa[0].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        psa[1].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        psa[2].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        fprintf(fpDebugOut,"Curve B Points\n") ; 
        psb[0].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        psb[1].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        psb[2].Print(fpDebugOut) ; fprintf(fpDebugOut,"\n") ; 
        fprintf(fpDebugOut, "\n") ; 
    ) ; 

    // End trivial input test case assignment of points
    ////////////////////////////////////////////////////

    // Now create the system of equations that need to be solved
    CS_MTX3 mx ; 
    CS_POINT abs, cdt ; // solutions

    mx.m[0] = psa[0].x ; mx.m[1] = psa[0].y ; mx.m[2] = 1.0 ; 
    mx.m[3] = psa[1].x ; mx.m[4] = psa[1].y ; mx.m[5] = 1.0 ; 
    mx.m[6] = psa[2].x ; mx.m[7] = psa[2].y ; mx.m[8] = 1.0 ; 

    CS_POINT q0, q1 ; 

    q0.x = psb[0].x ;
    q0.y = psb[1].x ;
    q0.z = psb[2].x ;

    q1.x = psb[0].y ;
    q1.y = psb[1].y ;
    q1.z = psb[2].y ;

    // This forms the first set of equations which will 
    // give us a,b of the solution matrix

    // The gauss jordan routine returns true if the matrix is 
    // singular, otherwise, false is returned meaning that there
    // is a valid result in A (a is inverted by this operation, with
    // the result vector b suitably modified)
    CS_VECTOR v(0,0,0) ; 
    if (CS_gaussj(mx.m, 3, v.v, 1))
    {   // Then matrix is singular
        return 1 ; 
    }


    // mx is inverted so now generate the solution vector
    abs = mx * q0 ;
    cdt = mx * q1 ;

    rx.m[0] = abs.x ; rx.m[1] = abs.y ; rx.m[2]  = 0 ; rx.m[3]  = abs.z ;
    rx.m[4] = cdt.x ; rx.m[5] = cdt.y ; rx.m[6]  = 0 ; rx.m[7]  = cdt.z ;
    rx.m[8] = 0     ; rx.m[9] = 0     ; rx.m[10] = 1 ; rx.m[11] = 0 ;

    return 0 ;
}


int CS_ReverseTransform2D(CS_Curve &ca, CS_Curve &cb, CS_MTX4 &rx)
{
    // To proceed, we need 3 matching key points from each shape.
    CS_POINT psa[3], psb[3] ; // point sets for curve a and b

    /*************************************************************
    The method used for extracting the 3 key points used is the 
    main heuristic problem in working out the inverse transform.
    Ideally we want to generate three points which create two 
    vectors of different length that are at 45->135 degrees to each
    other. This way their cross product is well defined, while also 
    making a unique set of points that isolates the mirroring,
    translation and rotation transformations simultaneously.
    **************************************************************/

    ////////////////////////////////////////////////////
    // Trivial input test case assignment of points
    /*
    psa[0] = ca.StartPoint() ; 
    psa[1] = ca.UPoint(0.3) ; 
    psa[2] = ca.UPoint(0.7) ; 

    psb[0] = cb.StartPoint() ;
    psb[1] = cb.UPoint(0.3) ;
    psb[2] = cb.UPoint(0.7) ;
    */
    if (ca.nodecnt < 2 || cb.nodecnt < 2)
        return 2 ;

    psa[0] = ca.pStart->StartPoint() ; 
    psa[1] = ca.pStart->EndPoint() ; 
    psa[2] = ca.pStart->next->EndPoint() ; 

    psb[0] = cb.pStart->StartPoint() ; 
    psb[1] = cb.pStart->EndPoint() ; 
    psb[2] = cb.pStart->next->EndPoint() ; 


    return CS_CalcReverseTransform2D(psa, psb, rx) ; 
}

struct _compMSPInfo
{
    CS_SegPtr psn ;
    double ias, iae ; // internal angle at segment start and end
} ;

static int compMSP(const void *a, const void *b)
{
    _compMSPInfo *pa = (_compMSPInfo *)a ;
    _compMSPInfo *pb = (_compMSPInfo *)b ;

    if (pa->psn->SegmentType() < pb->psn->SegmentType())
        return -1 ; 
    if (pa->psn->SegmentType() > pb->psn->SegmentType())
        return 1 ; 

    // Else they're the same type so test further
    double la = pa->psn->ArcLength() ; 
    double lb = pb->psn->ArcLength() ; 
    
    if (tcomp_LT(la, lb))
        return -1 ; 
    if (tcomp_GT(la, lb))
        return 1 ; 
    return 0 ; // equal 
}


// Test to see if the segments before and after the one pointed to 
// by index are different, and if so return true, otherwise return
// false.
int CS_MSP_UniqueSegment(_compMSPInfo *pcia, int nodecnt, int idx)
{
    if (nodecnt <= 1)
        return 1 ; // trivial case

    bool bDifferentFromPrev = false ; 
    bool bDifferentFromNext = false ;
    
    if (idx == 0)
        bDifferentFromPrev = true ;
    else
    {
        if (!pcia[idx].psn->Similar(pcia[idx-1].psn)) 
            bDifferentFromPrev = true ;
    }

    if (bDifferentFromPrev)
    {   // if bDifferentFromPrev wasn't true there would be no point
        // doing the following, but since it is we keep testing
        if (idx == nodecnt - 1)
            bDifferentFromNext = true ;
        else
        {
            if (!pcia[idx].psn->Similar(pcia[idx+1].psn)) 
                bDifferentFromNext = true ;
        }
    }

    if (bDifferentFromPrev && bDifferentFromNext)
        return 1 ; 
    return 0 ; 
}

// See file shapeXForm.cpp for actual code
int CS_Curve::MatchCurveStartPoints(CS_Curve &cb, CS_POINT *prefthis, CS_POINT *prefb)
{
    // To do this we need to 
    cb.Finalize() ; 

    if (nodecnt != cb.nodecnt)
        return 1 ;

    if (tcomp_NEQ(arclength, cb.arclength)) 
        return 2 ; 

    _compMSPInfo *pcia = new _compMSPInfo[nodecnt] ; 
    _compMSPInfo *pcib = new _compMSPInfo[cb.nodecnt] ; 

    CS_SegPtr psn = pStart ; 
    int i = 0 ; 
    while (psn)
    {
        pcia[i].ias = 0 ;
        pcia[i].iae = 0 ;
        pcia[i++].psn = psn ; 
        psn = psn->next ; 
    }
    
    i = 0 ; 
    psn = cb.pStart ; 
    while (psn)
    {
        pcib[i].ias = 0 ;
        pcib[i].iae = 0 ;
        pcib[i++].psn = psn ; 
        psn = psn->next ; 
    }
    
    // Now sort the segments by type, followed by arc length
    qsort(pcia, nodecnt, sizeof(_compMSPInfo), compMSP) ; 
    qsort(pcib, nodecnt, sizeof(_compMSPInfo), compMSP) ; 

    // Preliminaries are done. From here we try to find a unique 
    // segment within the psna array (the *this curve). If there is no
    // unique segment using compMSP, then have to use more information
    int foundStartPoint = 0 ; 

    for (i=0; i < nodecnt; i++)
    {   // See if there is any segment that does not have a matching 
        // segment on either side of it, if so then it is unique
        if (CS_MSP_UniqueSegment(pcia, nodecnt, i))
            break ; 
    }

    if (i < nodecnt)
    {   // Then we found a unique segment
        cb.SetStartSegment(pcib[i].psn) ; 
        foundStartPoint = 1 ; 
    }

    delete[] pcia ; 
    delete[] pcib ; 

    if (foundStartPoint)
        return 0 ; 

    // Perform the O(n^2) search 
    // Start at each node in *this. Then start at each node in curve
    // b and see if all segments match up as you walk around the curve.

    // First process with curve B in the forward direction
    CS_SegPtr pMatch ; 

    pMatch = 0 ; 
    psn = cb.pStart ; 
    int detectedMismatch = 0 ; 
    while (psn)
    {   
        if (Similar(cb, psn, prefthis, prefb))
        {
            pMatch = psn ; 
            break ; 
        }
        psn = psn->next ; 
    }

    if (pMatch)
        cb.SetStartSegment(pMatch) ;
    else
    {   // Test B curve in reverse
        cb.Reverse() ; // have to reverse the curve for things to work
        psn = cb.pStart ; 
        int detectedMismatch = 0 ; 
        while (psn)
        {   
            if (Similar(cb, psn, prefthis, prefb))
            {
                pMatch = psn ; 
                break ; 
            }
            psn = psn->next ; 
        }

        if (pMatch)
            cb.SetStartSegment(pMatch) ;
        else
            return 3 ;
    }

    return 0 ; 
}



/*!
  int CS_Curve::Similar(...)  - Tests whether or not two curves are similar
        by checking if the segments within the two curves are similar.

  Input 
    CS_Curve &crvb - the curve being compared against
    CS_SegPtr psnstart - start segnode on the B curve
    CS_POINT *refPntthis - Optional default=0 (or NULL)
                a reference point to be used in testing
                the distance to the end point of the segment on the
                base *this curve. This distance is compared against
                the equivalent distance obtained from the B curve 
                reference point to the end point of the segment on 
                the B curve
    CS_POINT *refpntB - Optional default=0 (or NULL)
                reference point used in testing equivalent
                distances to the base *this curve. The distance from
                this reference point to the end point of the B 
                segments is tested. 

  Output: 
    Nothing

  Returns - 1 if the two curves are similar over their entire length
            0 if any mismatches occur.

 */
int CS_Curve::Similar(CS_Curve &crvb, CS_SegPtr psnstart, 
                      CS_POINT *refPntthis, CS_POINT *refpntB) 
{
    CS_SegPtr psna = pStart ; 
    CS_SegPtr psnb = psnstart ; 
    while (psna)
    {
        if (!psna->Similar(psnb))
            return 0 ; 
        if (refPntthis)
        {
            double da = CS_Distance(*refPntthis, psna->EndPoint()) ; 
            double db = CS_Distance(*refpntB, psnb->EndPoint()) ; 
            if (tcomp_NEQ(da, db))
                return 0 ; 
        }
        psnb = crvb.Next(psnb) ; 
        psna = psna->next ; 
    }

    return 1 ; 
}

