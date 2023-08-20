#include <Arduino.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

#include "ily.h"
#include "bye.h"
#include "nerd.h"
#include "see.h"
#include "who.h"
#include "wrst.h"

#define NONE 0
#define ERROR 1
#define WARN 2
#define DEBUG 3
#define ALL 4
#define DEBUG_LEVEL DEBUG

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

long randNumber;

void setup()
{
    Serial.begin(9600);
    delay(1000);
    if (DEBUG_LEVEL >= DEBUG)
    {
        Serial.printf("Starting Setup");
    }

    audioLogger = &Serial;

    file = new AudioFileSourcePROGMEM();
    out = new AudioOutputI2S();
    wav = new AudioGeneratorWAV();
}

void select_random_file()
{
    long rand = random(1, 7);

    if (DEBUG_LEVEL >= DEBUG)
    {
        Serial.print("Generated number: ");
        Serial.println(rand);
    }

    switch (rand)
    {
    case 1:
        file = new AudioFileSourcePROGMEM(nerd, sizeof(nerd));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'Nerd'\n");
        }
        break;
    case 2:
        file = new AudioFileSourcePROGMEM(bye, sizeof(bye));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'Bye'\n");
        }
        break;
    case 3:
        file = new AudioFileSourcePROGMEM(ily, sizeof(ily));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'ILY'\n");
        }
        break;
    case 4:
        file = new AudioFileSourcePROGMEM(see, sizeof(see));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'See'\n");
        }
        break;
    case 5:
        file = new AudioFileSourcePROGMEM(who, sizeof(who));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'Who'\n");
        }
        break;
    case 6:
        file = new AudioFileSourcePROGMEM(wrst, sizeof(wrst));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'Wrst'\n");
        }
        break;
    }
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
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("WAV done\n");
        }
        file->close();
        delete file;
        delete wav;

        select_random_file();
        wav = new AudioGeneratorWAV();
        delay(2000);
        wav->begin(file, out);
    }
}