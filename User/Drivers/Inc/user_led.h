//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_LED_H_
#define _USER_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_gpio.h"

class UserLED {
private:
	UserGPIO io;
	bool activeHigh;

public:
	UserLED(const UserGPIO &_io, bool _activeHigh = false);

	UserState init();

	UserGPIO& getPin();
	bool isActiveHigh();

	UserState on();
	UserState off();
	UserState toggle();
	UserState setState(bool _state);
};

#ifdef __cplusplus
}
#endif

#endif
