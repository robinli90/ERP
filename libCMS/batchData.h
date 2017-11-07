// batchData.h Batch reporting data definitions
#pragma once

#ifndef __BATCHDATA_H__
#define __BATCHDATA_H__



/*

The Run time recorded is in RPRR.  

    - OAQTYG        15S 5       COLHDG('Quantity' 'Good')  
    - OAQTYS        15S 5       COLHDG('Quantity' 'Scrapped')  
    - OATIME         4S 2       COLHDG('Time' 'HH.HH')   


*/


enum 
{
    JOBSTATE_RUN        = 0x0001, 
    JOBSTATE_DOWN       = 0x0002, 
    JOBSTATE_IDLE       = 0x0004, 
    JOBSTATE_UNKNOWN    = 0x8000, 
} ; 

#define BATCH_HDR_LENGTH    21
#define BATCH_DTL_LENGTH    66
#define BATCH_PRT_LENGTH    252
#define BATCH_MAT_LENGTH    82
#define BATCH_lAB_LENGTH    28

struct BatchHeader
{
 CDate reportdate ; 
 char shift ;
 int  fiscalPeriod ;
 int fiscYear ; 
 int fiscMonth ; 
 char shiftGroup ;
 char stockloc[6] ;
 char plant[6] ; 
    
 // Member functions
 int SetString(char *buf) ; 
} ;


struct BatchDetail
{
 char mode ; // S=setup R=run D=down
 char dept[8]; 
 char resource[8] ;
 char part[30] ;
 char seqnum[6] ;
 char indcode[16] ;
 double machtime ; // stored in minutes
 char orderNum[14] ;
 char nummen ;
 char nummach ; 
 char dbldig ; // Y=use double digits
 int nMen2 ;
 int nMach2 ;

 // Member functions
 int SetString(char *buf) ; 
} ;


struct BatchPart
{
 char partnum[30] ;
 double qtygood ;
 double qtyscrap ;
 char units[6] ;
 char reason[4] ;
 char empdept[4] ;
 int empnum ; 
 char chargedept[4] ;
 char chargeresc[8] ;
 char reversing ; 
 char lotnum[20] ;
 char stamplot ;
 char createserial ;// Y=yes
 char outlib[16] ; // library name
 char queuename[16] ; // queuename within library
 char usr1[30] ;
 char usr2[30] ;
 char usr3[30] ;
 double voidser ;
 char prodser[40] ;
 char nobackflush ; // Y=yes
 char scanid[50] ;

 // Member functions
 int SetString(char *buf) ; 
} ;

struct BatchMaterial
{
 char matpart[30] ;
 char stockroom[6] ;
 char reqmode ; // R=required B=by-product
 char backflush ; // Y=yes N=no
 double qty ;
 char units[6] ;
 CDate transdate ;
 char seqnum[6] ;
 char lotnum[20] ;
 int sernum ;
 char isScrap ; // Y=yes

 // Member functions
 int SetString(char *buf) ; 
} ;


#endif