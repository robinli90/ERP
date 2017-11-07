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

// CAVLTree class definitions

#ifndef __AVLTREE_H__
#define __AVLTREE_H__   1

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif

// AVL Balanced binary trees

class CAVLNode {
public:
    CAVLNode *pnParent ;
    CAVLNode *pnLeft ;
    CAVLNode *pnRight ;
    char balance ; // -1,0,1

    void *m_pdata ;  // pointer to symbol data

    CAVLNode() ;
    ~CAVLNode() ;
} ;



////////////////////////////////////////////////////////////////////
// Note: operator overloads must exist to return valid results for 
//     comparison functions (T == T) and (T < T) since these are 
//     used in the tree.
////////////////////////////////////////////////////////////////////

template <class T> class CAVLTree {
  public:
    CAVLNode*  m_pnRoot ;
    int m_nTreeSize ;
    

    // Must define pointers to comparison functions in constructor
    CAVLTree() ;
    virtual ~CAVLTree() ;

    CAVLNode *FindNode(T &data) ;
    CAVLNode *FindNode(T *pdata) ;
    CAVLNode *FindGEQ(T &data) ;
    CAVLNode *FindIndex(int index) ; 
    CAVLNode *InsertNode(T &data) ;  // returns pointer to newly node created
    CAVLNode *InsertNode(T *pdata) ; // returns pointer to newly node created
    int       DeleteNode(T &data) ;
    void      DeleteTree(void); // reset entire tree and release all memory

    CAVLNode *MaxNode() ;
    CAVLNode *MinNode() ;
    CAVLNode *TreeMinimum(CAVLNode *x) ;
    CAVLNode *TreeMaximum(CAVLNode *x) ;
    CAVLNode *Successor(CAVLNode *pn) ;
    CAVLNode *Predecessor(CAVLNode *pn) ;

    // Recursively traverse the tree in sorted order calling the 
    // function pfunc at each node in the tree. Note: the function
    // pointer is duplicated on the stack for the entire recursive
    // call, thus it is safe for two tree traverses to be going 
    // on at the same time. It is however NOT safe to modify the 
    // tree structure while doing the traversal
    void TraverseTree(int (*pfunc)(T *pdata)) ; 

    // Cast the node data to the class template type
    T *GetData(CAVLNode *pnode) { return (T *)(pnode->m_pdata) ; } ; 

  private:
    // Private member functions

    // recrusive sub to TraverseTree()
    void ProcessNode(CAVLNode *pn, int (*pfunc)(T *pdata)) ;

    void FreeTree(CAVLNode* pn);
    int delnode(CAVLNode **pnp, T &data,
                int *pi_balance, int *pi_uar_called) ;
    void replaceRightMost(CAVLNode **pnr, int *pi_balance, 
                          CAVLNode **pnq, int* pi_uar_called) ;
    void balanceL(CAVLNode **pnp, int *pi_balance) ;
    void balanceR(CAVLNode **pnp, int *pi_balance) ;
    CAVLNode* RightRotate(CAVLNode* x) ;
    CAVLNode* LeftRotate(CAVLNode* x) ;

    // Returns true if node added, 0 if node replaced
    int AddNode(CAVLNode **pn, CAVLNode *pnew, int *pi_balance) ;
} ;


// CAVLTree class routines

/////////////////////////////////////////////////////////////////////
// AVL Balanced binary tree implementation
///////////////////////////////////////////////////////////////////// 


// Now the actual binary tree manipulation routines
template <class T> CAVLTree<T>::CAVLTree() 
{
    m_pnRoot = 0 ;
    m_nTreeSize = 0 ;
}


template <class T> CAVLTree<T>::~CAVLTree()
{
    if (m_pnRoot != 0)
        FreeTree(m_pnRoot) ;
} 

template <class T> void CAVLTree<T>::DeleteTree(void)
{
    if (m_pnRoot != 0)
        FreeTree(m_pnRoot) ;
    
    m_nTreeSize = 0 ;		
    m_pnRoot = 0 ;
}

template <class T> void CAVLTree<T>::FreeTree(CAVLNode* pn) 
{
    if (pn->pnLeft != 0)
        FreeTree(pn->pnLeft) ;
    if (pn->pnRight != 0)
        FreeTree(pn->pnRight) ;
    if (pn->m_pdata != 0)
    {
        delete GetData(pn) ;
        pn->m_pdata = 0 ;
    }
    delete pn ;
    m_nTreeSize-- ; // decrement the node count
}


// This is how data is added to the tree
// The external interface uses calls to InsertNode from here
template <class T> CAVLNode* CAVLTree<T>::InsertNode(T &data)
{
    CAVLNode* pnew = new CAVLNode ;
    
    // return 0 if insufficient memory to add node
    if (pnew == 0)
        return 0 ;
    
    // Now allocate memory for the new data node
    T *pnodedata = new T ; 

    if (!pnodedata)
    {   // Then an error occured allocating memory for the node
        // data. Clean up and return error
        delete pnew ; 
        return 0 ; 
    }

    *pnodedata = data ; 
    pnew->m_pdata = pnodedata ; // set the pointer

    
    if (m_pnRoot == 0)
    {
        // Node will be added so increment count 
        m_nTreeSize = 1 ; // first node in the tree
        m_pnRoot = pnew ;
        return m_pnRoot ; // done
    }
    
    int	i_balance = 0 ;
    
    // AddNode returns 0 if an existing node is replaced
    if (AddNode(&m_pnRoot, pnew, &i_balance))
        m_nTreeSize++ ;
    
    return pnew ;
}

// This is how data is added to the tree
// The external interface uses calls to InsertNode from here
// This version differs from the one above in that no memory
// allocation is done for the variable. The pointer passed is
// simply copied into the node. Thus the calling routine must
// have created the object using 'pdata = new T'. This 
// eliminates having to create a proper copy constructor for
// objects which allocate memory internally.
template <class T> CAVLNode* CAVLTree<T>::InsertNode(T *pdata)
{
    CAVLNode* pnew = new CAVLNode ;
    
    // return 0 if insufficient memory to add node
    if (pnew == 0)
        return 0 ;
    
    // Now allocate memory for the new data node
    pnew->m_pdata = pdata ; // set the pointer
    
    if (m_pnRoot == 0)
    {
        // Node will be added so increment count 
        m_nTreeSize = 1 ; // first node in the tree
        m_pnRoot = pnew ;
        return m_pnRoot ; // done
    }
    
    int	i_balance = 0 ;
    
    // AddNode returns 0 if an existing node is replaced
    if (AddNode(&m_pnRoot, pnew, &i_balance))
        m_nTreeSize++ ;
    
    return pnew ;
}



// See Notes in MISC Notes Pgs 18-19 for rotation diagrams
// Used internally to add nodes into the tree
template <class T> int CAVLTree<T>::AddNode(CAVLNode **pn, CAVLNode *pnew, int *pi_balance)
{
    CAVLNode *p1, *p2, *pT, *pa, *pb ; 
    
    // are we grounded?  if so, add the node "here" and set the rebalance
    // flag, then exit.

    if (*pn == 0) 
    {
        *pn = pnew ;
        *pi_balance = 1;
        return 1 ;
    }
    

    pnew->pnParent = *pn ; // default value
    // compare the data using routine passed by caller.
    
    // if LESS, prepare to move to the left.
    // if (compfuncLT(pnew->m_pdata, (*pn)->m_pdata)) 
    if (*GetData(pnew) < *GetData(*pn))
    {
        AddNode(&(*pn)->pnLeft, pnew, pi_balance) ;
        if (*pi_balance)
        {   // left branch has grown longer 
            switch ((*pn)->balance)
            {
            case 1 :	
                // right branch WAS longer; balance is ok now 
                (*pn)->balance = 0;
                *pi_balance = 0;
                break;
            case 0 :	
                // balance WAS okay; now left branch longer 
                (*pn)->balance = -1;
                break;
            case -1 :
                // left branch was already too long. rebalnce 
                p1 = (*pn)->pnLeft ;
                if (p1->balance == -1)
                {   // Right Rotation (MISC NOTES Pg 18, Sept20, 1999)
                    pT = *pn ; // save this for later

                    pT->pnLeft = p1->pnRight ;
                    p1->pnRight = pT ;
                    pT->balance = 0 ; 
                    *pn = p1 ; // overwrite to set the new top node
                    
                    // p1 is now the top node here
                    // Now adjust the parent pointers
                    p1->pnParent = pT->pnParent ; 
                    pT->pnParent = p1 ;
                    if (pT->pnLeft) 
                        pT->pnLeft->pnParent = pT ; 
                }
                else
                {   // Left-Right Rotation (MISC NOTES Pg 18, Sept20, 1999)
                    pT = *pn ; // save pn value

                    pb = p1->pnRight ;
                    p1->pnRight = pb->pnLeft ;
                    pb->pnLeft = p1;
                    
                    pT->pnLeft = pb->pnRight ;
                    pb->pnRight = pT ;
                    
                    if (pb->balance == -1)
                        pT->balance = 1 ;
                    else
                        pT->balance = 0 ;
                    
                    if (pb->balance == 1)
                        p1->balance = -1 ;
                    else
                        p1->balance = 0 ;
                    *pn = pb ;

                    // Now fix up the parent pointers
                    pb->pnParent = pT->pnParent ; 
                    p1->pnParent = pb ; 
                    if (p1->pnRight)
                        p1->pnRight->pnParent = p1 ; 
                    pT->pnParent = pb ; 
                    if (pT->pnLeft)
                        pT->pnLeft->pnParent = pT ; 

                } /*else*/
                (*pn)->balance = 0 ;
                *pi_balance = 0 ; 
                break ;
            } /*switch*/
        } /*if*/
        return 1 ;
    } /*if*/
    
    // if MORE, prepare to move to the right. 
    // if (!compfuncEQ(pnew->m_pdata, (*pn)->m_pdata))
    if (!(*GetData(pnew) == *GetData(*pn)))
    {   // Then new node is > than current node
        AddNode(&(*pn)->pnRight, pnew, pi_balance) ;
        if (*pi_balance) 
        {   // right branch has grown longer 
            
            switch ((*pn)->balance)
            {
            case -1 : // balance was off, fixed implicitly
                (*pn)->balance = 0 ;
                *pi_balance = 0 ;
                break ;
            case 0 :  // balance was okay, now off but ok 
                (*pn)->balance = 1;
                break;
            case 1 :  // balance was off, need to rebalance
                p2 = (*pn)->pnRight ;
                if (p2->balance == 1) 
                {   // Left Rotation (MISC NOTES Pg 19, Sep 20, 1999)
                    pT = *pn ; // save for later
                    (*pn)->pnRight = p2->pnLeft ;
                    p2->pnLeft = pT ;
                    pT->balance = 0 ;
                    *pn = p2 ;

                    // Fix parent nodes now
                    p2->pnParent = pT->pnParent ;
                    pT->pnParent = p2 ; 
                    if (pT->pnRight)
                        pT->pnRight->pnParent = pT ; 
                }
                else
                {   /* double rotate right then left */
                    pT = *pn ; // save for later

                    pa = p2->pnLeft ;
                    p2->pnLeft = pa->pnRight ;
                    pa->pnRight = p2;
                    
                    pT->pnRight = pa->pnLeft ;
                    pa->pnLeft = pT ;
                    
                    if (pa->balance == 1)
                        pT->balance = -1 ;
                    else
                        pT->balance = 0 ;
                    
                    if (pa->balance == -1)
                        p2->balance = 1 ;
                    else
                        p2->balance = 0 ;
                    
                    *pn = pa ;

                    // Now fix up the parent pointers
                    pa->pnParent = pT->pnParent ; 
                    p2->pnParent = pa ; 
                    if (p2->pnLeft) 
                        p2->pnLeft->pnParent = p2 ; 
                    pT->pnParent = pa ; 
                    if (pT->pnRight)
                        pT->pnRight->pnParent = pT ; 
                } /*else*/
                (*pn)->balance = 0;
                *pi_balance = 0;
                break ;
            } /*switch*/
        } /*if*/
        return 1 ;
    } /*if*/
    
    // not less, not more: this is the same key!  replace...
    // so we replace this entry with the new one
    *pi_balance = 0;
    if ((*pn)->m_pdata)
        delete GetData(*pn) ; 
    
    (*pn)->m_pdata = pnew->m_pdata ;
    delete pnew ;
    
    return 0 ; // node replaced
}	

template <class T> int CAVLTree<T>::DeleteNode(T &data)
{
    int	i_balance = 0 ; 
    int i_uar_called = 0 ;
    
    return delnode(&m_pnRoot, data, &i_balance, &i_uar_called) ;
}



template <class T> int 
    CAVLTree<T>::delnode(CAVLNode **pnp, T &data,
                         int *pi_balance, int *pi_uar_called)
{
    CAVLNode *pr_q ;
    int	i_ret ;
    
    if (*pnp == 0)
    {
        return 0 ;
    }
    
    // if (compfuncLT(pdata, (*pnp)->m_pdata))
    if (data < *GetData(*pnp))
    {   // data < currentnode, move down left branch
        i_ret = delnode(&(*pnp)->pnLeft, data, pi_balance, pi_uar_called) ;
        if (*pi_balance)
            balanceL(pnp, pi_balance) ;
    }
    // else if (!compfuncEQ(pdata, (*pnp)->m_pdata))
    else if (!(data == *GetData(*pnp)))
    {	// data > currentnode, move down right branch
        i_ret = delnode(&(*pnp)->pnRight, data, pi_balance, pi_uar_called) ;
        if (*pi_balance)
            balanceR(pnp, pi_balance);
    }
    else
    {   // found the node to delete
        pr_q = *pnp ;
        if (pr_q->pnRight == 0)
        {	// then the right subtree is 0
            *pnp = pr_q->pnLeft ;
            *pi_balance = 1 ;
            // Fix up parent pointer
            if (*pnp)
                (*pnp)->pnParent = pr_q->pnParent ; 
        }
        else if (pr_q->pnLeft == 0)
        {   // right subtree non-0, left subtree 0
            *pnp = pr_q->pnRight ;
            *pi_balance = 1 ;
            // Fix up parent pointer
            if (*pnp)
                (*pnp)->pnParent = pr_q->pnParent ; 
        }
        else
        {   // neither subtree 0
            replaceRightMost(&pr_q->pnLeft, pi_balance, &pr_q, pi_uar_called);
            if (*pi_balance)
                balanceL(pnp, pi_balance);
        }
        
        // Now delete the data
        if (!(*pi_uar_called))
        {
            delete GetData(pr_q) ; 
        }
        
        delete pr_q ;
        
        m_nTreeSize -= 1 ; // decrement tree size count
        i_ret = 1;
    }
    return i_ret ;
}


template <class T> 
    void CAVLTree<T>::replaceRightMost(CAVLNode **pnr, int *pi_balance, 
                                       CAVLNode **pnq, int *pi_uar_called)
{
    // pnr will not be Null on entry
    if ((*pnr)->pnRight != 0)
    {
        replaceRightMost(&(*pnr)->pnRight, pi_balance, pnq, pi_uar_called) ;
        if (*pi_balance)
            balanceR(pnr, pi_balance) ;
    }
    else 
    {	// substitute r into q
        // At this point because the tree is balanced we will have 
        // at most a single left node hanging off this node (pnr)
        
        delete GetData(*pnq) ; 
        *pi_uar_called = 1;
        (*pnq)->m_pdata = (*pnr)->m_pdata ;
        *pnq = *pnr ;  // set q to the swapped out node
        
        CAVLNode *rparent = (*pnr)->pnParent ; // added for parent wrkings

        *pnr = (*pnr)->pnLeft ; // pnLeft is a terminal node if it exists

        // two lines added for parent wrkings
        if (*pnr)
            (*pnr)->pnParent = rparent ; 
           
        *pi_balance = 1;
    }
    return ;
}


template <class T> 
    void CAVLTree<T>::balanceL(CAVLNode **pnp, int *pi_balance)
{
    CAVLNode *pTop ; 
    CAVLNode *p1, *p2;
    int	b1, b2 ;
    
    // left branch has shrunk

    // See MISC NOTES Pg 21, Sep 20, 1999 for diagrams of balanceL
    
    switch ((*pnp)->balance)
    {
    case -1 : // was imbalanced, fixed implicitly
        (*pnp)->balance = 0 ;
        break ;
    case 0 :  // was okay, is now one off
        (*pnp)->balance = 1 ;
        *pi_balance = 0 ;
        break ;
    case 1 :  // was already off, this is too much
        p1 = (*pnp)->pnRight ;
        b1 = p1->balance ;
        if (b1 >= 0) 
        {   // single rotate left
            pTop = *pnp ; // save for parent correction later

            pTop->pnRight = p1->pnLeft ;
            p1->pnLeft = pTop ;

            if (b1 == 0)
            {   // b1 == 0
                pTop->balance = 1 ;
                p1->balance = -1 ;
                *pi_balance = 0 ; 
            }
            else
            {	// b1 != 0
                pTop->balance = 0 ;
                p1->balance = 0;
            }
            *pnp = p1;

            // Fix up parent pointers
            p1->pnParent = pTop->pnParent ; 
            pTop->pnParent = p1 ; // save top parent pointer
            if (pTop->pnRight)
                pTop->pnRight->pnParent = pTop ; 
        }
        else
        {   // double rotate right then left
            pTop = *pnp ; // save for parent correction

            p2 = p1->pnLeft ;
            b2 = p2->balance ;
            p1->pnLeft = p2->pnRight ;
            p2->pnRight = p1 ;
            pTop->pnRight = p2->pnLeft ;
            p2->pnLeft = pTop ;
            if (b2 == 1)
                pTop->balance = -1 ;
            else
                pTop->balance = 0 ;
            if (b2 == -1)
                p1->balance = 1 ;
            else
                p1->balance = 0 ;
            *pnp = p2 ;
            p2->balance = 0 ;

            // Fix parent pointers
            p2->pnParent = pTop->pnParent ; 
            pTop->pnParent = p2 ; 
            p1->pnParent = p2 ; 
            if (pTop->pnRight)
                pTop->pnRight->pnParent = pTop ; 
            if (p1->pnLeft)
                p1->pnLeft->pnParent = p1 ; 
        }
    }
    return ;
}


template <class T> 
    void CAVLTree<T>::balanceR(CAVLNode **pnp, int *pi_balance)
{
    CAVLNode *pTop ; 
    CAVLNode *p1, *p2 ;
    int	b1, b2 ;
    
    // right branch has shrunk
    switch ((*pnp)->balance)
    {
    case 1 :  // was imbalanced, fixed implicitly
        (*pnp)->balance = 0 ;
        break ;
    case 0 :  // was okay, is now one off
        (*pnp)->balance = -1 ;
        *pi_balance = 0 ;
        break ;
    case -1 : // was already off, this is too much
        p1 = (*pnp)->pnLeft ;
        b1 = p1->balance ;
        if (b1 <= 0) 
        {   // single rotate right
            pTop = *pnp ; 

            pTop->pnLeft = p1->pnRight ;
            p1->pnRight = pTop ;
            if (b1 == 0)
            {   // b1 == 0
                pTop->balance = -1 ;
                p1->balance = 1 ;
                *pi_balance = 0;
            }
            else
            {	// b1 != 0
                pTop->balance = 0 ;
                p1->balance = 0 ;
            }
            *pnp = p1 ;

            // Fix parent pointers
            p1->pnParent = pTop->pnParent ; 
            pTop->pnParent = p1 ; 
            if (pTop->pnLeft)
                pTop->pnLeft->pnParent = pTop ; 
        } 
        else
        {   // double rotate left then right
            pTop = *pnp ; 

            p2 = p1->pnRight ;
            b2 = p2->balance ;
            p1->pnRight = p2->pnLeft ;
            p2->pnLeft = p1 ;
            pTop->pnLeft = p2->pnRight ;
            p2->pnRight = pTop ;
            if (b2 == -1)
                pTop->balance = 1 ;
            else
                pTop->balance = 0 ;
            if (b2 == 1)
                p1->balance = -1 ;
            else
                p1->balance = 0 ;
            *pnp = p2 ;
            p2->balance = 0 ;
            
            // Fix Up parent pointers
            p2->pnParent = pTop->pnParent ;
            pTop->pnParent = p2 ; 
            p1->pnParent = p2 ; 
            if (p1->pnRight)
                p1->pnRight->pnParent = p1 ; 
            if (pTop->pnLeft)
                pTop->pnLeft->pnParent = pTop ; 
        }
    }
    return ;
}

// Find the entry with the same data pointed to by pData
template <class T> CAVLNode *CAVLTree<T>::FindNode(T &data)
{
    CAVLNode* pn = m_pnRoot ;
    while (pn != 0) 
    {
        if (data == *GetData(pn))
            return pn ;
        
        // test if (data < pn->data)
        if (data < *GetData(pn)) // if data is less than current node
            pn = pn->pnLeft ; // then go left
        else 
            pn = pn->pnRight ; // else go right
    }
    return 0 ; // couldn't find the data in the tree so return 0
}


template <class T> CAVLNode *CAVLTree<T>::FindNode(T *pdata)
{
    CAVLNode* pn = m_pnRoot ;
    while (pn != 0) 
    {
        if (*pdata == *GetData(pn))
            return pn ;
        
        // test if (data < pn->data)
        if (*pdata < *GetData(pn)) // if data is less than current node
            pn = pn->pnLeft ; // then go left
        else 
            pn = pn->pnRight ; // else go right
    }
    return 0 ; // couldn't find the data in the tree so return 0
}


// Find the entry with the same data pointed to by pData
template <class T> CAVLNode *CAVLTree<T>::FindGEQ(T &data)
{
    CAVLNode *pnLast ; 
    CAVLNode *pn = m_pnRoot ;
    pnLast = pn ; 
    while (pn != 0) 
    {
        if (data == *GetData(pn))
            return pn ;
        
        // test if (data < pn->data)
        pnLast = pn ; 
        if (data < *GetData(pn)) // if data is less than current node
            pn = pn->pnLeft ; // then go left
        else 
            pn = pn->pnRight ; // else go right
    }
    // Nothing is equal so see if we can return the next larger node
    // Note if pnLast == NULL then the tree is empty so return NULL
    if (pnLast)
    {
        if (data < *GetData(pnLast))
            return pnLast ; 
        return Successor(pnLast) ; 
    }

    return 0 ; // couldn't find the data in the tree so return 0
}


template <class T> CAVLNode* CAVLTree<T>::MaxNode() 
{
    CAVLNode *pn = m_pnRoot ;
    CAVLNode *pprev = pn ;
    while (pn)
    {
        pprev = pn ; 
        pn = pn->pnRight ; 
    } 
    return pprev ;
}

template <class T> CAVLNode* CAVLTree<T>::MinNode() 
{
    CAVLNode *pn = m_pnRoot ;
    CAVLNode *pprev = pn ;
    while (pn)
    {
        pprev = pn ; 
        pn = pn->pnLeft ; 
    } 
    return pprev ;
}


template <class T> CAVLNode* CAVLTree<T>::TreeMinimum(CAVLNode *x)
{
    if (x == 0)
        return 0 ; // error condition
    while (x->pnLeft != 0)
        x = x->pnLeft ;
    return x ;
}

template <class T> CAVLNode* CAVLTree<T>::TreeMaximum(CAVLNode *x)
{
    if (x == 0)
        return 0 ; // error condition
    while (x->pnRight != 0)
        x = x->pnRight ;
    return x ;
}

template <class T> void CAVLTree<T>::ProcessNode(CAVLNode *pn, int (*pfunc)(T *pdata)) 
{
    if (!pn)
        return ; // nothing to do

    if (pn->pnLeft)
        ProcessNode(pn->pnLeft, pfunc) ; 

    pfunc(GetData(pn)) ; // call the function on this node

    if (pn->pnRight)
        ProcessNode(pn->pnRight, pfunc) ; 
}

template <class T> void CAVLTree<T>::TraverseTree(int (*pfunc)(T *pdata))
{
    ProcessNode(m_pnRoot, pfunc) ; 
}


// Return the tree successor or the next node in a straight walk
// traversal of the tree (See MISC NOTES Pg 23, Sep 20, 1999)
template <class T> CAVLNode *CAVLTree<T>::Successor(CAVLNode *pn)
{
    if (pn->pnRight)
        return TreeMinimum(pn->pnRight) ; 
    // Else walk backwards to first parent node > current
    CAVLNode *pg ; 
    pg = pn->pnParent ; 
    while (pg)
    {
        if (*GetData(pg) < *GetData(pn))
            pg = pg->pnParent ; 
        else
            break ; // found node we want
    }
    return pg ; 
}

template <class T> CAVLNode *CAVLTree<T>::Predecessor(CAVLNode *pn)
{
    if (pn->pnLeft)
        return TreeMaximum(pn->pnLeft) ; 
    // Else walk backwards to first parent node < current
    CAVLNode *pg ; 
    pg = pn->pnParent ; 
    while (pg)
    {
        if (*GetData(pg) < *GetData(pn))
            break ; // found node we want
        else
            pg = pg->pnParent ; 
    }
    return pg ; 
}


// Return the node in the tree at the given index count based
// on stepping through the tree one by one from the MinNode()
// to the MaxNode with Successor() calls
template <class T> CAVLNode *CAVLTree<T>::FindIndex(int index)
{
    if (!m_nTreeSize)
        return 0 ; // nothing in tree

    if (index < 0 || index > m_nTreeSize)
        return 0 ; 

    CAVLNode *pn ; 

    pn = MinNode() ; 
    for (int i=0; pn && (i < index); i++)
        pn = Successor(pn) ; 

    return pn ; 
}


#endif   //  ifndef AVLTREE_H
