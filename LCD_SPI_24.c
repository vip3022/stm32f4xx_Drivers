/*
 * LCD_SPI_24.c
 *
 *  Created on: 15-Jan-2021
 *      Author: vipulgupta
 */

#include "LCD_SPI_24.h"


/*
 * function name:-	LCD_INIT
 * description:- 	to send a command to the the driver
 * parameter1:- 	LCD(LCD configuration structure)
 */

void LCD_INIT(LCD_INIT_t *LCD){

	//initialise the CS,DC and RESET pins as
	GPIO_INIT(LCD->GPIO_CS,LCD->CS_PinNum,OUTPUT,PushPull,veryHighSpeed,noPushPull);
	GPIO_INIT(LCD->GPIO_DC,LCD->DC_PinNum,OUTPUT,PushPull,veryHighSpeed,noPushPull);
	GPIO_INIT(LCD->GPIO_RST,LCD->RST_PinNum,OUTPUT,PushPull,veryHighSpeed,noPushPull);

	//pull CS and RST(turn on display) pin HIGH
	GPIO_OUTPUT(LCD->GPIO_CS,LCD->CS_PinNum,HIGH);
	GPIO_OUTPUT(LCD->GPIO_RST,LCD->RST_PinNum,HIGH);

	//---------- software reset ------------//
	LCD_CMD(LCD,ILI9341_RESET);
	delay();
	LCD_CMD(LCD,ILI9341_DISPLAY_OFF);

	//---------- POWER control -------------//
	LCD_CMD(LCD,ILI9341_POWER1);
	LCD_DATA(LCD,0x26); 				//GVDD = 4.75V
	LCD_CMD(LCD,ILI9341_POWER2);
	LCD_DATA(LCD,0x11);					//AVDD=VCIx2, VGH=VCIx7, VGL=-VCIx3

	//---------- VCOM control ----------//
	LCD_CMD(LCD,ILI9341_VCOM1);
	LCD_DATA(LCD,0x35); 				// Set the VCOMH voltage (0x35 = 4.025v)
	LCD_DATA(LCD,0x3e); 				// Set the VCOML voltage (0x3E = -0.950v)
	LCD_CMD(LCD,ILI9341_VCOM2); 		// vcom control
	LCD_DATA(LCD,0xbe);

	//---------- memory control ---------//

	LCD_CMD(LCD,ILI9341_MAC);
	LCD_DATA(LCD,0x48);

	LCD_CMD(LCD,ILI9341_PIXEL_FORMAT);
	LCD_DATA(LCD,0x55);

	//---------- FRC(frame rate control -------//

	LCD_CMD(LCD,ILI9341_FRC);
	LCD_DATA(LCD,0x00);
	LCD_DATA(LCD,0x1F);

	//---------- DDRAM --------//

	LCD_SetCursor(LCD,0,240,0,320);
	LCD_CMD(LCD,ILI9341_TEARING_OFF);
	//LCD_CMD(LCD,ILI9341_DISPLAY_INVERSION);
	LCD_CMD(LCD,ILI9341_Entry_Mode_Set);
	LCD_DATA(LCD,0x07);

	//---------- Display --------//

	LCD_CMD(LCD,ILI9341_DFC);
	LCD_DATA(LCD,0x0a);
	LCD_DATA(LCD,0x82);
	LCD_DATA(LCD,0x27);
	LCD_DATA(LCD,0x00);

	//------ turning on the display ------//

	LCD_CMD(LCD,ILI9341_SLEEP_OUT);
	LCD_CMD(LCD,ILI9341_DISPLAY_ON);
	LCD_CMD(LCD,ILI9341_GRAM);

}

/*
 * function name:-  LCD_CMD
 * description:- 	to send a command to the the driver
 * parameter1:- 	LCD(LCD configuration structure)
 * parameter2:-		cmd(8 bit command)
 */

void LCD_CMD(LCD_INIT_t *LCD,uint8_t cmd){

	//DC pin low(for command)
	GPIO_OUTPUT(LCD->GPIO_DC,LCD->DC_PinNum,LOW);

	//CS pin low(to start the communication
	GPIO_OUTPUT(LCD->GPIO_CS,LCD->CS_PinNum,LOW);

	//transmit the command
	SPI_MasterWrite(LCD->SPIx,cmd);

	//CS pin high
	GPIO_OUTPUT(LCD->GPIO_CS,LCD->CS_PinNum,HIGH);

}

/*
 * function name:-  LCD_DATA
 * description:- 	to send a data to the the driver
 * parameter1:- 	LCD(LCD configuration structure)
 * parameter2:-		data(8 bit data)
 */

void LCD_DATA(LCD_INIT_t *LCD,uint8_t data){

	//DC pin low(for command)
	GPIO_OUTPUT(LCD->GPIO_DC,LCD->DC_PinNum,HIGH);

	//CS pin low(to start the communication
	GPIO_OUTPUT(LCD->GPIO_CS,LCD->CS_PinNum,LOW);

	//transmit the command
	SPI_MasterWrite(LCD->SPIx,data);

	//CS pin high
	GPIO_OUTPUT(LCD->GPIO_CS,LCD->CS_PinNum,HIGH);

}

/*
 * function name:-  LCD_SetCursor
 * description:- 	to set the cursor
 * parameter1:- 	LCD(LCD configuration structure)
 * parameter2:-		x1(start column point)
 * parameter3:- 	x2(end column point)
 * parameter4:- 	y1(start row point)
 * parameter5:- 	y2(end row point)
 */

void LCD_SetCursor(LCD_INIT_t *LCD,uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2){

	//send the command code
	LCD_CMD(LCD,ILI9341_COLUMN_ADDR);

	//send first parameter x1 and x2
	LCD_DATA(LCD,x1>>8);
	LCD_DATA(LCD,x1 & 0xff);

	LCD_DATA(LCD,x2>>8);
	LCD_DATA(LCD,x2 & 0xff);

	//send the command code
	LCD_CMD(LCD,ILI9341_PAGE_ADDR);

	//send second parameter y1 and y2
	LCD_DATA(LCD,y1>>8);
	LCD_DATA(LCD,y1 & 0xff);

	LCD_DATA(LCD,y2>>8);
	LCD_DATA(LCD,y2 & 0xff);

}

/*
 * function name:-  LCD_SetCursor
 * description:- 	to set the cursor
 * parameter1:- 	LCD(LCD configuration structure)
 * parameter2:-		x1(start column point)
 * parameter3:- 	x2(end column point)
 * parameter4:- 	y1(start row point)
 * parameter5:- 	y2(end row point)
 */

void LCD_DrawPixel(LCD_INIT_t *LCD,uint16_t x, uint16_t y, uint16_t color){

	LCD_SetCursor(LCD,x, y, x, y);
	LCD_DATA(LCD,color>>8);
	LCD_DATA(LCD,color&0xFF);

}


/*
 * small delay function
 */

void delay(void){
	for(int i=0;i<10000;i++);
}



