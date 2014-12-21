/*
 * i2cAdapter.hpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#ifndef DRIVERS_SRC_I2CADAPTER_HPP_
#define DRIVERS_SRC_I2CADAPTER_HPP_

#include "board.h"
#include "stdint.h"

enum I2CModeEnum{
	I2C_STANDARD = 0
};

class I2CAdapter {
private:
	bool boardIsI2CMaster;
	uint32_t i2cBitrate; // Max 3.4 MHz
	enum I2CModeEnum i2cMode;
	I2CM_XFER_T  i2cmXferRec;
	uint32_t I2C_CLK_DIVIDER_1P8MHZ; // = 40
	void Init_I2C_PinMux(void);
	void setupI2CMaster(void);
	void setupI2CSlave();
public:
	I2CAdapter(
			bool boardIsMaster,
			const uint32_t bitrate,
			enum I2CModeEnum mode);
	bool read(
			uint8_t address,
			uint8_t * txBufferPtr,
			uint16_t txSize,
			uint8_t * rxBufferPtr,
			uint16_t rxSize);
	bool write(
			uint8_t address,
			uint8_t * txBufferPtr,
			uint16_t txSize);
};

#endif /* DRIVERS_SRC_I2CADAPTER_HPP_ */
