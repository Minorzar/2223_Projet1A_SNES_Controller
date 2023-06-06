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
