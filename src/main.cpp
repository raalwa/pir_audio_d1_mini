#include <Arduino.h>
#include <math.h>

int PIR_PIN = 5;

void handle_motion()
{
  Serial.println("---");
  Serial.println("Motion detected");
  Serial.println("---");
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(PIR_PIN) == HIGH)
  {
    handle_motion();
  }
}