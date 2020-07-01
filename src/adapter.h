/*******************************************************************************
 * Title   :
 * Author  :
 * Version :
 * Date    :
 *******************************************************************************
 * Description:
 *
 * Version History:
 *
 * Bugs:
 *
 ******************************************************************************/

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include "BIOS/bios.h"
#include <math.h>
#include "CAN/can.h"
#include "RNS_interface\RNS_interface.h"
#include "PSx_Interface/PSx_Interface.h"
#include "I2C/i2c.h"
#include "MODN/MODN.h"
#include "PIDABT/PID/PID.h"
#include "PIDABT/ABT/ABT.h"

#define MUX1_INPUT_PIN 		GPIOE , GPIO_Pin_1
#define MUX1_S0_PIN 		GPIOE , GPIO_Pin_2
#define MUX1_S1_PIN 		GPIOE , GPIO_Pin_3
#define MUX1_S2_PIN 		GPIOE , GPIO_Pin_4

#define SR_SCK_PIN			GPIOE , GPIO_Pin_7
#define SR_RCK_PIN			GPIOE , GPIO_Pin_8
#define SR_SI_PIN			GPIOE , GPIO_Pin_10

#define UART2_Tx			GPIOD , GPIO_Pin_5
#define UART2_Rx			GPIOD , GPIO_Pin_6

#define UART3_Tx			GPIOD , GPIO_Pin_9
#define UART3_Rx			GPIOD , GPIO_Pin_8

#define UART4_Tx			GPIOC , GPIO_Pin_10
#define UART4_Rx			GPIOC , GPIO_Pin_11

#define UART5_Tx			GPIOC , GPIO_Pin_12
#define UART5_Rx			GPIOD , GPIO_Pin_2

#define CAN1_Tx				GPIOD , GPIO_Pin_1
#define CAN1_Rx				GPIOD , GPIO_Pin_0

#define CAN2_Tx				GPIOB , GPIO_Pin_13
#define CAN2_Rx				GPIOB , GPIO_Pin_12

#define QEI1_PLUSEA_PIN		GPIOE , GPIO_Pin_9
#define QEI1_PLUSEB_PIN		GPIOE , GPIO_Pin_11

#define QEI4_PLUSEA_PIN		GPIOD , GPIO_Pin_12
#define QEI4_PLUSEB_PIN		GPIOD , GPIO_Pin_13

#define QEI6_PLUSEA_PIN		GPIOC , GPIO_Pin_6
#define QEI6_PLUSEB_PIN		GPIOC , GPIO_Pin_7

#define TIM5_CHANNEL1_PIN	GPIOA, GPIO_Pin_0
#define TIM5_CHANNEL2_PIN	GPIOA, GPIO_Pin_1
#define TIM5_CHANNEL3_PIN	GPIOA, GPIO_Pin_2
#define TIM5_CHANNEL4_PIN	GPIOA, GPIO_Pin_3

#define TIM9_CHANNEL1_PIN	GPIOE, GPIO_Pin_5
#define TIM9_CHANNEL2_PIN	GPIOE, GPIO_Pin_6

#define TIM3_CHANNEL3_PIN	GPIOB, GPIO_Pin_0
#define TIM3_CHANNEL4_PIN	GPIOB, GPIO_Pin_1

#define LED1_PIN			GPIOC, GPIO_Pin_13
#define LED2_PIN			GPIOC, GPIO_Pin_14
#define LED3_PIN			GPIOC, GPIO_Pin_15

#define PB1_PIN				GPIOB, GPIO_Pin_7
#define PB2_PIN				GPIOE, GPIO_Pin_0

#define IP1_PIN				GPIOE, GPIO_Pin_12
#define IP2_PIN				GPIOE, GPIO_Pin_13
#define IP3_PIN				GPIOE, GPIO_Pin_14
#define IP4_PIN				GPIOE, GPIO_Pin_15
#define IP5_PIN				GPIOB, GPIO_Pin_14
#define IP6_PIN				GPIOB, GPIO_Pin_15
#define IP7_PIN				GPIOD, GPIO_Pin_10
#define IP8_PIN				GPIOD, GPIO_Pin_11
#define IP9_PIN				GPIOC, GPIO_Pin_8
#define IP10_PIN			GPIOA, GPIO_Pin_10
#define IP11_PIN			GPIOD, GPIO_Pin_3
#define IP12_PIN			GPIOD, GPIO_Pin_4
#define IP13_PIN			GPIOD, GPIO_Pin_7
#define IP14_PIN			GPIOB, GPIO_Pin_5
#define IP15_PIN			GPIOB, GPIO_Pin_6

#define IP16_Analog1_PIN	GPIOC, GPIO_Pin_0
#define IP17_Analog2_PIN	GPIOC, GPIO_Pin_1
#define IP18_Analog3_PIN	GPIOC, GPIO_Pin_2
#define IP19_Analog4_PIN	GPIOC, GPIO_Pin_3
#define IP20_Analog7_PIN	GPIOC, GPIO_Pin_4
#define IP21_Analog8_PIN	GPIOC, GPIO_Pin_5

#define SPI1_NSS_PIN		GPIOA, GPIO_Pin_4
#define SPI1_SCK_PIN		GPIOA, GPIO_Pin_5
#define SPI1_MISO_PIN		GPIOA, GPIO_Pin_6
#define SPI1_MOSI_PIN		GPIOA, GPIO_Pin_7

MUX_t MUX;
shiftreg_t SR;
RNS_interface_t rns;
BDC_t BDC1, BDC2, BDC3, BDC4, BDC5, BDC6, BDC7, BDC8;
uint8_t insData_receive[2];
PSxBT_t ps4;
MODN_t Modn;
ABT_t filter;
PID_t Pid;

//Global Declarations
float v1, v2, v3, v4, wa, xr, yr;                 //MODN variables
float xpos, ypos, z;                              //Encoder Values
int flag;
int manual, autoflag;
int counter;                                      //global timer variable
float speed;                                      //for manual control
int jun;
int32_t angle;

union{
	float data;
	struct{
		char byte1;
		char byte2;
		char byte3;
		char byte4;
	};
}buf1_receive[2];
union{
	float data;
	struct{
		char byte1;
		char byte2;
		char byte3;
		char byte4;
	};
}buf2_receive[2];


void CAN_PROCESS(void);
void Initialize (void);
void slave_rcv(unsigned char length, unsigned char *pdata);
void PS4_rcv(unsigned char length, unsigned char *pdata);
// void manual_mode (void);
// void enq (void);
// void var_init (void);

#endif /* ADAPTER_H_ */
