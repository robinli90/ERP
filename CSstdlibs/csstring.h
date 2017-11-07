/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/


#ifndef __CSSTRING_H__
#define __CSSTRING_H__

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif

#include <string.h>
#include <stdarg.h>

#include <list>
#include <vector>


using namespace std ;

// Similar to the VB functionality

//! Return location of pkey in pstr ignoring case. 
char *CS_istrstr(char *pstr, char *pkey) ;

void CS_TrimLeftString(char *str) ;
void CS_TrimRightString(char *str) ;
void CS_TrimString(char *str) ;
void CS_StringToUpper(char *ps) ;
char *CS_trmncpy(char *dst, char *src, int len) ;

typedef char* charptr ; 

//! same as strncpy except doesn't pad with null bytes
/*!
    Returns pointer to the NULL byte terminating dst. 

    dst will always be null terminated, thus dst must be one character 
    longer than maxlen. 
 */
char *CS_strmaxcpy(char *dst, const char *src, int maxlen) ;

//! Same as CS_strmaxcpy except returns length (which does not include null terminator)
//! BUT the null terminator is always added. 
int CS_strmaxcat(char *dst, const char *src, int maxlen) ; 

//! Same as CS_strmaxcpy without length checking
char *CS_strcpy(char *dst, const char *src) ; 

//! Same as strtok, except that the ps pointer is modified so that no 
//! static memory parameter is required. 
char *CS_strtok(charptr &ps, const char *delim) ; 

int CS_ExtractDateMMMDDYY(char *datestr, int *year, int *month, int *day) ;


// Append string and return the new end of the string as the pointer
// useful for fast string building. 
inline char *CS_AppendString(char *dst, char *src)
{
    if (src)
    {
        while (*src)
            *dst++ = *src++ ; // copy over the character
    }
    *dst = 0 ; // Null terminate it
    return dst ; // return point where next character should be added
}



class csString {
public:
    char *str ;  // pointer to the string memory - this must be first
    int   len ;  // actual length of the string
    int   idx ;  // current working index into string

    // with *str as the first element it is possible to cast a 
    // csString object to char *. Keep in mind though that you
    // can't string these along as printf parameters since the
    // length of each one is not sizeof(char *). If it's the last
    // parameter to a printf you should be OK though (iff it's 
    // the last and only csString in the parm list)

    csString() ; 
    csString(const int n) ; // allocate space for string and set to NULL
    csString(const char c) ; // makes single character string
    csString(const char c, const int n) ; // repeat character for n times
    // csString(char *ps) ; 
    csString(const char *ps) ; 
    csString(const char *ps, const int len) ; 
    csString(const csString &refstr) ; // copy constructor

    //! Returns the pointer to the string
    /*!
        This will return the pointer to the actual string that is allocated
        within the class. If the member variable str is NULL the the 
        function returns a pointer to a zero length NULL string, but 
        you cannot assign any value to this string since doing so will 
        corrupt static program memory. This null string return is to 
        simplify making the output of printf type %s functions predictable. 
     */
    char *c_str() { if (str) return str ; else return "" ; } ; 

    csString &SetString(const char *s, int len=0) ; // copies the string without 
    // building a intermediate string. If more space is required then it 
    // is allocated, otherwise the copy occurs in the existing memory
    // len=0 copies until NULL, else only copy up to len characters.
    // Stops at NULL if len > length of input string. Returns *this

    //! csString &operator=(csString &) ;  // assignment overridden
    csString &operator=(const csString &) ;  // assignment overridden
    
    csString &operator=(const char *pstr) ;

    csString &Append(const char *s) ; 
    csString &Append(const csString &css) ; 
    csString &Append(const char c) ; 

    csString &operator+=(const csString &a) ; 
    // csString &operator+=(char *s) ; 
    csString &operator+=(const char *s) ; 
    csString &operator+=(const char c) ; 

    ~csString() ;

    // return character reference at the specified index
    char& operator[] (const int idx)  ; 

    int Length() const { return len ; } 
    int size() const { return len ; } 
    
    //! clear out the string from idx onward, defaults deletes the entire string
    void Erase(int idx=0) ;  

    //! clear out the entire string 
    void Reset() { Erase(); } ;  

    //! Another method to be consistent with STL 
    void clear() { Erase() ; } ; 

    //! Remove characters at position index for length characters
    /*! 
        \param index 0 based offset position to start removing from 
        \param length number of characters to remove from the string, default=1
        \return pointer to char @index after removal, will point 
          to the NULL terminating char at the end of the string
          if index is beyond end of result string. If the string 
          is completely deleted then a NULL pointer is returned. 
     */   
    char *Remove(int index=0, int length=1) ;
        
    //! Removes spaces from the string 
    /*!
        \param index the starting offset to begin searching for spaces at
        \param length the maximum number of characters to scan
        \return reference to the resulting string

        The default is to remove all spaces from the string. If and index is 
        specified then it starts from that point. A length of 0 means to 
        scan until the end of the string. 
     */
    csString &RemoveSpaces(int index=0, int length=0) ;


    //! Removes characters from the string 
    /*!
        \param rmchars a set of individual characters to remove from the string
        \param index the starting offset to begin searching for spaces at
        \param length the maximum number of characters to scan
        \return reference to the resulting string

        Each character in the *this string, is tested against each character 
        in the rmchars string, and if a match is found then that character 
        is removed from the *this string and processing continues. 

        If and index is specified then it starts from that point. 
        A length of 0 means to scan until the end of the string. 
     */
    csString &RemoveChars(char *rmchars, int index=0, int length=0) ;


    //! Removes strings from the string 
    /*!
        \param rmstr a set of individual characters to remove from the string
        \param index the starting offset to begin searching for spaces at
        \param length the maximum number of characters to scan
        \return reference to the resulting string

        For each occurence of the pattern within the *this string it 
        removes the matching pattern. The result will have no matching
        rmstr patterns in it over the length specified. If 0 is passed
        in for the length then the pattern will be removed from the entire
        string. 
        
        and if a match is found then that entire matching string pattern 
        is removed from the *this string and processing continues. 

        If and index is specified then it starts from that point. 
        A length of 0 means to scan until the end of the string. 
     */
    csString &RemoveStrings(char *rmstr, int index=0, int length=0) ;

    //! Replace matching strings in the string 
    /*!
        \param rmstr string pattern to match that are replaced
        \param rplstr string to replace the pattern with
        \param index the starting offset to begin searching for spaces at
        \param length the maximum number of characters to scan
        \return reference to the resulting string

        Each character in the *this string, is tested against rmstr
        and if a match is found then that entire matching string pattern 
        is removed from the *this string and processing continues. 

        If and index is specified then it starts from that point. 
        A length of 0 means to scan until the end of the string. 

        If more memory is required realloc is called. If the routine 
        runs out of memory then it simply stops and whatever changes 
        were made are not undone since the search and replace is done 
        in place. 
     */
    csString &ReplaceStrings(char *rmstr, char *rplstr, int index=0, int length=0) ;


    //! Insert char at the specified index, default is at the front
    /*!
        \param c character to insert
        \return pointer to inserted character

        If the index insertion point is beyond the end of the string
        then the string is padded with spaces and the character is
        set as the last char in the resultant string.
        If idx is < 0 then internal errors will result as this 
        is not tested for. idx >= 0 must hold on entry
    */
    char *Insert(char c, int idx=0) ;

    //! Insert string at the specified index, default is at the front
    /*!
        \param ps pointer to string to be inserted
        \return pointer to first inserted character

        If the index insertion point is beyond the end of the string
        then the string is padded with spaces before the new string
        section is inserted.
        If idx is < 0 then internal errors will result as this 
        is not tested for. idx >= 0 must hold on entry
    */
    char *Insert(char *ps, int idx=0) ; 

    //! Insert char at the specified index, default is at the front
    /*!
        \param ps reference to string to be inserted
        \return pointer to first inserted character

        If the index insertion point is beyond the end of the string
        then the string is padded with spaces before the new string
        section is inserted.
        If idx is < 0 then internal errors will result as this 
        is not tested for. idx >= 0 must hold on entry
    */
    char *Insert(csString &str, int idx=0) ; 

    //! Insert char at the specified index, default is at the front
    /*!
        \param ps pointer to string to be inserted
        \return pointer to first inserted character

        If the index insertion point is beyond the end of the string
        then the string is padded with spaces before the new string
        section is inserted.
        If idx is < 0 then internal errors will result as this 
        is not tested for. idx >= 0 must hold on entry
    */
    char *Insert(csString *str, int idx=0) ; 

    //! trim white space off both end of string, if n!=0 then it does
    //! TrimLeft(n) followed by TrimRight(n)
    csString &Trim(int n=0) ;       

    //! trim white space off the right end of the string. If n!=0 then 
    //! trim n characters (whether spaces or not) off the right end
    csString &TrimRight(int n=0) ;  

    //! trim white space off the left end of the string. If n!=0 then 
    //! trim n characters (whether spaces or not) off the left end
    csString &TrimLeft(int n=0) ;   

    //! return the left most n characters, original string is unchanged
    csString Left(const int n) const ;  

    //! return the right most n characters, original string is unchanged
    csString Right(const int n) const ; // take right most n characters

    //! return string from index for len characters. If len=-1 then the 
    //! remainder of string from idx is returned. The original string is unchanged.
    //! A len of zero returns an empty string
    csString Mid(const int idx, const int len=-1) const ; 

    //! convert string to upper case, startidx defines point in string to 
    //! do conversion from. 
    csString &ToUpper(int startidx=0) ; 

    bool operator==(const csString &b) ; 
    bool operator!=(const csString &b) ; 
    bool operator<(const csString &b) ; 
    bool operator>(const csString &b) ; 
    bool operator<=(const csString &b) ; 
    bool operator>=(const csString &b) ; 

    bool operator==(const char *b) ; 
    bool operator!=(const char *b) ; 
    bool operator<(const char *b) ; 
    bool operator>(const char *b) ; 
    bool operator<=(const char *b) ; 
    bool operator>=(const char *b) ; 

    //! Returns true if the string is NULL
    int IsEmpty() ;

    // find first occurence of any char in ps
    // returns NULL if none is found
    // For the index routines -1 is returned if nothing is found
    char *FindOneOf(char *ps, int startidx=0) ; 
    char *FindOneOf(csString &b, int startidx=0) ; 
    int   FindOneOfIDX(char *ps, int startidx=0) ; 
    int   FindOneOfIDX(csString &b, int startidx=0) ; 

    // find last occurence of any char in ps, startidx is the offset from the 
    // start of the string where the search begins from. The default causes 
    // the search to start from the end of the string
    char *FindLastOneOf(char *ps, int startidx=-1) ;
    int   FindLastOneOfIDX(char *ps, int startidx=-1) ;
    char *FindLastOneOf(csString &b, int startidx=-1) ; 
    int   FindLastOneOfIDX(csString &b, int startidx=-1) ; 

    char *Find(char c, int startidx=0) ;    
    int   FindIDX(char c, int startidx=0) ;     
    char *Find(const char *ps, int startidx=0) ; 
    int   FindIDX(const char *ps, int startidx=0) ; 
    char *Find(csString &b, int startidx=0) ;  // find first occurence of b in string
    int   FindIDX(csString &b, int startidx=0) ;  // find first occurence of b in string

    //! Ignore case find character
    char *icFind(char c, int startidx=0) ;    

    //! Ignore case find character index
    int   icFindIDX(char c, int startidx=0) ;     

    //! Ignore case find string
    char *icFind(const char *ps, int startidx=0) ; 

    //! Ignore case find string index
    int   icFindIDX(const char *ps, int startidx=0) ; 

    //! Ignore case find first occurence of b in string and return pointer
    char *icFind(const csString &b, int startidx=0) const ;  

    //! Ignore case find first occurence of b in string and return offset index
    int   icFindIDX(const csString &b, int startidx=0) const ;  

    // If startidx is specified it should be the character position first matching 
    // character desired in the *this string
    char *FindLast(const char c, int startidx=-1) ; // reverse find
    int   FindLastIDX(const char c, int startidx=-1) ; // reverse find
    char *FindLast(const char *ps, int startidx=-1) ; // reverse find
    int   FindLastIDX(const char *ps, int startidx=-1) ; // reverse find
    char *FindLast(csString &b, int startidx=-1) ; // reverse find 
    int   FindLastIDX(csString &b, int startidx=-1) ; // reverse find 

    // Token processing 
    int MoreTokens() ; // after extracting the first token (or initializing
    // the idx parameter, this tests to see if idx < len is valid. It only
    // indicates that there is the possibility of more tokens existing
    // since the remaining characters in the string could all be delimiters

    // Similar to NextToken but instead of stripping out characters until a 
    // delimiter character is reached, it strips out those characters which
    // match the validchars values and stops as soon as it reaches a character
    // which is not in the list. 
    csString NextCharsInSetToken(char *szValidchars, int ofsidx=-1) ;
    csString NextCharsInSetToken(csString csValid, int ofsidx=-1) ;
    
    // The following actually call NextCharsInSetToken() allowing for all 
    // integer and floating point characters respectively. No consideration
    // is given for proper numeric formatting. All characters in the set 
    // are stripped out. Thus 1.2.3.4X would return the token 1.2.3.4 for 
    // NextFloatToken()
    csString NextIntToken(int ofsidx=-1) ; // Regex: [-+0123456789]
    csString NextFloatToken(int ofsidx=-1) ; // Regex: [-+.e0123456789]

    //! Extract the next token from the string
    /*!
        \param szDelims string of delimiters defining token boundaries
        \param ofsidx controls character position in the string where token 
        searching begins
        \return the token found in the string. 

         Extracts a token starting at the
         offset specified, if ofsidx is not -1 then the internal idx pointer is 
         initialized to maintain where we are in the string. If ofsidx==-1 then
         the search starts from the current value of ofsidx. The token is 
         delimited by finding any character. A new csString object is created
         to hold the token and this is returned on the stack
    
         Token search logic is different if ofsidx is specified. 
         If ofsidx is specified, then all delim characters are skipped until a 
         non-delim character is found. Then all characters up to the first delim 
         char (or NULL) are returned as the token. 
         If ofsidx is not specified, then it is assumed we are continuing from 
         a previous call, and in this case characters are copied into the token
         return string until a delim character is found. Thus it is possible
         to get a null token with two delimiter characters one after the other
         For example scanning . scanstr = ',,1,2,3,,5'
         using   
              s.NextToken(",", 0) 
              s.NextToken(",") 
              s.NextToken(",") 
              s.NextToken(",") 
              s.NextToken(",") 
         Would return tokens:
           '1' 
           '2'
           '3'
           ''   (NULL string)
           '5'
    
         using   
              s.idx = 0 ;          
              s.NextToken(",") 
              s.NextToken(",") 
              s.NextToken(",") 
              s.NextToken(",") 
              s.NextToken(",") 
         Would return tokens:
           ''   (NULL string)  
           ''   (NULL string)
           '1' 
           '2'
           '3'
           ''   (NULL string)
           '5'
    
         using   
              s.NextToken(",", 0) 
              s.NextToken(",", s.idx) 
              s.NextToken(",", s.idx) 
              s.NextToken(",", s.idx) 
              s.NextToken(",", s.idx) 
         Would return tokens:
           '1' 
           '2'
           '3'
           '5'
      
         When searching for tokens, the first character not in the string ps 
         (or NULL) is the first character of the next token. Then all characters 
         until one of the characters in ps is found (or NULL) are copied to the 
         token result. 
     */
    csString NextToken(char *szDelims, int ofsidx = -1) ;
    csString NextToken(csString csDelims, int ofsidx = -1) ; 


    //! Extract the next token, that can optional be enclosed in quotes
    /*! 
        \param pdelims string of possible delimiter characters
        \param ofsidx starting offset index to begin looking for next token
        \param qc character used as the quote, thus could substitute single quote
        as the quote character instead of the default double quotes. 
        \return returns the resultant token. 

        Behaves the same as nextToken with the exception that a quote is also 
        used as a delimiter character. Thus when scanning for the terminating delimiter
        if the scan is inside a quoted section (found a single quote previously and 
        hasn't exited the quoted section yet by finding a second quote) then 
        any delimiters that are found are ignored until after the terminating
        quote is reached. While searching for a 
        matching quote character, if a \[qc] sequence is detected, then the backslash
        and the qc quote character are both copied to the result string and the 
        search continues. 

        Note: do not specify the " character as one of the delimiter characters
        as the results will be unpredictable.
     */
    csString NextQuotedToken(char *pdelims, int ofsidx = -1, char qc='\"') ; // This works 

    int IsAlpha(int startidx=0) ; //!< all characters in string are in range [A-Za-z]
    int IsNumeric(int startidx=0) ; //!< all chars in string one of [+-.e0123456789]
    int IsDigit(int startidx=0) ;  //!< all chars in string are 0123456789

    // Converts the characters in the string from ASCII hex to an integer
    // The default is to convert the entire string, but portions of the 
    // string can also be extracted. Invalid characters are treated as 
    // hex zero values. 
    unsigned int HexToInt(int startidx=0, int length=-1) ;

    //! Convert the input binary string into a HEX encoded string. Thus 
    //! the resultant string will be twice as long as the input string
    csString &StrToHex(unsigned char *binstr, int len) ; 

    //! Convert a hex encoded string into a binary string of bytes
    csString &HexToStr(unsigned char *binstr, int len) ; 

    //! Generate string using printf formatting
    /*!
        \param formatstr the printf format
        \param ... all parameters defined within the printf format
        \return reference to the string (*this)

        Note: internally a block of memory is allocated that is printed to
        where the size of the block is equal to:

            strlen(formatstr) + (256 * number_of_parms_found_in_formatstr)

        Thus we waste a bunch of memory on the heap, but since there is no
        way to know how big %s parameters will be without scanning the stack
        and practically doing the complete printf processing. If you want
        to conserve memory (or need more) you can pass the amount of memory
        to allocate using the FormatSz(..) member function.

     */
    csString &Format(const char *formatstr, ...) ; 

    //! Generate string using printf formatting
    /*!
        \param size amount of memory to allocate for the resultant formatted string
        \param formatstr the printf format
        \param ... all parameters defined within the printf format
        \return reference to the string (*this)

        Note: internally allocates a block of memory size bytes long to 
        accept the resultant printf string

     */
    csString &FormatSz(int size, const char *formatstr, ...) ;

    //! Converts a unicode string that is coded as standard ANSII into a byte string. 
    /*!
        \param unicodestr pointer to the unicode string to be converted. 
        \return reference to the string

        This works by skipping over the null bytes in the unicode string until a 
        double null byte is found signaling the end of the unicode string. 
     */
    csString &UnicodeToBytes(const char *unicodestr) ;

    //! More Microsoft crap
    /*!
        This isn't really unicode but 2 byte wide characters. 
        If bytelen != 0 then it will skip the string length 
        test and simply allocate an array at twice the length of
        the byte len plus 2 bytes for the null at the end. 
     */
    csString &BytesToUnicode(const char *bytestr, int bytelen=0) ;

} ;


//! Creates a string enclosed in double quotes
/*!
    \param str the string to be processed and converted to a quoted delimited string
    \return the quote delimited string

    str is scanned for double quote chraceters and if any are found then an backslash
    is inserted in front of the double quote. Also, and backslash characters found
    will have an additional backslash inserted in front of them so that the character
    following the backslash is not treated as a special character. 

    For example:
            
    Input:    He said, "What was that?".\n
    Output:   "He said, \"What was that?\".\\n"
 */
csString MakeQuotedString(const char *str) ; 

//! Extract a string enclosed in double quotes
/*!
    \param str the quoted string to be processed. 
    \return the result string with embedded quotes and double backslashes
    mapped back to what they were when passed in by MakeQuotedString(..)

    For example:
            
    Input:    "He said, \"What was that?\".\\n"
    Output:   He said, "What was that?".\n

 */
csString ExtractQuotedString(const char *str) ; 


//! See if the test string matches the wildcard string
//! ** is illegal in the wildcard string (there is no way 
//! to test for the * character currently.
int CS_StringsMatch(char *wild, char *test) ;

//! See if the test string starts with the startswith string
//! After the end of the startswith string is reached if the 
//! characters all match then it returns true, else false is returned. 
int CS_StartsWith(char *test, char *startswith) ;
//! Same as CS_StartsWith but ignore case during compar
int CS_icStartsWith(char *test, char *startswith) ;


// String concatenation
csString operator+(const csString &a, const csString &b) ; 
csString operator+(const char *a, const csString &b) ; 
csString operator+(const csString &a, const char *b) ; 
csString operator+(const char a, const csString &b) ; 
csString operator+(const csString &a, const char b) ; 

// csString operator+(const char *a, csString &b) ; 

bool operator==(const char *a, const csString &b) ;
bool operator!=(const char *a, const csString &b) ; 
bool operator<(const char *a, const csString &b) ; 
bool operator>(const char *a, const csString &b) ;
bool operator<=(const char *a, const csString &b) ;
bool operator>=(const char *a, const csString &b) ;

// Why are these defined?
bool operator==(const csString &a, const csString &b) ;
bool operator!=(const csString &a, const csString &b) ; 
bool operator<(const csString &a, const csString &b) ; 
bool operator>(const csString &a, const csString &b) ;
bool operator<=(const csString &a, const csString &b) ;
bool operator>=(const csString &a, const csString &b) ;



// On the fly string conversion utilities
csString csIntToStr(int i) ;
csString csDoubleToStr(double d, char *format) ;
csString csFloatToStr(float d, char *format) ;


csString AddFile2Path(const csString &path, const csString &filename) ;
csString AddFile2Path(const char *path,     const csString &filename) ;
csString AddFile2Path(const csString &path, const char *filename) ;
csString AddFile2Path(const char *path,     const char *filename) ;

// returns true if string is changed
int AddTrailingSlashToPath(csString &path) ;
int AddTrailingSlashToPath(char *path) ;


int SplitPathAndFile(csString &fullname, csString &path, csString &file) ; 

/*!
    \param fullname input file name with extension
    \param returned file name without extension (without '.' also) 
    \param returned extension string (without '.') 

    Splits the file by searching for the first '.' from the end.
    If no period is found then file is set to fullname and ext is
    set to null. The extension returned is everything after the last
    period in the file name. The file returned does not include the
    last period character.
 */
int SplitFileAndExtension(csString &fullname, csString &file, csString &ext);

csString GetPathName(csString &fullname) ; 
csString GetPathName(const char *fullname) ; 

//! Return just the file name from the full pathname
csString GetFileName(csString &fullname) ; 
csString GetFileName(const char *fullname) ; 

bool CS_FileExists(const char *filename) ; 

// Returns number of characters changed
int SubCharacters(char *str, char from, char to) ;

/** 
    Expects as input a string of the form
          name = "value"

    the name only portion will be returned in name and the value portion
    without the quotes will be returned in the value portion. The = sign
    is used as the delimiter to separate the name from the value so, the 
    name string cannot have embedded '=' characters. Whitespace is stripped
    off the ends of the name and value strings as well. 

    Returns 0 on success
    The following bits are ored together otherwise:
        0x01=noname, 0x02=novalue, 0x04=noequal

  */
int GetNameAndValue(csString &input, csString &name, csString &value) ; 

// This is a capitalized hex encoded string
extern char hextable[256][2] ; 
// Lower case hex encoded string
extern char hextableLC[256][2] ; 
    

//! Convert binary array to hex encoded string
/*!
    \param binstr pointer to the input binary array
    \param binlen length of the input array
    \param hexstr pointer to pre-allocated memory to accept hex encoding

    The hexstr array must be allocated to accept (binlen * 2 + 1) bytes.
    No error checking is done, the routine simply overwrites memory as 
    required until the desired number of bytes are output. 
 */
void CS_BinToHex(unsigned char *binstr, int binlen, char *hexstr) ;

//! Convert hex encoded string to binary
/*!
    \param hexstr pointer to the input hex encoded string
    \param hexlen length of the input array 
    \param binstr pointer to pre-allocated memory to accept hex encoding
    \return the length of the returned binary arrary

    The hexstr array must be in character pairs, two characters for each
    byte in the output binary array. Thus if the hexlen is 4, then 2 bytes
    are output to binstr. If hexlen is an odd number then the last character
    is ignored and will have no effect. 

    The binstr is not null terminated. 

 */
int CS_HexToBin(unsigned char *hexstr, int hexlen, unsigned char *binstr) ;


//! Convert hex encoded string to binary
/*!
    \param hexstr pointer to the null terminated input hex encoded string
    \param binstr pointer to pre-allocated memory to accept hex encoding
    \return the length of the returned binary arrary

    The hexstr array must be in character pairs, two characters for each
    byte in the output binary array. Thus if the hexlen is 4, then 2 bytes
    are output to binstr. If hexlen is an odd number then the last character
    is ignored and will have no effect. 

    The binstr is not null terminated. binstr must be pre-allocated to 
    sufficient length to accept the full binary array. 

    This version stops when it reaches a null byte on the input pair. 

 */
int CS_HexToBin(unsigned char *hexstr, unsigned char *binstr) ;

//! Returns true if c={[A-Z]|[a-z]|[0-9]} else returns false
bool CS_IsHexChar(const char c) ;

//! If the string is null returns 0
int CS_StrToInt(const char *str); 
long CS_StrToLong(const char *str); 
double CS_StrToDbl(const char *str); 
unsigned int CS_StrToUInt(const char *str) ;
unsigned long CS_StrToULong(const char *str); 


//! skip over floating point value 
/*!
    \param ps pointer to number string to skip over. 
    \return pointer to character after the last character in the valid float string

    This does not handle exponential floating point representations. It simply skips
    over patterns that match the following. [+/-]N[.[N]]  where N represents any 
    string of digits. 

    For example if ps points to "-123.556inches" then the pointer returned
    would be at the 'i' character position in the string. If "123..456" is
    passed in then the pointer returned would be to the second decimal point
    since there can only be a single decimal point in a number. 
 */
char *CS_SkipFloat(char *ps) ; 

typedef vector<csString> csStringList ; 
typedef vector<csString>::iterator csStringListItr ; 

typedef vector<csString> csStringVec ; 
typedef vector<csString>::iterator csStringVecItr ; 

typedef vector<char *> CS_CharPtrVec ; 
typedef vector<char *>::iterator CS_CharPtrVecItr ; 

class csStringStack
{
public:
    csStringList strstack ; // this is the internal stack set

    csStringStack() {} ; 
    ~csStringStack() {} ; 

    const char *GetLast() 
    {
        if (strstack.size() > 0)
        {
            csStringListItr i = strstack.end() ; 
            i-- ; 
            return i->c_str() ; 
        }
        return "" ; 
    }

    void Push(char *s) { strstack.push_back(csString(s)) ; } 
    void Pop()
    {
        if (strstack.size() > 0)
            strstack.pop_back() ; 
    }

} ; 


// hexstr must be 2 bytes long
void CS_CharToHex(unsigned char *pc, char *hexstr) ;


//! Converts the integer bytes to a hex encoded string, hexstr must be 4 bytes long
/*!
    \param pint pointer to the integer to be hex encoded. 
    \param hexstr the 4 byte output hex string

    The 0x0000ffff part of the integer is converted to a hex string. This 
    is intended to be used when you know that the integer will have a short
    int value stored in it. 

    Note: the hexstr is NOT null terminated. You need to add the null terminator
    if required.
 */
void CS_IntToHex2B(int *pint, char *hexstr) ; 


//! Converts the integer bytes to a hex encoded string, hexstr must be 8 bytes long
/*!
    \param pint pointer to the integer to be hex encoded. 
    \param hexstr the 8 byte output hex string

    Note: the hexstr is NOT null terminated. You need to add the null terminator
    if required.
 */
void CS_IntToHex(int *pint, char *hexstr) ;

// The hexstr can be from 1 to 8 bytes in length on 32 bit machines. 
int CS_HexToInt(unsigned char *hexstr, int hexlen, unsigned int &retvalue) ; 

// Returns the number of bytes in the UTF8 pattern. 
int CS_UTF8StartChar(unsigned char c) ; 

char *CS_URLenccpy(char *dst, const char *src, int maxlen) ;

int CS_IsDots(char *filename) ; 


#endif


