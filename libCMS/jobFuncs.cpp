// jobFuncs.cpp


#include <assert.h>
#include <libSQL/SQLRecordset.h>
#include "CMSBOMRTE.h"

// ************** CMSJob Member Functions *************

CMSJob::CMSJob()
{
    parttype = 0 ; // One of TYPE_FDR, TYPE_MND etc... 
    length = 0 ;   // thickness of the part. 
    diam = 0.0 ;   // diameter of the part in inches. 
    seqnum = 0 ;   // seq num for the record. 
    linenum = 0 ; 
    steel = 0 ;    // the type of material used to make the part STEEL_H13, STEEL_2714

    // Turned and hardened blank flags. 
    statFlags = 0 ; 
    
    // set to false when part is not used or is being deleted. 
    bIsRequired = 0  ; 
    bAddedRecord = 0 ; 
    processState = 0 ; 
    nCavities = 0 ; 

    bStockOverride = 0 ; // reset the override material stock warning
    bOutOfStock = 0 ; 
}

CMSJob::~CMSJob()
{
    cjobdrVec.clear() ; 
    methdrVec.clear() ; 
}

int CMSJob::DefaultSteelType(SteelTypeVec &stv, csString &deftype)
{
    steel = 0 ; 
    bSteelIsActual = false ; 
    for (int i=0; i < (int)stv.size(); i++)
    {
        int prelen = stv[i].prefix.size() ; 
        csString pre = mattype.Left(prelen) ; 
        if (pre == stv[i].prefix)
        {
            bSteelIsActual = true ; 
            steel = i+1 ; 
            return steel ; 
        }

        pre = deftype.Left(prelen) ; 
        if (pre == stv[i].prefix)
        {
            bSteelIsActual = true ; 
            steel = i+1 ; 
            return steel ; 
        }
    }

    if (mattype.Left(4) == "2714")
    {
        steel = STEEL_2714 ; 
    }
    else if (mattype.Left(4) == "H-13")
    {
        steel = STEEL_H13 ; 
    }
    else 
    {   // Set the steel type based on the type of part. 
        if (partname.Left(2) == "HD")
        {
            if (mattype.FindIDX("MA", 4) > 0 || mattype.FindIDX("PL", 4) > 0)
                steel = STEEL_H13 ;
            else if (mattype.Right(1) == "M" || mattype.Right(1) == "P")
                steel = STEEL_H13 ;
            else
                steel = STEEL_2714 ; 
        }
        else if (partname.Left(2) == "SD")
            steel = STEEL_H13 ;
        else if (partname.Left(2) == "FD")
            steel = STEEL_H13 ;
        else if (partname.Left(2) == "BA")
            steel = STEEL_2714 ;
        else if (partname.Left(2) == "BO")
            steel = STEEL_2714 ;
        else if (partname.Left(2) == "RI")
            steel = STEEL_2714 ;
    }
    return steel ; 
}

int CMSJob::AppendOpt(CMSOption &opt)
{
    if (opt.opttype == "CAVITIES")
    {
        nCavities = opt.qty ; 
    }

    optvec.push_back(opt) ; 
    return 0 ; 
}


int CMSJob::LoadRouting(CCMSDatabase &db, FILE *fplog)
{
    cjobdrVec.clear() ; 

    if (jobnum.size() == 0)
        return 0 ; // nothing to do. 

    int retcode = 0 ; 

    char qry[2048] ; 

    if (subCount > 1 && subCount < 10)
    {
        sprintf(qry, 
                "SELECT A.EDJOB#,A.EDSEQ#,A.EDLIN#,A.EDDEPT,A.EDRESC,A.EDOPNM,A.EDRUNS,A.EDSTAT"
                ",A.EDREPP,A.EDFUT5"
                " FROM %s.CJOBDR AS A"
                " WHERE A.EDJOB# = %s"
                " ORDER BY A.EDSEQ#", 
                    db.dbname, jobnum.c_str()) ; 
    }
    else
    {
        sprintf(qry, 
                "SELECT A.EDJOB#,A.EDSEQ#,A.EDLIN#,A.EDDEPT,A.EDRESC,A.EDOPNM,A.EDRUNS,A.EDSTAT"
                ",A.EDREPP,A.EDFUT5,B.EFMTLP,B.EFQPPC,B.EFUNIT,B.EFSTKL"
                " FROM %s.CJOBDR AS A LEFT JOIN %s.CJOBDM AS B"
                " ON A.EDJOB#=B.EFJOB# AND A.EDSEQ#=B.EFSEQ#"
                " WHERE A.EDJOB# = %s"
                " ORDER BY A.EDSEQ#", 
                    db.dbname, db.dbname, jobnum.c_str()) ; 
    }

    try
    {
        CSQLRecordset rs(db);
        rs << qry ; 
        rs.SQLExec();

        //  EDREPP - reporting point
        // JOB# SEQ# LIN# DEPT RES OP RUNSTD EDSTAT EDREPP EDFUT5 EFMTLP  EFQPPC  EFUNIT EFSTKL
        //  1    2    3    4    5  6    7       8     9      10      11     12      13     14 
        while (rs.SQLFetch())
        {
            RouteDataRec rec ; 

            csString tok ; 
            tok = rs.SQLGetData(1).c_str() ; 

            tok = rs.SQLGetData(2).c_str() ; 
            rec.seqno = atoi(tok.c_str()) ; 

            // int xx = 0 ; 
            // if (rec.seqno == 780)
            // {
            //     xx++ ; 
            // }

            tok = rs.SQLGetData(3).c_str() ; 
            rec.linenum = atoi(tok.c_str()) ; 

            rec.dept = rs.SQLGetData(4).c_str() ; 
            rec.dept.Trim() ;
            rec.plant = rec.dept.Left(3) ; 
            rec.dept.TrimLeft(3) ; 

            rec.resource = rs.SQLGetData(5).c_str() ; 
            rec.resource.Trim() ;

            rec.operation = rs.SQLGetData(6).c_str() ; 
            rec.operation.Trim() ;

            tok = rs.SQLGetData(7).c_str() ; 
            rec.runstd = atof(tok.c_str()) ; 

            rec.status = rs.SQLGetData(8).c_str() ; 
            rec.status.Trim() ;

            rec.reporting = rs.SQLGetData(9).c_str() ; 
            rec.reporting.Trim() ;

            tok = rs.SQLGetData(10).c_str() ; 
            rec.fut5 = atof(tok.c_str()) ; 

            if (subCount == 1)
            {
                rec.material = rs.SQLGetData(11).c_str() ; 
                rec.material.Trim() ; 
                
                tok = rs.SQLGetData(12).c_str() ; 
                rec.mtlqty = atof(tok.c_str()) ; 

                rec.mtlunits = rs.SQLGetData(13).c_str() ; 
                rec.mtlunits.Trim() ; 

                rec.mtlStkLoc = rs.SQLGetData(14).c_str() ; 
                rec.mtlStkLoc.Trim() ; 
            }
            else
            {
                rec.material.clear() ; 
                rec.mtlqty = 0 ; 
                rec.mtlunits.clear() ; 
                rec.mtlStkLoc.clear() ; 
            }


            if (rec.seqno > 0 && 
                rec.dept.size() &&
                rec.resource.size() &&
                rec.operation.size())
            {   // Then it is probably a valid record. 
                rec.actualRunTime = -1.0 ; 
                rec.bRunTimeProcessed = false ; 
                rec.bProcessed = false ; 
                rec.totalRunTime = 0.0 ; 
                rec.pendingRunTime = 0.0 ; 
                rec.qtydone = 0.0 ; 
                rec.qtyscrap = 0.0 ; 
                rec.qtysaw = 0.0 ; 
                rec.bModified = 0 ; 
                rec.starttime.m_nYear = 0 ;
                rec.serialnum = 0 ;
                rec.assignedSerial = 0 ; 
                rec.processedSerial = 0 ; 
                rec.bEventFound = 0 ; 
                rec.bRuntimeFound = 0 ; 
                rec.statflags = 0 ; 
                rec.bSetStdRunIfBlank = 0 ; 
                rec.bProcFlags = 0 ;

                cjobdrVec.push_back(rec) ; 
            }
        }
    }
    catch(CSQLException* e)
    {
        if (gCMSparms.pevp->fpLOG)
        {
            fprintf(gCMSparms.pevp->fpLOG, "SQL error %d loading routing details:\n%s\n",
                        (int)e->m_nRetCode, e->m_strError.c_str()) ;
            fprintf(gCMSparms.pevp->fpLOG, "        qry = '%s'\n", qry) ; 
            fflush(gCMSparms.pevp->fpLOG) ; 
        }

        retcode =  e->m_nRetCode ; 
    }
    catch(...)
    {
        retcode = -100 ; // unkown failure. 
    }

    return retcode ; 
}




// ************** CMSBOM Member Functions *************

void CMSBOM::SetJobParms(CMSJob &job)
{
    SetOrderNumber(job.jobnum.c_str()) ; 
    SetSeqNum(job.seqnum) ; 
    SetLineNum(job.linenum) ; 
    SetMaterial(job.partname.c_str()) ; 
}

// ************** CMSOrder Member Functions *************

CMSOrder::CMSOrder()
{
    clear() ; 
}

CMSOrder::CMSOrder(const CMSOrder &ord)
{
    orderNumber = ord.orderNumber ; 
    status = ord.status ; 

    jobvec = ord.jobvec ; 

    custCode = ord.custCode ; 
    custName = ord.custName ; 
    orderDate = ord.orderDate ; 
    reqdDate = ord.reqdDate ; 

    for (int i=0; i < 3; i++)
    {
        feederCount[i]     = ord.feederCount[i] ; 
        mandrelCount[i]    = ord.mandrelCount[i] ; 
        plateCount[i]      = ord.plateCount[i] ; 
        backerCount[i]     = ord.backerCount[i] ; 
        bolsterCount[i]    = ord.bolsterCount[i] ; 
        subbolsterCount[i] = ord.subbolsterCount[i] ; 
        ringCount[i]       = ord.ringCount[i] ; 
    }

    ijobFDR = -1 ; 
    ijobMND = -1 ; 
    ijobPLT = -1 ; 
    ijobBKR = -1 ; 
    ijobBOL = -1 ; 
    ijobSUB = -1 ; 
    ijobRNG = -1 ; 

    bHollowDie = ord.bHollowDie ; 

    for (int i=0; i < (int)jobvec.size(); i++)
    {
        if (jobvec[i].IsFeeder())
            ijobFDR = i ; 
        else if (jobvec[i].IsMandrel()) 
            ijobMND = i ; 
        else if (jobvec[i].IsPlate()) 
            ijobPLT = i ; 
        else if (jobvec[i].IsBacker()) 
            ijobBKR = i ; 
        else if (jobvec[i].IsBolster()) 
            ijobBOL = i ; 
        else if (jobvec[i].IsSubBolster()) 
            ijobSUB = i ; 
        else if (jobvec[i].IsDieRing()) 
            ijobRNG = i ; 
    }

    nCavities = ord.nCavities ; 

    fdrThk = ord.fdrThk ; 
    mndThk = ord.mndThk ; 
    pltThk = ord.pltThk ; 
    bkrThk = ord.bkrThk ; 
    bolThk = ord.bolThk ; 
    subThk = ord.subThk ; 
    rngThk = ord.rngThk ; 

    fdrDia = ord.fdrDia ; 
    mndDia = ord.mndDia ; 
    pltDia = ord.pltDia ; 
    bkrDia = ord.bkrDia ; 
    bolDia = ord.bolDia ; 
    subDia = ord.subDia ; 
    rngDia = ord.rngDia ; 

    bHasFDR = ord.bHasFDR ; 
    bHasMND = ord.bHasMND ; 
    bHasPLT = ord.bHasPLT ; 
    bHasBKR = ord.bHasBKR ; 
    bHasBOL = ord.bHasBOL ; 
    bHasSUB = ord.bHasSUB ; 
    bHasRNG = ord.bHasRNG ; 

    bCentreFeed = ord.bCentreFeed ; 
    bMultiCore  = ord.bMultiCore  ; 
    bOnePiece   = ord.bOnePiece   ; 
    bTripleSkim = ord.bTripleSkim ; 
    bSparkPlate = ord.bSparkPlate ;
    bHeatSink   = ord.bHeatSink   ; 
}

CMSOrder& CMSOrder::operator=(const CMSOrder &ord)
{
    orderNumber = ord.orderNumber ;
    status = ord.status ;

    jobvec = ord.jobvec ;

    custCode = ord.custCode ; 
    custName = ord.custName ; 
    orderDate = ord.orderDate ; 
    reqdDate = ord.reqdDate ; 

    bHollowDie = ord.bHollowDie ; 

    for (int i=0; i < 3; i++)
    {
        feederCount[i]     = ord.feederCount[i] ; 
        mandrelCount[i]    = ord.mandrelCount[i] ; 
        plateCount[i]      = ord.plateCount[i] ; 
        backerCount[i]     = ord.backerCount[i] ; 
        bolsterCount[i]    = ord.bolsterCount[i] ; 
        subbolsterCount[i] = ord.subbolsterCount[i] ; 
        ringCount[i]       = ord.ringCount[i] ; 
    }

    ijobFDR = -1 ; 
    ijobMND = -1 ; 
    ijobPLT = -1 ; 
    ijobBKR = -1 ; 
    ijobBOL = -1 ; 
    ijobSUB = -1 ; 
    ijobRNG = -1 ; 

    bHollowDie = ord.bHollowDie ; 

    for (int i=0; i < (int)jobvec.size(); i++)
    {
        if (jobvec[i].IsFeeder())
            ijobFDR = i ; 
        else if (jobvec[i].IsMandrel()) 
            ijobMND = i ; 
        else if (jobvec[i].IsPlate()) 
            ijobPLT = i ; 
        else if (jobvec[i].IsBacker()) 
            ijobBKR = i ; 
        else if (jobvec[i].IsBolster()) 
            ijobBOL = i ; 
        else if (jobvec[i].IsSubBolster()) 
            ijobSUB = i ; 
        else if (jobvec[i].IsDieRing()) 
            ijobRNG = i ; 
    }

    nCavities = ord.nCavities ; 

    fdrThk = ord.fdrThk ; 
    mndThk = ord.mndThk ; 
    pltThk = ord.pltThk ; 
    bkrThk = ord.bkrThk ; 
    bolThk = ord.bolThk ; 
    subThk = ord.subThk ; 
    rngThk = ord.rngThk ; 

    fdrDia = ord.fdrDia ; 
    mndDia = ord.mndDia ; 
    pltDia = ord.pltDia ; 
    bkrDia = ord.bkrDia ; 
    bolDia = ord.bolDia ; 
    subDia = ord.subDia ; 
    rngDia = ord.rngDia ; 

    bHasFDR = ord.bHasFDR ; 
    bHasMND = ord.bHasMND ; 
    bHasPLT = ord.bHasPLT ; 
    bHasBKR = ord.bHasBKR ; 
    bHasBOL = ord.bHasBOL ; 
    bHasSUB = ord.bHasSUB ; 
    bHasRNG = ord.bHasRNG ; 

    bCentreFeed = ord.bCentreFeed ;
    bMultiCore  = ord.bMultiCore  ;
    bOnePiece   = ord.bOnePiece   ;
    bTripleSkim = ord.bTripleSkim ;
    bSparkPlate = ord.bSparkPlate ;
    bHeatSink   = ord.bHeatSink   ;

    return *this ; 
}

CMSOrder::~CMSOrder()
{
    clear() ; 
}


void CMSOrder::clear() 
{
    orderNumber.clear() ; 
    status = 0 ; 
    
    custCode = "" ; 
    custName = "" ; 

    bHollowDie = 0 ; 

    jobvec.clear() ; 

    ijobFDR = -1 ; 
    ijobMND = -1 ; 
    ijobPLT = -1 ; 
    ijobBKR = -1 ; 
    ijobBOL = -1 ; 
    ijobSUB = -1 ; 
    ijobRNG = -1 ; 

    memset(feederCount,     0, sizeof(feederCount)) ; 
    memset(mandrelCount,    0, sizeof(mandrelCount)) ; 
    memset(plateCount,      0, sizeof(plateCount)) ; 
    memset(backerCount,     0, sizeof(backerCount)) ; 
    memset(bolsterCount,    0, sizeof(bolsterCount)) ; 
    memset(subbolsterCount, 0, sizeof(subbolsterCount)) ; 
    memset(ringCount,       0, sizeof(ringCount)) ; 

    nCavities = 0 ; 

    fdrThk = 0 ; 
    mndThk = 0 ; 
    pltThk = 0 ; 
    bkrThk = 0 ; 
    bolThk = 0 ; 
    subThk = 0 ; 
    rngThk = 0 ; 

    fdrDia = 0 ; 
    mndDia = 0 ; 
    pltDia = 0 ; 
    bkrDia = 0 ; 
    bolDia = 0 ; 
    subDia = 0 ; 
    rngDia = 0 ; 

    bHasFDR = 0 ; 
    bHasMND = 0 ; 
    bHasPLT = 0 ; 
    bHasBKR = 0 ; 
    bHasBOL = 0 ; 
    bHasSUB = 0 ; 
    bHasRNG = 0 ; 

    bCentreFeed = 0 ; 
    bMultiCore  = 0 ; 
    bOnePiece   = 0 ; 
    bTripleSkim = 0 ; 
    bSparkPlate = 0 ;
    bHeatSink   = 0 ; 

}

int CMSOrder::LoadDetails(CCMSDatabase &db)
{
    int retcode = 0 ;
    char qry[2048] ; 
    sprintf(qry, 
        "SELECT dcbcus,dcbnam,dcodat,dccdat FROM %s.ocrh WHERE dcord# = %s", 
            db.dbname, orderNumber.c_str()) ; 
    try
    {
        CSQLRecordset rs(db);
        rs << qry ; 
        rs.SQLExec();
        CMSOrder order ; 

        while (rs.SQLFetch())
        {
            custCode = rs.SQLGetData(1).c_str() ; 
            custCode.Trim() ;

            custName = rs.SQLGetData(2).c_str() ; 
            custName.Trim() ;

            struct tm tmval ; 
            CSQL_ConvertTime(rs.SQLGetData(3).c_str(), tmval) ; 
            orderDate.SetDateTime(&tmval) ; 

            CSQL_ConvertTime(rs.SQLGetData(4).c_str(), tmval) ; 
            reqdDate.SetDateTime(&tmval) ; 
        }
    }
    catch(CSQLException* e)
    {
        retcode =  e->m_nRetCode ; 
    }
    catch(...)
    {
        retcode = -100 ; // unkown failure. 
    }

    return retcode ; 
}


int CMSOrder::IsPartRec(CMSJob &job) 
{
    if (job.IsFeeder() || job.IsMandrel() || job.IsPlate() || job.IsBacker() || 
        job.IsBolster() || job.IsSubBolster() || job.IsDieRing())
        return 1 ; 
    return 0 ; 
}

int CMSOrder::PartIDXActual(char parttype)
{
    for (int i=0; i < (int)jobvec.size(); i++)
    {
        switch(parttype)
        {
            case FEEDER_PARTCODE :
                if (jobvec[i].partname.icFindIDX("FDR") >= 0 && jobvec[i].bSteelIsActual)
                    return i ;
                break ; 
            case MANDREL_PARTCODE : 
                if ((jobvec[i].partname.icFindIDX("MA", 4) >= 0 || 
                    (jobvec[i].partname.Left(1) == "H" && jobvec[i].partname.Right(1) == "M")) 
                        && jobvec[i].bSteelIsActual)
                    return i ; 
                break ; 
            case PLATE_PARTCODE :
                if ((jobvec[i].partname.icFindIDX("PL", 4) >= 0 ||
                    (jobvec[i].partname.icFindIDX("SD") == 0) ||
                    (jobvec[i].partname.Left(1) == "H" && jobvec[i].partname.Right(1) == "P"))
                        && jobvec[i].bSteelIsActual)
                        return i ; 
                break ; 
            case BACKER_PARTCODE :
                if ((jobvec[i].partname.icFindIDX("BA", 4) >= 0 || 
                    (jobvec[i].partname.Left(1) == "H" && jobvec[i].partname.Right(1) == "B"))
                        && jobvec[i].bSteelIsActual)
                        return i ; 
                break ; 
            case BOLSTER_PARTCODE :
                if (jobvec[i].partname.icFindIDX("BO") >= 0 && jobvec[i].bSteelIsActual)
                        return i ; 
                break ; 
            case SUBBOLSTER_PARTCODE :
                if (jobvec[i].partname.icFindIDX("SB") >= 0 && jobvec[i].bSteelIsActual)
                        return i ; 
                break ; 
            case RING_PARTCODE :
                if (jobvec[i].partname.icFindIDX("RI") >= 0 && jobvec[i].bSteelIsActual)
                        return i ; 
                break ; 
            default :
                return -1 ; // unknown parttype. 
        }
    }

    return -1 ; 
}


int CMSOrder::GetPartDims(CMSJob &job, double &dia, double &thk)
{
    dia = job.diam ; 
    thk = job.length ; 

    if (job.IsFeeder())
    {
        fdrDia = dia ; 
        fdrThk = thk ; 
        return 1 ; 
    }
    else if (job.IsMandrel()) 
    {
        mndDia = dia ; 
        mndThk = thk ; 
        return 1 ; 
    }
    else if (job.IsPlate()) 
    {
        pltDia = dia ; 
        pltThk = thk ; 
        return 1 ; 
    }
    else if (job.IsBacker()) 
    {
        bkrDia = dia ; 
        bkrThk = thk ; 
        return 1 ; 
    }
    else if (job.IsBolster()) 
    {
        bolDia = dia ; 
        bolThk = thk ; 
        return 1 ; 
    }
    else if (job.IsSubBolster()) 
    {
        subDia = dia ; 
        subThk = thk ; 
        return 1 ; 
    }
    else if (job.IsDieRing()) 
    {
        rngDia = dia ; 
        rngThk = thk ; 
        return 1 ; 
    }

    return 0 ;
}

double CMSOrder::GetDiam(csString &part)
{
    csString tok = part.NextToken(" ", 0) ; 
    tok = part.NextToken(" ") ; 
    tok.Trim(); 
    if (tok.size())
        return atof(tok.c_str()) ; 
    return 0.0 ; 
}

int CMSOrder::AppendJob(CMSJob &job, char **msg)
{
    jobvec.push_back(job) ; 
    int steel ;     // TODO - get rid of steel variable in this function 
    
    if (job.partname.Left(1) == "H")
        bHollowDie = TYPE_HOLLOW ;  

    if ((steel=job.IsFeeder()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            feederCount[0] += 1 ; 
            ijobFDR = (int)jobvec.size() - 1 ; 
            // jobFDR()->steel = steel ; 
            jobFDR()->diam   = fdrDia = GetDiam(job.partname) ; 
            jobFDR()->length = fdrThk = job.length ; 
            jobFDR()->parttype = TYPE_FDR | bHollowDie ;              
            bHasFDR = 1 ;
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            feederCount[1] += 1 ; 
            if (!jobFDR())
                ijobFDR = (int)jobvec.size() - 1 ; 
            jobFDR()->diam = fdrDia = GetDiam(job.partname) ; 
            jobFDR()->parttype = TYPE_FDR | bHollowDie ;              
            bHasFDR = 1 ;
        }
        else 
        {   // Adding brand new part not defined in sales. 
            feederCount[2] += 1 ; 
            if (!jobFDR())
                ijobFDR = (int)jobvec.size() - 1 ; 
            jobFDR()->diam = fdrDia = GetDiam(job.partname) ; 
            jobFDR()->parttype = TYPE_FDR | bHollowDie ;              
            bHasFDR = 1 ;
            if (msg)
            {
                *msg = 
                    "WARNING: You are trying to add a feeder which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }

    if ((steel=job.IsMandrel()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum  > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            mandrelCount[0] += 1 ; 
            ijobMND = (int)jobvec.size() - 1 ; 
            // jobMND()->steel = steel ; 
            jobMND()->diam   = mndDia = GetDiam(job.partname) ; 
            jobMND()->length = mndThk = job.length ; 
            jobMND()->parttype = TYPE_MND | bHollowDie ;              
            bHasMND = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            mandrelCount[1] += 1 ; 
            if (!jobMND())
                ijobMND = (int)jobvec.size() - 1 ; 
            jobMND()->parttype = TYPE_MND | bHollowDie ;              
            jobMND()->diam = mndDia = GetDiam(job.partname) ; 
            bHasMND = 1 ; 
        }
        else 
        {   // This is brand new part
            mandrelCount[2] += 1 ; 
            if (!jobMND())
                ijobMND = (int)jobvec.size() - 1 ; 
            jobMND()->parttype = TYPE_MND | bHollowDie ;              
            jobMND()->diam = mndDia = GetDiam(job.partname) ; 
            bHasMND = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a mandrel which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }
    if ((steel=job.IsPlate()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            plateCount[0] += 1 ; 
            ijobPLT = (int)jobvec.size() - 1 ; 
            // jobPLT()->steel = steel ; 
            jobPLT()->diam   = pltDia = GetDiam(job.partname) ; 
            jobPLT()->length = pltThk = job.length ; 
            jobPLT()->parttype = TYPE_PLT | bHollowDie ;              
            bHasPLT = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            plateCount[1] += 1 ; 
            if (!jobPLT())
                ijobPLT = (int)jobvec.size() - 1 ; 
            jobPLT()->diam = pltDia = GetDiam(job.partname) ; 
            jobPLT()->parttype = TYPE_PLT | bHollowDie ;              
            bHasPLT = 1 ; 
        }
        else 
        {   // This is brand new part
            plateCount[2] += 1 ; 
            if (!jobPLT())
                ijobPLT = (int)jobvec.size() - 1 ; 
            jobPLT()->diam = pltDia = GetDiam(job.partname) ; 
            jobPLT()->parttype = TYPE_PLT | bHollowDie ;              
            bHasPLT = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a plate which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }
    if ((steel=job.IsBacker()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            backerCount[0] += 1 ; 
            ijobBKR = (int)jobvec.size() - 1 ; 
            // jobBKR()->steel = steel ; 
            jobBKR()->diam   = bkrDia = GetDiam(job.partname) ; 
            jobBKR()->length = bkrThk = job.length ; 
            jobBKR()->parttype = TYPE_BKR | bHollowDie ;              
            bHasBKR = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            backerCount[1] += 1 ; 
            if (!jobBKR())
                ijobBKR = (int)jobvec.size() - 1 ; 
            jobBKR()->diam = bkrDia = GetDiam(job.partname) ; 
            jobBKR()->parttype = TYPE_BKR | bHollowDie ;              
            bHasBKR = 1 ; 
        }
        else 
        {   // This is brand new part
            backerCount[2] += 1 ; 
            if (!jobBKR())
                ijobBKR = (int)jobvec.size() - 1 ; 
            jobBKR()->diam = bkrDia = GetDiam(job.partname) ; 
            jobBKR()->parttype = TYPE_BKR | bHollowDie ;              
            bHasBKR = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a backer which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }
    if ((steel=job.IsBolster()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            bolsterCount[0] += 1 ; 
            ijobBOL = (int)jobvec.size() - 1 ; 
            // jobBOL()->steel = steel ; 
            jobBOL()->diam   = bolDia = GetDiam(job.partname) ; 
            jobBOL()->length = bolThk = job.length ; 
            jobBOL()->parttype = TYPE_BOL ; 
            bHasBOL = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            bolsterCount[1] += 1 ; 
            if (!jobBOL())
                ijobBOL = (int)jobvec.size() - 1 ; 
            jobBOL()->diam = bolDia = GetDiam(job.partname) ; 
            jobBOL()->parttype = TYPE_BOL ; 
            bHasBOL = 1 ; 
        }
        else 
        {   // This is brand new part
            bolsterCount[2] += 1 ; 
            if (!jobBOL())
                ijobBOL = (int)jobvec.size() - 1 ; 
            jobBOL()->diam = bolDia = GetDiam(job.partname) ; 
            jobBOL()->parttype = TYPE_BOL ; 
            bHasBOL = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a bolster which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }
    if ((steel=job.IsSubBolster()) != 0)
    {
        if (steel & 0x80)
            bHollowDie = TYPE_HOLLOW ; 
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            subbolsterCount[0] += 1 ; 
            ijobSUB = (int)jobvec.size() - 1 ; 
            // jobBOL()->steel = steel ; 
            jobSUB()->diam   = subDia = GetDiam(job.partname) ; 
            jobSUB()->length = subThk = job.length ; 
            jobSUB()->parttype = TYPE_SUB ; 
            bHasSUB = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            subbolsterCount[1] += 1 ; 
            if (!jobSUB())
                ijobSUB = (int)jobvec.size() - 1 ; 
            jobSUB()->diam = subDia = GetDiam(job.partname) ; 
            jobSUB()->parttype = TYPE_SUB ; 
            bHasSUB = 1 ; 
        }
        else 
        {   // This is brand new part
            subbolsterCount[2] += 1 ; 
            if (!jobSUB())
                ijobSUB = (int)jobvec.size() - 1 ; 
            jobSUB()->diam = subDia = GetDiam(job.partname) ; 
            jobSUB()->parttype = TYPE_SUB ; 
            bHasSUB = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a sub-bolster which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }
    if ((steel=job.IsDieRing()) != 0)
    {
        steel &= 0x0f ; 

        if (job.seqnum > 0 && job.seqnum <= gCMSparms.seqSplit)
        {   // Then this is the actual part and it was processed from before
            // This overrides the part definition
            ringCount[0] += 1 ; 
            ijobRNG = (int)jobvec.size() - 1 ; 
            // jobBOL()->steel = steel ; 
            jobRNG()->diam   = rngDia = GetDiam(job.partname) ; 
            jobRNG()->length = rngThk = job.length ; 
            jobRNG()->parttype = TYPE_RNG ; 
            bHasRNG = 1 ; 
        }
        else if (job.seqnum >= gCMSparms.seqMerge)
        {   // This is a definition type record
            ringCount[1] += 1 ; 
            if (!jobSUB())
                ijobSUB = (int)jobvec.size() - 1 ; 
            jobRNG()->diam = rngDia = GetDiam(job.partname) ; 
            jobRNG()->parttype = TYPE_RNG ; 
            bHasRNG = 1 ; 
        }
        else 
        {   // This is brand new part
            ringCount[2] += 1 ; 
            if (!jobSUB())
                ijobSUB = (int)jobvec.size() - 1 ; 
            jobRNG()->diam = rngDia = GetDiam(job.partname) ; 
            jobRNG()->parttype = TYPE_RNG ; 
            bHasRNG = 1 ; 
            if (msg)
            {
                *msg = 
                    "WARNING: You are adding a die-ring which is not\r\n"
                    "properly defined on the sales order. CHECK WITH DESIGN/SALES" ;
            }
        }
    }

    return 0 ; 
}

int CMSOrder::SetOptState(CMSOption &opt)
{
    if (opt.opttype == "CAVITIES")
    {
        nCavities = opt.qty ; 
    }
    else if (opt.IsTripleSkim())
    {
        bTripleSkim = true ; 
    }
    else if (opt.IsMultiCore())
    {
        bMultiCore = true ; 
    }
    else if (opt.IsOnePiece())
    {
        bOnePiece = true ; 
    }
    else if (opt.IsHeatSink())
    {
        bHeatSink = true ; 
    }
    else if (opt.IsCentreFeed())
    {
        bCentreFeed = true ; 
    }
    else if (opt.IsTripleSkim())
    {
        bTripleSkim = true ; 
    }

    return 0 ; 
}

// TODO this logic may have to be drastically enhanced or modified
// if the sequence number data is not cleaned up.

int CMSOrder::FindSeqSplitPart(int parttype)
{
    unsigned int i ; 
    for (i=0; i < jobvec.size(); i++)
    {
        if (jobvec[i].seqnum == gCMSparms.seqSplit && (jobvec[i].parttype & parttype)) 
            return 1 ; 
    }
    return -1 ; 
}

int CMSOrder::FindSeqMergePart(int parttype)
{
    unsigned int i ; 
    for (i=0; i < jobvec.size(); i++)
    {
        if (jobvec[i].seqnum >= gCMSparms.seqMerge && (jobvec[i].parttype & parttype)) 
            return i ; 
    }
    return -1 ; 
}

int CMSOrder::HasMasterComponents() 
{
    unsigned int i ; 
    for (i=0; i < jobvec.size(); i++)
    {
        if (jobvec[i].subCount > 1)
            return i ; 
    }
    return -1 ; 
}


int CMSOrder::HasSubWorkOrders() 
{
    unsigned int i ; 
    for (i=0; i < jobvec.size(); i++)
    {
        if (jobvec[i].subCount == 1)
            return i ; 
    }
    return -1 ; 
}


char CMSOrder::SingleSubPartType(int i)
{
    if (HasMasterComponents() >= 0)
        return 0 ; // Then this order has master and possibly sub-parts, thus not 
                   // a single sub-part type record. 

    // Now return the part for this job
    if (jobvec[i].IsMandrel())
        return 'M' ; 
    if (jobvec[i].IsSubPlate())
        return 'P' ; 
    if (jobvec[i].IsSubBacker())
        return 'B' ; 
    return 0 ; 
}

int CMSOrder::TopPriorityPartIndex()
{
    int topidx = -1 ; 
    if ((topidx = HasMasterComponents()) >= 0)
        return topidx ; // since there are master parts this is not an issue

    int i ; 
    int topPriVal = 999 ; // set to last priority
    for (i=0; i < (int)jobvec.size(); i++)
    {
        if (jobvec[i].IsPlate())
            return i ; // this is the top so no need to search further
        
        if (jobvec[i].IsMandrel())
        {
            if (topPriVal > 2)
            {
                topidx = i ; 
                topPriVal = 2 ; 
            }
        }
        else if (jobvec[i].IsFeeder())
        {
            if (topPriVal > 3)
            {
                topidx = i ; 
                topPriVal = 3 ; 
            }
        }
        else if (jobvec[i].IsBacker())
        {
            if (topPriVal > 4)
            {
                topidx = i ; 
                topPriVal = 4 ; 
            }
        }
        else if (jobvec[i].IsBolster())
        {
            if (topPriVal > 5)
            {
                topidx = i ; 
                topPriVal = 5 ; 
            }
        }
        else if (jobvec[i].IsSubBolster())
        {
            if (topPriVal > 6)
            {
                topidx = i ; 
                topPriVal = 6 ; 
            }
        }
        else if (jobvec[i].IsDieRing())
        {
            if (topPriVal > 7)
            {
                topidx = i ; 
                topPriVal = 7 ; 
            }
        }
    }

    return topidx ; 
}

bool CMSOrder::SingleSubIsNotTopPriority(int i)
{
    if (HasMasterComponents() >= 0)
        return false ; // Then this order has master and possibly sub-parts, thus not 
                   // a single sub-part type record. 

    // Now return the part for this job
    int topidx = TopPriorityPartIndex() ;
    if (topidx != i)
        return true ; 
    return false ; 
}



// Returns true if this order has already been released fully to the shop. 
bool CMSOrder::WasReleased()
{
    // The logic is different depending on whether or not sub-component 
    // parts exist. 
    if (HasMasterComponents() >= 0)
    {   // Then this is a hollow die, which means that the CAD department
        // is responsible for releasing the work orders for the 
        // sub-components, so we have to drill deeper to verify whether 
        // or not this has happened yet. 
        if (HasSubWorkOrders() >= 0)
            return true ; 
        return false ; 
    }

    // Else when a job does not have sub-components, then when sales 
    // releases the order, it is effectively completely released. 
    return true ; 
}


int CMSOrder::LoadMETHDR(CCMSDatabase &db, char *plant, FILE *fplog)
{
    if (jobvec.size() == 0)
        return 0 ; // nothing to do. 

    int retcode = 0 ; 
    unsigned int i ; 

    try {
    
        csString tok ; 

        // Load all the METHDR records       
        unsigned int njobs = (unsigned int)jobvec.size() ; 
        for (i=0; i < njobs ; i++)
        {
            assert(jobvec[i].subCount > 1) ; 
            jobvec[i].methdrVec.clear() ; 

            tok.clear() ; 

            char qry[2048] ; 
            sprintf(qry, 
                "SELECT AOSEQ#,AOLIN#,AODEPT,AORESC,AOOPNM,AORUNS,AOFUTC,AOREPP"
                " FROM %s.METHDR WHERE AOPART = '%s' AND AOPLNT = '%s' ORDER BY AOSEQ#", 
                    db.dbname, jobvec[i].mattype.c_str(), plant) ; 
            CSQLRecordset rs(db);
            rs << qry ; 
            rs.SQLExec();

            // JOB# SEQ# LIN# DEPT RES OP RUNSTD EDSTAT FUT5
            //  1    2    3    4    5  6    7       8    9
            while (rs.SQLFetch())
            {
                RouteDataRec rec ; 
                int fldNum = 1 ; 
                tok = rs.SQLGetData(fldNum++).c_str() ; 
                rec.seqno = atoi(tok.c_str()) ; 

                tok = rs.SQLGetData(fldNum++).c_str() ; 
                rec.linenum = atoi(tok.c_str()) ; 

                rec.dept = rs.SQLGetData(fldNum++).c_str() ; 
                rec.dept.Trim() ;
                rec.plant = rec.dept.Left(3) ; 
                rec.dept.TrimLeft(3) ; 

                rec.resource = rs.SQLGetData(fldNum++).c_str() ; 
                rec.resource.Trim() ;

                rec.operation = rs.SQLGetData(fldNum++).c_str() ; 
                rec.operation.Trim() ;

                tok = rs.SQLGetData(fldNum++).c_str() ; 
                rec.runstd = atof(tok.c_str()) ; 

                tok = rs.SQLGetData(fldNum++).c_str() ; 
                rec.fut5 = atof(tok.c_str()) ; 

                rec.reporting = rs.SQLGetData(fldNum++).c_str() ; 
                rec.reporting.Trim() ; 

                rec.status = status ; 

                rec.plant = plant ; 

                if (rec.seqno > 0 && 
                    rec.dept.size() &&
                    rec.resource.size() &&
                    rec.operation.size())
                {   // Then it is probably a valid record. 
                    rec.actualRunTime = -1.0 ; 
                    rec.bRunTimeProcessed = false ; 
                    rec.bProcessed = false ; 
                    jobvec[i].methdrVec.push_back(rec) ; 
                }
            }
        }
    }
    catch(CSQLException* e)
    {
        retcode =  e->m_nRetCode ; 
    }
    catch(...)
    {
        retcode = -100 ; // unkown failure. 
    }

    return retcode ; 
}

