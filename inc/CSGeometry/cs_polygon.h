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
// cs_polygon.h

#ifndef __cs_polygon_h__
#define __cs_polygon_h__

//! This typedef is so that we can redefine the polygon later on with a 
//! minimum of effort hopefully
typedef CS_Curve    CS_Polygon ; 


/*
//! Polygon data structure which is simply a list of points
class CS_Polygon
{
    CS_PointList pntlst ; 


    AddPoint(CS_POINT &p) ; 
    
    CS_POINT StartPoint() const ; 
    int NextPoint(CS_POINT &p) ; 


    TODO - finish this

    CS_BSPTree::PlaneTestNSplit(..) will have to be reworked once 
    this Polygon structure is implemented. 

} : 
*/

typedef CS_Polygon* CS_PolygonPtr ; 




#endif