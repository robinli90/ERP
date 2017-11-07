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
// cs_nmcurves.h

#ifndef __CS_NMCURVES_H__
#define __CS_NMCURVES_H__

//! structure used for fast binary search of some variable x mapping to u coord
//! when segments will be added in sequence
struct CS_X2SegRec
{
    CS_SegPtr pseg ; 
    double x ; 
} ;

typedef vector<CS_X2SegRec> CS_X2SegRecVec ; 
typedef vector<CS_X2SegRec>::iterator CS_X2SegRecVecItr ; 

//! Class to perform binary search of data records
class CS_FastSegVector 
{ 
public:

    CS_X2SegRecVec vs ; 

    CS_FastSegVector() {} ; 
    CS_SegPtr Find(double x) ; 
} ;


//! \todo implement the map lookup routines. 
//! Structure to be used when we need to add segments in random order
/*
typedef map<x, CS_SegPtr> CS_SegPtrMap ; 
typedef map<x, CS_SegPtr>::iterator CS_SegPtrMapItr ; 

//! Class to perform binary search of data records
class CS_FastSegMap 
{ 
public:

    CS_SegPtrMap segmap ; 

    CS_FastSegMap() {} ; 
    CS_SegPtrMapItr AddSegRec(CS_SegPtr pseg, double &x) ; 
    CS_SegPtr FindSeg(double x) ; 
} ;
*/




//! Class to build a curve from stepwise points
/*!
    Points are passed to the AddPoint() member function one at a time, each
    point defining the next subsequent step in the crv that is being 
    built. Sequential points that are collinear end up defining a single 
    line segment. Similarily, sequential points that all lie on the same
    arc end up defining a single arc. This then attempts to minimize the 
    number of segments in the final curve. Note that if the steps are too
    small then points that would normally generate arcs could be output
    as small line segments. The reason is that if 3 points are found to 
    be collinear within the system tolerance, then those points 
    automatically define a line segment. With slightly larger steps 
    however, the third point may not be on the line in which case the 
    system switches to arc mode, and subsequent points that still fall
    on the same curve as the arc, get appended to that arc. There
    are limits as to how large a step that can be taken while still 
    generating expected results. The reason being that a very large
    step could still randomly happen to occur on the curve of the 
    temporary arc being built which would result in strange output curves.

    The cp temporary points are used to reference a master curve that was
    used to build this new curve from points. This makes it possible to
    synchronize the two curves together. The cp will always refer to the 
    point on the master curve that corresponds to the start of the segment
    in the curve that is being built in a piecewise manner.
 */
class CS_PntCurveBuilder
{
public:
    enum {
        NOMODE      = 0, 
        LINEMODE    = 1, 
        ARCMODE     = 2, 
        NEXTSEG     = 3, 
    } ;

    //! saves current mode
    int mode ;

    //! the curve being built, must be allocated before use
    CS_CurvePtr pcrv ; 
    
    //! Last two input points, temporary storage
    CS_POINT pl[2] ; 

    //! Last two references to base curve, temporary storage. 
    CS_CrvPnt rcp[2] ;

    //! Number of temporary points defined. 
    int np ; 
    

    //! The current line segment when in LINEMODE
    CS_LineSeg line ; 
    
    //! The current arc segment when in ARCMODE
    CS_ArcSeg arc ;

    //! Constructor 
    CS_PntCurveBuilder() ;


    //! Incorporate the point P defined by pointangle into the arc. 
    /*! 
        \param pointangle the angle of the new point w.r.t. the arc 

        The point (P) being merged into the arc should be close to one of the
        end points of the arc for this to work reliably. The point P must not
        be within the sweep of the arc otherwise the arc will end up being 
        reduced in size.

        The arc used in the calculations is the member arc variable for the class. 
     */
    void IncludeArcPoint(double pointangle) ;

    //! Returns the current mode
    /*!
        \param nextpnt the next point to be added to the curve
        \param cp reference to the base curve that corresponds to nextpnt
        \return the current mode.

        The points are expected to be input in a manner similar to taking
        small steps down the resultant curve. Large steps can be used 
        if the input points are well defined, otherwise strange results
        will be generated. See the overall class description for further
        details. 
     */
    int AddPoint(CS_POINT &nextpnt, CS_CrvPnt &cp) ; 

    //! Complete the current segment
    void CompleteSegment() ; 
        
} ;


//! Curve segment node synchronization data structure
struct CS_CurveSyncData
{
    //! curve A overall u coordinate of synch point w.r.t.A
    double ua ; 

    //! curve B overall u coordinate of synch point w.r.t.B
    double ub ; 

    //! curve A segment synch point, cpa.UCrv() == ua 
    CS_CrvPnt cpa ;

    //! curve B segment synch point, cpb.UCrv() == ub
    CS_CrvPnt cpb ; 
} ;

typedef vector<CS_CurveSyncData> CS_CurveSyncDataVec ; 
typedef vector<CS_CurveSyncData>::iterator CS_CurveSyncDataVecItr ; 


//! Synchronize the segment end points between the two curves 
/*!
    \param crva the first curve to synchronize
    \param crvb the second curve to synchronize
    \param scrva the synchronized output curve A
    \param scrvb the synchronized output curve B
    \param pdata pointer to the curve synchronization points array
    \param ndata number of entries in the curve synchronization array
    \return error code, 0=OK

    Synchronizes the two curves together so that a segment by segment walk down
    both curves simultaneously will keep the two curves matched. For example, 
    say you are trying to drive a numerically controlled machine (NC machine)
    and there are two simultaneous but interconnected paths to be followed
    by the control such as with a 4 axis wire EDM path. In the case of the wire
    EDM machine there is an XY plane curve that must be synchronized to a
    UV plane curve. Say the XY curve is a circle defined by 1 arc segment which
    is passed in as crva, and the UV curve is a circle defined by four 
    arcs that span each of the 4 quadrants in a cartesian coordinate system. 
    Now say you want to synch these two curves together but skewed in the top
    view such that the resultant shape cut by the wire is a tube with a concave
    arc section swepth out around it. This function will automatically break
    up crva in 4 sections and start crva such that the skewed start points 
    of the two curves are the start points of the two start segments. 

    SPECIAL CONDITIONS: if the ua value for an entry in the pdata array is
    equal to 1 and the curve is closed, it should be reset to 0. This is 
    needed for the internal logic to work correctly in the case there are
    multiply defined nodes that cross the 0/1 boundary on the B curve 
    simulatneously with the 0/1 node on the A curve. This could be fixed
    but would require an additional sort step which is probably being 
    done elsewhere so for effeciency this condition must be met. 

    For multiply defined nodes of where the [ua,ub] value pairs for subsequent
    nodes match, for example [.4, .2] [.5, .6] [.5, .7] [ .5, .8] [.7, .1]
    then there will be 2 zero length point segments defined in the A curve
    in this case so that the number of segments in the A and B curve are 
    identical even though you end up with 0 length segments in one or both
    of the curves. 

    If required call CS_SortCurveSynchData(...) to put the nodes in the 
    correct order. 

    This function will never reduce the number of segments in either of the 
    curves passed in. The minimum effect will be to leave the number of 
    segments the same. 

    The array of synch points passed in defines how the two curves are aligned.
    In between the respective synch points the u values along both curves are 
    swept out in proportionately spaced amounts. 

    This function could also be used to define the motion of the XY and AB axes 
    of a multi axis milling operation, or any other operation where you need
    to walk along two curves in some sort of synchronized manner. Ultimately 
    this function is not really required since the operation could be directly
    implemented elsewhere, but it can serve to simplify the logic of certain 
    programming operations.

    If crva is open then processing will only occur between the first and
    last record in the data array. If the {0,1} nodes are to be included,
    then entries at the start and end points of the curve must be defined
    as the first and last entries in the data array respectively. 
    If the curve is opened and no pdata is passed in then the crva u=0 
    and the crvb u=0 are used as the base starting synch points and then 
    everything is linearly scanned from there, where linearly is defined 
    in terms of the parametric u value along both curves. 

    Note, the opened/closed logic is determined by the crva curve. 
 */
int CS_CurveSynch(CS_Curve &crva, CS_Curve &crvb, 
                  CS_Curve &scrva, CS_Curve &scrvb, 
                  CS_CurveSyncData **pdata=0, int ndata=0) ;

//! Free memory in a CS_CurveSyncData array
int CS_FreeCurveSyncData(CS_CurveSyncData **pdata, int ndata) ;

//! Sort and adjust the entries in a CS_CurveSyncData array
int CS_SortCurveSyncData(CS_CurveSyncData **pdata, int ndata, int closed) ;



//! Returns the sweep step for arc to line approximation
/*!
    \param arc input arc to be approximated
    \param tol tolerance value, max chord height away from arc
    \param swpstep output sweep step along arc to be used to create lines
    \param nsteps the number of steps required at swpstep
    \return Error code, 0=all ok, -1=sweep angle is zero 

    This works out the angle step from the start angle to the end angle that is required
    to fit lines segments around an arc where all line segment end points lie on the 
    arc. Thus arc.UPoint(arc.AngleU(swp + swpstep * n)) are the end points of the 
    line segments where n is the step count. nsteps * swpstep will be equal to the 
    sweep of the arc. If the arc is CW then swpstep will be negative and if the arc
    is CCW then swpstep will be positive. Thus you can simply do
    
    \verbatim
    CS_Curve lnsegcrv ; 
    for (int n=0; n < nsteps; n++)
    {
        lnsegcrv.Append(new CS_LineSeg(
                    arc.UPoint(arc.AngleU(arc.sa + swpstep * n)),
                    arc.UPoint(arc.AngleU(arc.sa + swpstep * n+1))) ; 
    }
    \endverbatim

    To generate a curve of line segments after calling this function. See also 
    CS_ArcToLine which directly generates the curve for you. 

    Return error codes:
        -1 = zero radius arc
        -2 = zero step angle generated
 */
int CS_ArcToLinesInsideMode(CS_ARC &arc, double &tol, double &swpstep, int &nsteps) ; 

#define CS_LINESINSIDE     0x00000001
#define CS_LINESCROSS      0x00000002
#define CS_LINESOUTSIDE    0x00000004

//! Generate curve of line segments approximating input arc
/*!
    \param arc input arc to be converted to line segments
    \param tol max chord height tolerance when creating segments
    \param crv output curve of line segments 
    \param mode mode of operation, currently only CS_LINESINSIDE supported
    \return 0=OK, else an error code

    \todo Implement this function with all three possible modes

    The mode determines how the line segments are positioned relative to the arc. 
    In CS_LINESINSIDE mode all the line segment end points will be on the input
    arc such that the line segments will all be contained within the circle 
    defined by the arc (the arc's circle). In CS_LINESCROSS mode, the endpoints 
    of the line segments will be outside the arc's circle, but the line midpoints
    will be inside the arc's circle. This mode minimizes how far away the line 
    deviates from the arc with the least amount of segments. In CS_LINESOUTSIDE
    mode, all line segments are completely outside the arc's circle. The the lines
    outside mode, all the line segment mid points will touch the arc but the end
    points will be outside the arc's circle. A vector from the arc center to a line
    end point will have a magnitude of arc.rad + tol (for all line segments except
    the two at the ends which are really half length lines so that the end points
    of these match the start point and end point of the arc excatly.)

    Note: the mode is currently ignored, the result will always be a CS_LINESINSIDE
    type approximation. 

    Return error codes:
        -1 = zero radius arc
        -2 = zero step angle generated

 */
int CS_ArcToLines(CS_ARC &arc, double &tol, CS_Curve &crv, int mode=CS_LINESINSIDE) ;

#endif