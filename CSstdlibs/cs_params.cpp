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

// cs_params.cpp 

#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4786)

#include "csstring.h"
#include "cs_params.h"

#ifdef WIN32

#define    READMODETEXT    "rt"
#define    WRITEMODETEXT   "wt"

#else

#define    READMODETEXT    "r"
#define    WRITEMODETEXT   "w"

#endif 

// =========================================================== 
// CS_Var virtual member functions for the int,double and 
// csString typdef's 
// =========================================================== 

/* --------------------------------------------------------------*/
/***************/
/*   CS_VarInt */
/***************/
template<> CS_Var<int, CSPVT_INT>::CS_Var()
{
}

template<> CS_Var<int, CSPVT_INT>::~CS_Var()
{
}

template<> CS_Var<int, CSPVT_INT>::CS_Var(const CS_Var<int, CSPVT_INT> &var) 
{
    Copy(var) ; // copies name and state  
    v = var.v ;
}

CS_VarInt &CS_VarInt::operator=(const CS_VarInt &var) 
{
    v = var.v ; 
    CS_VarObj::operator=(var) ; 
    return *this ; 
}


csString CS_VarInt::ToStr(const char *parent) 
{ 
    char buffer[64] ; 
    sprintf(buffer, "%d", v) ; 
    csString str(buffer) ; 
    return str ; 
}

    //! Inverse operation of the ToStr function
int CS_VarInt::FromStr(const char *parent, const char *pcs) 
{ 
    if (pcs)
        v = atoi(pcs) ; 
    else
        v = 0 ; 
    return 0 ; 
} 


/* --------------------------------------------------------------*/
/*****************/
/*  CS_VarDouble */
/*****************/

template<> CS_Var<double, CSPVT_DOUBLE>::CS_Var() 
{
}


template<> CS_Var<double, CSPVT_DOUBLE>::~CS_Var() 
{
}


template<> CS_Var<double, CSPVT_DOUBLE>::CS_Var(const CS_Var<double, CSPVT_DOUBLE> &var) 
{
    Copy(var) ; // copies name and state 
    v = var.v ;
}

CS_VarDouble &CS_VarDouble::operator=(const CS_VarDouble &var) 
{
    v = var.v ; 
    CS_VarObj::operator=(var) ; 
    return *this ; 
}


csString CS_VarDouble::ToStr(const char *parent) 
{ 
    char buffer[64] ; 
    sprintf(buffer, "%.16g", v) ; 
    csString str(buffer) ; 
    return str ; 
}

    //! Inverse operation of the ToStr function
int CS_VarDouble::FromStr(const char *parent, const char *pcs) 
{ 
    if (pcs)
        v = atof(pcs) ; 
    else
        v = 0 ; 
    return 0 ; 
} 


/* --------------------------------------------------------------*/
/*****************/
/*  CS_VarString */
/*****************/

template<> CS_Var<csString, CSPVT_STRING>::CS_Var() 
{
}

template<> CS_Var<csString, CSPVT_STRING>::~CS_Var() 
{
}


template<> CS_Var<csString, CSPVT_STRING>::CS_Var(const CS_Var<csString, CSPVT_STRING> &var) 
{
    Copy(var) ; // copies name and state 
    v = var.v ;
}

CS_VarString &CS_VarString::operator=(const CS_VarString &var) 
{
    v = var.v ; 
    CS_VarObj::operator=(var) ; 
    return *this ; 
}


csString CS_VarString::ToStr(const char *parent) 
{ 
    return v ; 
}

    //! Inverse operation of the ToStr function
int CS_VarString::FromStr(const char *parent, const char *pcs) 
{ 
    if (pcs)
        v = pcs ; 
    else
        v.clear() ; 
    return 0 ; 
} 


/* --------------------------------------------------------------*/
/*****************/
/*  CS_VarSet    */
/*****************/
template<> CS_Var<CS_DataSet, CSPVT_DATASET>::CS_Var() 
{
}

template<> CS_Var<CS_DataSet, CSPVT_DATASET>::~CS_Var() 
{
}


template<> CS_Var<CS_DataSet, CSPVT_DATASET>::CS_Var(const CS_Var<CS_DataSet, CSPVT_DATASET> &var) 
{
    Copy(var) ; // copies name and state 
    v = var.v ;
}

CS_VarSet &CS_VarSet::operator=(const CS_VarSet &var) 
{
    v = var.v ; 
    CS_VarObj::operator=(var) ; 
    return *this ; 
}


csString CS_VarSet::ToStr(const char *parent) 
{ 
    csString resp ; 
    CS_VarMapItr vmi ; 
    // Do non set members first and then the subsets

    for (vmi = v.vm.begin(); vmi != v.vm.end(); vmi++)
    {
        if (vmi->second->VType() != CSPVT_DATASET)
        {
            csString fullname = parent + csString(".") + vmi->first ; 
            resp += "  <parm>\n" ;
            resp += "    <name>" + fullname + "</name>\n" ; 
            resp += "    <value>" ; 
            resp += vmi->second->ToStr(fullname.str) ; 
            resp += "</value>\n" ; 
            resp += "  </parm>\n" ;
        }
    }

    // Now go through everything again and do just the subsets.
    for (vmi = v.vm.begin(); vmi != v.vm.end(); vmi++)
    {
        if (vmi->second->VType() == CSPVT_DATASET)
        {
            csString fullname = parent + csString(".") + vmi->first ; 
            resp += vmi->second->ToStr(fullname.str) ; 
        }
    }

    return resp ; 
}

//! Inverse operation of the ToStr function
int CS_VarSet::FromStr(const char *parent, const char *pcs) 
{ 
    // This should never get called since GetVar() should always 
    // drill down to a base variable which will have a FromStr() defined
    
    return 0 ; 
} 



/* --------------------------------------------------------------*/
// ===================================== 
// ===  CS_DataSet member functions  === 
// ===================================== 

CS_DataSet::~CS_DataSet() 
{
    CS_VarMapItr vmi ; 
    for (vmi = vm.begin(); vmi != vm.end(); vmi++)
    {
        delete vmi->second ; 
        vmi->second = 0 ; 
    }
}



//! Add the object to the set or change the value of object in set
void CS_DataSet::SetVar(CS_VarObj *pvo)
{
    CS_VarMapItr vmi = vm.find(pvo->name) ; 
    if (vmi != vm.end())
    {
        vmi->second->Set(pvo) ;
    }
    else
    {
        vm.insert(pair<csString, CS_VarObj*>(pvo->name, pvo)) ;
    }
}

//! Retrieve the named object, returns NULL if object not defined
CS_VarObj *CS_DataSet::GetVar(const char *varname)
{
    CS_VarMapItr vmi = vm.find(csString(varname)) ;
    if (vmi != vm.end())
    {
        return vmi->second ;
    }
    else
    {   // Have to search for the variable with subsets if they exist
        CS_VarObj *pretobj = 0 ; 
        for (vmi = vm.begin(); vmi != vm.end(); vmi++)
        {
            if (vmi->second->VType() == CSPVT_DATASET)
            {
                CS_VarSet *pvs = static_cast<CS_VarSet*>(vmi->second) ; 
                csString vname(varname) ; 
                int idx = vname.FindIDX(pvs->name) ; 
                csString varsubname = vname.Mid(idx + pvs->name.len+1) ; 
                if ((pretobj = pvs->v.GetVar(varsubname.str)) != 0)
                    return pretobj ; 
            }
        }
    }

    return 0 ; 
}

csString CS_DataSet::GetParentName(csString &varname)
{
    csString parent ; 
    int i = varname.FindLastIDX(".") ; 
    if (i > 0)
        parent = varname.Left(i) ; 
    return parent ; 
}


//! Read data from file, returns 0 on success
int CS_DataSet::Read(const char *filename)
{
    FILE *fp = fopen(filename, "r") ; 
    if (fp != 0)
    {
        Read(fp) ; 
        fclose(fp) ; 
    }
    return 0 ; 
}


//! Returns length of value extracted
int CS_DataSet::ExtractXMLValue(csString &ln, csString &xmltype, csString &value) 
{
    char *ps = ln.str ; 
    if (!ps)
        return 0 ; 
    csString parm ; 

    xmltype.clear() ; 
    value.clear() ;

    int i1 = ln.FindIDX("<") ; 
    int i2 = ln.FindIDX(">", i1) ; 
    // Search from the end now
    int i4 = ln.FindLastIDX(">") ; 
    int i3 = ln.FindLastIDX("</", i4) ; 
    
    i1 += 1 ;  
    i3 += 2 ; 

    //   <parm>........</parm>
    //   i1   i2       i3    i4

    if (i1 < i2 && i2 < i3 && i3 < i4)
    {   // Hopefully everything makes sense then 
        xmltype = ln.Mid(i1, i2-i1) ; 
        csString xmlend = ln.Mid(i3, i4-i3) ; 
        if (xmltype == xmlend)
            value = ln.Mid(i2+1, i3-i2-3) ; 
    }

    return value.len ; 
}


int CS_DataSet::Read(FILE *fp)
{
    char *buf = new char[XMLBUFLEN] ; 

    csString setnamedef = "<set name=\"" + name + '\"' + csString(">") ; 

    while(fgets(buf, XMLBUFLEN, fp))
    {   // Loop until we find the start of the set
        if (strncmp(setnamedef.str, buf, setnamedef.len) == 0)
            break ; // found the line that defines the start of the set
    }

    csString setend("</set>") ; 

    int i ; 

    csString xmltype, value ; 
    csString varname, varval ; 

    while(fgets(buf, XMLBUFLEN, fp))
    {   // Read data until we reach the end of file or read </set> line
        csString ln(buf) ; 
        ln.Trim() ; 

        if (ln == setend)
            break ; // done
        else if ((i = ln.FindIDX("<parm>")) >= 0)
        {   // Read lines until we find the matching </parm>
            varname.clear() ; 
            varval.clear() ; 
            while(fgets(buf, XMLBUFLEN, fp))
            {
                ln = buf ; 
                ln.Trim() ; 
                if (ln.FindIDX("</parm>") >= 0)
                    break ; 
                else if (ExtractXMLValue(ln, xmltype, value) > 0)
                {   
                    if (xmltype == "name") 
                        varname = value ; 
                    else if (xmltype == "value") 
                        varval = value ; 
                }
            }
        }

        if (varname.len > 0)
        {
            csString parent = GetParentName(varname) ; 
            csString varpath = varname.Mid(name.len+1) ;
            CS_VarObj *pvo = GetVar(varpath.str) ; 
            if (pvo)
                pvo->FromStr(parent.str, varval.str) ;
        }
    }
    
    delete[] buf ; 
    return 0 ; 
}



//! Write data to file, returns 0 on success
int CS_DataSet::Write(const char *flname)
{
    int retval = 0; 
    FILE *fp = fopen(flname, "w") ; 
    retval = Write(fp) ; 
    if (fp != stdout)
        fclose(fp) ; 
    return retval ; 
}

int CS_DataSet::Write(const FILE *fpout)
{
    FILE *fp = (FILE *)fpout ; 
    
    if (!fp)
        fp = stdout ; 

    CS_VarMapItr vmi ; 
    csString basename = name ; 

    fprintf(fp, "\n<set name=\"%s\">\n", name.c_str()) ; 

    if (name.len > 0)
        basename += "." ; // add field separator character

    // First process all the main variables, and then do all the subset variables
    for (vmi = vm.begin(); vmi != vm.end(); vmi++)
    {
        if (vmi->second->VType() != CSPVT_DATASET)
        {
            csString parent = basename + vmi->first ; 
            fprintf(fp, "  <parm>\n") ;
            fprintf(fp, "    <name>%s</name>\n", parent.str) ; 
            fprintf(fp, "    <value>") ; 
            fprintf(fp, "%s", (vmi->second->ToStr(parent.str)).str) ; 
            fprintf(fp, "</value>\n") ; 
            fprintf(fp, "  </parm>\n") ;
        }
    }

    // Now go through everything again and do just the subsets.
    for (vmi = vm.begin(); vmi != vm.end(); vmi++)
    {
        if (vmi->second->VType() == CSPVT_DATASET)
        {
            csString parent = basename + vmi->first ; 
            fprintf(fp, "%s", (vmi->second->ToStr(parent.str)).str) ; 
        }
    }

    fprintf(fp, "</set>\n") ; 

    return 0 ; 
}



/*
//! Convert variable to a string representation for writing to file
csString CS_PSet::ToStr() 
{ 
    string retstr ;
    CS_PVarMapItr pvi ; 
    for (pvi = vmap.begin(); pvi != vmap.end(); pvi++)
    {
        // \todo have to add XML type file encoding here
        CS_PVar *pv = pvi->second ; 
        retstr += pv->ToStr() ;
        retstr += "\n" ; 
    }
    return 0 ; 
}

//! Inverse operation of the ToStr function
/ *!
    \param str multiline string which contains the data for the set

    This reads parameter data from the str. The string contains
    multiline data. The sets basename string can exist
    within the name descriptors for the data. Thus depending on 
    how the data is to be stored the FromStr() can decide whether
    or not to use the full path names in storing data into the 
    parameter set. 
 * /
void CS_PSet::FromStr(string &str) 
{ 
    int idx = 0, inxt ; 
    csString line ; 
    while ((inxt = str.find("\n", idx)) > idx)
    {
        line.SetString(str.c_str() + idx, inxt - idx) ;
        idx = inxt + 1 ; 

        // Process the line

        // \todo have to add XML type file encoding here
    }
} 

*/

/*

CS_PVar *CS_PSet::Find(const char *varname)
{
    CS_VarMapItr vmi ; 
    vmi = vmap.find(csString(varname)) ; 
    if (vmi != vmap.end())
        return vmi->second ; 
    return 0 ; 
}



// =========================================================== 
// =====================     SET        ====================== 
// =========================================================== 


int CS_PSet::SetParm(const char *varname, const int val)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() == CSPVT_INT)
        {
            ((CS_PVarInt *)pvar)->Set(val) ; 
        }
        else
            return WRONGTYPE ; 
    }
    else
    {
        vmap.insert(pair<string, CS_PVar*>(string(varname), new CS_PVarInt(varname, val))) ; 
    }
    return 0 ; 
}


int CS_PSet::SetParm(const char *varname, const double val)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() == CSPVT_DOUBLE)
            ((CS_PVarDouble *)pvar)->Set(val) ; 
        else
            return WRONGTYPE ; 
    }
    else
    {
        vmap.insert(pair<string, CS_PVar*>(string(varname), new CS_PVarDouble(varname, val))) ; 
    }
    return 0 ; 
}


int CS_PSet::SetParm(const char *varname, const string &val)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() == CSPVT_STRING)
            ((CS_PVarString *)pvar)->Set(val) ; 
        else
            return WRONGTYPE ; 
    }
    else
    {
        vmap.insert(pair<string, CS_PVar*>(string(varname), new CS_PVarString(varname, val))) ; 
    }
    return 0 ; 
}


int CS_PSet::SetParm(const char *varname, const char *val)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() == CSPVT_STRING)
            ((CS_PVarString *)pvar)->Set(val) ; 
        else
            return WRONGTYPE ; 
    }
    else
    {
        vmap.insert(pair<string, CS_PVar*>(string(varname), new CS_PVarString(varname, string(val)))) ; 
    }
    return 0 ; 
}



// =========================================================== 
// =====================     GET        ====================== 
// =========================================================== 

//! Return reference to actual variable
int& CS_PSet::GetInt(const char *varname)
{
    static int dummyref = 0 ; 
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_INT)
        {
            errorcode = WRONGTYPE ; 
            return dummyref; 
        }
        errorcode = 0 ; 
        return ((CS_PVarInt *)pvar)->Get() ; 
    }
    errorcode = VARNOTFOUND ; 
    return dummyref ; 
}

//! Return reference to actual variable
double& CS_PSet::GetDouble(const char *varname)
{
    static double dummyref = 0 ; 
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_DOUBLE)
        {
            errorcode = WRONGTYPE ; 
            return dummyref ; 
        }
        errorcode = 0 ; 
        return ((CS_PVarDouble *)pvar)->Get() ; 
    }
    errorcode = VARNOTFOUND ; 
    return dummyref ; 
}

//! Return reference to actual variable
string& CS_PSet::GetString(const char *varname)
{
    static string dummyref ; 
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_STRING)
        {
            errorcode = WRONGTYPE ; 
            return dummyref ; 
        }
        errorcode = 0 ; 
        return ((CS_PVarString *)pvar)->Get() ; 
    }
    errorcode = VARNOTFOUND ; 
    return dummyref ; 
}


//! Set variable value and return error code
int CS_PSet::Get(const char *varname, int &var)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_INT)
        {
            errorcode = WRONGTYPE ; 
        }
        else
        {
            errorcode = 0 ; 
            var = ((CS_PVarInt *)pvar)->Get() ; 
        }
    }
    else
    {
        errorcode = VARNOTFOUND ; 
    }
    return errorcode ; 
}


//! Set variable value and return error code
int CS_PSet::Get(const char *varname, double &var)
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_DOUBLE)
        {
            errorcode = WRONGTYPE ; 
        }
        else
        {
            errorcode = 0 ; 
            var = ((CS_PVarDouble *)pvar)->Get() ; 
        }
    }
    else
    {
        errorcode = VARNOTFOUND ; 
    }
    return errorcode ; 
}

//! Set variable value and return error code
int CS_PSet::Get(const char *varname, string &var) 
{
    CS_PVar *pvar = Find(varname) ; 
    if (pvar)
    {
        if (pvar->VarType() != CSPVT_STRING)
        {
            errorcode = WRONGTYPE ; 
        }
        else
        {
            errorcode = 0 ; 
            var = ((CS_PVarString *)pvar)->Get() ; 
        }
    }
    else
    {
        errorcode = VARNOTFOUND ; 
    }
    return errorcode ; 
}



/////////////////////////////////////////////////////////////////////
// End of Get/Set parameter methods. Following are file I/O and
// various other functions
/////////////////////////////////////////////////////////////////////


// returns 0 on success else returns error code. 
int CS_PSet::WriteParms(const char *filename)
{
    CS_PVar *pvar ; 
    FILE *fp = fopen(filename, WRITEMODETEXT) ; 

    if (!fp)
        return -1 ; 
    
    fprintf(fp, "[%s]\n", name.c_str()) ; // output the setname first
    CS_PVarMapItr pvi = vmap.begin() ; 
    while (pvi != vmap.end())
    {   
        pvar = pvi->second ;
        string varstr = pvar->ToStr() ; 
        fprintf(fp, "%s=%s\n", pvar->name.c_str(), varstr.c_str()) ; 
        pvi++ ; 
    }

    fclose(fp) ; 
    return 0 ; 
}

//! Returns true if the string in val looks like an integer
int CS_PSet::IsInteger(csString &val) 
{
    if (((val[0] == '+' || val[0] == '-') && val.IsDigit(1)) 
        || val.IsNumeric()) 
        return 1 ; 
    return 0 ; 
}

//! Returns true if the string in val looks like a floating point value
int CS_PSet::IsDouble(csString &val)
{
    if (val.IsNumeric())
        return 1 ; 
    return 0 ; 
}


CS_PVar *CS_PSet::SetNewPVar(csString &name, csString &val)
{
    if (IsInteger(val))
    {
        CS_PVarInt *pv = new CS_PVarInt(name.str, atoi(val.str)) ; 
    }
    else if (IsDouble(val))
    {
        CS_PVarDouble *pv = new CS_PVarDouble(name.str, atof(val.str)) ; 
    }
    else
    {   // Default to a string
        CS_PVarString *pv = new CS_PVarString(name.str, val.str) ; 
    }
    return 0 ; 
}


// Before caling this function, all the variables must be initialized
// so that the name lookup works correctly. Without the proper name
// and variable type definition, it is impossible for the load to
// know what type of data it is looking at. 
int CS_PSet::ReadParms(const char *filename) 
{   // Exrtact the parameters from the edit string created by the 
    // GetParms routine after user editing. This function will simply 
    // fail without warning if the returned user data is invalid
    char buffer[PARMSBUF_SIZE] ; // 64k buffer
    csString linein ;
    csString parmname ; 
    csString parmval ;

    CS_PVar *pvar, tmpvar ; 
    CS_PVarMapItr pvi ; 

    FILE *fp = fopen(filename, READMODETEXT) ; 
    if (!fp)
        return 1 ; // no data file

    while (fgets(buffer, PARMSBUF_SIZE, fp))
    {

        linein = buffer ; 
        
        linein.Trim() ; 
        if (linein.IsEmpty() || linein.Left(1) == "[" || linein.Left(1) == "#") 
            continue ; // skip title markers and comments

        parmname = linein.NextToken("=", 0) ; 
        parmval = linein.NextToken("=", linein.idx) ; 

        parmname.Trim() ; 
        parmval.Trim() ; 

        tmpvar.name = parmname.str ; 
        pvi = vmap.find(tmpvar.name) ; 

        if (pvi != vmap.end())
        {   // Reloading an existing variable
            pvar = pvi->second ; 
            pvar->FromStr(string(parmval.str)) ; 
        }
        else 
        {   // loading a new variable and adding it to the map
            CS_PVar *pv = SetNewPVar(parmname, parmval) ;
            if (pv)
                vmap.insert(pair<string, CS_PVar*>(string(parmname.str), pv)) ; 
        } ; 
    } 

    fclose(fp) ; 

    return 0 ; 
}


*/


//////////////////////////////////////////////////////////
// THIS IS OLD CODE TO SUPPORT THE srvrproc APPLICATION
//////////////////////////////////////////////////////////



void CS_ParameterVar::StringValue(csString &str)
{
    char tmpstr[128] ; 
    switch(type) 
    {
    case CS_INT :
        sprintf(tmpstr, "%d", i) ; 
        str = tmpstr ; 
        break ; 
    case CS_DOUBLE :
        sprintf(tmpstr, "%.16f", d) ; 
        str = tmpstr ; 
        break ; 
    case CS_CHAR :
        str = c ; 
        break ; 
    case CS_STRING :
        str = "\"" ;
        str += s ; 
        str += "\"" ; 
        break ; 
    case CS_DATA :
        unsigned int ii ; 
        for (int j=0; j < alloclen; j++)
        {
            ii = (unsigned char)s[j] ; // convert char to int
            sprintf(tmpstr, "%02x", ii) ; 
            str += tmpstr ; 
        }
        break ; 
    }
}

int CS_ParameterSet::InitParm(char *name, CS_ParameterType type, void *pdata, int size) 
{
    return 0 ; 
}


// Returns 0 on successfully initializing the variable. -1 is 
// returned if a memory allocation error occurs. pdata points to 
// default initial data
int CS_ParameterSet::AddParm(char *name, CS_ParameterType type, void *pdata, int size) 
{
    CS_ParameterVar *pvar = new CS_ParameterVar ; 
    pvar->name = name ; 
    pvar->type = type ; 
    switch(type)
    {
    case CS_INT :
        pvar->i = *((int *)pdata) ; 
        break ; 
    case CS_DOUBLE :
        pvar->d = *((double *)pdata) ; 
        break ; 
    case CS_CHAR :
        pvar->c = *((char *)pdata) ; 
        break ; 
    case CS_STRING :
        pvar->s = (char *)malloc(size) ; 
        if (!pvar->s)
            return -1 ; 
        memcpy(pvar->s, pdata, size) ; 
        pvar->alloclen = size ; 
        break ; 
    case CS_DATA :
        pvar->v = malloc(size) ; 
        if (!pvar->v)
            return -1 ; // memory error
        if (pdata)
            memcpy(pvar->v, pdata, size) ; 
        else
            memset(pvar->v, 0, size) ; 
        pvar->alloclen = size ; 
        break ; 
    }
    varTree.InsertNode(pvar) ; 
    return 0 ; 
}


// returns 0 on success else returns error code. 
int CS_ParameterSet::SaveParms(const char *filename)
{
    CS_ParameterVar *pvar ; 
#ifdef WIN32
    FILE *fp = fopen(filename, "wt+") ; 
#else
    FILE *fp = fopen(filename, "w+") ; 
#endif 

    if (!fp)
        return -1 ; 
    
    fprintf(fp, "[%s]\n", name.str) ; // output the setname first
    CAVLNode *pn = varTree.MinNode() ;  
    while (pn)
    {   
        csString varstr ; 
        pvar = varTree.GetData(pn) ; 
        pvar->StringValue(varstr) ; 
        fprintf(fp, "%s=%s\n", pvar->name.str, varstr.str) ; 
        pn = varTree.Successor(pn) ; 
    }

    fclose(fp) ; 
    return 0 ; 
}


#define CS_PARMSBUF_SIZE    0x10000
// Before caling this function, all the variables must be initialized
// so that the name lookup works correctly. Without the proper name
// and variable type definition, it is impossible for the load to
// know what type of data it is looking at. 
int CS_ParameterSet::LoadParms(const char *filename) 
{   // Exrtact the parameters from the edit string created by the 
    // GetParms routine after user editing. This function will simply 
    // fail without warning if the returned user data is invalid
    char buffer[CS_PARMSBUF_SIZE] ; // 64k buffer
    csString linein ;
    csString parmname ; 
    csString parmval ;

    CS_ParameterVar *pvar, tmpvar ; 
    CAVLNode *pn ; 

#ifdef WIN32
    FILE *fp = fopen(filename, "rt") ; 
#else
    FILE *fp = fopen(filename, "r") ; 
#endif 
    if (!fp)
        return 1 ; // no data file

    while (fgets(buffer, CS_PARMSBUF_SIZE, fp))
    {

        linein = buffer ; 
        
        linein.Trim() ; 
        if (linein.IsEmpty() || linein.Left(1) == "[" || linein.Left(1) == "#") 
            continue ; // skip title markers and comments

        parmname = linein.NextToken("=", 0) ; 
        parmval = linein.NextToken("=", linein.idx) ; 

        parmname.Trim() ; 
        parmval.Trim() ; 


        tmpvar.name = parmname ; 
        pn = varTree.FindNode(tmpvar) ; 
        if (!pn)
            continue ; 

        pvar = varTree.GetData(pn) ; 
        switch(pvar->type) 
        {
        case CS_INT :
            pvar->i = atoi(parmval.str) ; 
            break ; 
        case CS_DOUBLE :
            pvar->d = atof(parmval.str) ; 
            break ; 
        case CS_CHAR :
            pvar->c = parmval[0] ;
            break ; 
        case CS_STRING :
            // Chop off the enclosing quotes around the string
            parmval.TrimRight(1) ; 
            parmval.TrimLeft(1) ; 
            pvar->s = (char *)malloc(parmval.len + 1) ; 
            if (!pvar->s)
                continue ; 
            memcpy(pvar->s, parmval.str, parmval.len + 1) ; 
            pvar->alloclen = parmval.len + 1 ; 
            break ; 
        case CS_DATA :
            int i, j ; 
            unsigned char *puc ; 
            pvar->v = malloc(parmval.len / 2) ; 
            if (!pvar->v)
                return -1 ; // memory error
            pvar->alloclen = parmval.len / 2 ;
            unsigned int x ; 

            puc = (unsigned char *)pvar->v ; 
            for (i=0, j=0; i < pvar->alloclen ; i+=2, ++j)
            {
                x = (unsigned int)parmval.HexToInt(i, 2) ; 
                puc[j] = x ; 
            }
            break ; 
        }
    } 

    fclose(fp) ; 

    return 0 ; 
}


// Returns true if the variable was found and the
// data was copied to the parameter, otherwise returns false
int CS_ParameterSet::SetParm(char *name, void *pnew)
{
    CS_ParameterVar wrkvar ;
    wrkvar.name = name ; 
    CAVLNode *pn = varTree.FindNode(wrkvar) ;
    if (pn)
    {
        CS_ParameterVar *pvar = varTree.GetData(pn) ;
        switch(pvar->type) 
        {
        case CS_INT :
            pvar->i = *(int *)pnew ; 
            break ; 
        case CS_DOUBLE :
            pvar->d = *(double *)pnew ; 
            break ; 
        case CS_CHAR :
            pvar->c = *(char *)pnew ;
            break ; 
        case CS_STRING :
            int l ;
            char *sz ;
            sz = (char *)pnew ; 
            l = (int)strlen(sz) ; 
            if (l < pvar->alloclen)
                strcpy(pvar->s, sz) ; 
            else
            {
                free(pvar->s) ;
                pvar->s = (char *)malloc(l + 2) ; 
                strcpy(pvar->s, sz) ; 
                pvar->alloclen = l ;
            }
            break ; 
        case CS_DATA :
            unsigned char *pv = (unsigned char *)pnew ; 
            unsigned char *pdata = (unsigned char *)pvar->v ; 
            for (int i=0; i < pvar->alloclen; i++)
                pdata[i] = pv[i] ; 
            break ; 
        }
        return 1 ; 
    }
    return 0 ; 
}


// If the parameter is a type string or binary, then the pointer 
// passed in must have enough space allocated to it to accept the 
// variable data. Returns true if the variable was found and the
// data was copied to the void pointer, otherwise returns false
int CS_ParameterSet::GetParm(char *name, void *pdata)
{
    CS_ParameterVar wrkvar ; 
    wrkvar.name = name ; 
    CAVLNode *pn = varTree.FindNode(wrkvar) ;
    if (pn)
    {
        CS_ParameterVar *pvar = varTree.GetData(pn) ; 
        switch(pvar->type) 
        {
        case CS_INT :
            *(int *)pdata = pvar->i ; 
            break ; 
        case CS_DOUBLE :
            *(double *)pdata = pvar->d ; 
            break ; 
        case CS_CHAR :
            *(char *)pdata = pvar->c ;
            break ; 
        case CS_STRING :
            strcpy((char *)pdata, pvar->s) ; 
            break ; 
        case CS_DATA :
            memcpy(pdata, pvar->v, pvar->alloclen) ; 
            break ; 
        }
        return 1 ; 
    }
    return 0 ; 
}
