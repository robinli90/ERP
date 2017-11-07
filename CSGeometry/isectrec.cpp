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
// isectrec.cpp - intersection records control class

#include "stdlib.h"

#include "cs_geomdefs.h"

#include "cs_curves.h"


#define CS_DEBUG(a)     

/*
CS_ISectRecord::CS_ISectRecord ()
{
    u1 = 0.0 ;  // uvalue along base curve where intersect occurs
    u2 = 0.0 ;  // u value along along the secondary curve @ intersect
    pseg1 = NULL ; // pointer to the base curve intersection segment
    pseg2 = NULL ; // pointer to the secondary curve intersection record
}

CS_ISectRecord::CS_ISectRecord(double a, double b, CS_POINT &p, 
                   CS_SegPtr ps1, CS_SegPtr ps2) 
{
    u1 = a ; 
    u2 = b ; 
    ipnt = p ; 
    pseg1 = ps1 ; 
    pseg2 = ps2 ; 
}

void CS_ISectRecord::Reset()
{
    ipnt = CS_POINT(0,0,0) ; 
    u1 = 0.0 ;  // uvalue along base curve where intersect occurs
    u2 = 0.0 ;  // u value along along the secondary curve @ intersect
    pseg1 = NULL ; // pointer to the base curve intersection segment
    pseg2 = NULL ; // pointer to the secondary curve intersection record
}

// Set of intersection records
CS_ISectSet::CS_ISectSet()
{
    icnt = 0 ; 
    listsize = 0 ; 
    plist = NULL ; 
}

CS_ISectSet::~CS_ISectSet()
{
    Reset() ; 
}

int CS_ISectSet::CopyFromCS_IntersectList(CS_IntersectList &islist) 
{
    // Convert the isreclist into an isset
    CS_ISectRecord iswrkrec ; 
    CS_ListNode *pn = islist.pFirst ;
    CS_IntersectRec *pisrec ; 
    while (pn)
    {
        pisrec = islist[pn] ; 
        iswrkrec.ipnt  = pisrec->ipnt1 ; 
        iswrkrec.pseg1 = pisrec->psegAstart ;
        iswrkrec.pseg2 = pisrec->psegBstart ; 
        iswrkrec.u1    = pisrec->uastart ; 
        iswrkrec.u2    = pisrec->ubstart ; 

        if (!Add(iswrkrec))
            return -1 ;

        if (pisrec->statinfo & CS_IREC::OVERLAP)
        {   // Then the second point is defined as well
            iswrkrec.ipnt = pisrec->ipnt2 ; 
            iswrkrec.pseg1 = pisrec->psegAend ;
            iswrkrec.pseg2 = pisrec->psegBend ; 
            iswrkrec.u1    = pisrec->uaend ; 
            iswrkrec.u2    = pisrec->ubend ; 

            if (!Add(iswrkrec))
                return -1 ;
        }   
        pn = pn->next ; 
    }
    return 0 ; 
}



// sort by the u1 values of each CS_ISectRecord
void CS_ISectSet::SortSet() 
{
    int i, j ;
    for (i=0;i<icnt-1;i=i+1)
    { 
        for(j=i+1;j<icnt;j=j+1)
        {
            if (plist[i].u1 > plist[j].u1)
            {   // swap the elements
                CS_ISectRecord irtmp = plist[i] ; 
                plist[i] = plist[j] ; 
                plist[j] = irtmp ; 
            }
        }
    }
}

void CS_ISectSet::Reset()
{
    if (plist)
    {
        free(plist) ; 
        plist = NULL ; 
    }
    icnt = 0 ;
    listsize = 0 ; 
}

// add record to the list
int CS_ISectSet::Add(CS_ISectRecord &irec) 
{
    if (icnt >= listsize)
    {   // Then we have to allocate more space for the array
        CS_ISectRecord *pisr ; 
        pisr = (CS_ISectRecord *)
            realloc(plist, sizeof(CS_ISectRecord) * (listsize + 10)) ; 
        if (pisr == NULL) 
        {   // There wasn't enough memory to allocate intersection record list
            return 0 ; // return failure
        }
        listsize += 10 ;
        plist = pisr ; 
    }
    
    plist[icnt++] = irec ; // copy over the intersect information
    return 1 ; // success
}

void CS_ISectSet::DeleteCoincidentPoints()
{
    // We want to filter out any duplicate points found, which could happen
    // if a segment intersects the curve at an endpoint in which case it would
    // intersect with two segments in the base curve. Thus if there are two
    // intersection records where the ipnt's match then delete the second one
    /////////////////////////////////////////////
    // This an O(n^2) operation
    // TO DO - look at making this more efficient
    /////////////////////////////////////////////
    for (int i=0;i<icnt;i++)
    {
        for (int j=i+1; j<icnt; j++)
        {
            if (plist[i].ipnt == plist[j].ipnt)
            {
                DeleteIDX(j) ; 
                j -= 1 ; // since the array was compressed down at [j]
                         // by the delete operation
            }
        }
    }
}

// returns true if it deleted a record, otherwise returns false
int CS_ISectSet::DeleteIDX(int delidx) 
{
    if ((delidx < icnt) && (delidx >= 0))
    {
        for (int i=delidx; i<icnt-1;i++)
            plist[i] = plist[i+1] ; 
        icnt-- ; 
        return 1 ; 
    }
    return 0 ; 
}

void CS_ISectSet::PrintSet(FILE *fp)
{
    if (!fp)
        fp = fpDebugOut ; 
       
    fprintf(fp, "Intersection set has %d nodes\n", icnt) ;
    for (int i=0; i < icnt; i++)
    {
        fprintf(fp, "Node %3d u1=%9.7lf u2=%9.7lf pnt=(%.5lf, %.5lf, %.5lf)\n", 
                    i, plist[i].u1, plist[i].u2, 
                    plist[i].ipnt.p[0] ,
                    plist[i].ipnt.p[1] ,
                    plist[i].ipnt.p[2]) ; 
    }
    fprintf(fp, "\n") ; 
}

void CS_ISectSet::RemovePointsNear(CS_POINT &pnt, double neardist)
{
    int i = 0 ; 
    while (i < icnt)
    {
        CS_VECTOR vm(pnt, plist[i].ipnt) ;

        if (vm.Mag() <= neardist)
        {
            // Then copy the end element to this position and then
            // reduce the length of the list by 1 effectively 
            // deleting the element
            plist[i] = plist[icnt-1] ; 
            plist[icnt-1].Reset() ; 
            icnt -= 1 ; 
            // Don't want to increment i since we want to test this
            // element that was moved here as well
        }
        else
        {  
            i++ ; 
        }
    }
}
*/