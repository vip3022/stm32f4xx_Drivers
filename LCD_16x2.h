/*
 * LCD_16x2.h
 *
 *  Created on: 23 Jan 2021
 *      Author: User
 */

#ifndef LCD_16X2_H_
#define LCD_16X2_H_

#include <stm32f4x.h>
#include <stdint.h>
#include <string.h>
#include <stm32f4xxGPIO.h>

/***** Structure to give all the pins ********/

/*
 * member 1:- configPort(port in which RS,RW and en are connected)
 * member 2:- en (pin number of en)
 * member 3:- RS (pin number of RS)
 * member 4:- RW (pin number of RW)
 * member 5:- dataPort(port in which d0,d1,d2,d3,d4,d5,d6 and d7 are connected)
 * member 6-13:- d0-d7 (pin numbers of d0-d7)
 */

typedef struct {
	GPIO_RegDef_t* configPort;
	uint8_t en;
	uint8_t RS;
	uint8_t RW;
	GPIO_RegDef_t* dataPort;
	uint8_t d[8];
}LCD;

/****** Prototypes of each function in the .c file *******/

void LCD_INIT(LCD *lcdx);
void LCD_Clear(void);
void LCD_Write(char msg[]);
void LCD_PrintChar(uint8_t alpha);
void LCD_ShiftCursor(void);


#endif /* LCD_16X2_H_ */
