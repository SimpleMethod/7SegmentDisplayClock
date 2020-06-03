/*
 * DS3231.cpp
 *
 *  Created on: May 28, 2020
 *      Author: Pathfinder
 */


#include "main.h"
#include "DS3231.h"


I2C_HandleTypeDef *hi2c_ds3231;
uint8_t Ds3231Buffer[7];

uint8_t bcd2dec(uint8_t BCD)
{
	//return (((BCD & 0xF0)>>4) *10) + (BCD & 0xF);
	 return ((BCD / 16 * 10) + (BCD % 16));
}

uint8_t dec2bcd(uint8_t DEC)
{
	//return ((DEC / 10)<<4) + (DEC % 10);
	 return ((DEC / 10 * 16) + (DEC % 10));
}


void DS3231_GetDateTime(RTC_data *rtc)
{
	HAL_I2C_Mem_Read(hi2c_ds3231, DS3231_ADDRESS<<1, 0x00, 1, Ds3231Buffer, 7, 100);
	rtc->second = bcd2dec(Ds3231Buffer[0]);
	rtc->minute= bcd2dec(Ds3231Buffer[1]);
	rtc->hour = bcd2dec(Ds3231Buffer[2] & 0x3F);
	rtc->day = bcd2dec(Ds3231Buffer[4]);
	rtc->month = bcd2dec(Ds3231Buffer[5] & 0x1F);
	rtc->year = 2000 + bcd2dec(Ds3231Buffer[6]);

}

int dayofweek(int Day, int Month, int Year)
{
    int Y, C, M, N, D;
    M = 1 + (9 + Month) % 12;
    Y = Year - (M > 10);
    C = Y / 100;
    D = Y % 100;
    N = ((13 * M - 1) / 5 + D + D / 4 + 6 * C + Day + 5) % 7;
    return (7 + N) % 7;
}


void DS3231_SetDateTime(RTC_setup *rtc)
{
	uint8_t tmp[7];

	tmp[0] = dec2bcd(rtc->second);
	tmp[1] = dec2bcd(rtc->minute);
	tmp[2] = dec2bcd(rtc->hour);
	tmp[3] = dayofweek(rtc->day, rtc->month, rtc->year) + 1;
	tmp[4] = dec2bcd(rtc->day);
	tmp[5] = dec2bcd(rtc->month);
	tmp[6] = dec2bcd(rtc->year - 2000);
	HAL_I2C_Mem_Write(hi2c_ds3231, DS3231_ADDRESS<<1, DS3231_REG_TIME, 1, tmp, 7, 100);
}

void DS3231_Init(RTC_data *rtc, I2C_HandleTypeDef *hi2c)
{
	rtc->huart_sds=hi2c;
	hi2c_ds3231=hi2c;
}
