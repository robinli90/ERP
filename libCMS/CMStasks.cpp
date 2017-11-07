// CMStasks.cpp - taskMap interface routines 

#include <CSstdlibs/cslib.h>

#include "Log.h"
#include "CMSBOMRTE.h"


// returns taskMap.end() if it can't find anything that matches
TaskMapItr FindTaskMatch(TaskMap &taskMap, char *task, char *part) 
{
    csString ubtask(task) ; 
    if (ubtask.size() == 0)
        return taskMap.end() ; 
    ubtask = ubtask.Left(1) ; 
    ubtask[0] -= 1 ; 
    ubtask.ToUpper() ; 

    TaskMapItr itm = taskMap.end() ;  // best match record
    
    int curRank = -1 ; 
    int curMatchCount = 0 ; 
    TaskMapItr itmsrch = taskMap.upper_bound(ubtask) ;  
    int found = 0 ; 
    while (itmsrch != taskMap.end())
    {   // Is this the best match
        if (itmsrch->first.Left(2) != task)
        {
            if (found)
                break ; // exit out, tasks should all match during this process. 
            itmsrch++ ; 
            continue ; // go to next record. 
        }

        found = 1 ; 

        int rank = PartRank(itmsrch->second.part) ; 
        int matchCount = PartCharsThatMatch(itmsrch->second.part, part) ; 
        if (rank >= curRank)
        {
            if (itmsrch->second.part[0] == '*') // matches everything
            {
                itm = itmsrch ; 
                curRank = rank ; 
                curMatchCount = 0 ; 
            }
            else if (matchCount > curMatchCount)
            {
                itm = itmsrch ; 
                curRank = rank ; 
                curMatchCount = matchCount ; 
            }
        }
        itmsrch++ ; 
    }

    return itm ; 
}


StationMapItr FindStationMatch(StationMap &stationMap, csString &station)
{
    csString ss = station.Left(1) ; 
    if (ss.size() == 0)
        return stationMap.end() ; 
    ss.ToUpper() ; 
    ss[0] -= 1 ; 

    StationMapItr iss = stationMap.upper_bound(ss) ; 
    int matchcount = 0 ; 
    int found = 0 ; 
    while (iss != stationMap.end())
    {
        if (iss->first == station)
            return iss ; // exact match found so done. 
        csString key(iss->first) ; 
        if (found && (key[0] != station[0]))
            return stationMap.end() ; // couldn't find a match
        else if (key[0] == station[0])
            found = 1 ; 

        int lenpre = key.FindIDX("*") ; 
        if (lenpre > 0)
        {
            if (station.Left(lenpre) == iss->first.Left(lenpre))
                return iss ; 
        }
        else if (station == key)
            return iss ; 
        iss++ ; 
    }

    return stationMap.end() ; 
}
