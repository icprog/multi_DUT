#include <string>                                                                     
#include <iostream>
#include <pthread.h>
#include     <fcntl.h> 
#include     <unistd.h> 
#include     <sys/types.h>  
#include     <sys/stat.h>
#include     <errno.h>
#include     <stdlib.h> 
#include     <stdio.h>
#include     <sys/ioctl.h>

#include "Cylinder.h"
using namespace std;



#define MPP_ADDR_1 0xf1010014
#define MPP_ADDR_2 0xf1010018
#define FUN_ADDR 0xf1010144
#define OUT_ADDR 0xf1010140
#define BLINK_ADDR 0xf1010148
#define BUTTON_IN_ADDR  0xf1010150
#define MPP_MASK_1 0x0000ffff
#define MPP_MASK_2 0xffffff00
#define FUN_IN_MASK 0x00014000
#define FUN_OUT_MASK 0xfff14fff
#define BUTTON1_ADDR_BIT 14
#define BUTTON2_ADDR_BIT 16

#define RED_LED_ADDR_BIT 13
#define GREEN_LED_ADDR_BIT 12
#define YELLOW_LED_ADDR_BIT 17

int  gt_reg_read(unsigned int rgst,unsigned int *vlue);
int  gt_reg_write(unsigned int rgst, unsigned int vlue);
int init_io_port();
unsigned int getBtn1Status();
unsigned int getBtn2Status();
void setGreenOn();
void setGreenOff();
void setGreenBlink();
void setRedOn();
void setRedOff();
void setRedBlink();
void setYellowOn();
void setYellowOff();
void setYellowBlink();
