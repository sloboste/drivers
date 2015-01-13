/*
 * lsm303dlhc.hpp
 *
 *  Created on: Dec 21, 2014
 *      Author: steven
 */

#ifndef LSM303DLHC_HPP_
#define LSM303DLHC_HPP_

#include "i2cAdapter.hpp"
#include "stdint.h"

enum magModeEnum {
	CONTINUOUS			= 0x00,
	SINGLE_CONVERSION	= 0x01,
	SLEEP				= 0x02
};

// LSM303DLHC Triple Axis Accelerometer, Magnetometer, and Temperature Sensor
class LSM303DLHCSensor {
private:
	I2CAdapter * i2cAdapterPtr;

	/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
	 *  Use:
	 *
	 * Parameters:
	 *
	 */
	// int16_t getRawTemperature(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getRawAccelXYZ(int16_t &x, int16_t &y, int16_t &z);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getRawMagXYZ(int16_t &x, int16_t &y, int16_t &z);

public:
	/* Use:
	 *
	 * Parameters:
	 *
	 */
	LSM303DLHCSensor(I2CAdapter * i2cAdPtr);

	/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
	 * Use:
	 *	None.
	 * Parameters:
	 *	None.
	 */
	//void enableTemperature(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void enableAccelXYZ(void);

	/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
	 * Use:
	 *	None.
	 * Parameters:
	 *	None.
	 */
	// int32_t getTemperature(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getMagXYZ(int32_t &x, int32_t &y, int32_t &z);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getAccelXYZ(int32_t &x, int32_t &y, int32_t &z);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void setMagMode(enum magModeEnum m);

};

#endif /* LSM303DLHC_HPP_ */
