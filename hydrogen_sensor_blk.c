/*
 * hydrogen_sensor_blk.c
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */


#include "hydrogen_sensor_blk.h"
#include <string.h>
#include <math.h>

#define RL_VALUE 10
#define RO_CLEAN_AIR_FACTOR 9.21

static float Ro;
static const float H2Curve[] = {2.3, 0.93, -1.44};

static float MQResistanceCalculation(float raw_adc){
	return (((float)RL_VALUE*(4095-raw_adc)/raw_adc));
}

static float MQCalibration(ADC_HandleTypeDef* hadc1){
	float val = 0;
	for (int i = 0; i < 50; i++){
		HAL_ADC_Start(hadc1);
		HAL_ADC_PollForConversion(hadc1, 20);
		val += MQResistanceCalculation(HAL_ADC_GetValue(hadc1));
		HAL_Delay(50);
	}
	val = val/50;
	val = val/RO_CLEAN_AIR_FACTOR;
	return val;
}

void hydrogen_sensor_init(ADC_HandleTypeDef* hadc1) {
	Ro = MQCalibration(hadc1);
	return;
}


static float MQRead(ADC_HandleTypeDef* hadc1){
	float rs = 0;
	for(int i = 0; i <50; i++){
		HAL_ADC_Start(hadc1);
		HAL_ADC_PollForConversion(hadc1, 20);
		rs += MQResistanceCalculation(HAL_ADC_GetValue(hadc1));
		HAL_Delay(50);
	}

	rs = rs/50;
	return rs;
}

static double MQGetPercentage(float rs_ro_ratio, float *pcurve){
	return(pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2])+pcurve[0])));
}

double hydrogen_sensor_read(ADC_HandleTypeDef* hadc1) {
	return MQGetPercentage(MQRead(hadc1)/Ro, H2Curve);
}