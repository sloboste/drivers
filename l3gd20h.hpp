/*
 * l3gd20h.hpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#ifndef DRIVERS_SRC_L3GD20H_HPP_
#define DRIVERS_SRC_L3GD20H_HPP_

#include "stdint.h"
#include "i2cAdapter.hpp"

// Miscellaneous Constants
enum {
	I_AM					= 0xD7,
	L3GD20H_I2C_ADDR_7BIT	= 0x6B,
	AUTOINC_MASK			= 0x80
};

// Control Reg 1 Constants
enum ctrl1RegEnum {
	X_ENABLE_MASK			= 0x02,
	Y_ENABLE_MASK			= 0x01,
	Z_ENABLE_MASK			= 0x04,
	NORMAL_MODE_ENABLE_MASK = 0x08

};

// Registers
enum L3GD20HRegEnum {
	WHO_AM_I		= 0x0F,
	CTRL1			= 0x20,
	CTRL2			= 0x21,
	CTRL3			= 0x22,
	CTRL4			= 0x23,
	CTRL5			= 0x24,
	REFERENCE		= 0x25,
	OUT_TEMP		= 0x26,
	STATUS			= 0x27,
	OUT_X_L			= 0x28,
	OUT_X_H			= 0x29,
	OUT_Y_L			= 0x2A,
	OUT_Y_H			= 0x2B,
	OUT_Z_L			= 0x2C,
	OUT_Z_H			= 0x2D,
	FIFO_CTRL		= 0x2E,
	FIFO_SRC		= 0x2F,
	IG_CFG			= 0x30,
	IG_SRC			= 0x31,
	IG_THIS_XH		= 0x32,
	IG_THIS_XL		= 0x33,
	IG_THIS_YH		= 0x34,
	IG_THIS_YL		= 0x35,
	IG_THIS_ZH		= 0x36,
	IG_THIS_ZL		= 0x37,
	IG_DURATION		= 0x38,
	LOW_ODR			= 0x39
};

// Sensitivity Range Options
enum sensitivityRangeEnum {
	PLUS_MINUS_245DPS,
	PLUS_MINUS_500DPS,
	PLUS_MINUS_2000DPS
};

// Bit Masks for Sensitivity Settings
enum sensitivityMaskEnum {
	PLUS_MINUS_245DPS_MASK		= 0x00,
	PLUS_MINUS_500DPS_MASK		= 0x10,
	PLUS_MINUS_2000DPS_MASK		= 0x20
};

// Sensitivity multipliers in mili-degrees per second, per digit
const float MULTIPLIER_245DPS		= 8.75;
const float MULTIPLIER_500DPS		= 17.5;
const float MULTIPLIER_2000DPS		= 70;

// Gyroscope Zero-Bias Calibration Data
struct L3GD20H_CalDataStruct {
	int32_t xOffset;
	int32_t yOffset;
	int32_t zOffset;
};

// L3GD20H Triple Axis Gyroscope Class
class L3GD20HSensor {
private:
	I2CAdapter * i2cAdapterPtr;
	enum sensitivityRangeEnum sensitivity;
	struct L3GD20H_CalDataStruct calData;

	/* Use:
	 *	Check that the sensor is the sensor that we expect it to be. Reads from
	 *	WHO_AM_I register and compares with the value of I_AM. Called in the
	 *	constructor.
	 * Parameters:
	 *	None.
	 */
	bool verifyId(void);

	/* Use:
	 *	Read the raw values for x, y, and z angular rotation rates. These values
	 *	aren't very useful on their own. Requires that the gyroscope is powered
	 *	on and the x, y, z measurements are enabled.
	 * Parameters:
	 *	uint16_t &x: Standard integer that will hold the raw angular rotation
	 *				 rate of the x axis when the method returns. Passed by
	 *				 reference.
	 *	uint16_t &y: Standard integer that will hold the raw angular rotation
	 *				 rate of the y axis when the method returns. Passed by
	 *				 reference.
	 *	uint16_t &z: Standard integer that will hold the raw angular rotation
	 *				 rate of the z axis when the method returns. Passed by
	 *				 reference.
	 */
	void getRawXYZ(int16_t &x, int16_t &y, int16_t &z);
public:
	/* Use:
	 *	Create an instance of the L3GD20H gyroscope with a specified sensitivity.
	 * Parameters:
	 *	I2CAdapter * i2cAdPtr: I2C interface for the gyroscope.
	 *	enum sensitivityRangeEnum sensitivityRange: Selects the sensitivity
	 *												range.
	 */
	L3GD20HSensor(
			I2CAdapter * i2cAdPtr,
			enum sensitivityRangeEnum sensitivityRange);

	/* Use:
	 *	Set the gyroscope to power on mode and enable x, y, and z measurements.
	 * Parameters:
	 *	None.
	 */
	void powerOnEnXYZ(void);

	/* Use:
	 *	Calculate the zero-bias offset of the gyroscope by taking the mean of
	 *	500 measurements for each axis. This data is stored in the
	 *	L3GD20HCalDataStruct and used in the getXYZ(---) method.
	 * Parameters:
	 *	None.
	 */
	void calibrateXYZ(void);

	/* Use:
	 *	Select the sensitivity range of the gyroscope.
	 * Parameters:
	 *	enum sensitivityRangeEnum sensitivityRange: Selects the sensitivity
	 *												range.
	 */
	void setSensitivity(enum sensitivityRangeEnum sensitivityRange);

	/* Use:
	 *	Get the angular rotation rate values in *** mili-degrees per second ***
	 *	from the sensor. Calibration offsets are used in the calculation.
	 * Parameters:
	 *	uint32_t &x: Standard integer that will hold the angular rotation
	 *				 rate of the x axis when the method returns. Passed by
	 *				 reference.
	 *	uint32_t &y: Standard integer that will hold the angular rotation
	 *				 rate of the y axis when the method returns. Passed by
	 *				 reference.
	 *	uint32_t &z: Standard integer that will hold the angular rotation
	 *				 rate of the z axis when the method returns. Passed by
	 *				 reference.
	 */
	void getXYZ(int32_t &x, int32_t &y, int32_t &z); // mili-degrees per second
};

#endif /* DRIVERS_SRC_L3GD20H_HPP_ */
