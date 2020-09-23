#include <SoftwareSerial.h>

//bluetooth
#define RX 2
#define TX 3

SoftwareSerial mySerial(TX, RX);

//MUX1 Pin set
int pinSIG = A0;
int pinEN2 = 4;
int a0 = 5; int a1 = 6;
int a2 = 7; int a3 = 8;

//MUX2 Pin set
int pinSIG2 = A1;
int pinEN = 9;
int s0 = 10; int s1 = 11;
int s2 = 12; int s3 = 13;

int controlPin[4] = {s0, s1, s2, s3};
int controlPin2[4] = {a0, a1, a2, a3};

int c[30] = {0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0
            };

int muxChannel[16][4] = {
  //[2^0, 2^1, 2^2, 2^3]

  {0, 0, 0, 0}, //channel 0
  {1, 0, 0, 0}, //channel 1
  {0, 1, 0, 0}, //channel 2
  {1, 1, 0, 0}, //channel 3
  {0, 0, 1, 0}, //channel 4
  {1, 0, 1, 0}, //channel 5
  {0, 1, 1, 0}, //channel 6
  {1, 1, 1, 0}, //channel 7
  {0, 0, 0, 1}, //channel 8
  {1, 0, 0, 1}, //channel 9
  {0, 1, 0, 1}, //channel 10
  {1, 1, 0, 1}, //channel 11
  {0, 0, 1, 1}, //channel 12
  {1, 0, 1, 1}, //channel 13
  {0, 1, 1, 1}, //channel 14
  {1, 1, 1, 1} //channel 15
};

int muxChannel2[16][4] = {
  //[2^0, 2^1, 2^2, 2^3]

  {0, 0, 0, 0}, //channel 0
  {1, 0, 0, 0}, //channel 1
  {0, 1, 0, 0}, //channel 2
  {1, 1, 0, 0}, //channel 3
  {0, 0, 1, 0}, //channel 4
  {1, 0, 1, 0}, //channel 5
  {0, 1, 1, 0}, //channel 6
  {1, 1, 1, 0}, //channel 7
  {0, 0, 0, 1}, //channel 8
  {1, 0, 0, 1}, //channel 9
  {0, 1, 0, 1}, //channel 10
  {1, 1, 0, 1}, //channel 11
  {0, 0, 1, 1}, //channel 12
  {1, 0, 1, 1}, //channel 13
};


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(pinEN, OUTPUT); digitalWrite(pinEN, LOW);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  pinMode(pinEN2, OUTPUT); digitalWrite(pinEN2, LOW);
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
}

void loop() {

  //MUX를 거친 압력센서의 데이터 저장
  //MUX1 data
  for (int i = 0; i < 16; i++) {
    c[i] = map(readADCMux(i), 0, 950, 0, 100);
  }

  //MUX2 data
  for (int i = 0; i < 14; i++) {
    c[i + 16] = map(readADCMux2(i), 0, 950, 0, 100);
  }
  /*
    압력센서 값 출력
    =====================
    C4  C3  C2  C1 C0
    C9  C8  C7  C1 C5
    C14 C13 C12 C1 C10
    C19 C18 C17 C1 C15
    C24 C23 C22 C1 C20
    C29 C28 C27 C1 C25
  */

  /*
    Serial.println("=================================================");
    for (int i = 4; i >=0 ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();

    for (int i = 9; i >=5 ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();

    for (int i = 14; i >=10 ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();

    for (int i = 19; i < 15 ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();
    for (int i = 24; i < 20 ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();

    for (int i = 29; i <25  ; i--) {
    Serial.print(c[i]);
    Serial.print("\t");
    }
    Serial.println();
  */


  //데이터 한줄 배열로 출력
  for (int i = 0; i < 30; i++) {
    Serial.print(c[i]);
    Serial.print("\t");
    mySerial.print(c[i]);
    if (i < 29)
      mySerial.print(",");
  }
  mySerial.println();
  Serial.println();

  delay(1000);
}

//해당 채널의 압력센서값 출력
//MUX 1
int readADCMux(int ch) {
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[ch][i]);
  }
  return analogRead(pinSIG);
}

//MUX 2
int readADCMux2(int ch) {
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin2[i], muxChannel2[ch][i]);
  }
  return analogRead(pinSIG2);
}
