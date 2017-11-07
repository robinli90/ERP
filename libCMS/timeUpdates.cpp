// timeUpdates.cpp - functions related to routing run times.


#include "CMSBOMRTE.h"

int ValidPartCharacter(char c)
{
    char *ps = VALID_PARTCODES ; 
    while (*ps != c)
        ps++ ; 
    return (int)(*ps) ; 
}

int LoadPatternStrings(csStringList &strlist, csString &strs)
{
    int retcode = 0 ; 
    csString tok ; 
    strs.idx = 0 ; 
    do {
        tok = strs.NextToken(",") ; 
        if (tok.size())
        {   // TODO - Make sure each code is a valid string
            strlist.push_back(tok) ; 
        }
    } while (tok.size()) ;
    return retcode ; 
}

int LoadNCTimingMap(char *filename, RouteDataRecMap &timemap, FILE *fplog)
{
    FILE *fp = fopen(filename, "rt") ;
    if (!fp)
        return -1 ;

    int linenum = 0 ; 
    char buf[2048] ; 
    try {
        csString ln ; 
        bool done = false ; 

        while (fgets(buf, 2000, fp))
        {
            csString ln(buf) ; 
            ln.Trim() ; 
            linenum++ ; 

            if (ln.size() == 0 || ln[0] == '#')
            {   // Read the next line. 
                continue ; // skip comments and all non-condition lines
            }

            RouteDataRec rec ; 
            csString tok ; 
            ln.idx = 0 ; 

            // --------------------------------------------------------------
            //          FIELD 1:  SEQUENCE NUMBER
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ; 
            if (!tok.size())
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "ERR: time map file '%s' line# %d: "
                        "sequence number (field 1) missing\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; 
            }
            else
            {
                tok.Trim() ; 
                rec.seqno = atoi(tok.c_str()) ;
                if (!rec.seqno)
                {
                    fprintf(fplog, 
                        "ERR: time map file '%s' line# %d : "
                        "Sequence number (field 1) was zero, must be a valid number\n", 
                                filename, linenum) ; 
                    fflush(fplog) ; 
                }
            }

            // --------------------------------------------------------------
            //          FIELD 2:  CUSTOMER
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ; 
            tok.Trim() ; 
            if (tok.size() != 1)
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "ERR: time map file '%s' line# %d: "
                        "part type code must be a single character (field 2) missing\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; 
            }
            else if (!ValidPartCharacter(tok[0]))
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "ERR: time map file '%s' line# %d: "
                        "part type not one of F,M,P,B,k,L,S,R,I,A,C,or T (field 2) missing\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; 
            }
            else
            {
                rec.partCode = tok[0] ; 
            }

            // --------------------------------------------------------------
            //          FIELD 3:  CMS DEPT code
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ; 
            tok.Trim() ; 
            if (!tok.size())
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "ERR: time map file '%s' line# %d: "
                        "DEPT (field 3) missing, check your field separators ';'\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; 
            }
            else
            {
                rec.dept = tok ; 
            }


            // --------------------------------------------------------------
            //          FIELD 4:  CMS RESOURCE code
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ;
            tok.Trim() ;
            if (!tok.size())
            {
                if (fplog)
                {
                    fprintf(fplog,
                        "ERR: time map file '%s' line# %d: "
                        "RESOURCE (field 4) missing, check your field separators ';'\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; 
            }
            else
            {
                rec.resource = tok ; 
            }

            // --------------------------------------------------------------
            //          FIELD 5:  PREFIX type strings for the time file
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ;
            tok.Trim() ;
            if (tok.size())
            {
                if (LoadPatternStrings(rec.preList, tok)) 
                {   // Error loading characters pattern strings
                    if (fplog)
                    {
                        fprintf(fplog,
                            "ERR: time map file '%s' line# %d: "
                            "PREFIX (field 5) problem, must be a comma separated list of strings.\n", 
                                filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
            }


            // --------------------------------------------------------------
            //          FIELD 6:  POSTFIX type strings for the time file
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ;
            tok.Trim() ;
            if (tok.size())
            {
                if (LoadPatternStrings(rec.postList, tok)) 
                {   // Error loading characters pattern strings
                    if (fplog)
                    {
                        fprintf(fplog,
                            "ERR: time map file '%s' line# %d: "
                            "SUFFIX (field 6) problem, must be a comma separated list of strings.\n", 
                                filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
            }

            if (rec.preList.size() == 0 && rec.postList.size() == 0)
            {   // At least one of these must be defined. 
                if (fplog)
                {
                    fprintf(fplog,
                        "ERR: time map file '%s' line# %d: "
                        "One of PREFIX or SUFFIX string sets must be defined.\n", 
                            filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ;
            }

            // --------------------------------------------------------------
            //          FIELD 7:  Number of digits
            // --------------------------------------------------------------
            tok = ln.NextToken(";") ;
            tok.Trim() ;
            rec.ndigits = 0 ;
            if (tok.size())
            {
                rec.ndigits = atoi(tok.c_str()) ;
            }

            // Now have to loop through and load all the possible routing
            // details for this condition.
            // We only want data records that actually contain records. If a condition
            // has no data ignore it.
            csString key ;
            key.FormatSz(64, "%c%d", rec.seqno, rec.partCode) ;
            timemap.insert(pair<csString, RouteDataRec>(key, rec)) ;

        } // end main while loop. 
    }
    catch (...)
    {   // Shouldn't get here
        if (fplog)
        {
            fprintf(fplog,
                "ERR: unkown error reading time map file '%s' line# %d\n",
                    filename, linenum) ;
            fflush(fplog) ; 
        }
    }

    return (int)timemap.size() ;
}

int GetNCTimeFromFile(csString &filedir, char *filename, double &tmins)
{
    csString pathname = AddFile2Path(filedir, filename) ; 
    FILE *fp = fopen(pathname.c_str(), "rt") ; 
    if (!fp)
        return -1 ; 

    char buf[256] ; 
    fgets(buf, 200, fp) ; 
    fclose(fp) ; 

    csString ln(buf) ; 
    ln.Trim() ; 
    if (ln.size() == 0)
        return -2 ; // nothing in the file.

    tmins = atof(ln.c_str()) ; 
    return 0 ; // OK
}

char *ExtractNumber(char *pstr, csString &num)
{
    while (pstr && !isdigit(*pstr) && 
           *pstr != '-' && *pstr != '.')
    {
           pstr++ ; 
    }

    while (pstr && 
            (isdigit(*pstr) || *pstr == '-' || *pstr == '.'))
    {
        num += *pstr++ ; 
    }

    return pstr ; 
}


char *ExtractInt(char *pstr, csString &num)
{
    if (pstr && *pstr == '-')
        num += *pstr++ ; 
    while (pstr && !isdigit(*pstr))
           pstr++ ; 

    while (pstr && isdigit(*pstr))
        num += *pstr++ ; 

    return pstr ; 
}


int RouteDataRec::TimeFileMatch(csString &jobnumstr, char *filename)
{
    // See if the file matches one of the patterns defined for 
    // this time map record.
    csString flstr(filename) ; 
    csString flnums ; 
    char *pszsuf = ExtractInt(filename, flnums) ; 
    csString suf(pszsuf) ; 

    if (flnums.size() == 0)
        return 0 ; // no number in the filename so pointless to proceed. 

    if (jobnumstr.Right(ndigits) != flnums.Right(ndigits))
        return 0 ;  // the job numbers don't match

    unsigned int i ; 
    for (i=0; i < preList.size(); i++)
    {
        if (preList[i].ToUpper() == flstr.Left(preList[i].size()).ToUpper())
        {   // Then this is a match of the string portion. Now move to the
            // first digit in both strings and see if the proper number
            // of trailing digits match. 
            return 1 ; // found a match
        }
    }

    for (i=0; i < postList.size(); i++)
    {
        if (postList[i].ToUpper() == suf.Left(postList[i].size()).ToUpper())
        {   // Then this is a match of the string portion. Now move to the
            return 1 ; // found a match
        }
    }

    return 0 ; // no match 
} 




int CMSBOMRTE::GetJobNumberData(CMSOrder &ord, RouteDataRecMapItr &rmi)
{
    // Find the job/work order in the jobvec that matches this timemap 
    unsigned int i ; 
    for (i=0; i < ord.jobvec.size(); i++)
    {   // RouteDataRec
        if (rmi->second.partCode == ord.jobvec[i].partcode)
        {
            return i ; 
        }
    }
    return -1 ; 
}


// Load all the UG NC runtimes for this job.
int CMSBOMRTE::LoadNCTimes(CMSOrder &ord)
{
    RouteDataRecMapItr rmi ; 

    // First reset all the actual run time values.
    for (rmi=timemap.begin(); rmi != timemap.end(); rmi++)
    {
        rmi->second.actualRunTime = -1.0 ; // define as uninitialized. 
        rmi->second.bRunTimeProcessed = false ; 
    }

    // Go through all the time map definitions and scan the directory 
    // for time files. 
    csString timedir(NCTimesDir) ; 
    csString jobNumStr ; 
    jobNumStr.FormatSz(16, "%d", atoi(ord.orderNumber.c_str())) ; 
    jobNumStr = jobNumStr.Right(ncFileDigits) ; // we only need to look at the 
    // designated number of digits. 

    csString filepat = "*" + jobNumStr + "*" ; 
    csString searchPat = AddFile2Path(timedir, filepat) ; 

    unsigned int fileCount = 0 ; 
    
    RouteDataRec *prdrec = 0 ; 

    WIN32_FIND_DATA ff ;
    HANDLE hFind;
    hFind = FindFirstFileA(searchPat.c_str(), &ff) ;
    if (hFind != INVALID_HANDLE_VALUE) 
    {   // Load the file times
        do {
            for (rmi=timemap.begin(); rmi != timemap.end(); rmi++)
            {   
                prdrec = &(rmi->second) ; 
                if (prdrec->TimeFileMatch(ord.orderNumber, ff.cFileName))
                {
                    double tmins = 0.0 ; 
                    if (!GetNCTimeFromFile(timedir, ff.cFileName, tmins))
                    {
                        fileCount++ ; 
                        if (prdrec->actualRunTime < 0)
                            prdrec->actualRunTime = 0.0 ; // initialize it
                        // The divide by 60 is to convert minutes into hours
                        prdrec->actualRunTime += (tmins / 60.0) ; 
                    }
                }
            }
        }   while (FindNextFile(hFind, &ff)) ;
            
        FindClose(hFind);
    }

    return fileCount ; 
}
