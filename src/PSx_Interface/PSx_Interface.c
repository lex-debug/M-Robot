/************************************************/
/*		 	 	Include Header	       		  	*/
/************************************************/
#include "PSx_Interface.h"

/************************************************/
/*		 	 	Variables	      	 		  	*/
/************************************************/
unsigned char PSxdata;

/************************************************/
/*		 	 	Functions		       		  	*/
/************************************************/

/*
 * Function Name		: PSxBTReceiveData
 * Function Description : This function is called to receive PSx data from arduino through UART.
 * Function Remarks		: Called in respective UART interrupt
 * Function Arguments	: *psxbt	,pointer to structure PSxBT_t
 * 						  USARTx	,x can be 1 to 6.
 * Function Return		: None
 * Function Example		: PSxBTReceiveData(&ps3x, USART1);
 */
void PSxBTReceiveData(PSxBT_t *psxbt, PSx psx, USART_TypeDef* USARTx)
{
	PSxdata = (unsigned char) ReadUART(USARTx);
	psxbt->ReceiveBuffer[psxbt->x++] = PSxdata;
	psxbt->psx1 = psx;
}

/*
 * Function Name		: PSx_HandlerUART
 * Function Description : This function is called to handle the received PSx data from UART.
 * Function Remarks		: Called after PSxBTReceiveData function
 * Function Arguments	: *psxbt	,pointer to structure PSxBT_t
 * Function Return		: None
 * Function Example		: PSx_HandlerUART(&ps3x);
 */
void PSx_HandlerUART(PSxBT_t *psxbt){
	static int i;
		if(PSxdata == '\n'){
			for (i = psxbt->x; i < PSxBTMAXLEN; i++){
				psxbt->ReceiveBuffer[i] = '\0';
			}
			psxbt->x = 0;

			if(psxbt->psx1 == PS4)
				sscanf(psxbt->ReceiveBuffer,"%u %u %u %d %d %d %d %d %d", &psxbt->buf1, &psxbt->buf2, &psxbt->buf3, &psxbt->leftjoy_x, &psxbt->leftjoy_y, &psxbt->rightjoy_x, &psxbt->rightjoy_y, &psxbt->an_L2, &psxbt->an_R2);
			else if(psxbt->psx1 == PS3)
				sscanf(psxbt->ReceiveBuffer,"%u %d %d %d %d %d %d", &psxbt->button, &psxbt->leftjoy_x, &psxbt->leftjoy_y, &psxbt->rightjoy_x, &psxbt->rightjoy_y, &psxbt->an_L2, &psxbt->an_R2);

			PSxBTGetXY(psxbt);
		}
}
/*
 * Function Name		: PSx_HandlerI2C
 * Function Description : This function is called to handle the received PSx data from I2C.
 * Function Remarks		: None
 * Function Arguments	: *psxbt	,pointer to structure PSxBT_t
 * Function Return		: None
 * Function Example		: PSx_HandlerI2C(&ps4x);
 */

void PSx_HandlerI2C(PSxBT_t *psxbt){
	psxbt->buf1 = psxbt->ReceiveBuffer[1];
	psxbt->buf2 = psxbt->ReceiveBuffer[2];
	psxbt->leftjoy_x = psxbt->ReceiveBuffer[3];
	psxbt->leftjoy_y = psxbt->ReceiveBuffer[4];
	psxbt->rightjoy_x = psxbt->ReceiveBuffer[5];
	psxbt->rightjoy_y = psxbt->ReceiveBuffer[6];
	psxbt->an_L2 = psxbt->ReceiveBuffer[7];
	psxbt->an_R2 = psxbt->ReceiveBuffer[8];
	psxbt->buf3 = psxbt->ReceiveBuffer[9];
	PSxBTGetXY(psxbt);
}

/*
 * Function Name		: PSxBTGetXY
 * Function Description : This function is called to normalise raw data.
 * Function Remarks		: None
 * Function Arguments	: *psxbt	,pointer to structure PSxBT_t
 * Function Return		: None
 * Function Example		: PSxBTGetXY(&ps3x);
 */

void PSxBTGetXY(PSxBT_t *psxbt)
{
	if(joyR_up){
		psxbt->joyR_y  = ((psx_low_Ry - ((float)psxbt->rightjoy_y))/100.0)/1.00;
		if(psxbt->joyR_y < 0.0){
			psxbt->joyR_y = 0.0;
		}else if(psxbt->joyR_y > 1.0){
			psxbt->joyR_y = 1.0;
		}
	}else if(joyR_down){
		psxbt->joyR_y = ((psx_high_Ry - ((float)psxbt->rightjoy_y))/100.0)/1.00;
		if(psxbt->joyR_y > 0.0){
			psxbt->joyR_y = 0.0;
 		}else if(psxbt->joyR_y < -1.0){
			psxbt->joyR_y = -1.0;
		}
	}else{
		psxbt->joyR_y = 0.0;
	}

	if(joyR_left){
		psxbt->joyR_x = ((psx_low_Rx - ((float)psxbt->rightjoy_x))/100.0)/1.00;
		if(psxbt->joyR_x < 0.0){
			psxbt->joyR_x = 0.0;
		}else if(psxbt->joyR_x > 1.0){
			psxbt->joyR_x = 1.0;
		}
	}else if(joyR_right){
		psxbt->joyR_x = ((psx_high_Rx - ((float)psxbt->rightjoy_x))/100.0)/1.00;
		if(psxbt->joyR_x > 0.0){
			psxbt->joyR_x = 0.0;
		}else if(psxbt->joyR_x < -1.0){
			psxbt->joyR_x = -1.0;
		}
	}else{
		psxbt->joyR_x = 0.0;
	}

	if(joyL_up){
		psxbt->joyL_y = ((psx_low_Ly - ((float)psxbt->leftjoy_y))/100.0)/1.00;
		if(psxbt->joyL_y < 0.0){
			psxbt->joyL_y = 0.0;
		}else if(psxbt->joyL_y > 1.0){
			psxbt->joyL_y = 1.0;
		}
	}else if(joyL_down){
		psxbt->joyL_y = ((psx_high_Ly - ((float)psxbt->leftjoy_y))/100.0)/1.00;
		if(psxbt->joyL_y > 0.0){
			psxbt->joyL_y = 0.0;
		}else if(psxbt->joyL_y < -1.0){
			psxbt->joyL_y = -1.0;
		}
	}else{
		psxbt->joyL_y = 0.0;
	}

	if(joyL_left){
		psxbt->joyL_x = ((psx_low_Lx - ((float)psxbt->leftjoy_x))/100.0)/1.00;
		if(psxbt->joyL_x < 0.0){
			psxbt->joyL_x = 0.0;
		}else if(psxbt->joyL_x > 1.0){
			psxbt->joyL_x = 1.0;
		}
	}else if(joyL_right){
		psxbt->joyL_x = ((psx_high_Lx - ((float)psxbt->leftjoy_x))/100.0)/1.00;
		if(psxbt->joyL_x > 0.0){
			psxbt->joyL_x = 0.0;
		}else if(psxbt->joyL_x < -1.0){
			psxbt->joyL_x = -1.0;
		}
	}else{
		psxbt->joyL_x = 0.0;
	}

	psxbt->joyR_2 = (psxbt->an_R2/255.0);
	psxbt->joyL_2 = (psxbt->an_L2/255.0);
}

