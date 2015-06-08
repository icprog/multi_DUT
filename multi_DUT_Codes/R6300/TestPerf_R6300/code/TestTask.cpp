 /*
	do the act test in process function definition and script description
 */
#include "TestTask.h"
#include "VersionAndLog.h"

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

/*
	End the test work
*/
int EndTestWork()
{

    list<TEST_ITEM>::iterator Cy;
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {               
        if (TFLAG_END_RUN!=Cy->Para.GetHashMapIntPara(ITEM_ENABLE_FALG))//judge the test flag
        {
            continue;
        }

        ItemTestTask(&(*Cy));
    }
    return 1;
}

/*
	mian test thread
*/
void MainTestThread(void *lpParameter)
{
    
    list<TEST_ITEM>::iterator Cy; 
    //.DeleteHashMapItem 
    cylin = 0;
    PerfTest(&Cy);
    ReportTestResult(Cy);
    SFISDataHashMap.DestroyHashMapPara();
    printf("After Test Work\n");

    struct timeval Start_t,Current_t;
    clock_t Duration=0;
    gettimeofday(&Start_t,NULL);
    do
    {
        usleep(100000);
        gettimeofday(&Current_t,NULL);
	    Duration=Current_t.tv_sec-Start_t.tv_sec;
        
    }while((cylin!=1)&&(Duration < 60));
    cylinder.doAction("RELAY_CTL_OFF:1;");

    gThreadExitFlag=true;
    return ;
}


/*
	after the mian test thread
*/
void StopMainTest()
{
    if(TestThreadID)
		pthread_cancel(TestThreadID);
    SFISDataHashMap.DestroyHashMapPara();
    printf("Stop Test by UI!\n");
    cylinder.doAction("RELAY_CTL_OFF:1;");
    cylin = 0;
    gThreadExitFlag=true;
    return ;
}

/*
	Item Test Task
*/
int  ItemTestTask(TEST_ITEM *pTI)
{
    CCenTime Time;
    int TestResult=0;
    char TimeBuf[50];
    int RetryCount=0;
    int RetryLimit=0;
    char RetryInformation[30]="";
    int alarmSecond = 90;
    int secondCost = 0;
    Time.TimeStartCount();//count the time

    if(NO_TEST==pTI->Result.ResultFlag)
    {
        pTI->Num = ItemTestID;
        amprintf("ITEM=ID[%d]NAME[%s];\n",ItemTestID,pTI->Para.GetHashMapStrPara(ITEM_ID));
        RetryLimit=pTI->Para.GetHashMapIntPara(RETRY_FLAG);
        RetryLimit+=2;
        for (RetryCount=1; (RetryCount<RetryLimit)&&(secondCost < alarmSecond); RetryCount++)
        {
            amprintf("Test time:%d:\n",RetryCount);
            if(RetryCount != 1)
                sleep(1);
            TestResult=ItemTest(pTI);
            Time.GetElapseSecond(&secondCost);
            printf("secondCost=%d\n",secondCost);
            if (!(pTI->Para.GetHashMapIntPara(RETRY_FLAG)))
            {
                break;
            }
            else if (TestResult==1)
            {
                break;
            }
            else
            {
               
                sprintf(RetryInformation, "%d", RetryCount);
                pTI->RetryItemCount++;
                
            }
        }
        pTI->Result.ResultFlag=TestResult;
        
        if (TestResult==1)//perform the actual test action
        {
            amprintf("ITEM=ID[%d]RESULT[PASS];\n",ItemTestID);
            ItemTestID++;
        }
        else
        {   
            TestPassFail=1;
            amprintf("ITEM=ID[%d]RESULT[FAIL];\n",ItemTestID);
            ItemTestID++;
        }

        Time.GetElapseTime(TimeBuf,sizeof(TimeBuf));
        amprintf("Item test time:%s;\n",TimeBuf);
      
    }

    return 1;
}

/*
	get sunlight setting for LED test.
*/
int GetSunLight()
{
    list<TEST_ITEM>::iterator Cy;
    char *testItem = NULL;
    int r_limit = 0;
    int g_limit = 0;
    int b_limit = 0;
    int i_limit = 0;
    char ledSun[2056]="LEDSUNLIGHT=";
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {
        testItem = Cy->Para.GetHashMapStrPara(ITEM_ID);
        if(!(strcmp(testItem,"CHECK_POWER_LED")&&
            strcmp(testItem,"CHECK_WAN_LED")&&
            strcmp(testItem,"CHECK_2GWL_LED")&&
            strcmp(testItem,"CHECK_5GWL_LED")&&
            strcmp(testItem,"CHECK_LAN1_LED")&&
            strcmp(testItem,"CHECK_LAN2_LED")&&
            strcmp(testItem,"CHECK_LAN3_LED")&&
            strcmp(testItem,"CHECK_LAN4_LED")&&
            strcmp(testItem,"CHECK_USB1_LED")&&
            strcmp(testItem,"CHECK_USB2_LED")&&
            strcmp(testItem,"CHECK_SYMBOL_LED")&&
            strcmp(testItem,"CHECK_WPS_LED")
           ))
        {
            r_limit = 0;
            g_limit = 0;
            b_limit = 0;
            i_limit = 0;
            char *limit = NULL;
            limit = Cy->Para.GetHashMapStrPara("R_LIMIT");
            if(limit)
                r_limit = atoi(limit);
            limit = NULL;
            limit = Cy->Para.GetHashMapStrPara("G_LIMIT");
            if(limit)
                g_limit = atoi(limit);
            limit = NULL;
            limit = Cy->Para.GetHashMapStrPara("B_LIMIT");
            if(limit)
                b_limit = atoi(limit);
            limit = NULL;
            limit = Cy->Para.GetHashMapStrPara("I_LIMIT");
            if(limit)
                i_limit = atoi(limit);
             sprintf(ledSun,"%sLED test item:%s\r\n     Sunlight:R:%dHz G:%dHz B:%dHz I:%dHz\r\n",
                    ledSun,testItem,r_limit,g_limit,b_limit,i_limit);
        }
    }
    amprintf("%s;",ledSun); 
    return 1;
}

/*
	Test sunlight for LED test.
*/
int SunlightCheck()
{
    list<TEST_ITEM>::iterator Cy;
    char *testItem = NULL;
    char *ledSpecValue=NULL;
    int channel = 0;
    LEDCheck ledCheck;
    char strLEDBuf[100]="";
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {
        testItem = Cy->Para.GetHashMapStrPara(ITEM_ID);
        if(!(strcmp(testItem,"CHECK_POWER_LED")&&
            strcmp(testItem,"CHECK_WAN_LED")&&
            strcmp(testItem,"CHECK_2GWL_LED")&&
            strcmp(testItem,"CHECK_5GWL_LED")&&
            strcmp(testItem,"CHECK_LAN1_LED")&&
            strcmp(testItem,"CHECK_LAN2_LED")&&
            strcmp(testItem,"CHECK_LAN3_LED")&&
            strcmp(testItem,"CHECK_LAN4_LED")&&
            strcmp(testItem,"CHECK_USB1_LED")&&
            strcmp(testItem,"CHECK_USB2_LED")&&
            strcmp(testItem,"CHECK_SYMBOL_LED")&&
            strcmp(testItem,"CHECK_WPS_LED")
           ))
        {
           
            ledSpecValue = Cy->Para.GetHashMapStrPara("SPEC");
            if(!ledSpecValue)
                return 0;
            ledSpecValue = strstr(ledSpecValue,",")+1;
            if(!ledSpecValue)
                return 0;
            channel = atoi(ledSpecValue);
            memset(strLEDBuf,0,strlen(strLEDBuf));
            if(ledCheck.getFrequency(strLEDBuf,channel)==0)
            {
                amprintf("Sensor Board is not connected!\n");
                return 0;
            }
            if(strstr(strLEDBuf,"fail"))
            {
                amprintf("Get RGB  value fail!\n");
                return 0;
            }
            char strRed[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strRed,"R:","G:")==0)
            {
                amprintf("No R frequence value!\n");
                return 0;
            }
            int fRed = atoi(strRed);
            char arrayRGBI[10] = "";
            sprintf(arrayRGBI,"%d",fRed);
            Cy->Para.ModifyHashMapItem("R_LIMIT",arrayRGBI);
            char strGreen[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strGreen,"G:","B:")==0)
            {
                amprintf("No G frequence value!\n");
                return 0;
            }
            int fGreen = atoi(strGreen);
            memset(arrayRGBI,0,sizeof(arrayRGBI));
            sprintf(arrayRGBI,"%d",fGreen);
            Cy->Para.ModifyHashMapItem("G_LIMIT",arrayRGBI);
            char strBlue[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strBlue,"B:","I:")==0)
            {
                amprintf("No B frequence value!\n");
                return 0;
            }
            int fBlue = atoi(strBlue);
            memset(arrayRGBI,0,sizeof(arrayRGBI));
            sprintf(arrayRGBI,"%d",fBlue);
            Cy->Para.ModifyHashMapItem("B_LIMIT",arrayRGBI);
            char strIight[10] = "";
            if(ledCheck.GetStrBetween(strLEDBuf,strIight,"I:",";")==0)
             {
                amprintf("No I frequence value!\n");
                return 0;
            }
            int fIight = atoi(strIight);
            memset(arrayRGBI,0,sizeof(arrayRGBI));
            sprintf(arrayRGBI,"%d",fIight);
            Cy->Para.ModifyHashMapItem("I_LIMIT",arrayRGBI);
               
        }
       
    } 
    GetSunLight();
    return 1;  
}

/*
	send test inforamtion to UI Program.
*/
int SendIDInfoToUI(void)
{
    strcpy(gTI.TestStaInfo.TestProgramVersion,SOFTWARE_VERSION);
    amprintf("CONTROL=TSNAME[%s]TSMODEL[%s]TSVER[%s]LOGPATH[%s];", 
        gTI.TestStaInfo.TestStaName,gTI.DUTInfo.DUTName,gTI.TestStaInfo.TestProgramVersion,gTI.TestStaInfo.TestLogPath
        ); //Add send DUT model to UI for database use
    GetSunLight();
    

    return 1;
}

/*
	perf test
*/
int PerfTest(list<TEST_ITEM>::iterator *pCy)
{
    ItemTestID = 1;
    int  iItemCount=0;
    char *pFlag=NULL;
    int flag=1;
    gThreadExitFlag=0;
    char TimeBuf[50];

    CCenTime Time;
    CCenTime TotalTime;

    list<TEST_ITEM>::iterator Cy;
    list<TEST_ITEM>::iterator JumpCy;

    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {
        Cy->Result.ResultFlag=NO_TEST;
        memset(Cy->Result.Result,0,sizeof(Cy->Result.Result));
        memset(Cy->Result.ResultAim,0,sizeof(Cy->Result.ResultAim));
        strncpy(Cy->Result.Result,"-999999",sizeof(Cy->Result.Result));
        strncpy(Cy->Result.ResultAim,"-999999",sizeof(Cy->Result.ResultAim));
        Cy->RetryItemCount=0;//reset retry item counter
        if (TFLAG_SKIP!=Cy->Para.GetHashMapIntPara(ITEM_ENABLE_FALG))//judge the test flag
        {
            iItemCount++;
        }
    }
    sleep(1);
    amprintf("ITEM=NUMBER[%d];\n",iItemCount);
    Time.GetDate(gTI.DUTInfo.TestDate,sizeof(gTI.DUTInfo.TestDate));
    Time.GenCurrentTime(gTI.DUTInfo.TestTime, sizeof(gTI.DUTInfo.TestTime));
    TotalTime.TimeStartCount();
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {
        char *testItem = NULL;
        testItem = Cy->Para.GetHashMapStrPara(ITEM_ID);
        if(!strcmp(testItem,"CHECK_DUT_BOARDID"))
        {
            CTestItemScript bootupScript;
            int bootupFlag=0;
            int alarmSecond = 90;
            int secondCost = 0;
            Time.TimeStartCount();//count the time
            while((bootupFlag!=1)&&(secondCost<alarmSecond))
            {
                bootupFlag = bootupScript.RunBoardIdTest(&(*Cy));
                Time.GetElapseSecond(&secondCost);
            }
            if(bootupFlag == 6)
            {
                system("./telnetenable 192.168.1.1");
                system("(sleep 1&&echo \"nvram set parser_enable=1\"&&sleep 1&&echo \"nvram set telnetd_enable=1\"&&sleep 1&&echo \"nvram set wan_proto=static\"&&sleep 1&&echo \"nvram set wan_ipaddr_old=111.111.111.111\"&&sleep 1&&echo \"nvram set wan_ipaddr=111.111.111.111\"&&sleep 1&&echo \"nvram set wan_netmask=255.255.255.0\"&&sleep 1&&echo \"nvram set wan_gateway=111.111.111.222\"&&sleep 1&&echo \"nvram set wan_dns1=111.111.111.222\"&&sleep 1&&echo \"nvram set wan_dns_sel=1\"&&sleep 1&&echo \"nvram save\"&&sleep 1&&echo \"reboot\"&&sleep 1&&echo \"exit\") |telnet 192.168.1.1");
                secondCost = 0;
                Time.TimeStartCount();//count the time
                 while((bootupFlag!=1)&&(secondCost<alarmSecond))
                {
                    bootupFlag = bootupScript.RunBoardIdTest(&(*Cy));
                    Time.GetElapseSecond(&secondCost);
                }
            }
            if(bootupFlag == 5)
            {
                Cy->Result.ResultFlag=5;
                TestPassFail=1;  
                goto LB_EXIT;
            } 
        }
    }
    InitialTestWork();
    for (Cy=TItemList.begin(); Cy!=TItemList.end();Cy++)
    {
        
        pFlag = Cy->Para.GetHashMapStrPara(ITEM_ENABLE_FALG);
        if(!pFlag)
            flag = 1;
        else
            flag = atoi(pFlag);
        if (TFLAG_SKIP==flag)//judge the test flag
        {
            continue;
        }
        if (TFLAG_INI_RUN==flag)//judge the test flag
        {
            continue;
        }
        if (TFLAG_END_RUN==flag)//judge the test flag
        {
            continue;
        }
        if (TFLAG_TERMINATE_RUN==flag)//judge the test flag
        {
            continue;
        }

        ItemTestTask(&(*Cy));
        if(Cy->Result.ResultFlag!=TEST_PASS)
        {
            switch (flag)
            {
                case TFLAG_FAIL_STOP:
                *pCy=Cy;//RETURN THE current test item index
                goto LB_EXIT;
                break;
                case TFLAG_FAIL_CONTINUE:continue;break;
                //case TFLAG_FAIL_PAUSE:;break;
                case TFLAG_FAIL_PAUSE:break;/*FreezeFlag=1*/;break;
                default:;break;

            }
        }

    }
    *pCy=TItemList.end();//RETURN THE current test item index
    LB_EXIT:

    EndTestWork();

    TotalTime.GetElapseTime(TimeBuf,sizeof(TimeBuf));
    strncpy(gTI.DUTInfo.TestTimeCost,TimeBuf,sizeof(gTI.DUTInfo.TestTimeCost));
    amprintf("Total test time:%s;\n",TimeBuf);
    
    return 1;
}

/*
	Report test result to UI program.
*/
int ReportTestResult(list<TEST_ITEM>::iterator StopCy)
{

    char ErrorCode[512]="",*errCode=NULL;
    char ErrorCodeAdd[512]="";
    char SFISToUI[512]="";
    char SFISTemp[512]="";
    int ErrorCodeCount = 0,num=1;
    char logbuf[5046]="";
    char errlog[1024]="";
    
    map<char*,char*>::iterator iter;
    for(iter=SFISDataHashMap.pParaHashMap->begin();iter!=SFISDataHashMap.pParaHashMap->end();iter++)
    {
        sprintf(SFISTemp,"%s[%s]",iter->first,iter->second);
        strncat(SFISToUI,SFISTemp,strlen(SFISTemp));
    }
    memset(logbuf,0,sizeof(logbuf));
    memset(errlog,0,sizeof(errlog));
    for (StopCy=TItemList.begin(); StopCy!=TItemList.end();StopCy++,num++)
    {       
            
        if (TEST_FAIL==(StopCy->Result.ResultFlag))
        {

            if(ErrorCodeCount>0)
            {
             strcat(ErrorCode,",");
             
            }
            
            errCode = StopCy->Para.GetHashMapStrPara(ITEM_ERR_CODE);
            if(!errCode)
            {
                sprintf(ErrorCodeAdd,"CE%02d",StopCy->Num);
                strncat(ErrorCode,ErrorCodeAdd,strlen(ErrorCodeAdd));
                strcat(errlog,ErrorCodeAdd);
                strcat(errlog,",");
                strcat(errlog,"No \"ERR_CODE\"");
                strcat(errlog,",");
                if(strcmp(StopCy->Result.Result,"-999999"))
                {
                    strcat(errlog,StopCy->Result.Result);
                }
                strcat(errlog,"|");
                      
            }
            else
            {
                strncat(ErrorCode,errCode,strlen(errCode));
                strcat(errlog, errCode);
                strcat(errlog,",");
                char *errDes = NULL;
                errDes = StopCy->Para.GetHashMapStrPara(ITEM_ERR_CODE_DES);
                if(errDes)
                {
                    strcat(errlog,errDes);
                }
                else
                {
                    strcat(errlog,"No error code descaription");
                }
                strcat(errlog,",");
                if(strcmp(StopCy->Result.Result,"-999999"))
                {
                    strcat(errlog,StopCy->Result.Result);
                }
                strcat(errlog,"|");
            }  
          ErrorCodeCount++;
            
        }
        else if(TEST_COMMAD_ERROR==(StopCy->Result.ResultFlag))
        {
            if(ErrorCodeCount>0)
            {
             strcat(ErrorCode,",");
            }
            sprintf(ErrorCodeAdd,"CM%02d",StopCy->Num); 
            strncat(ErrorCode,ErrorCodeAdd,strlen(ErrorCodeAdd));
            strcat(errlog,ErrorCodeAdd);
            char *errDes = NULL;
            strcat(errlog,",");
            errDes = StopCy->Para.GetHashMapStrPara("ERR_DES_ADD");
             if(errDes)
            {
                strcat(errlog,errDes);
            }
            else
            {
                strcat(errlog,"No error code descaription");
            }
            strcat(errlog,",");
            strcat(errlog,"|");
            ErrorCodeCount++;
        }
       
        else if(TEST_CONFIG_ERROR==(StopCy->Result.ResultFlag))
        {
            if(ErrorCodeCount>0)
            {
                strcat(ErrorCode,",");
            }
            sprintf(ErrorCodeAdd,"CE%02d",StopCy->Num); 
            strncat(ErrorCode,ErrorCodeAdd,strlen(ErrorCodeAdd));   
            strcat(errlog,ErrorCodeAdd);
            char *errDes = NULL;
            strcat(errlog,",");
            errDes = StopCy->Para.GetHashMapStrPara("ERR_DES_ADD");
             if(errDes)
            {
                strcat(errlog,errDes);
            }
            else
            {
                strcat(errlog,"No error code description");
            }
            strcat(errlog,",");
            strcat(errlog,"|");
            ErrorCodeCount++; 
        }
        else if(NO_CONNECT==(StopCy->Result.ResultFlag))
        {
            if(ErrorCodeCount>0)
            {
                strcat(ErrorCode,",");
            }
            sprintf(ErrorCodeAdd,"NDUT"); 
            strncat(ErrorCode,ErrorCodeAdd,strlen(ErrorCodeAdd));   
            strcat(errlog,ErrorCodeAdd);
            strcat(errlog,",");
            
            strcat(errlog,"Not find DUT");
            strcat(errlog,",");
            strcat(errlog,"|");
            ErrorCodeCount++; 
        }
        else if(NO_PARSER==(StopCy->Result.ResultFlag))
        {
            if(ErrorCodeCount>0)
            {
                strcat(ErrorCode,",");
            }
            sprintf(ErrorCodeAdd,"NPAR"); 
            strncat(ErrorCode,ErrorCodeAdd,strlen(ErrorCodeAdd));   
            strcat(errlog,ErrorCodeAdd);
            strcat(errlog,",");
            
            strcat(errlog,"No Parser in DUT");
            strcat(errlog,",");
            strcat(errlog,"|");
            ErrorCodeCount++; 
        }
        if(strcmp(StopCy->Result.Result,"-999999"))
        {
            strcat(logbuf,StopCy->Result.ResultAim);
            strcat(logbuf,",");
            strcat(logbuf,StopCy->Result.Result);
            strcat(logbuf,",");
        }
   
    }
    
    strcpy(gTI.TestStaInfo.TesterPCName,"ARM");
    if (TestPassFail)
    {
        amprintf("LOG=MAINFOR[%s,0,%s,%s,%s,%s,%s,%s,%s];\n",SFISDataHashMap.GetHashMapStrPara("SN"),gTI.TestStaInfo.TestLogPath,gTI.TestStaInfo.TestProgramVersion,gTI.TestStaInfo.TesterPCName,gTI.DUTInfo.TestTimeCost,gTI.DUTInfo.TestTime,SFISDataHashMap.GetHashMapStrPara("ETHERNETMAC"),SFISDataHashMap.GetHashMapStrPara("PIN"));
    }
    else
    {
        
        amprintf("LOG=MAINFOR[%s,1,%s,%s,%s,%s,%s,%s,%s];\n",SFISDataHashMap.GetHashMapStrPara("SN"),gTI.TestStaInfo.TestLogPath,gTI.TestStaInfo.TestProgramVersion,gTI.TestStaInfo.TesterPCName,gTI.DUTInfo.TestTimeCost,gTI.DUTInfo.TestTime,SFISDataHashMap.GetHashMapStrPara("ETHERNETMAC"),SFISDataHashMap.GetHashMapStrPara("PIN"));
    }   
    amprintf("LOG=CONTENT[%s,%s,%s,%s,%s,%s];\n",SFISDataHashMap.GetHashMapStrPara("SN"),SFISDataHashMap.GetHashMapStrPara("SSID_2G"),SFISDataHashMap.GetHashMapStrPara("Password_2G"),SFISDataHashMap.GetHashMapStrPara("SSID_5G"),SFISDataHashMap.GetHashMapStrPara("Password_5G"),logbuf);
     if (TestPassFail)
    {
        
        amprintf("LOG=ERROR[%s];\n",errlog);
        amprintf("SFIS=%sERRORCODE[%s]RESULT[FAIL];CONTROL=RESULT[FAIL];",SFISToUI,ErrorCode);
        PrintPassFail(0); 
    }
    else
    {
        amprintf("LOG=ERROR[ ];\n");
        amprintf("SFIS=%sRESULT[PASS];CONTROL=RESULT[PASS];",SFISToUI); 
        PrintPassFail(1);
    }   
    return 1;
}

/*
	recevie the test result from UI program.
*/
int AcceptCMD(char *pCmd,int DataLen)
{
    printf("CMD:%s\n",pCmd);
    CAmParser cParser;
    cParser.SetStartStopTag("[","]");

    char DDBuf[3000]="";
    char cCmdBuf[300]="";
    char *pTok=NULL;
    char *pToken=NULL;
    char *pTokFlag=NULL;

    if (!pCmd)
    {
        return 0;
    }
    if ((!DataLen)||(DataLen>(int)(sizeof(DDBuf))))
    {
        return 0;
    }

    memcpy(DDBuf,pCmd,DataLen);

    
    pToken = DDBuf;
    while(strstr(pToken,";"))
    {
        if ((pTok=strstr(pToken, "CONTROL=")))
        {       
            if (!cParser.ParserGetPara(pTok, "CMD", cCmdBuf, sizeof(cCmdBuf)))
            {
                 if (!cParser.ParserGetPara(pTok, "LED", cCmdBuf, sizeof(cCmdBuf)))
                {
                     amprintf("Illogical Command Input:%s!\n",pTok);
                     break;
                }
                else
                {
                    LEDCheck ledCheck;
                    char strLEDBuf[100]="";
                    char sendRGBBuf[100]="";
                    int channel = atoi(cCmdBuf);
                    if(channel==0)
                    {
                        amprintf("LEDRGB=Send a channel number fail!;");
                    }
                    else if(ledCheck.getFrequency(strLEDBuf,channel)==0)
                    {
                        amprintf("LEDRGB=Sensor Board is not connected!;");
                    }
                    else if(strstr(strLEDBuf,"fail"))
                    {
                        amprintf("LEDRGB=Get RGB  value fail!;");
                    }
                    else
                    {
                        char *led = strstr(strLEDBuf,"B:");
                        if(led)
                        {
                            strncpy(sendRGBBuf,strLEDBuf,led - strLEDBuf);
                            sprintf(sendRGBBuf,"%s\r\n%s",sendRGBBuf,led);
                            amprintf("LEDRGB=%s;",sendRGBBuf);
                        }
                        else
                            amprintf("LEDRGB=%s;",strLEDBuf);
                    }
                }
                
            }   
            else
            {
            if(!strncmp("EXIT", cCmdBuf, strlen("EXIT")))
            {
                return 1;
            }
            else if(!strncmp("STOP", cCmdBuf, strlen("STOP")))
            {
                StopMainTest();
                return 1;
            }
             else if(!strncmp("REBOOT", cCmdBuf, strlen("REBOOT")))
            {
                system("reboot");
            }
            else if(!strncmp("START", cCmdBuf, strlen("START")))
            {
                amprintf("CONTROL=ECHOCMD[START];\n");
                if(gThreadExitFlag)
                {
                    printf("Start Run Test\n");
                    TestEnd=0;
                    buttonTest=0;
                    buttonBegin=0;
                    TestPassFail=0;
                   
                    
                    RunTest();
                }                   
                else
                {
                    amprintf("Error:There are another test running!\n");
                }
            }
            else if(!strncmp("SUNLIGHT", cCmdBuf, strlen("SUNLIGHT")))
            {
                if(SunlightCheck())
                    amprintf("CONTROL=SUNLIGHT[1];\n");
                else
                    amprintf("CONTROL=SUNLIGHT[0];\n");
            }
             else if(!strncmp("END", cCmdBuf, strlen("END")))
            {
                cylin = 1;
            }
             else if(!strncmp("RESETPRESS", cCmdBuf, strlen("RESETPRESS")))
            {
                 cylinder.doAction("RELAY_CTL_ON:2;");
            }
             else if(!strncmp("RESETRELEASE", cCmdBuf, strlen("RESETRELEASE")))
            {
                cylinder.doAction("RELAY_CTL_OFF:2;");
            }
             else if(!strncmp("WIFIPRESS", cCmdBuf, strlen("WIFIPRESS")))
            {
                cylinder.doAction("RELAY_CTL_ON:3;");
            }
             else if(!strncmp("WIFIRELEASE", cCmdBuf, strlen("WIFIRELEASE")))
            {
                cylinder.doAction("RELAY_CTL_OFF:3;");
            }
             else if(!strncmp("WPSPRESS", cCmdBuf, strlen("WPSRELEASE")))
            {
                 cylinder.doAction("RELAY_CTL_ON:4;");
            }
             else if(!strncmp("WPSRELEASE", cCmdBuf, strlen("WPSRELEASE")))
            {
                cylinder.doAction("RELAY_CTL_OFF:4;");
            }
                 else if(!strncmp("PORTIN", cCmdBuf, strlen("PORTIN")))
                {
                     cylinder.doAction("RELAY_CTL_ON:5;");
                }
                 else if(!strncmp("PORTOUT", cCmdBuf, strlen("PORTOUT")))
                {
                    cylinder.doAction("RELAY_CTL_OFF:5;");
                }
            }
        }

        else if ((pTok=strstr(pToken, "SFIS")))
        {
                char TempBuf[512] ="";
                memset(TempBuf,0,512);
                
                SFIS_ITEM SfisItemTemp;
                pTokFlag = strstr(pToken, "[");
                if (!pTokFlag)
                {
                    amprintf("SFIS Data is empty;\n");
                    return 1;
                }
                pTok += strlen("SFIS=");
                memset(SfisItemTemp.Item,0,sizeof(SfisItemTemp.Item));
                strncpy(SfisItemTemp.Item,pTok,(int)(pTokFlag-pTok));
                printf("SFIS Item=%s\n",SfisItemTemp.Item);
                
                if (cParser.ParserGetPara(pTok, SfisItemTemp.Item, TempBuf, sizeof(TempBuf)))
                {
                    strcpy(SfisItemTemp.Data, TempBuf);
                    printf("SFIS Val=%s\n",SfisItemTemp.Data);
                }
                while(!gThreadExitFlag)
                    sleep(1);
                SFISDataHashMap.CreateHashMapPara();
                SFISDataHashMap.InsertHashMapPara(SfisItemTemp.Item,SfisItemTemp.Data);
                
                pTok = strstr(pTok,"]");
                pTok+=1;
                while(*pTok!=';')
                {
                    pTokFlag = strstr(pTok, "[");
                    memset(SfisItemTemp.Item,0,sizeof(SfisItemTemp.Item));
                    memset(SfisItemTemp.Data,0,sizeof(SfisItemTemp.Data));
                    strncpy(SfisItemTemp.Item,pTok,pTokFlag-pTok);
                                       
                    if (cParser.ParserGetPara(pTok, SfisItemTemp.Item, TempBuf, sizeof(TempBuf)))
                    {
                        strcpy(SfisItemTemp.Data,TempBuf);
                    }
                   
                    SFISDataHashMap.InsertHashMapPara(SfisItemTemp.Item,SfisItemTemp.Data);
                    pTok = strstr(pTok,"]");
                    pTok+=1;
                }
                
                if(gThreadExitFlag)
                {
                    printf("Start Run Test by SFIS message\n");
                    TestEnd=0;
                    buttonTest=0;
                    buttonBegin=0;
                    TestPassFail=0; 
                   
                    RunTest();
                    
                }           
            
        }
        else
        {
            printf("The other data.\n");
        } 
        pToken=strstr(pToken,";");
        pToken+=1;
    } 
    return 1;
}

/*
	run test.
*/
int RunTest()
{   
    PrepareTestWork();
    int createIf = pthread_create(&TestThreadID,NULL,(void* (*) (void*))MainTestThread,NULL);
    if(createIf)
        printf("Create Thread fail!\n");
    pthread_detach(TestThreadID);
    return 1;
}



