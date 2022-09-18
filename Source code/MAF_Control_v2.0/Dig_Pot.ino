////////////Inicializa Digi Pot////////////
void init_DigiPot() {
  pinMode (CS, OUTPUT);
  SPI.begin();
  digitalPotWrite(0x00);
}
////////////Envía Digi Pot////////////
int digitalPotWrite(int value) // Envia dato al Pot (100k/8bit/0-255)
{
  digitalWrite(CS, LOW);
  SPI.transfer(spi_address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

////Unit Testing//////
void testDigiPOT(){
    while(true){
      digitalPotWrite(255);
      RXLED1;
      delay(2000);
      digitalPotWrite(0);
      RXLED0;
      delay(2000);
    }
  }


