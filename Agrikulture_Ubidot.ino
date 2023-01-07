#include <Arduino.h>
#include "A4988.h"
#include "Ubidots.h"

// Akses Ubidots
#define DEVICE         "....."
#define TOKEN          "....."
#define VARIABLE       "....."
#define VARIABLE1      "....."

#define WIFISSID       "....."
#define PASSWORD       "....."

// Pin Push Button
#define button1 4       // Pin Push Button1 D2
#define button2 15      // Pin Push Button2 D8

// Pin Relay
#define relay1  16      // Pin Relay1 D0
#define relay2  5       // Pin Relay2 D1

// Pin Driver Stepper
#define Step    14       // Pin Steep Driver D5
#define Dire    12       // Pin Direction Driver D6
#define Sleep   13       // Pin Sleep Driver D7

const int Spr = 200;
int Speed = 80;
int Microsteps = 2;
int Maju = 4500;
int Mundur = -4500;

A4988 stepper(Spr, Dire, Step);
Ubidots client(TOKEN);

void setup() {
  Serial.begin(9600);
  client.wifiConnect(WIFISSID, PASSWORD);
  
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(Sleep, HIGH);
  digitalWrite(Step, LOW);
  digitalWrite(Dire, LOW);

  stepper.begin(Speed, Microsteps);
}

void loop() {
  
  int bt1 = digitalRead(button1);
  int bt2 = digitalRead(button2);  

  float pestisida1 = client.get(DEVICE, VARIABLE);
  float pengairan1 = client.get(DEVICE, VARIABLE1);  

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  if (bt1 == 1) {
    Serial.println(F("Pengairan"));
    digitalWrite(relay1, LOW);
    stepper.rotate(Maju);
    delay(100);
    digitalWrite(relay1, LOW);
    stepper.rotate(Mundur);
    delay(100);
    
  }

  if (bt2 == 1) {
    Serial.println(F("Pestisida"));
    digitalWrite(relay2, LOW);
    stepper.rotate(Maju);
    delay(100);
    digitalWrite(relay2, LOW);
    stepper.rotate(Mundur);
    delay(100);
   
  }

    if (pengairan1 == 1) {
    Serial.println(F("Pengairan"));
    digitalWrite(relay1, LOW);
    stepper.rotate(Maju);
    delay(100);
    digitalWrite(relay1, LOW);
    stepper.rotate(Mundur);
    delay(100);
  
  }

  if (pestisida1 == 1) {
    Serial.println(F("Pestisida"));
    digitalWrite(relay2, LOW);
    stepper.rotate(Maju);
    delay(100);
    digitalWrite(relay2, LOW);
    stepper.rotate(Mundur);
    delay(100);
   
  }
}
