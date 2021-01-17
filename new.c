
#include <LCD_SPI_24.h>

/*
 * SPI1 NSS-> PA4
 * 		SCK-> PA5
 * 		MISO->PA6
 * 		MOSI->PA7
 */

int main(void){

	GPIOA_PCEN();
	GPIOB_PCEN();
	SPI1_PCEN();

	GPIO_INIT(GPIOA,4,AF_Mode,PushPull,highSpeed,noPushPull);
	GPIO_AFMODE(GPIOA,4,AF5);
	GPIO_INIT(GPIOA,5,AF_Mode,PushPull,highSpeed,noPushPull);
	GPIO_AFMODE(GPIOA,5,AF5);
	GPIO_INIT(GPIOA,6,AF_Mode,PushPull,highSpeed,noPushPull);
	GPIO_AFMODE(GPIOA,6,AF5);
	GPIO_INIT(GPIOA,7,AF_Mode,PushPull,highSpeed,noPushPull);
	GPIO_AFMODE(GPIOA,7,AF5);

	SPI_config_t *spix;

	spix->CPHA = LOW;
	spix->CPOL = LOW;
	spix->dff16_8 = disable;
	spix->SSM = enable;
	spix->SPIx = SPI1;
	spix->SSI = HIGH;
	spix->masterSlave = master;
	spix->preScaler = preScaler_2;
	spix->frameFormat = MSB;

	SPI_INIT(spix);
	SPI_en(SPI1);

	LCD_INIT_t *LCD;

	LCD->CS_PinNum  =  2;
	LCD->DC_PinNum  =  1;
	LCD->RST_PinNum =  0;
	LCD->SPIx = SPI1;
	LCD->GPIO_CS = GPIOB;
	LCD->GPIO_DC = GPIOB;
	LCD->GPIO_RST = GPIOB;

	LCD_INIT(LCD);

	uint16_t x1 =1;
	uint16_t x2 =1;

	while(1){

		LCD_DrawPixel(LCD,x1,x2,COLOR_GREEN);
		x1++;
		x2++;
		delay();

	}


}
