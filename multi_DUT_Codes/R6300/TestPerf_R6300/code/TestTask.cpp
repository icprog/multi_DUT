 /*
	do the act test in process function definition and script description
 */
#include "TestTask.h"


/*
	Compare the max length.
*/
int strMaxLenCmp(const char *p1, const char *p2)
{
    size_t len;
    len=strlen(p1);
    if (strlen(p2)>len)
    {
        len=strlen(p2);
    }
    return (strncmp(p1,p2,len));
}


/*
	prepare the test.
*/
int PrepareTestWork()
{

    list<TEST_ITEM>::iterator Cy;
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {           
        Cy->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"None");
    }
    return 1;
}


/*
	Initial the test 
*/
int InitialTestWork()
{

    list<TEST_ITEM>::iterator Cy;
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {           
        if (TFLAG_INI_RUN!=Cy->Para.GetHashMapIntPara(ITEM_ENABLE_FALG))//judge the test flag
        {
            continue;
        }

        ItemTestTask(&(*Cy));
    }
    return 1;
}

/*
	After the test 
*/
int AfterTestWork()
{

    list<TEST_ITEM>::iterator Cy;
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {                   
        if (TFLAG_TERMINATE_RUN!=Cy->Para.GetHashMapIntPara(ITEM_ENABLE_FALG))//judge the test flag
        {
            continue;
        }

        ItemTest(&(*Cy));
    }
    return 1;
}


