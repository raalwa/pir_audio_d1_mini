#include <Arduino.h>
#include <Adafruit_ZeroI2S.h>
#include <math.h>

/* max volume for 32 bit data */
#define VOLUME ((1UL << 31) - 1)
/* create a buffer for both the left and right channel data */
#define BUFSIZE 128
int left[BUFSIZE];
int right[BUFSIZE];

int PIR_PIN = 5;

int LRC = 3;
int BCLK = 12;
int DIN = 13;
int VIN = 14;

// Use default pins in board variant
Adafruit_ZeroI2S i2s = Adafruit_ZeroI2S(3, 12, 13, 14);

void setup()
{
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LRC, OUTPUT);
  pinMode(BCLK, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(VIN, OUTPUT);
  digitalWrite(VIN, HIGH);
  Serial.begin(9600);

  while (!Serial)
    delay(10);
  Serial.println("I2S demo");
  for (int i = 0; i < BUFSIZE; i++)
  {
    /* create a sine wave on the left channel */
    left[i] = sin((2 * PI / (BUFSIZE)) * i) * VOLUME;
    /* create a cosine wave on the right channel */
    right[i] = cos((2 * PI / (BUFSIZE)) * i) * VOLUME;
  }
  /* begin I2S on the default pins. 24 bit depth at
   * 44100 samples per second
   */
  i2s.begin(I2S_32_BIT, 44100);
  i2s.enableTx();
}

void loop()
{
  // if (digitalRead(PIR_PIN) == HIGH)
  // {
  //   // digitalWrite(LED_BUILTIN, HIGH);
  //   Serial.println("---");
  //   Serial.println("Motion detected");
  //   Serial.println("---");
  // }
  for (int i = 0; i < BUFSIZE; i++)
  {
    i2s.write(left[i], right[i]);
  }
}