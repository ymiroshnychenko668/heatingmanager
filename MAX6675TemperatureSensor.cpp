/*
 * MAX6675TemperatureSensor.cpp
 *
 *  Created on: Mar 3, 2024
 *      Author: yuriymiroshnichenko
 */
#include "MAX6675TemperatureSensor.h"
#include <Arduino.h>


MAX6675TemperatureSensor::MAX6675TemperatureSensor(uint32_t MISO, uint32_t selectPin, uint32_t clockPin){
	max6675 = new MAX6675(clockPin, selectPin, MISO);
};


float MAX6675TemperatureSensor::currentTemperature()  {
	updateLastIfNecessary();
	return curTemp;


}

int MAX6675TemperatureSensor::getStatus(){
	double temp =  currentTemperature();
	if(isnan(temp)||temp==0.00){
		return -1;

	}
	return 1;
}

void MAX6675TemperatureSensor::updateLastIfNecessary() {
	unsigned long now = millis();
	unsigned long timeChange = (now - last);

    if(timeChange  >= 1000){
        last = now;
        float f = max6675->readCelsius();
        this->curTemp = f;
    }
}
