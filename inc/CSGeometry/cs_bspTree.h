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
// cs_bspTree.h
#ifndef __bspTree_h__
#define __bspTree_h__

#include "cs_plane.h"
#include "cs_polygon.h"

//! Polygon data structure used during BSP tree processing
/*!
    The polygons that are created during processing are stored in a vector
    array structure which simply grows larger and is never destroyed until 
    the entire array is not needed. Then the polygon that is being referenced
    can be called by it's index in the array. Depending no the number of 
    polygons used, finite element grid can be made up of:
    
            #Bytes For Index     Max# of Polygons  
                    1                   256 
                    2                16,384  
                    3            16,777,216
                    4         4,294,967,296 

    During processing, if a polygon needs to be split, then the original is
    kept, and one new polygon generated which is added to the end of the 
    array. For performance reasons, you probably want to stick with 1,2,4,8
    etc... bytes per grid plane position. 

    Then all we need is to pass around a list of integers instead of a list
    of complete polygon data structures or pointers. 

    The only reason we resort to integers and not pointers is so that we can 
    conserve memory when the number of polygons is quaranteed less than 16,000.
 */
struct CS_BSPPolygon
{
    // Member variables
    
    //! index in the master polygon list
    // int idx ; 
    CS_PLANE pln ; 

    //! The poly3D transformed to the plane coordinate space,
    //! This polygon is created and deleted internally. 
    CS_Polygon *poly ; 

    //! The defining input polygon, the pointer poassed in must be valid 
    //! for the duration of processing as only the pointer is saved. Must
    //! be freed externally. 
    CS_Polygon *poly3D ;

    // Used in polygon list selection
    CS_POINT centroid ; 
    double area ; 

    //! coordinate system transformation from ABS to PLN coords
    CS_MTX4 mxap ; 

    //! coordinate system transformation from PLN to ABS coords
    CS_MTX4 mxpa ; 

    // ======================
    //     Member functions
    // ======================

    CS_BSPPolygon() ; 
    ~CS_BSPPolygon() ; 

    //! Initialize this polygon structure with the input crv
    int Init(CS_Polygon *ppoly) ; 

} ;


typedef vector<CS_BSPPolygon> CS_BSPPolygonVec ; 


//! this list is used during the construction of the BSP tree. 
typedef list<int> CS_BSPIntList ; 
typedef list<int>::iterator CS_BSPIntListItr ; 


//! BSP Tree node structure
/*! 
    A tree node is defined by the plane that the polygon lies on 
    as well as the polygon vertices on that plane. During processing
    the thing we want to know most of the time is whether a projected
    point onto the polygon's plane lies inside or outside of the 
    polygon on that plane. This is done in the 2D coordinate system 
    of the plane. The 2D polygon is represented by the poly2D 
    member variable. (TODO - create a fast 2D polygon representation
    with fast indside/outside determination). 

*/
struct CS_BSPTreeNode
{
    //! list of polygon indexes
    /*!
        All CS_BSPPolygon data is maintained in the CS_BSPTree polyvec member
        variable which is then accessed by an index offest. The index offsets
        are stored in pil as a list so that the lists can be easily added to
        and deleted from as the tree is build. If new polygons have to be
        created during a split, then the front polygon is the modified 
        original and the back polygon is the newly created one that is added
        to the end of the polyvec master set. 
     */
    CS_BSPIntList pil ; 

    CS_BSPTreeNode *pParent ; 
    CS_BSPTreeNode *pBackChild ; 
    CS_BSPTreeNode *pFrontChild ; 

    // Member functions.
    CS_BSPTreeNode() ; 
    ~CS_BSPTreeNode() ; 
} ;


class CS_BSPTree ; 

typedef int (*CS_BSPRenderFunction)(CS_BSPTree *, CS_BSPTreeNode *)  ; 

//! BSP Tree class (Binary Space Partition Tree)
/*!
    Class controls and manages the building of a BSP tree. To use this class
    there are some initialization steps required. Below is an example template
    required to use this class. 

    \verbatim

    // 
    CS_BSPTree bsptree ; 

    // Fill in here as required
    while (for each polygon p in set)
    {
        CS_BSPPolygon bsppoly ; 
        bsppoly.Init(p) ; 
        bsptree.polyvec.push_back(bsppoly) ; 
    }

    bsptree.MakeTree() ;

    // Now ready to use bsptree 

    \endverbatim


    In an attempt to minimize memory manipulation of polygons during processing, 
    all the polygons are stored within the polyvec member of of the master BSP 
    tree. Then indexes into that vector array are used to reference the polygon
    of interest. The other option is to use pointers, but in later processing 
    we want to be able to reference a specific polygon with a 16 bit int to 
    reduce memory requirements. The reason is that during the projectiong to 
    viewing plane stage where a particular view based on the BSP tree is being
    generated, a brute force pixel overwrite will be done which will store the
    index of the polygon in the "pixel" map. Thus the pixel map, which will 
    operate at a user defined resolution, will contain the polygon index that
    is visible at that pixel location. 
    
    So at some point this integer mapping will be required, which is why 
    pointers are not being used to reference the polygons. TODO - see if it
    is more efficient to use pointers initially and then introduce the index
    mapping in the later stages. The trade off will be in how many times
    the mapping function needs to be performed based on the different models. 

    This means that polyvec should only ever be added to so that indexes 
    always remain valid. Removing an entry from the middle of the polyvec 
    array will invalidate all index references after that point. 
    
 */
class CS_BSPTree
{
public:
    // MEMBER VARIABLES
    
    //! Used to indicate internal error conditions
    int errorState ; 

    enum {
        BSP_MEMORY_ERROR        = 0x0001,
        BSP_ABORT_DISPLAY       = 0x0002, 
    } ; 

    //! the root node of the tree. 
    CS_BSPTreeNode *pRootNode ; 

    //! count of the number of nodes in the tree
    int nNodes ; 

    //! This is the master set of polygons used during processing. 
    CS_BSPPolygonVec polyvec ; 

    //! This is the list of polygon indexes used during processing 
    CS_BSPIntList polylist ; 

    //! This is the current view point during display operations
    CS_POINT viewPnt ; 

    // MEMBER FUNCTIONS

    CS_BSPRenderFunction renderFunc ; 

    CS_BSPTree() ; 
    ~CS_BSPTree() ; 

    void DeleteTree(CS_BSPTreeNode *pnode) ; 


    // Recursively build the BSP tree. 
    /*!
        \return the number of nodes in the resulting tree

        Resets errorState to 0 on statup. 
     */
    int MakeTree() ;

    //! Recursively build the BSP tree
    /*!
        \param pparent pointer to the parent node
        \param polylist current list of polygons that will define this branch
        \return pointer to the node just created, null is polylist is empty

        Returns pointer to node created, whereby the polylist is completely 
        subdivided or split into child nodes. If the polylist is empty on 
        entry then nothing is done and null is returned. 

        Polylist will always be empty when this function returns. 
     */
    CS_BSPTreeNode *MakeBranch(CS_BSPTreeNode *pparent, CS_BSPIntList &polylst) ;


    //! Uses a simple heuristic to select the next spliting plane 
    /*!
        \param polyvec the input set of polygons to search
        \return iterator to the polygon removed from polylst 

        Goes through the list and finds a plane that is in the middle 
        of the other planes based on the polygon centroid. This plane
        is then extracted from the input polylist and it's pointer is
        returned. 
     */
    int  SelectNextSplit(CS_BSPIntList &polylist) ;  


    // Returns the polygon with the greatest area. 
    int CS_BSPTree::SelectNextSplitByArea(CS_BSPIntList &polylist) ; 

    //! Test the input polygon against plane and split if needed
    /*! 
        \param iref index of reference CS_BSPPolygon
        \param itst index of CS_BSPPolygon to test against iref
        \param ifront index to front polygon
        \param iback index to back polygon 
        \return returns the side bit flag status of the input polygon
        
        All the points in the polygon pp are tested against the this->pln 
        
        The following bit flags can be returned. 
        <ul>
            <li>CS_POINT_ON_PLANE     = pnt was on the plane, thus pnt is the returned point
            <li>CS_POINT_ABOVE_PLANE  = pnt was above the plane
            <li>CS_POINT_BELOW_PLANE  = pnt was below the plane
        </ul>

        If the return value indicates the points above and below the plane, 
        then both ifront and iback will be defined where ifront will be a 
        modified version of ipt, and iback will be the index of the back split 
        polygon that was just added to the polvec array. 
        
        If the only return side bit flag set is CS_POINT_ON_PLANE, then that means 
        the test polygon was on the same plane as the input plane in which case that 
        polygon should be added to this nodes pil polygon list. In this case neither
        ifront or iback will be set. 

        In all other cases ifront and/or iback will be set based on the above or 
        below plane status flags.

        NOTE: Currently only works with regular convex polygons. 
        
        TODO - extend to concave polygons
     */
    int PlaneTestNSplit(const int iref, const int itst, int &ifront, int &iback) ;


    //! Returns the overall centroid of the polygon list's centroids
    CS_POINT PolygonListCentroid(CS_BSPIntList &polylist) ;

    //! Display the tree
    /*!
     */
    void Display() ; 

    //! Display the BSP tree starting from the designated root node
    void DisplayBranch(CS_BSPTreeNode *pnode) ;

    //! Perform actual visualization rendering for this node
    /*!
        \param pnode pointer to the node to be rendered
        \return error code, 0=OK

        The member variable renderFunc must be set as a pointer to a valid 
        function to perform the rendering. The default is to return and do
        nothing. 
     */
    int RenderNode(CS_BSPTreeNode *pnode) ;

} ; 

// Support Functions
#endif