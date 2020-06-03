/*
 * DS3231.h
 *
 *  Created on: May 28, 2020
 *      Author: Pathfinder
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_



typedef struct RTC_t {
 I2C_HandleTypeDef* huart_sds;
 uint8_t second;
 uint8_t minute;
 uint8_t hour;
 uint8_t day;
 uint8_t month;
 uint16_t year;
} RTC_data;


typedef struct RTC_s {
 uint8_t second;
 uint8_t minute;
 uint8_t hour;
 uint8_t day;
 uint8_t month;
 uint16_t year;
} RTC_setup;



#define DS3231_ADDRESS              0x68


void DS3231_GetDateTime(RTC_data *rtc);
void DS3231_Init(RTC_data* rtc, I2C_HandleTypeDef *hi2c);
void DS3231_SetDateTime(RTC_setup *rtc);
int dayofweek(int Day, int Month, int Year);
#endif /* INC_DS3231_H_ */
