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
// cs_convexhull.h

// TO DO - figure this out and document it, get rid of CS_List also

#ifndef __CS_CONVEXHULL_H__
#define __CS_CONVEXHULL_H__


struct CS_CHTestData
{
    int status ; 
    double u0 ; // curve 0 u intersect point
    double u1 ; // curve 1 u intersect point
    CS_POINT pnt0 ; // points correspond to u values
    CS_POINT pnt1 ; 
} ;

typedef CS_List<CS_CHTestData> CS_CHTestDataList ;

///////////////////////////////////////////////////////////////////////
// Calculate convex hull of two segments
// The int value returned is a bit ORed result of the following flags
#define CS_CH_MODFIEDSEG_0          0x00000001
#define CS_CH_MODFIEDSEG_1          0x00000002
#define CS_CH_DELETEDSEG_0          0x00000004
#define CS_CH_DELETEDSEG_1          0x00000008
#define CS_CH_BRIDGECREATED         0x00000010
#define CS_CH_BRIDGEDALL            0x0000001f

// Returns the resultant curve if more than 3 points are passed in
// Note if the 3 points are collinear then the curve returned
// will be 4 line segments  two straight out, and two that walk
// back straight back over the original two. 
CS_Curve *CalcHullPoints(CS_POINT *ppnts, int npnts) ;

int CalcHullSegmentARC_ARC(CS_ArcSeg *pseg0, CS_ArcSeg *pseg1, CS_Curve *prescrv) ;
int CalcHullSegmentARC_LINE(CS_ArcSeg *pseg0, CS_LineSeg *pseg1, CS_Curve *prescrv) ;
int CalcHullSegmentLINE_ARC(CS_LineSeg *pseg0, CS_ArcSeg *pseg1, CS_Curve *prescrv) ;
int CalcHullSegmentLINE_LINE(CS_LineSeg *pseg0, CS_LineSeg *pseg1, CS_Curve *prescrv) ;

CS_Curve *CS_ConvexHull(CS_Curve &crv) ;

#endif
