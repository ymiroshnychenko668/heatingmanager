/*
 * LM35.h
 *
 *  Created on: Mar 5, 2024
 *      Author: yuriymiroshnichenko
 */

#ifndef LIBRARIES_HEATINGMANAGER_LM35TEMPERATURESENSOR_H_
#define LIBRARIES_HEATINGMANAGER_LM35TEMPERATURESENSOR_H_

#include <TemperatureSensor.h>
#include <Arduino.h>

class LM35TemperatureSensor : public TemperatureSensor{
private:
	int pin;

public:
	LM35TemperatureSensor(int pin);
	float currentTemperature() override;
    virtual int getStatus() override;


};


#endif /* LIBRARIES_HEATINGMANAGER_LM35TEMPERATURESENSOR_H_ */
