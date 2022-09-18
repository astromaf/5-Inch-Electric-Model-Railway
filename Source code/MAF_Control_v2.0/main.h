#include <SPI.h>
#include <EEPROM.h>
#include "interrupts.h"

//////HARDWARE//////
//RC-Channel
const byte channel_1_Pin = 1; //Volante->Potencia
const byte channel_2_Pin = 2; //Gatillo->Bocina
const byte channel_3_Pin = 3; //Interruptor->Luz

//Equipos
const byte rele_Bocina = 4;
const byte rele_Luz =5;
const byte pin_Avanza = 6;
const byte pin_Retrocede = 7;

//SPI
/*
  MCP41100
  CS >>> D10
  SCLK >> D15
  MOSI/DI >> D16
*/
const byte CS = 10;
byte spi_address = 0x11;



//////GLOBAL VARIABES//////
float _potencia = 0; //0-255
boolean _dir = 0;
boolean _bocina = 0;
boolean _luz = 0;
boolean _bloqueo = 0;
boolean _SafeMode = 0;
boolean _CalibrationMode= 0;
boolean _ECO=0;
boolean _cal_p_vez=true;
int _MaxRC=2000;
int _MinRC=1000;
int _MedRC=12;



