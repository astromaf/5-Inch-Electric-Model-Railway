/********************************************//**
   restore_ALL
 ***********************************************/
/* EEPROM addresses */
#define  EEPROM_SIZE       EEPROM.length()
#define  EEPROM_BASE        200
#define  Max_Address        EEPROM_BASE+0
#define  Min_Address        EEPROM_BASE+4
#define  Med_Address        EEPROM_BASE+8

/********************************************//**
   restore_ALL
 ***********************************************/
void restore_NVM() {

  int temp_max, temp_min, temp_med;

  EEPROM.get(Max_Address, temp_max);
  EEPROM.get(Min_Address, temp_min);
  EEPROM.get(Med_Address, temp_med);

  _MaxRC = constrain(temp_max, 1500, 2500);
  _MinRC = constrain(temp_min, 500, 1500);
  _MedRC = constrain(temp_med, 1000, 2000);

  delay(500);
  Serial.println("Cal values:");
  Serial.print("  Max="); Serial.println(_MaxRC);
  Serial.print("  Min="); Serial.println(_MinRC);
  Serial.print("  Med="); Serial.println(_MedRC);
  Serial.println();
  Serial.println();
  delay(500);
}

/********************************************//**
  update_MAX
 ***********************************************/
boolean update_MAX(int p){
  int temp;
  temp=constrain(p,1500,2500);
  if(p==temp){
    EEPROM.put(Max_Address,p);
    return(1);
   }
   return(0);
 }
 /********************************************//**
  update_MIN
 ***********************************************/
boolean update_MIN(int p){
  int temp;
  temp=constrain(p,500,1500);
  if(p==temp){
    EEPROM.put(Min_Address,p);
    return(1);
   }
   return(0);
 }
 /********************************************//**
  update_MED
 ***********************************************/
boolean update_MED(int p){
  int temp;
  temp=constrain(p,1000,2500);
  if(p==temp){
    EEPROM.put(Med_Address,p);
    return(1);
   }
   return(0);
 }
 
 
 
