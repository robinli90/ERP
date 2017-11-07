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
#include "math.h"
#include "cs_shapes.h"
#include "cs_rects.h"


#ifndef min
#define min(a,b)        (a < b ? a : b) 
#define max(a,b)        (a > b ? a : b) 
#endif


// The z component is ignored
// The point coords are adjusted to form a top left bottom right 
// rectangular definition
CS_RECT::CS_RECT(CS_POINT &pa, CS_POINT &pb)
{
    if (pa.p[0] < pb.p[0])
    {
        l = pa.p[0] ;
        r = pb.p[0] ; 
    }
    else
    {
        r = pa.p[0] ;
        l = pb.p[0] ; 
    }

    if (pa.p[1] < pb.p[1])
    {
        b = pa.p[1] ;
        t = pb.p[1] ; 
    }
    else
    {
        t = pa.p[1] ;
        b = pb.p[1] ; 
    }
}

CS_RECT::CS_RECT(double top, double left, double bottom, double right) 
{
    t = top ; 
    l = left ; 
    b = bottom ; 
    r = right ; 
}

//! Returns the center point of the rectangle
CS_POINT CS_RECT::Center()
{
    return CS_POINT((l+r)/2.0, (t+b)/2.0, 0.0) ; 
}

//! Returns the center point of the rectangle
CS_POINT CS_RECT::Centre()
{
    return CS_POINT((l+r)/2.0, (t+b)/2.0, 0.0) ; 
}

//! Tests if the point is inside or on the rectangle
int CS_RECT::Inside(CS_POINT &pnt)
{
    if ((tcomp_GEQ(pnt.p[0],l) && tcomp_LEQ(pnt.p[0],r)) &&
        (tcomp_GEQ(pnt.p[1],b) && tcomp_LEQ(pnt.p[1],t)))
        return 1 ; 
    return 0 ; 
}

int CS_RECT::Inside(CS_POINT &pnt, const double &tol)
{
    if ((tcomp_GEQ(pnt.p[0],l, tol) && tcomp_LEQ(pnt.p[0],r, tol)) &&
        (tcomp_GEQ(pnt.p[1],b, tol) && tcomp_LEQ(pnt.p[1],t, tol)))
        return 1 ; 
    return 0 ; 
}



// multiplies all the internal parms by the scaling factor
// NOTE: this has the effect of also translating the rectangle 
// in space, only use this if the only thing you are interested 
// in is the actual volume of the rectangle and not its location.
// To expand or shrink the rectangle use the Expand function below
CS_RECT &CS_RECT::Scale(double sfactor)
{
    t *= sfactor ;
    l *= sfactor ;
    b *= sfactor ;
    r *= sfactor ;
    return *this ; 
}


// Enlarges or shrinks the rectangle by the scale factor. A scale
// factor of zero will leave the rectangle as it was. A negative 
// scale factor will shrink the rectangle and a positive scale factor
// will enlarge the rectangle. The centroid of the rectangle will 
// remain the same after this operation. A scale factor of 2 will 
// result in a rectangle who's sides are all three times as long as the 
// original since half the current length of a side will be added to 
// each edge of the rectangle.
//      Scale        Side Dimension 
//                       delta %
//         .               0.0     |  Anything in this region causes
//         .               0.0     |  the resulting rectangle to invert
//         .               0.0     |  and grow to a larger size
//       -5.0           -500.0     |
//       -4.0           -400.0     |
//       -3.0           -300.0    /
//       -2.0           -200.0    ==> Inverted rectangle same as original
//       -1.0           -100.0    ==> rectangle with zero area
//        0.0              0.0    No Change
//        1.0            100.0
//        2.0            200.0
//        3.0            300.0
//        4.0            400.0
  
CS_RECT &CS_RECT::Expand(double scale)
{
    double vdelta, hdelta ; 
    vdelta = fabs(t - b) * scale / 2.0 ; 
    hdelta = fabs(r - l) * scale / 2.0 ; 
    if (vdelta == 0.0)
        vdelta = hdelta ; 
    else if (hdelta == 0.0)
        hdelta = vdelta ; 
    t += vdelta ;
    l -= hdelta ;
    b -= vdelta ;
    r += hdelta ;
    return *this ; 
}

CS_RECT &CS_RECT::Union(CS_RECT &rect)
{
    r = max(r, rect.r) ;
    l = min(l, rect.l) ;
    t = max(t, rect.t) ;
    b = min(b, rect.b) ;
    return *this ; 
}

// See RR-Vol1 Pg 137
int CS_RECT::Overlaps(CS_RECT &B) 
{
    if ((r <= B.l) || (t <= B.b) || (l >= B.r) || (b >= B.t))
        return 0 ; 
    return 1 ; 
}


//***********************************************************************
//                      3D Bounding boxes
//***********************************************************************


CS_BoundBox::CS_BoundBox(const double &d)
{
    Init(d) ; 
}

CS_BoundBox &CS_BoundBox::Init(const double &d)
{
    minpnt.x = d ; 
    minpnt.y = d ; 
    minpnt.z = d ; 

    maxpnt.x = -d ; 
    maxpnt.y = -d ; 
    maxpnt.z = -d ; 

    return *this ; 
}

CS_BoundBox &CS_BoundBox::UpdateMinMaxPnts(CS_POINT &p)
{
    if (p.x < minpnt.x)
        minpnt.x = p.x ; 
    if (p.y < minpnt.y)
        minpnt.y = p.y ; 
    if (p.z < minpnt.z)
        minpnt.z = p.z ; 

    if (p.x > maxpnt.x)
        maxpnt.x = p.x ; 
    if (p.y > maxpnt.y)
        maxpnt.y = p.y ; 
    if (p.z > maxpnt.z)
        maxpnt.z = p.z ; 

    return *this ; 
}

// Set the bounding box for the curve
CS_BoundBox &CS_BoundBox::SetMinMaxPnts(CS_Curve *pcrv) 
{
    CS_SegPtr pseg = pcrv->pStart ; 
    // These are bounding box points for all the planes
    UpdateMinMaxPnts(pseg->StartPoint()) ;
    while (pseg)
    {
        UpdateMinMaxPnts(pseg->EndPoint()) ; 
        pseg = pseg->next ; 
    } 
    return *this ; 
}