//
// Created by Gralerfics on 2022/12/18.
//

#include "user_key.h"

#include "user_delayer.h"

UserKey::UserKey(const UserGPIO &_io) {
	this -> io = _io;
	this -> io.setMode(GPIO_Mode_IPU);
}

UserKey::UserKey(const UserGPIO &_io, bool _activeHigh): UserKey(_io) {
	this -> activeHigh = _activeHigh;
	if (_activeHigh) {
		this -> io.setMode(GPIO_Mode_IPD);
	} else {
		this -> io.setMode(GPIO_Mode_IPU);
	}
}

UserGPIO &UserKey::getPin() {
	return this -> io;
}

bool UserKey::isActiveHigh() {
	return this -> activeHigh;
}

bool UserKey::isActive(uint32_t ms_filter) {
	for (uint8_t i = 0; i < 2; i ++) {
		Delayer::ms(ms_filter);
		if (this -> activeHigh != (bool) this -> io.getState()) return false;
	}
	return true;
}
