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

// cs_adjacecny.h - adjacency lists and associated structures


#ifndef __CS_ADJACECNY_H__
#define __CS_ADJACECNY_H__

#ifdef WIN32

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#pragma warning( disable : 4996 )

#endif

struct CS_AdjacencyObject
{
    int stat ;     // not used yet
    CS_AdjacencyObject() { stat = -1 ; } ; 
    virtual ~CS_AdjacencyObject() {} ; 
    virtual int SharesEdge(CS_AdjacencyObject &obj, void **pda=0, void **pdb=0)  { return 0; } ; 
    virtual int SharesEdge(CS_AdjacencyObject *pobj, void **pda=0, void **pdb=0) { return 0; } ; 
    virtual int Touches(CS_AdjacencyObject &obj, void **pda=0, void **pdb=0)     { return 0; } ; 
    virtual int Touches(CS_AdjacencyObject *pobj, void **pda=0, void **pdb=0)    { return 0; } ; 
} ;

struct CS_AdjacencyNode ;

struct CS_AdjacencyEdge
{
    CS_AdjacencyNode *pParent ;       // node that this edge is part of
    CS_AdjacencyNode *pMatchingNode ; // the other connected node 
    CS_AdjacencyEdge *pMatchingEdge ; // edge data in other list
    void *pEdgeData ;                 // edge data specific to this node
} ;

#define CS_ADJ_SCANNEDADJLIST       0x0001
#define CS_ADJ_OUTOFSEQUENCE        0x0002

struct CS_AdjacencyNode
{
    // used to designate a common level among nodes. The first level
    // is assigned the value
    int idx ; // index in the array (needed when walking adjNodesList
    int stat ; 
    int level ; 
    CS_AdjacencyObject *pObject ; 
    CS_List<CS_AdjacencyEdge> edgeList ; 


    CS_AdjacencyNode() 
    { 
        idx = 0 ; 
        stat = 0 ; 
        level = 0 ; 
        pObject = 0 ;
    } ;

    ~CS_AdjacencyNode() {} ; 
} ;


template <class T, class ET> class CS_AdjacencyList
{
public: 
    // The actual array of node data
    CS_AdjacencyNode *objNode ; 

    // The number of entries in the above array
    int nObjects ; 
    
    // total number of levels in the graph
    int maxLevel ; 

    // Incremented if a node's level is set out of sequence based
    // on the walk through the graph. This indicates a non-regular
    // level section graph

    // Class methods
    CS_AdjacencyList() 
    {
        maxLevel = 0 ; 
        nObjects = 0 ;
        objNode = 0 ; 
    } ;    

    ~CS_AdjacencyList() 
    {
        if (objNode)
            delete[] objNode ; 
    } ; 

    // Takes the list of objects and fills the objList as well as the 
    // adjNodesList within each of the CS_AdjacencyNode's. Each object
    // will have the same index number in the objNode array as it does
    // in the pObjs array that is passed in.
    int InitializeNodes(T *pObjs, int nobjs)
    {
        if (objNode)
            delete[] objNode ; 
    
        int i,j ; 
        maxLevel = 0 ; 
        nObjects = nobjs ; 
        void *pda, *pdb ; 

        objNode = new CS_AdjacencyNode[nObjects] ; 
        if (!objNode)
        {
            nObjects = 0 ; 
            return -1 ; 
        }

        // Assign objects to each node 
        for (i=0; i < nObjects; i++)
        {
            objNode[i].idx = i ; 
            objNode[i].pObject = &pObjs[i] ; 
            objNode[i].level = -1 ; 
            objNode[i].stat  = 0 ; 
        }


        /*
        struct CS_AdjacencyEdge
        {
            CS_AdjacencyNode *pParent ;       // node that this edge is part of
            CS_AdjacencyNode *pMatchingNode ; // the other connected node 
            CS_AdjacencyEdge *pMatchingEdge ; // edge data in other list
            void *pEdgeData ;                 // edge data specific to this node
        } ;
        */
        CS_AdjacencyEdge wrkedge, *pea, *peb ; 
        CS_ListNode *plna, *plnb ; 

        for (i=0; i < nObjects - 1; i++)
        {
            for (j=i+1; j < nObjects; j++)
            {
                pda = pdb = 0 ; 
                if (objNode[i].pObject->SharesEdge(objNode[j].pObject, &pda, &pdb))
                {   // Then create the link entries 
                    wrkedge.pParent       = &objNode[i] ;
                    wrkedge.pMatchingNode = &objNode[j] ;
                    wrkedge.pEdgeData     = pda ;
                    plna = objNode[i].edgeList.Append(wrkedge) ; 

                    wrkedge.pParent       = &objNode[j] ;
                    wrkedge.pMatchingNode = &objNode[i] ;
                    wrkedge.pEdgeData     = pdb ;
                    plnb = objNode[j].edgeList.Append(wrkedge) ; 

                    // Finally cross link the pMatchingEdge variables
                    pea = objNode[i].edgeList.GetData(plna) ; 
                    peb = objNode[i].edgeList.GetData(plnb) ; 

                    pea->pMatchingEdge = peb ; 
                    peb->pMatchingEdge = pea ; 
                }
            }
        }

        return 0 ; 
    } ;

    ET *GetEdgeData(CS_ListNode *pln)
    {
        return (ET *)edgeList.GetData(pln) ; 
    }



    // The concept of levels is based on how many nodes you have to 
    // step on to get to another node based on the given start node. 
    // Thus the pointer to the node passed in determines the start 
    // point and as such will have its level=0. Then all the nodes 
    // adjacent to it would be labeled level 1. Then all unlabeled 
    // nodes adjacent to level 1 nodes would be labeled 2, and so on.
    int EnumerateLevels(int startidx=0) 
    {
        if (nObjects < 2)
            return 0 ; // nothing to do

        CS_AdjacencyNode *pan ; 
        CS_ListNode *pln ; 
        int i ; 
        int scancol, nxtcol ; 
        int scanlen, nxtscanlen ; 
        int level ; 

        int (*scan)[2] = new int[nObjects][2] ; 
        if (!scan)
            return -1 ; 

        level = 0 ; 
        scancol = 0 ; 
        scanlen = 1 ; 
        nxtcol = 1 ; 
        scan[0][0] = startidx ; 

        objNode[startidx].level = level++ ; 

        do 
        {
            nxtscanlen = 0 ; 
            for (i=0; i < scanlen; i++)
            {
                pln = objNode[scan[i][scancol]].edgeList.First() ; 
                while (pln)
                {
                    //pan = *(objNode[scan[i][scancol]].adjNodesList.GetData(pln)) ; 
                    pan = *((CS_AdjacencyNode **)(pln->pdata)) ; 

                    if (!(pan->stat & CS_ADJ_SCANNEDADJLIST))
                    {   // Then add to list of objNodes to scan next
                        scan[nxtscanlen++][nxtcol] = pan->idx ; 
                    }

                    if (pan->level == -1)
                    {
                        pan->level = level ; 
                    }
                    else
                    {   // Check sequencing
                        if ((pan->level-2 != level) && (pan->level+2 != level) &&
                            (pan->level != level) )
                        {
                            pan->stat |= CS_ADJ_OUTOFSEQUENCE ;
                        }
                    }
                    pln = pln->next ; 
                }
                // Mark this node as being processed
                objNode[scan[i][scancol]].stat |= CS_ADJ_SCANNEDADJLIST ;
            }
            // Set up for the next level set
            maxLevel = level ; 
            level++ ; 
            scanlen = nxtscanlen ; 
            scancol ^= 1 ; // toggle the columns  
            nxtcol  ^= 1 ;

        } while(nxtscanlen) ; 
    
        delete[] scan ; 
        return 0 ; 
    } ; 
} ;




#endif
