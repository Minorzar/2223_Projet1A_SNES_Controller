/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NRF24.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// This is where every macro I use in the code is implemented
/*
 * UARTTXBUFFERSIZE is the size use for the TX buffer when communicating with uart
 * UARTRXBUFFERSIZE is the size use for the RX buffer when communicating with uart
 * LED2_PORT is use to control the port of the user LED 2
 * LED2_PIN is use to control the pin of the user LED 2
 *
 */
#define UARTTXBUFFERSIZE 32
#define UARTRXBUFFERSIZE 32
#define LED2_PORT GPIOE
#define LED2_PIN GPIO_PIN_1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// This is where the basic declaration are made
/*
 * uartTxBuffer is the buffer use for TX mode with uart communication
 * uartRxBuffer is the buffer use for RX mode with uart communication
 * huart3 is the uart configuration we are using
 * uartFlag is a flag the indicate whether or not a communication has been made from the computer to the board
 * mode indicate in which mode (between TX and RX) we are with SPI communication
 * msglu is use to indicate that a message has been receive with uart communication
 * RxPipeAddrs is the adress of the receiving pipe for the NRF24
 * myRxData is the buffer that will receive the data
 * myAckPayload is the payload that will indicate if the communication has really been made
 * TxpipeAddrs is the adress of the transmitting pipe for NRF24
 * myTxData is the text that will be send during test phase
 * AckPayload is the buffer that will be use for collecting the data of the ACK payload
 *
 */
extern char uartTxBuffer[UARTTXBUFFERSIZE];
extern char uartRxBuffer[UARTRXBUFFERSIZE];
extern UART_HandleTypeDef huart3;
extern uint8_t uartFlag;
int mode ;

char* msglu = "\r\nMessage recu !\r\n";

//RX mode
uint64_t RxpipeAddrs = 0x11223344AA;
char myRxData[50];
char myAckPayload[32] = "Ack by STM32H7!";

//TX mode
uint64_t TxpipeAddrs = 0x11223344AA;
char myTxData[32] = "Hello World!";
char AckPayload[32];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART3_UART_Init();
	MX_USB_OTG_HS_USB_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
	HAL_UART_Transmit(&huart3, (uint8_t*) "Booting...\r\n",12,100);


	/*
	 *
	 * This is where the configuration of the NRF24 is made, the only thing needed to change from TX to RX is to comment the instruction for TX or RX
	 * depending on which mode you want to use.
	 *
	 */
	// TX mode
	mode = 0;

	//RX mode
	//mode = 1;



	switch(mode){
	case 0:										// Configuration for TX mode
		NRF24_begin(hspi1);						// Initialise the NRF24 with default value and link to hspi1
		nrf24_DebugUART_Init(huart3);			// Use to make sure huart3 is connected

		printRadioSettings();					// A first print of the setting of the NRF24

		NRF24_stopListening();					// This is to disable the NRF24 while we continue the setup
		NRF24_openWritingPipe(TxpipeAddrs);		// This setup the TX pipe
		NRF24_setAutoAck(true);					// Configure the auto acknowledge
		NRF24_setChannel(52);					// Confire the channel where the NRF24 will be communicating
		NRF24_setPayloadSize(32);				// Define the payload size

		NRF24_enableDynamicPayloads();			// Enable the Dynamic payload (must be enable for ACK mode)
		NRF24_enableAckPayload();				// Enable the ACK payload (must be enable for ACK mode)
		break;
	case 1:										// Configuration for RX mode
		NRF24_begin(hspi1);						// Initialise the NRF24 with default value and link to hspi1
		nrf24_DebugUART_Init(huart3);			// Use to make sure huart3 is connected

		printRadioSettings();					// A first print of the setting of the NRF24

		NRF24_setAutoAck(true);					// Configure the auto acknowledge
		NRF24_setChannel(52);					// Configure the channel where the NRF24 will be communicating
		NRF24_setPayloadSize(32);				// Define the payload size
		NRF24_openReadingPipe(1, RxpipeAddrs);	// This setup the RX pipe
		NRF24_enableDynamicPayloads();			// Enable the Dynamic payload (must be enable for ACK mode)
		NRF24_enableAckPayload();				// Enable the ACK payload (must be enable for ACK mode)

		NRF24_startListening();					// Enable the listening of the NRF24
		break;
	}


	printRadioSettings();						// Print the final configuration of the NRF24

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1){
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		/*
		 *
		 * The first part is set to test the uart communication
		 * at first, it was suppose to be: pc -> uart -> board 1 -> spi -> NRF24 TX -> NRF24 RX -> spi -> board 2 -> uart -> pc
		 * Everytime a g is entered, it will print the current memory of every register of the NRF24
		 * In other cases, it will just make the second user LED flicker.
		 *
		 */
		if(uartFlag == 1){
			switch(uartRxBuffer[0]){
			case 'g' :
				HAL_UART_Transmit(&huart3,(uint8_t*) "et informations for nrf24\r\n",27,100);
				void NRF24_ShowMemory() ;
				break;
			default :
				HAL_GPIO_TogglePin(LED2_PORT,  LED2_PIN) ;
				HAL_UART_Transmit(&huart3, (uint8_t*) msglu, 18, 100) ;
				HAL_GPIO_TogglePin(LED2_PORT,  LED2_PIN) ;
				break;
			}
			uartFlag = 0 ;
		}


		/*
		 *
		 * This is the code for the NRF24.
		 * The case 0 is for the transmission
		 * The NRF24_read is to confirm that the AckPayload has been filled.
		 * The rest of the code is to transmit to the uart (this is mainly for test purpose)
		 *
		 * The case 1 is for the receive
		 * It first check if there is data available then will put it in the RxData buffer.
		 * The rest is also to transmit to the uart for test purpose
		 *
		 */
		switch(mode){
		case 0:
			if(NRF24_write(myTxData, 32)){
				NRF24_read(AckPayload, 32);
				HAL_UART_Transmit(&huart3, (uint8_t *)"Transmitted Successfully\r\n", strlen("Transmitted Successfully\r\n"), 10);

				char myDataack[80];
				sprintf(myDataack, "AckPayload:  %s \r\n", AckPayload);
				HAL_UART_Transmit(&huart3, (uint8_t *)myDataack, strlen(myDataack), 10);
			}
			break;
		case 1:
			if(NRF24_available()){
				NRF24_read(myRxData, 32);
				NRF24_writeAckPayload(1, myAckPayload, 32);
				myRxData[32] = '\r'; myRxData[32+1] = '\n';
				HAL_UART_Transmit(&huart3, (uint8_t *)myRxData, 32+2, 10);
			}
			break ;
		}

		HAL_Delay(1000);


	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/*AXI clock gating */
	RCC->CKGAENR = 0xFFFFFFFF;

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
			|RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV4;
	RCC_OscInitStruct.HSICalibrationValue = 64;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 280;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
			|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief Peripherals Common Clock Configuration
 * @retval None
 */
void PeriphCommonClock_Config(void)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/** Initializes the peripherals clock
	 */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
	PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
