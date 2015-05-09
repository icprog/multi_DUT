
#include"AmCommonIO.h"

extern pthread_t TestThreadID;
extern bool gThreadExitFlag;
extern CSocketConnection SocketConnection;


/*
	amprintf - print to the UI console
	This routine is the equivalent of printf.  It is used such that logging	capabilities can be added.
	RETURNS: same as printf.  Number of characters printed
*/
long amprintf
(
const char * format,
...
)
{
	va_list argList;
	bool  result;
	long     retval = 0;
	char    buffer[3000];
	memset(buffer , 0, sizeof(buffer));

	/*if have logging turned on then can also write to a file if needed */

	/* get the arguement list */
	va_start(argList, format);

	/* using vprintf to perform the printing it is the same is printf, only
	* it takes a va_list or arguments
	*/
	retval = vprintf(format, argList);
	fflush(stdout);

	//if the GUI flag is be define,the message will be print to GUI process
	#ifdef GUI_IO
	usleep(1);
	vsprintf(buffer, format, argList);
	result=SocketConnection.socketSend(buffer);
	/*
        while(!ensureSymbol);
        printf("ensureSymbol: %d\n",ensureSymbol);
           ensureSymbol=0;
           */
	if(!result)
	{
		printf("Connection with UI error!\n  ");
		gThreadExitFlag=true;
		if(TestThreadID)
		    pthread_cancel(TestThreadID);
		return 0;
	}
		
        //usleep(1);
	#endif
	va_end(argList);    /* cleanup arg list */
	return 1;
}


/*
	print test result to log file
*/
int LogPrint(int PrintMode)
{

	switch(PrintMode)
	{
		case 1:
		break;
		case 2:
		break;
		default:
		break;
	}

	return 1;

}

