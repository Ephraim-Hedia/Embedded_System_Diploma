/*
 * I2C_EEPROM_Slave.h
 *
 *  Created on: Apr 30, 2023
 *      Author: Ephraim
 */

#ifndef INC_I2C_EEPROM_SLAVE_H_
#define INC_I2C_EEPROM_SLAVE_H_

#include "STM32_F103C6_I2C_Driver.h"

//E2PROM is an I2C SLAVE
//Idle Mode : device is in high-impedance state and waits for data .
// Master Transmitter mode : the decive transmits data to a slave receiver
// Master Receiver Mode : the decive receives data from a slave transmitter

#define EEPROM_Slave_address 0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address , unsigned char *bytes , unsigned char Data_Length );
unsigned char eeprom_read_Nbytes(unsigned int address , uint8_t *dataOut , uint8_t dataLen );



#endif /* INC_I2C_EEPROM_SLAVE_H_ */
