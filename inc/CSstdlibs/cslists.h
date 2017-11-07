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

// ntoplist.h - maintains a list of the N top elements. To do this 
// the operators (T < T) and (T==T) must be defined for the member
// element. This function maintains a linked list of the elements so
// that insertion and updates are fast. Probably want to create a
// second type of list which is optimized with a tree instead of a 
// linked list for situations where that will work better.

#ifndef __NTOPTLIST_H__
#define __NTOPTLIST_H__

// The list node can be used for a standard linked list
struct CS_ListNode 
{
    void *pdata ;
    CS_ListNode *prev, *next ;
} ;


// The operator T==T must be defined for the class if the 
// Find() function is used
template <class T> class CS_List
{
public:
    CS_ListNode *pFirst, *pLast ; 
    int len ; // number of nodes in the list

    CS_List() 
    {
        len = 0 ;
        pFirst = pLast = 0 ; 
    } 


    ~CS_List()
    {
        while (pFirst)
        {   
            pLast = pFirst ; 
            pFirst = pFirst->next ; 
            delete ((T *)pLast->pdata) ;
            delete pLast ; 
        }
    } 

    // Add existing list to the end of current list and empty that list
    // in the process. Returns pointer to last node in the list
    CS_ListNode *Append(CS_List<T> &list) 
    {
        CS_ListNode *pn = list.pFirst ; 

        if (!pn)
            return pLast ; 

        CS_ListNode *pnxt ; 

        // Test for an empty list only once
        pnxt = pn ; // need this if we don't do the !pLast if()
        if (!pLast)
        {   // Save pointers
            pnxt = pn->next ;
            // Set up *this list
            len = 1 ;
            pFirst = pn ;
            pLast = pn ;
            pn->prev = 0 ;
            pn->next = 0 ;
        }

        pn = pnxt ;

        while (pn)
        {
            pnxt = pn->next ; 
            // Fix up *this values
            len += 1 ;
            pLast->next = pn ;
            pn->prev = pLast ;
            pn->next = 0 ;
            pLast = pn ;

            pn = pnxt ; 
        }

        // Delete contents of list passed in 
        list.pFirst = 0 ; 
        list.pLast = 0 ; 
        list.len = 0 ; 

        return pLast ; 
    }

    CS_ListNode *Append(T &nodedata)
    {
        CS_ListNode *pn = new CS_ListNode ; 
        T *pnewdata = new T ; 
        *pnewdata = nodedata ; 
        len += 1 ; 
        if (pLast)
        {
            pLast->next = pn ; 
            pn->prev = pLast ; 
            pn->next = 0 ; 
            pLast = pn ; 
            pn->pdata = pnewdata ; 
        }
        else
        {   // This is the first node in the list
            pFirst = pn ; 
            pLast = pn ; 
            pn->prev = 0 ; 
            pn->next = 0 ; 
            pn->pdata = pnewdata ; 
        }

        return pn ; 
    } 

    CS_ListNode *Append(T *pnewdata)
    {
        CS_ListNode *pn = new CS_ListNode ; 
        len += 1 ; 
        if (pLast)
        {
            pLast->next = pn ; 
            pn->prev = pLast ; 
            pn->next = 0 ; 
            pLast = pn ; 
            pn->pdata = pnewdata ; 
        }
        else
        {   // This is the first node in the list
            pFirst = pn ; 
            pLast = pn ; 
            pn->prev = 0 ; 
            pn->next = 0 ; 
            pn->pdata = pnewdata ; 
        }

        return pn ; 
    } 

    CS_ListNode *First() { return pFirst ;} 
    CS_ListNode *Last() { return pLast ;} 

    CS_ListNode *Insert(CS_ListNode *pinsert, T &nodedata)
    {
        // Insert the node before the node pointed to by pinsert
        T *pnewdata = new T ; 
        *pnewdata = nodedata ; 
        return Insert(pinsert, pnewdata) ; 
    } 

    CS_ListNode *Insert(CS_ListNode *pinsert, T *pnewdata)
    {
        // Insert the node before the node pointed to by pinsert
        CS_ListNode *pn = new CS_ListNode ; 
        len += 1 ; 
        pn->pdata = pnewdata ; 

        if (pinsert)
        {   // Then the list is not empty
            if (pinsert->prev)
            {   // insert in the middle of the list somewhere
                pinsert->prev->next = pn ; 
                pn->prev = pinsert->prev ; 
                pn->next = pinsert ; 
                pinsert->prev = pn ; 
            }
            else
            {   // We're inserting at the front of the list
                pinsert->prev = pn ; 
                pn->prev = 0 ; 
                pn->next = pinsert ;
                pFirst = pn ; 
            }
        }
        else
        {  
            if (pFirst)
            {   // Then insert at the front of the list
                pFirst->prev = pn ;
                pn->next = pFirst ; 
                pn->prev = 0 ; 
                pFirst = pn ; 
            }
            else
            {   // We are inserting into an empty list
                pFirst = pn ; 
                pLast = pn ; 
                pn->prev = 0 ; 
                pn->next = 0 ; 
            }
        }
        return pn ; 
    } 


    CS_ListNode *InsertSorted(T *pnodedata)
    {
        CS_ListNode *pln = pFirst ; 
        while (pln)
        {
            if (!(*GetData(pln) < *pnodedata))
                break ; 
            pln = pln->next ; 
        }

        if (pln)
        {   // Found the node to insert in front of
            return Insert(pln, pnodedata) ; 
        }
        else
        {   // Append to the end of the list since greater than
            // all entries currently in the list,.
            return Append(pnodedata) ; 
        }
        return 0 ; 
    }

    CS_ListNode *InsertSorted(T &nodedata)
    {
        T *pT = new T ; 
        *pT = nodedata ; 
        return InsertSorted(pT) ; 
    }


    // Could override the [] operator for this function
    T *GetData(CS_ListNode *pn)
    {
        return (T *)(pn->pdata) ; 
    } 
    
    T *operator[](CS_ListNode *pn)
    {
        return (T *)(pn->pdata) ; 
    }

    T *operator[](int n)
    {
        CS_ListNode *pn = pFirst ; 
        for (int i=0; pn && i < len && i < n ; i++)
            pn = pn->next ; 
        if (pn)
            return (T *)(pn->pdata) ; 
        return 0 ; 
    }


    // Delete this node from the list. The list cannot be empty when 
    // this is called. Ptr to next node after the one deleted is returned
    CS_ListNode *Delete(CS_ListNode *pdelnode)
    {
        // First take care of situations where the start or the end
        // of the list is the element deleted (can be both also)
        CS_ListNode *pretnode ;
        if (pdelnode->next)
            pretnode = pdelnode->next ; 
        else
            pretnode = pdelnode->prev ; 

        if (pdelnode == pFirst) 
            pFirst = pFirst->next ; 
        if (pdelnode == pLast)
            pLast = pLast->prev ; 

        len -= 1 ; 
        // fix up adjacent node pointerss to previous and next
        if (pdelnode->prev)
            pdelnode->prev->next = pdelnode->next ;
        
        if (pdelnode->next)
            pdelnode->next->prev = pdelnode->prev ; 

        delete (T *)(pdelnode->pdata) ; 
        delete pdelnode ; 

        return pretnode ; 
    } 

    // Delete the entire list
    void Clear() 
    {
        while (pFirst)
        {
            pLast = pFirst ; 
            pFirst = pFirst->next ; 
            delete (T *)(pLast->pdata) ; 
            delete pLast ; 
        }
        pFirst = 0 ; 
        pLast = 0 ; 
        len = 0 ; 
    } 

    CS_ListNode *Find(T &nodedata)
    {
        CS_ListNode *pn = pFirst ; 
        while (pn)
        {
            if (*(GetData(pn)) == nodedata)
                return pn ; 
            pn = pn->next ; 
        }
        return 0 ; 
    } 

    int Length()
    {
        return len ; 
    } 


} ;


////////////////////////////////////////////////////////////////////
// The data is duplicated when stored in the list, So keep this in 
// mind when defining the T class. 
// The operators T==T and T<T must be defined since we must be 
// able to Find() duplicate nodes, and we have to be able to test
// where the node should sort in the list. Note the == and < 
// operators do not have to test the same data, how they are 
// defined depends on the application. The == could test a string
// while the < operator tests some numeric value. 
// TO DO - generated a lot of code handling each case separately.
// A bit of logic cleanup should reduce the amount of code required.
////////////////////////////////////////////////////////////////////

template<class T> class CS_NTopList
{
public:
    int nSize ; // actual max size for the list
    int nLen ; // number of elements in the list, also used as index
    // pointer to next available node data space
    T *pList ; // points to the start of the array

public:

    CS_NTopList() 
    {
        nSize = 0 ; 
        nLen = 0 ;
        pList = 0 ; 
    } 

    ~CS_NTopList()
    {
        if (pList)
            delete[] pList ; 
    } 

    void Init(int n) 
    {   // This allocates memory for all the nodes that are to defined
        // for this list.
        if (n < 1)
            return ; // nothing to do

        if (pList)
            delete[] pList ; 
        pList = 0 ; 
        nSize = 0 ; 
        nLen = 0 ; 

        pList = new T[n] ; 
        nSize = n ; 
        nLen = 0 ; 
    } 

    // Reset all values in the list to v
    void Reset(void *pdata)
    {
        for (int i=0; i < nLen; i++)
            pList[i].Reset(pdata) ; 

    }

    void Swap(int a, int b) 
    {
        T tmpdata ; 
        tmpdata = pList[a] ; 
        pList[a] = pList[b] ; 
        pList[b] = tmpdata ; 
    } 

    // idx must be >= 1 when this is called since it is impossible to 
    // due the shift otherwise
    void ShiftUp(int idx)
    {
        Swap(idx-1, idx) ; 
    } 

    // Nodes pn and pn->next must exist when called
    void ShiftDown(int idx)
    {
        Swap(idx, idx+1) ; 
    } 

    int BubbleUp(int i)
    {
        int modified = 0 ; 
        while (i > 0)
        {   // Then we can continue testing
            if (pList[i-1] < pList[i])
            {
                modified = 1 ; 
                ShiftUp(i) ;
            }
            else
                break ; // we're sorted OK so exit
            i -= 1 ; 
        }
        return modified ; 
    } 

    int SinkDown(int i)
    {
        int modified = 0 ; 
        while (i < (nLen - 1))
        {   // Then we can continue testing
            if (pList[i] < pList[i+1])
            {
                modified = 1 ; 
                ShiftDown(i) ;
            }
            else
                break ; // we're sorted OK so exit
            i += 1 ; 
        }
        return modified ; 
    } 


    /////////////////////////////////////////////////////////////////////
    // This is the main logic section which maintains a sorted list
    // See Misc-01RR Notes Pg 49 for details.
    //
    // Returns 1 if the list was re-organized
    // Returns 2 if a the list stayed the same but a value changed
    // otherwise it returns false (or zero)
    int Update(T &testdata)
    {
        // See if the node is in the list
        int i, res ; 
        for (i=0; i < nLen; i++)
        {
            if (pList[i] == testdata)
                break ; 
        }

        if (i < nLen)
        {   // Then we found the testdata node record in the list
            // Now we have to check to see if the node is still 
            // sorted in the list based on its new value
            pList[i] = testdata ; // save the current result

            // See if we should shift the node up
            res = BubbleUp(i) ; 
            if (res)
                return 1 ; // Yes the data was shifted up so were done

            // Else see if we should shift the node down
            res = SinkDown(i) ; 
            if (res)
                return 1 ; // yes it was shifted down

            // didn't have to move anything in the list, only update
            // the value so return 2
            return 2 ; 
        }

        // Else the testdata node is not currently in the list

        // Else the list is not empty
        if (nLen < nSize)
        {   // Then the list is not full so we simply have to work out
            // where in the list this node is going to be inserted
            // First append the new node onto the end 
            if (nLen == 0)
            {   // Then the list is empty
                // Set the first and last pointers to the first node area
                nLen = 1 ; 
                pList[0] = testdata ; 
                return 1 ; 
            }

            pList[nLen] = testdata ; 
            nLen++ ; 

            // And then see if we have to shift it up the list
            BubbleUp(nLen-1) ; 

            // Done 
            return 1 ; // return true since the list was modified
        }

        // Else the list is currently full so see if we have to shift
        // it up into the current list
        if (testdata < pList[nLen-1])
            return 0 ; // nothing to do

        // Else substitute the last node and then shift it up as far as
        // possible
        pList[nLen - 1] = testdata ; 
        BubbleUp(nLen-1) ;
        return 1 ; 
    } 

} ;


#endif


