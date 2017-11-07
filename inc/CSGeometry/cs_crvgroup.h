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
// cs_crvgroup.h

#include "cs_curves.h."

class CS_CrvGrp ;

typedef list<CS_CrvGrp *> CS_CrvGrpList ;
typedef list<CS_CrvGrp *>::iterator CS_CrvGrpListItr ;


//! Storage class for groups of related curves
/*!
    The intent is to have a structure which defines a set of curves that 
    are related in a tree structure such that curves enclose one another 
    starting from the main curve and then working down to the innermost
    curve loop. All the main curves are expected to be closed although
    you can use this structure in any way you like. 
 */
class CS_CrvGrp
{
public:
    //! The main curve that encloses or defines this group
    CS_CurvePtr pcrv ;

    //! The set of curve groups enclosed/included within/with the main curve
    CS_CrvGrpList cgl ;

    CS_CrvGrp() { pcrv = 0 ; }
    
    CS_CrvGrp(CS_CurvePtr &pc) { pcrv = pc ; } 
    CS_CrvGrp(const CS_CrvGrp &cgrp) 
    {
        pcrv = cgrp.pcrv ; 
        cgl = cgrp.cgl ; 
    }

    CS_CrvGrp &operator=(const CS_CrvGrp &cgrp) 
    {
        pcrv = cgrp.pcrv ;
        cgl = cgrp.cgl ;
        return *this ;
    }
} ;


//! Initializes a CS_CrvGrpList from the vector of curve pointers required by CS_OrderCurveGroup()
int CS_InitGroupList(CS_CurveVec &cvec, CS_CrvGrpList &grplist) ;

//! Must use this to de-allocate memory used in a CS_CrvGrpList
void CS_FreeCrvGrp(CS_CrvGrpList &grplist) ;

//! Order the curve group list
/*!
    \param cgi the input curve group list
    \param cgo the output curve group list, should be empty on entry
    \return 0=success, otherwise an error code is returned

    The cgi list will be empty on exit, with the entire contents
    having been transferred to the cgo list and the cgo list will
    be fully structured with the largest enclosing closed curves
    at the top of the tree like structure. 
 */
int CS_OrderCurveGroup(CS_CrvGrpList &cgi, CS_CrvGrpList &cgo) ;


