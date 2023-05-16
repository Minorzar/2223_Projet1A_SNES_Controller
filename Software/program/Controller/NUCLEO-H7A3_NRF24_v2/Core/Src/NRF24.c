/*
 *
 * NRF24 Library for project Snes_ENSEA2025
 * Date: 16/05/2023
 * Author: Gauthier BIEHLER
 * Document: NRF24.c
 *
 */



#include "NRF24.h"

/*
 *
 *
 * Start of the initialisation of the NRF24
 *
 *
 */




/*
 *
 * nrf24_ToggleCSCE will be used to select or unselect the device.
 * As for the value of sel:
 * 0 -> CS up
 * 1 -> CS down
 * 2 -> CE up
 * 3 -> CE down
 *
 *
 */
void nrf24_ToggleCSCE(uint8_t sel){
	switch (sel){
	case 0: HAL_GPIO_WritePin(GPIO_CS_Port,GPIO_CS_Pin,GPIO_PIN_SET) ;
			break ;
	case 1: HAL_GPIO_WritePin(GPIO_CS_Port,GPIO_CS_Pin,GPIO_PIN_RESET) ;
			break ;
	case 2: HAL_GPIO_WritePin(GPIO_CE_Port,GPIO_CE_Pin,GPIO_PIN_SET) ;
			break ;
	case 3: HAL_GPIO_WritePin(GPIO_CE_Port,GPIO_CE_Pin,GPIO_PIN_RESET) ;
			break ;
	}
}



/*
 *
 *
 * nrf24_WriteRegister1bit will be use to write 1 bit of data inside one register using SPI connection
 *
 *
 */
void nrf24_WriteRegister1bit(uint8_t reg , uint8_t data){
	uint8_t buf[2] ;
	buf[0] = reg | 1<<5 ;
	buf[1] = data ;

	nrf24_ToggleCSCE(1); // Put the CS pin low

	HAL_SPI_Transmit(&hspi1,buf,2,1000);

	nrf24_ToggleCSCE(0); // Put the CS pin up
}



/*
 *
 *
 * nrf24_WriteRegisterNbit will be use to write N bit (N = size) of data inside one register using SPI connection
 *
 *
 */
void nrf24_WriteRegisterNbit(uint8_t reg , uint8_t* data ,int size){
	uint8_t buf[2] ;
	buf[0] = reg | 1<<5 ;

	nrf24_ToggleCSCE(1); // Put the CS pin low

	HAL_SPI_Transmit(&hspi1,buf,1,100);
	HAL_SPI_Transmit(&hspi1,data,size,1000);


	nrf24_ToggleCSCE(0); // Put the CS pin up
}



/*
 *
 *
 * nrf24_ReadRegister1bit will be use to read 1 bit of data inside one register using SPI connection.
 * It will be return inside a uint8_t data.
 *
 *
 */
uint8_t nrf24_ReadRegister1bit(uint8_t reg){
	uint8_t data ;

	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1,&reg,1,100) ;
	HAL_SPI_Receive(&hspi1,&data,1,100) ;

	nrf24_ToggleCSCE(1) ;

	return data ;
}



/*
 *
 *
 * nrf24_ReadRegisterNbit will be use to read N bit (N = size) of data inside one register using SPI connection.
 * It will be stored inside a uint8_t data.
 *
 *
 */
void nrf24_ReadRegisterNbit(uint8_t reg, uint8_t *data, int size){
	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1, &reg, 1, 100);
	HAL_SPI_Receive(&hspi1, data, size, 1000);

	nrf24_ToggleCSCE(1) ;
}



/*
 *
 *
 * nrf24_CmdTransmit will be use to send a command to the nrf24 using SPI connection.
 *
 *
 */
void nrf24_CmdTransmit(uint8_t cmd){
	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1,&cmd,1,100) ;

	nrf24_ToggleCSCE(1) ;
}



/*
 *
 *
 * nrf24_reset will be use to reset the registers of the nrf24 to their original value.
 *
 *
 */
void nrf24_reset(uint8_t Reg){

	switch(Reg){

	case STATUS:
		nrf24_WriteRegister1bit(STATUS, 0x00);
		break ;

	case FIFO_STATUS:
		nrf24_WriteRegister1bit(FIFO_STATUS, 0x11);
		break ;

	default:
		nrf24_WriteRegister1bit(CONFIG, 0x08);
		nrf24_WriteRegister1bit(EN_AA, 0x3F);
		nrf24_WriteRegister1bit(EN_RXADDR, 0x03);
		nrf24_WriteRegister1bit(SETUP_AW, 0x03);
		nrf24_WriteRegister1bit(SETUP_RETR, 0x03);
		nrf24_WriteRegister1bit(RF_CH, 0x02);
		nrf24_WriteRegister1bit(RF_SETUP, 0x0E);
		nrf24_WriteRegister1bit(STATUS, 0x00);
		nrf24_WriteRegister1bit(OBSERVE_TX, 0x00);
		nrf24_WriteRegister1bit(CD, 0x00);

		uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegisterNbit(RX_ADDR_P0, rx_addr_p0_def, 5);

		uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
		nrf24_WriteRegisterNbit(RX_ADDR_P1, rx_addr_p1_def, 5);

		nrf24_WriteRegister1bit(RX_ADDR_P2, 0xC3);
		nrf24_WriteRegister1bit(RX_ADDR_P3, 0xC4);
		nrf24_WriteRegister1bit(RX_ADDR_P4, 0xC5);
		nrf24_WriteRegister1bit(RX_ADDR_P5, 0xC6);

		uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegisterNbit(TX_ADDR, tx_addr_def, 5);

		nrf24_WriteRegister1bit(RX_PW_P0, 0);
		nrf24_WriteRegister1bit(RX_PW_P1, 0);
		nrf24_WriteRegister1bit(RX_PW_P2, 0);
		nrf24_WriteRegister1bit(RX_PW_P3, 0);
		nrf24_WriteRegister1bit(RX_PW_P4, 0);
		nrf24_WriteRegister1bit(RX_PW_P5, 0);
		nrf24_WriteRegister1bit(FIFO_STATUS, 0x11);
		nrf24_WriteRegister1bit(DYNPD, 0);
		nrf24_WriteRegister1bit(FEATURE, 0);
		break;
	}
}



/*
 *
 *
 * nrf24_Init will initialise the nrf24.
 *
 *
 */
void nrf24_Init(){
	nrf24_ToggleCSCE(3);

	nrf24_reset(0);
	nrf24_WriteRegister1bit(CONFIG, 0);
	nrf24_WriteRegister1bit(EN_AA, 0);  // No Auto ACK
	nrf24_WriteRegister1bit(EN_RXADDR, 0);
	nrf24_WriteRegister1bit(SETUP_AW, 0x03); // Define the 5 byte for adresses
	nrf24_WriteRegister1bit(SETUP_RETR, 0);
	nrf24_WriteRegister1bit(RF_CH, 0);  // will be setup during Tx or RX, currently disable

	nrf24_WriteRegister1bit (RF_SETUP, 0x0E);   // Setup the Power at 0db and data rate at 2Mbps

	nrf24_ToggleCSCE(2);

}

/*
 *
 *
 * End of the initialisation of the NRF24
 *
 *
 */



/*
 *
 *
 * Start of the TX configuration
 *
 *
 */



/*
 *
 *
 * nrf24_TxMode will be use to activate the Transmit mode.
 *
 *
 */
void nrf24_TxMode(uint8_t *Address, uint8_t channel){
	nrf24_ToggleCSCE(3);

	nrf24_WriteRegister1bit(RF_CH, channel);
	nrf24_WriteRegisterNbit(TX_ADDR, Address, 5);

	uint8_t config = nrf24_ReadRegister1bit(CONFIG);
	config = config & (0xF2);
	nrf24_WriteRegister1bit(CONFIG, config);

	nrf24_ToggleCSCE(2);
}



/*
 *
 *
 * nrf24_Transmit will be use to transmit data using the nrf24.
 * It will return a 1 if it succeed to send the data, otherwise it will return a 0.
 *
 *
 */
HAL_StatusTypeDef nrf24_Transmit(uint8_t *data){
	uint8_t cmd;

	nrf24_ToggleCSCE(0);

	cmd = W_TX_PAYLOAD;

	HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);
	HAL_StatusTypeDef hal_status = HAL_SPI_Transmit(&hspi1, data, 32, 1000);

	nrf24_ToggleCSCE(1);

	HAL_Delay(100);

	return hal_status;
}

/*
 *
 *
 * End of the TX configuration
 *
 *
 */

/*
 *
 *
 * Start of the RX configuration
 *
 *
 */



/*
 *
 *
 * nrf24_RxMode will be use to activate the Receive mode.
 *
 *
 */
void nrf24_RxMode(uint8_t *Address, uint8_t channel){
	nrf24_ToggleCSCE(3);

	nrf24_reset(STATUS);

	nrf24_WriteRegister1bit(RF_CH, channel);

	uint8_t en_rxaddr = nrf24_ReadRegister1bit(EN_RXADDR);
	en_rxaddr = en_rxaddr | (1<<2);
	nrf24_WriteRegister1bit(EN_RXADDR, en_rxaddr);

	/*
	 *
	 * Pipe 1 ADDR = 0xAABBCCDD11
	 * Pipe 2 ADDR = 0xAABBCCDD22
	 * Pipe 3 ADDR = 0xAABBCCDD33
	 *
	 */

	nrf24_WriteRegisterNbit(RX_ADDR_P1, Address, 5);
	nrf24_WriteRegister1bit(RX_ADDR_P2, 0xEE);

	nrf24_WriteRegister1bit(RX_PW_P2, 32);   // Size of 2 bytes for the data pipe 2 (will be set as 2)

	uint8_t config = nrf24_ReadRegister1bit(CONFIG);
	config = config | (1<<1) | (1<<0);
	nrf24_WriteRegister1bit(CONFIG, config);

	nrf24_ToggleCSCE(2);
}



/*
 *
 *
 * nrf24_DataAvailable will be use to determine if their has been data received in the pipe in entry.
 * If their is, it will return a 1, otherwise a 0.
 *
 *
 */
uint8_t nrf24_DataAvailable(int pipe){
	uint8_t status = nrf24_ReadRegister1bit(STATUS);

	if ((status&(1<<6))&&(status&(pipe<<1))){

		nrf24_WriteRegister1bit(STATUS, (1<<6));

		return 1;
	}
	return 0;
}



/*
 *
 *
 * nrf24_Receive will be use to receive data using the nrf24.
 *
 *
 */
HAL_StatusTypeDef nrf24_Receive(uint8_t *data){
	uint8_t cmd = 0;

	nrf24_ToggleCSCE(0);

	cmd = R_RX_PAYLOAD;

	HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);
	HAL_StatusTypeDef hal_status = HAL_SPI_Receive(&hspi1, data, 32, 1000);

	nrf24_ToggleCSCE(1);

	HAL_Delay(100);

	cmd = FLUSH_RX;
	nrf24_CmdTransmit(cmd);

	return hal_status ;
}

/*
 *
 *
 * End of the RX configuration
 *
 *
 */
