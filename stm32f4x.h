/*
 * stm32f4x.h
 *
 *  Created on: Jan 4, 2021
 *      Author: vipulgupta
 */

#ifndef STM32F4X_H_
#define STM32F4X_H_


#include <stdint.h>
#define __v volatile

/*
 * initializing the NVIC base address
 */

#define NVIC_BASE_addr					(0xE000E100U)

/*
 *  NVIC registers(processor specific)
 */

typedef struct
{
	uint32_t   ISER[8];     /* Address offset: 0x000 - 0x01C */
	uint32_t  RES0[24];     /* Address offset: 0x020 - 0x07C */
	uint32_t   ICER[8];     /* Address offset: 0x080 - 0x09C */
	uint32_t  RES1[24];     /* Address offset: 0x0A0 - 0x0FC */
	uint32_t   ISPR[8];     /* Address offset: 0x100 - 0x11C */
	uint32_t  RES2[24];     /* Address offset: 0x120 - 0x17C */
	uint32_t   ICPR[8];     /* Address offset: 0x180 - 0x19C */
	uint32_t  RES3[24];     /* Address offset: 0x1A0 - 0x1FC */
	uint32_t   IABR[8];     /* Address offset: 0x200 - 0x21C */
	uint32_t  RES4[56];     /* Address offset: 0x220 - 0x2FC */
	uint8_t   IPR[240];     /* Address offset: 0x300 - 0x3EC */
	uint32_t RES5[644];     /* Address offset: 0x3F0 - 0xEFC */
	uint32_t      STIR;    /* Address offset:         0xF00 */
} NVIC_RegDef_t;

/*
 * initailising the structure
 */

#define NVIC						((NVIC_RegDef_t*)NVIC_BASE_addr)

/*
 * helpful macros
 */

#define HIGH 					1
#define LOW 					0
#define RESET					0
#define SET						1
#define enable 					1
#define disable					0

/*
 *  initialisation of main memories
 */

#define Flash_baseAddr 				0x08000000U				/* flash base address*/
#define SRAM_baseAddr				0x20000000U				/* SRAM base address */

/*
 *  initialisation of AHB/APB buses
 */

#define AHB3_base					0xA0000000U				/* AHB3 base address*/
#define AHB2_base					0x50000000U				/* AHB2 base address*/
#define AHB1_base					0x40020000U				/* AHB1 base address*/
#define APB2_base					0x40010000U				/* APB2 base address*/
#define APB1_base					0x40000000U				/* APB1 base address*/

/*
 *  initialising the AHB1 peripheral
 */

#define GPIOA_addr					(AHB1_base)				/* GPIOA base address*/
#define GPIOB_addr					(AHB1_base + 0x0400)		/* GPIOB base address*/
#define GPIOC_addr					(AHB1_base + 0x0800)		/* GPIOC base address*/
#define GPIOD_addr					(AHB1_base + 0x0C00)		/* GPIOD base address*/
#define GPIOE_addr					(AHB1_base + 0x1000)		/* GPIOE base address*/
#define GPIOF_addr					(AHB1_base + 0x1400)		/* GPIOF base address*/
#define GPIOG_addr					(AHB1_base + 0x1800)		/* GPIOG base address*/
#define GPIOH_addr					(AHB1_base + 0x1C00)		/* GPIOH base address*/
#define GPIOI_addr					(AHB1_base + 0x2000)		/* GPIOI base address*/
#define GPIOJ_addr					(AHB1_base + 0x2400)		/* GPIOJ base address*/
#define GPIOK_addr					(AHB1_base + 0x2800)		/* GPIOK base address*/

#define RCC_addr					(AHB1_base + 0x3800)		/* RCC base address */

/*
 * initialising the APB2 peripheral
 */

#define SPI1_base					(APB2_base + 0x3000)		/* SPI1 base address */
#define SPI4_base					(APB2_base + 0x3400)		/* SPI1 base address */
#define SPI5_base					(APB2_base + 0x5000)		/* SPI1 base address */
#define SPI6_base					(APB2_base + 0x5400)		/* SPI1 base address */

#define EXTI_base 					(APB2_base + 0x3C00)		/* EXTI base address */

#define	SYSCONFIG_base 				(APB2_base + 0x3800)		/* EXTI base address */

/*
 * initialising the APB1 peripheral
 */

#define SPI2_base					(APB1_base + 0x3800)		/* SPI2 base address */
#define SPI3_base					(APB1_base + 0x3C00)		/* SPI2 base address */
#define I2C1_base					(APB1_base + 0x5400)		/* I2C1 base address */
#define I2C2_base					(APB1_base + 0x5800)		/* I2C1 base address */
#define I2C3_base					(APB1_base + 0x5C00)		/* I2C1 base address */

/*
 * initialising structures
 */

#define RCC 						((RCC_RegDef_t*)RCC_addr)

#define GPIOA 						((GPIO_RegDef_t*)GPIOA_addr)
#define GPIOB 						((GPIO_RegDef_t*)GPIOB_addr)
#define GPIOC 						((GPIO_RegDef_t*)GPIOC_addr)
#define GPIOD 						((GPIO_RegDef_t*)GPIOD_addr)
#define GPIOE 						((GPIO_RegDef_t*)GPIOE_addr)
#define GPIOF 						((GPIO_RegDef_t*)GPIOF_addr)
#define GPIOG						((GPIO_RegDef_t*)GPIOG_addr)

#define SPI1						((SPI_RegDef_t*)SPI1_base)
#define SPI2						((SPI_RegDef_t*)SPI2_base)
#define SPI3						((SPI_RegDef_t*)SPI3_base)
#define SPI4						((SPI_RegDef_t*)SPI4_base)
#define SPI5						((SPI_RegDef_t*)SPI5_base)
#define SPI6						((SPI_RegDef_t*)SPI6_base)

#define I2C1						((I2C_RegDef_t*)I2C1_base)
#define I2C2						((I2C_RegDef_t*)I2C2_base)
#define I2C3						((I2C_RegDef_t*)I2C3_base)

#define EXTI						((EXTI_RegDef_t*)EXTI_base)


/*
 * structure for RCC registers
 */

typedef struct{

	__v uint32_t CR;
	__v uint32_t PLLCFGR;
	__v uint32_t CFGR;
	__v uint32_t CIR;

	__v uint32_t AHB1RSTR;
	__v uint32_t AHB2RSTR;
	__v uint32_t AHB3RSTR;
	__v uint32_t RESERVED1;

	__v uint32_t APB1RSTR;
	__v uint32_t APB2RSTR;
	__v uint32_t RESERVED2;
	__v uint32_t RESERVED3;

	__v uint32_t AHB1ENR;
	__v uint32_t AHB2ENR;
	__v uint32_t AHB3ENR;
	__v uint32_t RESERVED4;

	__v uint32_t APB1ENR;
	__v uint32_t APB2ENR;
	__v uint32_t RESERVED5;
	__v uint32_t RESERVED6;

	__v uint32_t AHB1LPENR;
	__v uint32_t AHB2LPENR;
	__v uint32_t AHB3LPENR;
	__v uint32_t RESERVED7;

	__v uint32_t APB1LPENR;
	__v uint32_t APB2LPENR;
	__v uint32_t RESERVED8;
	__v uint32_t RESERVED9;

	__v uint32_t BDCR;
	__v uint32_t CSR;
	__v uint32_t RESERVED10;
	__v uint32_t RESERVED11;

	__v uint32_t SSCGR;
	__v uint32_t PLLI2SCFGR;
	__v uint32_t PLLSAICFGR;
	__v uint32_t DCKCFGR;

}RCC_RegDef_t;

typedef struct{

	__v uint32_t MODER;
	__v uint32_t OTYPER;
	__v uint32_t OSPEEDR;
	__v uint32_t PUPDR;
	__v uint32_t IDR;
	__v uint32_t ODR;
	__v uint32_t BSRR;
	__v uint32_t LCKR;
	__v uint32_t AFRL;
	__v uint32_t AFRH;

} GPIO_RegDef_t;

/*
 * structure for SPI registers
 */

typedef struct{

	__v uint32_t CR1;
	__v uint32_t CR2;
	__v uint32_t SR;
	__v uint32_t DR;
	__v uint32_t CRCPR;
	__v uint32_t RXCRCR;
	__v uint32_t TXCRCR;
	__v uint32_t I2SCFGR;
	__v uint32_t I2SPR;

}SPI_RegDef_t;

typedef struct{

	__v uint32_t CR1;
	__v uint32_t CR2;
	__v uint32_t OAR1;
	__v uint32_t OAR2;
	__v uint32_t DR;
	__v uint32_t SR1;
	__v uint32_t SR2;
	__v uint32_t CCR;
	__v uint32_t TRISE;
	__v uint32_t FLTR;

} I2C_RegDef_t;

/*
 * structure for EXTI
 */

typedef struct{

	__v uint32_t IMR;
	__v uint32_t EMR;
	__v uint32_t RTSR;
	__v uint32_t FTSR;
	__v uint32_t SWIER;
	__v uint32_t PR;

} EXTI_RegDef_t;


/*
 * macros to enable clock for GPIOs
 */

#define GPIOA_PCEN()						(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCEN()						(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCEN()						(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCEN()						(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCEN()						(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCEN()						(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCEN()						(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCEN()						(RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCEN()						(RCC->AHB1ENR |= (1<<8))
#define GPIOJ_PCEN()						(RCC->AHB1ENR |= (1<<9))
#define GPIOK_PCEN()						(RCC->AHB1ENR |= (1<<10))

/*
 * macros to enable clock SPI
 */

#define SPI1_PCEN()							(RCC->APB2ENR |= (1<<12))
#define SPI2_PCEN()							(RCC->APB1ENR |= (1<<14))
#define SPI3_PCEN()							(RCC->APB1ENR |= (1<<15))
#define SPI4_PCEN()							(RCC->APB2ENR |= (1<<13))
#define SPI5_PCEN()							(RCC->APB2ENR |= (1<<20))
#define SPI6_PCEN()							(RCC->APB2ENR |= (1<<21))

/*
 * macros to enable clock for I2C
 */

#define I2C1_PCEN()							(RCC->APB1ENR |= (1<<21))
#define I2C2_PCEN()							(RCC->APB1ENR |= (1<<22))
#define I2C3_PCEN()							(RCC->APB1ENR |= (1<<23))

#endif /* STM32F4X_H_ */
