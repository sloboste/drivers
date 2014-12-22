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

// Registers
enum LSM303DLHCRegEnum {
	CTRL_REG1_A			= 0x20,
	CTRL_REG2_A			= 0x21,
	CTRL_REG3_A			= 0x22,
	CTRL_REG4_A			= 0x23,
	CTRL_REG5_A			= 0x24,
	CTRL_REG6_A			= 0x25,
	REFERENCE_A			= 0x26,
	STATIS_REG_A		= 0x27,
	OUT_X_L_A			= 0x28,
	OUT_X_H_A			= 0x29,
	OUT_Y_L_A			= 0x2A,
	OUT_Y_H_A			= 0x2B,
	OUT_Z_L_A			= 0x2C,
	OUT_Z_H_A			= 0x2D,
};

// LSM303DLHC Triple Axis Magnetometer
class LSM303DLHCSensor {
private:
	I2CAdapter * i2cAdapterPtr;

	/* Use:
	 *
	 * Parameters:
	 *
	 */
	bool verifyId(void);

public:
	/* Use:
	 *
	 * Parameters:
	 *
	 */
	LSM303DLHCSensor(I2CAdapter * i2cAdPtr);

};

#endif /* LSM303DLHC_HPP_ */
