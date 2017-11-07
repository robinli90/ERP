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
// intersection.cpp - intersection set support routines

#include "math.h"

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_QuickSort.h"

inline 
void CS_AddIRECToIRECList(CS_IRECList *pl, CS_IREC *pir)
{
    CS_INODE node ; 
    node.pir = pir ; 
    pl->push_back(node) ; 
    node.pir = 0 ; 
}

int CS_AppendIRECList(CS_IRECList &dst, CS_IRECList &src) 
{
    CS_IRECListItr irl = src.begin() ; 
    while (irl != src.end())
    {
        dst.push_back(*irl) ; 
        irl->pir = 0 ; // make sure destructor doesn't to anything
        irl++ ; 
    }
    src.clear() ; 
    return (int)dst.size() ; 
}

void CS_AddIRECToIRECList(CS_IRECList &l, CS_IREC *pir)
{
    CS_AddIRECToIRECList(&l, pir) ; 
}

void CS_AddIRECToIRECList(CS_IRECList *pl, CS_INODE &inode)
{
    CS_INODE node ; 
    node.pir = inode.pir ; 
    pl->push_back(node) ; 
    node.pir = 0 ; 
}

void CS_AddIRECToIRECList(CS_IRECList &l, CS_INODE &inode)
{
    CS_AddIRECToIRECList(&l, inode) ; 
}

int comp_IRECList(const void *a, const void *b)
{
    CS_IRECListItr ira, irb ; 
    ira = *((CS_IRECListItr*)a) ; 
    irb = *((CS_IRECListItr*)b) ; 

    return ira->pir->US0() < irb->pir->US0() ;
    // Used to be the following:
    // return ira->pir->UP1() < ira->pir->US1() ;
    // changed July 3, 2010. Used by FitCircle, CS_ClipArcToRect, and xhatching
}

void swap_IRECList(const void *a, const void *b)
{
    CS_IRECListItr ira, irb ; 
    ira = *((CS_IRECListItr*)a) ; 
    irb = *((CS_IRECListItr*)b) ; 

    CS_IREC *pcrtmp ; 
    pcrtmp = ira->pir ; 
    ira->pir = irb->pir ; 
    irb->pir = pcrtmp ; 
}

void CS_IREC::Print(FILE *fp)
{
    if (statinfo & POINT)
    {
        fprintf(fp, "   TYPE = POINT\n") ; 
        fprintf(fp, "     PNT: ") ; ipnt[0].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     UP0=%.5f  US0=%.5f\n", UP0(), US0()) ; 
    }
    else if (statinfo & OVERLAP)
    {
        if (statinfo & BREVERSED)
            fprintf(fp, "   TYPE = OVERLAP, BREVERSED\n") ; 
        else 
            fprintf(fp, "   TYPE = OVERLAP\n") ; 
        fprintf(fp, "     PNT1: ") ; ipnt[0].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     PNT2: ") ; ipnt[1].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     UP0=%.5f  US0=%.5f\n", UP0(), US0()) ; 
        fprintf(fp, "     UP1=%.5f  US1=%.5f\n", UP1(), US1()) ; 
    }
    else if (statinfo & TANGENT)
    {
        fprintf(fp, "   TYPE = TANGENT\n") ; 
        fprintf(fp, "     PNT: ") ; ipnt[0].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     UP0=%.5f  US0=%.5f\n", UP0(), US0()) ; 
    }
    else if (statinfo & PARALLEL)
    {
        fprintf(fp, "   TYPE = PARALLEL\n") ; 
        fprintf(fp, "     PNT1: ") ; ipnt[0].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     PNT2: ") ; ipnt[1].Print(fpDebugOut) ; fprintf(fp, "\n") ; 
        fprintf(fp, "     UP0=%.5f  US0=%.5f\n", UP0(), US0()) ; 
        fprintf(fp, "     UP1=%.5f  US1=%.5f\n", UP1(), US1()) ; 
    }
    else 
    {
        fprintf(fp, "   TYPE = UNDEFINED\n") ; 
    }
}

// Orders the list of intersection records by the A segment ustart 
// u values. All parent pointers must be connected up for this to 
// work properly. Also, the overall curve u values must be valid
// for the base curve (all A segment components). 
int CS_SortIntersectSetByUValue(CS_IRECList &isset, int secondary)
{
    if (!secondary)
        isset.sort() ; 
    else
    {   // Have to do the sorting ourselves 
        int i ; 
        CS_IRECListItr irl ; 
        CS_IRECListItr *irarray = new CS_IRECListItr[isset.size()] ;
        for (i=0, irl = isset.begin(); irl != isset.end(); irl++, i++)
            irarray[i] = irl ; 
        QuickSort(irarray, (int)isset.size(), sizeof(CS_IRECListItr), 
                    comp_IRECList, swap_IRECList) ; 
    }

    return 0 ; 
}


// Note must call CS_SortIntersectSetByUValue() before calling this routine
int CS_DeleteCommonIntersections(CS_IRECList &isset, double *tol)
{
    if (isset.size() == 0)
        return 0 ;

    CS_Curve *pacrv, *pbcrv ;
    CS_IREC *pira, *pirb ;
    int deletecount = 0 ;

    CS_IRECListItr ira, irb ;

    for (ira = isset.begin(); ira != isset.end(); ira++)
    {
        irb = ira ;
        irb++ ;
        if (irb == isset.end())
            break ;

        pira = ira->pir ;
        pirb = irb->pir ;
        pacrv = pira->cpp[0].s->pParent ;
        pbcrv = pira->cps[0].s->pParent ;
        if (CS_SameCurveUPoints(pacrv, pira->UP0(), pirb->UP0(), tol) &&
            ((pira->cps[0].s->pParent == pirb->cps[0].s->pParent) &&
             (CS_SameCurveUPoints(pbcrv, pira->US0(), pirb->US0(), tol))
            )
           )
        {   // Then they're the same, pointdelete the second entry
            isset.erase(irb) ;
            deletecount++ ;
        }
    }

    // Now test last and first
    ira = isset.begin() ; 
    if (tcomp_EQ(ira->pir->UP0(), 1.0) && ira->pir->cpp[0].s->pParent->Closed())
    {
        // We're looping here in case there are multiple nodes at the
        // start that have a u value of 0
        pira = ira->pir ; 
        irb = ira ; 
        irb++ ; 
        while(irb != isset.end())
        {
            pirb = irb->pir ; 
            if (tcomp_NEZ(pirb->UP0()))
                break ; // no need to test anymore

            pbcrv = pira->cps[0].s->pParent ;

            if ((pira->cps[0].s->pParent == pirb->cps[0].s->pParent) &&
                 (CS_SameCurveUPoints(pbcrv, pira->US0(), pirb->US0()))  
               )
            {   // Then they're the same, delete the second entry
                CS_IRECListItr irdel ; 
                irdel = irb ; 
                irb++ ; 
                isset.erase(irdel) ;
                deletecount++ ; 
                continue ; 
            }
            irb++ ; 
        }
    }

    return deletecount ; 
}


// TO DO - clean this up
int CS_DeleteCommonIntersectionPoints(CS_IRECList &isset)
{
    if (isset.size() == 0)
        return 0 ; 


    CS_IRECListItr ira, irb ; 
    CS_IREC *pira, *pirb ; 
    int deletecount = 0 ; 
    
    for (ira = isset.begin(); ira != isset.end(); ira++)
    {
        pira = ira->pir ;
        irb = ira ; 
        irb++ ; 
        while (irb != isset.end())
        {
            pirb = irb->pir ; 
            if (pira->ipnt[0] == pirb->ipnt[0])
            {   // Then they're the same, delete the second entry
                CS_IRECListItr irdel ; 
                irdel = irb ; 
                irb++ ; 
                isset.erase(irdel) ;
                deletecount++ ; 
                continue ; 
            }
            irb++ ; 
        }
    }

    return deletecount ; 
}


int CS_DeleteCommonCrvPntRecs(CS_CrvPntRecLst &cpl)
{
    if (cpl.size() == 0)
        return 0 ; 

    CS_CrvPntRecLstItr ira, irb ; 
    int deletecount = 0 ;
    
    for (ira = cpl.begin(); ira != cpl.end(); ira++)
    {
        irb = ira ;
        irb++ ;
        while (irb != cpl.end())
        {
            if (ira->p == irb->p)
            {   // Then they're the same, delete the second entry
                CS_CrvPntRecLstItr irdel ;
                irdel = irb ;
                irb++ ;
                cpl.erase(irdel) ;
                deletecount++ ;
                continue ;
            }
            irb++ ;
        }
    }

    return deletecount ;
}
