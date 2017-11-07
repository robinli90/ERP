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

// forkmgr.cpp - multi threaded process manager


#include <windows.h>
#include <winbase.h>


#include "forkmgr.h"
#include "stdlib.h"

MTGateKeeper::MTGateKeeper()
{
    memset(&m_critsect, 0, sizeof(CRITICAL_SECTION)) ; 
    m_nWritesPending = 0 ; // number of write threads waiting
    m_nReadsPending = 0 ;  // number of read threads waiting
    m_nReadsActive = 0 ;   // number of read threads running
    m_nWritesActive = 0 ;  // number of write threads running (range [0,1])
    m_nMaxThreads = 0 ;    // maximum number of threads allowed

    InitializeCriticalSection(&m_critsect) ; // used for sequence control
}

MTGateKeeper::~MTGateKeeper()
{
    while (m_thrdIDqueue.Length() > 0)
    {   // Signal all the waiting threads
        MTThreadInfo thrdInfo ;
        m_thrdIDqueue.Pop(thrdInfo) ; 
        ResumeThread(&thrdInfo.thrdID) ; 
    }
    
    DeleteCriticalSection(&m_critsect) ; 
} 


int MTGateKeeper::Initialize(int maxthreads)
{
    int retcode = m_thrdIDqueue.Initialize(maxthreads) ; 
    m_nMaxThreads = maxthreads ; 
    return retcode ; 
}


// wait for allowed read operation
void MTGateKeeper::EnterRead()
{
    EnterCriticalSection(&m_critsect) ; 
    if (m_nWritesPending || m_nWritesActive)
    {
        MTThreadInfo thrdInfo ;
        thrdInfo.thrdID = GetCurrentThreadId() ; 
        thrdInfo.thrdType = MTTHREADTYPE_READ ; 
        m_thrdIDqueue.Push(thrdInfo) ;
        m_nReadsPending++ ; 
        LeaveCriticalSection(&m_critsect) ; 

        ////////////////
        // pause here //
        ////////////////
        SuspendThread(&thrdInfo.thrdID) ; 
        // To avoid a race condition, the thread responsible for
        // releasing this thread, will also be responsible for 
        // incrementing the Active count for the thread. We have to 
        // do this because of following. This thread is resumed by 
        // another thread that finishes. Another thread that wants to 
        // do a write is just about to start up. Thus we would have to 
        // enter critical section again here and make sure that we got
        // the resource all over again. Since the other thread already
        // controls the critical section, might as well let it do 
        // the required control logic and thus save one more call to 
        // EnterCriticalSection()
        return ; // so simply return from here
    }

    // Else just keep right on going
    m_nReadsActive++ ;
    LeaveCriticalSection(&m_critsect) ;
}

// free read count that was used up, and release other threads if required
void MTGateKeeper::LeaveRead()
{
    EnterCriticalSection(&m_critsect) ; 
    // If a read is active a write cannot be active
    if (m_nReadsActive == 1)
    {   // Then this is the last thing consuming resource so see if
        // there is anything waiting in the queue, and if there is then
        // release some. The way this works is that we release all
        // sequential reads up to a write or end of queue, or we release
        // a single write. 
        // Thus we release multiple reads if we are able to do so.
        ReleaseQueue() ; 
    }
    m_nReadsActive-- ;
    LeaveCriticalSection(&m_critsect) ;
}

// wait for exclusive write access
void MTGateKeeper::EnterWrite()
{
    EnterCriticalSection(&m_critsect) ; 
    // For a write operation, if anything else is going on then we have to
    // wait, if a write or read is pending, then one or the other must also
    // be active, so we only have to test for the activity of either a read
    // or write to see if this thread should queue itself
    // Note the m_nReadsPending variable is not really used and could be 
    // removed although the extra overhead it incurs is minimal and may 
    // prove useful later on. 

    if (m_nReadsActive || m_nWritesActive)
    {
        MTThreadInfo thrdInfo ;
        thrdInfo.thrdID = GetCurrentThreadId() ; 
        thrdInfo.thrdType = MTTHREADTYPE_WRITE ; 
        m_thrdIDqueue.Push(thrdInfo) ;
        m_nWritesPending++ ; 
        LeaveCriticalSection(&m_critsect) ; 

        ////////////////
        // pause here //
        ////////////////
        SuspendThread(&thrdInfo.thrdID) ; 
        // To avoid a race condition, the thread responsible for
        // releasing this thread, will also be responsible for 
        // incrementing the Active count for the thread. We have to 
        // do this because of following. This thread is resumed by 
        // another thread that finishes. Another thread that wants to 
        // do a write is just about to start up. Thus we would have to 
        // enter critical section again here and make sure that we got
        // the resource all over again. Since the other thread already
        // controls the critical section, might as well let it do 
        // the required control logic and thus save one more call to 
        // EnterCriticalSection()
        return ; // so simply return from here
    }

    // Else just keep right on going
    m_nWritesActive++ ;
    LeaveCriticalSection(&m_critsect) ;
}

// free up write resource that was used
void MTGateKeeper::LeaveWrite()
{
    EnterCriticalSection(&m_critsect) ; 
    // If a read is active a write cannot be active
    if (m_nWritesActive == 1)
    {   // Then this is the last thing consuming resource so see if
        // there is anything waiting in the queue, and if there is then
        // release some. The way this works is that we release all
        // sequential reads up to a write or end of queue, or we release
        // a single write. 
        // Thus we release multiple reads if we are able to do so.
        ReleaseQueue() ; 
    }
    m_nWritesActive-- ;
    LeaveCriticalSection(&m_critsect) ;
}

void MTGateKeeper::ReleaseQueue()
{
    MTThreadInfo *pInfo ; 
    while ((pInfo = m_thrdIDqueue.GetFirst()) != 0)
    {
        if (pInfo->thrdType == MTTHREADTYPE_WRITE)
        {   // Then based on what has happened we do one of two things
            // exit immediately if we have already released a Read thread
            // or release this write thread and exit
            if (m_nReadsActive)
                break ; // we've already released a read thread

            MTThreadInfo thrdInfo ; 
            m_thrdIDqueue.Pop(thrdInfo) ; 
            ResumeThread(&thrdInfo.thrdID) ; 
            m_nWritesPending-- ; 
            m_nWritesActive++ ; 
            break ; 
        }
        else
        {   // It must be a Read thread so we can release it and continue
            // to release other read threads that follow
            MTThreadInfo thrdInfo ; 
            m_thrdIDqueue.Pop(thrdInfo) ; 
            ResumeThread(&thrdInfo.thrdID) ; 
            m_nReadsPending-- ; 
            m_nReadsActive++ ; 
        }
    }
}