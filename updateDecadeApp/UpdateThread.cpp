// UpdateThread.cpp: implementation of the UpdateThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UpdateThread.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define DUMMY_ORDER_NUMBER (-10000)
#define PRE_IDLE_MESSAGE_DISPLAY_ALLOWANCE 2000 // ms
#define MIN_DIAMETER_TO_INTERPRET_AS_MM	50.0

void LogError(HWND hWnd, char *szMessage);
void SetErrorIcon(HWND hWnd, int bErrorIcon, char *statusMessage);
void LogInfo(HWND hWnd, char *szMessage);

// globals
SQLHENV	g_env = NULL;    // initialized once, globally, to
// avoid a small handle leak by
// the driver!
extern HWND g_hWndDialog;
int g_nPointNumber;

// data structure for tracking "untouchable" orders (shipped or invoiced)
#	define ORDER_STATE_MODULUS	1000	// should be 1000 for production, small for testing.
// This is the size of the hash header for order state
// lookups.
#   define MAX_ACTIVE_ORDERS	100000	// should be 100000 for production, small for testing.
#   define ORDER_STATE_NULL_PTR (-1)

struct orderStateDescriptor {
	int ordernumber;
	int untouchable;
	int next;
} orderState[MAX_ACTIVE_ORDERS];	
int orderStates;
int orderStateHashHeader[ORDER_STATE_MODULUS];

void initializeOrderStateVector(void) {
	int i;
	for (i = 0; i < ORDER_STATE_MODULUS; i++) {
		orderStateHashHeader[i] = ORDER_STATE_NULL_PTR;
	}
	orderStates = 0;
} // initializeOrderStateVector

void setOrderState(int ordernumber, int untouchable) {
	int i, headerPosition;

	if (orderStates == MAX_ACTIVE_ORDERS) {
		LogError(g_hWndDialog, "Exceeded max active orders in setup of untouchable index");
		return;
	}
	orderState[orderStates].ordernumber = ordernumber;
	orderState[orderStates].untouchable = untouchable;
	headerPosition = ordernumber % ORDER_STATE_MODULUS;
	i = orderStateHashHeader[headerPosition];
	orderStateHashHeader[headerPosition] = orderStates;
	orderState[orderStates].next = i;
	++orderStates;

} // setOrderState

int getOrderState(int ordernumber) {
	int i, headerPosition, returnValue;

	headerPosition = ordernumber % ORDER_STATE_MODULUS;
	i = orderStateHashHeader[headerPosition];

	returnValue = 1; // by default (e.g. on overflow or "not found") don't touch order
	while (i != ORDER_STATE_NULL_PTR) {
		if (orderState[i].ordernumber == ordernumber) {
			returnValue = orderState[i].untouchable;
			break; // while
		}
		i = orderState[i].next;
	} // while

	return returnValue;

} // getOrderState


// NOT IN USE extern SharedData *pSharedData;

void LogError(HWND hWnd, char *szMessage);
void SetErrorIcon(HWND hWnd, int bErrorIcon, char *statusMessage);
void LogInfo(HWND hWnd, char *szMessage);

// --------FindDecadeCustomerCodeFromCMSCustomerNumber----------
char *FindDecadeCustomerCodeFromCMSCustomerNumber(SQLHSTMT stmt, char *cms) 
	// stmt is assumed to be open. Its cursor will be closed (if open)
	// and it will be used to fetch from d_customermapping in the
	// connected database.
{
	static char szCodeToReturn[8];
	char statementText[1024];
	SQLRETURN returnValue;
	SQLINTEGER sNameLenOrInd;

	sprintf(statementText, 
		"SELECT decadeCode FROM d_customermapping WHERE cmsNumber LIKE '%%%s%%'",
		cms);
	SQLFreeStmt(stmt, SQL_CLOSE);
	returnValue = SQLExecDirect(stmt, 
		(SQLTCHAR *) statementText, strlen(statementText));
	returnValue = SQLBindCol(stmt, 1, SQL_C_CHAR, 
		szCodeToReturn, 
		7,
		&sNameLenOrInd);
	returnValue = SQLFetch(stmt);
	if (returnValue != SQL_SUCCESS
		&& returnValue != SQL_SUCCESS_WITH_INFO) {
			szCodeToReturn[0] = '\0';
			return (char *) szCodeToReturn;
	}

	return (char *) szCodeToReturn;

} // FindDecadeCustomerCodeFromCMSCustomerNumber

// Mapping back to Decade die prefixes, from new part classes
#	define PLANTS 4
enum eDieType {eDTSolid = 0, eDTHollow = 1, eDTBacker = 2,
	eDTBolster = 3, eDTSubBolster = 4, eDTFeeder = 5, eDTHDMandrel = 6,
	eDTHDPlate = 7, eDTHDBacker = 8, eDTRing = 9,
	eDTUnknown = 10};
#	define DIE_TYPES 11

char *decadePrefix[PLANTS][DIE_TYPES] = {
	{ // Markham
		"DI","HO","BA","BO","SB","FE","MA","PL","BA","RI","MI"},
		{ // AluDie
			"DI","HO","BA","BO","SB","FE","MA","PL","BA","RI","MI"},
			{ // Michigan
				"DI","HO","BA","BO","SB","FE","MA","PL","BA","RI","MI"},
				{ // Colombia
					"DI","HO","BA","BO","SB","FE","MA","PL","BA","RI","MI"}};

					char *cmsPrefix[PLANTS][DIE_TYPES] = {
						{ // Markham
							"SD","HD","BAH","BOH","SBH","FDR","MA","PL","BAC","RI","MI"},
							{ // AluDie
								"SD","HD","BAH","BOH","SBH","FDR","MA","PL","BAC","RI","MI"},
								{ // Michigan
									"SD","HD","BAH","BOH","SBH","FDR","MA","PL","BAC","RI","MI"},
									{ // Colombia
										"SO","HU","BK","BOL","SBL","FD ","MA","PL","BAC","ANI","MI"}};

										// feature names
#	define FEATURE_NAMES			6
#	define FEATURE_CAVITIES			0
#	define FEATURE_NITRIDING		1
#   define FEATURE_EXTRA_CHARGE		2
#   define FEATURE_POCKET_CHARGE	3
#   define FEATURE_N2_GROOVES		4
#   define FEATURE_UNKNOWN			5

										char *featureCode[PLANTS][FEATURE_NAMES] = {
											{ // Markham
												"CAVITIES","NITRIDING","EXTRA CHRG","PKT CHRG","N2 GROOVES","UNKNOWN"},
												{ // AluDie
													"CAVITIES","NITRIDING","EXTRA CHRG","PKT CHRG","N2 GROOVES","UNKNOWN"},
													{ // Michigan
														"CAVITIES","NITRIDING","EXTRA CHRG","PKT CHRG","N2 GROOVES","UNKNOWN"},
														{ // Colombia
															"CAVIDADES","NITRURADO","CARGO EXT.","CAMARA","N2 GROOVES","UNKNOWN"}};  // N2 GROOVES NOT USED

															// Data structures for new order data coming in from
															// iSeries, to be sent to Decade DB.
#   define CUSTOMER_CODE_LENGTH 6
#   define CUSTOMER_TEXT_FIELD_LENGTH   50
#   define CUSTOMER_NOTE_LENGTH   151
#	define SHIPPING_VENDOR_LENGTH 32
#   define TRACKING_NUMBER_LENGTH 32
#   define CUSTOMER_POSTAL_CODE_LENGTH 20
#   define MAX_ORDERS	16384
#   define MAX_ORDER_ITEMS 32768
#   define MAX_ITEMS_PER_ORDER 256
#	define FULL_DESCRIPTION_LENGTH 350
															struct orderDescriptor {
																int ordernumber;
																char customercode[CUSTOMER_CODE_LENGTH+1];
																int employeenumber;
																TIMESTAMP_STRUCT orderdate;
																TIMESTAMP_STRUCT invoicedate;
																TIMESTAMP_STRUCT shopdate;
																TIMESTAMP_STRUCT expshipdate;
																TIMESTAMP_STRUCT expreceiveddate;
																TIMESTAMP_STRUCT shipdate;
																int onhold;
																char customerpo[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char note[FULL_DESCRIPTION_LENGTH];
																int defaultfreight;
																int salesInCents;
																int freightInCents;			// == sum(autoFreightInCents + manualFreightInCents) auto and manual treated differently re:GST
																int autoFreightInCents;		// == freight passed from Solarsoft as an order-level field
																int manualFreightInCents;	// == sum("FREIGHT CHARGE" lines) 
																int gstInCents;
																int parts;
																char baddress1[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char baddress2[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char baddress3[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char baddress4[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char bpostalcode[CUSTOMER_POSTAL_CODE_LENGTH+1];
																char saddress1[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char saddress2[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char saddress3[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char saddress4[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char spostalcode[CUSTOMER_POSTAL_CODE_LENGTH+1];
																int fasttrack;
																int packageDiscount;
																int priority;
																char shipvia[CUSTOMER_TEXT_FIELD_LENGTH+1];
																int defaultnitride;
																int nitrideInCents;
																int ncr;
																int combineprices;
																int shelf;
																int zeroprice;
																int defaultsteelsurcharge;
																int steelsurchargeInCents;
																int shelforder;
																int stock;
																int poscanned;
																char polink[CUSTOMER_TEXT_FIELD_LENGTH+1];
																int cor;
																int wr;
																int ncrs;
																double nitrideweight;
																int nitridechargeInCents;
																double roughweight;
																double freightweight;
																int freightchargeInCents; 
																int fasttrackchargeInCents;
																int packageDiscountInCents;
																int totalInCents;
																int subtotalInCents;
																int steelInCents;
																int shipvendorid;
																char shippingvendor[SHIPPING_VENDOR_LENGTH+1];
																char trackingnumber[TRACKING_NUMBER_LENGTH+1];
																double discountpercentage;
																int discountAmountInCents;
																TIMESTAMP_STRUCT lastchange;
																int hasnitridecomputedline;
																int maxItemNumberUsed;
																// Fields for recomputation of extra charges
																float freightrate;
																float steelrate;
																float nitriderate;
																int ftpremium;
																float surcharge;
																float minnitridecost;
																TIMESTAMP_STRUCT minnitrideeffectivedate;
																float maxnitridecost;
																// path to the items...
																int firstOrderItem;
																int orderItems;
																int firstExtraOrderItem;
																int extraOrderItems;
																// convenience fields
																int hasNitrideItem;
																int hasSkimCutItem;
																// CMS raw amounts, for recomputation of totals as needed
																float fCMSTaxAmount;
																float fCMSTotal;
																// CMS status field
																char cStatus;   // == 'N' (new) 'C' (complete) 
																// 'H' (hold, rare) 'A' (find out, rare)
																// additional CAM file fields
																char backerNumber[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char backerLocation[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char feederNumber[CUSTOMER_TEXT_FIELD_LENGTH+1];

															} order[MAX_ORDERS];
															int orders;

#   define MAX_OPTIONS_PER_ITEM 8
#	define SMALL_FIELD_LENGTH 10
															struct optionDescriptor {
																int featureType; // see feature names further up
																char szOptionCode[CUSTOMER_TEXT_FIELD_LENGTH+1];
																int quantity;
																float unitPrice;
																char szUnits[SMALL_FIELD_LENGTH+1];
																char szFut1Field[SMALL_FIELD_LENGTH+1];
															};

#   define PREFIX_LENGTH 2
															struct orderitemDescriptor {
																int ispart;
																int ordernumber;
																int orderIndex;
																int line;
																char prefix[PREFIX_LENGTH+1];
																char suffix[CUSTOMER_TEXT_FIELD_LENGTH+1];
																double qty;
																char description[FULL_DESCRIPTION_LENGTH];
																char location[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char dienumber[CUSTOMER_TEXT_FIELD_LENGTH+1];
																char note[FULL_DESCRIPTION_LENGTH];
																int priceInCents;
																int chargenitride;
																int nitridecostInCents;
																int steelcostInCents;
																int freightcostInCents;
																double roughweight;
																double finishedweight;
																int optionListNumber;
																struct optionDescriptor option[MAX_OPTIONS_PER_ITEM];
																int options;
																float fCustomerSteelRate;
																float fCustomerNitrideRate;
																float cmsSteel;
																float cmsFastTrack;
																float cmsPackageDiscount;
																// convenience fields
																int nCavities;
															} orderitem[MAX_ORDER_ITEMS];
															int orderitems;

															//
															// EscapeSingleQuotes(char *szString)
															//
															void EscapeSingleQuotes(char *szString)
															{
																char szCopy[65536], *from, *to;

																from = szString;
																to = szCopy;

																while (*from) {
																	if (*from == '\'') {
																		*to++ = '\'';
																		*to++ = '\'';
																	}
																	else {
																		*to++ = *from;
																	}
																	++from;
																}
																*to = '\0';
																strcpy(szString, szCopy);

															} // EscapeSingleQuotes

															//
															// Decade weight calculations
															//
															float FinishedWeight(float fDiameter, float fHeight) {
																float fWeight;
																BOOL bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);

																if (bMetric) {
																	fDiameter /=  (float) 25.4;
																	fHeight /= (float) 25.4;
																}

																fWeight = (float) (fDiameter * fDiameter * fHeight * 0.224);

																return fWeight;

															} // FinishedWeight

															float RoughWeight(int bHollow, float fDiameter, float fHeight) {
																float fWeight, fRoundedDiameter;
																int nWeightInHundredths;

																BOOL bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);

																if (bMetric) {
																	fDiameter /=  (float) 25.4;
																	fHeight /= (float) 25.4;
																}

																const double numericalErrorTolerance = 0.0001;

																if (fDiameter > 14.0 && fDiameter <= 14.5 + numericalErrorTolerance) {
																	fRoundedDiameter = 14.5;
																}
																else if (fDiameter > 15.0 && fDiameter <= 15.5 + numericalErrorTolerance) {
																	fRoundedDiameter = 15.5;
																}
																else {
																	fRoundedDiameter  = (float) ceil(fDiameter);
																}

																fDiameter = fRoundedDiameter;

																// In Decade:
																// if (pCustomer->GetNitrideMinEffectiveDate() <= orderDate) { }
																// I am assuming that most are switched over by now, so...
																// Use new (Jan 2008) weight calculation
																// DW: Also added a numerical error allowance
																if (bHollow) {
																	if (fDiameter <= 8.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 1.0) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 10.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 1.4) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 14.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 2.0) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 18.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 2.5) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 22.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 2.8) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else {
																		fWeight = (float) (0.224 * (fHeight + 3.1) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																}
																else /* solids and others */ {
																	if (fDiameter <= 10.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 0.12) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 14.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 0.15) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 18.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 0.18) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else if (fDiameter <= 22.0 + numericalErrorTolerance) {
																		fWeight = (float) (0.224 * (fHeight + 0.21) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																	else {
																		fWeight = (float) (0.224 * (fHeight + 0.24) * (fDiameter * 1.01) * (fDiameter * 1.01));
																	}
																}
																// from Decade: else /* use middle-aged weight calculation */ {}...

																// round to the nearest hundredth
																nWeightInHundredths = (int) (fWeight * 100.0 + 0.5);
																fWeight = (float) (((double) nWeightInHundredths) / 100.0);

																return fWeight;

															} // RoughWeight

															// -------------------------generateCAMFile----------------------

															//
															//Generate a log file used by the CAM people to autopopulate fields in their drawings.
															//
															//
															void GenerateCAMFile(int nOrderNumber,
																char *szCustomerCode,
																TIMESTAMP_STRUCT stShopDate,
																char *szItem1DieNumber, // set = "" if no items in order
																int nItemCount,
																int nCavities, // set = 0 if not applicable
																char *szLocation,
																int bNitride,
																int bSkimCut,
																char *szBackerNumber,
																char *szBackerLocation,
																char *szFeederNumber)
															{
																//CStdioFile c;
																FILE *fCAMFile;

																//CFileException e;
																//CString s;
																char s[1024], t[1024];
																int i;
																bool boolHasDash;
																char x[50];
																char szPathToWrite[1024];

																// insert Shop Order Number
																itoa(nOrderNumber,x,10);		

																// create or reopen a file with the name <shop order#>.txt
																strcpy(szPathToWrite, CAM_FILE_LOCATION);
																strcat(szPathToWrite, x);
																strcat(szPathToWrite, ".txt");

																if ((fCAMFile = fopen(szPathToWrite, "wt")) == NULL) {
																	return; // fail silently, a la Decade
																}        

																strcat(x,"\n");
																strcpy(s, x);

																fwrite(s, strlen(s), 1, fCAMFile);

																// insert Customer Code minus first character
																strcpy(s, szCustomerCode+1);
																strcat(s, "\n");
																fwrite(s, strlen(s), 1, fCAMFile);

																// insert delivery date
																switch (stShopDate.month) {
																case 1:
																	sprintf(s, "Jan %02d\n", stShopDate.day);
																	break;
																case 2:
																	sprintf(s, "Feb %02d\n", stShopDate.day);
																	break;
																case 3:
																	sprintf(s, "Mar %02d\n", stShopDate.day);
																	break;
																case 4:
																	sprintf(s, "Apr %02d\n", stShopDate.day);
																	break;
																case 5:
																	sprintf(s, "May %02d\n", stShopDate.day);
																	break;
																case 6:
																	sprintf(s, "Jun %02d\n", stShopDate.day);
																	break;
																case 7:
																	sprintf(s, "Jul %02d\n", stShopDate.day);
																	break;
																case 8:
																	sprintf(s, "Aug %02d\n", stShopDate.day);
																	break;
																case 9:
																	sprintf(s, "Sep %02d\n", stShopDate.day);
																	break;
																case 10:
																	sprintf(s, "Oct %02d\n", stShopDate.day);
																	break;
																case 11:
																	sprintf(s, "Nov %02d\n", stShopDate.day);
																	break;
																case 12:
																	sprintf(s, "Dec %02d\n", stShopDate.day);
																	break;
																} // switch

																fwrite(s, strlen(s), 1, fCAMFile);

																// insert die number
																strcpy(s, szItem1DieNumber);
																unsigned int k = 0, isBlank = 1;
																while (k < strlen(s)) {
																	if (!isspace(s[k])) {
																		isBlank = 0;
																		break; // while
																	}
																	++k;
																}

																boolHasDash = false;
																if (isBlank) {
																	strcpy(s, "-\n");
																	fwrite(s, strlen(s), 1, fCAMFile);
																	fwrite(s, strlen(s), 1, fCAMFile);  // and again
																}
																else if (!strcmp(s,"/")) {
																	strcpy(s,"-\n");
																	fwrite(s, strlen(s), 1, fCAMFile);
																	fwrite(s, strlen(s), 1, fCAMFile);  // and again
																}
																else {
																	char *pSlash;
																	pSlash = strstr(s, "/");
																	// was i = s.Find("/",0);
																	if (pSlash == NULL) {
																		strcat(s, "\n");
																		fwrite(s, strlen(s), 1, fCAMFile);
																		strcpy(s, "-\n");
																		fwrite(s, strlen(s), 1, fCAMFile);
																	}
																	//if (i == - 1) {
																	//c.Write(s+"\n",s.GetLength()+1); // die
																	//    s = "-\n";
																	//c.Write(s,s.GetLength()); // dash
																	//}
																	else {
																		i = pSlash - s;
																		if (s[strlen(s)-1] != '/') {
																			strncpy(t, s, i);
																			t[i] = '\n';
																			t[i+1] = '\0';
																			fwrite(t, strlen(t), 1, fCAMFile);
																			strcpy(t, pSlash+1);
																			fwrite(t, strlen(t), 1, fCAMFile);
																			fwrite("\n", 1, 1, fCAMFile);
																			//else if (s.Right(1) != "/") {
																			//c.Write(s.Left(i) +"\n", i+1); // die
																			//s = s.Mid(i + 1) + "\n";
																			//c.Write(s,s.GetLength()); // dash }
																		}
																		else {
																			strncpy(t, s, i);
																			t[i] = '\n';
																			t[i+1] = '\0';
																			fwrite(t, strlen(t), 1, fCAMFile);
																			strcpy(t, "-\n");
																			fwrite(t, strlen(t), 1, fCAMFile);
																			//c.Write(s.Left(s.GetLength()-1)+"\n",s.GetLength()); // die
																			//s = "-\n";
																			//c.Write(s,s.GetLength()); // dash
																		}
																	}
																} // outer else

																// insert number of cavities (last two digits of the code)
																if (nItemCount < 1 ) {
																	strcpy(s, "-\n");
																	// s = "-\n";
																	fwrite(s, strlen(s), 1, fCAMFile);
																	fwrite(s, strlen(s), 1, fCAMFile);
																	fwrite(s, strlen(s), 1, fCAMFile);
																	fwrite(s, strlen(s), 1, fCAMFile);
																	//c.Write(s,s.GetLength()); // cav
																	//c.Write(s,s.GetLength()); // loc
																	//c.Write(s,s.GetLength()); // nitride
																	//c.Write(s,s.GetLength()); // skim cut
																}
																else {
																	if (!nCavities) {
																		strcpy(s, "-\n");
																		fwrite(s, strlen(s), 1, fCAMFile);
																	}
																	else {
																		sprintf(s, "%d\n", nCavities);
																		fwrite(s, strlen(s), 1, fCAMFile);
																	}
																	// s = m_pOrder->GetItem(1)->GetCode().Right(2);
																	// if (s.GetLength() < 2) {
																	// s = "-";
																	// }
																	// else if ((s.GetAt(0) < '0' || s.GetAt(0) > '9') &&
																	//    (s.GetAt(1) < '0' || s.GetAt(1) > '9'))
																	// s = "-";
																	// else if (s == "00") {
																	// s = "-";
																	// }
																	// else if (s.GetAt(0) == '0') {
																	//    s = s.GetAt(1);
																	// }
																	// s = s + "\n";
																	// c.Write(s,s.GetLength());

																	// insert location
																	if (!strcmp(szLocation, "")) {
																		sprintf(s, "-\n");
																	}
																	else {
																		sprintf(s, "%s\n", szLocation);
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);
																	// s = m_pOrder->GetItem(1)->GetLocation();
																	// if (s.IsEmpty()) {
																	// s = "-";
																	// }
																	// s = s + "\n";
																	// c.Write(s,s.GetLength());			

																	// insert "nitride" if exists, or "-" if not
																	if (bNitride) {
																		strcpy(s, "nitride\n");
																	}
																	else {
																		strcpy(s, "-\n");
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);
																	// s = "-\n";
																	// for (i = 1 ; i < m_pOrder->GetItemCount()+1; i++) {
																	// s = m_pOrder->GetItem(i)->GetDescription();
																	// s.MakeLower();
																	// if (s.Find("nitride") != -1) {
																	// s = "nitride\n";
																	// i = m_pOrder->GetItemCount();
																	// }
																	// else {
																	// s = "-\n";
																	// }
																	// }
																	// c.Write(s,s.GetLength());

																	// insert "skim cut" if exists, or "-" if not
																	if (bSkimCut) {
																		strcpy(s, "skim cut\n");
																	}
																	else {
																		strcpy(s, "-\n");
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);
																	// s = "-\n";
																	// for (i = 1 ; i < m_pOrder->GetItemCount()+1; i++) {
																	// s = m_pOrder->GetItem(i)->GetDescription();
																	// s.MakeLower();
																	// if (s.Find("skim cut") != -1) {
																	// s = "skim cut\n";
																	// i = m_pOrder->GetItemCount();
																	// }
																	// else {
																	// s = "-\n";
																	// }
																	// }
																	// c.Write(s,s.GetLength());

																	// DW 20110322 addition from here to end of else:

																	// insert backer number, if it exists
																	if (!strcmp(szBackerNumber, "")) {
																		sprintf(s, "-\n");
																	}
																	else {
																		sprintf(s, "%s\n", szBackerNumber);
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);

																	// insert backer location, if it exists
																	if (!strcmp(szBackerLocation, "")) {
																		sprintf(s, "-\n");
																	}
																	else {
																		sprintf(s, "%s\n", szBackerLocation);
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);

																	// insert feeder number, if it exists
																	if (!strcmp(szFeederNumber, "")) {
																		sprintf(s, "-\n");
																	}
																	else {
																		sprintf(s, "%s\n", szFeederNumber);
																	}
																	fwrite(s, strlen(s), 1, fCAMFile);

																}
																fclose(fCAMFile);
																// c.Close();
																//#endif
															} // GenerateCAMFile

															// -------------------------checkForOrderDeletions---------------
#define MAX_OPEN_ORDERS 65536

															int decadeOpenOrder[MAX_OPEN_ORDERS];
															int decadeOpenOrders;

															int solarsoftOrder[MAX_OPEN_ORDERS];
															int solarsoftOrders;

															// (NOW IN-LINE)

															// --------------------end of checkForOrderDeletions-------------

															// --------------------------DoTheUpdate-------------------------
#define MAX_REQUESTED_ORDERS 4096

															void DoTheUpdate(void) {
																// Stats for GUI
																long lMinOrderNumberInUpdate,
																	lMaxOrderNumberInUpdate,
																	lOrderCountInUpdate,
																	lShipCountInUpdate;
																SYSTEMTIME tStartTimeOfUpdate,
																	tFinishTimeOfUpdate,
																	tLocalTime;
																TIME_ZONE_INFORMATION tz;

																// ODBC interface vars
																SQLHDBC dbc = NULL;
																SQLHSTMT stmt = NULL;
																SQLHDBC dbcCMS = NULL;
																SQLHSTMT stmtCMS = NULL;
																SQLHSTMT stmtCUST = NULL;
																SQLHSTMT stmtFOOD = NULL;
																SQLHSTMT stmtOCRS = NULL;
																SQLHSTMT stmtOENOTE = NULL;
																SQLHSTMT stmtOCRD = NULL;
																SQLHSTMT stmtOCRF = NULL;
																SQLHSTMT stmtUSRC = NULL;
																SQLHSTMT stmtBOLH = NULL;
#		ifdef ORDER_MIRROR
																SQLHSTMT stmtMirror = NULL;
																SQLHSTMT stmtOCRO = NULL;
#		endif
																SQLRETURN returnValue;
																SQLINTEGER sNameLenOrInd;
																SQLINTEGER sShippedIndicator, sInvoicedIndicator;
																char statementText[32768];
																char statementPart[2048];
																char errorMessage[2048];
																time_t now;
																struct tm *tmNow;
																int i, j;
																int bNoLastUpdateInDB = 0;
																char szFeatureCode[1024];
																char szOptionCode[1024];
																long int nQuantity;
																char szUnits[1024];
																char szFut1[1024];
																struct optionDescriptor *pOption;
																int extraChargeItems;
																long int nLine;
																SQLSMALLINT iRecord = 0;
																SQLTCHAR sqlState[1024];
																SQLINTEGER sqlError;
																SQLTCHAR sqlErrorMessage[1024];
																SQLSMALLINT sqlbErrorMessage;
																long nLineNumber;

																// OCRS fields
																char szDiscountCode[1024];
																char szDescription[1024];
																float fPercent;
																float fDiscountAmount;
																float fExtension;

																// OENOTE fields
																char szNoteLine[1024];

																float fFinishedWeight,
																	fCMSFinishedWeight,
																	fCMSOrderFinishedWeight,
																	fCMSOrderFreight,
																	fCMSOrderFreightTax;

																// update state
																char fromOrderNumber[1024],
																	toOrderNumber[1024],
																	fromTime[1024],
																	fromTimeDateOnly[1024],
																	orderCount[1024],
																	shipCount[1024],
																	toTime[1024];
																long nFromOrderNumber, nToOrderNumber;
																TIMESTAMP_STRUCT stFromTime, stToTime;
																int nPreviousOrderNumber = DUMMY_ORDER_NUMBER, 
																	nCurrentOrderNumber, nRequestedOrderNumber;

																// 20100706 DW: New data structure for explicit update requests
																int updateRequestOrderNumber[MAX_REQUESTED_ORDERS];
																int updateRequestOrderNumbers;

																long lShelfFlag;
																long lDiscountNumber;

																char szMessage[1024];
																char szLogMessage[1024];

																BOOL bMetric;

																static int solarsoftConnectionFailures = 0;
																int bRecordFound;

#	ifdef ORDER_MIRROR
																FILE *fOrderMirrorControl;
																int bOrderMirroring;
																unsigned long OCROlistNumber;
#   endif

																g_nPointNumber = 1;

																GetSystemTime(&tStartTimeOfUpdate);
																SetErrorIcon(g_hWndDialog, 0, "UPDATING");

																initializeOrderStateVector();

#	ifdef ORDER_MIRROR
																bOrderMirroring = FALSE;
																if ((fOrderMirrorControl = fopen(ORDER_MIRROR_CONTROL, "r")) != NULL) {
																	fscanf(fOrderMirrorControl, "%d", &bOrderMirroring);
																	fclose(fOrderMirrorControl);
																} 
#	endif

																g_nPointNumber = 10;
																// Zero the data structures
																ZeroMemory(order, sizeof(order));
																ZeroMemory(orderitem, sizeof(orderitem));
																orders = 0;
																orderitems = 0;
																char szDebug[1024];
																sprintf(szDebug, "sizeof(order) = %d\n", sizeof(order));
																OutputDebugString(szDebug);
																g_nPointNumber = 11;

																// Open a connection to decade DB
																// environment now initialized globally -- this was
																// a small handle leak.
																//returnValue = SQLAllocHandle(SQL_HANDLE_ENV, 
																//		                     SQL_NULL_HANDLE, 
																//							 &env);
																//if (returnValue != SQL_SUCCESS) {
																//	LogError(hWnd, "Cannot open handle to Decade");
																//	}
																//version = SQL_OV_ODBC3;
																//returnValue = SQLSetEnvAttr(env, 
																//							SQL_ATTR_ODBC_VERSION, 
																//							(void *) version, 
																//							0);
																returnValue = SQLAllocHandle(SQL_HANDLE_DBC, 
																	g_env, &dbc);
																// connection for Decade ODBC connection:
																returnValue = SQLConnect(dbc, 
																	(SQLTCHAR *) DECADE_DATABASE_NAME, 
																	strlen(DECADE_DATABASE_NAME), 
																	(SQLTCHAR *) "jamie", 
																	5, 
																	(SQLTCHAR *) "jamie", 
																	5);
																switch (returnValue) {
																case SQL_SUCCESS:
																	break;
																case SQL_SUCCESS_WITH_INFO:
																	iRecord = 1;
																	SQLGetDiagRec(SQL_HANDLE_DBC, dbc, iRecord, sqlState,
																		&sqlError, sqlErrorMessage, 1023, &sqlbErrorMessage);
																	break;
																case SQL_ERROR:
																	LogError(g_hWndDialog, "Error trying to connect to Decade");
																	break;
																case SQL_INVALID_HANDLE:
																	LogError(g_hWndDialog, "Invalid handle complaint on connect to Decade");
																	break;
																default:
																	LogError(g_hWndDialog, "Unknown error connecting to Decade");
																	break;
																} // switch
																// Initialize
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbc, &stmt);

																// 20100706 DW New: Check table d_updateRequest for any new requests for order updates,
																// which take priority over the usual updates.
																strcpy(statementText, 
																	"SELECT ordernumber FROM d_updaterequest WHERE updatetime IS NULL");
																SQLFreeStmt(stmt, SQL_CLOSE);
																returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
																	&nRequestedOrderNumber, 
																	sizeof(nRequestedOrderNumber),
																	&sNameLenOrInd);
																updateRequestOrderNumbers = 0;
																do {
																	returnValue = SQLFetch(stmt);
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			break; // do
																	}
																	updateRequestOrderNumber[updateRequestOrderNumbers++] = nRequestedOrderNumber;
																} while (1);


																g_nPointNumber = 12;
																if (updateRequestOrderNumbers) {
																	sprintf(szMessage, 
																		"Processing request for update of %d orders in d_updaterequest",
																		updateRequestOrderNumbers);
																	LogInfo(g_hWndDialog, szMessage);
																	stFromTime.year = 2000;
																	stFromTime.month = 1;
																	stFromTime.day = 1;
																	stFromTime.hour = 0;
																	stFromTime.minute = 0;
																	stFromTime.second = 0;
																	stFromTime.fraction = 0;
																	time(&now);
																	tmNow = localtime(&now);
																	stToTime.year = tmNow->tm_year + 1900;
																	stToTime.month = tmNow->tm_mon + 1;
																	stToTime.day = tmNow->tm_mday;
																	stToTime.hour = tmNow->tm_hour;
																	stToTime.minute = tmNow->tm_min;
																	stToTime.second = tmNow->tm_sec;
																	sprintf(fromTimeDateOnly, "%d-%02d-%02d",
																		stFromTime.year, stFromTime.month,
																		stFromTime.day);
																}
																else {
																	// Look up latest order number and update time in Decade
																	// and display these in the (often hidden) dialog.
																	strcpy(statementText, 
																		"SELECT lastordernumber, lastupdate FROM d_updatetime");
																	//SQLCloseCursor(stmt);
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
																		&nFromOrderNumber, 
																		sizeof(nFromOrderNumber),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 2, 
																		SQL_C_TYPE_TIMESTAMP, 
																		&stFromTime, 
																		sizeof(stFromTime),
																		&sNameLenOrInd);
																	returnValue = SQLFetch(stmt);
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			LogError(g_hWndDialog, 
																				"Unable to Fetch info on last update");
																			strcpy(fromTime, "2012-01-01 00:00:00");
																			stFromTime.year = 2012;
																			stFromTime.month = 1;
																			stFromTime.day = 1;
																			stFromTime.hour = 0;
																			stFromTime.minute = 0;
																			stFromTime.second = 0;
																			strcpy(fromOrderNumber, "Unknown");
																			bNoLastUpdateInDB = 1;
																	}
																	else {
																		sprintf(fromTime, 
																			"%d-%02d-%02d %02d:%02d:%02d",
																			stFromTime.year, stFromTime.month,
																			stFromTime.day, stFromTime.hour,
																			stFromTime.minute, stFromTime.second);
																		sprintf(fromOrderNumber, "%ld", nFromOrderNumber);
																	}

																	//SQLCloseCursor(stmt);
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	// Fetch updates in CMS db from previous time to now
																	time(&now);
																	tmNow = localtime(&now);
																	stToTime.year = tmNow->tm_year + 1900;
																	stToTime.month = tmNow->tm_mon + 1;
																	stToTime.day = tmNow->tm_mday;
																	stToTime.hour = tmNow->tm_hour;
																	stToTime.minute = tmNow->tm_min;
																	stToTime.second = tmNow->tm_sec;
																	sprintf(fromTimeDateOnly, "%d-%02d-%02d",
																		stFromTime.year, stFromTime.month,
																		stFromTime.day);
																	// Sleep for a second, to avoid race conditions
																	// with concurrent CMS updates getting missed
																	Sleep(1001);
																} // if (!updateRequestOrderNumbers)

																g_nPointNumber = 13;

																// Connect to the CMS DB
																returnValue = SQLAllocHandle(SQL_HANDLE_DBC, 
																	g_env, &dbcCMS);
																// connection for CMS ODBC connection:
																returnValue = SQLConnect(dbcCMS, 
																	(SQLTCHAR *) "cms1", 
																	4, 
																	(SQLTCHAR *) CMS_USER, 
																	3, 
																	(SQLTCHAR *) CMS_PASSWORD, 
																	3);
																switch (returnValue) {
																case SQL_SUCCESS:
																	solarsoftConnectionFailures = 0;
																	break;
																case SQL_SUCCESS_WITH_INFO:
																	solarsoftConnectionFailures = 0;
																	iRecord = 1;
																	SQLGetDiagRec(SQL_HANDLE_DBC, dbcCMS, iRecord, sqlState,
																		&sqlError, sqlErrorMessage, 1023, &sqlbErrorMessage);
																	break;
																case SQL_ERROR:
																	iRecord = 1;
																	SQLGetDiagRec(SQL_HANDLE_DBC, dbcCMS, iRecord, sqlState,
																		&sqlError, sqlErrorMessage, 1023, &sqlbErrorMessage);
																	if (solarsoftConnectionFailures == 1) { // i.e. previous try failed, too
																		LogError(g_hWndDialog, "Error trying to connect to Solarsoft");
																	}
																	else {
																		LogInfo(g_hWndDialog, "Error trying to connect to Solarsoft");
																	}
																	++solarsoftConnectionFailures;
																	break;
																case SQL_INVALID_HANDLE:
																	LogError(g_hWndDialog, "Invalid handle complaint on connect to Solarsoft");
																	break;
																default:
																	LogError(g_hWndDialog, "Unknown error connecting to Solarsoft");
																	break;
																} // switch
																// Initialize
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtCMS);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtCUST);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtOCRS);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtOENOTE);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtOCRD);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtOCRF);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtUSRC);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT, 
																	dbcCMS, &stmtFOOD);
																returnValue = SQLAllocHandle(SQL_HANDLE_STMT,
																	dbcCMS, &stmtBOLH);
#					ifdef ORDER_MIRROR
																if (bOrderMirroring) {
																	returnValue = SQLAllocHandle(SQL_HANDLE_STMT,
																		dbcCMS, &stmtMirror);
																	returnValue = SQLAllocHandle(SQL_HANDLE_STMT,
																		dbcCMS, &stmtOCRO);
																}
#					endif

																// Query table OCRH for orders
#					define MAX_FIELD_LENGTH 256
																int nOrderNumber;
																TIMESTAMP_STRUCT stOrderDate, stPromiseDate, stUpdateDate, stDecadeShipDate,
																	stShipDate, stExpectedShipDate, stShopDate, stExpectedReceivedDate,
																	stDecadeInvoiceDate, stFirstSeen;
																char szBillCustomerNumber[MAX_FIELD_LENGTH],
																	szShipVia[MAX_FIELD_LENGTH],
																	szShipCustomerNumber[MAX_FIELD_LENGTH],
																	szShipCustomerName[MAX_FIELD_LENGTH],
																	szShipAddress1[MAX_FIELD_LENGTH],
																	szShipAddress2[MAX_FIELD_LENGTH],
																	szBillCustomerName[MAX_FIELD_LENGTH],
																	szBillAddress1[MAX_FIELD_LENGTH],
																	szBillPhone[MAX_FIELD_LENGTH],
																	szShipPostalCode[MAX_FIELD_LENGTH],
																	szPO[MAX_FIELD_LENGTH],
																	szStatus[MAX_FIELD_LENGTH],
																	szCarrier[MAX_FIELD_LENGTH],
																	szFastTrackLine[MAX_FIELD_LENGTH + 1],
																	szService[MAX_FIELD_LENGTH], *pStatus;
																float fTotal, fDiscount, fTax;
																g_nPointNumber = 14;

																if (!updateRequestOrderNumbers) {
																	sprintf(statementText, 
																		"SELECT DCORD#,DCODAT,DCBCUS,DCSHVI,DCSCUS,DCPO,DCMDAT,DCSTAT,DCTOTO,DCTDIS,DCTTAX,DCTFRT,DCTWGT,DCUDAT,DCCARC,DCSERC,DCSDAT,DCSNAM,DCSAD1,DCSAD2,DCSPOS,DCBNAM,DCBAD1,DCBPHO,DCCDAT FROM %s.OCRH ",
																		//        1		  2		3		4		5	 6		7	  8		9		10	  11	 12		13		14	  15	 16		17		18	   19	 20	    21     22     23     24     25 
																		CMS_DATABASE_NAME);
																	sprintf(statementPart,
																		"WHERE (DCORD# > '%s' OR DCODAT >= '%s' OR DCUDAT >= '%s') AND DCPLNT = '%s' ORDER BY DCORD#",
																		fromOrderNumber, fromTimeDateOnly, 
																		fromTimeDateOnly, PLANT_CODE);
																	strcat(statementText, statementPart);

																	g_nPointNumber = 2;

																	//OutputDebugString(statementText);
																	//SQLCloseCursor(stmtCMS);
																	SQLFreeStmt(stmtCMS, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtCMS, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtCMS, 1, SQL_C_ULONG, 
																		&nOrderNumber, 
																		sizeof(nOrderNumber),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 2, SQL_C_TYPE_TIMESTAMP, 
																		&stOrderDate, 
																		sizeof(stOrderDate),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 3, SQL_C_CHAR, 
																		szBillCustomerNumber, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 4, SQL_C_CHAR, 
																		szShipVia, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 5, SQL_C_CHAR, 
																		szShipCustomerNumber, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 6, SQL_C_CHAR, 
																		szPO, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 7, SQL_C_TIMESTAMP, 
																		&stExpectedShipDate, 
																		sizeof(stExpectedShipDate),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 8, SQL_C_CHAR, 
																		szStatus, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 9, SQL_C_FLOAT, 
																		&fTotal, 
																		sizeof(fTotal),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 10, SQL_C_FLOAT, 
																		&fDiscount, 
																		sizeof(fDiscount),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 11, SQL_C_FLOAT, 
																		&fTax, 
																		sizeof(fTax),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 12, SQL_C_FLOAT, 
																		&fCMSOrderFreight, 
																		sizeof(fCMSOrderFreight),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 13, SQL_C_FLOAT, 
																		&fCMSOrderFinishedWeight, 
																		sizeof(fCMSOrderFinishedWeight),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 14, SQL_C_TIMESTAMP, 
																		&stUpdateDate, 
																		sizeof(stUpdateDate),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 15, SQL_C_CHAR, 
																		szCarrier, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 16, SQL_C_CHAR, 
																		szService, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 17, SQL_C_TIMESTAMP, 
																		&stShipDate, 
																		sizeof(stShipDate),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 18, SQL_C_CHAR, 
																		szShipCustomerName, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 19, SQL_C_CHAR, 
																		szShipAddress1, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 20, SQL_C_CHAR, 
																		szShipAddress2, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 21, SQL_C_CHAR, 
																		szShipPostalCode, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 22, SQL_C_CHAR, 
																		szBillCustomerName, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 23, SQL_C_CHAR, 
																		szBillAddress1, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 24, SQL_C_CHAR, 
																		szBillPhone, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 25, SQL_C_TIMESTAMP, 
																		&stPromiseDate, 
																		sizeof(stPromiseDate),
																		&sNameLenOrInd);
																} // if (!updateRequestOrderNumbers)

																orders = 0;
																lMinOrderNumberInUpdate = 100000000;
																lMaxOrderNumberInUpdate = 0;
																nToOrderNumber = nFromOrderNumber;
																do {
																	if (updateRequestOrderNumbers) {
																		if (orders == updateRequestOrderNumbers) {
																			break; // do, on orders to fetch
																		}
																		// fetch updateRequestOrderNumber[orders] into the
																		// same vars as the usual update	    
																		sprintf(statementText, 
																			"SELECT DCORD#,DCODAT,DCBCUS,DCSHVI,DCSCUS,DCPO,DCMDAT,DCSTAT,DCTOTO,DCTDIS,DCTTAX,DCTFRT,DCTWGT,DCUDAT,DCCARC,DCSERC,DCSDAT,DCSNAM,DCSAD1,DCSAD2,DCSPOS,DCBNAM,DCBAD1,DCBPHO,DCCDAT FROM %s.OCRH ",
																			//        1		  2		3		4		5	 6		7	  8		9		10	  11	 12		13		14	  15	 16		17		18	   19	 20	    21     22     23     24     25 
																			CMS_DATABASE_NAME);
																		sprintf(statementPart,
																			"WHERE DCORD# = '%d'",
																			updateRequestOrderNumber[orders]);
																		strcat(statementText, statementPart);
																		SQLFreeStmt(stmtCMS, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtCMS, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtCMS, 1, SQL_C_ULONG, 
																			&nOrderNumber, 
																			sizeof(nOrderNumber),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 2, SQL_C_TYPE_TIMESTAMP, 
																			&stOrderDate, 
																			sizeof(stOrderDate),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 3, SQL_C_CHAR, 
																			szBillCustomerNumber, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 4, SQL_C_CHAR, 
																			szShipVia, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 5, SQL_C_CHAR, 
																			szShipCustomerNumber, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 6, SQL_C_CHAR, 
																			szPO, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 7, SQL_C_TIMESTAMP, 
																			&stExpectedShipDate, 
																			sizeof(stExpectedShipDate),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 8, SQL_C_CHAR, 
																			szStatus, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 9, SQL_C_FLOAT, 
																			&fTotal, 
																			sizeof(fTotal),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 10, SQL_C_FLOAT, 
																			&fDiscount, 
																			sizeof(fDiscount),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 11, SQL_C_FLOAT, 
																			&fTax, 
																			sizeof(fTax),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 12, SQL_C_FLOAT, 
																			&fCMSOrderFreight, 
																			sizeof(fCMSOrderFreight),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 13, SQL_C_FLOAT, 
																			&fCMSOrderFinishedWeight, 
																			sizeof(fCMSOrderFinishedWeight),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 14, SQL_C_TIMESTAMP, 
																			&stUpdateDate, 
																			sizeof(stUpdateDate),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 15, SQL_C_CHAR, 
																			szCarrier, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 16, SQL_C_CHAR, 
																			szService, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 17, SQL_C_TIMESTAMP, 
																			&stShipDate, 
																			sizeof(stShipDate),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 18, SQL_C_CHAR, 
																			szShipCustomerName, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 19, SQL_C_CHAR, 
																			szShipAddress1, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 20, SQL_C_CHAR, 
																			szShipAddress2, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 21, SQL_C_CHAR, 
																			szShipPostalCode, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 22, SQL_C_CHAR, 
																			szBillCustomerName, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 23, SQL_C_CHAR, 
																			szBillAddress1, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 24, SQL_C_CHAR, 
																			szBillPhone, 
																			MAX_FIELD_LENGTH,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCMS, 25, SQL_C_TIMESTAMP, 
																			&stPromiseDate, 
																			sizeof(stPromiseDate),
																			&sNameLenOrInd);
																	} // if (updateRequestOrderNumbers)

																	returnValue = SQLFetch(stmtCMS);
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			if (updateRequestOrderNumbers) {
																				sprintf(szMessage, "Could not fetch OCRH record for request number %d == ordernumber %d",
																					orders, updateRequestOrderNumber[orders]);
																				LogInfo(g_hWndDialog, szMessage);
																			}
																			break;
																	}

#					ifdef ORDER_MIRROR
																	if (bOrderMirroring) {
																		sprintf(statementText,
																			"SELECT DCORD# FROM %s.OCRH WHERE DCORD# = %ld",
																			ORDER_MIRROR, nOrderNumber); 						
																		SQLFreeStmt(stmtMirror, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																		bRecordFound = FALSE;
																		if (returnValue == SQL_SUCCESS
																			|| returnValue == SQL_SUCCESS_WITH_INFO) {
																				returnValue = SQLFetch(stmtMirror);
																				if (returnValue == SQL_SUCCESS 
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						bRecordFound = TRUE;
																				}
																		}
																		if (bRecordFound) {
																			// do an update
																			sprintf(statementText, 
																				"UPDATE %s.OCRH SET ROW = (SELECT * FROM %s.OCRH WHERE %s.OCRH.DCORD# = %ld) WHERE %s.OCRH.DCORD# = %ld",
																				ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, nOrderNumber,
																				ORDER_MIRROR, nOrderNumber);
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					sprintf(errorMessage, 
																						"Unable to update %s.OCRH order number %ld",
																						ORDER_MIRROR, nOrderNumber);
																					LogError(g_hWndDialog, errorMessage);
																					sprintf(errorMessage,
																						"Statement was |%s|", statementText);
																					LogError(g_hWndDialog, errorMessage);
																			}
																		}
																		else {
																			// do an insert
																			sprintf(statementText,
																				"INSERT INTO %s.OCRH (SELECT * FROM %s.OCRH WHERE %s.OCRH.DCORD# = %ld)",
																				ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, nOrderNumber);
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					sprintf(errorMessage, 
																						"Unable to insert into %s.OCRH order number %ld",
																						ORDER_MIRROR, nOrderNumber);
																					LogError(g_hWndDialog, errorMessage);
																					sprintf(errorMessage,
																						"Statement was |%s|", statementText);
																					LogError(g_hWndDialog, errorMessage);
																					sprintf(errorMessage,
																						"Statement was |%s|", statementText);
																					LogError(g_hWndDialog, errorMessage);
																			}							
																		}
																	}
#					endif
																	if (nOrderNumber < lMinOrderNumberInUpdate) {
																		lMinOrderNumberInUpdate = nOrderNumber;
																	}
																	if (nOrderNumber > lMaxOrderNumberInUpdate) {
																		lMaxOrderNumberInUpdate = nOrderNumber;
																	}
																	order[orders].ordernumber = nOrderNumber;
																	order[orders].firstOrderItem = -1;
																	order[orders].orderItems = 0;
																	order[orders].firstExtraOrderItem = -1;
																	order[orders].extraOrderItems = 0;
																	order[orders].hasNitrideItem = 0;
																	order[orders].hasSkimCutItem = 0;
																	order[orders].shelf = 0;
																	order[orders].shelforder = 0;
																	order[orders].ncr = 0;
																	order[orders].ncrs = 0;
																	order[orders].freightInCents = 0;
																	order[orders].autoFreightInCents = 0;
																	order[orders].manualFreightInCents = 0;
																	order[orders].backerNumber[0] = '\0';
																	order[orders].backerLocation[0] = '\0';
																	order[orders].feederNumber[0] = '\0';
#					ifdef SHIPVIA_FROM_SHIPVIA
																	strcpy(order[orders].shipvia, szShipVia);
#					else
																	strcpy(order[orders].shipvia, szCarrier);
#					endif
																	order[orders].note[0] = '\0';
																	order[orders].employeenumber = 0;
																	if (nOrderNumber > nToOrderNumber) {
																		nToOrderNumber = nOrderNumber;
																		// robust to changes in ORDER BY
																	}
																	if (stOrderDate.year < 2000) {
																		stOrderDate.year = 2000;
																	}
																	if (stOrderDate.month < 1) {
																		stOrderDate.month = 1;
																	}
																	if (stOrderDate.day < 1) {
																		stOrderDate.day = 1;
																	}
																	// set order[orders].orderdate to be the earliest date and time
																	// at which nOrderNumber was seen, according to
																	// table d_ordertime. Handle various exceptions
																	// gracefully...
																	sprintf(statementText,
																		"SELECT firstseen FROM d_ordertime WHERE ordernumber = %ld",
																		nOrderNumber);
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																	bRecordFound = FALSE;
																	if (returnValue == SQL_SUCCESS
																		|| returnValue == SQL_SUCCESS_WITH_INFO) {
																			returnValue = SQLBindCol(stmt, 1, SQL_C_TIMESTAMP, 
																				&stFirstSeen, 
																				sizeof(stFirstSeen),
																				&sNameLenOrInd);
																			returnValue = SQLFetch(stmt);
																			if (returnValue == SQL_SUCCESS 
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					bRecordFound = TRUE;
																			}
																	}
																	if (!bRecordFound) { 
																		// set a new first seen record
																		time(&now);
																		tmNow = localtime(&now);
																		stFirstSeen.year = tmNow->tm_year + 1900;
																		stFirstSeen.month = tmNow->tm_mon + 1;
																		stFirstSeen.day = tmNow->tm_mday;
																		stFirstSeen.hour = tmNow->tm_hour;
																		stFirstSeen.minute = tmNow->tm_min;
																		stFirstSeen.second = tmNow->tm_sec;
																		sprintf(statementText, 
																			"INSERT INTO d_ordertime (ordernumber, firstseen) "
																			"VALUES (%ld, '%d-%02d-%02d %02d:%02d:%02d')",
																			nOrderNumber,
																			stFirstSeen.year, stFirstSeen.month,
																			stFirstSeen.day, stFirstSeen.hour,
																			stFirstSeen.minute, stFirstSeen.second);
																		SQLFreeStmt(stmt, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				sprintf(errorMessage,
																					"Error storing firstseen record for so %ld, stmt '%s'", 
																					nOrderNumber, statementText);
																				LogError(g_hWndDialog, errorMessage);
																		}
																	} // if (!bRecordFound)
																	if (stOrderDate.year != stFirstSeen.year
																		|| stOrderDate.month != stFirstSeen.month
																		|| stOrderDate.day != stFirstSeen.day) {
																			order[orders].orderdate = stOrderDate;
																	}
																	else {
																		order[orders].orderdate = stFirstSeen;
																	}
																	strcpy(order[orders].customercode, 
																		FindDecadeCustomerCodeFromCMSCustomerNumber(stmt, szBillCustomerNumber));
																	if (strlen(order[orders].customercode) < 6) {
																		strcpy(order[orders].customercode,
																			FindDecadeCustomerCodeFromCMSCustomerNumber(stmt, szShipCustomerNumber));
																	}
																	if (strlen(order[orders].customercode) < 6) {
																		strcpy(order[orders].customercode, "XXXXXX");
																		sprintf(errorMessage, 
																			"No decade customer code found for CMS code '%s'",
																			szBillCustomerNumber);
																		LogError(g_hWndDialog, errorMessage);
																	}
																	if ((strstr(szStatus, "H") == NULL)
																		&& (strstr(szStatus, "h") == NULL)) {
																			order[orders].onhold = 0;
																	}
																	else {
																		order[orders].onhold = 1;
																	}
																	pStatus = szStatus;
																	do {
																		if (!*pStatus) {
																			break;
																		}
																		if (*pStatus >= 'A' && *pStatus <= 'Z') {
																			break;
																		}
																		++pStatus;
																	} while (1);
																	order[orders].cStatus = *pStatus;
																	// Query CMS for the CUST address fields,
																	// since they are not populating the
																	// OCRH ones!
																	char szADR1[64],
																		szADR2[64],
																		szADR3[64],
																		szADR4[64],
																		szPOST[64];
																	sprintf(statementText, 
																		"SELECT BVADR1,BVADR2,BVADR3,BVADR4,BVPOST FROM %s.CUST WHERE BVCUST='%s'",
																		CMS_DATABASE_NAME, szBillCustomerNumber);
																	//SQLCloseCursor(stmtCUST);
																	SQLFreeStmt(stmtCUST, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtCUST, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtCUST, 1, SQL_C_CHAR, 
																		szADR1, 
																		sizeof(szADR1),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCUST, 2, SQL_C_CHAR, 
																		szADR2, 
																		sizeof(szADR2),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCUST, 3, SQL_C_CHAR, 
																		szADR3, 
																		sizeof(szADR3),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCUST, 4, SQL_C_CHAR, 
																		szADR4, 
																		sizeof(szADR4),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCUST, 5, SQL_C_CHAR, 
																		szPOST, 
																		sizeof(szPOST),
																		&sNameLenOrInd);
																	returnValue = SQLFetch(stmtCUST);
																	if (returnValue == SQL_SUCCESS
																		|| returnValue == SQL_SUCCESS_WITH_INFO) {
																			strcpy(order[orders].baddress1, szADR1);
																			strcpy(order[orders].baddress2, szADR2);
																			strcpy(order[orders].baddress3, szADR3);
																			strcpy(order[orders].baddress4, szADR4);
																			strcpy(order[orders].bpostalcode, szPOST);
																	}
																	else {
																		order[orders].baddress1[0] = '\0';
																		order[orders].baddress2[0] = '\0';
																		order[orders].baddress3[0] = '\0';
																		order[orders].baddress4[0] = '\0';
																		order[orders].bpostalcode[0] = '\0';
																	}
																	if (strlen(szShipCustomerNumber) < 4) {
																		// use bill address both places...
																		strcpy(order[orders].saddress1, order[orders].baddress1);
																		strcpy(order[orders].saddress2, order[orders].baddress2);
																		strcpy(order[orders].saddress3, order[orders].baddress3);
																		strcpy(order[orders].saddress4, order[orders].baddress4);
																		strcpy(order[orders].spostalcode, order[orders].bpostalcode);
																	}
																	else {
																		sprintf(statementText, 
																			"SELECT BVADR1,BVADR2,BVADR3,BVADR4,BVPOST FROM %s.CUST WHERE BVCUST='%s'",
																			CMS_DATABASE_NAME, szShipCustomerNumber);
																		//SQLCloseCursor(stmtCUST);
																		SQLFreeStmt(stmtCUST, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtCUST, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtCUST, 1, SQL_C_CHAR, 
																			szADR1, 
																			sizeof(szADR1),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCUST, 2, SQL_C_CHAR, 
																			szADR2, 
																			sizeof(szADR2),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCUST, 3, SQL_C_CHAR, 
																			szADR3, 
																			sizeof(szADR3),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCUST, 4, SQL_C_CHAR, 
																			szADR4, 
																			sizeof(szADR4),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtCUST, 5, SQL_C_CHAR, 
																			szPOST, 
																			sizeof(szPOST),
																			&sNameLenOrInd);
																		returnValue = SQLFetch(stmtCUST);
																		if (returnValue == SQL_SUCCESS
																			|| returnValue == SQL_SUCCESS_WITH_INFO) {
																				strcpy(order[orders].saddress1, szADR1);
																				strcpy(order[orders].saddress2, szADR2);
																				strcpy(order[orders].saddress3, szADR3);
																				strcpy(order[orders].saddress4, szADR4);
																				strcpy(order[orders].spostalcode, szPOST);
																		}
																		else /* retreat to bill address */ {
																			strcpy(order[orders].saddress1, order[orders].baddress1);
																			strcpy(order[orders].saddress2, order[orders].baddress2);
																			strcpy(order[orders].saddress3, order[orders].baddress3);
																			strcpy(order[orders].saddress4, order[orders].baddress4);
																			strcpy(order[orders].spostalcode, order[orders].bpostalcode);
																		}
																	}
																	// Query CMS for any whole-order notes from
																	// table OENOTE
																	sprintf(statementText,
																		"SELECT GGTEXT, GGLIN# FROM %s.OENOTE WHERE GGKEY='%09d' AND GGPAG#=1 AND GGLIN#>0 ORDER BY GGLIN#",
																		CMS_DATABASE_NAME, order[orders].ordernumber);
																	//SQLCloseCursor(stmtOENOTE);
																	SQLFreeStmt(stmtOENOTE, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtOENOTE, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtOENOTE, 1, SQL_C_CHAR, 
																		szNoteLine, 
																		sizeof(szNoteLine),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtOENOTE, 2, SQL_C_ULONG,
																		&nLineNumber,
																		sizeof(nLineNumber),
																		&sNameLenOrInd);
																	order[orders].note[0] = '\0';
																	do {
																		returnValue = SQLFetch(stmtOENOTE);
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				break; // do
																		}
#							ifdef ORDER_MIRROR
																		if (bOrderMirroring) {
																			sprintf(statementText,
																				"SELECT GGKEY FROM %s.OENOTE WHERE GGKEY='%09d' AND GGPAG# = 1 AND GGLIN# = %ld",
																				ORDER_MIRROR, order[orders].ordernumber, nLineNumber); 						
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			bRecordFound = FALSE;
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					returnValue = SQLFetch(stmtMirror);
																					if (returnValue == SQL_SUCCESS 
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							bRecordFound = TRUE;
																					}
																			}
																			if (bRecordFound) {
																				// do an update
																				sprintf(statementText, 
																					"UPDATE %s.OENOTE SET ROW = (SELECT * FROM %s.OENOTE WHERE %s.OENOTE.GGKEY = '%09d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld) WHERE %s.OENOTE.GGKEY = '%09d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[orders].ordernumber, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																					nLineNumber, ORDER_MIRROR, order[orders].ordernumber,
																					ORDER_MIRROR, ORDER_MIRROR, nLineNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to update %s.OENOTE order number %ld, line %ld",
																							ORDER_MIRROR, order[orders].ordernumber, nLineNumber);
																						LogError(g_hWndDialog, errorMessage);
																				}
																			}
																			else {
																				// do an insert
																				sprintf(statementText,
																					"INSERT INTO %s.OENOTE (SELECT * FROM %s.OENOTE WHERE %s.OENOTE.GGKEY = '%09d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld)",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																					order[orders].ordernumber, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																					nLineNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to insert into %s.OENOTE order number %ld, line %ld",
																							ORDER_MIRROR, order[orders].ordernumber, nLineNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}							
																			}
																		}
#							endif

																		// trim extra whitespace from szNoteLine
																		char *pChar, szTrimmed[1024];
																		int newLength;
																		pChar = szNoteLine;
																		while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																			++pChar;
																		}
																		strcpy(szTrimmed, pChar);
																		pChar = szTrimmed + strlen(szTrimmed) - 1;
																		while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																			--pChar;
																		}
																		newLength = (pChar - szTrimmed + 1);
																		strncpy(szNoteLine, szTrimmed, newLength);
																		szNoteLine[newLength] = '\0';
																		if (strlen(order[orders].note) + strlen(szNoteLine) + 1 < FULL_DESCRIPTION_LENGTH) {
																			if (order[orders].note) {
																				strcat(order[orders].note, " ");
																			}
																			strcat(order[orders].note, szNoteLine);
																		}
																	} while (1);		

																	order[orders].fasttrack = 0;
																	order[orders].fasttrackchargeInCents = 0;
																	order[orders].packageDiscount = 0;
																	order[orders].packageDiscountInCents = 0;
																	// new fetch of user-defined fasttrack field

																	// Fetch fasttrack field (a user-defined field) for the current order
																	if (order[orders].ordernumber == 210002
																		|| order[orders].ordernumber ==  210005
																		|| order[orders].ordernumber == 24) {
																			int lkjklkj = 342334; // breakpoint hanger
																	}
																	sprintf(statementText, 
																		"SELECT MFRESP FROM %s.USRC WHERE MFSRCE = 'ORD' AND MFKEY1 = 'ORDER HEADER' AND MFKEY2 = '%09d           '",
																		CMS_DATABASE_NAME, 
																		order[orders].ordernumber);
																	//SQLCloseCursor(stmtUSRC);
																	SQLFreeStmt(stmtUSRC, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtUSRC, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtUSRC, 1, SQL_C_CHAR, 
																		szFastTrackLine, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLFetch(stmtUSRC);
																	if (returnValue == SQL_SUCCESS
																		|| returnValue == SQL_SUCCESS_WITH_INFO) {
																			if (strstr(szFastTrackLine, "N") == NULL
																				&& strstr(szFastTrackLine, "n") == NULL) {
																					order[orders].fasttrack = 1;
																			}
																			else {
																				order[orders].fasttrack = 0;
																			}

#							ifdef ORDER_MIRROR
																			if (bOrderMirroring) {
																				sprintf(statementText,
																					"SELECT MFKEY2 FROM %s.USRC WHERE MFSRCE='ORD' AND MFKEY1='ORDER HEADER' AND MFKEY2='%09d           '",
																					ORDER_MIRROR, order[orders].ordernumber); 						
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				bRecordFound = FALSE;
																				if (returnValue == SQL_SUCCESS
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						returnValue = SQLFetch(stmtMirror);
																						if (returnValue == SQL_SUCCESS 
																							|| returnValue == SQL_SUCCESS_WITH_INFO) {
																								bRecordFound = TRUE;
																						}
																				}
																				if (bRecordFound) {
																					// do an update
																					sprintf(statementText, 
																						"UPDATE %s.USRC SET ROW = (SELECT * FROM %s.USRC WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER HEADER' AND %s.USRC.MFKEY2='%09d           ') WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER HEADER' AND %s.USRC.MFKEY2= '%09d           '",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																						CMS_DATABASE_NAME, CMS_DATABASE_NAME, order[orders].ordernumber,
																						ORDER_MIRROR, ORDER_MIRROR, ORDER_MIRROR,
																						order[orders].ordernumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to update %s.USRC header rec, order number %ld",
																								ORDER_MIRROR, order[orders].ordernumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}
																				}
																				else {
																					// do an insert
																					sprintf(statementText,
																						"INSERT INTO %s.USRC (SELECT * FROM %s.USRC WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER HEADER' AND %s.USRC.MFKEY2='%09d           ')",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																						CMS_DATABASE_NAME, CMS_DATABASE_NAME, order[orders].ordernumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to insert into %s.USRC header rec order number %ld",
																								ORDER_MIRROR, order[orders].ordernumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}							
																				}
																			}
#							endif
																	}
																	else {
																		order[orders].fasttrack = 0;
																	}

																	// end of fasttrack fetch

																	g_nPointNumber = 3;

																	// Query Decade DB for nitride and steel rates.
																	sprintf(statementText,
																		"SELECT freightcost,steelcost,nitridecost,ftpremium,surcharge,minnitridecost,maxnitridecost,nitridemineffectivedate FROM d_customer WHERE customercode = '%s'",
																		//			1			2			3			4		5			6				7				8			
																		order[orders].customercode);
																	if (order[orders].ordernumber == 1036) {
																		int pqr = 123;
																	}
																	//SQLCloseCursor(stmt);
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmt, 1, SQL_C_FLOAT, 
																		&(order[orders].freightrate), 
																		sizeof(float),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 2, SQL_C_FLOAT, 
																		&(order[orders].steelrate), 
																		sizeof(float),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 3, SQL_C_FLOAT, 
																		&(order[orders].nitriderate), 
																		sizeof(float),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 4, SQL_C_LONG,
																		&(order[orders].ftpremium),
																		sizeof(int),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 5, SQL_C_FLOAT,
																		&(order[orders].surcharge),
																		sizeof(int),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 6, SQL_C_FLOAT,
																		&(order[orders].minnitridecost),
																		sizeof(int),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 7, SQL_C_FLOAT,
																		&(order[orders].maxnitridecost),
																		sizeof(int),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 8, SQL_C_TIMESTAMP,
																		&(order[orders].minnitrideeffectivedate),
																		sizeof(int),
																		&sNameLenOrInd);
																	returnValue = SQLFetch(stmt);
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			sprintf(szMessage, 
																				"Cannot fetch rate fields for customer '%s'",
																				order[orders].customercode);
																			LogError(g_hWndDialog, szMessage);
																	}
																	strcpy(order[orders].customerpo, szPO);
																	if (stPromiseDate.year < 2000) {
																		stPromiseDate.year = 2000;
																	}
																	if (stPromiseDate.month < 1) {
																		stPromiseDate.month = 1;
																	}
																	if (stPromiseDate.day < 1) {
																		stPromiseDate.day = 1;
																	}
																	order[orders].expreceiveddate = stPromiseDate;
																	stShopDate = stExpectedShipDate;
																	order[orders].shopdate = stShopDate;
																	stExpectedReceivedDate = stPromiseDate;
																	order[orders].expreceiveddate = stExpectedReceivedDate;
																	order[orders].expshipdate = stExpectedShipDate;
																	order[orders].discountAmountInCents = 0;
																	// was (int) (fDiscount * 100.0 + 0.5); but
																	// Solarsoft in fact aggregates the global discounts
																	// here, which in our case are the fasttrack and steel charges
																	order[orders].fCMSTaxAmount = fTax;
																	// DW 20100706 change to accommodate HST: gst on freight may be totalled from
																	// OCRF.UVFTTX for individual order items
																	sprintf(statementText,
																		"SELECT SUM(UVFTTX) AS CMSOrderFreightTax FROM %s.OCRF WHERE UVORDR='%d'",
																		//			1					
																		CMS_DATABASE_NAME, order[orders].ordernumber);
																	SQLFreeStmt(stmtOCRF, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtOCRF, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtOCRF, 1, SQL_C_FLOAT, 
																		&fCMSOrderFreightTax, 
																		sizeof(float),
																		&sNameLenOrInd);
																	returnValue = SQLFetch(stmtOCRF);
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			sprintf(szMessage, 
																				"Cannot fetch freight tax field sum for order %d",
																				order[orders].ordernumber);
																			LogError(g_hWndDialog, szMessage);
																	}

																	double dGSTAmount;

																	// 20100706 DW: WAS
																	// dGSTAmount = fTax * 100.0 + fCMSOrderFreight * GST_RATE;
																	// NOW:
																	dGSTAmount = (fTax + fCMSOrderFreightTax) * 100.0;

																	if (fabs(fTax) > 0.005) {
																		if (dGSTAmount >= 0.0) {
																			order[orders].gstInCents = (int) (dGSTAmount + 0.5);
																		}
																		else {
																			order[orders].gstInCents = (int) (dGSTAmount - 0.5);
																		}
																	}
																	else {
																		order[orders].gstInCents = 0;
																	}
																	double dFreightAmount;
																	dFreightAmount = fCMSOrderFreight * 100.0;
																	if (dFreightAmount >= 0.0) {
																		order[orders].freightInCents += (int) (dFreightAmount + 0.5);
																		order[orders].autoFreightInCents += (int) (dFreightAmount + 0.5);
																	}
																	else {
																		order[orders].freightInCents += (int) (dFreightAmount - 0.5);
																		order[orders].autoFreightInCents += (int) (dFreightAmount - 0.5);
																	}
																	order[orders].fCMSTotal = fTotal;
																	if (fTotal >= 0.0) {
																		order[orders].totalInCents = order[orders].gstInCents + order[orders].autoFreightInCents + (int) (fTotal * 100.0 + 0.5);
																	}
																	else {
																		order[orders].totalInCents = order[orders].gstInCents + order[orders].autoFreightInCents + (int) (fTotal * 100.0 - 0.5);
																	}
																	order[orders].freightweight = fCMSOrderFinishedWeight;
																	order[orders].shippingvendor[0] = '\0'; // OK not to pass back
																	if (stShipDate.year < 2000) {
																		stShipDate.year = 2000;
																	}
																	if (stShipDate.month < 1) {
																		stShipDate.month = 1;
																	}
																	if (stShipDate.day < 1) {
																		stShipDate.day = 1;
																	}
																	order[orders].shipdate = stShipDate;
																	// NO. shipdate will be set null below.
																	// At the moment, it should be set
																	// from old systems, not new.
																	order[orders].invoicedate.year = 2000;
																	order[orders].invoicedate.month = 1;
																	order[orders].invoicedate.day = 1;
																	// NO. Should be null on the way into
																	// the old systems.
																	order[orders].steelsurchargeInCents = 0;
																	order[orders].subtotalInCents = 0;
																	if (updateRequestOrderNumbers) {
																		sprintf(szMessage, "Processed OCRH fetch for request %d == ordernumber %d",
																			orders, updateRequestOrderNumber[orders]);
																		LogInfo(g_hWndDialog, szMessage);
																	}
																	++orders;
																} while(1);
																lOrderCountInUpdate = orders;

																orderitems = 0;
																for (i = 0; i < orders; i++) {
#			define MAX_PART_LENGTH 20
																	int nItemNumber;
																	float fQuantity, fUnitPrice, fTotal, 
																		fDiameter, fThickness, fID,
																		fSteelCost, fFreight;
																	char szPart[MAX_FIELD_LENGTH + 1],
																		szAliasPart[MAX_FIELD_LENGTH + 1],
																		szPricingUnit[MAX_FIELD_LENGTH + 1],
																		szDieNumber[MAX_FIELD_LENGTH + 1];
																	int diameterUnits, diameterFraction,
																		thicknessUnits, thicknessFraction,
																		IDUnits, IDFraction;
																	long int nOptionListNumber;
																	int bHeader2Appended;

																	// DDD DW DEBUG
																	if (order[i].ordernumber == 252535) {
																		int ijk = 1234;
																	}

																	SQLFreeStmt(stmtCMS, SQL_CLOSE);
																	order[i].maxItemNumberUsed = 0;
																	order[i].freightchargeInCents = 0;
																	order[i].subtotalInCents = 0;
																	if (order[i].ordernumber == 1082) {
																		int pamj = 8364; // break hanger
																	}
																	// fetch the order items for the ith order
																	OutputDebugString("\n");
																	sprintf(statementText, //                   V--- was DDTOTI
																		"SELECT %s.OCRI.DDITM#,DDQTOI,DDUNPR,DDTOTB,DDPART,DDPRUN,DDRAN#,DDOLST,DDTWGT,DDCSPA,DDTFRT FROM %s.OCRI,%s.OCRIE WHERE %s.OCRI.DDORD# = %d AND %s.OCRI.DDORD#=%s.OCRIE.DDORD# AND %s.OCRI.DDITM#=%s.OCRIE.DDITM# ORDER BY %s.OCRI.DDITM#",
																		//				  1		  2		3		4		5	  6		7		8		9	  10	11
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		order[i].ordernumber,
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME, 
																		CMS_DATABASE_NAME);
																	OutputDebugString(statementText);
																	SQLFreeStmt(stmtCMS, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtCMS, (SQLTCHAR *) statementText, strlen(statementText));
																	returnValue = SQLBindCol(stmtCMS, 1, SQL_C_ULONG, 
																		&nItemNumber, 
																		sizeof(nItemNumber),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 2, SQL_C_FLOAT, 
																		&fQuantity, 
																		sizeof(fQuantity),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 3, SQL_C_FLOAT, 
																		&fUnitPrice, 
																		sizeof(fUnitPrice),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 4, SQL_C_FLOAT, 
																		&fTotal, 
																		sizeof(fTotal),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 5, SQL_C_CHAR, 
																		szPart, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 6, SQL_C_CHAR, 
																		szPricingUnit, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 7, SQL_C_CHAR, 
																		szDieNumber, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 8, SQL_C_ULONG,
																		&nOptionListNumber,
																		sizeof(nOptionListNumber),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 9, SQL_C_FLOAT,
																		&fCMSFinishedWeight,
																		sizeof(fCMSFinishedWeight),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 10, SQL_C_CHAR, 
																		szAliasPart, 
																		MAX_FIELD_LENGTH,
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmtCMS, 11, SQL_C_FLOAT,
																		&fFreight,
																		sizeof(fFreight),
																		&sNameLenOrInd);
																	do {
																		char szDescriptionLine[32];
																		char szPreviousDescriptionLine[32];
																		char szLocationLine[51];
																		char *pPartDescription;
																		long lineNumber;
																		returnValue = SQLFetch(stmtCMS);
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				break;
																		}

#					ifdef ORDER_MIRROR
																		if (bOrderMirroring) {
																			sprintf(statementText,
																				"SELECT DDORD# FROM %s.OCRI WHERE DDORD# = %ld AND DDITM# = %ld",
																				ORDER_MIRROR, order[i].ordernumber, nItemNumber); 						
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			bRecordFound = FALSE;
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					returnValue = SQLFetch(stmtMirror);
																					if (returnValue == SQL_SUCCESS 
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							bRecordFound = TRUE;
																					}
																			}
																			if (bRecordFound) {
																				// do an update
																				sprintf(statementText, 
																					"UPDATE %s.OCRI SET ROW = (SELECT * FROM %s.OCRI WHERE %s.OCRI.DDORD# = %ld AND %s.OCRI.DDITM# = %ld) WHERE %s.OCRI.DDORD# = %ld AND %s.OCRI.DDITM# = %ld",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																					ORDER_MIRROR, order[i].ordernumber, ORDER_MIRROR,
																					nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to update %s.OCRI order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}
																			}
																			else {
																				// do an insert
																				sprintf(statementText,
																					"INSERT INTO %s.OCRI (SELECT * FROM %s.OCRI WHERE %s.OCRI.DDORD# = %ld AND %s.OCRI.DDITM# = %ld)",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to insert into %s.OCRI order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}							
																			}

																			sprintf(statementText,
																				"SELECT DDORD# FROM %s.OCRIE WHERE DDORD# = %ld AND DDITM# = %ld",
																				ORDER_MIRROR, order[i].ordernumber, nItemNumber); 						
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			bRecordFound = FALSE;
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					returnValue = SQLFetch(stmtMirror);
																					if (returnValue == SQL_SUCCESS 
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							bRecordFound = TRUE;
																					}
																			}
																			if (bRecordFound) {
																				// do an update
																				sprintf(statementText, 
																					"UPDATE %s.OCRIE SET ROW = (SELECT * FROM %s.OCRIE WHERE %s.OCRIE.DDORD# = %ld AND %s.OCRIE.DDITM# = %ld) WHERE %s.OCRIE.DDORD# = %ld AND %s.OCRIE.DDITM# = %ld",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																					ORDER_MIRROR, order[i].ordernumber, ORDER_MIRROR,
																					nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to update %s.OCRIE order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}
																			}
																			else {
																				// do an insert
																				sprintf(statementText,
																					"INSERT INTO %s.OCRIE (SELECT * FROM %s.OCRIE WHERE %s.OCRIE.DDORD# = %ld AND %s.OCRIE.DDITM# = %ld)",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to insert into %s.OCRIE order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}							
																			}
																			// DW 20091020At1103: Added copy of OCRO, which indexes between (so#,item#) and w.o.#, and whose
																			// entries DISAPPEAR as work orders are released
																			sprintf(statementText,
																				"SELECT X3ORD#, X3ITM#, X3OLST, RXLSTN FROM %s.OCRO, %s.FOOH WHERE X3ORD# = %ld AND X3ITM# = %ld AND X3OLST = RXLSTN AND RXFLG1 <> '1'",
																				CMS_DATABASE_NAME, ORDER_MIRROR, order[i].ordernumber, nItemNumber); 						
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					SQLBindCol(stmtMirror, 3, SQL_C_ULONG, &OCROlistNumber, sizeof(OCROlistNumber), &sNameLenOrInd);  
																					do {
																						returnValue = SQLFetch(stmtMirror);
																						if (returnValue != SQL_SUCCESS 
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								break; // do
																						}
																						sprintf(statementText,
																							"SELECT X3ORD# FROM %s.OCRO WHERE X3ORD# = %ld AND X3ITM# = %ld AND X3OLST = %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber, OCROlistNumber);
																						SQLFreeStmt(stmtOCRO, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtOCRO, (SQLTCHAR *) statementText, strlen(statementText));
																						bRecordFound = FALSE;
																						if (returnValue == SQL_SUCCESS
																							|| returnValue == SQL_SUCCESS_WITH_INFO) {
																								returnValue = SQLFetch(stmtOCRO);
																								if (returnValue == SQL_SUCCESS 
																									|| returnValue == SQL_SUCCESS_WITH_INFO) {
																										bRecordFound = TRUE;
																								}
																						}
																						if (bRecordFound) {
																							// do an update
																							sprintf(statementText, 
																								"UPDATE %s.OCRO SET ROW = (SELECT * FROM %s.OCRO WHERE %s.OCRO.X3ORD# = %ld AND %s.OCRO.X3ITM# = %ld AND %s.OCRO.X3OLST = %ld) WHERE %s.OCRO.X3ORD# = %ld AND %s.OCRO.X3ITM# = %ld AND %s.OCRO.X3OLST = %ld",
																								ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																								order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																								CMS_DATABASE_NAME, OCROlistNumber,
																								ORDER_MIRROR, order[i].ordernumber, ORDER_MIRROR,
																								nItemNumber, ORDER_MIRROR, OCROlistNumber);
																							SQLFreeStmt(stmtOCRO, SQL_CLOSE);
																							returnValue = SQLExecDirect(stmtOCRO, (SQLTCHAR *) statementText, strlen(statementText));
																							if (returnValue != SQL_SUCCESS
																								&& returnValue != SQL_SUCCESS_WITH_INFO) {
																									sprintf(errorMessage, 
																										"Unable to update %s.OCRO order number %ld, item %ld, list %ld",
																										ORDER_MIRROR, order[i].ordernumber, nItemNumber, OCROlistNumber);
																									LogError(g_hWndDialog, errorMessage);
																									sprintf(errorMessage,
																										"Statement was |%s|", statementText);
																									LogError(g_hWndDialog, errorMessage);
																							}
																						}
																						else {
																							// do an insert
																							sprintf(statementText,
																								"INSERT INTO %s.OCRO (SELECT * FROM %s.OCRO WHERE %s.OCRO.X3ORD# = %ld AND %s.OCRO.X3ITM# = %ld AND %s.OCRO.X3OLST = %ld)",
																								ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																								order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																								CMS_DATABASE_NAME, OCROlistNumber);
																							SQLFreeStmt(stmtOCRO, SQL_CLOSE);
																							returnValue = SQLExecDirect(stmtOCRO, (SQLTCHAR *) statementText, strlen(statementText));
																							if (returnValue != SQL_SUCCESS
																								&& returnValue != SQL_SUCCESS_WITH_INFO) {
																									sprintf(errorMessage, 
																										"Unable to insert into %s.OCRO order number %ld, item %ld, list %ld",
																										ORDER_MIRROR, order[i].ordernumber, nItemNumber, OCROlistNumber);
																									LogError(g_hWndDialog, errorMessage);
																									sprintf(errorMessage,
																										"Statement was |%s|", statementText);
																									LogError(g_hWndDialog, errorMessage);
																							}							
																						}
																					} while (1);
																			}
																			// DW 20091020At1250 Need OCRF for order mirroring
																			sprintf(statementText,
																				"SELECT UVORDR FROM %s.OCRF WHERE UVORDR = %ld AND UVITEM = %ld",
																				ORDER_MIRROR, order[i].ordernumber, nItemNumber); 						
																			SQLFreeStmt(stmtMirror, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																			bRecordFound = FALSE;
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					returnValue = SQLFetch(stmtMirror);
																					if (returnValue == SQL_SUCCESS 
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							bRecordFound = TRUE;
																					}
																			}
																			if (bRecordFound) {
																				// do an update
																				sprintf(statementText, 
																					"UPDATE %s.OCRF SET ROW = (SELECT * FROM %s.OCRF WHERE %s.OCRF.UVORDR = %ld AND %s.OCRF.UVITEM = %ld) WHERE %s.OCRF.UVORDR = %ld AND %s.OCRF.UVITEM = %ld",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																					ORDER_MIRROR, order[i].ordernumber, ORDER_MIRROR,
																					nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to update %s.OCRF order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}
																			}
																			else {
																				// do an insert
																				sprintf(statementText,
																					"INSERT INTO %s.OCRF (SELECT * FROM %s.OCRF WHERE %s.OCRF.UVORDR = %ld AND %s.OCRF.UVITEM = %ld)",
																					ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																					order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber);
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						sprintf(errorMessage, 
																							"Unable to insert into %s.OCRF order number %ld, item %ld",
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						LogError(g_hWndDialog, errorMessage);
																						sprintf(errorMessage,
																							"Statement was |%s|", statementText);
																						LogError(g_hWndDialog, errorMessage);
																				}							
																			}
																		}
#					endif

																		if (order[i].firstOrderItem == -1) {
																			order[i].firstOrderItem = orderitems;
																		}
																		if (!strncmp(szPart, "FREIGHT CHARGE", 14)) {
																			// need to recompute freight-dependent fields, but
																			// differently, since OCRH.DCTOTO includes
																			// the FREIGHT CHARGE line item, but excludes
																			// standard freight.
																			float fCMSOrderFreight = fTotal;
																			double dGSTAmount;
																			dGSTAmount = order[i].fCMSTaxAmount * 100.0;
																			if (fabs(order[i].fCMSTaxAmount) > 0.005) {
																				if (dGSTAmount >= 0.0) {
																					order[i].gstInCents = (int) (dGSTAmount + 0.5);
																				}
																				else {
																					order[i].gstInCents = (int) (dGSTAmount - 0.5);
																				}
																			}
																			else {
																				order[i].gstInCents = 0;
																			}
																			// Solarsoft does not appear to store the gst on freight.
																			double dFreightAmount;
																			dFreightAmount = fCMSOrderFreight * 100.0;
																			if (dFreightAmount >= 0.0) {
																				order[i].freightInCents += (int) (dFreightAmount + 0.5);
																				order[i].manualFreightInCents += (int) (dFreightAmount + 0.5);
																			}
																			else {
																				order[i].freightInCents += (int) (dFreightAmount - 0.5);
																				order[i].manualFreightInCents += (int) (dFreightAmount - 0.5);
																			}
																			if (order[i].fCMSTotal >= 0.0) {
																				order[i].totalInCents = order[i].gstInCents + order[i].autoFreightInCents + (int) (order[i].fCMSTotal * 100.0 + 0.5);
																			}
																			else {
																				order[i].totalInCents = order[i].gstInCents + order[i].autoFreightInCents + (int) (order[i].fCMSTotal * 100.0 - 0.5);
																			}
																			order[i].defaultfreight = 0;
																			continue; // do
																		}
																		// The part below skipped by above continue, omitting
																		// the FREIGHT CHARGE items for CDN plants
																		++(order[i].orderItems);
																		g_nPointNumber = 4;
																		orderitem[orderitems].line = nItemNumber;
																		orderitem[orderitems].nCavities = 0;
																		orderitem[orderitems].chargenitride = !strcmp(szPricingUnit, "NLB");
																		// was: strcpy(orderitem[orderitems].description, szPart);
																		// now:
																		// Fetch description fields for the current order item, and
																		// insert delimiters for distributing them out again
																		// in decade order and invoice documents.
																		sprintf(statementText, 
																			"SELECT DGDESC,DGLIN# FROM %s.OCRD WHERE DGORD# = %d AND DGITM# = %d ORDER BY DGLIN#",
																			CMS_DATABASE_NAME, 
																			order[i].ordernumber,
																			nItemNumber);
																		SQLFreeStmt(stmtOCRD, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtOCRD, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtOCRD, 1, SQL_C_CHAR, 
																			szDescriptionLine, 
																			31,
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRD, 2, SQL_C_ULONG, 
																			&lineNumber, 
																			sizeof(lineNumber),
																			&sNameLenOrInd);
																		orderitem[orderitems].description[0] = '\0';
																		szPreviousDescriptionLine[0] = '\0';
																		bHeader2Appended = 0;
																		do {
																			returnValue = SQLFetch(stmtOCRD);
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					break; // do
																			}

#							ifdef ORDER_MIRROR
																			if (bOrderMirroring) {
																				sprintf(statementText,
																					"SELECT DGORD# FROM %s.OCRD WHERE DGORD# = %ld AND DGITM# = %ld AND DGLIN# = %ld",
																					ORDER_MIRROR, order[i].ordernumber, nItemNumber, lineNumber); 						
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				bRecordFound = FALSE;
																				if (returnValue == SQL_SUCCESS
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						returnValue = SQLFetch(stmtMirror);
																						if (returnValue == SQL_SUCCESS 
																							|| returnValue == SQL_SUCCESS_WITH_INFO) {
																								bRecordFound = TRUE;
																						}
																				}
																				if (bRecordFound) {
																					// do an update
																					sprintf(statementText, 
																						"UPDATE %s.OCRD SET ROW = (SELECT * FROM %s.OCRD WHERE %s.OCRD.DGORD#=%ld AND %s.OCRD.DGITM#=%ld AND %s.OCRD.DGLIN#=%ld) WHERE %s.OCRD.DGORD#=%ld AND %s.OCRD.DGITM#=%ld AND %s.OCRD.DGLIN#=%ld",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																						order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																						CMS_DATABASE_NAME, lineNumber, ORDER_MIRROR,
																						order[i].ordernumber, ORDER_MIRROR, nItemNumber,
																						ORDER_MIRROR, lineNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to update %s.OCRD order number %ld, item %ld, line %ld",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, lineNumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}
																				}
																				else {
																					// do an insert
																					sprintf(statementText,
																						"INSERT INTO %s.OCRD (SELECT * FROM %s.OCRD WHERE %s.OCRD.DGORD# = %ld AND %s.OCRD.DGITM# = %ld AND %s.OCRD.DGLIN# = %ld)",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																						order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																						CMS_DATABASE_NAME, lineNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to insert into %s.OCRD order number %ld, item %ld, line %ld",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, lineNumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}							
																				}
																			}
#							endif

																			if (orderitem[orderitems].description[0]) {
																				switch (lineNumber) {
																				case 1:
																					break;
																				case 2:
																					if (!strncmp(orderitem[orderitems].description, szDescriptionLine, 6)
																						|| !strncmp(szDescriptionLine, "NITROGEN GROOVES BOLSTER", 18)) {
																							break; // line 2 often duplicates line 1
																					}
																					else {
																						strcat(orderitem[orderitems].description, "<2>");
																						bHeader2Appended = 1;
																						break;
																					}
																				case 3:
																					if (!bHeader2Appended) {
																						strcat(orderitem[orderitems].description, "<2>");
																						bHeader2Appended = 1;
																						break;
																					}
																					else {
																						strcat(orderitem[orderitems].description, " ");											
																						break;
																					}
																				case 5:
																				case 6:
																				case 8:
																				case 9:
																				case 10:
																				case 11:
																					strcat(orderitem[orderitems].description, " ");
																					break;
																				case 4:
																					strcat(orderitem[orderitems].description, "<3>");
																					break;
																				case 7:
																					strcat(orderitem[orderitems].description, "<4>");
																					break;
																				}
																			}
																			if ((!strncmp(szPreviousDescriptionLine, szDescriptionLine, 6)
																				|| !strncmp(szDescriptionLine, "NITROGEN GROOVES BOLSTER", 18))
																				&& lineNumber == 2) {
																					continue; // do. Line is a duplicate
																			}
																			strcpy(szPreviousDescriptionLine, szDescriptionLine);
																			char szUpperCasedDescription[1024];
																			// check for "SHELF" keyword
																			strcpy(szUpperCasedDescription, szDescriptionLine);
																			_strupr(szUpperCasedDescription);
																			if (strstr(szUpperCasedDescription, "SHELF") != NULL) {
																				order[i].shelf = 0; // was 1, but AluDie's process is to
																				// shelve the order explicitly when 
																				// complete, for the sake of their
																				// ontime performance reporting.
																				// This field is NO LONGER PASSED TO
																				// Decade DB, for the above reason.
																				order[i].shelforder = 1;
																			}
																			// check for "RUSH" keyword
																			if (strstr(szUpperCasedDescription, "RUSH") != NULL) {
																				order[i].priority = 1;
																			}
																			if (lineNumber == 1 
																				&& (strcspn(szAliasPart, "0123456789") != strlen(szAliasPart))
																				&& (strcspn(szPart, "0123456789") != strlen(szPart))) {
																					// trim leading and trailing blanks from szAliasPart
																					char *pChar, szStripped[1024];
																					pChar = szAliasPart;
																					while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																						++pChar;
																					}
																					strcpy(szStripped, pChar);
																					pChar = szStripped + (strlen(szStripped) - 1);
																					while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																						--pChar;
																					}
																					int newLength = (pChar - szStripped + 1);
																					strncpy(szAliasPart, szStripped, newLength);
																					szAliasPart[newLength] = '\0';
																					strcat(orderitem[orderitems].description, szAliasPart);
																			}
																			else {
																				// trim leading and trailing blanks from szDescriptionLine
																				char *pChar, szStripped[1024];
																				pChar = szDescriptionLine;
																				while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																					++pChar;
																				}
																				strcpy(szStripped, pChar);
																				pChar = szStripped + (strlen(szStripped) - 1);
																				while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																					--pChar;
																				}
																				int newLength = (pChar - szStripped + 1);
																				strncpy(szDescriptionLine, szStripped, newLength);
																				szDescriptionLine[newLength] = '\0';
																				strcat(orderitem[orderitems].description, szDescriptionLine);
																			}
																		} while (1); 
																		// Fetch any line item notes from CMS table OENOTE
																		sprintf(statementText,
																			"SELECT GGTEXT,GGLIN# FROM %s.OENOTE WHERE GGKEY='%09d%03d' AND GGPAG#=1 AND GGLIN#>0 ORDER BY GGLIN#",
																			CMS_DATABASE_NAME, 
																			order[i].ordernumber,
																			nItemNumber);
																		SQLFreeStmt(stmtOENOTE, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtOENOTE, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtOENOTE, 1, SQL_C_CHAR, 
																			szNoteLine, 
																			sizeof(szNoteLine),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOENOTE, 2, SQL_C_ULONG, 
																			&nLineNumber, 
																			sizeof(nLineNumber),
																			&sNameLenOrInd);
																		orderitem[orderitems].note[0] = '\0';
																		do {
																			returnValue = SQLFetch(stmtOENOTE);
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					break; // do
																			}

#							ifdef ORDER_MIRROR
																			if (bOrderMirroring) {
																				sprintf(statementText,
																					"SELECT GGKEY FROM %s.OENOTE WHERE GGKEY='%09d%03d' AND GGPAG# = 1 AND GGLIN# = %ld",
																					ORDER_MIRROR, order[i].ordernumber, nItemNumber, 
																					nLineNumber); 						
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				bRecordFound = FALSE;
																				if (returnValue == SQL_SUCCESS
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						returnValue = SQLFetch(stmtMirror);
																						if (returnValue == SQL_SUCCESS 
																							|| returnValue == SQL_SUCCESS_WITH_INFO) {
																								bRecordFound = TRUE;
																						}
																				}
																				if (bRecordFound) {
																					// do an update
																					sprintf(statementText, 
																						"UPDATE %s.OENOTE SET ROW = (SELECT * FROM %s.OENOTE WHERE %s.OENOTE.GGKEY = '%09d%03d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld) WHERE %s.OENOTE.GGKEY = '%09d%03d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																						order[i].ordernumber, nItemNumber, CMS_DATABASE_NAME,
																						CMS_DATABASE_NAME, nLineNumber, CMS_DATABASE_NAME,
																						order[i].ordernumber, nItemNumber, CMS_DATABASE_NAME,
																						CMS_DATABASE_NAME, nLineNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to update %s.OENOTE order number %ld, item %ld, line %ld",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, nLineNumber);
																							LogError(g_hWndDialog, errorMessage);
																					}
																				}
																				else {
																					// do an insert
																					sprintf(statementText,
																						"INSERT INTO %s.OENOTE (SELECT * FROM %s.OENOTE WHERE %s.OENOTE.GGKEY = '%09d%03d' AND %s.OENOTE.GGPAG# = 1 AND %s.OENOTE.GGLIN# = %ld)",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																						order[i].ordernumber, nItemNumber, CMS_DATABASE_NAME, 
																						CMS_DATABASE_NAME, nLineNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to insert into %s.OENOTE order number %ld, item %ld, line %ld",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, nLineNumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}							
																				}
																			}
#							endif

																			// trim extra whitespace from szNoteLine
																			char *pChar, szTrimmed[1024];
																			int newLength;
																			pChar = szNoteLine;
																			while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																				++pChar;
																			}
																			strcpy(szTrimmed, pChar);
																			pChar = szTrimmed + strlen(szTrimmed) - 1;
																			while (*pChar == ' ' || *pChar == '\t' || *pChar == '\n' || *pChar == '\r') {
																				--pChar;
																			}
																			newLength = (pChar - szTrimmed + 1);
																			strncpy(szNoteLine, szTrimmed, newLength);
																			szNoteLine[newLength] = '\0';
																			if (strlen(orderitem[orderitems].note) + strlen(szNoteLine) + 1 < FULL_DESCRIPTION_LENGTH) {
																				if (orderitem[orderitems].note) {
																					strcat(orderitem[orderitems].note, " ");
																				}
																				strcat(orderitem[orderitems].note, szNoteLine);
																			}
																		} while (1);		
																		// Fetch location field (a user-defined field) for the current order item
																		sprintf(statementText, 
																			"SELECT MFRESP FROM %s.USRC WHERE MFSRCE = 'ORD' AND MFKEY1 = 'ORDER ITEM' AND MFKEY2 = '%09d        %03d'",
																			CMS_DATABASE_NAME, 
																			order[i].ordernumber,
																			nItemNumber);
																		OutputDebugString("\n");
																		OutputDebugString(statementText);
																		OutputDebugString("\n");
																		SQLFreeStmt(stmtUSRC, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtUSRC, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtUSRC, 1, SQL_C_CHAR, 
																			szLocationLine, 
																			50,
																			&sNameLenOrInd);
																		returnValue = SQLFetch(stmtUSRC);
																		if (returnValue == SQL_SUCCESS
																			|| returnValue == SQL_SUCCESS_WITH_INFO) {

#							ifdef ORDER_MIRROR
																				if (bOrderMirroring) {
																					sprintf(statementText,
																						"SELECT MFKEY2 FROM %s.USRC WHERE MFSRCE='ORD' AND MFKEY1='ORDER ITEM' AND MFKEY2='%09d        %03d'",
																						ORDER_MIRROR, order[i].ordernumber, nItemNumber); 						
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					bRecordFound = FALSE;
																					if (returnValue == SQL_SUCCESS
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							returnValue = SQLFetch(stmtMirror);
																							if (returnValue == SQL_SUCCESS 
																								|| returnValue == SQL_SUCCESS_WITH_INFO) {
																									bRecordFound = TRUE;
																							}
																					}
																					if (bRecordFound) {
																						// do an update
																						sprintf(statementText, 
																							"UPDATE %s.USRC SET ROW = (SELECT * FROM %s.USRC WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER ITEM' AND %s.USRC.MFKEY2='%09d        %03d') WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER ITEM' AND %s.USRC.MFKEY2= '%09d        %03d'",
																							ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																							CMS_DATABASE_NAME, CMS_DATABASE_NAME, order[i].ordernumber,
																							nItemNumber, ORDER_MIRROR, ORDER_MIRROR, 
																							ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to update %s.USRC item rec, order number %ld, item %ld",
																									ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																								LogError(g_hWndDialog, errorMessage);
																						}
																					}
																					else {
																						// do an insert
																						sprintf(statementText,
																							"INSERT INTO %s.USRC (SELECT * FROM %s.USRC WHERE %s.USRC.MFSRCE='ORD' AND %s.USRC.MFKEY1='ORDER ITEM' AND %s.USRC.MFKEY2='%09d        %03d')",
																							ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																							CMS_DATABASE_NAME, CMS_DATABASE_NAME, order[i].ordernumber,
																							nItemNumber);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to insert into %s.USRC item rec order number %ld, item %ld",
																									ORDER_MIRROR, order[i].ordernumber, nItemNumber);
																								LogError(g_hWndDialog, errorMessage);
																								sprintf(errorMessage,
																									"Statement was |%s|", statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}							
																					}
																				}
#							endif

																				char szLocationUpper[1024], *pLocation;
																				strcpy(szLocationUpper, szLocationLine);
																				_strupr(szLocationUpper);
																				pLocation = szLocationUpper;
																				while (*pLocation == ' '
																					|| *pLocation == '\t') {
																						++pLocation;
																				}
																				if (strncmp(pLocation, "NA", 2)) {
																					strcpy(orderitem[orderitems].location, szLocationLine);
																				}
																				else {
																					orderitem[orderitems].location[0] = '\0';
																				}
																		}
																		else {
																			orderitem[orderitems].location[0] = '\0';
																		}
																		if (order[i].maxItemNumberUsed < nItemNumber) {
																			order[i].maxItemNumberUsed = nItemNumber;
																		}
																		orderitem[orderitems].ispart = 0; // until proven otherwise
																		// Fetch steel, fasttrack and package discount items for a given
																		// order item from table OCRS
																		sprintf(statementText, 
																			"SELECT FFDISC,FFDDES,FFPERC,FFDAMT,FFDEXT,FFDIS# FROM %s.OCRS WHERE FFORD# = %d AND FFITM# = %d",
																			CMS_DATABASE_NAME,
																			order[i].ordernumber,
																			nItemNumber);
																		SQLFreeStmt(stmtOCRS, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmtOCRS, (SQLTCHAR *) statementText, strlen(statementText));
																		returnValue = SQLBindCol(stmtOCRS, 1, SQL_C_CHAR, 
																			szDiscountCode, 
																			sizeof(szDiscountCode),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRS, 2, SQL_C_CHAR, 
																			szDescription, 
																			sizeof(szDescription),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRS, 3, SQL_C_FLOAT, 
																			&fPercent, 
																			sizeof(fPercent),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRS, 4, SQL_C_FLOAT, 
																			&fDiscountAmount, 
																			sizeof(fDiscountAmount),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRS, 5, SQL_C_FLOAT, 
																			&fExtension, 
																			sizeof(fExtension),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmtOCRS, 6, SQL_C_ULONG, 
																			&lDiscountNumber, 
																			sizeof(lDiscountNumber),
																			&sNameLenOrInd);
																		orderitem[orderitems].cmsFastTrack = 0.0;
																		orderitem[orderitems].cmsSteel = 0.0;
																		do {
																			returnValue = SQLFetch(stmtOCRS);
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					break;
																			}

#							ifdef ORDER_MIRROR
																			if (bOrderMirroring) {
																				sprintf(statementText,
																					"SELECT FFORD# FROM %s.OCRS WHERE FFORD# = %ld AND FFITM# = %ld AND FFDISC = '%s' AND FFDIS# = %ld",
																					ORDER_MIRROR, order[i].ordernumber, nItemNumber, szDiscountCode, lDiscountNumber); 						
																				SQLFreeStmt(stmtMirror, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																				bRecordFound = FALSE;
																				if (returnValue == SQL_SUCCESS
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						returnValue = SQLFetch(stmtMirror);
																						if (returnValue == SQL_SUCCESS 
																							|| returnValue == SQL_SUCCESS_WITH_INFO) {
																								bRecordFound = TRUE;
																						}
																				}
																				if (bRecordFound) {
																					// do an update
																					sprintf(statementText, 
																						"UPDATE %s.OCRS SET ROW = (SELECT * FROM %s.OCRS WHERE %s.OCRS.FFORD# = %ld AND %s.OCRS.FFITM# = %ld AND %s.OCRS.FFDISC = '%s' AND %s.OCRS.FFDIS# = %ld) WHERE %s.OCRS.FFORD# = %ld AND %s.OCRS.FFITM# = %ld AND %s.OCRS.FFDISC = '%s' AND %s.OCRS.FFDIS# = %ld",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																						order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																						CMS_DATABASE_NAME, szDiscountCode, 
																						CMS_DATABASE_NAME, lDiscountNumber, ORDER_MIRROR, 
																						order[i].ordernumber, ORDER_MIRROR,	nItemNumber,
																						ORDER_MIRROR, szDiscountCode, ORDER_MIRROR, lDiscountNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to update %s.OCRS order number %ld, item %ld, discount '%s'",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, szDiscountCode);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}
																				}
																				else {
																					// do an insert
																					sprintf(statementText,
																						"INSERT INTO %s.OCRS (SELECT * FROM %s.OCRS WHERE %s.OCRS.FFORD# = %ld AND %s.OCRS.FFITM# = %ld AND %s.OCRS.FFDISC = '%s' AND %s.OCRS.FFDIS# = %ld)",
																						ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																						order[i].ordernumber, CMS_DATABASE_NAME, nItemNumber,
																						CMS_DATABASE_NAME, szDiscountCode, CMS_DATABASE_NAME, lDiscountNumber);
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to insert into %s.OCRS order number %ld, item %ld, discount '%s' dis# %ld",
																								ORDER_MIRROR, order[i].ordernumber, nItemNumber, szDiscountCode, lDiscountNumber);
																							LogError(g_hWndDialog, errorMessage);
																							sprintf(errorMessage,
																								"Statement was |%s|", statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}							
																				}
																			}
#							endif

																			if (strstr(szDiscountCode, "F") != NULL) {
																				orderitem[orderitems].cmsFastTrack += fExtension;
																				if (fExtension >= 0.0) {
																					order[i].fasttrackchargeInCents += (int) (fExtension * 100.0 + 0.5);
																				}
																				else {
																					order[i].fasttrackchargeInCents += (int) (fExtension * 100.0 - 0.5);
																				}
																				order[i].fasttrack = 1;
																			}
																			else if (strstr(szDiscountCode, "S") != NULL
																				|| strstr(szDiscountCode, "P") != NULL) {
																					orderitem[orderitems].cmsSteel += fExtension;
																			}
																			else if (strstr(szDiscountCode, "D") != NULL) {
																				orderitem[orderitems].cmsPackageDiscount += fExtension;
																				// may potentially populate a package discount description field here
																				// ONLY IF NEEDED
																				order[i].packageDiscountInCents += (int) (fExtension * 100.0 - 0.5);
																				//  ^ because amount is negative
																				order[i].packageDiscount = 1;
																			}
																		} while (1);
																		orderitem[orderitems].ordernumber = order[i].ordernumber;
																		orderitem[orderitems].orderIndex = i;
																		if ((strcspn(szAliasPart, "0123456789") != strlen(szAliasPart))
																			&& (strcspn(szPart, "0123456789") != strlen(szPart))) {
																				pPartDescription = szAliasPart;
																		}
																		else {
																			pPartDescription = szPart;
																		}
																		g_nPointNumber = 5;
																		if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTSolid]) != NULL
#						ifdef COLOMBIA
																			|| strstr(szPart, cmsPrefix[0][eDTSolid]) != NULL) {
#						else
																			) {
#						endif
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTSolid]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning SD part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",  // 01 a placeholder
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTHDMandrel]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTHDMandrel]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning HD MANDREL part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(1, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTHDPlate]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTHDMandrel]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning HD PLATE part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTHDBacker]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTHDBacker]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning HD BACKER part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTHollow]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTHollow]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning HD part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(1, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTFeeder]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTFeeder]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning FDR part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																				strcpy(order[i].feederNumber, szDieNumber);
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTBacker]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTBacker]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning BA part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																				strcpy(order[i].backerNumber, szDieNumber);
																				strcpy(order[i].backerLocation, orderitem[orderitems].location);
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTBolster]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTBolster]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning BO part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTSubBolster]) != NULL
																			) {
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTSubBolster]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																					&fDiameter, &fThickness) != 2) {
																						// report error
																						fDiameter = 0.0;
																						fThickness = 0.0;
																						LogError(g_hWndDialog, "Error scanning SB part code");
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"M%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"I%04d.%03dx%04d.%03d-01",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else if (strstr(szPart, cmsPrefix[TARGET_PLANT][eDTRing]) != NULL
																			) {
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTRing]);
																				sprintf(orderitem[orderitems].suffix, "CUSTOM - TBD");
																				orderitem[orderitems].ispart = 1;
																				strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTRing]);
																				if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f - %f",
																					&fDiameter, &fThickness, &fID) != 3) {
																						fID = 0.0;
																						if (sscanf(pPartDescription, "%*s%*[^0123456789]%f X %f",
																							&fDiameter, &fThickness) != 2) {
																								// report error
																								fDiameter = 0.0;
																								fThickness = 0.0;
																								LogError(g_hWndDialog, "Error scanning RI part code");
																						}
																				}
																				diameterUnits = (int) fDiameter;
																				diameterFraction = ((int)(fDiameter * 1000.0 + 0.5)) % 1000;
																				thicknessUnits = (int) fThickness;
																				thicknessFraction = ((int) (fThickness * 1000.0 + 0.5)) % 1000;
																				IDUnits = (int) fID;
																				IDFraction = ((int)(fID * 1000.0 + 0.5)) % 1000;
																				bMetric = (fDiameter >= MIN_DIAMETER_TO_INTERPRET_AS_MM);
																				if (bMetric) {
																					sprintf(orderitem[orderitems].suffix, 
																						"MD%04d.%03dx%04d.%03d-%04d.%03d",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction,
																						IDUnits, IDFraction);
																				}
																				else {
																					sprintf(orderitem[orderitems].suffix, 
																						"ID%04d.%03dx%04d.%03d-%04d.%03d",
																						diameterUnits, diameterFraction,
																						thicknessUnits, thicknessFraction,
																						IDUnits, IDFraction);
																				}
																				orderitem[orderitems].roughweight =
																					RoughWeight(0, fDiameter, fThickness);
																				// NOW: Using CMS value, unchecked
																				fSteelCost = orderitem[orderitems].cmsSteel;
																				if (orderitem[orderitems].roughweight > 0.1) {
																					order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																				}
																				if (fSteelCost >= 0.0) {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 + 0.5);
																				}
																				else {
																					orderitem[orderitems].steelcostInCents
																						= (int) (fSteelCost * 100.0 - 0.5);
																				}
																				order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																				if (fabs(fSteelCost - orderitem[orderitems].cmsSteel) > 0.015) {
																					sprintf(szMessage, 
																						"Steel surcharges on order# %d item %d differ by more than one cent",
																						order[i].ordernumber,
																						orderitem[orderitems].line);
																					LogError(g_hWndDialog, szMessage);
																				}
																		}
																		else {
																			strcpy(orderitem[orderitems].prefix, decadePrefix[TARGET_PLANT][eDTUnknown]);
																			strcpy(orderitem[orderitems].suffix, "");
																			fSteelCost = orderitem[orderitems].cmsSteel;
																			if (orderitem[orderitems].roughweight > 0.1) {
																				order[i].steelrate = (float) (fSteelCost / orderitem[orderitems].roughweight);
																			}
																			if (fSteelCost >= 0.0) {
																				orderitem[orderitems].steelcostInCents
																					= (int) (fSteelCost * 100.0 + 0.5);
																			}
																			else {
																				orderitem[orderitems].steelcostInCents
																					= (int) (fSteelCost * 100.0 - 0.5);
																			}
																			order[i].steelsurchargeInCents += orderitem[orderitems].steelcostInCents;
																		}
																		g_nPointNumber = 6;
																		if (fUnitPrice >= 0.0) {
																			orderitem[orderitems].priceInCents = (int) (fUnitPrice * 100.0 + 0.5);
																		}
																		else {
																			orderitem[orderitems].priceInCents = (int) (fUnitPrice * 100.0 - 0.5);
																		}
																		orderitem[orderitems].qty = (double) fQuantity;

																		// find options associated with 
																		// the present item
																		orderitem[orderitems].optionListNumber = nOptionListNumber;
																		if (nOptionListNumber != 0) {
																			sprintf(statementText,
																				"SELECT R0FCDE,R0OCDE,R0QTYR,R0UNIT,R0UPRC,R0FUT1 FROM %s.FOOD WHERE R0LSTN = %ld",
																				CMS_DATABASE_NAME, nOptionListNumber);
																			SQLFreeStmt(stmtFOOD, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmtFOOD, (SQLTCHAR *) statementText, strlen(statementText));
																			returnValue = SQLBindCol(stmtFOOD, 1, SQL_C_CHAR, 
																				szFeatureCode, 
																				sizeof(szFeatureCode),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtFOOD, 2, SQL_C_CHAR, 
																				szOptionCode, 
																				sizeof(szOptionCode),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtFOOD, 3, SQL_C_ULONG, 
																				&nQuantity, 
																				sizeof(nQuantity),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtFOOD, 4, SQL_C_CHAR, 
																				szUnits, 
																				sizeof(szUnits),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtFOOD, 5, SQL_C_FLOAT, 
																				&fUnitPrice, 
																				sizeof(fUnitPrice),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtFOOD, 6, SQL_C_CHAR, 
																				szFut1, 
																				sizeof(szFut1),
																				&sNameLenOrInd);
																			orderitem[orderitems].options = 0;
																			if (order[i].ordernumber == 210002) {
																				int kjhkj = 9887987; // break hanger
																			}
																			do {
																				returnValue = SQLFetch(stmtFOOD);
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						break;
																				}

#								ifdef ORDER_MIRROR
																				if (bOrderMirroring) {
																					sprintf(statementText,
																						"SELECT R0LSTN FROM %s.FOOD WHERE R0LSTN = %ld AND R0FCDE = '%s' AND R0OCDE = '%s'",
																						ORDER_MIRROR, nOptionListNumber, szFeatureCode, szOptionCode); 						
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					bRecordFound = FALSE;
																					if (returnValue == SQL_SUCCESS
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							returnValue = SQLFetch(stmtMirror);
																							if (returnValue == SQL_SUCCESS 
																								|| returnValue == SQL_SUCCESS_WITH_INFO) {
																									bRecordFound = TRUE;
																							}
																					}
																					if (bRecordFound) {
																						// do an update
																						sprintf(statementText, 
																							"UPDATE %s.FOOD SET ROW = (SELECT * FROM %s.FOOD WHERE %s.FOOD.R0LSTN = %ld AND %s.FOOD.R0FCDE = '%s' AND %s.FOOD.R0OCDE = '%s') WHERE %s.FOOD.R0LSTN = %ld AND %s.FOOD.R0FCDE = '%s' AND %s.FOOD.R0OCDE = '%s'",
																							ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																							nOptionListNumber, CMS_DATABASE_NAME, szFeatureCode,
																							CMS_DATABASE_NAME, szOptionCode, ORDER_MIRROR, 
																							nOptionListNumber, ORDER_MIRROR, szFeatureCode, 
																							ORDER_MIRROR, szOptionCode);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to update %s.FOOD option list %ld for order number %ld",
																									ORDER_MIRROR, nOptionListNumber, 
																									order[i].ordernumber);
																								LogError(g_hWndDialog, errorMessage);
																								sprintf(errorMessage,
																									"Statement was |%s|", statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}
																					}
																					else {
																						// do an insert
																						sprintf(statementText,
																							"INSERT INTO %s.FOOD (SELECT * FROM %s.FOOD WHERE %s.FOOD.R0LSTN = %ld AND %s.FOOD.R0FCDE = '%s' AND %s.FOOD.R0OCDE = '%s')",
																							ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																							nOptionListNumber, CMS_DATABASE_NAME, szFeatureCode, 
																							CMS_DATABASE_NAME, szOptionCode);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to insert into %s.FOOD option list %ld for order number %ld",
																									ORDER_MIRROR, nOptionListNumber, order[i].ordernumber);
																								LogError(g_hWndDialog, errorMessage);
																								sprintf(errorMessage,
																									"Statement was |%s|", statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}							
																					}
																					// DW 20091020At1229: FOOH Needed for order mirroring
																					sprintf(statementText,
																						"SELECT RXLSTN FROM %s.FOOH WHERE RXLSTN = %ld",
																						ORDER_MIRROR, nOptionListNumber); 						
																					SQLFreeStmt(stmtMirror, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																					bRecordFound = FALSE;
																					if (returnValue == SQL_SUCCESS
																						|| returnValue == SQL_SUCCESS_WITH_INFO) {
																							returnValue = SQLFetch(stmtMirror);
																							if (returnValue == SQL_SUCCESS 
																								|| returnValue == SQL_SUCCESS_WITH_INFO) {
																									bRecordFound = TRUE;
																							}
																					}
																					if (bRecordFound) {
																						// do an update
																						sprintf(statementText,
																							"UPDATE %s.FOOH AS T1 SET (RXMCDE,RXQTYR,RXUNIT,RXMBPR,RXPUNT,RXUCST,RXUPRC,RXPART,RXPLNT) = (SELECT T2.RXMCDE,T2.RXQTYR,T2.RXUNIT,T2.RXMBPR,T2.RXPUNT,T2.RXUCST,T2.RXUPRC,T2.RXPART,T2.RXPLNT FROM %s.FOOH AS T2 WHERE T1.RXLSTN = T2.RXLSTN) WHERE T1.RXLSTN = %ld",
																							ORDER_MIRROR, CMS_DATABASE_NAME, nOptionListNumber);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to update %s.FOOH option list %ld for order number %ld",
																									ORDER_MIRROR, nOptionListNumber, 
																									order[i].ordernumber);
																								LogError(g_hWndDialog, errorMessage);
																								sprintf(errorMessage,
																									"Statement was |%s|", statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}
																					}
																					else {
																						// do an insert
																						sprintf(statementText,
																							"INSERT INTO %s.FOOH (SELECT * FROM %s.FOOH WHERE %s.FOOH.RXLSTN = %ld)",
																							ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME, 
																							nOptionListNumber);
																						SQLFreeStmt(stmtMirror, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to insert into %s.FOOH option list %ld for order number %ld",
																									ORDER_MIRROR, nOptionListNumber, order[i].ordernumber);
																								LogError(g_hWndDialog, errorMessage);
																								sprintf(errorMessage,
																									"Statement was |%s|", statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}							
																					}
																				}
#								endif

																				pOption = orderitem[orderitems].option
																					+ orderitem[orderitems].options;
																				if (strstr(szFeatureCode, featureCode[TARGET_PLANT][FEATURE_CAVITIES]) != NULL
																					) {
																						pOption->featureType = FEATURE_CAVITIES;
																						orderitem[orderitems].nCavities = nQuantity; 
																				}
																				else if (strstr(szFeatureCode, featureCode[TARGET_PLANT][FEATURE_NITRIDING]) != NULL
																					) {
																						pOption->featureType = FEATURE_NITRIDING;
																						order[i].hasNitrideItem = 1;
																				}
																				else if (strstr(szFeatureCode, featureCode[TARGET_PLANT][FEATURE_EXTRA_CHARGE]) != NULL
																					|| strstr(szFeatureCode, "INDALEX CA") != NULL
																					|| strstr(szFeatureCode, "INDALEX US") != NULL
																					) {
																						pOption->featureType = FEATURE_EXTRA_CHARGE;
																				}
																				else if (strstr(szFeatureCode, featureCode[TARGET_PLANT][FEATURE_POCKET_CHARGE]) != NULL
																					) {
																						pOption->featureType = FEATURE_POCKET_CHARGE;
																				}
																				else if (strstr(szFeatureCode, featureCode[TARGET_PLANT][FEATURE_N2_GROOVES]) != NULL
																					) {
																						pOption->featureType = FEATURE_N2_GROOVES;
																				}
																				else {
																					char szFeatureMessage[1024];
																					sprintf(szFeatureMessage,
																						"In order %d, encountered unknown feature '%s'",
																						order[i].ordernumber, szFeatureCode);
																					LogInfo(g_hWndDialog, szFeatureMessage);
																					pOption->featureType = FEATURE_UNKNOWN;
																				}
																				strncpy(pOption->szOptionCode, szOptionCode, CUSTOMER_TEXT_FIELD_LENGTH);
																				pOption->szOptionCode[CUSTOMER_TEXT_FIELD_LENGTH] = '\0';
																				_strupr(szOptionCode);
																				if (strstr(szOptionCode, "SKIM") != NULL) {
																					order[i].hasSkimCutItem = 1;
																				}
																				if (strstr(szOptionCode, "NITRID") != NULL) { // covers the ad hoc nitride items
																					order[i].hasNitrideItem = 1;										}
																				pOption->quantity = nQuantity;
																				strncpy(pOption->szUnits, szUnits, 3);
																				pOption->szUnits[3] = '\0';
																				pOption->unitPrice = fUnitPrice;
																				strncpy(pOption->szFut1Field, szFut1, SMALL_FIELD_LENGTH);
																				pOption->szFut1Field[SMALL_FIELD_LENGTH] = '\0';
																				++(orderitem[orderitems].options);
																			} while (1);
																			SQLFreeStmt(stmtFOOD, SQL_CLOSE);
																		}
																		fFinishedWeight = FinishedWeight(fDiameter, fThickness);
																		orderitem[orderitems].finishedweight = fFinishedWeight;
																		// compute freight cost
																		float fFreightCost;
																		fFreightCost = fFreight; // from OCRI.DDTFRT
																		if (fFreightCost >= 0.0) {
																			orderitem[orderitems].freightcostInCents
																				= (int) (fFreightCost * 100.0 + 0.5);
																		}
																		else {
																			orderitem[orderitems].freightcostInCents
																				= (int) (fFreightCost * 100.0 - 0.5);
																		}
																		order[i].freightchargeInCents +=
																			orderitem[orderitems].freightcostInCents;
																		// DW CHANGE 2009-02-03 copy die number unconditionally
																		strcpy(orderitem[orderitems].dienumber, szDieNumber);
																		if (orderitem[orderitems].chargenitride) {
																			float fNitrideWeight, fNitrideCost;
																			fNitrideWeight = fFinishedWeight;
																			order[i].nitrideweight += fNitrideWeight;
																			fNitrideCost = fNitrideWeight * order[i].nitriderate;
																			if (fNitrideCost >= 0.0) {
																				orderitem[orderitems].nitridecostInCents
																					= (int) (fNitrideCost * 100.0 + 0.5);
																			}
																			else {
																				orderitem[orderitems].nitridecostInCents
																					= (int) (fNitrideCost * 100.0 - 0.5);
																			}
																			orderitem[orderitems].qty = 1.0;
																			if (fTotal >= 0.0) {
																				orderitem[orderitems].priceInCents = (int) (fTotal * 100.0 + 0.5);
																			}
																			else {
																				orderitem[orderitems].priceInCents = (int) (fTotal * 100.0 - 0.5);
																			}
																		} // if (orderitem...nitride)
																		double dSubtotal;
																		dSubtotal = ((double) orderitem[orderitems].priceInCents) * orderitem[orderitems].qty;
																		if (dSubtotal >= 0.0) {
																			order[i].subtotalInCents += (int) (dSubtotal + 0.5);
																		}
																		else {
																			order[i].subtotalInCents += (int) (dSubtotal - 0.5);
																		}
																		++orderitems;
																	} while(1);

																	// Add fasttrack order item, if necessary
																	if (order[i].fasttrack) {
																		//double dbFastTrack;
																		orderitem[orderitems].chargenitride = 0;
																		orderitem[orderitems].cmsFastTrack = 0;
																		orderitem[orderitems].cmsSteel = 0;
																		strcpy(orderitem[orderitems].description,
																			"Fast Track");
																		orderitem[orderitems].dienumber[0] = '\0';
																		orderitem[orderitems].fCustomerNitrideRate = 0.0;
																		orderitem[orderitems].fCustomerSteelRate = 0.0;
																		orderitem[orderitems].finishedweight = 0.0;
																		orderitem[orderitems].freightcostInCents = 0;
																		orderitem[orderitems].ispart = 0;
																		orderitem[orderitems].line =
																			++(order[i].maxItemNumberUsed);
																		orderitem[orderitems].nitridecostInCents = 0;
																		orderitem[orderitems].note[0] = '\0';
																		orderitem[orderitems].options = 0;
																		orderitem[orderitems].orderIndex = i;
																		orderitem[orderitems].ordernumber =
																			order[i].ordernumber;
																		strcpy(orderitem[orderitems].prefix,
																			"MI");
																		strcpy(orderitem[orderitems].suffix,
																			"FAST TRACK");
																		orderitem[orderitems].priceInCents =
																			order[i].fasttrackchargeInCents; 
																		orderitem[orderitems].qty = 1.0;
																		double dSubtotalTemp;
																		dSubtotalTemp = ((double) orderitem[orderitems].priceInCents) * orderitem[orderitems].qty;
																		if (dSubtotalTemp >= 0.0) {
																			order[i].subtotalInCents += (int) (dSubtotalTemp + 0.5);
																		}
																		else {
																			order[i].subtotalInCents += (int) (dSubtotalTemp - 0.5);
																		}
																		orderitem[orderitems].roughweight = 0.0;
																		orderitem[orderitems].steelcostInCents = 0;
																		++orderitems;
																	} // if (...fasttrack)

																	// Add shelf order item, if necessary
																	if (order[i].shelforder) {
																		orderitem[orderitems].chargenitride = 0;
																		orderitem[orderitems].cmsFastTrack = 0;
																		orderitem[orderitems].cmsSteel = 0;
																		strcpy(orderitem[orderitems].description,
																			"SHELF");
																		orderitem[orderitems].dienumber[0] = '\0';
																		orderitem[orderitems].fCustomerNitrideRate = 0.0;
																		orderitem[orderitems].fCustomerSteelRate = 0.0;
																		orderitem[orderitems].finishedweight = 0.0;
																		orderitem[orderitems].freightcostInCents = 0;
																		orderitem[orderitems].ispart = 0;
																		orderitem[orderitems].line =
																			++(order[i].maxItemNumberUsed);
																		orderitem[orderitems].nitridecostInCents = 0;
																		orderitem[orderitems].note[0] = '\0';
																		orderitem[orderitems].options = 0;
																		orderitem[orderitems].orderIndex = i;
																		orderitem[orderitems].ordernumber =
																			order[i].ordernumber;
																		strcpy(orderitem[orderitems].prefix,
																			"MI");
																		strcpy(orderitem[orderitems].suffix,
																			"SHELF");
																		orderitem[orderitems].priceInCents = 0;
																		orderitem[orderitems].qty = 1.0;
																		orderitem[orderitems].roughweight = 0.0;
																		orderitem[orderitems].steelcostInCents = 0;
																		++orderitems;
																	} // if (...shelforder)

																	// Add rush order item, if necessary
																	if (order[i].priority) {
																		orderitem[orderitems].chargenitride = 0;
																		orderitem[orderitems].cmsFastTrack = 0;
																		orderitem[orderitems].cmsSteel = 0;
																		strcpy(orderitem[orderitems].description,
																			"RUSH");
																		orderitem[orderitems].dienumber[0] = '\0';
																		orderitem[orderitems].fCustomerNitrideRate = 0.0;
																		orderitem[orderitems].fCustomerSteelRate = 0.0;
																		orderitem[orderitems].finishedweight = 0.0;
																		orderitem[orderitems].freightcostInCents = 0;
																		orderitem[orderitems].ispart = 0;
																		orderitem[orderitems].line =
																			++(order[i].maxItemNumberUsed);
																		orderitem[orderitems].nitridecostInCents = 0;
																		orderitem[orderitems].note[0] = '\0';
																		orderitem[orderitems].options = 0;
																		orderitem[orderitems].orderIndex = i;
																		orderitem[orderitems].ordernumber =
																			order[i].ordernumber;
																		strcpy(orderitem[orderitems].prefix,
																			"MI");
																		strcpy(orderitem[orderitems].suffix,
																			"RUSH");
																		orderitem[orderitems].priceInCents = 0;
																		orderitem[orderitems].qty = 1.0;
																		orderitem[orderitems].roughweight = 0.0;
																		orderitem[orderitems].steelcostInCents = 0;
																		++orderitems;
																	} // if (...priority)

																	// Add package discount order item, if necessary
																	if (order[i].packageDiscount) {
																		orderitem[orderitems].chargenitride = 0;
																		orderitem[orderitems].cmsFastTrack = 0;
																		orderitem[orderitems].cmsSteel = 0;
																		strcpy(orderitem[orderitems].description,
																			"DISCOUNT");
																		orderitem[orderitems].dienumber[0] = '\0';
																		orderitem[orderitems].fCustomerNitrideRate = 0.0;
																		orderitem[orderitems].fCustomerSteelRate = 0.0;
																		orderitem[orderitems].finishedweight = 0.0;
																		orderitem[orderitems].freightcostInCents = 0;
																		orderitem[orderitems].ispart = 0;
																		orderitem[orderitems].line =
																			++(order[i].maxItemNumberUsed);
																		orderitem[orderitems].nitridecostInCents = 0;
																		orderitem[orderitems].note[0] = '\0';
																		orderitem[orderitems].options = 0;
																		orderitem[orderitems].orderIndex = i;
																		orderitem[orderitems].ordernumber =
																			order[i].ordernumber;
																		strcpy(orderitem[orderitems].prefix,
																			"MI");
																		strcpy(orderitem[orderitems].suffix,
																			"DISCOUNT");
																		orderitem[orderitems].priceInCents =
																			order[i].packageDiscountInCents; 
																		orderitem[orderitems].qty = 1.0;
																		double dSubtotalInCents;
																		dSubtotalInCents = ((double) orderitem[orderitems].priceInCents) * orderitem[orderitems].qty;
																		if (dSubtotalInCents >= 0.0) {
																			order[i].subtotalInCents += (int) (dSubtotalInCents + 0.5);
																		}
																		else {
																			order[i].subtotalInCents += (int) (dSubtotalInCents - 0.5);
																		}
																		orderitem[orderitems].roughweight = 0.0;
																		orderitem[orderitems].steelcostInCents = 0;
																		++orderitems;
																	} // if (...packageDiscount)

																	// Add "order note" order item, if necessary
																	if (order[i].note[0]) {
																		orderitem[orderitems].chargenitride = 0;
																		orderitem[orderitems].cmsFastTrack = 0;
																		orderitem[orderitems].cmsSteel = 0;
																		strcpy(orderitem[orderitems].description,
																			order[i].note);
																		orderitem[orderitems].dienumber[0] = '\0';
																		orderitem[orderitems].fCustomerNitrideRate = 0.0;
																		orderitem[orderitems].fCustomerSteelRate = 0.0;
																		orderitem[orderitems].finishedweight = 0.0;
																		orderitem[orderitems].freightcostInCents = 0;
																		orderitem[orderitems].ispart = 0;
																		orderitem[orderitems].line =
																			++(order[i].maxItemNumberUsed);
																		orderitem[orderitems].nitridecostInCents = 0;
																		orderitem[orderitems].note[0] = '\0';
																		orderitem[orderitems].options = 0;
																		orderitem[orderitems].orderIndex = i;
																		orderitem[orderitems].ordernumber =
																			order[i].ordernumber;
																		strcpy(orderitem[orderitems].prefix,
																			"MI");
																		strcpy(orderitem[orderitems].suffix,
																			"NOTE");
																		orderitem[orderitems].priceInCents = 0;
																		orderitem[orderitems].qty = 1.0;
																		orderitem[orderitems].roughweight = 0.0;
																		orderitem[orderitems].steelcostInCents = 0;
																		++orderitems;
																	} // if ("order note")

																	SQLFreeStmt(stmtCMS, SQL_CLOSE);
																} // for (i...)

																g_nPointNumber = 7;
																// Make a pass over the orderitems to ensure that each
																// order has as its first "part" type item
																// an item with line number 1.
																// This is to cope with the fact that Solarsoft does
																// NOT renumber line items when a line is deleted.
																// For each order i:
																//		lineFound = false
																//		partLineFound = false
																//		For each line j in order i
																//			lineFound = true
																//			lineToBeLineOne = j
																//			if line j is part
																//				partLineFound = true
																//				lineToBeLineOne = j
																//				break; // inner for
																//		End for
																//		if lineFound 
																//			line lineToBeLineOne.linenumber = 1
																// End for	
																int bPartLineFound, nLineToBeLineOne;
																nPreviousOrderNumber = DUMMY_ORDER_NUMBER;
																for (j = 0; j < orderitems; j++) {
																	nCurrentOrderNumber = orderitem[j].ordernumber;
																	if (nCurrentOrderNumber != nPreviousOrderNumber) {
																		if (nPreviousOrderNumber != DUMMY_ORDER_NUMBER) {
																			if (bPartLineFound) {
																				if (orderitem[nLineToBeLineOne].line != 1) {
																					char szLineOneMessage[1024];
																					sprintf(szLineOneMessage,
																						"In order %d, remapping Solarsoft line %d to be decade order line 1",
																						nPreviousOrderNumber,
																						orderitem[nLineToBeLineOne].line);
																					LogInfo(g_hWndDialog, szLineOneMessage);
																					orderitem[nLineToBeLineOne].line = 1;
																				}
																			}
																		}
																		bPartLineFound = 0;
																		nPreviousOrderNumber = nCurrentOrderNumber;
																	}
																	if (bPartLineFound) {
																		continue;
																	}
																	nLineToBeLineOne = j;
																	if (orderitem[j].ispart) {
																		bPartLineFound = 1;
																	}
																} // (for j...)

																// Store updates into Decade DB
																// 2010-07-06 DW: no pruning of updates is done if 
																// updateRequestOrderNumbers (such as shipped 
																// or invoiced order) -- it is assumed you really
																// mean it if you ask for an update of a given
																// order number!
																long int bImportedOrder;
																for (i = 0; i < orders; i++) {
																	// Prep the order for SQL INSERT:
																	EscapeSingleQuotes(order[i].customerpo);
																	EscapeSingleQuotes(order[i].shippingvendor);
																	EscapeSingleQuotes(order[i].baddress1);
																	EscapeSingleQuotes(order[i].baddress2);
																	EscapeSingleQuotes(order[i].baddress3);
																	EscapeSingleQuotes(order[i].baddress4);
																	EscapeSingleQuotes(order[i].bpostalcode);
																	EscapeSingleQuotes(order[i].saddress1);
																	EscapeSingleQuotes(order[i].saddress2);
																	EscapeSingleQuotes(order[i].saddress3);
																	EscapeSingleQuotes(order[i].saddress4);
																	EscapeSingleQuotes(order[i].spostalcode);
																	EscapeSingleQuotes(order[i].shipvia);
																	EscapeSingleQuotes(order[i].note);

																	SQLFreeStmt(stmt, SQL_CLOSE);
																	sprintf(statementText,
																		"SELECT ordernumber,shipdate,shelf,invoicedate FROM d_order WHERE ordernumber = %d",
																		order[i].ordernumber);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																	OutputDebugString("\n");
																	OutputDebugString(statementText);
																	returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
																		&nOrderNumber, 
																		sizeof(nOrderNumber),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 2, SQL_C_TIMESTAMP, 
																		&stDecadeShipDate, 
																		sizeof(stDecadeShipDate),
																		&sShippedIndicator);
																	returnValue = SQLBindCol(stmt, 3, SQL_C_ULONG, 
																		&lShelfFlag, 
																		sizeof(lShelfFlag),
																		&sNameLenOrInd);
																	returnValue = SQLBindCol(stmt, 4, SQL_C_TIMESTAMP, 
																		&stDecadeInvoiceDate, 
																		sizeof(stDecadeInvoiceDate),
																		&sInvoicedIndicator);
																	returnValue = SQLFetch(stmt);
																	if (returnValue == SQL_SUCCESS
																		|| returnValue == SQL_SUCCESS_WITH_INFO) {
#ifndef SHIPPED_REFRESH
																			if (sShippedIndicator != SQL_NULL_DATA
																				&& !updateRequestOrderNumbers) {
																					setOrderState(order[i].ordernumber, 1);
																					continue; // i.e. leave this order alone
																					// it is "shipped"
																			}
#endif
																			if (sInvoicedIndicator != SQL_NULL_DATA
																				&& !updateRequestOrderNumbers) {
																					setOrderState(order[i].ordernumber, 1);
																					continue; // i.e. leave this order alone
																					// it is invoiced
																			}
																			if ((order[i].cStatus == 'C'
																				|| order[i].cStatus == 'c')
																				&& !updateRequestOrderNumbers) {
																					setOrderState(order[i].ordernumber, 1);
																					continue; // do not update orders in
																					// Solarsoft's "complete" state
																			}
																			// doing an update of found order 
																			setOrderState(order[i].ordernumber, 0);
																			sprintf(statementText,
																				"UPDATE d_order SET ordernumber=%d,orderdate='%d-%02d-%02d %02d:%02d:%02d',customercode='%s',customerpo='%s',expshipdate='%d-%02d-%02d',total=%d.%02d,discountamount=%d.%02d,gst=%d.%02d,freight=%d.%02d,freightweight=%f,shippingvendor='%s',shopdate='%d-%02d-%02d',expreceiveddate='%d-%02d-%02d',onhold=%d,defaultfreight=%d,parts=0,baddress1='%s',baddress2='%s',baddress3='%s',baddress4='%s',bpostalcode='%s',saddress1='%s',saddress2='%s',saddress3='%s',saddress4='%s',spostalcode='%s',fasttrack=%d,priority=0,defaultnitride=1,nitride=0,combineprices=0,zeroprice=0,defaultsteelsurcharge=1,steelsurcharge=%d.%02d,steelrate=%f,shelforder=%d,stock=0,subtotal=%d.%02d,sales=%d.%02d,importedorder=1,ncr=%d,ncrs=%d,shipvia='%s',note='%s',employeenumber=%d WHERE ordernumber = %d",
																				order[i].ordernumber,
																				order[i].orderdate.year,
																				order[i].orderdate.month,
																				order[i].orderdate.day,
																				order[i].orderdate.hour,
																				order[i].orderdate.minute,
																				order[i].orderdate.second,
																				order[i].customercode,
																				order[i].customerpo,
																				order[i].expshipdate.year,
																				order[i].expshipdate.month,
																				order[i].expshipdate.day,
																				order[i].totalInCents / 100,
																				abs(order[i].totalInCents % 100),
																				order[i].discountAmountInCents / 100,
																				abs(order[i].discountAmountInCents % 100),
																				order[i].gstInCents / 100,
																				abs(order[i].gstInCents % 100),
																				order[i].freightInCents / 100,
																				abs(order[i].freightInCents % 100),
																				order[i].freightweight,
																				order[i].shippingvendor,
																				order[i].shopdate.year,
																				order[i].shopdate.month,
																				order[i].shopdate.day,
																				order[i].expreceiveddate.year,
																				order[i].expreceiveddate.month,
																				order[i].expreceiveddate.day,
																				order[i].onhold,
																				order[i].defaultfreight,
																				order[i].baddress1,
																				order[i].baddress2,
																				order[i].baddress3,
																				order[i].baddress4,
																				order[i].bpostalcode,
																				order[i].saddress1,
																				order[i].saddress2,
																				order[i].saddress3,
																				order[i].saddress4,
																				order[i].spostalcode,
																				order[i].fasttrack,
																				order[i].steelsurchargeInCents / 100,
																				abs(order[i].steelsurchargeInCents % 100),
																				order[i].steelrate,
																				order[i].shelforder,
																				order[i].subtotalInCents / 100,
																				abs(order[i].subtotalInCents % 100),
																				order[i].subtotalInCents / 100,
																				abs(order[i].subtotalInCents % 100),
																				0,  /*order[i].ncr,*/
																				0,  /*order[i].ncrs,*/
																				order[i].shipvia,
																				"", /*order[i].note,*/
																				0,   /*order[i].employeenumber*/
																				order[i].ordernumber);
																			SQLFreeStmt(stmt, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO
																				&& returnValue != SQL_NO_DATA) {
																					SetErrorIcon(g_hWndDialog, 1, "Error updating order");
																					OutputDebugString("\n");
																					OutputDebugString(statementText);
																			}
																	}
																	else {
																		// doing an insert
																		strcpy(statementPart,
																			"INSERT INTO d_order (ordernumber,orderdate,customercode,customerpo,expshipdate,total,discountamount,gst,freight,freightweight,shippingvendor,shopdate,expreceiveddate,onhold,defaultfreight,parts,baddress1,baddress2,baddress3,baddress4,bpostalcode,saddress1,saddress2,saddress3,saddress4,spostalcode,fasttrack,priority,defaultnitride,nitride,combineprices,zeroprice,defaultsteelsurcharge,steelsurcharge,steelrate,shelforder,stock,subtotal,sales,importedorder,ncr,ncrs,shipvia,note,employeenumber) VALUES ");
																		sprintf(statementText,
																			"%s(%d,'%d-%02d-%02d %02d:%02d:%02d','%s','%s','%d-%02d-%02d',%d.%02d,%d.%02d,%d.%02d,%d.%02d,%f,'%s','%d-%02d-%02d','%d-%02d-%02d',%d,%d,0,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%d,0,1,0,0,0,1,%d.%02d,%f,%d,0,%d.%02d,%d.%02d,1,%d,%d,'%s','%s',%d)",
																			statementPart,
																			order[i].ordernumber,
																			order[i].orderdate.year,
																			order[i].orderdate.month,
																			order[i].orderdate.day,
																			order[i].orderdate.hour,
																			order[i].orderdate.minute,
																			order[i].orderdate.second,
																			order[i].customercode,
																			order[i].customerpo,
																			order[i].expshipdate.year,
																			order[i].expshipdate.month,
																			order[i].expshipdate.day,
																			order[i].totalInCents / 100,
																			abs(order[i].totalInCents % 100),
																			order[i].discountAmountInCents / 100,
																			abs(order[i].discountAmountInCents % 100),
																			order[i].gstInCents / 100,
																			abs(order[i].gstInCents % 100),
																			order[i].freightInCents / 100,
																			abs(order[i].freightInCents % 100),
																			order[i].freightweight,
																			order[i].shippingvendor,
																			order[i].shopdate.year,
																			order[i].shopdate.month,
																			order[i].shopdate.day,
																			order[i].expreceiveddate.year,
																			order[i].expreceiveddate.month,
																			order[i].expreceiveddate.day,
																			order[i].onhold,
																			order[i].defaultfreight,
																			order[i].baddress1,
																			order[i].baddress2,
																			order[i].baddress3,
																			order[i].baddress4,
																			order[i].bpostalcode,
																			order[i].saddress1,
																			order[i].saddress2,
																			order[i].saddress3,
																			order[i].saddress4,
																			order[i].spostalcode,
																			order[i].fasttrack,
																			order[i].steelsurchargeInCents / 100,
																			abs(order[i].steelsurchargeInCents % 100),
																			order[i].steelrate,
																			order[i].shelforder,
																			order[i].subtotalInCents / 100,
																			abs(order[i].subtotalInCents % 100),
																			order[i].subtotalInCents / 100,
																			abs(order[i].subtotalInCents % 100),
																			0,  /*order[i].ncr,*/
																			0,  /*order[i].ncrs,*/
																			order[i].shipvia,
																			"", /*order[i].note,*/
																			0   /*order[i].employeenumber*/);
																		SQLFreeStmt(stmt, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				SetErrorIcon(g_hWndDialog, 1, "Error inserting order");
																				OutputDebugString("\n");
																				OutputDebugString(statementText);
																				OutputDebugString("\n");
																		}
																	} // else ... insert

#				ifdef WRITE_CAM_FILE
																	if (order[i].firstOrderItem == -1) {
																		GenerateCAMFile(order[i].ordernumber,
																			order[i].customercode, order[i].shopdate,
																			"", 0, 0, "", 0, 0,
																			"", "", "");
																	}
																	else {
																		GenerateCAMFile(order[i].ordernumber,
																			order[i].customercode, order[i].shopdate,
																			orderitem[order[i].firstOrderItem].dienumber,
																			order[i].orderItems, orderitem[order[i].firstOrderItem].nCavities,
																			orderitem[order[i].firstOrderItem].location,
																			order[i].hasNitrideItem, order[i].hasSkimCutItem,
																			order[i].backerNumber, order[i].backerLocation, 
																			order[i].feederNumber);
																	}
#				endif

																} // for (i...) 
																nPreviousOrderNumber = DUMMY_ORDER_NUMBER;
																struct fetchedOrderItemDescriptor {
																	int line;    
																	int updated;
																	int shipped;
																} fetchedOrderItem[MAX_ITEMS_PER_ORDER];
																int fetchedOrderItems;
																extraChargeItems = 0; // NOT USED AT PRESENT, but if
																// not zeroed it trips code
																// at for (i = orderitems; i < orderitems+extraChargeItems...

																g_nPointNumber = 8;
																for (i = 0; i < orderitems; i++) {
																	// DW DDD DEBUG
																	if (orderitem[i].ordernumber == 252535) {
																		int ijk = 12345;
																	}
																	if (getOrderState(orderitem[i].ordernumber)) {
																		// this order is untouchable (e.g. shipped)
																		continue; // for
																	}
																	// scan options to set
																	// number of holes, and to generate additional
																	// MI orderitems for extra charge features
																	char szSupplement[32];
																	extraChargeItems = 0;
																	for (int j = 0; j < orderitem[i].options; j++) {
																		pOption = orderitem[i].option + j;
																		switch (pOption->featureType) {
																		case FEATURE_CAVITIES:
																			if (orderitem[i].ispart) {
																				sprintf(szSupplement, " (%d CAV)", pOption->quantity);
																				// insert szSupplement just prior to "<2>" mark, or at
																				// end of description if none
																				char *pTwo;
																				pTwo = strstr(orderitem[i].description, "<2>");
																				if (pTwo == NULL) {
																					strcat(orderitem[i].description, szSupplement);
																				}
																				else {
																					char szTail[1024];
																					strcpy(szTail, pTwo);
																					orderitem[i].description[(pTwo - orderitem[i].description)] = '\0';
																					strcat(orderitem[i].description, " ");
																					strcat(orderitem[i].description, szSupplement);
																					strcat(orderitem[i].description, szTail);
																				}
																			}
																			if (strlen(orderitem[i].suffix) >= 2) {
																				orderitem[i].suffix[strlen(orderitem[i].suffix)-2]
																				= pOption->quantity / 10 + '0';
																				orderitem[i].suffix[strlen(orderitem[i].suffix)-1]
																				= pOption->quantity % 10 + '0';
																			}
																			break;
																		default:
																			break;
																		} // switch
																	} // for (int j...)
																	// do an insert
																	nCurrentOrderNumber = orderitem[i].ordernumber;
																	if (nCurrentOrderNumber != nPreviousOrderNumber) {
																		if (nPreviousOrderNumber != DUMMY_ORDER_NUMBER) {
																			// delete any un-updated lines
																			for (int k = 0; k < fetchedOrderItems; k++) {
																				if (!fetchedOrderItem[k].updated) {
																					sprintf(statementText,
																						"DELETE FROM d_orderitem WHERE ordernumber = %d AND line = %d",
																						nPreviousOrderNumber,
																						fetchedOrderItem[k].line);
																					SQLFreeStmt(stmt, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmt, 
																						(SQLTCHAR *) statementText, 
																						strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							char szWarning[1024];
																							sprintf(szWarning,
																								"Cannot delete unupdated, fetched item %d (line %d) for order %d",
																								k, fetchedOrderItem[k].line, nPreviousOrderNumber);
																							LogError(g_hWndDialog, szWarning);
																					}
																				} // if (!...updated)
																			} // for (int k...)
																		} // if (nPrevious...
																		nPreviousOrderNumber = nCurrentOrderNumber;
																		// fill fetchedOrderItem from the decade database	
																		SQLFreeStmt(stmt, SQL_CLOSE);
																		sprintf(statementText,
																			"SELECT line,shipdate FROM d_order,d_orderitem WHERE d_order.ordernumber = d_orderitem.ordernumber AND d_order.ordernumber = %d",
																			orderitem[i].ordernumber);
																		returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				char szWarning[1024];
																				sprintf(szWarning,
																					"Cannot fetch decade order items for order %d",
																					orderitem[i].ordernumber);
																				LogError(g_hWndDialog, szWarning);
																		}
																		returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
																			&nLine, 
																			sizeof(nLine),
																			&sNameLenOrInd);
																		returnValue = SQLBindCol(stmt, 2, SQL_C_TIMESTAMP, 
																			&stDecadeShipDate, 
																			sizeof(stDecadeShipDate),
																			&sShippedIndicator);
																		fetchedOrderItems = 0;
																		bImportedOrder = 0;
																		do {
																			returnValue = SQLFetch(stmt);
																			if (returnValue == SQL_SUCCESS
																				|| returnValue == SQL_SUCCESS_WITH_INFO) {
																					fetchedOrderItem[fetchedOrderItems].updated = 0;
																					fetchedOrderItem[fetchedOrderItems].line = nLine;
																					fetchedOrderItem[fetchedOrderItems].shipped = (sShippedIndicator != SQL_NULL_DATA);
																					++fetchedOrderItems;
																			}
																			else {
																				break;
																			}
																		} while (1);
																	} // if (...Current... != ...Previous...)

																	char szDescriptionAndNotes[1024];
																	int availableSpace;
																	strcpy(szDescriptionAndNotes, orderitem[i].description);
																	if (orderitem[i].note[0]) {
																		if (strlen(szDescriptionAndNotes) + 2 < FULL_DESCRIPTION_LENGTH) {
																			strcat(szDescriptionAndNotes, " ");
																		}
																		availableSpace = FULL_DESCRIPTION_LENGTH 
																			- strlen(szDescriptionAndNotes) - 1;
																		if (availableSpace < (int) strlen(orderitem[i].note)) {
																			strncat(szDescriptionAndNotes, 
																				orderitem[i].note, 
																				availableSpace);
																			szDescriptionAndNotes[FULL_DESCRIPTION_LENGTH-1] = '\0';
																		}	
																		else {
																			strcat(szDescriptionAndNotes,
																				orderitem[i].note);
																		}
																	}
																	EscapeSingleQuotes(szDescriptionAndNotes);
																	EscapeSingleQuotes(orderitem[i].dienumber);
																	EscapeSingleQuotes(orderitem[i].location);

																	// try to find the current (ordernumber, line)
																	// among the fetchedOrderItem's
																	int bItemFound = 0;
																	int oi;
																	for (oi = 0; oi < fetchedOrderItems; oi++) {
																		if (fetchedOrderItem[oi].line == orderitem[i].line) {
																			bItemFound = 1;
																			break;
																		}
																	} // for (oi...)
																	if (bItemFound) {
																		fetchedOrderItem[oi].updated = 1;
																		// regardless of whether update done or not,
																		// do NOT delete order
																		if (!fetchedOrderItem[oi].shipped) {
																			// do an update
																			sprintf(statementText,
																				"UPDATE d_orderitem SET ordernumber=%d,line=%d,prefix='%s',suffix='%s',qty=%f,description='%s',dienumber='%s',price=%d.%02d,chargenitride=%d,steelcost=%d.%02d,roughweight=%f,location='%s' WHERE ordernumber = %d AND line = %d",
																				orderitem[i].ordernumber,
																				orderitem[i].line,
																				orderitem[i].prefix,
																				orderitem[i].suffix,
																				orderitem[i].qty,
																				szDescriptionAndNotes,
																				orderitem[i].dienumber,
																				orderitem[i].priceInCents / 100,
																				abs(orderitem[i].priceInCents % 100),
																				orderitem[i].chargenitride,
																				orderitem[i].steelcostInCents / 100,
																				abs(orderitem[i].steelcostInCents % 100),
																				orderitem[i].roughweight,
																				orderitem[i].location,
																				orderitem[i].ordernumber,
																				orderitem[i].line);
																			SQLFreeStmt(stmt, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																			if (returnValue != SQL_SUCCESS
																				&& returnValue != SQL_SUCCESS_WITH_INFO) {
																					char szErrorMsg[4096];
																					sprintf(szErrorMsg, "Error updating order item. SQL is: |%s|",
																						statementText);
																					LogError(g_hWndDialog, szErrorMsg);
																			}
																		}
																	}
																	else {
																		// do an insert
																		strcpy(statementPart,
																			"INSERT INTO d_orderitem (ordernumber,line,prefix,suffix,qty,description,dienumber,price,chargenitride,steelcost,roughweight,location) VALUES ");
																		sprintf(statementText,
																			"%s(%d,%d,'%s','%s',%f,'%s','%s',%d.%02d,%d,%d.%02d,%f,'%s')",
																			statementPart,
																			orderitem[i].ordernumber,
																			orderitem[i].line,
																			orderitem[i].prefix,
																			orderitem[i].suffix,
																			orderitem[i].qty,
																			szDescriptionAndNotes,
																			orderitem[i].dienumber,
																			orderitem[i].priceInCents / 100,
																			abs(orderitem[i].priceInCents % 100),
																			orderitem[i].chargenitride,
																			orderitem[i].steelcostInCents / 100,
																			abs(orderitem[i].steelcostInCents % 100),
																			orderitem[i].roughweight,
																			orderitem[i].location);
																		SQLFreeStmt(stmt, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				char szErrorDump[4096];
																				sprintf(szErrorDump, "Error inserting oi. SQL: |%s|",
																					statementText);
																				LogError(g_hWndDialog, szErrorDump);
																		}
																	}

																} // for (i...)

																g_nPointNumber = 9;

																// Clean up last d_orderitem set
																if (nPreviousOrderNumber != DUMMY_ORDER_NUMBER) {
																	if (!getOrderState(nPreviousOrderNumber)) {
																		// delete any un-updated lines
																		for (int k = 0; k < fetchedOrderItems; k++) {
																			if (!fetchedOrderItem[k].updated) {
																				sprintf(statementText,
																					"DELETE FROM d_orderitem WHERE ordernumber = %d AND line = %d",
																					nPreviousOrderNumber,
																					fetchedOrderItem[k].line);
																				SQLFreeStmt(stmt, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmt, 
																					(SQLTCHAR *) statementText, 
																					strlen(statementText));
																				if (returnValue != SQL_SUCCESS
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						char szWarning[1024];
																						sprintf(szWarning,
																							"Cannot delete unupdated, fetched item %d (line %d) for order %d",
																							k, fetchedOrderItem[k].line, nPreviousOrderNumber);
																						LogError(g_hWndDialog, szWarning);
																				}
																			} // if (!...updated)
																		} // for (int k...)
																	} // if (!get...)
																} // if (nPrevious...	

																// NOTE!: extraChargeItems always zero, with present code.
																for (i = orderitems; i < orderitems + extraChargeItems; i++) {
																	// Write out the newly generated MI orderitems
																	strcpy(statementPart,
																		"INSERT INTO d_orderitem (ordernumber,line,prefix,suffix,qty,description,dienumber,price,chargenitride,steelcost,roughweight) VALUES ");
																	EscapeSingleQuotes(orderitem[i].description);
																	EscapeSingleQuotes(orderitem[i].dienumber);
																	sprintf(statementText,
																		"%s(%d,%d,'%s','%s',%f,'%s','%s',%d.%02d,%d,%d.%02d,%f)",
																		statementPart,
																		orderitem[i].ordernumber,
																		orderitem[i].line,
																		orderitem[i].prefix,
																		orderitem[i].suffix,
																		orderitem[i].qty,
																		orderitem[i].description,
																		orderitem[i].dienumber,
																		orderitem[i].priceInCents / 100,
																		abs(orderitem[i].priceInCents % 100),
																		orderitem[i].chargenitride,
																		orderitem[i].steelcostInCents / 100,
																		abs(orderitem[i].steelcostInCents % 100),
																		orderitem[i].roughweight);
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			LogError(g_hWndDialog, "Error inserting/updating order item");
																			OutputDebugString("\n");
																			OutputDebugString(statementText);
																	}
																} // for (i...)

																int nDeletedOrderNumber;

																// was, prior to inlining:
																//nDeletedOrderNumber = checkForOrderDeletions(); 
																// allocates and deallocates its own ODBC resources

																// inlined check for order deletions 
																long int lOrderNumber, lMinOrderNumber, lMaxOrderNumber;
																int d, s, found;

																nDeletedOrderNumber = DUMMY_ORDER_NUMBER;

																// select ordernumber from d_order 
																// where importedorder=1 and shipdate is null, ordered by ordernumber desc
																// and restricted to orderdate's in past 4 months
																// and find min and max ordernumber while filling
																// decadeOpenOrder[].
																// Leaving shelved orders out of this check, since to
																// obliterate one as a result of a fetch error
																// would reset the shelved status.
																strcpy(statementText, 
																	"SELECT ordernumber FROM d_order WHERE orderdate >= DATEADD(Month,-4,GETDATE()) AND importedorder = 1 AND shipdate IS NULL AND shelf = 0 ORDER BY ordernumber DESC");
																SQLFreeStmt(stmt, SQL_CLOSE);
																returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																returnValue = SQLBindCol(stmt, 1, SQL_C_ULONG, 
																	&lOrderNumber, 
																	sizeof(lOrderNumber),
																	&sNameLenOrInd);
																decadeOpenOrders = 0;
																lMinOrderNumber = 10000000;
																lMaxOrderNumber = 0;
																do {
																	returnValue = SQLFetch(stmt);
																	if (returnValue != SQL_SUCCESS 
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			break; // do
																	}
																	if (lOrderNumber < lMinOrderNumber) {
																		lMinOrderNumber = lOrderNumber;
																	}
																	if (lOrderNumber > lMaxOrderNumber) {
																		lMaxOrderNumber = lOrderNumber;
																	}
																	decadeOpenOrder[decadeOpenOrders++] = lOrderNumber;
																} while (1);

																sprintf(statementText, 
																	"SELECT DCORD# FROM %s.OCRH WHERE DCORD# >= %ld AND DCORD# <= %ld ORDER BY DCORD# DESC",
																	CMS_DATABASE_NAME, lMinOrderNumber, lMaxOrderNumber);
																SQLFreeStmt(stmtCMS, SQL_CLOSE);
																returnValue = SQLExecDirect(stmtCMS, (SQLTCHAR *) statementText, strlen(statementText));
																if (returnValue != SQL_SUCCESS 
																	&& returnValue != SQL_SUCCESS_WITH_INFO) {
																		// do nothing, we're not connected!
																		nDeletedOrderNumber = DUMMY_ORDER_NUMBER;
																}
																else {
																	returnValue = SQLBindCol(stmtCMS, 1, SQL_C_ULONG, 
																		&lOrderNumber, 
																		sizeof(lOrderNumber),
																		&sNameLenOrInd);
																	solarsoftOrders = 0;
																	do {
																		returnValue = SQLFetch(stmtCMS);
																		if (returnValue != SQL_SUCCESS 
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				break; // do
																		}
																		solarsoftOrder[solarsoftOrders++] = lOrderNumber;
																	} while (1);
																	// For each in decadeOpenOrder[], find in solarsoftOrder[]
																	// or delete one and return.
																	s = 0;
																	for (d = 0; d < decadeOpenOrders; d++) {
																		// seek decadeOpenOrder[d] in solarsoftOrder[], from
																		// position s onwards (since vectors are ordered)
																		found = 0;
																		do {
																			if (s >= solarsoftOrders) {
																				// no more numbers, it isn't there
																				break; // do
																			}
																			if (decadeOpenOrder[d] == solarsoftOrder[s]) {
																				found = 1;
																				break; // do
																			}
																			if (decadeOpenOrder[d] > solarsoftOrder[s]) {
																				// it isn't there
																				break; // do
																			}
																			++s;
																		} while (1);

																		if (!found) {
																			// delete the order from decade d_order and d_orderitem

																			sprintf(statementText,
																				"DELETE FROM d_orderitem WHERE ordernumber = %d",
																				decadeOpenOrder[d]);
																			SQLFreeStmt(stmt, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmt, 
																				(SQLTCHAR *) statementText, 
																				strlen(statementText));
																			sprintf(statementText,
																				"DELETE FROM d_order WHERE ordernumber = %d",
																				decadeOpenOrder[d]);
																			SQLFreeStmt(stmt, SQL_CLOSE);
																			returnValue = SQLExecDirect(stmt, 
																				(SQLTCHAR *) statementText, 
																				strlen(statementText));

																			nDeletedOrderNumber = decadeOpenOrder[d];
																			// DW 20090708 added break;
																			// Want no more than one deletion per update
																			break; // for (d...)
																		} // if (!found)
																	} // for (d...)
																} // else

																// end of inlined check for order deletions

#		ifdef ORDER_MIRROR
																if (bOrderMirroring) {
																	// do a cross-check between ORDER_MIRROR and CMS_DATABASE_NAME for
																	// order deletions. Checking OCRH, OCRI, OCRIE, FOOD. This will leave a few orphans
																	// in secondary tables, with negligible effect, I hope.
																	sprintf(statementText, 
																		"DELETE FROM %s.OCRH AS T1 WHERE NOT EXISTS (SELECT %s.OCRH.DCORD# FROM %s.OCRH WHERE %s.OCRH.DCORD# = T1.DCORD#)",
																		ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																		CMS_DATABASE_NAME);
																	SQLFreeStmt(stmtMirror, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO
																		&& returnValue != SQL_NO_DATA) {
																			LogError(g_hWndDialog, "Error executing OCRH deletion check");
																			sprintf(errorMessage,
																				"Statement was |%s|", statementText);
																			LogError(g_hWndDialog, errorMessage);
																	}

																	sprintf(statementText, 
																		"DELETE FROM %s.OCRI AS T1 WHERE NOT EXISTS (SELECT %s.OCRI.DDORD# FROM %s.OCRI WHERE %s.OCRI.DDORD# = T1.DDORD# AND %s.OCRI.DDITM# = T1.DDITM#)",
																		ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																		CMS_DATABASE_NAME, CMS_DATABASE_NAME); // does all items at once.
																	SQLFreeStmt(stmtMirror, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO
																		&& returnValue != SQL_NO_DATA) {
																			LogError(g_hWndDialog, "Error executing OCRI deletion check");
																			sprintf(errorMessage,
																				"Statement was |%s|", statementText);
																			LogError(g_hWndDialog, errorMessage);
																	}

																	sprintf(statementText, 
																		"DELETE FROM %s.OCRIE AS T1 WHERE NOT EXISTS (SELECT %s.OCRIE.DDORD# FROM %s.OCRIE WHERE %s.OCRIE.DDORD# = T1.DDORD#)",
																		ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																		CMS_DATABASE_NAME);
																	SQLFreeStmt(stmtMirror, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO
																		&& returnValue != SQL_NO_DATA) {
																			LogError(g_hWndDialog, "Error executing OCRIE deletion check");
																			sprintf(errorMessage,
																				"Statement was |%s|", statementText);
																			LogError(g_hWndDialog, errorMessage);
																	}

																	sprintf(statementText, 
																		"DELETE FROM %s.FOOD AS T1 WHERE NOT EXISTS (SELECT %s.FOOD.R0LSTN FROM %s.FOOD WHERE %s.FOOD.R0LSTN = T1.R0LSTN AND %s.FOOD.R0FCDE = T1.R0FCDE AND %s.FOOD.R0OCDE = T1.R0OCDE)",
																		ORDER_MIRROR, CMS_DATABASE_NAME, CMS_DATABASE_NAME,
																		CMS_DATABASE_NAME, CMS_DATABASE_NAME, CMS_DATABASE_NAME);
																	SQLFreeStmt(stmtMirror, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtMirror, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO
																		&& returnValue != SQL_NO_DATA) {
																			LogError(g_hWndDialog, "Error executing FOOD deletion check");
																			sprintf(errorMessage,
																				"Statement was |%s|", statementText);
																			LogError(g_hWndDialog, errorMessage);
																	}
																}
#		endif

																lShipCountInUpdate = 0;
																if (!updateRequestOrderNumbers) {
																	// Check for Solarsoft shipping events requiring an update to
																	// the Decade shipdate field:
																	sprintf(statementText,
																		"SELECT FEORD#,FESDAT FROM %s.BOLH WHERE FESDAT >= '%s' AND FEPLTC = '%s'",
																		CMS_DATABASE_NAME, fromTimeDateOnly, PLANT_CODE); 						
																	SQLFreeStmt(stmtBOLH, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmtBOLH, (SQLTCHAR *) statementText, strlen(statementText));
																	if (returnValue == SQL_SUCCESS
																		|| returnValue == SQL_SUCCESS_WITH_INFO) {
																			unsigned long shippedOrderNumber;
																			TIMESTAMP_STRUCT tsCMSShipDate, tsDecadeShipDate;

																			returnValue = SQLBindCol(stmtBOLH, 1, SQL_C_ULONG, 
																				&shippedOrderNumber, 
																				sizeof(shippedOrderNumber),
																				&sNameLenOrInd);
																			returnValue = SQLBindCol(stmtBOLH, 2, SQL_C_TYPE_TIMESTAMP, 
																				&tsCMSShipDate, 
																				sizeof(tsCMSShipDate),
																				&sNameLenOrInd);
																			do {
																				returnValue = SQLFetch(stmtBOLH);
																				if (returnValue != SQL_SUCCESS 
																					&& returnValue != SQL_SUCCESS_WITH_INFO) {
																						break;
																				}
																				++lShipCountInUpdate;
																				// See whether decade shipdate exists already
																				tsDecadeShipDate.year = 1900;
																				tsDecadeShipDate.month = 1;
																				tsDecadeShipDate.day = 1;
																				sprintf(statementText, "SELECT shipdate from d_order WHERE ordernumber = %ld",
																					shippedOrderNumber);
																				SQLFreeStmt(stmt, SQL_CLOSE);
																				returnValue = SQLExecDirect(stmt, 
																					(SQLTCHAR *) statementText, 
																					strlen(statementText));
																				if (returnValue != SQL_SUCCESS && returnValue != SQL_SUCCESS_WITH_INFO) {
																					sprintf(errorMessage, "Unable to fetch Decade order %ld for ship date update", shippedOrderNumber);
																					LogError(g_hWndDialog, errorMessage);
																				}
																				returnValue = SQLBindCol(stmt, 1, SQL_C_TYPE_TIMESTAMP,
																					&tsDecadeShipDate,
																					sizeof(tsDecadeShipDate),
																					&sNameLenOrInd);
																				returnValue = SQLFetch(stmt);
																				if (returnValue == SQL_SUCCESS 
																					|| returnValue == SQL_SUCCESS_WITH_INFO) {
																						if (tsDecadeShipDate.year == tsCMSShipDate.year
																							&& tsDecadeShipDate.month == tsCMSShipDate.month
																							&& tsDecadeShipDate.day == tsCMSShipDate.day) {
																								// nothing need be done with this record
																								continue;
																						}
																						// else, decade record exists but disagrees on date.
																						// Update it.
																						sprintf(statementText, 
																							"UPDATE d_order SET shipdate = '%d-%02d-%02d %02d:%02d:%02d' WHERE ordernumber = %ld",
																							tsCMSShipDate.year, tsCMSShipDate.month, tsCMSShipDate.day,
																							stToTime.hour, stToTime.minute, stToTime.second, shippedOrderNumber);
																						SQLFreeStmt(stmt, SQL_CLOSE);
																						returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																						if (returnValue != SQL_SUCCESS
																							&& returnValue != SQL_SUCCESS_WITH_INFO) {
																								sprintf(errorMessage, 
																									"Unable to update decade ship date (branch 0), order %ld, statement '%s'",
																									shippedOrderNumber, statementText);
																								LogError(g_hWndDialog, errorMessage);
																						}
																				}
																				else {
																					// Try to update decade ship date anyway.
																					sprintf(statementText, 
																						"UPDATE d_order SET shipdate = '%d-%02d-%02d %02d:%02d:%02d' WHERE ordernumber = %ld",
																						tsCMSShipDate.year, tsCMSShipDate.month, tsCMSShipDate.day,
																						stToTime.hour, stToTime.minute, stToTime.second, shippedOrderNumber);
																					SQLFreeStmt(stmt, SQL_CLOSE);
																					returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																					if (returnValue != SQL_SUCCESS
																						&& returnValue != SQL_SUCCESS_WITH_INFO) {
																							sprintf(errorMessage, 
																								"Unable to update decade ship date (branch 1), order %ld statement '%s'",
																								shippedOrderNumber, statementText);
																							LogError(g_hWndDialog, errorMessage);
																					}
																				}

																			} while (1);
																	} // if successful SELECT on BOLH
																} // if (!updateRequestOrderNumbers)
																if (updateRequestOrderNumbers) {
																	// insert update time into d_updaterequest entries
																	for (i = 0; i < updateRequestOrderNumbers; i++) {
																		sprintf(statementText, 
																			"UPDATE d_updaterequest SET updatetime = '%d-%02d-%02d %02d:%02d:%02d' WHERE ordernumber = '%d'",
																			stToTime.year, stToTime.month, stToTime.day,
																			stToTime.hour, stToTime.minute, stToTime.second,
																			updateRequestOrderNumber[i]);
																		SQLFreeStmt(stmt, SQL_CLOSE);
																		returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));
																		if (returnValue != SQL_SUCCESS
																			&& returnValue != SQL_SUCCESS_WITH_INFO) {
																				char szError[1024];
																				sprintf(szError, "Unable to update d_updaterequest order number %d",
																					updateRequestOrderNumber[i]);
																				LogError(g_hWndDialog, szError);
																		}

																	} // for (i...0
																}
																else {
																	// Update Decade's d_updatetime table
																	int lastStableOrder;
																	if (nDeletedOrderNumber != DUMMY_ORDER_NUMBER) {
																		// DW 20090708 COMMENTED OUT:
																		// lastStableOrder = nDeletedOrderNumber - 1;
																		// we'll want to confirm the deletion on the
																		// next update cycle.
																		// NOW:
																		lastStableOrder = nToOrderNumber;

																		// Use LogInfo to log the deletion, to
																		// assess the behaviour of the new system
																		sprintf(szLogMessage, 
																			"Deleted order number %d in deletion check", 
																			nDeletedOrderNumber);
																		LogInfo(g_hWndDialog, szLogMessage);
																	}
																	else {
																		lastStableOrder = nToOrderNumber;
																	}
																	if (bNoLastUpdateInDB) {
																		sprintf(statementText,
																			"INSERT INTO d_updatetime (lastordernumber, lastupdate) VALUES (%d,'%d-%02d-%02d %02d:%02d:%02d')",
																			lastStableOrder,
																			stToTime.year, stToTime.month, stToTime.day,
																			stToTime.hour, stToTime.minute, stToTime.second);
																	}
																	else {
																		sprintf(statementText, 
																			"UPDATE d_updatetime SET lastordernumber=%d, lastupdate='%d-%02d-%02d %02d:%02d:%02d' ",
																			lastStableOrder,
																			stToTime.year, stToTime.month, stToTime.day,
																			stToTime.hour, stToTime.minute, stToTime.second);
																	}
																	SQLFreeStmt(stmt, SQL_CLOSE);
																	returnValue = SQLExecDirect(stmt, (SQLTCHAR *) statementText, strlen(statementText));

																	if (returnValue != SQL_SUCCESS
																		&& returnValue != SQL_SUCCESS_WITH_INFO) {
																			char szError[1024];
																			sprintf(szError, "Unable to update d_updatetime");
																			LogError(g_hWndDialog, szError);
																	}
																} // if (!updateRequestOrderNumbers)

																// disconnect from ODBC data sources, to free
																// (hopefully) all resources...
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtCMS);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtCUST);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtOCRS);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtOENOTE);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtOCRD);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtOCRF);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtUSRC);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtFOOD);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtBOLH);
#			ifdef ORDER_MIRROR
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtMirror);
																returnValue = SQLFreeHandle(SQL_HANDLE_STMT, stmtOCRO);
#			endif
																returnValue = SQLDisconnect(dbcCMS);
																returnValue = SQLFreeHandle(SQL_HANDLE_DBC, dbcCMS);
																returnValue = SQLDisconnect(dbc);
																returnValue = SQLFreeHandle(SQL_HANDLE_DBC, dbc);

																GetSystemTime(&tFinishTimeOfUpdate);

																if (lOrderCountInUpdate == 0) {
																	strcpy(fromOrderNumber, "NO RECENT ORDERS");
																	strcpy(toOrderNumber, "NO RECENT ORDERS");
																}
																else {
																	sprintf(fromOrderNumber, "%ld", lMinOrderNumberInUpdate);
																	sprintf(toOrderNumber, "%ld", lMaxOrderNumberInUpdate);
																}
																sprintf(orderCount, "%ld", lOrderCountInUpdate);
																sprintf(shipCount, "%ld", lShipCountInUpdate);
																GetTimeZoneInformation(&tz);
																SystemTimeToTzSpecificLocalTime(&tz, 
																	&tStartTimeOfUpdate, &tLocalTime);
																sprintf(fromTime, 
																	"%hd-%02hd-%02hd %02hd:%02hd:%02hd",
																	tLocalTime.wYear, tLocalTime.wMonth,
																	tLocalTime.wDay, tLocalTime.wHour,
																	tLocalTime.wMinute, tLocalTime.wSecond);

																SystemTimeToTzSpecificLocalTime(&tz, 
																	&tFinishTimeOfUpdate, &tLocalTime);
																sprintf(toTime, 
																	"%hd-%02hd-%02hd %02hd:%02hd:%02hd",
																	tLocalTime.wYear, tLocalTime.wMonth,
																	tLocalTime.wDay, tLocalTime.wHour,
																	tLocalTime.wMinute, tLocalTime.wSecond);

																SetDlgItemText(g_hWndDialog, IDC_FROM_TIME, fromTime);
																SetDlgItemText(g_hWndDialog, IDC_TO_TIME, toTime);
																SetDlgItemText(g_hWndDialog, IDC_FROM_ORDER,
																	fromOrderNumber);
																SetDlgItemText(g_hWndDialog, IDC_TO_ORDER, toOrderNumber);
																SetDlgItemText(g_hWndDialog, IDC_ORDER_COUNT, orderCount);
																SetDlgItemText(g_hWndDialog, IDC_SHIP_COUNT, shipCount);
																Sleep(PRE_IDLE_MESSAGE_DISPLAY_ALLOWANCE);
																SetDlgItemText(g_hWndDialog, IDC_STATUS_MESSAGE, "IDLE");

#		ifdef GOOD_NEWS_LOGGING
																sprintf(szLogMessage, 
																	"Updated %ld orders %ld shipments",
																	lOrderCountInUpdate, lShipCountInUpdate);
																LogInfo(g_hWndDialog, szLogMessage);
#		endif

															} // DoTheUpdate

															// --------------------end of DoTheUpdate------------------------

															//////////////////////////////////////////////////////////////////////
															// Construction/Destruction
															//////////////////////////////////////////////////////////////////////

															UpdateThread::UpdateThread()
															{
																SQLINTEGER version;
																SQLRETURN returnValue;

																// initialize ODBC environment
																g_env = NULL;
																returnValue = SQLAllocHandle(SQL_HANDLE_ENV, 
																	SQL_NULL_HANDLE, 
																	&g_env);
																if (returnValue != SQL_SUCCESS) {
																	LogError(g_hWndDialog, "Cannot open handle to Decade");
																}
																version = SQL_OV_ODBC3;
																returnValue = SQLSetEnvAttr(g_env, 
																	SQL_ATTR_ODBC_VERSION, 
																	(void *) version, 
																	0);
															}

															UpdateThread::~UpdateThread()
															{
																SQLRETURN returnValue;

																returnValue = SQLFreeHandle(SQL_HANDLE_ENV, g_env);
															}

															void UpdateThread::UpdateThreadLoop()
															{
																int updates;

																stopExecution = false;
																updates = 0;

																while (!stopExecution) {
																	DoTheUpdate();
																	++updates;
																	// wait a bit
																	Sleep(DB_INTERUPDATE_INTERVAL-PRE_IDLE_MESSAGE_DISPLAY_ALLOWANCE);
																} // while (!stopExecution) 

															} // UpdateThreadLoop

															DWORD WINAPI UpdateThread::LaunchUpdateThread(void *pInstance)
															{
																UpdateThread *p = (UpdateThread *) pInstance;

																p->UpdateThreadLoop();

																return false;
															}

															int UpdateThread::Start()
															{
																DWORD threadID;

																CreateThread(NULL, 0, LaunchUpdateThread, this, 0, &threadID);

																return false;
															}

															void UpdateThread::Stop()
															{
																stopExecution = true;
															}
