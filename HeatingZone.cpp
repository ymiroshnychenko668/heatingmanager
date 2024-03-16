/*
 * HeatingZone.cpp
 *
 *  Created on: Mar 3, 2024
 *      Author: yuriymiroshnichenko
 */

#include "HeatingZone.h";
const int NORMALLY_OPENED = 1;
const int NORMALLY_CLOSED = 0;

HeatingZone::HeatingZone(String zoneId, float setPointTemperature,
		int heaterPin, double KP, double KI, double KD, int relayMode) {
	this->zoneId = zoneId;
	this->heaterPin = heaterPin;
	this->setPointTemperature = setPointTemperature;
	pinMode(heaterPin, OUTPUT);
	this->pid = new PID(&currentTemperature, &outputSignal,
			&this->setPointTemperature, KP, KI, KD, 1, relayMode);
	this->pid->SetMode(AUTOMATIC);

}

HeatingZone::HeatingZone(String zoneId, float setPointTemperature, // @suppress("Class members should be properly initialized")
		int heaterPin, double KP, double KI, double KD) {
	HeatingZone(zoneId, setPointTemperature, heaterPin, KP, KI, KD,
			NORMALLY_OPENED);

}

void HeatingZone::setRate(int rate) {
	this->rate = rate;
	this->pid->SetSampleTime(rate);

}

float HeatingZone::getCurrentTemperature() {
	float val = 0;
	for (int i = 0; i < sensors.size(); i++) {
		TemperatureSensor *sensor = sensors.get(i);
		double cur = sensor->currentTemperature();
		if (sensor->getStatus() <= 0 || sensor->isOutOfRange()) {
			setError();
			return cur;
		}
		if (!algorytm) {
			val = val > cur ? val : cur;
		} else {
			val += cur;
		}
	}
	isError = false;
	if (!algorytm) {
		return val;
	} else {
		return val / sensors.size();
	}

}
void HeatingZone::setHeatingHandler(
		void (*heatingHadler)(String zoneId, double*, double*)) {
	this->heatingHandler = heatingHadler;
}

void HeatingZone::setErrorHandler(
		void (*errorHadler)(String zoneId, double*, double*)) {
	this->errorHandler = errorHadler;
}

void HeatingZone::performPid() {
	unsigned long now = millis();
	unsigned long timeChange = (now - lastTime);

	if (timeChange >= rate) {
		lastTime = now;
		if (heaterPin > 0 && sensors.size() > 0) {
			currentTemperature = getCurrentTemperature();

			if (isError) {
				handleError();
			} else if (state > 0) {
				if (pid->Compute()) {
					heating();
				}
			}
		}
	}
}

void HeatingZone::handleError() {
	if (errorHandler != nullptr) {
		(*errorHandler)(zoneId, &outputSignal, &currentTemperature);
	}

}

String HeatingZone::getId() {
	return zoneId;
}

void HeatingZone::heating() {
	state = HEATING;
	analogWrite(heaterPin, outputSignal);
	if (heatingHandler != nullptr) {
		(*heatingHandler)(zoneId, &outputSignal, &currentTemperature);
	}
}

byte HeatingZone::getState() {
	if (isError) {
		return ERROR;
	}
	return state;
}

void HeatingZone::setTarget(float targetTemp) {
	double temp = targetTemp;
	this->setPointTemperature = temp;

}
void HeatingZone::addTemperatureSensor(TemperatureSensor *sensor) {
	sensors.add(sensor);
}

byte HeatingZone::switchOn() {
	state = ON;
	performPid();
	return state;

}
byte HeatingZone::switchOff() {
	state = OFF;
	analogWrite(heaterPin, 255);
	return state;
}

void HeatingZone::setError() {
	this->isError = true;
	this->outputSignal = 255;
	analogWrite(heaterPin, 255);
}
void HeatingZone::setTunings(double KP, double KI, double KD){
	pid->SetTunings(KP,KI,KD);
}

