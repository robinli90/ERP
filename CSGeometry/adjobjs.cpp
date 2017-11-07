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

// adjobjs.cpp - adjacecny objects

#pragma warning  ( disable : 4786 )

#include "cs_geomdefs.h"
#include "cs_adjobjs.h"


// CS_PolyAdjObj virtual override methods

int CS_PolyAdjObj::SharesEdge(CS_AdjacencyObject &obj, void **pda, void **pdb)
{
    return SharesEdge(&obj, pda, pdb) ; 
}

int CS_PolyAdjObj::SharesEdge(CS_AdjacencyObject *pobj, void **pda, void **pdb) 
{
    CS_PolyAdjObj *paobj = (CS_PolyAdjObj *)pobj ; 
    CS_Curve *pca = this->pcrv ; 
    CS_Curve *pcb = paobj->pcrv ;

    CS_SegPtr pmatcha = 0 ;
    CS_SegPtr pmatchb = 0 ; 
    CS_SegPtr psna ;
    CS_SegPtr psnb ; 
    int overlapcount ; 

    // Just build on this list and delete entire thing at the end
    CS_IRECList islist ; 

    psna = pca->pStart ; 
    while (psna)
    {
        psnb = pcb->pStart ; 
        while (psnb)
        {
            psna->Intersect2D(psnb, &islist) ;
            psnb = psnb->next ; 
        }
        psna = psna->next ; 
    }

    CS_IREC *pisrec ; 
    overlapcount = 0 ; 
    CS_IRECListItr iri ; 

    for (iri = islist.begin(); iri != islist.end(); iri++)
    {
        pisrec = iri->pir ; 
        if (iri->pir->statinfo & CS_IREC::OVERLAP)
        {   // Then they share an edge here
            pmatcha = iri->pir->cpp[0].s ; 
            pmatchb = iri->pir->cps[0].s ; 
            overlapcount++ ; 
            break ; 
        }
    }

    if (pda)
        *pda = pmatcha ; 
    if (pdb) 
        *pdb = pmatchb ; 

    return overlapcount ; 
}
