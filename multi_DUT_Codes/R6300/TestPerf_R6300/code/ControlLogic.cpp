
/*
	Used for defined control logic between program and UI program.
*/

#include "ControlLogic.h"



CControlLogic::CControlLogic(void)
{
}
CControlLogic::~CControlLogic(void)
{
}

/*
	init the CControlLogic class
*/
int CControlLogic::Init()
{

	if (!UIConnection())//establish connection UI between testperf
	{
		printf("ERROR Can not connect server.exit\n");
		return 0;
	}
	if (!ReadConfigFile())
	{

		return 0;
	}

	if (!StartAMBTUIParseCammandTask())
	{
		return 0;
	}
    if(!StartAutoFixtureTask())
    {
        return 0;
    }

	usleep(1);
	return 1;
}

/*
	Read config file.
*/
int CControlLogic::ReadConfigFile(void)
{

	CConfigFile ConfigFile;
	if(ConfigFile.GetLoadConfigFile((char *)"downFile.txt"))
	    return (ConfigFile.PerformParse((char *)"ambtconfig.txt"));
	else
	    return 0;
}

/*
	test information cross
*/
int CControlLogic::InformationCross(void)
{
	SendIDInfoToUI();
	return 0;
}

/*
	parse the test command
*/
int CControlLogic::ParseCommand(char *pCMD,int DataLen)
{
	printf("Recv CMD:%s\n", pCMD);
	int ret=AcceptCMD(pCMD,DataLen);
	printf("ACCEPT OK\n");
	return ret;
	//return 0;
}

/*
	connect the UI program .
*/
int CControlLogic::UIConnection()
{
	std::cout<<"Server open.\n";

	if(SocketConnection.Connection())
	{
		sleep(10);
		return 1;
	}
	else
	return 0;
}