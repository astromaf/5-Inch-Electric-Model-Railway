////////////Init-Funciones////////////
void init_Funciones() {
  pinMode(rele_Bocina, OUTPUT);
  pinMode(rele_Luz, OUTPUT);
  digitalWrite(rele_Bocina, LOW);
  digitalWrite(rele_Luz, LOW);

  //Regulador
  pinMode (pin_Avanza, OUTPUT);
  pinMode(pin_Retrocede, OUTPUT);
  digitalWrite(pin_Avanza, HIGH);
  digitalWrite(pin_Retrocede, HIGH);

}
////////////Lee-CONTROLES////////////
void lee_Controles(int ch1, int ch2, int ch3) {
  static float raw_pot=0;
  
  //CANAL 1 - Rueda
  int med_value = _MedRC;
  ch1 = constrain(ch1, _MinRC, _MaxRC);
  if (ch1> med_value + 20) {
    _dir = 0;
    raw_pot = map(ch1, med_value + 20, _MaxRC, 0, 255);
  }
  else if (ch1 < med_value - 20) {
    _dir = 1;
    raw_pot = map(ch1, _MinRC, med_value - 20, 255, 0);
  }
  else { //Zona muerta
    raw_pot = 0;
    _dir = 0;
    _potencia=0;
  }

  _potencia += (1.0 / (freq_ciclo * 1.5)) * (raw_pot - _potencia); //LPF n muestras sample=1/(freq_ciclo[hz]*timepo[s])
  //Serial Plotter
  //Serial.print(_potencia);
  //Serial.print(" ");
  //Serial.println(raw_pot);
  
  //CANAL 2- Gatillo
  _bocina = 0;
  static boolean p_vez_pes = true;
  if (ch2 > 1750) { //Gatillo muy atrás
    if (p_vez_pes) {
      _bloqueo = !_bloqueo;
      p_vez_pes = false;
    }
  }
  else if (ch2 < 1100) { //Gatillo adelante
    _bocina = 1;
  }
  else {
    p_vez_pes = true;
  }

  //CANAL 3- Interruptor
  static boolean p_vez_luz = true;
  if ((ch3 > 1600) && (ch3 < 2500)) {
    if (p_vez_luz) {
      _luz = !_luz;
      p_vez_luz = false;
    }
  }
  else {
    p_vez_luz = true;
  }
}

////////////Ejecuta-ACCIONES////////////
void ejecuta_Acciones() {
  if (_SafeMode) {
    accion_emergencia(); //Luz parpadea advirtiendo
  }
  accion_Motor(_dir, (byte)_potencia, _bloqueo);
  accion_Bocina(_bocina);
  accion_Luz(_luz);
}

////////////Accion-MOTOR////////////
void accion_Motor(boolean dir, byte pot, boolean bloqueo) {
  static boolean dir_old = 0;
  static byte pot_old = 0;

  if (bloqueo == false) { //Si está el bloqueo, no actualices
    if (dir == 0) { //Adelante
      sentido_Marcha(true);
      if (_TEST) Serial.print("Avanza:");
    }
    else { //Atrás
      sentido_Marcha(false);
      if (_TEST) Serial.print("Retrocede:");
    }
    digitalPotWrite(pot); //Comandar Dig_Pot
    if (_TEST) Serial.println(pot);
    dir_old = dir;
    pot_old = pot;
  }
  else {
    if (dir_old == 0) { //Adelante
      if (_TEST) Serial.print("Avanza:");
    }
    else { //Atrás
      if (_TEST) Serial.print("Retrocede:");
    }
    if (_TEST) Serial.println(pot_old);
  }

}
////////////Accion-BOCINA////////////
void accion_Bocina(boolean state) {
  static boolean prev = true;
  if (prev != state) {
    if (state) {
      digitalWrite(rele_Bocina, HIGH);
      if (_TEST) Serial.println("Bocina: ON");
    }
    else {
      digitalWrite(rele_Bocina, LOW);
      if (_TEST) Serial.println("Bocina: OFF");
    }
    prev = state;
  }
}

////////////Accion-LUZ////////////
void accion_Luz(boolean state) {
  static boolean prev = true;
  if (prev != state) {
    if (state) {
      digitalWrite(rele_Luz, HIGH);
      if (_TEST) Serial.println("LUZ: ON");
    }
    else {
      digitalWrite(rele_Luz, LOW);
      if (_TEST) Serial.println("LUZ: OFF");
    }
    prev = state;
  }
}

////////////Sentido-Marcha////////////
void sentido_Marcha(boolean state) {
  if (state) { //Avanza
    digitalWrite(pin_Avanza, LOW);
    digitalWrite(pin_Retrocede, HIGH);
  }
  else { //Retrocede
    digitalWrite(pin_Avanza, HIGH);
    digitalWrite(pin_Retrocede, LOW);
  }
}
////////////Revisión Seguridad ////////////
/*Revisamos que el mando esté encendido y funcionando*/
void  revision_seguridad(int ch3) {

  _SafeMode = false;

  //1º CHECK:
  if ((ch3 > 20000) || (ch3 < 500)) { //Si CH3 muy alto/bajo es síntoma de que está fuera de control
    _SafeMode = true;
  }

  //2º CHECK: CH3 congelado significa que se apagó la emisora de repente
  static int ch3_old = 0;
  static int cnt = 0;
  int residuo = ch3_old - ch3;
  ch3_old = ch3;
  if (residuo == 0) {
    cnt++;
  }
  else {
    cnt = 0;
  }

  if (cnt > freq_ciclo * 3) { //3 segundos sin variar nada
    _SafeMode = true;
  }
}

////////////Acción emergencia////////////
void accion_emergencia() {
  static boolean state = true;
  static int cnt = 0;
  _dir = 0;
  _potencia = 0;
  _bloqueo = 0;
  _bocina = 0;

  cnt++;

  if (cnt > (freq_ciclo * 0.5)) {
    cnt = 0;
    state = !state;
  }

  if (state) {
    digitalWrite(rele_Luz, HIGH);
  }
  else {
    digitalWrite(rele_Luz, LOW);
  }
}

////////////Modo CALIBRACION////////////
void modo_calibracion(int entrada) {
  if (_cal_p_vez) {
    update_MAX(1500);
    update_MIN(1500);
    update_MED(0);
    _cal_p_vez = false;
  }
  encontrar_limites(entrada);
}

////////////Encontrar MAX-MED-MIN////////////
void encontrar_limites(int entrada) {
  static int max_val = 1500;
  static int min_val = 1500;
  static int med_val = 1500;


  if (abs(entrada - 1500) < 30) {
    med_val += (1.0 / (freq_ciclo * 0.25)) * (entrada - med_val);
  }
  if (entrada > max_val) {
    max_val = entrada;
  }
  if (entrada < min_val) {
    min_val = entrada;
  }

  static int cnt = 0;
  cnt++;
  if (cnt > (freq_ciclo * 1)) {
    cnt = 0;

    Serial.print("Max:");
    Serial.print(max_val);
    Serial.print("\t");

    Serial.print("Min:");
    Serial.print(min_val);
    Serial.print("\t");

    Serial.print("Med:");
    Serial.print(med_val);
    Serial.print("\t");

    Serial.print("Raw:");
    Serial.print(entrada);
    Serial.println("\t");

    update_MAX(max_val);
    update_MIN(min_val);
    update_MED(med_val);
  }
}


