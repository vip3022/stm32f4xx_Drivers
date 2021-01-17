/*
 * stm32f4xxSPI->c
 *
 *  Created on: 07-Jan-2021
 *      Author: vipulgupta
 */

#include <stm32f4xxSPI.h>

/*
 * driver specific functions
 */

static void NVIC_ISER(uint8_t position);

/*
 * function name:- 	SPI_INIT
 * description:- 	initialising the the SPI peripheral
 * parameter1:- 	*SPI_config(parameters to configure the SPI peripheral)
 */

void SPI_INIT(SPI_config_t *SPI_config){

	/**** preScaler for the clock ****/

	uint16_t tempVar = SPI_config->preScaler << 3;
	SPI_config->SPIx->CR1 |= tempVar;

	/**** clock polarity ****/

	if(SPI_config->CPOL == 1)SPI_config->SPIx->CR1 |= (1<<1);
	else SPI_config->SPIx->CR1 &= ~(1<<1);

	/**** clock phase ****/

	if(SPI_config->CPHA == 1)SPI_config->SPIx->CR1 |= (1<<0);
	else SPI_config->SPIx->CR1 &= ~(1<<0);

	/**** data frame format ****/

	if(SPI_config->dff16_8 == 1)SPI_config->SPIx->CR1 |= (1<<11);
	else SPI_config->SPIx->CR1 &= ~(1<<11);

	/**** msb or lsb configuration ****/

	if(SPI_config->frameFormat == 1)SPI_config->SPIx->CR1 |= (1<<7);
	else SPI_config->SPIx->CR1 &= ~(1<<7);

	/**** enabling half or full duplex ****/

	if(SPI_config->HDFD==1)SPI_config->SPIx->CR1 |= (1<<15);
	else SPI_config->SPIx->CR1 &= ~(1<<15);

	/**** Receive only and transmit only for half duplex ****/

	if(SPI_config->TxRxOnly == 1)SPI_config->SPIx->CR1 |= (1<<14);
	else SPI_config->SPIx->CR1 &= ~(1<<14);


	/**** software slave management ****/

	if(SPI_config->SSM ==1)SPI_config->SPIx->CR1 |= (1<<9);
	else SPI_config->SPIx->CR1 &= ~(1<<9);

	/**** SSI enable ********/

	if(SPI_config->SSI == 1)SPI_config->SPIx->CR1 |= (1<<8);
	else SPI_config->SPIx->CR1 &= ~(1<<8);

	/**** master or slave ****/

	if(SPI_config->masterSlave == 1)SPI_config->SPIx->CR1 |= (1<<2);
	else SPI_config->SPIx->CR1 &= ~(1<<2);

}

/*
 * function name:- 	SPI_MasterWrite
 * description:- 	to write into the data register
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	msg(data you want to send)
 */


void SPI_MasterWrite(SPI_RegDef_t *SPIx, uint8_t TxBuffer){

		while(!(SPI_FlagStatus(SPIx,TxEmptyFlag)));
		SPIx->DR = (TxBuffer);

}

/*
 * function name:- 	SPI_FlagStatus
 * description:- 	to get the flag status from SR register
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	flag(which the user wants to check)
 */

uint8_t SPI_FlagStatus(SPI_RegDef_t *SPIx, uint8_t flag){

	uint8_t tempVar = (SPIx->SR >> flag) & 0x01;
	return tempVar;

}

/*
 * function name:- 	SPI_SSI
 * description:- 	to enable or disable the SSI bit
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	state(eable or disable)
 */


void SPI_SSI(SPI_RegDef_t *SPIx,uint8_t state){

	if(state == 1)SPIx->CR1 |= (1<<8);
	else SPIx->CR1 &= ~(1<<8);

}

/*
 * function name:- 	SPI_SSOE
 * description:- 	to enable or disable the SSOE bit
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	state(eable or disable)
 */

void SPI_SSOE(SPI_RegDef_t *SPIx,uint8_t state){

	if(state == 1)SPIx->CR2 |= (1<<2);
	else SPIx->CR2 &= ~(1<<2);

}

/*
 * function name:- 	SPI_en
 * description:- 	to enable or disable the spi peripheral
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	state(eable or disable)
 */

void SPI_en(SPI_RegDef_t *SPIx){
	SPIx->CR1 |= (1<<6);
}

/*
 * function name:- 	SPI_di
 * description:- 	to enable or disable the spi peripheral
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * parameter2:- 	state(eable or disable)
 */

void SPI_di(SPI_RegDef_t *SPIx){
	while(SPI_FlagStatus(SPIx,BusyFlag))
	SPIx->CR1 &= ~(1<<6);
}

/*
 * function name:- 	SPI_ReadDR
 * description:- 	to enable or disable the spi peripheral
 * parameter1:- 	*SPIx(register defination of the SPI used)
 */

void SPI_ReadDR(SPI_RegDef_t *SPIx){

	uint16_t a = SPIx->DR;
	(void)a;

}

/*
 * function name:-  NVIC_ISER
 * description:- 	to enable the SPIx line on NVIC
*/

static void NVIC_ISER(uint8_t position){

	int x = position/32;
	NVIC->ISER[x] |= (1 << (position%32));

}

/*
 * function name:- 	SPI_INT_en
 * description:- 	enable the SPI interrupt
 * parameter1:- 	*SPIx(register defination of the SPI used)
 * paramter2:- 		INT(interrupt type)
 * paramter3:- 		SPI_NUM(to enable the line on NVIC)
 */

void SPI_INT_en(SPI_RegDef_t *SPIx,uint8_t INT,uint8_t SPI_NUM){

	if(SPI_NUM ==1)NVIC_ISER(42);
	else if(SPI_NUM ==2)NVIC_ISER(43);
	else NVIC_ISER(58);
	SPIx->CR2 |= (1<<INT);

}

