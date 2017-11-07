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
//! CS_BarCodes.h - barcode generation header file

#ifndef __CS_BARCODES_H__
#define __CS_BARCODES_H__

#pragma warning( disable : 4786 )

#include "cs_vectors.h"
#include "cs_curves.h"

// Data parameters for the barcode

struct CS_BarPattern3of9 {
   char c ;
   int bars ;
   int spaces ;
} ;

extern CS_BarPattern3of9 cs_bpats39data[] ; 


//! Defines a bar code strcuture and data
/*!
    The barcodes themselves are made up of a bunch of fixed width line segments. Thick and thin
    lines are constrcuted by adding multiple single lines together side by side. The lwidth
    parameter defines the spacing used for indexing individual lines when building up an 
    actual barcode line stroke. Thus this parameter will be dependent on the thickness of 
    the line when output to the physical plotting device. The spcfactor is applied as a 
    secondary scaling factor to control space widths since these may need to be slighly
    different than the actual line widths. 

    The codecrv curve is actually a list of CS_LineSeg lines which can then be drawn 
    for each custom application. The virtual function Print() needs to be overridden
    for each of the different environments or printers to be used. 

    All units are dimensionless. 

 */
class CS_BarCode 
{
public :

    enum {
        THREEOFNINE     = 0x01,
    } ; 

    int mode ;          //! defines what type of barcode to gene
    char *barstr ;      //! the actual barcode data string
        
    double scale ;      //! overall scaling factor to increase or decrease
                        //! the size of the generated barcode. 

    double lheight ;    //! height of a line (line length)

    double lwidth ;     //! width of a line. This is the effective output width

    double spcfactor;   //! spacing factor between lines

    // Note the thick and thin are multiplied by the spacing factor to determine
    // how far to shift over for a thin or thick space. The actual spacing distance
    // moved would be scale * (lwidth * (bIsThick ? nThick : nThin)) * spcfactor
    
    int nThick ;        //! number of lines in a thick bar

    int nThin ;         //! number of lines in a thin bar

    int nCharSpace ;    //! number of line widths for spacing between barcode characters

    double rotation ;   //! radian angle the bar code is drawn in

    //! Barcode definition made up of line segments, these are all CS_LineSeg's
    CS_Curve codecrv ;   

    //! Next point to output bars at 
    CS_POINT nxtpnt ; 


    CS_BarCode() ; 

    //! Re-creates the entire bar code in the barcode curve 
    /*!
        \param str the barcode string to output
        \return 0 if OK, else error code is returned. 
     */
    int GenCode(char *str=0) ; 

    //! adds the next character to the barcode 
    /*!
        \param c the barcode character to output
        \return 0 if OK, else error code is returned. 
     */
    int GenChar(char c) ; 


    //! Sets default generation parameters for 3 of 9 codes (this is the ctor default). 
    void SetDefault3of9() ; 

    //! Re-creates the entire bar code in the barcode curve using 3 of 9 pattern
    /*!
        \param str the barcode string to output
        \return 0 if OK, else error code is returned. 
     */
    int Gen3of9Code(char *str=0) ; 

    //! adds the next character to the barcode for the 3 of 9 code format
    /*!
        \param c the barcode character to output
        \return 0 if OK, else error code is returned. 
     */
    int Gen3of9Char(char c) ; 

    //! Must be override this to perform the actual printing function
    /*! 
        \param org The origin point or reference point for the barcode
        \param rotationang rotation angle in radians for code generation
        \param scaling scaling factor to apply while generating code
        \return 0=OK, else an error code.

        This function must be defined for the environment that it is going 
        to be used in to create a valid barcode. In Windows for example it
        would likely draw to the current window in a Paint() message 
        handler. In a CAD system, it would generate the necessary line
        geometry to define the actual barcode. The actual implemenation
        is application specific. 
     */
    virtual int Print(CS_POINT &org, double rotationang=0.0, double scaling=1.0) ; 
} ;

 
#endif 