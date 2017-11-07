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
// cs_camfuncs.h - CAM library defintions

#ifndef __CS_CAMFUNCS_H__ 
#define __CS_CAMFUNCS_H__


struct CAM4XEventRec
{
    CS_Curve *pcrv1 ; 
    CS_Curve *pcrv2 ; 

    double arc1len ; 
    double arc2len ; 

    int istep ;  // current step count
    int nsteps ; // number of steps to traverse current section

    CS_CrvPnt cp1start ; // overall section start point
    CS_CrvPnt cp2start ; 

    double u1s ; // = cp1start.UCrv() ; 
    double u2s ; // = cp2start.UCrv() ; 

    CS_CrvPnt cp1end ; // overall section end point
    CS_CrvPnt cp2end ; 

    double u1e ; // = cp1end.UCrv() ; 
    double u2e ; // = cp2end.UCrv() ; 

    CS_CrvPnt cp1cur ; // current from point on first curve
    CS_CrvPnt cp2cur ; // current from point on second curve
    double u1len ; // overall curve 1 based u len for the current section 
    double u2len ; // overall curve 2 based u len for the current section 

    double seg1arclen ; 
    double seg2arclen ; 
    
    double seg1ulen ; 
    double seg2ulen ; 

    double du1 ; // overall curve 1 step size
    double du2 ; // overall curve 2 step size

    double u1i ; // overall curve 1 target u location of current step
    double u2i ; // overall curve 2 target u location of current step

    int Initialize(CS_Curve *pcrv1, CS_Curve *pcrv2) ; 

    void AdjustCurvePoint(CS_CrvPnt &cp) ; 
    int InitializeSection(CS_CurveSyncDataVec &csvec, int i, double stepsize) ; 
    
    // Returns true if incrementing the current uli value by du1 takes
    // things to the next segment
    int JumpsToNextSeg(CS_CrvPnt &cp, double ui, double du) ; 

    void NextSeg1() ; // increment to the next segment on curve 1
    void NextSeg2() ; // increment to the next segment on curve 2

    void NextEvent() ; // move to next event position
} ; 


//! Generate 4 axis wire paths
/*!
    \param p1crv input planar curve 1
    \param z1crv input Z height of planar curve 1
    \param p2crv input planar curve 2
    \param z2crv input Z height of planar curve 2
    \param xycrv the output xycrv
    \param uvcrv the output uvcrv
    \param ZXY Z height of the output XY plane curve
    \param ZUV Z height of the output UV plane curve
    \param stepsize resolution step to walk along p1crv with
    \param csvec synchronization data vector
    \return error code, 0=OK

    This walks along the p1crv using the stepsize value for each section 
    of the p1crv as defined by the synchronization lines. The sections
    define regions over which the steps will be evenly divided between 
    the p1crv and p2crv. it is possible to have zero length sections
    for one or the other curve. For zero length sections then, u1 would
    increment while u2 doesn't or vice versa. This would be defined 
    by two sequential synch lines whose u value on the same curve
    match. If no synch lines are defined then the routine automatically 
    defines one synch line at the start and end of the curves. 

    The synchronization data, if defined must be properly formatted. 
    If it is not defined, then a single set of synch lines will be 
    internally generated that spans the full length of both segments.
    The synch sections must occur in pairs, thus if passing in a full
    loop that does not start at the curve startpoint then the first
    and last synch data definition should be identical. If a closed
    loop starts at the start point then the two ends can be different
    in that the start u=0 and the end u=1 is possible even though thses
    define the same point on the curve. If u.i > u.i+1 then it is 
    assumed that the curve is closed and the routine simply walks through
    the end/start point of the curve. 

    The z1crv and z2crv should start at x=0, and proceed in the positive 
    x direction such that the x coordinate of the endpoint of the curves 
    matches the arclength of the p1crv and p2crv respectively. The y 
    value of the z1crv and z2crv are used as the Z height along the
    p1crv and p2crv. Thus each step u coordinate along the p1crv grabs
    the matching point on the z1crv and extracts the y value to be used
    as the Z height. 

    \todo Update for spline support. 

    In the future, a second version of this function will be defined whereby
    the p1crv and p2crv do not have to be planar and can have the required
    Z height data within the curve itself. This will be done when full 
    spline support is included in the package. 

 */
int
CS_4AXWirePathGen(CS_Curve &p1crv, CS_Curve &z1crv,  
                  CS_Curve &p2crv, CS_Curve &z2crv,  
                  CS_Curve &xycrv, CS_Curve &uvcrv,
                  double ZXY, double ZUV, double stepsize,            
                  CS_CurveSyncDataVec &csvec) ;

//! Generate 4 axis wire paths
/*!
    \param splinecrv XY projection of the curve which oscillates
    \param zsplinecrv Z oscillation data
    \param clrcrv defines the planar clearance curve
    \param zoclr the reference Z height for clearance curve
    \param zdepclr the reference dep of the clearance curve
    \param xycrv the output xycrv
    \param uvcrv the output uvcrv
    \param ZXY Z height of the output XY plane curve
    \param ZUV Z height of the output UV plane curve
    \param stepsize resolution step to walk along p1crv with
    \param csvec synchronization data vector
    \return error code, 0=OK

  Similar to the CS_4AXWirePathGen() function except that in this version
  only the spline curve has Z component data. The clrcrv is taken as flat.
  The angle of the wire is calculated as the shortest distance from the 
  splinecurve to the clearance curve forming the base of a triangle, and 
  the value (zoclr-zdepclr) as the height of the triangle. Then using 
  similar triangles to work out distances the XY and UV plane points are 
  generated where the XY plane point is in the negative vector direction
  of Vsc where Vsc is the XY plane projected vector from the spline
  curve point to the nearest clearance curve point. 

  */
int CS_4AXWirePathAngGen(CS_Curve &splinecrv, CS_Curve &zsplinecrv, 
                         CS_Curve &clrcrv, double zoclr, double zdepclr,
                         CS_Curve &xycrv, CS_Curve &uvcrv,
                         double ZXY, double ZUV, double stepsize,         
                         CS_CurveSyncDataVec &csvec) ;




#endif