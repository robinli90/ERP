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
// cs_chain.h


#ifndef __CS_CHAIN_H__
#define __CS_CHAIN_H__

#pragma warning( disable : 4786 )

extern int chainDebugSaveCurves ; 
extern char *szChainDebugFileName ; 
extern FILE *fpChainDebugFile ; 

// See Notes Geom Algo's RR-Vol4 pg. 67 for a diagram of the new chaining
// structure


class CS_Chain ; 
class CS_ChainREC ; 

// This has to be defined as a pointer list since the chain record
// has to point back to the stack which isn't defined yet. 
typedef list<CS_ChainREC*>           CS_ChainRECList ; 
typedef list<CS_ChainREC*>::iterator CS_ChainRECListItr ; 


//! Stack of chaining records. 
/*!
    A CS_ChainSTK contains a list of CS_ChainREC records. There is a single
    CS_ChainREC entry for each segment that intersects at the point 
    represented by the chaining stack. Thus when chaining you are effectively
    jumping from one chaining stack to another following along different 
    curve sections during each jump. 

    Some of the variables within the chain stack are updated dynamically 
    as the chain curve is being built. These are pcrFROM, lastDirection, 
    pcrTO, and direction as well as certain member variables within the 
    CS_ChainREC's that are contained within the creclist variable. 
    The remainder of the variables remain fixed once the chaining 
    operation begins. See the diagram and further notes in CS_Chain for 
    a more detailed discussion of how CS_ChainSTK's are used. 
 */
class CS_ChainSTK 
{
public: 
    
    //! pointer to the parent CS_Chain class that this stack is a member of
    CS_Chain *pChain ; 

    //! point that defines this stack
    CS_POINT stkpnt ; 

    //! The CS_ChainREC list that make up this stack
    CS_ChainRECList creclist ;

    //! These two parameters are only required by the custom chaining
    //! callback logic. They tell the callback routine where the chaining
    //! was coming from. This should be referenced but not modified as
    //! they are updated internally.
    CS_ChainREC *pcrFROM ;
    int lastDirection ;

    //! During chaining, the direction decision callback set these
    //! values to indicate which direction was chosen for the next 
    //! chain record node in the chaining list.
    CS_ChainREC *pcrTO ;
    int direction ;

    CS_ChainSTK() {} ;

    //! Must de-allocate the stack list since the collection of
    //! pointers in the stack list are allocated on the heap and 
    //! there is no way to maintain a reference set of those pointers
    //! without incurring significant overhead. 
    ~CS_ChainSTK() ;

    //! returns the point that defines this stack of chaining intersection records
    CS_POINT &StackPnt() {return stkpnt ; } ;
} ;

//! Definition for CS_ChainSTK list
typedef list<CS_ChainSTK>           CS_ChainSTKList ; 

//! Definition for the CS_ChainSTKList iterator
typedef list<CS_ChainSTK>::iterator CS_ChainSTKListItr ; 


//! Chaining node information record
/*!
    The main chaining record storage structure. The CS_ChainREC entries in the
    chain stacks contain all the information required to decide which new
    direction to take from each chaining node (which is a CS_ChainSTKList).

    When there are overlapping interesections involved in the chaining 
    data, things can get complicated since the intersecting overlaps may
    go in opposite directions. Keep in mind that the forward and reverse
    directions are relative to the original curve. With overlap sections
    the tangent forward and reverse vector directions (and by extension) 
    angles may not end up working out to exactly the same values as the 
    corresponding angles for the overlap section. So what ends up happening
    is that depending on your chaining tolerance the routine ends up 
    trying to walk backwards, since it is following a reversed overlap 
    section in the forward direction. When this happens you usually 
    end up with a closed curve that has no volume since the curve walks
    out and then walks back on itself ending up back at the start point. 
    Depending on the geometry however this may not be the case and you
    could end up with shapes that overlap on themselves and also have 
    an area to them. To try and avoid this problem set the angle tolerance
    in the main CS_Chain class to a large value, but this can introduce 
    problems as well. The other way is to create a callback for direction
    decisions. 

    vtanfwd and vtanrev are in the directions you would follow if walking 
    forwards or backwards on the curve from that point. For example in the 
    following situation


        A________________________________________B
                           D
                          / \ 
                        /     \
                      /         \
                    /             E
                  /
                C

    
     Line AB will have a chaining record occur at point D. For the 
     AB curve assuming that AB is the forward direction, vtanfwd will
     be in the AB direction and vtanrev will be in the BA direction. 
     Also, the Curve CDE will have a vtanfwd in the DE direction and 
     a vtanrev in the DC direction. 

 */
class CS_ChainREC  
{
public:

    enum {
        BLOCKFWD        = 0x01, //!< foward angle equals negative PI
        BLOCKREV        = 0x02, //!< reverse angle equals negative PI
        AVOIDFWD        = 0x04, //!< take this direction as last resort
        AVOIDREV        = 0x08, //!< take this direction as last resort
        OVRLAPSTART     = 0x10, //!< start of overlap section
        OVRLAPEND       = 0x20, //!< end of overlap section 
        BLOCKED         = 0x40, //!< don't chain to this node
        CLEARMASK       = 0x3f, //!< mask of all the above bits
        PNTFWD_ON       = 0x01, //!< pntFwdMid is on a reversed curve intersection
        PNTFWD_ONREV    = 0x02, //!< pntFwdMid is on an overlap intersection
        PNTFWD_INSIDE   = 0x04, //!< pntFwdMid is inside another curve. 
    } ; 

    //! iterator to the parent stack list
    CS_ChainSTKListItr istk ; 

    /*!
        Point on the curve that this record defines. 
        The CS_CrvPnt variable contains a pointer to the segment
        that this CS_ChainREC is based on. Thus it is possible to 
        retieve the parent CS_Curve with crvpnt.s->pParent which is
        of type CS_Curve* (see member function CS_ChainREC::ParentCrv()).
     */
    CS_CrvPnt crvpnt ;     
    
    //! u parameter value with respect to the parent curve at this 
    //! chain node location. 
    double ucrv ;

    //! How many times the curve has been followed in the forward
    //! direction from this node point
    int fwdwalkcount ; 

    //! How many times the curve has been followed in the reverse
    //! direction from this node point
    int revwalkcount ; 

    //! pointer to user data to store extra information about this node
    //! when the custom chaining method is implemented. This pointer 
    //! is not initialized and is not used by the library in any way.
    void *pUser ; 

    //! The mid point in the forward direction for this section. This is 
    //! used by the union boolean operation only for now. 
    CS_POINT pntFwdMid ; 
    //! bIsInside and bIsOn are set in a mutually exclusive manner. Thus 
    //! if bIsInside is set, then it was set for a curve condition where it 
    //! was also not on the curve. If both the INSIDE and ON conditions are 
    //! true, then only the ON condition is set. If during processing the 
    //! INSIDE and ON flags are both set, this would mean there were at least
    //! two other curves, one where just the INSIDE condition was satisfied 
    //! and another where the ON condition was satisifed.
    bool bIsInside ; // true if pntFwdMid is inside another curve
    int statPntFwd ; // pntFwdMid status flags

    //! The tangent direction just slightly forward of the crvpnt on 
    //! the curve. The reason we move forward is to deal those situations
    //! where the intersection is at the corner of two line segments
    //! where the forward and reverse directions are different.
    CS_VECTOR vtanfwd ; 

    //! The tangent direction just slightly backwards of the crvpnt on 
    //! the curve. The reason we move backwards is to deal with those 
    //! situations where the intersection is at the corner of two 
    //! line segments where the forward and reverse directions are 
    //! different.
    CS_VECTOR vtanrev ; 

    //! returns the curve pointer associated with this chain record node
    CS_Curve *ParentCrv() { return crvpnt.s->pParent; } ; 

    //! Pointer to the next chain record in the forward direction along
    //! the parent curve 
    CS_ChainREC *pcrfwd ; 

    //! Pointer to the next chain record in the reverse direction along
    //! the parent curve 
    CS_ChainREC *pcrrev ; 

    //! The following are temporary variables that are modified 
    //! as each chaining decision is made. 
    
    //! The turn angle from the last section in the chain curve
    //! if the forward direction is followed along this record
    double fwdang ; 

    //! The turn angle from the last section in the chain curve
    //! if the reverse direction is followed along this record
    double revang ; 

    //! saves status information about the original intersection
    int origstatus ;

    //! temp status used to control chaining state and logic
    int status ; 
    
    // Member functions

    CS_ChainREC() ; 
   ~CS_ChainREC() {} ; 


    void SetAngleStats(double *tol=0) 
    {
        if (tol)
        {
            if (tcomp_EQ(fabs(fwdang), RADIAN180, *tol))
                status |= AVOIDFWD ; 
            if (tcomp_EQ(fabs(revang), RADIAN180, *tol))
                status |= AVOIDREV ; 
        }
        else
        {
            if (tcomp_EQ(fwdang, RADIAN180) || tcomp_EQ(fwdang, -RADIAN180))
                status |= AVOIDFWD ; 
            if (tcomp_EQ(revang, RADIAN180) || tcomp_EQ(revang, -RADIAN180))
                status |= AVOIDREV ; 
        }
    }

    //! Returns true if the forward direction should not be followed
    int FWDBlocked()
    {
        if (status & BLOCKFWD)
            return 1 ; 
        return 0 ; 
    }

    //! Returns true if the reverse direction should not be followed
    int REVBlocked()
    {
        if (status & BLOCKREV)
            return 1 ; 
        return 0 ; 
    }

    //! Returns true if the forward direction should be used only as a last resort
    int FWDAvoid()
    {
        if (status & (BLOCKFWD | AVOIDFWD))
            return 1 ; 
        return 0 ; 
    }

    //! Returns true if the reverse direction should be used only as a last resort
    int REVAvoid()
    {
        if (status & (BLOCKREV | AVOIDREV))
            return 1 ; 
        return 0 ; 
    }

    //! Returns the number of times this segement has be walked past in either the 
    //! forward or reverse directions. 
    int WalkedCount() { return fwdwalkcount + revwalkcount ; }

    //! tests to see if the section specified was walked before, this 
    //! checks if the node was reached from the next node in the 
    //! reverse direction as well, since these are the only two ways
    //! in which a section of a curve can be traversed.
    int WasWalked(int dir)
    {
        if (dir == CS_FORWARD)
        {
            if (fwdwalkcount > 0)
                return 1 ; 

            if (pcrfwd && pcrfwd->revwalkcount > 0)
                return 1 ; 
            return 0 ; 
        }
        else
        {
            if (revwalkcount > 0)
                return 1 ; 

            if (pcrrev && pcrrev->fwdwalkcount > 0)
                return 1 ; 
            return 0 ; 
        }
    }


} ;


/*!
    Ordered list of chain records associated with one curve in 
    ascending u value order. 

    As intersection nodes are created, chain records can be inserted
    in a sorted manner into the list for the curve. Then once all
    intersections are complete, the pcrfwd and pcrrev pointers can
    be connected for all the CS_ChainREC records. 
    
    The first CS_ChainREC's curve u parm becomes the master u value
    for all associated intersection records at this node w.r.t. the 
    base curve. This way the tolerance comparison always uses the 
    same reference point, which means that chaining from this point
    will be consistently within the region around the initial point,
    and that no two chain records will be closer than the tolerance
    distance. This helps keep the logic simpler when deciding 
    which direction to follow along a chain.

    Note that there is only a single CS_ChnNode record defined at 
    a specific u point for the curve even if there are multiple
    intersection records that occur at that point. Also there will
    only be a single CS_ChainREC entry within the chain stack 
    for the specific u value, since the ChainREC only needs to walk
    backwards or forwards along the curve no matter how many 
    intersections occur at this point. 
 */
class CS_ChnNode
{
public:
    //! Pointer to the chain record at this node
    CS_ChainREC *pcr ; 

    //! reference to the parent CS_ChainSTK that this chaining record 
    //! is contained in. 
    CS_ChainSTKListItr istk ; 

    //! u value w.r.t. the entire curve for this node
    //! The CS_ChnNodeMap is sorted by this value. 
    double ucrv ; 

    CS_ChnNode() {} ; 
    CS_ChnNode(const CS_ChnNode &cn)
    {
        pcr = cn.pcr ; 
        istk = cn.istk ; 
        ucrv = cn.ucrv ; 
    }

    int operator<(CS_ChnNode &cr)
    {
        if (tcomp_LT(ucrv, cr.ucrv))
            return 1 ; 
        return 0 ; 
    }

    int operator==(CS_ChnNode &cr)
    {
        if (tcomp_EQ(ucrv, cr.ucrv))
            return 1 ; 
        return 0 ; 
    }

    int operator>(CS_ChnNode &cr)
    {
        if (tcomp_GT(ucrv, cr.ucrv))
            return 1 ; 
        return 0 ; 
    }
} ;

//! one list must be defined for each curve that is included for chaining
typedef map<TolDbl, CS_ChnNode>   CS_ChnNodeMap ;
typedef map<TolDbl, CS_ChnNode>::iterator    CS_ChnNodeMapItr ;


//! This is the data class used to store chains that are being built 
//! into final curves. ChainCrvs are maintained as stacked records
//! with each record defining a curve section to be added to the final
//! chained curve. The stack is maintained so that we can back up 
//! and try other directions if during the chaining a dead end is 
//! reached. This way all chain routes can be searched out regardless
//! of where the chain starts from. 
struct CS_ChnCrvRec
{
    //! The chain record defining the next curve section
    CS_ChainREC *pcr ; 

    enum  {
        FORWARD     = CS_FORWARD,
        REVERSE     = CS_REVERSE,
        TOSTART     = 0x04,
        TOEND       = 0x08,
    } ;
    
    //! whether to use the forward or reverse section from the pcr 
    //! node point. Thus the ChainREC can be followed in either 
    //! the forward or reverse direction as indicated by this flag.
    //! future expansion for other status indicators. 
    int status ;
    
    void Print(FILE *fp) ; 
} ;

typedef list<CS_ChnCrvRec>            CS_ChnCrvRecList ;
typedef list<CS_ChnCrvRec>::iterator  CS_ChnCrvRecListItr ;

//////////////////////////////////////////////////////////////////////////
// Used for temporary storage for basic chaining operations
struct CS_ChainSegment
{
    CS_SegPtr pseg ;
    CS_RECT bndbox ;
    int status ;
    CS_ChainSegment *prev, *next ;
} ;


//////////////////////////////////////////////////////////////////////////
// Following structures are used for complex chaining of multiple 
// intersecting curves.
//////////////////////////////////////////////////////////////////////////

//! Takes the input segment array and returns the minimum set of chained curves
/*! 
    \param pIN pointer to array of CS_Segment pointers defining the input 
                curve segments
    \param nIN length of the pIN pointer array
    \param crvset the resultant curve set generated after end point connection
    \param tol is the tolerance to use for end point matching
    \return Returns 0 if OK, else an error code. Currently no errors defined
    but memory allocation errors will be likely error codes returned in future.

    The pIN array is not modified in any way during processing. All segments
    are copied and transfered to unique curves by this process, with
    the exception of overlap segments which are ignored. Note if there
    is a partial overlap, then one segment is trimmed to eliminate the 
    overlap, and if a segment completely overlaps another, then the segment
    which has an overlap range of [0,1] is removed and is no longer used. 
 */
int CS_ChainUniqueSegments(CS_Segment **pIN, int nIN, CS_CurveSet &crvset, double *tol=0) ;

/*! 
    \param csin input set of curve fragments to be chained
    \param csout output chained curves
    \return Returns 0 if OK, else an error code. If there is a node count
    discrepancy in any of the input curve fragments, then an error code of
    0x00010000 is returned. 

    The input CS_CurveSet csin is not modified in any way during processing. 
    This creates a CS_Segment* array and then calls:
            CS_ChainUniqueSegments(CS_Segment**, int, CS_CurveSet&)
    See the description for the same function which takes a segment 
    array list as input for further details on behaviour. 
 */
int CS_ChainUniqueSegments(CS_CurveSet &csin, CS_CurveSet &csout) ;

// Chaining support function prototypes
#define CS_CONNECT_A_START      0x0001
#define CS_CONNECT_A_END        0x0002
#define CS_CONNECT_B_START      0x0004
#define CS_CONNECT_B_END        0x0008
#define CS_CONNECT_ALL          0x000f


/*!
    \param psa first segment to test 
    \param psb second segment to test 
    \param tol default tolerance override value
    \return some combination of CS_CONNECT_A_START, CS_CONNECT_A_END,
    CS_CONNECT_B_START, and CS_CONNECT_B_END

    Checks to see if the endpoints of the two segments are equal and
    sets the bit mask based on which end nodes match up. If all 4 bits
    are set, then both ends of the segments are connected together, OR
    the two segments are complete circles that start at the same tangent
    point (which means they are connected in a sense but not the type
    of connection you would typically be looking for in a chaining
    operation. 
 */
int SegmentsConnected(CS_SegPtr psa, CS_SegPtr psb, double *tol=0) ;


//! This function should return 0. 
/*!
    \param istk iterator referencing the chaining stack to test from
    \param mode the chaining mode in force for the direction testing

    The function is given an iterator reference to the current
    stack node at which point we have to decide which direction to
    take. From here, the pcrnxt and direction parameters must be set.

    To do this, the callback function scans through the creclist defined
    for the stack and decides which direction to take. Once a final decision
    is made the istk->pcrTO and istk->direction are set based on which 
    direction to follow. Note the pcrTO member is set to point to one of
    the CS_ChainREC entries within the creclist, and direction is set to 
    either CS_FORWARD or CS_REVERSE to indicate whether or not to follow
    the forward or reverse direction along the curve that the pcrTO 
    record references. The fwdang and revang member variables for each
    CS_ChainREC in creclist will be set before this callback is called
    based on the direction followed along the last current section in 
    the chain. It is entirely up to the callback function as to what 
    decision making process is used, the mode variable doesn't necessarily
    have to be followed. Also, if the user wants to track additional information
    then the pUser pointer within the CS_ChainREC's should be set before the
    entire chaining process is started. 

    The callback can also be used to prompt a user and allow the user
    to select the desired next step to follow in the chain. 

    Refer to CS_FindRightChain(...), CS_FindTangentChain(...), CS_FindLeftChain(...), 
    for ideas on how to go about implementing a custom function. 
 */
typedef int (*CS_ChainCustomCallbackFunc)(CS_ChainSTKListItr &istk, int mode) ;

//! Returns the next node in the chain given the current position and direction
inline CS_ChainREC *CS_NextChainRECNode(CS_ChainREC *pcurnode, int direction) ;

//! Sets the istk->pcrTO and istk->direction variables to follow the rightmost
//! turn direction taking into consideration special status info defined in mode
//! and within the CS_ChainREC status variables.
int CS_FindRightChain(CS_ChainSTKListItr &istk, int mode) ;

//! Sets the istk->pcrTO and istk->direction variables to follow the leftmost
//! turn direction taking into consideration special status info defined in mode
//! and within the CS_ChainREC status variables.
int CS_FindLeftChain(CS_ChainSTKListItr &istk, int mode) ;

//! Sets the istk->pcrTO and istk->direction variables to follow the straightest
//! turn direction taking into consideration special status info defined in mode
//! and within the CS_ChainREC status variables.
int CS_FindTangentChain(CS_ChainSTKListItr &istk, int mode) ;


//! Connects multiple curves together based on rule set
/*! 
    \showinitializer

    The \a CS_Chain class is intended to be used in situations where there
    are a number of curves that need to be connected in some manner to 
    create a different set of curves. Possible uses would be to extract 
    the smallest inside loops or the largest outside loops among
    all the input intersecting curves. To do this requires a fairly 
    complicated data structure in order to allow for either fixed 
    rules or custom user defined rules when following the intersection
    nodes during the creation of the new curve set. The diagram below 
    is an example of a set of input curves to be chained. 

    \image latex chain-samp.eps "Sample Set of Intersected Curves" width=120mm

    When this set of curves is loaded in to the \a CS_Chain class and
    initialized properly, a data structure is created which resembles the
    diagram below. 

    \image latex chaining2.eps "CS_Chain Internal Representation" width=120mm

    Chaining records are extensions of standard intersection records. The
    initial step when doing a chaining operation is to create a full 
    intersection of all the curves that will be used (considered for use)
    in the chaining operation. In addition to the standard intersection 
    information, chaining needs to know which direction the curve 
    segments go, as well as whether or not a particular section of a 
    curve has been used anywhere in a chain so far. The forward and 
    reverse tangent vectors are both stored, since if the intersection
    occurs at a corner node (non-tangent segment connection, corner of 
    a square for example) we need to know the different tangents
    in both the forward and reverse directions. The chaining tolerance
    controls how far forward and backwards we look along the segment to 
    determine the tangent vector directions. A section of a curve 
    between intersections defines a \a chaining \a segment. 
    Chains are constructed by walking from one \a CS_ChainREC node 
    to another and adding the full \a chaining \a segment to the final
    chain curve as each node is traversed. If the ChainAllLoops 
    function is called, as each \a chaining \a segment is 
    added to a chain it is marked as being part of an output chain curve. 
    Then the node set is continually processed until all the 
    \a chaining \a segments are marked. This will produce multiple
    chained curves, that are returned in a curve set. 

    Chaining Modes:      
    <UL>
        <LI>Left. Chaining proceeds from segment to segment by always talking
        the leftmost possible direction at each node. 
        <LI>Right. Chaining proceeds from segment to segment by always talking
        the rightmost possible direction at each node. 
        <LI>Tangent. Chaining proceeds from segment to segment by always talking
        the route which is most tangent to the direction the proceeding segment
        <LI>Custom. A user defined callback controls the direction chosen for 
        the next chaining segment. Special logic can be applied, or user
        input can be used to determine the next chaining segment.
        <LI>Same Curve. Stay on the same defining curve as the proceeding 
        chain segment if possible. This is done by testing the parent 
        curve pointers of the CS_Segment data within the chaining records.
        
        Important: Make sure that the CS_Curve parent pointers are valid 
        before calling the intersection operation during the chaining
        initialization.
    </UL>
    

    During the intersection part of the processing, if an overlap intersection
    occurs, then two CS_ChainREC nodes are created, one for the 
    start of the overlap intersection, and one for the end. Thus the
    \a cpp[1] and \a cps[1] variables in the CS_IREC records are never
    used during chaining processing, the reason being that it simplifies the 
    logic, and overlap sections will be followed normally anyways. 
    
    Chain loops based on where the intersection points occur. This 
    chaining is used when polygonal shapes are to be extracted from
    a set of intersected curves. The curve that drives the chaining
    acts as the base, but segments chained in this case, are complete
    curve sections in between intersection points. By adjusting 
    the mode however it is possible to bypass intersection points
    and follow the original base curve. 
    
    To set up eveything for use follow these steps:

     <OL>
     <LI>Create a set of CS_Curves that will be intersected. </LI>
       
     <LI>For each curve call the member function Complete() so that
         the uo values are set, and all parent pointers for each 
         segment are also set correctly.</LI>
        
     <LI>Call Intersect2D(CS_Curve *pcrv, CS_IRECList *pirlist)
         once for each of the other CS_Curves, and use the same 
         CS_IntersectList for each call (thus the CS_IntersectList()
         could grow very large). You can use multiple base curves
         when performing the intersections if the chain will 
         potentially jump from one base to another joined by 
         connecting curves. In this scenario you simply have to 
         make sure that all the curves that might intersect
         each other are intersected. Thus in a worst case scenario
         make sure that all curves are intersected with every other
         curve (O((n^2)/2) required for intersections alone).</LI>
      
     <LI>Call AddIntersectDataToCurves(islist) passing the single 
         large intersection list just created. This will fill in 
         the CS_ChnNodeMap *pcnmap variable for all the curves that
         are part of the intersection set.
      
     <LI>For all curves involved call SetFwdRevPointers() </LI>
      
     <LI>Call the desired chaining function to generate the desired
         chain curves</LI>

     </OL>   

    Version 2.0 defintion of chaining set records. Chaining operations are
    used wherever multiple curves must be intersected and then paths 
    followed along the set of curves, taking various directions at each 
    intersection point based on a set of rules. The chaining process can
    either follow fixed standard rules, or custom callbacks can be used
    to define any rule set desired. The callbacks can use the standard 
    rules as part of the logic applied to the custom rule set. 

    The data structure used consists of chaining node records CS_ChainREC
    stacks of nodes at common intersection points, CS_ChainSTK and 
    finally the set of all stacks, CS_ChainSET. Chaining is done from 
    CS_ChainREC to CS_ChainREC where the two CS_ChainREC nodes are not
    in the same CS_ChainSTK.

    The standard chaining rules operate on the XY plane, but could be extended
    to follow custom rule sets in 3D space. 

    Example:

    This general example assumes that you have a bunch of curves in space and
    that each curve has been intersected with all the other curves. Now you 
    want to create chains of all the outside closed shapes. Since there could
    be more than a single oustide closed shape you have to loop through and test
    each curve to see if it has been chained yet. Then if not perform the chaining
    operations starting with the chain map for that curve. The chaining operation
    sets the forward and reverse walk count values, so by testing to see if the
    value is zero for the first chain node record in the pcnmap for each curve
    you can tell if that curve has already been included in a chain or not. 
    By looping through and chaining all chain node maps that have zero walk 
    counts, all possible closed outer contours can be generated (note that the 
    closed outside contour is only one possible output set which gives us the
    union of all the intersecting curve, and to do this there are several ways 
    to proceed. You can orient all the curves CCW and always chain RIGHT or
    orient all curves CW and always chain LEFT moving in the forward direction 
    only in both cases. 
   
    The following example has oriented all the curves CW and the final output
    set is the finalouterloops. The set of starting curves is startset

    \verbatim

    CS_CurveSet startset ; 
    CS_CurveSet finalouterloops ;

    // Load startset with a bunch of closed curves
    //  .
    //  . 

    // Note: startset is modified during this process
    CS_Curve *pcrv ; 
    startset.InitIterator() ; 
    while (pcrv = startset.NextCurve())
    {   // Make sure the parent pointers are set and that the curves 
        // are all going in a clockwise direction
        pcrv->Complete(CW) ;
    }

    // Now intersect all curves in startset with all other curves


    CS_IRECList ichainset ; 
    CS_CurveVecItr ic1, ic2 ; 
    for (ic1 = startset.crvlist.begin(); ic1 != startset.crvlist.end(); ic1++)
    {
        ic2 = ic1 ; 
        ic2++ ; 
        while (ic2 != startset.crvlist.end())
        {
            (*ic1)->Intersect2D(*ic2, &ichainset) ; 
            ic2++ ; 
        }
    }

    
    CS_Chain chn ;
    chn.chntol = 0.001 ;
    chn.AddIntersectDataToCurves(ichainset) ; 
    
    CS_CurveVecItr pcn = startset.crvlist.begin() ; 
    while (pcn != startset.crvlist.end())
    {
        pcrv = *pcn ; 
        if (pcrv->pcnmap)
        {   // This means that this curve intersected with another curve 
            // since it has pcnmap data defined. There would only be 
            // pcnmap data defined if there was an intersection, since the 
            // AddIntersectDataToCurves(...) call above creates the pcnmap
            // entry for each curve that has an intersection associated 
            // with it. 
            chn.SetFwdRevPointers(pcrv) ; 
            pcn++ ; 
        }
        else
        {   // No intersections with this curve, thus must delete it 
            // from processing for chaining but keep it as part of the 
            // final outer loop set. 
            finalouterloops.AddCurve(pcrv) ; 
            pcn = startset.crvlist.erase(pcn) ; 
        }
    }

    // We're now ready to chain the intersecting curves together

    startset.InitIterator() ;
    while (pcrv = startset.NextCurve())
    {
        CS_ChnNodeMapItr cmi = pcrv->pcnmap->begin() ; 
        if (cmi->second.pcr->WalkedCount() == 0)
        {
            CS_CurveSet chnwrkset ; 
            chn.ChainAllLoops(pcrv->pcnmap, chnwrkset, CS_Chain::LEFT | CS_Chain::FORWARDONLY) ; 

            chnwrkset.InitIterator() ;
            CS_Curve *pc ; 
            while (pc = chnwrkset.NextCurve())
                pc->Complete(CW) ; 
            
            if (chwrkset.size() > 0)
                finalouterloops.AppendSet(chnwrkset) ; 
        }
    }
    
    // finalouterloops should contain all the closed outer loops, or the union of 
    // all the starting curves in startset 

    \endverbatim

    When there are overlapping interesections involved in the chaining 
    data, things can get complicated since the intersecting overlaps may
    go in opposite directions. Keep in mind that the forward and reverse
    directions are relative to the original curve. With overlap sections
    the tangent forward and reverse vector directions (and by extension) 
    angles may not end up working out to exactly the same values as the 
    corresponding angles for the overlap section. So what ends up happening
    is that depending on your chaining tolerance the routine ends up 
    trying to walk backwards, since it is following a reversed overlap 
    section in the forward direction. When this happens you usually 
    end up with a closed curve that has no volume since the curve walks
    out and then walks back on itself ending up back at the start point. 
    Depending on the geometry however this may not be the case and you
    could end up with shapes that overlap on themselves and also have 
    an area to them. To try and avoid this problem set the angle tolerance
    in the main CS_Chain class to a large value, but this can introduce 
    problems as well. The other way is to create a callback for direction
    decisions. 
    
    Also, see the function CS_UnionCurves(...) for more information on 
    how to use chaining. CS_UnionCurves forms the UNION of two curves
    with the CS_Chain class. 

    IMPORTANT: Make sure that the chn.mode flag to ALLOWREVERSALS is 
    set if it is expected to follow a path almost completely backwards
    (reverse direction) when following a curve chain. This is disabled
    by default, which has the effect of ignoring possible chaining paths
    where an accute angle of less than 1 degree or so will be created
    in the output chained curve. See revangtol for more information. 

 */
class CS_Chain
{
public:
    
    enum {
        //! follow leftmost direction 
        LEFT            =   0x0001, 

        //! follow rightmost direction 
        RIGHT           =   0x0002, 
        
        //! follow straightest direction 
        TANGENT         =   0x0004, 

        //! use custom callback rule for direction decision
        CUSTOM          =   0x0008, 
        
        //! follow the same curve if possible
        SAMECRV         =   0x0010, 
        
        METHODMASK      =   0x001f, 
        
        //! only chain along curve in forward direction
        FORWARDONLY     =   0x0100, 
        
        //! only use a curve segment once in result set
        WALKONCE        =   0x0200, 

        //! allow near reversal directions in chain
        ALLOWREVERSALS  =   0x0400, 

        //! Open curve chaining mode, disables the abort chain condition
        OPENCURVES      =   0x0800,

        //! Only start on sections where bIsInside is false
        STARTOUTSIDE    =   0x1000, 

        //! Only start on sections where bIsInside is true
        STARTINSIDE     =   0x2000, 

        //! Return to signal abort chaing in the custom callback
        CUSTOMABORT     =   0x8000, 
    } ;

    //! Stores a list of all the chaining stack nodes, this is the main internal
    //! data store for the chaining operation
    CS_ChainSTKList stklst ; 

    /*!
        The chaining tolerance factor is a 
        multiplier used to control the small distance walked forward 
        and backwards along the curve segment when specifying 
        the \a vtanfwd and \a vtanrev
        direction vectors. The default value is 0.001, thus the tangent
        vectors are taken from a point 1/1000th of the arclength
        of the curve segment at the intersection/CS_ChainSTK point.
        NOTE: If COMPARETOLERANCE < 0.001 on initialization of the 
        CS_Chain class, then chntol is set to the default value
        of 0.001 otherwise chntol is set to (COMPARETOLERANCE * 2.0).
     */
    double chntol ;

    /*!
        For some chaining operations it is convenient to have a list of 
        all the input curves to iterate through during testing. 
     */
    CS_CurveVec chncrvs ; 
 
    /*!
        The radian angle tolerance use in the comparison of angle directions
        when deciding how to turn left or right. Only if the angle is 
        a better direction by more than the angtol value in radians 
        will that direction be followed. Default is 1e-10.

        Note: when the turn angles are decided at the chaining stack 
        points, internally the program moves slightly ahead on the curve
        to determine the forward direction, and shifts slightly backwards
        on the curve to decide the backward direction. The intent here 
        is to provide a valid directional angle if the stack point
        occurs directly on a corner where two non-tangent lines meet.
        Without doing this, at a corner the logic would arbitrarily 
        decide on a single direction for both forward and reverse giving
        (1,0) and (-1,0) instead of (1,0) and (0,1)  for this example


                    |
                    |
                    |
                    |           
                    |___________  >   Curve going in this direction
                                  >     

            
        TODO - make this a parameter so that it can be adjusted. 


     */
    double angtol ; 

    /*! 
        Stored in radians.

        This is the reverse angle tolerance. Generally going directly backwards 
        from wherever you currently are is a bad idea. In some situations by 
        setting this value large (5 degrees say) you can avoid situations where
        the angle test is happening almost exactly on a corner intersection 
        where the reverse direction is actually different from what you would 
        expect it to be by almost 90 degrees since the backoff check points
        put you on the other side of the corner. There are specific cases 
        where the reverse direction then becomes the preferred choice
        when this happens. By setting this larger you can effectively filter
        out path reversals. 

        The default will be just over 1 degree (stored as 0.0175 radians). 
        This will only be used if the mode flag ALLOWREVERSALS is not set. 

        See angtol Note: section
     */
    double revangtol ; 

    //! Defines the starting record for chaining
    CS_ChainREC *pStartRec ; // the set defining the chain start

    //! A chaining section is defined by a from-to section which is pointed to
    //! by the pcurRec and direction variables. The section spanning pcrTO 
    //! and pcrTO->pcr{fwd,rev} defines the next section in the curve chain.
    //! where fwd and rev are chosen by the value of the direction variable.

    //! next node in the chain
    CS_ChainREC *pcrTO ;   

    //! set to CS_FORWARD or CS_REVERSE to indicate which way to follow 
    //! along the next curve segment from the current CS_ChainREC
    int direction ;    

    //! the last node in the chain. 
    CS_ChainREC *pcrFROM ;  

    //! the last direction followed during chaining
    int lastDirection ; 

    //! This is a list of chain nodes that are stacked as the chain is 
    //! built. With this stack the ability to back up at dead ends is
    //! possible since the end of the list is simply popped and new
    //! directions attempted. 
    CS_ChnCrvRecList chnreclist ; 
    
    //! Initial chaining point, can be used for a chaining complete
    //! termination test (e.g. when the last chained point hits the start
    //! chain point, stop chaining)
    CS_POINT startchnpnt ; 

    //! last point added to the chain
    CS_POINT lastchnpnt ; 

    //! Vector direction of the last chaining segment added to the current
    //! curve chain. 
    CS_VECTOR lastchnvec ; 

    //! chain curve currently being built, it is created by following
    //! the \a chnreclist once the chaining is complete
    CS_Curve *pchncrv ; 

    //! If pendCrv is not null then if a chaining node hits this curve
    //! and u value, the chaining will stop. Make sure \a uend is valid 
    //! when \a pendCrv is defined.
    CS_Curve *pendCrv ; 
    
    //! chaining stop condition point when \a pendCrv is defined
    double uend ; 
    
    //! Method in which the chaining direction changes are made
    int chnmode ; 


    enum { 
        PRCMODE_EXACT       = 0x0001
    } ; 

    //! Determines how the tangent vectors are processed and potential future extensions
    /*!
        PRCMODE_EXACT - use exact tangent vector point locations
     */
    int prcmode ; 

    //! when not equal zero, then within the ChainLoop() do..while
    //! the loop will only be done this many times. 
    int maxSegCount ; 

    
    //! Pointer to user defined custom callback function. 
    /*!
        The callback function is reponsible for deciding which 
        chaining path to take, based on the data passed to it by the 
        CalcNextSection() member function. The CS_ChainCallbackData
        variables diridx and reverse must be set by the callback, 
        since these define the next chain segment section to add
        to the overall chaining curve. To abort the chaining process
        set diridx to -1.
     */
    CS_ChainCustomCallbackFunc cbfunc ; 

    // Class Methods

    CS_Chain() 
    {
        pStartRec = 0 ; 
        pcrTO   = 0 ; 
        pcrFROM = 0 ; 
        pchncrv = 0 ;
        maxSegCount = 0 ; 
        pendCrv = 0 ; 
        uend = 0.0 ; 
        chntol = FBepsilon ; 
        if (FBepsilon < COMPARETOLERANCE)
            chntol = COMPARETOLERANCE * 2.0 ; 
        chnmode = LEFT | WALKONCE ;
        lastDirection = CS_FORWARD ; 
        angtol = 1e-10 ; 
        revangtol = 0.0175 ; 
    } ; 

    ~CS_Chain() 
    {
        stklst.clear() ;
    } ; 

    //! Adds a chain CS_ChainREC to the curve chain node map
    /*!
        \param pcrv tthe curve to add the node to
        \param ucrv the u point on the curve at where the point is to be added
        \param epsilon amall u distance to move for vtanfwd and vtanrev
        \return pointer to the CS_ChainREC record created.

        If no chain node map exists for the curve then one is 
        created. If an existing CS_ChainREC is already defined
        at the point requested then a pointer to the record 
        is returned and nothing is modified. Otherwise a full
        stack node is created with a single new CS_ChainREC 
        entry. If a chain node map exists then the fwd and 
        reverse pointers are also connected up.

        The default epsilon value is the global defined parameters 
        value FBepsilon.
     */
    CS_ChainREC *AddChainRECToCurve(CS_Curve *pcrv, double ucrv, double epsilon=FBepsilon) ;

    //! Initializes the chaining stack nodes for the input intersections 
    /*!
        \param irlist input intersection record list to save into stack nodes
        \return the number of stack nodes currently defined.
        
        After intersecting the desired \a CS_Curve's together call 
        this function to initialize the chaining data structure.
        This will add the CS_ChnNde records to each curve as well
        as build the chaining stacks for each unique intersection 
        point that is generated. 
     */
    int AddIntersectDataToCurves(CS_IRECList &irlist) ;

    /*!
        \param pcrv pointer to curve whose chain node map is to be connected 
        by setting the forward reverse pointers. 
        \return Simply returns 0 (currently means nothing)
        
        Once all calls to AddChainRECToCurve(...) and AddIntersectDataToCurves(...)
        are complete, the last step is to set the pcrfwd and pcrrev pointers
        within the chain node maps. Thus a complete list of all curves involved
        must be maintained since we have to call this function for all the 
        curves that have matching chain stack information. Note we could 
        simply go through all the stack nodes, but this is more efficient
        since there could be multiple stacks referencing the same curve. 

        \todo See if getting rid of the forward and reverse pointers makes 
        sense since that information is already stored in the map. It would 
        make it impossible however for a user to follow custom node paths
        through overriding the standard forward/reverse pointers. This
        may prove useful so for now we'll leave as is even though it requires
        making this extra call. 
     */
    int SetFwdRevPointers(CS_Curve *pcrv) ;


    /*!
        Used by the boolean two curves operation. Goes through and for all ChainRECs
        it sets the pntFwdMid values. 
        
        NOTE: Before calling this function SetBoundingRect() must have been 
        called for each of the input curves being considered for chaining. 
     */
    int SetAllFwdMidPoints() ;


    /*!
        \param pcurnode the current node to walk from 
        \return The next set node pointer for creating a from-to 
        section pair. If direction is forward it returns the 
        next node in the list. If direction is reverse it returns
        the previous node in the list. If the curve is closed and 
        the next or prev is null, then the routine wraps around
        back to the start or the end and returns that node. 
        Otherwise, if the curve is open and we walk off an end
        based on the requested direction, then NULL is returned. 

        If pcurnode is NULL, the default to step along from pcrFROM, but if 
        pcurnode is defined, then the next step is taken from that
        node insted. 
     */   
    CS_ChainREC *NextChainRECNode(CS_ChainREC *pcurnode=0) ;

    /*!
        \param pbc main base curve to initiate chaining from
        \param ustart u value point to start chain from
        \param uend u value point where chain ends default=-1.0
        \param mode method of chaining default = LEFT|FORWARDONLY
        \param fp custom chaining callback function
        \return the resultant chained curve, caller must delete this curve

        Chains the curve from the starting u value to 
        the to the end point u value. If uend is negative, then 
        chaining continues until a closed loop 
        is formed or until we can't go any further. The mode controls 
        how the chaining functions, LEFT, RIGHT, TANGENT, CUSTOM.
        If CUSTOM, then a user defined custom callback function pointer
        must be passed into the routine. This can allow for custom 
        chaining methods as well. 
        To use this function make sure all the setup steps have been
        followed as outlined in the general chaining discussion. 

        Default mode is (LEFT | FORWARDONLY). The chaining is only designed to ever
        proceed in the forward direction initially. Once chaining has started,
        then it is possible to follow subsequent chaining sections in the reverse
        direction.

     */
    CS_Curve *ChainCurve(CS_Curve *pbc, double ustart, double uend = -1.0,
                         int mode=0, CS_ChainCustomCallbackFunc fp=0) ;

    //! Chain single loop from current piSetStartNode
    /*!
        \param pcrstart starting node for the chaining
        \param dir direction to follow from the starting node
        \param chainmode method for chaining
        \return see below
        
        Return values
        <ul>
            <li>0 - no chain curve created </li>
            <li>1 - created a chain record list that terminated normally
            <li>2 - may have created chain record list, but process terminated 
                    before a valid end contition was met</li>
        </ul>


        Completes a single chain loop based on the information  set in
        pisr which must be initialized to the start point. The chaining
        proceeds based on the mode specified. If CUSTOM mode is 
        selected, then the custom callback must be initialized. Failure
        to initialize the custom callback using CUSTOM mode will generate
        an error. The resultant chain curve is referenced by the member
        variable pchncrv. Returns 0 if a curve is chain successfully
        otherwise returns an error code. 
        
        If the CS_Chain::FORWARDONLY bit is set in the chainmode variable on 
        entry, then the chaining will only proceed in the forward direction
        along curve segments. Thus if a CS_Chain::LEFT | CS_Chain::FORWARDONLY
        is the input chainmode, and the chain must follow a reverse segment
        in order to chain left, then the routine aborts, and returns a 
        status code of 2. The partial chain curve is deleted in this case.

        If the curve is closed, or no more chaining sections can be found, 
        and the routine doesn't exit due to a reverse section as 
        described below, then the full closed or partial
        chained curve is returned with a status code of 1. 

        IMPORTANT: Make sure that the chn.mode flag to ALLOWREVERSALS is 
        set if it is expected to follow a path almost completely backwards
        (reverse direction) when following a curve chain. This is disabled
        by default, which has the effect of ignoring possible chaining paths
        where an accute angle of less than 1 degree or so will be created
        in the output chained curve. See revangtol for more information. 

        Note: after calling this the chnreclist now contains the 
        data needed to create the final chained curve. pchncrv will
        not contain the valid curve until BuildChainCurve() is called. 

        An example used to create the union of two closed curves is 
        as follows (this is the actual code from CS_UnionCurves(..) 
        with some of the error checking and special case handling 
        deleted for clarity).

        \verbatim

        int SimpleUnion(CS_Curve *pca, CS_Curve *pcb, CS_Curve **punioncrv)
        {
            pca->Complete(CCW) ; 
            pcb->Complete(CCW) ; 

            // Make use of chaining
            CS_IRECList ichainset ; 
            int nisects = pca->Intersect2D(pcb, &ichainset) ; 

            if (ichainset.size() == 0)
            {   // Test if one inside the other
                return DONOTINTERSECT ; 
            }

            // Otherwise we've intersected at 2 or more points, thus it is 
            // possible to walk around the outside of the shape to create the 
            // union of the two parts. 

            CS_Chain chn ; 
            chn.chntol = 0.001 ; 
            chn.AddIntersectDataToCurves(ichainset) ; 
            chn.SetFwdRevPointers(pca) ; 
            chn.SetFwdRevPointers(pcb) ; 
            chn.mode |= CS_Chain::ALLOWREVERSALS ;

            // Ideally we want to start on a section on one shape that is outside
            // of the other so that the first complete walk around gives us the final
            // result. To do this we find a chain section where the midpoint is outside
            // of the other curve. 
            // The chainnode map pcnmap attached to the curve is sorted by U value 
            // of the intersection points. Thus this can be used to figure out what
            // section is on the outside
            
            CS_ChnNodeMapItr icstart ;
            CS_ChnNodeMapItr ica = pca->pcnmap->begin() ; 
            CS_ChnNodeMapItr icb = ica ; 
            icb++ ; 

            if (icb == pca->pcnmap->end())
                return 0 ; // something went wrong. 

            double u = pca->UMid(ica->second.ucrv, icb->second.ucrv) ; 
            if (pcb->Inside(pca->UPoint(u)))
            {   // Then we want to start from the icb record node since the next
                // step in the forward direction from b will be outside of the
                // other curve. 
                icstart = icb ; 
            }
            else
            {   // Start from the ica record node, since the next step in the 
                // forward direction from the a node will be outside
                icstart = ica ; 
            }
               
            int chainret = chn.ChainLoop(icstart->second.pcr, CS_FORWARD, 
                                CS_Chain::RIGHT | 
                                CS_Chain::FORWARDONLY | 
                                CS_Chain::WALKONCE) ;

            if (chainret == 1)
                chn.BuildChainCurve() ;

            if (chn.pchncrv && chn.pchncrv->nodecnt > 1)
            {   // This is the final result curve that we want
                *punioncrv = chn.pchncrv ; 
                chn.pchncrv = 0 ; // 
                return SUCCESS ;
            }
            else if (pchncrv)
            {   // If there is a curve and it has only one node, then 
                // something went wrong, so delete it and signal error
                delete pchncrv ;
            }
            
            return NORESULT ; 
        }

        \endverbatim

        IMPORTANT: After performing a ChainLoop(...) operation on a set of curves
        there will be pcnmap data defined against these curves. If, another call 
        to ChainLoop(...) is required with the exact same set of curves, then 
        there is no need to reset the crv.pcnmap variables. If however the same 
        curve will be used later in a brand new ChainLoop operation, then make sure
        the pcnmap is deleted (with the \a delete operator) before calling the 
        AddIntersectDataToCurves(...) followed by ChainLoop since the chaining record
        nodes will point to invalid memory locations. 

     */
    int ChainLoop(CS_ChainREC *pcrstart, int dir, int chainmode) ;

    //! Chain all possible loops from the given list of chain records
    /*!
        \param pcnmap list of chain records to be processed 
        \param chaincrvs output set of chained loops
        \param chainmode the method to be used in doing the chaining

        Call ChainAllLoops(...) with the desired mode. The returned
        curve set will contain all possible closed loops associated
        with this base curve. If further loops with other curves are
        required it is possible to see what sections have not yet 
        been processed by checking the walkcount variable within 
        the CS_ChainREC records associated with those curves. Simply
        calling ChainAllLoops for each curve will guarantee that all
        possible loops have been generated once since ChainAllLoops
        skips intersection sets where walkcount != 0.
        To use this function make sure all the setup steps have been
        followed as outlined in the general chaining discussion.
     */
    int ChainAllLoops(CS_ChnNodeMap *pcnmap, CS_CurveSet &chaincrvs, int chainmode) ;

   
    /*!        
        \return pointer to the next CS_ChainREC node, which also defines 
        the end point of the curve section just added to the chain.

        Based on the pcrTO pointer and the direction, the next section
        of curve is added to the chain stack/list. AddChainSection() and 
        CalcNextSection(...) are intended to be used together.
     */   
    CS_ChainREC *AddChainSection() ; 

    /*!        
        Works out the next direction to follow while adding sections to 
        the chain curve. The pisncur and the direction variables are set
        properly for the next call to AddChainSection()
        Returns false when there are no more sections to be added, this
        determination is made by checking to see if the chain curve
        has been closed, or if there is no other chain section that 
        can be followed.
     */   
    int CalcNextSection(CS_ChainREC *pnxtrec=0) ; 


    //! Builds the pchncrv from the chnreclist that is currently defined
    /*!
        \return pointer to pchncrv, NULL is returned on error or if the 
        chnreclist is empty
     */
    CS_Curve *BuildChainCurve() ;

} ;





#endif