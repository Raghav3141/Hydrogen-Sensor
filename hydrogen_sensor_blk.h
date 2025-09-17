/*
 * hydrogen_sensor_blk.h
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */

#include "stm32f1xx_hal.h"

#ifndef INC_HYDROGEN_SENSOR_BLK_H_
#define INC_HYDROGEN_SENSOR_BLK_H_


void hydrogen_sensor_init(ADC_HandleTypeDef* hadc1);

double hydrogen_sensor_read(ADC_HandleTypeDef* hadc1);

#endif /* INC_HYDROGEN_SENSOR_BLK_H_ */
