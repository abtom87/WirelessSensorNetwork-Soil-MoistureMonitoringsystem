/*
 * sensor_processing.h
 *
 *  Created on: Jan 11, 2018
 *      Author: abel
 */

#ifndef SENSOR_PROCESSING_H_
#define SENSOR_PROCESSING_H_

#include <stdint.h>

#define TRUE  (1)
#define FALSE (0)

#define ADC_MAX_VOLTAGE_IN_mV 3300UL
#define ADC_MAX_VAL_TEN_BIT   1023UL
#define FILTER_COUNT          15UL






typedef struct {

	uint16_t integer_part;
	uint16_t mantissa_part;

}meas_val_t;



void signal_processing(uint16_t, meas_val_t* );
void signal_acquisition(uint16_t);


#endif /* SENSOR_PROCESSING_H_ */
