
// pins for the LEDs:
const int corePins[3] = {3,5,6};
const int bodyPins[3] = {9,10,11};

void setup() {
  Serial.begin(9600);
  Serial.println("Papai");

  for (int i=0; i<3; i++) {
    pinMode(corePins[i], OUTPUT);
    pinMode(bodyPins[i], OUTPUT); 
    digitalWrite(corePins[i], LOW);
    digitalWrite(bodyPins[i], LOW); 
  } 
}



const int buff_len = 15;
char buff[buff_len] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pwms[6] = {255,255,255,0,0,63};

void loop() {

  while (Serial.available() > 0) {
    char c = Serial.read();
    for (int i=0; i<(buff_len-1); i++) {
      buff[i] = buff[i+1];
    }
    buff[14] = c;
    
    if (c == '\n') {
      if (buff[buff_len-2] == '0' && buff[buff_len-3] == '0') {
        Serial.println("raw mode");
        for (int i=0; i<6; i++) {
        }
      //red = constrain(red, 0, 255);
        update_pwms();
      }
      Serial.print("Buffer: ");
      Serial.println(buff);
    }
  }
}

void update_pwms() {
  analogWrite(corePins[0], pwms[0]);
  analogWrite(corePins[1], pwms[1]);
  analogWrite(corePins[2], pwms[2]);
  
  analogWrite(bodyPins[0], pwms[3]);
  analogWrite(bodyPins[1], pwms[4]);
  analogWrite(bodyPins[2], pwms[5]);
}






