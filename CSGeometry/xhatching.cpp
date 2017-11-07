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
// xhatching.cpp - Geometric processing routines related to CS_Curve's,
//  specifically these are CAD user interface like operations


#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_cadfuncs.h"


#ifdef	CSDEBUG
#define CS_DEBUG(a)	
#else
#define CS_DEBUG(a)
#endif



int CS_XHatchLines(CS_Curve &xcrv, 
                   const double &degangle, 
                   const double &spacing, 
                   CS_POINT *ppnts, 
                   int maxpnts)
{
    xcrv.SetBoundingRect() ; 
    double alpha = degangle * DEGREEStoRADIANS ; 
    double w = xcrv.bndrect.Width() ; 
    double h = xcrv.bndrect.Height() ; 
    double sl = w + h ;
    CS_POINT S(xcrv.bndrect.BLPoint()) ; 
    CS_VECTOR vsl(1,0,0) ; 
    vsl.Rotate(alpha) ; 
    CS_LineSeg baseline(S, S+(vsl * sl)) ; 
    CS_LineSeg scanline(baseline) ; 

    double ca = cos(alpha) ;
    double sa = sin(alpha) ; 

    double ds ; // delta step
    double dv ; // vector delta offset

    // Can optimize this further by eliminating the CS_IRECList structures
    // and using predefined arrays. 

    int bFoundIntersect = 0 ; // set when the first intersect occurs during scanning
    // First do the X axis scan lines
    int n = 0 ; 
    if (tcomp_GT(sa, 0.0))
    {   // Then there is something to be done here
        ds = spacing / sa ; 
        for (dv = 0.001; (dv < w) && (n < maxpnts); dv += ds) 
        {
            scanline.sp.x = baseline.sp.x + dv ; 
            scanline.ep.x = baseline.ep.x + dv ; 

            CS_IRECList irlst ; 
            xcrv.Intersect2D(&scanline, &irlst) ; 
            
            if (irlst.size() > 0)
            {
                bFoundIntersect = 1 ;
                CS_SortIntersectSetByUValue(irlst, 1) ; // sort by line seg u values
                if (irlst.size() & 0x0001)
                    continue ; // skip whenever we have degenerate cases. 

                CS_IRECListItr iri = irlst.begin() ; 
                while (iri != irlst.end() && (n < maxpnts))
                {
                    ppnts[n].x = iri->pir->ipnt[0].x ; 
                    ppnts[n].y = iri->pir->ipnt[0].y ; 
                    n++ ; iri++ ; 
                    ppnts[n].x = iri->pir->ipnt[0].x ; 
                    ppnts[n].y = iri->pir->ipnt[0].y ; 
                    n++ ; iri++ ; 
                }
            }
            else if (bFoundIntersect)
                break ; // done
        }
    }

    scanline = baseline ; 

    if (tcomp_GT(ca, 0.0))
    {   // Then must scan up along the Y axis
        for (dv = ds; (dv < h) && (n < maxpnts); dv += ds) 
        {
            scanline.sp.y = baseline.sp.y + dv ; 
            scanline.ep.y = baseline.ep.y + dv ; 

            CS_IRECList irlst ; 
            xcrv.Intersect2D(&scanline, &irlst) ; 
            
            if (irlst.size() > 0)
            {
                bFoundIntersect = 1 ;
                CS_SortIntersectSetByUValue(irlst, 1) ; // sort by line seg u values
                if (irlst.size() & 0x0001)
                    continue ; // skip whenever we have degenerate cases. 

                CS_IRECListItr iri = irlst.begin() ; 
                while (iri != irlst.end() && (n < maxpnts))
                {
                    ppnts[n].x = iri->pir->ipnt[0].x ; 
                    ppnts[n].y = iri->pir->ipnt[0].y ; 
                    n++ ; iri++ ; 
                    ppnts[n].x = iri->pir->ipnt[0].x ; 
                    ppnts[n].y = iri->pir->ipnt[0].y ; 
                    n++ ; iri++ ; 
                }
            }
            else if (bFoundIntersect)
                break ; // done
        }
    }

    return n ; 
}
