/*
 * interrupt.c
 *
 *  Created on: 14-Jan-2021
 *      Author: vipulgupta
 */

#include <stm32f4xxGPIO.h>
#include <stm32f4xxSPI.h>

int main(void){

	SPI2_PCEN();

	SPI_INT_en(SPI2,TXEIE,2);
	GPIOA_PCEN();
	GPIOD_PCEN();
	GPIO_INIT(GPIOD,12,OUTPUT,PushPull,highSpeed,noPushPull);
	GPIO_INIT(GPIOD,13,OUTPUT,PushPull,highSpeed,noPushPull);
	GPIO_INIT(GPIOD,14,OUTPUT,PushPull,highSpeed,noPushPull);
	GPIO_INIT(GPIOD,15,OUTPUT,PushPull,highSpeed,noPushPull);

	GPIO_OUTPUT(GPIOD,13,HIGH);
	GPIO_OUTPUT(GPIOD,15,HIGH);
	GPIO_INT_EN(0,RisingEdge);

	while(1);

}


void EXTI0_IRQHandler(void){

	GPIO_TogglePin(GPIOD,12);
	GPIO_TogglePin(GPIOD,13);
	GPIO_TogglePin(GPIOD,14);
	GPIO_TogglePin(GPIOD,15);
	clearPendingRegister(13);


}
