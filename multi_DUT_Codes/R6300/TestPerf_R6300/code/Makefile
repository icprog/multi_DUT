OBJS = TestPROPerf.o TestTask.o	AmParser.o AmbitParser.o AAPTest.o CenTime.o TestItemScript.o Socket.o AmCommonIO.o	ConfigFile.o HashMapPara.o VersionAndLog.o ControlLogic.o SocketConnection.o AmbitExeCtrl.o	LEDCheck.o Cylinder.o Gpio.o Telnet.o

CC	 = g++ -pthread

CPPFLAGS = -Wall -O	-g	

TestPerf : $(OBJS)
	$(CC) $(OBJS) -o TestPerf

TestPROPerf.o :	TestPROPerf.cpp	
	$(CC) $(CPPFLAGS) -c TestPROPerf.cpp -o	TestPROPerf.o

TestTask.o : TestTask.cpp TestTask.h
	$(CC) $(CPPFLAGS) -c TestTask.cpp -o TestTask.o

AmParser.o : AmParser.cpp AmParser.h
	$(CC) $(CPPFLAGS) -c AmParser.cpp -o AmParser.o

AmbitParser.o :	AmbitParser.cpp	AmbitParser.h
	$(CC) $(CPPFLAGS) -c AmbitParser.cpp -o	AmbitParser.o

AAPTest.o :	AAPTest.cpp	AAPTest.h
	$(CC) $(CPPFLAGS) -c AAPTest.cpp -o	AAPTest.o

CenTime.o :	CenTime.cpp	CenTime.h
	$(CC) $(CPPFLAGS) -c CenTime.cpp -o	CenTime.o

TestItemScript.o : TestItemScript.cpp TestItemScript.h
	$(CC) $(CPPFLAGS) -c TestItemScript.cpp	-o TestItemScript.o

Socket.o : Socket.cpp Socket.h
	$(CC) $(CPPFLAGS) -c Socket.cpp	-o Socket.o

PerfConfigFile.o : ConfigFile.cpp ConfigFile.h
	$(CC) $(CPPFLAGS) -c ConfigFile.cpp	-o ConfigFile.o

HashMapPara.o :	HashMapPara.cpp	HashMapPara.h
	$(CC) $(CPPFLAGS) -c HashMapPara.cpp -o	HashMapPara.o

VersionAndLog.o	: VersionAndLog.cpp	VersionAndLog.h
	$(CC) $(CPPFLAGS) -c VersionAndLog.cpp -o VersionAndLog.o

ControlLogic.o : ControlLogic.cpp ControlLogic.h
	$(CC) $(CPPFLAGS) -c ControlLogic.cpp -o ControlLogic.o

AmCommonIO.o : AmCommonIO.cpp AmCommonIO.h
	 $(CC) $(CPPFLAGS) -c AmCommonIO.cpp -o	AmCommonIO.o
	 
SocketConnection.o : SocketConnection.cpp SocketConnection.h
	$(CC) $(CPPFLAGS) -c SocketConnection.cpp -o SocketConnection.o
	
AmbitExeCtrl.o : AmbitExeCtrl.cpp AmbitExeCtrl.h
	$(CC) $(CPPFLAGS) -c AmbitExeCtrl.cpp -o AmbitExeCtrl.o
	
LEDCheck.o : LEDCheck.cpp LEDCheck.h
	$(CC) $(CPPFLAGS) -c LEDCheck.cpp -o LEDCheck.o
	
Cylinder.o : Cylinder.cpp Cylinder.h
	$(CC) $(CPPFLAGS) -c Cylinder.cpp -o Cylinder.o
Gpio.o : Gpio.cpp Gpio.h
	$(CC) $(CPPFLAGS) -c Gpio.cpp	-o Gpio.o
Telnet.o : Telnet.cpp Telnet.h
	$(CC) $(CPPFLAGS) -c Telnet.cpp -o Telnet.o	

clean: 
	rm -rf *.o TestPerf

