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
// cs_crvgroup.cpp

#pragma warning( disable : 4786 )

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_curves.h"

#include "cs_crvgroup.h"


int CS_InitGroupList(CS_CurveVec &cvec, CS_CrvGrpList &grplist)
{
    unsigned int i ; 
    for (i=0; i < cvec.size(); i++)
    {
        cvec[i]->Complete() ; 
        if (cvec[i]->Closed())
        {
            grplist.push_back(new CS_CrvGrp(cvec[i])) ; 
        }
    }

    return 0 ; 
}

void CS_FreeCrvGrp(CS_CrvGrpList &grplist)
{
    CS_CrvGrpListItr ig ; 
    ig = grplist.begin() ;
    while (ig != grplist.end())
    {
        if ((*ig)->cgl.size() > 0)
            CS_FreeCrvGrp((*ig)->cgl) ; 
        
        delete (*ig) ; // de-alloc the actual curve group
        ig++ ; 
        grplist.pop_front() ; // delete the first element
    }
    grplist.clear() ; 
}

int CS_OrderCurveGroup(CS_CrvGrpList &cgi, CS_CrvGrpList &cgo)
{
    CS_CrvGrp *pcg ; 
    CS_CrvGrpListItr ig, icg, idel ; 
    while (cgi.size() > 0)
    {
        icg = cgi.begin() ; // get next element in list
        pcg = *icg ; // save the curve group pointer
        cgi.pop_front() ; // and then delete it from the list

        ig  = cgi.begin() ;
        while (ig != cgi.end())
        {
            if (pcg->pcrv->PointInside((*ig)->pcrv->StartPoint())) 
            {
                pcg->cgl.push_back(*ig) ; 
                idel = ig ; 
                ig++ ; 
                cgi.erase(idel) ; 
            }
            else
            {
                ig++ ; 
            }
        }

        ig = cgo.begin() ; 
        while (ig != cgo.end())
        {
            if (pcg->pcrv->PointInside((*ig)->pcrv->StartPoint())) 
            {
                pcg->cgl.push_back(*ig) ; 
                idel = ig ; 
                ig++ ; 
                cgo.erase(idel) ; 
            }
            else
            {
                ig++ ; 
            }
        }

        cgo.push_back(pcg) ; // move it to the output list
    }

    for (ig = cgo.begin(); ig != cgo.end(); ig++)
    {
        if ((*ig)->cgl.size() > 1)
        {
            CS_CrvGrpList newcgo ; 
            CS_OrderCurveGroup((*ig)->cgl, newcgo) ; 
            (*ig)->cgl.clear() ; 
            (*ig)->cgl = newcgo ; 
        }
    }

    return 0 ; 
}
