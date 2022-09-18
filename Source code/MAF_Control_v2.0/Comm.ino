/********************************************//**
   Manage Comms
 ***********************************************/
void manageComms()
{
  if (Serial.available() > 2) {
    ManageTerminal();
  }
}
/********************************************//**
   Manage Terminal
   >> CAL to enter Calibration Mode
   >> HEL to get Help
   >> ECO to activate terminal feedbacl
   >> TES to cativate TES mode
 ***********************************************/
void ManageTerminal() {
  char incommingByte[3];

  for (int i = 0; i < 3; i++) {
    incommingByte[i] = 0;
  }

  incommingByte[0] = Serial.read();

  //Manage to CAL mode
  if (incommingByte[0] == 'C') {
    incommingByte[1] = Serial.read();
    if (incommingByte[1] == 'A') {
      incommingByte[2] = Serial.read();
      if (incommingByte[2] == 'L') {
        _CalibrationMode = !_CalibrationMode;
        if (!_CalibrationMode) {
          restore_NVM();
          Serial.println(">> EXIT CAL MODE");
        }
        else{
           _cal_p_vez=true;
            menu_calibracion();
          }
      }
    }
  }
  //Mange HELP
  else if (incommingByte[0] == 'H') {
    incommingByte[1] = Serial.read();
    if (incommingByte[1] == 'E') {
      incommingByte[2] = Serial.read();
      if (incommingByte[2] == 'L') {
        _ECO = false;
        _TEST = false;
        Serial.print(">> HELP:");
        Help_terminal();
      }
    }
  }
  //Manage ECO
  else if (incommingByte[0] == 'E') {
    incommingByte[1] = Serial.read();
    if (incommingByte[1] == 'C') {
      incommingByte[2] = Serial.read();
      if (incommingByte[2] == 'O') {
        Serial.print(">> ECO:"); Serial.println(_ECO);
        _ECO = !_ECO;
      }
    }
  }

  //Manage TEST
  else if (incommingByte[0] == 'T') {
    incommingByte[1] = Serial.read();
    if (incommingByte[1] == 'E') {
      incommingByte[2] = Serial.read();
      if (incommingByte[2] == 'S') {
        _ECO = false;
        _TEST = !_TEST;
        Serial.print(">> TEST:"); Serial.println(_TEST);
      }
    }
  }

  else if (incommingByte[0] == 'W') {
    incommingByte[1] = Serial.read();
    if (incommingByte[1] == 'E') {
      incommingByte[2] = Serial.read();
      if (incommingByte[2] == 'L') {
        wellcome_terminal();
      }
    }
  }
}

/********************************************//**
   Menu Calibracion por  Terminal
 ***********************************************/
void menu_calibracion() {
  Serial.println("**** MODO CALIBRACION ****");
  Serial.println("Mueva el control de motor al MAX y al MIN durante varios segundos:");
  Serial.println("**************************");
  Serial.println();
}

/********************************************//**
   Help Terminal
 ***********************************************/
void Help_terminal() {
  //Store data in flash (program) memory instead of SRAM
  char PROGMEM largeText[] = "\n\
  \n\
  *****************************************************************************************************************\n\
  MENU DE AYUDA:\n\
  \n\
  Es es un SW de control para máquina de 5 pulgadas. \n\
  \n\
  Lista de comandos:\n\
  (1) CAL: \n\
  Entra en modo calibracion del RC. Una vez dentro mueva el control a la MAX y MIN posición durante varios segundos.\n\
  Los valores se guardaran en la memoria no volátil.\n\
  Para salir del modo introduzca de nuevo CAL o reinicie alimnetacion.\n\
  \n\
  (2) ECO: \n\
  Activa la salida por terminal de ciertos parámetros generales de control.\n\
  Para desacrivar, vuelva a introducir ECO.\n\
  \n\
  (3) TES: \n\
  Activa un modo especial de prueba. \n\
  Para desacrivar, vuelva a introducir TES.\n\
    \n\
  *****************************************************************************************************************\n\
  ";
  //Print it
  int idx = 0;
  while (largeText[idx] != '\0')
  {
    Serial.print(largeText[idx]);
    idx++;
  }
  Serial.println();
}
/********************************************//**
   Wellcome Terminal
 ***********************************************/
void wellcome_terminal() {

  Serial.println("/////////////////////////////////////////////////");
  Serial.println("////     FBA: Electronica Tren 5 Pulgadas    ////");
  Serial.println("/////////////////////////////////////////////////");
  Serial.print("SW Date: ");
  Serial.println( __DATE__ " " __TIME__ );
  Serial.println("Author: Miguel Ángel de Frutos - 2021");
  restore_NVM();
}
