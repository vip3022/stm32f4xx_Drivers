void SPISlaveInit(void)
{
//set MISO as output
DDRB |= (1<<PB4);
//enable SPI and enable SPI interrupt
SPCR = (1<<SPE);
}

void SPI_Resc(void){

  char data_r;

  data_r = SPDR;
  Serial.println(data_r);

  while(!(SPSR & (1<<SPIF)));
  
}


int main(void)
{
//initialize slave SPI
SPISlaveInit();
Serial.begin(9600);

while (1)
{
  SPI_Resc();
}
}
