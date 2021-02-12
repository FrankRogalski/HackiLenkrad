#ifndef __SHBUTTON_H__
#define __SHBUTTON_H__

#include <Arduino.h>
#include "SHFastIO.h"

typedef void(*SHButtonChanged) (int, byte);

class SHButton {

private:
	uint8_t buttonState;
	int buttonLastState;
	unsigned long buttonLastStateChanged;
	byte id;
	SHButtonChanged shButtonChangedCallback;

public:

	void begin(byte buttonid, SHButtonChanged changedcallback) {
		id = buttonid;
		buttonLastState = LOW;
		shButtonChangedCallback = changedcallback;
	}

	uint8_t getPressed() {
		return !buttonLastState;
	}

	void read(uint8_t buttonState) {
		if (buttonState != buttonLastState && buttonLastStateChanged - millis() > 50) {
			shButtonChangedCallback(id, buttonState == HIGH ? 0 : 1);
			buttonLastState = buttonState;
			buttonLastStateChanged = millis();
		}
	}
};

#endif
