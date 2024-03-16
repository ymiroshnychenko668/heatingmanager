/*
 * ThermocouplesModule.cpp
 *
 *  Created on: Mar 2, 2024
 *      Author: yuriymiroshnichenko
 */

#include "HeatingManager.h"

HeatingManager::HeatingManager() {
	// Constructor implementation (if needed)
}

void HeatingManager::addZone(HeatingZone *zone) {
	zones.add(zone);
}

HeatingZone* HeatingManager::getZoneById(String zoneId) {
	for (int i = 0; i < zones.size(); i++) {
		HeatingZone *zone = zones.get(i);
		if (zone->getId().equals(zoneId)) {
			return zone;
		}

	}
	return nullptr;

}

float HeatingManager::getZoneTemperatureC(String zoneId) {
	HeatingZone *zone = getZoneById(zoneId);
	if (zone != nullptr) {
		return zone->getCurrentTemperature();
	}
	return ERROR;

}

void HeatingManager::setRate(int rate) {
	for (int i = 0; i < zones.size(); i++) {
		HeatingZone *zone = zones.get(i);
		zone->setRate(rate);

	}
}

void HeatingManager::swichOnAll() {
	for (int i = 0; i < zones.size(); i++) {
		HeatingZone *zone = zones.get(i);
		zone->switchOn();

	}
}

void HeatingManager::switchOffAll() {
	for (int i = 0; i < zones.size(); i++) {
		HeatingZone *zone = zones.get(i);
		zone->switchOff();

	}
}

void HeatingManager::performPid() {
	for (int i = 0; i < zones.size(); i++) {
		zones.get(i)->performPid();

	}
}

