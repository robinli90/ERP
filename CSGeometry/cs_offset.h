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
// offset.h - definitions specific to the machining offset operation


#ifndef __OFFSET_H__
#define __OFFSET_H__

//! Used to store the segment information and rectangles 
struct CCISNode 
{
    int crvnum ;     // curve number that this segment belongs to
    CS_Curve *pcrv ;   // curve that the segment comes from. 
    CS_SegPtr psn ;  // the segment node
    int count ;      // this nodes count within Offset2 curve
    CS_RECT   rect ; // it's rectangle
} ;

// Used by call to qsort on the OfsISNode array
int OfsISNodeComp(const void *a, const void *b) ;



// Block of plist UEventRecords to reserve when space is needed
// to minimize the re-alloc calls
// Note: the block size can never be less than 4 since the logic
// requires that there be at least 4 empty entries available under
// certain conditions
#define UEVENT_ALLOCBLKSIZE         50

// Lower byte defines the type of record
// The high order bits store status information
#define UEVENT_TYPEMASK             0x000000FF
#define UEVENT_INTERSECTION         0x00000001
#define UEVENT_OVERLAP              0x00000002
#define UEVENT_INVERTARC            0x00000004


/*******************************************************************
    The primary intersection is set if this record is the primary 
    reference to the intersection definition. This means that the 
    A (or 1) parameters refer to the current segment and the B
    parameters refer to the segment elsewhere on the curve. If 
    The primary isect bit is not set then the sense of A and B
    are reversed. This saves time and memory since the curve is 
    self intersecting, there were always be two identical entries
    for every intersection event.

    The UEVENT_OVERLAPBREVERSE bit indicates that the overlap 
    section for the second overlap record goes in the reverse
    direction to the primary section. This means that if the 
    primary is an overlap start point then the secondary is an
    overlap endpoint.

*******************************************************************/
// The status UEVENT_PRIMARYRECORD can be regarded as (REFERS TO psna)
// and !UEVENT_PRIMARYRECORD equivalent to (REFERS TO psnb)
#define UEVENT_PRIMARYRECORD        0x80000000
#define UEVENT_STARTPOINT           0x40000000
#define UEVENT_CROSSOVER            0x20000000
#define UEVENT_TOUCHOFF             0x10000000
#define UEVENT_OVERLAPBREVERSE      0x08000000
#define UEVENT_DELETED              0x04000000 // ignore this event record
#define UEVENT_OVERLAPDELETED       0x02000000
#define UEVENT_LEFT                 0x00100000
#define UEVENT_RIGHT                0x00200000

#define UEVENT_OVERLAPSTARTPOINT    (UEVENT_OVERLAP | UEVENT_STARTPOINT)
#define UEVENT_REVERSED             (UEVENT_OVERLAPBREVERSE)


// Crossover definitions, as defined in lookup table
#define XOVER_XLR       1
#define XOVER_XRL       2
#define XOVER_TL        3
#define XOVER_TR        4

#define STARTPOINT_SEG   0x01 
#define ENDPOINT_SEG     0x02     

/*!
    This data is structured to speed up intersection set processing.
    The U event stores a specific change in conditions along an
    offset curve that is used to determine processing direction
    (what to do next) when reducing the raw offset data to a 
    set of closed curves. The various events (or conditions)
    that are stored are:
     1) intersect - two line segments physically cross at a 
        single point. All information related to both segments
        is stored
     2) overlap start - the start of an overlap section is 
        defined 
     3) overlap end - the end of an overlap section
     4) invert arc start - the beginning of an inverted arc
     5) invert arc end -   the end point of an inverted arc

 The UEvent defines the details to an intersection, overlap, or inverted
 arc section definition. For intersections, the u's define the intersect
 point along the two curves. u1 and u2 define the u point for the actual
 curve segment. ua and ub define the u values along the entire curve. The
 segnode pointers are used since we have to check if the segments are 
 adjacent in the list for various condition testing. For an overlap section
 two entries are created, one that defines the start of the overlap and 
 the second that defines the end of the overlap. The point where the 
 overlap starts or ends for both curves is defined by the u1,u2 and ua,ub
 pairs. For the start section ua defines the start point along the overall
 curve for the current section and ub defines the start point along the 
 overall curve for the secondary section. Because of the way that the 
 data is created ua < ub (u1 < u2) will always hold and the primary 
 secondary indicator bit is redundant but we maintain it here so as to 
 save the floating point compare operation. We've already done the 
 calculations so might as well simply save the status as a bit in the 
 type definition. For an inverted arc section, there will also be two
 records and events defined. One for the start of the arc and one for 
 the end. But in this case only u1,ua, and psna are defined. Since the 
 inverted arc only deals with itself we don't need to use all of the 
 parameters. For an inverted arc u1=0 will always hold and u2=1 will 
 always hold. The ua and ub values will define the range of the arc 
 along the overall curve. If the EventRecord pointing to the inverted
 arc definition has the UEVENT_STARTPOINT bit set then the processing
 logic will use the u1,ua values, whereas if the STARTPOINT is cleared
 then the end point values for the arc will be used. Note the only 
 thing that is actually done with an inverted arc end event is that the
 OnInvertedArc condition flag is cleared in the processing. Note
 however that then OnInvertedArcChainf flag will not be cleared at
 this point.

 When the UEVENT_STARTPOINT bit is set, it indicates that the event
 definition is for the start of that particular event obviously. This
 is only pertinent to overlap and inverted arc conditions. Actual 
 crossing intersections occur at a point, so a start/stop concept is
 meaningless in this case. 

 The UEVENT_CROSSOVER bit is set during a stage two pre-processing
 step, when it is determined how overlap/intersect occurs. It will be 
 defined both in the start and end overlap event records. If this 
 bit is not set for an overlap/intersection the event is a touch 
 off style, and does not actually cross sides. See RR-Vol1 pg151 for
 a diagram showing what is meant exactly by a crossover or a touch off.


    UEvent's are malloced and in memory as they are created. They never
    move and are cleaned up at the end of processing. They will be 
    referenced by more than one record. The primary record will be
    used in deleting the record when it is time to deallocate memory.

*/

struct UEvent
{
    CS_POINT pnt ;      // point where event occurs 
    int cnta, cntb ; // A and B segment counts
    
    // points on the segments where the intersects occur
    // these two u values are relative to the individual curve
    double u1, u2 ; 

    // these are the u values along the overall curve
    // where the intersections occur
    double ua, ub ; 
    
    CS_SegPtr psna ;
    CS_SegPtr psnb ; // pointer to segments that intersect
    CS_Curve *pca, *pcb ; 

    // index back to the primary UEventRecord in the plist[] array
    int primIDX ;

    // index back to the secondary UEventRecord in the plist[] array
    int scndIDX ; 

    // The status record is only used to store the CROSSOVER, TOUCH OFF,
    // LEFT, and RIGHT conditions so that we don't have to calculate these
    // twice for the same set of conditions (once for each UEventRecord)
    // If the UEventRecord is primary then status is interpreted as it is
    // defined, otherwise, the LEFT and RIGHT values must be reversed.
    int status ; 
} ;


// See the dicsussion regarding MergeScanAndDelete()  and TestMatchingEvent()
// as to why we have to carry around the actual event point.
struct UEventRecord
{
    unsigned long einfo ; // event type and status information
    double usort ;        // u value used for sorting records
    double u ;            // redundant but speeds processing
    UEvent *pevent ;      // pointer to event details
    // setCount used in the MergeOverlap and onwards
    int setCount ; // u value group set number

    // backward link to IndexRecord entries
    int irsIDX ; // index record that starts with this event
    int ireIDX ; // index record that ends with this event
} ;


// local parameters used to pass values to internal function within the 
// merge routine
struct MergeParameters
{   
    int setStartIDX ;  // index count when the u value changed
    int setCount ;     // current u event set count
} ;

class UEventList
{
public:
    
    UEventRecord *plist ; 
    // CS_Curve *pcrv ; // CS_Curve associated with the event list
    int listlen  ; // amount of memory actual used (# entries in the list)
    int alloclen ; // amount of memory allocated
    UEventList() ; 
    ~UEventList() ; 
    void ResetVars() ; 
    int *eventSets ;
    int numSets ; 
    
    // int (*sublist)[2] ;
    UEventRecord *ovlprecs ; 

    // alloc Event and EventRecord
    void DumpList(FILE *fp=0) ; 

    // UEvent *Append(int eventtype, UEvent &event) ; 
    UEvent *AppendPrimary(int eventtype, UEvent &event) ; 
    UEvent *AppendSecondary(int eventtype, UEvent *pevent) ; 

    int IsEndPoint(CS_Curve *pcrv, CS_SegPtr pseg, double useg) ;

    void OffsetIXEvent(CCISNode *pisn, int i, int j,
                       double *uvi, double *uvj) ;
    void OffsetOVLPEvent(CCISNode *pisn, int i, int j,
                         double *uvi, double *uvj) ;
    void OffsetInvArcEvent(CCISNode *pisn, int countiIn) ;

    // Boolean events are stored somewhat differently since each intersection
    // only generates one event and not two. We should probably clean this 
    // up in the future so that in the offset algorithm we end up making 
    // calls to an AddEvent() type function which returns a pointer to a 
    // a UEvent type. Then define an AddEvent(UEvent *, ...) which doesn't 
    // create a UEvent object
    UEvent *BoolIXEvent(CCISNode *pisn, int i, int j, double &uvi, double &uvj) ;
    UEvent *BoolOVLPEvent(CCISNode *pisn, int i, int j, 
                          double &uvi, double &uvj, int *evtype) ;

    void SortList() ; // sort event records by u value
    int EquivalentEvents(int i, int j) ;
    bool TestMatchingEvent(int i, int j) ;
    void MoveInvArcsToEnd(int ss, int se) ; // set start and end indexes
    int  MoveOverlapsToTop(int ss, int se) ; // set start and end indexes
    int MergeOverlaps() ; // merge overlap sections into continuous runs
    void MergeScanAndDelete(MergeParameters &mp, int i) ; 
    void LabelCrossovers() ;
    int IntersectionCrossover(int i) ; 
    int OverlapCrossover(int i, int j) ; 

    //! Used to grab tangent vector a small amount forward of event point
    CS_VECTOR VectorForwards(CS_Curve *pcrv, CS_SegPtr pn, 
                             double ux, int endstat) ;

    //! Used to grab tangent vector a small amount behind the event point
    CS_VECTOR VectorBackwards(CS_Curve *pcrv, CS_SegPtr pn, 
                              double ux, int endstat) ;
} ;



/*!
    If the curve section contains an inverse arc within it then set this bit
    The bit definitions are as follows:
        REC_CONTAINSINVERTARC - is the only bit required when processing 
                offset curve sections currently. Later will want to extend
                the offset processing logic so as to include valid overlap
                sections or delete them, which will mean add the crossover
                status bit in the offset routine. The REC_CONTAINSINVERTARC
                is used to discard sections when building final curves since
                any section with an inverted arc must by definition be
                invalid.
        REC_OVERLAP - used in the boolean operations to indicate that the
                record defines a curve section which is shared with the 
                other curve. 
 */

#define REC_CONTAINSINVERTARC       0x000000001
#define REC_OVERLAPSECTION          0x000000002 

struct IndexRecord
{
    CS_Curve *pcrv ; // the actual curve that the section is on (boolean only)

    //! used to speed up section breakout processing
    CS_SegPtr pss ;
    CS_SegPtr pse ; 

    //! u value of the curve sections relative to segment
    double uss, use ; 

    double us, ue ; // u values of curve section relative to overall curve
    // The esfrom and esto define the section that the curve traverses for 
    // this index count. We need these to search for the specific event 
    // within the set, after all the index values are set. Then the proper
    // values can be assigned to pss, pse, uss, use, us, and ue
    
    int ifromEvent, itoEvent ; // actual event offset indexes into 
    // the event list plist[] array

    // Event start start nodes defining the ends of this section, (these will
    // almost always match ifromEvent and itoEvent - I think)
    int esfromIDX ;  // event set start index (plist[] offset)
    int estoIDX ;    // event set start index (plist[] offset)

    int idxCount ;  // actual index count for the section
    int idxDelta ;  // index delta change from previous event

    int idxas, idxae ; // Inverse Arc start and end points for 
    // this index count section

    int status ;    // used to store bit info
} ;


class OffsetIndexing
{
public:

    int indexDelta ; 
    int sideINC ;    // indicates an inside(-1) or outside(+1) offset
    int lastIndexCount ; // previous index counter value
    int indexCount ; // current index count
    int minidxCount ; // minimum count value during processing
    int bInvertArc ; // invert arc active indicator
    int bInvertArcSection ; // currently on an inverted arc section
    int bInOverlap ; // inside overlap section indicator
    int esetLength ; 
    // firstXOverIDX and lastXOverIDX are used to determine the exact U 
    // values to be used when multiple cross over events occur at the 
    // same uevent point. If the index count increases in the common set
    // then we want to use the first U values otherwise we want to use
    // the last u values.
    int firstXOverIDX, lastXOverIDX ; 
    // Here we save the last event set calculated
    int prevXOverESet ; // the last crossover event set count
    int prevXOverEventIDX ; // index node which established the actual 
    // U event for the last index set 

    int overallEventStat ; // used to record types of records processed

    IndexRecord *pidxrecs ; 
    int irecLen ; // number of index record entries defined
    UEventList *pevlst ; 
    
    OffsetIndexing() ; 
    ~OffsetIndexing() ; 

    int Initialize(UEventList *plst) ; 

    // Main indexing operation
    int CalcIndexes(int closed) ; // Does the index counting
    int CalcIndexesClosed() ; // index counting for closed curve
    int CalcIndexesOpen() ; // index counting for an open curve
    int BuildCurves(CS_Curve *pcrv, CS_CurveSet &curveset) ;
    int BuildCurvesClosed(CS_Curve *pcrv, CS_CurveSet &curveset) ;
    int BuildCurvesOpen(CS_Curve *pcrv, CS_CurveSet &curveset) ;

    // Indexing support functions
    int IncEventSet(int e) ;
    int DoIndexCount(int i) ; 
    int GetSetStatus(int esidx) ;
    void Dump(FILE *fp=0) ; 
    
} ;


/*!
 Boolean indexing is much simpler than in the offset case. The
 reason is that here there are no inverse arcs to worry about. 
 We are simply crossing into and out of regions as we cross
 boundaries of the other curve. No inverse arcs means that the 
 logic for overlap sections is somewhat different. 

 The status information is used to store state information 
 determined during the index counting process. With boolean
 operations we need to know if there were overlap events, 
 while not finding any intersection events. This would
 mean that one curve is completely inside the other and 
 signals a special case (this situation would occur when 
 offsetting an offset curve backwards to determine uncut areas
 for example)

  The following definitions are used in index counting and 
  have the following meanings within the framework of boolean
  index counting only.

    <ol>
    <li>UEVENT_INTERSECTION - indicates that an intersection occured
        somewhere between the two curves. Thus there had to be 
        two intersections and standard logic will apply. The left
        and right status bits are set but are not useful since
        both types will be set in this situation.
    <li>UEVENT_OVERLAP - set when an overlap occurs. If an overlap 
        occurs without a crossover then the intersection bit
        is not set, but the left and right bits are set. Thus
        if only the UEVENT_OVERLAP is set then we know that
        there were no intersections, but the curves do touch
        one another. In this case if the UEVENT_LEFT bit is
        set then the second curve touched the main curve to the 
        left and because we are going around the curve CCW, this
        means that the second curve is completely inside the main
        curve. If UEVENT_OVERLAP and UEVENT_RIGHT are set and
        BOOLIDX_INTERSECTION is not set, then the reverse is true,
        the two curves touch and the main curve is completely 
        inside the second curve. By inside here we mean that those
        portions of the curve which do not touch are inside the other
        curve, and never is a non-overlap section considered to be
        outside. Obviously the overlap sections are neither inside
        or outside. 
    <li>UEVENT_LEFT, UEVENT_RIGHT - these two are only useful when 
        there is no intersection, but there are overlaps. This 
        enables us to quickly decide which curve is inside the other
        curve. 
    </ol>


    Note: we still have to test the special situation where both 
        curves completely overlap. In this situation, we will
        have overlap curves but in the merge scan and delete
        every single event gets deleted, since each overlap
        event is an end-start pair. 

*/

class BooleanIndexing
{
public:
    int status ;     // used to store state information
    int indexDelta ; 
    int lastIndexCount ; // previous index counter value
    int indexCount ; // current index count
    int minidxCount ; // minimum count value during processing
    int bInOverlap ; // inside overlap section indicator
    int esetLength ; 
    /*! firstXOverIDX and lastXOverIDX are used to determine the exact U 
      values to be used when multiple cross over events occur at the 
      same uevent point. If the index count increases in the common set
      then we want to use the first U values otherwise we want to use
      the last u values.
     */
    int firstActiveIDX, lastActiveIDX ; 

    //! Here we save the last event set calculated
    int prevActiveESet ; // the last crossover event set count
    int prevActiveEventIDX ; // index node which established the actual 
    // U event for the last index set 
    
    int overallActiveStat ; // simply a logical OR of all active states
    // returned for each event set. With this we can quickly filter 
    // through various special cases

    IndexRecord *pidxrecs ; 
    int irecLen ; // number of index record entries defined
    CS_Curve *pcrv ; // Pointer to actual curve being processed
    UEventList *pevlst ; // pointer to the associated event list class
    
    BooleanIndexing() ; 
    ~BooleanIndexing() ; 

    int Initialize(UEventList *plst) ; 

    // Main indexing operation
    int CalcIndexes() ;    // Does the index counting
    void NormalizeIndexes() ;

    // Indexing support functions
    int FindFirstActiveESet() ;
    int IncEventSet(int e) ;
    int DoIndexCount(int i) ; 
    void Dump(FILE *fp=0) ; 
    
} ;


struct CS_CurveChain
{
    // list of connected curves, the curves are simply appended into one long 
    // curve, the only reason for defining this struct is to add the sp, ep 
    // and status members
    CS_Curve *pcrv ; 

    CS_POINT sp, ep ; // start and end points of the overall connected list
    int status ;  // set if contains an inverse arc

    CS_CurveChain() ; 
    ~CS_CurveChain() ; 
} ;

typedef list<CS_CurveChain*> CS_CurveChainList ; 
typedef list<CS_CurveChain*>::iterator CS_CurveChainListItr ; 


int IntersectCurves(CS_Curve *pcrva, CS_Curve *pcrvb, 
                    UEventList &ela, UEventList &elb) ;

int BoolIntersectCurve(BooleanIndexing &bia, // input curve A data
                       BooleanIndexing &bib, // input curve B data
                       CS_CurveSet &crvset) ;  // output result set


// 2D boolean operations
class Bool2D
{
public:
    // output variable
    CS_CurveSet *presSet ; // the final result set

    // First three vars control all processing
    int aindex ; 
    int bindex ; 
    int breversed ; 

    // Internal status values
    int OnA ; 
    int iridx ; 
    int error ; 

    UEventList evlstA ; // curve A event set data
    UEventList evlstB ; // curve B event set data
    
    BooleanIndexing bia ; // curve A data
    BooleanIndexing bib ; // curve B data
    
    CS_POINT startpnt ; 
    CS_POINT endpnt ; 
    

    Bool2D() ; 
    ~Bool2D() ; 

    ////////////////////////////////////////////////////////////////
    // These are the main routines called by the external functions
    int Union(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) ; 
    int Intersect(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) ; 
    int Difference(CS_Curve *pcrva, CS_Curve *pcrvb, CS_CurveSet *presultSet) ;  

    /////////////////////////
    // Internal functions  //
    /////////////////////////
    // Do preliminary setup and curve intersections
    int Setup(CS_Curve *pcrva, CS_Curve *pcrvb) ; 
    
    // performs the actual connection for
    int BoolConnect(char *contype) ; 

    // start the connection routines
    int UnionConnect() ;
    int IntersectConnect() ; 
    int DifferenceConnect() ; 
    int ConnectIRs(CS_CurveSet &crvset) ; 

    // internal function
    void GetNextIRSection() ; 
} ;




// See RR-Vol2 pg 77 for notes 
inline int ZXOffsetArcDirection(CS_VECTOR &va, CS_VECTOR &vb,
                                CS_SegPtr psega, CS_SegPtr psegb)
{
    double zx = ZCross(va, vb) ; 
    int zret ; 
    if (tcomp_EQZ(zx))
    {   // Then there is some more work to do
        // va and vb will both be unit vectors since they were 
        // generated by calls to UTangent() which always return
        // unit vectors
        zret = 1 ; // default to positive, note: if the testing below
        // doesn't assign a value to zret then it won't be used for
        // any decision making later on by virtue of the geometric
        // situation that this defines. 
        CS_VECTOR vbtmp(vb) ; 
        if (va == vbtmp.Reverse())
        {   // 
            if (psega->SegmentType() == CS_Segment::ARC_TYPE)
            {
                if (((CS_ArcSeg *)psega)->swp > 0)
                    zret = -1 ; 
            }
            else if (psegb->SegmentType() == CS_Segment::ARC_TYPE)
            {
                if (((CS_ArcSeg *)psegb)->swp > 0)
                    zret = -1 ; 
            }
        }
    }
    else
    {
        zret = zx < 0 ? -1 : 1 ;
    }

    return zret ; 
}




// See RR-Vol2 pg75 for partial pseudo code (Note the code does take
// into account storage of tangent vectors used to determine arc 
// direction. 
// Too many parameters to this function, is better expand inline 
// correctly, otherwise have to push 6 things to stack
inline int OffsetInsertArc(CS_ArcSeg *piaseg, 
                           CS_POINT &cpnt, 
                           CS_POINT &aoepnt,
                           CS_POINT &bospnt,
                           double delta,
                           int zx) 
{
    // vectors from arc center to the offset points
    piaseg->info &= ~(CRV_ARCCONVEX | CRV_ARCREFLEX) ; 

    if (aoepnt == bospnt)
        return 0 ; // can't do it since they're tangent or inv arc rad=0

    CS_VECTOR vcae(cpnt, aoepnt) ; 
    CS_VECTOR vcbs(cpnt, bospnt) ; 

    double sang = vcae.AngleXY() ; 
    double eang = vcbs.AngleXY() ; 

    piaseg->ctr = cpnt ; 
    piaseg->rad = fabs(delta) ; 
    piaseg->sa = sang ; 
    
    // Note the iaseg arc inverse flag is 0 at this point
    
    if (zx > 0)
    {
        piaseg->swp = arc_sweep(sang, eang, CCW) ; 
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(piaseg->swp, RADIAN360))
            return 0 ; 
        if (delta < 0)
            piaseg->info |= CRV_ARCCONVEX ;
        else
            piaseg->info |= CRV_ARCREFLEX ;
    }
    else
    {
        piaseg->swp = -arc_sweep(sang, eang, CW) ;
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(fabs(piaseg->swp), RADIAN360))
            return 0 ; 

        if (delta > 0)
            piaseg->info |= CRV_ARCCONVEX ; 
        else
            piaseg->info |= CRV_ARCREFLEX ;
    }

    return 1 ; 
}

// Inserts offset arcs in same manner as OffsetInsertArc but does 
// so only if inserting a reflex arc. Does not insert inverse (convex)
// arc segments.
inline int OffsetInsertReflexArc(CS_ArcSeg *piaseg, 
                                 CS_POINT &cpnt, 
                                 CS_POINT &aoepnt,
                                 CS_POINT &bospnt,
                                 double delta,
                                 int zx) 
{
    // vectors from arc center to the offset points
    piaseg->info &= ~(CRV_ARCCONVEX | CRV_ARCREFLEX) ; 

    if (aoepnt == bospnt)
        return 0 ; // can't do it since they're tangent or inv arc rad=0

    CS_VECTOR vcae(cpnt, aoepnt) ; 
    CS_VECTOR vcbs(cpnt, bospnt) ; 

    double sang = vcae.AngleXY() ; 
    double eang = vcbs.AngleXY() ; 

    piaseg->ctr = cpnt ; 
    piaseg->rad = fabs(delta) ; 
    piaseg->sa = sang ; 
    
    // Note the iaseg arc inverse flag is 0 at this point
    
    if (zx > 0)
    {
        piaseg->swp = arc_sweep(sang, eang, CCW) ; 
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(piaseg->swp, RADIAN360))
            return 0 ; 
        if (delta < 0)
            return 0 ; // inverse arc which we don't want
    }
    else
    {
        piaseg->swp = -arc_sweep(sang, eang, CW) ;
        if (tcomp_EQZ(piaseg->swp) ||
            tcomp_EQ(fabs(piaseg->swp), RADIAN360))
            return 0 ; 

        if (delta > 0)
            return 0 ; // inverse arc which we don't want

    }
    piaseg->info |= CRV_ARCREFLEX ;
    return 1 ; 
}


//  Variable offset data structures and defintions
struct CS_VarOfsData
{
    double u ;     // u point for the offset
    double delta ; // delta for the offset
} ;

typedef vector<CS_VarOfsData> CS_VarOfsDataVect ;

//! Variable offset using numerical approximation with multiple offset curves
/*!
    \param crv input curve to be offset
    \param ov  input vector of variable offset values
    \param crvset  the output offset curve set
    \param ofstol controls how many offset curves will be used to approximate the 
    variable offset. This number is a percentage of the min-max offset distance.
    The default is 5% which means 20 (=1/.05) offset curves will be used
    \param lintol linear tolerance allowance when rebuilding the approximate output curve
    \param arctol arc tolerance allowance when rebuilding the approximate output curve
    \return error code, 0=all ok, 1=ov was empty 

    If the output curve set contains more than one curve, then strange results may exists
    since the routine attempts to piece together the resultant curves based on nearest 
    neighbor of where the approximation points occur. 
    
 **/
int CS_VarOffset(CS_Curve &crv, CS_VarOfsDataVect &ov, CS_CurveSet &crvset, 
                 double ofstol=0.05, 
                 double lintol=kCOMPARETOLERANCE*10.0, 
                 double arctol=kCOMPARETOLERANCE*1000.0) ;



//! Create variable offset curve using numerical method
/*! 
    \param crv input curve to be offset
    \param dofs array of offset values at u points along curve. [0]=u, [1]=ofs
    \param ndofs length of the dofs array
    \param rescrv the resultant offset curve
    \param filletrad initial fillet radius for sharp corners
    \return returns status information flags

    The dofs array contains floating point pairs where the first pair value
    is the u parameteric point along the curve and the second value in the 
    pair is the actual offset at that u point. Thus the dofs[i][0] values
    define u points with dofs[i][1] defining the matching offset delta. 

    A perpendicular vector is used to determine an iterative offset point
    and these points are chained together to form arcs and lines. As the 
    arcs and lines are built up they are added to the final result curve. 
    
    To get smooth transitions around sharp corners a filleting operation 
    is done at the start so that all sharp corners are converted into 
    small radius arcs, the radius being defined by filletrad. If filletrad
    is zero, no filleting operation is performed. 

    The status return value is always 0 for now. 

 */
int VarOfsNM(CS_Curve &crv, double dofs[][2], int ndofs, double filletrad, int segsteps, CS_Curve &rescrv) ;

//! Same as VarOfsNM but with more reliable method (hopefully)
int VarOfsNMC(CS_Curve &crv, double dofs[][2], int ndofs, double filletrad, int segsteps, CS_Curve &rescrv) ;

//! Same as VarOfsNMC using pre-defined incremental dofs data
// int VarOfsNMCp(CS_Curve &crv, double dofs[][2], int ndofs, CS_Curve &rescrv) ;

#include "cs_varoffset.h"

#endif