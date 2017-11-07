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
// fonts.cpp - class routines for the curve based fonts

#pragma warning ( disable : 4786 )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <csstdlibs/cslib.h>
#include "cs_geomdefs.h"
#include "cs_fonts.h"



#ifdef CSDEBUG
#define CS_DEBUG(a)    
#else
#define CS_DEBUG(a)
#endif



CS_FontChar::CS_FontChar()
{
    width = 0.0 ; 
}

CS_FontChar::~CS_FontChar()
{
    // De-allocate the curves in the list
    CS_CurveVecItr icv ; 
    for (icv = cv.begin(); icv != cv.end(); icv++)
    {
        CS_CurvePtr pc = *icv ; 
        delete *icv ;
    }
}

//////////////////////////////////////////////////////////////////////////
// Reads an individual character from file
// Upon entry it is assumed that the CHAR 'a' line has already been read
// and now it is a matter of loading up the curves themselves. Curves are
// read into memory until the ENDCHAR line is read at which point control
// returns. If memory is allocated successfully and the end of file is 
// not reached then 0 is returned otherwise an error code is returned

int CS_FontChar::ReadChar(FILE *fl) 
{
    char inbuf[1024] ; 
    int morecurves = 1 ;
    fpos_t pos ; 

    cv.clear() ; 

    CS_CurvePtr pcrv ; // temporary work curve

    CS_DEBUG(fprintf(fpDebugOut, "Reading character from font file\n")) ; 
    
    while (1) // we break out of the loop when we are done
    {   
        pcrv = new CS_Curve ; // allocate space for a new curve
        if (!pcrv)
            return -1 ; // memory allocation error

        if (!pcrv->ReadFromFile(fl))
            break ; // didn't read any curves
        cv.push_back(pcrv) ; 

        // Now read the next line to see if it's the ENDCHAR indicator
        if (fgetpos(fl, &pos) != 0) // save current file position
        {   // Error getting file position
            return -2 ; // file error
        }

        if (!fgets(inbuf, 1024, fl))
        {   // break since end of file reached
            break ; 
        }
        else
        {
            if (strncmp(inbuf, "ENDCHAR", 7) == 0)
            {   // Then we are done and character is valid so exit
                break ; 
            }
            else
            {   // Back up so that we can let the CS_Curve routine read in 
                // the next curve
                long offset ; 
                offset = (long)strlen(inbuf) ; 
                if (fsetpos(fl, &pos) != 0) // restore file position
                {
                    return -2 ; // file error
                }
            }
        }
    }

    if (cv.size() > 0)
    {
        CS_DEBUG
        (
            fprintf(fpDebugOut, "%d curves read defining letter\n", numcrvs) ;
            for (int i=0; i < numcrvs; i++)
            {
                fprintf(fpDebugOut, "Curve %d ==> ", i) ; 
                pcrvs[i]->PrintCurve(0, fpDebugOut) ; 
            }
        )
        return 0 ; // success
    }
    return 1 ; // error loading character data
}

int CS_FontChar::CompleteBezierCurve(CS_BezierChn &bcrv, CS_BezierCrv &bp)
{
    if (bcrv.size() > 0)
    {
        // Must add the start point to the end of the set of curve points
        bp.push_back(bcrv[0][0]) ; 
    }
    else if (bp.size() > 0)
    {
        bp.push_back(bp[0]) ; 
    }
    else
    {
        return 0 ; // nothing defined for the character
    }

    // add the set of bezier points to the current curve being built
    bcrv.push_back(bp) ; 
    
    // Finally add the curve to the font definition. 
    bcs.push_back(bcrv) ; 
    bcrv.clear() ; 

    // Set all the Z components to 0
    for (unsigned int i=0; i < bcs.size() ; i++)
    {
        for (unsigned int j=0; j < bcs[i].size() ; j++)
        {   // the bcs[] are CS_BezierChn's
            for (unsigned int k=0; k < bcs[i][j].size(); k++)
            {   // the bcs[][] are CS_BezierCrv
                bcs[i][j][k].z = 0.0 ; // bcs[][][] is the actual point
            }
        }
    }



    return 0 ; 
}

// Z Coordinate contains the degree of the point
int CS_FontChar::GetPoint(csString &str, CS_POINT &pnt)
{
     csString tok ; 
     
     tok = str.NextToken(" ,", str.idx) ; 
     if (tok.len == 0)
         return -1 ; 
     pnt.x = atof(tok.str) ; 
     
     tok = str.NextToken(" ,", str.idx) ; 
     if (tok.len == 0)
         return -1 ; 
     pnt.y = atof(tok.str) ;

     tok = str.NextToken(" ,", str.idx) ;
     if (tok.len == 0)
         pnt.z = 0 ;
     else
         pnt.z = atoi(tok.str) ;

     return 0 ;
}

int CS_FontChar::ReadTTChar(FILE *fl, int iterations, double toldist) 
{
    char inbuf[1024] ; 
    int morecurves = 1 ;
   
    width = 0 ; 

    cv.clear() ; 

    CS_DEBUG(fprintf(fpDebugOut, "Reading character from font file\n")) ; 

    CS_POINT pnt ; 
    CS_BezierCrv bp ; 
    CS_BezierChn  bcrv ; 
    
    // break out of the loop on EOF or ENDCHAR line
    while (fgets(inbuf, 1024, fl)) 
    {   
        csString lnstr(inbuf) ; 
        lnstr.Trim() ; 
        csString tok = lnstr.NextToken(" ", 0) ; 

        if (tok == "MOVE")
        {   
            if (bcrv.size() > 0)
            {   // Add the current point set to the Bezier set
                CompleteBezierCurve(bcrv, bp) ; 
            }

            // Make sure the point set is also reset
            bp.clear() ; 
            
            if (GetPoint(lnstr, pnt))
                return -2 ; // invalid point data
            bp.push_back(pnt) ; 
        }
        else if (tok == "WIDTH")
        {
            tok = lnstr.NextToken(" ,", lnstr.idx) ; 
            width = atof(tok.str) ; 
        }
        else if (tok == "DRAW")
        {   // Next point along the Bezier curve chain
            if (GetPoint(lnstr, pnt))
                return -2 ; // invalid point data

            if (tcomp_EQ(pnt.z, 1.0))
            {   // Then end the current curve and create a new one
                bp.push_back(pnt) ; 
                if (bp.size() > 1)
                    bcrv.push_back(bp) ; 
                else
                    return -4 ; // invalid curve ; 
                bp.clear() ;
                bp.push_back(pnt) ; 
            }
            else if (tcomp_EQ(pnt.z, 2.0))
            {   // control point off the actual curve
                // If there are two 2nd order points back to back then for the
                // TrueType font definition, there is an implied 1st order point
                // (on the curve point) midway between the two off curve (2nd
                // order) points. So in the case of 2 2nd order points, generate
                // the implied point and create the additional point set that
                // gets added to the final output curve. 
                int n = (int)bp.size() ; 
                if (n > 0)
                {
                    if (tcomp_EQ(bp[n-1].z, 2.0))
                    {   // Then must create the implied on curve point
                        CS_POINT ion = (pnt + bp[n-1]) / 2.0 ; 
                        ion.z = 1.0 ; 
                        bp.push_back(ion) ;
                        bcrv.push_back(bp) ; 
                        bp.clear() ; 
                        bp.push_back(ion) ;
                        bp.push_back(pnt) ; 
                    }
                    else
                    {   // This is the first 2nd order point so just add it 
                        // to the end of the current point list. 
                        bp.push_back(pnt) ; 
                    }
                }
                else
                {   // This is an error condition since must always have on curve
                    // points before an off curve point occurs
                    return -5 ; 
                }
            }
            else
            {   
                return -3 ; // curve degree definition error
            }
        }
        else if (tok == "ENDCHAR")
        {
            CompleteBezierCurve(bcrv, bp) ; 
            break ; 
        }
    }

    // The Bezier curve data is now defined. Create the equivalent line/arc
    // curves from the Bezier curve data. 
    BezierToCurves(iterations, toldist) ; 

    if (cv.size() > 0)
    {
        CS_DEBUG
        (
            fprintf(fpDebugOut, "%d curves read defining letter\n", numcrvs) ;
            for (int i=0; i < numcrvs; i++)
            {
                fprintf(fpDebugOut, "Curve %d ==> ", i) ; 
                pcrvs[i]->PrintCurve(0, fpDebugOut) ; 
            }
        )
        return 0 ; // success
    }
    return 1 ; // error loading character data
}

int CS_FontChar::BezierToCurves(int iterations, double toldist)
{
    int nSets = (int)bcs.size() ; 
    
    // TrueType fonts are built from a series of closed curves
    // Each curve in the final curve vector will be a fully closed curve. 
    CS_CurvePtr pclosedcrv = 0 ; 

    for (int i=0; i < nSets ; i++)
    {
        // Walk through each point set in the curve set
        int setSize = (int)bcs[i].size() ; 
        for (int j=0; j < setSize ; j++)
        {
            CS_CurvePtr pcrv = new CS_Curve ; 
            if (!CS_BezierToCurve(*pcrv, bcs[i][j], 0.0, 1.0, iterations, toldist))
            {
                if (!pclosedcrv)
                {
                    pclosedcrv = new CS_Curve ;
                    pclosedcrv->AddCurve(pcrv) ; 
                }
                else if (pclosedcrv->EndPoint() == pcrv->StartPoint())
                {
                    pclosedcrv->AddCurve(pcrv) ; 
                }
                else
                {
                    cv.push_back(pclosedcrv) ; 
                    pclosedcrv = new CS_Curve ;
                    pclosedcrv->AddCurve(pcrv) ; 
                }
            }
            else
                delete pcrv ; 
            pcrv = 0 ; 
        }
    }

    if (pclosedcrv)
        cv.push_back(pclosedcrv) ; 

    return 0 ; 
}


int CS_FontChar::WriteChar(FILE *fl) 
{
    CS_CurveVecItr icv ; 
    for (icv = cv.begin(); icv != cv.end(); icv++)
    {
        fprintf(fl, "CURVE\n") ; 
        (*icv)->WriteCurveToFile(fl) ;     
        fprintf(fl, "END\n") ; 
    }
    return 0 ; // error loading character data
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Actual Font Member Functions
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

CS_Font::CS_Font()
{
    InitVars() ; 
}

CS_Font::CS_Font(char *fontname)
{
    InitVars() ; 
    LoadFont(fontname) ; 
}

void CS_Font::InitVars()
{
    for (int i=0; i<256;i++)
    {   // Make sure all pointers are NULL
        pchars[i] = 0 ; 
    }

    toldist = 0.02 ; 
    iterations = 3 ; 
}

CS_Font::~CS_Font()
{
    Reset() ; 
}

void CS_Font::Reset()
{
    for (int i=0; i<256; i++)
    {
        if (pchars[i])
            delete pchars[i] ; 
        pchars[i] = 0 ; 
    }
}

int CS_Font::LoadFont(char *pathname)
{
    FILE *fl ;
    unsigned char inbuf[1024] ; 
    int i, charidx ; 

    CS_DEBUG(fprintf(fpDebugOut, "Opening font file '%s'\n", pathname)) ; 

    fl = fopen(pathname, "r") ; // open font file for reading
    if (!fl)
        return -2 ; // file error 
    
    // Read font data
    while (fgets((char *)inbuf, 1024, fl) != NULL)
    {
        
        CS_DEBUG(fprintf(fpDebugOut, "Read line: %s", inbuf)) ; 

        if (strncmp((char *)inbuf, "CHAR", 4) == 0)
        {   // Then we found a character definition string
            i = 5 ; // skip over the CHAR string
            while(isspace(inbuf[i])) i++ ; 
            
            if (inbuf[i] == 0x27) // test if it's a ' char
            {   // It's an actual character
                charidx = inbuf[i+1] ; 
            }
            else
            {   // It's a Hex value
                sscanf((char *)&inbuf[i], "%x", &charidx) ;
            }

            if (charidx < 0 || charidx > 255)
                continue ; // cannot process this character

            CS_DEBUG(fprintf(fpDebugOut, "About to load character '%c' %02x\n", 
                        charidx, (unsigned)charidx)) ; 

            CS_FontChar *pnewchar = new CS_FontChar ;
            if (!pnewchar->ReadChar(fl))
            {   // Read character info OK
                pchars[charidx] = pnewchar ; 
            }
            else
            {   // Else there was an error loading the character
                delete pnewchar ; 
            }
        }
    }

    fclose(fl) ; 
    return 0 ; 
}

int CS_Font::LoadTTFont(char *pathname)
{
    FILE *fl ;
    unsigned char inbuf[1024] ; 
    int charidx ; 

    CS_DEBUG(fprintf(fpDebugOut, "Opening font file '%s'\n", pathname)) ; 

    fl = fopen(pathname, "r") ; // open font file for reading
    if (!fl)
        return -2 ; // file error 
    
    // Read font data
    fonttop = -99999.0 ; 
    fontbot = 99999.0 ; 
    fontheight = -99999.9 ; 
    maxwidth = 0.0 ; 

    while (fgets((char *)inbuf, 1024, fl) != NULL)
    {
        
        CS_DEBUG(fprintf(fpDebugOut, "Read line: %s", inbuf)) ; 

        if (strncmp((char *)inbuf, "CHAR", 4) == 0)
        {   // Then we found a character definition string
            csString ln((char *)(inbuf + 5)) ; 
            ln.Trim() ; 
            csString tok ; 
            tok = ln.NextToken(" ,") ; 
            
            if (tok[0] == 0x27) // test if it's a ' char (single quote)
            {   // It's an actual character
                charidx = tok[1] ;
            }
            else if (tok.Left(2) == "0x")
            {   // It's a Hex value
                sscanf(tok.str + 2, "%x", &charidx) ;
            }
            else if (tok.IsDigit())
            {   // It's a decimal ASCII value
                charidx = atoi(tok.str) ; 
            }

            if (charidx < 0 || charidx > 255)
                continue ; // cannot process this character

            CS_DEBUG(fprintf(fpDebugOut, "About to load character '%c' %02x\n", 
                        charidx, (unsigned)charidx)) ; 

            CS_FontChar *pnewchar = new CS_FontChar ;
            int retcode = pnewchar->ReadTTChar(fl, iterations, toldist) ;
            if (retcode == 0)
            {   // Read character info OK
                CS_RECT rect(0,0,0,0) ; 
                if (pnewchar->cv.size() > 0)
                {
                    pnewchar->cv[0]->SetBoundingRect() ; 
                    rect = pnewchar->cv[0]->bndrect ; 
                }

                for (unsigned int i=1 ; i < pnewchar->cv.size(); i++)
                {
                    pnewchar->cv[i]->SetBoundingRect() ; 
                    rect.Union(pnewchar->cv[i]->bndrect) ; 
                }

                if (rect.Height() > fontheight)
                    fontheight = rect.Height() ; 
                if (rect.Width() > maxwidth) 
                    maxwidth = rect.Width() ; 

                if (fonttop < rect.t)
                    fonttop = rect.t ; 
                if (fontbot > rect.b)
                    fontbot = rect.b ; 

                pchars[charidx] = pnewchar ; 
            }
            else if (pnewchar->width > 0.0)
            {   // Then read a space or similar blank character
                if (pnewchar->width > maxwidth)
                    maxwidth = pnewchar->width ; 
                pchars[charidx] = pnewchar ; 
            }
            else
            {   // Else there was an error loading the character
                delete pnewchar ; 
            }
        }
    }

    fclose(fl) ; 
    return 0 ; 
}


// Returns 0 on success or error code if failure
int CS_Font::WriteFont(char *filename)
{
    FILE *fl ; 

    if ((fl = fopen(filename, "w")) == NULL)
        return -2 ; 

    for (int i=0; i < 256; i++)
    {
        if (pchars[i] != NULL)
        {   // Then write this character to the file
            if (i > 0x20 && i < 0x7f)
            {   // Then this is a printable ASCII character
                fprintf(fl, "CHAR '%c'\n", (char)i) ; 
            }
            else
            {
                fprintf(fl, "CHAR %02x", i) ; 
            }
            if (pchars[i]->WriteChar(fl))
                return -2 ; // error writing character
        }
    }
    return 0 ; 
}

