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
// crvisect.cpp - curve intersection routines (chaining support)

#include "math.h"

#pragma warning( disable : 4786 )


#include "cs_geomdefs.h"
#include "cs_mathutls.h"
#include "cs_shapes.h"
#include "cs_curves.h"
#include "cs_chain.h"
#include "cs_QuickSort.h"

//////////////////// DEBUG DECLARATIONS ///////////////////////////
#define SELFISECT(a)      


static int compSegInfoBBoxLR(const void *a, const void *b)
{
    CS_SegDataRecord *pia = (CS_SegDataRecord *)a ; 
    CS_SegDataRecord *pib = (CS_SegDataRecord *)b ; 

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


static int fcnt=0 ; 
// Returns the number of self intersections found. End to end segment 
// intersections are filetered out. \TODO get rid of skipcomplete 
int CS_Curve::SelfIntersect(int direction, CS_IRECList &islist, double *comptol)
{
    if (!nodecnt)
        return 0 ; 

    if (pcnmap)
        delete pcnmap ; 

    SELFISECT(
        csString flname ; 
        flname.Format("sidata%d.txt", fcnt) ; 
        FILE *fp = fopen(flname.c_str(), "w") ; 

        fprintf(fp, "===================================  %d =======================================\n",fcnt++) ; 
        PrintCurve(0, fp) ; 
        fprintf(fp, "\n\n") ; 
        PrintCurve(1, fp) ; 
    ) 

    int i, j ; 

    Complete(direction) ; // sets parent pointers as well

    CS_SegDataRecord *segi = new CS_SegDataRecord[nodecnt+2] ; 
    CS_SegPtr psn ; 
    for (psn = pStart, i=0 ; psn ; i++, psn = psn->next) 
    {
        segi[i].pseg = psn ; 
        segi[i].bbox = psn->BoundingRect() ; 
        segi[i].bbox.Expand(0.01) ; // expand 1%
    }

    qsort(segi, nodecnt, sizeof(CS_SegDataRecord), compSegInfoBBoxLR) ; 

    // Now self intersect the curve
    for (i=0; i < nodecnt-1; i++)
    {
        for (j=i+1; j < nodecnt; j++)
        {
            if (segi[i].bbox.r < segi[j].bbox.l)
                break ; 

            if (segi[i].bbox.Overlaps(segi[j].bbox))
            {
                CS_IRECList isl ; 

                SELFISECT(
                    fprintf(fp,"\ni=%d  j=%d\n", i, j) ; 
                    segi[i].pseg->PrintPoints2D(fp) ; 
                    segi[j].pseg->PrintPoints2D(fp) ; 
                 )

                if (segi[i].pseg->Intersect2D(segi[j].pseg, &isl))
                {
                    SELFISECT( fprintf(fp, "Has %d intersects at: ", isl.size()) ; ) 

                    // If its an end point intersection see if the 
                    // segments are connected
                    CS_IRECListItr iri ; 
                    for (iri = isl.begin(); iri != isl.end(); iri++)
                    {

                        SELFISECT (
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



                        if (!SequentialSegments(&(iri->pir->cpp[0]), &(iri->pir->cps[0]), comptol))
                        {   // Then keep this intersection
                            CS_AddIRECToIRECList(islist, iri->pir) ; 
                            SELFISECT (
                                fprintf(fp, "up0=%.14f  up1=%.14f  us0=%.14f  us0=%.14f\n", 
                                        pir->cpp[0].u, pir->cpp[1].u, 
                                        pir->cps[0].u, pir->cps[1].u) ; 
                            )
                            iri->pir = 0 ; // disable destructor
                        }
                    }
                }
            }
        }
    }
    delete[] segi ; 
    
    // DEBUG CODE 
    SELFISECT ( fclose(fp) ; )

    return (int)islist.size() ; 
}




