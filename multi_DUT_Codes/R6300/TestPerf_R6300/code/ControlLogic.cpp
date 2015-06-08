
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


/*
	Parse Process
*/
void ParsePktProcess(void* lpPara)
{
	char RevBuf[3000];
	CControlLogic *pCL=(CControlLogic*)lpPara;
	while (1)
	{
		
		if(ConnectionIf==1)
		{
			pCL->InformationCross();
			ConnectionIf=0;
		}
		memset(RevBuf, '\0', sizeof(RevBuf));
		int ret = 0;
		ret=SocketConnection.GetRevList(RevBuf,sizeof(RevBuf));
		if(ret!=0)
		{
			
			if(pCL->ParseCommand(RevBuf,strlen(RevBuf)))
			continue;

		}
		usleep(1);
	}
	return ;
}

/*
	Cylinder Start Test
*/
void CylinderStartTest()
{
    int status = 0,status1=0;
    int duration=0;
    struct timeval tvStart,tvEnd;
    int auto_status=0;
    init_io_port();
    while(1)
    {
       status = getBtn1Status();
       
       usleep(30000);
       status1 = getBtn1Status();
      
       if((!status1)&&(!status)&&gThreadExitFlag)
        {
            int i=0;
            while(!getBtn1Status()&&( i < 100000))
            {
            	i++;
            	usleep(100);
            }
            if(i==100000)
                continue;
            if(cylinder.doAction("RELAY_CTL_GET:14;") == 1)
            	cylinder.doAction("RELAY_CTL_OFF:1;");
            else
            {
            	auto_status = 0;
	            cylinder.doAction("RELAY_CTL_ON:1;");
	            printf("Cylinder start!\n");
	            gettimeofday(&tvStart,NULL);
	            duration=0;
	            while((auto_status != 1)&&(duration<2))
	            {
	                auto_status = cylinder.doAction("RELAY_CTL_GET:14;");
	                gettimeofday(&tvEnd,NULL);
	                duration=tvEnd.tv_sec-tvStart.tv_sec;
	            }
	            if(duration >= 2)
	                cylinder.doAction("RELAY_CTL_OFF:1;");
	            else
	           {
	                amprintf("FIX=FIXNUM[1];\n"); 
	            }
	        }  
        }
        
    }
    return;
}

/*
	Start Parse Cammand Task
*/
int CControlLogic::StartAMBTUIParseCammandTask(void)
{
	pthread_t parser_pkt_id;
	pthread_create(&parser_pkt_id,NULL,(void* (*) (void*))ParsePktProcess,this);
	return true;
}

/*
	Start Auto Fixture Task
*/
int CControlLogic::StartAutoFixtureTask(void)
{
	pthread_t cylinder_id;
	pthread_create(&cylinder_id,NULL,(void* (*) (void*))CylinderStartTest,NULL);
	return true;
}