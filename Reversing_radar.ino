byte bcd_code[10][4] = {
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1}
};
int toneTable[7][5]={
  { 66, 131, 262, 523, 1046},  // C Do
  { 74, 147, 294, 587, 1175},  // D Re
  { 83, 165, 330, 659, 1318},  // E Mi
  { 88, 175, 349, 698, 1397},  // F Fa
  { 98, 196, 392, 784, 1568},  // G So
  {110, 220, 440, 880, 1760},  // A La
  {124, 247, 494, 988, 1976}   // B Si
};
int starBeat[]={
    1,1,1,1,1,1,2, 1,1,1,1,1,1,2,
    1,1,1,1,1,1,2, 1,1,1,1,1,1,2,
    1,1,1,1,1,1,2, 1,1,1,1,1,1,2
};
char toneName[]="CDEFGAB";
char starTone[]="CCGGAAGFFEEDDCGGFFEEDGGFFEEDCCGGAAGFFEEDDC";
int trigpin = 7;
int echopin = 8;
int buzzerpin = 11, length, toneNo;
double duration, cm, tone_duration;

void disp(byte d) {
  for(byte i=0; i<4; i++) {
    digitalWrite(5-i, bcd_code[d][i]);
  }
}

int getTone(char symbol) {
  int toneNo = 0;
  for ( int i=0; i<7; i++ ) {
    if ( toneName[i]==symbol ) {
      toneNo = i;
      break;
      }
    }
  return toneNo;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzerpin, OUTPUT);
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  pinMode(echopin, INPUT);
  
  duration = pulseIn(echopin, HIGH);
  cm = duration / 2 * 0.034;
  
  Serial.print("Distance : ");
  Serial.print(cm);
  Serial.println("cm");

  cm = (int)(cm + 0.5);

  disp(cm);

  if(cm > 0 && cm < 10){
  length = sizeof(starTone)-1;
  for(int i = 0; i < length; i++){
    digitalWrite(trigpin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    pinMode(echopin, INPUT);
  
    duration = pulseIn(echopin, HIGH);
    cm = duration / 2 * 0.034;
  
    Serial.print("Distance : ");
    Serial.print(cm);
    Serial.println("cm");

    cm = (int)(cm + 0.5);

    disp(cm);
    if(cm > 0 && cm < 10){
      toneNo = getTone(starTone[i]);
      tone_duration = starBeat[i] * 333 * cm * 0.1;
      tone(buzzerpin, toneTable[toneNo][3]);
      delay(tone_duration);
      noTone(buzzerpin);
      }
    }
  }
}
