#include <Arduino.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

// #include "ily.h"
// #include "bye.h"
// #include "nerd.h"
// #include "see.h"
// #include "who.h"
// #include "wrst.h"

#include "anton_original.h"
#include "badbird_original.h"
#include "bleib_original.h"
#include "bye_original.h"
#include "hallo_original.h"
#include "komm_original.h"
#include "love_original.h"
#include "peekaboo_original.h"
#include "schmeckt_original.h"
#include "schnaps_original.h"
#include "seeyou_original.h"
#include "watchadoin_original.h"
#include "who_original.h"

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
    long rand = random(1, 14);

    if (DEBUG_LEVEL >= DEBUG)
    {
        Serial.print("Generated number: ");
        Serial.println(rand);
    }

    switch (rand)
    {
    case 1:
        file = new AudioFileSourcePROGMEM(anton_original, sizeof(anton_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'anton_original'\n");
        }
        break;
    case 2:
        file = new AudioFileSourcePROGMEM(badbird_original, sizeof(badbird_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'badbird_original'\n");
        }
        break;
    case 3:
        file = new AudioFileSourcePROGMEM(bleib_original, sizeof(bleib_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'bleib_original'\n");
        }
        break;
    case 4:
        file = new AudioFileSourcePROGMEM(bye_original, sizeof(bye_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'bye_original'\n");
        }
        break;
    case 5:
        file = new AudioFileSourcePROGMEM(hallo_original, sizeof(hallo_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'hallo_original'\n");
        }
        break;
    case 6:
        file = new AudioFileSourcePROGMEM(komm_original, sizeof(komm_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'komm_original'\n");
        }
        break;
    case 7:
        file = new AudioFileSourcePROGMEM(love_original, sizeof(love_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'love_original'\n");
        }
        break;
    case 8:
        file = new AudioFileSourcePROGMEM(peekaboo_original, sizeof(peekaboo_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'peekaboo_original'\n");
        }
        break;
    case 9:
        file = new AudioFileSourcePROGMEM(schmeckt_original, sizeof(schmeckt_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'schmeckt_original'\n");
        }
        break;
    case 10:
        file = new AudioFileSourcePROGMEM(schnaps_original, sizeof(schnaps_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'schnaps_original'\n");
        }
        break;
    case 11:
        file = new AudioFileSourcePROGMEM(seeyou_original, sizeof(seeyou_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'seeyou_original'\n");
        }
        break;
    case 12:
        file = new AudioFileSourcePROGMEM(watchadoin_original, sizeof(watchadoin_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'watchadoin_original'\n");
        }
        break;
    case 13:
        file = new AudioFileSourcePROGMEM(who_original, sizeof(who_original));
        if (DEBUG_LEVEL >= DEBUG)
        {
            Serial.printf("Selecting 'who_original'\n");
        }
        break;
    }

    // switch (rand)
    // {
    // case 1:
    //     file = new AudioFileSourcePROGMEM(nerd, sizeof(nerd));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'Nerd'\n");
    //     }
    //     break;
    // case 2:
    //     file = new AudioFileSourcePROGMEM(bye, sizeof(bye));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'Bye'\n");
    //     }
    //     break;
    // case 3:
    //     file = new AudioFileSourcePROGMEM(ily, sizeof(ily));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'ILY'\n");
    //     }
    //     break;
    // case 4:
    //     file = new AudioFileSourcePROGMEM(see, sizeof(see));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'See'\n");
    //     }
    //     break;
    // case 5:
    //     file = new AudioFileSourcePROGMEM(who, sizeof(who));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'Who'\n");
    //     }
    //     break;
    // case 6:
    //     file = new AudioFileSourcePROGMEM(wrst, sizeof(wrst));
    //     if (DEBUG_LEVEL >= DEBUG)
    //     {
    //         Serial.printf("Selecting 'Wrst'\n");
    //     }
    //     break;
    // }
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