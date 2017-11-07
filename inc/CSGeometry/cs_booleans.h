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
// cs_booleans.h

#ifndef __CS_BOOLEANS_H__
#define __CS_BOOLEANS_H__

// Search on Bool2D 


struct BoolCurveNode
{
    CS_Curve *pcrv ; 
    BoolCurveNode *prev, *next ; 
} ; 

class BoolCrvLst
{
public:
    BoolCurveNode *pStart, *pEnd ; 

    BoolCrvLst() 
    {
        pStart = pEnd = 0 ; 
    }

    BoolCurveNode *AddNode(CS_Curve *pc)
    {
        BoolCurveNode *pnew = new BoolCurveNode ; 
        pnew->pcrv = pc ; 
        if (!pStart)
        {
            pnew->prev = 0 ; 
            pnew->next = 0 ;
            pStart = pEnd = pnew ; 
            return pnew ; 
        }

        pEnd->next = pnew ; 
        pnew->prev = pEnd ; 
        pnew->next = 0 ; 
        pEnd = pnew ; 

        return pnew ; 
    }

    // Delete node and return point to the next node after the deleted node
    BoolCurveNode *DelNode(BoolCurveNode *pdel, int keepCurve=0)
    {
        BoolCurveNode *prev = pdel->prev ; 
        BoolCurveNode *next = pdel->next ; 
        if (!keepCurve)
            delete pdel->pcrv ; // de-allocate the curve in the node
        delete pdel ; // delete the node itself

        if (prev)
        {
            prev->next = next ; 
        }
        else
        {   // Deleted the start node
            pStart = next ; 
        }

        if (next)
        {
            next->prev = prev ; 
        }
        else
        {   // Deleted the end node
            pEnd = prev ; 
        }

        return next ; 
    }
} ;


//! Create an outer boundary of two input curves
/*!
    \param pca first input curve
    \param pcb second input curve
    \param pcu  output unioned curve, if not null then free memory with delete 
    \param holeSet resultant holes within the final output region
    \return status code

    Take the two input curves and if one is completely inside the other
    then return the outer curve. If they intersect then return the outer 
    envelope of the two curves. 

    If the two curves are disjoint, then do nothing and don't allocate 
    any memory for pcu

    <ul>
    <li>If A and B intersect returns 0x01</li>
    <li>If B is inside A     returns 0x02, pcu is a copy of a</li>
    <li>If A is inside B     returns 0x04, pcu is a copy of b</li>
    <li>A and B completely overlap  returns 0x06, thus A and B are the same, pcu is a copy of A</li>
    <li>If A and B touch at a single point returns 0x08, does nothing</li>
    <li>If A and B are not connected returns 0, does nothing</li>
    </ul>

    Thus a return value of 0 indicates that nothing happened.
    
    A mask of 0x07 can be used to see if pcu was set during the 
    process. 

    If the curves touch at a single point then nothing happens (pcu 
    is not defined) and the function returns 0x08.

    This calls ChainLoops(...) internally, so the pcnmap will be modified.
    If multiple calls to UnionCurves(...) are made, then you must reset the
    pcnmap parameter through a crv.ClearChaining() call. 
 */
int CS_UnionCurves(CS_Curve *pca, CS_Curve *pcb, CS_Curve **pcu, CS_CurveSet &holeSet) ;


//! Create the largest possible collection of containing curves
/*!
    \param inset input set of curves to UNION
    \param outset the generated set of output curves
    \param holeset any holes that result in the output union regions
    \return number of curves in the output set. 

    Any intersecting curves in the input set are connected together 
    into single closed loops of the overall enclosing curve (the union)
    of the intersecting curves. This is done two at a time until 
    everything has been tested against everything else. 

    The inset curves are not affected through this process. 

    It is the responsibility of the calling function to deallocate
    the outset curves. this can be done with a call of outset.clear() 

    This is an updated version of the CS_Curve::Union() function which
    makes use of the old offset intersection routines. This version 
    makes use of the newer chaining functions through chaining records
    and chain stack nodes. 

    No further development will be done on the older version, this version
    is the one to use for all future applications. 

    This works through O(n.log(n)) union operations between two curves. 
    It simply calls CS_UnionCurves(...) repeatedly, attempting to join 
    each input curve with every other curve. The final set contains the 
    largest possible join curves, for curves that do not intersect with
    others, individual sets are returned. Thus this is not a overall
    convex hull type operation. 

    Note: there will only be holes if there are resultant curves in the outset. 
    If the outset is empty, then holes are not possible. 
 */
int CS_UnionCurveSet(CS_CurveSet &inset, CS_CurveSet &outset, CS_CurveSet &holeset, double *tol=0) ;


//! Subtract the curves in csB set from crvA, and output results to diffSet and holes
/*!
    \param crvA main input curve that everything is subtracted from
    \param csB the curves that are to be subtracted from A
    \param diffSet the final output result set
    \param holes curves defining a subtracted area contained within one of diffSet curves
    \return 0=OK, else an error code. 

    If there are curves defined in the holes curve set, then the pUserData parameter for
    each of those curves will be a CS_Curve pointer to the curve within diffSet that 
    contains the hole curve. 

    During processing, crvA is not modified, all csB curves are set CW, but are otherwise left alone. 

 */
int CS_CurveSetDiff(CS_Curve &crvA, CS_CurveSet &csB, CS_CurveSet &diffSet, CS_CurveSet &holes) ; 

//! Unions the B set before subtracting
int CS_CurveSetDiff2(CS_Curve &crvA, CS_CurveSet &csB, CS_CurveSet &diffSet, CS_CurveSet &holes) ;


#endif 