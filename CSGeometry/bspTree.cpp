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
// bspTree.cpp


#include <assert.h>
#include "cs_bspTree.h"


// ======================================================================
//          BSP Tree Node Class Member Functions
// ======================================================================
CS_BSPTreeNode::CS_BSPTreeNode()
{
}


CS_BSPTreeNode::~CS_BSPTreeNode()
{
}



// ======================================================================
//          BSP Tree Class Member Functions
// ======================================================================

CS_BSPTree::CS_BSPTree() 
{
    errorState = 0 ; 
    pRootNode = 0 ; 
    nNodes = 0 ; 
    renderFunc = 0 ; 
}

CS_BSPTree::~CS_BSPTree()
{
    DeleteTree(pRootNode) ; 
}

void CS_BSPTree::DeleteTree(CS_BSPTreeNode *pnode)
{
    if (!pnode)
        return ; 

    DeleteTree(pnode->pBackChild) ; 
    DeleteTree(pnode->pFrontChild) ; 

    nNodes-- ; 
    delete pnode ; 
}

// Build the BSP tree. 
int CS_BSPTree::MakeTree()
{
    //! Add initialization steps here if required. 
    errorState = 0 ; 
    if (pRootNode)
        DeleteTree(pRootNode) ; 
    pRootNode = MakeBranch(0, polylist) ; 
    return nNodes ; 
}

// Recursively build a branch of the BSP tree. 
CS_BSPTreeNode *CS_BSPTree::MakeBranch(CS_BSPTreeNode *pparent, CS_BSPIntList &polylst) 
{
    if (polylist.size() == 0)
        return 0 ; 

    // get center polygon and use this as the split plain
    CS_BSPTreeNode *pnode = new CS_BSPTreeNode ; 
    if (!pnode)
    {
        errorState = BSP_MEMORY_ERROR ; 
        return 0 ; // memory allocation error
    }

    int isplit = SelectNextSplit(polylist) ;
    pnode->pil.push_back(isplit) ;  

    CS_BSPIntList *backlist = new CS_BSPIntList ; 
    CS_BSPIntList *frontlist = new CS_BSPIntList ; 

    int side ; 
    int ifront, iback ; 

    CS_BSPIntListItr ipl = polylist.begin();
    
    while (ipl != polylist.end())
    {
        int ip = *ipl ; 
        side = PlaneTestNSplit(isplit, *ipl, ifront, iback) ;
        if (side == CS_POINT_ABOVE_PLANE ||
            side == CS_POINT_INFRONT)
        {
            assert(ifront >= 0) ;
            frontlist->push_back(ifront) ; 
        }
        else if (side == CS_POINT_BELOW_PLANE ||
            side == CS_POINT_INBACK)
        {
            assert(iback >= 0) ;
            backlist->push_back(iback) ; 
        }
        else if (side & CS_POINT_ABOVE_PLANE && 
                 side & CS_POINT_BELOW_PLANE)
        {   // Then we split the poly with the plane
            assert(ifront >= 0) ;
            frontlist->push_back(ifront) ; 

            assert(iback >= 0) ;
            backlist->push_back(iback) ; 
        }
        else if (side == CS_POINT_ON_PLANE)
        {
            pnode->pil.push_back(*ipl) ; 
        }
        else
            assert(0) ; // something went wrong

        ipl = polylist.erase(ipl) ; 
    }

    pnode->pParent = pparent ;

    pnode->pBackChild = MakeBranch(pnode, *backlist) ; 
    pnode->pFrontChild = MakeBranch(pnode, *frontlist) ; 

    delete frontlist ; 
    delete backlist ; 

    return pnode ; 
}

// returns the side that the input polygon is relative to this->pln
int CS_BSPTree::PlaneTestNSplit(const int iref, const int itst, int &ifront, int &iback) 
{
    // Initialize the return indexes. 
    ifront = -1 ; 
    iback = -1 ; 

    CS_BSPPolygon *pbpref = &polyvec[iref] ;
    CS_BSPPolygon *pbptst = &polyvec[itst] ;

    if (pbpref->pln == pbptst->pln) 
        return CS_POINT_ON_PLANE ; // then the polygons are on the same plane

    CS_Polygon *pref = pbpref->poly3D ; // simplify referencing this member
    CS_Polygon *ptst = pbptst->poly3D ; // simplify referencing this member

    /*!
        If itst is on the same plane as iref, then neither ifront or iback
        will be set, and CS_POINT_ON_PLANE will be returned.
     */
    
    //! start and end points of current line segment 
    /*
        Work through all polygon segments and save plane intersection points

        If the polygon has multiple lines segment on the plane and is not 
        completely on the plane, then the only way for this to happen and
        be valid is if there are multiple line segments on the test 
        polygon curve that are co-linear. Only penetrations through the 
        polygon will be considered for splitting up the test curve. 
     */

    CS_CrvPntRecLst cpl ;
    int nisect = 0 ;

    CS_POINT ipnt ; // intersection point
    int isecstat = 0 ;
    double uis ;

    int aboveCount = 0 ; 
    int belowCount = 0 ;

    CS_LineSeg *pls = (CS_LineSeg *)ptst->pStart ;

    while (pls)
    {
        int istat = pbpref->pln.Intersect(*pls, ipnt, &uis) ;

        if (istat & CS_POINT_ABOVE_PLANE)
            aboveCount++ ; 
        if (istat & CS_POINT_BELOW_PLANE)
            belowCount++ ; 

        isecstat |= istat ;
        
        if (istat == 0)
        {   // Line intersects the plane
            CS_CrvPntRec cp ;
            cp.s = pls ;
            cp.u = uis ;
            cp.p = ipnt ; 
            cpl.push_back(cp) ;
        }
    }

    CS_DeleteCommonCrvPntRecs(cpl) ; // get rid of redundant information

    // Now do the split
    if (cpl.size() < 2)
    {   // Then there were no clean intersections which means that the
        // test polygon is either completely in front or behind the plane
        if (aboveCount > belowCount)
            ifront = itst ;
        else
            iback = itst ;
    }
    else
    {   // There were intersections, thus split and reconnect the
        // itst plane and create the inew plane, then allocate them
        // to the front and back as required. 
        assert(cpl.size() == 2) ; // TODO - trap this and recover
        
        CS_CrvPntRecLstItr i1, i2 ; 
        i1 = cpl.begin() ; 
        i2 = i1 ; 
        i2++ ; 
        CS_Polygon *ppnew = new CS_Polygon ; 
        pbptst->poly3D->Slice(*i1, *i2, ppnew) ; 
        pbptst->Init(pbptst->poly3D) ; 

        CS_BSPPolygon bsppoly ; 
        bsppoly.Init(ppnew) ; 

        int sidetst = pbpref->pln.PointSide(pbptst->centroid) ; 
        int sidenew = pbpref->pln.PointSide(bsppoly.centroid) ; 

        assert((sidetst | sidenew) == 
               (CS_POINT_ABOVE_PLANE | CS_POINT_BELOW_PLANE)) ; 

        if (sidetst & CS_POINT_ABOVE_PLANE)
        {
            ifront = itst ; 
            iback = (int)polyvec.size() ; 
        }
        else
        {
            ifront = (int)polyvec.size() ; 
            iback = itst ; 
        }

        // Now add bsppoly to the end, which will give it the proper index
        polyvec.push_back(bsppoly) ; 
    }

    return isecstat ; //  return plane intersection status
}


CS_POINT CS_BSPTree::PolygonListCentroid(CS_BSPIntList &polylist)
{
    CS_POINT centroid(0,0,0) ; 
    int n = 0 ; 
    CS_BSPIntListItr ipl = polylist.begin() ; 
    while (ipl != polylist.end())
    {
        centroid = centroid + polyvec[*ipl].centroid ; 
        n++ ; 
        ipl++ ; 
    }

    if (n > 0)
        centroid = centroid * (1.0/(double)n) ; 

    return centroid ; 
}


//! extracts the polygon whose centroid that is closest to the center 
//! of the point cloud of centroids defined by the input polylist
int CS_BSPTree::SelectNextSplit(CS_BSPIntList &polylist) 
{
    CS_POINT centroid(0,0,0) ;
    centroid = PolygonListCentroid(polylist) ; 

    // Now look for the polygon whose centroid is closest to the point cloud centroid 
    // for the input polylist
    double r, rmin = 9e99 ; // large number
    CS_BSPIntListItr ipmin = polylist.end() ; 
    
    CS_BSPIntListItr ipl = polylist.begin() ; 
    while (ipl != polylist.end())
    {
        r = CS_Distance(centroid, polyvec[*ipl].centroid) ; 
        if (r < rmin)
        {
            ipmin = ipl ; 
            rmin = r ; 
        }
        ipl++ ; 
    }

    int retidx = -1 ; 
    if (ipmin != polylist.end())
    {
        retidx = *ipmin ; 
        polylist.erase(ipmin) ;
    }

    return retidx ; 
}

//! Select split by max area
int CS_BSPTree::SelectNextSplitByArea(CS_BSPIntList &polylist) 
{
    // Now look for the polygon whose centroid is closest to the point cloud centroid 
    // for the input polylist
    double a ; 
    double areamax = 0 ; 
    CS_BSPIntListItr ipmin = polylist.end() ; 

    CS_BSPIntListItr ipl = polylist.begin() ; 
    while (ipl != polylist.end())
    {
        a = polyvec[*ipl].area ; 
        if (a > areamax)
        {
            ipmin = ipl ; 
            areamax = a ; 
        }
        ipl++ ; 
    }

    int retidx = -1 ; 
    if (ipmin != polylist.end())
    {
        retidx = *ipmin ; 
        polylist.erase(ipmin) ;
    }

    return retidx ; 
}

void CS_BSPTree::Display()
{
    errorState &= ~BSP_ABORT_DISPLAY ; 
    DisplayBranch(pRootNode) ; 
}

void CS_BSPTree::DisplayBranch(CS_BSPTreeNode *pnode)
{
    if (!pnode || 
        (errorState & BSP_ABORT_DISPLAY))
    {
        return ; 
    }

    // Note each node must have at least the first polygon defined
    if (polyvec[*(pnode->pil.begin())].pln.PointSide(viewPnt) & CS_POINT_ABOVE_PLANE)
    {   // In front
        DisplayBranch(pnode->pBackChild) ; 
        RenderNode(pnode) ; 
        DisplayBranch(pnode->pFrontChild) ; 
    }
    else
    {   // In back
        DisplayBranch(pnode->pFrontChild) ; 
        RenderNode(pnode) ; 
        DisplayBranch(pnode->pBackChild) ; 
    }
} 


int CS_BSPTree::RenderNode(CS_BSPTreeNode *pnode)
{
    if (!renderFunc || (errorState & BSP_ABORT_DISPLAY))
        return 0 ;

    return renderFunc(this, pnode) ; 
}
