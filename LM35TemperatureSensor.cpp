/*
 * LM35TemperatureSensor.cpp
 *
 *  Created on: Mar 5, 2024
 *      Author: yuriymiroshnichenko
 */

#include <LM35TemperatureSensor.h>

LM35TemperatureSensor::LM35TemperatureSensor(int analogPin) {
	this->pin = analogPin;

}

float LM35TemperatureSensor::currentTemperature() {
	curTemp = (float(analogRead(pin)) * 5 / (1023)) / 0.01;
	if (isnan(curTemp) || curTemp == 0.00) {
		status = -1;

	}
	return curTemp;

}

int LM35TemperatureSensor::getStatus() {
	double temp = currentTemperature();
	if (isnan(temp) || temp == 0.00) {
		return -1;

	}
	return 1;
}
