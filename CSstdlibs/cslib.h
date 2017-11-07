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

// cslib.h - master library include file

#ifndef __CSLIB_H__ 
#define __CSLIB_H__

#ifdef CS_LINUX

// LINUX

#include <cs_endian.h>
#include <permscombs.h>
#include <csstring.h>
#include <wrkfuncs.h>
#include <cslists.h>
#include <stacks.h>
#include <datefunc.h>
#include <fileparams.h>
#include <cs_fileblk.h>
#include <govsupp.h>

#else

// WINDOWS OR OTHERS
#pragma warning( disable : 4996 )
#pragma warning( disable : 4786 )

#include "Disable4786.h"

#include "cs_endian.h"
#include "permscombs.h"
#include "avltree.h"
#include "csstring.h"
#include "wrkfuncs.h"
#include "cs_params.h"
#include "cslists.h"
#include "cs_adjacency.h"
#include "stacks.h"
#include "datefunc.h"
#include "fileparams.h"
#include "cs_fileblk.h"
#include "govsupp.h"
#include "cs_filelog.h"

#ifdef _WIN32
#include "sysProc.h"
#endif

#endif
#endif
