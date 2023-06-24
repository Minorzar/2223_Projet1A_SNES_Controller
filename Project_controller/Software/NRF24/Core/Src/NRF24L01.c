#include "stm32l4xx_hal.h"
#include "NRF24L01.h"

// SPI_Handle
extern SPI_HandleTypeDef hspi1;
#define NRF24_SPI &hspi1

// Pin to be defined (WIP)
#define NRF24_CE_PORT	GPIOG
#define NRF24_CE_PIN	GPIO_PIN_X

#define NRF24_CSN_PORT	GPIOG
#define NRF24_CSN_PIN	GPIO_PIN_Y


void CE_Select(void){
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_SET);
}
void CE_Unselect(void){
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_RESET);
}
void CSN_Enable(void){
	HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_SET);
}
void CSN_Disable(void){
	HAL_GPIO_WritePin(NRF24_CSN_PORT, NRF24_CSN_PIN, GPIO_PIN_RESET);
}

void nrf24_WriteReg(uint8_t Reg, uint8_t Data){
	uint8_t buf[2];
	buf[0] = Reg|1<<5;		// W_REGISTER	001A AAAA	(Page 48)
	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CSN_Select();

	// SPI_Handler, Data, Size, Timeout
	HAL_SPI_Transmit(NRF24_SPI, buf, 2, 1000);

	// Pull the CS Pin HIGH to release the device
	CSN_Unselect();
}

// Write multiple bytes starting from a particular register
void nrf24_WriteRegMulti(uint8_t Reg, uint8_t *data, int size){
	uint8_t buf[2];
	buf[0] = Reg|1<<5;		// W_REGISTER	001A AAAA	(Page 48)
//	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CSN_Select();

	// SPI_Handler, Data, Size, Timeout
	HAL_SPI_Transmit(NRF24_SPI, buf, 1, 100);
	HAL_SPI_Transmit(NRF24_SPI, data, size, 1000);

	// Pull the CS Pin HIGH to release the device
	CSN_Unselect();
}

void nrf24_ReadReg(uint8_t Reg){
	uint8_t data = 0;

	// Pull the CS Pin LOW to select the device
	CSN_Select();

	// SPI_Handler, Data, Size, Timeout
	HAL_SPI_Transmit(NRF24_SPI, Reg, 1, 100);
	HAL_SPI_Receive(NRF24_SPI, &data, 1, 100);

	// Pull the CS Pin HIGH to release the device
	CSN_Unselect();

	return data;
}

// Read multiple bytes from the register
void nrf24_ReadRegMulti(uint8_t Reg, uint8_t *data, int size){
	// Pull the CS Pin LOW to select the device
	CSN_Select();

	// SPI_Handler, Data, Size, Timeout
	HAL_SPI_Transmit(NRF24_SPI, Reg, 1, 100);
	HAL_SPI_Receive(NRF24_SPI, &data, size, 1000);

	// Pull the CS Pin HIGH to release the device
	CSN_Unselect();

	return data;
}

// Send command to the NRF
void nrf24_SendCommand(uint8_t cmd){
	// Pull the CS Pin LOW to select the device
	CSN_Select();

	// SPI_Handler, Data, Size, Timeout
	HAL_SPI_Transmit(NRF24_SPI, &cmd, 1, 100);

	// Pull the CS Pin HIGH to release the device
	CSN_Unselect();

	return data;
}


// Initialising the NRF
void nrf24_Init(uint8_t cmd){
	// Disable the chip before configuring the device
	CE_Disable();
	CS_Unselect();

	// Configurations
	nrf24_WriteReg(CONFIG, 0);		// Config (WIP)
	nrf24_WriteReg(EN_AA, 0);		// Auto Acknowledgement (No auto ACK)
	nrf24_WriteReg(EN_RXADDR, 0);	// Receiver data pipe (WIP: Disabled)
	nrf24_WriteReg(SETUP_AW, 0x03);	// Address width (11: 5 bytes)
	nrf24_WriteReg(SETUP_RETR, 0);	// No retransmission (not needed since no ACK)
	nrf24_WriteReg(RF_CH, 0);		// Channel (WIP)
	nrf24_WriteReg(RF_SETUP, 0x0E);	// Setup (1110: power = 0 dB, data rate = 2 Mbps)

	return data;
}

