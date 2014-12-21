/*
 * i2cAdapter.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#include "board.h"
#include "i2cAdapter.hpp"
#include "stdint.h"

void I2CAdapter::Init_I2C_PinMux(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 22, IOCON_DIGMODE_EN | i2cMode);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 23, IOCON_DIGMODE_EN | i2cMode);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);
}

void I2CAdapter::setupI2CMaster(void)
{
	// Enable I2C clock and reset I2C peripheral - the boot ROM does not
	// 	do this
	Chip_I2C_Init(LPC_I2C0);

	// Setup clock rate for I2C
	Chip_I2C_SetClockDiv(LPC_I2C0, I2C_CLK_DIVIDER_1P8MHZ);

	// Setup I2CM transfer rate
	Chip_I2CM_SetBusSpeed(LPC_I2C0, i2cBitrate);

	// Enable Master Mode
	Chip_I2CM_Enable(LPC_I2C0);
}

void I2CAdapter::setupI2CSlave(void)
{
	// IMPLEMENT ME!
}


I2CAdapter::I2CAdapter(
		bool boardIsMaster,
		uint32_t bitrate,
		enum I2CModeEnum mode)
{
	I2C_CLK_DIVIDER_1P8MHZ = 40;
	boardIsI2CMaster = boardIsMaster;
	if (bitrate > 3400000) {
		bitrate = 3400000;
	}
	i2cBitrate = bitrate;
	i2cMode = mode;

	Init_I2C_PinMux();
	if (boardIsMaster) {
		setupI2CMaster();
	} else {
		setupI2CSlave();
	}
	// Disable the interrupt for the I2C
	NVIC_DisableIRQ(I2C0_IRQn);
}

bool I2CAdapter::read(
		uint8_t address,
		uint8_t * txBufferPtr,
		uint16_t txSize,
		uint8_t * rxBufferPtr,
		uint16_t rxSize)
{
	// Setup I2C transfer record
	i2cmXferRec.slaveAddr = address;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = rxSize;
	i2cmXferRec.txBuff = txBufferPtr;
	i2cmXferRec.rxBuff = rxBufferPtr;

	Chip_I2CM_XferBlocking(LPC_I2C0, &i2cmXferRec);

	// Test for valid operation
	if (i2cmXferRec.status != I2CM_STATUS_OK) {
		DEBUGOUT("Error %d reading from device %x\n",
				i2cmXferRec.status,
				address);
		return false;
	}
	return true;
}

bool I2CAdapter::write(
		uint8_t address,
		uint8_t * txBufferPtr,
		uint16_t txSize)
{
	// Setup I2C transfer record
	i2cmXferRec.slaveAddr = address;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = 0;
	i2cmXferRec.txBuff = txBufferPtr;
	i2cmXferRec.rxBuff = NULL;

	Chip_I2CM_XferBlocking(LPC_I2C0, &i2cmXferRec);

	// Test for valid operation
	if (i2cmXferRec.status != I2CM_STATUS_OK) {
		DEBUGOUT("Error %d writing to device %x\n",
				i2cmXferRec.status,
				address);
		return false;
	}
	return true;
}
