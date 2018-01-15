/*
 * main.c
 *
 *  Created on: Nov 17, 2017
 *      Author: abel
 */

//#include <util/delay.h>
//#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart_receive.h"
#include "i2c_lcd_pc8574.h"

#define BUFFER_SIZE 20
#define DELAY_IN_MICROSECONDS 1000U

char Rx_string_buff[BUFFER_SIZE] = { 0 };

volatile char data = 0;
char RxInterruptFlag = 0;

int main()
{
	int i;
	static int count = 0;
	sei();

	usart_init(BAUD_VAL);

	/**Initialize LCD**/
	set_i2c_clock(I2C_CLK_FREQ);
	LCD_Init();
	LCD_Clear();
	LCD_Clear();

	while (1)
	{

		if (RxInterruptFlag == 1)
		{
			if (data == 'V')
				count = 0;
			else
				count++;

			Rx_string_buff[count] = data;

			if (data == '\n')
			{
				for (i = 0; i < BUFFER_SIZE; i++)
					USART_Tx_byte(&Rx_string_buff[i]);
				USART_Tx_string("");
				count = 0;

				LCD_Goto(1, 1);
				LCD_Write_String(Rx_string_buff);

			}
			RxInterruptFlag = 0;

		}
		_delay_us(DELAY_IN_MICROSECONDS);

	}

	return 0;
}

ISR(USART_RX_vect)
{
	data = UDR0;

	RxInterruptFlag = 1;
}
