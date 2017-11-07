// #include <ugutils.h>
#include <CSstdlibs/cslib.h>
#include <CSGeometry/cs_geometry.h>
// #include "Log.h"
#include "CMSBOMRTE.h"


bool PartNames(int dietype, char *prefix, char *suffix)
{
    prefix[0] = 0 ; 
    suffix[0] = 0 ; 

    if (dietype & TYPE_HOLLOW)
    {
        if (TYPE_MND & dietype)
        {
            strcpy(prefix, "HD") ; 
            strcpy(suffix, "MANDREL") ; 
            return true ; // found something
        }

        if (TYPE_PLT & dietype)
        {
            strcpy(prefix, "HD") ; 
            strcpy(suffix, "PLATE") ; 
            return true ; // found something
        }

        if (TYPE_BKR & dietype)
        {
            strcpy(prefix, "HD") ; 
            strcpy(suffix, "BACKER") ; 
            return true ; // found something
        }
    }

    if (TYPE_FDR & dietype)
    {
        strcpy(prefix, "FDR") ; 
        return true ; // found something
    }

    if (TYPE_MND & dietype)
    {   // This is an error condition
        return false ; 
    }

    if (TYPE_PLT & dietype)
    {
        strcpy(prefix, "SD") ; 
        return true ; // found something
    }

    if (TYPE_BKR & dietype)
    {
        strcpy(prefix, "BA") ; 
        return true ; // found something
    }

    if ((TYPE_BOL | TYPE_SUB) & dietype)
    {
        strcpy(prefix, "BO") ; 
        return true ; // found something
    }

    if (TYPE_RNG & dietype)
    {
        strcpy(prefix, "RI") ; 
        return true ; // found something
    }

    return false ; 
}


csString FormatFloatStr(const csString &strFloat)
{
    csString strTmp = strFloat ;
    strTmp.Trim();

    int pos = strTmp.FindIDX('.');
    if (pos != -1)
    {
        int nLen = strTmp.size();

        while (nLen >= pos)
        {
            if (strTmp[ nLen - 1 ] == '0'
                || strTmp[ nLen - 1 ] == '.')
            {
                --nLen;
            }
            else
            {
                break;
            }
        }

        strTmp = strTmp.Mid(0, nLen);
    }

    return strTmp;
}

/*
bool SplitPart(const std::string &strSrc, std::string &strType, double *pdblDiam, double *pdblThick)
{
    strType.clear();

    csString strPart = strSrc.c_str();
    strPart.Trim();

    if (pdblDiam != NULL) *pdblDiam = 0.0;
    if (pdblThick != NULL) *pdblThick = 0.0;

    int pos = strPart.FindIDX(' ');
    if (pos != -1)
    {
        strType = strPart.Mid(0, pos).Trim().c_str();

        int pos2 = strPart.FindIDX('X', pos);
        if (pos2 != -1)
        {
            if (pdblDiam != NULL) *pdblDiam = atof(strPart.Mid(pos, pos2 - pos).c_str());

            if (pdblThick != NULL) *pdblThick = atof(strPart.Mid(pos2 + 1).c_str());
        }

        return true;
    }

    return false;
}
*/

CMSBOMRTE::CMSBOMRTE(void)
{
    dbName[0] = 0 ; 
    szFlatFileDir[0] = 0 ; 
    szFlatFilePrefix[0] = 0 ;
    NCTimesDir[0] = 0 ; 
    ncFileDigits = 0 ; 
    oIDX = 0 ; 
    FFtmpnum = 1 ; 
    skipStockCheck = 0 ; 
    firstRun = 0 ;
}

CMSBOMRTE::~CMSBOMRTE(void)
{
    m_db.Close();
    FreeOrderList();
}

void CMSBOMRTE::FreeOrderList(void)
{
    for (size_t i = 0; i < m_vecWorkOrderList.size(); ++i)
    {
        free(m_vecWorkOrderList[ i ]);
    }

    m_vecWorkOrderList.clear();
}

char emptyEntry[] = " " ; 

CS_CharPtrVec CMSBOMRTE::ActiveOrdersList(void) 
{
    CS_CharPtrVec ptrlist ; 
    ptrlist.push_back(emptyEntry) ; 
    for (size_t i=0; i < activeOrders.size(); i++)
        ptrlist.push_back(activeOrders[i].orderNumber.str) ; 
    return ptrlist ; 
}

bool CMSBOMRTE::InitSteelTypes()
{
    steelvec.clear() ; 

    // Predefine the two main steel types. 
    SteelType st ; 
    st.prefix = "H-13" ; 
    steelvec.push_back(st) ; 
    st.prefix = "2714" ; 
    steelvec.push_back(st) ; 

    char qrytmp[256] ; 

    _snprintf(qrytmp, 256, 
            "SELECT STLCODE FROM %s.STLTYPE WHERE PLANT='%s'", 
                    m_db.dbname, gCMSparms.plantID)   ;  

    // strcpy(steelvec[0].

    bool retcode = true ; 
    int retry = 0 ; 
    while (retry++ < 4)
    {

        retcode = true ; 
        try
        {
            CSQLRecordset rs(GetDatabase());
            rs << qrytmp ; 
            rs.SQLExec();
            while (rs.SQLFetch())
            {
                csString steelstr = rs.SQLGetData(1).c_str() ; 
                steelstr.Trim() ;

                bool found = false ; 
                for (size_t i=0; i < steelvec.size(); i++)
                {
                    if (steelvec[i].prefix == steelstr)
                    {
                        found = true ; 
                        break ; 
                    }
                }

                if (!found)
                {
                    st.prefix = steelstr ; 
                    steelvec.push_back(st) ; 
                }
            }

            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4000, "CMSBOMRTE::InitSteelTypes errorcode = %d, msg = %s\r\n", 
                            e->m_nRetCode, e->m_strError.c_str());
            msg[4000] = 0 ; 
            msg[4001] = 0 ; 
            LogError(msg) ; 
            e->Delete();

            GetDatabase().Reconnect() ; 
            retcode = false;
        }
    }

    return retcode ; 
}

/*
    int retcode = true ; 
    int retry = 0 ; 
    while (retry++ < 4)
    {

        GetDatabase().Reconnect() ; 
        retcode = false;

*/

void CMSBOMRTE::CorrectSteelTypes(CMSOrder &order)
{
    // Match up the exact steel types
    for (size_t i=0; i < order.jobvec.size(); i++)
    {
        if (order.jobvec[i].bSteelIsActual == false)
        {   // Then look for the actual steel type
            int actIDX = order.PartIDXActual(order.jobvec[i].partcode) ; 
            if (actIDX >= 0)
                order.jobvec[i].steel = order.jobvec[actIDX].steel ; 
        }
    }
}

// if ordernumber is null then load all active orders. 
bool CMSBOMRTE::InitOrderList(const char *ordernumber)
{
    activeOrders.clear() ; 
    FreeOrderList();

    /*
        SELECT dnjob,a.dnstat,dnpart,dnord#,efseq#,efqppc,c.awdes1,b.efmtlp,b.eflin#,b.efpart FROM excophase1.cjobh AS a
            LEFT JOIN excophase1.cjobdm AS b ON a.dnjob = b.efjob#
            LEFT JOIN excophase1.stkmp AS c ON b.efmtlp = c.awpart
            WHERE a.dnstat <> 'C' ORDER BY dnord#

     */

    char qrytmp[4096] ; 

    if (ordernumber)
    {
        _snprintf(qrytmp, 4000, 
            //       1       2       3       4     5       6       7       8         9       10       11      12       13
            "SELECT dnjob,a.dnstat,dnpart,dnord#,efseq#,efqppc,c.awdes1,b.efmtlp,b.eflin#,b.efpart,a.dnnmat,d.dcstat,e.aqmtlp   "
            " FROM %s.cjobh AS a"
            " LEFT JOIN %s.cjobdm AS b ON a.dnjob = b.efjob#"
            " LEFT JOIN %s.stkmp AS c ON b.efmtlp = c.awpart"
            " LEFT JOIN %s.ocrh AS d ON a.dnord# = d.dcord#"
            " LEFT JOIN %s.METHDM as e ON (e.AQPART = b.EFMTLP and e.AQPLNT= a.DNPLNT)" 
            " WHERE a.dnstat <> 'C' AND a.dnord# = %s ORDER BY dnord#", 
                m_db.dbname, m_db.dbname, m_db.dbname, m_db.dbname, m_db.dbname, ordernumber) ;
    }
    else
    {
        _snprintf(qrytmp, 4000, 
            //       1       2       3       4     5       6       7       8         9       10       11      12        13
            "SELECT dnjob,a.dnstat,dnpart,dnord#,efseq#,efqppc,c.awdes1,b.efmtlp,b.eflin#,b.efpart,a.dnnmat,d.dcstat,e.aqmtlp  "
            " FROM %s.cjobh AS a"
            " LEFT JOIN %s.cjobdm AS b ON a.dnjob = b.efjob#"
            " LEFT JOIN %s.stkmp AS c ON b.efmtlp = c.awpart"
            " LEFT JOIN %s.ocrh AS d ON a.dnord# = d.dcord#"
            " LEFT JOIN %s.METHDM as e ON (e.AQPART = b.EFMTLP and e.AQPLNT= a.DNPLNT)" 
            " WHERE a.dnstat <> 'C' ORDER BY dnord#", 
                        m_db.dbname, m_db.dbname, m_db.dbname, m_db.dbname, m_db.dbname)   ;  
    }

    csString lastJobNum ; 


    /*
        "SELECT distinct a.dcord#,a.dcstat FROM excophase1.ocrh AS a"
        " LEFT JOIN excophase1.cjobh AS b ON a.dcord# = b.dnord#"
        " WHERE a.dcstat <> 'C' AND b.dnord# IS NOT NULL" ; 
     */


    bool retcode = true ; 
    int retry = 0 ; 
    while (retry++ < 4)
    {

        retcode = true ; 

        try
        {
            CSQLRecordset rs(GetDatabase());
            rs << qrytmp ; 
            rs.SQLExec();
            CMSOrder order ; 

            while (rs.SQLFetch())
            {
                csString jobnum = rs.SQLGetData(1).c_str() ; 
                jobnum.Trim() ;

                csString status = rs.SQLGetData(2).c_str() ;
                status.Trim() ;

                csString part = rs.SQLGetData(3).c_str() ;
                part.Trim() ; 

                csString ordnum = rs.SQLGetData(4).c_str() ;
                ordnum.Trim() ; 

                csString seqnum = rs.SQLGetData(5).c_str() ;
                seqnum.Trim() ; 

                if (seqnum.size() == 0)
                    continue ; // if undefined then data is corrupted. 

                csString length = rs.SQLGetData(6).c_str() ;
                length.Trim() ; 

                csString matdesc = rs.SQLGetData(7).c_str() ;
                matdesc.Trim() ; 

                csString mattype = rs.SQLGetData(8).c_str() ;
                mattype.Trim() ; 

                csString linenum = rs.SQLGetData(9).c_str() ;
                linenum.Trim() ; 

                csString partname = rs.SQLGetData(10).c_str() ;
                partname.Trim() ; 

                csString subCount ; 
                csString jobStatus ; 
                subCount = rs.SQLGetData(11).c_str() ;
                subCount.Trim() ; 

                jobStatus = rs.SQLGetData(12).c_str() ;
                jobStatus.Trim() ; 

                csString defmattype = rs.SQLGetData(13).c_str() ;
                defmattype.Trim() ; 

                if (jobnum.size() && ordnum.size())
                {   // Then save the job record. 
                    if (order.orderNumber != ordnum)
                    {
                        if (order.orderNumber.size() > 0)
                        {   // Then this is a new order number, save the current order
                            CorrectSteelTypes(order) ;
                            order.LoadDetails(GetDatabase()) ; 
                            activeOrders.push_back(order) ; 
                            order.clear() ; 
                        }
                        else
                        {   // This is is the very first order
                            // Nothing special to do right now. 
                        }

                        order.orderNumber = ordnum ; 
                        order.status = status[0] ; 
                    }

                    // Add the job data for the order. 
                    CMSJob job ; 
                    order.status = jobStatus[0] ;
                    job.jobnum = jobnum ; 
                    job.length = length.size() ? atof(length.c_str()) : 0.0 ; 
                    if (!partname.size())
                        job.partname = part ; 
                    else
                        job.partname = partname ; 
                    job.mattype = mattype ; 
                    job.seqnum = atoi(seqnum.c_str()) ; 
                    job.SetPartCode() ; 
                    job.linenum = linenum.size() ? atoi(linenum.c_str()) : 0 ; 
                    job.DefaultSteelType(steelvec, defmattype) ; 
                    job.subCount = atoi(subCount.c_str()) ; 

                    order.AppendJob(job); 
                }
            }
            
            if (order.orderNumber.size() > 0)
            {   // Save the last working order. 
                CorrectSteelTypes(order) ;
                order.LoadDetails(GetDatabase()) ; 
                activeOrders.push_back(order) ; 
            }

            break ; 
        }
        catch (CSQLException* e)
        {
            char msg[4096] ; 
            _snprintf(msg, 4000, "CMSBOMRTE::InitOrderList database errorcode = %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str());
            msg[4000] = 0 ; 
            msg[4001] = 0 ; 
            LogError(msg) ; 
            e->Delete();

            LogError(qrytmp) ; 
            LogError("\r\n") ; 

            GetDatabase().Reconnect() ; 
            retcode = false;
        }
    }

    return true;
}


int CMSBOMRTE::LoadFeaturesAndOptions()
{
    int retcode = 0 ; 
    int i, j ; 
    csString qry ;
    for (i=0; i < (int)activeOrders.size(); i++)
    {
        // Create a list of unique order numbers
        // map<csString, int> jobset ; 
        // for (j=0; j < (int)activeOrders[i].jobvec.size(); j++)
        // {
        //     csString jobnum = activeOrders[i].jobvec[j].jobnum ; 
        //     jobset[jobnum] = j ; 
        // }
        // map<csString, int>::iterator ijob ; 
        // for (ijob = jobset.begin(); ijob != jobset.end(); ijob++)


        for (j=0; j < (int)activeOrders[i].jobvec.size() ; j++)
        {   // Now have to loop through each part in the order
            CMSJob *pjob = &(activeOrders[i].jobvec[j]) ; 
            
                            //        1       2     3      4     
            qry.clear() ;
            qry =  "SELECT r0lstn,r0fcde,r0ocde,r0qtyr FROM " ; 
            qry += m_db.dbname ; 
            qry += ".food WHERE r0lstn = '" + pjob->jobnum + "'" ; 
            
            int retry = 0 ; 
            while (retry++ < 4)
            {
                retcode = 0 ;

                try
                {
                    CSQLRecordset rs(GetDatabase()) ;
                    rs << qry.c_str() ; 
                    rs.SQLExec();
                    CMSOption opt ; 

                    while (rs.SQLFetch())
                    {
                        csString jobnum = rs.SQLGetData(1).c_str() ;
                        jobnum.Trim() ; 

                        opt.opttype= rs.SQLGetData(2).c_str() ;
                        opt.opttype.Trim() ;

                        opt.optname= rs.SQLGetData(3).c_str() ;
                        opt.optname.Trim() ;

                        opt.qty = rs.nSQLGetData(4) ; 
                        
                        // Filter out duplicate cavity counts, since a plate 
                        // and a backer for example would both have 2 cavities 
                        // but we only need to see this number once since they
                        // will always match for both parts. CAVCOUNTCHECK
                        if (opt.opttype == "CAVITIES" && opt.optname == "HOLES")
                        {   // Set the number of cavities for the overall job    
                            activeOrders[i].nCavities = opt.qty ; 
                        }

                        activeOrders[i].SetOptState(opt) ; 
                        pjob->AppendOpt(opt) ; 
                        // activeOrders[i].jobvec[ijob->second].AppendOpt(opt) ; 
                    }

                    break ; 
                }
                catch (CSQLException* e)
                {
                    char msg[4096] ; 
                    _snprintf(msg, 4000, "CMSBOMRTE::LoadFeaturesAndOptions database errorcode = %d, msg = %s\r\n", e->m_nRetCode, e->m_strError.c_str()) ;
                    msg[4000] = 0 ; 
                    msg[4001] = 0 ; 
                    LogError(msg) ; 
                    e->Delete();

                    LogError(qry.c_str()) ; 
                    LogError("\r\n") ; 

                    GetDatabase().Reconnect() ; 
                    retcode = -1 ;
                }
            }
        }
    }

    return retcode ; 
}



//! Add the fixed TURNED BLANK feature
int AddTurnedBlank(CMSJob *pjob)
{
    CMSOption opt ; 
    opt.opttype = "XXTRNDBLANK" ;
    opt.optname = "STD" ; // this is ignored. 
    opt.qty = 1 ; 
    pjob->AppendOpt(opt) ; 
    return 0 ; 
}


int AddHardenedBlank(CMSJob *pjob)
{
    CMSOption opt ; 
    opt.opttype = "XXHRDBLANK" ;
    opt.optname = "STD" ; // this is ignored. 
    opt.qty = 1 ; 
    pjob->AppendOpt(opt) ; 
    return 0 ; 
}


int CMSBOMRTE::PartsAlreadyExist(CMSOrder &ord) 
{
    for (int i=0; i < (int)ord.jobvec.size(); i++)
    {
        if (ord.jobvec[i].seqnum > 0 && 
            ord.jobvec[i].seqnum <= gCMSparms.seqSplit)
        {   // This is an actual part in process
            return 1 ; 
        }
    }

    return 0 ; 
}

int CMSBOMRTE::FindMatchingPartRec(CMSJob &job, CMSOrder &ord)
{
    for (int i=0; i < (int)ord.jobvec.size(); i++)
    {
        if (job.seqnum  >= gCMSparms.seqMerge && 
            job.jobnum  == ord.jobvec[i].jobnum && 
            job.seqnum  == ord.jobvec[i].seqnum && 
            job.mattype == ord.jobvec[i].mattype)
        {
            return i ; 
        }
        else if (job.seqnum > 0 && 
                 job.seqnum   <= gCMSparms.seqSplit && 
                 job.jobnum   == ord.jobvec[i].jobnum && 
                 job.seqnum   == ord.jobvec[i].seqnum && 
                 job.partname == ord.jobvec[i].partname)
        {
            return i ; 
        }
    }

    return -1 ; // not found
}


int CMSBOMRTE::OutputLengthUpdateRecs(FILE *fp, CMSOrder &oldord, CMSOrder &neword)
{
    int i ; 
    for (i=0; i < (int)neword.jobvec.size(); i++)
    {
        if (neword.jobvec[i].IsFeeder())
            neword.jobvec[i].bIsRequired = neword.bHasFDR ? true : false ; 
        else if (neword.jobvec[i].IsPlate())
            neword.jobvec[i].bIsRequired = neword.bHasPLT ? true : false ; 
        else if (neword.jobvec[i].IsMandrel())
            neword.jobvec[i].bIsRequired = neword.bHasMND ? true : false ; 
        else if (neword.jobvec[i].IsBacker())
            neword.jobvec[i].bIsRequired = neword.bHasBKR ? true : false ; 
        else if (neword.jobvec[i].IsBolster())
            neword.jobvec[i].bIsRequired = neword.bHasBOL ? true : false ; 
        else if (neword.jobvec[i].IsSubBolster())
            neword.jobvec[i].bIsRequired = neword.bHasSUB ? true : false ; 
        else if (neword.jobvec[i].IsDieRing())
            neword.jobvec[i].bIsRequired = neword.bHasRNG ? true : false ; 
    }

    // Verify material is in stock
    bool noStock = false ; 
    for (i=0; i < (int)oldord.jobvec.size(); i++)
    {
        int ni = FindMatchingPartRec(oldord.jobvec[i], neword) ; 
        if (ni < 0) 
            continue ; // not found, can't deal with it. 

        if (oldord.jobvec[i].seqnum > 0 && 
            oldord.jobvec[i].seqnum <= gCMSparms.seqSplit)
        {
            if (neword.jobvec[ni].bIsRequired)
            {
                double dia ; 
                double thk ; 
                neword.GetPartDims(neword.jobvec[ni], dia, thk) ;
                // tcomp NEQ
                
                // TODO TURNEDBLANKS - update stock check logic

                csString barPartNum ; 
                if (CS_NEQ(oldord.jobvec[i].diam, dia) ||
                    oldord.jobvec[i].steel != neword.jobvec[ni].steel)
                {   // Then we need to verify the stock material is still valid
                    // for this part. Thus must lookup the stock (this causes
                    // a DB lookup so want to avoid it if possible). 
                    barPartNum = FindBarStock(neword.jobvec[ni].steel, 
                                              neword.jobvec[ni].diam,
                                              neword.jobvec[ni].length,
                                              neword.jobvec[ni].statFlags) ;
                }
                else
                {   // Nothing changed
                    barPartNum = oldord.jobvec[i].mattype ; 
                }

                // Now check for stock
                if (!MaterialInStock(neword.jobvec[ni], barPartNum))
                {
                    neword.jobvec[ni].bOutOfStock = 1 ; 
                    noStock = true ; 
                }
            }
        }
    }

    if (noStock)
        return -1 ; 

    for (i=0; i < (int)oldord.jobvec.size(); i++)
    {
        int ni = FindMatchingPartRec(oldord.jobvec[i], neword) ; 
        if (ni < 0) 
            continue ; // not found, can't deal with it. 

        if (oldord.jobvec[i].seqnum > 0 && 
            oldord.jobvec[i].seqnum <= gCMSparms.seqSplit)
        {
            if (neword.jobvec[ni].bIsRequired)
            {
                double dia ; 
                double thk ; 
                neword.GetPartDims(neword.jobvec[ni], dia, thk) ;
                // tcomp NEQ

                csString barPartNum ; 
                if (CS_NEQ(oldord.jobvec[i].diam, dia) ||
                    oldord.jobvec[i].steel != neword.jobvec[ni].steel)
                {   // Then we need to verify the stock material is still valid
                    // for this part. Thus must lookup the stock (this causes
                    // a DB lookup so want to avoid it if possible). 
                    barPartNum = FindBarStock(neword.jobvec[ni].steel, 
                                              neword.jobvec[ni].diam,
                                              neword.jobvec[ni].length,
                                              neword.jobvec[ni].statFlags) ;
                }
                else
                {   // Nothing changed
                    barPartNum = oldord.jobvec[i].mattype ; 
                }

                if (((thk - 0.001) > oldord.jobvec[i].length) ||
                    ((thk + 0.001) < oldord.jobvec[i].length) ||
                    (barPartNum != oldord.jobvec[i].mattype))
                {
                    neword.jobvec[ni].length = thk ; 

                    CMSBOM bom ; 
                    bom.Init() ; 
                    bom.SetJobParms(neword.jobvec[ni]) ; 
                    bom.SetAction(ACTION_UPDATE) ; 
                    // For update length records the material has to reference the bar stock 
                    bom.SetMaterial(barPartNum.c_str()) ; 
                    if (neword.jobvec[ni].IsPartBlank())
                        bom.SetQty(1.0, "EA") ;
                    else
                        bom.SetQty(neword.jobvec[ni].length, "IN") ; 
                    bom.CRLF() ;
                    bom.Write(fp) ; 
                }
            }
            else
            {   // We are deleting an existing record. 
                CMSBOM bom ; 
                bom.Init() ; 
                bom.SetJobParms(oldord.jobvec[i]) ; 
                bom.SetAction(ACTION_DELETE) ; 
                // For update length records the material has to reference the bar stock 
                bom.SetMaterial(oldord.jobvec[i].mattype.c_str()) ; 
                bom.CRLF() ;
                bom.Write(fp) ; 
            }
        }
        else if (oldord.jobvec[i].seqnum >= gCMSparms.seqMerge)
        {   // Then we need to test the delete condition only 
            // since for updates only the SEQ# 040 records matter. 
            if (!neword.jobvec[ni].bIsRequired)
            {   // Nothing 
                CMSBOM bom ; 
                bom.Init() ; 
                bom.SetJobParms(oldord.jobvec[i]) ; 
                bom.SetAction(ACTION_DELETE) ; 
                // For update length records the material has to reference the bar stock 
                bom.SetMaterial(oldord.jobvec[i].mattype.c_str()) ; 
                bom.CRLF() ;
                bom.Write(fp) ; 
            }
        }
    }

    // Now see if we have added any new parts. 
    // The data structure should be reworked so we don't need part 
    // specific function calls. 
    int retcode = 0 ; 
    retcode += TestAddFeeder (fp, oldord, neword) ; 
    retcode += TestAddPlate  (fp, oldord, neword) ; 
    retcode += TestAddMandrel(fp, oldord, neword) ; 
    retcode += TestAddBacker (fp, oldord, neword) ; 
    retcode += TestAddBolster(fp, oldord, neword) ; 
    retcode += TestAddSub    (fp, oldord, neword) ; 
    retcode += TestAddRing   (fp, oldord, neword) ; 
    
    return retcode ; 
}



int CMSBOMRTE::TestAddFeeder (FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasFDR)
        return 0 ; // nothing to do

    double dia, thk ; 
    neword.GetPartDims(*(neword.jobFDR()), dia, thk) ; 
    csString barPartNum = FindBarStock(neword.jobFDR()->steel, 
                                       dia, thk,
                                       neword.jobFDR()->statFlags) ;

    if (!MaterialInStock(*(neword.jobFDR()), barPartNum)) 
    {
        neword.jobFDR()->bOutOfStock = 1 ; 
        return -1 ; 
    }

    return 0 ; 
}

int CMSBOMRTE::TestAddMandrel(FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasMND)
        return 0 ; // nothing to do

    int retcode = 0 ; 
    int i ; 
    // TODO - have to clean this up potentially to deal with different 
    // Sequence Split values
    if (oldord.FindSeqSplitPart(TYPE_MND) < 0)
    {   // Then we need to add a mandrel to the overall job. 
        // Should never get here really. 
        if ((i = oldord.FindSeqMergePart(TYPE_MND)) >= 0)
        {
            retcode = CreateAddSubPart(fp, neword, i) ;
        }
        else
        {
            CMSJob job ; 
            job.bIsRequired = true ;
            job.bAddedRecord = true ; 

            job.seqnum = gCMSparms.seqMerge ; 
            job.diam = neword.jobMND()->diam ; 
            job.length = neword.jobMND()->length ; 
            job.partcode = MANDREL_PARTCODE ; 
            job.parttype = TYPE_MND ; 
            job.steel = neword.jobMND()->steel ; 
            int parttype = TYPE_MND | TYPE_HOLLOW ; 
            job.partname = BuildPartName(parttype, neword, job) ; 
            job.bStockOverride = neword.jobMND()->bStockOverride ; 
            neword.AppendJob(job); 
            CMSJob *pjob = &(neword.jobvec[neword.jobvec.size() - 1]) ;
            retcode = CreatePartAddRecord(fp, *pjob) ;
        }
    }

    return retcode ; 
}

int CMSBOMRTE::TestAddPlate (FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasPLT)
        return 0 ; // nothing to do

    int i ; 
    int retcode = 0 ; 
    if (oldord.FindSeqSplitPart(TYPE_PLT) < 0)
    {   // Then we need to add a plate to the overall job. 
        if ((i = oldord.FindSeqMergePart(TYPE_PLT)) >= 0)
        {
            retcode = CreateAddSubPart(fp, neword, i) ;
        }
        else
        {   // Trying to create/release a brand new part here. 
            CMSJob job ; 
            job.bIsRequired = true ;
            job.bAddedRecord = true ; 

            job.seqnum = gCMSparms.seqMerge ; 
            job.diam = neword.jobPLT()->diam ; 
            job.length = neword.jobPLT()->length ; 
            job.partcode = PLATE_PARTCODE ; 
            job.parttype = TYPE_PLT ; 
            job.steel = neword.jobPLT()->steel ; 
            int parttype = TYPE_PLT | oldord.bHollowDie ; 
            job.bStockOverride = neword.jobPLT()->bStockOverride ; 
            job.partname = BuildPartName(parttype, neword, job) ; 

            neword.AppendJob(job); 
            CMSJob *pjob = &(neword.jobvec[neword.jobvec.size() - 1]) ;
            retcode = CreatePartAddRecord(fp, *pjob) ;
        }
    }

    return retcode ; 
}

int CMSBOMRTE::TestAddBacker (FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasBKR)
        return 0 ; // nothing to do

    int i ; 
    int retcode = 0 ; 
    if (oldord.FindSeqSplitPart(TYPE_BKR) < 0)
    {   // Then we need to add a backer to the overall job. 
        if ((i = oldord.FindSeqMergePart(TYPE_BKR)) >= 0)
        {
            retcode = CreateAddSubPart(fp, neword, i) ;
        }
        else
        {
            CMSJob job ; 
            job.bIsRequired = true ;
            job.bAddedRecord = true ; 

            job.seqnum = gCMSparms.seqMerge ; 
            job.diam = neword.jobBKR()->diam ; 
            job.length = neword.jobBKR()->length ; 
            job.partcode = BACKER_PARTCODE ; 
            job.parttype = TYPE_BKR ; 
            job.steel = neword.jobBKR()->steel ; 
            int parttype = TYPE_BKR | oldord.bHollowDie ; 
            job.bStockOverride = neword.jobBKR()->bStockOverride ; 
            job.partname = BuildPartName(parttype, neword, job) ; 

            neword.AppendJob(job); 
            CMSJob *pjob = &(neword.jobvec[neword.jobvec.size() - 1]) ;
            retcode = CreatePartAddRecord(fp, *pjob) ;
        }
    }

    return retcode ; 
}

int CMSBOMRTE::TestAddBolster (FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasBOL)
        return 0 ; // nothing to do

    double dia, thk ; 
    neword.GetPartDims(*(neword.jobBOL()), dia, thk) ; 
    csString barPartNum = FindBarStock(neword.jobBOL()->steel, 
                                       dia, thk, 
                                       neword.jobBOL()->statFlags) ;

    if (!MaterialInStock(*(neword.jobBOL()), barPartNum)) 
    {
        neword.jobBOL()->bOutOfStock = 1 ; 
        return -1 ; 
    }

    return 0 ; 
}


int CMSBOMRTE::TestAddSub(FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasSUB)
        return 0 ; // nothing to do

    double dia, thk ; 
    neword.GetPartDims(*(neword.jobSUB()), dia, thk) ; 
    csString barPartNum = FindBarStock(neword.jobSUB()->steel, 
                                       dia, thk, 
                                       neword.jobSUB()->statFlags) ;

    if (!MaterialInStock(*(neword.jobSUB()), barPartNum)) 
    {
        neword.jobSUB()->bOutOfStock = 1 ; 
        return -1 ; 
    }

    return 0 ; 
}


int CMSBOMRTE::TestAddRing(FILE *fp, CMSOrder &oldord, CMSOrder &neword) 
{
    if (!neword.bHasRNG)
        return 0 ; // nothing to do

    double dia, thk ; 
    neword.GetPartDims(*(neword.jobRNG()), dia, thk) ; 
    csString barPartNum = FindBarStock(neword.jobRNG()->steel, 
                                       dia, thk, 
                                       neword.jobRNG()->statFlags) ;

    if (!MaterialInStock(*(neword.jobRNG()), barPartNum)) 
    {
        neword.jobRNG()->bOutOfStock = 1 ; 
        return -1 ; 
    }


    return 0 ; 
}


//! Returns an error code. This will only be called when adding a 
//! part that doesn't currently exist within the order. 
int CMSBOMRTE::CreatePartAddRecord(FILE *fp, CMSJob &job)
{
    csString barPartNum = FindBarStock(job.steel, job.diam, job.length, job.statFlags) ;
    if (!MaterialInStock(job, barPartNum))
    {
        job.bOutOfStock = 1 ; 
        return -1 ; 
    }

    CMSBOM bom ;
    bom.Init() ;
    bom.SetJobParms(job) ;
    bom.SetAction(ACTION_ADD) ;

    // For update length records the material has to reference the bar stock 
    bom.SetOper('3') ; // create and release
    bom.SetMaterial(job.mattype.c_str()) ;
    bom.SetQty(1) ;
    job.GetTmpJobNumber(FFtmpnum) ; 
    bom.SetTempWork(job.tmpjobnum.c_str()) ;
    bom.CRLF() ;
    bom.Write(fp) ;

    // Now create the actual update record. 
    CMSBOM bom2 ;
    bom2.Init() ;
    bom2.SetJobParms(job) ;
    bom2.SetOrderNumber(job.tmpjobnum.c_str()) ;
    bom2.SetAction(ACTION_UPDATE) ;
    bom2.SetOper('1') ; // no change
    bom2.SetSeqNum(gCMSparms.seqSplit) ;
    bom2.SetLineNum(1) ; // will always be this

    // csString barPartNum = FindBarStock("H-13", job.diam) ; // CHANGED Sep 14, 2009
    bom2.SetMaterial(barPartNum.c_str()) ;
    if (job.IsPartBlank())
        bom2.SetQty(1.0, "EA") ;
    else
        bom2.SetQty(job.length, "IN") ;
    bom2.CRLF() ;
    bom2.Write(fp) ;

    return 0 ;
}


int CMSBOMRTE::CreateAddSubPart(FILE *fp, CMSOrder &ord, int i)
{
    int retcode = 0 ; 
    if (ord.jobvec[i].seqnum >= gCMSparms.seqMerge && ord.IsPartRec(ord.jobvec[i]))
    {   // Then this was the original part order number
        // Found it, create the update length record

        double dia, thk ; 
        ord.GetPartDims(ord.jobvec[i], dia, thk) ; 
        csString barPartNum = FindBarStock(ord.jobvec[i].steel, 
                                           dia, thk, 
                                           ord.jobvec[i].statFlags) ;

        if (!MaterialInStock(ord.jobvec[i], barPartNum)) 
        {
            ord.jobvec[i].bOutOfStock = 1 ; 
            return -1 ; 
        }

        CMSBOM bom ; 
        bom.Init() ; 
        bom.SetJobParms(ord.jobvec[i]) ; 
        bom.SetAction(ACTION_UPDATE) ; 

        // For update length records the material has to reference the bar stock 
        bom.SetOper('3') ; // create and release

        // Need to search for the best match on HD plt's, mnd's and bkr's and sub in 
        // the matching part for the mattype string. 

        csString bestMatchPart = FindBestPart(ord.jobvec[i], ord.jobvec[i].mattype, thk) ; 

        bom.SetMaterial(bestMatchPart.c_str()) ; 
        bom.SetQty(1) ; 
        ord.jobvec[i].GetTmpJobNumber(FFtmpnum) ; 
        bom.SetTempWork(ord.jobvec[i].tmpjobnum.c_str()) ; 
        bom.CRLF() ;
        bom.Write(fp) ; 

        // Now create the actual update record. 
        CMSBOM bom2 ; 
        bom2.Init() ; 
        bom2.SetJobParms(ord.jobvec[i]) ; 
        bom2.SetOrderNumber(ord.jobvec[i].tmpjobnum.c_str()) ; 
        bom2.SetAction(ACTION_UPDATE) ; 
        bom2.SetOper('1') ; // no change 
        bom2.SetSeqNum(gCMSparms.seqSplit) ; 
        bom2.SetLineNum(1) ; // will always be this
        bom2.SetMaterial(barPartNum.c_str()) ; 
        if (ord.jobvec[i].IsPartBlank())
            bom2.SetQty(1.0, "EA") ;
        else
            bom2.SetQty(thk, "IN") ; 
        bom2.CRLF() ;
        bom2.Write(fp) ; 
    }
    return retcode ; 
}


int CMSBOMRTE::OutputMaterialRecs(FILE *fp, CMSOrder &ord)
{
    for (int i=0; i < (int)ord.jobvec.size(); i++)
    {
        if (ord.jobvec[i].seqnum >= gCMSparms.seqMerge && ord.IsPartRec(ord.jobvec[i]))
        {   // Then this was the original part order number
            // Found it, create the update length record
            CMSBOM bom ; 
            bom.Init() ; 
            bom.SetJobParms(ord.jobvec[i]) ; 
            bom.SetAction(ACTION_UPDATE) ; 

            // For update length records the material has to reference the bar stock 
            bom.SetOper('3') ; // create and release
            bom.SetMaterial(ord.jobvec[i].mattype.c_str()) ; 
            bom.SetQty(1) ; 
            ord.jobvec[i].GetTmpJobNumber(FFtmpnum) ; 
            bom.SetTempWork(ord.jobvec[i].tmpjobnum.c_str()) ; 
            bom.CRLF() ;
            bom.Write(fp) ; 

            // Now create the actual update record. 
            CMSBOM bom2 ; 
            bom2.Init() ; 
            bom2.SetJobParms(ord.jobvec[i]) ; 
            bom2.SetOrderNumber(ord.jobvec[i].tmpjobnum.c_str()) ; 
            bom2.SetAction(ACTION_UPDATE) ; 
            bom2.SetOper('1') ; // no change 
            bom2.SetSeqNum(gCMSparms.seqSplit) ; 
            bom2.SetLineNum(1) ; // will always be this
            double dia, thk ; 
            ord.GetPartDims(ord.jobvec[i], dia, thk) ; 

            csString barPartNum = FindBarStock(ord.jobvec[i].steel, dia, thk, ord.jobvec[i].statFlags) ;
            bom2.SetMaterial(barPartNum.c_str()) ; 
            if (ord.jobvec[i].IsPartBlank())
                bom2.SetQty(1.0, "EA") ;
            else
                bom2.SetQty(thk, "IN") ; 
            bom2.CRLF() ;
            bom2.Write(fp) ; 
        }
    }
 
    return 0 ; 
}




//! By comparing the previous value to the new we can create the proper flat file
//! for final processing. 
int CMSBOMRTE::ProcessFlatFile(FILE *fp, CMSOrder &origOrd, CMSOrder &updOrd)
{
    // FFtmpnum = 1 ; 

    // ======== New version ==========
    // BOM RECORDS   jobvec.push
    int njobs = (int)updOrd.jobvec.size() ; 
    for (int i=0; i < (int)updOrd.jobvec.size(); i++)
        updOrd.jobvec[i].bOutOfStock = 0 ; 
    
    njobs = (int)updOrd.jobvec.size() ; 
    if (OutputLengthUpdateRecs(fp, origOrd, updOrd) < 0)
        return -1 ; // out of stock

    // RTE RECORDS
    njobs = (int)updOrd.jobvec.size() ; 
    ProcessRoutingRecords(fp, updOrd) ; 

    // Old version of the code

    /*
    int partsExist = PartsAlreadyExist(origOrd) ; 
    if (partsExist)
    {   // Then we need to create update records. 
        // Create update records for the lengths that have changed. 
        OutputLengthUpdateRecs(fp, origOrd, updOrd) ; 
    }
    else
    {   // Then none of the parts within the order have been released yet. 
        // This will only happen for order with an 'HD xxxxx' type part
        // SD and other types of parts will have jobs released to the shop 
        // directly since there is no sub-assembly to those components. 
        OutputMaterialRecs(fp, updOrd) ; 
    }
    */

    return 0 ; 
}


int CodesMatch(csString &pat, csString &test)
{
    if (pat[0] == '*')
    {
        if (pat.size() == 1)
            return 1 ; 
        
        csString pcs(pat.str + 1) ; 
        csString cstest(test) ; 
        if (cstest.ToUpper() == pcs.Right(cstest.size()).ToUpper()) 
            return 1 ; 
    }
    else
    {
        if (pat.Right(1) == "*") 
        {   
            csString pcs(pat) ; 
            pcs.TrimRight(1) ; 
            if (test.Left(pcs.size()).ToUpper() == pcs.ToUpper()) 
                return 1 ; 
        }
        else if(pat == test)
        {   // Strings match
            return 1 ; 
        }
    }

    return 0 ; 
}

// MODE 1 means that the order wasn't released or that we are adding somehing
// MODE 2 indicates that we are changing something, so see if we have to proceed or not
#define RTEMODE_METHDR    1      // USE METHDR RECORD
#define RTEMODE_CJOBDR    2      // USE CJOBDR RECORDS 

inline void CMSBOMRTE::WriteRTEChanges(FILE *fpout,
                                       CMSOrder &ord, 
                                       int ijob, 
                                       int iopt, 
                                       RoutingCondRec &rcrec,
                                       int mode) 
{
    bool bWasReleased = ord.WasReleased() ; 

    for (int k=0; k < (int)rcrec.drecs.size(); k++)
    {
        RouteDataRec *prcondrec = &(rcrec.drecs[k]) ;

        int bFoundMatch = 0 ; // 1=if found and exists, else 0
        RouteDataRec *pdbrec = 0 ; 

        // TODO - add extra filtering on these comparisons. 

        if (bWasReleased || mode == RTEMODE_CJOBDR)
        {
            for (int ii=0; ii < (int)ord.jobvec[ijob].cjobdrVec.size(); ii++) 
            {
                pdbrec = &ord.jobvec[ijob].cjobdrVec[ii] ;
                if (!pdbrec->bProcessed && 
                    ((prcondrec->seqno == pdbrec->seqno) || (prcondrec->seqno == 0)) &&
                    CodesMatch(prcondrec->dept, pdbrec->dept) &&
                    CodesMatch(prcondrec->resource, pdbrec->resource) &&
                    CodesMatch(prcondrec->operation, pdbrec->operation))
                {
                    pdbrec->bProcessed = true ; 
                    bFoundMatch = 1 ;
                    break ;
                }
            }
        }
        else
        {   // Need to search through the METHDR records since the CJOBDR table
            // won't have any relevant information yet. 
            unsigned int ii ; 
            for (ii=0; ii < ord.jobvec[ijob].methdrVec.size(); ii++) 
            {
                pdbrec = &ord.jobvec[ijob].methdrVec[ii] ;
                if (!pdbrec->bProcessed && 
                    ((prcondrec->seqno == pdbrec->seqno) || (prcondrec->seqno == 0)) &&
                    CodesMatch(prcondrec->dept, pdbrec->dept) &&
                    CodesMatch(prcondrec->resource, pdbrec->resource) &&
                    CodesMatch(prcondrec->operation, pdbrec->operation))
                {
                    pdbrec->bProcessed = true ;
                    bFoundMatch = 1 ;
                    break ;
                }
            }
        }

        if ((prcondrec->command == ROUTE_ADD && !bFoundMatch) ||
            (prcondrec->command == ROUTE_DEL && bFoundMatch) ||
            (prcondrec->command == ROUTE_MOD && bFoundMatch))
        {   // Then condition for actually doing something exists so
            // output the action record. Note that the command is
            // defined within the prrec record.

            double *pUGTime = 0 ;
            if (prcondrec->command != ROUTE_DEL)
            {   // Search for a matching timemap record entry with an 
                // updated run time stamp. 
                
                // If there is a UG run time available then pass that
                // to the SetRoutingParms function so that this new updated
                // time is included in the data. 

                RouteDataRecMapItr rmi ; 

                // First reset all the actual run time values.
                for (rmi=timemap.begin(); rmi != timemap.end(); rmi++)
                {
                    RouteDataRec *ptimerec = &(rmi->second) ; 
                    if ((ptimerec->partCode == ord.jobvec[ijob].partcode) &&
                        (ptimerec->seqno    == prcondrec->seqno) &&
                        (ptimerec->actualRunTime >= 0.0) &&
                        (ptimerec->bRunTimeProcessed == false))
                    {   // Found a run time update record 
                        pUGTime = &(ptimerec->actualRunTime) ; 
                        ptimerec->bRunTimeProcessed = true ; 
                        break ; 
                    }
                }
            }

            CMSRTE rte ;
            rte.Init() ;
            rte.SetRoutingParms( ord, ijob, iopt, *prcondrec, *pdbrec,  pUGTime) ;
            rte.Write(fpout) ;
        }
    }
}

// For each job (part in the order) go through and output all the required
// routing update records. 
int CMSBOMRTE::ProcessRoutingRecords(FILE *fp, CMSOrder &ord)
{   
    // Now output routing updates

    // jobvec are all the work orders
    // For each work order 

    LoadNCTimes(ord) ; 

    // Look up all the UG run time for this job. 

    // During this processing we have to maintain a set of parts and sequence
    // numbers that were output as routing updates. Then anything that is 
    // left over must be processed for time map corrections. All ADD/MOD 
    // records that are processed because of a feature/option trigger need
    // to have time adjustments applied on the fly so that we don't have to
    // deal with the same records twice.

    // =====================================
    // 1) Load CJOBDR and METHDR if required
    // =====================================

    unsigned int i ; 
    for (i=0; i < ord.jobvec.size(); i++)
    {
        ord.jobvec[i].LoadRouting(m_db, 0) ;

        // Now check to see if we have mandrel master parts and whether the 
        // sub-parts also exist within the data read back or if only the 
        // master is defined. 
    }

    bool bWasReleased = ord.WasReleased() ; 
    if (!bWasReleased)
    {   // Then need to load the METHDR records
        ord.LoadMETHDR(m_db, plant, 0) ; 
    }

    int njobs = (int)ord.jobvec.size() ; 
    for (int i=0; i < njobs ; i++)
    {
        if (!ord.jobvec[i].bIsRequired || !ord.IsPartRec(ord.jobvec[i]))
            continue ; 


        if ((!bWasReleased && ord.jobvec[i].seqnum >= gCMSparms.seqMerge) || 
            ord.jobvec[i].bAddedRecord)
        {   // Process any routing specific changes specific to this part. 

            // -------------------------------------------------------------
            // This section is for sub assembly type components only where the 
            // routing data being added is to a master hollow die for example.
            // These jobs have not really been fully released yet since the 
            // sub component sequence number changes to the merge point value
            // once the job is released. WARNGING: If Solarsoft modifies their
            // logic here things would have to change accordingly. This is 
            // very kludgey type logic, but trying to get the required info
            // from Solarsoft to do this correctly would be next to impossible. 
            // -------------------------------------------------------------
            
            // This will contain all RTE (CJOBDR) records currently defined
            // for this part. It will only be loaded once. 
            size_t j ; 

            // Reset the condition state, see bDefined definition for more info
            for (j=0; j < rcondvec.size(); j++)
                rcondvec[j].bDefined = false ;

            // Loop through all features and options on the order
            for (j=0; j < ord.jobvec[i].optvec.size(); j++)
            {
                // Search for any positive condition records. 
                unsigned int irv ; 
                for (irv = 0; irv < rcondvec.size(); irv++)
                {
                    if (!rcondvec[irv].Matches(ord.jobvec[i].optvec[j].opttype.c_str(),
                                             ord.jobvec[i].optvec[j].optname.c_str(), 
                                             ord.custCode.c_str(), 
                                             ord.jobvec[i].diam, 
                                             ord.jobvec[i].partcode)
                        || rcondvec[irv].inverted)
                    {   // Then this is not a match so continue searching
                        continue ; 
                    }

                    if (rcondvec[irv].bDefined)
                        continue ; // then already was processed so skip it. 

                    /*
                        Old version only found the first hit.
                    int irv = FindRoutingRec(rcondvec,
                                    ord.jobvec[i].optvec[j].opttype.c_str(), 
                                    ord.jobvec[i].optvec[j].optname.c_str(), 
                                    ord.custCode.c_str(), 
                                    ord.jobvec[i].diam, 
                                    ord.jobvec[i].partcode) ; 
                    */

                    // -----------------------------------------------------------------
                    // ---------------------- FOUND MATCHING CONDITION -----------------
                    // -----------------------------------------------------------------
                    // Then we found a matching condition for this part/feature/option
                    // combination. 
                    rcondvec[irv].bDefined = true ; // mark it so that it is skipped later

                    // TODO - load all the CJOBDR records for this part and then output
                    // RTE records based on the contents of the database. If the records
                    // already exists in the database, then we don't want to re-create it.
                    // Also, we will only delete and update records if required. 


                    /*
                        The possible conditions are as follows:

                        FUNCTION   STATE       ACTION
                          ADD       none        ADD record
                          ADD       exists      nothing
                          DEL       none        nothing
                          DEL       exists      DEL record
                          MOD       none        nothing
                          MOD       exists      MOD record

                        So drive things from the drecs[] array which is the FUNCTION 
                        column. The state is determined from reading the cjobdr 
                        array. Then set the action and create the record. 
                            
                     */

                    WriteRTEChanges(fp, ord, (int)i, (int)j, rcondvec[irv], RTEMODE_METHDR) ;
                    if (!rcondvec[irv].bNonTerminating)
                        break ; // then we are done
                }
            }

            if (ord.jobvec[i].optvec.size() == 0)
            {   // Then we won't even get through the above operations and thus 
                // won't see the wildcard type operations that are not dependent
                // on features and options. Thus loop through to find any global
                // operations and process these. 
                unsigned int irv ; 
                for (irv = 0; irv < rcondvec.size(); irv++)
                {
                    if (!rcondvec[irv].Matches("", "", // only wildcard matches possible
                                             ord.custCode.c_str(), 
                                             ord.jobvec[i].diam, 
                                             ord.jobvec[i].partcode)
                        || rcondvec[irv].inverted)
                    {   // Then this is not a match so continue searching
                        continue ; 
                    }

                    if (rcondvec[irv].bDefined)
                        continue ; // then already was processed so skip it. 

                    /*
                        Old version only found the first hit.
                        int irv = FindRoutingRec(rcondvec,
                                    ord.jobvec[i].optvec[j].opttype.c_str(), 
                                    ord.jobvec[i].optvec[j].optname.c_str(), 
                                    ord.custCode.c_str(), 
                                    ord.jobvec[i].diam, 
                                    ord.jobvec[i].partcode) ; 
                    */

                    // -----------------------------------------------------------------
                    // ---------------------- FOUND MATCHING CONDITION -----------------
                    // -----------------------------------------------------------------
                    // Then we found a matching condition for this part/feature/option
                    // combination. 
                    rcondvec[irv].bDefined = true ; // mark it so that it is skipped later

                    // See if the data already exists within the CJOBDR records
                    WriteRTEChanges(fp, ord, (int)i, (int)j, rcondvec[irv], RTEMODE_METHDR) ;

                    if (!rcondvec[irv].bNonTerminating)
                        break ; // then we are done
                }
            }


            // Finally process all the inverted routing conditions
            for (j=0; j < rcondvec.size(); j++)
            {   // RoutingCondRec
                if (!rcondvec[j].inverted || rcondvec[j].bDefined)
                    continue ; 
                
                // Feature and option wasn't found so this can now be ignored
                if (!rcondvec[j].Matches("*", "*", ord.custCode.c_str(), 
                                        ord.jobvec[i].diam, ord.jobvec[i].partcode))
                {   // Then this record does match the other needed conditions so
                    // there is nothing to process. 
                    continue ; 
                }

                // Don't really need this here since it is the last time we use this flag
                // but if more logic is added later this will help prevent bugs, and 
                // it helps keep the data consistent. 
                rcondvec[j].bDefined = true ; 

                // Otherwise, this routing condition has a part type 
                // designator which is valid for this inverted rule. 


                // TODO - load all the CJOBDR records for this part and then output
                // RTE records based on the contents of the database. If the records
                // already exists in the database, then we don't want to re-create it.
                // Also, we will only delete and update records if required. 

                /*
                    The possible conditions are as follows:

                    FUNCTION   STATE       ACTION
                        ADD       none        ADD record
                        ADD       exists      nothing
                        DEL       none        nothing
                        DEL       exists      DEL record
                        MOD       none        nothing
                        MOD       exists      MOD record

                    So drive things from the drecs[] array which is the FUNCTION 
                    column. The state is determined from reading the cjobdrVec
                    array. Then set the action and create the record. 
                        
                */
                WriteRTEChanges(fp, ord, (int)i, -1, rcondvec[j], RTEMODE_METHDR) ;

            } // End inverted condition rule search loop

            // The last step is to go through all the RTE records and see
            // if any have updated run times that still haven't been 
            // output as updated RTE records yet. 
            RouteDataRecMapItr rmi ; 
            for (rmi=timemap.begin(); rmi != timemap.end(); rmi++)
            {
                RouteDataRec *ptimerec = &rmi->second ; 
                if (ptimerec->bRunTimeProcessed ||
                    ptimerec->actualRunTime < 0.0 ||
                    ptimerec->partCode != ord.jobvec[i].partcode)
                {   // Then there is no need to process this record
                    continue ; 
                }
                
                // Else must create an update record 
                if (bWasReleased)
                {
                    // Find the CJOBDR record that matches this one. 
                    for (j=0; j < ord.jobvec[i].cjobdrVec.size(); j++)
                    {
                        if (ord.jobvec[i].cjobdrVec[j].seqno == ptimerec->seqno)
                        {   // This is the record we're looking for. 
                            RouteDataRec *prrec = &(ord.jobvec[i].cjobdrVec[j]) ;
                            ptimerec->bRunTimeProcessed = true ; 
                            double *pUGTime = &(ptimerec->actualRunTime) ; 

                            prrec->command = ROUTE_MOD ; 

                            CMSRTE rte ;
                            rte.Init() ;
                            rte.SetRoutingParms( ord, (int)i, -1, *prrec, *prrec, pUGTime) ;
                            rte.Write(fp) ;
                        }
                    }
                }
                else
                {   // Find the METHDR record that matches
                    for (j=0; j < ord.jobvec[i].methdrVec.size(); j++)
                    {
                        if (ord.jobvec[i].methdrVec[j].seqno == ptimerec->seqno)
                        {   // This is the record we're looking for. 
                            RouteDataRec *prrec = &(ord.jobvec[i].methdrVec[j]) ;
                            ptimerec->bRunTimeProcessed = true ; 
                            double *pUGTime = &(ptimerec->actualRunTime) ; 

                            prrec->command = ROUTE_MOD ; 

                            CMSRTE rte ;
                            rte.Init() ;
                            rte.SetRoutingParms( ord, (int)i, -1, *prrec, *prrec, pUGTime) ;
                            rte.Write(fp) ;
                        }
                    }
                }
            }
        } // end if initial job release type setup
        else if (bWasReleased && 
                ord.jobvec[i].seqnum > 0 && 
                ord.jobvec[i].seqnum <= gCMSparms.seqSplit)
        {   // Do the processing for jobs that have already been fully released.
            // In this situation we want to see if there are any records that need
            // to be updated. The only thing that will change here is if there is 
            // a part that was added or if the run time processing has changed. 

            // We have to check the CJOBDR records to make sure they correspond to the
            // required routing changes and updates. The METHDR records are ignored
            // in this mode since the METHDR data should already be included in the 
            // CJOBDR records for those jobs that are released. 
            
            unsigned int j ; 

            // NOTE  - identical logic to above but we pass RTEMODE_CJOBDR instead
            // Could combine the two code sections and just set parm to pass this 
            // single mode.

            // Reset the condition state, see bDefined definition for more info
            for (j=0; j < rcondvec.size(); j++)
                rcondvec[j].bDefined = false ;

            for (j=0; j < rsingvec.size(); j++)
                rsingvec[j].bDefined = false ;

            for (j=0; j < rnomastvec.size(); j++)
                rnomastvec[j].bDefined = false ;

            // Loop through all features and options on the order
            for (j=0; j < ord.jobvec[i].optvec.size(); j++)
            {
                // Search for any positive condition records. 
                unsigned int irv ; 
                for (irv = 0; irv < rcondvec.size(); irv++)
                {
                    if (!rcondvec[irv].Matches(ord.jobvec[i].optvec[j].opttype.c_str(),
                                             ord.jobvec[i].optvec[j].optname.c_str(), 
                                             ord.custCode.c_str(), 
                                             ord.jobvec[i].diam, 
                                             ord.jobvec[i].partcode)
                        || rcondvec[irv].inverted)
                    {   // Then this is not a match so continue searching
                        continue ; 
                    }

                    if (rcondvec[irv].bDefined)
                        continue ; // then already was processed so skip it. 

                    // -----------------------------------------------------------------
                    // ---------------------- FOUND MATCHING CONDITION -----------------
                    // -----------------------------------------------------------------
                    // Then we found a matching condition for this part/feature/option
                    // combination. 
                    rcondvec[irv].bDefined = true ; // mark it so that it is skipped later

                    WriteRTEChanges(fp, ord, (int)i, (int)j, rcondvec[irv], RTEMODE_CJOBDR) ;
                    if (!rcondvec[irv].bNonTerminating)
                        break ; // then we are done
                }
            }

            if (ord.jobvec[i].optvec.size() == 0)
            {   // Then we won't even get through the above operations and thus 
                // won't see the wildcard type operations that are not dependent
                // on features and options. Thus loop through to find any global
                // operations and process these. 
                unsigned int irv ; 
                for (irv = 0; irv < rcondvec.size(); irv++)
                {
                    if (!rcondvec[irv].Matches("", "", // only wildcard matches possible
                                             ord.custCode.c_str(), 
                                             ord.jobvec[i].diam, 
                                             ord.jobvec[i].partcode)
                        || rcondvec[irv].inverted)
                    {   // Then this is not a match so continue searching
                        continue ; 
                    }

                    if (rcondvec[irv].bDefined)
                        continue ; // then already was processed so skip it. 


                    // -----------------------------------------------------------------
                    // ---------------------- FOUND MATCHING CONDITION -----------------
                    // -----------------------------------------------------------------
                    // Then we found a matching condition for this part/feature/option
                    // combination. 
                    rcondvec[irv].bDefined = true ; // mark it so that it is skipped later

                    // See if the data already exists within the CJOBDR records
                    WriteRTEChanges(fp, ord, (int)i, (int)j, rcondvec[irv], RTEMODE_CJOBDR) ;

                    if (!rcondvec[irv].bNonTerminating)
                        break ; // then we are done
                }
            }

            // Finally process all the inverted routing conditions
            for (j=0; j < rcondvec.size(); j++)
            {   // RoutingCondRec
                if (!rcondvec[j].inverted || rcondvec[j].bDefined)
                    continue ; 
                
                // Feature and option wasn't found so this can now be ignored
                if (!rcondvec[j].Matches("*", "*", ord.custCode.c_str(), 
                                        ord.jobvec[i].diam, ord.jobvec[i].partcode))
                {   // Then this record does match the other needed conditions so
                    // there is nothing to process. 
                    continue ; 
                }

                // Otherwise, this routing condition has a part type 
                // designator which is valid for this inverted rule. 

                /*
                    The possible conditions are as follows:

                    FUNCTION   STATE       ACTION
                        ADD       none        ADD record
                        ADD       exists      nothing
                        DEL       none        nothing
                        DEL       exists      DEL record
                        MOD       none        nothing
                        MOD       exists      MOD record

                    So drive things from the drecs[] array which is the FUNCTION 
                    column. The state is determined from reading the cjobdrVec
                    array. Then set the action and create the record. 
                        
                */
                WriteRTEChanges(fp, ord, (int)i, -1, rcondvec[j], RTEMODE_CJOBDR) ;

            } // End inverted condition rule search loop


            // Now do the processing with respect to single sub-parts. We only do
            // this if this is a hollow die assembly sub-part and the order has no
            // master part.  CMSOrder
            char subPartType = 0 ; 
            if ((subPartType = ord.SingleSubPartType((int)i)) >  0)
            {   // Then there are no master parts and this is a single sub part
                // Loop through and process all the single sub parts that match
                for (j=0; j < rsingvec.size(); j++)
                {
                    if (rsingvec[j].parts.FindIDX(subPartType) >= 0)
                    {   // Then this matches
                        WriteRTEChanges(fp, ord, (int)i, -1, rsingvec[j], RTEMODE_CJOBDR) ;
                    }
                }
            }


            // ********************************************************************
            //   No master part processing logic
            // ********************************************************************
            // This is where we deal with single parts (solid dies mainly, hollow dies
            // are OK because they have master parts) and delete redundant CAD/CAM and 
            // inspection routing steps based on a priority scheme. 

            if (ord.SingleSubIsNotTopPriority((int)i))
            {   // Then there are no master parts and this is a single sub part
                // Loop through and process all the single sub parts that match
                for (j=0; j < rnomastvec.size(); j++)
                {
                    WriteRTEChanges(fp, ord, (int)i, -1, rnomastvec[j], RTEMODE_CJOBDR) ;
                }
            }
                
            // Do time map adjustments as required. 
            RouteDataRecMapItr rmi ; 
            for (rmi=timemap.begin(); rmi != timemap.end(); rmi++)
            {
                RouteDataRec *ptimerec = &rmi->second ; 
                if (ptimerec->bRunTimeProcessed ||
                    ptimerec->actualRunTime < 0.0 ||
                    ptimerec->partCode != ord.jobvec[i].partcode)
                {   // Then there is no need to process this record
                    continue ; 
                }
                
                // Else must create an update record 
                // Find the CJOBDR record that matches this one. 
                unsigned int j ; 
                for (j=0; j < ord.jobvec[i].cjobdrVec.size(); j++)
                {
                    if (ord.jobvec[i].cjobdrVec[j].seqno == ptimerec->seqno)
                    {   // This is the record we're looking for. 
                        RouteDataRec *prrec = &(ord.jobvec[i].cjobdrVec[j]) ;
                        ptimerec->bRunTimeProcessed = true ; 

                        if (RunTimesDifferent(ptimerec->actualRunTime, ord.jobvec[i].cjobdrVec[j].runstd))
                        {
                            double *pUGTime = &(ptimerec->actualRunTime) ; 
                            prrec->command = ROUTE_MOD ; 

                            CMSRTE rte ;
                            rte.Init() ;
                            rte.SetRoutingParms( ord, (int)i, -1, *prrec, *prrec, pUGTime) ;
                            rte.Write(fp) ;
                        }
                    }
                }
            }
        }

        // Done with this job record
    } // next job/work-order

    return 0 ; 
}

double Thick_FinMM2StkIN(double finsize)
{
    return (finsize + STEEL_CUTALLOWANCE) / 25.4 ; 
}


double SawCutAllowance(double thk, int mode)
{
    if (IS_IMPERIAL & mode)
        return STEEL_CUTALLOWANCE / 25.4 ; 
    return STEEL_CUTALLOWANCE ;
}

bool RunTimesDifferent(double a, double b)
{
    int m = (int)(a * 1000.0) ; 
    int n = (int)(b * 1000.0) ; 

    if ((m % 10) >= 5)
        m += 10 ; 
    if ((n % 10) >= 5)
        n += 10 ; 
    
    m = m / 10 ; 
    n = n / 10 ; 

    if (m != n)
        return true ; 
    return false ; 
}
