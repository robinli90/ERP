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
// cs_offsoval.h - structure for storing the offset ovals


#ifndef __CS_OFFSOVAL_H__
#define __CS_OFFSOVAL_H__
/**
  An oval is simply that a shape that looks like an oval.
  Typically it will be made up of a base curve and offset
  curve and then two semicircle end node curves. For Reflex
  point type ovals we end up with a zero length base curve
  and thus the oval becomes a pie wedge. But to keep things
  consistent, these pie wedges will still be store in the 
  oval structure. 

    CS_OVAL_PIEWEDGE   - this oval section is defined by 
        a pie wedge meaning that there is no base curve. The base
        curve is simply defined by a point. 

    CS_OVAL_CLIPPEDALL - set when an offset segment has been 
        completely clipped out of the final result curve. Thus
        if this bit is set we don't have to worry about further
        clip testing or checking to include this during the line
        stitching process in the last step
 */

//* Oval status definition bits
#define CS_OVAL_PIEWEDGE    0x00000001
#define CS_OVAL_CLIPPEDALL  0x00000002
#define CS_OVAL_LEFTOFFSET  0x00000004
#define CS_OVAL_RIGHTOFFSET 0x00000008


// MERGE_NONE means no merge took place
// MERGED     means that the range was merged (but not necessarily modified)
// CHANGED    the u parm pair was modified during the merge
// FULLRANGE  the u parm pair defines the full [0,1] range
struct UParameterPair 
{
    enum StatusBits 
    {
        MERGE_NONE    =    0,
        MERGED        =    0x0001,
        FULLRANGE     =    0x0002,
        CHANGED       =    0x0004,
        UA_ISECT_BASE =    0x0010,  //!< ua point intersects base curve
        UB_ISECT_BASE =    0x0020,  //!< ub point intersects base curve
        OVERLAP       =    0x0100,  //!< the range overlaps 
        DELETE_B      =    0x4000   //!< status code returned
    } ;
    unsigned int status ; // OR of above values
    double ua, ub ; 
    UParameterPair() {} 
    UParameterPair(double a, double b) 
    {
        ua = a; 
        ub = b; 
        if (tcomp_EQZ(ua) && tcomp_EQ(ub, 1.0))
            status = FULLRANGE ; 
        else
            status = 0 ; 
    } 

    UParameterPair(double *pp) 
    {
        ua = *pp ; 
        ub = *(pp+1); 
        if (tcomp_EQZ(ua) && tcomp_EQ(ub, 1.0))
            status = FULLRANGE ; 
        else
            status = 0 ; 
    } 

    int operator==(UParameterPair &b) 
    {
        if (ua == b.ua)
            return 1 ; 
        return 0 ; 
    }

    int operator<(UParameterPair &b) 
    {
        if (ua < b.ua)
            return 1 ; 
        return 0 ; 
    }

    int operator>(UParameterPair &b) 
    {
        if (ua > b.ua)
            return 1 ; 
        return 0 ; 
    }

    // Used to merge parameter pairs together in the oval cliplist
    int MergeRange(UParameterPair *ppb) ;
} ;

typedef list<UParameterPair> UParmPairList ;
typedef list<UParameterPair>::iterator UParmPairListItr ;

struct CS_Oval 
{
    int status ; 

    // Pointer the base curve segment node. If this is a pie wedge
    // oval then it points to the first curve of the two curves 
    // that make up the reflex corner. 
    CS_SegPtr pbseg ; 

    //* The oval offset segment shares the same direction as the base
    //* curve that it is based on. Thus the four segments in the oval
    //* are not all oriented to form a continuous walkable loop. The 
    //* offset segment is always in the reverse direction. 
    CS_SegPtr poseg ; 

    // The two semicircular end nodes. These are undefined for pie wedges
    // and thus waste space in those situations.
    CS_ArcSeg arcA ; // arc at the start of the base curve
    CS_ArcSeg arcB ; // arc at the end of the base curve

    CS_RECT ofsrect ; // bounding rect for the offset curve
    CS_RECT bndrect ; // bounding rectangle for entire oval 
    UParmPairList clipList ; 

    CS_Oval() 
    {
        poseg = 0 ; 
    }

    CS_Oval(const CS_Oval &o) 
    {
        status  = o.status ; 
        pbseg   = o.pbseg ; 
        poseg   = o.poseg ; 
        arcA    = o.arcA ; 
        arcB    = o.arcB ; 
        ofsrect = o.ofsrect ; 
        bndrect = o.bndrect ; 
        clipList = o.clipList ; 
    }
    

    ~CS_Oval()
    {
        if (poseg)
            delete poseg ; 
    }


    //* returns reference to the expanded oval rectangle
    CS_RECT &SetBoundingRects() ; 

    // Adds to this members clipping list based on what portions 
    // lie inside the oval pointed to by poval.
    int AddToClipList(CS_Oval *poval) ;

    //* returns true if the test point pnt is on or inside the oval 
    //  Note: for borderline cases this test can return true 
    //  even though the line lies outside yet didn't intersect
    //  any of the oval curves. 
    //  TO DO - either make the inside test more robust, or 
    //  improve the intersection routines. Or test multiple
    //  points to make sure the Inside() test is returning
    //  the desired result.
    int Inside(CS_POINT &pnt) ;
} ;

typedef list<CS_Oval> CS_OvalList ; 
typedef list<CS_Oval>::iterator CS_OvalListItr ; 

struct CS_OvalArrayNode 
{
    CS_OvalArrayNode *prev, *next ; 
    CS_Oval          *poval ; 
} ;


#endif