#include "main.h"
#include "gps_neo6.h"
#include "string.h"
#include "stdlib.h"

volatile uint8_t UartReceivedChar;


char* strtoke(char *str, const char *delim)
{
  static char *start = NULL;
  char *token = NULL;
  if (str) start = str;
  if (!start) return NULL;
  token = start;
  start = strpbrk(start, delim);
  if (start) *start++ = '\0';
  return token;
}

void NEO6_ReceiveUartChar(NEO6_State *GpsStateHandler)
{
	uint8_t TempHead;

	TempHead = (GpsStateHandler->UartBufferHead + 1) % GPS_UART_BUFFER_SIZE;

	if( TempHead == GpsStateHandler->UartBufferTail) // No room for new data
	{
		GpsStateHandler->UartBufferHead = GpsStateHandler->UartBufferTail;
	}
	else
	{
		if(UartReceivedChar == 13)
		{
			GpsStateHandler->UartBufferLines++;
			GpsStateHandler->UartBufferHead = TempHead;
			GpsStateHandler->UartBuffer[TempHead] = UartReceivedChar;
		}
		else if(UartReceivedChar == 10)
		{

		}
		else
		{
			GpsStateHandler->UartBufferHead = TempHead;
			GpsStateHandler->UartBuffer[TempHead] = UartReceivedChar;
		}

	}

	HAL_UART_Receive_IT(GpsStateHandler->neo6_huart, (uint8_t*)&UartReceivedChar, 1);
}

int NEO6_GetCharFromBuffer(NEO6_State *GpsStateHandler)
{
	if(GpsStateHandler->UartBufferHead == GpsStateHandler->UartBufferTail)
	{
		return -1;
	}
	GpsStateHandler->UartBufferTail = (GpsStateHandler->UartBufferTail + 1) % GPS_UART_BUFFER_SIZE;

	return GpsStateHandler->UartBuffer[GpsStateHandler->UartBufferTail];
}

int NEO6_GetLineFromBuffer(NEO6_State *GpsStateHandler)
{
	char TempChar;
	char* LinePointer = (char*)GpsStateHandler->WorkingBuffer;
	if(GpsStateHandler->UartBufferLines)
	{
		while((TempChar = NEO6_GetCharFromBuffer(GpsStateHandler)))
		{
			if(TempChar == 13)
			{
				break;
			}
			*LinePointer = TempChar;
			LinePointer++;
		}
		*LinePointer = 0;
		GpsStateHandler->UartBufferLines--;
	}
	return 0;
}


void NEO6_ParseGPRMC(NEO6_State *GpsStateHandler)
{
	char *ParsePoiner;
	uint32_t Temp;

	ParsePoiner = strtoke(NULL, ",");
	if(strlen(ParsePoiner) > 0)
	{
		Temp = atoi(ParsePoiner);
		GpsStateHandler->Second = Temp % 100;
		GpsStateHandler->Minute = (Temp / 100) % 100;
		GpsStateHandler->Hour = (Temp / 10000) % 100;
	}
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	ParsePoiner = strtoke(NULL, ",");
	if(strlen(ParsePoiner) > 0)
	{
		Temp = atoi(ParsePoiner);
		GpsStateHandler->Year = Temp % 100;
		GpsStateHandler->Month = (Temp / 100) % 100;
		GpsStateHandler->Day = (Temp / 10000) % 100;
	}
}



uint8_t NEO6_IsFix(NEO6_State *GpsStateHandler)
{
	return GpsStateHandler->Quality;
}

void NEO6_Task(NEO6_State *GpsStateHandler)
{
	if(GpsStateHandler->UartBufferLines)
	{
		NEO6_GetLineFromBuffer(GpsStateHandler);
		if(strcmp(strtoke((char*)GpsStateHandler->WorkingBuffer, ","), "$GPRMC") == 0) NEO6_ParseGPRMC(GpsStateHandler);
	}
}

void NEO6_Init(NEO6_State *GpsStateHandler, UART_HandleTypeDef *huart)
{
	GpsStateHandler->neo6_huart = huart;
	GpsStateHandler->UartBufferHead = 0;
	GpsStateHandler->UartBufferTail = 0;
	GpsStateHandler->UartBufferLines = 0;

	GpsStateHandler->Hour = 0;
	GpsStateHandler->Minute = 0;
	GpsStateHandler->Second = 0;
	GpsStateHandler->Day = 0;
	GpsStateHandler->Month = 0;
	GpsStateHandler->Year = 0;

	HAL_UART_Receive_IT(GpsStateHandler->neo6_huart, (uint8_t*)&UartReceivedChar, 1);
}
