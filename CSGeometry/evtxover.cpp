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
// evtxover.cpp - works out curve crossover type for entries in UEventList


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

#include "cs_offset.h"
#include "cs_offsoval.h"

#ifdef	CSDEBUG
#define CS_DEBUG(a)                
#define CS_FAULTASSERT(a)           a
#else
#define CS_DEBUG(a)
#define CS_FAULTASSERT(a)           
#endif


// Here we scan all the intersection and overlap events and label each
// intersection/overlap as either a touch off type or a crossover type. 
// This information is used in the decision process when doing the final
// offset processing
void UEventList::LabelCrossovers()
{
    int i ;
    i = 0 ; 

    for (i=0 ; i < listlen; i++)
    {
        if (((plist[i].einfo & (UEVENT_DELETED | UEVENT_INVERTARC)) != 0) ||
            (plist[i].pevent->status != 0))
            continue ; // ignore it or it's already been done

        // else we have to deal with the intersect of overlap intersect
        // condition
        if ((plist[i].einfo & UEVENT_OVERLAP) && 
            (plist[i].einfo & UEVENT_STARTPOINT)) 
        {   // For overlap events we have to search forward to find the
            // end event if this is a start event

            // The next overlap event has to be the matching end overlap 
            // condition to this start overlap condition
            int j ; 
            for (j=i+1; j < listlen ; j++)
            {
                if ((plist[j].einfo & UEVENT_OVERLAP) && 
                    !(plist[j].einfo & UEVENT_DELETED))
                    break ; 
            }

            if (j < listlen)
            {   // Then we found the end overlap record
                // So we want to set the crossover/touch off bits for these 
                // records
                switch(OverlapCrossover(i,j))
                {
                case XOVER_XLR :
                    plist[i].einfo |= UEVENT_CROSSOVER | UEVENT_LEFT ;
                    plist[i].pevent->status |= UEVENT_CROSSOVER | UEVENT_LEFT ; 
                    plist[j].einfo |= UEVENT_CROSSOVER | UEVENT_LEFT ;
                    plist[j].pevent->status |= UEVENT_CROSSOVER | UEVENT_LEFT ; 
                    break ; 
                case XOVER_XRL :
                    plist[i].einfo |= UEVENT_CROSSOVER | UEVENT_RIGHT ;
                    plist[i].pevent->status |= UEVENT_CROSSOVER | UEVENT_RIGHT ;
                    plist[j].einfo |= UEVENT_CROSSOVER | UEVENT_RIGHT ;
                    plist[j].pevent->status |= UEVENT_CROSSOVER | UEVENT_RIGHT ;
                    break ; 
                case XOVER_TL :
                    plist[i].einfo |= UEVENT_TOUCHOFF | UEVENT_LEFT ;
                    plist[i].pevent->status |= UEVENT_TOUCHOFF | UEVENT_LEFT ; 
                    plist[j].einfo |= UEVENT_TOUCHOFF | UEVENT_LEFT ;
                    plist[j].pevent->status |= UEVENT_TOUCHOFF | UEVENT_LEFT ; 
                    break ; 
                case XOVER_TR :
                    plist[i].einfo |= UEVENT_TOUCHOFF | UEVENT_RIGHT ;
                    plist[i].pevent->status |= UEVENT_TOUCHOFF | UEVENT_RIGHT ; 
                    plist[j].einfo |= UEVENT_TOUCHOFF | UEVENT_RIGHT ;
                    plist[j].pevent->status |= UEVENT_TOUCHOFF | UEVENT_RIGHT ; 
                    break ; 
                }
            }
            else
            {   // Something went wrong in the pre-processing 
                sprintf(szGeomErrString, 
                    "No matching overlap end found for node %d", i) ; 
            }
        }
        else if (plist[i].einfo & UEVENT_INTERSECTION)
        {
            switch(IntersectionCrossover(i))
            {
            case XOVER_XLR :
                plist[i].einfo |= UEVENT_CROSSOVER | UEVENT_LEFT ; 
                plist[i].pevent->status |= UEVENT_CROSSOVER | UEVENT_LEFT ;
                break ; 
            case XOVER_XRL :
                plist[i].einfo |= UEVENT_CROSSOVER | UEVENT_RIGHT ;  
                plist[i].pevent->status |= UEVENT_CROSSOVER | UEVENT_RIGHT ;
                break ; 
            case XOVER_TL :
                plist[i].einfo |= UEVENT_TOUCHOFF | UEVENT_LEFT ; 
                plist[i].pevent->status |= UEVENT_TOUCHOFF | UEVENT_LEFT ;
                break ; 
            case XOVER_TR :
                plist[i].einfo |= UEVENT_TOUCHOFF | UEVENT_RIGHT ; 
                plist[i].pevent->status |= UEVENT_TOUCHOFF | UEVENT_RIGHT ;
                break ; 
            }
        }
    }
}


/*
  See RR-Vol1 Pgs.175-192

  The 6 +/-signs represent the 6 possible cross product combinations
  in the following order 02 03 12 13 01 23 where each digit represents
  a vector. So in the diagram below for example

                          O  
                        // \\
                      / /   \ \
                    /  /     \  \
                  /   /       \   \
                /|   /         \    \|
              /     /           \     \
            /     |/            |\      \
          /       /               \       \
        A=0      B=1              C=2       D=3

  we have four vectors AO, OB, CO, OD which would be substituted 
  for vectors 0,1,2,3 respectively. The cross product Z component
  if >=0 results in a plus sign and a - sign if less than 0. The 
  left column shows the arrangement of the vectors (which position
  the vector is in for that permutation). The cross prodcucts 
  represented there are as stated above 02, 03, 12, 13, 01, 23 
  (or 02=AOxCO  03=AOxOD  12=OBxCO  etc... 
  The numeric columns after the +/-'s are the binary representations
  of the +/-'s in different forms. The 1st column is the left four bits
  the 2nd column is all bits, and the 3rd column is the decimal value
  of all the bits.  Finally the T/X RL values represent what is 
  happening. T means a touch off condition, X means a crossover, LR means
  CD (or vector 23) crosses vector AB (or 01) from left to right. A L or 
  R on it's own is used to designate the 23 (CD) touches off of AB (01) 
  on the left or right side respectively. 

  Note: when B=C (or equivalent) above we have an overlap situation which 
  this test is not designed to deal with. The overlap logic will correctly
  deal with those cases when they occur.



  Set 1        0 0 1 1 0 2             Type
               2 3 2 3 1 3             
    0 1 2 3  | + - - + - - 09 24 36     TL 
    0 1 3 2  | + - - + - + 09 25 37     TL 
    0 2 3 1  | + - + - - - 0a 28 40     TR 
    0 2 1 3  | + - + + - - 0b 2c 44     XRL
    0 3 1 2  | + - - - - + 08 21 33     XLR
    0 3 2 1  | + - + - - + 0a 29 41     TR 
    1 2 3 0  | - + - + + - 05 16 22     TL 
    1 2 0 3  | - - - + + - 01 06 06     XLR
    1 3 0 2  | + + - + + + 0d 37 55     XRL
    1 3 2 0  | - + - + + + 05 17 23     TL 
    1 0 2 3  | + - - + + - 09 26 38     TR 
    1 0 3 2  | + - - + + + 09 27 39     TR 
    2 3 0 1  | - + + - - - 06 18 24     TL 
    2 3 1 0  | - + + - + - 06 1a 26     TR 
    2 0 1 3  | - - + + - - 03 0c 12     TL 
    2 0 3 1  | - - + - - - 02 08 08     XLR
    2 1 3 0  | - + + + + - 07 1e 30     XRL
    2 1 0 3  | - - + + + - 03 0e 14     TR 
    3 0 1 2  | + + - - - + 0c 31 49     TL 
    3 0 2 1  | + + + - - + 0e 39 57     XRL
    3 1 2 0  | - + - - + + 04 13 19     XLR
    3 1 0 2  | + + - - + + 0c 33 51     TR 
    3 2 0 1  | - + + - - + 06 19 25     TL 
    3 2 1 0  | - + + - + + 06 1b 27     TR 


  Set 2                                Type
    
    0 1 2 3  | - - + - + + 02 0b 11     TR 
    0 1 3 2  | + + + - + - 0e 3a 58     TR 
    0 2 3 1  | - + - + - + 05 15 21     TL 
    0 2 1 3  | - - - - + + 00 03 03     XLR
    0 3 1 2  | + + + + + - 0f 3e 62     XRL
    0 3 2 1  | - + - + - - 05 14 20     TL
    1 2 3 0  | + - + - + + 0a 2b 43     TR 
    1 2 0 3  | + + + + - + 0f 3d 61     XRL
    1 3 0 2  | - - - - - - 00 00 00     XLR
    1 3 2 0  | + - + - + - 0a 2a 42     TR 
    1 0 2 3  | - + + + - + 07 1d 29     TL 
    1 0 3 2  | - + - - - - 04 10 16     TL 
    2 3 0 1  | + - + + + + 0b 2f 47     TR 
    2 3 1 0  | - - - + - + 01 05 05     TL 
    2 0 1 3  | + + - - + - 0c 32 50     TR 
    2 0 3 1  | + + + + + + 0f 3f 63     XRL
    2 1 3 0  | - - - - - + 00 01 01     XLR
    2 1 0 3  | + + - - - - 0c 30 48     TL 
    3 0 1 2  | - - + + + + 03 0f 15     TR 
    3 0 2 1  | - - - - + - 00 02 02     XLR
    3 1 2 0  | + + + + - - 0f 3c 60     XRL
    3 1 0 2  | - - + + - + 03 0d 13     TL 
    3 2 0 1  | + - - - + - 08 22 34     TR 
    3 2 1 0  | + + - + - - 0d 34 52     TL 

  Set 3                                Type 

    0 1 2 3  | + + - + - - 0d 34 52     TL 
    0 1 3 2  | - - - + - + 01 05 05     TL 
    0 2 3 1  | + - + - + - 0a 2a 42     TR 
    0 2 1 3  | + + + + - - 0f 3c 60     XRL
    0 3 1 2  | - - - - - + 00 01 01     XLR
    0 3 2 1  | + - + - + + 0a 2b 43     TR
    1 2 3 0  | - + - + - - 05 14 20     TL 
    1 2 0 3  | - - - - + - 00 02 02     XLR
    1 3 0 2  | + + + + + + 0f 3f 63     XRL
    1 3 2 0  | - + - + - + 05 15 21     TL 
    1 0 2 3  | + - - - + - 08 22 34     TR 
    1 0 3 2  | + - + + + + 0b 2f 47     TR 
    2 3 0 1  | - + - - - - 04 10 16     TL 
    2 3 1 0  | + + + - + - 0e 3a 58     TR 
    2 0 1 3  | - - + + - + 03 0d 13     TL 
    2 0 3 1  | - - - - - - 00 00 00     XLR
    2 1 3 0  | + + + + + - 0f 3e 62     XRL
    2 1 0 3  | - - + + + + 03 0f 15     TR 
    3 0 1 2  | + + - - - - 0c 30 48     TL 
    3 0 2 1  | + + + + - + 0f 3d 61     XRL
    3 1 2 0  | - - - - + + 00 03 03     XLR
    3 1 0 2  | + + - - + - 0c 32 50     TR 
    3 2 0 1  | - + + + - + 07 1d 29     TL 
    3 2 1 0  | - - + - + + 02 0b 11     TR 


  These are the numbers defined above sorted.

  Value	Type	      Value    Type
    0	XLR		5	TL
    0	XLR		5	TL
    1	XLR		12	TL
    1	XLR		13	TL
    2	XLR		13	TL
    2	XLR		16	TL
    3	XLR		16	TL
    3	XLR		20	TL
    5	TL		20	TL
    5	TL		21	TL
    6	XLR		21	TL
    8	XLR		22	TL
    11	TR		23	TL
    11	TR		24	TL
    12	TL		25	TL
    13	TL		29	TL
    13	TL		29	TL
    14	TR		36	TL
    15	TR		37	TL
    15	TR		48	TL
    16	TL		48	TL
    16	TL		49	TL
    19	XLR		52	TL
    20	TL		52	TL
    20	TL		11	TR
    21	TL		11	TR
    21	TL		14	TR
    22	TL		15	TR
    23	TL		15	TR
    24	TL		26	TR
    25	TL		27	TR
    26	TR		34	TR
    27	TR		34	TR
    29	TL		38	TR
    29	TL		39	TR
    30	XRL		40	TR
    33	XLR		41	TR
    34	TR		42	TR
    34	TR		42	TR
    36	TL		43	TR
    37	TL		43	TR
    38	TR		47	TR
    39	TR		47	TR
    40	TR		50	TR
    41	TR		50	TR
    42	TR		51	TR
    42	TR		58	TR
    43	TR		58	TR
    43	TR		0	XLR
    44	XRL		0	XLR
    47	TR		1	XLR
    47	TR		1	XLR
    48	TL		2	XLR
    48	TL		2	XLR
    49	TL		3	XLR
    50	TR		3	XLR
    50	TR		6	XLR
    51	TR		8	XLR
    52	TL		19	XLR
    52	TL		33	XLR
    55	XRL		30	XRL
    57	XRL		44	XRL
    58	TR		55	XRL
    58	TR		57	XRL
    60	XRL		60	XRL
    60	XRL		60	XRL
    61	XRL		61	XRL
    61	XRL		61	XRL
    62	XRL		62	XRL
    62	XRL		62	XRL
    63	XRL		63	XRL
    63	XRL		63	XRL


  From this table we can see that all values are unique thus with the six
  cross products we can uniquely identify the situation. Reducing the 
  above logic is a pain. See the notes on RR-Vol1 pg 192



*/


// The terms represent the condition of the cross products as follows:
//    0 = undefined
//    1 = XLR
//    2 = XRL
//    3 = TL
//    4 = TR

static int terms[] = {
    1,     //  0
    1,     //  1
    1,     //  2
    1,     //  3
    0,     //  4
    3,     //  5
    1,     //  6
    0,     //  7
    1,     //  8
    0,     //  9
    0,     // 10
    4,     // 11
    3,     // 12
    3,     // 13
    4,     // 14
    4,     // 15
    3,     // 16
    0,     // 17
    0,     // 18
    1,     // 19
    3,     // 20
    3,     // 21
    3,     // 22
    3,     // 23
    3,     // 24
    3,     // 25
    4,     // 26
    4,     // 27
    0,     // 28
    3,     // 29
    2,     // 30
    0,     // 31
    0,     // 32
    1,     // 33
    4,     // 34
    0,     // 35
    3,     // 36
    3,     // 37
    4,     // 38
    4,     // 39
    4,     // 40
    4,     // 41
    4,     // 42
    4,     // 43
    2,     // 44
    0,     // 45
    0,     // 46
    4,     // 47
    3,     // 48
    3,     // 49
    4,     // 50
    4,     // 51
    3,     // 52
    0,     // 53
    0,     // 54
    2,     // 55
    0,     // 56
    2,     // 57
    4,     // 58
    0,     // 59
    2,     // 60
    2,     // 61
    2,     // 62
    2      // 63
} ;  


int UEventList::IntersectionCrossover(int i)
{
    UEvent *pev = plist[i].pevent ; 
    CS_VECTOR va, vb ; 
    
    // Must test to see if the intersection occurs at crossover and if it does
    // then we must also grab the adjacent segments work out even more vectors
    // and do the table lookup.
    int aend, bend ; 
    
    aend = 0 ; 
    bend = 0 ; 
    
    /*
        The following logic was intended to do end point cleanupt but 
        for cases where the intersection occured very close to the end
        point problems could arise in certain situations. The file arcerr.prt
        generated such a condition. See RR-Vol2 Pg 179-181 for notes on what 
        happened. The problem though is that this change then breaks the 
        offsetting for excoprt_02.prt for a near zero length inverase 
        arc segment. 
    */

    if (tcomp_EQZ(pev->u1))
        aend = STARTPOINT_SEG ;
    else if (tcomp_EQ(pev->u1, 1.0))
        aend = ENDPOINT_SEG ;

    if (tcomp_EQZ(pev->u2))
        bend = STARTPOINT_SEG ;
    else if (tcomp_EQ(pev->u2, 1.0))
        bend = ENDPOINT_SEG ;

    /*
    // This is the above code corrected to deal with the problem
    if (pev->u1 <= 0.0)
        aend = STARTPOINT_SEG ;
    else if (pev->u1 >= 1.0)
        aend = ENDPOINT_SEG ;

    if (pev->u2 <= 0.0)
        bend = STARTPOINT_SEG ;
    else if (pev->u2 >=  1.0)
        bend = ENDPOINT_SEG ;

    */

    if (!aend && !bend)
    {   // Then intersection is in the middle potentially saving us having
        // to do the full cross product table lookup
        double vabz ; 
        va = pev->psna->UTangent(pev->u1) ; 
        vb = pev->psnb->UTangent(pev->u2) ; 
        vabz = ZCross(va,vb) ; 
        if (tcomp_GT(vabz, 0.0))
            return XOVER_XRL ; 
        else if (tcomp_LT(vabz, 0.0))
            return XOVER_XLR ; 
    }

    // Otherwise we either have tangent arcs or we have a multiple end
    // point condition which requires full blown complex calculations
    CS_VECTOR v0,v1,v2,v3 ; 
    double z0,z1,z2,z3,z4,z5 ;

    v0 = VectorBackwards(pev->pca, pev->psna, pev->u1, aend) ; 
    v1 = VectorForwards(pev->pca, pev->psna, pev->u1, aend) ; 
    v2 = VectorBackwards(pev->pcb, pev->psnb, pev->u2, bend) ; 
    v3 = VectorForwards(pev->pcb, pev->psnb, pev->u2, bend) ; 

    z0 = ZCross(v0, v2) ; 
    z1 = ZCross(v0, v3) ; 
    z2 = ZCross(v1, v2) ; 
    z3 = ZCross(v1, v3) ; 
    z4 = ZCross(v0, v1) ; 
    z5 = ZCross(v2, v3) ; 
    
    unsigned int tableval ; 
    tableval = 0 ; 

    // TO DO - change these to (z0 >= 0.0) after we've debugged the routine
    // since it should be more robust (generate what we want more often) with
    // the more accurate test. The tolerance compare will tend to highlight
    // problems with the algorithm though so it is better to use the tolerance
    // testing during the initial design and testing.

    if (tcomp_GEQ(z0, 0.0))
        tableval |= 0x0020 ; 

    if (tcomp_GEQ(z1, 0.0))
        tableval |= 0x0010 ; 
    
    if (tcomp_GEQ(z2, 0.0))
        tableval |= 0x0008 ; 
    
    if (tcomp_GEQ(z3, 0.0))
        tableval |= 0x0004 ; 
    
    if (tcomp_GEQ(z4, 0.0))
        tableval |= 0x0002 ; 
    
    if (tcomp_GEQ(z5, 0.0))
        tableval |= 0x0001 ; 

    return terms[tableval] ; 

    return 0 ; 
}


/*
    
    See RR VOL2 Pgs 1-2 for a description of what is going on here
    
    See RR Vol2 Pgs 56-57 for a revised description of what is
    happening. Major change from first version is that the vr and
    vs vectors are based on the aa' direction for both A and B
    which simplifies the logic. Note that b' is the start vector
    and b the end vector in the reverse case.
    The data in the tables below was generated with xovlpmain.cpp

  There are quite a number of invalid conditions (impossible due to 
  the fact that overlap sections cannot cross over back on themselves)
  Thus we can test in the logic whenever we get a bad term and during
  the debug process attempt to deal with all the special cases. We
  may have to manually insert entries into the table to deal with
  the special cases that may arise.


    New version without the vr and vs reversal for the reverse case

  Note: text below can be automatically converted to a lookup table
  and tested for consistency with the program parse.exe. First split
  the forward and reverse sections into separate files and then extract
  the last two columns ('18 XLR' only part) and then run parse on the file. 


    a a b b
      p   p

    0 2 1 3   :  - + - - + -  18 XLR 
    0 3 1 2   :  - + - + - +  21 TL
    1 2 0 3   :  + - + - + -  42 TR
    1 3 0 2   :  + - + + - +  45 XRL

    0 2 1 3   :  - + + - + +  27 XLR
    0 3 1 2   :  - + + + - -  28 TL
    1 2 0 3   :  + - - - + +  35 TR
    1 3 0 2   :  + - - + - -  36 XRL

    0 2 1 3   :  + + - - - -  48 XLR
    0 3 1 2   :  + + - - - +  49 TL
    1 2 0 3   :  + + + - - -  56 TR
    1 3 0 2   :  + + + - - +  57 XRL

    0 2 1 3   :  - - + + + +  15 XRL
    0 3 1 2   :  - - + + + -  14 TR
    1 2 0 3   :  - - - + + +   7 TL
    1 3 0 2   :  - - - + + -   6 XLR

    0 2 1 3   :  + + - + + -  54 XLR
    0 3 1 2   :  + + - + + +  55 TL
    1 2 0 3   :  + + + + + -  62 TR
    1 3 0 2   :  + + + + + +  63 XRL

    0 2 1 3   :  - + - - + -  18 XLR
    0 3 1 2   :  - + - + - +  21 TL
    1 2 0 3   :  + - + - + -  42 TR
    1 3 0 2   :  + - + + - +  45 XRL

    0 2 1 3   :  - + - - + +  19 XLR
    0 3 1 2   :  - + - + - -  20 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - -  44 XRL

    0 2 1 3   :  - + + - + -  26 XLR 
    0 3 1 2   :  - + + + - +  29 TL
    1 2 0 3   :  + - - - + -  34 TR
    1 3 0 2   :  + - - + - +  37 XRL

    0 2 1 3   :  - + + - + +  27 XLR
    0 3 1 2   :  - + + + - +  29 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - +  45 XRL

    0 2 1 3   :  - + - - + +  19 XLR
    0 3 1 2   :  - + - + - +  21 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - +  45 XRL

    0 2 1 3   :  - + + - + +  27 XLR
    0 3 1 2   :  - + + + - +  29 TL
    1 2 0 3   :  + - - - + +  35 TR
    1 3 0 2   :  + - - + - +  37 XRL

    0 2 1 3   :  - + + - + -  26 XLR
    0 3 1 2   :  - + + + - +  29 TL
    1 2 0 3   :  + - + - + -  42 TR
    1 3 0 2   :  + - + + - +  45 XRL

    0 2 1 3   :  - + + - + +  27 XLR
    0 3 1 2   :  - + + + - -  28 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - -  44 XRL

    0 2 1 3   :  + + - - + +  51 XLR
    0 3 1 2   :  + + - + - -  52 TL
    1 2 0 3   :  + + + - + +  59 TR
    1 3 0 2   :  + + + + - -  60 XRL

    0 2 1 3   :  - + - - + +  19 XLR
    0 3 1 2   :  - + - + - -  20 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - -  44 XRL

    0 2 1 3   :  + + - - + +  51 XLR
    0 3 1 2   :  + + - + - -  52 TL
    1 2 0 3   :  + + + - + +  59 TR
    1 3 0 2   :  + + + + - -  60 XRL

    0 2 1 3   :  - + - - + +  19 XLR
    0 3 1 2   :  - + - + - -  20 TL
    1 2 0 3   :  + - + - + +  43 TR
    1 3 0 2   :  + - + + - -  44 XRL

    0 2 1 3   :  + + - - + -  50 XLR
    0 3 1 2   :  + + - + - +  53 TL
    1 2 0 3   :  + + + - + -  58 TR
    1 3 0 2   :  + + + + - +  61 XRL

    0 2 1 3   :  - + - + + -  22 XLR
    0 3 1 2   :  - + - + + +  23 TL
    1 2 0 3   :  + - + + + -  46 TR
    1 3 0 2   :  + - + + + +  47 XRL

    Reverse Overlap cases
    (Note the b and bp points are actually swapped when considering 
     what the XRL, XLR, TL and TR values should be)

    a a b b
      p   p

    0 2 1 3   :  - - + - - +   9 XRL
    0 3 1 2   :  - - + + + -  14 TL 
    1 2 0 3   :  + + - - - +  49 TR 
    1 3 0 2   :  + + - + + -  54 XLR

    0 2 1 3   :  - - - - - -   0 XRL 
    0 3 1 2   :  - - - + + +   7 TL 
    1 2 0 3   :  + + + - - -  56 TR 
    1 3 0 2   :  + + + + + +  63 XLR

    0 2 1 3   :  + - + - + +  43 XRL 
    0 3 1 2   :  + - + - + -  42 TL 
    1 2 0 3   :  + - - - + +  35 TR 
    1 3 0 2   :  + - - - + -  34 XLR

    0 2 1 3   :  - + - + - -  20 XLR 
    0 3 1 2   :  - + - + - +  21 TR 
    1 2 0 3   :  - + + + - -  28 TL 
    1 3 0 2   :  - + + + - +  29 XRL

    0 2 1 3   :  + - + + - +  45 XRL
    0 3 1 2   :  + - + + + -  46 TL 
    1 2 0 3   :  + + - + - +  53 TR 
    1 3 0 2   :  + + - + + -  54 XLR

    0 2 1 3   :  - + + - + +  27 XRL
    0 3 1 2   :  - + + + + -  30 TL 
    1 2 0 3   :  + + - - + +  51 TR 
    1 3 0 2   :  + + - + + -  54 XLR

    0 2 1 3   :  - - + - - -   8 XRL
    0 3 1 2   :  - - + + + +  15 TL 
    1 2 0 3   :  + + - - - -  48 TR 
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  - - - - - +   1 XRL
    0 3 1 2   :  - - - + + -   6 TL 
    1 2 0 3   :  + + + - - +  57 TR 
    1 3 0 2   :  + + + + + -  62 XLR

    0 2 1 3   :  - - + - - +   9 XRL
    0 3 1 2   :  - - + + + +  15 TL 
    1 2 0 3   :  + + + - - +  57 TR 
    1 3 0 2   :  + + + + + +  63 XLR

    0 2 1 3   :  - - + - - +   9 XRL
    0 3 1 2   :  - - + + + +  15 TL 
    1 2 0 3   :  + + - - - +  49 TR 
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  - - - - - +   1 XRL
    0 3 1 2   :  - - - + + +   7 TL 
    1 2 0 3   :  + + + - - +  57 TR 
    1 3 0 2   :  + + + + + +  63 XLR

    0 2 1 3   :  - - + - - +   9 XRL
    0 3 1 2   :  - - + + + -  14 TL 
    1 2 0 3   :  + + + - - +  57 TR 
    1 3 0 2   :  + + + + + -  62 XLR

    0 2 1 3   :  - - + - - -   8 XRL
    0 3 1 2   :  - - + + + +  15 TL 
    1 2 0 3   :  + + + - - -  56 TR 
    1 3 0 2   :  + + + + + +  63 XLR

    0 2 1 3   :  + - + - - -  40 XRL
    0 3 1 2   :  + - + + + +  47 TL
    1 2 0 3   :  + + - - - -  48 TR
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  - + + - - -  24 XRL
    0 3 1 2   :  - + + + + +  31 TL
    1 2 0 3   :  + + - - - -  48 TR
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  + - + - - -  40 XRL
    0 3 1 2   :  + - + + + +  47 TL
    1 2 0 3   :  + + - - - -  48 TR
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  - + + - - -  24 XRL
    0 3 1 2   :  - + + + + +  31 TL
    1 2 0 3   :  + + - - - -  48 TR
    1 3 0 2   :  + + - + + +  55 XLR

    0 2 1 3   :  + - + - + +  43 XRL
    0 3 1 2   :  + - + + + -  46 TL
    1 2 0 3   :  + + - - + +  51 TR
    1 3 0 2   :  + + - + + -  54 XLR

    0 2 1 3   :  - + + + - +  29 XRL 
    0 3 1 2   :  - + + + + -  30 TL
    1 2 0 3   :  + + - + - +  53 TR
    1 3 0 2   :  + + - + + -  54 XLR


*/

// These are used when the OVERLAPBREVERSE bit is NOT set
// The program parse.cpp when run on the two right columns in the set 
// tables above will quickly create these tables, and also check 
// the data for consistency.
// The two right columns would be for example:
// 
//  27 XRL
//  14 TL 
//  49 TR 
//  36 XLR
// 
//   as can be seen in the table above. Parse maps the values
//   {XLR, XRL, TL, TR} to {1,2,3,4} respectively

static int forwardTerms[] = {
    0,     //  0
    0,     //  1
    0,     //  2
    0,     //  3
    0,     //  4
    0,     //  5
    1,     //  6
    3,     //  7
    0,     //  8
    0,     //  9
    0,     // 10
    0,     // 11
    0,     // 12
    0,     // 13
    4,     // 14
    2,     // 15
    0,     // 16
    0,     // 17
    1,     // 18
    1,     // 19
    3,     // 20
    3,     // 21
    1,     // 22
    3,     // 23
    0,     // 24
    0,     // 25
    1,     // 26
    1,     // 27
    3,     // 28
    3,     // 29
    0,     // 30
    0,     // 31
    0,     // 32
    0,     // 33
    4,     // 34
    4,     // 35
    2,     // 36
    2,     // 37
    0,     // 38
    0,     // 39
    0,     // 40
    0,     // 41
    4,     // 42
    4,     // 43
    2,     // 44
    2,     // 45
    4,     // 46
    2,     // 47
    1,     // 48
    3,     // 49
    1,     // 50
    1,     // 51
    3,     // 52
    3,     // 53
    1,     // 54
    3,     // 55
    4,     // 56
    2,     // 57
    4,     // 58
    4,     // 59
    2,     // 60
    2,     // 61
    4,     // 62
    2      // 63
} ;


//  34 defined cases which is an oddball number, will probably find more
//  of these eventually. Although there are 32 cases defined for the 
// forward terms (after the few we added with cases 14 through 17) so 
// maybe we do have them all at this point. 

// These are used when the OVERLAPBREVERSE bit is set
static int reverseTerms[] = {
    2,     //  0        
    2,     //  1  
    0,     //  2  
    0,     //  3  
    0,     //  4  
    0,     //  5  
    3,     //  6  
    3,     //  7  
    2,     //  8  
    2,     //  9  
    0,     // 10  
    0,     // 11  
    0,     // 12  
    0,     // 13  
    3,     // 14  
    3,     // 15  
    0,     // 16  
    0,     // 17  
    0,     // 18  
    0,     // 19  
    1,     // 20  
    4,     // 21  
    0,     // 22  
    0,     // 23  
    2,     // 24  
    0,     // 25  
    0,     // 26  
    2,     // 27  
    3,     // 28  
    2,     // 29  
    3,     // 30  
    3,     // 31  
    0,     // 32  
    0,     // 33  
    1,     // 34  
    4,     // 35  
    0,     // 36  
    0,     // 37  
    0,     // 38  
    0,     // 39  
    2,     // 40  
    0,     // 41  
    3,     // 42  
    2,     // 43  
    0,     // 44  
    2,     // 45  
    3,     // 46  
    3,     // 47  
    4,     // 48  
    4,     // 49  
    0,     // 50  
    4,     // 51  
    0,     // 52  
    4,     // 53  
    1,     // 54  
    1,     // 55  
    4,     // 56  
    4,     // 57  
    0,     // 58  
    0,     // 59  
    0,     // 60  
    0,     // 61  
    1,     // 62  
    1      // 63  
} ;


// i=overlap startpoint, j=overlap endpoint
// Note this doesn't take into consideration the case where an overlap
// section goes out and reverses back on itself. See 2nd diagram in 
// RR-Vol2
int UEventList::OverlapCrossover(int i, int j)
{
    // Need to create 6 cross products and then create the logic lookup 
    // value by bit shifting the ZCross condition into a lookup int which
    // is used to read the terms table to give final result.
    UEvent *pevstart = plist[i].pevent ; 
    UEvent *pevend = plist[j].pevent ; 

    int bSidesReversed = 0 ; // gets set when the sides are flipped from 
    // the start and end events

    // only want to do this when working on the same curve (offset)
    // If on different curves (boolean ops) then never set bSidesReversed
    if ((pevstart->pca == pevend->pcb) && 
        (pevstart->cntb <= pevend->cnta))
    {
        bSidesReversed = 1 ; 
    }
    
    // For an overlap we always do full testing
    int astart, aend, bstart, bend ; 
    
    astart = 0 ;
    bstart = 0 ;  

    aend = 0 ; 
    bend = 0 ; 

    // Otherwise we either have tangent arcs or we have a multiple end
    // point condition which requires full blown complex calculations
    CS_VECTOR va, vap, vb, vbp, vr, vs ; 
    double z0,z1,z2,z3,z4,z5 ;
    int BReversed ; 

    BReversed = plist[i].einfo & UEVENT_OVERLAPBREVERSE ;

    if (tcomp_EQZ(pevstart->u1))
        astart = STARTPOINT_SEG ;
    else if (tcomp_EQ(pevstart->u1, 1.0))
        astart = ENDPOINT_SEG ;

    if (tcomp_EQZ(pevend->u1))
        aend = STARTPOINT_SEG ;
    else if (tcomp_EQ(pevend->u1, 1.0))
        aend = ENDPOINT_SEG ;


    if (tcomp_EQZ(pevstart->u2))
        bstart = STARTPOINT_SEG ;
    else if (tcomp_EQ(pevstart->u2, 1.0))
        bstart = ENDPOINT_SEG ;

    if (tcomp_EQZ(pevend->u2))
        bend = STARTPOINT_SEG ;
    else if (tcomp_EQ(pevend->u2, 1.0))
        bend = ENDPOINT_SEG ;

    // 0=a 1=a' 2=b 3=b' 

    // Note we are somewhat messing around with the primes (p extension) 
    // here in that for the b vector if BReversed, then vbp is the start 
    // of the vector chain and vb is the end of the vector chain, so that
    // we always multiply va x vb for the first z0 cross product and 
    // the remainder of the cross products follow from this designatoin

    if (!bSidesReversed)
    {   // Process normally
        va = VectorBackwards(pevstart->pca, pevstart->psna, pevstart->u1, astart) ; 
        vap = VectorForwards(pevend->pca, pevend->psna, pevend->u1, aend) ; 

        vr = pevstart->psna->UTangent(pevstart->u1) ;
        vs = pevend->psna->UTangent(pevend->u1) ; 

        if (!BReversed)
        {
            vb  = VectorBackwards(pevstart->pcb, pevstart->psnb, pevstart->u2, bstart) ; 
            vbp = VectorForwards(pevend->pcb, pevend->psnb, pevend->u2, bend) ; 
        }
        else
        {
            vb  = VectorForwards(pevstart->pcb, pevstart->psnb, pevstart->u2, bstart) ; 
            vbp = VectorBackwards(pevend->pcb, pevend->psnb, pevend->u2, bend) ; 
        }
    }
    else
    {   // Otherwise the sides have to be flipped at one end (reverse a and b in 
        // the end event to accomplish this)
        // Note in this situation the direction is also reversed, since the 
        // orientation is actual from the end to the start
        va = VectorBackwards(pevend->pcb, pevend->psnb, pevend->u2, bend) ; 
        vap = VectorForwards(pevstart->pca, pevstart->psna, pevstart->u1, astart) ; 

        vr = pevend->psnb->UTangent(pevend->u2) ; 
        vs = pevstart->psna->UTangent(pevstart->u1) ;

        if (!BReversed)
        {
            vb = VectorBackwards(pevend->pca, pevend->psna, pevend->u1, aend) ; 
            vbp  = VectorForwards(pevstart->pcb, pevstart->psnb, pevstart->u2, bstart) ; 
        }
        else
        {
            vb = VectorForwards(pevend->pca, pevend->psna, pevend->u1, aend) ; 
            vbp  = VectorBackwards(pevstart->pcb, pevstart->psnb, pevstart->u2, bstart) ; 
        }
    }
    
    z0 = ZCross(va, vr) ; 
    z1 = ZCross(vb, vr) ; 
    z2 = ZCross(va, vb) ; 
    z3 = ZCross(vap, vs) ; 
    z4 = ZCross(vbp, vs) ; 
    z5 = ZCross(vap, vbp) ; 
    
    // TO DO - change these to (z0 >= 0.0) after we've debugged the routine
    // since it should be more robust (generate what we want more often) with
    // the more accurate test. The tolerance compare will tend to highlight
    // problems with the algorithm though so it is better to use the tolerance
    // testing during the initial design and testing.

    unsigned int tableval ; 
    tableval = 0 ; 

    if (tcomp_GEQ(z0, 0.0))
        tableval |= 0x0020 ; 

    if (tcomp_GEQ(z1, 0.0))
        tableval |= 0x0010 ; 
    
    if (tcomp_GEQ(z2, 0.0))
        tableval |= 0x0008 ; 
    
    if (tcomp_GEQ(z3, 0.0))
        tableval |= 0x0004 ; 
    
    if (tcomp_GEQ(z4, 0.0))
        tableval |= 0x0002 ; 
    
    if (tcomp_GEQ(z5, 0.0))
        tableval |= 0x0001 ; 

    if (!BReversed)
        return forwardTerms[tableval] ; 
    else
        return reverseTerms[tableval] ; 
}



// TO DO - may have to investigate effects of changing the size 
// of epsilon, for now it seems to be working OK

CS_VECTOR UEventList::VectorForwards(CS_Curve *pcrv, CS_SegPtr pn, 
                                     double ux, int endstat)
{
    double epsilon = 0.02 ; 

    if (endstat & STARTPOINT_SEG)
    {   // Move ahead 2% along the current segment
        return pn->UTangent(epsilon) ; 
    }
    else if (endstat & ENDPOINT_SEG)
    {   // Then we have to move to the next segment
        if (!pn->next) 
        {   // Test if this is a closed curve 
            if (pcrv->statflags & CS_CLOSEDCURVE)
            {
                return pcrv->pStart->UTangent(epsilon) ; 
            }
            // Otherwise return the end point
            return pn->UTangent(1.0) ; 
        }
        return pn->next->UTangent(epsilon) ; 
    }
    else
    {   // We can move around on the existing segment
        ux += epsilon ; 
        if (ux > 1.0)
            ux = 1.0 ; 
        return  pn->UTangent(ux) ;
    }
}

CS_VECTOR UEventList::VectorBackwards(CS_Curve *pcrv, CS_SegPtr pn, 
                                      double ux, int endstat)
{
    double epsilon = 0.02 ; 

    if (endstat & ENDPOINT_SEG)
    {   // Move ahead 2% along the current segment
        return pn->UTangent(1.0 - epsilon) ; 
    }
    else if (endstat & STARTPOINT_SEG)
    {   // Then we have to move to the next segment
        if (!pn->prev) 
        {   // Test if this is a closed curve 
            if (pcrv->statflags & CS_CLOSEDCURVE)
            {
                return pcrv->pEnd->UTangent(1.0 - epsilon) ; 
            }
            // Otherwise return the end point
            return pn->UTangent(0.0) ; 
        }
        return pn->prev->UTangent(1.0 - epsilon) ; 
    }
    else
    {   // We can move around on the existing segment
        ux -= epsilon ; 
        if (ux < 0.0)
            ux = 0.0 ; 
        return  pn->UTangent(ux) ;
    }
}
