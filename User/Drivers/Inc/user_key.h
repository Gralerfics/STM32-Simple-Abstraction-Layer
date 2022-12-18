//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_KEY_H_
#define _USER_KEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_gpio.h"

class UserKey {
private:
	UserGPIO io;
	bool activeHigh = false;

public:
	UserKey(const UserGPIO &_io);
	UserKey(const UserGPIO &_io, bool _activeHigh);

	UserGPIO& getPin();
	bool isActiveHigh();

	bool isActive(uint32_t ms_filter);
};

#ifdef __cplusplus
}
#endif

#endif
