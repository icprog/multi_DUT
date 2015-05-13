#include "VersionAndLog.h"
#include <stdio.h>


/*
	print the result 
*/
void PrintPassFail(bool bPassFail)
{
    if(!bPassFail)
    {
		printf("\r\n");
		printf("========================================================================\n");
        printf("FFFFFFFFFF     AA        IIIIII    LL          EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("FFFFFFFFFF   AA  AA      IIIIII    LL          EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("FF          AA    AA       II      LL          EE          DD   DD    !!\r\n");
		printf("FF          AA    AA       II      LL          EE          DD    DD   !!\r\n");
		printf("FFFFFF      AAAAAAAA       II      LL          EEEEEE      DD    DDD  !!\r\n");
		printf("FFFFFF      AAAAAAAA       II      LL          EEEEEE      DD    DDD  !!\r\n");
		printf("FF          AA    AA       II      LL          EE          DD    DD   !!\r\n");
		printf("FF          AA    AA     IIIIII    LLLLLLLLLL  EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("FF          AA    AA     IIIIII    LLLLLLLLLL  EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("========================================================================\n");
		printf("Board is not functioning properly.\r\n");
    }
    else
    {
        printf("\r\n");
		printf("========================================================================\n");
        printf("PPPPPPPPP      AA      SSSSSSSSSS   SSSSSSSSS  EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("PPPPPPPPPP   AA  AA   SSSSSSSSSSS  SSSSSSSSSS  EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("PP      PP  AA    AA  SS           SS          EE          DD   DD    !!\r\n");
		printf("PP      PP  AA    AA  SS           SS          EE          DD    DD   !!\r\n");
		printf("PPPPPPPPP   AAAAAAAA   SSSSSSSSS    SSSSSSSS   EEEEEE      DD    DDD  !!\r\n");
		printf("PPPPPPPP    AAAAAAAA   SSSSSSSSS    SSSSSSSS   EEEEEE      DD    DDD  !!\r\n");
		printf("PP          AA    AA           SS          SS  EE          DD    DD   !!\r\n");
		printf("PP          AA    AA           SS          SS  EE          DD   DD    !!\r\n");
		printf("PP          AA    AA  SSSSSSSSSSS  SSSSSSSSSS  EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("PP          AA    AA  SSSSSSSSSS   SSSSSSSSS   EEEEEEEEEE  DDDDDD     !!\r\n");
		printf("========================================================================\n");
		printf("### Board passed all tests!!! ###\r\n");
    }

}

/*
	print the program version
*/
void PrintTheVersion()
{

   printf("*******************************************************************************\n");
   printf("\n");
   printf("               Test program, version:%s .\n", SOFTWARE_VERSION);
   printf("               Copyright(C) Ambt Micro system.   \n");
   printf("               PE II RD Software Team     \n");
   printf("\n");
   printf("*******************************************************************************\n");

}


