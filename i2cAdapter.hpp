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

// Supported Hardware Platforms for this I2C Interface
enum boardEnum {
	LPCXPRESSO_1549
};

// LPCXpresso 1549 I2C Modes
enum I2CModeEnum {
	I2C_STANDARD = 0
};

// Generic I2C Interface Class
class I2CAdapter {
private:
	enum boardEnum board;
public:
	/* Use:
	 * 	Instantiate an I2C Adapter for the LPCXpresso 1549 board
	 * Parameters:
	 * 	enum boardEnum boardName: Selects the hardware platform.
	 * 	bool boardIsMaster: Configures the LPCXpresso 1549 board as an
	 * 						I2C master or slave.
	 * 	const uint32_t bitrate: Maximum 3.4 MHz. Sets the bitrate for the
	 * 						    I2C transactions.
	 * 	enum I2CModeEnum mode: Sets the I2C mode on the LPCXpresso 1549 board.
	 */
	I2CAdapter(enum boardEnum boardName,
			bool boardIsMaster,
			const uint32_t bitrate,
			enum I2CModeEnum mode);

	/* Use:
	 * 	Perform I2C Read Transaction
	 * Parameters:
	 * 	uint8_t address: 7 bit I2C target address. Bit 8 (MSB) of this parameter
	 * 					 is unused and should be 0.
	 *	uint8_t * txBufferPtr: Transmit buffer. Elements (bytes) in the array
	 *						   are sent to the target in order from least to
	 *						   greatest array index.
	 *	uint16_t txSize: The number of elements (bytes) in the transmit buffer.
	 *	uint8_t * rxBuffer: Receive buffer. Elements (bytes) in the array are
	 *						received in order from least to greatest array index.
	 *	uint16_t rxSize: The number of elements (bytes) in the receive buffer.
	*/
	bool read(
			uint8_t address,
			uint8_t * txBufferPtr,
			uint16_t txSize,
			uint8_t * rxBufferPtr,
			uint16_t rxSize);

	/* Use:
	 * 	Perform I2C Write Transaction
	 * Parameters:
	 * 	uint8_t address: 7 bit I2C target address. Bit 8 (MSB) of this parameter
	 * 					 is unused and should be 0.
	 *	uint8_t * txBufferPtr: Transmit buffer. Elements (bytes) in the array
	 *						   are sent to the target in order from least to
	 *						   greatest array index.
	 *	uint16_t txSize: The number of elements (bytes) in the transmit buffer.
	*/
	bool write(
			uint8_t address,
			uint8_t * txBufferPtr,
			uint16_t txSize);
};

#endif /* DRIVERS_SRC_I2CADAPTER_HPP_ */
