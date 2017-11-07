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
// tokens.h

#ifndef __TOKENS_H__

#define __TOKENS_H__

#define MAXTOKENLEN	10000


#define WILDCARDTOKEN	0x0001	// token had a * at the end of it
#define QUOTEDTOKEN	0x0002	// token was enclosed in quotes
#define PLUSPREFIX	0x0004	// token had a + in front of it
#define BRACKETTOKEN    0x0008  // token had leading bracket
#define FOUNDMATCH      0x0010  // used when checking matches in token list


// Maintains a list of search and data tokens. The search tokens
// are all compared against the data tokens to find matches.


class Token {
public:
	Token *prev, *next ;
	char *tokstr ;   // the token string which can contain spaces etc...
	int toklen ;     // strlen for the actual token
	int flags ;

	Token() ;
	virtual ~Token() ;
	virtual int SetTokStr(char *str) ;
} ;


class TokenList {
public:
	int nTokens ;   // number of tokens in the list
	Token *pStart ;	// pointer to the first token in list
	Token *pEnd ;

	TokenList() ;
	~TokenList() ;
	
	void ResetFoundMatch() ;
	void Add(Token *ptok) ; // add token to the list, returns index
	void Empty() ; // clear out the list
	int ScanTokens(char *str) ; 
	int nexttoken(char *str, char *tok, int &whtlen, int &quotes) ;
} ;


#endif