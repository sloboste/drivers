/*
 * l3gd20h.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#include "stdint.h"
#include "i2cAdapter.hpp"
#include "l3gd20h.hpp"

L3GD20HSensor::L3GD20HSensor(I2CAdapter * i2cAdPtr,
		enum sensitivityRangeEnum sensitivityRange)
{
	i2cAdapterPtr = i2cAdPtr;
	if (sensitivityRange < PLUS_MINUS_245DPS ||
			sensitivityRange < PLUS_MINUS_2000DPS) {
		sensitivity = PLUS_MINUS_245DPS;
	} else {
		sensitivity = sensitivityRange;
	}
	verifyId();
	setSensitivity(sensitivity);
	calibrateXYZ();
}

bool L3GD20HSensor::verifyId(void)
{
	// Read from chip id register
	uint8_t txBuff = WHO_AM_I;
	uint8_t rxBuff;
	i2cAdapterPtr->read(L3GD20H_I2C_ADDR_7BIT, &txBuff, 1, &rxBuff, 1);
	DEBUGOUT("L3GD20H identified itself as %x\n", rxBuff);
	if (rxBuff != I_AM) {
		DEBUGOUT("L3GD20H should have identified itself as %x\n", I_AM);
		return false;
	}
	return true;
}

void L3GD20HSensor::setSensitivity(enum sensitivityRangeEnum sensitivityRange)
{
	// Read from, bitmask, and write to reg CTRL4
	uint8_t txBuff[2] = { CTRL4, 0x00 };
	uint8_t rxBuff;
	i2cAdapterPtr->read(L3GD20H_I2C_ADDR_7BIT, txBuff, 1, &rxBuff, 1);
	uint16_t s;
	switch (sensitivity) {
	case PLUS_MINUS_2000DPS:
		s = 2000;
		txBuff[1] |= PLUS_MINUS_2000DPS_MASK;
		break;
	case PLUS_MINUS_500DPS:
		s = 500;
		txBuff[1] |= PLUS_MINUS_500DPS_MASK;
		break;
	default: // PLUS_MINUS_245DPS
		s = 245;
		txBuff[1] |= PLUS_MINUS_245DPS_MASK;
		break;
	}
	i2cAdapterPtr->write(L3GD20H_I2C_ADDR_7BIT, txBuff, 2);
	DEBUGOUT("Set sensitivity to +-%d dps\n", s);
}

void L3GD20HSensor::calibrateXYZ(void)
{
	// Determine zero bias
	const uint32_t numSamples = 500;
	long long int averages[3] = { 0, 0, 0 };
	uint16_t temps[3];
	for (uint32_t i = 0; i < numSamples; ++i) {
		getRawXYZ(temps[0], temps[1], temps[2]);
		averages[0] += temps[0];
		averages[1] += temps[1];
		averages[2] += temps[2];
	}
	calData.xOffset = (uint32_t) (averages[0] / numSamples);
	calData.yOffset = (uint32_t) (averages[1] / numSamples);
	calData.zOffset = (uint32_t) (averages[2] / numSamples);
	DEBUGOUT("xOffset = %x\n", calData.xOffset);
	DEBUGOUT("yOffset = %x\n", calData.yOffset);
	DEBUGOUT("zOffset = %x\n", calData.zOffset);
}

void L3GD20HSensor::powerOnEnXYZ(void)
{
	// Write to reg ctrl1
	uint8_t txBuff[2] = {
		CTRL1,
		X_ENABLE_MASK | Y_ENABLE_MASK | Z_ENABLE_MASK | NORMAL_MODE_ENABLE_MASK };
	i2cAdapterPtr->write(L3GD20H_I2C_ADDR_7BIT, txBuff, 1);
	DEBUGOUT("Powered on and enabled x, y, z\n");
}

void L3GD20HSensor::getRawXYZ(uint16_t &x, uint16_t &y, uint16_t &z)
{
	// Read from X_L, X_H, Y_L, Y_H, Z_L, Z_H
	uint8_t txBuff[6] = { OUT_X_L, OUT_X_H, OUT_Y_L, OUT_Y_H, OUT_Z_L, OUT_Z_H };
	uint8_t rxBuff[6];
	i2cAdapterPtr->read(L3GD20H_I2C_ADDR_7BIT, txBuff, 6, rxBuff, 6);
	//DEBUGOUT("X_L = %x\n", rxBuff[0]);
	//DEBUGOUT("X_H = %x\n", rxBuff[1]);
	//DEBUGOUT("Y_L = %x\n", rxBuff[2]);
	//DEBUGOUT("Y_H = %x\n", rxBuff[3]);
	//DEBUGOUT("Z_L = %x\n", rxBuff[4]);
	//DEBUGOUT("Z_H = %x\n", rxBuff[5]);
	x = rxBuff[0] + (rxBuff[1] << 8);
	y = rxBuff[2] + (rxBuff[3] << 8);
	z = rxBuff[4] + (rxBuff[5] << 8);
}

void L3GD20HSensor::getXYZ(int32_t &x, int32_t &y, int32_t &z)
{
	// Get raw x, y, z values
	uint16_t rawX;
	uint16_t rawY;
	uint16_t rawZ;
	getRawXYZ(rawX, rawY, rawZ);
	x = (int32_t) rawX;
	y = (int32_t) rawY;
	z = (int32_t) rawZ;

	// Apply offsets
	x -= calData.xOffset;
	y -= calData.yOffset;
	z -= calData.zOffset;

	// Apply sensitivity multipliers
	switch (sensitivity) {
	case PLUS_MINUS_2000DPS:
		x *= MULTIPLIER_2000DPS;
		y *= MULTIPLIER_2000DPS;
		z *= MULTIPLIER_2000DPS;
		break;
	case PLUS_MINUS_500DPS:
		x *= MULTIPLIER_500DPS;
		y *= MULTIPLIER_500DPS;
		z *= MULTIPLIER_500DPS;
		break;
	default: // PLUS_MINUS_245DPS
		x *= MULTIPLIER_245DPS;
		y *= MULTIPLIER_245DPS;
		z *= MULTIPLIER_245DPS;
		break;
	}
}
