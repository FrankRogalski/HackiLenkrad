#ifndef __SHRGBLEDSNEOPIXEL_H__
#define __SHRGBLEDSNEOPIXEL_H__
#define DATA_PIN 4
#define CLOCK_PIN 6
#define LATCH_PIN 5

#include <Arduino.h>
#include "SHRGBLedsBase.h"
#include <Adafruit_NeoPixel.h>

class SHRGBLedsNeoPixel : public SHRGBLedsBase {
private:
	unsigned long lastRead = 0;
    unsigned byte pins = 0;

protected:
	Adafruit_NeoPixel * NeoPixel_strip;
public:

	void begin(Adafruit_NeoPixel * strip, int maxLeds, int righttoleft, bool testMode) {
		SHRGBLedsBase::begin(maxLeds, righttoleft);
		NeoPixel_strip = strip;
		NeoPixel_strip->begin();
		NeoPixel_strip->show();

		if (testMode > 0) {
			for (int i = 0; i < maxLeds; i++) {
				NeoPixel_strip->setPixelColor(i, 255, 0, 0);
				NeoPixel_strip->show();
			}
		}
	}

	void show() {
		NeoPixel_strip->show();
	}

protected:
	void setPixelColor(uint8_t lednumber, uint8_t r, uint8_t g, uint8_t b) {
		//NeoPixel_strip->setPixelColor(lednumber, r, g, b);
        bool on = r + g + b > 0;
        lednumber -= 50;
        //Changing the nth bit to x
        //https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
        pins ^= (-int(on) ^ pins) & (1UL << lednumber);
        digitalWrite(LATCH_PIN, LOW);
        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pins);
        digitalWrite(LATCH_PIN, HIGH);
	}
};

#endif
