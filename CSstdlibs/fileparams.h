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

// fileparams.h - persistent file parameters class, used to quickly load and store
//      file parameters, such as windows parameters in a .INI file for example.
// TO DO Support nesting by including parameters within parameters
#ifndef __fileparams_h__
#define __fileparams_h__

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif

#include <stdio.h>
#include "avltree.h"

// Maintains a list of parameters and saves them in a text file using the 
// XML Format. Initially we have only one level of parameters defined
// but eventually we want to extend this to allow a full tree structure
// The tree structure could be implemented in place now using . separators
// for the fields. 

#define FPARMS_MODIFIED         0x00000001
#define FPARMS_NOSAVEONEXIT     0x00000002

#define FPARMS_MAXLINELENGTH    8192


// enum ParmType {type_double, type_string, type_integer} ;
#define FP_PARMTYPE_DOUBLE     1
#define FP_PARMTYPE_STRING     2
#define FP_PARMTYPE_INTEGER    3

struct FileParmNode
{
    unsigned char type ; // parameter type
    csString name ; // parameter name

    // Parameter variables follow
    union
    {
        double d ;
        int    i ;
    } ;
    csString str ; // because of the destructor we have to keep this
                   // outside the union.

    // These operators are used by the Tree to access the parameters
    // so we are testing the name and type for equality here
    int operator<(FileParmNode &fpn)
    {
        if (type < fpn.type)
            return 1 ; 
        else if (type == fpn.type)
        {   // Then test the string portion
            if (name < fpn.name)
                return 1 ; 
        }
        return 0 ; 
    } ;
    
    int operator==(FileParmNode &fpn)
    {
        if ((type == fpn.type) && (name == fpn.name))
            return 1 ; 
        return 0 ; 
    };
} ;

/*! CFileParameters:  Usage 
 Instantiate the class
      CFileParameters cfp ; 
   
  Load the parameters
     
    cfp.LoadParms(char *fullpathnameofparmfile) ;
  
  For initial usage define parameters

     cfp.TestInitParm("ANALYSIS.BASENAME", "fundscan") ; 
     cfp.TestInitParm("ANALYSIS.EXTNAME", "data") ; 

  and so on for as many parameters that there are

  Then call GetParm() to access the information, there are overrides for 3
  variables typs, int, double, and char*, for example:


    char fundscanname[128]
    cfp.GetParm("ANALYSIS.BASENAME", fundscanname) ; 


  To set a parameter used 

     cfp.SetParm("ANALYSIS.BASENAME", "newfundscan") ; 


  Finally to save the data back use:

     cfp.SaveParms() ; 

  Note: the file name must be set through a LoadParms() call first though


 */

class  CFileParameters {
private:

    // name of the parameter set. The parameter set is stored with 
    // this as the file name followed by ".INI"
    csString setname ;  
    
    // directory where parameters are stored
    csString pathname ; 

    // status and configuration flags 
    int bFlags ;

    // To make the parameter nodes generic we could create a Get/Set
    // where all values are accessed with strings and then converted
    // elsewhere.
    CAVLNode *itrnode ; 
    CAVLTree<FileParmNode> parmtree ;

    // Member functions
public:

    CFileParameters(int flags=0) ;
    CFileParameters(csString parmsetname, int flags=0) ;
    ~CFileParameters() ; 

    CAVLNode *GetItr() {return itrnode; } 
    void SetItr(CAVLNode *itr) {itrnode = itr; } 

    // reset the flags
    void SetFlags(int f) ; 

    // Used to walk the tree of parameters
    void InitIterator() ;
    FileParmNode *NextParm() ;
    FileParmNode *FindParm(char *parmname, unsigned char t) ; 

    int TestInitParm(char *name, double d) ;
    int TestInitParm(char *name, int i) ;
    int TestInitParm(char *name, csString &str) ;
    int TestInitParm(char *name, char *str) ;

    int SetParm(char *name, double d) ;
    int SetParm(char *name, int i) ;
    int SetParm(char *name, long i) ;
    int SetParm(char *name, const char *s) ;
    int SetParm(char *name, csString &) ; 

    int GetParm(char *name, double &d, double *def=0) ;
    int GetParm(char *name, int &i, int *def=0) ;
    int GetParm(char *name, long &i, long *def=0) ;
    int GetParm(char *name, csString &str, char *def=0) ;

    int GetInitParm(char *name, double &d, double def) ;
    int GetInitParm(char *name, int &i, int def) ;
    int GetInitParm(char *name, long &i, long def) ;
    int GetInitParm(char *name, csString &str, char *def) ;

    int GetInt(char *name) ; 
    long GetLong(char *name) ; 
    double GetDouble(char *name) ; 
    char *GetString(char *name) ; 


    int BuildParmStrings(csString &result) ; 
    int ExtractParm(csString &inputstring) ; 

    int SaveParms(const char *filename=0) ;
    int LoadParms(const char *filename=0) ; 



private:
    // extract the pathname and setname
    int setNameAndPath(csString &str, csString &name, csString &path) ;

    // see if the parm exists

} ;



#endif


