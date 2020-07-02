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

void autoTask(void){

	float point1[2][5]={
			{5.0, 0.0, 0.0, 0.0, 0.0},
			{5.0, x, y, 0.0, 0.0}					//those points need to measure using robot, for now just leave it there
	};
	float point2[2][5]={
			{2.5, x, y, 0.0, 0.0},
			{2.5, x1, y1, 0.0, 0.0}
	};
	float point3[2][5]={
			{3.0, x1, y1, 0.0, 0.0},
			{3.0, x2, y2, 0.0, 0.0}
	};
	float point4[2][5]={
			{5.0, x2, y2, 0.0, 0.0},
			{5.0, x3, y3, 0.0, 0.0},
	};
	float point5[3][5]={
			{5.0, x3, y3, 0.0, 0.0},
			{5.0, x4, y4, 0.0, 0.0},
			{5.0, x5, y5, 0.0, 0.0},
			{5.0, x6, y6, 0.0, 0.0}
	};

	if(!ANA_receive && ppflag.flag1==0){
		jun = 1;
		ppflag.flag1 = 1;
	}else if(ppflag.flag2==1){
		jun = 3;
		ppflag.flag3 = 1;
	}else{
		jun = 2;
		ppflag.flag2 = 1;
	}

	if(IP18 && ppflag.flag3==1){
		jun = 4;
		ppflag.flag4 = 1;
	}

	if(LS_l1 && LS_l2 && ppflag.flag4==1){
		jun = 5;
		ppflag.flag5 = 1;
	}

	switch(jun){
		case 1 :	RNSPPstart(point1, 2, &rns);
					break;
		case 2 :	RNSPPstart(point2, 2, &rns);
					break;
		case 3 :	RNSPPstart(point3, 2, &rns);
					break;
		case 4 :	RNSPPstart(point4, 2, &rns);
					break;
		case 5 :	RNSPPstart(point5, 3, &rns);
					RNSStop(&rns);
						shootShagai_out;
							break;
		default :	break;
	}

}

int32_t pwAngleRead(QEI_TypeDef QEIx){

	const int ppr = 12;
	pwenc.pulse = QEIRead(QEIx);
	pwenc.delta_angle = pwenc.pulse/ppr * 360;
	if(LS_shagai){
		pwenc.angle = 0;
	}else{
		pwenc.angle += pwenc.delta_angle;
	}

	return pwenc.angle;
}

void no_shagai(int32_t angle, BDC_t* bdc, int32_t pwm){		//execute first angle =  pwAngleRead(QEIx); in main.c while(1)
	while(angle < horizontal_angle){						//measure the horizontal angle
		WriteBDC(&bdc, pwm);
	}
	StopBDC(&bdc);
}

void take_shagai(int32_t angle, BDC_t* bdc, int32_t pwm){	//execute first angle =  pwAngleRead(QEIx); in main.c while(1)
	while(angle > 0){
		WriteBDC(&bdc, pwm);								//pwm must be in negative
	}
	StopBDC(&bdc);
}

void got_shagai(int32_t angle, BDC_t* bdc, int32_t pwm){	//execute first angle =  pwAngleRead(QEIx); in main.c while(1)
	while(angle < shoot_angle){								//measure the shoot angle
		WriteBDC(&bdc, pwm);
	}
	StopBDC(&bdc);
}

void cylinderInit(void){
	shootShagai_in;
	shootFrisbee_in;
	reloadFrisbee_in;
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
