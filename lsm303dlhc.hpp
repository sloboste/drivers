/*
 * lsm303dlhc.hpp
 *
 *  Created on: Dec 21, 2014
 *      Author: steven
 */

#ifndef LSM303DLHC_HPP_
#define LSM303DLHC_HPP_

#include "i2cAdapter.hpp"
#include "stdint.h"

class LSM303DLHCSensor {
private:
	I2CAdapter * i2cAdapterPtr;

public:
	LSM303DLHCSensor(I2CAdapter * i2cAdPtr);
	bool verifyId(void);

};

#endif /* LSM303DLHC_HPP_ */
