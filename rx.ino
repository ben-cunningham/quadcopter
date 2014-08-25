volatile long time;
volatile long prevTime[4];
volatile long rxInput[4];
volatile int rxState[4] = { 0, 0, 0 ,0 };
PROGMEM const byte rxPins[4]={8,9,10,11};


void initRX() {
  for(int i = 8; i < 12; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
  PCICR |= (1 << PCIE0);   //Pin Change interrupts moniter inputs D8-D13
  PCMSK0 |= (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT0) | (1 << PCINT1);
  sei(); //start interrupts
}

long getYaw() {
  return rxInput[0];
}

long getRoll() {  
  return rxInput[1];
}

long getPitch() {
  return rxInput[2];
}

long getThrottle() {
  return constrain(rxInput[3], 1000, 1999);
}

ISR(PCINT0_vect) {
  for(byte i = 0; i < 4; i++) {
    byte rxtemp=digitalRead(pgm_read_byte(&rxPins[i]));
    if(rxState[i] == 0 & rxtemp == 1) {
      prevTime[i] = micros();
      rxState[i] = 1;
    }
    else if(rxState[i] == 1 & rxtemp == 0) {
      rxInput[i] = micros() - prevTime[i];
      rxState[i] = 0;
    }
  }
}
