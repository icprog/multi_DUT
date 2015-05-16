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
	
};

#endif
