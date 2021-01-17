/*
 * stm32f4xxGPIO.c
 *
 *  Created on: 06-Jan-2021
 *      Author: vipulgupta
 */


#include <stm32f4xxGPIO.h>

/*
 * driver specific functions
 */

static void NVIC_ISER(uint8_t number);

/*
 * function name:- 	GPIO_INIT
 * description:- 	initialising the the GPIO pin
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	pinNum(pin number of the pin to configure)
 * parameter3:-		mode(input/output)
 * parameter4:- 	outputType(specify the
 */

void GPIO_INIT(GPIO_RegDef_t* GPIOx,uint8_t pinNum, uint8_t mode, uint8_t outputType, uint8_t speed, uint8_t pp){

	GPIOx->MODER &= ~(0b11<<(2*pinNum));
	GPIOx->MODER |= (mode<<(pinNum*2));

	if(outputType == 1)GPIOx->OTYPER |= (1<<pinNum);
	else GPIOx->OTYPER &= ~(1<<pinNum);

	GPIOx->OSPEEDR &= ~(0b11<<(2*pinNum));
	GPIOx->OSPEEDR |= (speed << (2*pinNum));

	GPIOx->PUPDR &= ~(0b11<<(2*pinNum));
	GPIOx->PUPDR |= (pp << (2*pinNum));

}

/*
 * function name:- 	GPIO_OUTPUT
 * description:- 	to give output to pins
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	pinNum(pin number to which the input is given)
 */

void GPIO_OUTPUT(GPIO_RegDef_t* GPIOx, uint8_t pinNum, uint8_t state){

	if(state == 1)GPIOx->ODR |= (1<<pinNum);
	else GPIOx->ODR &= ~(1<<pinNum);

}

/*
 * function name:- 	GPIO_TogglePin
 * description:- 	to toggle the given pin
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	pinNum(toggeling pin number)
 */

void GPIO_TogglePin(GPIO_RegDef_t* GPIOx, uint8_t pinNum){
	GPIOx->ODR ^= (1<<pinNum);
}

/*
 * function name:- 	GPIO_OUTPUT_PORT
 * description:- 	to give output to a port
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	msg(16bit data)
 */

void GPIO_OUTPUT_PORT(GPIO_RegDef_t* GPIOx, uint16_t msg){

	GPIOx->ODR &= ~(0xFFFF);
	GPIOx->ODR |= (msg);

}

/*
 * function name:- 	GPIO_INPUT
 * description:- 	to take inputs from pin
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	pinNum(pin number from the input is taken)
 */

uint8_t GPIO_INPUT(GPIO_RegDef_t* GPIOx,uint8_t pinNum){

	uint8_t tempVar = (GPIOx->IDR >> pinNum) & 0x01;
	return tempVar;
}

/*
 * function name:- 	GPIO_INPUT
 * description:- 	to take inputs from a port
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
*/

uint16_t GPIO_INPUT_PORT(GPIO_RegDef_t* GPIOx){

	uint16_t tempVar = GPIOx->IDR;
	return tempVar;

}

/*
 * function name:- 	GPIO_AFMODE
 * description:- 	to take inputs from pin
 * parameter1:- 	GPIOx(structure GPIOx port's registers)
 * parameter2:- 	pinNum(to enable the alternate function of that pin)
 * parameter3:-		mode(alternate function mode)
*/

void GPIO_AFMODE(GPIO_RegDef_t* GPIOx,uint8_t pinNum, uint16_t mode){

	if(pinNum < 8){
		GPIOx->AFRL &= ~(0b1111<< (pinNum*4));
		GPIOx->AFRL |= (mode<<(4*pinNum));
	}
	else {
		GPIOx->AFRH &= ~(0b1111<< (pinNum*4));
		GPIOx->AFRH |= (mode<<(4*pinNum));
	}

}

/*
 * function name:- 	GPIO_INT_EN
 * description:- 	to enable the interrupt for the given pin
 * parameter2:- 	pinNum(to enable interrupt of that pin)
 * parameter3:-		edge(rising edge or falling edge)
*/

void GPIO_INT_EN(uint8_t pinNum,uint8_t edge){

	EXTI->IMR |= (1<<pinNum);
	EXTI->EMR |= (1<<pinNum);

	if(edge)EXTI->RTSR |= (1<<pinNum);
	else EXTI->FTSR |= (1<<pinNum);

	if(pinNum < 5)NVIC_ISER(6+pinNum);
	else if((4 < pinNum) & (pinNum < 10))NVIC_ISER(30);
	else NVIC_ISER(47);

}

/*
 * function name:- 	ClearPendingRegister
 * description:- 	to clear the interrupt pending register for that pin
 * parameter2:- 	pinNum
*/

void clearPendingRegister(uint8_t pinNum){

	EXTI->PR |= (1<< pinNum);

}

/*
 * function name:-  NVIC_ISER
 * description:- 	to enable the EXTI line for that pin
*/

static void NVIC_ISER(uint8_t position){

	int x = position/32;
	NVIC->ISER[x] |= (1 << (position%31));

}




