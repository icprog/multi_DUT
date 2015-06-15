
#ifndef AMBT_TEST_SYS_DEF_H
#define AMBT_TEST_SYS_DEF_H

#include "ATestIO.h"
#include "HashMapPara.h"

/*the version define rule:
Version: A.B.C.D
A. main version number (A - 1, N - 2, T - 3)
B. large version number(PT - 10, FT - 20, RC - 30)
C.version number(intial - 101) when little version increase 10,update the version number
D.little version number ()   when modify the code more then 10 then modify it.
tag. a - demo, b - demo range, NULL - release 
for example
A project    1.20.101.0
N project    2.30.101.0
T project    3.30.101.0
*/

#define SOFTWARE_VERSION	"2.30.1.1@"
#define DUT_NAME "NETGEAR"
#define AM_UI_IP "10.0.0.150"// use com with UI
#define AM_UI_PORT  10000    // use com with UI


// DUT informations 
typedef struct DUTInfoTag
{
	char DUTName[512];
	char DUTMO[256];
	char DUTSN[256];
	char DUTMAC1[256];
	char DUTMAC2[256];
	char DUTMAC3[256];
	char TestTime[50];
	char TestTimeCost[50];
	char TestDate[50];
	char MsgRes[256];
	char SSID2G[50];
	char SSID5G[50];
	char PassPhrase2G[50];
	char PassPhrase5G[50];
	//char TitleVersion[256];	
}DUT_INFO;


// Tester station informations
typedef struct TestStationInfoTag
{
	char TestStaName[256];
	int  TestStaSN;
	int  TestStaID;
	char TestProgramVersion[256];
	char UIVersion[100];
	char ManufactureLine[50];
	char Sector[50];
	char Post[50];
	char Area[50];
	char TesterPCName[100];
	char TesterPCIP[50];
	char TestLogPath[128];
	
}TEST_STATION_INFO;


// Tester station informations
typedef struct TestInputDataTag
{
	TEST_STATION_INFO TestStaInfo;
	DUT_INFO DUTInfo;
}TEST_INPUT_INFO;


//test result define
typedef struct TestResultTag
{
	//result define
	char ResultType[100];
	int  ResultFlag;
	char Result[2048];
	char ResultAim[2048];
	char ErrorCode[512];//for error code define
    char ErrorDes[2048];//for error code descript
}TEST_RESULT;

#define CMD_NUMBER 200
#define SFIS_USE_NUM 10    //090613 for sfis use number in test item

// data format define, use in rightlist show the Item detail information
typedef struct TestItemTag
{
	int  Num;// index the item show sequence
	int  RetryItemCount;
	CHashMapPara Para;
	//test result
    TEST_RESULT Result;
	
}TEST_ITEM;


// when entire system initilaztion, this config infomation will be dynamic load to GUI
typedef struct AmPROTLConfigTag
{
	char TestStaName[50];
	char TSysSoftVersion[50];
	char TestStaSN[128];
	char TestStaID[128];
	char DUTName[20];
	char FM_Version[50];
	char DUT_MODEL[50];	
}AM_PROTL_CONFIG;


enum TEST_FLAG_DEFINE
{
	TFLAG_SKIP,          
	TFLAG_FAIL_STOP,     
	TFLAG_FAIL_CONTINUE,
	TFLAG_FAIL_PAUSE,
	TFLAG_INI_RUN,//Run flag,the item will be perform when test initial
	TFLAG_END_RUN,//the item will be perform when all item be clear
	TFLAG_TERMINATE_RUN,//The item will be perform when test end,after show PASS/FAIL
};


enum TEST_RESULT_FLAG_DEFINE
{
	TEST_FAIL=0,
	TEST_PASS,
	TEST_COMMAD_ERROR,
	TEST_CONFIG_ERROR,
	NO_TEST,
	NO_CONNECT,
	NO_PARSER,
};

typedef struct SFISItemTag
{
	//test item ID define
	char Item[128];// index the item show sequence
	char Data[512];
}SFIS_ITEM;

//----------------------------------------------------------------------------------------
//Flag for whether to send data log of the test item to MYDAS
#define LOG_TO_MYDAS 1
#define NO_LOG_TO_MYDAS 0

//------------------------------------------------------------------------------------------
//parse flag table
#define SN                    "SN"//
#define ITEM_ID               "ITEM_ID"//
#define ITEM_DESCRIPT         "ITEM_DES"
#define DUT_CMD               "DUT_CMD"
#define ITEM_ENABLE_FALG      "FLAG"//test item disable or enable switch
#define PARALELL_FALG         "PARALELL_RUN"//set test item to parallel run
#define RETRY_FLAG            "RETRY_TIME"//Set test item fail and retry time 
#define RETRY_JUMP_ID_INDEX   "JUMP_ID_RETRY"// Set retry jump item id when test item retry
#define ITEM_ERR_CODE         "ERR_CODE"//
#define ITEM_ERR_CODE_DES     "ERR_CODE_DES"

//------------------------------------------------------------------------------------------

#endif
