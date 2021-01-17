/*
 * stm32f4xxI2C.h
 *
 *  Created on: 10-Jan-2021
 *      Author: vipulgupta
 */

#ifndef STM32F4XXI2C_H_
#define STM32F4XXI2C_H_

#include <stm32f4x.h>
#include <stm32f4xxGPIO.h>

/*
 * macros for configuration
 */

#define fastMode						1
#define standardMode					0

#define ADDR_Mode_7						0
#define ADDR_Mode_10					1

#define dutyCycle2						0
#define dutyCycle16_9					1

/*
 * macros of flag names
 */
//SR2
#define DUALF							21
#define SMBHOST							20
#define SMBDEFAULT						5
#define GENCALL							19
#define TRA								18
#define BUSY							17
#define MSL								16

//SR1
#define SMBALERT						15
#define TIMEOUT							14
#define PECERR							12
#define OVR								11
#define AF								10
#define ARLO							9
#define BERR							8
#define TxE								7
#define RxNE							6
#define STOPF							4
#define ADD10							3
#define BTF								2
#define ADDR							1
#define SB								0

/*
 * structure definition for I2Cx configuration
 * member 1:- clockStretching (to enable or disable clock stretch
 * member 2:- enPEC(to enable or disable PEC)
 * member 3:- enARP(to enable or disable ARP)
 * member 4:- FREQ(frequency of the APB1 bus)
 * member 5:- slaveADRR(slave address)
 * member 6:- CCR
 * member 7:- TRise(time taken by pulse reach 70% from 30% rise either SDA or SCL)
 * member 8:- FastOrStandardMode
 * member 9:- dutyCycle;
 * member 10:- ADDR_Mode(10 bit or 7 bit address mode)
 * member 11:- I2Cx(I2C peripheral used)
 */

typedef struct{

	I2C_RegDef_t *I2Cx;
	uint32_t SCL_freq;
	uint8_t clockStretch;
	uint8_t enPEC;
	uint8_t enARP;
	uint16_t slaveADDR;
	uint8_t FastOrStandardMode;
	uint8_t dutyCyle;
	uint8_t ADDR_Mode;

} I2C_Config_t;

/*
 * prototypes of the function in .c file
 */

void I2C_INIT(I2C_Config_t i2c);
void I2C_Write(I2C_RegDef_t *I2Cx, uint8_t *msg,uint8_t slaveADDR);
void I2C_ACK(I2C_RegDef_t *I2Cx,uint8_t state);
void I2C_ACK(I2C_RegDef_t *I2Cx,uint8_t state);
void I2C_PE(I2C_RegDef_t *I2Cx,uint8_t state);


#endif /* STM32F4XXI2C_H_ */
