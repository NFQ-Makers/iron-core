
// pins for the LEDs:
const int corePins[3] = {3,6,5};
const int bodyPins[3] = {11,10,9};

const int fan = A2;

void setup() {
  Serial.begin(9600);
  //Serial.println("Papai");

  for (int i=0; i<3; i++) {
    pinMode(corePins[i], OUTPUT);
    pinMode(bodyPins[i], OUTPUT); 
    digitalWrite(corePins[i], LOW);
    digitalWrite(bodyPins[i], LOW); 
  } 
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);
}

int fanDelay = 0;

void spinIfNeeded() {
  if(fanDelay / 900) {
    digitalWrite(fan, HIGH);
  } else {
    digitalWrite(fan, LOW);
  }
  
  fanDelay++;
  if(fanDelay > 1030) {
    fanDelay = 0;
  }  
}

int getInt(char a, char b) {
  char firstBuffer[2];
  char secondBuffer[2];
  firstBuffer[1] = 0;
  secondBuffer[1] = 0;
  
  firstBuffer[0] = a;
  secondBuffer[0] = b;
  
  return atoi((char*) &firstBuffer) * 10 + atoi((char*) &secondBuffer);
}


const int buff_len = 15;
char buff[buff_len] = {0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0};
int pwms[6] = {255,255,255,255,255,255};

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    for (int i=0; i<(buff_len-1); i++) {
      buff[i] = buff[i+1];
    }
    buff[14] = c;
    
    if (c == '\n') {
      if (buff[buff_len-2] == '0' && buff[buff_len-3] == '0') {
        for (int i=0; i<6; i++) {
          int colour = getInt(buff[i * 2],
                              buff[i * 2 + 1]);
          pwms[i] = colour;
        }
        update_pwms();
      }
      //Serial.print("Buffer: ");
      //Serial.println(buff);
    }
  }
  spinIfNeeded();
  delay(1);
}


void update_pwms() {
  analogWrite(corePins[0], pwms[0]);
  analogWrite(corePins[1], pwms[1]);
  analogWrite(corePins[2], pwms[2]);
  
  analogWrite(bodyPins[0], pwms[3]);
  analogWrite(bodyPins[1], pwms[4]);
  analogWrite(bodyPins[2], pwms[5]);
}






