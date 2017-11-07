// 
// Windows service to launch/kill a process in synch with a
// second process, as named in the defines below. This module 
// is based on "Simple Service" and "Enumerating All Processes"
// examples from uSoft.
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include <time.h>
#include "psapi.h"
#include "service.h"

//#define MARKHAM_BACKUP 1
#undef MARKHAM_BACKUP
#define MARKHAM 1
//#undef MARKHAM
//#define ALUDIE 1		// all of live, test and backup
#undef ALUDIE
//#define MICHIGAN 1
#undef MICHIGAN
//#define COLOMBIA 1
#undef COLOMBIA

//#define DDDDWDEBUG	1
#undef DDDDWDEBUG

#ifdef MARKHAM_BACKUP
#define APP_USER "Administrator"
#define APP_DOMAIN "EXCO130SPY"
#define APP_PASSWORD "desktopTIME"
#endif
#ifdef MARKHAM
//#define APP_USER "test"
//#define APP_DOMAIN ""
//#define APP_PASSWORD "123test"
#define APP_USER "services"
#define APP_DOMAIN "EXCO130SPY"
#define APP_PASSWORD "12#$56&*"
#define ERROR_EMAIL_SUBJECT			"UpdateDecade SERVICE error report (Markham)"
#define INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS	1800	
#define LAST_HEALTH_CHECK_HOUR	23    // Allows for cutoff during backups
#define LAST_HEALTH_CHECK_MINUTE 59
#define LAST_HEALTH_CHECK_SECOND 59
#endif
#ifdef ALUDIE
#define APP_USER "Administrator"
#define APP_DOMAIN "ALUDIEDOM"
#define APP_PASSWORD "!AL1u7DiE"
#define ERROR_EMAIL_SUBJECT			"UpdateDecade SERVICE error report (AluDie)"
#define INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS	1800	
#define LAST_HEALTH_CHECK_HOUR	16    // Allows for cutoff during backups
#define LAST_HEALTH_CHECK_MINUTE 30
#define LAST_HEALTH_CHECK_SECOND 0
#endif
#ifdef MICHIGAN
#define APP_USER "track"
#define APP_DOMAIN NULL
#define APP_PASSWORD "123track"
#define ERROR_EMAIL_SUBJECT			"UpdateDecade SERVICE error report (Michigan)"
#define INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS	3600	
#define LAST_HEALTH_CHECK_HOUR	23    // Allows for cutoff during backups
#define LAST_HEALTH_CHECK_MINUTE 59
#define LAST_HEALTH_CHECK_SECOND 59
#endif
#ifdef COLOMBIA
#define APP_USER "track"
#define APP_DOMAIN NULL
#define APP_PASSWORD "123track"
#define ERROR_EMAIL_SUBJECT			"UpdateDecade SERVICE error report (Colombia)"
#define INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS	3600	
#define LAST_HEALTH_CHECK_HOUR	23    // Allows for cutoff during backups
#define LAST_HEALTH_CHECK_MINUTE 59
#define LAST_HEALTH_CHECK_SECOND 59
#endif

#define MAX_ERROR_NOTIFICATION_EMAILS	2
#define ERROR_NOTIFICATION_EMAILS		2  // selects both Al and me
#define ERROR_EMAIL_SMTP_SERVER			"mail.wilkesassociates.com"
#define ERROR_EMAIL_SMTP_PORT			587
#define ERROR_EMAIL_FROM_ADDRESS		"notifications@wilkesassociates.com"
#define ERROR_EMAIL_FIRST_CONTACT		"wilkes@wilkesassociates.com"
#define ERROR_EMAIL_SECOND_CONTACT		"al@aludie.com"
#define ERROR_EMAIL_PWD					"123howdy"

#define MAIN_LOOP_IDLE_INTERVAL						2000	// ms. 
#define HEALTH_CHECK_INTERVAL_IN_LOOPS				100		// ~ 200 seconds, for given idle interval
#define DECADE_DATABASE_NAME						"decade"
#define LOG_FILE_NAME								"C:\\Program Files\\updateDecade\\logFile.txt"
	// to avoid loading the host PC unduly.
#define WAIT_INTERVAL_AFTER_STATE_CHANGE	300000 // ms
    // this will (hopefully) keep multiple copies of the target
	// from being spawned, if the target is slow to start up at
	// boot time, yet things will appear responsive to a
    // single, isolated state change, with the above 
	// MAIN_LOOP_IDLE_INTERVAL
#define WAIT_INTERVAL_AFTER_LAUNCH_FAILURE	60000 // ms

#define MONITORED_PROCESS	"sqlservr"   // These must be
#define LAUNCHED_PROCESS	"updatedecadeapp"	  // lowercase
//#define LAUNCHED_APP_PATH   "C:\\Program Files\\updateDecade\\updateDecadeApp.exe" 
#define MAX_PROCESS_NAME_LENGTH 1024

char *g_szErrorNotificationEmailAddress[MAX_ERROR_NOTIFICATION_EMAILS] =
{ ERROR_EMAIL_FIRST_CONTACT, ERROR_EMAIL_SECOND_CONTACT };

#define MIN_INTERVAL_BETWEEN_EMAILS 3600 // seconds
time_t g_lastEmail = 0L;

// this event is signalled when the
// service should end
//
HANDLE  hServerStopEvent = NULL;

void LogError(char *szMessage) {
	FILE *fLog;
	time_t now;
	struct tm *tmNow;
	int i;
	char stampedMessage[1024],
		 blatLine[1024];

	if (!szMessage) {
		return;
		}

	time(&now);
	tmNow = localtime(&now);

	fLog = fopen(LOG_FILE_NAME, "a+");
	sprintf(stampedMessage,
		    "%d-%02d-%02d %02d:%02d:%02d: %s\n",
		    tmNow->tm_year + 1900,
			tmNow->tm_mon + 1,
			tmNow->tm_mday,
			tmNow->tm_hour,
			tmNow->tm_min,
			tmNow->tm_sec,
			szMessage);
	fprintf(fLog, "%s", stampedMessage);
	fclose(fLog);

	if (now - g_lastEmail >= MIN_INTERVAL_BETWEEN_EMAILS) {
		// e-mail stamped message
		for (i = 0; i < ERROR_NOTIFICATION_EMAILS; i++) {
			sprintf(blatLine,
				"blat - -to %s -server %s -port %d -f %s -u %s -pw %s -subject \"%s\" -body \"%s\"",
				g_szErrorNotificationEmailAddress[i],
				ERROR_EMAIL_SMTP_SERVER, ERROR_EMAIL_SMTP_PORT,
				ERROR_EMAIL_FROM_ADDRESS, ERROR_EMAIL_FROM_ADDRESS,
				ERROR_EMAIL_PWD, ERROR_EMAIL_SUBJECT,
				stampedMessage);
			system(blatLine);
			}
		g_lastEmail = now;
		} // if (now...)

} // LogError

void FetchProcessName(DWORD processID,
					  char *szProcessName)
{
	HANDLE hProcess;
    HMODULE hModArray[1024];
    DWORD cbNeeded;

    strcpy(szProcessName, "unknown");

    // Get a handle to the process.
		hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.
		if (hProcess) {
			if (EnumProcessModules(
				    hProcess, hModArray, sizeof(hModArray), 
					&cbNeeded)) {
	            GetModuleBaseName(hProcess, hModArray[0], 
					szProcessName, 
                    (size_t) MAX_PROCESS_NAME_LENGTH);
				}		
			}

	_strlwr(szProcessName);

    CloseHandle( hProcess );
}

void KillProcess(DWORD processID)
{
	HANDLE hProcess;

    // Get a handle to the process.
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,
                               FALSE, processID);

	if (!TerminateProcess(hProcess, // handle to the process
						  0)) {   // exit code for the process
		// log the error
		}

} // KillProcess

//---------------------------------------------------
// 20100518: Second example from MSDN on cleanup 
// of unused ACE's, added after CreateProcessAsUser()
// started failing with ERROR_NOT_ENOUGH_QUOTA,
// which has to do with running out of space for
// ACE's on the ACL's of a given window station
// "Call after CreateProcessAsUser()"

BOOL RemoveAceFromWindowStation(HWINSTA hwinsta, PSID psid)
{
   ACL_SIZE_INFORMATION aclSizeInfo;
   BOOL                 bDaclExist;
   BOOL                 bDaclPresent;
   BOOL                 bSuccess = FALSE;
   DWORD                dwNewAclSize;
   DWORD                dwSidSize = 0;
   DWORD                dwSdSizeNeeded;
   PACL                 pacl;
   PACL                 pNewAcl;
   PSECURITY_DESCRIPTOR psd = NULL;
   PSECURITY_DESCRIPTOR psdNew = NULL;
   ACCESS_ALLOWED_ACE*  pTempAce;
   SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
   unsigned int         i;

   __try
   {
      // Obtain the DACL for the window station.

      if (!GetUserObjectSecurity(
             hwinsta,
             &si,
             psd,
             dwSidSize,
             &dwSdSizeNeeded)
      )
      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
      {
         psd = (PSECURITY_DESCRIPTOR)HeapAlloc(
               GetProcessHeap(),
               HEAP_ZERO_MEMORY,
               dwSdSizeNeeded);

         if (psd == NULL)
            __leave;

         psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
               GetProcessHeap(),
               HEAP_ZERO_MEMORY,
               dwSdSizeNeeded);

         if (psdNew == NULL)
            __leave;

         dwSidSize = dwSdSizeNeeded;

         if (!GetUserObjectSecurity(
               hwinsta,
               &si,
               psd,
               dwSidSize,
               &dwSdSizeNeeded)
         )
            __leave;
      }
      else
         __leave;

      // Create a new DACL.

      if (!InitializeSecurityDescriptor(
            psdNew,
            SECURITY_DESCRIPTOR_REVISION)
      )
         __leave;

      // Get the DACL from the security descriptor.

      if (!GetSecurityDescriptorDacl(
            psd,
            &bDaclPresent,
            &pacl,
            &bDaclExist)
      )
         __leave;

      // Initialize the ACL.

      ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
      aclSizeInfo.AclBytesInUse = sizeof(ACL);

      // Call only if the DACL is not NULL.

      if (pacl != NULL)
      {
         // get the file ACL size info
         if (!GetAclInformation(
               pacl,
               (LPVOID)&aclSizeInfo,
               sizeof(ACL_SIZE_INFORMATION),
               AclSizeInformation)
         )
            __leave;
      }

      // Compute the size of the new ACL.

      dwNewAclSize = aclSizeInfo.AclBytesInUse +
            (2*sizeof(ACCESS_ALLOWED_ACE)) + (2*GetLengthSid(psid)) -
            (2*sizeof(DWORD));

      // Allocate memory for the new ACL.

      pNewAcl = (PACL)HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            dwNewAclSize);

      if (pNewAcl == NULL)
         __leave;

      // Initialize the new DACL.

      if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION))
         __leave;

      // If DACL is present, copy it to a new DACL.

      if (bDaclPresent)
      {
         // Copy the ACEs to the new ACL.
         if (aclSizeInfo.AceCount)
         {
            for (i=0; i < aclSizeInfo.AceCount; i++)
            {
               // Get an ACE.
               if (!GetAce(pacl, i, (void**)(&pTempAce)))
                  __leave;

           if ( !EqualSid( psid, &pTempAce->SidStart ) )
           {

               // Add the ACE to the new ACL.
               if (!AddAce(
                 pNewAcl,
                 ACL_REVISION,
                 MAXDWORD,
                 pTempAce,
                ((PACE_HEADER)pTempAce)->AceSize)
               )
              __leave;
           }
            }
         }
      }

      if( pacl != NULL )
    HeapFree(GetProcessHeap(), 0, (LPVOID)pacl);

      // Set a new DACL for the security descriptor.

      if (!SetSecurityDescriptorDacl(
            psdNew,
            TRUE,
            pNewAcl,
            FALSE)
      )
         __leave;

      // Set the new security descriptor for the window station.

      if (!SetUserObjectSecurity(hwinsta, &si, psdNew))
         __leave;

      // Indicate success.

      bSuccess = TRUE;
   }
   __finally
   {
      // Free the allocated buffers.

      if( pacl != NULL )
         HeapFree(GetProcessHeap(), 0, (LPVOID)pacl);

      if (pNewAcl != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);

      if (psd != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)psd);

      if (psdNew != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
   }

   return bSuccess;

} // RemoveACEFromWindowStation


BOOL RemoveAceFromDesktop(HDESK hdesk, PSID psid)
{
   ACL_SIZE_INFORMATION aclSizeInfo;
   BOOL                 bDaclExist;
   BOOL                 bDaclPresent;
   BOOL                 bSuccess = FALSE;
   DWORD                dwNewAclSize;
   DWORD                dwSidSize = 0;
   DWORD                dwSdSizeNeeded;
   PACL                 pacl;
   PACL                 pNewAcl;
   PSECURITY_DESCRIPTOR psd = NULL;
   PSECURITY_DESCRIPTOR psdNew = NULL;
   ACCESS_ALLOWED_ACE*  pTempAce;
   SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
   unsigned int         i;

   __try
   {
      // Obtain the security descriptor for the desktop object.

      if (!GetUserObjectSecurity(
            hdesk,
            &si,
            psd,
            dwSidSize,
            &dwSdSizeNeeded))
      {
         if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
         {
            psd = (PSECURITY_DESCRIPTOR)HeapAlloc(
                  GetProcessHeap(),
                  HEAP_ZERO_MEMORY,
                  dwSdSizeNeeded );

            if (psd == NULL)
               __leave;

            psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
                  GetProcessHeap(),
                  HEAP_ZERO_MEMORY,
                  dwSdSizeNeeded);

            if (psdNew == NULL)
               __leave;

            dwSidSize = dwSdSizeNeeded;

            if (!GetUserObjectSecurity(
                  hdesk,
                  &si,
                  psd,
                  dwSidSize,
                  &dwSdSizeNeeded)
            )
               __leave;
         }
         else
            __leave;
      }

      // Create a new security descriptor.

      if (!InitializeSecurityDescriptor(
            psdNew,
            SECURITY_DESCRIPTOR_REVISION)
      )
         __leave;

      // Obtain the DACL from the security descriptor.

      if (!GetSecurityDescriptorDacl(
            psd,
            &bDaclPresent,
            &pacl,
            &bDaclExist)
      )
         __leave;

      // Initialize.

      ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
      aclSizeInfo.AclBytesInUse = sizeof(ACL);

      // Call only if NULL DACL.

      if (pacl != NULL)
      {
         // Determine the size of the ACL information.

         if (!GetAclInformation(
               pacl,
               (LPVOID)&aclSizeInfo,
               sizeof(ACL_SIZE_INFORMATION),
               AclSizeInformation)
         )
            __leave;
      }

      // Compute the size of the new ACL.

      dwNewAclSize = aclSizeInfo.AclBytesInUse +
            sizeof(ACCESS_ALLOWED_ACE) +
            GetLengthSid(psid) - sizeof(DWORD);

      // Allocate buffer for the new ACL.

      pNewAcl = (PACL)HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            dwNewAclSize);

      if (pNewAcl == NULL)
         __leave;

      // Initialize the new ACL.

      if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION))
         __leave;

      // If DACL is present, copy it to a new DACL.

      if (bDaclPresent)
      {
         // Copy the ACEs to the new ACL.
         if (aclSizeInfo.AceCount)
         {
            for (i=0; i < aclSizeInfo.AceCount; i++)
            {
               // Get an ACE.
               if (!GetAce(pacl, i, (void**)(&pTempAce)))
                  __leave;

           if ( !EqualSid( psid, &pTempAce->SidStart ) )
           {

               // Add the ACE to the new ACL.
               if (!AddAce(
              pNewAcl,
              ACL_REVISION,
              MAXDWORD,
              pTempAce,
              ((PACE_HEADER)pTempAce)->AceSize)
               )
              __leave;
           }
            }
         }
      }

      // Set new DACL to the new security descriptor.

      if (!SetSecurityDescriptorDacl(
            psdNew,
            TRUE,
            pNewAcl,
            FALSE)
      )
         __leave;

      // Set the new security descriptor for the desktop object.

      if (!SetUserObjectSecurity(hdesk, &si, psdNew))
         __leave;

      // Indicate success.

      bSuccess = TRUE;
   }
   __finally
   {
      // Free buffers.

      if( pacl != NULL )
         HeapFree(GetProcessHeap(), 0, (LPVOID)pacl);

      if (pNewAcl != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);

      if (psd != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)psd);

      if (psdNew != NULL)
         HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
   }

   return bSuccess;
} // RemoveACEFromDesktop



//---------------------------------------------------
// Start of original eg code, with our routine's header in place
// of main() from e.g.
//

#define RTN_OK     0
#define RTN_ERROR 13

#define WINSTA_ALL (WINSTA_ACCESSCLIPBOARD|WINSTA_ACCESSGLOBALATOMS|WINSTA_CREATEDESKTOP|WINSTA_ENUMDESKTOPS|WINSTA_ENUMERATE|WINSTA_EXITWINDOWS|WINSTA_READATTRIBUTES|WINSTA_READSCREEN|WINSTA_WRITEATTRIBUTES|DELETE|READ_CONTROL|WRITE_DAC|WRITE_OWNER)

#define DESKTOP_ALL (DESKTOP_CREATEMENU|DESKTOP_CREATEWINDOW|DESKTOP_ENUMERATE|DESKTOP_HOOKCONTROL|DESKTOP_JOURNALPLAYBACK|DESKTOP_JOURNALRECORD|DESKTOP_READOBJECTS|DESKTOP_SWITCHDESKTOP|DESKTOP_WRITEOBJECTS|DELETE|READ_CONTROL|WRITE_DAC|WRITE_OWNER)

#define GENERIC_ACCESS (GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE|GENERIC_ALL)

   BOOL ObtainSid(
        HANDLE hToken,           // Handle to an process access token.
        PSID   *psid             // ptr to the buffer of the logon sid
        );

   void RemoveSid(
        PSID *psid               // ptr to the buffer of the logon sid
        );

   BOOL AddTheAceWindowStation(
        HWINSTA hwinsta,         // handle to a windowstation
        PSID    psid             // logon sid of the process
        );

   BOOL AddTheAceDesktop(
        HDESK hdesk,             // handle to a desktop
        PSID  psid               // logon sid of the process
        );

int StartLaunchedProcess(void)
    // See notes re: what to do on Vista systems.
	// Vista and Win2K approach are mutually
	// incompatible, since API required for Vista
	// approach.
	{
        HANDLE              hToken = NULL;
        HDESK               hdesk = NULL;
        HWINSTA             hwinsta = NULL;
        PROCESS_INFORMATION pi;
        PSID                psid = NULL;
        STARTUPINFO         si;
		HWINSTA				hwinstaold;
		char				message[1024];
		int					nReturnValue = RTN_ERROR;

		memset(&pi, 0, sizeof(PROCESS_INFORMATION));

#		ifdef DDDDWDEBUG
			LogError("Trying to start DecadeUpdate");
#		endif

		__try {
			// 
			// obtain an access token for the user APP_USER
			// 
			if (!LogonUser(
				 APP_USER,
				 APP_DOMAIN,
				 APP_PASSWORD,
				 LOGON32_LOGON_INTERACTIVE,
				 LOGON32_PROVIDER_DEFAULT,
				 &hToken
				 )) {
				LogError("LogonUser() failed");
				__leave;
				}
			// 
			// obtain a handle to the interactive windowstation
			// 
			hwinsta = OpenWindowStation(
				 "winsta0",
				 FALSE,
				 /*WINSTA_ALL*/ READ_CONTROL | WRITE_DAC
				 );
			if (hwinsta == NULL) {
				LogError("OpenWindowStation() failed");
				__leave;
				}
			hwinstaold = GetProcessWindowStation();

			// 
			// set the windowstation to winsta0 so that you obtain the
			// correct default desktop
			// 
			if (!SetProcessWindowStation(hwinsta)) {
				LogError("SetProcessWindowStation() failed");
				__leave;
				}

			// 
			// obtain a handle to the "default" desktop
			// 
			hdesk = OpenDesktop(
				 "default",
				 0,
				 FALSE,
				 /*DESKTOP_ALL*/ READ_CONTROL | WRITE_DAC | DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS
				 );
			if (hdesk == NULL) {
				LogError("OpenDesktop() failed");
				__leave;
				}

			// 
			// obtain the logon sid of the user
			// 
			if (!ObtainSid(hToken, &psid)) {
				LogError("ObtainSid() failed");
				__leave;
				}

			// 
			// add the user to interactive windowstation
			// 
			if (!AddTheAceWindowStation(hwinsta, psid)) {
				LogError("AddTheAceWindowStation() failed");
				__leave;
				}

			// 
			// add user to "default" desktop
			// 
			if (!AddTheAceDesktop(hdesk, psid)) {
				LogError("AddTheAceDesktop() failed");
				__leave;
				}
			
			// 
			// initialize STARTUPINFO structure
			// 
				ZeroMemory(&si, sizeof(STARTUPINFO));
				si.cb        = sizeof(STARTUPINFO);
				si.lpDesktop = "winsta0\\default";

			// 
			// start the process
			// 
				if (!CreateProcessAsUser(
					 hToken,
					 NULL,
					 LAUNCHED_PROCESS,
					 NULL,
					 NULL,
					 FALSE,
					 NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
					 NULL,
					 NULL,
					 &si,
					 &pi
					 )) {
					DWORD dwLastError = GetLastError();
					sprintf(message, "CreateProcessAsUser() failed with code %ld\n",
								(long) dwLastError);
					LogError(message);	
					__leave;
					}

			nReturnValue = RTN_OK; 

			} // __try

		__finally {
			if (hwinsta && psid) {
				RemoveAceFromWindowStation(hwinsta, psid);
				}

			if (hdesk && psid) {
				RemoveAceFromDesktop(hdesk, psid);
				}

			if (psid) {
				// 
				// free the buffer for the logon sid
				// 
					RemoveSid(&psid);
				}

			// 
			// close the handles to the interactive windowstation and desktop
			// 
				if (hwinsta) {
					CloseWindowStation(hwinsta);
					}

				if (hdesk) {
					CloseDesktop(hdesk);
					}

			SetProcessWindowStation(hwinstaold); //set it back

			// 
			// close the handles
			// 
			if (pi.hProcess) {
				CloseHandle(pi.hProcess);
				}

			if (pi.hThread) {
				CloseHandle(pi.hThread);
				}

		} // __finally

	return nReturnValue;

} // StartLaunchedProcess


   BOOL ObtainSid(HANDLE hToken, PSID *psid)

      {
        BOOL                    bSuccess = FALSE; // assume function will
                                                  // fail
        DWORD                   dwIndex;
        DWORD                   dwLength = 0;
        TOKEN_INFORMATION_CLASS tic      = TokenGroups;
        PTOKEN_GROUPS           ptg      = NULL;

        __try
             {
             // 
             // determine the size of the buffer
        // 
             if (!GetTokenInformation(
             hToken,
             tic,
             (LPVOID)ptg,
             0,
             &dwLength
             ))
                  {
                  if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                       {
                       ptg = (PTOKEN_GROUPS)HeapAlloc(
                            GetProcessHeap(),
                  HEAP_ZERO_MEMORY,
                  dwLength
                  );
                       if (ptg == NULL)
                            __leave;
                       }
                   else
                       __leave;
         }

             // 
             // obtain the groups the access token belongs to
             // 
             if (!GetTokenInformation(
                  hToken,
             tic,
             (LPVOID)ptg,
             dwLength,
             &dwLength
             ))
                  __leave;

             // 
             // determine which group is the logon sid
             // 
             for (dwIndex = 0; dwIndex < ptg->GroupCount; dwIndex++)
                  {
             if ((ptg->Groups[dwIndex].Attributes & SE_GROUP_LOGON_ID)
                  ==  SE_GROUP_LOGON_ID)
                       {
                       // 
                       // determine the length of the sid
                       // 
                       dwLength = GetLengthSid(ptg->Groups[dwIndex].Sid);

                       // 
                       // allocate a buffer for the logon sid
                       // 
                       *psid = (PSID)HeapAlloc(
                            GetProcessHeap(),
                  HEAP_ZERO_MEMORY,
                  dwLength
                  );
                  if (*psid == NULL)
                       __leave;

                  // 
                  // obtain a copy of the logon sid
                  // 
                  if (!CopySid(dwLength, *psid, ptg->Groups[dwIndex].Sid))
                       __leave;

                  // 
                  // break out of the loop because the logon sid has been
                  // found
                  // 
                  break;
                  }
             }

             // 
             // indicate success
             // 
             bSuccess = TRUE;
             }
        __finally
             {
             // 
        // free the buffer for the token group
        // 
             if (ptg != NULL)
                  HeapFree(GetProcessHeap(), 0, (LPVOID)ptg);
             }

        return bSuccess;

   }

   void RemoveSid(PSID *psid)
   {
        HeapFree(GetProcessHeap(), 0, (LPVOID)*psid);
   }

   BOOL AddTheAceWindowStation(HWINSTA hwinsta, PSID psid)
   {

        ACCESS_ALLOWED_ACE   *pace;
        ACL_SIZE_INFORMATION aclSizeInfo;
        BOOL                 bDaclExist;
        BOOL                 bDaclPresent;
        BOOL                 bSuccess  = FALSE; // assume function will
                                                //fail
        DWORD                dwNewAclSize;
        DWORD                dwSidSize = 0;
        DWORD                dwSdSizeNeeded;
        PACL                 pacl;
        PACL                 pNewAcl;
        PSECURITY_DESCRIPTOR psd       = NULL;
        PSECURITY_DESCRIPTOR psdNew    = NULL;
        PVOID                pTempAce;
        SECURITY_INFORMATION si        = DACL_SECURITY_INFORMATION;
        unsigned int         i;
		char				 message[1024];

        __try {
            // 
            // obtain the dacl for the windowstation
            // 
			    if (!GetUserObjectSecurity(hwinsta, &si, psd, dwSidSize, &dwSdSizeNeeded)) {
					if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
						psd = (PSECURITY_DESCRIPTOR) HeapAlloc(GetProcessHeap(),
															   HEAP_ZERO_MEMORY,
															   dwSdSizeNeeded);
						if (psd == NULL) {
							LogError("Cannot alloc memory for GetUserObjectSecurity");
							__leave;
							}

						psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(),
																 HEAP_ZERO_MEMORY,
																 dwSdSizeNeeded);
						if (psdNew == NULL) {
							LogError("Cannot alloc memory for GetUserObjectSecurity");
	                        __leave;
							}

						dwSidSize = dwSdSizeNeeded;

						if (!GetUserObjectSecurity(hwinsta, &si, psd, dwSidSize, &dwSdSizeNeeded)) {
							LogError("GetUserObjectSecurity() failed after memory allocation");
							__leave;
							}
						}
					else {
						LogError("GetUserObjectSecurity() failed (on general error)");
						__leave;
						}
					}

            // 
            // create a new dacl
			// 
				if (!InitializeSecurityDescriptor(psdNew, SECURITY_DESCRIPTOR_REVISION)) {
					LogError("InitializeSecurityDescriptor() failed");
					__leave;
					}

            // 
			// get dacl from the security descriptor
            // 
				if (!GetSecurityDescriptorDacl(psd, &bDaclPresent, &pacl, &bDaclExist)) {
					LogError("GetSecurityDescriptor() failed");
					__leave;
					}

            // 
            // initialize
            // 
				ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
				aclSizeInfo.AclBytesInUse = sizeof(ACL);

            // 
            // call only if the dacl is not NULL
            // 
				if (pacl != NULL) {
					// get the file ACL size info
						if (!GetAclInformation(pacl, (LPVOID)&aclSizeInfo, 
											   sizeof(ACL_SIZE_INFORMATION),
											   AclSizeInformation)) {
							LogError("GetAclInformation() failed");
							__leave;
							}
					}

            // 
            // compute the size of the new acl
            // 
				dwNewAclSize = aclSizeInfo.AclBytesInUse + (2 *
					sizeof(ACCESS_ALLOWED_ACE)) + (2 * GetLengthSid(psid)) - (2 *
					sizeof(DWORD));

            // 
            // allocate memory for the new acl
            // 
				pNewAcl = (PACL)HeapAlloc(GetProcessHeap(), 
										  HEAP_ZERO_MEMORY,
										  dwNewAclSize);
				if (pNewAcl == NULL) {
					LogError("HeapAlloc for new acl failed");
					__leave;
					}

            // 
            // initialize the new dacl
            // 
				if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION)) {
					LogError("InitializeAcl() failed.");
					__leave;
					}

            // 
            // if DACL is present, copy it to a new DACL
            // 
				if (bDaclPresent) {
					// copy the ACEs to our new ACL
						if (aclSizeInfo.AceCount) {
							for (i=0; i < aclSizeInfo.AceCount; i++) {
								// get an ACE
									if (!GetAce(pacl, i, &pTempAce)) {
										LogError("GetAce() failed.");
										__leave;
										}

								// add the ACE to the new ACL
									if (!AddAce(pNewAcl, ACL_REVISION, MAXDWORD,
												pTempAce, ((PACE_HEADER)pTempAce)->AceSize)) {
										LogError("AddAce() failed.");
										__leave;
										}
								} // for 
							}
					}

            // 
            // add the first ACE to the windowstation
            // 
				pace = (ACCESS_ALLOWED_ACE *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
														sizeof(ACCESS_ALLOWED_ACE) 
														+ GetLengthSid(psid) 
														- sizeof(DWORD));
				if (pace == NULL) {
					LogError("Alloc failed for ACE");
					__leave;
					}

				pace->Header.AceType  = ACCESS_ALLOWED_ACE_TYPE;
				pace->Header.AceFlags = CONTAINER_INHERIT_ACE |
					                    INHERIT_ONLY_ACE      |
										OBJECT_INHERIT_ACE;
				pace->Header.AceSize  = sizeof(ACCESS_ALLOWED_ACE) 
										+ GetLengthSid(psid) - sizeof(DWORD);
				pace->Mask            = GENERIC_ACCESS;

				if (!CopySid(GetLengthSid(psid), &pace->SidStart, psid)) {
					LogError("CopySid failed.");
					__leave;
					}

				if (!AddAce(pNewAcl, ACL_REVISION, MAXDWORD, (LPVOID)pace, pace->Header.AceSize)) {
					LogError("AddAce() failed.");
					__leave;
					}

            // 
            // add the second ACE to the windowstation
            // 
				pace->Header.AceFlags = NO_PROPAGATE_INHERIT_ACE;
				pace->Mask            = WINSTA_ALL;

				if (!AddAce(pNewAcl, ACL_REVISION, MAXDWORD, (LPVOID)pace, pace->Header.AceSize)) {
					LogError("AddAce() (2nd) failed.");
					__leave;
					}

            // 
            // set new dacl for the security descriptor
            // 
                if (!SetSecurityDescriptorDacl(psdNew, TRUE, pNewAcl, FALSE)) {
					LogError("SetSecurityDescriptorDacl() failed.");
                    __leave;
					}	

            // 
			// set the new security descriptor for the windowstation
			// 
				if (!SetUserObjectSecurity(hwinsta, &si, psdNew)) {
					DWORD dwLastError = GetLastError();	  
					sprintf(message, "SetUserObjectSecurity() failed, code %ld",
						    (long) dwLastError);
					LogError(message);
					__leave;
					}

			// 
			// indicate success
			// 
				bSuccess = TRUE;
			} // __try

        __finally {
             // 
             // free the allocated buffers
             // 
				if (pace != NULL) {
		            HeapFree(GetProcessHeap(), 0, (LPVOID)pace);
					}

				if (pNewAcl != NULL) {
					HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);
					}

				if (psd != NULL) {
					HeapFree(GetProcessHeap(), 0, (LPVOID)psd);
					}

				if (psdNew != NULL) {
					HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
					}
			} // __finally

        return bSuccess;

   } // AddTheAceWindowStation

   BOOL AddTheAceDesktop(HDESK hdesk, PSID psid)
   {

        ACL_SIZE_INFORMATION aclSizeInfo;
        BOOL                 bDaclExist;
        BOOL                 bDaclPresent;
        BOOL                 bSuccess  = FALSE; // assume function will
                                                // fail
        DWORD                dwNewAclSize;
        DWORD                dwSidSize = 0;
        DWORD                dwSdSizeNeeded;
        PACL                 pacl;
        PACL                 pNewAcl;
        PSECURITY_DESCRIPTOR psd       = NULL;
        PSECURITY_DESCRIPTOR psdNew    = NULL;
        PVOID                pTempAce;
        SECURITY_INFORMATION si        = DACL_SECURITY_INFORMATION;
        unsigned int         i;

        __try
             {
             // 
             // obtain the security descriptor for the desktop object
             // 
             if (!GetUserObjectSecurity(
                  hdesk,
                  &si,
                  psd,
                  dwSidSize,
                  &dwSdSizeNeeded
                  ))
                  {
                  if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                       {
                       psd = (PSECURITY_DESCRIPTOR)HeapAlloc(
					            GetProcessHeap(),
						        HEAP_ZERO_MEMORY,
							    dwSdSizeNeeded
								);
                       if (psd == NULL)
                            __leave;

                       psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
									GetProcessHeap(),
		                            HEAP_ZERO_MEMORY,
					                dwSdSizeNeeded
									);
                       if (psdNew == NULL)
                            __leave;

                       dwSidSize = dwSdSizeNeeded;

                       if (!GetUserObjectSecurity(
                            hdesk,
                            &si,
                            psd,
                            dwSidSize,
                            &dwSdSizeNeeded
                            ))
                            __leave;
                       }
                  else
                       __leave;
                  }

             // 
             // create a new security descriptor
             // 
             if (!InitializeSecurityDescriptor(
                  psdNew,
                  SECURITY_DESCRIPTOR_REVISION
                  )) {
				__leave;
				}

             // 
             // obtain the dacl from the security descriptor
             // 
             if (!GetSecurityDescriptorDacl(
                  psd,
                  &bDaclPresent,
                  &pacl,
                  &bDaclExist
                  ))
                  __leave;

             // 
             // initialize
             // 
             ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
             aclSizeInfo.AclBytesInUse = sizeof(ACL);

             // 
             // call only if NULL dacl
             // 
             if (pacl != NULL)
                  {
                  // 
                  // determine the size of the ACL info
                  // 
                  if (!GetAclInformation(
                       pacl,
                       (LPVOID)&aclSizeInfo,
                       sizeof(ACL_SIZE_INFORMATION),
                       AclSizeInformation
                       ))
                       __leave;
                   }

             // 
             // compute the size of the new acl
             // 
        dwNewAclSize = aclSizeInfo.AclBytesInUse +
                            sizeof(ACCESS_ALLOWED_ACE) +
                            GetLengthSid(psid) - sizeof(DWORD);

             // 
             // allocate buffer for the new acl
             // 
             pNewAcl = (PACL)HeapAlloc(
                  GetProcessHeap(),
                  HEAP_ZERO_MEMORY,
                  dwNewAclSize
                  );
             if (pNewAcl == NULL)
                  __leave;

             // 
             // initialize the new acl
             // 
             if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION))
                  __leave;

             // 
             // if DACL is present, copy it to a new DACL
             // 
             if (bDaclPresent) // only copy if DACL was present
                  {
                  // copy the ACEs to our new ACL
                  if (aclSizeInfo.AceCount)
                       {
                       for (i=0; i < aclSizeInfo.AceCount; i++)
                            {
                            // get an ACE
                            if (!GetAce(pacl, i, &pTempAce))
                                 __leave;

                            // add the ACE to the new ACL
                            if (!AddAce(
                                 pNewAcl,
                                 ACL_REVISION,
                                 MAXDWORD,
                                 pTempAce,
                                 ((PACE_HEADER)pTempAce)->AceSize
                                 ))
                                 __leave;
                             }
                        }
                  }

             // 
             // add ace to the dacl
             // 
             if (!AddAccessAllowedAce(
                  pNewAcl,
                  ACL_REVISION,
                  DESKTOP_ALL,
                  psid
                  ))
                  __leave;

             // 
             // set new dacl to the new security descriptor
             // 
             if (!SetSecurityDescriptorDacl(
                       psdNew,
                       TRUE,
                       pNewAcl,
                       FALSE
                       ))
                  __leave;

             // 
             // set the new security descriptor for the desktop object
             // 
             if (!SetUserObjectSecurity(hdesk, &si, psdNew))
                  __leave;

             // 
             // indicate success
             // 
             bSuccess = TRUE;
             }
        __finally
            {
            // 
            // free buffers
            // 
            if (pNewAcl != NULL)
                 HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);

             if (psd != NULL)
                  HeapFree(GetProcessHeap(), 0, (LPVOID)psd);

             if (psdNew != NULL)
                  HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
             }

        return bSuccess;
   }
				
// end of eg code
//---------------------------------------------------

//
//  FUNCTION: ServiceStart
//
//  PURPOSE: Actual code of the service
//           that does the work.
//
//  PARAMETERS:
//    dwArgc   - number of command line arguments
//    lpszArgv - array of command line arguments
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    The default behavior is to monitor
//	  MONITORED_PROCESS, and mirror its
//    run state with LAUNCHED_PROCESS.
//    The service
//    stops when hServerStopEvent is signalled
//

// globals
	SQLHENV	g_env = NULL;    // initialized once only, to
							 // avoid a small handle leak in
							 // the driver.

VOID ServiceStart (DWORD dwArgc, LPTSTR *lpszArgv)
{
    HANDLE                  hPipe = INVALID_HANDLE_VALUE;
    HANDLE                  hEvents[2] = {NULL, NULL};
    PSECURITY_DESCRIPTOR    pSD = NULL;
    SECURITY_ATTRIBUTES     sa;
    LPTSTR                  lpszPipeName = TEXT("\\\\.\\pipe\\simple");
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
	char szProcessName[MAX_PROCESS_NAME_LENGTH];
	int bLaunchedProcessRunning, bMonitoredProcessRunning,
		nLaunchedProcessIndex, nMonitoredProcessIndex;
	SQLRETURN returnValue;
	SQLINTEGER version;
	SQLHDBC dbc = NULL;
	SQLHSTMT stmt = NULL;
	SQLINTEGER sNameLenOrInd;
	unsigned int loopCount;
	char statementText[1024];
	TIMESTAMP_STRUCT stTime;
	struct tm tmTime;
	struct tm *tmNow, *tmCutoff;
	time_t ttTime, now, restartThreshold, lastStartTime, ttCutoff;
	long nFromOrderNumber;
	char szMessage[1024];
	// Initialize ODBC environment for connection to Decade
	// to monitor last update time (and hence health of 
	// launched process)
	// initialize ODBC environment
		returnValue = SQLAllocHandle(SQL_HANDLE_ENV, 
				                     SQL_NULL_HANDLE, 
									 &g_env);
		if (returnValue != SQL_SUCCESS && returnValue != SQL_SUCCESS_WITH_INFO) {
			LogError("Cannot open handle to Decade");
			}
		version = SQL_OV_ODBC3;
		returnValue = SQLSetEnvAttr(g_env, 
									SQL_ATTR_ODBC_VERSION, 
									(void *) version, 
									0);


    ///////////////////////////////////////////////////
    //
    // Service initialization
    //

    // report the status to the service control manager.
    //
    if (!ReportStatusToSCMgr(
        SERVICE_START_PENDING, // service state
        NO_ERROR,              // exit code
        3000))                 // wait hint
        goto cleanup;

    // create the event object. The control handler function signals
    // this event when it receives the "stop" control code.
    //
    hServerStopEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if ( hServerStopEvent == NULL)
        goto cleanup;

    hEvents[0] = hServerStopEvent;

    // report the status to the service control manager.
    //
    if (!ReportStatusToSCMgr(
        SERVICE_START_PENDING, // service state
        NO_ERROR,              // exit code
        3000))                 // wait hint
        goto cleanup;

    // create the event object object use in overlapped i/o
    //
    hEvents[1] = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if ( hEvents[1] == NULL)
        goto cleanup;

    // report the status to the service control manager.
    //
    if (!ReportStatusToSCMgr(
        SERVICE_START_PENDING, // service state
        NO_ERROR,              // exit code
        3000))                 // wait hint
        goto cleanup;

    // create a security descriptor that allows anyone to write to
    //  the pipe...
    //
    pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );

    if (pSD == NULL)
        goto cleanup;

    if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
        goto cleanup;

    // add a NULL disc. ACL to the security descriptor.
    //
    if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
        goto cleanup;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = pSD;
    sa.bInheritHandle = TRUE;


    // report the status to the service control manager.
    //
    if (!ReportStatusToSCMgr(
        SERVICE_START_PENDING, // service state
        NO_ERROR,              // exit code
        3000))                 // wait hint
        goto cleanup;

	// Any time-consuming or time-out prone inits
	// should go here so that service is not
	// reported to be running before it is actually
	// in a fully functional state.

    // report the status to the service control manager.
    //
    if (!ReportStatusToSCMgr(
        SERVICE_RUNNING,       // service state
        NO_ERROR,              // exit code
        0))                    // wait hint
        goto cleanup;

    //
    // End of initialization
    //
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    //
    // Service is now running, perform work until shutdown
    //

	loopCount = 0;
	lastStartTime = 0;
	restartThreshold = INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS;

    while (1) { // main loop
		// Poll for processes of interest
			if (!EnumProcesses(aProcesses, 
				sizeof(aProcesses), &cbNeeded )) {
				// log the failure
				LogError("Unable to enumerate processes");
				}

		// Calculate how many process identifiers were returned.
		    cProcesses = cbNeeded / sizeof(DWORD);

		// Set booleans with status for processes of interest
			bMonitoredProcessRunning = 0;
			bLaunchedProcessRunning = 0;
			for (i = 0; i < cProcesses; i++) {
				FetchProcessName(aProcesses[i],
								 szProcessName);
				if (strstr(szProcessName, MONITORED_PROCESS)) {
					bMonitoredProcessRunning = 1;
					nMonitoredProcessIndex = i;
					}
				if (strstr(szProcessName, LAUNCHED_PROCESS)) {
					bLaunchedProcessRunning = 1;
					nLaunchedProcessIndex = i;
					}
				} // for (i...)

		if (bMonitoredProcessRunning) {
			if (!bLaunchedProcessRunning) {
				// Launch it!
					if (StartLaunchedProcess() == RTN_ERROR) {
						sprintf(szMessage,
							"Unable to start application -- will try again after %d seconds",
							WAIT_INTERVAL_AFTER_LAUNCH_FAILURE / 1000);
						LogError(szMessage);
						if (WaitForSingleObject(hServerStopEvent,
								WAIT_INTERVAL_AFTER_LAUNCH_FAILURE)
								!= WAIT_TIMEOUT) {
							break; // main loop
							}
						}
					else {
						time(&lastStartTime);
						// Give it time to start up,
						// to avoid multiple copies...
							if (WaitForSingleObject(hServerStopEvent,
									WAIT_INTERVAL_AFTER_STATE_CHANGE)
									!= WAIT_TIMEOUT) {
								break; // main loop
								}
						}
				} // if (!bLaunchedProcessRunning)
			else {
				// Check on the monitored process's health
				// (for updateDecadeApp, this means checking
				// for a reasonable d_updatetime.lastupdate
				// value.
				if (++loopCount >= HEALTH_CHECK_INTERVAL_IN_LOOPS) {
					loopCount = 0;
					returnValue = SQLAllocHandle(SQL_HANDLE_DBC, 
												 g_env, &dbc);
					// connection for Decade ODBC connection:
						returnValue = SQLConnect(dbc, 
										 (SQLTCHAR *) DECADE_DATABASE_NAME, 
										 (SQLSMALLINT) strlen(DECADE_DATABASE_NAME), 
										 (SQLTCHAR *) "jamie", 
										 (SQLSMALLINT) 5, 
										 (SQLTCHAR *) "jamie", 
										 (SQLSMALLINT) 5);
						switch (returnValue) {
							case SQL_SUCCESS:
								break;
							case SQL_SUCCESS_WITH_INFO:
								//	iRecord = 1;
								//	SQLGetDiagRec(SQL_HANDLE_DBC, dbc, iRecord, sqlState,
								//		          &sqlError, sqlErrorMessage, 1023, &sqlbErrorMessage);
								break;
							case SQL_ERROR:
								LogError("Error trying to connect to Decade");
								break;
							case SQL_INVALID_HANDLE:
								LogError("Invalid handle complaint on connect to Decade");
								break;
							default:
								LogError("Unknown error connecting to Decade");
								break;
							} // switch
					// Initialize
						returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
													 dbc, &stmt);
					// fetch d_updatetime.lastupdate
						strcpy(statementText, 
							   "SELECT lastordernumber, lastupdate FROM d_updatetime");
						SQLFreeStmt(stmt, SQL_CLOSE);
						returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
						returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
												 &nFromOrderNumber, 
												 sizeof(nFromOrderNumber),
												 &sNameLenOrInd);
						returnValue = SQLBindCol(stmt, 2, 
												 SQL_C_TYPE_TIMESTAMP, 
												 &stTime, 
												 sizeof(stTime),
												 &sNameLenOrInd);
						returnValue = SQLFetch(stmt);
						if (returnValue != SQL_SUCCESS
							&& returnValue != SQL_SUCCESS_WITH_INFO) {
							LogError("Unable to fetch last update time");
							}
						else {
							tmTime.tm_year = stTime.year - 1900;
							tmTime.tm_mon = stTime.month - 1;
							tmTime.tm_mday = stTime.day;
							tmTime.tm_hour = stTime.hour;
							tmTime.tm_min = stTime.minute;
							tmTime.tm_sec = stTime.second;
							ttTime = mktime(&tmTime);
							// ...and check against 
							if (ttTime < lastStartTime) {
								ttTime = lastStartTime;
								}
							// at this point ttTime is the later of the last update time
							// and the last app start time, to give the app time to do
							// a complete update, if it is only just (re)started.

							time(&now);

							// Also check against health check cutoff time
							// (which allows suspension of the check for
							//  evening backups)
								tmCutoff = localtime(&now);
								tmCutoff->tm_hour = LAST_HEALTH_CHECK_HOUR;
								tmCutoff->tm_min  = LAST_HEALTH_CHECK_MINUTE;
								tmCutoff->tm_sec  = LAST_HEALTH_CHECK_SECOND;
								ttCutoff = mktime(tmCutoff);
		
							if ((now <= ttCutoff) && (now - ttTime > restartThreshold)) {
								// kill the target process
									KillProcess(aProcesses[nLaunchedProcessIndex]);
									// it will restart on next loop
									tmNow = localtime(&now);
									sprintf(szMessage, 
										    "%d-%02d-%02d %02d:%02d:%02d Health check is restarting updateDecadeApp.\n",
										    tmNow->tm_year + 1900,
											tmNow->tm_mon + 1,
											tmNow->tm_mday,
											tmNow->tm_hour,
											tmNow->tm_min,
											tmNow->tm_sec);
									LogError(szMessage);
								restartThreshold = (restartThreshold * 3) / 2;
								}
							else if ((now - ttTime) < 
								(HEALTH_CHECK_INTERVAL_IN_LOOPS * MAIN_LOOP_IDLE_INTERVAL)) {
								// reset
								    restartThreshold = INFEASIBLY_LONG_UPDATE_INTERVAL_IN_SECONDS;
								}
							}
						returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
						returnValue = SQLDisconnect(dbc);
						returnValue = SQLFreeHandle(SQL_HANDLE_DBC, dbc);
					} // if (++loopCount...)
				} // else of if (!bLaunchedProcessRunning)
			}
		else {
			if (bLaunchedProcessRunning) {
				// Kill it!
					KillProcess(aProcesses[nLaunchedProcessIndex]);
				// Give it time to die...
					if (WaitForSingleObject(hServerStopEvent,
							WAIT_INTERVAL_AFTER_STATE_CHANGE)
							!= WAIT_TIMEOUT) {
						break; // main loop
						}
				}
			}

		// To maintain a low impact, spend most of the time
		// asleep.
			if (WaitForSingleObject(hServerStopEvent,
					MAIN_LOOP_IDLE_INTERVAL)
					!= WAIT_TIMEOUT) {
				break; // main loop
				}
	} // main loop

  cleanup:

    if (hServerStopEvent)
        CloseHandle(hServerStopEvent);

    if ( pSD )
        free( pSD );

}


//
//  FUNCTION: ServiceStop
//
//  PURPOSE: Stops the service
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    If a ServiceStop procedure is going to
//    take longer than 3 seconds to execute,
//    it should spawn a thread to execute the
//    stop code, and return.  Otherwise, the
//    ServiceControlManager will believe that
//    the service has stopped responding.
//    
VOID ServiceStop()
{
    if ( hServerStopEvent )
        SetEvent(hServerStopEvent);
}
