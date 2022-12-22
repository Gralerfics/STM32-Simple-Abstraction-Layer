//
// Created by Gralerfics on 2022/12/18.
//

#include "user_key.h"

#include "user_delayer.h"

UserKey::UserKey(const UserGPIO &_io, bool _activeHigh) {
	this -> io = _io;
	this -> activeHigh = _activeHigh;
	this -> init();
}

UserState UserKey::init() {
	if (this -> activeHigh) {
		this -> io.setMode(GPIO_Mode_IPD);
	} else {
		this -> io.setMode(GPIO_Mode_IPU);
	}
	this -> io.init();
	return UserState::OK;
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
