#ifndef CYLINDER_H
#define CYLINDER_H

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
using namespace std;

class Cylinder
{
    #define AUDIOSW_ADDRESS 0x24  
    #define BOARD_IOCTL_I2C_CTRL 0x1
    #define RELAY_ADDRESS 0x24
    #define AUDIOSW_ADDRESS 0x24 
    unsigned char relay_status[2];
    unsigned char audio_status[3];
    typedef enum 
    {
        I2C_READ=0,
        I2C_WRITE,
        I2C_PROBE
    }MV_I2C_ACTION;
    
    typedef struct MVI2CIoctlParams
    {
        MV_I2C_ACTION action;
        char chanNum;
        char dev_addr;
        int offset;
        int alen;
        char* data;
        int len;
    } MV_I2C_IOCTL_PARMS;
    
    #define I2C_DEVICE_NAME   "/dev/i2c"
    #define BUFFER_SIZE 5120
    #define MAX_RELAY_PORTS 16
    #define MAX_AUDIOSWITCH_PORTS 12

public:    
    int fd_i2c;
  

public:
    Cylinder();
public:
    virtual ~Cylinder();

    int doAction(const char *cmd);
     
};
#endif
