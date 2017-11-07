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
// curves.h - definitions for using curves

#ifndef __CS_CURVES_H__
#define __CS_CURVES_H__

#ifndef FILE
#include <stdio.h>
#endif


#pragma warning (disable : 4786)

#include <csstdlibs/cslib.h>

#include "cs_vectors.h"
#include "cs_matrices.h"
#include "cs_rects.h"

#define NODIR   -1
#define CCW 0 
#define CW  1       

// The following two status bits are set when generating insert arcs during
// an offset operation. convex arcs are inserted in convex node (tangents
// meet at <180degs). Reflex arcs are inserted where tangents meet at 
// greater than 180 degrees. If tangents equal, then nothing would be
// inserted. 
#define CRV_ARCCONVEX    0x00000001  // using same terminology as M. Held
#define CRV_ARCREFLEX    0x00000002  // inserted reflex arc segment

// set to false
#define CS_ENDPOINTADJUSTMENT           0    

#define CS_NOENDPOINTADJUSTMENT         1    // set to true
#define CS_NOADJUST                     1    // short form of the above. 

#define CS_ADJUST_STARTPOINT            2    //!< used by CS_Curve::AddCurve() 

#define CS_ADJUST_ENDPOINT              3

#define CS_ADJUST_APPENDCURVE_ENDPOINTS 4    //!< CS_Curve::AddCurve parameter

#define CS_ADJUST_BASECURVE_ENDPOINTS   5    //!< CS_Curve::AddCurve parameter


//! Constant used to inidicate the forward chaining direction, as well as 
//! other forward type conditions
#define CS_FORWARD               0x01

//! Constant used to inidicate the reverse chaining direction, as well as 
//! other reverse type conditions
#define CS_REVERSE               0x02

#define CS_MINIMUM                0
#define CS_MAXIMUM                1

class CS_Segment ; 
typedef CS_Segment* CS_SegPtr ; 

//! Point on a curve segment
/*!
    \a CS_CrvPnt is used to respresent a point on a CS_Segment which is 
    an arbitrary point on a CS_Curve typically. Since the segment pointer
    and u value with respect to the segment must be carried around in 
    numerous routines, this structure makes the code easier to follow.
 */
struct CS_CrvPnt
{
public:
    
    //! Pointer to the segment that the point is on
    CS_SegPtr s ; 

    //! points u value along the segment
    double u ; 

    CS_CrvPnt() {} ;
    
    // simply using the default copy constructor
    // CS_CrvPnt(const CS_CrvPnt &b) {s = b.s; u = b.u; } 
    // CS_CrvPnt& operator=(const CS_CrvPnt &b) {s = b.s; u = b.u; return *this; } 

    void Reset() { s = 0; u =0 ; } 
    
    CS_CrvPnt(CS_SegPtr sp, double uval) : s(sp), u(uval) {} ;

    //! Returns the u value for the overall curve
    /*!
        Returns the u value of the point with respect to the overall curve
        defined by the segment's parent pointer. If the parent pointer is 
        NULL, then the function simply returns u (the CS_CrvPnt member variable). 
        Thus, make sure that the parent pointers are defined for the CS_Curve
        in order for this function to work correctly. If the s segment 
        pointer is NULL then a memory error will result, this isn't trapped 
        to speed processing since it is a frequently called function and must
        be as efficient as possible. 
     */
    double UCrv() ; 

    //! Return the actual point
    virtual CS_POINT Point() ; 

    //! If at end of segment move to start of next segment
    CS_CrvPnt &AdjustToStart() ;
} ;


struct CS_CrvPntRec : public CS_CrvPnt
{
    CS_POINT p ; // actual point for the curve point
    CS_POINT Point() { return p; } ; 
} ;  


typedef list<CS_CrvPntRec> CS_CrvPntRecLst ;
typedef list<CS_CrvPntRec>::iterator CS_CrvPntRecLstItr ;

typedef vector<CS_CrvPnt> CS_CrvPntVec ;

class CS_LineSeg ; 
class CS_ArcSeg ; 

// redefinition of the map since it's defined inside the CS_Curve structure
class CS_ChnNode ;
typedef map<TolDbl, CS_ChnNode>  CS_ChnNodeMap ;


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////     INTERSECTION          ////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////


//! Intersection record
/*! 
 \class CS_IREC

    The intersection record pointers are ordered in the same direction 
    as the curve at the time that the curves or segments are intersected
    If a curves direction is reversed after the intersection is performed
    then the segment pointers and u values will no longer be valid with
    respect to the newly reversed curve. For CS_Curve intersections
    where the segments are part of a CS_Curve, the u values are relative 
    to the individual segments and not the overall curve. This is 
    to increase the accuracy of the data maintained wrt the intersections

    If BREVERSED is set pay carefull attention to the secondary curve point
    values. In this case, the cps[0] value will correspond to the 
    cpp[0] value (likewise cpp[1] will correspond to cps[1]). This convention
    may be confusing but this is the way it is. Thus in this case
    cps[0].CurveU() > cps[1].CurveU() will hold. Thus in traversing the
    secondary segment from [0] to [1] you are walking backwards along the 
    secondary segment. This only applies if BREVERSED is true.

    For the cpp[], cps[], ipnt[] parameters the cpp[0] value relates to 
    the cps[0] value and ipnt[0] point. Thus cps[0]->cps[1] could be 
    a line section directed in the reverse direction along the secondary
    curve (if BREVERSED is set). The cpp[0]->cpp[1] curve section will 
    always be oriented in the forward direction relative to the base curve. 
 */
struct CS_IREC
{
public:
    /*! 
     */
    enum {
        POINT      = 0x00000001,    //!< Single point intersection
        OVERLAP    = 0x00000002,    //!< overlapping segments intersection
        TANGENT    = 0x00000004,    //!< tangent point intersection
        PARALLEL   = 0x00000008,    //!< parallel lines, no intersection
        BREVERSED  = 0x00000010,    //!< overlapped secondary curve is reversed w.r.t. base
    } ; 

    //! intersection points on the primary/base curve. 
    CS_CrvPnt cpp[2] ; 

    //! intersection points on the secondary curve. 
    CS_CrvPnt cps[2] ; 
    
    //! Actual intersection points. 
    /*!
        Note these are redundant, since the
        points could be generated from cpp[] alone, but this speeds
        up processing since the actual points have already been 
        calculated.
     */
    CS_POINT ipnt[2] ; 

    //! information about the intersection, see bit flag definitions
    int statinfo ; 

    //! return overall curve u value for primary/base curve
    /*!
        at start (i=0) or end (i=1), any value other than 0 or 1 
        will cause a memory fault to occur
     */
    double UP(int i) {return cpp[i].UCrv() ; } ;

    //! return overall curve u value for primary/base curve
    /*!
        This matches the base curve u value at point ipnt[0]
     */
    double UP0() {return cpp[0].UCrv() ; } ;

    //! return overall curve u value for primary/base curve
    /*!
        This matches the base curve u value at point ipnt[1]
     */
    double UP1() {return cpp[1].UCrv() ; } ;

    //! return overall curve u value for secondary curve
    /*!
        At the start (i=0) or end (i=1), any value other than 0 or 1 
        will cause a memory fault to occur
     */
    double US(int i) {return cpp[i].UCrv() ; } ;
    
    //! return overall curve u value for secondary curve
    /*!
        This matches the secondary curve u value at point ipnt[0]
     */
    double US0() {return cps[0].UCrv() ; } ;

    //! return overall curve u value for secondary curve
    /*!
        This matches the secondary curve u value at point ipnt[1]
     */
    double US1() {return cps[1].UCrv() ; } ;

    void Print(FILE *fp) ; 

} ;


enum {
    //! Trim point is w.r.t. first curve's primary intersection curve first point
    CS_TRIMA_PRI0      = 0x0001,

    //! Trim point is w.r.t. first curve's primary intersection curve second point
    CS_TRIMA_PRI1      = 0x0002,

    //! Trim point is w.r.t. first curve's secondary intersection curve first point
    CS_TRIMA_SEC0      = 0x0004,

    //! Trim point is w.r.t. first curve's secondary intersection curve second point
    CS_TRIMA_SEC1      = 0x0008, 

    //! Trim point is w.r.t. second curve's primary intersection curve first point
    CS_TRIMB_PRI0      = 0x0010,

    //! Trim point is w.r.t. second curve's primary intersection curve second point
    CS_TRIMB_PRI1      = 0x0020,

    //! Trim point is w.r.t. second curve's secondary intersection curve first point
    CS_TRIMB_SEC0      = 0x0040,

    //! Trim point is w.r.t. second curve's secondary intersection curve second point
    CS_TRIMB_SEC1      = 0x0080, 
} ;


/*! 
    The node structure is used to speed up processing so that
    the list doesn't have to call the copy constructor to duplicate
    all the CS_IREC data when adding records to the list. Here
    only the pointer is stored. 
    \todo - look into STL allocators as there's probably a simple
            way to do this without the added wrapper, just too lazy 
            to get into it right now.
 */
struct CS_INODE
{
    //! Pointer to the actual intersection record
    CS_IREC *pir ; 

    CS_INODE() {pir = 0 ; } ;
    CS_INODE(CS_IREC *pirec)
    {
        pir = pirec ; 
    }

    CS_INODE(const CS_INODE &irec)
    {
        pir = irec.pir ; 
    }

    ~CS_INODE() 
    {
        if (pir)
            delete pir ; 
    }; 

    bool operator<(CS_INODE &b)
    {
        return pir->UP0() < b.pir->UP0() ; 
    }

    bool operator>(CS_INODE &b)
    {
        return pir->UP0() > b.pir->UP0() ; 
    }


    int    Status() { return pir->statinfo ; } ; 
    int    Overlap() { return pir->statinfo & CS_IREC::OVERLAP ; } 

    double SegUP(int n) { return pir->cpp[n].u ; } 
    double SegUP0() { return pir->cpp[0].u ; } 
    double SegUP1() { return pir->cpp[1].u ; } 
    double SegUS(int n) { return pir->cps[n].u ; } 
    double SegUS0() { return pir->cps[0].u ; } 
    double SegUS1() { return pir->cps[1].u ; } 
    double UP(int n) { return pir->UP(n) ; }
    double UP0() { return pir->UP0() ; }
    double UP1() { return pir->UP1() ; }
    double US(int n) { return pir->US(n) ; }
    double US0() { return pir->US0() ; }
    double US1() { return pir->US1() ; }
    CS_POINT Point() { return pir->ipnt[0] ; } ; 
    CS_POINT Point(int i) { return pir->ipnt[i] ; } ; 
    CS_POINT Point0() { return pir->ipnt[0] ; } ; 
    CS_POINT Point1() { return pir->ipnt[1] ; } ; 
} ;

///////////////////////////////////////////////////////////////////////
// Intersection sets are simply a linked list of intersection records
///////////////////////////////////////////////////////////////////////

//! Intersection record list definition
typedef list<CS_INODE> CS_IRECList ;

//! Intersection record list interator
typedef list<CS_INODE>::iterator CS_IRECListItr ;

// add src to the end of dst, src is empty on return
int CS_AppendIRECList(CS_IRECList &dst, CS_IRECList &src) ; 

//! Add an intersection record to the intersection list.
/*!
    \param l pointer to the intersection record list to add to
    \param pir the intersection record to add
    
    The CS_IREC pointer pir is simply assigned to the pir pointer in the 
    CS_INODE that is created. This the CS_IRECList pointed to by \a l will
    be responsible for deallocating the pir pointer. Thus pir must be allocated
    with a call similar to:\n
    
    CS_IREC *pir = new CS_IREC ; 
 */
void CS_AddIRECToIRECList(CS_IRECList *l, CS_IREC *pir) ;

//! Add an intersection record to the intersection list.
/*!
    \param l pointer to the intersection record list to add to
    \param pir the intersection record to add
    
    The CS_IREC pointer pir is simply assigned to the pir pointer in the 
    CS_INODE that is created. This the CS_IRECList referenced by \a l will
    be responsible for deallocating the pir pointer. Thus pir must be allocated
    with a call similar to:\n
    
    CS_IREC *pir = new CS_IREC ; 
 */
void CS_AddIRECToIRECList(CS_IRECList &l, CS_IREC *pir) ;

//! Add an intersection record to the intersection list.
/*!
    \param l pointer to the intersection record list to add to
    \param inode the intersection record node to add
    
    The CS_INODE record is appended to the list. The CS_IRECList pointed to 
    by \a l will takes over responsibility for deallocating the pir pointer.
    within the CS_INODE record. Thus make sure that the pir pointer for the 
    CS_INODE inode is set to 0 (NULL) before it goes out of scope so that
    the CS_INODE destructor does not de-allocate pir. Thus you would define
    a block of code similar to:\n

    \verbatim
    CS_IRECList irl ; 
    CS_INODE inode ; 
    inode.pir = new CS_IREC ; 
    // Define pir parameters
    //      ...
    CS_AddIRECToIRECList(irl, inode) ; 
    inode.pir = 0 ; // make sure pir is not de-allocated
        .
        .
        .
    // CS_IRECList destructor de-allocates pir that was allocated above
    \endverbatim

 */
void CS_AddIRECToIRECList(CS_IRECList *l, CS_INODE &inode) ;

//! Add an intersection record to the intersection list.
/*!
    \param l pointer to the intersection record list to add to
    \param inode the intersection record to add
    
    See  CS_AddIRECToIRECList(CS_IRECList *l, CS_INODE &inode)
 */
void CS_AddIRECToIRECList(CS_IRECList &l, CS_INODE &inode) ;

/*!
    \param irlist The interesection set to be sorted
    \param secondary Flag indicating whether to sort by A segments
    or B segments. 
    \return always returns 0

    Orders the list of intersection records by the A segment ustart 
    u values. All parent pointers must be connected up for this to 
    work properly. Also, the overall curve u values must be valid
    for the base curve (all A segment components). The A constraints
    apply to the B data if the secondary flag is set. If the A or B
    curve that was intersected is a single segment, and you want 
    to sort along that single segment, then it's parent pointer must 
    be set to NULL. The parent pointers are referenced to grab the 
    overall curve u values. 

    Thus, make sure to call this routine only for two unique curves
    that were intersected together. If the intersection set contains
    intersections from a bunch of random segments then the sort 
    operation is meaningless.
 */    
int CS_SortIntersectSetByUValue(CS_IRECList &irlist, 
                                int secondary=0) ; 


//! Deletes common duplicate intersection points
/*!
    \param irlist Intersection list to be processed for duplicate records
    \param tol pointer to tolerance value to be used instead of current default
    \return the number of intersection records deleted

    If an intersection occurs at the same basic overall u value
    point relative to the A segments, but involves different
    portions of the A curve, yet the same B curve segment 
    and is at 1.0 or 0.0 on the two A segments, then delete
    one of the A segment intersection records. Note, very similar
    filtering occured with the machining style offset.

    If the base A curve is closed and there are common intersections
    at the u=0 and u=1 points then the u=0 records are deleted leaving
    behind the unique u=1 record.

    IMPORTANT:Call CS_SortIntersectSetByUValue() before calling this function


    <ul>
        <li>This does not work for overlap intersections currently
        <li>Call CS_SortIntersectSetByUValue() before calling this function
        <li>Returns number of intersections deleted
    </ul>

    Note: See CS_DeleteCommonIntersectPoints() also.

 */
int CS_DeleteCommonIntersections(CS_IRECList &irlist, double *tol=0) ;


/*!
    This simply deletes all duplicate intersection points regardless
    of whether they are on different curves or not. The 
    CS_DeleteCommonIntersections() function, makes sure that the intersections
    being deleted are actually not unique, since if two intersections occur
    at the same point but belong to different segments then 
    CS_DeleteCommonIntersections() would retain those points.

    Note: this won't work on overlap intersections where the secondary
    points match up. It only tests for equality against the primary
    points in the set. 
 */
int CS_DeleteCommonIntersectionPoints(CS_IRECList &irlist) ;

//! returns true if the point is one of the intersection points in the list
/*!
 */
int CS_PointInIRECList(CS_POINT &pnt, CS_IRECList &irlist) ;
int CS_PointInIRECList(CS_POINT &pnt, CS_IRECList &irlist, double tol) ;


//! Deletes extra records that are at the same point, leaving only the first one in the list. 
int CS_DeleteCommonCrvPntRecs(CS_CrvPntRecLst &cpl) ;


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////    END INTERSECTION       ////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

class CS_Curve ; 
class CS_ARC ; 
class CS_LINE ; 

//! Pointer to CS_Curve type definition
typedef CS_Curve*   CS_CurvePtr ; 

//! Vector array of CS_Curve* 
typedef vector<CS_CurvePtr> CS_CurveVec ; 

//! Iterator definition to the CS_Curve* vector array CS_CurveVec
typedef vector<CS_CurvePtr>::iterator CS_CurveVecItr ; 


typedef list<CS_CurvePtr> CS_CurveList ; 
typedef list<CS_CurvePtr>::iterator CS_CurveListItr ; 


//! Curve segments within a CS_Curve 
/*!
     Segments can be lines or arcs. New curve segment types to be added in the future 
    are spline, ellipse ...

    This class cannot be used alone even though most of the member functions are 
    not defined as pure virtual. A derived class with CS_Segment as the base 
    must be defined in order to use the new segment type within CS_Curves.
    Almost all the member functions do nothing and are defined to simplify 
    creation of a derived class in that you don't have to defined a function 
    if it isn't used. 
 */
class CS_Segment {
public:
    //! bit field information status about the curve
    int info ;   

    //! pointer to arbitrary user data. This is not used within the library
    void *pUserData ;   

    //! Cross reference point 
    /*!
        Only used for certain operations where synchronization between an original
        base curve and a resultant curve is required. Currently this point is
        only used by offseting, thus if you don't need this information you can
        use the point for some other purpose. If the data you want to track is 
        more complex then use the pUserData pointer. 
     */
    CS_CrvPnt cp ; 

    //! pointer to the parent curve that this segment is a part of
    CS_Curve *pParent ; 

    //! pointer to adjacent segment within the CS_Curve segment list
    CS_SegPtr prev ;
    CS_SegPtr next ; 

    //! The u value of the start of this segment within the overall parent curve
    double uo ; 

    //! the node count of this segment
    /*!
        This is the count of the segment within the CS_Curve. 
        The CS_Curve pStart segment count is zero and the pEnd segment will have a 
        node count value of n-1 where n is the total number of segments within the 
        overall CS_Curve. This value is undefined if the segment is not part 
        of a CS_Curve.
     */
    int cnt ; 

    //! Segment type ID constants
    enum { 
        LINE_TYPE  = 2,
        ARC_TYPE   = 3,
    } ; 

    virtual int IsARC() { return 0 ; } ; 
    virtual int IsLINE() { return 0 ; } ; 

    CS_Segment() ;
    CS_Segment(CS_SegPtr pseg) ; 

    virtual ~CS_Segment() ; 
    
    //! Make copy of segment, must be freed by the caller with delete
    /*! Makes an exact copy of the segment and must be freed by the caller with
        the delete function.
        Note, a member by member copy is performed, thus the prev, next and parent 
        pointers will all be identical in the new copied segment and it is 
        up to the caller to adjust these as required.
     */
    virtual CS_SegPtr Copy() ; 

    //! Copy portion of segment
    /*!
        \param us the u value to copy from
        \param ue the u value to copy to

        Copies the portion of the segment defined by the range us and ue. The 
        u values are relative to the segment itself and not the overall curve
        that the segment may be part of. New memory is allocated within the 
        copy and must be freed by the calling routine with delete. Note, a 
        member by member copy is performed, thus the prev, next and parent 
        pointers will all be identical in the newly copied segment and it is 
        up to the caller to adjust these as required.
     */
    virtual CS_SegPtr Copy(double us, double ue) ; 

    //! returns the segment type ID number
    virtual inline int SegmentType() ; 

    //! reverses the segment direction
    virtual void Reverse(void) ; 

    //! Returns point on segment a specified u value
    virtual CS_POINT UPoint(double u) ; 

    //! Move the segment as defined by the vector v
    virtual void Move(CS_VECTOR &v) ; // move in XYZ space 

    //! Sets the z coordinate of points in all segments to \a z
    virtual void SetZ(double z) ; 

    //! Transform the segment in 3D space. 
    /*!
        Performs a full 3D transformation of the segment. The last column
        in the transform matrix defines a translation. Transformation
        matrix can be set up through the CS_MTX4 class.
     */
    virtual void Transform(double p[12]) ; 

    //! Returns true if the segments are similar
    /*!
        \param psb pointer to other segment to compare against
        \return Returns true if the segments are similar otherwise returns false.

        Compares the two segments and if their types and lengths match
        then true is returned. The segments can be located differently anywhere
        in 3D space, so long as they can be transformed to overlap then true 
        will be returned. The format of the \a p[12] array is as follows:

     */
    virtual int Similar(CS_SegPtr psb) ; // true if same type and length

    //! Returns which side of the segment the point is on
    /*!
        \param pnt the point to test
        \return Returns CS_LEFTSIDE, CS_RIGHTSIDE, or CS_COLLINEAR depending on where the
        points lies based on the direction of the segment looking down on it 
        from the positive Z side of the XY plane.
     */
    virtual int PointSide(CS_POINT &pnt) ; 

    //! Returns the mid point of the segment 
    virtual CS_POINT MidPoint(void) ; 

    //! Returns the start point of the segment 
    virtual CS_POINT StartPoint(void) ; 

    //! Returns the end point of the segment 
    virtual CS_POINT EndPoint(void) ; 

    //! Returns the centroid of the segment in 3D space
    virtual CS_POINT Centroid(void) ; 

    //! Returns the centroid of the segment in 2D space
    virtual CS_POINT Centroid2D(void) ; 

    //! Returns the arc length of the segment 
    virtual double ArcLength(void) ; 

    //! apply the scaling transform to the segment
    virtual void MTX3Mult(CS_MTX3 &mx) ; // apply transform defined by matrix

    //! scale factor s is equivalent to MTX3Mult with s as diagonals of matrix
    virtual void Scale(double s) ; 

    //! arc length projected on XY-plane
    virtual double XY_ArcLength(void) ; 
    
    //! tangent vector at u along segment, u range = [0,1]
    virtual CS_VECTOR UTangent(double u) ; 

    //! offset segment,-ve=left, +ve=right based on direction of segment
    virtual int Offset(double delta) ; 

    //! returns the bounding rectangle, this can be infinitely thin for lines
    virtual CS_RECT BoundingRect() ; 


    //! Generic intersection definition extension
    /*!
      \param pseg pointer to segment that is intersected with this segment.
      \param pirlist pointer to intersection record list 

      Any new intersections generated are added to the CS_IRECList pointed
      to by pirlist. pirlist cannot be NULL on entry, it must point to a valid 
      CS_IRECList variable.
     */
    virtual int Intersect2D(CS_SegPtr pseg, CS_IRECList *pirlist) = 0 ;

    //! Trim the start of the curve away leaving the section [u,1]
    virtual void TrimStart(double u) ; 

    //! Trim the end of the curve away leaving the section [0,u]
    virtual void TrimEnd(double u) ; 

    //! Trim both ends of the curve off leaving section [u1,u2]
    /*!
        If u1=0 then the behaviour is identical to TrimEnd. Similarily
        if u2=1 then the behaviour is identical to TrimStart. u1 < u2
        must be true on entry.
     */
    virtual void Trim(double u1, double u2) ; // keep section [u1,u2]

    //! Change the start point of the segment to pnt
    virtual int AdjustStartPoint(CS_POINT &pnt) ; 

    //! Change the end point of the segment to pnt
    virtual int AdjustEndPoint(CS_POINT &pnt) ; 
    
    //! Return true if point is actually on the segment within tolerance limits
    /*!
     \param p the point to be tested
     \param puval used to store u value of point on segment nearest to p
     \param pnpnt used to store point on segment nearest to p
     \param toldist pointer to a tolerance value which would override the current default
     \return true if point p is on the segment, otherwise returns false

     This routine calculates the point on the segment that is closest to 
     the input point p. If the point is actually on the segment then this
     nearest point will equal point p. If puval is not NULL, then the 
     u value of the nearest point on the segment will be saved in *puval.
     Likewise if pnpnt is not NULL, the nearest point on the segment will
     be saved in *pnpnt. True is returned only if the nearest point 
     calculated and the input point p match within the current system 
     tolerance value. The value returned in puval will always be in the 
     range [0,1]. Thus the returned nearest point will never be beyond
     the actual endpoints of the segment. 
     */
    virtual int PointOnSegment(CS_POINT &p, 
                               double *puval=NULL, 
                               CS_POINT *pnpnt=NULL, 
                               double *toldist=NULL) ;

    //! Return true if point is actually on the segment within tolerance limits
    /*!
     \param p the point to be tested
     \param puval used to store u value of point on segment nearest to p
     \param pnpnt used to store point on segment nearest to p
     \param toldist pointer to a tolerance value which would override the current default
     \return true if point p is on the segment, otherwise returns false

     This works exactly the same as PointOnSegment() except that the 
     Z component of the curve and the point is ignored when testing. 
     Thus all geometry is effectively projected onto the XY plane along
     the Z axis. See PointOnSegment() for further details. 
     */
    virtual int PointOnSegment2D(CS_POINT &p, 
                                 double *puval=NULL, 
                                 CS_POINT *pnpnt=NULL, 
                                 double *toldist=NULL) ;


    //! debug dump to file fp using fprintf, fp=0 dumps to stdout
    virtual void Print(FILE *fp=0, int prec=12) ; // print data to stdout

    //! Print the x,y coords of each end point for the segment
    virtual void PrintPoints2D(FILE *fp=0, int prec=12) ;

} ;


class CS_CIRCLE ; 

//! Defines an infinite 3D line
/*!
    Infinite lines are stored in exactly the same way as line segments. 
    The only real difference between CS_LINE and CS_LineSeg is that the 
    intersection and other routines treat a CS_LINE as infinite whereas
    the CS_LineSeg has its limits defined by its end points. Thus when 
    a CS_LINE is intersected with another CS_LINE, if the lines are not
    parallel then a single intersection point will be found (for 2D
    intersections).
 */
class CS_LINE {
public:
    //! start point of the line segment
    CS_POINT sp ; 

    //! end point of the line segment
    CS_POINT ep ; 

    CS_LINE() {}
    CS_LINE(CS_POINT &p1, CS_POINT &p2) ;
    CS_LINE(CS_LineSeg &lseg) ; 

    // CS_LINE(double m, double b) ; 

    //! get the line parameters m,b for the equation y=mx+b
    /*!
        \param m the slope of the line
        \param b the y intercept for the line
        \return -1 if line is vertical, else 0

        Extracts the line parameters m and b for the equation 
        y = mx + b. If the line is vertical within the system 
        tolerance limits, then m and b are both set to zero,
        since no value for the slope parameter m can be calculated. 
     */
    int LineParameters2D(double &m, double &b) ; 

    //! Perform 2D intersection with another line
    /*!
        \param ln the other line to intersect with
        \param ipnt the resultant intersection point if any. 
        \return Returns the number of intersections. If 
        no intersection is found then returns 0 and ipnt is unchanged. 
        If a single intersect point is found, then returns 1, and ipnt is 
        set to the point of intersection. If the lines
        are collinear then the number of intersects returned is 2, and 
        ipnt is set to the start point of *this.
     */
    int Intersect2D(CS_LINE &ln, CS_POINT &ipnt) ;

    //! Intersect 3D lines, t1 and t2 are parameteric intersect points
    /*!
        \param ln 3D line to intersect with
        \param u1 parametric intersection point on *this line
        \param u2 parametric intersection point on ln line
        \return 0=no solution, 1=intersect at point, 2=collinear

        To create the actual point of intersection use the UPoint
        function with the respective line. 
     */
    int Intersect(CS_LINE &ln, double &u1, double &u2) ;

    //! Perform 2D intersection of line with a circle. 
    /*!
        \param cir circle to intersect the *this line with
        \param p1 Resultant intersection point 1
        \param p2 Resultant intersection point 2
        \return The number of intersections found.

        If the line is tangent to the circle, then there is only a single 
        intersection point and this is returned in \a p1, \a p2 is 
        left unchanged in this case, and the function returns 1. If the line
        is not tangent to the circle and goes through the circle then two 
        intersections are returned, the first in \a p1 and the second in \a p2
        and the function returns 2. When no intersections are found, \a p1 and 
        \a p2 are left unchanged, and the function returns 0. 
     */
    int Intersect2D(CS_CIRCLE &cir, CS_POINT &p1, CS_POINT &p2) ;

    //! Returns nearest point on line to the input point \a pnt
    CS_POINT NearestPoint(CS_POINT &pnt) ; 

    //! Returns CS_LEFTSIDE, CS_RIGHTSIDE, or CS_COLLINEAR depending on where the
    //! points lies based on the direction of the segment looking down on it 
    //! from the positive Z side of the XY plane.
    int PointSide(CS_POINT &pnt) ; 

    //! Returns true if the two lines are collinear
    int Collinear(CS_LINE &ln) ; 

    //! Ignores the Z component in the collinear testing
    int Collinear2D(CS_LINE &ln) ; 

    //! Returns true if the two lines are collinear
    int Collinear(CS_LineSeg &lseg) ; 

    //! Ignores the Z component in the collinear testing
    int Collinear2D(CS_LineSeg &lseg) ; 

    //! Returns the slope of the line
    /*!
        If the line is vertical then the slope returned is either +/-HUGE_VAL
        depending on the vector that is defined with \a sp and \a ep variables.
        If the sp->ep points vertically upwards then +HUGE_VAL is returned, 
        conversely if it points vertically downwards then -HUGE_VAL is returned. 
     */
    double Slope() ; 

    //! Swaps the \a sp and \a ep values
    void Reverse() ; 


    //! Returns point on the line at parametric distance u 
    /*!
        \param u parametric distance along line for point
        \return the point at the u value specified

        Even though this is an infinite line, since there is a 
        start point and end point defined internally, a parametric point
        can be calculated. u [0,1] will return a point in between the start
        and end points. U values outside the range [0,1] are valid in the 
        case of inifinite lines and will work as expected returning points
        outside of the segment section in between the start and end points.
     */
    CS_POINT UPoint(double u) ; 

    //! calculates the u parameter on the line closest to point \a p
    /*!
        \param p the point to calculate nearest point to. 
        \param puval pointer variable that accepts the u value of the closest point 
        \param pnpnt pointer to CS_POINT that accepts the closest point on segment
        \return 1 if the test point \a p is on the segment, otherwise returns 0

        Returns true if point is on the infinite line defined by the 
        segment end points. The parameter returned is in the range \f$(-\infty,+\infty)\f$
        and pnpnt is the nearest point on the infinite line to p
     */ 
    int UParmClosestToPoint(CS_POINT p, double *puval=NULL, CS_POINT *pnpnt=NULL) ;

    //! Return true if point is actually on the line within tolerance limits
    /*!
     \param p the point to be tested
     \param puval used to store u value of point on line nearest to p
     \param pnpnt used to store point on line nearest to p
     \return true if point p is on the line, otherwise returns false

     This routine calculates the point on the line that is closest to 
     the input point p. If the point is actually on the line then this
     nearest point will equal point p. If puval is not NULL, then the 
     u value of the nearest point on the line will be saved in *puval.
     Likewise if pnpnt is not NULL, the nearest point on the line will
     be saved in *pnpnt. True is returned only if the nearest point 
     calculated and the input point p match within the current system 
     tolerance value. The value returned in puval will can be in the range
     (-inf, inf). Since a line is stored by defining it's endpoints, a 
     u value of 0 maps to the startpoint, and u=1 the endpoint. 
     \sa CS_LINE::UParmClosestToPoint
     */
    int PointOnLine(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL) ;


    void Move(CS_VECTOR &v) ; // move in XYZ space 

    //! Sets the z coordinate of points in all segments to \a z
    void SetZ(double z) ; 

    void Transform(double p[12]) ; // full transform

    //! Returns the mid-point of the line 
    CS_POINT MidPoint() ;

    //! Returns the start point of the line
    CS_POINT StartPoint(void) ;

    //! Returns the end point of the line
    CS_POINT EndPoint(void) ;

    //! Returns the length of the line
    double ArcLength(void) ; 

    //! Returns the length of the line projected onto the XY plane
    double XY_ArcLength(void) ;

    //! Returns the centroid, same as the mid point of the line
    CS_POINT Centroid(void) ; 

    //! Returns the centroid, same as the mid point of the line
    //! projected onto the XY plane. 
    CS_POINT Centroid2D(void) ; 

    //! Multiplies the two end points by the scaling factor
    /*!
        \param s scaling factor
        
        The sp and ep member variables are multiplied by the 
        scaling factor s. This can have the effect of shifting
        the line in space, despite being an infinite line definition.
        It behaves indentically to the CS_LineSeg::Scale() function.

        See Also: the definition of CS_POINT::operator*()
     */
    void Scale(double s) ; 

    //! Transform line the end points
    /*!
        \param mx 3D transformation matrix

        Transforms the line end points by the transformation matrix
        mx. See CS_MTX3 for further details. 
     */
    void MTX3Mult(CS_MTX3 &mx) ; // apply transform defined by matrix

    //! Return tangent vector at parameteric u point
    /*!
        \param u parametric u point where tangent is calculated
        \return unit vector tangent to the line segment

        The u point is ignored in this calculation since the tangent
        of a line segment anywhere on the line. This function call
        is here to maintain consistency with the general 
        \latexonly \mbox{CS\_Segment::UTangent()} \endlatexonly
        base member. 
     */
    CS_VECTOR UTangent(double u) ; // unit tangent vector at u[0,1]

    //! offset the segment by delta
    /*!
        \param delta the magnitude of the offset
        \return always returns 0
        
        A positive offset delta causes the line to be shifted to the 
        right whereas a negative delta causes the line to be shifted 
        to the left. The direction is based on the vector direction
        returned by RightPerp() for the line tangent vector. If the
        line has z components then the offset direction will also have 
        a z component which may generate an undesired result. 
     */
    int Offset(double delta) ; 

    //! Trim off the start of the curve
    /*!
        \param u parameteric value to 'trim' up to

        The line will be effectively shortened by changing the 
        current start point to the point defined by UPoint(u).
        Because this is an infinite line definition, all that 
        really happens is that the internal definition point is
        shifted. 
     */
    void TrimStart(double u) ;

    //! Trim off the end of the curve
    /*!
        \param u parameteric value to 'trim' from

        The line will be effectively shortened by changing the 
        current end point to the point defined by UPoint(u).
        Because this is an infinite line definition, all that 
        really happens is that the internal definition point is
        shifted. 
     */
    void TrimEnd(double u) ; // trim off the end of the curve seg

    //! Trim off the ends of the curve
    /*!
        \param u1 parameteric value to 'trim' to
        \param u2 parameteric value to 'trim' from

        The line will be effectively shortened by changing the 
        current end points to the points defined by UPoint(u).
        Because this is an infinite line definition, all that 
        really happens is that the internal definition points are
        shifted. 
     */
    void Trim(double u1, double u2) ; // trim out section of curve

    //! Sets sp to pnt
    int AdjustStartPoint(CS_POINT &pnt) ; 

    //! Sets ep to pnt
    int AdjustEndPoint(CS_POINT &pnt) ; 

    //! Returns the bounding rectangle of the two interal definition points
    /*!
        The sp and ep member variables are used to set the bounding rectangle.
        Even though the line is infinite, the internal representation 
        points are used to define the bounding rectangle. 
     */
    CS_RECT BoundingRect() ; // returns the bounding rectangle
} ;



//! Defines circle in XY plane 
/*!
    This is a basic circle definition in the XY plane. The center
    of the circle is defined with a 3D point so it is possible to 
    define an elevation for the circle, but internal routines that 
    use circles ignore the Z component of the center. 
 */
class CS_CIRCLE {
public:
    //! center of the circle
    CS_POINT ctr ;     

    //! radius of the circle
    double rad ; 


    CS_CIRCLE() ; 
    CS_CIRCLE(CS_POINT &p, double radius) ; 

    //! create circle from arc parameters, if defined the arc 3D transform is discarded 
    CS_CIRCLE(CS_ArcSeg &aseg) ; 

    //! Returns bounding box for the circle
    CS_RECT BoundingRect() ; 


    //! returns true if the point is inside the circle
    /*!
        \param p point to test
        \return true if the test point is inside the circle, otherwise false.

        The point \a p has to actually be inside the circle by at least the 
        current system tolerance. Returns true only if the distance 
        from the center to the test point is less than the radius minus the 
        current system tolerance \f$\epsilon\f$. Or stated differently:\n
        \latexonly \begin{center} $\|\vec{cp}\| < r - \epsilon $ \end{center} \endlatexonly \n
        where r is the radius. and \f$\vec{cp}\f$ is the vector from the center
        to the test point p.
     */
    int CS_CIRCLE::Inside(CS_POINT &p) ;

    //! Tests if a point is inside of or on the edge of a circle
    /*!
        \param p the test point
        \return true if the test point is on the edge or anywhere inside the circle

        Returns true only if the distance 
        from the center to the test point is less than the radius plus the 
        current system tolerance \f$\epsilon\f$. Or stated differently:\n
        \latexonly \begin{center} $\|\vec{cp}\| < r + \epsilon $ \end{center} \endlatexonly \n
        where r is the radius. and \f$\vec{cp}\f$ is the vector from the center
        to the test point p.
    
     */
    int CS_CIRCLE::InsideOrOn(CS_POINT &p) ;

    //! return true if the circle \a c is inside the *this circle
    /*!
        \param c the circle to test
        \return true if the circle \a c is completely inside the 
        base circle, false otherwise

        If the vector from the center of the base cicle to the circle \a c 
        is given by \f$\mathbf{v}\f$, the current system tolerance by
        \f$\epsilon\f$, the radius of circle \a c by \f$c_{r}\f$ and the
        radius of the base circle by \f$r\f$, then this function returns
        true if the following condition holds:\n
        \latexonly 
            \begin{center} 
                \[\|\mathbf{v}\| + c_{r} < r - \epsilon \]
            \end{center}
        \endlatexonly

        \image latex circ-inside-circ.eps "Testing circle inside another circle" width=120mm
                
     */
    int CS_CIRCLE::Inside(CS_CIRCLE &c) ;

    //! return true if the circle \a c is inside the *this circle
    /*!
        \param l the line segment to test
        \return true if the line \a l is completely inside the 
        base circle, false otherwise

        If the two endpoints of the line are inside the circle then it returns
        true otherwise it returns false. 
     */
    int CS_CIRCLE::Inside(CS_LINE &l) ;

    //! return true if the circle \a c is inside the *this circle
    /*!
        \param a the circle to test
        \return true if the arc \a a is completely inside the 
        base circle, false otherwise

        If the arc intersects the circle anywhere or the arc is outside 
        of the circle then it returns false, otherwise it returns true
     */
    int CS_CIRCLE::Inside(CS_ARC &a) ;


    //! return true if the circle \a c is inside or on the *this circle
    /*!
        \param c the circle to test
        \return true if the circle \a c is inside or on the 
            base circle, false otherwise

        If the vector from the center of the base cicle to the circle \a c 
        is given by \f$\mathbf{v}\f$, the current system tolerance by
        \f$\epsilon\f$, the radius of circle \a c by \f$c_{r}\f$ and the
        radius of the base circle by \f$r\f$, then this function returns
        true if the following condition holds:\n
        \latexonly 
            \begin{center} 
                \[\|\mathbf{v}\| + c_{r} <= r - \epsilon \]
            \end{center}
        \endlatexonly

        \image latex circ-inside-circ.eps "Testing circle inside another circle" width=120mm
                
     */
    int CS_CIRCLE::InsideOrOn(CS_CIRCLE &c) ;


    //! Intersect two circles together
    /*!
        \param cir the second circle to intersect against
        \param p1 the first intersection point result
        \param p2 the second intersection point result
        \return the number of intersections generated.

        If the circles do not intersect then 0 is returned and neither p1 or p2
        is updated. Zero intersections can occur if one circle is either 
        completely outside the other circle or completely inside the other
        circle. If the circles are tangent to one another, then 1 is 
        returned and p1 is set the contact point of the two circles, 
        p2 is unchanged. If the two circles are coincident (that have the
        same center point and radius within the system tolerance) then
        neither p1 or p2 is changed, and the number of intersections 
        returned is 3 (indicating an infinite number of intersections).
     */
    int Intersect2D(CS_CIRCLE &cir, CS_POINT &p1, CS_POINT &p2) ;

    //! Intersect circle with the line
    /*!
        \param ln the line to intesect with
        \param p1 the first intersection point result
        \param p2 the second intersection point result
        \return the number of intersection points found

        If there are no intersections between the line and circle then 
        0 is returned, and p1 and p2 are left unchanged. If the line is
        tangent to the circle then 1 is returned and p1 is set to the 
        intersection point. If the line crosses the circle, then 
        2 is returned, with p1 and p2 being set to the two intersection 
        points. There is no particular ordering of the p1 and p2 points.
     */
    int Intersect2D(CS_LINE &ln, CS_POINT &p1, CS_POINT &p2) ;
    CS_POINT NearestPoint(CS_POINT &pnt) ; 
    double Area() ; 
} ;


//! Arc definition in 3D
/*!
    \class CS_ARC

    \image latex arc_ccw2.eps "CS_ARC Representation" width=80mm

    All arcs are defined parallel to the XY plane. As defined internally
    the center point is in absolute space. The z component simply shifts
    the arc up or down in Z but still parallel to the XY plane. If the 
    arc is to be oriented in a different plane then a higher order object 
    is required to define how the arc will be stored. A new class could
    be derived such as CS_ArcSeg3D which includes a plane unit normal vector
    to its parameters which would define the plane the arc is in, as well
    as an X (and possibly Y) vector within that plane in order to give 
    the start angle and sweep angle meaning. 
    The sweep angle determines the arc direction, CW=negative sweep, 
    CCW=positive sweep. The arc end angle can be determined by 
    endangle = startangle + sweep. All angles are stored in radians.
    The offset function is simply within the plane of the arc. A positive
    offset offsets the arc to the right based on the start point tangent
    vector, taking into account the defined direction for the arc.
    A negative offset is to the left. If the resultant offset is towards 
    the center of the arc and is >= to the radius of the arc then the 
    resultant arc gets it's direction flipped during the offset process,
    otherwise the direction remains the same.

    For 3D arcs the variable pxfrm points to a matrix which defines the coordinate
    system transformation for the plane that the arc lies in. In this case, 
    ctr defines the center point on of the arc on the transformed plane 
    which fully defines the coordinate system for the arc. 
 */
class CS_ARC
{
public:
    
    //! radius of arc
    double rad ;    

    //! center point of the arc
    CS_POINT ctr ;  

    //! sweep angle of the arc swp>0 is CCW, and swp<0 is CW
    double swp ;    

    //! start angle in radians of the arc 
    double sa ;     

    //! defines the transformation of the arc in arbitrary 3D space. 
    CS_MTX3 *pxfrm ; 

    CS_ARC()
    {
        rad = 0.0 ;
        swp = 0 ;
        ctr.x = 0.0 ;
        ctr.y = 0.0 ;
        ctr.z = 0.0 ;
        sa = 0.0 ;
        pxfrm = 0 ; 
    }

    CS_ARC(const CS_ARC &base)
    {
        rad = base.rad ; 
        swp = base.swp ;
        ctr = base.ctr ;
        sa = base.sa ;
        if (base.pxfrm)
        {
            pxfrm = new CS_MTX3 ; 
            *pxfrm = *(base.pxfrm) ; 
        }
        else
            pxfrm = 0 ; 
    }

    CS_ARC(CS_POINT ctrpnt, double startang, double sweep, double radius) 
        : ctr(ctrpnt), sa(startang), swp(sweep), rad(radius)
    {
        pxfrm = 0 ; 
    } ;

    //! Destructor, de-allocates transformation matrix if defined
    ~CS_ARC()
    {
        if (pxfrm)
            delete pxfrm ; 
    }

    //! Set arc parameters based on start \a sp and end \a ep point
    /*!
        \param sp the start point of the resultant arc
        \param ep the end point of the resultant modified arc
        \param direction is either CCW or CW
        
        Set start angle, sweep, and rad based on the start point and endpoint
        parameters passed in, as well as the direction. Requires that
        the center point be defined on entry, all other parameters are set.
     */
    void SetSPEP(CS_POINT &sp, CS_POINT &ep, int direction) ; 

    //! Set arc parameters based on start \a sp and end \a ep point
    /*!
        \param ctr new center point for the arc
        \param sp the start point of the resultant arc
        \param ep the end point of the resultant modified arc
        \param direction is either CCW or CW

        Set start angle, sweep and rad based on the start, end 
        and center point, as well as the direction. This completely
        resets all values for the arc and nothing need be defined
        on entry.
     */
    void SetCtrSPEP(CS_POINT &ctr, CS_POINT &sp, CS_POINT &ep, int direction) ; 

    //! Reverse the direction of the arc, sa=sa+swp, swp=-swp
    void Reverse()
    {
        sa = mod2PI(sa + swp) ;
        swp = -swp ;
    }

    //! Force the arc swp parameter negative
    /*!
        The resultant arc is identical except that the endpoints may 
        get swapped if the direction is reversed
     */   
    void SetCW() ; 

    //! Force the arc swp parameter positive
    /*!
        The resultant arc is identical except that the endpoints may 
        get swapped if the direction is reversed
     */   
    void SetCCW() ; 

    //! Return point on the arc at parameteric distance u where \f$u\in[0,1]\f$
    /*!
        Returns point on the arc at parameteric distance u 
        where \f$u\in[0,1]\f$ must be true on entry. If u is out of range then 
        a point that is not actually on the arc (or an erroneous point) will
        be returned since no testing is done on the u value on entry. 
     */
    CS_POINT UPoint(double u) ; 

    //! return tangent vector to arc at parameteric distance u where \f$u\in[0,1]\f$
    CS_VECTOR UTangent(double u) ;

    //! Returns sweep and from the arc start angle at the given u
    /*!
        \param u parametric u value [0,1] along the arc
        \return the sweep in radians from the arc start to the given u
   
        Refering to figure in CS_ARC::AngleU() if the u value 0.75 is input then this 
        function would return an angle of \f$\pi/4\f$ (45<SUP>o</SUP> in radians).
        No testing is done to make sure the u domain is [0,1]. Numbers outside
        of the [0,1] input domain will result in angles outside of the sweep 
        of the arc. 
        
        The returned value will always be in the range \f$[0,2\pi]\f$
     */
    double UAngle(double u) ;  

    //! Returns parameteric u value matching the input sweep angle 
    /*!
        \param phi sweep angle along the arc in radians
        \return the u value along the arc that matches the angle phi

        \image latex AngleU.eps "AngleU and UAngle operation" width=80mm
        
        In the above diagram if the angle \f$\pi/4\f$ (45<SUP>o</SUP> in radians)
        is input for phi then \a AngleU would return 0.75. If an angle
        larger than 60<SUP>o</SUP> is input then u values greater than 
        1.0 will result, no testing is done to make sure that 
        the input angle is contained within the sweep of the arc. 
     */
    double AngleU(double phi) ; 


    //! Return true if point is actually on the arc within tolerance limits
    /*!
     \param p the point to be tested
     \param puval used to store u value of point on arc nearest to p
     \param pnpnt used to store point on arc nearest to p
     \param toldist overrides the default system compare tolerance
     \return true if point p is on the arc, otherwise returns false

     This routine calculates the point on the arc that is closest to 
     the input point p. If the point is actually on the arc then this
     nearest point will equal point p. If puval is not NULL, then the 
     u value of the nearest point on the arc will be saved in *puval.
     Likewise if pnpnt is not NULL, the nearest point on the arc will
     be saved in *pnpnt. True is returned only if the nearest point 
     calculated and the input point p match within the current system 
     tolerance value. The value returned in puval will always be in the 
     range [0,1]. Thus the returned nearest point will never be beyond
     the actual endpoints of the arc. 

     \remark This will only work for arcs parallel to the XY plane 
     currently.
     */
    int PointOnArc(CS_POINT &p, double *puval, CS_POINT *pnpnt, const double &toldist) ;
    int PointOnArc2D(CS_POINT &p, double *puval, CS_POINT *pnpnt, const double &toldist) ;

    //! More efficient code since doesn't test if needs to use system tolerance or not
    int PointOnArc(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL) ;
    int PointOnArc2D(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL) ;

    //! Returns CS_LEFTSIDE, CS_RIGHTSIDE, or CS_COLLINEAR 
    /*! 
        \param pnt - the test point 
        \return CS_LEFTSIDE, CS_RIGHTSIDE, or CS_COLLINEAR

        \image latex pointside-arc1.eps "Example where swp < 180 degrees" width=100mm

        When deciding which side of an arc a point is on, if the line connecting
        the center of the arc to the point does not intersect the arc, then 
        tangent lines are extend from the arc endpoints to decide which side 
        of the arc the point lies on. When the arc sweeps out an angle of greater
        than 180 degrees, then the intersection point of the two tangent lines
        defines the furthest point in a region that makes up the 'interior' side
        of the arc. This interior region will be on the left for CCW arcs and 
        on the right for CW arcs. The diagram is an example of the CCW case. 

        \image latex pointside-arc2.eps "Example of swp > 180 degrees" width=100mm
     */
    int PointSide(CS_POINT &pnt) ; 

    //! move in XYZ space, does ctr=ctr+v 
    void Move(CS_VECTOR &v) ; 

    //! Sets ctr.z = 0 
    void SetZ(double z) ; 

    //! Scales the arc by setting rad=rad * s, and ctr=ctr * s
    void Scale(double s) ; 

    //! Applies full 3D spatial transformation to the arc.  
    void Transform(double p[12]) ; // full transform

    //! returns the mid point of the arc, equivalent to UPoint(0.5)
    CS_POINT MidPoint(void) ; 

    //! returns the start point of the arc, equivalent to UPoint(0.0) 
    CS_POINT StartPoint(void) ; 

    //! returns the end point of the arc, equivalent to UPoint(1.0)
    CS_POINT EndPoint(void) ; 

    // length of the arc = r * fabs(swp)
    double ArcLength(void) ; 

    //! Transform the arc as defined by the matrix
    void MTX3Mult(CS_MTX3 &mx) ; 

    //! returns curve length projected on XY plane
    double XY_ArcLength(void) ; 

    //! simply calls Centroid2D 
    //! \todo enhance to 3D
    CS_POINT Centroid(void) ;  

    //! returns the line centroid point for the arc segment
    /*!
        \return the line integral centroid for the arc.

        \image latex centroid-arc.eps "Sample of Arc Centroid Point" width=80mm
        
        The centroid of an arc is given by the formula:\n
        \latexonly
            \begin{center}
            $ \overline{r}=$ \scalebox{1.5}{$\frac{r \sin \alpha}{\alpha}$}
            \end{center}
        \endlatexonly 
        \n
        where \f$ \alpha \f$ is half the sweep angle of the arc. 
     */
    CS_POINT Centroid2D(void) ; 

    //! offset segment,-ve=left, +ve=right
    int Offset(double delta) ; 

    //! returns CW if swp<0, and CCW if swp>0 
    int ArcDir() ; 
    
    //! Returns true if (sa <= phi <= ea), deals with arcs that cross 0 degrees
    int AngleOnSweep(double phi) ;       

    //! Returns true if (sa < phi < ea), deals with arcs that cross 0 degrees
    //! doesn't use tolerance in comparison    
    int AngleOnSweepX(double phi) ;      

    //! Returns true if (sa < phi < ea), deals with arcs that cross 0 degrees
    int AngleInSweep(double phi) ; 

    //! return the chordheight for the arc
    double ChordHeight() ;          

    //! trim off the start of the curve
    void TrimStart(double u) ; 

    //! trim off the end of the curve seg
    void TrimEnd(double u) ; 

    // trim out section of curve
    void Trim(double u1, double u2) ; 

    //! adjust the arc parameters to match the given start point
    /*! 
        \param pnt - the start point of the arc to update
        \return 0 if no errors occur
        
        This is intended to be used to make very minor corrections and 
        adjustments to the arc. The current mid and end points of the arc
        are stored, then a three point arc is created which goes through
        the given start point and the old mid and end points. 
     */
    int AdjustStartPoint(CS_POINT &pnt) ;

    //! adjust the arc parameters to match the given end point
    /*! 
        \param pnt - the end point of the arc to update
        \return 0 if no errors occur
        
        This is intended to be used to make very minor corrections and 
        adjustments to the arc. The current start and mid points of the arc
        are stored, then a three point arc is created which goes through
        the given start point and the old start and mid points. 
     */
    int AdjustEndPoint(CS_POINT &pnt) ;

    //! Set arc from start point, point inside endpoints, and the endpoint
    int Arc3Points(CS_POINT &startpnt, CS_POINT &intpnt, CS_POINT &endpnt) ;

    //! return the 2D bounding rectangle for the arc
    CS_RECT BoundingRect() ;
} ;

//! Arc segment
/*!
    An arc segment is derived from the \a CS_Segment and \a CS_ARC classes. This is 
    the arc definition used within \a CS_Curve's. See the description of CS_ARC
    for more details of how an arc is defined. 
 */
class CS_ArcSeg : public CS_Segment, public CS_ARC {
public:
    CS_ArcSeg() {} 
    CS_ArcSeg(CS_ArcSeg &arc) : CS_Segment(&arc)  
    {
        rad  = arc.rad ; 
        ctr  = arc.ctr ; 
        sa   = arc.sa ; 
        swp  = arc.swp ; 
        if (arc.pxfrm)
        {
            pxfrm = new CS_MTX3 ; 
            *pxfrm = *(arc.pxfrm) ; 
        }
    }

    CS_ArcSeg(CS_ARC &arc)
    {
        rad  = arc.rad ; 
        ctr  = arc.ctr ; 
        sa   = arc.sa ; 
        swp  = arc.swp ; 
        if (arc.pxfrm)
        {
            pxfrm = new CS_MTX3 ; 
            *pxfrm = *(arc.pxfrm) ; 
        }
    }

    CS_ArcSeg(CS_ARC *arc)
    {
        rad  = arc->rad ; 
        ctr  = arc->ctr ; 
        sa   = arc->sa ; 
        swp  = arc->swp ; 
        if (arc->pxfrm)
        {
            pxfrm = new CS_MTX3 ; 
            *pxfrm = *(arc->pxfrm) ; 
        }
    }

    CS_ArcSeg(CS_ArcSeg *pas) : CS_Segment(pas) 
    {
        rad  = pas->rad ; 
        ctr  = pas->ctr ; 
        sa   = pas->sa ; 
        swp  = pas->swp ; 
        if (pas->pxfrm)
        {
            pxfrm = new CS_MTX3 ; 
            *pxfrm = *(pas->pxfrm) ; 
        }
    }

    CS_ArcSeg(CS_POINT ctrpnt, double startang, double sweep, double radius) :
            CS_ARC(ctrpnt, startang, sweep, radius)
    {
    } ;


    //! Returns CS_Segment::ARC_TYPE
    int SegmentType() { return ARC_TYPE ; }

    int IsARC() { return 1 ; } ; 

    //! Returns a newly allocated copied segment 
    /*!
        All the parameters from the original segment are copied to the 
        newly allocated segment except for \a prev and \a next. A new
        transformation matrix is also created if there is one defined
        in the base arc. 
        
        The returned pointer must be deallocated by the user with delete.
     */
    CS_SegPtr Copy() ; 

    //! Returns a newly allocated copied segment section from us to ue
    /*!
        \param us the starting u value relative to the segment to copy from
        \param ue the ending u value relative to the segment to copy to
        
        Copies the segment section range [us,ue] into a newly allocated 
        segment. 

        All the parameters from the original segment are copied to the 
        newly allocated segment except for \a prev and \a next. A new
        transformation matrix is also created if there is one defined
        in the base arc. 
        
        The returned pointer must be deallocated by the user with delete.
     */
    CS_SegPtr Copy(double us, double ue) ; 


    //! Prints the arc parameters to a file
    /*!
        \param fp file pointer for the output arc data
        \param prec number of decimals for floating point values

        The format of the output string is:

            ASeg:cx,cy,cz,rad,sa,swp,{CW|CCW}

        Note, there is no space output at the start of the line. If 
        fp is NULL then the output goes to stdout (the global stdlib.h
        definition for stdout), otherwise output is to the file designated.
        If the file fp is not open for writing an error will result. 
     */
    void Print(FILE *fp=0, int prec=12) ; 

    //! Prints the 2D arc end points and parameters to a file
    /*!
        \param fp file pointer for the output arc data
        \param prec number of decimals for floating point values

        The format of the output string is:

            ASeg (spx, spy) -> (epx, epy) r=rad sa=sa swp=swp dir={CW|CCW}

        Note, there is no space output at the start of the line. If 
        fp is NULL then the output goes to stdout (the global stdlib.h
        definition for stdout), otherwise output is to the file designated.
        If the file fp is not open for writing an error will result. 
    */
    void PrintPoints2D(FILE *fp=0, int prec=12) ;

    //! Set arc angle and sweep based on the start point and endpoint
    //! parameters passed in, as well as the direction. 
    void SetSPEP(CS_POINT &sp, CS_POINT &ep, int direction)
    {
        CS_ARC::SetSPEP(sp, ep, direction) ;
    }

    //! Reverse the direction of the arc, sa=sa+swp, swp=-swp
    void Reverse() 
    { 
        CS_ARC::Reverse(); 
    }

    //! Return point on the arc at parameteric distance u where \f$u\in[0,1]\f$
    /*!
        \param u parameteric coordinate of point
        \return the point at the specified u relative to the arc segment defined

        Returns point on the arc at parameteric distance u 
        where \f$u\in[0,1]\f$ must be true on entry. If u is out of range then 
        a point that is not actually on the arc (or an erroneous point) will
        be returned since no testing is done on the u value on entry. 
     */
    CS_POINT UPoint(double u) 
    {
        return CS_ARC::UPoint(u) ; 
    }

    //! Tangent vector to arc a parametric point u
    /*!
        \param u parametric value indicating distance along arc \f$u\in[0,1]\f$
        \return Unit vector tangent to the arc at the point u. 
        
        If u < 0, then the tangent at the start point of the arc is returned, 
        likewise if u > 1 then the tangent at the end of the arc is returned.
     */
    CS_VECTOR UTangent(double u) 
    {
        return CS_ARC::UTangent(u) ; 
    }

    //! Return true if point is actually on the segment within tolerance limits
    /*!
     \param p the point to be tested
     \param puval used to store u value of point on segment nearest to p
     \param pnpnt used to store point on segment nearest to p
     \param toldist tolerance to use in the point test if defined. 
     \return true if point p is on the segment, otherwise returns false

     This routine calculates the point on the segment that is closest to 
     the input point p. If the point is actually on the segment then this
     nearest point will equal point p. If puval is not NULL, then the 
     u value of the nearest point on the segment will be saved in *puval.
     Likewise if pnpnt is not NULL, the nearest point on the segment will
     be saved in *pnpnt. True is returned only if the nearest point 
     calculated and the input point p match within the current system 
     tolerance value. The value returned in puval will always be in the 
     range [0,1]. Thus the returned nearest point will never be beyond
     the actual endpoints of the segment. 
     */
    int PointOnSegment(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL, double *toldist=0) ;
    int PointOnSegment2D(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL, double *toldist=0) ;

    int PointSide(CS_POINT &pnt) 
    {
        return CS_ARC::PointSide(pnt) ; 
    }

    //! Sets the z coordinate of points in all segments to \a z
    void SetZ(double z) 
    {
        CS_ARC::SetZ(z) ; 
    }

    //! Calls CS_ARC::Move
    void Move(CS_VECTOR &v)
    {
        CS_ARC::Move(v) ; 
    }

    //! Calls CS_ARC::Scale
    void Scale(double s) 
    {
        CS_ARC::Scale(s) ; 
    }

    //! Calls CS_ARC::Transform
    void Transform(double p[12]) 
    {
        CS_ARC::Transform(p) ; 
    }

    //! Returns true if the arcs are similar
    /*!
        \param psb segment pointer to the arc to compare against
        \return True if the arcs are similar otherwise false

        The two arcs are similar if their radii match to within the 
        system tolerance, and if the magnitude of the sweep of the two
        arcs match within the system tolerance. The orientation and 
        start angle of the arcs are not factored into the testing.
     */
    int Similar(CS_SegPtr psb)
    {
        if (psb->SegmentType() == ARC_TYPE)
        {
            CS_ArcSeg *pas = (CS_ArcSeg *)psb ; 
            if (tcomp_EQ(pas->rad, rad) &&
                tcomp_EQ(fabs(pas->swp), fabs(swp)))
            {
                return 1 ; 
            }
        }
        return 0 ; 
    }

    CS_POINT StartPoint(void) 
    {
        return CS_ARC::StartPoint() ; 
    }

    CS_POINT MidPoint(void)
    {
        return CS_ARC::MidPoint() ; 
    }

    CS_POINT Centroid(void) 
    {
        return CS_ARC::Centroid() ; 
    }

    CS_POINT Centroid2D(void) 
    {
        return CS_ARC::Centroid2D() ; 
    }

    CS_POINT EndPoint(void) 
    {
        return CS_ARC::EndPoint() ; 
    }

    double ArcLength(void)
    {
        return CS_ARC::ArcLength() ; 
    }

    void MTX3Mult(CS_MTX3 &mx) 
    {
        CS_ARC::MTX3Mult(mx) ; 
    }

    double XY_ArcLength(void) 
    {
        return CS_ARC::XY_ArcLength() ; 
    }
    
    // offset segment,-ve=left, +ve=right
    int Offset(double delta) 
    {
        info |= CS_ARC::Offset(delta) ; 
        return info ; 
    }

    //! Intersect the arc with another arc or line segment
    /*!
        \param pseg pointer to the other segment to intersect with
        \param pirlist pointer to the intersection record list to add intersection results to
        \return the number of intersection records add to \a pirlist

        Intersects the arc with the input segment. This handles all the possible
        cases that could occur, and will generate 0, 1 or 2 intersection records. 
        In the case of two arcs intersecting that overlap it is possible to 
        return two separate intersection overlap segments since the second
        arc could be completing (closing) the first arc into a complete circle
        with overlaps at each end. In this scenario it's also possible to have
        a point intersect as well as a separate overlap intersection.
        Any intersection records generated are simply added to the end 
        of the \a pirlist intersection record list. When intersecting with 
        a line segment the results will always be point style intersections
        but if the line is tangent to the arc, the tangent property will also
        be set, whether or not the intersection occurs at the ends or somewhere
        inside the arc segment. 
     */        
    int Intersect2D(CS_SegPtr pseg, CS_IRECList *pirlist) ;

    // If Intersect2D returns 3 then the two arcs are coincident and
    // overlay one another. The points returned define the points on 
    // the *this arc of the coincident section. 
    int Intersect2D(CS_ArcSeg &cas, double *uva, double *uvb) ;
    int Intersect2D(CS_LineSeg &cls, double *uva, double *uvb) ;

    // Trim the start of the curve off (trim [0,u] section)
    void TrimStart(double u) 
    {
        CS_ARC::TrimStart(u) ; 
    }

    // Trims the [u,1] section away
    void TrimEnd(double u) 
    {
        CS_ARC::TrimEnd(u) ; 
    }

    // Trim ends off the arc
    void Trim(double u1, double u2)
    {
        CS_ARC::Trim(u1, u2) ; 
    }

    //! Sets the start point of the arc to pnt
    int AdjustStartPoint(CS_POINT &pnt) 
    {
        return CS_ARC::AdjustStartPoint(pnt) ; 
    }

    //! Sets the emd point of the arc to pnt
    int AdjustEndPoint(CS_POINT &pnt) 
    {
        return CS_ARC::AdjustEndPoint(pnt) ; 
    }

    //! Returns the bounding rectangle of the arc
    CS_RECT BoundingRect()
    {
        return CS_ARC::BoundingRect() ; 
    }
} ;

typedef vector<CS_ArcSeg> CS_ArcSegVec ; 



class CS_LineSeg : public CS_Segment, public CS_LINE {
public:
    CS_LineSeg() {}
    
    CS_LineSeg(CS_LineSeg &line) : CS_Segment(&line) 
    {
        sp = line.sp ; 
        ep = line.ep ; 
    }
    
    CS_LineSeg(CS_LINE &line) 
    {
        sp = line.sp ; 
        ep = line.ep ; 
    }

    CS_LineSeg(CS_LINE *pln)
    {
        sp = pln->sp ; 
        ep = pln->ep ; 
    }

    CS_LineSeg(CS_LineSeg *pls) : CS_Segment(pls) 
    {
        sp = pls->sp ;
        ep = pls->ep ;
    }


    CS_LineSeg(CS_POINT &p1, CS_POINT &p2) : CS_LINE(p1, p2) {}
    ~CS_LineSeg() {} ;

    //! Returns a newly allocated copied segment 
    /*!
        All the parameters from the original segment are copied to the 
        newly allocated segment except for \a prev and \a next. 
        
        The returned pointer must be deallocated by the user with delete.
     */
    CS_SegPtr Copy() ; 

    //! Returns a newly allocated copied segment section from us to ue
    /*!
        \param us the starting u value relative to the segment to copy from
        \param ue the ending u value relative to the segment to copy to
        
        Copies the segment section range [us,ue] into a newly allocated 
        segment. 

        All the parameters from the original segment are copied to the 
        newly allocated segment except for \a prev and \a next. 
        
        The returned pointer must be deallocated by the user with delete.
     */
    CS_SegPtr Copy(double us, double ue) ; 
   
    int SegmentType() { return LINE_TYPE ; }

    int IsLINE() { return 1 ; } ; 

    //! Print line parameters to a file
    /*!
        \param fp file pointer for the output arc data
        \param prec number of decimals for floating point values

        The format of the output string is:

            LSeg:spx,spy,spz,epx,epy,epz

        Note, there is no space output at the start of the line. If 
        fp is NULL then the output goes to stdout (the global stdlib.h
        definition for stdout), otherwise output is to the file designated.
        If the file fp is not open for writing an error will result. 
     */
    void Print(FILE *fp=0, int prec=12) ; 

    //! Prints the 2D line end points to file
    /*!
        \param fp file pointer for the output arc data
        \param prec number of decimals for floating point values

        The format of the output string is:

            LSeg (spx, spy) -> (epx, epy)

        Note, there is no space output at the start of the line. If 
        fp is NULL then the output goes to stdout (the global stdlib.h
        definition for stdout), otherwise output is to the file designated.
        If the file fp is not open for writing an error will result. 
    */
    void PrintPoints2D(FILE *fp=0, int prec=12) ;

    //! Reverse the line segment
    /*!
        Swaps the sp and ep member variable contents
     */
    void Reverse()
    {
        CS_LINE::Reverse() ; 
    }


    //! Return point on the line at parameteric distance u 
    /*!
        Returns point on the line at parameteric distance u 
        where \f$u\in[0,1]\f$ must be true on entry. If u is out of range then 
        a point that is not actually on the line will be returned. 
        Simply calls CS_LINE::UPoint() which can be referred to for more 
        information.
     */
    CS_POINT UPoint(double u) 
    {
        return CS_LINE::UPoint(u) ; 
    }

    int PointOnSegment(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL, double *toldist=0) ;
    int PointOnSegment2D(CS_POINT &p, double *puval=NULL, CS_POINT *pnpnt=NULL, double *toldist=0) ;

    int PointSide(CS_POINT &pnt) 
    {
        return CS_LINE::PointSide(pnt) ; 
    }

    void Move(CS_VECTOR &v)
    {
        CS_LINE::Move(v) ; 
    }

    //! Sets the z coordinate of points in all segments to \a z
    void SetZ(double z)  
    {
        CS_LINE::SetZ(z) ; 
    }


    void Transform(double p[12]) 
    {
        CS_LINE::Transform(p) ; 
    }

    int Similar(CS_SegPtr psb)
    {
        if (psb->SegmentType() == LINE_TYPE)
        {
            CS_LineSeg *pls = (CS_LineSeg *)psb ; 
            if (tcomp_EQ(pls->ArcLength(), ArcLength()))
                return 1 ; 
        }
        return 0 ; 
    }

    CS_POINT StartPoint(void) 
    {
        return CS_LINE::StartPoint() ; 
    }

    CS_POINT MidPoint(void) 
    {
        return CS_LINE::MidPoint() ; 
    }

    CS_POINT EndPoint(void) 
    {
        return CS_LINE::EndPoint() ; 
    }

    double ArcLength(void) 
    {
        return CS_LINE::ArcLength() ; 
    }

    double XY_ArcLength(void) 
    {
        return CS_LINE::XY_ArcLength() ; 
    }

    CS_POINT Centroid(void) 
    {
        return CS_LINE::Centroid() ; 
    }

    CS_POINT Centroid2D(void) 
    {
        return CS_LINE::Centroid2D() ; 
    }

    void Scale(double s) 
    {
        CS_LINE::Scale(s) ; 
    }

    void MTX3Mult(CS_MTX3 &mx) 
    {
        CS_LINE::MTX3Mult(mx) ; 
    }

    // unit tangent vector at u
    CS_VECTOR UTangent(double u) 
    {
        return CS_LINE::UTangent(u) ; 
    }


    int Offset(double delta) 
    {
        return CS_LINE::Offset(delta) ; 
    }

    // Trim away [0,u]
    void TrimStart(double u) 
    {
        CS_LINE::TrimStart(u) ; 
    }

    // Trim away [u,1]
    void TrimEnd(double u)
    {
        CS_LINE::TrimEnd(u) ; 
    }

    // Trim away [0,u1] and [u2,1]
    void Trim(double u1, double u2) 
    {
        CS_LINE::Trim(u1, u2) ; 
    }


    int AdjustStartPoint(CS_POINT &pnt) 
    {
        return CS_LINE::AdjustStartPoint(pnt) ; 
    }

    int AdjustEndPoint(CS_POINT &pnt) 
    {
        return CS_LINE::AdjustEndPoint(pnt) ; 
    }

    CS_RECT BoundingRect()
    {
        return CS_LINE::BoundingRect() ; 
    }

    // Intersect the arc with another arc or line segment
    // returns the number of intersects found
    int Intersect2D(CS_SegPtr pseg, CS_IRECList *pirlist) ;
    int Intersect2D(CS_ArcSeg &cas, double *uva, double *uvb) ;

    // Call below only returns 1 point for a simple intersect, and
    // 2 points if the segments overlay one another. If they do overlay
    // one another then the points define the sections of the two lines
    // which are coincident
    int Intersect2D(CS_LineSeg &cls, double *uva, double *uvb) ; 
} ;


typedef vector<CS_LineSeg> CS_LineSegVec ; 

//! This version doesn't deallocate the segment and is used strictly for
struct CS_SegDataRecord
{
    CS_SegPtr pseg ; 
    CS_RECT bbox ; 
} ;



//! Used for extending the segment information in other routines
struct CS_SegInfo
{
    CS_SegPtr pseg ; 
    CS_RECT bbox ;      // segment bounding box

    CS_SegInfo() {pseg=0; } ; 
    ~CS_SegInfo()
    {
        if (pseg)
            delete pseg ; 
    }
} ;


/////////////////////////////////////////////////////////////////////
// This structure is used to maintain a list of CS_Curve objects
// Such lists are generated by the CS_Curve Offset and boolean 
// operations
/////////////////////////////////////////////////////////////////////

//! Collection of CS_Curves
class CS_CurveSet
{
public:
    CS_CurveVec    crvlist ;   // list of curves (related or not)
    CS_CurveVecItr ploopnode ; // used for iteration through list

    CS_CurveSet() ;
    CS_CurveSet(const CS_CurveSet &) ; // copy constructor
    CS_CurveSet &operator=(const CS_CurveSet &crv) ; //

    ~CS_CurveSet() ; // calls Reset() ; 

    //! delete and de-alloc all curves in set, same as clear() function
    void Reset() ;

    //! delete and de-alloc all curves in set, same as the Reset() function, 
    void clear() ; 

    // Add this curve to the set. Once added, the reponsibility of deleting
    // the curve and freeing it's memory will be assumed by the CS_CurveSet
    // class. Do not add curves that were created dynamically on the stack
    // unless the CS_CurveSet will be destroyed before the function scope
    // that defines the add curve is exited. Then you must ensure that the
    // CS_Curve's destructor is not called as well. 
    int AddCurve(CS_Curve *pcrv) ; 

    //! Appends the crvset by removing all the curves from the input set
    /*!
        \param crvset the input curve set that will be appended.

        Once done all the curves in crvset will be moved to the end
        of the *this curve set. The input crvset will be empty after
        this call. 
     */
    int AppendSet(CS_CurveSet &crvset) ; 

    //! Delete the curve from the set
    /*!
        \param pcrv pointer to the curve to be deleted
        \return 0=curve was removed, -1=curve not found

        The DeleteCurve() calls do not delete the pcrv data that they reference. 
        Only the CS_CurveSet destructor will do this. The pcrv data will still be valid. 
        Find the node with the curve pcrv and delete the curve and node 
        from the list. This finds the node first, and then calls the 
        DeleteCurve(CS_CurveVecItr pn) member function. See below with 
        respect to deleting the current curve when iterating through the set. 
     */
    int DeleteCurve(CS_Curve *pcrv) ; 

    // NOTE: The DeleteCurve() calls do not delete the pcrv 
    // data that they reference. Only the CS_CurveSet destructor 
    // will do this. The pcrv data will still be valid. If iterating
    // through the list and the current node is deleted, then the current
    // node becomes the next after the one that is deleted. 
    // This way you can continue to iterate through the list using 
    // NextCurve and still get the next curve in the set as expected. 
    int DeleteCurve(CS_CurveVecItr pn) ; 

    //! Remove all curves from the set
    /*!
        Removes all curves from the curve set but does not destroy the individual
        curves within the set. This is intended to be used when copying the curve
        set to another set and then clearing the original so that the 
        destructor in the original set does not affect the curve pointers in 
        the set that was copied to. 
     */
    void DeleteAllCurves() ; 

    //! Initialize the internal iterator to the start of the set
    /*!
        After calling the InitIterator function for a set, calling NextCurve() or
        RemoveNextCurve() will return the first curve in the set. The internal 
        iterator is also advanced to the next curve after the one just returned. 
        In the case of RemoveNextCurve() this would be the first curve in the set
        again (since the previous first curve is no longer part of the set).
        Thus you can iterate through the set by doing the following
        
        \verbatim
        CS_CurveSet crvset ; 
        
        // Code that adds curves to crvset

        CS_CurvePtr pcrv ; 
        crvset.InitIterator() ; 
        while (pcrv = crvset.NextCurve())
        {
            // process with pcrv, loop continues once for each curve in 
            // curveset. 
                .
                .
                .
        }
        \endverbatim
     */
    void InitIterator() ;

    // Returns pointer to next curve, advancing the iterator. The curve
    // is left within the set.
    CS_Curve *NextCurve() ;

    // Return the next curve in the set and delete the node within
    // the curve set. Thus class no longer responsible for the 
    // CS_Curve destruction.
    CS_Curve *RemoveNextCurve() ;

    size_t Count() { return (crvlist.size()); } ; 
    size_t Length() { return (crvlist.size()); } ; 
    size_t size() { return (crvlist.size()); } ; 

    //! Sort the curves in the list by area
    /*!
        \param descending set to true to sort from largest to smallest area
        \param noinit do not calculate area, XYarclength already set
        
        The CS_Curve internal parameter XYarclength is used to sort 
        the curves into a list from smallest to largest area. 
        If noinit is true, then XYarclength
        must be defined before this function is called for each of 
        the curves in the set. If noinit is false then before the sort
        is done, the function calls Complete(CCW) and then sets
        the XYarclength = Area() for each of the curves respectively. 

        To reverse the sort order to largest -> smallest set descending
        to true. 

        If you want to sort the curves by a different metric other than 
        area simply define each curve value in XYarclength and call
        this function with noinit true.
     */
    void SortByArea(int descending=0, int noinit=0) ; 

    //! Sort the curves in the list by curve arc length
    /*!
        \param descending set to true to sort from largest to smallest length
        \param noinit do not calculate lengths, arclength already set
        
        The CS_Curve internal parameter arclength is used to sort 
        the curves into a list from smallest to largest area. 
        If noinit is true, then arclength must already
        be defined for each of the curves in the set before this function 
        is called. If noinit is false then before the sort
        is done, the function calls ArcLength(NODIR) for each of the 
        curves.

        To reverse the sort order to longest -> shortest set descending
        to true. 

        If you want to sort the curves by a different metric other than 
        arc length simply define each curve value in arclength and call
        this function with noinit true.
     */
    void SortByArcLength(int descending=0, int noinit=0) ; 
} ;


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// These status flags are used to optimze the processing time for 
// various curve functions.

//  statflag 
#define CS_XY_ARCLENGTH_VALID   0x0001 
#define CS_CLOSEDCURVE          0x0002 // curve is closed
#define CS_ARCLENGTH_VALID      0x0004 
#define CS_HOLECURVE            0x0008 // represents hole inside another curve
#define CS_CURVEINSIDE          CS_HOLECURVE // curve is inside another curve
#define CS_ISLANDDELETED        0x0010 // used during pocketing operations
#define CS_NODECNT_VALID        0x0020 // cnt variables within segnodes are valid
#define CS_UVALUE_VALID         0x0040
#define CS_FORCEOPENOFS         0x0080 // forces offset to be open for closed curves 
#define CS_BNDRECT_VALID        0x0100  
#define CS_NEXTSTART            0x0200 // on next call to NextPoint() return psegnxt start point

// The following are used in the UPoint() and USegment() functions and determine
// how a the appropriate parameter is to be retieved. In future we want to clean
// up the setting of all the statflag parameters so that the internal functions
// decide automatically when Finalize needs to be called, so that the end user
// need not concern themselves about these parameters. The internal functions
// can decide automatically if we maintain the current validity of all the 
// curve segment uo parameters, as well as the validity of the overall curves
// arc length values
#define CS_SEARCHBYARCLENGTH      1 
#define CS_SEARCHBYUVALUE         0 

// Used as parameter passed to CopySection()
#define CURVEBASED_UVALUES        0
#define SEGMENTBASED_UVALUES      1  


#define CS_FILLET_SEGMENTS_TANGENT      0x00000001 
#define CS_FILLET_ZERO_RADIUS           0x00000002 

///////////////////////////////////////////////////////////////////////////
// Maintains a list of lines, arcs, amd splines defining a polyline style 
// curve. The end points of adjacent curves define redundant information 
// but this does speed up processing when processing the various curve 
// segments.

///////////////////////////////////////////////////////////////////////////
// TO DO - define a bounding rectangle for the curve which is dynamically
//      maintained or calculated upon request dependent on a flag setting
//      This can be used to speed up point inside type tests.
///////////////////////////////////////////////////////////////////////////

//! A List of segments defining arbitrary curves
/*!
    \class CS_Curve

    The CS_Curve class is the basic general curve structure used through
    the geometry library. It consists of an array of \a CS_Segment's (which
    for now consist of only lines and arcs), and can be opened, closed,
    self intersecting, or even disjoint. Some operations place restrictions
    on curves, such as offsetting which require continuous non-intersecting
    curves to behave correctly.
    
    The segment within the curve has a pointer back to the parent CS_Curve
    class to permit tracing through different curves in chaining operations
    and other operations where it is necessary to know which base curve
    a particular segment is associated with. The segments within a curve
    must be unique in that two \a CS_Curve's cannot share the same segment, 
    since the \a prev and \a next segment pointers cannot be set to follow
    two different curves at the same time (it would be possible to have the
    same segment in two curves if each curve had only a single segment 
    defined within it, since in this case the \a prev and \a next pointers
    for the segment would both be NULL, but this is not recommeneded). The
    diagram below is an example of what a CS_Curve looks like. It defines
    an open curve made up of 4 segments. Each segment is oriented in the 
    direction of increasing u value, which is handled automatically as 
    curves are being built. 

    \image latex cs_curves.eps "CS_Curve sample definition" width=120mm
    
\latexonly 
It is possible to add segments in the reversed 
direction by defining \mbox{CS\_NOENDPOINTADJUSTMENT} when the segment is 
appended to the curve. Doing so would create a disjoint curve, so keep
that in mind if using the \mbox{CS\_NOENDPOINTADJUSTMENT} option since the 
curve segments can be randomly located anywhere in this case.
\endlatexonly

 */
class CS_Curve  {
public: 
    //! number of segments making up the curve
    int nodecnt ; 

    //! internal working pointer, set in StartPoint() and used in NextPoint() call
    CS_SegPtr psegnext ; 

    //! pointer to the first segment in the curve
    CS_SegPtr pStart ;

    //! pointer to the last segment in the curve
    CS_SegPtr pEnd ;     

    //! sunm of the arclengths for each segment in the curve
    double arclength ; /// overall arc length of the curve

    //! sum of the arclengths for each segment in the curve when projected onto XY plane
    double XYarclength ; 
    
    //! bounding rectangle for the curve
    CS_RECT bndrect ; 

    //! flags indicating the current status of the curve
    /*!
        CS_XY_ARCLENGTH_VALID   0x0001 
        CS_CLOSEDCURVE          0x0002 // curve is closed
        CS_ARCLENGTH_VALID      0x0004 
        CS_HOLECURVE            0x0008 // represents hole inside another curve
        CS_CURVEINSIDE          CS_HOLECURVE // curve is inside another curve
        CS_ISLANDDELETED        0x0010 // used during pocketing operations
        CS_NODECNT_VALID        0x0020 // cnt variables within segnodes are valid
        CS_UVALUE_VALID         0x0040
        CS_FORCEOPENOFS         0x0080 // forces offset to be open for closed curves 
        CS_BNDRECT_VALID        0x0100  
        CS_NEXTEND              0x0200 on next call to NextPoint() return end point and exit
     */
    int statflags ;   

    //! pointer to arbitrary user data, not used internally by the library
    void *pUserData ;  

    //! This data structure is only assigned during chaining operations
    /*!
        The \a pcnmap is a sorted list of chaining nodes sorted by u value
        w.r.t. the overall curve. These are the interesection nodes with
        other curves that are stored within the CS_ChainSTK set of the 
        CS_Chain class. The chaining functions are responsible for maintaining
        the data stored in pcnmap. 

        Warning: when curves are copied the pcnmap pointer is simply copied
        from one curve to the other, a new map is not created. Thus make sure
        that if a pcnmap is defined for a copied curve that the pointer is 
        set to 0 (null) before the destructor is called. 
     */
    CS_ChnNodeMap *pcnmap ; 

    //////////////////////////////////////////////////////////////////
    // CS_Curve Member functions
    //////////////////////////////////////////////////////////////////

    //! Base constructor
    CS_Curve() ; 

    //! De-allocates all memory associated with the curve, including all segments
    ~CS_Curve() ; 

    //! copy constructor
    CS_Curve(const CS_Curve &crv) ; 

    //! Default assignment operator
    CS_Curve &operator=(const CS_Curve &crv) ; 

    //! Copy the contents of crv into *this
    int CopyCurve(const CS_Curve &crv) ; 

    //! Allocates a curve using new operator that is a copy of the *this curve
    CS_Curve *CopyCurve() ; 


    //! Returns the next segment and walks past the end of the curve looping
    //! forever, even on open curves.
    CS_SegPtr Next(CS_SegPtr pn)
    {
        CS_SegPtr psnext = pn->next ; 
        if (!psnext)
            return pStart ; 
        return psnext ; 
    }; 

    //! Next segment with End Stop
    /*!
        \param pn pointer to current segment to walk from
        \return pointer to the next segment (the one attached to pn's end point)
        
        Returns the next segment but will not walk past the end of an open curve.
        For open curves, walking past the end returns NULL. The closed status
        must be set accurately before calling this function.
     */
    CS_SegPtr NextES(CS_SegPtr pn)
    {
        CS_SegPtr psnext = pn->next ; 
        if (!psnext && (statflags & CS_CLOSEDCURVE))
            return pStart ; 
        return psnext ; 
    }; 

    //! Returns the previous segment and walks past the start of the curve 
    //! looping forever, even on open curves.
    CS_SegPtr Prev(CS_SegPtr pn)
    {
        CS_SegPtr psprev = pn->prev ; 
        if (!psprev)
            return pEnd ; 
        return psprev ; 
    }; 

    //! Previous segment with End Stop
    /*!
        \param pn pointer to current segment to walk from
        \return pointer to the previous segment (the one attached to pn's start point)
        
        Returns the previous segment but will not walk past the end of an open curve.
        For open curves, walking past the end returns NULL. The closed status
        must be set accurately before calling this function.
     */
    CS_SegPtr PrevES(CS_SegPtr pn)
    {
        CS_SegPtr psprev = pn->prev ; 
        if (!psprev && (statflags & CS_CLOSEDCURVE))
            return pEnd ; 
        return psprev ; 
    }; 


    //! Returns u value of start of next segment, doesn't wrap around 
    /*!
        \param ps the starting segment pointer to advance from
        \return the u value at the start of the next segment

        If the ps segment is the last one in the curve then the function
        returns 1.0 indicating the end of the curve. 
     */
    double NextSegU(CS_SegPtr ps)
    {
        if (ps->next)
            return ps->next->uo ; 
        return 1.0 ; // then end of the curve
    }

    //! Returns u value of start of previous segment, doesn't wrap around 
    /*!
        \param ps the starting segment pointer to walk backwards from
        \return the u value at the start of the previous segment

        If the ps segment is the first one in the curve then the function
        returns 0.0 indicating the end of the curve (which is the uo value
        of the input ps segment as well, so effectively nothing happens)
     */
    double PrevSegU(CS_SegPtr ps)
    {
        if (ps->prev)
            return ps->prev->uo ; 
        return 0.0 ; 
    }

    //! Walk along each curve segment, stopping at the to crv point
    /*!
        This wraps past the end of the curve, back to the start 
        even on open curves. Thus eventually the to point will be hit. 

        The point returned is the start of the next segment unless 
        the to point is hit first. 

        If the two curve points are equal, then next step will be 
        taken. It is up to the calling routine to test if the points
        are equal as an exit condition. 
     */
    CS_CrvPnt StepTo(CS_CrvPnt &from, CS_CrvPnt &to) ; 

    //! Walk backwards along each curve segment, stopping at the to crv point,
    /*!
        This wraps past the start of the curve, back to the end
        even on open curves. Thus eventually the to point will be hit. 

        The point returned is the start of the previous segment. If the 
        from point u value is not zero, then the curve point returned
        is the same segment with a u value of 0, unless the to point 
        is hit first. 

        If the two curve points are equal, then next step will be 
        taken. It is up to the calling routine to test if the points
        are equal as an exit condition. 
     */
    CS_CrvPnt StepBackTo(CS_CrvPnt &from, CS_CrvPnt &to) ; 


    //! Assigns the CS_Segment parent pointers to point to the *this curve
    void SetParentPointers() ;

    //! Updates the \a CS_Segment::cnt member variable and this->nodecnt
    void SetNodeCounts()
    {
        int count = 0 ; 
        CS_SegPtr psn = pStart ; 
        while (psn)
        {
            psn->cnt = count++ ; 
            psn = psn->next ; 
        }
        statflags |= CS_NODECNT_VALID ;
    }

    //! Add a point to the end of the curve, creates a new line segment
    /*!
        This extends the current curve. If the curve is empty, then the 
        initial call creates a line segment of zero length. The second
        call to AddPoint updates the endpoint of the zero length segment. 

        Then segments are added continuously. If the end point wraps back around
        to the start point the curve gets closed. If you add more segments after
        that then the curve wouldn't be closed anymore but would be self 
        intersecting. 
        
        Returns pointer to the last segment, thus segptr->EndPoint() will be the 
        point just added. 

        The last segment in the curve must be null or a line for this to work. 
        If the last segment is something that is not a line then memory will 
        be corrupted. 
     */
    CS_SegPtr AddPoint(CS_POINT &p) ; 
   
    //! Add a node to an existing CurveList structure
    /*!
        \param pseg the new segment to be added
        \param NoEndpointAdjustment if true then skip the endpoint adjustment logic
        \return pointer to the same segment that was appended. 
        
        Note pseg must point to a CS_ArcSeg or CS_LineSeg that was allocated with
        the C++ 'new' operator. Freeing the pseg data will be taken care of by the 
        CS_Curve destructor. The end point adjustment if called, attempts to 
        re-orient the curve as it is added. Thus the newly appended segment will be
        reversed if required to connect up to the curve properly. It is possible
        to create a disjoint curve if a collection of segments is required for 
        some reason that do no connect endpoint to endpoint. 
        Do this by appending disconnected segments and set endpoint adjustment 
        to CS_NOENDPOINTADJUSTMENT. 
     */
    CS_SegPtr Append(CS_SegPtr pseg, int NoEndpointAdjustment = 0) ;

    //! Insert a node into an existing curve list before the specified segment
    /*!
        \param pins Insert the new segment before the pins segment
        \param pseg the new segment to be inserted
        \param NoEndpointAdjustment if true then skip the endpoint adjustment logic
        \return pointer to the same segment that was inserted. 

        Note pseg must point to a CS_ArcSeg or CS_LineSeg that was allocated with
        the C++ 'new' operator. Freeing the pseg data will be taken care of by the 
        CS_Curve destructor. The end point adjustment if called, attempts to 
        re-orient the curve as it is added. Thus the newly appended segment will be
        reversed if required to connect up to the curve properly. It is possible
        to create a disjoint curve if a collection of segments is required for 
        some reason. Do this by appending disconnected segments with 
        NoEndpointAdjustment set to CS_NOENDPOINTADJUSTMENT. 
        If pins is NULL then the segment is inserted at the 
        start of the curve. 
     */
    CS_SegPtr Insert(CS_SegPtr pins, CS_SegPtr pseg,
                       int NoEndpointAdjustment = 0 ) ;

    //! Insert a node into an existing curve list after the specified segment
    /*!
        \param pins Insert the new segment after the pins segment
        \param pseg the new segment to be inserted
        \param NoEndpointAdjustment if true then skip the endpoint adjustment logic
        \return pointer to the same segment that was inserted. 

        Note pseg must point to a CS_ArcSeg or CS_LineSeg that was allocated with
        the C++ 'new' operator. Freeing the pseg data will be taken care of by the 
        CS_Curve destructor. The end point adjustment if called, attempts to 
        re-orient the curve as it is added. Thus the newly appended segment will be
        reversed if required to connect up to the curve properly. It is possible
        to create a disjoint curve if a collection of segments is required for 
        some reason. Do this by appending disconnected segments with 
        NoEndpointAdjustment set to CS_NOENDPOINTADJUSTMENT. 
        If pins is NULL then the segment is appended to the 
        end of the curve. 
     */
    CS_SegPtr InsertAfter(CS_SegPtr pins, 
                            CS_SegPtr pseg, 
                            int NoEndpointAdjustment = 0) ;

    void AdjustSegmentDirection(CS_SegPtr pn) ;


    //! Adjust segment directions so that curves connect properly endpoint to endpoint
    /*!
        \return 0=OK, else an error occured

        Return codes:
        -1 nothing to do since curve empty or only has single segment
     */
    int OrientSegments() ; 

    //! Delete the segment from the curve list
    /*!
        \param pdelnode the node to delete from the curve

        The pdelnode is removed from the curve and the memory used by that 
        node is freed. The curve uo, xy_arclength, and status values will 
        no longer be valid after this function. \a pdelnode must be a segment
        in the curve otherwise linked list pointers will be corrupted. 
        If the pdelnode is NULL then nothing happens. 
     */ 
    void Delete(CS_SegPtr pdelnode) ; 

    //! Remove the segment from the curve list
    /*!
        \param premnode the node to delete from the curve
        \return pointer to the next segment after premnode

        The premnode is removed from the curve and the memory used by that 
        node is freed. The curve uo, xy_arclength, and status values will 
        no longer be valid after this function. \a premnode must be a segment
        in the curve otherwise linked list pointers will be corrupted. 
        If the premnode is NULL then nothing happens and NULL is returned. 
        If the curve is closed and premnode is the last segment in the
        current curve while there are still segments in the curve
        then a pointer to the first segment is returned, this way all 
        nodes can be removed from any starting point within the curve. 
     */ 
    CS_SegPtr Remove(CS_SegPtr premnode) ; 

    //! Replace segment in curve with another segment
    /*!
        \param preplace the segment node to be replaced
        \param pnewseg  the new segment to replace preplace with

        The end points of the new segment must match the end points of the
        segment being replaced. The only segment internal variable that is
        not set from the current segment is the pUserData pointer. The caller
        must set the pUserData pointer as required. The uo, cnt and pParent
        values are all copied from the old into the new segment. 

        pnode is de-allocated and must not be referenced after this function is
        called. 

        Note pseg must point to a CS_ArcSeg or CS_LineSeg that was allocated with
        the c++ 'new' operator. 
    */
    void Replace(CS_SegPtr preplace, CS_SegPtr pnewseg) ; 

    //! de-allocates all segments and resets all pointers and counters to 0 (NULL)
    void Destroy() ; 

    //! Calls destroy (yes it's redundant, call Destroy() to avoid extra function call)
    void Reset() ; 

    //! reverse the curve direction, no uo values are adjusted
    void Reverse() ; 

    //! Return the n'th (0 based counting) from the curve
    /*!
        This simply walks the curve list counting the segments as it goes and when 
        it reaches n it stops and returns a pointer to that segment. Thus it is not
        efficient and should only be used when performance is not an issue
     */
    CS_SegPtr GetAt(int n) ; // retrieve the n'th Node

    //! Add pcrv to end of *this curve
    /*!
        \param pcrv curve to be added to *this that was created from new operator. 
        \param mode controls how the curve is added. 
        \return Reference to the base curve

        This function adds the second curve to the first and effectively 
        empties the curve passed in and then  de-allocates it. The start of the 
        pcrv is appended to the end of the base curve. Since the final step
        within AddCurve() is to do a \verbatim delete pcrv \endverbatim operation
        make sure that the pcrv pointer passed in was allocated on the heap with 
        the new operator. 

        No testing is done to see if the end points match up properly 
        with the default parameter of CS_NOENDPOINTADJUSTMENT. For the other
        modes the behaviour is as follows: 

        Modes: 

        CS_ADJUST_STARTPOINT -  force the start point of the first
            segment in pcrv to the end point of the base curve. This can 
            cause problems with arcs if the endpoints are far apart since
            the resultant arc could end up being drastically different
            than the original arc. 

        CS_ADJUST_ENDPOINT - force the endpoint on the base curve to 
            match the startpoint of the first segment in pcrv.  This can 
            cause problems with arcs if the endpoints are far apart since
            the resultant arc could end up being drastically different
            than the original arc. 

        CS_ADJUST_APPENDCURVE_ENDPOINTS - pcrv curve is flipped 
            if it's endpoint matches the endpoint of the base curve (*this).
        
        CS_ADJUST_BASECURVE_ENDPOINTS - base curve is flipped (reversed) 
            if the startpoint of *this matches the startpoint of the 
            curve being added.

        During the append process the CS_Segments are simply moved 
        from one list to the other.
     */
    CS_Curve &AddCurve(CS_Curve *pcrv, int mode=CS_NOENDPOINTADJUSTMENT) ; 

    //! Insert pcrv at the start of base (or the *this) curve
    /*!
        \param pcrv curve to be prepended to base that was created from new operator. 
        \param mode controls how the curve is added. 
        \return Reference to the base (*this) curve

        This function inserts pcrv in front of *this and effectively 
        empties the curve passed in and then de-allocates it. The end of the 
        pcrv is connected to the start of the base curve. Since the final step
        within AddCurve() is to do a \verbatim delete pcrv \endverbatim operation
        make sure that the pcrv pointer passed in was allocated on the heap with 
        the new operator. 

        No testing is done to see if the end points match up properly 
        with the default parameter of CS_NOENDPOINTADJUSTMENT. For the other
        modes the behaviour is as follows: 

        Modes: 

        CS_ADJUST_STARTPOINT -  force the start point of the first
            segment in base to the end point of the pcrv curve. This can 
            cause problems with arcs if the endpoints are far apart since
            the resultant arc could end up being drastically different
            than the original arc. 

        CS_ADJUST_ENDPOINT - force the endpoint on the pcrv curve to 
            match the startpoint of the first segment in base.  This can 
            cause problems with arcs if the endpoints are far apart since
            the resultant arc could end up being drastically different
            than the original arc. 

        CS_ADJUST_APPENDCURVE_ENDPOINTS - pcrv curve is flipped 
            if it's startpoint matches the startpoint of the base curve (*this).
        
        CS_ADJUST_BASECURVE_ENDPOINTS - base curve is flipped (reversed) 
            if the endpoint of *this matches the endpoint of the 
            curve being added.

        During the append process the CS_Segments are simply moved 
        from one list to the other.
     */
    CS_Curve &InsertCurve(CS_Curve *pcrv, int mode=CS_NOENDPOINTADJUSTMENT) ; 


    //! Return the point at the specified curve u value
    /*! 
        \param u parameter u value along the curve for point to be returned
            The domain of u must be [0,1]
        \param psegpnt pointer to the segment pointer where the point occurs
        \param searchmode = {CS_SEARCHBYARCLENGTH, CS_SEARCHBYUVALUE}
        \return The point on the curve at the specified u point

        This returns the point on the curve at that u value given (u is with 
        respect to the curve). If psegpnt is not NULL then the actual CS_Segment
        that the point is on will be returned. If psegpnt is defined it must 
        point to a valid CS_SegPtr (memory must already be allocated to accept
        the pointer value, since none is allocated by this function). 

        The searh mode controls how the point is searched for while stepping
        from one segment to the next. With CS_SEARCHBYARCLENGTH, the arclength
        of the overall curve and each segment is mapped back to their equivalent 
        u values for determining the final point. The only advantage of this 
        method is that the uo values for each segment do not need to be set
        before calling the function. If the uo values are set for the 
        overall curve, then the default CS_SEARCHBYUVALUE mode will be
        more efficient. 
     */
    CS_POINT UPoint(double u, CS_SegPtr *psegpnt=0, int searchmode=CS_SEARCHBYARCLENGTH) ;

    //! Uses the psegarray to quickly find the U point of the segment
    /*!
        \param u value on curve for the point to be returned
        \param psegarray array of segments so that a binary search of uo values can be done
        \return the point on the curve at u

        Only speeds up processing if the curve has more than 10 or more segments. For 
        curves with hundreds or thousands of segments this function will drastically
        improve performance. Make sure the u value is in the range [0,1] otherwise
        the binary search could enter into an infinite loop.
     */
    CS_POINT FastUPoint(double u, CS_SegPtr *psegarray) ; 

    //! Uses the psegarray to quickly find the U point of the segment
    /*!
        \param u value on curve for the segment to be returned
        \param psegarray array of segments so that a binary search of uo values can be done
        \return the segment in the curve that contains the point at u

        Only speeds up processing if the curve has more than 10 or more segments. For 
        curves with hundreds or thousands of segments this function will drastically
        improve performance. Make sure the u value is in the range [0,1] otherwise
        the binary search could enter into an infinite loop.
     */
    CS_SegPtr FastUSegment(double u, CS_SegPtr *psegarray) ; 

    //! The psegarray that is required by FastUSegment and FastUPoint
    /*!
        Make sure nodecnt is correclty defined before calling this function, by 
        calling SetNodeCounts or CalcArcLength(). Returns an array of segments
        matching the segments in the curve

        Free the pointer returned by calling:
            \verbatim delete[] retptr ; \endverbatim
     */
    CS_SegPtr *BuildSegArray() ; 
    
    //! Return the segment which contains the specified curve u value
    /*! 
        \param u parameter u value along the curve for point to be returned
            The domain of u must be [0,1]
        \param searchmode = {CS_SEARCHBYARCLENGTH, CS_SEARCHBYUVALUE}
        \return The point on the curve at the specified u point

        This returns the segment on the curve at that contains the curve u 
        value given. If the u value occurs at a segment end point, then 
        the first segment reached will be returned (so the point on the 
        curve at that u value will occur at the EndPoint() of the segment
        returned). 

        The searh mode controls how the point is searched for while stepping
        from one segment to the next. With CS_SEARCHBYARCLENGTH, the arclength
        of the overall curve and each segment is mapped back to their equivalent 
        u values for determining the final point. The only advantage of this 
        method is that the uo values for each segment do not need to be set
        before calling the function. If the uo values are set for the 
        overall curve, then the default CS_SEARCHBYUVALUE mode will be
        more efficient. 
     */
    CS_SegPtr USegment(double u, int searchmode=CS_SEARCHBYARCLENGTH) ;

    //! Return u point for the curve projected onto XY plane
    /*!
        \param u The projected u value of the desired point
            The domain of u must be [0,1]
        \param psegpnt pointer to the segment pointer where the point occurs
        \return The point at the projected u value

        This is equivalent to the UPoint() function except that the
        search is done through XY projected arclengths. 

        \todo Create a diagram for CS_Curve::XY_UPoint()
     */
    CS_POINT XY_UPoint(double u, CS_SegPtr *psegpnt=0) ; 

    // Detemines nearest point to curve, returns true if point is on curve
    /*!
        If the pseg pointer is not null then useg must also be valid. If only
        useg is defined and pseg is not, then pseg and useg will not be set.
     */
    int PointOnSegment(CS_POINT &p, double *puval=0, 
                       CS_POINT *pnpnt=0, CS_SegPtr *pseg=0, double *useg=0);
    
    /////////////////////////////////////////////////////////////////////////
    // TO DO - currently this routine calls
    // PointOnSegment(...) simplifies name mapping, should probably
    // be defined as a macro but point on segment should one day take a 
    // segment index as the segment to process specifically, so the two 
    // will eventually be different.
    int PointOnCurve(CS_POINT &p, double *puval=NULL,
                     CS_POINT *pnpnt=0, CS_SegPtr *pseg=0,
                     double *useg=0) ;
    
    // Simply calls the above, simplifies parameter passing. 
    int PointOnCurve(CS_POINT &p, CS_CrvPnt &cp, 
                     double *puval=NULL, CS_POINT *pnpnt=0) ; 

    //! Returns the u value along curve closest to input \a pnt. Calls PointOnCurve
    double UValue(CS_POINT &pnt) ; 

    //! Return curve point +/- deltau from cp. deltau w.r.t overall curve.
    /*!
        \param cp curve point reference position
        \param deltau u distance from cp for resultant curve point
        \return the curve point deltau from cp

        The deltau value is with respect to the overall curve. Thus values
        of +/-1.0 will wrap forwards and backwards around the entire curve
        and not the segment reference by cp. The deltau value is normalized
        upon entry so values outside [-1, 1] can be input but on open curves
        this means the end points will act as limitting stops.
     */
    CS_CrvPnt CrvPntDeltaU(CS_CrvPnt &cp, const double &deltau) ; 

    // Returns true if point inside closed curve, raylen used to indicate inf
    /*!
        The point must be actually inside the shape within the tolerance
        distance otherwise the routine will probably return false. The 
        reason is that 5 rays are shot out from the point and if the 
        majority of those rays return an even number of intersections then 
        the point is considered to be outside. Taking a circle as an example
        if the point is on the circle then if the ray goes through to the 
        opposite side of the circle two intersections will result, one at the 
        point, and the other at the opposite side, which will be an even 
        intersect result and count as the point being outside. 
        Do a PointOnCurve() test to filter out if the point is actually 
        on the curve first if you want to test the point is on OR inside
        condition. 

        If raylen is 0 (or not defined), then the max dimension (width or height)
        of the bounding box times 2.0 is used as the raylength

        skipSetBounds will bypass the SetBoundingRect() call internally. 
        SetBoundingRect() must have been called previously or raylen must 
        not be zero, otherwise the results will be undefined. 

     */
    int PointInside(CS_POINT &p, double raylen=0.0, int skipSetBounds=0) ; 
    int Inside(CS_POINT &p, double raylen=0.0, int skipSetBounds=0) ; 

    int SetDirection(int direction=CCW, double *parea=0) ; // CW or CCW

    //! Returns the start point of the curve, if curve is undefined, returns (0,0,0)
    /*!
        After calling StartPoint() the next call to NextPoint() would return 
        the next point after the start point. Thus StartPoint() is another 
        way to initialize the NextPoint() logic. 
     */
    CS_POINT StartPoint() ;

    //! Get next point and return pointer to next segment. Returns null when no more points. 
    /*!
        There are two ways to use this in a loop to return all points in the curve

        \verbatim
        // Method 1
        CS_Curve crv ; 
            
            create crv data here

        CS_POINT p = crv.StartPoint() ; 
        do {
            .
            .  // do something with point p
            .
        } while (crv.NextPoint(p)) ; 

        \endverbatim

        The other way to use NextPoint() in a loop is as follows

        \verbatim
        // Method 1
        CS_Curve crv ; 
            
            create crv data here

        CS_POINT p l 
        crv.ResetNextPoint() ; 
        while (crv.NextPoint(p))
        {
            .
            .  // do something with point p
            .
        }

        \endverbatim
     */
    CS_SegPtr CS_Curve::NextPoint(CS_POINT &p) ;

    //! Resets the NextPoint so that the next call to NextPoint() returns the StartPoint()
    void ResetNextPoint() ;

    //! Returns the mid point of the curve, if curve is undefined, returns (0,0,0)
    CS_POINT MidPoint() { return UPoint(0.5) ; } 

    //! Returns the end point of the curve, if curve is undefined, returns (0,0,0)
    CS_POINT EndPoint() ; 

    void Scale(double s) ; 

    //! Apply full 3D transform, including translation
    void Transform(CS_MTX4 &mx) ;

    //! Apply 3D transform defined by matrix mx, no translation
    void MTX3Mult(CS_MTX3 &mx) ; 

    //! Mirror the curve across mirrorline
    void Mirror(CS_LINE &mirrorline) ; 

    //! translate curve by vector v
    void Move(CS_VECTOR &v) ; 

    //! Sets the z coordinate of points in all segments to \a z
    void SetZ(double z) ; 

    
    //! returns the overall curve u value based on the segment u value in curve.
    double SegU2CrvU(CS_SegPtr pseg, double useg) ; 
    double SegU2CrvU(CS_CrvPnt &cp) ; 
    
    //! Returns the CS_CrvPnt for the input u (u is w.r.t to the entire curve)
    CS_CrvPnt CS_Curve::UCrvPnt(double u) ;

    //! Given the overall curve u point returns the segment and the u value
    //! relative to that segment. This function fails is passed in u values 
    //! that are out of range [0,1]
    void CrvU2SegU(double u, CS_CrvPnt &cpout) ;
    void CrvU2SegU(double u, CS_SegPtr &psegout, double &usegout) ; 
    void CrvU2SegU(double u, CS_SegPtr pseghint, CS_CrvPnt &cpout) ;

    //! Returns the u on the segment given the curve u passed in.
    /*!
        \param u on curve 
        \param pseg pointer to segment that u point occurs on
        \return u value w.r.t the segment

        Only call this function if you know the point occurs on the given
        segment otherwise an invalid result will be returned, although
        the value returned will always be in the range [0,1]
     */
    double CrvU2SegU(double u, CS_SegPtr pseg) ; 

    //! Same as CrvU2SegU(doubleu, CS_SegPtr pseg) without retval check
    /*! 
        \param u on curve 
        \param pseg pointer to segment that u point occurs on
        \return u value w.r.t the segment

        Only call this function if you know the point occurs on the given
        segment otherwise an invalid result will be returned.Same as the 
        CrvU2SegU(double u, CS_SegPtr pseg) function except that the 
        u value is not tested to guarantee that it is in the range [0,1]. 
        If you get a value < 0 then the u point actually occured before the
        segment along the curve at a distance equivalent to 
        uret * arclengthOfSeg before the segments start point. And if a 
        value greter than 1 is returned then the actual point is on the 
        curve a distance of uret * arclengthOfSeg beyond the start point
        of the segment. 
     */
    double FastCrvU2SegU(double u, CS_SegPtr pseg) ; 

    //! Adjust u to the range [0,1]
    /*! 
        This function takes into account start/end crossovers on closed
        curves. Thus a value of 1.4 would return .4 and -1.2 would return 0.8.
        For open curves u values less than 0 return 0 and u values 
        greater than 1.0 return 1.0. 
     */
    double UNorm(double u) ;

    // arclength from start to u point, the internal arclength variable
    // must be valid thus make sure CalcArcLength() has been called first
    double UArcLength(double u) { return u * arclength ; } ; 
        // the curve is built
    
    //! recalculate and return the arclength, resets nodecnt also
    double CalcArcLength() ; 

    //! Re-calculates arclength if CS_ARCLENGTH_VALID is not set
    /*!
        \return the arclength of the curve

        If the statflag bit CS_ARCLENGTH_VALID is not set then this 
        calls CalcArcLength(). 
     */
    double ArcLength() ; 

    //! Re-arranges the curve so that node pnewStart is the new start node
    /*!
        \param pnewStart pointer to the segment that should define the start of the curve

        This routine simply modifies the pStart and pEnd pointers as well as 
        the prev and next pointers for the old and new start and end segments
        to that the overall curve is now linked from the pnewStart segment. 
        The uo values will all be invalid after this call, unless the 
        pnewStart==pStart since in that case nothing happens (the function tests
        for this condition on entry and returns without doing anything in this
        case). 
    
        Note: this should only be used on closed curves.
     */
    void SetStartSegment(CS_Segment* pnewStart) ; 

    //! re-arranges the curve so that the point at u becomes the new start of the curve
    //! Note: this should only be used on closed curves
    void SetStartPoint(double u) ; 
    
    //! Returns area of closed curve CCW = +ve area, CW = -ve area
    /*!
        Returns the enclosed area of a closed curve. If the curve
        is not closed zero is returned. The area function does 
        a loop integral and adjusts the sign so that a CCW oriented
        curve will generate a positive area, and a CW oriented 
        curve a negative area. SetDirection() calls the Area() 
        function to figure out which way the curve is directed. 
     */
    double Area() ; 
    
    //! calls CalcArcLength and then SetUParameters
    void Finalize() ; 

    //! calls Finalize(), SetDirection() and SetParentPointers(), skips direction
    //! setting if direction < 0
    void Complete(int direction=CCW) 
    { 
        Finalize() ;
        if (direction >= 0)
            SetDirection(direction) ; 
        SetParentPointers() ; 
    } ;


    //! Sets the uo parameters for each segment 
    void SetUParameters() ; 

    //! Calculates the arclength of the curve projected onto the XY plane
    /*!
        Note that the projection direction is fixed along the Z axis. This 
        is useful if you have a curve with varying Z components and you 
        need to know the linear distance travelled on the XY plane with
        no height variations. 
     */ 
    double CalcXYArcLength() ; // recalculate and return the arclength

    //! returns the value of XYarclength, 
    /*! 
        XYarclength is not maintained as the curve is built, thus only call
        this function with calc false if CalcXYArcLength() has been called.
        If calc is true then it calls CalcXYArcLength() before returning 
        the value of XYarclength.
     */
    double XY_ArcLength(int calc = 0) ; 

    // TODO remove all these math functions from CS_Curve and simply make them 
    //      stand alone. AreaMomentOfInertia(), AreaProductOfInertia(), 
    //      PrincipalAxis(), 

    //! Returns the line centroid of the curve, arclength must be valid upon entry
    /*!
        This function returns the line integral based centroid of the curve
        using the definition:
        \latexonly
            \begin{center}
            $ \overline{x}=$ \scalebox{1.5}{$\frac{\int_{C} x(t) |\mathbf{r}'(t)|dt}{\int_{C} |\mathbf{r}'(t)|dt} $}
                \, \, and \, \, 
            $ \overline{y}=$ \scalebox{1.5}{$\frac{\int_{C} y(t) |\mathbf{r}'(t)|dt}{\int_{C} |\mathbf{r}'(t)|dt} $}
            \end{center}
        \endlatexonly
     */
    CS_POINT Centroid() ; 

    CS_POINT Centroid2D() ; // arclength must be valid when this is called

    // Returns the Area centroid of the closed curve, if the curve is open
    // then the point [0,0,0] is returned
    CS_POINT AreaCentroid() ;

    // returns OK=0 if the values were set correctly, otherwise returns
    // an error code 1=open curve, 2=zero area. If pcentroid is not NULL
    // then I = Io + Ad^2 is used to shift moment relative to that coord
    // which typically would be the centroid. 
    int AreaMomentOfInertia(double &Ix, double &Iy, CS_POINT *pcentroid=0) ;


    // Returns 1 if curve not closed (error code=1) and Ixy is not changed, 
    // else returns OK and the Ixy value is set.
    int AreaProductOfInertia(double &Ixy, CS_POINT *pcentroid=0) ;

    // Returns the principal axis angle for Imax, Imin is simply 
    // Imax rotated 90degress
    // The determiniation of Imax and Imin is based on the formulas
    //  Imax = (Ix+Iy)/2 + 0.5*sqrt((Ix-Iy)^2 + 4*Ixy^2)
    //  Imin = (Ix+Iy)/2 - 0.5*sqrt((Ix-Iy)^2 + 4*Ixy^2)
    // Also:
    //  Ix'=(Ix+Iy)/2 + (Ix-Iy)/2*cos(2a) - Ixy*sin(2a)
    //  Iy'=(Ix+Iy)/2 - (Ix-Iy)/2*cos(2a) + Ixy*sin(2a)
    // 
    //  Ixy' = (Ix-Iy)/2*sin(2a) + Ixy*cos(2a)
    //
    // The ' components are the resultant values with a rotation
    // of the axes through an angle a.
    // The Imax and Imin values occur at the critical angle b as
    // defined by the equation below. Solving for b will generate
    // 2 results 90 degrees apart. 
    //  tan(2b) = 2Ixy / (Ix - Iy)
    CS_VECTOR PrincipalAxis(int mode=CS_MINIMUM) ; 


    double ULength(CS_SegPtr psn) ; // the u delta for the segment
    // uo parameters must be valid

    // length of segment in terms of U, same as above. 
    double SegmentULength(CS_SegPtr psn) ; 


    //! The udelta from a to b
    /*!
        \param ua start point u value
        \param ub end point u value
        \return u distance from ua to ub in range [0,1]

        For closed curves ua > ub is valid since the routine will 
        calculate the ulen wrapping through the end/start point. If the 
        curve is open and ua > ub, then (1.0-ua) is returned and ub
        is ignored. If (ua == ub) within the system tolerance, and 
        the curve is open, then 0 is returned, and if the curve is 
        closed then 1 is returned. 

        Note: the Closed() function must have been called to set the 
        CS_CLOSEDCURVE statflags bit  properly before calling this function. 
     */
    double ULength(const double &ua, const double &ub) ; 

    //! The u length between the two points
    /*!
        \param cpfrom start point u value (a)
        \param cpto end point u value (b)
        \return u distance from a to b in range [0,1]

        This version behaves somewhat differently in that no 
        consideration is given to whether a curve is open or closed. 
        This function always walks past the end of the curve and 
        loops back to the start even on open curves. If the points
        are the same on entry then 0 is returned (with some possible 
        error since the routine actually calculates the zero distance
        and doesn't test for the exact equal points condition). 

     */
    double ULength(const CS_CrvPnt &cpfrom, const CS_CrvPnt &cpto) ;

    
    double ArcLengthToDeltaU(double alen) ; // converts the input value
    // from a length to a u delta value.

    //! Convert the u range to an arclength distance. 
    /*!
        \param uo the starting u coord to measure distance from
        \param uf the end u coord to measure distance to.
        \return the arc length from uo to uf

        If the curve is closed and uo > uf then the distance measured wraps
        around through the start of the curve up until the uo point, and 
        if the uo < uf then the arc length of the section [uo,uf] is returned. 
        If the curve is opened and uo < uf then that section length is returned
        otherwise the length from uo to 1.0 is returned since you can't wrap 
        around on a closed curve. 

        In both open and closed curves cases, if uo == uf within the 
        system tolerance then 0 is returned. 

        Note: the function Closed() must have been called in 
        order for the state of the closed flag to be valid 
        before calling this function. This can be accomplished by calling the 
        Complete() function. 
     */
    double DeltaUToArcLength(const double &uo, const double &uf) ;

    //! Return u value half way between ua and ub
    /*!
        \param ua the start u value
        \param ub the end u value
        \return u value that is half way in between ua and ub 

        This returns the midpoint that is half way in between ua and ub moving
        in the direction from ua to ub. If the curve is open then ua < ub must 
        hold in order for this to work correctly. If the curve is not open,
        the function ignores this fact and simply returns a point half the 
        u distance along the curve in between ua and ub
     */
    double UMid(const double &ua, const double &ub) ; 
    
    double UMidShortest(const double &ua, const double &ub) ; 

    //! Returns true if u is within the range ua -> ub or on the endpoints
    /*!
        \param u the point on the curve to test
        \param ua start of the range
        \param ub end of the range
        \return true if u is inside the range [ua,ub]

        If the curve is closed the ua > ub is valid on input. If the 
        curve is closed then ua < ub must be true in order for the 
        result to be true. 

        The u value can be equal the ua or ub endpoints within the current
        tolerance and will still return true. 

     */
    int UOnSection(double u, double ua, double ub) ; 


    //! Returns true if u is within the range ua -> ub but not on the endpoints
    /*!
        \param u the point on the curve to test
        \param ua start of the range
        \param ub end of the range
        \return true if u is inside the range (ua,ub)

        If the curve is closed the ua > ub is valid on input. If the 
        curve is closed then ua < ub must be true in order for the 
        result to be true. 

        The u value cannot equal the ua or ub endpoints within the current
        tolerance in order to return true. 
     */
    int UInSection(double u, double ua, double ub) ; 


    CS_VECTOR UTangent(double u) ; 
    
    //! ux value is w.r.t. the segment pn
    //! Returns tangent a distance FBepsilon in the forward direction on the segment
    CS_VECTOR TanVectorForwards(CS_SegPtr pn, double ux, double epsilon=FBepsilon) ;


    //! ux value is w.r.t. the segment pn
    //! Returns tangent a distance FBepsilon in the reverse direction on the segment
    CS_VECTOR TanVectorBackwards(CS_SegPtr pn, double ux, double epsilon=FBepsilon) ;

    //! Tangent looking forwards on curve at the point specified
    /*!
        \param pn segment pointer at point to determine tangent at
        \param ux u coordinate in segment terms (not the overall curve u point) 
        \param epsilon tolerance factor for testing ux for equality to 0 or 1.
        \return the tangent vector at the point

        The difference between this function and \a TanVectorForwards is that the tangent
        isn't taken at the distance epsilon from the point {pn,ux} but instead at the 
        exact point. There is a test however to see if the point designated by {pn,ux}
        is the end point of a segment, such as on the corner of two connecting segments
        that are not continuous at the end point. So at the corner of a square for example
        the tangents are 90 degrees from each other. In this case the forwards direction
        tangent will be on the side in the forward direction, and the reverse will take
        the tangent at 90 degrees respectively. 


            P--------->>-------------
            |
            |
            |
            ^
            ^
            |
            |
            |

        Thus for the above example where the point P is where we want the tangent, and the 
        ^^ >> marks indicate the curve direction, this would return a vector of (1,0,0)

     */
    CS_VECTOR TanVectorForwardsExact(CS_SegPtr pn, double ux, double epsilon=COMPARETOLERANCE) ;


    //! Tangent looking backwards on curve at the point specified
    /*!
        \param pn segment pointer at point to determine tangent at
        \param ux u coordinate in segment terms (not the overall curve u point) 
        \param epsilon tolerance factor for testing ux for equality to 0 or 1.
        \return the tangent vector at the point

        The difference between this function and \a TanVectorBackwards is that the tangent
        isn't taken at the distance epsilon from the point {pn,ux} but instead at the 
        exact point. There is a test however to see if the point designated by {pn,ux}
        is the end point of a segment, such as on the corner of two connecting segments
        that are not continuous at the end point. So at the corner of a square for example
        the tangents are 90 degrees from each other. In this case the forwards direction
        tangent will be on the side in the forward direction, and the reverse will take
        the tangent at 90 degrees respectively. 


            P--------->>-------------
            |
            |
            |
            ^
            ^
            |
            |
            |

        Thus for the above example where the point P is where we want the tangent, and the 
        ^^ >> marks indicate the curve direction, this would return a vector of (0,1,0)

     */
    CS_VECTOR TanVectorBackwardsExact(CS_SegPtr pn, double ux, double epsilon=COMPARETOLERANCE) ;

    //! Takes mid vector of right perpendicular vectors ueps on either side of u 
    CS_VECTOR RightBisector(const double &u, double ueps=0.00000025) ; 
    CS_VECTOR RightBisector(CS_CrvPnt &cp, double ueps=0.00000025) ; 

    //! Takes mid vector of left perpendicular vectors ueps on either side of u 
    CS_VECTOR LeftBisector(const double &u, double ueps=0.00000025) ; 
    CS_VECTOR LeftBisector(CS_CrvPnt &cp, double ueps=0.00000025) ; 
    
    // Offset related routines
    void Offset1(double delta) ; // simply segment by segment offset
    void Offset2(double delta) ; // Offset1 with arc insertion
    void OffsetWithReflexArcs(double delta) ;
    
    
    //! Offset the base curve by the distance delta
    /*!
        \param delta the amount to offset the curve
        \param crvset the resultant collection of offset curves
        \param offsetmode controls how the offset is performed
        \return Error code, 0 if no error.

        Full machining style offset. If a curve is closed, then a closed curve
        offset is performed. If the offsetmode is set to CS_FORCEOPENOFS, and 
        the curve is closed, then the curve is treated as being open at the 
        start and end points. 

        Positive delta parameters offset open curves to the right, and negative
        deltas will offset open curves to the left. If the curve is CCW and 
        closed then a positive delta offsets the curve out, such that the area 
        contained is increased, assuming that the curve is not self intersecting. 
        A negative offset of a closed curves shrinks the shape. If a curve is 
        closed and the CS_FORCEOPENOFS mode is specified then the delta 
        specifies a +ve=right or -ve=left offset, just as for normal open 
        curves. If the curve is actually open, then the offsetmode parameter 
        has no effect.

        Offset sets the curve direction to CCW for any closed curves where the
        CS_FORCEOPENOFS mode is not specified.

     */
    int Offset(double delta, CS_CurveSet &crvset, int offsetmode=0) ;
    
    // int OffsetSlow(double delta) ;
    //! Offset using a slower more reliable method. 
    /*!
        This method is only useful for non-selfintersecting open curves. Or any
        type of closed curve (still have to fully test the closed curve case). 
     */
    int OffsetSlow(double delta, CS_CurveSet &curveset, double *ptolerance=0, CS_CurveSet *pfailedset=0) ;
    
    // \todo Remove these operators out of the class. They should be part of separate functions
    // Boolean operators
    int Union(CS_Curve *pcrvB, CS_CurveSet &resultSet) ;
    int Intersection(CS_Curve *pcrvB, CS_CurveSet &resultSet) ;
    int Difference(CS_Curve *pcrvB, CS_CurveSet &resultSet) ;

    void ClearChaining() ; 

    // SequentialSegments() is used in the offsetting logic
    int SequentialSegments(const CS_CrvPnt *pcpa, const CS_CrvPnt *pcpb, double *compTol=0) ;

    int Closed(double *ptol=0) ; // returns true or false to indicate curve is closed

    ///////////////////////////////////
    // Geometry processing routines  //
    ///////////////////////////////////
    //! Returns the number of segments deleted
    int MergeCollinearLines() ;
    
    // Fuse together those segments which can be joined without modifying
    // the overall curve. Thus we are attempting to minimize the number
    // of segments required to represent the curve. 
    int Simplify(double *tolerance=0) { return 0 ; } ; // TO DO 

    // Returns the number of segments deleted
    int DeleteShortSegments(double minLength) ; 

    //! Convert flat arcs to lines
    /*!
        \param chtol chord height tolerance for line conversion
        \param copyuser when true the pUserData pointer is copied also
        \return the number of arcs that were converted to lines

        The chord height of each arc is tested and if it is less than 
        chtol (does not use tolerance in the comparison) then the 
        arc is converted to a line . If copyuser is false, then the pUserData
        pointer is not copied to the new line segment is created. The default
        is true which copies the pUserData to the line segment. 
     */
    int ConvertFlatArcs(double chtol, int copyuser=1) ; 

    //! Chamfer the corner psna, psna->next
    /*!
        \param psna the first segment to chamfer
        \param dista chamfer distance on segment psna
        \param distb chamfer distance on segment psna->next (0=dista)
        \return 0=success, else a failure code is returned

        Attempts to chamfer the psna segment and the one following it.
        The chamfer distance is how far back from the end point of that
        segment that chamfer line is made. This distance is in arc length
        units and not u value units. 
     */
    int Chamfer(CS_SegPtr psna, double dista, double distb=0.0) ; 

    //! Fillet all non-tangent corners in the curve with the specified radius.
    /*!
        \param frad fillet radius
        \param minfrad minimum fillet radius
        \param divfactor fillet radius divide factor
        \param searchfillet not implemented yet
        \return The number of corners that could not be filleted. 

        Attempts to fillet all the corners within the entire curve. If the 
        curve is closed, the start and end segments are also filleted if
        possible. A fillet will fail if the radius frad specified 
        completely consumes either of the adjacent line segments. In
        this situation, if minfrad is specified, then the fillet radius 
        is divided by the divide factor and an attempt is made to fillet
        the radius again. The function keeps dividing the fillet radius
        until the fillet succeeds or 10 times the current tolerance is 
        reached for the fillet radius. A minfrad greater than 0 must be 
        passed in for this behaviour. Also, divfactor must be greater
        than 1 within the system tolerance. If either of these 
        conditions does not hold then the node loop attempting to 
        fillet with progressively smaller rads will not be performed.

        Note: searchfillet is not implemented yet since the actual results 
        are less than desireable under all conditions. If you absolutely 
        must have every corner filleted, then the best method is to offset
        the curve in 3 steps once by -frad, then that curve by frad*2 and then
        that final curve by -frad again. This will ensure that there are no
        corners left in the final shape, and that every curve will be filleted
        with a radius of at least frad. 
     */
    int Fillet(double frad, double minfrad=-1.0, double divfactor=2.0, int searchfillet=0) ; 
    
    int Fillet3D(double frad, double minfrad=-1.0, double divfactor=2.0) ; 

    //! Fillets the corner connecting two adjacent segments
    /*!
     \param psna pointer to the base segment to fillet
     \param frad fillet arc radius
     \param searchfillet controls search operation, see below
     \param status if not NULL returns status info about fillet operation
     \return pointer to the arc fillet created if any

     This function fillets the segment pointed to by psna with the next
     segment in the curve list. If the curve is closed and the last
     entry in the curve list is passed in, then the routine attempts to fillet
     the last segment with the first segment. If a fillet is impossible
     due to the fact that the rad is too large and will consume the next
     segment then the next segment afterwards is checked to see if a
     fillet can be formed with that segment and so on until the end of
     the list is reached in an open boundary or until the routine reaches
     itself in the case of a closed boundary. If no fillet can be created
     then the fillet operation is not performed. The fillet arc is
     inserted into the curve list after the psna segment and nodes are
     deleted and adjusted as required.
     
     status
        - 0x0000 0001 CS_FILLET_SEGMENTS_TANGENT, no fillet
        - 0x0000 0002 CS_FILLET_ZERO_RADIUS,      no fillet

     If the searchfillet parameter is false, then the fillet is only
     performed if the current segment and the one immediately following
     it can be filleted. If the segments are tangent or the rad is too
     large to do the fillet then nothing is done and NULL is returned.
     A pointer to the CS_ArcSeg node inserted in the curve is returned
     when a fillet operation is performed
     searchfillet is defaulted to false.

     TO DO - add the searchfillet capability, maintain uo value in the segnode
	       as we modify the curve, so that uo is always valid

     searchfillet not implemented yet.   
     */
    CS_SegPtr FilletSegments(CS_SegPtr psna, double frad, int searchfillet=0, int *status=0) ;


    CS_SegPtr FilletSegments3D(CS_SegPtr psna, double frad, int searchfillet=0, int *status=0) ;

    //////////////////////////
    // File access routines //
    //////////////////////////
    // TO DO - convert these to DXF routines
    int ReadFromFile(FILE *fptr) ; // appends the curve defined in the file 
    void WriteCurveToFile(FILE *fl, int prec=12) ; // append curve data to open file
    void PrintCurve(int endpoints=0, FILE *fp=0) ; 
    void Print(int endpoints=0, FILE *fp=0) ;

    ///////////////////////////////////////
    // Intersection and chaining support //
    ///////////////////////////////////////
    // Find intersection points with the curve. The number of points found 
    // is returned. If no points found then pnts is not allocated. 
    int Intersect2D(CS_SegPtr pseg, CS_IRECList *pirlist) ;


    //! Intersect two curves with each other. 
    /*!
        \param pcrv the other curve to intersect with
        \param pirlist pointer to the resultant intersection set
        \return the number of intersection points.
        
        Each segment of the base curve is intersected with each segment 
        of the pcrv curve. If one of the segments intersects a curve
        at an endpoint, then two intersections will result since the
        two adjoining segments will each intersect the other curve. Thus
        it is possible to generate 4 intersections which are really all 
        same point if all segments cross at a common endpoint. Call
        the function CS_DeleteCommonIntersections() on the pirlist that
        is returned to eliminate all the duplicate intersections if 
        required.
     */
    int Intersect2D(CS_Curve *pcrv, CS_IRECList *pirlist) ; 

    /*!
      The following use the older style CS_ISectSet, should use the
      above intersection routines which make use of CS_IntersectList.
     */
    // int Intersect2D(CS_Curve &crv, CS_ISectSet &irlist) ; 
    // int Intersect2D(CS_SegPtr pnode, CS_ISectSet &irlist) ;
    // int Intersect2D(CS_ArcSeg &cas, CS_ISectSet &irlist) ;
    // int Intersect2D(CS_LineSeg &cls, CS_ISectSet &irlist) ;

    
    //! Intersect the segments within the curve with itself. 
    /*!
        \param direction Mode to call Complete() function with CW, CCW, or NODIR
        \param islist the output list of non-contiguous intersections
        \param comptol value to override the compare tolerance on end point u values
        \return the number of self intersections found

        This routine intersects each segment in the curve with every other segment
        in the curve. The individual end to end intersections as you walk around 
        the curve are filtered out based on the compare tolerance. A figure eight 
        for example should return a single result assuming that the eight has two 
        straight lines that intersect at their midpoints. The compare tolerance
        allows some flexibility in terms of how exact the end points must match 
        the exact end point of the segment. This is important with certain arcs
        since a low compare tolerance when intersecting arcs, can result in a 
        tangent intersection that is slightly different than the actual end point
        of the arc. In this case the u test internally requires a compare tolerance
        that is a couple order of magnitudes larger (less restrictive) so comptol
        would be 100 or 1000 times greater than COMPARETOLERANCE for example. 

        Sometimes including tolerance in a calculation is a blessing and at other
        times it is a curse - this is important to keep in mind. 
     */
    int SelfIntersect(int direction, CS_IRECList &islist, double *comptol=&COMPARETOLERANCE) ;


    //! Tests whether or not two curves are similar
    //! by checking if the segments within the two curves are similar.
    /*!
        \param crvb - the curve being compared against
        \param psnstart - start segnode on the B curve
        \param refPntthis - Optional default=0 (or NULL)
                    a reference point to be used in testing
                    the distance to the end point of the segment on the
                    base *this curve. This distance is compared against
                    the equivalent distance obtained from the B curve 
                    reference point to the end point of the segment on 
                    the B curve
        \param refpntB - Optional default=0 (or NULL)
                    reference point used in testing equivalent
                    distances to the base *this curve. The distance from
                    this reference point to the end point of the B 
                    segments is tested. 
        \return  1 if the two curves are similar over their entire length,
                 0 if any mismatches occur.

        The segment type and arclength of each segment is tested and if
        both match for all segments in the curves then they are similar.
        The tangent vector's angle between the connect segments is not 
        tested, thus this is not a very rigorous test. If the reference
        points are defined, then a slightly more rigorous similarity is
        tested for. 
     */
    int Similar(CS_Curve &crvb, CS_SegPtr psnstart,
                CS_POINT *refPntthis=0, CS_POINT *refpntB=0) ;
    
    //! For two similar curves, match the start point of the second curve
    /*!
     \param cb       the curve to match up.
     \param prefthis a reference point on the *this curve
     \param prefb    a reference point on curve B
     \return One of the following:
        <ul>
        <li>0=curve matched successfully
        <li>1=the number of segments in each curve were not the same
        <li>2=arclengths of the two curves were different
        <li>3=segments could not be aligned 
        </ul>

     Output: cb is modified so that it's startpoint matches *this.

     Assumes that two curves are passed in that are identical in shape
     but are represented differently. This would occur for example if the
     curves were being built from imported CAD data, and arbitrary 
     chaining start points were used, with the desired end result being
     testing for similar shapes in the input data. 

     Operation: The segments are sorted by type and arc length in order to
     try and quickly find a matching start point for the second curve. If 
     after the sort no unique element is found in the sorted list, then 
     the time spent performing the sort is effectively wasted, and an order
     n^2 search is used. After the search further testing is done if
     the reference points are defined. 


     Notes:

        The two reference point requirements are not necessary, unless the two
        curves are symmetrical (and identical obviously). Thus there would be
        more than one point along the B curve where you could start walking and
        match exactly to the base curve (or another way of stating this is that
        there are multiple different transformations that would map B onto 
        *this. Two squares for example, can map matched in four different ways
        since each side is identical and thus there is no way to distinguish
        which orientation is the correct one. If this does not matter, then 
        do not pass values for prefthis and prefb. If it does matter, then 
        prefthis and prefb can be passed in to further control the reverse
        mapping. Note that the location of these points has to lie somewhere 
        other than the centroid of the overall shape. If the shapes are not
        symmetrical, and a unique transformation is found based on the segments
        within the shapes, then prefthis and prefb are not used even if they
        are defined. 

        It only makes sense to apply this function to two closed curves, if the
        curves are open then moving the start point is impossible.
        
        If 0 is returned then a call to Similar(...) will return true.
     */
    int MatchCurveStartPoints(CS_Curve &cb, 
                              CS_POINT *prefthis = 0, // XForm ref pnt
                              CS_POINT *prefb = 0) ;  // XForm ref pnt



    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    // CAD style control functions, allows for splitting (or putting an
    // endpoint node into the curve at that u point), removing sections
    // out of a curve, copying sections of a curve. Chopping a curve 
    // (dividing into separate pieces without removing any portions of
    // the original)
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////

    // returns segment who's sp=split point, if pnt is not null it is set 
    // to the split point. Note, pnt must be a pointer to a valid CS_POINT
    // with memory already allocated. Make sure SetUParameters has been 
    // called before calling split (or make sure that you're CS_Segment uo's
    // are valid based on where the curve is to be split  
    CS_SegPtr Split(double u, CS_POINT *pnt=0) ; 

    // returns segment who's sp=split point, if pnt is not null it is set 
    // to the split point. Note, pnt must be a pointer to a valid CS_POINT
    // with memory already allocated. Make sure SetUParameters has been 
    // called before calling split (or make sure that you're CS_Segment uo's
    // are valid based on where the curve is to be split  
    CS_SegPtr Split(CS_CrvPnt &cp, CS_POINT *pnt=0) ; 


    // Break the curve by removing the section of the curve from u1 to u2.
    // If the curve was closed then the new start segment is the segment
    // on the curve who's start point is at the u2 point. If the curve
    // is originally open, then a second curve is generated. The second
    // curve starts at the original curves u2 point. crv2 will be assigned
    // to this second curve. If the curve is closed crv2 is not used. 
    // If crv2 is set then true is returned, otherwise false is returned.
    // The contents of crv2 are destroyed before it is updated.
    int Break(double u1, double u2, CS_Curve &crv2) ; 
    int CopySection(double u1, double u2, CS_Curve &crv2) ; 
    void Divide(CS_SegPtr pdivseg, CS_Curve &crv2) ;

    //! Split the segment at the curve point thus adding one extra
    //! segment to the curve. Returns pointer to the new segment
    //! returns null if the CrvPnt is already on a segment endpoint
    CS_SegPtr SplitSegment(CS_CrvPnt &cp) ; 


    //! Slice a closed curve into two where p1->p2 defines the cutting line
    /*!
        \param p1 first cut point
        \param p2 second cut point
        \param pslice the new curve, or the sliced off section. 
        \return 0=OK, else error code

        If the input curve is not closed then this does nothing. 

        Say the input curve looked like this and the 1 2 are the slice points


                     *******1***** 
                  ***              ****
                **                     *
               *                       *
               *                       *
               *                       *
               *                       *
               S                       *
               *                       *
               *                       *
                *                       **
                  **                       ****
                      **                        *
                         ***2*                    *
                              ***                  *
                                  **                *
                                    *               *
                                     *******       *
                                            *******                       

        Then after the operation we will end up with two curves that look like this
        where the two curves have effectively been sliced apart. 


                    ********  ****** 
                  ***      *  *      ****
                **         *  *           *
               *           *  *           *
               *           *  *           *
               *           *  *           *
               *           *  *           *
               *           *  *           *
               *           *  *           *
               *           *  *           *
                *          *  *            **
                  **       *  *               ****
                      **   *  *                    *
                         ***  **                    *
                                ***                  *
                                    **                *
                                      *               *
                                       *******       *
                                              *******                       


        Note: for doing this with polygons there is a simple process 
        using a point walk algorithm in Geom Algo's RR-Vol5 pg 77. 
     */
    int Slice(CS_CrvPnt &p1, CS_CrvPnt &p2, CS_CurvePtr &pslice) ; 
    

    ///////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // CopySection routines assume that uo values are correct on entry
    ///////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // CopySections make a copy of the curve section requested and then 
    // return a pointer to the curve section created. This must be later
    // de-allocated with delete since a (new CS_Curve) is what generates
    // the CS_Curve pointer is returned. The mode parameter refers to 
    // whether the u values are relative to the segments or the overall
    // curve. Default value of 0 means relative to overall curve. A
    // value of mode==1 means relative to the individual segments
    CS_Curve *CopySection(CS_SegPtr psa, CS_SegPtr psb, 
                          double ua, double ub, int mode=CURVEBASED_UVALUES) ; 
    
    //! Copy section of the curve and return a new curve
    /*!
        \param cpstart the start point of the section to copy
        \param cpend the end point of the section to copy
        \param dir whether we want the section in the forward or reverse direction
        \return pointer to the newly generated curve section. Caller is responsible
        for freeing the newly created returned curve with \a delete

        The dir parameter controls whether the section is copied in the forward 
        or reverse direction, where the default is forward. If cpa is past cpb 
        on the curve and the direction is forward then the curve section wraps
        through the start/end point (1.0->0.0) part of the curve. Likewise 
        the 0.0->1.0 section is crossed in reverse as required.  If the 
        curve is open however and an attempt is made to extract a section 
        past an endpoint then the copied section stops at the end point.
        This is to avoid having a disjointed curve returned.

        To clarify the cpstart and cpend parameters, cpstart is the location
        on the *this curve that will become the start point of the resultant
        copied section. Similarily cpend is the location on the *this curve
        that will become the end point of the resultant copied section. For
        both these cases when CS_REVERSE is used as the direction, the 
        copied section will go in the reverse direction to the *this curve.

     */
    CS_Curve *CopySection(const CS_CrvPnt &cpstart, 
                          const CS_CrvPnt &cpend, 
                          int dir=CS_FORWARD) ;

    //! Copy the section of the curve defined by the region ua->ub
    /*!
        \param ua the starting point to copy from
        \param ub the end point to copy to
        \return pointer to the newly copied curve section. If an error 
        occurs then NULL is returned.

        The direction is in the forward direction only, thus if ub < ua then 
        two outcomes are possible. If the curve if open, then the resultant
        curve will be the curve section from [ua,1] since the end point
        will not be passed. If the curve is closed then the curve section
        will be [ua,1,0,ub] since the copy process will walk through the 
        end/start point on the curve. If you need the resultant curve 
        to be reversed then call presultCurve->Reverse() to reverse the 
        direction of the resultant curve. The calling function is repsonsible
        for deleting the returned pointer with 'delete presultCurve ;' since
        the new operator is used to allocate the CS_Curve.
     */
    CS_Curve *CopySection(double ua, double ub) ; 


    //! Trimming mode bit flags
    /*!
        The TRIMA and TRIMB mode flags are used to indicate what part of the
        CS_IREC intersection record to use as the trim point. When two ends
        are being trimmed (meaning you need two CS_IREC's to define the two trim
        points) then TRIMA flags refer to the first trim point and TRIMB flags
        refer to the second trim point (second CS_IREC). The PRI/SEC and 0/1 
        extensions then further define what part of the CS_IREC definition
        to use in the trim. PRI indicates the use of primary records or stated
        another way the base segment/curve in the intersection pair, while
        SEC means the secondary segment/curve in the intersection pair (the
        parameter pased to the base intersection member function). The 0/1 
        extension designator refers to the 0 or 1 array index in the intersection
        record definition. The 1 index array position only applies if there
        is an overlap intersection, since in non-overlap intersections the
        1 index variables are undefined. For example, in the following code
        block \a arca is intersected with \a lineb and the arc is then trimmed
        to the two intersection points along the arc. 

        \verbatim
        // Defining semicircular arc at origin from 0 to 180 degrees
        CS_Curve crva, crvb ; 
        CS_ArcSeg *pas = new CS_ArcSeg ;
        pas->rad = 10.0 ; 
        pas->sa = 0 ; 
        pas->swp = RADIAN180 ;
        pas->ctr = CS_POINT(0,0,0) ; 

        CS_LineSeg *pls = new CS_LineSeg(CS_POINT(-20,5,0), CS_POINT(20,5,0)) ; 

        crva.Append(pas) ; 
        crvb.Append(pls) ; 

        crva.Complete() ; // sets parent pointers, not specifically needed here
        crvb.Complete() ; // but good practice 

        CS_IRECList irl ; 
        crva->Intersect2D(&crvb, &irl) ;
        // The intersection generates two intersection records (non-overlapping)
        // at (-8.66,5) and (8.66,5)

        CS_IREC *p1stISect, *p2ndISect ; 
        CS_IRECListItr iri = irl.begin() ; 
        p1stISect = iri->pir ; 
        iri++ ; 
        p2ndISect = iri->pir ; 

        // To trim the arc ends at the two intersection points do
        crva.Trim(p1stISect, p2ndISect, CS_TRIMA_PRI0 | CS_TRIMB_PRI0) ; 

        \endverbatim

        The above is typically how the trimming functions will be used, but 
        for cases where there are overlap intersections then the SEC and possibly
        0/1 extensions come into play. Another example using intersecting lines
        that overlap (thus the lines are also collinear) follows.

        \verbatim
        CS_Curve crva, crvb ; 
        CS_LineSeg *pl1 = new CS_LineSeg(CS_POINT(-1,0,0), CS_POINT(1,0,0)) ; 
        pas->rad = 10.0 ; 
        pas->sa = 0 ; 
        pas->swp = RADIAN180 ;
        pas->ctr = CS_POINT(0,0,0) ; 

        // Note this segment is defined in the revsere direction to pl1
        CS_LineSeg *pl2 = new CS_LineSeg(CS_POINT(2,0,0), CS_POINT(-2,0,0)) ; 

        crva.Append(pas) ; 
        crvb.Append(pls) ; 

        crva.Complete() ; // sets parent pointers, not specifically needed here
        crvb.Complete() ; // but good practice 

        CS_IRECList irl ; 
        crva->Intersect2D(&crvb, &irl) ;
        // The intersection generates two intersection records (non-overlapping)
        // at (-8.66,5) and (8.66,5)

        CS_IREC *pir = irl.begin()->pir ; 
        // pir will be defined as follows
        //   pir->statinfo = OVERLAP | BREVERSED
        //   pir->cpp[0]  -->> pl1, u=0
        //   pir->cpp[1]  -->> pl1, u=1
        //   pir->cps[0]  -->> pl2, u=.75
        //   pir->cps[1]  -->> pl2, u=.25
        //   pir->ipnt[0] -->> {-1,0,0} 
        //   pir->ipnt[1] -->> { 1,0,0} 

        // Trimming the line ends of pl2 off that don't overlap pl1
        crvb.Trim(pir, pir, CS_TRIMA_SEC1 | CS_TRIMB_SEC0) ;
        // pay careful attention to what is happening here since it can be 
        // somewhat confusing.

        // Or another way to do the same thing
        // Note: because of the BREVERSED condition, we have to flip the 
        // order of the secondary CS_CrvPnts that get passed to the trim function
        //  crvb.Trim(&pir->cps[1], &pir[cps[0]) ; 

        \endverbatim
    
        See the description for \a CS_IREC for a more detailed description of 
        PRI/SEC, and 0/1 designations.  
    */


   
    //! Trim the start of the curve off (trim [0,u] section leaving the
    //! [u,1] section)
    void TrimStart(double u) ; 

    //! Trim the start of the curve off 
    /*!
        \param crvpnt curve point segment where trim point occurs

        The trim point is defined by referencing a specific segment within the
        overall curve. The useg value is with respect to the segment only and 
        not the complete curve, thus if the curve was made up of 3 line segments
        each of unit length and you wanted to trim off the first line segment you 
        could do TrimStart(pFirstSegment, 1.0) or TrimStart(pSecondSegment, 0.0),
        leaving a curve with two segments and an overall length of 2 units.
     */
    void TrimStart(const CS_CrvPnt *crvpnt) ; // trim off the start of the curve

    //! Calls TrimStart(const CS_CrvPnt *crvpnt)
    void TrimStart(const CS_CrvPnt &crvpnt) ; // trim off the start of the curve


    //! Trim the start of the curve off 
    /*!
        \param pir The intersection point to trim to
        \param mode The part of the intersection to use in determining 
        trim to point.
        \return Nothing

        The pointer pir to the intersection record CS_IntersectRec defines
        the trim point on the curve. Since an intersection record can defined
        a start and end (when overlap sections occur) you can specify whether
        the start of the intersection or the end of the intersection is used. 
        For intersections that are a unique point, then the start and end are
        the same so the mode default is safe. For overlap type intersections
        though you must specifiy whether to use the start of the intersection
        or the end with CS_TRIMA_PRI1. Intersection records also contain 
        information about the other curve that was intersected. If this 
        record refers to the other curve then the mode must be specified as
        CS_TRIMA_SEC0, or CS_TRIMA_SEC1 as required. 

        Code Example:
                
     */
    void TrimStart(const CS_IREC *pir, int mode=CS_TRIMA_PRI0) ;

    //! Calls TrimStart(const CS_IREC *pir, int mode=CS_TRIMA_PRI0) 
    void TrimStart(const CS_IREC &ir,  int mode=CS_TRIMA_PRI0) ;
    
    //! Trim end of the curve off, trims section [u,1] 
    void TrimEnd(double u) ; 

    //! Trims the end of the curve off starting at the point pcrvpnt
    void TrimEnd(const CS_CrvPnt *pcrvpnt) ; 

    //! Trims the end of the curve off starting at the point crvpnt
    void TrimEnd(const CS_CrvPnt &crvpnt) ; 

    //! Trims the end of the curve off 
    /*!
        \param pir intersection record defining the trim start point
        \param mode defines which part of the intersection record to use in the trim
     */
    void TrimEnd(const CS_IREC *pir, int mode=CS_TRIMA_PRI0) ;

    //! Trims the end of the curve off 
    /*!
        \param ir intersection record defining the trim start point
        \param mode defines which part of the intersection record to use in the trim
     */
    void TrimEnd(const CS_IREC &ir,  int mode=CS_TRIMA_PRI0) ;

    //! Trim the start and end of the curve off, leaves section \f$[u_1,u_2]\f$
    void Trim(const double u1, const double u2) ; 

    //! Trim start and end of the curve off
    /*!
        \param pcp1 1st trim point 
        \param pcp2 2nd trim point

        The section of the curve in between pcp1 and pcp2 is kept. The ends of
        the curve are trimmed (discarded). 
     */
    void Trim(const CS_CrvPnt *pcp1, const CS_CrvPnt *pcp2) ; 

    //! Trim start and end of the curve off
    /*!
        \param cp1 1st trim point 
        \param cp2 2nd trim point

        The section of the curve in between cp1 and cp2 is kept. The ends of
        the curve are trimmed (discarded). 
     */
    void Trim(const CS_CrvPnt &cp1,  const CS_CrvPnt &cp2) ; 

    //! Trim start and end of the curve off
    /*!
        \param pira 1st trim point intersection record  
        \param pirb 2nd trim point intersection record 
        \param mode defines which part of the intersection record to use in the trim

        The section of the curve in between pira and pirb is kept. The ends of
        the curve are trimmed (discarded). See discussion of the mode bit flags
        above for details on the trim operation.
     */
    void Trim(const CS_IREC *pira, const CS_IREC *pirb, int mode=(CS_TRIMA_PRI0 | CS_TRIMB_PRI0)) ;

    //! Trim start and end of the curve off
    /*!
        \param ira 1st trim point intersection record 
        \param irb 2nd trim point intersection record 
        \param mode defines which part of the intersection record to use in the trim

        The section of the curve in between cp1 and cp2 is kept. The ends of
        the curve are trimmed (discarded). See discussion of the mode bit flags
        above for details on the trim operation.
     */
    void Trim(const CS_IREC &ira, const CS_IREC &irb, int mode=(CS_TRIMA_PRI0 | CS_TRIMB_PRI0)) ;

   
    //! Connect up curve end points
    /*!
        \param pStartEndtol pointer to tolerance used in the Start/End closed test
        \return 0 if all curves already matched exactly, 1 if endpoints were
        modified somewhere in the curve

        Intended to be used to perform small adjustments to connect the end
        points of the segments within the curve exactly. For line segments this 
        will be true since a direct assignment of ep=sp from one curve to the
        next can be performed. Since arc segment end points are calculated, 
        the arc endpoints cannot be guaranteed to be exactly the same. The 
        function uses the arc end and midpoint to recalculate a start point
        that is taken from the previous segments endpoint. Thus repeated 
        calls to this function could return different results depending on
        the nature of the segments within the curve. Typically you would 
        use this after reading in curves from a secondary data source where
        the input data was rounded off somewhat. This function works by making 
        repeated calls to MatchEndPoints(). 
        
        After calling this function it is a good idea to call Finalize() to 
        make sure that all the u parameters along the curve are valid. The 
        reason is that MatchEndPoints() will slightly modify the end points 
        of the segments and then when doing intersection routines later on, if
        an intersection occurs at an end point of a segment, without corrected
        u values, the SequentialSegments() routine might not think that these
        segments are contiguous any more since the u velues don't match [0,1]
        or [1,0] within the system tolerance. 

        If pStartEndtol is null then the current default tolerance is used. 
     */
    int ConnectEndPoints(double *pStartEndtol=0) ; 

    //! Sets the minimum bounding box for entire curve
    /*!
        The bndrct member variable is set to the minimum bounding box 
        for the entire curve. 

        \image latex crvboundrect.eps "Example CS_Curve Bounding Rectangle" width=100mm
     */
    void SetBoundingRect() ; // sets the CS_RECT values
} ; 


//! Match the end points of the two connected segments.
/*!
    \param pa pointer to first segment to adjust
    \param pb pointer to second segment to adjust
    \return 1 if the segments were modified, 0 otherwise

    This function works by taking the pa end point and the pb
    start point and then calculating the midpoint of those
    two points. If the midpoint matches both pa->EndPoint() and 
    pb->StartPoint() then nothing is done to the two segments. 
    Otherwise pa->AdjustEndPoint(midpoint) and 
    pb->AdjustEndPoint(midpoint) are called so that the two 
    segments connect together properly. 
 */
int CS_MatchEndPoints(CS_SegPtr pa, CS_SegPtr pb) ; 


//! Return true if u points define same point on curve
/*!
    \param pcrv the base reference curve 
    \param u1 first parametric point on the curve
    \param u2 second parametric point on the curve
    \param tol pointer to tolerance value to be used instead of current default
    \return true if u1==u2 or (curve closed and (u1=0 and u2=1) or (u1=1 and u2=0))

    All tests are done using the current system tolerance. Thus it automatically
    handles closed curves where the two u values may be just saddling the start/end
    point of the curve.

    Note \f$u_1\in[0,1]\f$ and \f$u_2\in[0,1]\f$ must be valid. 
 */
int CS_SameCurveUPoints(CS_Curve *pcrv, double u1, double u2, double *tol=0) ;

//! Closest segment end point on the pcrv to the given cp point
CS_CrvPnt CS_ClosestEndPoint(CS_Curve *pcrv, CS_POINT &cp) ; 

//! Closest segment end point on the pcrv to the given u point on the curve
CS_CrvPnt CS_ClosestEndPoint(CS_Curve *pcrv, double ucrv) ; 


//! Returns true if the curve points are the same point on the same curve. 
int CS_CrvPntsEQ(CS_Curve *pcrv, CS_CrvPnt &a, CS_CrvPnt &b) ;

//! Returns true if the curve points are not the same point on the same curve. 
int CS_CrvPntsNEQ(CS_Curve *pcrv, CS_CrvPnt &a, CS_CrvPnt &b) ;



//! If count=0 then the pcrvs[] array is walked along until a NULL 
//! pointer is hit
void CS_FreeCurves(CS_Curve **pcrvs, int count=0) ; 


//! u distance from us to ue
/*!
    \param us start u point
    \param ue end u point
    \return u distance from us to ue
    
    Does the following:

    \verbatim
        if (us > ue)
            return 1.0 - us + ue ; 
        return ue - us ; 
    \endverbatim
    
    Thus it is assuming the curve is closed if ue > us since this is 
    the only time passing such a pair of values in would make sense. 
    
 */
double CS_UCrvDelta(double us, double ue) ; 


#define SEGALLOCBLKSIZE     50

//! Maintains a set of segments
/*!
    Uses realloc to maintain a dynamically growable list of segment
    pointers. This differs from \a CS_Curve which uses a doubly linked 
    list of \a CS_Segment's.
 */
class CS_SegmentList
{
public:
    CS_SegPtr *psl ;     //! main segment list pointer
    int nseg ;           //! number of segments in the list
    int nalloc ;         //! allocated size of the array

    CS_SegmentList()
    {
        psl = 0 ; 
        nseg = 0 ; 
        nalloc = 0 ; 
    }

    ~CS_SegmentList()
    {
        if (psl)
        {
            for (int i=0; i < nseg; i++)
            {
                if (psl[i])
                    delete psl[i] ; 
            }
            free(psl) ; 
        }
        psl = 0 ; 
        nseg = 0 ; 
        nalloc = 0 ; 
    }

    //! returns array index if added else returns -1
    int AddSegment(CS_SegPtr sp) 
    {
        if (nseg >= nalloc)
        {
            CS_SegPtr *sptmp = (CS_SegPtr *)realloc(psl, 
                        sizeof(CS_SegPtr) * (nalloc + SEGALLOCBLKSIZE)) ; 
            if (!sptmp)
                return -1 ; 
            psl = sptmp ; 
            nalloc += SEGALLOCBLKSIZE ; 
        }
        psl[nseg] = sp ; 
        return nseg++ ; 
    }
} ;


//! Free the segments in the array
void CS_FreeSegments(CS_SegPtr psegs, int nsegs) ; 

//! Add segment to the array
void CS_AddSegment(CS_SegPtr psegs, int nsegs) ; 

//! Returns true if the curve overlaps itself
/*!
    \param pcrv pointer to curve to be tested for self overlaps
    \return true if the curve has self overlapping segments

    The curve must be properly formed in that end point of each segment
    must match the start point of the next segment since only the two 
    adjoining segments are tested. Thus this runs in O(n) time maximum
    since worst case it must test all segments. 
 */
int CS_CurveOverlaps(CS_Curve *pcrv) ;

//! Removes all segments that overlap themselves and builds a single non-overlapping curve
/*!
    \param ptstcrv input curve to be tested and processed for overlaps
    \param pnewcrv output non-overlapping curve, caller must free this curve
    \param mode processing mode - not used yet
    \return error code, 0=success

    This function has not been tested and is not written very efficiently either 
    as it copies memory around quite a few times creating temporary storage, 
    although it does created a sorted array up front to minimize the intersection
    processing time. 

 */
int CS_RemoveOverlaps(CS_Curve *ptstcrv, CS_CurvePtr &pnewcrv, int mode) ;

//! Map the ulen from a curve to a segment (increases the ulen if seg part of crv)
double CS_CrvULen2SegULen(double ulen, CS_Curve &crv, CS_SegPtr &pseg) ;

//! Returns the closest u point in between two other u points. 
double CS_UMidShortest(double ua, double ub, int closed) ; 


//! Returns true if u is within the range ua -> ub or on the endpoints
/*!
    \param u the point on the curve to test
    \param ua start of the range
    \param ub end of the range
    \param isClosed means that ua and ub are points that are from a closed curve
    \return true if u is inside the range [ua,ub]

    If the curve is closed the ua > ub is valid on input. If the 
    curve is closed then ua < ub must be true in order for the 
    result to be true. 

    The u value can be equal the ua or ub endpoints within the current
    tolerance and will still return true. 

 */
int UOnSection(double u, double ua, double ub, int isClosed) ;

//! Returns true if u is within the range ua -> ub but not on the endpoints
/*!
    \param u the point on the curve to test
    \param ua start of the range
    \param ub end of the range
    \param isClosed means that ua and ub are points that are from a closed curve
    \return true if u is inside the range (ua,ub)

    If the curve is closed the ua > ub is valid on input. If the 
    curve is closed then ua < ub must be true in order for the 
    result to be true. 

    The u value cannot equal the ua or ub endpoints within the current
    tolerance in order to return true. 
    */
int UInSection(double u, double ua, double ub, int isClosed) ; 

#endif
