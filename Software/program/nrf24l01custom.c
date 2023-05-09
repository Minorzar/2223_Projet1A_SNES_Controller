uint8_t tx_command  = 0b10100000;
uint8_t rx_command = 0b01100001;
#define W_REGISTER_command 0x0
#define CONFIG 0x0
#define EN_AA 0x1
uint8_t CONFIG_command = W_REGISTER_command + CONFIG;
uint8_t CONFIG_value = 0b00000010;
uint8_t EN_AA_command = W_REGISTER_command + EN_AA;
uint8_t EN_AA_value = 0b00000000;

//passage du mode STANDBY-1 au mode RX ou TX
void nrf24_RX_TX_Enable(void){
	HAL_GPIO_WritePin(SPI_CE_Port, SPI_CE_Pin, GPIO_PIN_SET);
}

//passage du mode RX ou TX au mode STANDBY-1 
void nrf24_RX_TX_Disable(void){
	HAL_GPIO_WritePin(SPI_CE_Port, SPI_CE_Pin, GPIO_PIN_RESET);
}

//Transmission de données sans fil
void nrf24_Transmit(pData){
	nrf24_RX_TX_Enable();
	HAL_SPI_Transmit(&hspi1,&tx_command,1,0);
	HAL_SPI_Transmit(&hspi1,pData+8,1,0);
	HAL_SPI_Transmit(&hspi1,pData,1,0);
	nrf24_RX_TX_Disable();
}

//Réception de données sans fil
void nrf24_Receive(pData){
	nrf24_RX_TX_Enable();
	HAL_SPI_Transmit(&hspi1,&rx_command,1,0);
	HAL_SPI_Receive(&hspi1,pData+8,1,0);
	HAL_SPI_Receive(&hspi1,pData,1,0);
	nrf24_RX_TX_Disable();
}

//Ecriture dans les registres du nrf24
void nrf24_W_REGISTER(uint8_t register, uint8_t value){
	HAL_SPI_Transmit(&hspi1, &register, 1, 0);
	HAL_SPI_Transmit(&hspi1, &value, 1, 0);
}
