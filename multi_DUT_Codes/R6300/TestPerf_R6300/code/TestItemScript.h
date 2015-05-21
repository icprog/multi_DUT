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
	
};

#endif
