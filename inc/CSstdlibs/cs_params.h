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

// cs_params.h


#ifndef __CS_PARAMS_H__
#define __CS_PARAMS_H__

#pragma warning( disable : 4996 )


#include <stdlib.h>
#include <list>
#include <map>

#include "avltree.h"
#include "csstring.h"
#include "cslists.h"


using namespace std ; 

#pragma warning ( disable : 4786 )

/*
  Usage Notes:

  1) Declare the parameter set class somewhere such as
        CS_PSet parmSet ; 
  2) Define the parameters that will be part of the set
     and define their intial values with the definition macros.


 */

#ifndef CS_CHARPTR
typedef char*  CS_CHARPTR ; 
#endif

#ifndef CS_VOIDPTR
typedef void*  CS_VOIDPTR ; 
#endif

//! Constant designating the type of data stored in this variable
enum {
    CSPVT_NONE     = 0,
    CSPVT_INT      = 1, //!< Parameter type int    i
    CSPVT_DOUBLE   = 2, //!< Parameter type double d
    CSPVT_STRING   = 3, //!< Parameter type string
    CSPVT_DATASET  = 4, //!< Parameter type void*  v
    CSPVT_LAST     = 5, //!< value of last internal definition
    CSPVT_USER     = 0x0100, //!< user defined type starting value
} ;  


//! Parameter data variable
/*!
    This is where the actual data is stored. When using the generic 
    binary data type variable, make sure that you don't include 
    classes that include _vtbl ptr type information, since on the reload
    these pointer values will certainly be incorrect. If you do
    need to save these variables, make sure you override the 
    get and set operations appropriately in a derived definition
    for the class. Thus, use a filter variable
    on the reload to transfer data to a properly initialized 
    class variable (with the proper _vtbl ptr)
 */    
class CS_VarObj
{
public:
    enum {  // Var specific state bits
        DONTSAVE    = 0x0001, //!< Do not read/write to file or save this parameter
    } ;
    //! The unique name of the parameter
    
    int state ; 
    csString name ;

    //! Constructor initializes the state to 0
    CS_VarObj() 
    {
        state = 0 ; 
    } ; 

    //! Copy constructor copies name and state
    CS_VarObj(const CS_VarObj &v)
    {
        name = v.name ; 
        state = v.state ; 
    } ;

    //! Assignment operator copies name and state
    virtual CS_VarObj &operator=(const CS_VarObj &v) 
    { 
        name = v.name ; 
        state = v.state ; 
        return *this ; 
    } ;

    void Copy(const CS_VarObj &v)
    {
        state = v.state ; 
        name = v.name ; 
    }

    virtual void Set(const CS_VarObj *pvo) {} ;

    //! Set the variable object's name
    void SetName(csString &n) { name = n ; }  ; 

    //! Returns the variable objects type identifier
    virtual int VType() { return CSPVT_NONE ; } ; 

    //! Generate a string representation for this variable
    virtual csString ToStr(const char *parent) 
    {
        csString str ; 
        return str ; 
    }
    

    //! Inverse of the ToStr function, returns 
    virtual int FromStr(const char *parent, const char *varstr) 
    {
        return 0 ; 
    }
} ;


//! Template used to define CS_VarMap entries
template <class T, int id> class CS_Var : public CS_VarObj
{
public:
    enum {
        FROMSTRERR      = 1, //!< Error loading data from string representation
    } ;

    //! Variable data being stored
    T v ; 

    //! This needs to be defined when a new variable is created
    CS_Var<T, id>() ; 

    CS_Var<T, id>(const char *varname, const T &value)
    {
        name = varname ; 
        v = value ; 
    }; 

    //! This needs to be defined when a new variable is created
    virtual ~CS_Var<T, id>() ; 

    //! This needs to be defined when a new variable is created
    CS_Var<T, id>(const CS_Var<T,id> &) ; 

    //! This needs to be defined when a new variable is created
    virtual CS_Var &operator=(const CS_Var<T,id> &) ; 

    
    //! Standard variable retrieval
    virtual T &Get() { return v; } ;

    //! Standard variable assignment
    virtual void Set(T vnew) { v = vnew; } ; 

    //! Set based on similar object, the pvo object must be of the same
    //! type or this fails with potential memory errors since pvo is cast
    //! to type T*  (\todo see if this is really needed, and if not remove it)
    virtual void Set(const CS_VarObj *pvo)
    {
        CS_Var<T,id> *pT = (CS_Var<T,id> *)pvo ; 
        v = pT->v ; 
    } ; 

    //! Returns the variable identifier initialized through the template declaration
    int VType() { return id ; } ; 

    //! Generate a string representation for this variable
    virtual csString ToStr(const char *parent) ;

    //! Inverse of the ToStr function, returns 
    virtual int FromStr(const char *parent, const char *varstr) ;
} ;




//! Map used to store collection of variable objects
typedef map<csString, CS_VarObj*>   CS_VarMap ; 

//! Iterator for CSVarMap 
typedef map<csString, CS_VarObj*>::iterator   CS_VarMapItr ; 


//! Data class to store and reload program variables to file
/*!
    \class CS_DataSet

    The CS_DataSet class is designed to simplify storing program variables 
    in a parameter file with a minimum of effort. The data parameters need 
    only be defined once, and then can be used directly within the program 
    as well as passed around as variables without the need of maintaining
    a bunch of routines to keep track of everything. The code below is an
    example of how you would use this class. The only real draw back is that 
    you have to continually specify the variable type when using the 
    CSDSSet and CSDSGet macros as well as the CSDSVarSet and  CSDSVarGet
    macros pairs. See the macro definitions on how to use these macros.

    The nice thing about this class is its ability to save the entire 
    data set with a single Write() call, and to retrieve the data set 
    with a Read() call. 

    \verbatim

    struct UserSubSubSet : public CS_VarSet
    {
        UserSubSubSet(const char *feedname)
        {
            SetName(csString(subsubname)) ; 
            v.SetVar(new CS_VarDouble("Parm1", 20.0)) ; 
            v.SetVar(new CS_VarDouble("Parm2", 100.0)) ; 
            v.SetVar(new CS_VarDouble("Parm3", 1500.6)) ; 
        }
    } ;

    struct UserSubSet : public CS_VarSet 
    {
        UserSubSet(const char *subname)
        {
            SetName(csString(subname)) ; 
            v.SetVar(new CS_VarInt("Var1", 10)) ; 
            v.SetVar(new CS_VarDouble("Var2", 5.0)) ; 
            v.SetVar(new CS_VarDouble("Var3", 2.0)) ; 
            v.SetVar(new UserSubSubSet("SubSub1")) ; 
            v.SetVar(new UserSubSubSet("SubSub2")) ; 
        }; 
    } ; 


    struct MainUserSet : public CS_DataSet
    {
        MainUserSet(const char *setname)  ; 
    } ;


    MainUserSet::MainUserSet(const char *setname)
    {
        SetName(setname) ; 
        SetVar(new CS_VarInt("MainVar1", 1)) ; 
        SetVar(new CS_VarDouble("MainVar2", 200.0)) ; 
        SetVar(new CS_VarDouble("MainVar3", 1000.0)) ; 
        SetVar(new ToolParms("Sub1")) ; 
    }


    int main(int argc, char **argv) 
    {
        MainUserSet p("Main") ;  

        printf("After initialization\n") ; 
        p.Write() ; 

        CSDSSet(p,"MainVar1", CS_VarInt,      2) ; 
        CSDSSet(p,"MainVar2", CS_VarDouble,   400.0) ; 
        CSDSSet(p,"MainVar3", CS_VarDouble,   2000.0) ; 

        printf("\nAfter change\n") ; 
        p.Write() ; 



        return 0 ; 
    }

    \endverbatim


    Since the character '.' is used as the name separator character when 
    defining subsets, do not use periods in your name definitions. You also
    can't use the '<', '/', and '>' characters in the names. 


 */
class CS_DataSet 
{
public:
    CS_VarMap vm ; 

    // This is required for the main top node set. 
    csString name ; 

    enum {
        XMLBUFLEN =  0x4000,
    } ; 


    CS_DataSet() {} ; 
    CS_DataSet(const char *setname) { name = setname ; } ; 

    ~CS_DataSet() ; 
    
    CS_DataSet(const CS_DataSet &ds)
    {
        vm = ds.vm ; 
    }

    CS_DataSet &operator=(const CS_DataSet &ds)
    {
        vm = ds.vm ; 
        return *this ; 
    }

    //! Extracts the parent part of the name from the string
    csString GetParentName(csString &varname) ; 

    //! Modify the name of the set
    void SetName(const char *setname) { name = setname ; } ; 

    //! Add the object to the set or change the value of object in set
    /*!
        \param pvo pointer to the variable object that is to be added to the set

        The desctruction of the CS_VarObj pointed to by pvo is handled
        by the CS_DataSet when ~CS_DataSet is called. Thus the pvo object
        must exist until after the data set is destroyed. The simplest way 
        to use this is to create the objects in the constructor of the 
        set using something similar to:

        \verbatim
        
        struct DataSubSet : public CS_VarSet
        {
            DataSubSet(const char *setname)
            {
                SetName(setname) ; 
                v.SetVar(new CS_VarString("StringParm", csString("default")) ; 
                v.SetVar(new CS_VarInt("intParm", 3)) ; 
                v.SetVar(new CS_VarDouble("doubleParm", -2.468)) ; 
                .
                .
                .
                .
            }
        } ;

        
        struct DataParms : public CS_VarSet
        {
            DataParms(const char *setname) 
            {
                SetName(setname) ; 
                v.SetVar(new CS_VarInt("FirstINTParm", 10)) ; 
                v.SetVar(new CS_VarInt("SecondINTParm", 15)) ; 
                v.SetVar(new CS_VarDouble("FirstDouble", 1.23456)) ; 
                v.SetVar(new DataSubSet("SubSet1")) ; 
                v.SetVar(new DataSubSet("SubSet2")) ; 
                .
                .
                .
                .
            }
        } ;

        \endverbatim

        Note that CS_VarSet is derived from CS_DataSet and should be used
        to define subset parameters sets so that they can be included in 
        other the parent set. The top node in the set tree (which you can
        picture having the same structure as a directory tree), should 
        be declared as a CS_DataSet. This way the name of the parent set
        is known to the read and write functions and can cascade down 
        the tree on Read and Write operations without being passed as
        a parameter. The example above demonstrates how sets can 
        be nested within one another. There is no limit to the level of 
        nesting that can occur, although it will take slightly longer to 
        find nested variables since the get routine must navigate it's way
        down into the various sets to find the parameter requested.
        Note, the example above also demonstrates a limitation in that 
        SubSet1 and SubSet2 will both be initialized with identical values
        as defaults. Upon doing a read from file there values will be 
        unique but the initial default requires that their values be
        the same. 
            
     */
    void SetVar(CS_VarObj *pvo) ;

    //! Retrieve the named object, returns NULL if object not defined
    /*!
        \param varname the fully qualified name of the object to be found
        \return pointer to the named object if found otherwise 0

        Make sure that you specify the fully qualified name of the variable
        when specifying the varname parameter. Thus for example, if there are
        several sub-parameters defined a name might look like:

        "Subset1.SubSubSet2.Var1" ; 

        CSDSGet(
            
     */
    CS_VarObj *GetVar(const char *varname) ; 


    //!
    /*!
        \param ln the line read from the XML file
        \param xmltype the xml parameter name extracted from the line
        \param value the value of the xml data for the parameter specified
        \return the length of value

        Expects to be passed a line of data with the following format:

            <parmname>parameter_value_data</parmname>

        If the two parmnames do not match then nothing is returned. The 
        variable \a value will be set to \a parameter_value_data.
        Any deviation in the format of the data results in an error. This
        class can not handle arbitrarily formatted XML data. Then 
        <name>namevalue</name> and <value>...</value> pairs must
        both be on the same line. The XML formatting is only used to allow
        other routines to process the same file if necessary, but the format
        expected by CS_DataSet can not be modifed.

        \todo Enhance so that arbitrary XML data is processed correctly

     */
    int ExtractXMLValue(csString &ln, csString &xmltype, csString &value) ; 


    //! Reads in the parameter set from the file specified. 
    /*! 
        \param filename The filename to load the data from 
        \return 0 if file is read successfully, -1 if a memory error
        occurs during the reading of the data, -2 if the file
        could not be opened, and -3 if the file name is NULL or invalid.
 
        If filename is not specified, then the set name is used as the 
        default filename for loading the data. If the set name is null
        and filename is specified, then the set name becomes filename.
     */
    virtual int Read(const char *filename) ; 

    virtual int Read(FILE *fp) ; 

    //! Write data to file, returns 0 on success
    /*!
        \param flname the name of the file to output to. 
     */
    virtual int Write(const char *flname) ;

    //! Write data to file, returns 0 on success
    /*!
        \param fp file pointer to write to.

        No file pointer moves are done, simply straight write operations, thus 
        you could open a file with data already in it, position the file pointer
        appropriately, and the data will simply be appended. The caller is 
        completely responsible for ensuring that fp points to a valid file
        upon entry, as well as closing the file pointer after the function 
        returns. If fp is null then data is written to stdout.
     */
    virtual int Write(const FILE *fp=0) ;


} ;


// Macros to simpify the get and set routines
#define CSDSSet(set, varname, VARTYPE, val)    ((VARTYPE *)(set).GetVar(varname))->Set(val) 
#define CSDSGet(set, varname, VARTYPE)    ((VARTYPE *)(set).GetVar(varname))->Get() 

#define CSDSVarSet(set, varname, VARTYPE, val)    ((VARTYPE *)(set).v.GetVar(varname))->Set(val) 
#define CSDSVarGet(set, varname, VARTYPE)    ((VARTYPE *)(set).v.GetVar(varname))->Get()


//! Define standard integer variable type
typedef CS_Var<int, CSPVT_INT> CS_VarInt ; 

//! Define standard double variable type
typedef CS_Var<double, CSPVT_DOUBLE> CS_VarDouble ; 

//! Define standard string variable type
typedef CS_Var<csString, CSPVT_STRING> CS_VarString ; 

// Define the self referencing variable for the data set
typedef CS_Var<CS_DataSet, CSPVT_DATASET>  CS_VarSet ;








//////////////////////////////////////////////////////////
// THIS IS OLD CODE TO SUPPORT THE srvrproc APPLICATION
//////////////////////////////////////////////////////////




enum CS_ParameterType {CS_INT, CS_DOUBLE, CS_CHAR, CS_STRING, CS_DATA} ;  


// This is where the actual data is stored. When using the generic 
// binary data type variable, make sure that you don't include 
// classes that include vptr type information, since on the reload
// these pointer values will certainly be incorrect. If you do
// need to save these variables, make sure you use a filter variable
// on the reload to transfer data to a properly initialized 
// class variable (with the proper _vtbl ptr)
struct CS_ParameterVar
{
    // anonymous union of all possible variables
    union {
        int    i ; 
        double d ; 
        char   c ; 
        char  *s ; 
        void  *v ; 
    } ; 
    csString name ; 
    CS_ParameterType type ; 
    int alloclen ; 

    // Initialize with name and default value
    CS_ParameterVar() 
    {
        v = 0 ; 
        alloclen = 0 ; 
    }; 

    ~CS_ParameterVar() 
    {
        if (alloclen > 0)
            free(v) ; 
    } ; 


    int operator==(CS_ParameterVar &varb)
    {
        if (name == varb.name)
            return 1 ; 
        return 0 ; 
    } ;

    int operator<(CS_ParameterVar &varb)
    {
        if (name < varb.name)
            return 1 ; 
        return 0 ; 
    } ;

    // Converts the value of the variable to a string
    void StringValue(csString &str) ; 
} ;


#define CS_AddParm(s,n,t)     s.AddParm(#n, t, &n, sizeof(n))
#define CS_GetParm(s,n)       s.GetParm(#n, &n)
#define CS_SetParm(s,n)       s.SetParm(#n, &n)

class CS_ParameterSet
{
public:
    csString name ; 
    CAVLTree<CS_ParameterVar> varTree ; 
    
    CS_ParameterSet()
    {
    }; 

    CS_ParameterSet(char *setname)
    {
        name = setname ; 
    }; 

    ~CS_ParameterSet() 
    {
    }; 
    

    void SetName(char *namestr)
    {
        name = namestr ; 
    } ;

    int InitParm(char *name, CS_ParameterType type, void *pdata, int size) ; 
    int AddParm(char *name, CS_ParameterType type, void *pdata, int size) ; 
    int SaveParms(const char *filename) ; 
    int LoadParms(const char *filename) ; 

    int SetParm(char *name, void *pnew) ; 
    int GetParm(char *name, void *pdata) ; 

} ;


#endif


