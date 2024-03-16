/*
 * TemperatureSensor.cpp
 *
 *  Created on: Mar 14, 2024
 *      Author: yuriymiroshnichenko
 */


#include <TemperatureSensor.h>

bool TemperatureSensor::isOutOfRange(){
	if(isAllowedRangeDef){
		return curTemp>=allowedMax || curTemp<=allowedMin;
	}
	return false;
}

void TemperatureSensor::setAllowedRange(double min, double max){
	allowedMax = max;
	allowedMin = min;
	isAllowedRangeDef = true;
}


