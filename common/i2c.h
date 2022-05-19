/*
 * i2c.h
 *
 *  Created on: 2017-4-20
 *      Author: Administrator
 */

#ifndef I2C_H_
#define I2C_H_

#include "5509.h"
#include "util.h"

extern void I2C_Init();
extern void I2C_Disable();
extern void I2C_Write(unsigned short int device, int count, unsigned char *bytedata);
extern void I2C_Read(unsigned short int device, int count, unsigned char *bytedata);

#endif /* I2C_H_ */
