// CMSrouting.cpp - support functions for routing updates to solarsoft

#include "CMSBOMRTE.h"


RouteDataRec::RouteDataRec()
{
    command = 0 ; // 0=ROUTE_DEL, 1=ROUTE_MOD, 2=ROUTE_ADD
    // This is the actual solarsoft routing operation data
    seqno = 0 ; 
    linenum = 0 ; // not really used
    runstd = 0.0 ; // defined in hours
    fut5 = 0.0 ; // not sure what this is for. 

    partCode = 0 ; 
    ndigits = 0 ; 
}

int GetToken(csString &ln, csString &tok)
{
    if (ln.idx >= ln.size())
        return -1 ; // no more tokens
    tok = ln.NextToken(";") ; 
    tok.Trim() ; 
    return 0 ; 
}



int LoadRoutingCondition(csString &ln, RoutingCondRec &rec, FILE *fplog, char *filename, int linenum)
{
    csString tok ; 

    if (ln[0] == '!')
    {
        rec.inverted = true ; 
        ln.idx = 1 ; // skip over the ! character
    }

    // --------------------------------------------------------------
    //          FIELD 1:  FEATURE
    // --------------------------------------------------------------
    if (GetToken(ln, tok))
        return -101 ; // no more data in the input line 
    if (!tok.size())
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERR: routing record file '%s' line# %d: "
                "feature,option definition (field 1) missing\n", filename, linenum) ; 
            fflush(fplog) ; 
        }
        return -10 ; 
    }
    else
    {
        int res = rec.ParseFeatureOption(tok) ;
        if (res)
        {
            if (fplog)
            {
                fprintf(fplog, 
                    "ERR: routing record file '%s' line# %d (%02x): "
                    "feature,option definition (field 1) defined incorrectly, must be 'feat,opt'  '*,opt'  or 'opt'\n", 
                        filename, linenum, res) ; 
                fflush(fplog) ; 
            }
            return -11 ; 
        }
    }

    // --------------------------------------------------------------
    //          FIELD 2:  CUSTOMER
    // --------------------------------------------------------------
    if (GetToken(ln, tok))
        return -101 ; // no more data in the input line 
    if (!tok.size())
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERR: routing record file '%s' line# %d: "
                "customer definition (field 2) missing\n", filename, linenum) ; 
            fflush(fplog) ; 
        }
        return -10 ; 
    }
    else
    {
        rec.customer = tok ; 
        if (rec.customer[0] == '*' && rec.customer.size() > 1 && fplog)
        {
            fprintf(fplog, 
                "WARNING: routing file '%s' line# %d: "
                " customer field wildcard * should not have any other characters, remaining characters ignore, did you forget the ';' field separator?\n",  
                filename, linenum ) ; 
            fflush(fplog) ; 
        }
        else if (rec.customer.size() > 8 && fplog)
        {
            fprintf(fplog, 
                "WARNING: routing file '%s' line# %d: "
                " customer field greater than 8 characters\n",  
                filename, linenum ) ; 
            fflush(fplog) ; 
        }
    }

    // --------------------------------------------------------------
    //          FIELD 3:  Diameters
    // --------------------------------------------------------------
    if (GetToken(ln, tok))
        return -101 ; // no more data in the input line 
    if (!tok.size())
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERR: routing record file '%s' line# %d: "
                "diameter (field 3) missing, check your field separators ';'\n", filename, linenum) ; 
            fflush(fplog) ; 
        }
        return -10 ; 
    }
    else
    {
        switch(rec.ParseDiams(tok))
        {   
            case 0 :
                if (fplog)
                {
                    fprintf(fplog, 
                        "WARNING: routing file '%s' line# %d: "
                        " diameter range field is incorrect.\n",  
                        filename, linenum ) ; 
                    fflush(fplog) ; 
                }
                break ; 
            default:
                break ; 
        }
    }


    // --------------------------------------------------------------
    //          FIELD 4:  Part characters
    // --------------------------------------------------------------
    if (GetToken(ln, tok))
        return -101 ; // no more data in the input line 
    if (!tok.size())
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERR: routing record file '%s' line# %d: "
                "part (field 4) missing, check your field separators ';'\n", filename, linenum) ; 
            fflush(fplog) ; 
        }
        return -10 ; 
    }
    else
    {
        rec.parts = tok ; 
    }

    // --------------------------------------------------------------
    //          FIELD 5:  Optional CONTINUE indicator
    // --------------------------------------------------------------
    if (!GetToken(ln, tok))
    {
        tok.ToUpper() ; 
        if (tok.size() && tok == "CONTINUE")
        {   // Then this is a non-terminating condition 
            rec.bNonTerminating = true ; 
        }
        else
        {
            if (fplog)
            {
                fprintf(fplog, 
                    "ERR: routing record file '%s' line# %d: "
                    "Expecting CONTINUE (field 5), to define a terminating condition omit"
                    " the CONTINUE parameter completely and not trailing ; field separateor.\n", 
                            filename, linenum) ; 
                fflush(fplog) ; 
            }
            return -11 ; 
        }
    }
    
    // OK - everything worked. 
    return 0 ; // return the standard recordType 
}

int LoadSingleCondition(csString &ln, RoutingCondRec &rec, FILE *fplog, char *filename, int linenum)
{
    csString tok ; 
    if (GetToken(ln, tok))
        return -110 ; 

    int i ; 

    switch(atoi(tok.str+1))
    {
        case 1 :    
            if (GetToken(ln, tok))
                return -111 ; 

            for (i=0; i < tok.size(); i++)
            {
                if (!ValidPartCharacter(tok[i]))
                    return -112 ; 
            }
            rec.parts = tok ; 
            return 1 ; // this is the single sub part recordType
        case 2 :
            // This special condition simply runs against all parts using a 
            // hard coded priority. TODO - could add a user defined priority field 
            // here. 
            rec.parts = "*" ; 
            return 2 ; 
        default : 
            if (fplog)
            {
                fprintf(fplog, 
                    "ERR: routing record file '%s' line# %d: "
                    "invalid special record type, only #1 is allowed right now.\n", 
                        filename, linenum) ; 
                fflush(fplog) ; 
            }
            break ; 
    }

    return -120 ; // Return abort condition. 
}

int LoadRoutingTable(char *filename, 
                     RoutingCondRecVec &rcondvec, 
                     RoutingCondRecVec &rsingvec, 
                     RoutingCondRecVec &rnomastvec, 
                     FILE *fplog)
{
    FILE *fp = fopen(filename, "rt") ;
    if (!fp)
        return -1 ;

    int linenum = 0 ; 
    char buf[2048] ; 
    try {
        csString ln ; 
        bool done = false ; 

        while (!done)
        {
            if (ln.size() == 0 || ln[0] == '#' || ln[0] != '[')
            {   // Read the next line. 
                buf[0] = 0 ; 
                if (!fgets(buf, 2000, fp))
                    done = true ; 
                linenum++ ; 
                ln = buf ; 
                ln.Trim() ; 
                continue ; // skip comments and all non-condition lines
            }

            RoutingCondRec rec ; 
            csString tok ; 
            ln.idx = 0 ; 
            // Strip off the enclosing [ ] brackets
            ln.TrimLeft(1) ; 
            if (ln.Right(1) != "]")
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "ERR: Reading '%s' line# %d: "
                        "Condition missing enclosing ']' right bracket\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
                continue ; // invalid condition
            }
            else
            {
                ln.TrimRight(1) ; 
            }
            ln.Trim() ; 

            /*  This is the record type specifier. 
                  0 - standard and inverted normal records
                  1 - single subpart record rules. 
                Other types are not allowed for now. 
             */

            int recordType = -1 ; 

            // --------------------------------------------------------------------------
            //    LOAD RECORD CONDITION TYPE 
            // --------------------------------------------------------------------------
            if (ln[0] == '~')
            {   // This is one of the custom record definitions 
                recordType = LoadSingleCondition(ln, rec, fplog, filename, linenum) ;
            }
            else 
            {   // Then this is a standard record
                recordType = LoadRoutingCondition(ln, rec, fplog, filename, linenum) ; 
            }

            if (recordType < -99)
                throw recordType ; 

            if (recordType < 0 || recordType > 2)
                continue ; // some type of error occured

            // --------------------------------------------------------------------------
            //    Now have to loop through and load all the possible routing 
            //    details for this condition. 
            //       LOAD RTE CHANGES FOR THIS CONDITION
            // --------------------------------------------------------------------------

            do {

                buf[0] = 0 ; 
                if (!fgets(buf, 2000, fp))
                {
                    done = true ; 
                    break ; 
                }
                linenum++ ; 
                ln = buf ; 
                ln.Trim() ; 
    
                if (ln[0] == '[')
                {   // Then this is a new condition definition record so exit 
                    // out of the inner loop and continue on the outer loop
                    break ; 
                }

                if (ln.size() == 0 || ln[0] == '#')
                    continue ; // skip blank lines and comments 

                RouteDataRec datarec ; 

                ln.idx = 0 ; // initialize the token scanning position. 

                // --------------------------------------------------------------
                //          FIELD 5:  Command
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "command (field 5) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    tok.ToUpper() ; 
                    
                    if (tok == "ADD")
                        datarec.command = ROUTE_ADD ; 
                    else if(tok == "DEL")
                        datarec.command = ROUTE_DEL ; 
                    else if(tok == "MOD")
                        datarec.command = ROUTE_MOD ; 
                    else
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "command (field 5) must be one of 'ADD', 'MOD', or 'DEL' \n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                }


                // --------------------------------------------------------------
                //          FIELD 6:  Seq#
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "seq# (field 6) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.seqno = atoi(tok.c_str()) ; 
                }


                // --------------------------------------------------------------
                //          FIELD 7:  Dept.
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Department (field 7) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.dept = tok ; 
                }

                // --------------------------------------------------------------
                //          FIELD 8:  Resource.
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Resource (field 8) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.resource = tok ; 
                }

                // --------------------------------------------------------------
                //          FIELD 9:  Operation.
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Operation (field 9) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.operation = tok ; 
                }

                // --------------------------------------------------------------
                //          FIELD 10:  Run standard
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Run standard (field 10) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.runstd = atof(tok.c_str()) ; 
                }

                // --------------------------------------------------------------
                //          FIELD 11:  Status
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Status (field 11) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.status = tok ; 
                }

                // --------------------------------------------------------------
                //          FIELD 12:  Reporting
                // --------------------------------------------------------------
                if (GetToken(ln, tok))
                    throw -100 ; // no more data in the input line 
                if (!tok.size())
                {
                    if (fplog)
                    {
                        fprintf(fplog, 
                            "ERR: routing record file '%s' line# %d: "
                            "Reporting (field 12) missing, check your field separators ';'\n", filename, linenum) ; 
                        fflush(fplog) ; 
                    }
                    continue ; 
                }
                else
                {
                    datarec.reporting = tok ; 
                }

                rec.drecs.push_back(datarec) ; 
            } while (!done) ; 

            // We only want data records that actually contain records. If a condition
            // has no data ignore it. 
            if (rec.drecs.size() > 0)
            {
                switch(recordType)
                {
                    case 0 : 
                        rcondvec.push_back(rec) ; 
                        break ; 
                    case 1 :
                        rsingvec.push_back(rec) ; 
                        break ; 
                    case 2 : 
                        rnomastvec.push_back(rec) ; 
                        break ; 
                    default:
                        if (fplog)
                        {
                            fprintf(fplog, 
                                "ERR: routing record file '%s' above line# %d: "
                                "Unkown record type, condition ignored.\n", filename, linenum) ; 
                            fflush(fplog) ; 
                        }
                        break ; 
                }
            }
            else
            {
                if (fplog)
                {
                    fprintf(fplog, 
                        "WARNING: routing record file '%s' line# %d: "
                        "Condition without and routing data records, condition ignored.\n", filename, linenum) ; 
                    fflush(fplog) ; 
                }
            }
        } // end main while loop. 
    }
    catch (int err)
    {
        if (fplog)
        {
            fprintf(fplog, 
                "ERR: (%d) routing record file '%s' line# %d: no token\n", 
                    err, filename, linenum) ; 
            fflush(fplog) ; 
        }
    }

    return (int)rcondvec.size() ; 
}



// The numbers cannot be neagtive since the '-' character is used
// to separate a range, indicating from-to value pair. 
int RoutingCondRec::ParseDiams(csString &tok)
{
    int retcode = 0 ;

    diaFrom = 0 ; 
    diaTo = 0 ; 

    tok.Trim() ; 

    csString n1, n2 ; 
    n1 = tok.NextToken("-", 0) ; 
    n2 = tok.NextToken("-") ; 

    n1.Trim() ; 
    n2.Trim() ; 

    if (n1 == "*")
    {
        diaTo = 9999.0 ; // include evrything possible
        retcode = 0x04 ; 
    }
    else if (n1.size() || n2.size())
    {   // Normal processing 
        double x ; 
        char *ps ; 

        if (n1.size())
        {
            x = atof(n1.c_str()) ; 
            ps = CS_SkipFloat(n1.str) ; 
            csString units ; 
            if (*ps)
            {   // Then something trails the number
                units = ps ; 
                units.Trim() ; 
            }

            diaFrom = x ; 
            if (units.size())
            {
                units.ToUpper() ; 
                if (units[0] == 'I')
                    diaFrom *= 25.4 ; 
            }
            else
            {   // The default unitless values are inches so convert to mm. 
                diaFrom *= 25.4 ;
            }

            retcode |= 0x01 ; 
        }

        if (n2.size())
        {   // Then there is something after a '-' character
            csString units ; 
            x = atof(n2.c_str()) ; 
            char *ps = CS_SkipFloat(n2.str) ; 
            if (*ps)
            {   // Then something trails the number
                units = ps ; 
                units.Trim() ; 
            }

            diaTo = x ; 
            if (units.size())
            {
                units.ToUpper() ; 
                if (units[0] == 'I')
                    diaTo *= 25.4 ; 
            }
            else
            {   // The default unitless values are inches so convert to mm. 
                diaTo *= 25.4 ;
            }

            retcode |= 0x02 ; 
        }
        else
        {   // There was only a leading value
            diaTo = diaFrom ; 
        }
    }

    return retcode ; 
}

int RoutingCondRec::ParseFeatureOption(csString &tok)
{
    int retcode = 0 ; 
    csString p1, p2 ; 
    p1 = tok.NextToken(",", 0) ; 
    p2 = tok.NextToken(",") ;  

    p1.Trim() ; 
    p2.Trim() ; 

    if (!p2.size())
    {   // Then there was only a single part to the field
        feature = "*" ; 
        option  = p1 ; 
    }
    else 
    {   
        feature = p1 ; 
        option  = p2 ; 
    }

    if (!feature.size())
        retcode |= 0x01 ; 

    if (!option.size())
        retcode |= 0x02 ; 

    return retcode ; 
}


int RoutingCondRec::Matches(char *szFeat,            // feature to match    
                            char *szOpt,             // option to match
                            char *szCust,            // customer code
                            double dia,              // part diameter
                            char part)               // part type character
{
    // Match stats
    //   0x01 = feat
    //   0x02 = opt
    //   0x04 = customer
    //   0x08 = dia
    //   0x10 = part

    int matchstat = 0 ; 

    // -------------------
    //      FEATURE 
    if (szFeat)
    {
        if (szFeat[0] == '*')
            matchstat |= 0x01 ; 
        else if (feature[0] == '*')
            matchstat |= 0x01 ; 
        else if (strstr(szFeat, feature.c_str()))
            matchstat |= 0x01 ;
    }
    else
    {
        matchstat |= 0x01 ; 
    }

    // -------------------
    //      OPTION 
    // the option must be defined and has to match 
    if (szOpt)
    {
        if (option == "*")
            matchstat |= 0x02 ; 
        if (szOpt[0] == '*')
            matchstat |= 0x02 ; 
        else if (strstr(szOpt, option.c_str()))
            matchstat |= 0x02 ;
    }
    else
    {
        matchstat |= 0x02 ; 
    }

    // -------------------
    //      CUSTOMER
    if (szCust)
    {
        if (szCust[0] == '*')
            matchstat |= 0x04 ; 
        else if (customer[0] == '*')
            matchstat |= 0x04 ; 
        else if (strstr(szCust, customer.c_str()))
            matchstat |= 0x04 ;
    }
    else
    {
        matchstat |= 0x04 ; 
    }


    // -------------------
    //      DIAMETER
    if (((diaFrom - 0.01) <= dia) && (dia <= (diaTo + 0.01)))
        matchstat |= 0x08 ; 
    else
        return 0 ; 


    // -------------------
    //      PART
    if (part)
    {
        if ((parts[0] == '*') || (part == '*') || parts.Find(part))
            matchstat |= 0x10 ; 
    }
    else
    {
        matchstat |= 0x10 ; 
    }

    if (matchstat == 0x1f)
        return 1 ; 
    return 0 ; 
}


// We only want to match positive condition records here. 
int FindRoutingRec(RoutingCondRecVec &recvec, // table to search
                   char *szFeat,            // feature to match    
                   char *szOpt,             // option to match
                   char *szCust,            // customer code
                   double dia,              // part diameter
                   char part)               // part type character
{
    unsigned int i ; 
    i = 0 ; 
    for (i=0; i < recvec.size(); i++)
    {
        if (recvec[i].Matches(szFeat, szOpt, szCust, dia, part))
        {   
            if (!recvec[i].inverted)
                return (int)i ; 
        }
    }

    return -1 ; // not found. 
}

