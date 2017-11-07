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

// stacks.cpp - used as FIFO rings or standard FILO stacks
// Note the FIFO ring setup is also used as a queue type entity 
// that is also thread safe.

#ifndef __STACKS_H__
#define __STACKS_H__

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif 



#include "wrkfuncs.h"

// allocate memory in blocks of STACKBLOCKSIZE
#define STACKBLOCKSIZE      10 

template<class T> class FIFOStack
{
private:
    int len  ; // current number of elements in the Ring
    int size ; // Total allocated memory space for the ring
    T  *pStack ; // pointer to memory allocated to store ring data
    int errorcode ; 
    

public:

    FIFOStack() 
    {
        pStack = 0 ; 
        size = 0 ; 
        len = 0 ; 
        errorcode = 0 ; 
    } ;

    ~FIFOStack() 
    {
        if (pStack)
            free(pStack) ; 
    } ;

    int Length() 
    { 
        return len ;
    } ; 

    
    void Reset()
    {
        if (pStack) 
            free(pStack) ; 
        len = 0 ; 
        size = 0 ; 
    } ;
    
    int Empty()
    {
        return ((len == 0) ? 1 : 0) ; 
    } ;

    // Push data onto the FIFO ring stack
    int Push(T &refdata)
    {
        // Copy the data into lastidx spot
        if (len >= size)
        {   // Then we have to allocate memory
            T *ptmp = (T *)realloc(pStack, sizeof(T) * (size + STACKBLOCKSIZE)) ; 
            if (!ptmp)
            {
                errorcode = 1 ; 
                return -1 ; // error allocating memory
            }
            pStack = ptmp ; 
        }

        pStack[len++] = refdata ; 

        return 0 ; // success
    } ;


    // Pop the oldest element from the FIFO stack 
    // True is returned if something is returned (there is data to pop)
    // Otherwise, if the buffer is empty, 0 or false is returned
    int Pop(T &datadest)
    {   
        if (len > 0)
        {
            datadest = pStack[(len--) - 1] ; 
            return 0 ; 
        }
        return -1 ; // stack empty
    } ;

    // Used if we want to check what the last thing in the stack without
    // removing it
    T *GetLast()
    {
        return &pStack[len - 1] ; 
    }

} ;


template<class T> class FIFORing 
{
public:
    int size ; // Total allocated memory space for the ring
    int len  ; // current number of elements in the Ring
    T *pRing ; // pointer to memory allocated to store ring data
    int errorcode ; 
    
    int firstidx, lastidx ; // current pointers to first and last elements
    // Once the ring is full lastidx will always be right behind firstidx
    // (using modulo size counting of course)
    // firstidx is in effect the oldest element in the FIFO ring. lastidx
    // points to the last entry added to the ring. If the FIFO fills up then
    // when an attempt is made to push the next data block the newest element
    // just added is overwritten. This sets an internal error condition
    // indicating that a buffer overflow condition has occured. A BufferFull()
    // test can be performed to make sure this won't happen on a call to 
    // Push().

    // This FIFO is thread safe if used by two threads at the same time
    // where startidx is updated exclusively by one thread and lastidx 
    // controlled by a second. Thus we can use the ring as a queue to 
    // safely pass information between two threads. firstidx is updated
    // on Pop operations and lastidx is incremented on Push operations
    // This of course assumes that the memory for ints is read and written 
    // in complete blocks, and that it is not possible to update 1/2 an 
    // int and then get interrupted and update the other half. 

    // Error codes:
    //      -1  memory allocation error
    //       1  buffer overrun
    //
    // Note: This is only thread safe if one thread accesses the Push and 
    // another thread accesses the Pop. (A single thread could access 
    // both Push and Pop obviously if it is the only thread accessing
    // the ring)

public:

    FIFORing() 
    {
        errorcode = 0 ; 
        pRing = 0 ; 
        size = 0 ; 
        len = 0 ; 
        firstidx = 0 ; 
        lastidx = 0 ; 
    } ;

    ~FIFORing() 
    {
        if (pRing)
            delete[] pRing ; 
    } ;

    int Initialize(int ringsize) 
    {
        if (ringsize == 0)
            return -2 ; // nothing to do 

        if (pRing)
        {   // Then we are re-initializing things
            if (ringsize != size)
            {   // Then our existing pointer is OK
                delete[] pRing ;
                pRing = new T[ringsize] ;
            }
        }
        else
        {   // pRing is NULL
            pRing = new T[ringsize] ;
        }

        len = 0 ; 
        firstidx = 0 ; 
        lastidx = 0 ; 
        if (pRing)
        {
            size = ringsize ; 
        }
        else
        {   // Memory allocation error
            errorcode = -1 ; 
            size = 0 ; 
            return -1 ; 
        }
        return 0 ; // everything went OK
    } ;

    int Length() 
    { 
        return len ;
    } ; 

    int BufferFull()
    {
        if (ModuloInc(lastidx, size) == firstidx)
            return 1 ; 
        return 0 ; 
    } ;

    int BufferEmpty()
    {
        if (firstidx == lastidx)
            return 1 ; 
        return 0 ; 
    } ;

    // Push data onto the FIFO ring stack
    int Push(T &refdata)
    {
        // Copy the data into lastidx spot
        errorcode = 0 ; 
        pRing[lastidx] = refdata ; 

        int nextidx = ModuloInc(lastidx, size) ; 
        if (nextidx == firstidx)
        {   // Then the buffer is full
            errorcode = 1 ; // buffer overrun
        }
        else
        {   // Buffer is not full, thus OK to increment counter
            lastidx = nextidx ; 
            len += 1 ; 
        }

        return errorcode ; 
    } ;


    /////////////////////////////////////////////////////////
    // Use the following 2 functions to copy data directly 
    // to the ring buffer area and then update the counters
    // after the data has been completely transferred. This
    // can eliminate an additional copy function to reduce
    // overhead.
    /////////////////////////////////////////////////////////
    // Use this function to get the pointer to the next empty
    // buffer storage area. If the ring is full, then returns
    // NULL. 

    //! Get the next empty location at the end of the ring
    /*!
        Returns null if the buffer is currently full
     */
    T *GetNext()
    {
        int nextidx = ModuloInc(lastidx, size) ; 
        if (nextidx == firstidx)
            return 0 ; // buffer is full
        return &pRing[lastidx] ; 
    }

    //! Call this after a GetNext to move the end pointer ahead one
    int PushNext()
    {
        errorcode = 0 ; 
        int nextidx = ModuloInc(lastidx, size) ; 
        if (nextidx == firstidx)
        {   // Then the buffer is full
            errorcode = 1 ; // buffer overrun
        }
        else
        {   // Buffer is not full, thus OK to increment counter
            lastidx = nextidx ; 
            len += 1 ; 
        }

        return errorcode ; 
    }

    // Pop the oldest element from the FIFO ring stack 
    // True is returned if something is returned (there is data to pop)
    // Otherwise, if the buffer is empty, 0 or false is returned
    int Pop(T &datadest)
    {   
        if (firstidx == lastidx)
            return 0 ; 
        
        datadest = pRing[firstidx] ; 
        firstidx = ModuloInc(firstidx, size) ; 
        len -= 1 ; 
        return 1 ; 
    } ;

    // Used if we want to check what the next thing in the queue is without
    // removing it from the queue, if the ring (queue) is empty then return 
    // NULL
    T *GetFirst()
    {
        if (BufferEmpty())
            return 0 ; 
        return &pRing[firstidx] ; 
    }

    // Increments counters so next data entry becomes available
    int MoveNext()
    {
        if (firstidx == lastidx)
            return 1 ; // buffer already empty so nothing to do
        firstidx = ModuloInc(firstidx, size) ; // else move ahead
        len -=1 ; 
        return 0 ; 
    }
} ;



#endif
