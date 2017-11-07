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
// tokens.cpp - class routines for handling the various token types and lists
// strsrch.cpp - string comparison routines for simple search engine

#include "stdio.h"
#include "string.h"
#include "ctype.h"

#ifndef NULL
#define NULL	0
#endif

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS     1

#include "tokens.h"

// The inquotes variable must be set to zero on the first call 
//int isdelim(char c)
//{
//	if (c == ' ' || c == ',' || c == ';' || c == '(' || c == ')' ||
//		c == '\r'|| c == '\t' || c == '\n')
//		return 1;
//	return 0 ;
//}


int isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1 ; 
	return 0 ; 
}


int isdelim(char c)
{
    // if (!isalpha(c) && !isnumber(c) && c != '(' && c != '"')
    if (c == 0x20 || c == '\t' || c == '\n' || c == ',')
        return 1 ; 
    return 0 ; 
}


////////////////////////////////////////////////////////////////////////
// Basic token class
////////////////////////////////////////////////////////////////////////

Token::Token()
{
    tokstr = NULL ; 
    toklen = 0 ; 
    flags = 0 ; 
    prev = NULL ; 
    next = NULL ; 
}

Token::~Token()
{
    if (tokstr != NULL)
    {
        delete[] tokstr ; 
    }
}


// Returns 0 if can't allocate memory or if the token length is 0
int Token::SetTokStr(char *str) 
{
    if (tokstr != NULL)
        delete[] tokstr ; 
    
    toklen = (int)strlen(str) ; 
    if (toklen >= MAXTOKENLEN)
        toklen = MAXTOKENLEN - 1; // maximum token size
    
    if (toklen == 0)
        return 0 ; // nothing to do
    
    tokstr = new char[toklen+1] ; 
    if (tokstr == NULL)
    {	// Not enough memory to save token
        return 0 ; 
    }
    else
    {	// Copy over the token
        strncpy(tokstr, str, toklen) ; 
        tokstr[toklen] = 0 ; 
    }
    
    // Then we have a non-zero length token
    if (tokstr[toklen-1] == '*')
    {	// Then this is a wildcard match type token
        tokstr[toklen-1] = '\0' ; // trash the * character
        toklen -= 1 ; 
        if (toklen == 0)
        {	// Then the '*' character was the only one in the token
            delete[] tokstr ; 
            return 0 ; 
        }
        flags |= WILDCARDTOKEN ; // set the wild card flag
    }
    
    return toklen ; 
}


////////////////////////////////////////////////////////////////////////
// Token list routines
////////////////////////////////////////////////////////////////////////
TokenList::TokenList()
{
    nTokens = 0 ; 
    pStart = NULL ; 
    pEnd = NULL ; 
}

TokenList::~TokenList()
{
    Empty() ; 
}

void TokenList::ResetFoundMatch()
{
    Token *ptok = pStart ; 
    while (ptok)
    {
        ptok->flags &= ~FOUNDMATCH ; 
        ptok = ptok->next ; 
    }
}

void TokenList::Add(Token *pTok)
{
    if (!pTok)
    {	// Nothing to do so return
        return ; 
    }
    
    nTokens += 1 ; // we will definitely add token to the list
    
    if (!pStart)
    {
        pStart = pTok ; 
        pEnd = pTok ; 
        return ; // everything worked ok
    }
    // Else the list already has entries in it
    pEnd->next = pTok ; 
    pTok->prev = pEnd ; 
    pEnd = pTok ; 
}

void TokenList::Empty()
{
    Token *pnxt ; 
    while(pStart)
    {	
        pnxt = pStart->next ; 
        delete pStart ; 
        pStart = pnxt ; 
    }
    pStart = NULL ; 
    pEnd = NULL ; 
    nTokens = 0 ; 
}


int TokenList::ScanTokens(char *str) 
{
    char tmptok[MAXTOKENLEN+2] ; 
    int tlen, whtlen, flags ;
    
    Empty() ; // clear out the current list
    
    tlen = nexttoken(str, tmptok, whtlen, flags) ; 
    
    while (tlen)
    {	// Found another token so add it to the list
        Token *ptok = new Token ; 
        if (!ptok) 
            return -1 ; // memory error
        ptok->SetTokStr(tmptok) ; 
        ptok->flags |= flags ; 
        Add(ptok) ; 
        str += tlen + whtlen ;
        tlen = nexttoken(str, tmptok, whtlen, flags) ; 
    }
    return 0 ; 
}


// Returns the length of the next token, 0=no more tokens. The token
// is copied over to the space pointed to by tok while scanning
// tok must point to a char array of MAXTOKENLEN+1 length
int TokenList::nexttoken(char *str, char *tok, int &whtlen, int &flags) 
{
    whtlen = 0 ; 
    flags = 0 ; 
    while (*str && isdelim(*str)) 
    {
        str++ ; // skip leading white space
        whtlen++ ; 
    }
    
    if (*str == '\0')
        return 0 ; // no more tokens
    
    if (*str == '+')
    {	// Then the token is required since it has a preceding + sign
        flags |= PLUSPREFIX ;
        str++ ; 
        whtlen++ ; 
    }
    
    int tlen = 0 ; 
    // Now we have to scan for the token, if the first character is a 
    // double quote then we return the full string up to the matching
    // double quote. 
    if (*str == '"')
    {	// Grab everything up until the matching quote
        flags |= QUOTEDTOKEN ; 
        str++ ;
        whtlen++ ; // so we skip over the quote character
        while (*str && (*str != '"') && (tlen < MAXTOKENLEN))
        {
            *tok++ = *str++ ; 
            tlen++ ; 
        }
        
        if (*str == '"')
        {   // want to skip past the trailing quote also next time through
            whtlen++ ; 
        }
    }
    else if (*str == '(')
    {   // Grab everything until the matching bracket and return everything 
        // including the the two brackets enclosing the token
        int brackcount = 1 ; 
        flags |= BRACKETTOKEN ; 
        do {
            *tok++ = *str++ ;
            tlen++ ; 
            if (*str == '(')
                brackcount++ ; 
            else if (*str == ')')
                brackcount-- ; 
        } while (*str && (brackcount > 0)) ;
        *tok++ = *str ;
        tlen++ ; 
        *tok = 0 ; 
    }
    else
    {	// We are simply grabbing everything up to the next delimiter
        while(*str && !isdelim(*str) && (tlen < MAXTOKENLEN))
        {
            *tok++ = *str++ ; 
            tlen ++ ; 
        }
    }
    *tok = 0 ; // make sure it's terminated
    return tlen ; 
}
