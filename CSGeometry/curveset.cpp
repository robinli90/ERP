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
// curveset.cpp


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <search.h>

#include <algorithm>
#include "cs_geomdefs.h"


#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif



// TO DO - convert this to STL (with STL we can assign a destrcutor function
//          and have everything done for free)
CS_CurveSet::CS_CurveSet()
{
    ploopnode = crvlist.end() ;
}

CS_CurveSet::CS_CurveSet(const CS_CurveSet &cset)
{
    crvlist = cset.crvlist ; 
    ploopnode = crvlist.begin() ; 
}


CS_CurveSet &CS_CurveSet::operator=(const CS_CurveSet &cset)
{
    crvlist = cset.crvlist ; 
    ploopnode = crvlist.begin() ; 
    return *this ; 
}


CS_CurveSet::~CS_CurveSet()
{
    Reset() ;
}

void CS_CurveSet::Reset()
{
    clear() ; 
}

void CS_CurveSet::clear()
{
    CS_CurveVecItr pn = crvlist.begin() ; 
    for (pn = crvlist.begin(); pn != crvlist.end(); pn++)
        delete *pn ; 
    crvlist.clear() ; 
}


// To loop through the set do
//   CS_Curve *pcrv ; 
//   set.InitIterator() ; 
//   while (pcrv = set.NextCurve())
//   {
//      ....
//   }

void CS_CurveSet::InitIterator()
{
    ploopnode = crvlist.begin() ; 
}

CS_Curve *CS_CurveSet::NextCurve()
{
    CS_Curve *retcrv = 0 ;
    if (ploopnode != crvlist.end())
    {
        retcrv = *ploopnode ; 
        ploopnode++ ; 
    }
    return retcrv ; // no more data
}

CS_Curve *CS_CurveSet::RemoveNextCurve()
{
    CS_Curve *retcrv = 0 ;
    if (ploopnode != crvlist.end())
    {
        retcrv = *ploopnode ; 
        ploopnode = crvlist.erase(ploopnode) ; 
    }
    return retcrv ; // no more data
}


int CS_CurveSet::AddCurve(CS_Curve *pcrv)
{
    if (pcrv)
    {
        crvlist.push_back(pcrv) ; 
        return 0 ; 
    }
    return -1 ; // no data
}


int CS_CurveSet::AppendSet(CS_CurveSet &crvset)
{
    CS_CurvePtr pcrv ; 
    crvset.InitIterator() ; 
    while (pcrv = crvset.RemoveNextCurve())
        AddCurve(pcrv) ; 
    return 0 ; 
}


int CS_CurveSet::DeleteCurve(CS_Curve *pcrv)
{
    CS_CurveVecItr pn = find(crvlist.begin(), crvlist.end(), pcrv) ; 
    return DeleteCurve(pn) ; 
}

int CS_CurveSet::DeleteCurve(CS_CurveVecItr pn)
{
    if (pn != crvlist.end())
    {
        int wasend = 0 ; 
        if (ploopnode == crvlist.end()) 
            wasend = 1 ; 

        if (ploopnode == pn)
            ploopnode++ ; 
        crvlist.erase(pn) ; 

        if (wasend)
            ploopnode = crvlist.end() ; 

        return 0 ; 
    }
    return -1 ; 
}

void CS_CurveSet::DeleteAllCurves()
{
    crvlist.clear() ; 
    ploopnode = crvlist.end() ; 
}



struct lessAreaCompFn : public binary_function<CS_CurvePtr, CS_CurvePtr, bool> 
{
	bool operator()(CS_CurvePtr x, CS_CurvePtr y)
        {
            return x->XYarclength < y->XYarclength ; 
        }
};


struct lessAreaCompFnDesc : public binary_function<CS_CurvePtr, CS_CurvePtr, bool> 
{
	bool operator()(CS_CurvePtr x, CS_CurvePtr y)
        {
            return y->XYarclength < x->XYarclength ; 
        }
};

void CS_CurveSet::SortByArea(int descending, int noinit) 
{
    CS_CurvePtr pcrv ; 
    if (!noinit)
    {
        InitIterator() ; 
        while (pcrv = NextCurve())
        {
            pcrv->Complete(CCW) ; 
            if (pcrv->Closed())
                pcrv->XYarclength = pcrv->Area() ; 
            else
                pcrv->XYarclength = pcrv->ArcLength() ; 
        }
    }

    if (!descending)
        sort(crvlist.begin(), crvlist.end(), lessAreaCompFn()) ;
    else
        sort(crvlist.begin(), crvlist.end(), lessAreaCompFnDesc()) ;
}

struct lessLenCompFn : public binary_function<CS_CurvePtr, CS_CurvePtr, bool> 
{
	bool operator()(CS_CurvePtr x, CS_CurvePtr y)
        {
            return x->arclength < y->arclength ; 
        }
};


struct lessLenCompFnDesc : public binary_function<CS_CurvePtr, CS_CurvePtr, bool> 
{
	bool operator()(CS_CurvePtr x, CS_CurvePtr y)
        {
            return y->arclength < x->arclength ; 
        }
};

void CS_CurveSet::SortByArcLength(int descending, int noinit)
{
    CS_CurvePtr pcrv ; 
    if (!noinit)
    {
        InitIterator() ; 
        while (pcrv = NextCurve())
            pcrv->CalcArcLength() ; 
    }

    if (!descending)
        sort(crvlist.begin(), crvlist.end(), lessLenCompFn()) ;
    else
        sort(crvlist.begin(), crvlist.end(), lessLenCompFnDesc()) ;
}