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
// barcodes.cpp

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "cs_geomdefs.h"

#include "CS_BarCodes.h"

/* 
    These are UPC bar code patterns I think. 
int barpatterns[] = {0x0d,    //  0  
		     0x19,    //  1  
		     0x13,    //  2  
		     0x3d,    //  3  
		     0x23,    //  4  
		     0x31,    //  5  
		     0x2f,    //  6  
		     0x3b,    //  7  
		     0x37,    //  8  
		     0x0b} ;  //  9  
 */


//! This is the 3 of 9 barcode pattern structure definition
CS_BarPattern3of9 cs_bpats39data[] = 
            {{'0', 0x06, 0x04},
	     {'1', 0x11, 0x04},
	     {'2', 0x09, 0x04},
	     {'3', 0x18, 0x04},
	     {'4', 0x05, 0x04},
	     {'5', 0x14, 0x04},
	     {'6', 0x0c, 0x04},
	     {'7', 0x03, 0x04},
	     {'8', 0x12, 0x04},
	     {'9', 0x0a, 0x04},
	     {'A', 0x11, 0x02},
	     {'B', 0x09, 0x02},
	     {'C', 0x18, 0x02},
	     {'D', 0x05, 0x02},
	     {'E', 0x14, 0x02},
	     {'F', 0x0c, 0x02},
	     {'G', 0x03, 0x02},
	     {'H', 0x12, 0x02},
	     {'I', 0x0a, 0x02},
	     {'J', 0x06, 0x02},
	     {'K', 0x11, 0x01},
	     {'L', 0x09, 0x01},
	     {'M', 0x18, 0x01},
	     {'N', 0x05, 0x01},
	     {'O', 0x14, 0x01},
	     {'P', 0x0c, 0x01},
	     {'Q', 0x03, 0x01},
	     {'R', 0x12, 0x01},
	     {'S', 0x0a, 0x01},
	     {'T', 0x06, 0x01},
	     {'U', 0x11, 0x08},
	     {'V', 0x09, 0x08},
	     {'W', 0x18, 0x08},
	     {'X', 0x05, 0x08},
	     {'Y', 0x14, 0x08},
	     {'Z', 0x0c, 0x08},
	     {'-', 0x03, 0x08},
	     {'.', 0x12, 0x08},
	     {' ', 0x0a, 0x08},
	     {'*', 0x06, 0x08},
	     {'$', 0x00, 0x0e},
	     {'/', 0x00, 0x0d},
	     {'+', 0x00, 0x0b},
	     {'%', 0x00, 0x07},
	     {0, 0x00, 0x00} };


static int getbars3of9(char c)
{
    int n ;
    n = 0 ;
    while (cs_bpats39data[n].c != 0)
    {
        if (cs_bpats39data[n].c == c)
            return cs_bpats39data[n].bars ;
        n++ ;
    }
    return -1  ; /* error */
}

static int getspaces3of9(char c)
{
    int n ;
    n = 0 ;
    while (cs_bpats39data[n].c != 0)
    {
        if (cs_bpats39data[n].c == c)
            return cs_bpats39data[n].spaces ;
        n++ ;
    }
    return -1  ; /* error */
}

CS_BarCode::CS_BarCode() 
{
    SetDefault3of9() ; 
}

void CS_BarCode::SetDefault3of9()
{
    mode = THREEOFNINE ; 
    barstr = "0" ; 
    lheight = 10.0 ; 
    lwidth = 1.0 ;   
    spcfactor = 1.0 ;
    nThick = 3 ;  
    nThin = 1 ;   
    nCharSpace = 1 ; 
    rotation = 0.0 ;
}

int CS_BarCode::GenCode(char *str) 
{
    if (mode == THREEOFNINE)
        return Gen3of9Code(str) ;
    return 0 ; 
}

int CS_BarCode::GenChar(char c)
{
    if (mode == THREEOFNINE)
        return Gen3of9Char(c) ;
    return 0 ; 
}


int CS_BarCode::Gen3of9Code(char *str)
{
    if (str)
        barstr = str ; 
    codecrv.Reset() ; // clear out existing data. 
    nxtpnt = CS_POINT(0,0,0) ; // initialize start point

    // Generate the 3 of 9 bar code
    Gen3of9Char('*') ;
    
    for (unsigned int i=0; i<strlen(barstr); i++)
        Gen3of9Char(barstr[i]) ;

    Gen3of9Char('*') ;

    return 1 ; /* Done */
}

/************************************************************************
   printbars39 prints vertical lines using the binary pattern passed to it.
   The bar pattern consist of wide and narrow black and space bars.
   Two binary patterns are passed bars & spaces. If the bit is 1 a wide
   block is output otherwise a narrow block is output. The bars and spaces
   alternate, starting with bars and ending with bars so that a black
   bar starts and ends each character.
*************************************************************************/


int CS_BarCode::Gen3of9Char(char c)
{
    CS_POINT startpnt, endpnt ;
    int i,n ;
    double deltax ; 

    int bars = getbars3of9(toupper(c)) ; 
    int spcs = getspaces3of9(toupper(c)) ;

    startpnt = nxtpnt ; 
    endpnt = nxtpnt ; 
    endpnt.y += lheight ; 
    
    for(i=0;i<9;i++)
    {
        if ((i & 0x01) == 0)
        {  // then we're printing the next bar
            if ((bars & 0x0010) != 0)
            {  // then print wide
                n = nThick ;
            }
            else
            {  // print narrow
                n = nThin ;
            }
            /***************************************************************
            Since the origin is in the middle of the trace always have to
            offset the current position by 1/2 the width of the current
            bar size. Thus add half the width, then draw the line, and
            then add the second half.
            ****************************************************************/
            deltax = lwidth / 2.0 ; 
            for (int j=0; j < n; j++)
            {
                startpnt.x += deltax ; 
                endpnt.x += deltax ; 
                codecrv.Append(new CS_LineSeg(startpnt, endpnt), CS_NOENDPOINTADJUSTMENT) ; 
            }
            bars <<= 1 ; // next bit
        }
        else
        {  // we're outputting the next space
            if ((spcs & 0x0008) != 0)
            {  // then print wide
                n = nThick ;
            }
            else
            {  // print narrow
                n = nThin ;
            }

            double deltax = lwidth * spcfactor * n ; ; 
            startpnt.x += deltax ; 
            endpnt.x += deltax ; 
            spcs <<= 1 ; // next bit
        }
    }

    deltax = lwidth * spcfactor * nCharSpace ; ; 
    nxtpnt.x = startpnt.x + deltax ; 

    return 0 ; 
}


int CS_BarCode::Print(CS_POINT &pnt, double rot, double scl) 
{
    return 0 ; 
}