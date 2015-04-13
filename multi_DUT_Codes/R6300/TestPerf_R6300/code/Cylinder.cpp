#include "Cylinder.h"

#include "Cylinder.h"
#include <stdlib.h>
#include <stdio.h>

Cylinder::Cylinder()
{
    if((fd_i2c=open(I2C_DEVICE_NAME,O_RDWR))<0)
  
    {
    	perror("Can not open device.\n");
    	exit(1);
    }
    //³õÊ¼»¯ 
    MV_I2C_IOCTL_PARMS params;
    int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
    ////Initialization for PCA9555
    audio_status[0]=0x06;
    audio_status[1]=0x00;
    audio_status[2]=0x00;
    params.action=I2C_WRITE;
    params.chanNum=0;
    params.offset=0;
    params.alen=0;
    params.len=3;
    params.data=(char *)audio_status;
    params.dev_addr=AUDIOSW_ADDRESS;
    ioctl(fd_i2c,board_ioctl_signal,&params);
    
    audio_status[0]=0x02;
    audio_status[1]=0xff;
    audio_status[2]=0xff;
    params.action=I2C_WRITE;
    params.chanNum=0;
    params.offset=0;
    params.alen=0;
    params.len=3;
    params.data=(char *)audio_status;
    params.dev_addr=AUDIOSW_ADDRESS;
    ioctl(fd_i2c,board_ioctl_signal,&params);
    
    //Initialization for PCA8575
    params.action=I2C_WRITE;
    params.chanNum=0;
    params.dev_addr=RELAY_ADDRESS;
    params.offset=0;
    params.alen=0;
    relay_status[0]=0x00;
    relay_status[1]=0xFF;
    params.data=(char *)relay_status;
    params.len=2;
    
    ioctl(fd_i2c,board_ioctl_signal,&params);
    
    ////Ö´ÐÐÃüÁî
    

}
Cylinder::~Cylinder()
{   
     close(fd_i2c); 
}