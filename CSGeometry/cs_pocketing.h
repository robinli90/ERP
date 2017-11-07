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
// cs_pocketing.h - 2-1/2D Milling pocketing operations

#ifndef __CS_POCKETING_H__
#define __CS_POCKETING_H__

// The ToolPathTree is an N-ary tree structure where each node 
// represents a single tool path loop (one complete loop pass
// for the overall toolpath)

class CS_TPTNode 
{
public:
    CS_Curve *pcrv ; 
    CS_Curve *pwrkcrv ; // copy of pcrv that is used for offsetting
    CS_TPTNode *parent ; 
    CS_TPTNode *offsnodes ; // offsets contained within this node
    int nOffsets ; // number of offsnodes defined.
    int depth ; 

    CS_TPTNode()
    {
        pcrv = 0 ; 
        pwrkcrv = 0 ; 
        parent = 0 ; 
        offsnodes = 0 ; 
        nOffsets = 0 ; 
    } 

    ~CS_TPTNode()
    {
        if (pcrv)
            delete pcrv ; 
        if (pwrkcrv)
            delete pwrkcrv ; 
        // Note offsnodes are deleted outside of this class
    } 
} ;

class CS_Pocketing
{
public:
    enum PocketType
    {
        CONTOUR_POCKETING   =   0x0001,
        ZIGZAG_POCKETING    =   0x0002
    } ;

    int maxDecentDepth ;
    int maxdepth ; 
    int mode ; 
    double toolrad ; // radius of tool
    double stepPercentage ; // step for each cut pass
    double zrapid ; // non cutting sections at this height
    double zcut ;   // cutting sections at this depth

    // The output curve is used when building the output toolpath. It
    // is also used by the debug function LoopsToCurves()
    CS_Curve *pOutputCurve ; 

    // topnode is the top of the toolpath tree. All toolpaths are 
    // created after the tree has been fully constructed.
    CS_TPTNode *topnode ; 

    CS_Curve *pBndCurve ;   // the main input outside boundary curve
    CS_CurveSet *pIslandCurveSet ; // input island curve set
    
    // Temporary working curve sets which defines the island offsets
    // as the island curves are intersected, they are removed from the 
    // island set.
    CS_CurveSet islandSet ; // working island curve set

    // Class methods
    CS_Pocketing() ;
    ~CS_Pocketing() ; 

    // Recusively work through the tree freeing up all curves and 
    // node definitions. 
    void DeleteTree(CS_TPTNode *pnode) ; 

    // CS_ContourPocket() does the initial setup required for generating
    // the pocketing toolpath. The last thing it does is call OffsetNode()
    // which recursively builds the toolpath tree.
    void ContourPocket(CS_Curve *bndcrv,
                       CS_CurveSet *islands, 
                       CS_Curve *toolpathcrv) ;


    // This is where the bulk of the work is done in generating the 
    // contour pocketing toolpath. The toolpath tree is built by
    // recursively calling the OffsetNode() function for each loop
    // that is created. Each loop is represented by a single node 
    // in the tree.
    int OffsetNode(CS_TPTNode *pnode) ; 

    // Intended for debugging use. Walks the entire tree and generates
    // a curve segment for every single segment in the tree. The result
    // is a discontinuous (disjoint) crv with unjoined tool path loops.
    // This routine calls AddNodeToOutputCurve() which adds segments 
    // from the inside out. 
    int LoopsToCurves(CS_Curve &crv) ; 

    // Recursive function called by LoopsToCurves()
    int AddNodeToOutputCurve(CS_TPTNode *pnode) ; 
} ;


#endif