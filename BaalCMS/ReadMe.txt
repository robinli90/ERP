========================================================================
    CONSOLE APPLICATION : BaalCMS Project Overview
========================================================================

AppWizard has created this BaalCMS application for you.  
This file contains a summary of what you will find in each of the files that
make up your BaalCMS application.


BaalCMS.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

BaalCMS.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named BaalCMS.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////


-c cfgfile.ini -d t:\acct\PRODcmds -r -l u:\cms\log\baallog -s u:\cms\log\baalsql -t u:\cms\log\taskarc -m u:\cms\taskdone --RTER -v
-c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone --RTER -v

// --RTER -v --tship --XDOWN -c cfgfile.ini -d t:\acct\PRODcmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone 
// -c cfgfile.ini -d c:\cms\cmds -r -l c:\cms\log\baallog -s c:\cms\log\baalsql -t c:\cms\log\taskarc -m c:\cms\taskdone --RTER -v


Usage:
This is a console program. It gets string information from shop and then cast into Decade and Solarsoft databases simutaneously.