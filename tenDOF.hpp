/*
 * tenDOF.hpp
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

#ifndef DRIVERS_SRC_TENDOF_HPP_
#define DRIVERS_SRC_TENDOF_HPP_

#include "stdint.h"

// Component Addresses
enum { // Left shift by 1 and add to 1/0 (R/W)
	L3GD20H_ADDR 						= 0x00,//?
	LSM303_ADDR 						= 0x00,//?
	BMP180_ADDR 						= 0x77
};

// Axis enum
enum axisEnum {
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

// Temperature Units enum
enum tempUnitsEnum {
	FARENHEIT,
	CELCIUS,
	KELVIN
};

// L3GD20H Gyroscope


// LSM303 Accelerometer/Magnetometer


// BMP180 Barometer/Temperature
enum /* BMP180_Registers */ {
	BMP180_REGISTER_CAL_AC1            = 0xAA,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_AC2            = 0xAC,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_AC3            = 0xAE,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_AC4            = 0xB0,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_AC5            = 0xB2,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_AC6            = 0xB4,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_B1             = 0xB6,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_B2             = 0xB8,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_MB             = 0xBA,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_MC             = 0xBC,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CAL_MD             = 0xBE,  // R   Calibration data (16 bits)
	BMP180_REGISTER_CHIPID             = 0xD0,
	BMP180_REGISTER_VERSION            = 0xD1,
	BMP180_REGISTER_SOFTRESET          = 0xE0,
	BMP180_REGISTER_CONTROL            = 0xF4,
	BMP180_REGISTER_TEMPDATA           = 0xF6,
	BMP180_REGISTER_PRESSUREDATA       = 0xF6,
	BMP180_REGISTER_READTEMPCMD        = 0x2E,
	BMP180_REGISTER_READPRESSURECMD    = 0x34
};
enum BMP180_ModeEnum {
	BMP085_MODE_ULTRALOWPOWER          = 0,
	BMP085_MODE_STANDARD               = 1,
	BMP085_MODE_HIGHRES                = 2,
	BMP085_MODE_ULTRAHIGHRES           = 3
};
struct BMP180_CalDataStruct {
	int16_t  ac1;
	int16_t  ac2;
	int16_t  ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t  b1;
	int16_t  b2;
	int16_t  mb;
	int16_t  mc;
	int16_t  md;
};


class TenDOFsensor {
private:

public:
	TenDOFsensor();

	int32_t getTemperature(enum tempUnitsEnum units);
	int32_t getPressure(void);

};

#endif /* DRIVERS_SRC_TENDOF_HPP_ */
