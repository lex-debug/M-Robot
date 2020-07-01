#include "main.h"

int main(void) {
	Initialize();

	BIOSTIMx_Init(TIM6, 20000, 84, 2, 1);



	RNS_config(CAN1);

	var_init();

	while (1) {
		angle = pwAngleRead(QEIx);					//x can be 1, 4, 6
		
		if(jun = 4){
			take_shagai(angle, &BDC1, );
		}else if(jun < 4){
			no_shagai(angle, &BDC1, );
		}else{
			got_shagai(angle, &BDC1, );
		}
		
		if(ps4.button==CIRCLE && ps4.button!=SELECT){
			manual = 0;
			autoflag = 1;
		}
		
		if(ps4.button!=CIRCLE && ps4.button==SELECT){
			manual=1;
			autoflag = 0;
		}


		while (manual) {
			manual_mode();
		}
		
		while(autoflag){
			autoTask();
		}
	}
	return 0;
}

void TIM6_DAC_IRQHandler(void) {

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		led1 = !led1;


		PS4Request(I2C1);
		PSx_HandlerI2C(&ps4);
	}
	return;
}
