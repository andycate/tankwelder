#include <Arduino.h>
#include <math.h>

#define DIRECTION 19
#define DIRECTION2 21
#define SLEEP 5
#define STEP 18 // was 18
#define STEP2 22
#define RESET 17
#define ENABLE 15
#define MS3 16
#define MS2 4
#define MS1 2

#define PEDDLE 13
#define BUTTON1 25
#define BUTTON2 26

float ipsec = 0.06; // CHANGE SPEED OF ROTATION
// float ipsec = 0.03;
// float ipsec = 0.6;
float ipstep = 4.0 * 3.14159 / 200.0 / 16.0 / 4.0;
// float ipstep = 1.5 * 3.14159 / 200.0 / 16.0 / 4.0;

int position = 0;
int onDelay = 0;
int offDelay = 0;

int feedDelay = 1000; // CHANGE SPEED OF FEEDER

int setpoint = 0;
bool pressed = false;


uint32_t lastWheelStep = 0;
bool lastWheelState = false;
uint32_t lastFeedStep = 0;
bool lastFeedState = false;



int calcOnDelay() {
  return (int) round(1000000.0 * ipstep / ipsec) / 2; // NOTE: does not account for even/odd delays
}

int calcOffDelay() {
  return (int) round(1000000.0 * ipstep / ipsec) / 2; // NOTE: does not account for even/odd delays
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  onDelay = calcOnDelay();
  offDelay = calcOffDelay();

  pinMode(DIRECTION, OUTPUT);
  pinMode(DIRECTION2, OUTPUT);
  pinMode(SLEEP, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS1, OUTPUT);

  pinMode(PEDDLE, INPUT_PULLUP);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  digitalWrite(DIRECTION, 0);
  digitalWrite(DIRECTION2, 0);
  digitalWrite(SLEEP, 1);
  digitalWrite(STEP, 0);
  digitalWrite(STEP2, 0);
  digitalWrite(RESET, 1);
  digitalWrite(ENABLE, 0);
  digitalWrite(MS3, 1);
  digitalWrite(MS2, 1);
  digitalWrite(MS1, 1);


  // ledcSetup(0, 1000, 2);
  // ledcAttachPin(STEP, 0);
  // ledcWrite(0, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
    // Serial.println("step");

  while(!digitalRead(PEDDLE)) {
    if(micros() - lastWheelStep > onDelay) {
      lastWheelStep = micros();
      position++;
      digitalWrite(STEP, !lastWheelState);
      lastWheelState = !lastWheelState;
    }

    if(micros() - lastFeedStep > feedDelay) {
      lastFeedStep = micros();
      // position++;
      digitalWrite(STEP2, !lastFeedState);
      lastFeedState = !lastFeedState;
    }
  }

  // while(!digitalRead(PEDDLE)) {
  //   position++;
  //   digitalWrite(STEP, 1);
  //   digitalWrite(STEP2, 1);
  //   delayMicroseconds(onDelay);
  //   digitalWrite(STEP, 0);
  //   digitalWrite(STEP2, 0);
  //   delayMicroseconds(offDelay);
  // }
}