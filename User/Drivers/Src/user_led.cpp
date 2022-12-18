//
// Created by Gralerfics on 2022/12/18.
//

#include "user_led.h"

UserLED::UserLED(const UserGPIO &_io) {
	this -> io = _io;
	this -> io.setMode(GPIO_Mode_Out_PP);
	this -> off();
}

UserLED::UserLED(const UserGPIO &_io, bool _activeHigh): UserLED(_io) {
	this -> activeHigh = _activeHigh;
	this -> off();
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
	return this -> io.setState((BitAction) !((bool) this -> io.getState()));
}

UserState UserLED::setState(bool _state) {
	return this -> io.setState((BitAction) (_state ^ !this -> activeHigh));
}
