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

void nrf24_WriteRegister1bit(uint8_t reg , uint8_t data){
	uint8_t buf[2] ;
	buf[0] = reg | 1<<5 ;
	buf[1] = data ;

	nrf24_ToggleCSCE(1); // Put the CS pin low

	HAL_SPI_Transmit(&hspi1,buf,2,1000);

	nrf24_ToggleCSCE(0); // Put the CS pin up
}

void nrf24_WriteRegisterNbit(uint8_t reg , uint8_t* data ,int size){
	uint8_t buf[2] ;
	buf[0] = reg | 1<<5 ;

	nrf24_ToggleCSCE(1); // Put the CS pin low

	HAL_SPI_Transmit(&hspi1,buf,1,100);
	HAL_SPI_Transmit(&hspi1,data,size,1000);


	nrf24_ToggleCSCE(0); // Put the CS pin up
}

uint8_t nrf24_ReadRegister1bit(uint8_t reg){
	uint8_t data ;

	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1,&reg,1,100) ;
	HAL_SPI_Receive(&hspi1,&data,1,100) ;

	nrf24_ToggleCSCE(1) ;

	return data ;
}

void nrf24_ReadRegisterNbit(uint8_t reg, uint8_t *data, int size){
	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1, &reg, 1, 100);
	HAL_SPI_Receive(&hspi1, data, size, 1000);

	nrf24_ToggleCSCE(1) ;
}

void nrf24_CmdTransmit(uint8_t cmd){
	nrf24_ToggleCSCE(0) ;

	HAL_SPI_Transmit(&hspi1,&cmd,1,100) ;

	nrf24_ToggleCSCE(1) ;
}

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
	}
}




void nrf24_Init(){
	nrf24_ToggleCSCE(3);
	nrf24_ToggleCSCE(1);

	nrf24_reset (0);
	nrf24_WriteRegister1bit(CONFIG, 0);
	nrf24_WriteRegister1bit(EN_AA, 0);  // No Auto ACK
	nrf24_WriteRegister1bit (EN_RXADDR, 0);
	nrf24_WriteRegister1bit (SETUP_AW, 0x03); // Define the 5 byte for adresses
	nrf24_WriteRegister1bit (SETUP_RETR, 0);
	nrf24_WriteRegister1bit (RF_CH, 0);  // will be setup during Tx or RX, currently disable

	nrf24_WriteRegister1bit (RF_SETUP, 0x0E);   // Setup the Power at 0db and data rate at 2Mbps

	nrf24_ToggleCSCE(2);
	nrf24_ToggleCSCE(0);

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

void nrf24_TxMode(uint8_t *Address, uint8_t channel){
	nrf24_ToggleCSCE(3);

	nrf24_WriteRegister1bit(RF_CH, channel);
	nrf24_WriteRegisterNbit(TX_ADDR, Address, 5);

	uint8_t config = nrf24_ReadRegister1bit(CONFIG);
	config = config & (0xF2);
	nrf24_WriteRegister1bit(CONFIG, config);

	nrf24_ToggleCSCE(2);
}

int nrf24_Transmit (uint8_t *data){
	uint8_t cmd;

	nrf24_ToggleCSCE(0);

	cmd = W_TX_PAYLOAD;

	HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);
	HAL_SPI_Transmit(&hspi1, data, 32, 1000);

	nrf24_ToggleCSCE(1);

	HAL_Delay(1);

	uint8_t fifostatus = nrf24_ReadRegister1bit(FIFO_STATUS);

	if ((fifostatus&(1<<4)) && (!(fifostatus&(1<<3)))){
		cmd = FLUSH_TX;
		nrf24_CmdTransmit(cmd);

		nrf24_reset(FIFO_STATUS);

		return 1;
	}
	return 0;
}


