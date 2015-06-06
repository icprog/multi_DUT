#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

class CControlLogic
{
public:
	CControlLogic();
public:
	~CControlLogic();
public:
	/*init the CControlLogic class*/
    int Init();
	
	/*Read config file.*/
	int ReadConfigFile(void);
	
	/*test information cross*/
	int InformationCross(void);
	
	/*parse the test command*/
	int ParseCommand(char * pCMD,int DataLen);
	
	/*connect the UI program .*/
    int UIConnection();
	
public:
	pthread_t dwParsePktThreadID;
	pthread_t dwAutoFixThreadID; 
};

/*Parse Process*/
void ParsePktProcess(void* lpPara);

/*Cylinder Start Test*/
void CylinderStartTest();

#endif
