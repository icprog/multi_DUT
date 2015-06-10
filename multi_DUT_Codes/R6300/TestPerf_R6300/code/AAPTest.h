
#ifndef A_AP_TEST_H
#define A_AP_TEST_H

#include <pthread.h>
#include "AmbitParser.h"
#include "AmCommonIO.h"
#include "CenTime.h"
#include "AAPTest.h"
#include "TestItemScript.h"
#include "AmParser.h"
#include "ControlLogic.h"

/*Parser the test items*/
int ParseTestItem(const char *p1, const char *p2);

/*define the test key word mapping the test function.*/
int  ItemTest(TEST_ITEM *pTI);

#endif