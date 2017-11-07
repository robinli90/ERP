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
// csstrs.h - definitions for the string extensions

#ifndef __CSSTRS_H__

#define __CSSTRS_H__

// Similar to the VB functionality
void CS_LTrimString(char *str) ;
void CS_RTrimString(char *str) ;
void CS_TrimString(char *str) ;
void CS_StringToUpper(char *ps) ;
char *CS_trmncpy(char *dst, char *src, int len) ;
int CS_ExtractDateMMMDDYY(char *datestr, int *year, int *month, int *day) ;

#endif