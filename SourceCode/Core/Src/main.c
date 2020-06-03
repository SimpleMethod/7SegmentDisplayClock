/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <DS3231.h>
#include <gps_neo6.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

RTC_data rtc;	// Date and Time variable
RTC_setup rtc_setup;

uint8_t muttexButton1 = 0;
uint8_t muttexButton2 = 0;
uint8_t muttexButton3 = 0;
uint8_t configMode = 0;

uint8_t alarmHour = 0;
uint8_t alarmMinute = 0;
uint8_t alarmDeactivate = 0;

/** Config mode 1 */

signed short timeOffset = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/*
 void vprint(const char *fmt, va_list argp) {
 char string[200];
 if (0 < vsprintf(string, fmt, argp)) // build string
 {
 HAL_UART_Transmit(&huart2, (uint8_t*) string, strlen(string), 0xffffff); // send message via UART
 }
 }

 void my_printf(const char *fmt, ...) // custom printf() function
 {
 va_list argp;
 va_start(argp, fmt);
 vprint(fmt, argp);
 va_end(argp);
 }
 */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void SprintHour_1(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(HOUR_1_D_GPIO_Port, HOUR_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_1_C_GPIO_Port, HOUR_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_B_GPIO_Port, HOUR_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_1_A_GPIO_Port, HOUR_1_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void SprintHour_2(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HOUR_2_C_GPIO_Port, HOUR_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_B_GPIO_Port, HOUR_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HOUR_2_A_GPIO_Port, HOUR_2_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void SprintMinute_1(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(MINUTE_1_D_GPIO_Port, MINUTE_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_1_C_GPIO_Port, MINUTE_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_B_GPIO_Port, MINUTE_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_1_A_GPIO_Port, MINUTE_1_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void SprintMinute_2(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(MINUTE_2_D_GPIO_Port, MINUTE_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MINUTE_2_C_GPIO_Port, MINUTE_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_B_GPIO_Port, MINUTE_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MINUTE_2_A_GPIO_Port, MINUTE_2_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void SprintSecond_1(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(SECOND_1_D_GPIO_Port, SECOND_1_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_1_C_GPIO_Port, SECOND_1_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_B_GPIO_Port, SECOND_1_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_1_A_GPIO_Port, SECOND_1_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void SprintSecond_2(int digit) {
	switch (digit) {
	case 0:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(SECOND_2_D_GPIO_Port, SECOND_2_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SECOND_2_C_GPIO_Port, SECOND_2_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_B_GPIO_Port, SECOND_2_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SECOND_2_A_GPIO_Port, SECOND_2_A_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void BuzzerActivate(int delay) {
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
	HAL_Delay(delay);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}

void DisplayHour(int digit) {
	int part1 = digit / 10;
	int part2 = digit % 10;
	SprintHour_1(part1);
	SprintHour_2(part2);
}

void DisplayMinute(int digit) {
	int part1 = digit / 10;
	int part2 = digit % 10;
	SprintMinute_1(part1);
	SprintMinute_2(part2);
}

void DisplaySecond(int digit) {
	int part1 = digit / 10;
	int part2 = digit % 10;
	SprintSecond_1(part1);
	SprintSecond_2(part2);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	NEO6_Init(&GpsState, &huart1);
	DS3231_Init(&rtc, &hi2c1);
	uint32_t Timer = HAL_GetTick();
	uint8_t update = 0;
	BuzzerActivate(40);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (update == 0) {
			NEO6_Task(&GpsState);
		}

		if ((HAL_GetTick() - Timer) > 100) {

			if (GpsState.Year != 00) {
				if (update == 0) {

					rtc_setup.hour = GpsState.Hour;
					rtc_setup.minute = GpsState.Minute;
					rtc_setup.second = GpsState.Second;
					rtc_setup.day = GpsState.Day;
					rtc_setup.month = GpsState.Month;
					rtc_setup.year = GpsState.Year + 2000;
					DS3231_SetDateTime(&rtc_setup);
					BuzzerActivate(200);
				}
				update = 1;

			}
			if (configMode != 2) {
				DS3231_GetDateTime(&rtc);
				DisplayHour(rtc.hour + timeOffset);
				DisplayMinute(rtc.minute);
				DisplaySecond(rtc.second);

				if (alarmHour == rtc.hour + timeOffset
						&& alarmMinute == rtc.minute && alarmDeactivate == 0) {
					BuzzerActivate(300);
					HAL_Delay(100);
					BuzzerActivate(300);
					alarmDeactivate = 1;
				}

			} else {
			}
			Timer = HAL_GetTick();
		}

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			HOUR_1_D_Pin | HOUR_1_C_Pin | HOUR_1_A_Pin | HOUR_1_B_Pin
					| MINUTE_1_A_Pin | SECOND_1_B_Pin | BUZZER_Pin
					| HOUR_2_C_Pin | HOUR_2_B_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			LD2_Pin | SECOND_2_D_Pin | SECOND_1_D_Pin | SECOND_1_A_Pin
					| SECOND_2_C_Pin | HOUR_2_A_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			MINUTE_2_D_Pin | SECOND_2_A_Pin | MINUTE_2_C_Pin | SECOND_2_B_Pin
					| MINUTE_1_B_Pin | MINUTE_1_D_Pin | MINUTE_2_B_Pin
					| MINUTE_2_A_Pin | MINUTE_1_C_Pin | SECOND_1_C_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(HOUR_2_D_GPIO_Port, HOUR_2_D_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : HOUR_1_D_Pin HOUR_1_C_Pin HOUR_1_A_Pin HOUR_1_B_Pin
	 MINUTE_1_A_Pin SECOND_1_B_Pin BUZZER_Pin HOUR_2_C_Pin
	 HOUR_2_B_Pin */
	GPIO_InitStruct.Pin = HOUR_1_D_Pin | HOUR_1_C_Pin | HOUR_1_A_Pin
			| HOUR_1_B_Pin | MINUTE_1_A_Pin | SECOND_1_B_Pin | BUZZER_Pin
			| HOUR_2_C_Pin | HOUR_2_B_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : LD2_Pin SECOND_2_D_Pin SECOND_1_D_Pin SECOND_1_A_Pin
	 SECOND_2_C_Pin HOUR_2_A_Pin */
	GPIO_InitStruct.Pin = LD2_Pin | SECOND_2_D_Pin | SECOND_1_D_Pin
			| SECOND_1_A_Pin | SECOND_2_C_Pin | HOUR_2_A_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : BUTTON_2_Pin BUTTON_1_Pin */
	GPIO_InitStruct.Pin = BUTTON_2_Pin | BUTTON_1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : MINUTE_2_D_Pin SECOND_2_A_Pin MINUTE_2_C_Pin SECOND_2_B_Pin
	 MINUTE_1_B_Pin MINUTE_1_D_Pin MINUTE_2_B_Pin MINUTE_2_A_Pin
	 MINUTE_1_C_Pin SECOND_1_C_Pin */
	GPIO_InitStruct.Pin = MINUTE_2_D_Pin | SECOND_2_A_Pin | MINUTE_2_C_Pin
			| SECOND_2_B_Pin | MINUTE_1_B_Pin | MINUTE_1_D_Pin | MINUTE_2_B_Pin
			| MINUTE_2_A_Pin | MINUTE_1_C_Pin | SECOND_1_C_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : BUTTON_3_Pin */
	GPIO_InitStruct.Pin = BUTTON_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(BUTTON_3_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : HOUR_2_D_Pin */
	GPIO_InitStruct.Pin = HOUR_2_D_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HOUR_2_D_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == GpsState.neo6_huart) {
		NEO6_ReceiveUartChar(&GpsState);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN) {

	if (GPIO_PIN == BUTTON_1_Pin) {
		if (muttexButton1 == 0) {
			if (configMode == 1) {
				configMode = 0;
			} else if (configMode == 2) {
				alarmHour = alarmHour + 1;
				DisplayHour(alarmHour);
				if (alarmHour >= 24) {
					alarmHour = 0;
				}
			} else {
				configMode = 1;
			}
			muttexButton1 = 1;
		}

	}

	if (GPIO_PIN == BUTTON_2_Pin) {
		if (muttexButton2 == 0) {
			if (configMode == 1) {
				timeOffset = timeOffset + 1;
			} else if (configMode == 2) {
				configMode = 0;
			} else {
				configMode = 2;
				alarmDeactivate = 0;
				DisplayHour(0);
				DisplayMinute(0);
				DisplaySecond(0);
			}

			muttexButton2 = 1;
		}
	}
	if (GPIO_PIN == BUTTON_3_Pin) {
		if (muttexButton3 == 0) {
			if (configMode == 1) {
				timeOffset = timeOffset - 1;
			} else if (configMode == 2) {
				alarmMinute = alarmMinute + 1;
				DisplayMinute(alarmMinute);
				if (alarmMinute >= 60) {
					alarmMinute = 0;
				}
			}
			muttexButton3 = 1;
		}
	}

	muttexButton1 = 0;
	muttexButton2 = 0;
	muttexButton3 = 0;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
