/*
 * sensor_processing.c
 *
 *  Created on: Jan 11, 2018
 *      Author: abel
 */

#include "sensor_processing.h"

void signal_processing(uint16_t U16_arg_ADC_val, meas_val_t *arg_meas_val)
{

	float f_temp_val = 0;
	f_temp_val =
			((float) ((float) U16_arg_ADC_val / (float) ADC_MAX_VAL_TEN_BIT)
					* (float) ADC_MAX_VOLTAGE_IN_mV);
	f_temp_val /= (float) 1000;

	arg_meas_val->integer_part = (uint16_t) f_temp_val;

	arg_meas_val->mantissa_part = (uint16_t) (((float) (f_temp_val)
			- (float) (arg_meas_val->integer_part)) * 1000);

}
