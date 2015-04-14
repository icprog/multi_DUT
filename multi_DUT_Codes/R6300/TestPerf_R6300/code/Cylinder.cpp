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
int Cylinder::doAction(const char *cmd)
{


    std::string data;
    std::string empty_data="";
    data=cmd;     
    
    if(data!=empty_data)
    {


        //	Audio switch for PCA9555		START


        if(data.find("AUDIOSWITCH_CTL_OFF:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"AUDIOSWITCH_CTL_OFF:");
				int idx=atoi(pos+strlen("AUDIOSWITCH_CTL_OFF:"));
				printf("%d\n",idx);
				if((idx>0)&&(idx<=MAX_AUDIOSWITCH_PORTS))
				{
					audio_status[0]=0x02;
					if(idx>8)
					{
						audio_status[2]|=1<<(idx-1-8);
					}
					else
					{	
						audio_status[1]|=1<<(idx-1);
					}
					MV_I2C_IOCTL_PARMS params;
					params.action=I2C_WRITE;
					params.chanNum=0;
					params.dev_addr=AUDIOSW_ADDRESS ;
					params.offset=0;
					params.alen=0;
					params.data=(char *)audio_status;
					params.len=3;

					int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
					params.data=(char *)audio_status;
					ioctl(fd_i2c,board_ioctl_signal,&params);
					printf("%02x %02x \n",audio_status[2],audio_status[1]);
					//usleep(500000);
					string response("AUDIOSWITCH_OFF_OK\n");
					printf(response.c_str());

				}				
			}	
		}

        if(data.find("AUDIOSWITCH_CTL_SELECT:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"AUDIOSWITCH_CTL_SELECT:");
				int idx=atoi(pos+strlen("AUDIOSWITCH_CTL_SELECT:"));
				printf("%d\n",idx);
				if((idx>0)&&(idx<=MAX_AUDIOSWITCH_PORTS))
				{
					audio_status[0]=0x02;
					if(idx>8)
					{
						audio_status[1]=0xff;
						audio_status[2]=~(1<<(idx-1-8));
					}
					else
					{	
						audio_status[1]=~(1<<(idx-1));
						audio_status[2]=0xff;
					}
					MV_I2C_IOCTL_PARMS params;
					params.action=I2C_WRITE;
					params.chanNum=0;
					params.dev_addr=AUDIOSW_ADDRESS;
					params.offset=0;
					params.alen=0;
					params.data=(char *)audio_status;
					params.len=3;

					int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
					params.data=(char *)audio_status;
					ioctl(fd_i2c,board_ioctl_signal,&params);
					printf("%02x %02x \n",audio_status[2],audio_status[1]);
					//usleep(500000);
					string response("AUDIOSWITCH_SELECT_OK\n");
					printf(response.c_str());

				}				
			}	
		}


		if(data.find("AUDIOSWITCH_CTL_ON:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"AUDIOSWITCH_CTL_ON:");
				int idx=atoi(pos+strlen("AUDIOSWITCH_CTL_ON:"));
				printf("%d\n",idx);
				if((idx>0)&&(idx<=MAX_AUDIOSWITCH_PORTS))
				{
					audio_status[0]=0x02;
					if(idx>8)
					{
						audio_status[2]&=~(1<<(idx-1-8));
					}
					else
					{	
						audio_status[1]&=~(1<<(idx-1));
					}
					MV_I2C_IOCTL_PARMS params;
					params.action=I2C_WRITE;
					params.chanNum=0;
					params.dev_addr=AUDIOSW_ADDRESS;
					params.offset=0;
					params.alen=0;
					params.data=(char *)audio_status;
					params.len=3;
					int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
					ioctl(fd_i2c,board_ioctl_signal,&params);
					
					printf("%02x %02x \n",audio_status[2],audio_status[1]);
					//usleep(500000);
					string response("AUDIOSWITCH_ON_OK\n");
					printf(response.c_str());

				}				
			}
			
		}

		if(data.find("AUDIOSWITCH_CTL_GET:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				sprintf(msg,"AUDIOSWITCH:0x%02x%02x;\n",audio_status[2],audio_status[1]);
				string response(msg);
				printf(response.c_str());
			}
		}                                                                                                                                                                                                                                                                                                                                                                                                     		if(data.find("AUDIOSWITCH_CTL_SET:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"AUDIOSWITCH_CTL_SET:");
				char * stop;
				long set_value=strtol(pos+strlen("AUDIOSWITCH_CTL_SET:"),&stop,16);
				printf("AUDIOSWITCH:0x%04lx;\n",set_value);
				unsigned char *pchar=(unsigned char *)&set_value;
				audio_status[1]=*pchar;
				audio_status[2]=*(pchar+1);
				audio_status[0]=0x02;

				MV_I2C_IOCTL_PARMS params;
				params.action=I2C_WRITE;
				params.chanNum=0;
				params.dev_addr=AUDIOSW_ADDRESS;
				params.offset=0;
				params.alen=0;
				params.data=(char *)audio_status;
				params.len=3;
				int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
				ioctl(fd_i2c,board_ioctl_signal,&params);
					
                printf("%02x %02x \n",audio_status[2],audio_status[1]);
				
			}
		}


//	 Audio switch for PCA9555	END
//   Relay for PCA8575          START
		if(data.find("RELAY_CTL_ON:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"RELAY_CTL_ON:");
				int idx=atoi(pos+strlen("RELAY_CTL_ON:"));
				printf("%d\n",idx);
				if((idx>0)&&(idx<=MAX_RELAY_PORTS))
				{
					
					if(idx>8)
					{
						relay_status[1]|=1<<(idx-1-8);
					}
					else
					{	
						relay_status[0]|=1<<(idx-1);
					}
					MV_I2C_IOCTL_PARMS params;
					params.action=I2C_WRITE;
					params.chanNum=0;
					params.dev_addr=RELAY_ADDRESS ;
					params.offset=0;
					params.alen=0;
					params.data=(char *)relay_status;
					params.len=2;
					int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
					params.data=(char *)relay_status;
					ioctl(fd_i2c,board_ioctl_signal,&params);
					printf("%02x %02x \n",relay_status[1],relay_status[0]);
					//usleep(500000);
					string response("RELAY_ON_OK\n");
					printf(response.c_str());

				}				
			}	
		}

		if(data.find("RELAY_CTL_OFF:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"RELAY_CTL_OFF:");
				int idx=atoi(pos+strlen("RELAY_CTL_OFF:"));
				printf("%d\n",idx);
				if((idx>0)&&(idx<=MAX_RELAY_PORTS))
				{
					
					if(idx>8)
					{
						relay_status[1]&=~(1<<(idx-1-8));
					}
					else
					{	
						relay_status[0]&=~(1<<(idx-1));
					}
					MV_I2C_IOCTL_PARMS params;
					params.action=I2C_WRITE;
					params.chanNum=0;
					params.dev_addr=RELAY_ADDRESS;
					params.offset=0;
					params.alen=0;
					params.data=(char *)relay_status;
					params.len=2;
					int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
					ioctl(fd_i2c,board_ioctl_signal,&params);
					
					printf("%02x %02x \n",relay_status[1],relay_status[0]);
					//usleep(500000);
					string response("RELAY_OFF_OK\n");
					printf(response.c_str());

				}				
			}
			
		}

		if(data.find("RELAY_CTL_GET:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"RELAY_CTL_GET:");
				pos += strlen("RELAY_CTL_GET:");
				int t=atoi(pos);
				if(t==0)
				    return 0;
				unsigned char readbuf[2];
				readbuf[0]=0xFF;
				readbuf[1]=0xFF;
				MV_I2C_IOCTL_PARMS params;
				params.action=I2C_READ;
				params.chanNum=0;
				params.dev_addr=RELAY_ADDRESS;
				params.offset=0;
				params.alen=0;
				params.data=(char *)readbuf;
				params.len=2;
				int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
				ioctl(fd_i2c,board_ioctl_signal,&params);
					
			    printf("%02x %02x\n",readbuf[1],readbuf[0]);
				string response("RELAY_GET_OK\n");
				printf(response.c_str());
				
	            if(t>8)
	            {
	                readbuf[1] &=1<<(t-1-8);
	                if(readbuf[1]==0)
	                    return 1;
	                else
	                    return 0;
				
	            }
	             else
				 {	
					readbuf[0] &=(1<<(t-1));
					if(readbuf[0]==0)
	                    return 1;
	                else
	                    return 0;
	                        
				 }   
	         
			}
		}
		if(data.find("RELAY_CTL_SET:")!=string::npos)
		{
			if(data.find(";")!=string::npos)
			{
				char msg[BUFFER_SIZE]="";
				strcpy(msg,data.c_str());
				char* pos=strstr(msg,"RELAY_CTL_SET:");
				
				char * stop;
				long set_value=strtol(pos+strlen("RELAY_CTL_SET:"),&stop,16);
				printf("RELAY:0x%04lx;\n",set_value);
				
				unsigned char *pchar=(unsigned char *)&set_value;
				relay_status[0]=*pchar;
				relay_status[1]=*(pchar+1);
				
				MV_I2C_IOCTL_PARMS params;
				params.action=I2C_WRITE;
				params.chanNum=0;
				params.dev_addr=RELAY_ADDRESS;
				params.offset=0;
				params.alen=0;
				params.data=(char *)relay_status;
				params.len=2;
				int board_ioctl_signal=BOARD_IOCTL_I2C_CTRL;
				ioctl(fd_i2c,board_ioctl_signal,&params);
					
			    printf("%02x %02x \n",relay_status[1],relay_status[0]);
				string response("RELAY_SET_OK\n");
				printf(response.c_str());
			}
		}
   
    } 
     return 1;
}
