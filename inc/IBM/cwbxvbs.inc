
' enum cwbReturnCodeEnum
' Client Access Express return code constants
Const cwbOK = 0
Const cwbInvalidFunction = 1
Const cwbFileNotFound = 2
Const cwbPathNotFound = 3
Const cwbTooManyOpenFiles = 4
Const cwbAccessDenied = 5
Const cwbInvalidHandle = 6
Const cwbNotEnoughMemory = 8
Const cwbInvalidDrive = 15
Const cwbNoMoreFiles = 18
Const cwbDriveNotReady = 21
Const cwbGeneralFailure = 31
Const cwbSharingViolation = 32
Const cwbLockViolation = 33
Const cwbEndOfFile = 38
Const cwbNotSupported = 50
Const cwbBadNetworkPath = 53
Const cwbNetworkBusy = 54
Const cwbDeviceNotExist = 55
Const cwbUnexpectedNetworkError = 59
Const cwbNetworkAccessDenied = 65
Const cwbFileExists = 80
Const cwbAlreadyAssigned = 85
Const cwbInvalidParameter = 87
Const cwbNetworkWriteFault = 88
Const cwbOpenFailed = 110
Const cwbBufferOverflow = 111
Const cwbDiskFull = 112
Const cwbProtectionViolation = 115
Const cwbInvalidLevel = 124
Const cwbBusyDrive = 142
Const cwbInvalidFSDName = 252
Const cwbInvalidPath = 253
Const cwbUserCancelledCommand = 4000
Const cwbConfigError = 4001
Const cwbLicenseError = 4002
Const cwbProdOrCompNotSet = 4003
Const cwbSecurityError = 4004
Const cwbGlobalCfgFailed = 4005
Const cwbProdRetrieveFailed = 4006
Const cwbCompRetrieveFailed = 4007
Const cwbCompCfgFailed = 4008
Const cwbCompFixLevelUpdateFailed = 4009
Const cwbInvalidAPIHandle = 4010
Const cwbInvalidAPIParameter = 4011
Const cwbHostNotFound = 4012
Const cwbNotCompatible = 4013
Const cwbInvalidPointer = 4014
Const cwbServerProgramNotFound = 4015
Const cwbAPIError = 4016
Const cwbCANotStarted = 4017
Const cwbFileIOError = 4018
Const cwbCommunicationsError = 4019
Const cwbRuntimeConstructorFailed = 4020
Const cwbDiagnostic = 4021
Const cwbCommVersionError = 4022
Const cwbNoViewer = 4023
Const cwbModuleNotLoadable = 4024
Const cwbAlreadySetup = 4025
Const cwbCannotStartProcess = 4026
Const cwbNonRepresentableUnicodeChar = 4027
Const cwbEntryNotFound = 4028
Const cwbUnknownUserid = 8001
Const cwbWrongPassword = 8002
Const cwbPasswordExpired = 8003
Const cwbInvalidPassword = 8004
Const cwbPasswordToExpire = 8005
Const cwbIncorrectDataFormat = 8006
Const cwbGeneralSecurityError = 8007
Const cwbUserProfileDisabled = 8011
Const cwbUserCancelled = 8013
Const cwbInvalidSysname = 8014
Const cwbInvalidUserid = 8015
Const cwbLimitedCapabilitiesUserid = 8016
Const cwbWindowsUserIDNotFound = 8017
Const cwbWindowsPasswordNotFound = 8018
Const cwbInvalidTPOnHost = 8019
Const cwbNotLoggedOn = 8022
Const cwbExitPgmError = 8026
Const cwbTimestampsNotSet = 8050
Const cwbPWTooLong = 8257
Const cwbPWTooShort = 8258
Const cwbPWRepeatCharacter = 8259
Const cwbPWAdjacentDigits = 8260
Const cwbPWConsecutiveChars = 8261
Const cwbPWPreviouslyUsed = 8262
Const cwbPWDisallowedChar = 8263
Const cwbPWNeedNumeric = 8264
Const cwbPWMatchesOld = 8266
Const cwbPWNotAllowed = 8267
Const cwbPWContainsUserid = 8268
Const cwbPWLastInvalidPwd = 8270
Const cwbInvAfterSignon = 8400
Const cwbInvWhenConnected = 8401
Const cwbInvBeforeValidate = 8402
Const cwbSecureSocketsNotavail = 8403
Const cwbReserved1 = 8404
Const cwbReceiveError = 8405
Const cwbServiceNameError = 8406
Const cwbGetPortError = 8407
Const cwbSuccessWarning = 8408
Const cwbNotConnected = 8409
Const cwbDefaultHostCodePageUsed = 8410
Const cwbUserTimeout = 8411
Const cwbSSLJavaError = 8412
Const cwbUserTimeoutSendReceive = 8413
Const cwbRestrictedByPolicy = 8500
Const cwbPolicyModifyMandatedEnv = 8501
Const cwbPolicyModifyCurrentEnv = 8502
Const cwbPolicyModifyEnvList = 8503
Const cwbSystemNotFound = 8504
Const cwbEnvironmentNotFound = 8505
Const cwbEnvironmentExists = 8506
Const cwbSystemExists = 8507
Const cwbNoSystemsConfigured = 8508
Const cwbInvalidMethodParm = 8600
Const cwbInvalidPropertyParm = 8601
Const cwbInvalidPropertyValue = 8602
Const cwbObjectNotInitialized = 8603
Const cwbObjectAlreadyInitialized = 8604
Const cwbInvalidDQOrder = 8605
Const cwbDataTransferRequired = 8606
Const cwbUnsupportedXferRequest = 8607
Const cwbAsyncRequestActive = 8608
Const cwbRequestTimedOut = 8609
Const cwbCannotSetPropNow = 8610
Const cwbObjStateNoLongerValid = 8611
Const cwbUnsupportedFunction = 8998
Const cwbInternalError = 8999
Const cwbTooManyOpenSockets = 10024
Const cwbResourceTemporarilyUnavailable = 10035
Const cwbSocketOperationOnNonSocket = 10038
Const cwbProtocolNotInstalled = 10047
Const cwbNetworkIsDown = 10050
Const cwbNetworkIsUnreachable = 10051
Const cwbNetworkDroppedConnectionOnReset = 10052
Const cwbSoftwareCausedConnectionAbort = 10053
Const cwbConnectionResetByPeer = 10054
Const cwbNoBufferSpaceAvailable = 10055
Const cwbSocketIsNotConnected = 10057
Const cwbCannotSendAfterSocketShutdown = 10058
Const cwbConnectionTimedOut = 10060
Const cwbConnectionRefused = 10061
Const cwbHostIsDown = 10064
Const cwbNoRouteToHost = 10065
Const cwbNetworkSubsystemIsUnavailable = 10091
Const cwbWinsockVersionNotSupported = 10092
Const cwbHostDefinitelyNotFound = 11001
Const cwbHostNotFoundButWeAreNotSure = 11002
Const cwbValidNameButNoDataRecord = 11004
Const cwbSSLKeyfileIOError = 20001
Const cwbSSLKeyfileOpenFailed = 20002
Const cwbSSLKeyfileBadFormat = 20003
Const cwbSSLKeyfileBadPassword = 20004
Const cwbSSLKeyfileBadMalloc = 20005
Const cwbSSLKeyfileNothingToWrite = 20006
Const cwbSSLKeyfileWriteFailed = 20007
Const cwbSSLKeyfileNotFound = 20008
Const cwbSSLKeyfileBadDName = 20009
Const cwbSSLKeyfileBadKey = 20010
Const cwbSSLKeyfileKeyExists = 20011
Const cwbSSLKeyfileBadLabel = 20012
Const cwbSSLKeyfileDuplicateName = 20013
Const cwbSSLKeyfileDuplicateKey = 20014
Const cwbSSLKeyfileDuplicateLabel = 20015
Const cwbSSLBadFormatOrInvalidPW = 20016
Const cwbSSLWarningInvalidServerCert = 20098
Const cwbSSLWarningInvalidServerPrivKey = 20099
Const cwbSSLErrInitParmNotValid = 20100
Const cwbSSLInitSecTypeNotValid = 20102
Const cwbSSLInitV2TimeoutNotValid = 20103
Const cwbSSLInitV3TimeoutNotValid = 20104
Const cwbSSLKeyfileCertExpired = 20105
Const cwbSSLErrorNoCiphers = 25001
Const cwbSSLErrorNoCertificate = 25002
Const cwbSSLErrorBadCertificate = 25004
Const cwbSSLErrorUnsupportedCertificateType = 25006
Const cwbSSLErrorIO = 25010
Const cwbSSLErrorBadMessage = 25011
Const cwbSSLErrorBadMac = 25012
Const cwbSSLErrorUnsupported = 25013
Const cwbSSLErrorBadCertSig = 25014
Const cwbSSLErrorBadCert = 25015
Const cwbSSLErrorBadPeer = 25016
Const cwbSSLErrorPermissionDenied = 25017
Const cwbSSLErrorSelfSigned = 25018
Const cwbSSLErrorBadMalloc = 25020
Const cwbSSLErrorBadState = 25021
Const cwbSSLErrorSocketClosed = 25022
Const cwbSSLErrorSSLInitializationFailed = 25023
Const cwbSSLErrorHandleCreationFailed = 25024
Const cwbSSLErrorBadDate = 25025
Const cwbSSLErrorBadKeyLenForExport = 25026
Const cwbSSLErrorNoPrivateKey = 25027
Const cwbSSLBadParameter = 25028
Const cwbSSLErrorInternal = 25029
Const cwbSSLErrorWouldBlock = 25030
Const cwbSSLErrorLoadGsklib = 25031
Const cwbSSLSocBadV2Cipher = 25040
Const cwbSSLSocBadV3Cipher = 25041
Const cwbSSLSocBadSecType = 25042
Const cwbSSLSocNoReadFunction = 25043
Const cwbSSLSocNoWriteFunction = 25044
Const cwbSSLErrorNotServer = 25050
Const cwbSSLErrorNotSSLV3 = 25051
Const cwbSSLErrorNotSSLV3Client = 25052
Const cwbSSLErrorUnknownError = 25099
Const cwbSSLErrorBadBufferSize = 25100
Const cwbSSLErrorBadSSLHandle = 25101
Const cwbSSLErrorTimeout = 25102

' enum cwbHResultEnum
' Client Access Express custom HRESULT constants
Const cwbxEInvalidMethodParm = &H80042198
Const cwbxEInvalidPropertyParm = &H80042199
Const cwbxEInvalidPropertyValue = &H8004219a
Const cwbxEObjectNotInitialized = &H8004219b
Const cwbxEObjectAlreadyInitialized = &H8004219c
Const cwbxEInvalidDQOrder = &H8004219d
Const cwbxEUnsupportedXferRequest = &H8004219f
Const cwbxEAsyncRequestActive = &H800421a0
Const cwbxEPolicyRestriction = &H80042134
Const cwbxERequestTimedOut = &H800421a1
Const cwbxECannotSetPropNow = &H800421a2
Const cwbxEObjStateNoLongerValid = &H800421a3

' enum cwbcoServiceEnum
' AS/400 host service constants
Const cwbcoServiceCentral = 1
Const cwbcoServiceNetFile = 2
Const cwbcoServiceNetPrint = 3
Const cwbcoServiceDatabase = 4
Const cwbcoServiceODBC = 5
Const cwbcoServiceDataQueues = 6
Const cwbcoServiceRemoteCmd = 7
Const cwbcoServiceSecurity = 8
Const cwbcoServiceDDM = 9
Const cwbcoServiceMAPI = 10
Const cwbcoServiceUSF = 11
Const cwbcoServiceWebAdmin = 12
Const cwbcoServiceTelnet = 13
Const cwbcoServiceMgmtCentral = 14
Const cwbcoServiceAny = 100
Const cwbcoServiceAll = 101

' enum cwbcoPromptModeEnum
' AS/400 prompt mode constants
Const cwbcoPromptIfNecessary = 0
Const cwbcoPromptAlways = 1
Const cwbcoPromptNever = 2
Const cwbcoPromptDefault = 0

' enum cwbcoValidateModeEnum
' AS/400 validate mode constants
Const cwbcoValidateIfNecessary = 0
Const cwbcoValidateAlways = 1
Const cwbcoValidateDefault = 0

' enum cwbcoDefaultUserModeEnum
' AS/400 default user mode constants
Const cwbcoDefaultUserModeNotSet = 0
Const cwbcoDefaultUserUse = 1
Const cwbcoDefaultUserIgnore = 2
Const cwbcoDefaultUserUseWinlogon = 3
Const cwbcoDefaultUserDefault = 0

' enum cwbcoIPAddrLookupModeEnum
' AS/400 IP address lookup mode constants
Const cwbcoIPAddrLookupAlways = 0
Const cwbcoIPAddrLookup1Hour = 1
Const cwbcoIPAddrLookup1Day = 2
Const cwbcoIPAddrLookup1Week = 3
Const cwbcoIPAddrLookupNever = 4
Const cwbcoIPAddrLookupAfterStartup = 5
Const cwbcoIPAddrLookupDefault = 0

' enum cwbcoPortLookupModeEnum
' AS/400 port lookup mode constants
Const cwbcoPortLookupServer = 0
Const cwbcoPortLookupLocal = 1
Const cwbcoPortLookupStandard = 2
Const cwbcoPortLookupDefault = 0

' enum cwbcoPersistenceModeEnum
' AS/400 persistent configuration mode constants
Const cwbcoMayMakePersistent = 0
Const cwbcoMayNotMakePersistent = 1
Const cwbcoPersistenceDefault = 0

' enum cwbcoMaxStringSizeEnum
' Client Access Express maximum string length constants
Const cwbcoMaxUserID = 10
Const cwbcoMaxPassword = 256
Const cwbcoMaxSysName = 255
Const cwbcoMaxEnvName = 50
Const cwbcoMaxServiceName = 32
Const cwbcoMaxIPAddress = 15
Const cwbcoMaxSSLPassword = 128

' enum cwbadClientComponentEnum
' Client Access Express installed component constants
Const cwbadCompBaseSupport = 1
Const cwbadCompOptionalComponents = 2
Const cwbadCompDirectoryUpdate = 3
Const cwbadCompIRC = 4
Const cwbadCompMAPI = 5
Const cwbadCompOnlineUsersGuide = 6
Const cwbadCompOpNav = 7
Const cwbadCompDataAccess = 8
Const cwbadCompDataTransfer = 9
Const cwbadCompDataTransferBase = 10
Const cwbadCompDataTransferExcelAddin = 11
Const cwbadCompDataTransferWK4Support = 12
Const cwbadCompODBC = 13
Const cwbadCompOLEDB = 14
Const cwbadCompAFPViewer = 15
Const cwbadCompJavaToolbox = 16
Const cwbadCompPC5250 = 17
Const cwbadCompPrinterDrivers = 18
Const cwbadCompAFPDriver = 19
Const cwbadCompSCSDriver = 20
Const cwbadCompOpConsole = 21
Const cwbadCompToolkit = 22
Const cwbadCompToolkitBase = 23
Const cwbadCompToolkitOLEDBWizards = 24
Const cwbadCompEZSetup = 25
Const cwbadCompToolkitJavaTools = 26
Const cwbadCompScreenCustomizerEnablement = 27
Const cwbadCompOpNavBaseSupport = 100
Const cwbadCompOpNavBasicOperations = 101
Const cwbadCompOpNavJobManagement = 102
Const cwbadCompOpNavSystemConfiguration = 103
Const cwbadCompOpNavNetwork = 104
Const cwbadCompOpNavSecurity = 105
Const cwbadCompOpNavUsersAndGroups = 106
Const cwbadCompOpNavDatabase = 107
Const cwbadCompOpNavMultimedia = 108
Const cwbadCompOpNavBackup = 109
Const cwbadCompOpNavAppDevelopment = 110
Const cwbadCompOpNavAppAdministration = 111
Const cwbadCompOpNavFileSystems = 112
Const cwbadCompOpNavMgmtCentral = 113
Const cwbadCompOpNavMgmtCommands = 114
Const cwbadCompOpNavMgmtPackProd = 115
Const cwbadCompOpNavMgmtMonitors = 116
Const cwbadCompOpNavLogicalSys = 117
Const cwbadCompOpNavAdvFuncPres = 118
Const cwbadCompPC5250KoreanBase = 150
Const cwbadCompPC5250KoreanPDFPDTFiles = 151
Const cwbadCompPC5250SimpChinBase = 152
Const cwbadCompPC5250SimpChinPDFPDTFiles = 153
Const cwbadCompPC5250TradChinBase = 154
Const cwbadCompPC5250TradChinPDFPDTFiles = 155
Const cwbadCompPC5250StandardBase = 156
Const cwbadCompPC5250StandardPDFPDTFiles = 157
Const cwbadCompPC5250FontArabic = 158
Const cwbadCompPC5250FontBaltic = 159
Const cwbadCompPC5250FontLatin2 = 160
Const cwbadCompPC5250FontCyrillic = 161
Const cwbadCompPC5250FontGreek = 162
Const cwbadCompPC5250FontHebrew = 163
Const cwbadCompPC5250FontLao = 164
Const cwbadCompPC5250FontThai = 165
Const cwbadCompPC5250FontTurkish = 166
Const cwbadCompPC5250FontVietnamese = 167
Const cwbadCompSSL = 200
Const cwbadCompSSL128Bit = 201
Const cwbadCompSSL56Bit = 202
Const cwbadCompSSL40Bit = 203

' enum cwbdqAuthorityEnum
' Data queues public authority constants
Const cwbdqAll = 0
Const cwbdqExclude = 1
Const cwbdqChange = 2
Const cwbdqUse = 3
Const cwbdqLibcrtaut = 4

' enum cwbdqRetrievalOrderEnum
' Data queues retrieval order constants
Const cwbdqSeqLifo = 0
Const cwbdqSeqFifo = 1
Const cwbdqSeqKeyed = 2

' enum cwbdqSearchOrderEnum
' Data queues search order constants
Const cwbdqEqual = 1
Const cwbdqNotEqual = 2
Const cwbdqGtOrEqual = 3
Const cwbdqGreater = 4
Const cwbdqLtOrEqual = 5
Const cwbdqLess = 6

' enum cwbdqReturnCodeEnum
' Data queues return code constants
Const cwbdqInvalidAttributeHandle = 6000
Const cwbdqInvalidDataHandle = 6001
Const cwbdqInvalidQueueHandle = 6002
Const cwbdqInvalidReadHandle = 6003
Const cwbdqInvalidQueueLength = 6004
Const cwbdqInvalidKeyLength = 6005
Const cwbdqInvalidOrder = 6006
Const cwbdqInvalidAuthority = 6007
Const cwbdqInvalidQueueTitle = 6008
Const cwbdqBadQueueName = 6009
Const cwbdqBadLibraryName = 6010
Const cwbdqBadSystemName = 6011
Const cwbdqBadKeyLength = 6012
Const cwbdqBadDataLength = 6013
Const cwbdqInvalidTime = 6014
Const cwbdqInvalidSearch = 6015
Const cwbdqDataTruncated = 6016
Const cwbdqTimedOut = 6017
Const cwbdqRejectedUserExit = 6018
Const cwbdqUserExitError = 6019
Const cwbdqLibraryNotFound = 6020
Const cwbdqQueueNotFound = 6021
Const cwbdqNoAuthority = 6022
Const cwbdqDamagedQueue = 6023
Const cwbdqQueueExists = 6024
Const cwbdqInvalidMessageLength = 6025
Const cwbdqQueueDestroyed = 6026
Const cwbdqNoData = 6027
Const cwbdqCannotConvert = 6028
Const cwbdqQueueSyntax = 6029
Const cwbdqLibrarySyntax = 6030
Const cwbdqAddressNotSet = 6031
Const cwbdqHostError = 6032
Const cwbdqInvalidSystemHandle = 6033
Const cwbdqUnexpectedError = 6099

' enum cwbrcParameterTypeEnum
' Distributed program call parameter type constants
Const cwbrcInput = 1
Const cwbrcOutput = 2
Const cwbrcInout = 3

' enum cwbsvErrorClassEnum
' Client Access Express error class constants
Const cwbsvClassInformational = 0
Const cwbsvClassWarning = 1
Const cwbsvClassError = 2
Const cwbsvClassErrorRetry = 1
Const cwbsvClassErrorAbort = 2
Const cwbsvClassHostWarning = 10
Const cwbsvClassHostError = 20
Const cwbsvClassHostSevError = 30
Const cwbsvClassHostSevErrorAbend = 40
Const cwbsvClassHostJobAbend = 50
Const cwbsvClassHostSysStatus = 60
Const cwbsvClassHostDeviceIntegrity = 70
Const cwbsvClassHostSysAlert = 80
Const cwbsvClassHostSysIntegrity = 90
Const cwbsvClassHostActionRequired = 99

' enum cwbrcReturnCodeEnum
' Distributed program call and remote command return code constants
Const cwbrcInvalidSystemHandle = 6000
Const cwbrcInvalidProgram = 6001
Const cwbrcSystemName = 6002
Const cwbrcCommandString = 6003
Const cwbrcProgramName = 6004
Const cwbrcLibraryName = 6005
Const cwbrcInvalidType = 6006
Const cwbrcInvalidParmLength = 6007
Const cwbrcInvalidParm = 6008
Const cwbrcTooManyParms = 6009
Const cwbrcIndexRangeError = 6010
Const cwbrcRejectedUserExit = 6011
Const cwbrcUserExitError = 6012
Const cwbrcCommandFailed = 6013
Const cwbrcProgramNotFound = 6014
Const cwbrcProgramError = 6015
Const cwbrcCommandTooLong = 6016
Const cwbrcUnexpectedError = 6099

' enum cwbnlReturnCodeEnum
' Code page conversion return code constants
Const cwbnlCnvUnsupported = 6101
Const cwbnlCnvTblInvalid = 6102
Const cwbnlCnvTblMissing = 6103
Const cwbnlCnvErrGet = 6104
Const cwbnlCnvErrComm = 6105
Const cwbnlCnvErrServer = 6106
Const cwbnlCnvErrStatus = 6107
Const cwbnlCnvIncompleteMultibyteInputChar = 6108
Const cwbnlCnvInvalidSISOStatus = 6109
Const cwbnlCnvInvalidPadLength = 6110

' enum cwbnlCodePageEnum
' Client Access Express code page constants
Const cwbnlCodePageAS400 = 1
Const cwbnlCodePageClientOEM = 2
Const cwbnlCodePageClientANSI = 3
Const cwbnlCodePageUnicodeBigEndian = 1200
Const cwbnlCodePageClientUnicode = 1202
Const cwbnlCodePageUTF8 = 1208
Const cwbnlCodePageUnicode = 13488
Const cwbnlCodePageUnicodeF200 = 61952

' enum cwbdtTimeSeparatorEnum
' Database Transfer time separator constants
Const cwbdtTimeSepNotSpecified = 0
Const cwbdtTimeSepColon = 1
Const cwbdtTimeSepPeriod = 2
Const cwbdtTimeSepComma = 3
Const cwbdtTimeSepBlank = 4


' enum cwbdtTimeFormatEnum
' Database Transfer time format constants
Const cwbdtTimeFmtHourMinSec = 0
Const cwbdtTimeFmtUSA = 1
Const cwbdtTimeFmtISO = 2
Const cwbdtTimeFmtEUR = 3
Const cwbdtTimeFmtJIS = 4

' enum cwbdtDateSeparatorEnum
' Database Transfer date separator constants
Const cwbdtDateSepNotSpecified = 0
Const cwbdtDateSepSlash = 1
Const cwbdtDateSepDash = 2
Const cwbdtDateSepPeriod = 3
Const cwbdtDateSepComma = 4
Const cwbdtDateSepBlank = 5

' enum cwbdtDateFormatEnum
' Database Transfer date format constants
Const cwbdtDateFmtJulian = 0
Const cwbdtDateFmtMonDayYr = 1
Const cwbdtDateFmtDayMonYr = 2
Const cwbdtDateFmtYrMonDay = 3
Const cwbdtDateFmtUSA = 4
Const cwbdtDateFmtISO = 5
Const cwbdtDateFmtEUR = 6
Const cwbdtDateFmtJIS = 7

' enum cwbdtDecimalSeparatorEnum
' Database Transfer decimal separator constants
Const cwbdtDecSepPeriod = 0
Const cwbdtDecSepComma = 1

' enum cwbdtAS400FileCreateEnum
' Database Transfer AS/400 file creation option constants
Const cwbdtCreateMember = 0
Const cwbdtCreateFileAndMember = 1
Const cwbdtReplaceMember = 2
Const cwbdtAppendToMember = 3

' enum cwbdtObjectAuthorityEnum
' Database Transfer AS/400 object authority constants
Const cwbdtObjAuthReadWrite = 0
Const cwbdtObjAuthReadOnly = 1
Const cwbdtObjAuthAll = 2
Const cwbdtObjAuthNone = 3

' enum cwbdtFileTypeEnum
' Database Transfer PC file type constants
Const cwbdtFileTypeNotSet = 0
Const cwbdtASCIIText = 1
Const cwbdtDosRandom = 2
Const cwbdtBasicSequential = 3
Const cwbdtBasicRandom = 4
Const cwbdtDIF = 5
Const cwbdtNoConversion = 6
Const cwbdtDosRandomType2 = 8
Const cwbdtBIFF4 = 9
Const cwbdtBIFF3 = 10
Const cwbdtBIFF5 = 11
Const cwbdtCSV = 12
Const cwbdtWK4 = 13
Const cwbdtTabDelimitedText = 14
Const cwbdtBIFF7 = 15
Const cwbdtBIFF8 = 16
Const cwbdt123 = 17
Const cwbdt123v9 = 19
Const cwbdtUnicodeText = 20
Const cwbdtExcelXML = 21
Const cwbdtHTML = 100

' enum cwbdtExistingOutputFileEnum
' Database Transfer existing PC file option constants
Const cwbdtOverwriteOutFile = 0
Const cwbdtAppendOutFile = 1
Const cwbdtFailDownload = 2
Const cwbdtCreateOverwriteOutFileEvenWhenEmptyResultsSet = 3

' enum cwbdtHTMLConversionTypeEnum
' Database Transfer HTML conversion type constants
Const cwbdtHTMLConvANSI = 0
Const cwbdtHTMLConvASCII = 1
Const cwbdtHTMLConvUTF8 = 2

' enum cwbdtDateTimeLocationEnum
' Database Transfer HTML date/time location constants
Const cwbdtDateTimeDoNotInclude = 0
Const cwbdtDateTimeUpperLeft = 1
Const cwbdtDateTimeLowerLeft = 2
Const cwbdtDateTimeUpperRight = 3
Const cwbdtDateTimeLowerRight = 4

' enum cwbdtTableAlignmentEnum
' Database Transfer HTML table alignment constants
Const cwbdtTableAlignLeft = 0
Const cwbdtTableAlignCenter = 1
Const cwbdtTableAlignRight = 2

' enum cwbdtSizeUnitsEnum
' Database Transfer HTML table width units constants
Const cwbdtSizePercentOfWindow = 0
Const cwbdtSizePixels = 1

' enum cwbdtCaptionAlignmentEnum
' Database Transfer HTML caption alignment constants
Const cwbdtCaptionAlignBrowserDefault = 0
Const cwbdtCaptionAlignTop = 1
Const cwbdtCaptionAlignBottom = 2
Const cwbdtCaptionAlignLeft = 3
Const cwbdtCaptionAlignRight = 4

' enum cwbdtTextSizeEnum
' Database Transfer HTML text size constants
Const cwbdtTextNormal = 0
Const cwbdtTextSmall = 1
Const cwbdtTextLarge = 2

' enum cwbdtVerticalAlignEnum
' Database Transfer HTML vertical alignment constants
Const cwbdtVertAlignBrowserDefault = 0
Const cwbdtVertAlignTop = 1
Const cwbdtVertAlignMiddle = 2
Const cwbdtVertAlignBottom = 3

' enum cwbdtHorizontalAlignEnum
' Database Transfer HTML horizontal alignment constants
Const cwbdtHorizAlignBrowserDefault = 0
Const cwbdtHorizAlignLeft = 1
Const cwbdtHorizAlignCenter = 2
Const cwbdtHorizAlignRight = 3

' enum cwbdtCellDataAlignEnum
' Database Transfer HTML cell data alignment constants
Const cwbdtCellDataAlignSameAsRow = 0
Const cwbdtCellDataAlignLeft = 1
Const cwbdtCellDataAlignCenter = 2
Const cwbdtCellDataAlignRight = 3

' enum cwbdtExtraRowsActionEnum
' Database Transfer HTML extra rows action constants
Const cwbdtTruncExtraRows = 0
Const cwbdtGenerateMultTables = 1
Const cwbdtGenerateMultDocs = 2

' enum cwbdtFewerRowsActionEnum
' Database Transfer HTML fewer rows action constants
Const cwbdtIgnoreExtraRows = 0
Const cwbdtGenerateBlankRows = 1

' enum cwbdtTextStyleEnum
' Database Transfer HTML text style constants
Const cwbdtTextBrowserDefaultStyle = 0
Const cwbdtTextBold = 1
Const cwbdtTextItalic = 2
Const cwbdtTextUnderline = 4
Const cwbdtTextFixedWidth = 8

' enum cwbdtConstants
' Database Transfer general constants
Const cwbdtNoMaximum = &HFFFFFFFF
Const cwbdtBrowserDefault = &HFFFFFFFE

' enum cwbdtTransferStatusEnum
' Database Transfer request status constants
Const cwbdtStatusCompletedOK = 0
Const cwbdtStatusCompletedWithWarning = 1
Const cwbdtStatusCompletedWithError = 2
Const cwbdtStatusConnectingToAS400 = 3
Const cwbdtStatusPerformingQuery = 4
Const cwbdtStatusReceivingData = 5
Const cwbdtStatusPerformingFileSetup = 6
Const cwbdtStatusSendingData = 7
Const cwbdtStatusRowsTransferred = 8
Const cwbdtStatusUpdatingPCFile = 9

' enum cwbdtDataErrorEnum
' Database Transfer data error type constants
Const cwbdtWarningTruncation = 1
Const cwbdtWarningRounding = 2
Const cwbdtWarningMissingData = 3
Const cwbdtWarningUntranslatableField = 4
Const cwbdtErrorTruncation = 5
Const cwbdtErrorRounding = 6
Const cwbdtErrorMissingData = 7
Const cwbdtErrorUntranslatableField = 8

' enum cwbdtSortSequenceTypeEnum
' Database Transfer sort sequence type constants
Const cwbdtSortAS400Default = 0
Const cwbdtSortHexadecimal = 1
Const cwbdtSortUserSpecifiedTable = 2
Const cwbdtSortSharedWeightTable = 3
Const cwbdtSortUniqueWeightTable = 4

' enum cwbdtReturnCodeEnum
' Database Transfer return code constants
Const cwbdtFileAlreadyExists = 7002
Const cwbdtTooManyRecords = 7003
Const cwbdtNoMatchingData = 7004
Const cwbdtIncorrectData = 7005
Const cwbdtInvalidFieldType = 7006
Const cwbdtDataRounded = 7007
Const cwbdtTooManyDigits = 7008
Const cwbdtPCDataTruncated = 7009
Const cwbdtDataPadded = 7010
Const cwbdtAS400DataTruncated = 7011
Const cwbdtUnexpectedError = 7012
Const cwbdtInvalidRecordLength = 7013
Const cwbdtErrorClosingFile = 7014
Const cwbdtErrorOpeningFile = 7015
Const cwbdtErrorWritingFile = 7016
Const cwbdtDiskFull = 7017
Const cwbdtNoRecordsToTransfer = 7018
Const cwbdtDataMissing = 7019
Const cwbdtExtraDataNotTransferred = 7020
Const cwbdtFDFRequired = 7021
Const cwbdtFileNotFound = 7022
Const cwbdtFDFEmpty = 7023
Const cwbdtTooManyFields = 7024
Const cwbdtIncorrectFieldLength = 7025
Const cwbdtInvalidPCFile = 7026
Const cwbdtInvalidPCType = 7027
Const cwbdtInvalidFDF = 7028
Const cwbdtFieldTypeNotCompat = 7029
Const cwbdtFieldNameTooLong = 7030
Const cwbdtInvalidDecPosition = 7031
Const cwbdtNotEnoughMemory = 7032
Const cwbdtHostFileNameRequired = 7033
Const cwbdtPCFileNameRequired = 7034
Const cwbdtInvalidHostFile = 7035
Const cwbdtNoFilesInLibrary = 7036
Const cwbdtCantTransferSourceAndDB = 7037
Const cwbdtInvalidLibFileName = 7038
Const cwbdtInvalidFRFFile = 7039
Const cwbdtHostFileDoesntExist = 7040
Const cwbdtFilesDontMatch = 7041
Const cwbdtInvalidColumnType = 7042
Const cwbdtInvalidSortSequence = 7043
Const cwbdtAppendFileDoesntExist = 7044
Const cwbdtLibraryDoesntExist = 7045
Const cwbdtLibListEntryRemoved = 7046
Const cwbdtAppendSourceWarning = 7047
Const cwbdtUploadFDFRequired = 7048
Const cwbdtTemplateDoesntExist = 7049
Const cwbdtTemplateTagRequired = 7050
Const cwbdtInvalidTemplateTag = 7051
Const cwbdtCreateInitFailure = 7052
Const cwbdtCantLoadWK4ConvFile = 7053
Const cwbdtNoValidData = 7054
Const cwbdtInvalidPCFileFormat = 7055
Const cwbdtInvalidWorksheet = 7056
Const cwbdtAS400File = 7057
Const cwbdtSSLNotAvailable = 7058
Const cwbdtCantChangeSecurity = 7059
Const cwbdtCantSetMember = 7060
Const cwbdtSQLStatementTooLong = 7061
Const cwbdtDatalinkNotSupported = 7062
Const cwbdtMemberNameRequired = 7063
Const cwbdtRequestAlreadyExists = 7064
Const cwbdtRowTooLong = 7065
Const cwbdtBadValueDefaulted = 7066
Const cwbdtExpressPathNotFound = 7067
Const cwbdtWK4NotEnoughMemory = 7068
Const cwbdtWK4MappingNotFound = 7069
Const cwbdtWK4InvalidConvTable = 7070
Const cwbdtWK4ConvInitError = 7071
Const cwbdtWK4FilesWrongLevels = 7072
Const cwbdtTooManyFiles = 7073
Const cwbdtErrorAddingLibToList = 7074
Const cwbdtWK4ConversionError = 7075
Const cwbdtBadTransferRequest = 7400
Const cwbdtUnicodeConversionError = 7401
Const cwbdtPCFileSameAsFDFFile = 7402
Const cwbdtTransferRequestNotExist = 7403
Const cwbdtTransferRequestExists = 7404
Const cwbdtWK4NoTranslationDLL = 7405
Const cwbdtWK4NonMatchingLevels = 7406
Const cwbdtWK4OpenInitializationError = 7407
Const cwbdtWK4InvalidTable = 7408
Const cwbdtWK4NoMappingForCCSID = 7409
Const cwbdtBadLibraryListIndex = 7410
Const cwbdtMemberNameNotSpecified = 7411
Const cwbdtDatabaseServerError = 7412
Const cwbdtLibraryAlreadyInList = 7463
Const cwbdtLibraryNotFoundInList = 7464
Const cwbdtLibraryNameNotValid = 7465
Const cwbdtGeneralLibListFailure = 7466
Const cwbdtDBStartError = 7467
Const cwbdtSystemConfigFailure = 7468
Const cwbdtCancelTimedOut = 7470
Const cwbdtCancelInProgress = 7471
Const cwbdtCancelProcessedSuccessfully = 7472
Const cwbdtInvalidMemberName = 7474
Const cwbdtUnsupportedFieldType = 7475
Const cwbdtCannotUseExcelFDF = 7476

' enum cwbdtFDFFormatEnum
' FDF Format type constants
Const cwbdtStandardFDF = 0
Const cwbdtEnhancedFDF = 1

' enum cwbdbReturnCodeEnum
' Database return code constants
Const cwbdbCannotContactServer = 6001
Const cwbdbAttributesFailure = 6002
Const cwbdbServerAlreadyStarted = 6003
Const cwbdbInvalidDRDAPackageSize = 6004
Const cwbdbRequestMemoryAllocationFailure = 6005
Const cwbdbRequestInvalidConversion = 6006
Const cwbdbServerNotActive = 6007
Const cwbdbParameterError = 6008
Const cwbdbCloneCreationError = 6009
Const cwbdbInvalidDataFormatForConnection = 6010
Const cwbdbDataFormatInUse = 6011
Const cwbdbInvalidDataFormatForData = 6012
Const cwbdbStringArgumentTooLong = 6013
Const cwbdbInvalidInternalArgument = 6014
Const cwbdbInvalidNumericArgument = 6015
Const cwbdbInvalidArgument = 6016
Const cwbdbStatementNotSelect = 6017
Const cwbdbStreamFetchNotComplete = 6018
Const cwbdbStreamFetchNotActive = 6019
Const cwbdbMissingDataProcessor = 6020
Const cwbdbIllegalCloneRequestType = 6021
Const cwbdbUnsolicitedData = 6022
Const cwbdbMissingData = 6023
Const cwbdbParameterInvalidBitstream = 6024
Const cwbdbConsistencyTokenError = 6025
Const cwbdbInvalidFunction = 6026
Const cwbdbFormatInvalidArgument = 6027
Const cwbdbInvalidColumnPosition = 6028
Const cwbdbInvalidColumnType = 6029
Const cwbdbRowVectorNotEmpty = 6030
Const cwbdbRowVectorEmpty = 6031
Const cwbdbMemoryAllocationFailure = 6032
Const cwbdbInvalidConversion = 6033
Const cwbdbDatastreamTooShort = 6034
Const cwbdbSQLWarning = 6035
Const cwbdbSQLError = 6036
Const cwbdbSQLParameterWarning = 6037
Const cwbdbSQLParameterError = 6038
Const cwbdbListServerWarning = 6039
Const cwbdbListServerError = 6040
Const cwbdbListParameterWarning = 6041
Const cwbdbListParameterError = 6042
Const cwbdbNDBFileServerWarning = 6043
Const cwbdbNDBFileServerError = 6044
Const cwbdbFileParameterWarning = 6045
Const cwbdbFileParameterError = 6046
Const cwbdbGeneralServerWarning = 6047
Const cwbdbGeneralServerError = 6048
Const cwbdbExitProgramWarning = 6049
Const cwbdbExitProgramError = 6050
Const cwbdbDataBufferTooSmall = 6051
Const cwbdbNLConversionError = 6052
Const cwbdbCommunicationsError = 6053
Const cwbdbInvalidArgumentAPI = 6054
Const cwbdbMissingDataHandler = 6055
Const cwbdbRequestDatastreamNotValid = 6056
Const cwbdbServerUnable = 6057
Const cwbdbWorkQueueStartError = 6058
Const cwbdbWorkQueueCreateError = 6059
Const cwbdbInitializationError = 6060
Const cwbdbServerAttributesError = 6061
Const cwbdbClientLevelError = 6062
Const cwbdbClientLangFeatureCodeError = 6063
Const cwbdbClientCCSIDError = 6064
Const cwbdbTranslationIndicatorError = 6065
Const cwbdbReturnServerAttributesError = 6066
Const cwbdbServerAttributesRequest = 6067
Const cwbdbReturnAttributesError = 6068
Const cwbdbServerAttributesMissing = 6069
Const cwbdbServerLangFeatureCodeConvError = 6070
Const cwbdbServerLevelConversionError = 6071
Const cwbdbServerLanguageTableError = 6072
Const cwbdbServerLanguageLibraryError = 6073
Const cwbdbServerLanguageIDError = 6074
Const cwbdbCommDequeueError = 6075
Const cwbdbCommEnqueueError = 6076
Const cwbdbUnsupportedColumnType = 6077
Const cwbdbServerInUse = 6078
Const cwbdbServerRelationalDBConvError = 6079
Const cwbdbLastStreamChunk = 6099
