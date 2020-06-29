#ifndef COMMON_C_
#define COMMON_C_

#include "common.h"
#include "math.h"

void RNS_config(CAN_TypeDef* CANx) {
	RNSInit(CANx, &rns);
	led3 = 1;
	BIOSDelay(500);
	RNSSet(&rns, RNS_DEVICE_CONFIG, (float) 0b11100101, (float) fwd_omni,
			(float) roboconPID);
	RNSSet(&rns, RNS_X_Y_ENC_CONFIG, 0.05 / 2000.0 * 3.142, 2.0,
			0.05 / 2000.0 * 3.142, 2.0); //1.0 for nonswap , 2.0 for swap
	RNSSet(&rns, RNS_F_KCD_PTD, 2636.018 / 2412.559, 0.127 * 3.142 / 263.6018);
	RNSSet(&rns, RNS_B_KCD_PTD, 2420.540 / 2410.963, 0.127 * 3.142 / 242.0540);

	RNSSet(&rns, RNS_F_LEFT_VEL_SATEU, 1.0, 1.0 / 7.390, 19999.0);
	RNSSet(&rns, RNS_F_LEFT_VEL_PID, 1.5, 1.0, 0.0); //1.5,1.7

	RNSSet(&rns, RNS_F_RIGHT_VEL_SATEU, 1.0, 1.0 / 8.203, 19999.0);
	RNSSet(&rns, RNS_F_RIGHT_VEL_PID, 1.0, 1.0, 0.0); //1.65,1.7

	RNSSet(&rns, RNS_B_LEFT_VEL_SATEU, 1.0, 1.0 / 8.236, 19999.0);
	RNSSet(&rns, RNS_B_LEFT_VEL_PID, 1.0, 1.0, 0.0);

	RNSSet(&rns, RNS_B_RIGHT_VEL_SATEU, 1.0, 1.0 / 7.851, 19999.0);
	RNSSet(&rns, RNS_B_RIGHT_VEL_PID, 1.5, 1.0, 0.0);
//function of odn use in rns,speed,pulse per rotation,meter per rotation

	RNSSet(&rns, RNS_PPInit);
	RNSSet(&rns, RNS_LF_LSA_POS, (float) AT_FRONT, (float) AT_LEFT,
			(float) AT_BACK, (float) AT_RIGHT);
}

void manual_mode(void) {



		if (ps4.button == R1){
			speed = speed + 1.0;
			while (ps4.button == R1);
		}
		else if (ps4.button == L1){
			speed = speed - 1.0;
			while (ps4.button == L1);
		}

		if(ps4.button == SELECT){
			manual=0;
		}
		xr = ps4.joyL_x * -speed;
		yr = ps4.joyL_y * speed;
		wa = (ps4.joyR_2 * 1.5) - (ps4.joyL_2 * 1.5);

		if (yr == 0 && xr == -0 && wa == 0.0) {
			//RNSStop(&rns);
		} else {
			MODN(&Modn);
			//RNSVelocity(v1, v2, v3, v4, &rns);

	}
}

void enq (void){
	//Enquiring pos and angle
	RNSEnquire(RNS_X_Y_POS, &rns);
	xpos = rns.enq.enq_buffer[0].data;
	ypos = rns.enq.enq_buffer[1].data;

	RNSEnquire(RNS_ANGLE, &rns);
	z = rns.enq.enq_buffer[0].data;
}

void var_init (void){

	//Timer global variable

	speed = 1.0;
	manual = 0;

	MODNWheelVelInit(&v1, &v2, &v3, &v4, &Modn);
	MODNRobotVelInit(&xr, &yr, &wa, &Modn);
	MODNRobotBaseInit(MODN_FWD_OMNI, 1.0, 0.0, &Modn);

}

#endif /* COMMON_C_ */
