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
// bspPolygon.cpp


#include "cs_bspTree.h"


CS_BSPPolygon::CS_BSPPolygon()
{
    poly = 0 ; 
    poly3D = 0 ; 
}


CS_BSPPolygon::~CS_BSPPolygon()
{
    delete poly ; 
}


int CS_BSPPolygon::Init(CS_Polygon *pcrv)
{
    poly3D = pcrv ; // copy the curve

    // Establish a plane for the polygon.
    CS_POINT pnts[3] ; 
    int npnts = 0 ; 
    CS_VECTOR va, vb, vx, vy, vz ; 
    
    pnts[npnts++] = poly3D->StartPoint() ;

    CS_POINT p ; 
    while (poly3D->NextPoint(p))
    {
        pnts[npnts] = p ; 
        if (npnts == 1)
        {   // Then this is the second point that was just set
            va = CS_VECTOR(pnts[0], pnts[1]) ; 
            if (va.Mag() > 0)
            {
                npnts++ ; 
                vx = va.Unit() ; 
            }
        }
        else if (npnts == 2)
        {   // Then this is the 3rd point that was just set
            pnts[npnts] = p ; 
            vb = CS_VECTOR(pnts[1], pnts[2]) ; 
            if (vb.Mag())
            {
                vz = va * vb ;
                if (!tcomp_EQZ(vz.Mag()))
                {   // Then we have our unit vectors
                    vz = vz.Unit() ;
                    vy = vz * vx ;
                    npnts++ ; 
                }
            }
        }
    }
    
    // Now have 3 coordinate system axes vectors defined
    pln.n = vz ; 
    pln.p = pnts[0] ; 

    mxpa.SetXYZO(vx,vy,vz, pln.p) ; 
    mxap = mxpa ; 
    CS_MTX3 mx(mxpa) ; 
    mx.Invert() ; 
    mxap = mx ; 
    mxap.SetOrigin(-1.0 * pln.p) ; 

    // coordinate systems defined, last step is to setup the 
    // polygon curve in the plane coordinate system. 
    if (poly)
        delete poly ; 
    poly = new CS_Polygon ; 

    poly3D->psegnext = 0 ; 
    poly3D->NextPoint(p) ; 
    while (poly3D->NextPoint(p)) 
    {
        CS_POINT px = mxap * p ; 
        poly->AddPoint(px) ; 
    } 

    centroid = poly3D->Centroid() ; 
    area = fabs(poly->Area()) ; 
    
    return 0 ; 
}



