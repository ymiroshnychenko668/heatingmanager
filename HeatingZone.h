/*
 * HeatingZone.h
 *
 *  Created on: Mar 3, 2024
 *      Author: yuriymiroshnichenko
 */

#ifndef HEATINGZONE_H_
#define HEATINGZONE_H_

#include <Arduino.h>
#include <max6675.h>
#include <LinkedList.h>
#include <TemperatureSensor.h>
#include <PID_v1.h>

const byte HEATING = 2;
const byte COOLING = 3;
const byte ERROR = -1;
const byte OFF = 0;
const byte ON = 1;

const byte MAXIMAL = 0;
const byte AVG = 1;

class HeatingZone {

private:
	int heaterPin;
	String zoneId;
	volatile int state = OFF;
	double setPointTemperature;
	double currentTemperature;
	volatile double outputSignal = 0;
	void (*heatingHandler)(String zoneId,double* value , double* temp);
	void (*errorHandler)(String zoneId,double* value, double* temp);
	LinkedList<TemperatureSensor*> sensors;
	byte algorytm = MAXIMAL;
	PID *pid;
	long lastTime;
	int rate = 100;
	void heating();
	void setError();
	volatile bool isError;
	void handleError();

public:
	HeatingZone(String zoneId, float setPointTemperature, int heaterPin,double KP, double KI, double KD);
	HeatingZone(String zoneId, float setPointTemperature, int heaterPin,double KP, double KI, double KD, int relayMode);
	float getCurrentTemperature();
	byte getState();
	void setTarget(float targetTemp);
	void addTemperatureSensor(TemperatureSensor *sensor);
	byte switchOn();
	byte switchOff();
	void setHeatingHandler(void (*heatingHadler)(String zoneId,double* value, double* temp));
	void setErrorHandler(void (*heatingHadler)(String zoneId,double* value, double* temp));
	String getId();
	void performPid();
	void setRate(int rate);
	void setTunings(double KP, double KI, double KD);


};

#endif /* HEATINGZONE_H_ */
