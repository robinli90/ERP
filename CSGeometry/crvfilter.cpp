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
// crvfilter.cpp - filter through curve segments for different properties

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef WATCOMCPP
#include <typeinfo.h>
#endif

#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_vectors.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_chain.h"


#define REMOVEOVERLAP(a)  


struct CS_uRange
{
    double u0, u1 ; 

    CS_uRange() {} ; 
    CS_uRange(double ua, double ub) : u0(ua), u1(ub) {} ; 

    int Full() 
    {
        if (tcomp_EQZ(u0) && tcomp_EQ(u1, 1.0)) 
            return 1 ; 
        else 
            return 0 ; 
    } 

    int operator<(const CS_uRange &ur)
    {
        if (u0 < ur.u0)
            return 1 ; 
        return 0 ; 
    }

    int operator==(const CS_uRange &ur)
    {
        if (u0 == ur.u0)
            return 1 ; 
        return 0 ; 
    }

    int operator<=(const CS_uRange &ur)
    {
        if (u0 <= ur.u0)
            return 1 ; 
        return 0 ; 
    }

    int operator>=(const CS_uRange &ur)
    {
        if (u0 >= ur.u0)
            return 1 ; 
        return 0 ; 
    }


    int operator>(const CS_uRange &ur)
    {
        if (u0 > ur.u0)
            return 1 ; 
        return 0 ; 
    }

} ;

typedef list<CS_uRange> CS_uRangeList ;
typedef list<CS_uRange>::iterator CS_uRangeListItr ;

struct CS_SegOvrlapRecord
{
    CS_SegPtr pseg ; 
    CS_RECT bbox ; 
    int del ; 
    CS_uRangeList url ; // sections to delete

    int MergeRangeList() ; 
} ;

#ifndef max
#define   max(a,b)      (a > b ? a : b)
#endif 

// Returns the number of unique ranges defined
int CS_SegOvrlapRecord::MergeRangeList()
{
    if (url.size() == 0)
        return 0 ; 

    url.sort() ; 
    CS_uRangeListItr uri ; 
    uri = url.begin() ; 
    while (uri != url.end())
    {   
        if (uri->Full())
        {   // Then simply create a single record and exit
            url.clear() ; 
            url.push_back(CS_uRange(0,1)) ; 
            return 1 ; 
        }

        CS_uRangeListItr urinxt = uri ; 
        urinxt++ ; 
        if (urinxt != url.end())
        {   // Then can merge these two record
            if (tcomp_GEQ(uri->u1, urinxt->u0))
            {   // Then these two overlap
                uri->u1 = max(uri->u1, urinxt->u1) ; 
                // Delete the next record
                url.erase(urinxt) ; 
                // Stay on uri record in case it will also merge 
                // with the following record
            }
            else
            {   // Advance to next range since this one doesn't intersect
                // with any others
                uri++ ; 
            }
        }
        else
        {   // We're done
            uri++ ; 
        }
    }

    return (int)url.size() ;
}

static int compSegBBoxLR(const void *a, const void *b)
{
    CS_SegOvrlapRecord *pia = (CS_SegOvrlapRecord *)a ; 
    CS_SegOvrlapRecord *pib = (CS_SegOvrlapRecord *)b ; 

    if (pia->bbox.l < pib->bbox.l)
        return -1 ; 
    else if (pia->bbox.l > pib->bbox.l)
        return 1 ; 
    else if (pia->bbox.t < pib->bbox.t)
        return -1 ; 
    else if (pia->bbox.t > pib->bbox.t)
        return 1 ; 
    return 0 ; 
}


// returns true if the curve overlaps itself anywhere,
int CS_CurveOverlaps(CS_Curve *ptstcrv)
{
    // Simply check adjacent curves for overlap intersections
    CS_SegOvrlapRecord *segrec = new CS_SegOvrlapRecord[ptstcrv->nodecnt+2] ; 
    CS_SegPtr psn ; 
    int i, j ; 
    for (psn = ptstcrv->pStart, i=0 ; psn ; i++, psn = psn->next) 
    {
        segrec[i].pseg = psn ; 
        segrec[i].del = 0 ; 
        segrec[i].bbox = psn->BoundingRect() ; 
    }

    qsort(segrec, ptstcrv->nodecnt, sizeof(CS_SegOvrlapRecord), compSegBBoxLR) ; 

    int hasOverlap = 0 ; 
    for (i=0; hasOverlap == 0 && i < ptstcrv->nodecnt-1; i++)
    {
        for (j=i+1; hasOverlap == 0 && j < ptstcrv->nodecnt; j++)
        {
            if (segrec[i].bbox.r < segrec[j].bbox.l)
                break ; // none of the rest will intersect

            if (segrec[i].bbox.Overlaps(segrec[j].bbox))
            {
                CS_IRECList isl ;

                if (segrec[i].pseg->Intersect2D(segrec[j].pseg, &isl))
                {   // If its an end point intersection see if the 
                    // segments are connected
                    CS_IRECListItr iri ; 
                    for (iri = isl.begin(); iri != isl.end(); iri++)
                    {
                        if (iri->pir->statinfo & CS_IREC::OVERLAP)
                        {   // want to create delete record for the second section
                            hasOverlap = 1 ; 
                        }
                    }
                }
            }
        }
    }

    delete[] segrec ;

    return hasOverlap ; 
}

// remove overlapping segments from the curve and rebuild the curve without
// any overlapping segments. Curve direction and start is same as the 
// initial start segment in ptstcrv
int CS_RemoveOverlaps(CS_Curve *ptstcrv, CS_CurvePtr &pnewcrv, int mode)
{
    if (ptstcrv->nodecnt < 2)
        return 0 ; // nothing to do
    
    int i, j ; 

    CS_SegOvrlapRecord *segrec = new CS_SegOvrlapRecord[ptstcrv->nodecnt+2] ; 
    CS_SegPtr psn ; 
    for (psn = ptstcrv->pStart, i=0 ; psn ; i++, psn = psn->next) 
    {
        segrec[i].pseg = psn ; 
        segrec[i].del = 0 ; 
        segrec[i].bbox = psn->BoundingRect() ; 
    }

    qsort(segrec, ptstcrv->nodecnt, sizeof(CS_SegOvrlapRecord), compSegBBoxLR) ; 


    for (i=0; i < ptstcrv->nodecnt-1; i++)
    {
        segrec[i].MergeRangeList() ; 

        if (segrec[i].url.size() == 0)
        {   // Then process this segment normally. 
            for (j=i+1; j < ptstcrv->nodecnt; j++)
            {
                if (segrec[i].bbox.r < segrec[j].bbox.l)
                    break ; // none of the rest will intersect

                if (segrec[i].bbox.Overlaps(segrec[j].bbox))
                {
                    CS_IRECList isl ;

                    if (segrec[i].pseg->Intersect2D(segrec[j].pseg, &isl))
                    {   // If its an end point intersection see if the 
                        // segments are connected
                        CS_IRECListItr iri ; 
                        for (iri = isl.begin(); iri != isl.end(); iri++)
                        {
                            if (iri->pir->statinfo & CS_IREC::OVERLAP)
                            {   // want to create delete record for the second section
                                CS_uRange ur ; 

                                ur.u0 = iri->SegUS0() ;
                                ur.u1 = iri->SegUS1() ;
                                segrec[j].url.push_back(ur) ; 
                            }
                        }
                    }
                }
            }
        }
        else 
        {   // Then there is at least one deleted section to 
            // this segment. See if it's the full segment that is 
            // being skipped over. 
            if (segrec[i].url.size() == 1)
            {
                if (segrec[i].del || segrec[i].url.begin()->Full())
                {
                    segrec[i].del = 1 ; 
                    continue ; // don't process this segment
                }
            }


            // TO DO - needs some work on efficiency

            // The overlap sections can be found easily enough but for this to work
            // efficiently the overlap segments have to be marked as they are detected. 
            // Say for example, one of the segments has a section in the middle the 
            // overlaps and is then removed from processing. Then when it is reached 
            // in the i part the loop it is now two segments and not just one anymore.
            // So it has to be split up, and then setup into the array in sorted order 
            // so that subsequent processing can continue correctly. 



            CS_Curve testsegs ; 
            // Else process the segment by creating sub segments
            // in the test curve

            CS_uRangeListItr uri1, uri2 ; 
            uri1 = segrec[i].url.begin() ; 
            if (tcomp_GT(uri1->u0, 0.0))
            {   // Then have to create the initial record
                testsegs.Append(segrec[i].pseg->Copy(0, uri1->u0)) ;
            }

            while (uri1 != segrec[i].url.end()) 
            {
                uri2 = uri1 ; 
                uri2++ ; 
                if (uri2 == segrec[i].url.end())
                {
                    if (tcomp_LT(uri1->u1, 1.0))
                    {
                        testsegs.Append(segrec[i].pseg->Copy(uri1->u1, 1.0)) ;
                    }
                }
                else
                {   // Add the section between the two delete records
                    testsegs.Append(segrec[i].pseg->Copy(uri1->u1, uri2->u0)) ;
                }

                uri1++ ; 
            }


            CS_SegPtr pseg = testsegs.pStart ; 
            while (pseg)
            {
                for (j=i+1; j < ptstcrv->nodecnt; j++)
                {
                    if (segrec[i].bbox.r < segrec[j].bbox.l)
                        break ; // none of the rest will intersect

                    if (segrec[i].bbox.Overlaps(segrec[j].bbox))
                    {
                        // Then there is a possibility of overlap
                        CS_IRECList isl ;

                        REMOVEOVERLAP(
                            fprintf(fp,"\ni=%d  j=%d\n", i, j) ; 
                            segrec[i].pseg->PrintPoints2D(fp) ; 
                            segrec[j].pseg->PrintPoints2D(fp) ; 
                        )

                        if (segrec[i].pseg->Intersect2D(segrec[j].pseg, &isl))
                        {
                            REMOVEOVERLAP( fprintf(fp, "Has %d intersects at: ", isl.size()) ; ) 

                            // If its an end point intersection see if the 
                            // segments are connected
                            CS_IRECListItr iri ; 
                            for (iri = isl.begin(); iri != isl.end(); iri++)
                            {

                                REMOVEOVERLAP (
                                    CS_IREC *pir = iri->pir ; 
                                    pir->ipnt[0].Print(fp) ; 
                                    fprintf(fp, "===") ; 
                                    pir->ipnt[1].Print(fp) ; 
                                    fprintf(fp, "\n%s %s %s %s %s\n", 
                                        pir->statinfo & CS_IREC::POINT ? "POINT" : "", 
                                        pir->statinfo & CS_IREC::OVERLAP ? "OVERLAP" : "", 
                                        pir->statinfo & CS_IREC::TANGENT ? "TANGENT" : "", 
                                        pir->statinfo & CS_IREC::PARALLEL ? "PARALLEL" : "", 
                                        pir->statinfo & CS_IREC::BREVERSED ? "BREVERSED" : "") ; 
                                )



                                if (iri->pir->statinfo & CS_IREC::OVERLAP)
                                {   // want to create delete record for the second section
                                    CS_uRange ur ; 

                                    ur.u0 = iri->SegUS0() ;
                                    ur.u1 = iri->SegUS1() ;
                                    segrec[j].url.push_back(ur) ; 
                                }
                            }
                        }
                    }
                }

                pseg = pseg->next ; 
            }
        }
    }



    // Now ready to rebuild the final output curve. 
    CS_SegPtr *pslist = new CS_SegPtr[ptstcrv->nodecnt + 10] ;
    int nsegs = 0 ; 
    for (i=0; i < ptstcrv->nodecnt; i++)
    {
        segrec[i].MergeRangeList() ; 

        if (segrec[i].url.size() == 0)
        {   // Then add this entire segment
            pslist[nsegs++] = segrec[i].pseg->Copy() ; 
        }
        else 
        {   // Then process this one record
            CS_uRangeListItr uri1, uri2 ; 
            uri1 = segrec[i].url.begin() ; 
            
            if (tcomp_GT(uri1->u0, 0.0))
            {   // Then have to create the initial record
                pslist[nsegs++] = segrec[i].pseg->Copy(0, uri1->u0) ;
            }

            while (uri1 != segrec[i].url.end()) 
            {
                uri2 = uri1 ; 
                uri2++ ; 
                if (uri2 == segrec[i].url.end())
                {
                    if (tcomp_LT(uri1->u1, 1.0))
                    {
                        pslist[nsegs++] = segrec[i].pseg->Copy(uri1->u1, 1.0) ;
                    }
                }
                else
                {   // Add the section between the two delete records
                    pslist[nsegs++] = segrec[i].pseg->Copy(uri1->u1, uri2->u0) ;
                }
                uri1++ ; 
            }
        }
    }

    CS_CurveSet cset ; 
    CS_ChainUniqueSegments(pslist, nsegs, cset) ;

    int retcode = 0 ; 
    if (cset.Length() < 1)
    {
        retcode = 1 ; // error in processing
    }
    else
    {
        cset.InitIterator() ; 
        pnewcrv = cset.RemoveNextCurve() ; 

        if (cset.Length() > 0)
            retcode = 2 ; 
    }

    // De-allocate all the segments
    for (i=0; i < nsegs; i++)
        delete pslist[i] ; 
    delete[] pslist ; 

    delete[] segrec ; 

    return retcode ; 
}
