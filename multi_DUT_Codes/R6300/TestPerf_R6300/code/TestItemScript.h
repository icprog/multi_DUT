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
	
};

#endif
