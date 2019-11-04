int pulses;
int pulsesChanged;
int encA = 2;   // blue wire
int encB = 4;
int dirPinA = 12;
int pwmPinA = 3;
float ang = 0.0;
float rev = 0.0;
int dira = 0;
int pwma = 0;

void setup() {
  Serial.begin(9600);
  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);

  attachInterrupt(0, A_CHANGE, CHANGE);
  
  pinMode(dirPinA, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 0);
}

void loop() {
  if (pulsesChanged != 0) {
    // ***** TO DO (2 lines) ***** //
    // calculate angle from pulses
    ang = pulses;
    // calculate revolution from angles
    rev = ang;
    // ***** END ***** //
    Serial.print(pulses);
    Serial.print("\t");
    Serial.print(ang);
    Serial.print("\t");
    Serial.print(rev);
    Serial.print("\n");
    pulsesChanged = 0;
  }
  
  char a = Serial.read();
  if (a == '1') {
    m_cw();
  }
  else if (a == '2') {
    m_ccw();
  }
  else if (a == '3') {
    m_stop();
  }
}

void A_CHANGE() {                                     
  if ( digitalRead(encB) == 0 ) {
    if ( digitalRead(encA) == 0 ) {
      // A fall, B is low
      pulses--; // Moving CCW
    } else {
      // A rise, B is low
      pulses++; // Moving CW
    }
  } else {
    if ( digitalRead(encA) == 0 ) {
      // A fall, B is high
      pulses++; // Moving CW
    } else {
      // A rise, B is high
      pulses--; // Moving CCW
    }
  }
  pulsesChanged = 1;
}

void m_cw() {
  digitalWrite(dirPinA, 1);
  digitalWrite(pwmPinA, 255);  
}

void m_ccw() {
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 255);    
}

void m_stop() {
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 0);  
}
