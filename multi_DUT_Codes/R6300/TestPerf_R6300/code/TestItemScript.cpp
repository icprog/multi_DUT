
/*
	do the per item act test in process function definitiong.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TestItemScript.h"
#include "AmCommonIO.h"
#include "Telnet.h"

#define ITEM_START '('
#define ITEM_END ")"


typedef enum 
{
    LED_GREEN=0,
    LED_AMBER,
    LED_BLUE,
    LED_SPARK,
    LED_RED,
    LED_WHITE
}LED_ITEM;
typedef struct Led_spec
{
    LED_ITEM item;
    int channel;
    int times;
    int r_limit;
    int g_limit;
    int b_limit;
    int i_limit;
    int i_spec;
} LED_SPEC;

extern CHashMapPara SFISDataHashMap;


int CTestItemScript::RunLedTest(TEST_ITEM *pTI)
{
    const char *delm=",";
    char *p=NULL;
    char *ledSpecValue=NULL;
    char StLedItem[50]="";
    LED_SPEC now_led_spec;
    memset(&now_led_spec,0,sizeof(now_led_spec));
    char logPrint[4096]="";
    char logStrcat[4096]="";
    bool reValue=false;
   
    ledSpecValue = pTI->Para.GetHashMapStrPara("SPEC");
    memset(StLedItem,0,50);
    for (int Index=0;Index<(int)strlen(ledSpecValue);Index++)
	{
		if (ITEM_START == *(ledSpecValue+Index))
		{
			strncpy(StLedItem,ledSpecValue+Index+1,strstr(ledSpecValue+Index,ITEM_END)-1-(ledSpecValue+Index));
		}
	}
    now_led_spec.channel=0;

    if((p=strtok(StLedItem,delm)))
    {
       if(!strncmp(p,"green",strlen("green")))
        {
            now_led_spec.item=LED_GREEN;
            
        }
        else if(!strncmp(p,"blue",strlen("blue")))
        {
            now_led_spec.item=LED_BLUE;
           
        }
        else if(!strncmp(p,"amber",strlen("amber")))
        {
            now_led_spec.item=LED_AMBER;
        }
        else if(!strncmp(p,"spark",strlen("spark")))
        {
            now_led_spec.item=LED_SPARK;
        }
        else if(!strncmp(p,"red",strlen("red")))
        {
            now_led_spec.item=LED_RED;
        }
        else if(!strncmp(p,"white",strlen("white")))
        {
            now_led_spec.item=LED_WHITE;
        }
        else
        {
            pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"No same color in \"SPEC\"item");
            amprintf("Error£»No same color in \"SPEC\"item!\n");
            return 3;
        }
         
    }
    now_led_spec.r_limit = 0;
    now_led_spec.g_limit = 0;
    now_led_spec.b_limit = 0;
    now_led_spec.i_limit = 0;
    char *limit = NULL;
    limit = pTI->Para.GetHashMapStrPara("R_LIMIT");
    if(limit)
        now_led_spec.r_limit = atoi(limit);
    limit = NULL;
    limit = pTI->Para.GetHashMapStrPara("G_LIMIT");
    if(limit)
        now_led_spec.g_limit = atoi(limit);
    limit = NULL;
    limit = pTI->Para.GetHashMapStrPara("B_LIMIT");
    if(limit)
        now_led_spec.b_limit = atoi(limit);
    limit = NULL;
    limit = pTI->Para.GetHashMapStrPara("I_LIMIT");
    if(limit)
        now_led_spec.i_limit = atoi(limit);
    int y=0;
    while((p=strtok(NULL,delm)))
    {
        if(y==0)
        {
            y++;
            now_led_spec.channel=atoi(p);
        }
        else if(y==1)
        {
            y++;
            now_led_spec.times=atoi(p);
        } 
         else if(y==2)
        {
            y++;
            now_led_spec.i_spec=atoi(p);
        } 
    }
    LEDCheck ledCheck;
   
    char strLEDBuf[100]="";
    memset(strLEDBuf,0,strlen(strLEDBuf));
    memset(logStrcat,0,sizeof(logStrcat));
    sprintf(logStrcat,"channel:%d\r\n       RGBI SunLight:R(%d),G(%d),B(%d),I(%d);\r\n",
                    now_led_spec.channel,
                    now_led_spec.r_limit,now_led_spec.g_limit,now_led_spec.b_limit,now_led_spec.i_limit);
    strcat(logPrint,logStrcat);
    if(now_led_spec.item==LED_SPARK)
    {
        int darkTime=0;
        for(int i=0;i<now_led_spec.times;i++)
        {
            ///GetRGB
            memset(strLEDBuf,0,strlen(strLEDBuf));
          
            memset(logStrcat,0,sizeof(logStrcat));
            sprintf(logStrcat,"RGB test time:%d:\n",(i+1));
            strcat(logPrint,logStrcat);
            if(ledCheck.getFrequency(strLEDBuf,now_led_spec.channel)==0)
            {
                pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"Sensor Board is not connected");
                amprintf("Sensor Board is not connected!\n");
                return 2;
            }
            memset(logStrcat,0,sizeof(logStrcat));
            sprintf(logStrcat,"Get frequency:%s\n",strLEDBuf);
            strcat(logPrint,logStrcat);
            if(strstr(strLEDBuf,"fail"))
             {
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"Get RGB  value fail");
            	amprintf("Get RGB  value fail!\n");
            	return 2;
            }
            char strIight[10] = "";
            ledCheck.GetStrBetween(strLEDBuf,strIight,"I:",";");
            int fIight = atoi(strIight);
            fIight -= now_led_spec.i_limit;
            if(fIight < now_led_spec.i_spec)
                darkTime++;
        }
       
        if(darkTime>=2)
        {
            reValue = false;
        }
        else
            reValue = true;
     
    }

        
    amprintf("%s",logPrint);


    if(reValue)
        return true;
    else
        return false;
          
}

