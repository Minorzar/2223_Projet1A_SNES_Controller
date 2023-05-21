/*
 *
 * NRF24 Library for project Snes_ENSEA2025
 * Date: 16/05/2023
 * Author: Gauthier BIEHLER
 * Document: NRF24.h
 *
 */



#include "stm32h7xx_hal.h"


// Constant used for registers

#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define OBSERVE_TX 0x08
#define RPD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

 // Constant used for pin

#define GPIO_CS_Port GPIOA
#define GPIO_CE_Port GPIOC
#define GPIO_CS_Pin GPIO_PIN_4
#define GPIO_CE_Pin GPIO_PIN_5
extern SPI_HandleTypeDef hspi1;

// Constant Mnemonic

#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

// Macro declaration

#define CS_UP 0b0001
#define CS_DOWN 0b0010
#define CE_UP 0b0100
#define CE_DOWN 0b1000

// Declaration of function

void nrf24_ToggleCSCE(uint8_t) ;
void nrf24_WriteRegister1bit(uint8_t, uint8_t) ;
void nrf24_WriteRegisterNbit(uint8_t, uint8_t*, int) ;
void nrf24_ShowMemory(void) ;
uint8_t nrf24_ReadRegister1bit(uint8_t) ;
void nrf24_ReadRegisterNbit(uint8_t, uint8_t*, int) ;
void nrf24_CmdTransmit(uint8_t) ;
void nrf24_reset(uint8_t) ;
void nrf24_Init(void) ;
void nrf24_TxMode (uint8_t* , uint8_t) ;
HAL_StatusTypeDef nrf24_Transmit (uint8_t*) ;
void nrf24_RxMode(uint8_t*, uint8_t) ;
uint8_t nrf24_DataAvailable(int) ;
HAL_StatusTypeDef nrf24_Receive(uint8_t*) ;
