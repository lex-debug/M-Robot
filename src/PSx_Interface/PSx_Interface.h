/************************************************
 * Title   : PS3_INTERFACE
 * Author  : Kai Sheng, Qiu Hui and Leonard Chin
 * Version : 1.1
 * Date    : 29 JUNE 2017
 * **********************************************
 * Descriptions:
 * - used to interface with PS3 and PS4 through Arduino via I2C or UART
 *
 * Version History:
 * 1.0 - used to interface with PS3 through Arduino via I2C or UART
 *
 * Bugs:
 *
 ************************************************/

/***************************************
 * 		Include Libraries 			   *
 **************************************/
#ifndef PSX_INTERFACE_PSX_INTERFACE_H_
#define PSX_INTERFACE_PSX_INTERFACE_H_

#include "BIOS/bios.h"
#include "I2C/i2c.h"

/************************************************/
/*		    	Define         					*/
/************************************************/

#define 	PSxBTMAXLEN					40

#define 	psx_low_Lx					115.0
#define 	psx_high_Lx					140.0

#define 	psx_low_Ly					115.0
#define 	psx_high_Ly					140.0

#define 	psx_low_Rx					115.0
#define 	psx_high_Rx					140.0

#define 	psx_low_Ry					115.0
#define 	psx_high_Ry					140.0

#define 	joyL_up						(float)psxbt->leftjoy_y < psx_low_Ly
#define 	joyL_down					(float)psxbt->leftjoy_y > psx_high_Ly
#define 	joyL_left					(float)psxbt->leftjoy_x < psx_low_Lx
#define 	joyL_right					(float)psxbt->leftjoy_x > psx_high_Lx

#define 	joyR_up						(float)psxbt->rightjoy_y < psx_low_Ry
#define 	joyR_down					(float)psxbt->rightjoy_y > psx_high_Ry
#define 	joyR_left					(float)psxbt->rightjoy_x < psx_low_Rx
#define 	joyR_right					(float)psxbt->rightjoy_x > psx_high_Rx

//
#define SELECT	 0x01
#define	L3		 0x02
#define R3		 0x04
#define START1	 0x08
#define UP		 0x10
#define RIGHT	 0x20
#define DOWN	 0x40
#define LEFT	 0x80
#define L2		 0x0100
#define R2		 0x0200
#define L1  	 0x0400
#define R1 		 0x0800
#define TRIANGLE 0x1000
#define CIRCLE 	 0x2000
#define CROSS 	 0x4000
#define SQUARE 	 0x8000
#define TOUCH	 0x020000 //ps4

/************************************************/
/*				Struct         					*/
/************************************************/
typedef enum{
	PS3 = 3,
	PS4
}PSx;

typedef struct{

	char ReceiveBuffer[PSxBTMAXLEN];
	volatile unsigned char x;
    volatile int flag;
    PSx psx1;

	volatile unsigned int leftjoy_x;
	volatile unsigned int leftjoy_y;
	volatile unsigned int rightjoy_x;
	volatile unsigned int rightjoy_y;

	volatile unsigned int an_L2;
	volatile unsigned int an_R2;

	volatile float joyR_y;
	volatile float joyR_x;
	volatile float joyL_y;
	volatile float joyL_x;
	volatile float joyR_2;
	volatile float joyL_2;

	union{
		volatile unsigned int button;
		struct{
			char buf1;
			char buf2;
			char buf3;
			char buf4;
		};
	};
}PSxBT_t;

/**************************************************
 * 		STRUCTURE DEFINES					  	  *
 *************************************************/

/**************************************************
 * 		Function Prototype					  	  *
 *************************************************/
void PSxBTReceiveData(PSxBT_t *psxbt, PSx psx, USART_TypeDef* USARTx);
void PSx_HandlerUART(PSxBT_t *psxbt);
void PSx_HandlerI2C(PSxBT_t *psxbt);
void PSxBTGetXY(PSxBT_t *psxbt);

#endif /* PSX_INTERFACE_PSX_INTERFACE_H_ */
