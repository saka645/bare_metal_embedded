/*
 * i2c.h
 *
 *  Created on: Feb 20, 2024
 *      Author: sanjay.kumar
 */

#ifndef I2C_H_
#define I2C_H_

void I2C_Init(void);
void i2c1_read(char sadd, char madd, char *data);
void i2c1_brustRead(char sadd, char madd, int n, char *data);
void i2c1_brustWrite(char sadd, char madd, int n, char *data);
#endif /* I2C_H_ */
