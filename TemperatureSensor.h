/*
 * TemperatureSensor.h
 *
 *  Created on: Mar 3, 2024
 *      Author: yuriymiroshnichenko
 */

#ifndef LIBRARIES_HEATINGMANAGER_TEMPERATURESENSOR_H_
#define LIBRARIES_HEATINGMANAGER_TEMPERATURESENSOR_H_




class TemperatureSensor {

protected:
    float curTemp;
	int status;
	double allowedMin;
	double allowedMax;
	bool isAllowedRangeDef;
public:
    virtual float currentTemperature();  // Pure virtual function
    virtual ~TemperatureSensor() {}
    virtual int getStatus();
    void setAllowedRange(double min, double max);
    bool isOutOfRange();


};

#endif /* LIBRARIES_HEATINGMANAGER_TEMPERATURESENSOR_H_ */
