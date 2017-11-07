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

// forkmgr.h

#ifndef __FORKMGR_H__

#define __FORKMGR_H__

#pragma warning( disable : 4996 )

#include "stacks.h"

#define MTTHREADTYPE_READ       0
#define MTTHREADTYPE_WRITE      1

struct MTThreadInfo
{
    DWORD thrdID ; 
    int thrdType ; 
} ;

// Manages a specific resource among multiple threads
// Reads and Writes are handled separately so that multiple reads can 
// occur while only a single write can occur at any given time. 
// Since these functions will cause other threads to block, make sure
// that the amount of time spent inside Enter/Leave pairs is minimal. 
// Threads must have their

class MTGateKeeper
{
private:
    CRITICAL_SECTION m_critsect ; // OS dependent
    int m_nWritesPending ; // number of write threads waiting
    int m_nReadsPending ;  // number of read threads waiting
    int m_nReadsActive ;   // number of read threads running
    int m_nWritesActive ;  // number of write threads running (range [0,1])
    int m_nMaxThreads ; // maximum number of threads allowed
    FIFORing<MTThreadInfo> m_thrdIDqueue ; // note must initialize this ??

    void ReleaseQueue() ; // called from LeaveRead and LeaveWrite
    // as many threads as required. This cannot overflow or else everything
    // crashes

public:

    MTGateKeeper() ; 
    ~MTGateKeeper() ; 
    int Initialize(int maxthreads) ; // returns 0 if successful
    void EnterRead() ; // wait for allowed read operation
    void LeaveRead() ; // free read count that was used up
    void EnterWrite() ; // wait for exclusive write access
    void LeaveWrite() ; // free up write resource that was used
} ;

#endif
