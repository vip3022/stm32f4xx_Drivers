/*
 * stm32f4xxGPIO.h
 *
 *  Created on: 06-Jan-2021
 *      Author: vipulgupta
 */

#ifndef STM32F4XXGPIO_H_
#define STM32F4XXGPIO_H_

#include <stm32f4x.h>

/*
 * macros for configuration
 */

#define INPUT					0
#define OUTPUT					1
#define AF_Mode					2
#define analogeMode				3

/*
 * output type macros
 */

#define PushPull				0
#define OpenDrain				1

/*
 * speed macros
 */

#define lowSpeed				0
#define mediumSpeed				1
#define highSpeed				2
#define veryHighSpeed			3

/*
 * macros for pushUp and pullDown
 */

#define noPushPull				0
#define pullUp					1
#define pullDown				2

/*
 * macros for alternate functions
 */

#define AF0 					0
#define AF1						1
#define AF2						2
#define AF3 					3
#define AF4						4
#define AF5						5
#define AF6 					6
#define AF7						7
#define AF8						8
#define AF9 					9
#define AF10					10
#define AF11					11
#define AF12					12
#define AF13					13
#define AF14					14
#define AF15					15

/*
 * macros for configuration of interrupts
 */

#define RisingEdge				1
#define FallingEdge				0


/*
 * prototypes of functions in .c files
 */

void GPIO_INIT(GPIO_RegDef_t* GPIOx,uint8_t pinNum, uint8_t mode, uint8_t outputType, uint8_t speed, uint8_t pp);
void GPIO_OUTPUT(GPIO_RegDef_t* GPIOx, uint8_t pinNum, uint8_t state);
void GPIO_TogglePin(GPIO_RegDef_t* GPIOx, uint8_t pinNum);
void GPIO_OUTPUT_PORT(GPIO_RegDef_t* GPIOx, uint16_t msg);
uint8_t GPIO_INPUT(GPIO_RegDef_t* GPIOx,uint8_t pinNum);
uint16_t GPIO_INPUT_PORT(GPIO_RegDef_t* GPIOx);
void GPIO_AFMODE(GPIO_RegDef_t* GPIOx,uint8_t pinNum, uint16_t mode);
void GPIO_INT_EN(uint8_t pinNum,uint8_t edge);
void clearPendingRegister(uint8_t pinNum);


#endif /* STM32F4XXGPIO_H_ */
