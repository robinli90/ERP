
#include "stdafx.h"

void printusage()
{
    /*printf(
        "usage:\n\n"
        " procff -w <watchdir> -i <iSeries_DirName>  -f <IBM_flatfile_name>\n"
        "       [-l logfile] [-m movetodir] [-e errdir] [-c] [-n]\n\n"
        " -w directory where individual CAD/CAM files are saved to\n"
        " -i directory where merged flat files are saved on IBM for processing\n"
        " -f name of the output flat file as defined in PDMN19 opt 12\n"
        " -l log file prefix, if not defined no logging occurs.\n"
        " -m directory where processed flat files are archived after processing\n"
        " -n no local progress output to standard out (not working yet)\n\n"
        " -c continue running on error condition (you must manually delete\n"
        "    the FF.txt file from the iSeries when an error occurs and then\n"
        "    check the WORTUPLOAD job log to see what went wrong. Enabling this\n"
        "    will allow the program to continue before having determined what\n"
        "    the previous problem was.)\n"
        " -e directory where the IBM flat file is moved to if after 30 minutes\n"
        "    it is still sitting in the IBM directory indicating that it has not\n"
        "    been processed. If -c is not set, the program will also quit at\n"
        "    that point.\n"
        "The program watches the iSeries directory and when the directory is\n"
        "empty procff initiates a new process loop. It reads all the current\n"
        "files in the watchdir and merges them into a single file. Which is then\n"
        "copied over to the iSeries directory and file name defined in the -i\n"
        "parameter. This directory and file name must match the filename and\n"
        "directory as specified in the iSeries flat file processing options\n"
        "PDMN19 #12. Thus for example if the directory on the iSeries is RTEBOMP1\n"
        "and this maps to \\\\10.0.0.35\\qdls\\RTEBOMP1 and you are using a filename\n"
        "of FF.txt and have an I: share that connects to \\\\10.0.0.35\\qdls, then\n"
        "the -i parameter would be 'I:\\RTEBOMP1' (the RTEBOMP1 directory\n"
        "must be created and configured before hand, on the iSeries for this to\n"
        "work properly); and the -f parmaeter would be 'FF.txt' (do not use.\n"
        "quotes in the parameter names, and make sure there are no embedded\n"
        "spaces in either the directory or file names).\n"
        "The log file is a directory path and file name prefix, to which\n"
        "the current date is appended in _YYYYMMDD.log format.\n" 
        "The movetodir is a directory where the RTE/BOM text files from the CAD\n"
        "area are moved to after processing. A subdirectory will automatically\n"
        "be created in the movetodir with the name YYYYMM. So a new directory\n"
        "will automatically be created once a month.\n"
        "Note, the file procFF_tempfile.txt is created in the watchdir during\n"
        "processing so make sure that this file is not used for anything else\n"
        "(don't create a file with this name in the watchdir since it will be\n"
        "over-written).\n\n"
        "The logfile prefix must define a directory as well as the initial\n"
        "prefix part of a file name to which the string <date>.log will be\n"
        "appended. Thus do not include the last portion as a directory\n"
        "otherwise the system will fail to create the log file.\n\n"
        "Also, make sure that the iSeries share has been authorized (password\n"
        "keyed in to connect to the share) otherwise errors will result when\n"
        "the program attempts to create the file on the IBM machine.\n"
        ) ; */
}

/* 
    The following may connect to the share automatically. 

    DWORD WNetAddConnection3(HWND hwndOwner, // owner window
                             LPNETRESOURCE lpNetResource, // connection details
                             LPTSTR lpPassword, // password string
                             LPTSTR lpUserName, // user name string
                             DWORD dwFlags // connection options
                           );

 */
