/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/

// mtavltree.cpp

#ifndef __MTAVLTREE_H__

#define __MTAVLTREE_H__

#include "windows.h"
#include "avltree.h"

////////////////////////////////////////////////////////////////////////////
// TO DO - enhance this so that multiple read or access functions can occur
// as long as no write operations are waiting. As soon as a write operation
// is queued, then everything becomes blocked until the write operation
// completes. After the write completes everything can proceed again. Note
// some type of scheduling management is required to handle the situation 
// of multiple reads and writes. As long as there are writes it's first 
// come first served for everybody. But if there are only reads then 
// no blocking takes place on the reads, only on the writes.
////////////////////////////////////////////////////////////////////////////


// Multi threaded AVL Tree
template <class T>  class CMTAVLTree : public CAVLTree<T> {
    LPCRITICAL_SECTION pcs ; // pointer to the Critical Section ot be used
    // for controlling access in this tree

public:

    CMTAVLTree(LPCRITICAL_SECTION pcritsect) 
    {   // Save pointer to the critical section that will be used to
        // control access to this tree
        pcs = pcritsect; 
    } ;

    ~CMTAVLTree() 
    {   // Save pointer to the critical section that will be used to
        // control access to this tree
        EnterCriticalSection(pcs) ; 
        CAVLTree::~CAVLTree() ; 
        LeaveCriticalSection(pcs) ; 
    } ;


    // These are the functions which need to be overridden for safe
    // multithreaded access
    CAVLNode *FindNode(T &data) 
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::FindNode(data) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;

    CAVLNode *FindIndex(int index)  
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::FindIndex(index) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;

    CAVLNode *InsertNode(T &data) 
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::InsertNode(data) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;

    int DeleteNode(T &data)
    {
        int retval ; 
        EnterCriticalSection(pcs) ; 
        retval = CAVLTree::DeleteNode(data) ; 
        LeaveCriticalSection(pcs) ; 
        return retval ; 
    } ;

    CAVLNode* MaxNode()
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::MaxNode() ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;

    CAVLNode* MinNode()
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::MinNode() ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;
        
    CAVLNode* TreeMinimum(CAVLNode *pn)
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::TreeMinimum(pn) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;

    CAVLNode* TreeMaximum(CAVLNode *pn)
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::TreeMaximum(pn) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;
        
    CAVLNode *Successor(CAVLNode *pn) 
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::Successor(pn) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;
        
    CAVLNode *Predecessor(CAVLNode *pn) 
    {
        CAVLNode *pretnode ; 
        EnterCriticalSection(pcs) ; 
        pretnode = CAVLTree::Predecessor(pn) ; 
        LeaveCriticalSection(pcs) ; 
        return pretnode ; 
    } ;



} ;

#endif

