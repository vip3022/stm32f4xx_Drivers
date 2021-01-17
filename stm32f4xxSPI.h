/*
 * stm32f4xxSPI.h
 *
 *  Created on: 07-Jan-2021
 *      Author: vipulgupta
 */

#ifndef STM32F4XXSPI_H_
#define STM32F4XXSPI_H_

#include <stm32f4x.h>

/***** macros for configuration SPI peripheral ****/

#define fullDuplex							0
#define halfDuplex							1

#define RxOnly								0
#define TxOnly								1

#define dff8								0
#define dff16								1

#define MSB									0
#define LSB									1

#define preScaler_2							0
#define preScaler_4							1
#define preScaler_8							2
#define preScaler_16						3
#define preScaler_32						4
#define preScaler_64						5
#define preScaler_128						6
#define preScaler_256						7

#define master								1
#define slave								0

/**** macros for flags in status register ****/

#define BusyFlag							7
#define OverRunFlag							6
#define ModeFlautFlag						5
#define CRC_ErrorFlag						4
#define UnderRunFlag						3
#define ChannelSideFlag						2
#define TxEmptyFlag							1
#define RxNotEmptyFlag						0

/*
 * macros for interrupts of SPI
 */

#define TXEIE								7
#define RXNEIE								6
#define ERRIE								5

/**** structure defination for configuration of SPI ****/

/*
 * member 1:- *SPIx(structure of registers of SPIx)
 * member 2:- HDFD(half duplex and full duplex)
 * member 3:- TxRxOnly(for half duplex)
 * member 4:- dff16_8(16 bit data frame or 8 bit)
 * member 5:- SSM(software slave select)
 * member 6:- SSI(used when SSM is enabled)
 * member 7:- frameFormat(msb or lsb)
 * member 8:- SPI_en(to enable the spi)
 * member 9:- preScaler(to divide the frequency of clock)
 * member 10:- masterSlave(master configuration or slave configuration)
 * member 11:- CPOL(clock polarity)
 * member 12:- CPHA(clock phase)
 */

typedef struct{

	SPI_RegDef_t* SPIx;
	uint8_t HDFD;
	uint8_t	TxRxOnly;
	uint8_t dff16_8;
	uint8_t SSM;
	uint8_t SSI;
	uint8_t frameFormat;
	uint8_t	SPI_en;
	uint8_t preScaler;
	uint8_t masterSlave;
	uint8_t CPOL;
	uint8_t CPHA;

}SPI_config_t;

/*
 * prototypes of functions in .c file
 */

void SPI_INIT(SPI_config_t *SPI_config);
void SPI_MasterWrite(SPI_RegDef_t *SPIx, uint8_t TxBuffer);
uint8_t SPI_FlagStatus(SPI_RegDef_t *SPIx, uint8_t flag);
void SPI_en(SPI_RegDef_t *SPIx);
void SPI_ReadDR(SPI_RegDef_t *SPIx);
void SPI_SSI(SPI_RegDef_t *SPIx,uint8_t state);
void SPI_SSOE(SPI_RegDef_t *SPIx,uint8_t state);
void SPI_di(SPI_RegDef_t *SPIx);
void SPI_INT_en(SPI_RegDef_t *SPIx,uint8_t INT,uint8_t SPI_NUM);


#endif /* STM32F4XXSPI_H_ */
