
#ifndef COMMON_H_
#define COMMON_H_

#include "adapter.h"


#define IP1  			GPIO_ReadInputDataBit(IP1_PIN)
#define IP2  			GPIO_ReadInputDataBit(IP2_PIN)
#define IP3  			GPIO_ReadInputDataBit(IP3_PIN)
#define IP4  			GPIO_ReadInputDataBit(IP4_PIN)
#define IP5  			GPIO_ReadInputDataBit(IP5_PIN)
#define IP6 			GPIO_ReadInputDataBit(IP6_PIN)
#define IP7  			GPIO_ReadInputDataBit(IP7_PIN)
#define IP8  			GPIO_ReadInputDataBit(IP8_PIN)
#define IP9  			GPIO_ReadInputDataBit(IP9_PIN)
#define IP10  			GPIO_ReadInputDataBit(IP10_PIN)
#define IP11  			GPIO_ReadInputDataBit(IP11_PIN)
#define IP12  			GPIO_ReadInputDataBit(IP12_PIN)
#define IP13  			GPIO_ReadInputDataBit(IP13_PIN)
#define IP14  			GPIO_ReadInputDataBit(IP14_PIN)
#define IP15			GPIO_ReadInputDataBit(IP15_PIN)
//
//#define LA 				GPIO_ReadInputDataBit(IP14_PIN)//
//#define LB 				GPIO_ReadInputDataBit(IP12_PIN)//
//#define LC 				GPIO_ReadInputDataBit(IP15_PIN)
//#define LD 				GPIO_ReadInputDataBit(IP11_PIN)
//#define LI 				GPIO_ReadInputDataBit(IP4_PIN)
//#define LO				GPIO_ReadInputDataBit(IP2_PIN)
//#define L3				GPIO_ReadInputDataBit(IP5_PIN)
//#define L2				GPIO_ReadInputDataBit(IP6_PIN)
//#define L1				GPIO_ReadInputDataBit(IP7_PIN)

#define height_high  	SR.cast[1].bit0=1
#define height_low	 	SR.cast[1].bit0=0
#define gereje_down		SR.cast[1].bit1=0
#define gereje_up		SR.cast[1].bit1=1
#define Wextend_out		SR.cast[1].bit4=1
#define Wextend_in		SR.cast[1].bit4=0
#define Bextend_out		SR.cast[1].bit5=1
#define Bextend_in		SR.cast[1].bit5=0
#define grab_out 		SR.cast[1].bit6=1
#define grab_in         SR.cast[1].bit6=0
#define shoot_out		SR.cast[1].bit7=1
#define shoot_in		SR.cast[1].bit7=0

#define InnerMotor(a)	WriteBDC(&BDC1,-a)
#define OuterMotor(a)	WriteBDC(&BDC2,-a)

//ANALOG PIN//
#define IP16	GPIO_ReadInputDataBit(IP16_Analog1_PIN)
#define IP17	GPIO_ReadInputDataBit(IP17_Analog2_PIN)
#define IP18	GPIO_ReadInputDataBit(IP18_Analog3_PIN)
#define IP19	GPIO_ReadInputDataBit(IP19_Analog4_PIN)
#define IP20	GPIO_ReadInputDataBit(IP20_Analog7_PIN)
#define IP21	GPIO_ReadInputDataBit(IP21_Analog8_PIN)


#define Mux1		 MUX.mux_data.bit0
#define Mux2		 MUX.mux_data.bit1
#define Mux3		 MUX.mux_data.bit2
#define Mux4		 MUX.mux_data.bit3
#define Mux5		 MUX.mux_data.bit4
#define Mux6		 MUX.mux_data.bit5
#define Mux7		 MUX.mux_data.bit6
#define Mux8		 MUX.mux_data.bit7

#define PB1 		GPIOB_IN->bit7
#define PB2 		GPIOE_IN->bit0

#define led1		GPIOC_OUT->bit13
#define led2		GPIOC_OUT->bit14
#define led3		GPIOC_OUT->bit15

typedef union{
	uint16_t flags;
	struct{
		unsigned flag1		:1;
		unsigned flag2 		:1;
		unsigned flag3		:1;
		unsigned flag4		:1;
		unsigned flag5		:1;
		unsigned flag6		:1;
		unsigned flag7 		:1;
		unsigned flag8		:1;
		unsigned flag9		:1;
		unsigned flag10		:1;
		unsigned flag11		:1;
		unsigned flag12		:1;
		unsigned flag13		:1;
		unsigned flag14		:1;
		unsigned flag15		:1;
		unsigned flag16		:1;
	};
}sys_t;

sys_t sys;



#define PS4Request(a)	I2CMasterReadII(a, 0x44, 10)

void RNS_config(CAN_TypeDef* CANx);

#endif /* COMMON_H_ */
