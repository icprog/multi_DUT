
#ifndef TETS_TASK_H
#define TETS_TASK_H

#include <list>
#include "AmbtTestSysDef.h"
#include "TestItemScript.h"
#include "AmParser.h"
#include "AmCommonIO.h"
#include "AmbtParser.h"
#include "CenTime.h"
#include "Cylinder.h"

/*Compare the max length.*/
int strMaxLenCmp(const char *p1, const char *p2);

/*prepare the test.*/
int PrepareTestWork();

/*Initial the test */
int InitialTestWork();

/*After the test */
int AfterTestWork();

/*mian test thread*/
void MainTestThread(void *lpParameter);

/*after the mian test thread*/
void StopMainTest();

/*Item Test Task*/
int  ItemTestTask(TEST_ITEM *pTI);

/*get sunlight setting for LED test.*/
int GetSunLight();

/*Test sunlight for LED test.*/
int SunlightCheck();

/*send test inforamtion to UI Program.*/
int SendIDInfoToUI(void);
#endif

