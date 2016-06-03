/**
 * Basic boost converter with PID loop for feedback control
 * 
 * @author Justin Bauer
 * @date June 3 2016
 * @see http://mcuhq.com
 */ 
#include <PID_v1.h>

int pwmPin = 6; //PIN 5 IS DAMAGED!
int ledPin = 13;
int analogPin = 0;
int val = 0;

unsigned long previousMillis = 0;        // will store last time
const long interval = 500;           // interval at which to delay

double Setpoint, Input, Output;
double Kp=.2, Ki=.4, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  pinMode(pwmPin,OUTPUT);
  pinMode(ledPin, OUTPUT); // onboard LED
  
  TCCR0B = (TCCR0B & 0b11111000) | 0x01; // 62KHz @see http://playground.arduino.cc/Main/TimerPWMCheatsheet
  analogWrite(pwmPin, 120);
  Serial.begin(9600);

  //initialize the variables we're linked to
  Input = analogRead(analogPin);
  Setpoint = 46; // 46= 24v 92=45V   200=99V 

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0,220);
}
void loop() {
    Input = analogRead(analogPin);    // read the input pin
    myPID.Compute();
    analogWrite(pwmPin, Output);


  // Blink the status LED
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(ledPin, !digitalRead(ledPin));
    Serial.println(Input);
    Serial.println(Output);
    Serial.println("");
    
  }
}
