#ifndef SHRGBLEDSNEOPIXELFASTLED_H
#define SHRGBLEDSNEOPIXELFASTLED_H
#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include "SHRGBLedsBase.h"
#include <FastLED.h>

CRGB SHRGBLedsNeoPixelFastLeds_leds[WS2812B_RGBLEDCOUNT];

class SHRGBLedsNeoPixelFastLeds : public SHRGBLedsBase {
private:
    unsigned long lastRead = 0;
  byte pins = 0;
  byte DATA_PIN = 4;
  byte CLOCK_PIN = 6;
  byte LATCH_PIN = 5;

public:

    void begin(int maxLeds, int righttoleft, bool testMode) {
        SHRGBLedsBase::begin(maxLeds, righttoleft);
        FastLED.addLeds<NEOPIXEL, WS2812B_DATAPIN>(SHRGBLedsNeoPixelFastLeds_leds, maxLeds);

    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(CLOCK_PIN,LOW);

        if (testMode > 0) {
            for (int i = 0; i < maxLeds; i++) {
                setPixelColor(i, 255, 0, 0);
            }
        }
        FastLED.show();
    }

    void show() {
        FastLED.show();
        //delay(10);
    }

protected:
    void setPixelColor(uint8_t lednumber, uint8_t r, uint8_t g, uint8_t b) {
        // 0 for GRB, 
        // 1 for RGB encoding
        // 2 for BRG encoding
        if (WS2812B_RGBENCODING == 0) {
            SHRGBLedsNeoPixelFastLeds_leds[lednumber].setRGB(r, g, b);
        }
        else if (WS2812B_RGBENCODING == 1) {
            SHRGBLedsNeoPixelFastLeds_leds[lednumber].setRGB(g, r, b);
        }
        else if (WS2812B_RGBENCODING == 2) {
            SHRGBLedsNeoPixelFastLeds_leds[lednumber].setRGB(b, g, r);
        }

        bool on = r + g + b > 0;
        //Changing the nth bit to x
        //https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
        pins ^= (-int(on) ^ pins) & (1UL << lednumber);
        //digitalWrite(LATCH_PIN, LOW);
        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pins);
        digitalWrite(LATCH_PIN, HIGH);
        delayMicroseconds(5);
        digitalWrite(LATCH_PIN, LOW);
    }
};

#endif