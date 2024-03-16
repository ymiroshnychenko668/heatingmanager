/*
 * ThermocouplesModule.h
 *
 *  Created on: Mar 2, 2024
 *      Author: yuriymiroshnichenko
 */

#ifndef HEATINGMANAGER_H_
#define HEATINGMANAGER_H_
#include <Arduino.h>
#include <LinkedList.h>
#include <HeatingZone.h>
#include <TemperatureSensor.h>




class HeatingManager {

private:
	LinkedList<HeatingZone*> zones;

public:
    HeatingManager();

    void addZone(HeatingZone* zone);

    HeatingZone* getZoneById(String zoneId);

    float getZoneTemperatureC(String zoneId);

    void swichOnAll();

    void switchOffAll();
    void performPid();

    void setRate(int rate);


};


#endif /* TEMPSENSORSMANAGERMODULE_H_ */
