#ifndef __CMSDATA_H__
#define __CMSDATA_H__

// #include <fstream>
#include <libCMS/CMSBOMRTE.h>



struct CMSData 
{
    CMSEventProcessing evp ; // event processing 

    // Complete data set
    CMSBOMRTE cms ;

    // Whenever the dialog is changed the original value of the order 
    // is saved. Then a comparison can be done to determine how to 
    // create the flat file. 
    CMSOrder origOrder ; 
} ;  

#endif 