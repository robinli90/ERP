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
// cs_adjobjs.h - adjacent polygon structure definitions


#ifndef __CS_ADJOBJS_H__
#define __CS_ADJOBJS_H__

#include "cs_curves.h"


class CS_PolyAdjObj : public CS_AdjacencyObject
{
public:
    CS_Curve *pcrv ; 

    // Class methods
    CS_PolyAdjObj() { pcrv = 0 ; } ; 
    virtual ~CS_PolyAdjObj() { pcrv = 0 ; } ; 

    // pda and pdb point to the CS_Segments that matched when the 
    // call returns true. 

    //!
    /*!
        \param obj adjacency object to test against
        \param pda set to last matching segment found on this->pcrv
        \param pdb set to last matching segment found on obj.pcrv
        \return Returns count of the number of segment edges that overlap

        The obj passed in must be the same type (CS_PolyAdjObj)or else
        everthing breaks. If the two polygons (which are represented 
        by CS_Curve's) share a common edge, then true is returned
        otherwise false is returned.
        Note: for these polygons, if the testing is occuring after 
        a ChainAllLoops() call, then we could also simply test the 
        parent segment pointers (psna->pParent) which will not
        point back to the psna CS_Segment but instead will point back to 
        the segment node of the curve that the chain segment originally
        occured in. The only danger here is if two separate curves 
        followed different overlap segments during generation. If this
        occurs then the chained segments would overlap but would 
        be derived from different curves and thus have different 
        parent segment node pointers in the two chained curves. Before
        chaining a filter needs to be called that removes any duplicate
        overlapping curve sections. Then this routine could be optimized
        to only test parent pointers, and not have to perform expensive
        intersections all over again. 
        TO DO - create two different SharesEdge() type call based 
          on a mode variable, one that does full intersections, and 
          one that test parent segment node pointers.
        Returns: true if they share an edge, stops on the first edge 
        match found. This runs in O(N*M) time. 
     */
    virtual int SharesEdge(CS_AdjacencyObject &obj, void **pda, void **pdb) ; 

    //! See SharesEdge(CS_AdjacencyObject &obj, void **pda, void **pdb)
    virtual int SharesEdge(CS_AdjacencyObject *pobj, void **pda, void **pdb) ; 
} ;





#endif



