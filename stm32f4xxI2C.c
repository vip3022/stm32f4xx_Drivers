/*
 * stm32f4xxI2C.c
 *
 *  Created on: 10-Jan-2021
 *      Author: vipulgupta
 */

#include <stm32f4xxI2C.h>

/*
 * array for preScalers
 */

uint16_t AHB_prescalers[8] = {2,4,8,16,64,128,256,512};
uint8_t APB_prescalers[4] = {2,4,8,16};

/**** driver specific functions ****/

static uint32_t Get_PCLK1_Freq(void);
static uint8_t I2C_FlagStatus(I2C_RegDef_t *I2Cx,uint8_t flag);
static void I2C_GenerateStart(I2C_RegDef_t *I2Cx);
static void I2C_GenerateStop(I2C_RegDef_t *I2Cx);
static void I2C_ReadSR(I2C_RegDef_t *I2Cx);
static void I2C_ReadSR1(I2C_RegDef_t *I2Cx);

/*
 * function name:- 	I2C_INIT
 * description:- 	Initiating the I2C peripheral
 * parameter1:- 	i2c( I2C configuration structure)
 */

void I2C_INIT(I2C_Config_t i2c){

	/** clock stretching is configured **/
	if(i2c.clockStretch == 1)i2c.I2Cx->CR1 &= ~(1<<7);
	else i2c.I2Cx->CR1 |= (1<<7);

	/** PEC is configured **/
	if(i2c.enPEC == 1)i2c.I2Cx->CR1 |= (1<5);
	else i2c.I2Cx->CR1 &= ~(1<<5);

	/** for enabling and disabling ARP **/
	if(i2c.enARP == 1)i2c.I2Cx->CR1 |= (1<5);
	else i2c.I2Cx->CR1 &= ~(1<<5);

	/** 7 bit or 10 bit address mode **/
	if(i2c.ADDR_Mode == 0){
		i2c.I2Cx->OAR1 |= (1<15);
		i2c.I2Cx->OAR1 |=  (i2c.slaveADDR & 0x7f)<1;
	}
	else {
		i2c.I2Cx->OAR1 &= ~((1<<15)|(1<<0));
		i2c.I2Cx->OAR1 |=  (i2c.slaveADDR & 0x1ff)<1;
	}

	/** OAR1 14th bit set by software **/
	i2c.I2Cx->OAR1 |= (1<<14);

	/** configuring the FREQ field **/
	i2c.I2Cx->CR2 |= ((Get_PCLK1_Freq()/1000000) & 0x3F);

	/** fast and standard mode, duty cycle and CCR configuration **/

	uint16_t tempVar;
	if(i2c.FastOrStandardMode == 1){
		i2c.I2Cx->CCR |= (1<<15);

		/** dutyCycle configuration **/

		if(i2c.dutyCyle == 1){
			i2c.I2Cx->CCR |= (1<<14);
			tempVar = ((Get_PCLK1_Freq())/(25*i2c.SCL_freq));
		}
		else{
			i2c.I2Cx->CCR &= ~(1<<14);
			tempVar = ((Get_PCLK1_Freq())/(3*i2c.SCL_freq));
		}

	}
	else {
		i2c.I2Cx->CCR &= ~(1<<15);
		tempVar = ((Get_PCLK1_Freq())/(2*i2c.SCL_freq));
	}
	i2c.I2Cx->CCR |= (tempVar & 0xFFF);

	/*** TRise configuration ***/

	tempVar = Get_PCLK1_Freq()/i2c.SCL_freq;
	i2c.I2Cx->TRISE |= (tempVar & 0x3F);

}

/*
 * function name:- 	I2C_Tx
 * description:- 	to write in data register
 * parameter1:- 	I2Cx(I2C peripheral used)
 */

void I2C_Write(I2C_RegDef_t *I2Cx, uint8_t *msg,uint8_t slaveADDR){

	// generating the start condition
	I2C_GenerateStart(I2Cx);

	// checking start generated or not
	while(!(I2C_FlagStatus(I2Cx,SB)));

	// clearing the SB flag by reading the SR1 register
	I2C_ReadSR1(I2Cx);

	// sending the slave address with the r/w bit
	I2Cx->DR = (slaveADDR<<1);

	// checking that address is sent or not
	while(!(I2C_FlagStatus(I2Cx,ADDR)));

	//clearing the ADDR flag by reading the SR
	I2C_ReadSR(I2Cx);

	// send the data
	I2Cx->DR = *(msg);

	// wait for BTF and TxE flag to set
	while(!(I2C_FlagStatus(I2Cx,BTF) & I2C_FlagStatus(I2Cx,TxE)));

	// generating the stop condition
	I2C_GenerateStop(I2Cx);

}

/*
 * function name:- 	I2C_ACK
 * description:- 	enable or disable acknowledge
 * parameter1:- 	I2Cx(I2C peripheral used)
 * parameter2:-  	state(enable or disable)
 */

void I2C_ACK(I2C_RegDef_t *I2Cx,uint8_t state){

	if(state == 1)I2Cx->CR1 |= (1<<10);
	else I2Cx->CR1 &= ~(1<<10);

}

/*
 * function name:- 	I2C_PE
 * description:- 	enable or disable the peripheral
 * parameter1:- 	I2Cx(I2C peripheral used)
 * parameter2:-  	state(enable or disable)
 */

void I2C_PE(I2C_RegDef_t *I2Cx,uint8_t state){

	if(state == 1)I2Cx->CR1 |= (1<<0);
	else I2Cx->CR1 &= ~(1<<0);

}

/*
 * function name:- 	I2C_GenerateStart
 * description:- 	to generate a start condition
 * parameter1:- 	I2Cx(I2C peripheral used)
 */

static void I2C_GenerateStart(I2C_RegDef_t *I2Cx){
	I2Cx->CR1 |= (1<<8);
}

/*
 * function name:- 	I2C_GenerateStop
 * description:- 	to generate a stop condition
 * parameter1:- 	I2Cx(I2C peripheral used)
 */

static void I2C_GenerateStop(I2C_RegDef_t *I2Cx){
	I2Cx->CR1 |= (1<<9);
}

/*
 * function name:- 	I2C_FlagStatus
 * description:- 	to check the status of the flags in SR1 and SR2
 * parameter1:- 	I2Cx(I2C peripheral used)
 * parameter2:- 	flag(flag you want to check)
 */

static uint8_t I2C_FlagStatus(I2C_RegDef_t *I2Cx,uint8_t flag){

	uint8_t tempVar;

	if(flag<15)tempVar = (I2Cx->SR1 >> flag) & 0x01;

	else tempVar = (I2Cx->SR2 >> flag) & 0x01;

	return tempVar;
}

/*
 * function name:- 	Get_PCLK1_Freq
 * description:- 	initialising the the GPIO pin
 */

static uint32_t Get_PCLK1_Freq(void){

	uint32_t CLK_Src, PCLK1;
	uint16_t AHB_Prescaler;
	uint8_t tempVar,APB_Prescaler;

	tempVar = (RCC->CFGR >> 2) & 0x3;
	if(tempVar == 0) CLK_Src = 16000000;
	else if (tempVar == 1) CLK_Src = 8000000;

	tempVar = (RCC->CFGR >> 4) & 0xf;
	if(tempVar <8)AHB_Prescaler = 1;
	else AHB_Prescaler = AHB_prescalers[tempVar - 8];

	tempVar = (RCC->CFGR >> 10) & 0x7;
	if(tempVar < 4)APB_Prescaler = 1;
	else APB_Prescaler = APB_prescalers[tempVar-4];

	PCLK1 = CLK_Src/(APB_Prescaler*AHB_Prescaler);
	return PCLK1;

}

/*
 * function name:- 	I2C_ReadSR
 * description:- 	to read the SR registers(clearing process)
 * parameter1 :- I2Cx
 */

static void I2C_ReadSR(I2C_RegDef_t *I2Cx){

	uint32_t dummyVar = I2Cx->SR1;
	dummyVar = I2Cx->SR2;
	(void)dummyVar;

}

/*
 * function name:- 	I2C_ReadSR
 * description:- 	to read the SR registers(clearing process)
 * parameter1 :-	I2Cx
 */

static void I2C_ReadSR1(I2C_RegDef_t *I2Cx){

	uint32_t dummyVar = I2Cx->SR1;
	(void)dummyVar;

}





