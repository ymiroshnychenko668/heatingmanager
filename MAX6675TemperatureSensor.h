/*
 * MAX6675TemperatureSensor.h
 *
 *  Created on: Mar 3, 2024
 *      Author: yuriymiroshnichenko
 */

#ifndef LIBRARIES_HEATINGMANAGER_MAX6675TEMPERATURESENSOR_H_
#define LIBRARIES_HEATINGMANAGER_MAX6675TEMPERATURESENSOR_H_

#include <TemperatureSensor.h>
#include <Arduino.h>
#include <max6675.h>


class MAX6675TemperatureSensor : public TemperatureSensor{
public:
	MAX6675TemperatureSensor(uint32_t MISO, uint32_t selectPin, uint32_t clockPin);
	float currentTemperature() override;
	int MAX6675TemperatureSensor::getStatus() override;
private:
	MAX6675* max6675;
	unsigned long last;
	void MAX6675TemperatureSensor::updateLastIfNecessary() ;


};



#endif /* LIBRARIES_HEATINGMANAGER_MAX6675TEMPERATURESENSOR_H_ */
