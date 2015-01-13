/*
 * lsm303dlhc.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: steven
 */

#include "lsm303dlhc.hpp"
#include "stdint.h"

// Miscellaneous Constants
enum {
	ACCEL_ADDR_7BIT			= 0x19,
	MAG_ADDR_7BIT 			= 0x1E,
	TEMP_ENABLE_MASK 		= 0x80,
	AUTOINC_MASK			= 0x80
};

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
	FIFO_CTRL_REG_A		= 0x2E,
	FIFO_SRC_REG_A		= 0x2F,
	INT1_CFG_A			= 0x30,
	INT1_SOURCE_A		= 0x31,
	INT1_THS_A			= 0x32,
	INT1_DURATION_A		= 0x33,
	INT2_CFG_A			= 0x34,
	INT2_SOURCE_A		= 0x35,
	INT2_THS_A			= 0x36,
	INT2_DURATION_A		= 0x37,
	CLICK_CFG_A			= 0x38,
	CLICK_SRC_A			= 0x39,
	CLICK_THS_A			= 0x3A,
	TIME_LIMIT_A		= 0x3B,
	TIME_LATENCY_A		= 0x3C,
	TIME_WINDOW_A		= 0x3D,
	CRA_REG_M			= 0x00,
	CRB_REG_M			= 0x01,
	MR_REG_M			= 0x02,
	OUT_X_H_M			= 0x03,
	OUT_X_L_M			= 0x04,
	OUT_Y_H_M			= 0x05,
	OUT_Y_L_M			= 0x06,
	OUT_Z_H_M			= 0x07,
	OUT_Z_L_M			= 0x08,
	SR_REG_Mg			= 0x09,
	IRA_REG_M			= 0x0A,
	IRB_REG_M			= 0x0B,
	IRC_REG_M			= 0x0C,
	TEMP_OUT_H_M		= 0x31,
	TEMP_OUT_L_M		= 0x32
};


LSM303DLHCSensor::LSM303DLHCSensor(I2CAdapter * i2cAdPtr)
{
	i2cAdapterPtr = i2cAdPtr;
}

void LSM303DLHCSensor::enableAccelXYZ(void)
{
	// Read from CTRL_REG1_A, bit mask, and write back
	uint8_t txBuff[2] = { CTRL_REG1_A, 0x00 };
	uint8_t rxBuff[1];
	i2cAdapterPtr->read(ACCEL_ADDR_7BIT, txBuff, 1, rxBuff, 1);
	txBuff[1] = rxBuff[0] | 0x07;
	i2cAdapterPtr->write(ACCEL_ADDR_7BIT, txBuff, 2);
}

/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
void LSM303DLHCSensor::enableTemperature(void)
{
	// Read from CRA_REG_M, bit mask, and write back
	DEBUGOUT("Enabling temperature\n");
	uint8_t txBuff[2] = { CRA_REG_M, 0x00 };
	uint8_t rxBuff;
	i2cAdapterPtr->read(MAG_ADDR_7BIT, txBuff, 1, &rxBuff, 1);
	txBuff[1] = rxBuff | TEMP_ENABLE_MASK;
	i2cAdapterPtr->write(MAG_ADDR_7BIT, txBuff, 2);
}
*/

void LSM303DLHCSensor::getAccelXYZ(int32_t &x, int32_t &y, int32_t &z)
{
	// FIXME: put in math equations
	int16_t rawX;
	int16_t rawY;
	int16_t rawZ;
	getRawAccelXYZ(rawX, rawY, rawZ);

	// DO MATH HERE????

	x = (int32_t) rawX;
	y = (int32_t) rawY;
	z = (int32_t) rawZ;
}

void LSM303DLHCSensor::getMagXYZ(int32_t &x, int32_t &y, int32_t &z)
{
	// FIXME: put in math equations
	int16_t rawX;
	int16_t rawY;
	int16_t rawZ;
	getRawMagXYZ(rawX, rawY, rawZ);

	// DO MATH HERE????

	x = (int32_t) rawX;
	y = (int32_t) rawY;
	z = (int32_t) rawZ;
}

void LSM303DLHCSensor::getRawAccelXYZ(int16_t &x, int16_t &y, int16_t &z)
{
	// Read from OUT_X_L_A, OUT_X_H_A, OUT_Y_L_A, OUT_Y_H_A, OUT_Z_L_A, OUT_Z_H_A
	uint8_t txBuff[1] = { OUT_X_L_A | AUTOINC_MASK };
	uint8_t rxBuff[6];
	i2cAdapterPtr->read(ACCEL_ADDR_7BIT, txBuff, 1, rxBuff, 6);
	x = (rxBuff[1] << 8) + rxBuff[0];
	y = (rxBuff[3] << 8) + rxBuff[2];
	z = (rxBuff[5] << 8) + rxBuff[4];
	printf("rawX_A = %x\n", x);
	printf("rawY_A = %x\n", y);
	printf("rawZ_A = %x\n", z);
}

void LSM303DLHCSensor::getRawMagXYZ(int16_t &x, int16_t &y, int16_t &z)
{
	// Read from OUT_X_H_M, OUT_X_L_M, OUT_Z_H_M, OUT_Z_L_M, OUT_Y_H_M, OUT_Y_L_M
	uint8_t txBuff[1] = { OUT_X_H_M | AUTOINC_MASK };
	uint8_t rxBuff[6];
	i2cAdapterPtr->read(MAG_ADDR_7BIT, txBuff, 1, rxBuff, 6);
	x = (rxBuff[0] << 8) + rxBuff[1];
	z = (rxBuff[2] << 8) + rxBuff[3];
	y = (rxBuff[4] << 8) + rxBuff[5];
	printf("rawX = %x\n", x);
	printf("rawZ = %x\n", z);
	printf("rawY = %x\n", y);
}

/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
int16_t LSM303DLHCSensor::getRawTemperature(void)
{
	// Read from TEMP_OUT_H_M and TEMP_OUT_L_M
	int16_t rawTemperature;
	uint8_t txBuff = TEMP_OUT_H_M | AUTOINC_MASK;
	uint8_t rxBuff[2];
	i2cAdapterPtr->read(MAG_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	DEBUGOUT("TEMP_OUT_H_M = %x\n", rxBuff[0]);
	DEBUGOUT("TEMP_OUT_L_M = %x\n", rxBuff[1]);
	rawTemperature = (rxBuff[0] << 4) + (rxBuff[1] >> 4);
	DEBUGOUT("rawTemperature = %x  8LSB/degree, 12-bit res\n", rawTemperature);
	return rawTemperature;
}
*/

/* DON'T USE THIS. NOT ENABLED ON THE CHIP!!
int32_t LSM303DLHCSensor::getTemperature(void)
{
	// Convert raw temperature to temp in degrees Celcius
	int32_t temperature = (int32_t) getRawTemperature();
	temperature /= 8;
	return temperature;
}
*/

void LSM303DLHCSensor::setMagMode(enum magModeEnum m)
{
	// Write the mode to register MR_REG_M
	uint8_t txBuff[2] = { MR_REG_M, m };
	i2cAdapterPtr->write(MAG_ADDR_7BIT, txBuff, 2);
}

