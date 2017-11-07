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

// fileparams.cpp


#include <stdlib.h>
#include "wrkfuncs.h"
#include "csstring.h"
#include "fileparams.h"

#pragma warning(disable : 4996)

// Create an empty parameter set definition
CFileParameters::CFileParameters(int flags) 
{   // Initialize parameter name file
    bFlags = flags ; 
}

// Initialize parameter name file, and load the parameter set, if the 
// .INI file extension is included in the name it is stripped off. 
CFileParameters::CFileParameters(csString parmsetname, int flags) 
{   
    csString name, path ; 
    setNameAndPath(parmsetname, setname, pathname) ; 
    LoadParms() ; 
    bFlags = flags ; 
}

CFileParameters::~CFileParameters()
{
    parmtree.DeleteTree() ; 
}

// extract the pathname and setname
int CFileParameters::setNameAndPath(csString &str, 
                                    csString &name,  csString &path)
{
    SplitPathAndFile(str, path, name) ; 
    // now extract the .INI off the end of the setname if it exists
    csString wrkstr(name) ; 
    wrkstr.ToUpper() ;
    if (wrkstr.Right(4) == ".INI")
    {
        name = name.Left(name.len - 4) ;
    }
    return 0 ; 
}


FileParmNode *CFileParameters::FindParm(char *str, unsigned char t)
{
    FileParmNode fpn ;
    fpn.name = str ;
    fpn.type = t ;

    CAVLNode *pn = parmtree.FindNode(fpn) ;
    if (pn)
        return parmtree.GetData(pn) ;
    return 0 ; // found nothing
}

// reset the flags
void CFileParameters::SetFlags(int f) 
{
    bFlags = f ; 
}

// Returns 0 if it does nothing, 1 if the value is changed
// and 3 if the parameter is created.
int CFileParameters::SetParm(char *name, double d)
{
    int retval = 0 ;
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_DOUBLE) ; 
    if (pfpn)
    {   // Then the node already exists in the tree
        if (pfpn->d == d)
        {   // Setting it to the same value so nothing to do
            return 0 ; 
        }
        pfpn->d = d ; 
        retval = 1 ; 
    }
    else
    {   // Create the parameter
        FileParmNode fpn ; 
        
        fpn.name = name ; 
        fpn.type = FP_PARMTYPE_DOUBLE ; 
        fpn.d = d ; 

        parmtree.InsertNode(fpn) ; 
        retval = 3 ; 
    }

    bFlags |= FPARMS_MODIFIED ; 
    return retval ; 
}


int CFileParameters::SetParm(char *name, int i)
{
    int retval = 0 ;
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_INTEGER) ; 
    if (pfpn)
    {   // Then the node already exists in the tree
        if (pfpn->i == i)
        {   // Setting it to the same value so nothing to do
            return 0 ; 
        }
        pfpn->i = i ; 
        retval = 1 ; 
    }
    else
    {   // Create the parameter
        FileParmNode fpn ; 
        
        fpn.name = name ; 
        fpn.type = FP_PARMTYPE_INTEGER ; 
        fpn.i = i ; 

        parmtree.InsertNode(fpn) ; 
        retval = 3 ; 
    }

    bFlags |= FPARMS_MODIFIED ; 
    return retval ; 
}

int CFileParameters::SetParm(char *name, long i)
{
    int x = (int)i ; 
    return SetParm(name, x) ; 
}


int CFileParameters::SetParm(char *name, const char *str)
{
    int retval = 0 ;
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_STRING) ; 
    if (pfpn)
    {   // Then the node already exists in the tree
        if (pfpn->str == csString(str))
        {   // Setting it to the same value so nothing to do
            return 0 ; 
        }
        pfpn->str = str ; 
        retval = 1 ; 
    }
    else
    {   // Create the parameter
        FileParmNode fpn ; 
        
        fpn.name = name ; 
        fpn.type = FP_PARMTYPE_STRING ; 
        fpn.str = str ; 

        parmtree.InsertNode(fpn) ; 
        retval = 3 ; 
    }

    bFlags |= FPARMS_MODIFIED ; 
    return retval ; 
}

int CFileParameters::SetParm(char *name, csString &str)
{
    int retval = 0 ;
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_STRING) ; 
    if (pfpn)
    {   // Then the node already exists in the tree
        if (pfpn->str == str)
        {   // Setting it to the same value so nothing to do
            return 0 ; 
        }
        pfpn->str = str ; 
        retval = 1 ; 
    }
    else
    {   // Create the parameter
        FileParmNode fpn ; 
        
        fpn.name = name ; 
        fpn.type = FP_PARMTYPE_STRING ; 
        fpn.str = str ; 

        parmtree.InsertNode(fpn) ; 
        retval = 3 ; 
    }

    bFlags |= FPARMS_MODIFIED ; 
    return retval ; 
}


// Set the parameter to the specified value only if it does not exist
// and if it doesn't then create it, and set the default value
int CFileParameters::TestInitParm(char *name, csString &str)
{
    csString dummy ; 
    int ret = GetParm(name, dummy, str.str) ; 
    return ret ; 
}

int CFileParameters::TestInitParm(char *name, char *str)
{
    csString dummy ; 
    int ret = GetParm(name, dummy, str) ; 
    return ret ; 
}


// Set the parameter to the specified value only if it does not exist
// and if it doesn't then create it, and set the default value
int CFileParameters::TestInitParm(char *name, int i)
{
    int dummy ; 
    int ret = GetParm(name, dummy, &i) ; 
    return ret ; 
}

// Set the parameter to the specified value only if it does not exist
// and if it doesn't then create it, and set the default value
int CFileParameters::TestInitParm(char *name, double d)
{
    double dummy ; 
    int ret = GetParm(name, dummy, &d) ; 
    return ret ; 
}


// returns 0 on successfully retrieving the parameter value, otherwise
// returns -1 (Error code). If it finds the parameter requested, its
// value is set in the second parameter passed in (d). If a default
// is defined and the parameter is not found, then the parameter
// is defined/created and a 1 is returned. If an error occurs in 
// creating the new parameter then -2 is returned. If then parameter
// is not found and no default is specified, then the value of the 
// parameter is not changed and -1 is returned. 

int CFileParameters::GetParm(char *name, double &d, double *def)
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_DOUBLE) ; 
    if (pfpn)
    {
        d = pfpn->d ; 
    }
    else if (def)
    {   // Then a default is defined so set the parameter to the default value
        if (!SetParm(name, *def))
            return 1 ;
        d = *def ; 
        return -2 ; 
    }

    return -1 ; // parameter not defined
}

int CFileParameters::GetParm(char *name, int &i, int *def)
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_INTEGER) ; 
    if (pfpn)
    {
        i = pfpn->i ; 
    }
    else if (def)
    {   // Then a default is defined so set the parameter to the default value
        if (!SetParm(name, *def))
            return 1 ;
        i = *def ;
        return -2 ; 
    }

    return -1 ; // parameter not defined
}

int CFileParameters::GetParm(char *name, long &i, long *def)
{
    int n, *ptrn ;
    n = (int)i ; 
    ptrn = (int *)def ; 
    int retval = GetParm(name, n, ptrn) ; 
    i = n ; 
    return retval ; 
}


int CFileParameters::GetParm(char *name, csString &str, char *def) 
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_STRING) ; 
    if (pfpn)
    {
        str = pfpn->str ; 
    }
    else if (def)
    {   // Then a default is defined so set the parameter to the default value
        if (!SetParm(name, def))
            return 1 ;
        str = def ;
        return -2 ; 
    }

    return -1 ; // parameter not defined
}

int CFileParameters::GetInt(char *name)
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_INTEGER) ; 
    if (pfpn)
    {
        return pfpn->i ; 
    }
    return 0 ; // not found so return default value of 0
}

long CFileParameters::GetLong(char *name)
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_INTEGER) ; 
    if (pfpn)
    {
        return (long)pfpn->i ; 
    }
    return 0 ; // not found so return default value of 0
}

double CFileParameters::GetDouble(char *name)
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_DOUBLE) ; 
    if (pfpn)
    {
        return pfpn->d ; 
    }
    return 0 ; // not found so return default value of 0
}

char *CFileParameters::GetString(char *name) 
{
    FileParmNode *pfpn = FindParm(name, FP_PARMTYPE_STRING) ; 
    if (pfpn)
    {
        return pfpn->str.str ; 
    }
    return "" ; // not found so return default value of NULL string
}


int CFileParameters::GetInitParm(char *name, double &d, double def) 
{
    return GetParm(name, d, &def) ;
}

int CFileParameters::GetInitParm(char *name, int &i, int def)
{
    return GetParm(name, i, &def) ;
}

int CFileParameters::GetInitParm(char *name, long &i, long def) 
{
    return GetParm(name, i, &def) ;
}

int CFileParameters::GetInitParm(char *name, csString &str, char *def) 
{
    return GetParm(name, str, def) ;
}



/**
  Save the parameter set to a new name, this does no change the 
  original default name of the parameter file

  File is saved in basic XML format as follows
  
  <PARM name="name" type="type"  value="value" />
  <PARM name="name" type="type"  value="value" />
  <PARM name="name" type="type"  value="value" />
  <PARM name="name" type="type"  value="value" />
      

  */
int CFileParameters::BuildParmStrings(csString &result)
{
    char tmpstr[FPARMS_MAXLINELENGTH] ; 
    CAVLNode *pn = parmtree.MinNode() ; 
    FileParmNode *pfpn ; 
    while (pn)
    {
        pfpn = parmtree.GetData(pn) ; 
        switch(pfpn->type)
        {
        case FP_PARMTYPE_DOUBLE :
            sprintf(tmpstr,"<PARM name=\"%s\" type=\"%d\" value=\"%g\" />\n", 
                        pfpn->name.str, (unsigned int)pfpn->type, pfpn->d) ; 
            result += tmpstr ; 
            break ; 
        case FP_PARMTYPE_INTEGER :
            sprintf(tmpstr,"<PARM name=\"%s\" type=\"%d\" value=\"%d\" />\n", 
                        pfpn->name.str, (unsigned int)pfpn->type, pfpn->i) ; 
            result += tmpstr ; 
            break ; 
        case FP_PARMTYPE_STRING :
            if (pfpn->str.Length() > 0)
            {
                sprintf(tmpstr,"<PARM name=\"%s\" type=\"%d\" value=\"%s\" />\n", 
                            pfpn->name.str, (unsigned int)pfpn->type, pfpn->str.str) ; 
            }
            else
            {
                sprintf(tmpstr,"<PARM name=\"%s\" type=\"%d\" value=\"\" />\n", 
                            pfpn->name.str, (unsigned int)pfpn->type) ; 
            }
            result += tmpstr ; 
            break ; 
        }

        pn = parmtree.Successor(pn) ; 
    }

    return 0 ; 
}

// Processes a single line of data and sets the parameter defined by it
int CFileParameters::ExtractParm(csString &wrkstr)
{
    csString tokname, tokvalue, parmname, parmvalue, parmtype ; 
    static char tokdelims[4] = " \t" ; 

    csString tok = wrkstr.NextToken(tokdelims, 0) ;
    if (tok == "<PARM")
    {   // Then this is a valid line, extract remaining tokens
        tok = wrkstr.NextQuotedToken(tokdelims, wrkstr.idx) ;
        GetNameAndValue(tok, tokname, tokvalue) ;
        if (tokname == "name")
        {   // Then the data is good so continue
            parmname = tokvalue ;
            tok = wrkstr.NextQuotedToken(tokdelims, wrkstr.idx) ;
            GetNameAndValue(tok, tokname, tokvalue) ;
            if (tokname == "type")
            {
                parmtype = tokvalue ;
                tok = wrkstr.NextQuotedToken(tokdelims, wrkstr.idx) ;
                GetNameAndValue(tok, tokname, tokvalue) ;
                if (tokname == "value")
                {
                    parmvalue = tokvalue ;
                    tok = wrkstr.NextQuotedToken(tokdelims, wrkstr.idx) ;
                    GetNameAndValue(tok, tokname, tokvalue) ;
                    if (tokname == "/>")
                    {   // This is the proper termination so save the parameter
                        switch(atoi(parmtype.str))
                        {
                        case FP_PARMTYPE_DOUBLE :
                            SetParm(parmname.str, atof(parmvalue.str)) ; 
                            break ; 
                        case FP_PARMTYPE_INTEGER :
                            SetParm(parmname.str, atoi(parmvalue.str)) ; 
                            break ; 
                        case FP_PARMTYPE_STRING :
                            SetParm(parmname.str, parmvalue.str) ; 
                            break ; 
                        }
                    }
                }
            }
        }
    }
    return 0 ; 
}




int CFileParameters::SaveParms(const char *filename)
{
    // Write the internal parameters. 
    csString outputSetname ;
    csString outputPathname ;
    if (filename != 0)
    {   // Then save using these new temporary file names
        csString tmpfile(filename) ; 
        csString tmpout(outputSetname + ".ini") ; 
        setNameAndPath(tmpfile,tmpout, outputPathname) ;
    }
    else
    {
        outputSetname = setname + ".ini" ; 
        outputPathname = pathname ; 
    }


    csString fname = AddFile2Path(outputPathname, outputSetname) ; 

    FILE *fp = fopen(fname.str, "w+t") ;
    if (!fp)
        return -1 ; // something went wrong

    csString result ; 
    
    BuildParmStrings(result) ; 
    fprintf(fp, "%s", result.str) ; 

    fclose(fp) ; 

    bFlags &= ~FPARMS_MODIFIED ; 

    return 0 ; 
}

/** 
  Load the parameter set from the file name specified, returns 0 if the 
  file is loaded without error. otherwise an error or warning condition
  is returned. 
  */
int CFileParameters::LoadParms(const char *filename)
{
    if (filename != 0)
    {
        csString tmpfile(filename) ; 
        setNameAndPath(tmpfile, setname, pathname) ; 
    }

    csString fname ; 
    fname = AddFile2Path(pathname, csString(setname + ".ini")) ; 

    FILE *fp = fopen(fname.str, READMODETEXT) ;

    if (!fp)
        return 1 ; // no data file present

    csString wrkstr, tokname, tokvalue, parmname, parmvalue, parmtype ; 

    char buffer[FPARMS_MAXLINELENGTH] ; 
    char tokdelims[4] = " \t" ; 

    while (fgets(buffer, FPARMS_MAXLINELENGTH, fp))
    {
        wrkstr = buffer ; 
        ExtractParm(wrkstr) ; 
    }

    bFlags &= ~FPARMS_MODIFIED ; 

    fclose(fp) ; 

    return 0 ; 
}


void CFileParameters::InitIterator()
{
    itrnode = parmtree.MinNode() ; 
}

FileParmNode *CFileParameters::NextParm()
{
    FileParmNode *retnode = 0 ; 
    if (itrnode != 0) 
    {
        retnode = parmtree.GetData(itrnode) ; 
        itrnode = parmtree.Successor(itrnode) ; 
    }
    return retnode ; 
}

