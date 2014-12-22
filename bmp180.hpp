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

// Miscellaneous Constants
enum {
	BMP180_I2C_ADDR_7BIT 	= 0x77,
	CHIPID 					= 0x55,
	READTEMPCMD        		= 0x2E,
	READPRESSURECMD    		= 0x34
};

// Registers
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

// Power and Resolution Modes
enum modeEnum {
	ULTRALOWPOWER           = 0,
	STANDARD                = 1,
	HIGHRES                 = 2,
	ULTRAHIGHRES            = 3
};

// Calibration Data (corresponds to registers)
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

// Barometric Pressure and Temperature Sensor with I2C Interface
class BMP180Sensor {
private:
	// Spoof readings to check math
	bool useTestNumbers;
	I2CAdapter * i2cAdapterPtr;
	struct BMP_CalDataStruct calData;
	enum modeEnum mode;

	/* Use:
	 * 	Check that the sensor is the sensor that we expect it to be. Read from
	 * 	REG_CHIPID and compare with CHIPID. Called in the constructor.
	 * Parameters:
	 * 	None.
	 */
	bool verifyId(void);

	/* Use:
	 * 	Read and store the calibration data from the appropriate registers. This
	 * 	needs to be done once before any measurements are taken. Called in the
	 * 	constructor.
	 * Parameters:
	 */
	bool getCalData(void);

	/* Use:
	 * 	Send the read pressure command and then read the uncompensated pressure
	 * 	value from the sensor. This number is useless without further math.
	 * 	This method takes AT LEAST 4.5ms to execute due to the way that the
	 * 	sensor takes measurements.
	 * Parameters:
	 * 	None.
	 */
	int32_t getRawPressure(void);

	/* Use:
	 * 	Send ther read temperature command and then read the uncompensated
	 * 	temperature value from the sensor. This number is useless without
	 * 	further math. This method takes AT LEAST 4.5ms to execute due to the way
	 * 	that the sensor takes measurements.
	 * Parameters:
	 * 	None.
	 */
	int16_t getRawTemperature(void);

public:
	/* Use:
	 * 	Create an instance of the BMP180 barometric pressure and temperature
	 * 	sensor.
	 * Parameters:
	 *	bool useTestVals: Spoof the raw temperature and pressure readings with
	 *					  numbers provided in the datasheet. Use this to check
	 *					  that the compensation equations are correct.
	 *	I2CAdapter * i2cAdPtr: Generic I2C interface for this sensor.
	 *	enum modeEnum m: Power and resolution mode for the sensor.
	 */
	BMP180Sensor(bool useTestVals, I2CAdapter * i2cAdPtr, enum modeEnum m);

	/* Use:
	 * 	Get the compensated temperature and pressure values from the sensor.
	 * 	This method takes AT LEAST 4.5ms to execute due to the way that the
	 * 	sensor takes measurements.
	 * Parameters:
	 * 	int32_t &temperature: Standard integer that will have the temperature
	 * 						  in *** deci-degrees Celcius *** stored in it after
	 * 						  the method returns. Passed by reference.
	 *	int32_t &pressure: Standard integer that will have the barometric
	 *					   pressure in *** Pa *** stored in it after the method
	 *					   returns. Passed by reference.
	 */
	void getTempAndPres(int32_t &temperature, int32_t &pressure);
};

#endif /* DRIVERS_SRC_BMP180_HPP_ */
