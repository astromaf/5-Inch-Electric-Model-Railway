
//ISR 1
void INTch1() {
  if (digitalRead(channel_1_Pin) == HIGH) ch1_Init = micros();
  if (digitalRead(channel_1_Pin) == LOW)ch1_Pulse = micros() - ch1_Init;
}
//ISR 2
void INTch2() {
  if (digitalRead(channel_2_Pin) == HIGH) ch2_Init = micros();
  if (digitalRead(channel_2_Pin) == LOW)ch2_Pulse = micros() - ch2_Init;
}
//ISR 3
void INTch3() {
  if (digitalRead(channel_3_Pin) == HIGH) ch3_Init = micros();
  if (digitalRead(channel_3_Pin) == LOW)ch3_Pulse = micros() - ch3_Init;
}
//Init Interrupts
void init_Interrupts(){
  pinMode(channel_1_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(channel_1_Pin), INTch1, CHANGE);
  pinMode(channel_2_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(channel_2_Pin), INTch2, CHANGE);
  pinMode(channel_3_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(channel_3_Pin), INTch3, CHANGE);
}
