/*
 * LCD_SPI_24.h
 *
 *  Created on: 15-Jan-2021
 *      Author: vipulgupta
 */

#ifndef LCD_SPI_24_H_
#define LCD_SPI_24_H_

#include "stm32f4xxGPIO.h"
#include "stm32f4xxSPI.h"
#include "string.h"

/*
 * macros for command
 */
#define ILI9341_WIDTH       				240
#define ILI9341_HEIGHT      				320
#define ILI9341_PIXEL_COUNT					ILI9341_WIDTH * ILI9341_HEIGHT

//ILI9341 LCD commands
#define ILI9341_RESET			 		    0x01
#define ILI9341_SLEEP_OUT		  			0x11
#define ILI9341_GAMMA			    		0x26
#define ILI9341_DISPLAY_OFF					0x28
#define ILI9341_DISPLAY_ON					0x29
#define ILI9341_COLUMN_ADDR					0x2A
#define ILI9341_PAGE_ADDR			  		0x2B
#define ILI9341_GRAM				    	0x2C
#define ILI9341_TEARING_OFF					0x34
#define ILI9341_TEARING_ON					0x35
#define ILI9341_DISPLAY_INVERSION			0xb4
#define ILI9341_MAC			        		0x36
#define ILI9341_PIXEL_FORMAT    			0x3A
#define ILI9341_WDB			    	  		0x51
#define ILI9341_WCD				      		0x53
#define ILI9341_RGB_INTERFACE   			0xB0
#define ILI9341_FRC					    	0xB1
#define ILI9341_BPC					    	0xB5
#define ILI9341_DFC				 	    	0xB6
#define ILI9341_Entry_Mode_Set				0xB7
#define ILI9341_POWER1						0xC0
#define ILI9341_POWER2						0xC1
#define ILI9341_VCOM1						0xC5
#define ILI9341_VCOM2						0xC7
#define ILI9341_POWERA						0xCB
#define ILI9341_POWERB						0xCF
#define ILI9341_PGAMMA						0xE0
#define ILI9341_NGAMMA						0xE1
#define ILI9341_DTCA						0xE8
#define ILI9341_DTCB						0xEA
#define ILI9341_POWER_SEQ					0xED
#define ILI9341_3GAMMA_EN					0xF2
#define ILI9341_INTERFACE					0xF6
#define ILI9341_PRC				   	  		0xF7
#define ILI9341_VERTICAL_SCROLL 			0x33

#define ILI9341_MEMCONTROL         			0x36
#define ILI9341_MADCTL_MY  					0x80
#define ILI9341_MADCTL_MX  					0x40
#define ILI9341_MADCTL_MV  					0x20
#define ILI9341_MADCTL_ML 					0x10
#define ILI9341_MADCTL_RGB 					0x00
#define ILI9341_MADCTL_BGR 					0x08
#define ILI9341_MADCTL_MH  					0x04

// colour macros

#define COLOR_BLACK          				0x0000
#define COLOR_NAVY            				0x000F
#define COLOR_DGREEN          				0x03E0
#define COLOR_DCYAN           				0x03EF
#define COLOR_MAROON      					0x7800
#define COLOR_PURPLE          				0x780F
#define COLOR_OLIVE           				0x7BE0
#define COLOR_LGRAY           				0xC618
#define COLOR_DGRAY           				0x7BEF
#define COLOR_BLUE            				0x001F
#define COLOR_BLUE2			  				0x051D
#define COLOR_GREEN           				0x07E0
#define COLOR_GREEN2		  				0xB723
#define COLOR_GREEN3		      			0x8000
#define COLOR_CYAN            				0x07FF
#define COLOR_RED             				0xF800
#define COLOR_MAGENTA         				0xF81F
#define COLOR_YELLOW          				0xFFE0
#define COLOR_WHITE           				0xFFFF
#define COLOR_ORANGE          				0xFD20
#define COLOR_GREENYELLOW     				0xAFE5
#define COLOR_BROWN 			    		0XBC40
#define COLOR_BRRED 			    		0XFC07




/*
 * structure for LCD initialisation
 *
 * member1:- spi(structure to configure the SPI)
 * member2:- GPIO_CS(chip select/slave select pin's port structure)
 * member3:- CS_pinNum(chip select/slave select pin number)
 * member4:- GPIO_DC(data/command pin's port structure)
 * member5:- DC_pinNum(data/command pin number)
 * member6:- GPIO_RST(reset pin's port structure)
 * member7:- RST_pinNum(reset pin number)
 */

typedef struct{

	SPI_RegDef_t *SPIx;
	uint8_t CS_PinNum;
	uint8_t DC_PinNum;
	uint8_t RST_PinNum;
	GPIO_RegDef_t *GPIO_CS;
	GPIO_RegDef_t *GPIO_DC;
	GPIO_RegDef_t *GPIO_RST;

}LCD_INIT_t;

/*
 * prototypes of function in the main file
 */

void LCD_INIT(LCD_INIT_t *LCD);
void LCD_CMD(LCD_INIT_t *LCD,uint8_t cmd);
void LCD_DATA(LCD_INIT_t *LCD,uint8_t data);
void LCD_SetCursor(LCD_INIT_t *LCD,uint16_t x1,uint16_t x2,uint16_t y1,uint16_t t2);
void LCD_DrawPixel(LCD_INIT_t *LCD,uint16_t x, uint16_t y, uint16_t color);
void delay(void);


#endif /* LCD_SPI_24_H_ */
