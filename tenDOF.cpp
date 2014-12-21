/*
 * tenDOF.cpp
 *
* Driver for Adafruit 10 DOF breakout board.
 *
 * Triple Axis Gyroscope: L3GD20H
 * Triple Axis Accelerometer/Magnetometer: LSM303
 * Barometer/Temperature: BMP180
 *
 *  Created on: Dec 19, 2014
 *      Author: Steven Sloboda
 */

#include "tenDOF.hpp"
#include "stdint.h"

#include "stdio.h"

TenDOFsensor::TenDOFsensor() {
	printf("tenDOF created!\n");

}

int32_t TenDOFsensor::getTemperature(enum tempUnitsEnum units) {
	printf("tenDOF getTemperature!\n");
	int32_t temperature = 0;
	switch (units) {
	case FARENHEIT:
		temperature = temperature * 1.8 + 32;
		break;
	case KELVIN:
		temperature += 273.15;
		break;
	default: // CELCIUS
		break;
	}
	return temperature;
}

int32_t TenDOFsensor::getPressure(void) {
	printf("tenDOF getPressure!\n");
	int32_t pressure = 0;
	return pressure;
}

