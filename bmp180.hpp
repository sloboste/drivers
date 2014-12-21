/*
 * bmp180.hpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#ifndef DRIVERS_SRC_BMP180_HPP_
#define DRIVERS_SRC_BMP180_HPP_

#include "stdint.h"
#include "i2cAdapter.hpp"

enum {
	BMP180_I2C_ADDR_7BIT 	= 0x77,
	CHIPID 					= 0x55,
	READTEMPCMD        		= 0x2E,
	READPRESSURECMD    		= 0x34
};

enum bmp180RegEnum {
	REG_CAL_AC1				= 0xAA,  // R   Calibration data (16 bits)
	REG_CAL_AC2				= 0xAC,  // R   Calibration data (16 bits)
	REG_CAL_AC3				= 0xAE,  // R   Calibration data (16 bits)
	REG_CAL_AC4             = 0xB0,  // R   Calibration data (16 bits)
	REG_CAL_AC5             = 0xB2,  // R   Calibration data (16 bits)
	REG_CAL_AC6             = 0xB4,  // R   Calibration data (16 bits)
	REG_CAL_B1              = 0xB6,  // R   Calibration data (16 bits)
	REG_CAL_B2              = 0xB8,  // R   Calibration data (16 bits)
	REG_CAL_MB              = 0xBA,  // R   Calibration data (16 bits)
	REG_CAL_MC              = 0xBC,  // R   Calibration data (16 bits)
	REG_CAL_MD              = 0xBE,  // R   Calibration data (16 bits)
	REG_CHIPID              = 0xD0,
	REG_VERSION             = 0xD1,
	REG_SOFTRESET           = 0xE0,
	REG_CONTROL             = 0xF4,
	REG_TEMPDATA            = 0xF6,
	REG_PRESSUREDATA        = 0xF6,
};

enum modeEnum {
	ULTRALOWPOWER           = 0,
	STANDARD                = 1,
	HIGHRES                 = 2,
	ULTRAHIGHRES            = 3
};

enum tempUnitsEnum {
	FARENHEIT,
	CELCIUS,
	KELVIN
};

struct BMP_CalDataStruct {
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

class BMP180Sensor {
private:
	bool useTestNumbers;
	I2CAdapter * i2cAdapterPtr;
	struct BMP_CalDataStruct calData;
	enum modeEnum mode;
	bool verifyId(void);
	bool getCalData(void);
	int16_t getRawPressure(void);
	int16_t getRawTemperature(void);
public:
	BMP180Sensor(bool useTestVals, I2CAdapter * i2cAdPtr, enum modeEnum m);
	void getTempAndPres(
			int32_t &temperature,
			int32_t &pressure/*,
			enum tempUnitsEnum units*/);
};

#endif /* DRIVERS_SRC_BMP180_HPP_ */
