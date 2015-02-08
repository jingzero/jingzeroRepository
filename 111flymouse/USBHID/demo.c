/*----------------------------------------------------------------------------
 * Name:    demo.c
 * Purpose: USB HID Demo
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H>                        /* LPC17xx definitions */

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "uart.h"


#include "demo.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
U8 InReport;                                /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

U8 OutReport;                               /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////																						
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SYS_H
 #define __SYS_H         
 #include <lpc17xx.h>

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

 
 #define LPC_GPIO0_PIN_Addr    (0x2009c014) //
 #define LPC_GPIO1_PIN_Addr    (0x2009c034) //
 #define LPC_GPIO2_PIN_Addr    (0x2009c054) //
 #define LPC_GPIO3_PIN_Addr    (0x2009c074) //
 #define LPC_GPIO4_PIN_Addr    (0x2009c094) //

#define P0(n)    BIT_ADDR(LPC_GPIO0_PIN_Addr,n)   
 
#define P1(n)    BIT_ADDR(LPC_GPIO1_PIN_Addr,n)  
 
#define P2(n)    BIT_ADDR(LPC_GPIO2_PIN_Addr,n)  

#define P3(n)    BIT_ADDR(LPC_GPIO3_PIN_Addr,n)  

#define P4(n)    BIT_ADDR(LPC_GPIO4_PIN_Addr,n)  
 
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
//U8   GucLastX = 0, GucCurX = 0;                                      /* X轴的上一次与当前的位置值    */
//U8   GucLastY = 0, GucCurY = 0;                                      /* Y轴的上一次与当前的位置值    */
//U8   GucLastZ = 0, GucCurZ = 0;                                      /* Z轴的上一次与当前的位置值    */
//U8   Keyzuo = 0,Keyyou=0 ,Keyzhong=0 ; 
//*********************************************************************************************************
U8 MyReportkey[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
U8 MyReportmouse[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
U8 Keyzuo    =0;
U8 Keyyou    =0;
U8 Keyzhong  =0;
U8 GucCurX   =0;                      
U8 GucLastX  =0;
U8 GucCurY   =0;
U8 GucLastY  =0;
U8 MouseTransMode = 0;

float AddX =0;

float accel[3] = {0x00,0x00,0x00};
float omiga[3] = {0,0,0};
float angle[3] = {0,0,0};
U8 Temple=0;



	
	extern volatile uint32_t UART0Count; 
	extern volatile uint8_t UART0Buffer[BUFSIZE]; 
  extern U8 sign0 ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------------
  Get HID Input Report -> InReport
 *------------------------------------------------------------------------------*/
void GetInReport (void) 
	{
			InReport = 0x00;
			MyReportmouse[0] = 0x02;MyReportkey[0] = 0x01;
			MyReportmouse[1] = 0x00;MyReportkey[1] = 0x00;
			MyReportmouse[2] = 0x00;MyReportkey[2] = 0x00;
			MyReportmouse[3] = 0x00;MyReportkey[3] = 0x00;
			MyReportmouse[4] = 0x00;MyReportkey[4] = 0x00;
			MyReportmouse[5] = 0x00;MyReportkey[5] = 0x00;
			MyReportmouse[6] = 0x00;MyReportkey[6] = 0x00;
			MyReportmouse[7] = 0x00;MyReportkey[7] = 0x00;
			MyReportmouse[8] = 0x00;MyReportkey[8] = 0x00;
			
		if(P2(10) == 0)
		{	
//			MyReportkey[4] = 0x52;
			MyReportmouse[4] = 0x01;               ////调试接口
		}
		if(P0(7) == 0)
			{
				MouseTransMode=~MouseTransMode;
			}
		if(P0(0) == 0)
			{	
				MyReportkey[4] = 0x1A;                 //////////////// W
			}
		if(P0(1) == 0)
			{	
				MyReportkey[4] = 0x16;                 //////////////// S
			}
		if(P0(11) == 0)
			{	
				MyReportkey[5] = 0x04;                 //////////////// D
			}
		if(P0(10) == 0)
			{	
				MyReportkey[5] = 0x07;                 //////////////// A
			}
		if(P0(20) == 0)
			{	
				 MyReportkey[1] = 0xE1;                //////////////// LEFT SHIFT
			}
		if(P0(21) == 0)
			{	
         MyReportkey[6]= 0x2C;       /////////////spacebarf
			}
		if(P0(22) == 0)
			{	
				 MyReportkey[1] = 0xE0;                 //////////////// LEFT CTRL
			}
		if(P2(4) == 0)
			{	
				MyReportkey[5] = 0x0A;                 //////////////// G
			}
		if(P2(5) == 0)
			{	
				MyReportkey[5] = 0x09;                 //////////////// F
			}
		if(P2(6) == 0)
			{	
				MyReportkey[5] = 0x15;                 //////////////// R
			}		
		if(P0(8) == 0)
			{	
				MyReportmouse[1]=(MyReportmouse[1] | 0x01);                           //////////////// zuo
			}
		if(P0(9) == 0)
			{	
				MyReportmouse[1]=(MyReportmouse[1] | 0x02);                          //////////////// you
			}			
		if(P2(7) == 0)
			{	
				MyReportmouse[4] = 1;                  ////////////////  GUN LUN +
			}      
		if(P2(8) == 0)
			{	
				MyReportmouse[4] = -5;                 ////////////////  GUN LUN -
			}
	//		MyReportmouse[1] = (U8)(Keyzuo|Keyyou|Keyzhong);
			if(MouseTransMode == 0)
				{
					GucCurX=angle[2]*32;
			    GucCurY=angle[0]*32;
					MyReportmouse[2] = (U8)( GucLastX - GucCurX );              /* X: 发送x变化值               */
					MyReportmouse[3] = (U8)( GucCurY -GucLastY );              /* Y: 发送y变化值               */
					GucLastX=GucCurX;
					GucLastY=GucCurY;
				}
	//				MyReportmouse[4] = 0;

	}


/*------------------------------------------------------------------------------
  Set HID Output Report <- OutReport
 *------------------------------------------------------------------------------*/
void SetOutReport (void) {
  static unsigned long led_mask[] = { 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7 };
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (OutReport & (1<<i)) {
      LPC_GPIO2->FIOPIN |= led_mask[i];
    } else {
      LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}





/*------------------------------------------------------------------------------
  Main Program
 *------------------------------------------------------------------------------*/
int main (void) 
	{

			SystemInit();                               /* initialize clocks */
			
			
			USB_Init();                                 /* USB Initialization */
			USB_Connect(__TRUE);                        /* USB Connect */
			LPC_SC->PCONP|=(1<<15); 
		  LPC_GPIO0->FIODIR0 = 000000000000000000000000000000000000 ;
			UARTInit(0, 115200);	/* baud rate setting */

			while (1)
				{
					if(sign0)
					{
						sign0=0;
							if(UART0Buffer[0]==0x55)
							{
								switch(UART0Buffer[1])
									{
										case 0x51:		
										accel[0]=(UART0Buffer[3]<<8|UART0Buffer[2])/32768.0*16;
										if(accel[0]>17) accel[0]=accel[0]-32;
										accel[1]=(UART0Buffer[5]<<8|UART0Buffer[4])/32768.0*16;
										if(accel[1]>17) accel[1]=accel[1]-32;
										accel[2]=(UART0Buffer[7]<<8|UART0Buffer[6])/32768.0*16;
                    if(accel[2]>17) accel[2]=accel[2]-32;										
										Temple = (UART0Buffer[9]<<8|UART0Buffer[8])/340.0+36.25;
										
										break;
										case 0x52:
										omiga[0] = (UART0Buffer[3]<<8| UART0Buffer[2])/32768.0*2000;
										omiga[1] = (UART0Buffer[5]<<8| UART0Buffer[4])/32768.0*2000;
										omiga[2] = (UART0Buffer[7]<<8| UART0Buffer[6])/32768.0*2000;
										Temple = (UART0Buffer[9]<<8| UART0Buffer[8])/340.0+36.25;
								
										break;
										case 0x53:
										angle[0] = (UART0Buffer[3]<<8| UART0Buffer[2])/32768.0*180;
										angle[1] = (UART0Buffer[5]<<8| UART0Buffer[4])/32768.0*180;
										angle[2] = (UART0Buffer[7]<<8| UART0Buffer[6])/32768.0*180;
										Temple = (UART0Buffer[9]<<8| UART0Buffer[8])/340.0+36.25;
									
										break;
								 }
						 }
					 }
			}
	}


