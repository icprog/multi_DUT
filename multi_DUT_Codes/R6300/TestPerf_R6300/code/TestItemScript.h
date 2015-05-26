#ifndef TEST_ITEM_SCRIPT_H
#define TEST_ITEM_SCRIPT_H

#include "AmbitTestSysDef.h"
#include "AmbitExeCtrl.h"
#include "LEDCheck.h"
#include "Cylinder.h"

class CTestItemScript
{
public:
    CTestItemScript(void);
public:
    ~CTestItemScript(void);
	
public:
	/*Check the Led*/
	int RunLedTest(TEST_ITEM *pTI);
	
	/*Check DUT boot up*/
	int RunConnectionTest(TEST_ITEM *pTI);
	
	/*Check DUT SN with message from SFIS*/
	int RunSNTest(TEST_ITEM *pTI);
	
	/*Check 2G PassPhrase Rule*/
	int Run2gPassPhraseRuleTest(TEST_ITEM *pTI);
	
	/*Check 5G PassPhrase Rule*/
	int Run5gPassPhraseRuleTest(TEST_ITEM *pTI);
	
	/*Check MAC*/
	int RunLMACTest(TEST_ITEM *pTI);
	
	/*Check Pin code*/
	int RunPINTest(TEST_ITEM *pTI);
	
	/*Check 2G SSID*/
	int Run2gSSIDTest(TEST_ITEM *pTI);
	
	/*Check 5G SSID*/
	int Run5gSSIDTest(TEST_ITEM *pTI);
	
	/*Check 2G passphrase*/
	int Run2gPassphraseTest(TEST_ITEM *pTI);
	
	/*Check 5G passphrase*/
	int Run5gPassphraseTest(TEST_ITEM *pTI);
	
	/*Check BoardID*/
	int RunBoardIdTest(TEST_ITEM *pTI);
	
	/*Check SKU*/
	int RunSkuTest(TEST_ITEM *pTI);
	
	/*Check SW time*/
	int RunSwTimeTest(TEST_ITEM *pTI);
	
	/*Check DUT Release version message*/
	int RunReleaseVsTest(TEST_ITEM *pTI);
	
	/*Check DUT Language*/
	int RunLanguageTest(TEST_ITEM *pTI);
	
	/*Check DUT GIGA Link rate*/
	int RunGigaLinkTest(TEST_ITEM *pTI);
	
	/*Check DUT CFE Version*/
	int RunCFEVsTest(TEST_ITEM *pTI);
	
	/*Check pot erase*/
	int RunPotEraseTest(TEST_ITEM *pTI);
	
	/*check USB attach status*/
	int RunUsbAttachTest(TEST_ITEM *pTI);
	
	/*check USB throughput*/
	int RunUsbThputTest(TEST_ITEM *pTI);
	
	/*check router information*/
	int RunRouterInfoTest(TEST_ITEM *pTI);
	
	/*Set reset no reboot mode*/
	int RunResetNoRebootTest(TEST_ITEM *pTI);
	
	/*Check reset button*/
	int RunResetButtonTest(TEST_ITEM *pTI);
	
	/*Check WPS button*/
	int RunWpsButtonTest(TEST_ITEM *pTI);
	
	/*Check wifi button*/
	int RunWifiButtonTest(TEST_ITEM *pTI);
	
	/*Set wifi down*/
	int RunWifiDownTest(TEST_ITEM *pTI);
	
	/*Do pot stop action*/
	int RunPotStopTest(TEST_ITEM *pTI);
	
	/*Check pot stop successfull or not*/
	int RunPotTimeTest(TEST_ITEM *pTI);
	
	/*Set DUT default*/
	int RunLodedefaultTest(TEST_ITEM *pTI);
	
};

#endif
