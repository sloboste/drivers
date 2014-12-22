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

// LSM303DLHC Triple Axis Accelerometer, Magnetometer, and Temperature Sensor
class LSM303DLHCSensor {
private:
	I2CAdapter * i2cAdapterPtr;

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	int16_t getRawTemperature(void);

public:
	/* Use:
	 *
	 * Parameters:
	 *
	 */
	LSM303DLHCSensor(I2CAdapter * i2cAdPtr);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void enableTemperature(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void enableAccelXYZ(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	int32_t getTemperature(void);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getRawMagXYZ(uint16_t &x, uint16_t &y, uint16_t &z);

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	void getRawAccelXYZ(uint16_t &x, uint16_t &y, uint16_t &z);

};

#endif /* LSM303DLHC_HPP_ */
