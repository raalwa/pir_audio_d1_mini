#include <Arduino.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

#include "ily.h"
#include "kommher.h"
#include "badbird.h"
#include "hallo.h"
#include "peekaboo.h"
#include "watcha.h"
#include "who.h"
#include "bleibda.h"

#define NONE 0
#define ERROR 1
#define WARN 2
#define DEBUG 3
#define ALL 4
#define DEBUG_LEVEL NONE

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

// GPIO 14 corresponds to D5
int PIR_PIN = 14;
bool motion_flag = false;

void setup()
{
    Serial.begin(9600);
    if (DEBUG_LEVEL >= DEBUG)
    {
        Serial.printf("Starting Setup");
    }

    pinMode(PIR_PIN, INPUT);

    audioLogger = &Serial;

    file = new AudioFileSourcePROGMEM();
    out = new AudioOutputI2S();
    wav = new AudioGeneratorWAV();
}

void select_random_file()
{
    long rand = random(1, 9);

    if (DEBUG_LEVEL >= DEBUG)
    {
        Serial.print("Generated number: ");
        Serial.println(rand);
    }

    switch (rand)
    {
    case 1:
        file = new AudioFileSourcePROGMEM(badbird, sizeof(badbird));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'badbird'\n");
        }
        break;
    case 2:
        file = new AudioFileSourcePROGMEM(hallo, sizeof(hallo));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'hallo'\n");
        }
        break;
    case 3:
        file = new AudioFileSourcePROGMEM(ily, sizeof(ily));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'ily'\n");
        }
        break;
    case 4:
        file = new AudioFileSourcePROGMEM(kommher, sizeof(kommher));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'kommher'\n");
        }
        break;
    case 5:
        file = new AudioFileSourcePROGMEM(peekaboo, sizeof(peekaboo));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'peekaboo'\n");
        }
        break;
    case 6:
        file = new AudioFileSourcePROGMEM(watcha, sizeof(watcha));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'watcha'\n");
        }
        break;
    case 7:
        file = new AudioFileSourcePROGMEM(who, sizeof(who));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'who'\n");
        }
        break;
    case 8:
        file = new AudioFileSourcePROGMEM(bleibda, sizeof(bleibda));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'bleibda'\n");
        }
        break;
    }
}

void loop()
{
    if (digitalRead(PIR_PIN) == HIGH && !motion_flag)
    {
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Motion recognized\n");
        }
        motion_flag = true;
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.print("Motion_Flag: ");
            Serial.println(motion_flag);
        }
    }
    if (motion_flag)
    {
        if (wav->isRunning())
        {
            if (!wav->loop())
                wav->stop();
        }
        else
        {
            if (DEBUG_LEVEL >= DEBUG)
            {
                Serial.printf("WAV done\n");
            }
            file->close();
            delete file;
            delete wav;
            motion_flag = false;

            select_random_file();
            wav = new AudioGeneratorWAV();
            wav->begin(file, out);
            delay(2000);
        }
    }
}