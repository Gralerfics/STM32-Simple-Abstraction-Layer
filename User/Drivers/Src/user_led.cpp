//
// Created by Gralerfics on 2022/12/18.
//

#include "user_led.h"

UserLED::UserLED(const UserGPIO &_io, bool _activeHigh) {
	this -> io = _io;
	this -> activeHigh = _activeHigh;
	this -> init();
}

UserState UserLED::init() {
	this -> io.setMode(GPIO_Mode_Out_PP);
	this -> io.init();
	this -> off();
	return UserState::OK;
}

UserGPIO &UserLED::getPin() {
	return this -> io;
}

bool UserLED::isActiveHigh() {
	return this -> activeHigh;
}

UserState UserLED::on() {
	return this -> io.setState((BitAction) this -> activeHigh);
}

UserState UserLED::off() {
	return this -> io.setState((BitAction) !this -> activeHigh);
}

UserState UserLED::toggle() {
	return this -> io.toggleState();
}

UserState UserLED::setState(bool _state) {
	return this -> io.setState((BitAction) (_state ^ !this -> activeHigh));
}
