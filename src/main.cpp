#include <Arduino.h>
#include <math.h>
#include <ESP8266WiFi.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

AudioFileSourceSPIFFS *file;
AudioGeneratorWAV *wav;
AudioOutputI2S *out;

int PIR_PIN = 5;

void handle_motion()
{
  Serial.println("---");
  Serial.println("Motion detected");
  Serial.println("---");
}

void setup()
{
  WiFi.mode(WIFI_OFF);
  Serial.begin(9600);
  SPIFFS.begin();

  file = new AudioFileSourceSPIFFS("/bye.wav");
  out = new AudioOutputI2S();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}

void loop()
{
  if (wav->isRunning())
  {
    if (!wav->loop())
      wav->stop();
  }
  else
  {
    Serial.printf("WAV done\n");
    delay(1000);
  }
}