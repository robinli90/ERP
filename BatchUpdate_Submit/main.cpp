#include <string>
// Include the necessary DQ Classes
#include <IBM/cwbdq.h>
#include <IBM/cwbsv.h>
#include <IBM/cwbrc.h>

using namespace std;

const int DONE = 0;
const int CREATE_SYSTEM_FAIL = -1;
const int SET_USER_ID_FAIL = -2;
const int SET_PASSWORD_FAIL = -3;
const int START_SYSTEM_FAIL = -4;
const int RUN_ADDLIBLE_CMSPD_FAILD = -5;
const int RUN_ADDLIBLE_CMSSYSTEM_FAILD = -6;
const int RUN_ADDLIBLE_CMSMAIN_FAILD = -7;
const int RUN_ADDLIBLE_CMSINV_FAILD = -8;
const int RUN_ADDLIBLE_CMSNOE_FAILD = -9;
const int RUN_CHGCURLIB_CMSDAT_FAILD = -10;
const int RUN_CHGPLNT_001_FAILD = -11;
const int RUN_BATCH_COMMAND_FAILD = -12;
const int STOP_SYSTEM_FAILD = -13;
const int DELETE_SYSTEM_FAILD = -14;

int main()
{
	cwbCO_SysHandle system;
	cwbRC_SysHandle request;
	cwbSV_ErrHandle errorHandle;
	// create IBM remote system
	if (CWB_OK != cwbCO_CreateSystem("10.0.0.35", &system))
	{
		return CREATE_SYSTEM_FAIL; 
	}
	// set user id
	if (CWB_OK != cwbCO_SetUserIDEx(system, "PSKINNER"))
	{
		return SET_USER_ID_FAIL;
	}
	// set password
	if (CWB_OK != cwbCO_SetPassword(system, "PSKINNER"))
	{
		return SET_PASSWORD_FAIL;
	}
	// Start the system
	if (CWB_OK != cwbRC_StartSysEx(system, &request))
	{
		return START_SYSTEM_FAIL;
	}
	try 
	{
		cwbSV_CreateErrHandle(&errorHandle);
		// Call the command to create a library
		if (CWB_OK != cwbRC_RunCmd(request, "ADDLIBLE CMSPD",       errorHandle))
		{
			throw RUN_ADDLIBLE_CMSPD_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "ADDLIBLE CMSSYSTEM",   errorHandle))
		{
			throw RUN_ADDLIBLE_CMSSYSTEM_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "ADDLIBLE CMSMAIN",     errorHandle))
		{
			throw RUN_ADDLIBLE_CMSMAIN_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "ADDLIBLE CMSINV",      errorHandle))
		{
			throw RUN_ADDLIBLE_CMSINV_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "ADDLIBLE CMSNOE",      errorHandle))
		{
			throw RUN_ADDLIBLE_CMSNOE_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "CHGCURLIB CMSDAT", errorHandle))
		{
			throw RUN_CHGCURLIB_CMSDAT_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "CHGPLNT 001", errorHandle))
		{
			throw RUN_CHGPLNT_001_FAILD;
		}
		if (CWB_OK != cwbRC_RunCmd(request, "PD818CMD 001 JOHN BATCH.TXT 2 1 BERR.TXT 1 2", errorHandle))
		{
			ULONG a = errorHandle;
			throw RUN_BATCH_COMMAND_FAILD;
		}
		// Stop the system
		if (CWB_OK != cwbRC_StopSys(request))
		{
			throw STOP_SYSTEM_FAILD ;
		}
	}
	catch (int errNum)
	{
		cwbCO_DeleteSystem(system);
		return errNum ; 
	}
	// Delete the system object
	if (CWB_OK != cwbCO_DeleteSystem(system))
	{
		return DELETE_SYSTEM_FAILD;
	}
	else
	{
		return DONE;
	}
}