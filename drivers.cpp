/*
===============================================================================
 Name        : drivers.cpp
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include "i2cAdapter.hpp"

#include "bmp180.hpp"
#include "l3gd20h.hpp"
//#include"lsm303dlhc.hpp"

int main(void) {

	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED states
	int k;
	for (k = 0; k < 3; ++k) {
		Board_LED_Set(k, false);
	}

	// I2C Adapter
	I2CAdapter i2cAd(LPCXPRESSO_1549, true, 100000, I2C_STANDARD);

	// BMP180
	//BMP180Sensor bmp(false, &i2cAd, STANDARD);

	// L3GD20H
	L3GD20HSensor gyro(&i2cAd, PLUS_MINUS_245DPS);
	gyro.powerOnEnXYZ();
	gyro.calibrateXYZ();

	// LSM303DLC
	//LSM303DLHCSensor mag(&i2cAd);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    volatile static int j = 0;
    // Enter an infinite loop, just incrementing a counter
    while(1) {

        i++ ;
        Board_LED_Toggle(0); // Red
		for (j = 0; j < 1000000; ++j) {
			i++;
		}
		Board_LED_Toggle(0);
		Board_LED_Toggle(1); // Green
		for (j = 0; j < 1000000; ++j) {
			i++;
		}
		Board_LED_Toggle(1);
		Board_LED_Toggle(2); // Blue
		for (j = 0; j < 1000000; ++j) {
			i++;
		}
		// White (RGB)
		Board_LED_Toggle(0);
		Board_LED_Toggle(1);
		for (j = 0; j < 1000000; ++j) {
			i++;
		}
		Board_LED_Toggle(0);
		Board_LED_Toggle(1);
		Board_LED_Toggle(2);

    	/* I2C read
    	uint8_t addr = 0x77;
    	uint8_t rxBuff[1] = { 0x00 };
    	uint8_t txBuff[1] = { 0xD0 };
    	i2cAd.read(addr, txBuff, 1, rxBuff, 1);
    	DEBUGOUT("Chip_id = %x\n", rxBuff[0]);
		*/

		/* Poll bmp sensor
		int32_t temperature = -1;
		int32_t pressure = -1;
		bmp.getTempAndPres(temperature, pressure);
		DEBUGOUT("Temperature = %d degrees C\n", temperature/10);
		DEBUGOUT("Pressure = %d Pa\n", pressure);
		DEBUGOUT("--------\n");*/

		// Poll gyro
		int32_t x;
		int32_t y;
		int32_t z;
		gyro.getXYZ(x, y, z);
		DEBUGOUT("X = %d dps\n", x/1000);
		DEBUGOUT("Y = %d dps\n", y/1000);
		DEBUGOUT("Z = %d dps\n", z/1000);
		DEBUGOUT("--------\n");

		// Poll mag
		//mag.verifyId();
	}

    return 0 ;
}
