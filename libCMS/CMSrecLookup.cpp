// Finds the bar stock material code based on the diamter
// Steel type must be "H-13"  or "2714"

// #include <ugutils.h>
#include <CSstdlibs/cslib.h>
#include "Log.h"
#include "CMSBOMRTE.h"


static bool CompEQ(double a, double b)
{
    if ((a - 0.01) < b && (a + 0.01) > b)
        return true ; 
    return false ; 
}


csString CMSBOMRTE::FindBarStock(int steeltype, double dia, double thk, int flags)
{
    if (steeltype >= 0 && steeltype < (int)steelvec.size())
        return FindBarStock(steelvec[steeltype].prefix.c_str(), dia, thk, flags) ; 
    if (flags & CMSJob::HARDENED_BLANK)
        return csString("HB") ; 
    else if (flags & CMSJob::TURNED_BLANK && steeltype == STEEL_H13)
        return csString("TH") ; 
    return csString("H-13") ; // go with most used steel type

    // Previous code - modified Oct 10, 2009
    // if (steeltype == STEEL_H13)
    //     return FindBarStock("H-13", dia) ; 
    // return FindBarStock("2714", dia) ; 
}

csString CMSBOMRTE::FindBarStock(char *steeltype, double dia, double thk, int flags)
{
    char qry[2048] ; 
    
    /*
        TH = Turned blank H-13
                range DIA[8,10]  THK[1,2] inches
             Pattern format  'TH d X t' where 
        
        T2 = Turned blank 2714
                range DIA[8,10]  THK[1,4] inches
             Pattern format  'T2 d X t' where 

        HB = Hardened blank H-13
                range DIA[8,12]  THK[1,2] inches
             Pattern format  'HB d X t' where 

             
             d=dia in 1 inch increments
             t=thickness in 0.25 inch increments

        To make this universal we simlpy scan for the proper diameter and then for the
        proper thickness. If nothing is found to match exactly then indicate it is out 
        of stock so that it can be cut from bar stock. 

    */

    csString bestStock ; 

    if (flags & (CMSJob::HARDENED_BLANK | CMSJob::TURNED_BLANK))
    {
        csString partPrefix ; 
        if (flags & CMSJob::HARDENED_BLANK) 
            partPrefix = "HB" ; 
        else if (_strnicmp(steeltype, STEEL_H13_STR, 4) == 0)
            partPrefix = "TH" ; 
        else if (_strnicmp(steeltype, STEEL_2714_STR, 4) == 0)
            partPrefix = "T2" ; 
        else 
            partPrefix = "XX~~ZZ" ; // set to nonsense so that the query fails. 

        _snprintf(qry, 2000,
            "SELECT V6PART FROM %s.STKA WHERE V6PART LIKE '%s%%' AND V6PLNT = '%s'",
                m_db.dbname, partPrefix.c_str(), plant) ; 

        try
        {
            CSQLRecordset rs((CSQLDatabase&)m_db);
            rs << qry ; 

            int ofx = (int)strlen(steeltype) ; 

            // The best diameter is the smallest diameter >= to the required diameter. 
            double bestDia = 999999.0 ; // init to impossibly large value
            double bestThk = 999999.0 ; 
            
            rs.SQLExec();
            while (rs.SQLFetch())
            {
                csString part = rs.SQLGetData(1).c_str() ; 
                part.Trim() ;

                if (part.Left(partPrefix.size()) != partPrefix)
                    continue ; 

                csString tok = part.NextToken(" ", 0) ; // tok = "<steeltype prefix>"
                tok = part.NextToken(" ") ; // tok should now be the diameter numeric value

                double stockdia = atof(tok.c_str()) ;
                int d = (int)floor(stockdia + 0.001) ;
                double r = fmod(stockdia, 1.0) ;

                tok = part.NextToken(" ") ; // tok = "X"
                tok = part.NextToken(" ") ; // Tok should now be the thickness
                double thickness = atof(tok.c_str()) ;
                int dt = (int)floor(thickness + 0.001) ;
                double rt = fmod(thickness, 1.0) ;
                double SCA = SawCutAllowance(thk, IS_IMPERIAL) ; 

                if ((stockdia - 0.025 <= dia) && 
                                        (dia <= stockdia + 0.025)
                                          &&
                    (thickness - 0.025 < (thk - SCA)) && 
                                        ((thk - SCA) < thickness + 0.05 ))
                {   // Then the value is in range
                    if (stockdia < bestDia)
                    {   // Save this
                        bestStock = part ; 
                        bestDia = stockdia ; 
                        bestThk = thickness ; 
                    }
                    else if (CompEQ(stockdia, bestDia))
                    {
                        if (thickness < bestThk)
                        {
                            bestStock = part ; 
                            bestThk = thickness ; 
                        }
                    }
                }
            }
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4000, "CMSBOMRTE::CreateFlatFile database errorcode STKB= %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str());
            msg[4000] = 0 ; 
            msg[4001] = 0 ; 
            LogError(msg) ; 
            e->Delete();
        }

    }
    else
    {   // Do standard query requests
        _snprintf(qry, 2000,
            "SELECT * FROM %s.STKA WHERE V6PART LIKE '%s%%'  AND V6PLNT = '%s'",
                m_db.dbname, steeltype, plant) ; 

        try
        {
            CSQLRecordset rs((CSQLDatabase&)m_db);
            rs << qry ; 

            int ofx = (int)strlen(steeltype) ; 

            // The best diameter is the smallest diameter >= to the required diameter. 
            double bestDia = 999999.0 ; // init to impossibly large value
            
            rs.SQLExec();
            while (rs.SQLFetch())
            {
                csString part = rs.SQLGetData(1).c_str() ; 
                part.Trim() ;

                if (part.Left((int)strlen(steeltype)) != steeltype)
                    continue ; 

                csString tok = part.NextToken(" ", 0) ; 
                tok = part.NextToken(" ") ; // tok should now be the diameter numeric value

                double stockdia = atof(tok.c_str()) ; 
                int d = (int)floor(stockdia + 0.001) ; 
                double r = fmod(stockdia, 1.0) ; 
                if (firstRun && r > 0.49 && r < 0.51)
                {   // skip all half inch sizes except 14 and 15
                    if (d != 14 && d != 15)
                        continue ; 
                }

                if (stockdia >= (dia - 0.025))
                {   // Then the value is in range
                    if (stockdia < bestDia)
                    {   // Save this
                        bestStock = part ; 
                        bestDia = stockdia ; 
                    }
                }
            }
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4000, "CMSBOMRTE::CreateFlatFile database errorcode = %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str());
            msg[4000] = 0 ; 
            msg[4001] = 0 ; 
            LogError(msg) ; 
            e->Delete();
        }
    }

    if (bestStock.size() == 0)
    {
        csString msg ; 
        msg.FormatSz(250, "%s X %0.2f DIA DOES NOT EXIST IN THE SYSTEM - MUST CORRECT BEFORE PROCEEDING", 
                        steeltype, dia) ; 
        if (steelStockMsg.size())
            steelStockMsg += "\r\n" ;
        steelStockMsg += msg ; 
    }

    return bestStock ; 
}

// Returns a number that falls on a multiple of 25 modulo 100
int NormalizeFraction(int n)
{
    n = n % 100 ; 
    if (n <= 5)
        return 0 ; 
    if (n <= 30)
        return 25 ; 
    if (n <= 55)
        return 50 ; 
    return 75 ; 
}

//!
/*! 
    Part naming convention assumed to be:  
        
        AAA N[.NN] X N[.NN] [MANDREL|PLATE|BACKER]

    The first number is the diameter, and the second number is the thickness. 
    For HD type parts, the thickness is for the overall stack and not the 
    individual parts. If we are adding a backer to an HD type order, then 
    the backer should be taken from the HD sub parts list. If the backer
    is being deleted then again it should only happen when deleting from 
    an HD type order. 

    The ability to add and delete other types of parts will be enabled 
    later on if required, but for now it will be assumed that sales will
    be responsible for adding all the necessary components and that all 
    we really need to do is delete parts. 

    The reason for adding a part would be if a component of a hollow die
    was deleted when in reality it shouldn't have been, and the user needs
    to add it back. 
    */
csString BuildPartName(char *prefix, char *subpart, double dia, double thk)
{
    double w, f ; 

    f = modf(dia, &w) ; 
    int dia_w = (int)w ; 
    int dia_f = NormalizeFraction((int)(f * 100.0)) ;

    f = modf(thk, &w) ; 
    int thk_w = (int)w ; 
    int thk_f = NormalizeFraction((int)(f * 100.0)) ;

    csString num ; 
    csString partname = prefix ; // start with the initial prefix
    partname += " " ; 
    partname += num.FormatSz(32, "%d", dia_w) ; 
    if (dia_f)
        partname += num.FormatSz(32, ".%d", dia_f) ; 
    partname += " X " ; 
    partname += num.FormatSz(32, "%d", thk_w) ; 
    if (thk_f)
        partname += num.FormatSz(32, ".%d", thk_f) ; 

    if (partname.Left(2) == "HD")
    {   // Then we need to append the subpart portion. 
        partname += " " ;
        csString psub(subpart, 20 - partname.size()); 
        partname += psub ;
    }

    return partname ; 
}

//! Attempt to extract the base part name based on the order items. 
csString BuildPartName(int parttype, CMSOrder &order, CMSJob &job)
{   
    char prefix[64], suffix[64] ; 
    if (!PartNames(parttype, prefix, suffix))
        return -1 ; 

    csString partname = BuildPartName(prefix, suffix, job.diam, job.length) ; 

    return partname ; 
}


int CMSBOMRTE::FindPart(char *prefix, char *subpart, 
                        double dia, double thk, csString &part)
{
    // Need to find nearest matching part.
    // For the part we must round up to the nearest part size within a 
    // 1/4inch part. There are also specialty parts but these will be ignored
    // in the search process since the sort order for these parts is all over
    // the map. 
 
    csString partname = BuildPartName(prefix, subpart, dia, thk) ; 

    csString qry("SELECT * FROM ") ; 
    csString wrk ; 
    qry += m_db.dbname ; 
    qry += ".stkmm WHERE AVPART = '" ; 
    qry += partname ; 
    qry += "'" ; 


    try
    {
        CSQLRecordset rs((CSQLDatabase&)m_db);
        rs << qry.c_str() ; 
        rs.SQLExec();
        while (rs.SQLFetch())
        {
            // If there was data then the record is valiud
            part = partname ; 
        }
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::FindPart database errorcode = %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();
    }

    return part.size() ; 
}
