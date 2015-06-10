
/*
	do the act test in process function definition.
*/

#include "AAPTest.h"
#include "TestItemScript.h"
#include "TestTask.h"

CTestItemScript tiScript;
int buttonTest,buttonBegin;

/*
	Parser the test items
*/
int ParseTestItem(const char *p1, const char *p2)
{
	size_t len;
	len=strlen(p1);
	if (strlen(p2)>len)
	{
		len=strlen(p2);
	}
	int reVal=strncmp(p1,p2,len);
	return reVal;
}


/*
	define the test key word mapping the test function.
*/
int  ItemTest(TEST_ITEM *pTI)
{
	int retFlag=0;
	char IDTemp[200],*item;
	memset(IDTemp,0,sizeof(IDTemp));
	item = pTI->Para.GetHashMapStrPara(ITEM_ID);
	if(!item)
	{
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"No \"ITEM_ID\"");
		amprintf("Error:No \"ITEM_ID\"!\n");
		return 3;
	}
	strncpy(IDTemp,item,strlen(item));//Get item id name
	printf("IDTemp=%s\n",IDTemp);
	if (ParseTestItem(IDTemp,"CHECK_RESET_BUTTON")==0)
	{
	  retFlag=tiScript.RunResetButtonTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"GET_ROUTER_INFO")==0)
	{
	  retFlag=tiScript.RunRouterInfoTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_WPS_BUTTON")==0)
	{
	  retFlag=tiScript.RunWpsButtonTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_WIFI_BUTTON")==0)
	{
	  retFlag=tiScript.RunWifiButtonTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN_TO_LAN_CONNECTION")==0)
	{
        retFlag=tiScript.RunConnectionTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN_TO_WAN_CONNECTION")==0)
	{
        retFlag=tiScript.RunConnectionTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_ROUTERINFO")==0)
	{
        retFlag=tiScript.RunRouterInfoTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_LMAC")==0)
	{
        retFlag=tiScript.RunLMACTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_PIN")==0)
	{
        retFlag=tiScript.RunPINTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_BOARDID")==0)
	{
        retFlag=tiScript.RunBoardIdTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_SN")==0)
	{
        retFlag=tiScript.RunSNTest(pTI);
	}
    else if (ParseTestItem(IDTemp,"CHECK_DUT_RELEASE_VS")==0)
	{
        retFlag=tiScript.RunReleaseVsTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_CFE_VS")==0)
	{
        retFlag=tiScript.RunCFEVsTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"ERASE_DUT_POT")==0)
	{
        retFlag=tiScript.RunPotEraseTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_USB_ATTACH")==0)
	{
        retFlag=tiScript.RunUsbAttachTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_USB_THROUGHPUT")==0)
	{
        retFlag=tiScript.RunUsbThputTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_DUT_RESET_NO_REBOOT")==0)
	{
        retFlag=tiScript.RunResetNoRebootTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_WIFI_DOWN")==0)
	{
        retFlag=tiScript.RunWifiDownTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_DUT_POT_STOP")==0)
	{
        retFlag=tiScript.RunPotStopTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_POT")==0)
	{
        retFlag=tiScript.RunPotTimeTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_DUT_DEFAULT")==0)
	{
        retFlag=tiScript.RunLodedefaultTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_ALL_LED_UP")==0)
	{
        retFlag=tiScript.RunSetLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_ALL_LED_DOWN")==0)
	{
        retFlag=tiScript.RunSetLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_POWER_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_WAN_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_SYMBOL_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_2GWL_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_5GWL_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN1_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN2_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN3_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN4_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_USB1_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_USB2_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_WPS_LED")==0)
	{
        retFlag=tiScript.RunLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"SET_WAN_LED")==0)
	{
        retFlag=tiScript.RunSetWanLedTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN_TO_WAN_THROUGHPUT")==0)
	{
        retFlag=tiScript.RunLanThroughputTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_LAN_TO_LAN_THROUGHPUT")==0)
	{
        retFlag=tiScript.RunLanThroughputTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_2G_SSID")==0)
	{
        retFlag=tiScript.Run2gSSIDTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_5G_SSID")==0)
	{
        retFlag=tiScript.Run5gSSIDTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_2G_PASSPHRASE")==0)
	{
        retFlag=tiScript.Run2gPassphraseTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_5G_PASSPHRASE")==0)
	{
        retFlag=tiScript.Run5gPassphraseTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_SKU")==0)
	{
        retFlag=tiScript.RunSkuTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_SW_TIME")==0)
	{
        retFlag=tiScript.RunSwTimeTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_LANGUAGE")==0)
	{
        retFlag=tiScript.RunLanguageTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_2G_PASSPHRASE_RULE")==0)
	{
        retFlag=tiScript.Run2gPassPhraseRuleTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_5G_PASSPHRASE_RULE")==0)
	{
        retFlag=tiScript.Run5gPassPhraseRuleTest(pTI);
	}
	else if (ParseTestItem(IDTemp,"CHECK_DUT_GIALINK")==0)
	{
        retFlag=tiScript.RunGigaLinkTest(pTI);
	}
	else
	{
	    pTI->Para.ModifyHashMapItem("ERR_DES_ADD",(char *)"No item match");
	    amprintf("Error:No item match!\n");
	    return 3;
	}
	
	printf("retFlag=%d\n",retFlag);
	return retFlag;
}

