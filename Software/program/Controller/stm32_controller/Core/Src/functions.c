#ifndef __fonction_H__
#define __fonction_H__

#include "stm32l4xx_hal.h"

#define LED_DEVICE           0x15
#define LED_REGISTER         0x6
#define LED_ENABLE           0x10

extern uint8_t LED_Buf[2];
extern uint8_t LED_ADDRESS;
extern I2C_HandleTypeDef hi2c1;


void LED_Init(){
	LED_Buf[1] = LED_ENABLE;
	int i;
	for(i=0;i<=15;i++){
		LED_Buf[0] = LED_REGISTER + 4*i + 1;
		HAL_I2C_Master_Transmit(&hi2c1, LED_ADDRESS, LED_Buf, 2, HAL_MAX_DELAY);
	}
}



void LED_Write(uint8_t lednum, uint8_t state){
	LED_Buf[0] = LED_REGISTER + 4*lednum + 3;
	if (state == 0){
		LED_Buf[1] = LED_ENABLE;
	}
	else{
		LED_Buf[1] = 0;
	}
	HAL_I2C_Master_Transmit(&hi2c1, LED_ADDRESS, LED_Buf, 2, HAL_MAX_DELAY);
}

#endif
