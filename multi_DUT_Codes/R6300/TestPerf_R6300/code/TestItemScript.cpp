
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

//for PassPhrase ruler check
#define C_MAX_KEY_STR_SIZE                  (32)
static char Adjectives[][C_MAX_KEY_STR_SIZE] = 
{
    "ancient",      "aquatic",      "basic",    "black",        "blue",
    "brave",        "breezy",       "bright",   "calm",         "cheerful",
    "classy",       "clever",       "cloudy",   "crispy",       "curly",
    "daily",        "delightful",   "dizzy",    "dynamic",      "elated",
    "elegant",      "excited",      "exotic",   "fancy",        "fearless",
    "festive",      "fluffy",       "fresh",    "friendly",     "fuzzy",
    "gentle",       "gigantic",     "graceful", "grand",        "great",
    "green",        "happy",        "heavy",    "helpful",      "husky",
    "icy",          "imaginary",    "jagged",   "jolly",        "joyous",
    "kind",         "large",        "little",   "lively",       "lucky",
    "magical",      "melodic",      "mighty",   "misty",        "modern",
    "narrow",       "new",          "nifty",    "noisy",        "odd",
    "orange",       "pastel",       "perfect",  "phobic",       "pink",
    "precious",     "purple",       "quaint",   "quick",        "quiet",
    "rapid",        "red",          "rocky",    "round",        "royal",
    "rustic",       "shiny",        "silent",   "silky",        "silly",
    "smiling",      "slow",         "smooth",   "strong",       "sunny",
    "sweet",        "thirsty",      "tiny",     "thoughtful",   "uneven",
    "unusual",      "vanilla",      "vast",     "watery",       "wide",
    "witty",        "wonderful",    "yellow",   "young",        "zany",
};

static char Nouns[][C_MAX_KEY_STR_SIZE] = 
{
    "airplane",     "apple",        "balloon",  "banana",       "breeze",
    "bird",         "boat",         "box",      "bug",          "butter",
    "cartoon",      "canoe",        "carrot",   "cello",        "chair",
    "cheese",       "coconut",      "comet",    "curtain",      "cream",
    "daisy",        "diamond",      "earth",    "elephant",     "fire",
    "flamingo",     "flower",       "flute",    "giant",        "grasshopper",
    "hat",          "hill",         "iris",     "ink",          "jade",
    "jungle",       "kangaroo",     "kayak",    "lake",         "lightning",
    "lotus",        "mango",        "mint",     "moon",         "mountain",
    "nest",         "ocean",        "onion",    "octopus",      "orchestra",
    "owl",          "lotus",        "mango",    "phoenix",      "piano",
    "pineapple",    "planet",       "pond",     "potato",       "prairie",
    "quail",        "rabbit",       "raccoon",  "raven",        "river",
    "road",         "rosebud",      "sea",      "ship",         "shoe",
    "shrub",        "skates",       "sky",      "socks",        "sparrow",
    "spider",       "squash",       "squirrel", "star",         "street",
    "sun",          "table",        "teapot",   "trail",        "train",
    "tree",         "tomato",       "trumpet",  "tuba",         "tulip",
    "umbrella",     "unicorn",      "valley",   "vase",         "violet",
    "violin",       "water",        "window",     "wind",       "zoo",
};


/*
	Check the Led
*/
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
	else 
    {
        //GetRGB
        int R_frequency=0,G_frequency=0,B_frequency=0,I_frequency=0;
        int failTime=0;
        for(int i=0;i<now_led_spec.times;i++)
        {
            memset(logStrcat,0,sizeof(logStrcat));
            sprintf(logStrcat,"RGB test time:%d:\n",i+1);
            strcat(logPrint,logStrcat);
            
            for(int i=0;i<3;i++)
            {
                memset(strLEDBuf,0,strlen(strLEDBuf));
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
                    amprintf("Error:Can't get RGB frequence value once!\n");
                }
                else if(strstr(strLEDBuf,"error"))
                {
                    amprintf("Error led command:%s!\n",strLEDBuf);
                }
                else
                    break;
            }
            if(strstr(strLEDBuf,"fail")||strstr(strLEDBuf,"error"))
            {
                amprintf("Error:Can't get RGB frequence value three times!\n");
                failTime++;
                continue;
            }
            char strRed[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strRed,"R:","G:")==0)
            {
              amprintf("No R frequence value!\n");
              failTime++;
              continue;
            }
            int fRed = atoi(strRed);
            fRed -= now_led_spec.r_limit;
            R_frequency += fRed;
            char strGreen[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strGreen,"G:","B:")==0)
            {
              amprintf("No G frequence value!\n");
              failTime++;
              continue;
            }
            int fGreen = atoi(strGreen);
            fGreen -= now_led_spec.g_limit;
            G_frequency += fGreen;
            char strBlue[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strBlue,"B:","I:")==0)
            {
              amprintf("No B frequence value!\n");
              failTime++;
              continue;
            }
            int fBlue = atoi(strBlue);
            fBlue -= now_led_spec.b_limit;
            B_frequency += fBlue;
            char strIight[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strIight,"I:",";")==0)
            {
              amprintf("No I frequence value!\n");
              failTime++;
              continue;
            }
            int fIight = atoi(strIight);
            fIight -= now_led_spec.i_limit;
            I_frequency += fIight;
            memset(logStrcat,0,sizeof(logStrcat));
            sprintf(logStrcat,"     Frequency abandon sunlight:R:%d G:%d B:%d I:%d;\r\n",fRed,fGreen,fBlue,fIight);
            strcat(logPrint,logStrcat);
        }
        
        if((now_led_spec.times-failTime)==0)
        {
            pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"Get RGB  value fail");
            amprintf("Error:Can't get led data from Serial Port!\n");
            return 2;
        }
        R_frequency = R_frequency/(now_led_spec.times-failTime);
        G_frequency = G_frequency/(now_led_spec.times-failTime);
        B_frequency = B_frequency/(now_led_spec.times-failTime);
        I_frequency = I_frequency/(now_led_spec.times-failTime);
        
        //strcpy(strLEDBuf,"R:10000Hz G:200000Hz B:10000Hz I:220000Hz;");
        memset(strLEDBuf,0,strlen(strLEDBuf));
        sprintf(strLEDBuf,"R:%dHz G:%dHz B:%dHz I:%dHz;",R_frequency,G_frequency,B_frequency,I_frequency);
       
        if(now_led_spec.item==LED_GREEN)
        {
            reValue=ledCheck.CheckGreenLED(strLEDBuf,now_led_spec.i_spec);
           
        }
        else if(now_led_spec.item==LED_BLUE)
        {
            reValue=ledCheck.CheckBlueLED(strLEDBuf,now_led_spec.i_spec);
           
        }
        else if(now_led_spec.item==LED_AMBER)
        {
            reValue=ledCheck.CheckAmberLED(strLEDBuf,now_led_spec.i_spec);
            
        }
         else if(now_led_spec.item==LED_RED)
        {
            reValue=ledCheck.CheckRedLED(strLEDBuf,now_led_spec.i_spec);
           
        }
          else if(now_led_spec.item==LED_WHITE)
        {
            reValue=ledCheck.CheckWhiteLED(strLEDBuf,now_led_spec.i_spec);
           
        }
        memset(logStrcat,0,sizeof(logStrcat));
        sprintf(logStrcat,"     average RGBI value:%s,I spec:%d.", strLEDBuf,now_led_spec.i_spec);
        strcat(logPrint,logStrcat);
            
    } 
        
    amprintf("%s",logPrint);


    if(reValue)
        return true;
    else
        return false;
          
}

/*
	Check DUT boot up
*/
int CTestItemScript::RunConnectionTest(TEST_ITEM *pTI)
{       
    char *BeforeInt,*AfterInt,chara[10],result[800];
    char log[1024];
    memset(log,0,sizeof(log));
    memset(chara,0,10);
    memset(result,0,800);
    int returnValue =  RunCommand(pTI,result);
    if(returnValue==1)
    {
        BeforeInt=strstr(result,"packets transmitted,");
        if(!BeforeInt)
        {
            if(strstr(result,"\n"))
        	{
            	strncpy(log,result,strstr(result,"\n")-result);
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",log);
            }
            else
            {
               pTI->Para.ModifyHashMapItem("ERR_DES_ADD",result); 
            }
	        amprintf("Error message:%s",result);
            return 2;
        }
        BeforeInt+=(strlen("packets transmitted,")+1);
        AfterInt=strstr(result,"packets received,");
        AfterInt-=1;
        strncpy(chara,BeforeInt,(AfterInt-BeforeInt));
        if(atoi(chara)!=0)
            return 1;
        else
            return 0;
    }

    else if(returnValue==3)
        return 3;
    else
        return 2;
}


/*
	Check DUT SN with message from SFIS
*/
int CTestItemScript::RunSNTest(TEST_ITEM *pTI)
{       
    int returnValue = EnsureSFISResult(pTI,DUT_CMD,SN,LOG_TO_MYDAS);
    return returnValue;
}


/*
	Check 2g PassPhrase
*/
int CTestItemScript::Run2gPassPhraseRuleTest(TEST_ITEM *pTI)
{       
    char *sfis = NULL,passPhrase[20]="";
    sfis=SFISDataHashMap.GetHashMapStrPara("Password_2G");
    if(!sfis)
    {
        char sfisStr[20]= "";
		sprintf(sfisStr,"No \"Password_2G\" SFIS item");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",sfisStr);
		amprintf("Error:%s!",sfisStr);
        return 2;
    }
    strcpy(passPhrase,sfis);
    amprintf("2g PassPhrase get from SFIS:%s\n",passPhrase);
    return Check_Passphrase(passPhrase);
    
}


/*
	Check 5g PassPhrase
*/
int CTestItemScript::Run5gPassPhraseRuleTest(TEST_ITEM *pTI)
{       
    char *sfis = NULL,passPhrase[20]="";
    sfis=SFISDataHashMap.GetHashMapStrPara("Password_5G");
    if(!sfis)
    {
        char sfisStr[20]= "";
		sprintf(sfisStr,"No \"Password_5G\" SFIS item");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",sfisStr);
		amprintf("Error:%s!",sfisStr);
        return 2;
    }
    strcpy(passPhrase,sfis);
    amprintf("5g PassPhrase get from SFIS:%s\n",passPhrase);
    return Check_Passphrase(passPhrase);
}

/*
	Check DUT MAC address with message from SFIS
*/
int CTestItemScript::RunLMACTest(TEST_ITEM *pTI)
{       
    int returnValue = EnsureSFISResult(pTI,DUT_CMD,"ETHERNETMAC",LOG_TO_MYDAS);
    return returnValue;
}


/*
	Check DUT pin with message from SFIS
*/
int CTestItemScript::RunPINTest(TEST_ITEM *pTI)
{       
    int returnValue = EnsureSFISResult(pTI,DUT_CMD,"PIN",LOG_TO_MYDAS);
    return returnValue;
}


/*
	Check DUT 2g SSID with message from SFIS
*/
int CTestItemScript::Run2gSSIDTest(TEST_ITEM *pTI)
{
    int returnValue = EnsureRouterInfoResult(pTI,nowDUT.SSID2G,"SSID_2G");
    return returnValue;
}


/*
	Check DUT 5g SSID with message from SFIS
*/
int CTestItemScript::Run5gSSIDTest(TEST_ITEM *pTI)
{
    int returnValue = EnsureRouterInfoResult(pTI,nowDUT.SSID5G,"SSID_5G");
    return returnValue;
}


/*
	Check DUT 2g Passphrase with message from SFIS
*/
int CTestItemScript::Run2gPassphraseTest(TEST_ITEM *pTI)
{
    int returnValue = EnsureRouterInfoResult(pTI,nowDUT.PassPhrase2G,"Password_2G");
    return returnValue;
}

/*
	Check DUT 5g Passphrase with message from SFIS
*/
int CTestItemScript::Run5gPassphraseTest(TEST_ITEM *pTI)
{
    int returnValue = EnsureRouterInfoResult(pTI,nowDUT.PassPhrase5G,"Password_5G");
    return returnValue;
}

/*
	Check DUT boardid
*/
int CTestItemScript::RunBoardIdTest(TEST_ITEM *pTI)
{       
    int returnValue = EnsureConfigResult(pTI,DUT_CMD,"SPEC",LOG_TO_MYDAS);
    return returnValue;
}


/*
	Check DUT Sku
*/
int CTestItemScript::RunSkuTest(TEST_ITEM *pTI)
{
    int returnValue = EnsureConfigResult(pTI,DUT_CMD,"SPEC",NO_LOG_TO_MYDAS);
    return returnValue;
}


/*
	Check DUT Time
*/
int CTestItemScript::RunSwTimeTest(TEST_ITEM *pTI)
{
    char result[5200],SpecValue[5100],log[1024],swTime[100],*specValue=NULL;
    SFIS_ITEM SfisItemAdd;
    memset(result,0,sizeof(result));
    memset(SpecValue,0,sizeof(SpecValue));
    memset(swTime,0,sizeof(swTime));
    memset(SfisItemAdd.Item,0,sizeof(SfisItemAdd.Item));
	memset(SfisItemAdd.Data,0,sizeof(SfisItemAdd.Data));
	memset(pTI->Result.Result,0,sizeof(pTI->Result.Result));
    memset(pTI->Result.ResultAim,0,sizeof(pTI->Result.ResultAim));
	memset(log,0,sizeof(log));
    int returnValue = RunExeFile(pTI,result,DUT_CMD);
    if(returnValue==1)
    {
        if(strncmp(result,"received:",strlen("received:")))
        {
            if(strstr(result,"\n"))
        	{
            	strncpy(log,result,strstr(result,"\n")-result);
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",log);
            }
            else
            {
                pTI->Para.ModifyHashMapItem("ERR_DES_ADD",result); 
            }
	        amprintf("Error message:%s",result);
            return 2;
        }
        char *resultStart=NULL;
        char *resultEnd=NULL;
        resultStart = strstr(result,"Time :");
        
        if(resultStart)
        {
            resultEnd = strstr(resultStart,"\n");
            if(!resultEnd)
            {
                char dutStr[50]= "";
        		sprintf(dutStr,"Can't find Sw Time in DUT message");
        		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        	    amprintf("Error:%s!\n",dutStr);
                return 2;
            }
            resultStart += strlen("Time :")+1;
            strncpy(swTime,resultStart,resultEnd-resultStart);
            strcpy(pTI->Result.Result,swTime);
            amprintf("Sw Time in DUT:%s\n",swTime);
        }
        else
        {
            char dutStr[50]= "";
    		sprintf(dutStr,"Can't find Sw Time in DUT message");
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
    	    amprintf("Error:%s!\n",dutStr);
            return 2;
        }
         
        specValue = pTI->Para.GetHashMapStrPara("SPEC");
        if(!specValue)
        {
            char specStr[20]= "";
    		sprintf(specStr,"No \"SPEC\"");
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	    amprintf("Error:%s!\n",specStr);
            return 3;
        }
        strncpy(SpecValue,specValue,strlen(specValue));
        strcpy(pTI->Result.ResultAim,SpecValue);
        amprintf("Sw Time in Config=%s\n",SpecValue);
        if(!strcmp(SpecValue,swTime))
            return 1;
        else
            return 0;
    }
    else
        return 3;
       
}

/*
	Check DUT Release version message 
*/
int CTestItemScript::RunReleaseVsTest(TEST_ITEM *pTI)
{       
    char result[5200],SpecValue[5100],log[1024],fwVersion[1024],*specValue=NULL;
    SFIS_ITEM SfisItemAdd;
    memset(result,0,sizeof(result));
    memset(SpecValue,0,sizeof(SpecValue));
    memset(fwVersion,0,sizeof(fwVersion));
    memset(SfisItemAdd.Item,0,sizeof(SfisItemAdd.Item));
	memset(SfisItemAdd.Data,0,sizeof(SfisItemAdd.Data));
	memset(log,0,sizeof(log));
    int returnValue = RunExeFile(pTI,result,DUT_CMD);
    if(returnValue==1)
    {
        if(strncmp(result,"received:",strlen("received:")))
        {
            if(strstr(result,"\n"))
        	{
            	strncpy(log,result,strstr(result,"\n")-result);
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",log);
            }
            else
            {
                pTI->Para.ModifyHashMapItem("ERR_DES_ADD",result); 
            }
	        amprintf("Error message:%s",result);
            return 2;
        }
        char *resultStart=NULL;
        char *resultEnd=NULL;
        //resultStart = strstr(result,"\n")+1;
        resultStart = strstr(result,"\n");
        memset(pTI->Result.Result,0,sizeof(pTI->Result.Result));
        if(resultStart)
        {
            if(strlen(resultStart)<2)
            {
                char dutStr[50]= "";
        		sprintf(dutStr,"Can't find Release Version in DUT message");
        		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        	    amprintf("Erro1r:%s!\n",dutStr);
                return 2;
            }
            resultStart++;
            resultEnd = strstr(resultStart,"\n");
            if(!resultEnd)
            {
                char dutStr[50]= "";
        		sprintf(dutStr,"Can't find Release Version in DUT message");
        		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        	    amprintf("Error2:%s!\n",dutStr);
                return 2;
            }
            strncpy(fwVersion,resultStart,resultEnd-resultStart);   
            strcpy(pTI->Result.Result,fwVersion);
            amprintf("Release Version in DUT:%s\n",pTI->Result.Result);
         }
        else
        {
            strcpy(pTI->Result.Result,"No Val");
        }
        specValue = pTI->Para.GetHashMapStrPara("SPEC");
        if(!specValue)
        {
            char specStr[20]= "";
    		sprintf(specStr,"No \"SPEC\"");
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	    amprintf("Error:%s!\n",specStr);
            return 3;
        }
        memset(pTI->Result.ResultAim,0,sizeof(pTI->Result.ResultAim));
        strcpy(pTI->Result.ResultAim,specValue);
        strcpy(SfisItemAdd.Item,"FW");
        strcpy(SfisItemAdd.Data,fwVersion);
        SFISDataHashMap.InsertHashMapPara(SfisItemAdd.Item,SfisItemAdd.Data);
        strncpy(SpecValue,specValue,strlen(specValue));
        amprintf("Release Version in Config=%s\n",SpecValue);
        if(!strcmp(SpecValue,fwVersion))
            return 1;
         else
            return 0;
    }
    else if(returnValue==3)
        return 3;
    else
        return 2;

}

/*
	Check DUT Language
*/
int CTestItemScript::RunLanguageTest(TEST_ITEM *pTI)
{
    char fullCmd[128],Line[200],result[5200],*cmdPoint=NULL,*specPoint=NULL,cmdOut[256],*cmdEnd=NULL;
    FILE *fread=NULL;
    memset(fullCmd,0,sizeof(fullCmd));
    memset(Line,0,sizeof(Line));
    memset(result,0,sizeof(result));
    memset(cmdOut,0,sizeof(cmdOut));
    cmdPoint = pTI->Para.GetHashMapStrPara("DUT_CMD");
    if(!cmdPoint)
     {
        char specStr[20]= "";
		sprintf(specStr,"No \"DUT_CMD\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    sprintf(fullCmd,"%s |tee out.txt",cmdPoint);
    amprintf("command:%s\n",fullCmd);
    system(fullCmd);
    
    fread = fopen("out.txt","r");
    if(fgets(Line,200,fread)==NULL)
	{
        fclose(fread);
        char dutStr[50]= "";
        sprintf(dutStr,"No output of the command");
        pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        amprintf("Error:%s!\n",dutStr);
        return 2;
	}
	else
	{
		strncat(result,Line,strlen(Line));
	}
	while(!feof(fread))
	{
		memset(Line,0,sizeof(Line));
		if(fgets(Line,200,fread)==NULL)
		{
			break;
		}
		else
		{
			strncat(result,Line,strlen(Line));
		}
	}
	amprintf("telnet output:%s\n",result);
    fclose(fread);
    char *languagePoint = NULL;
    languagePoint = strstr(result,"getchksum 6");
    if(!languagePoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find language message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error1:%s!\n",dutStr);
        return 2;
    }
    char *languagePoint1 = NULL;
    languagePoint += strlen("getchksum 6") -1;
    languagePoint1 = strstr(languagePoint,"getchksum 6");
    if( languagePoint1)
    {
        languagePoint = languagePoint1;
    }
    languagePoint = strstr(languagePoint,"\n");
    if(!languagePoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find language message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error2:%s!\n",dutStr);
        return 2;
    }
    if(strlen(languagePoint) == 1)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find language message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error3:%s!\n",dutStr);
        return 2;
    }
    languagePoint++;
    cmdEnd = strstr(languagePoint,"#");
    if(!cmdEnd)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find language message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error4:%s!\n",dutStr);
        return 2;
    }
    strncpy(cmdOut,languagePoint,cmdEnd - languagePoint);
    amprintf("command output:%s",cmdOut);
    specPoint = pTI->Para.GetHashMapStrPara("SPEC1");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC1\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 1 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    specPoint = NULL;
    specPoint = pTI->Para.GetHashMapStrPara("SPEC2");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC2\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 2 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    specPoint = NULL;
    specPoint = pTI->Para.GetHashMapStrPara("SPEC3");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC3\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 3 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    specPoint = NULL; 
    specPoint = pTI->Para.GetHashMapStrPara("SPEC4");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC4\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 4 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    specPoint = NULL;
    specPoint = pTI->Para.GetHashMapStrPara("SPEC5");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC5\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 5 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    specPoint = NULL;
    specPoint = pTI->Para.GetHashMapStrPara("SPEC6");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC6\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 6 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;      
    return 1;
    
}

/*
	Check DUT GIGA Link rate
*/
int CTestItemScript::RunGigaLinkTest(TEST_ITEM *pTI)
{
    char fullCmd[128],Line[200],result[5200],*cmdPoint=NULL,*specPoint=NULL,cmdOut[256],*cmdEnd=NULL;
    FILE *fread=NULL;
    memset(fullCmd,0,sizeof(fullCmd));
    memset(Line,0,sizeof(Line));
    memset(result,0,sizeof(result));
    memset(cmdOut,0,sizeof(cmdOut));
    cmdPoint = pTI->Para.GetHashMapStrPara("DUT_CMD");
    if(!cmdPoint)
     {
        char specStr[20]= "";
		sprintf(specStr,"No \"DUT_CMD\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error:%s!\n",specStr);
        return 3;
    }
    sprintf(fullCmd,"%s |tee out.txt",cmdPoint);
    amprintf("command:%s\n",fullCmd);
    system(fullCmd);
    
    fread = fopen("out.txt","r");
    if(fgets(Line,200,fread)==NULL)
	{
        fclose(fread);
        char dutStr[50]= "";
        sprintf(dutStr,"No output of the command");
        pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        amprintf("Error:%s!\n",dutStr);
        return 2;
	}
	else
	{
		strncat(result,Line,strlen(Line));
	}
	while(!feof(fread))
	{
		memset(Line,0,sizeof(Line));
		if(fgets(Line,200,fread)==NULL)
		{
			break;
		}
		else
		{
			strncat(result,Line,strlen(Line));
		}
	}
	amprintf("telnet output:%s\n",result);
    fclose(fread);
    char *linkPoint = NULL;
    linkPoint = strstr(result,"et robord 1 0");
    if(!linkPoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find link message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error1:%s!\n",dutStr);
        return 2;
    }
    char *linkPoint1 = NULL;
    linkPoint += strlen("et robord 1 0") -1;
    linkPoint1 = strstr(linkPoint,"et robord 1 0");
    if(linkPoint1)
    {
        linkPoint = linkPoint1;
    }
    linkPoint = strstr(linkPoint,"\n");
    if(!linkPoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find link message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error2:%s!\n",dutStr);
        return 2;
    }
    if(strlen(linkPoint) == 1)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find link message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error3:%s!\n",dutStr);
        return 2;
    }
    linkPoint++;
    cmdEnd = strstr(linkPoint,"#");
    if(!cmdEnd)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find link message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error4:%s!\n",dutStr);
        return 2;
    }
    strncpy(cmdOut,linkPoint,cmdEnd - linkPoint);
    amprintf("command output:%s",cmdOut);
    specPoint = pTI->Para.GetHashMapStrPara("SPEC1");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC1\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error5:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 1 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    linkPoint = NULL;
    linkPoint = strstr(cmdEnd,"et robord 1 4");
    memset(cmdOut,0,sizeof(cmdOut));
    if(!linkPoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find Gia message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error6:%s!\n",dutStr);
        return 2;
    }
    linkPoint1 = NULL;
    linkPoint += strlen("et robord 1 4") -1;
    linkPoint1 = strstr(linkPoint,"et robord 1 4");
    if( linkPoint1)
    {
        linkPoint = linkPoint1;
    }
    linkPoint = strstr(linkPoint,"\n");
    if(!linkPoint)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find Gia message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error7:%s!\n",dutStr);
        return 2;
    }
    if(strlen(linkPoint) == 1)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find Gia message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error8:%s!\n",dutStr);
        return 2;
    }
    linkPoint++;
    cmdEnd = strstr(linkPoint,"#");
    if(!cmdEnd)
    {
        char dutStr[50]= "";
		sprintf(dutStr,"Can't find link message in DUT message");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
	    amprintf("Error9:%s!\n",dutStr);
        return 2;
    }
    strncpy(cmdOut,linkPoint,cmdEnd - linkPoint);
    amprintf("command output:%s",cmdOut);
    specPoint = NULL;
    specPoint = pTI->Para.GetHashMapStrPara("SPEC2");
    if(!specPoint)
    {
        char specStr[20]= "";
		sprintf(specStr,"No \"SPEC2\"");
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	amprintf("Error10:%s!\n",specStr);
        return 3;
    }
    amprintf("SPEC 2 in Config:%s!\n",specPoint);
    if(!strstr(cmdOut,specPoint))
        return 0;
    return 1;
}

/*
	Check DUT CFE Version
*/
int CTestItemScript::RunCFEVsTest(TEST_ITEM *pTI)
{
    char result[5200],SpecValue[5100],log[1024],CFEVersion[100],*specValue=NULL;
    SFIS_ITEM SfisItemAdd;
    memset(result,0,sizeof(result));
    memset(SpecValue,0,sizeof(SpecValue));
    memset(CFEVersion,0,sizeof(CFEVersion));
    memset(SfisItemAdd.Item,0,sizeof(SfisItemAdd.Item));
	memset(SfisItemAdd.Data,0,sizeof(SfisItemAdd.Data));
	memset(pTI->Result.Result,0,sizeof(pTI->Result.Result));
	memset(pTI->Result.ResultAim,0,sizeof(pTI->Result.ResultAim));
	memset(log,0,sizeof(log));
    int returnValue = RunExeFile(pTI,result,DUT_CMD);
    if(returnValue==1)
    {
        if(strncmp(result,"received:",strlen("received:")))
        {
            if(strstr(result,"\n"))
        	{
            	strncpy(log,result,strstr(result,"\n")-result);
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",log);
            }
            else
            {
                pTI->Para.ModifyHashMapItem("ERR_DES_ADD",result); 
            }
	        amprintf("Error message:%s",result);
            return 2;
        }
        char *resultStart=NULL;
        char *resultEnd=NULL;
        resultStart = strstr(result,"CFE version :");
        memset(pTI->Result.Result,0,sizeof(pTI->Result.Result));
        if(resultStart)
        {
            resultEnd = strstr(resultStart,"\n");
            if(!resultEnd)
            {
                char dutStr[50]= "";
        		sprintf(dutStr,"Can't find CFE Version in DUT message");
        		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
        	    amprintf("Error1:%s!\n",dutStr);
                return 2;
            }
            resultStart += strlen("CFE version :")+1;
            strncpy(CFEVersion,resultStart,resultEnd-resultStart);
            strcpy(pTI->Result.Result,CFEVersion);
            amprintf("CFE Version in DUT:%s\n",CFEVersion);
        }
        else
        {
            char dutStr[50]= "";
    		sprintf(dutStr,"Can't find CFE Version in DUT message");
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",dutStr);
    	    amprintf("Error2:%s!\n",dutStr);
            return 2;
        }
         
        specValue = pTI->Para.GetHashMapStrPara("SPEC");
        if(!specValue)
        {
            char specStr[20]= "";
    		sprintf(specStr,"No \"SPEC\"");
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	    amprintf("Error:%s!\n",specStr);
            return 3;
        }
        strncpy(SpecValue,specValue,strlen(specValue));
        strcpy(pTI->Result.ResultAim,SpecValue);
        amprintf("CFE Version in Config=%s\n",SpecValue);
        if(!strcmp(SpecValue,CFEVersion))
            return 1;
        else
            return 0;
    }
    else
        return 3;
       
}

/*
	Check pot erase
*/
int CTestItemScript::RunPotEraseTest(TEST_ITEM *pTI)
{       
    int returnValue =EnsureResult(pTI,"Erase done.",DUT_CMD);
    return returnValue;
}

/*
	check USB attach status
*/
int CTestItemScript::RunUsbAttachTest(TEST_ITEM *pTI)
{       
    int returnValue = EnsureConfigResult(pTI,DUT_CMD,"SPEC",NO_LOG_TO_MYDAS);
    return returnValue;
}

