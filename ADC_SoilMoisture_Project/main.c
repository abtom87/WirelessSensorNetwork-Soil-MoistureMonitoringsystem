/*
 * main.c
 *
 *  Created on: Jan 11, 2018
 *      Author: abel
 */
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "sensor_processing.h"

#define ACTIVATE_SLEEP_MODE
#define DELAY_IN_uS 100UL

char value_buf[8] = { 0 };
char msg_to_transmit[20] = { 0 };
char msg_header[] = "VAL:";

char dec_val_buf[5] = { 0 };
char adc_buffer[6] = { 0 };
volatile uint16_t U16_adc_val = 0;
volatile uint16_t U16_temp = 0;
volatile uint16_t U16_dec_part = 0;

volatile float f_temp = 0;

volatile char ADCInterruptFlag = 1;
extern volatile char filtering_cplt_flag;
extern meas_val_t measured_val;

void init_adc()
{

	ADCSRA = ((1 << ADEN) | /*Enable ADC module*/
	(1 << ADSC) | /*Enable start conversion*/
	(1 << ADIE) | /*Interrupt enable*/
	(1 << ADLAR) | /*Left-adjust result enabled*/
	(1 << ADATE) | /*Auto-trigger enabled*/
	(1 << ADPS2)); /*ADPS[2:0]  100-->Prescaler is 16  */

	ADMUX = ((1 << REFS1) | (1 << REFS0) | (0 << MUX0)); /*ADC channel 0 is chosen*/
}

int main()
{
	DDRC = 0x00;

	init_adc();
	usart_init(BAUD_VAL);
	sei();

	while (1)
	{

#ifdef ACTIVATE_SLEEP_MODE

		set_sleep_mode(SLEEP_MODE_ADC);
		sleep_mode()
		;
#endif

		if (ADCInterruptFlag == 1)
		{
			cli();
			signal_acquisition(U16_adc_val);
			//signal_processing(U16_adc_val,&measured_val);
			sei();
			ADCInterruptFlag = 0;
		}

		if (filtering_cplt_flag == TRUE)
		{
			cli();
			dec_val_buf[0] = '.';
			sprintf(dec_val_buf, "%1u", measured_val.mantissa_part); /*Convert the mantissa of number t string*/

			sprintf(value_buf, "%u", measured_val.integer_part); /*Convert the characteristic of number to
			 string	 	 	 	 	*/
			strcat(value_buf, ".");
			strcat(value_buf, dec_val_buf);
			strcat(msg_to_transmit, msg_header);
			memcpy(&msg_to_transmit[strlen(msg_header)], value_buf,
					strlen(value_buf));

			USART_Tx_string(msg_to_transmit);

			filtering_cplt_flag = FALSE;
			sei();

		}
		_delay_us(DELAY_IN_uS);

	}

	return 0;
}

ISR(ADC_vect)
{
	cli();
	ADCInterruptFlag = 1;
	U16_adc_val = ADCW;
	sei();

}
