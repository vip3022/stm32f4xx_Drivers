/*
 * LCD_16x2.c
 *
 *  Created on: 23 Jan 2021
 *      Author: User
 */

#include <LCD_16x2.h>

//creating an static LCD structure
static LCD lcd;

//prototyping driver specific functions
static void EN_Toggle(GPIO_RegDef_t* configPort,uint8_t en);
static void small_delay(void);
static void delay(void);
static void bigger_delay(void);

void LCD_INIT(LCD *lcdx){

	memcpy(&lcd,lcdx,sizeof(*lcdx));

	/****** initializing each pin as mode:- output and config:- pullUp/pullDown  ******/

	GPIO_INIT(lcd.configPort,lcd.en,OUTPUT,PushPull,highSpeed,noPushPull);		/* initializing en */
	GPIO_INIT(lcd.configPort,lcd.RS,OUTPUT,PushPull,highSpeed,noPushPull);		/* initializing RS */
	GPIO_INIT(lcd.configPort,lcd.RW,OUTPUT,PushPull,highSpeed,noPushPull);		/* initializing RW */
	for(int i=0;i<8;i++){
		GPIO_INIT(lcd.dataPort,lcd.d[i],OUTPUT,PushPull,highSpeed,noPushPull);	/* initializing d[0]-d[7] */
	}

	/**** clearing and moving the cursor to 0x0 *******/

	LCD_Clear();

	/******** display on, cursor on and cursor blink off command *******/

	lcd.dataPort->ODR &= ~((1<<lcd.d[7])|(1<<lcd.d[6])|(1<<lcd.d[5])|(1<<lcd.d[4])|(1<<lcd.d[0]));
	lcd.dataPort->ODR |= (1<<lcd.d[1])|(1<<lcd.d[2])|(1<<lcd.d[3]);

	EN_Toggle(lcd.configPort,lcd.en);

	/******* cursor moves right and display does not shift command *******/

	lcd.dataPort->ODR &= ~((1<<lcd.d[7])|(1<<lcd.d[6])|(1<<lcd.d[5])|(1<<lcd.d[4])|(1<<lcd.d[3])|(1<<lcd.d[0]));
	lcd.dataPort->ODR |= (1<<lcd.d[1])|(1<<lcd.d[2]);

	EN_Toggle(lcd.configPort,lcd.en);


	/******** turning on 8bit mode, 2 line mode, 5x8 dot format******/

	lcd.dataPort->ODR &= ~((1<<lcd.d[7])|(1<<lcd.d[6])|(1<<lcd.d[2]));
	lcd.dataPort->ODR |= (1<<lcd.d[3])|(1<<lcd.d[4])|(1<<lcd.d[5]);

	EN_Toggle(lcd.configPort,lcd.en);

}

void LCD_Clear(void){

	/******* enabling the configuration mode RS=0,RW=0 *******/
	lcd.configPort->ODR &= ~((1<<lcd.RS)|(1<<lcd.RW));

	/****** clearing command******/

	lcd.dataPort->ODR &= ~((1<<lcd.d[7])|(1<<lcd.d[6])|(1<<lcd.d[5])|(1<<lcd.d[4])|(1<<lcd.d[3])|(1<<lcd.d[2])|(1<<lcd.d[1]));
	lcd.dataPort->ODR |= (1<<lcd.d[0]);

	EN_Toggle(lcd.configPort,lcd.en);
	bigger_delay();

	/****** Return Home command ********/

	lcd.dataPort->ODR &= ~((1<<lcd.d[7])|(1<<lcd.d[6])|(1<<lcd.d[5])|(1<<lcd.d[4])|(1<<lcd.d[3])|(1<<lcd.d[2]));
	lcd.dataPort->ODR |= (1<<lcd.d[1]);

	EN_Toggle(lcd.configPort,lcd.en);
	bigger_delay();

}

void LCD_Write(char msg[30]){

	/******* enabling the write data mode RS=1,RW=0 *******/
	lcd.configPort->ODR |= (1<<lcd.RS);
	lcd.configPort->ODR &= ~(1<<lcd.RW);

	/***** writing in the data pins ******/
	int i =0;
	while(msg[i] != '\0'){
		LCD_PrintChar(msg[i]);
	    i++;
	 }
}

/*
 * function name:- 	LCD_PrintChar
 * description:- 	printing only 1 character on the display
 * parameter1:- 	*lcd(structure of lcd pins and ports)
 * parameter2:- 	alpha(charater to print)
 */

void LCD_PrintChar(uint8_t alpha){

	for(int i=0;i<8;i++){
		GPIO_OUTPUT(lcd.dataPort,lcd.d[i],(alpha>>i) & 0x01);
	}
	EN_Toggle(lcd.configPort,lcd.en);


}

/*
 * function name:- 	EN_Toggle
 * description:- 	to toggle the en pin
 * parameter1:- 	configPort(port of configuration pins)
 * parameter2:- 	en(pin number of en pin)
 */

static void EN_Toggle(GPIO_RegDef_t* configPort,uint8_t en){

	GPIO_OUTPUT(configPort,en,LOW);
	small_delay();
	GPIO_OUTPUT(configPort,en,HIGH);
	small_delay();
	GPIO_OUTPUT(configPort,en,LOW);
	delay();

}

/***** some delay functions (JuGad) ******/

static void small_delay(void){
	for(int i=0; i<100; i++);
}

static void delay(void){
	for(int i=0; i<1000; i++);
}

static void bigger_delay(void){
	for(int i=0; i<10000; i++);
}


