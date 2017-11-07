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
// cs_fonts.h - character font control class

#ifndef __CS_FONTS_H__

#define __CS_FONTS_H__


#include "cs_curves.h"
#include "cs_bezier.h"
//////////////////////////////////////////////////////////////////////////////


//! Data strucuture used to store each character in the full font set.
/*!
    The font file is made up of characters, which are made up of curves
    and terminated by an ENDCHAR string as follows:


        Note these comments cannot appear in the file

    \verbatim
    CHAR {'a'|hh}               each line starts with a char indicator
    CURVE                       then the curve start indicator
    {ARC|LINE}......            the curve data
    .
    .
    END                         end of first curve
    CURVE                       remaining curves
    {ARC|LINE}......
    .
    .
    END
    CURVE
    {ARC|LINE}......
    .
    .
    END
    .
    .
    .
    ENDCHAR                     end of character definition

    CHAR {'a'|hh}
    .
    .
    .

    \endverbatim

    The end of file indicates there are no more characters to be loaded 
    The valid range of characters must have hex values of 0 -> 255. 
    Note 0 should be reserved for NULL bytes but can be defined for 
    special purposes if required, to store a company logo for example.


    The class will also load a text file definition of TrueType fonts, and
    convert the Bezier spline data to lines and arcs, as well as load the 
    Bezier representation. Note that if the standard line/arc font file
    is loaded there will be no Bezier data defined. Only when loading 
    TrueType font text files is the Bezier data defined. Also, the format
    of the TrueType font file below is not an actual TTF file but an ASCII
    representation of the raw Bezier control points which make up the 
    font. This file is created by first processing an actual TTF file
    with the open source utility ttf2txt.exe which is built from the 
    open source FreeType library. Instructions for downloading and 
    using the ttf2txt.exe utility as well as where to get FreeType can be
    found here http://www.cadamation.com/truetype .

    \verbatim

    # -------------------
    CHAR 32, ' '
    WIDTH 569
    ENDCHAR
    # -------------------
    CHAR 33, '!'
    WIDTH 569
    MOVE 231,364
    DRAW 176,1141,1
    DRAW 176,1466,1
    DRAW 399,1466,1
    DRAW 399,1141,1
    DRAW 347,364,1
    MOVE 184,0
    DRAW 184,205,1
    DRAW 391,205,1
    DRAW 391,0,1
    ENDCHAR
    # -------------------
    CHAR 34, '"'
    WIDTH 727
    MOVE 144,947
    DRAW 94,1226,1
    DRAW 94,1466,1
    DRAW 299,1466,1
    DRAW 299,1226,1
    DRAW 254,947,1
    MOVE 475,947
    DRAW 426,1226,1
    DRAW 426,1466,1
    DRAW 631,1466,1
    DRAW 631,1226,1
    DRAW 583,947,1
    ENDCHAR

    .
    .
    .


    # -------------------
    CHAR 46, '.'
    WIDTH 569
    MOVE 186,0
    DRAW 186,205,1
    DRAW 391,205,1
    DRAW 391,0,1
    ENDCHAR
    # -------------------

    \endverbatim

*/
class CS_FontChar {
public:
    CS_CurveVec cv ; 

    //! only defined if the text format TrueType file is loaded
    double width ; // used for proportional fonts (TrueType for example)
    CS_BezierChnSet bcs ; 
    
    // int numcrvs ; 
    // CS_Curve **pcrvs ; 

    CS_FontChar() ; 
    ~CS_FontChar() ; 

    //! extract x,y coordinate point from the line, as well as the Bezier
    //! curve degree value if there is one  in the Z coord of the pnt. 
    int GetPoint(csString &str, CS_POINT &pnt) ;

    //! reads an individual character from file
    int ReadChar (FILE *fl) ; 

    //! adds last curve to the character definition
    int CompleteBezierCurve(CS_BezierChn &bcrv, CS_BezierCrv &bp) ;

    //! reads a TrueType font character from file
    int ReadTTChar (FILE *fl, int iterations, double toldist) ; 

    //! Convert the bcs curves to lines and arcs
    int BezierToCurves(int iterations, double toldist) ; 

    //! write character to file
    int WriteChar (FILE *fl) ; 

} ;


class CS_Font {
public: 
    //! array of characters for Font. The array is index using the ASCII
    //! decimal value of the character. Thus only the standard language
    //! alphabets that fit in the 0x00-0xFF range are allowed. Unicode
    //! is currently note supported. 
    CS_FontChar *pchars[256] ; 

    //! The maximum deviation that the test points on the approximating
    //! arcs can be from the Bezier curves defining TrueType fonts. The 
    //! smaller the number the more exact the approximation and thus 
    //! increases the number of arcs generated. Default is 0.02
    double toldist ; 

    //! How many points to divide each Bezier curve into, thus we iterate
    //! through this many test points to check for accuracy of the arcs.
    //! The greater the number the more precise and exact an approximation
    //! resulting in a greater number of arcs. Default is 3
    int iterations ; 

    double fonttop ;    // highest y value of any character in font
    double fontbot ;    // lowest y value of any character in font
    double fontheight ; // This is the height of the highest character in the font.
    double maxwidth ;   // width of the widest character in the font. 

    CS_Font() ;     // Constructor
    CS_Font(char *fontname) ; // loads from current directory 'fontname'.fnt

    //! Initialize variables. 
    void InitVars() ; 

    virtual ~CS_Font() ; 

    //! Frees all memory used to store the font
    virtual void Reset() ; 
    
    //! Full path name to the line/arc font file to load
    virtual int LoadFont(char *pathname) ; 

    //! Full path name to the custom text format TrueType font file to load
    virtual int LoadTTFont(char *pathname) ; 

    //! Writes the line/arc font to disk, overwrites existing file
    virtual int WriteFont(char *filename) ; 

} ;
    

#endif 