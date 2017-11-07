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
// cs_geomalgos.h - class and function prototypes  for specialty
//      geometric processing algorithms


#ifndef __CS_GEOMALGOS_H__
#define __CS_GEOMALGOS_H__

#include "cs_shapes.h"
#include "cs_curves.h"


//! Work out transform to map point set a to b
/*!
    \param psa input array of three points on shape A
    \param psb input array of three matching points on shape B
    \param rx  the transformation matrix mapping shape A to B
    \return 0 on success, else an error code. 

    Work out the transformation to map point set A onto point set b, 
    This effectively returns the reverse transform. If point set A
    A is transformed by the matrix returned in rx, then it
    should match curve B. 
    
    Note, the matrix returned is of the form:
      | a b 0 s |
      | c d 0 t |
      | 0 0 1 0 |
      | 0 0 0 1 |
    where [s,t] represent a 2D translation. and a,b,c,d are a basic
    2D transformation. The Z component is ignored completely when 
    performing this operation.

    Returns: 0 = success, 
           1 = only singular matrix results were generated 
           2 = some other error occured
  */  
int CS_CalcReverseTransform2D(CS_POINT *psa, CS_POINT *psb, CS_MTX4 &rx) ;

//! Takes the start points of the first three segments of each curve and
//! then calls CS_CalcReverseTransform2D(...) for final result
int CS_ReverseTransform2D(CS_Curve &ca, CS_Curve &cb, CS_MTX4 &rx) ;

//! Clip a segment to the specified rectangle
/*!
    \param rect the clipping rectangle
    \param pseg the segment to be clipped
    \param seglist the output resultant set of clipped segments
    \return The number of segments that remain after the clipping 
    operation. Ranges from [0,5]. This will equal the number of segments
    added to the seglist
 */
int CS_ClipToRect(CS_RECT &rect, CS_SegPtr pseg, CS_SegmentList &seglist) ; 


//! Returns a point that is inside the input curve
/*!
    \param pcrv pointer to closed curve
    \param inspnt the resultant point
    \return 0=success, otherwise an error code (usually curve is open)

    The routine attempts to find a point that is more or less centered
    within the shape defined by pcrv. It draws a line from UPoint(0) to 
    UPoint(0.5) and then sees if the midpoint is inside. If it is
    then that is the point returned. Otherwise the line is divided
    in two alternating halves until a point is found that is inside 
    the shape. If more than 1000 iterations are required then the routine
    aborts and returns an error code. 
 */
int CS_GetPointInside(CS_CurvePtr pcrv, CS_POINT &inspnt) ;


//! Returns a point that is a little outside the input curve
/*!
    \param pcrv pointer to closed curve
    \param outpnt the resultant point
    \return 0=success, otherwise an error code (usually curve is open)

    The bounding box for the shape is generated. Then a point 25% 
    beyond the edge of the right center of the bounding box is returned
    as the outside point for the shape. The Z component of the point 
    will be the same as the startpoint for the curve
 */
int CS_GetPointOutside(CS_CurvePtr pcrv, CS_POINT &outpnt) ;


// Returns the intersection set
/*
    \param unputSet set of closed general input curves (which may be modified on return)
    \param intersectedSet instersection set of input curves that actual intersected in some way.
    \param nonIntersectedSet those curves on the input that intersected with nothing. 
    \param chaintol used to modify the default chaining tolerance
    \return an error code, 0=success

    The first step in the processing calls Complete(CCW) on each of the inputSet 
    curves. Thus the input curves will be modified in that they may be reversed 
    if they were not in the CCW direction on input. 
    
    The intersectedSet contains the set of outer boundaries defined for all of the 
    input curves that actually intersected with one or more of the other input curves. 
    The nonIntersectedSet are copies of the input curves that did not intersect with
    any of the other input curves. This way you can decide whether or not to include 
    the copied curves for further processing. To get the complete intersection set of 
    curves simply call intersectedSet.AppendSet(nonIntersectedSet) after this call. 

    Note, upon return, anything in the nonIntersectedSet will have been removed 
    from the inputSet. This way we minimize the number or curves that have to be
    created. It is up to the user to make copies afterward if required.
 */
int CS_CreateIntersectionSet(CS_CurveSet &inputSet, 
                             CS_CurveSet &intersectedSet, 
                             CS_CurveSet &nonIntersectedSet,
                             double *chaintol=0, double *revangtol=0) ; 

// Returns set of largest outer loops that can be made from input curves
/*
    \param inset set of general input curves
    \param outset set of non-connected curves defining container for all input curves
    \return an error code, 0=success
    
    The outset contains a separate curve for each island grouping of curves that
    exist within the input set. Each curve in the out set is the outside contour
    enclosing the input curves in each individual island group. 

    Probably a better idea to use CS_CreateIntersectionSet(...) since this one
    is not fully tested yet. 
 */
int CS_CreateOuterBoundaries(CS_CurveSet &inset, CS_CurveSet &outset) ;



// TODO EVERYTHING FROM HERE TO --------------------->



// Return the closest points on the two segments
/*
    \param psa pointer to first segment to test
    \param psb pointer to the second segment to test
    \param pnta point on segment A closest to segment B
    \param pntb point on segment B closest to segment A
    \return 0=error, 1=segments intersect pnta==pntb, 2=two points returned
 */
int CS_ClosestPoints(CS_SegPtr psa, CS_SegPtr psb, CS_POINT &pnta, CS_POINT &pntb) ;
int CS_ClosestPoints(CS_LineSeg *psa, CS_LineSeg *psb, CS_POINT &pnta, CS_POINT &pntb) ;
int CS_ClosestPoints(CS_LineSeg *psa, CS_ArcSeg  *psb, CS_POINT &pnta, CS_POINT &pntb) ;
int CS_ClosestPoints(CS_ArcSeg  *psa, CS_ArcSeg  *psb, CS_POINT &pnta, CS_POINT &pntb) ;


// Return the closest points on the two segments
/*
    \param psa pointer to first segment to test
    \param psb pointer to the second segment to test
    \param ua u parm for point on segment A closest to segment B
    \param ua u parm for point on segment B closest to segment A
    \return 0=error, 1=segments intersect pnta==pntb, 2=two points returned
 */
int CS_ClosestPoints(CS_SegPtr psa, CS_SegPtr psb, double &ua, double &ub) ;

//  ---------------------------> HERE
// None of the above section is actually implemented. USE CS_MinDistance2D(...)



#endif  