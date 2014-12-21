/*
 * bmp180.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: steven
 */

#include "bmp180.hpp"
#include "i2cAdapter.hpp"
#include "stdint.h"

BMP180Sensor::BMP180Sensor(bool useTestVals, I2CAdapter * i2cAdPtr, enum modeEnum m)
{
	useTestNumbers = useTestVals;
	i2cAdapterPtr = i2cAdPtr;
	if (m < ULTRALOWPOWER || m > ULTRAHIGHRES) {
		mode = STANDARD;
	} else {
		mode = m;
	}
	verifyId();
	getCalData();
}

bool BMP180Sensor::verifyId(void)
{
	// Read from chip id register
	uint8_t txBuff = REG_CHIPID;
	uint8_t rxBuff;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, &rxBuff, 1);
	DEBUGOUT("BMP180 identified itself as %x\n", rxBuff);
	if (rxBuff != CHIPID) {
		DEBUGOUT("BMP180 should have identified itself as %x\n", CHIPID);
		return false;
	}
	return true;
}

bool BMP180Sensor::getCalData(void)
{
	if (useTestNumbers) {
		calData.ac1 = 408;
		calData.ac2 = -72;
		calData.ac3 = -14383;
		calData.ac4 = 32741;
		calData.ac5 = 32757;
		calData.ac6 = 23153;
		calData.b1 = 6190;
		calData.b2 = 4;
		calData.mb = -32768;
		calData.mc = -8711;
		calData.md = 2868;
		return true;
	}

	bool calDataGood = true;

	// Read from calibration register AC1
	uint8_t txBuff = REG_CAL_AC1;
	uint8_t rxBuff[2];
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac1 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac1 == 0x00 || calData.ac1 == 0xFF) {
		DEBUGOUT("Calibration register AC1 not working.\n");
		DEBUGOUT("Contents of AC1 = %x\n", calData.ac1);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac1 = %x\n", calData.ac1);

	// Read from calibration register AC2
	txBuff = REG_CAL_AC2;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac2 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac2 == 0x00 || calData.ac2 == 0xFF) {
		DEBUGOUT("Calibration register AC2 not working.\n");
		DEBUGOUT("Contents of AC2 = %x\n", calData.ac2);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac2 = %x\n", calData.ac2);

	// Read from calibration register AC3
	txBuff = REG_CAL_AC3;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac3 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac3 == 0x00 || calData.ac3 == 0xFF) {
		DEBUGOUT("Calibration register AC3 not working.\n");
		DEBUGOUT("Contents of AC3 = %x\n", calData.ac3);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac3 = %x\n", calData.ac3);

	// Read from calibration register AC4
	txBuff = REG_CAL_AC4;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac4 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac4 == 0x00 || calData.ac4 == 0xFF) {
		DEBUGOUT("Calibration register AC4 not working.\n");
		DEBUGOUT("Contents of AC4 = %x\n", calData.ac4);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac4 = %x\n", calData.ac4);

	// Read from calibration register AC5
	txBuff = REG_CAL_AC5;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac5 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac5 == 0x00 || calData.ac5 == 0xFF) {
		DEBUGOUT("Calibration register AC5 not working.\n");
		DEBUGOUT("Contents of AC5 = %x\n", calData.ac1);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac5 = %x\n", calData.ac5);

	// Read from calibration register AC6
	txBuff = REG_CAL_AC6;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.ac6 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.ac6 == 0x00 || calData.ac6 == 0xFF) {
		DEBUGOUT("Calibration register AC6 not working.\n");
		DEBUGOUT("Contents of AC6 = %x\n", calData.ac6);
		calDataGood = false;
	}
	DEBUGOUT("calData.ac6 = %x\n", calData.ac6);

	// Read from calibration register B1
	txBuff = REG_CAL_B1;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.b1 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.b1 == 0x00 || calData.b1 == 0xFF) {
		DEBUGOUT("Calibration register B1 not working.\n");
		DEBUGOUT("Contents of B1 = %x\n", calData.b1);
		calDataGood = false;
	}
	DEBUGOUT("calData.b1 = %x\n", calData.b1);

	// Read from calibration register B2
	txBuff = REG_CAL_B2;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.b2 = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.b2 == 0x00 || calData.b2 == 0xFF) {
		DEBUGOUT("Calibration register B2 not working.\n");
		DEBUGOUT("Contents of B2 = %x\n", calData.b2);
		calDataGood = false;
	}
	DEBUGOUT("calData.b2 = %x\n", calData.b2);

	// Read from calibration register MB
	txBuff = REG_CAL_MB;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.mb = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.mb == 0x00 || calData.mb == 0xFF) {
		DEBUGOUT("Calibration register MB not working.\n");
		DEBUGOUT("Contents of MB = %x\n", calData.mb);
		calDataGood = false;
	}
	DEBUGOUT("calData.mb = %x\n", calData.mb);

	// Read from calibration register MC
	txBuff = REG_CAL_MC;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.mc = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.mc == 0x00 || calData.mc == 0xFF) {
		DEBUGOUT("Calibration register MC not working.\n");
		DEBUGOUT("Contents of MC = %x\n", calData.mc);
		calDataGood = false;
	}
	DEBUGOUT("calData.mc = %x\n", calData.mc);

	// Read from calibration register MD
	txBuff = REG_CAL_MD;
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, &txBuff, 1, rxBuff, 2);
	calData.md = rxBuff[1] + (rxBuff[0] << 8);
	// Calibration reg contents cannot be 0x00 or 0xFF
	if (calData.md == 0x00 || calData.md == 0xFF) {
		DEBUGOUT("Calibration register MD not working.\n");
		DEBUGOUT("Contents of MD = %x\n", calData.md);
		calDataGood = false;
	}
	DEBUGOUT("calData.md = %x\n", calData.md);

	return calDataGood;
}


int16_t BMP180Sensor::getRawPressure(void) // MAYBE BROKEN!!
{
	if (useTestNumbers) {
		return 23843;
	}

	int16_t rawPressure;
	// Write pressure command to control reg
	uint8_t txBuff[2] = { REG_CONTROL, READPRESSURECMD };
	i2cAdapterPtr->write(BMP180_I2C_ADDR_7BIT, txBuff, 2);
	// Wait 4.5ms for sensor to take measurement
	static volatile int i;
	for (i = 0; i < 1000000; ++i) {
		i;
	}
	// Read from the data reg
	txBuff[0] = REG_PRESSUREDATA;
	uint8_t rxBuff[2];
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, txBuff, 1, rxBuff, 2);
	rawPressure = rxBuff[1] + (rxBuff[0] << 8);
	return rawPressure;
}

int16_t BMP180Sensor::getRawTemperature(void) // BROKEN!!!
{
	if (useTestNumbers) {
		return 27898;
	}

	int16_t rawTemperature;
	// Write pressure command to control reg
	uint8_t txBuff[2] = { REG_CONTROL, READPRESSURECMD };
	i2cAdapterPtr->write(BMP180_I2C_ADDR_7BIT, txBuff, 2);
	// Wait 4.5ms for sensor to take measurement
	static volatile int i;
	for (i = 0; i < 1000000; ++i) {
		i;
	}
	// Read from the data reg
	txBuff[0] = REG_TEMPDATA;
	uint8_t rxBuff[2];
	i2cAdapterPtr->read(BMP180_I2C_ADDR_7BIT, txBuff, 1, rxBuff, 2);
	rawTemperature = rxBuff[1] + (rxBuff[0] << 8);
	DEBUGOUT("rawTemperature (UT) = %d == %x\n", rawTemperature, rawTemperature);
	return rawTemperature;
}

void BMP180Sensor::getTempAndPres(
		int32_t &temperature,
		int32_t &pressure/*,
		enum tempUnitsEnum units*/)
{
	// Raw values
	int16_t rawTemperature = getRawTemperature();
	int16_t rawPressure = getRawPressure();

	// True temperature calculation
	int32_t x1 = (((int32_t)(rawTemperature) - (int32_t)(calData.ac6)) * (int32_t)(calData.ac5)) >> 15;
	DEBUGOUT("X1 = %d\n", x1);
	int32_t x2 = ((int32_t)(calData.mc) << 11) / (x1 + (int32_t)(calData.md));
	DEBUGOUT("X2 = %d\n", x2);
	int32_t b5 = x1 + x2;
	DEBUGOUT("B5 = %d\n", b5);
	temperature = (b5 + 8) >> 4; // In centi-Degrees Celcuis
	DEBUGOUT("temperature (T) in 0.1 Deg C = %d\n", temperature);

	// True pressure calculation
	int32_t b6 = b5 - 4000;
	DEBUGOUT("B6 = %d\n", b6);
	x1 = ((int32_t)(calData.b2) * ((b6 * b6) >> 12)) >> 11;
	DEBUGOUT("X1 = %d\n", x1);
	x2 = ((int32_t)(calData.ac2) * b6) >> 11;
	DEBUGOUT("X2 = %d\n", x2);
	int32_t x3 = x1 + x2;
	DEBUGOUT("X3 = %d\n", x3);
	int32_t b3 = ((((int32_t)(calData.ac1) * 4 + x3) << mode) + 2) >> 2;
	DEBUGOUT("B3 = %d\n", b3);
	x1 = ((int32_t)(calData.ac3) * b6) >> 13;
	DEBUGOUT("X1 = %d\n", x1);
	x2 = (int32_t)(calData.b1) * ((b6 * b6) >> 12) >> 16;
	DEBUGOUT("X2 = %d\n", x2);
	x3 = ((x1 + x2) + 2) >> 2;
	DEBUGOUT("X3 = %d\n", x3);
	uint32_t b4 = ((int32_t)(calData.ac4) * (uint32_t)(x3 + 32768)) >> 15;
	DEBUGOUT("B4 = %d\n", b4);
	uint32_t b7 = (uint32_t)((int32_t)(rawPressure) - b3) * (50000 >> mode);
	DEBUGOUT("B7 = %d\n", b7);
	if (b7 < 0x80000000) {
		pressure = (b7 << 1) / b4;
	} else {
		pressure = (b7 / b4) << 1;
	}
	DEBUGOUT("p = %d\n", pressure);
	x1 = (pressure >> 8) * (pressure >> 8);
	DEBUGOUT("X1 = %d\n", x1);
	x1 = (x1 * 3038) >> 16;
	DEBUGOUT("X1 = %d\n", x1);
	x2 = (-7357 * pressure) >> 16;
	DEBUGOUT("X2 = %d\n", x2);
	pressure = pressure + ((x1 + x2 + 3791) >> 4);
	DEBUGOUT("Pressure in Pa = %d\n", pressure);
}

