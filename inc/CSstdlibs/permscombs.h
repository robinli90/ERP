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

// permscombs.h


#ifndef __PERMSCOMBS_H__
#define __PERMSCOMBS_H__

#ifdef WIN32

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#pragma warning( disable : 4996 )

#endif


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Permute a list of objects
//////////////////////////////////////////////////////////////////

// Support function used by permite which rotates an array one
// element to the left, and takes the 0th element and stuffs 
// it into the N-1 position at the end
template<class T> void rotateleft(T *pset, int len, int count)
{
    // Want to rotate the array count number of times
    T tmpVar ; 
    int i, c ; 
    for (c=0; c < count ; c++)
    {
        tmpVar = pset[0] ; 
        for (i=0; i < len-1; i++)
            pset[i] = pset[i+1] ; 
        pset[len-1] = tmpVar ; 
    }
}

// These two template functions define a generic method
// to permute through a list a objects and perform an operation
// on each permutation set. A global memory vector of type T
// is called and permutted through each possible arrangement
// Note that this is thread safe so long as each thread defines
// it's own memory set array on the permute call. Note there
// are no parameters to the permutefunc since the intent is that
// for every possible permutation ordering of the full array 
// pset, permutefunc will be called once. Thus, it is assumed 
// that permutefunc will have it's own internal reference to the
// start of the pset array. 
template<class T> void permute(T *pset, int len, void (*permutefunc)())
{
    int i ; 
    if (len == 1)
    {
        permutefunc() ;
    }
    else
    {
        for (i=0; i < len; i++)
        {
            permute(pset+1, len - 1, permutefunc) ;
            rotateleft<T>(pset, len, 1) ; 
        }
    }
}

//
//////////////////////////////////////////////////////////////////
// End permute functions
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


#endif 
