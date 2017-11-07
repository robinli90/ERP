
#pragma once

/* 

BOM Flat File record definition

Flush = back flush 
Draw = draw from stockroom 
Oper = operation 1=No, 2=Create, 3=Create and Release

WORK       R A S  L                               U  Qty  TAF S D S O Temp
ORDER      e c e  I                               n  Per  yll tRr cPp Work
NUMBER     c t q  N    Material             Qty   i       plu ooa rce Ord#                            THIS AREA NOT USED IN THE BOM RECORD - ALL BLANKS
           I i #  E     Part#                     t       eos cow atr
           D n    #                               s        ch km  p 
----------XXX-XXX----XXXXXXXXXXXXXXXXXXXX--------XXX------X-X---X---X----------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
001000028 BOM20400001HD 9 X 5 PLATE      00016700IN 000100RYYPRDY0001                                                                                                                    

                                                                                                   1         1         1         1`        1         1         1         1         1
         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8  
12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345

0000059   BOM21800001HD 9 X 5 PLATE      00010000EA 000100RYYPRDY0003TMP101                                                                                                              
TMP101    BOM20400001H-13 9 DIA          00012500IN 000100RYYPRDY0001                                                                                                                    
0000059   BOM21800002HD 9 X 5 MANDREL    00010000EA 000100RYYPRDY0003TMP102                                                                                                              
TMP102    BOM20400001H-13 9 DIA          00035000IN 000100RYYPRDY0001                                                                                                                    
0000059   BOM21800003HD 9 X 5 BACKER     00010000EA 000100RYYPRDY0003TMP103                                                                                                              
TMP103    BOM204000012714 9 DIA          00011500IN 000100RYYPRDY0001                                                                                                                    



RTE Flat File record definition. 

WORK       R A S  P D Res   O  Setup   Sched.  Cost   T E  Run    CS # # Lag     xfer   R Burden  S Vendor    OS Description                Freight    Freight    O/S        Based  Est
ORDER      e c e  L E ource P   Std.    Run    Run    y f  Qty    ri M M Time    batch  p Rate    t                                          Out        In        Cost        On    Time
NUMBER     c t q  A P       E           Std.   Std.   p f         ez E A Hours          t Factor  a                                          Cost       Cost                  Qty
           I i #  N T       R                         e c         we N C                P         t                                           
           D n    T                                     y              H                t                                                    
----------XXX-XXX---XX-----XXX--------XXXXXXXX--------X---XXXXXXXX--XX--XXXXXXXX--------X---------X----------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-----------XXXXXXXXXXX-----------XXXXXXXX-----
001000003 RTE1084001EDS10  EF 000000000000050000000500C100000000010001010000000000000001N000000000N                                        0000000000000000000000000000000000000000000000
                                                                                                   1         1         1         1`        1         1         1         1         1
         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8  
12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
0000049   RTE1200001INEMPL INS000000000000010000000100C100000000010001010000000000000001Y000000000C                                        0000000000000000000000000000000000000000000000
TMP01     RTE1200001INEMPL INS000000000000010000000100C100000000010001010000000000000001Y000000000C                                        0000000000000000000000000000000000000000000000
TMP1      RTE1190001PNEMPL PN 000000000000010000000100C100000000010001010000000000000001N000000000N                                        0000000000000000000000000000000000000000000000
TMP1      RTE3050001L1L8   TUR000000000000010000000100C100000000010001010000000000000001N000000000N                                        0000000000000000000000000000000000000000000000

For RTE delete operations only need to specify, SEQ#, PLANT, DEPT (may not even need DEPT) the RESOURCE and OPERATION fields can be 
blank and the delete operation will still reference the correct record. 


*/
#include <vector>
using namespace std;


// The fields size (number of characters) for the job number in the RTE and BOM
// records in the flat file interface for Solarsoft. 
#define FFTMPSZ 10
#define FFTMPPREFIX       "ZZTMPYY"


struct CMSJob ;
struct CMSOption ;
struct CMSOrder ; 

extern const char* BASERTE ;
extern const char *BASEBOM ;

#define ACTION_ADD      '1'
#define ACTION_UPDATE   '2'
#define ACTION_DELETE   '3'

// Copies the src string to dst for a maximum of count characters. If 
// src is less than count characters then dst is filled with blanks until
// count characters are copied. There is no terminating character. 
void StrCpyBlankFill(char *dst, const char *src, int count) ; 


// Copies starting on the right and moves left to fill the characters
// and then pads with spaces until the first character position in 
// dst is filled. 
void StrCpyBlankFillRight(char *dst, const char *src, int count) ;


// The integer value is right justify into the string position at dst. The final
// output value is count characters long. No trailing characters are added and 
// there is no terminator. The value is padded in the front with 0's
void ZeroPadInt(char *dst, int val, int count) ; 

// The floating point value is zero padded on the left and right based on the 
// number of integer characters and the decimal characters. The decimal is not
// output and is assumed to come exactly after the intcount position. 
void ZeroPadDbl(char *dst, double val, int intcount, int deccount) ; 

#define BOMRTE_LENGTH   187

struct CMSRTE
{
    char ffstr[190] ; 
    void Init() { memcpy(ffstr, BASERTE, 187) ; }

    void SetOrderNumber(char *str)      { StrCpyBlankFill(ffstr, str, 10) ; }

    void SetAction(char c)              { ffstr[13] = c ; } 
    void SetAction(int n)               
    { 
        switch(n)
        {
            case ROUTE_ADD : 
                ffstr[13] = ACTION_ADD ; 
                break ; 
            case ROUTE_MOD : 
                ffstr[13] = ACTION_UPDATE ; 
                break ; 
            case ROUTE_DEL : 
                ffstr[13] = ACTION_DELETE ; 
                break ; 
        }
    }

    void SetSeqNum(int n)               { ZeroPadInt(ffstr + 14, n, 3) ; } 

    void SetPlant(char *str)            { StrCpyBlankFill(ffstr + 17, str, 3) ; }

    void SetDept(char *str)             { StrCpyBlankFill(ffstr + 20, str, 2) ; }

    void SetResource(char *str)         { StrCpyBlankFill(ffstr + 22, str, 5) ; }

    void SetOperation(char *str)        { StrCpyBlankFill(ffstr + 27, str, 3) ; }

    void SetRunStandard(double r)       { if (r < 0.01) r = 0.011 ;  
                                          ZeroPadDbl(ffstr + 38, r, 6, 2) ; 
                                          ZeroPadDbl(ffstr + 46, r, 6, 2) ; }       

    //! Is it a reporting point Y N
    void SetReporting(char c)           { ffstr[88] = c ; } 

    //! N=new, A=active, C=complete
    void SetStatus(char c)              { ffstr[98] = c ; } 

    void CRLF() { ffstr[185] = '\r'; ffstr[186] = '\n' ; }
    
    //! Prepare RTE output record data
    /*!
        \param ord  the complete order vector being processed
        \param ijob  index into the jobvec list
        \param iopt  index into the ordvec list
        \param rdr  the routing update data record
        \param rCurDB the actual METHDR or CJOBDR record data
        \param pUGTime if not null then an updated run time

        This goes through each rv record searching for a match, and when it
        finds one, that data is used to set the member variable parameter 
        values. If no matching rv record is found, then this returns 0 
        and does nothing. If it returns 1, then this record is ready to 
        write out to the flat file for processing. 
     */
    void SetRoutingParms(CMSOrder &ord, int ijob, int iopt, 
                         RouteDataRec &rdr, RouteDataRec &rCurDB, double *pUGTime) ; 
    
    //! Write this RTE record out to the flatfile. 
    size_t Write(FILE *fp) 
    {
        size_t bwrt = fwrite(ffstr, 1, BOMRTE_LENGTH, fp) ; 
        fflush(fp) ; 
        return bwrt ; 
    } 
} ; 


struct CMSBOM
{
    char ffstr[190] ; 

    void Init() { memcpy(ffstr, BASEBOM, 187) ; }

    void SetOrderNumber(const char *str) { StrCpyBlankFill(ffstr, str, 10) ; }

    void SetAction(char c)              { ffstr[13] = c ; } 

    void SetSeqNum(int n)               { ZeroPadInt(ffstr + 14, n, 3) ; } 

    void SetLineNum(int n)              { ZeroPadInt(ffstr + 17, n, 4) ; } 

    void SetMaterial(const char *str)   { StrCpyBlankFill(ffstr+21, str, 20) ; }

    void SetQty(int n)                  { ZeroPadDbl(ffstr + 41, (double)n, 4, 4) ;
                                          StrCpyBlankFill(ffstr + 49, "EA", 3) ; }  

    void SetQty(double d, char *units)  { ZeroPadDbl(ffstr + 41, d, 4, 4) ; 
                                          StrCpyBlankFill(ffstr + 49, units, 3) ; }  

    void SetOper(char c)                { ffstr[68] = c ; } 

    void SetTempWork(const char *str)   { StrCpyBlankFill(ffstr + 69, str, 10) ; }  

    void SetJobParms(CMSJob &job) ; 

    void CRLF() { ffstr[185] = '\r'; ffstr[186] = '\n' ; }

    size_t Write(FILE *fp) {return fwrite(ffstr, 1, BOMRTE_LENGTH, fp) ; } 
} ; 


/*
class CJobRoutingStep;
class CMethodDR;

class CRTERecord
{
public:
    CRTERecord(void);
    ~CRTERecord(void);

    void InitRecord(void);

    void CreateDeleteRecord(const char *szWorkOrder, int nSequence);

    void Load(const char * wordid, const CJobRoutingStep &job);
    void Load(const char *szWordid, const CMethodDR &dr);

    std::string GetFlatFileFormat(void);

    char workorder[10];             // must be existing work order
private:
    char recordid[3];               // would be "RTE" or "BOM"
public:
    char action;                    // 1: add, 2: udpate, 3: delete
    int sequence;                   // 3 bytes: 3 integers and 0 decimal places, no decimal point. like:  001

    char plant[3];                  // must be the same plant as the work order
    char department[2];             // must be valid department under the plant
    char resource[5];               // must be valid resource under the department
    char operation[3];              // must be valid operation code under the plant
    float setupstandard;            // 8 bytes: 6 integers and 2 decimal places, no decimal point
    float schedulerunstandard;      // 8 bytes: 6 integers and 2 decimal places, no decimal point:  Don't know just set them to 1 for now. 
    float costrunstandard;          // 8 bytes: 6 integers and 2 decimal places, no decimal point:  Don't know just set them to 1 for now. 
    char standardtype;              // must be A(pieces per hour) or B(hours per 100 pieces) or C(total hours regardless of quantity)
    int efficiency;                 // 3 bytes: 3 integers and 0 decimal places, no decimal point. like:  001
    int runquantity;                // 8 bytes: 8 integers and 0 decimal places, no decimal point. like:  00000001
    int crewsize;                   // 2 bytes: 2 integers and 0 decimal places, no decimal point. like:  01
    int men;                        // 2 bytes: 2 integers and 0 decimal places, no decimal point. like:  01
    int machines;                   // 2 bytes: 2 integers and 0 decimal places, no decimal point. like:  01
    float lagtime;                  // 8 bytes: 6 integers and 2 decimal places, no decimal point
    int transferbatch;              // 8 bytes: 8 integers and 0 decimal places, no decimal point. like:  00000001
    char reportingpoint;            // must be Y(yes) or N(no), and must be Y if OS department
    float burdenratefactor;         // 9 bytes: 5 integers and 4 decimal places, no decimal point, no validation rule
    char status;                    // must be A(Active) or N(New) or C(Complete)
    
    char vendor[10];                // Optional, applicable only for OS department
    char osdescription[30];         // If defined(not blanks/zeros), must be OS department
    float freightoutcost;           // If defined(not blanks/zeros), must be OS department 11 bytes: 6 integers and 5 decimal places, no decimal point
    float freightincost;            // If defined(not blanks/zeros), must be OS department 11 bytes: 6 integers and 5 decimal places, no decimal point
    float oscost;                   // If defined(not blanks/zeros), must be OS department 11 bytes: 6 integers and 5 decimal places, no decimal point
    int baseonquantity;             // If defined(not blanks/zeros), must be OS department 11 bytes: 8 bytes: 8 integers and 0 decimal places, no decimal point. like:  00000001
    float estimatedtime;            // If defined(not blanks/zeros), must be OS department 5 bytes: 3 integers and 2 decimal places, no decimal point
};

typedef vector<CRTERecord> CRTERecordVec;

class CJobMaterial;
class CMethodDM;

class CBOMRecord
{
public:
    CBOMRecord(void);
    ~CBOMRecord(void);

    void InitRecord(void);

    void CreateDeleteRecord(const char *szWorkOrder, int nSequence, int nLine);

    void Load(const char * szWorkid, int nSeq, const CJobMaterial &jobm);

    void Load(const char * szWorkid, const CMethodDM &dm);

    std::string GetFlatFileFormat(void);

    char workorder[10];             // must be existing work order
private:
    char recordid[3];               // would be "RTE" or "BOM"
public:
    char action;                    // 1: add, 2: udpate, 3: delete
    int sequence;                   // 3 bytes: 3 integers and 0 decimal places, no decimal point
    int line;                       // 4 bytes: 4 integers and 0 decimal places, no decimal point
    char materialpart[20];          // must be valid part number
    float quantity;                 // 8 bytes: 4 integers and 4 decimal places, no decimal point, must be greater than zero
    char unit[3];                   // must be valid unit of measure for the material part
    float quantityper;              // 6 bytes: 4 integers and 2 decimal places, no decimal point, must be greater than or equal to zero
    char timetype;                  // R-Requirement or B-ByProduct
    char allocate;                  // Y-Yes or N-No
    char backflush;                 // Y-Yes or N-No
    char stockroom[3];              // Stock room will never be used.
    char drawfromsrd;               // Draw-From Stockroom as defined, Y-Yes or N-No
    float scrap;                    // 3 bytes: 2 integers and 1 decimal places, no decimal point
    char createnewfirm;             // 1-No or 2-CreateOnly or 3-Create&Release
    char tempworkorder[10];         // 
private:
    //char filler[106];             // Not Used
    enum { enFillerSize = 106 };
};

typedef vector<CBOMRecord> CBOMRecordVec;

class CJob;

class CBRFlatFile
{
public:
    CBRFlatFile(void);
    ~CBRFlatFile(void);

    enum enFileType
    {
        enBOM = 1,
        enRTE
    };

    void Load(const CJob &job);

    bool OutputToFile(const char *szFileName, enFileType enType);
    
    CRTERecordVec rterecords;
    CBOMRecordVec bomrecords;
};

*/
