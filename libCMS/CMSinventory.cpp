// CMSinventory.cpp

#include <CSstdlibs/cslib.h>
#include <CSGeometry/cs_geometry.h>
// #include "Log.h"
#include "CMSBOMRTE.h"

/* 
    The current stock table is STKB (stock balance). To get the total inventory of
    a specific type of steel use the following query. 

    SELECT SUM(BXQTOH) FROM <LIB>.STKB WHERE BXPART = '<part num>' AND BXSTOK = '<plant>STL'

    So for example the H-13 9 inch steel for Markham would be using the live production
    database

    SELECT SUM(BXQTOH) FROM CMSDAT.STKB WHERE BXPART = 'H-13 9 DIA' AND BXSTOK = '001STL'

    BXQTOH = quantity on hand
    BXSTOK = stock location

 */

int CMSBOMRTE::MaterialInStock(CMSJob &job, csString &barPart)
{
    if (barPart.size() == 0)
        return 0 ; // part must exist. 

    if (skipStockCheck)
        return 1 ; 

    if (job.bStockOverride)
        return 1 ; 

    /*
       SELECT BXQTOH FROM <LIB>.STKB WHERE BXPART = '<part num>' AND BXSTOK = '<plant>STL'

       Then look for one record that exceeds the required thickness

     */

    char qrytmp[4096] ; 

    _snprintf(qrytmp, 4000, 
        "SELECT BXQTOH FROM %s.STKB WHERE BXPART = '%s' AND BXSTOK = '%sSTL' AND BXUNIT = 'IN' ", 
                m_db.dbname, barPart.c_str(), plant) ;  


    double maxthk = 0 ; 
    try
    {
        CSQLRecordset rs(GetDatabase());
        rs << qrytmp ; 
        rs.SQLExec();

        while (rs.SQLFetch())
        {
            double amount = atof(rs.SQLGetData(1).c_str()) ;
            if (amount > maxthk)
                maxthk = amount ; 
        }
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE::Check stock database errorcode = %d, msg = %s\r\n",
                e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();
        return false;
    }

    if (job.IsPartBlank())
    {   // Only need a quatity of 1 in this case (at least in theory since there is no
        // Solarsoft data available to verify this logic.)
        if (maxthk >= 0.999) 
            return 1 ; 
    }
    else if (job.length < maxthk)
    {   // Standard processing cutting material from bar stock. 
        return 1 ; 
    }

    return 0 ; 
}


int ExtractPartSizes(csString &part, double &dia, double &thk, char &type)
{
    // HD n X n P'
    csString tok = part.NextToken(" ", 0) ; 
    
    csString diastr = part.NextToken("X") ; 
    diastr.Trim() ; 
    
    csString thkstr = part.NextToken(" ", part.idx) ; 
    thkstr.Trim() ; 

    csString typestr = part.NextToken(" ", part.idx) ; 
    typestr.Trim() ; 

    dia = atof(diastr.c_str()) ; 
    thk = atof(thkstr.c_str()) ; 
    type = typestr[0] ; 

    return 0 ; 
}


csString CMSBOMRTE::FindBestPart(CMSJob &job, csString &basePart, double &actThk)
{
    if (basePart.Left(2) != "HD")
        return basePart ; 

    actThk -= 0.378 ; // subtract the saw cut allowance ;

    double D, T ; 
    char P ; 

    ExtractPartSizes(basePart, D, T, P) ; 

    /*
       SELECT BXQTOH FROM <LIB>.STKB WHERE BXPART = '<part num>' AND BXSTOK = '<plant>STL'

       Then look for one record that exceeds the required thickness

     */

    // Work out the best matching diameter
    double r = fmod(D, 1.0) ; 
    char fract[16] ; 
    int iD = (int)(floor(D)) ; 

    fract[0] = 0 ; 
    if (r > 0.125 && r < .375)
        strcpy(fract, ".25") ;
    else if (r > 0.35 && r < .625)
        strcpy(fract, ".5") ;
    else if (r > 0.6)
        strcpy(fract, ".75") ;


    char qrytmp[4096] ; 

    _snprintf(qrytmp, 4000, 
        "SELECT AQPART FROM %s.METHDM WHERE AQPART LIKE 'HD %d%s X%%%c%%' AND AQPLNT = '%s'", 
                m_db.dbname, iD, fract, P, plant) ;  


    double thkmatch = 0 ; 
    double deltaT = fabs(actThk - T) ; 
    csString bestPart(basePart) ; 

    try
    {
        CSQLRecordset rs(GetDatabase());
        rs << qrytmp ; 
        rs.SQLExec();


        while (rs.SQLFetch())
        {
            csString part = rs.SQLGetData(1).c_str() ;
            part.Trim() ; 
            double tD, tT ; 
            char tP ; 
            ExtractPartSizes(part, tD, tT, tP) ; 

            if (tP != P)
                continue ; 

            double dt = fabs(tT - actThk) ; 
            if (dt < deltaT)
            {
                deltaT = dt ; 
                bestPart = part ; 
            }
        }
    }
    catch (CSQLException* e)
    {
        char msg[4096] ; 
        _snprintf(msg, 4000, "CMSBOMRTE:: Error looking up best matching mandrel part errorcode = %d, msg = %s\r\n",
                e->m_nRetCode, e->m_strError.c_str());
        msg[4000] = 0 ; 
        msg[4001] = 0 ; 
        LogError(msg) ; 
        e->Delete();
    }

    return bestPart ; 
}

