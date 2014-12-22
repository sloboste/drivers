/*
 * i2cAdapter.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#include "board.h"
#include "i2cAdapter.hpp"
#include "stdint.h"

// LPCXpresso 1549 Board Configuration Options
static bool LPCXpresso1549_boardIsI2CMaster;
static uint32_t LPCXpresso1549_i2cBitrate; // Max 3.4 MHz
static enum I2CModeEnum LPCXpresso1549_i2cMode;
static I2CM_XFER_T LPCXpresso1549_i2cmXferRec;
static uint32_t LPCXpresso1549_I2C_CLK_DIVIDER_1P8MHZ; // = 40

void LPCXpresso1549_Init_I2C_PinMux(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 22, IOCON_DIGMODE_EN | LPCXpresso1549_i2cMode);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 23, IOCON_DIGMODE_EN | LPCXpresso1549_i2cMode);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);
}

void LPCXpresso1549_setupI2CMaster(void)
{
	// Enable I2C clock and reset I2C peripheral - the boot ROM does not
	// 	do this
	Chip_I2C_Init(LPC_I2C0);

	// Setup clock rate for I2C
	Chip_I2C_SetClockDiv(LPC_I2C0, LPCXpresso1549_I2C_CLK_DIVIDER_1P8MHZ);

	// Setup I2CM transfer rate
	Chip_I2CM_SetBusSpeed(LPC_I2C0, LPCXpresso1549_i2cBitrate);

	// Enable Master Mode
	Chip_I2CM_Enable(LPC_I2C0);
}

void LPCXpresso1549_setupI2CSlave(void)
{
	// IMPLEMENT ME!
}

// Constructor for LPCXpresso 1549 board
I2CAdapter::I2CAdapter(
		enum boardEnum boardName,
		bool boardIsMaster,
		uint32_t bitrate,
		enum I2CModeEnum mode)
{
	board = boardName;
	LPCXpresso1549_I2C_CLK_DIVIDER_1P8MHZ = 40;
	LPCXpresso1549_boardIsI2CMaster = boardIsMaster;
	if (bitrate > 3400000) {
		bitrate = 3400000;
	}
	LPCXpresso1549_i2cBitrate = bitrate;

	LPCXpresso1549_i2cMode = mode;

	LPCXpresso1549_Init_I2C_PinMux();
	if (boardIsMaster) {
		LPCXpresso1549_setupI2CMaster();
	} else {
		LPCXpresso1549_setupI2CSlave();
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
	LPCXpresso1549_i2cmXferRec.slaveAddr = address;
	LPCXpresso1549_i2cmXferRec.status = 0;
	LPCXpresso1549_i2cmXferRec.txSz = txSize;
	LPCXpresso1549_i2cmXferRec.rxSz = rxSize;
	LPCXpresso1549_i2cmXferRec.txBuff = txBufferPtr;
	LPCXpresso1549_i2cmXferRec.rxBuff = rxBufferPtr;

	Chip_I2CM_XferBlocking(LPC_I2C0, &LPCXpresso1549_i2cmXferRec);

	// Test for valid operation
	if (LPCXpresso1549_i2cmXferRec.status != I2CM_STATUS_OK) {
		DEBUGOUT("Error %d reading from device %x\n",
				LPCXpresso1549_i2cmXferRec.status,
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
	LPCXpresso1549_i2cmXferRec.slaveAddr = address;
	LPCXpresso1549_i2cmXferRec.status = 0;
	LPCXpresso1549_i2cmXferRec.txSz = txSize;
	LPCXpresso1549_i2cmXferRec.rxSz = 0;
	LPCXpresso1549_i2cmXferRec.txBuff = txBufferPtr;
	LPCXpresso1549_i2cmXferRec.rxBuff = NULL;

	Chip_I2CM_XferBlocking(LPC_I2C0, &LPCXpresso1549_i2cmXferRec);

	// Test for valid operation
	if (LPCXpresso1549_i2cmXferRec.status != I2CM_STATUS_OK) {
		DEBUGOUT("Error %d writing to device %x\n",
				LPCXpresso1549_i2cmXferRec.status,
				address);
		return false;
	}
	return true;
}
