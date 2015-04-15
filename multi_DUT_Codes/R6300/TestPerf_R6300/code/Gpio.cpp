#include "Gpio.h"



/*************************************************************************************/

int  gt_reg_read(unsigned int rgst,unsigned int *vlue)
 {
    unsigned int reg = rgst, value;
    FILE *resource_dump;
    resource_dump = fopen ("/proc/resource_dump" , "w");
    if (!resource_dump) {
      printf ("Error opening file /proc/resource_dump\n");
      return 0;
    }
    fprintf (resource_dump,"register  r %08x",reg);
    fclose (resource_dump);
    resource_dump = fopen ("/proc/resource_dump" , "r");
    if (!resource_dump) {
      printf ("Error opening file /proc/resource_dump\n");
      return 0;
    }
    fscanf (resource_dump , "%x" , &value);
    fclose (resource_dump);
    //printf ("%08x : %08x \n",reg,value);
    *vlue=value; 
    return 1;
}
/*************************************************************************************/

int  gt_reg_write(unsigned int rgst, unsigned int vlue) 
{
  unsigned int reg = rgst, value = vlue;
  FILE *resource_dump;
  resource_dump = fopen ("/proc/resource_dump" , "w");
  if (!resource_dump) {
    printf ("Eror opening file /proc/resource_dump\n");
    return 0;
  }
  fprintf (resource_dump,"register  w %08x %08x",reg,value);
  fclose (resource_dump);
  return 1;
}

/*************************************************************************************/


/*************************************************************************************/
int init_io_port()
{
   unsigned int reg,value;
   reg=MPP_ADDR_1;
   gt_reg_read(reg,&value);
   value &= MPP_MASK_1;
   gt_reg_write(reg,value);

   reg=MPP_ADDR_2;
   gt_reg_read(reg,&value);
   value &= MPP_MASK_2;
   gt_reg_write(reg,value);

   reg=FUN_ADDR;
   gt_reg_read(reg,&value);
   value |= FUN_IN_MASK;
   value &= FUN_OUT_MASK;
   gt_reg_write(reg,value);

   return 1;
}
/*************************************************************************************/
unsigned int getBtn1Status()
{
     unsigned int reg,value;
     unsigned int data_btn1=0;
     reg=BUTTON_IN_ADDR;
     gt_reg_read(reg,&value);
     data_btn1 = value & (1<<BUTTON1_ADDR_BIT);
     if(data_btn1==0)
     {
	return 0;
     } 
     else
     {
	return 1;
     }  
}
/*************************************************************************************/
unsigned int getBtn2Status()
{
     unsigned int reg,value;
     unsigned int data_btn2=0;
     reg=BUTTON_IN_ADDR;
     gt_reg_read(reg,&value);
     data_btn2 = value & (1<<BUTTON2_ADDR_BIT);
     if(data_btn2==0)
     {
	return 0;
     } 
     else
     {
	return 1;
     }  
}
/*************************************************************************************/
void setGreenOn()
{	
   unsigned int reg,value;

   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<GREEN_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<GREEN_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setGreenOff()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<GREEN_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<GREEN_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setGreenBlink()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<GREEN_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/

/*************************************************************************************/
void setRedOn()
{	
   unsigned int reg,value;

   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<RED_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<RED_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setRedOff()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<RED_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<RED_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setRedBlink()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<RED_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/

/*************************************************************************************/
void setYellowOn()
{	
   unsigned int reg,value;

   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<YELLOW_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<YELLOW_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setYellowOff()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<YELLOW_LED_ADDR_BIT);
   gt_reg_write(reg,value);

   reg=OUT_ADDR;
   gt_reg_read(reg,&value);
   value &= ~(1<<YELLOW_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/
void setYellowBlink()
{
   unsigned int reg,value;
   reg=BLINK_ADDR;
   gt_reg_read(reg,&value);
   value |= (1<<YELLOW_LED_ADDR_BIT);
   gt_reg_write(reg,value);
}
/*************************************************************************************/

