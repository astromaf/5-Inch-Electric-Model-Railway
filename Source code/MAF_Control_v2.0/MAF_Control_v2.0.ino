#include "main.h"
boolean _TEST = 0;
/// Frecuencia Ejecución Bucle Loop
const float freq_ciclo = 20;  //En Hz
const float t_espera =  (1.0 / freq_ciclo) * 1000;
long _loop_timer;

void setup() {
  init_Interrupts();
  init_DigiPot();
  init_Funciones();
  Serial.begin(115200);
  delay(1000);
  wellcome_terminal();
  //testDigiPOT();
}

void loop() {
  while (millis() - _loop_timer < t_espera);
  _loop_timer = millis();
  manageComms();
  
  if (!_CalibrationMode) {
    lee_Controles(ch1_Pulse, ch2_Pulse, ch3_Pulse);
    revision_seguridad(ch3_Pulse);
    ejecuta_Acciones();
  }
  else {
    modo_calibracion(ch1_Pulse);
  }
  print_Samples();
}

////////////Pint-SAMPLES////////////
void print_Samples() {
   if (false){ 
    Serial.print("CH1:");
    Serial.print(ch1_Pulse);
    Serial.print("\t");
    Serial.print("Med:");
    Serial.print(_MedRC);
    Serial.print("\t");
    Serial.print("Pot:");
    Serial.print(_potencia);
    Serial.println("\t");
   }


  
  if (_ECO){ 
    Serial.print("CH1:");
    Serial.print(ch1_Pulse);
    Serial.print("\t");
    Serial.print("CH2:");
    Serial.print(ch2_Pulse);
    Serial.print("\t");
    Serial.print("CH3:");
    Serial.print(ch3_Pulse + 100);
    Serial.print("\t");
    Serial.print("Dir:");
    Serial.print(_dir);
    Serial.print("\t");
    Serial.print("Pot:");
    Serial.print(_potencia);
    Serial.print("\t");
    Serial.print("Pes:");
    Serial.print(_bloqueo);
    Serial.print("\t");
    Serial.print("Boz:");
    Serial.print(_bocina);
    Serial.print("\t");
    Serial.print("Luz:");
    Serial.print(_luz);
    Serial.print("\t");
    Serial.print("SAFE:");
    Serial.print(_SafeMode);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print("MAX_NVM:");
    Serial.print(_MaxRC);
    Serial.print("\t");
    Serial.print("MIN_NVM:");
    Serial.print(_MinRC);
    Serial.print("\t");
    Serial.print("MED_NVM:");
    Serial.print(_MedRC);
    Serial.println("\t");
  }
}
