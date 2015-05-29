
#ifndef TETS_TASK_H
#define TETS_TASK_H

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
#endif

