// CMSsupport.cpp

// #include <ugutils.h>
#include <CSstdlibs/cslib.h>
#include "Log.h"
#include "CMSBOMRTE.h"


void PrintSampleCMSConfig(FILE *fp) 
{
    fprintf(fp, 
    "# Lines starting with hashes (pound sign) are ignored as comments\n"
    "# The parameter names in front of the '=' sign are case sensitive.\n"
    "DECodbc=<odbc name>\n"
    "DECusr=<username>\n"
    "DECpwd=<password>\n"
    "CMSIP=<iSeries Machine IP>   example: 10.0.0.35\n"
    "CMSodbc=<CMS ODBC name>\n"
    "CMSDBusr=<username>\n"
    "CMSDBpwd=<password>\n"
    "CMSQusr=<username>\n"
    "CMSQpwd=<password>\n"
    "CMSInQ=SF223DQI\n"
    "CMSOutQ=SF223DQO\n"
    "CMSDBName=<database name>  example: EXCOPHASE1\n"
    "CMSPlant=<plantid>    For Markham is 001 for example, this is a string\n"
    "SEQSPLIT=40         (Probably different for Michigan and possible Alu'Die)\n"
    "SEQMERGE=500\n") ; 
    fflush(fp) ; 

}


//! Initialize the default parameters
CMSConnectionParms::CMSConnectionParms() 
{
    logfp = 0 ; 
    cfgfile[0] = 0 ; 

    strcpy(gCMSparms.ibmhost, "10.0.0.35") ; 
    strcpy(gCMSparms.dbname,  "PRODTEST") ; 

    strcpy(gCMSparms.odbc,    "cms1") ; 
    strcpy(gCMSparms.dbpwd,   "smc") ; 
    strcpy(gCMSparms.dbusr,   "cms") ; 

    strcpy(gCMSparms.DQpwd,   "SMC") ; 
    strcpy(gCMSparms.DQusr,   "CMS") ; 
    strcpy(gCMSparms.inputQ,  "SF223DQI") ; 
    strcpy(gCMSparms.outputQ, "SF223DQO") ; 

    plantID[0] = 0 ; 
    seqSplit = 0 ; 
    seqMerge = 0 ; 

    bDoVerification = false ; 
}

CMSConnectionParms::~CMSConnectionParms() 
{
    if (bDoVerification)
        DeleteCriticalSection(&chkqSection) ; 
}

int CMSConnectionParms::InitVerification() 
{
    InitializeCriticalSection(&chkqSection) ; 
    bDoVerification = true ; 
    return 0  ;
}


//! this->cfgfile must be set upon entry. 
//! returns 0=ok else error code. 
int CMSConnectionParms::LoadConfigFile(const char *configname, FILE *fpmsg)
{
    cfgfile[0] = 0 ; 
    FILE *fp = fopen(configname, "rt") ; 
    if (!fp)
        return -1 ; 

    strcpy(cfgfile, configname) ; // save this filename

    int retcode = 0; 
    char buf[1024] ; 
    while (fgets(buf, 1024, fp))
    {
        csString line(buf) ; 
        line.Trim() ; 

        if (line[0] == '#' || line.size() == 0)
            continue ; 

        csString name, val ; 
        name = line.NextToken("=", 0) ; 
        val = line.NextToken("=") ; 

        name.Trim() ; 
        val.Trim() ; 
        if (name == "DECodbc")
        {
            CS_strmaxcpy(decDBname, val.c_str(), 60) ; 
        }
        else if(name == "DECusr") 
        {
            CS_strmaxcpy(decDBusr, val.c_str(), 60) ; 
        }
        else if(name == "DECpwd") 
        {
            CS_strmaxcpy(decDBpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSIP") 
        {
            CS_strmaxcpy(ibmhost, val.c_str(), 60) ; 
        }
        else if(name == "CMSodbc") 
        {
            CS_strmaxcpy(odbc, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBusr") 
        {
            CS_strmaxcpy(dbusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBpwd") 
        {
            CS_strmaxcpy(dbpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSQusr") 
        {
            CS_strmaxcpy(DQusr, val.c_str(), 60) ; 
        }
        else if(name == "CMSQpwd") 
        {
            CS_strmaxcpy(DQpwd, val.c_str(), 60) ; 
        }
        else if(name == "CMSInQ") 
        {
            CS_strmaxcpy(inputQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSOutQ") 
        {
            CS_strmaxcpy(outputQ, val.c_str(), 60) ; 
        }
        else if(name == "CMSDBName") 
        {
            CS_strmaxcpy(dbname, val.c_str(), 60) ; 
        }
        else if(name == "CMSPlant") 
        {
            CS_strmaxcpy(plantID, val.c_str(), 60) ; 
            int plant = atoi(plantID) ; 
            if (plant < 1 || plant > 3)
            {
                if (fpmsg)
                {
                    fprintf(fpmsg, "Error, unkown plant# = %d in the config file\n", plant) ; 
                    fflush(fpmsg) ; 
                }
            }
        }
        else if(name == "SEQSPLIT") 
        {
            seqSplit = atoi(val.c_str()) ; 
        }
        else if(name == "SEQMERGE") 
        {
            seqMerge= atoi(val.c_str()) ; 
        }
         else if(name == "BATCH") 
        {
            CS_strmaxcpy(batchDir, val.c_str(), 250) ; 
        }
        else
        {
            if (fpmsg)
            {
                fprintf(fpmsg, "ERROR: unknown parameter type '%s' in config file '%s'\n", name.c_str(), cfgfile) ; 
                fflush(fpmsg) ; 
            }
            retcode = -2 ; 
            break ; 
        }
    }
    
    fclose(fp) ; 
    return retcode ; 
}


int PartRank(char *partstr)
{
    csString part(partstr) ; 
    if (part == "*") 
        return 1 ; 
    if (part.size() == 1)
        return 2 ; 
    if (part.size() == 2)
        return 3 ; 
    return 0 ; // something went wrong, give it lowest rank
}

int PartCharsThatMatch(char *taskdefpart, char *trackpart) 
{
    int n = 0 ; 
    while (taskdefpart[n] && trackpart[n])
    {
        if (taskdefpart[0] && (taskdefpart[n] == trackpart[n]))
            n++ ; 
        else
            break ; 
    }
    return n ; 
}

// ================================================================
//              CMSJob member fucntions
// ================================================================

int CMSJob::IsFeeder() 
{
    if (partname.icFindIDX("FDR") >= 0 ||
        mattype.icFindIDX("FDR") >= 0)
    {
        partcode = FEEDER_PARTCODE ; 
        return 1 ; 
    }
    return 0 ; 
}

int CMSJob::IsMandrel()
{
    if ((partname.icFindIDX("MA", 4) >= 0 ||
         mattype.icFindIDX("MA", 4) >= 0) ||
        (partname.Left(1) == "H" && partname.Right(1) == "M") || 
        (mattype.Left(1) == "H" && mattype.Right(1) == "M"))
    {
        partcode = MANDREL_PARTCODE ; 
        return 0x81 ; 
    }
    return 0 ; 
}

// Note: mandrels are always sub parts no matter what.
char CMSJob::IsSubPlate()
{
    if ((partname.icFindIDX("PL", 4) >= 0 ||
         mattype.icFindIDX("PL", 4) >= 0) ||
        (partname.Left(1) == "H" && partname.Right(1) == "P") || 
        (mattype.Left(1) == "H" && mattype.Right(1) == "P"))
    {
        return 'P' ; 
    }
    return 0 ; 
}

char CMSJob::IsSubBacker()
{
    if ((partname.icFindIDX("BA", 4) >= 0 || 
        mattype.icFindIDX("BA", 4) >= 0) ||
        (partname.Left(1) == "H" && partname.Right(1) == "B") || 
        (mattype.Left(1) == "H" && mattype.Right(1) == "B"))
    {
        return 'B' ; 
    }
    return 0 ; 
}

int CMSJob::IsPlate()
{
    if (IsSubPlate())
    {
        partcode = PLATE_PARTCODE ;
        return 0x81 ; // indicate plate and hollow die
    }

    if (partname.icFindIDX("SD") == 0)
    {
        partcode = PLATE_PARTCODE ;
        return 1 ; // plate but not hollow die. 
    }
    return 0 ; 
}


//! This must return the proper steel code type for the part. 
int CMSJob::IsBacker() 
{
    if (partname.icFindIDX("BAH") >= 0 || 
        mattype.icFindIDX("BAH") >= 0)
    {
        partcode = BACKER_PARTCODE ; 
        return 1 ; 
    }
    if (IsSubBacker())
    {
        partcode = BACKER_PARTCODE ; 
        return 0x81 ; 
    }
    if (partname.icFindIDX("BA2") >= 0 || 
        mattype.icFindIDX("BA2") >= 0)
    {
        partcode = BACKER_PARTCODE ; 
        return 2 ; 
    }
    return 0 ; 
}

int CMSJob::IsBolster() 
{
    if (partname.icFindIDX("BOH") >= 0 || 
        mattype.icFindIDX("BOH") >= 0)
    {
        partcode = BOLSTER_PARTCODE ; 
        return STEEL_H13 ; 
    }
    if (partname.icFindIDX("BO2") >= 0 || 
        mattype.icFindIDX("BO2") >= 0)
    {
        partcode = BOLSTER_PARTCODE ; 
        return STEEL_2714 ; 
    }
    return 0 ; 
}

int CMSJob::IsSubBolster() 
{
    if (partname.icFindIDX("SBH") >= 0 || 
        mattype.icFindIDX("SBH") >= 0)
    {
        partcode = SUBBOLSTER_PARTCODE ; 
        return STEEL_H13 ; 
    }
    if (partname.icFindIDX("SB2") >= 0 || 
        mattype.icFindIDX("SB2") >= 0)
    {
        partcode = SUBBOLSTER_PARTCODE ; 
        return STEEL_2714 ; 
    }
    return 0 ; 
}

int CMSJob::IsDieRing() 
{
    if (partname.icFindIDX("RI") == 0 || 
        mattype.icFindIDX("RI") == 0)
    {
        partcode = RING_PARTCODE ; 
        return STEEL_H13 ; 
    }
    return 0 ; 
}

// Enforce mutually exclusive rules etc..
void SetStatFlags(int newStat, int &destFlags)
{
    if (newStat & CMSJob::HARDENED_BLANK)
        newStat &= ~CMSJob::TURNED_BLANK ; // clear the TURNED_BLANK bit
    newStat &= (CMSJob::TURNED_BLANK | CMSJob::HARDENED_BLANK) ; // clear all extra bits. 
    destFlags = newStat ; 
}

char CMSJob::SetPartCode() 
{
    partcode = 0 ; // initialize to NULL 
    if (partname.Left(3) == "FDR")
    {
        partcode = FEEDER_PARTCODE ; 
    }
    else if (mattype.Find("MA", 4))
    {
        partcode = MANDREL_PARTCODE ; 
    }
    else if ((seqnum > 0 && seqnum <= gCMSparms.seqSplit && 
               (mattype.Find("PLA") || partname.Left(2) == "SD"))  ||
             (seqnum >= gCMSparms.seqMerge && mattype.Find("PL", 4)))
    {
        partcode = PLATE_PARTCODE ; 
    }
    else if ((seqnum > 0 && seqnum <= gCMSparms.seqSplit && 
               (mattype.Find("BAC") || partname.Left(1) == "B"))  ||
             (seqnum >= gCMSparms.seqMerge && mattype.Find("BA", 4)))
    {
        partcode = BACKER_PARTCODE ; 
    }
    else if (partname.Left(2) == "BO")
    {
        partcode = BOLSTER_PARTCODE ; 
    }
    else if (partname.Left(2) == "SB")
    {
        partcode = SUBBOLSTER_PARTCODE ; 
    }
    else if (partname.Left(2) == "RI")
    {
        partcode = RING_PARTCODE ; 
    }
    else if (partname.Left(1) == "H")
    {
        if (mattype.Right(1) == "M")
            partcode = MANDREL_PARTCODE ; 
        else if (mattype.Right(1) == "P")
            partcode = PLATE_PARTCODE ; 
        else if (mattype.Right(1) == "B")
            partcode = BACKER_PARTCODE ; 
    }
    return partcode ; 
}

csString &CMSJob::GetTmpJobNumber(int &count)
{
    if (tmpjobnum.size() == 0)
    {
        char tmpstr[32] ; 
        sprintf(tmpstr, FFTMPPREFIX "%d", count++) ; 
        tmpjobnum = tmpstr ; 
    }
    return tmpjobnum ; 
}


// ================================================================
//               CMSOption member functions
// ================================================================


int CMSOption::IsTripleSkim() 
{
    if (optname.icFindIDX("TRIPLE SKIM") >= 0)
        return 1 ;
    return 0 ; 
}

int CMSOption::IsHeatSink()
{
    if (optname.icFindIDX("HEAT SINK") >= 0)
        return 1 ;
    return 0 ; 
}

int CMSOption::IsSparkBrgs()
{
    if (optname.icFindIDX("SPARK") >= 0)
        return 1 ;
    return 0 ; 
}

int CMSOption::IsMultiCore()
{
    if (optname.icFindIDX("MULTI - MANDREL") >= 0)
        return 1 ;
    return 0 ; 
}

int CMSOption::IsOnePiece()
{
    if (optname.icFindIDX("ONE PIECE") >= 0)
        return 1 ;
    return 0 ; 
}

int CMSOption::IsCentreFeed()
{
    if (optname.icFindIDX("CENTRE FEED") >= 0)
        return 1 ;
    return 0 ; 
}


void CMSRTE::SetRoutingParms(CMSOrder &ord, int ijob, int iopt, 
                             RouteDataRec &rdr, RouteDataRec &rCurRec, 
                             double *pUGTime)
{
    CMSJob *pjob = &ord.jobvec[ijob] ; 
    SetOrderNumber(pjob->tmpjobnum.size() > 0 ? pjob->tmpjobnum.c_str() : pjob->jobnum.c_str()) ; 
    if (rdr.command == ROUTE_ADD)
    {
        SetAction(rdr.command) ; 
        SetSeqNum(rdr.seqno) ; 
        SetPlant(gCMSparms.plantID) ; 
        SetDept(rdr.dept.c_str()) ; 
        SetResource(rdr.resource.c_str()) ; 
        SetOperation(rdr.operation.c_str()) ; 
        SetRunStandard(pUGTime ? *pUGTime : rdr.runstd) ; 
        SetStatus(rdr.status[0]) ; 
        SetReporting(rdr.reporting[0]) ; 
    }
    else
    {
        SetAction(rdr.command) ; 
        SetSeqNum(rCurRec.seqno) ; 
        SetPlant(gCMSparms.plantID) ; 
        SetDept(rCurRec.dept.c_str()) ; 
        SetResource(rCurRec.resource.c_str()) ; 
        SetOperation(rCurRec.operation.c_str()) ; 
        SetRunStandard(pUGTime ? *pUGTime : rdr.runstd) ; 
        SetStatus(rCurRec.status[0]) ; 
        SetReporting(rCurRec.reporting[0]) ; 
    }
    CRLF() ; 
}
            

//! Extract the date information from a CMS DAT field
int CMSSQL_GetDate(CDateTime &dt, const char *datestr)
{
    // These are formatted as YYYY-MM-DD
    csString date(datestr) ; 
    csString year = date.NextToken("-", 0) ; 
    csString mon  = date.NextToken("-") ; 
    csString day  = date.NextToken("-") ; 
    dt.m_nYear  = atoi(year.c_str()) ; 
    dt.m_nMonth = atoi(mon.c_str()) ; 
    dt.m_nDay   = atoi(day.c_str()) ; 

    if (!dt.m_nYear || !dt.m_nMonth || !dt.m_nDay)
        return -1 ; // something went wrong
    return 0 ; // all OK
}

//! Extract the time information from a CMS TIM fields (24 hour clock
int CMSSQL_GetTime(CDateTime &dt, const char *timestr)
{
    // These are formatted as YYYY-MM-DD
    csString tmstr(timestr) ; 
    csString hour = tmstr.Left(2) ; 
    csString min  = tmstr.Mid(3,2) ;
    csString sec  = tmstr.Mid(6,2) ; 
    dt.m_nHours = atoi(hour.c_str()) ; 
    dt.m_nMins  = atoi(min.c_str()) ; 
    dt.m_nSecs  = atoi(sec.c_str()) ; 

    if (!hour.size() || !min.size() || !sec.size())
        return -1 ; // something went wrong
    return 0 ; // all OK
}



char PartCodeCharFromCMSPart(csString &partname)
{
    char partcode = 0 ; 
    if (partname.Left(3) == "FDR")
    {
        partcode = FEEDER_PARTCODE ; 
    }
    else if (partname.Find("MAN", 4) ||
             (partname.Left(2) == "HD" && 
              (partname.Find("MA", 4) || partname.Right(1) == "M"))
            )
    {
        partcode = MANDREL_PARTCODE ; 
    }
    else if (partname.Find("PLA") || 
             (partname.Left(2) == "SD") ||
             (partname.Left(2) == "HD" && 
              (partname.Find("PL", 4) || partname.Right(1) == "P"))
            )
    {   // Then it is a plate
        partcode = PLATE_PARTCODE ; 
    }
    else if (partname.Find("BAC") || 
             (partname.Left(2) == "BA") ||
             (partname.Left(2) == "HD" && 
              (partname.Find("BA", 4) || partname.Right(1) == "B"))
            )
    {
        partcode = BACKER_PARTCODE ; 
    }
    else if (partname.Left(2) == "BO")
    {
        partcode = BOLSTER_PARTCODE ; 
    }
    else if (partname.Left(2) == "SB")
    {
        partcode = SUBBOLSTER_PARTCODE ; 
    }
    else if (partname.Left(2) == "RI")
    {
        partcode = RING_PARTCODE ; 
    }
    else if (partname.Left(2) == "HD")
    {
        partcode = GLOBAL_MASTER_PARTCODE ; 
    }

    return partcode ; 
}


int GetPartPriorityValue(char partCode)
{
    /* 
        Priority ranking 

        PLATE    - rated higher for consistency since this is always present
        MANDREL  - most complicated component so ranks next
        FEEDER   - contains surfaceing potentially
        BACKER   - next most common, with engraving etc...
        BOLSTER  - from here on down it is arbitrary. 
        SUB-BOLSTER
        SUB-BACKER
        RING
    */

    switch (partCode)
    {
        case GLOBAL_MASTER_PARTCODE : return 1 ; 
        case PLATE_PARTCODE         : return 2 ; 
        case MANDREL_PARTCODE       : return 3 ; 
        case FEEDER_PARTCODE        : return 4 ;
        case BACKER_PARTCODE        : return 5 ; 
        case BOLSTER_PARTCODE       : return 6 ; 
        case SUBBOLSTER_PARTCODE    : return 7 ; 
        case SUBBACKER_PARTCODE     : return 8 ; 
        case RING_PARTCODE          : return 9 ;
        case INSERT_PARTCODE        : return 10 ; 
        case PLATEINSERT_PARTCODE   : return 11 ; 
        case MANDRELINSERT_PARTCODE : return 12 ; 
        case BOLT_PARTCODE          : return 13 ; 
    }
    return 9999 ; 
}

int IsOldPartHigherPriority(char oldpart, char newpart)
{
    int oldvalue = GetPartPriorityValue(oldpart) ;
    int newvalue = GetPartPriorityValue(newpart) ;

    if (oldvalue < newvalue)
        return 1 ; 
    return 0 ; 
}



