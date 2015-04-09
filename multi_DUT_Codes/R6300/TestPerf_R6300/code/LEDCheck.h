
#include <string>                                                                     
#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<termios.h>
#include<time.h>
#include<signal.h>
#include<sys/stat.h>
#define BUFFER_SIZE 5120


class LEDCheck
{
public:
  LEDCheck();
  virtual ~LEDCheck();
  public:
  //set the port parameter
  void setTermios(struct termios* pNewtio,int uBaudRate);
  
  //at class init check the parameter
  int initCheck();
  
  //send the command to COM port
  char* sendCommand(char *cmd);
  
  //get LED test
  int getFrequency(char *stringRGB,int channel);
  
  //get RGB value from the return result
  int GetStrBetween(char *strSource,char *rGb, const char *strB,const char *strN);
  
  //check Bule LED
  bool CheckBlueLED(char *strLEDBuf,int i_spec);
  
  //check Green LED
  bool CheckGreenLED(char *strLEDBuf,int i_spec);
  
  //check Amber LED
  bool CheckAmberLED(char *strLEDBuf,int i_spec);
  
  //check RED LED
  bool CheckRedLED(char *strLEDBuf,int i_spec);
  
  //check White LED
  bool CheckWhiteLED(char *strLEDBuf,int i_spec);
public:
  int fd_com1;

  struct termios oldtio, newtio;
  char buff[BUFFER_SIZE];
};


