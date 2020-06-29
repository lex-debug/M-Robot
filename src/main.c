#include "main.h"

int main(void) {
	Initialize();

	BIOSTIMx_Init(TIM6, 20000, 84, 2, 1);



	RNS_config(CAN1);

	var_init();

	while (1) {
		if(ps4.button==SELECT)
		manual=1;


		while (manual) {
			manual_mode();
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
