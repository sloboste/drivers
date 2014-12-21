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

enum {
	I_AM					= 0xD7,
	L3GD20H_I2C_ADDR_7BIT	= 0x6B
};

enum ctrl1RegEnum {
	X_ENABLE_MASK			= 0x02,
	Y_ENABLE_MASK			= 0x01,
	Z_ENABLE_MASK			= 0x04,
	NORMAL_MODE_ENABLE_MASK = 0x08

};

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

enum sensitivityRangeEnum {
	PLUS_MINUS_245DPS,
	PLUS_MINUS_500DPS,
	PLUS_MINUS_2000DPS
};

enum sensitivityMaskEnum {
	PLUS_MINUS_245DPS_MASK		= 0x00,
	PLUS_MINUS_500DPS_MASK		= 0x10,
	PLUS_MINUS_2000DPS_MASK		= 0x20
};

// Sensitivity multipliers in mili-degrees per second, per digit
const float MULTIPLIER_245DPS		= 8.75;
const float MULTIPLIER_500DPS		= 17.5;
const float MULTIPLIER_2000DPS		= 70;

struct L3GD20H_CalDataStruct {
	uint32_t xOffset;
	uint32_t yOffset;
	uint32_t zOffset;
};

class L3GD20HSensor {
private:
	I2CAdapter * i2cAdapterPtr;
	enum sensitivityRangeEnum sensitivity;
	struct L3GD20H_CalDataStruct calData;
	bool verifyId(void);
	void calibrateXYZ(void);
	void getRawXYZ(uint16_t &x, uint16_t &y, uint16_t &z);
public:
	L3GD20HSensor(
			I2CAdapter * i2cAdPtr,
			enum sensitivityRangeEnum sensitivityRange);
	void powerOnEnXYZ(void);
	void setSensitivity(enum sensitivityRangeEnum sensitivityRange);
	void getXYZ(int32_t &x, int32_t &y, int32_t &z); // mili-degrees per second
};

#endif /* DRIVERS_SRC_L3GD20H_HPP_ */
