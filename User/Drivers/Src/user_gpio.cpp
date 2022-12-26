//
// Created by Gralerfics on 2022/12/18.
//

#include "user_gpio.h"

#include <cstring>

#include "user_rcc.h"

#define IS_GPIO_INPUT_MODE(MODE) ((MODE & 0x10) == 0)

UserGPIO::UserGPIO(GPIO_TypeDef *_port, uint32_t _pin, GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed) {
	this -> port = IS_GPIO_ALL_PERIPH(_port) ? _port : USER_GPIO_PORT_DEFAULT;
	this -> params.GPIO_Pin = IS_GPIO_PIN(_pin) ? _pin : USER_GPIO_PIN_DEFAULT;
	this -> params.GPIO_Mode = IS_GPIO_MODE(_mode) ? _mode : USER_GPIO_MODE_DEFAULT;
	this -> params.GPIO_Speed = IS_GPIO_SPEED(_speed) ? _speed : USER_GPIO_SPEED_DEFAULT;
	this -> init();
}

UserGPIO::UserGPIO(UserGPIOs _label, GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed) {
	auto *_port = (GPIO_TypeDef *) (APB2PERIPH_BASE + 0x0800 + (_label / 100) * 0x0400);
	if (!IS_GPIO_ALL_PERIPH(_port)) return;

	uint32_t _pin = 0x1 << (_label % 100);
	if (!IS_GPIO_PIN(_pin)) return;

	this -> port = _port;
	this -> params.GPIO_Pin = _pin;
	this -> params.GPIO_Mode = IS_GPIO_MODE(_mode) ? _mode : USER_GPIO_MODE_DEFAULT;
	this -> params.GPIO_Speed = IS_GPIO_SPEED(_speed) ? _speed : USER_GPIO_SPEED_DEFAULT;
	this -> init();
}

UserState UserGPIO::init() {
	UserRCC::EnableGPIOClock(this -> port);
	GPIO_Init(this -> port, &this -> params);
	return OK;
}

GPIO_TypeDef *UserGPIO::getPort() const {
	return this -> port;
}

uint32_t UserGPIO::getPin() const {
	return this -> params.GPIO_Pin;
}

GPIOMode_TypeDef UserGPIO::getMode() const {
	return this -> params.GPIO_Mode;
}

GPIOSpeed_TypeDef UserGPIO::getSpeed() const {
	return this -> params.GPIO_Speed;
}

UserState UserGPIO::setPin(GPIO_TypeDef *_port, uint32_t _pin) {
	if (!IS_GPIO_ALL_PERIPH(_port) || !IS_GPIO_PIN(_pin)) return FAIL;

	this -> port = _port;
	this -> params.GPIO_Pin = _pin;
	this -> init();
	return OK;
}

UserState UserGPIO::setMode(GPIOMode_TypeDef _mode) {
	if (!IS_GPIO_MODE(_mode)) return FAIL;

	this -> params.GPIO_Mode = _mode;
	this -> init();
	return OK;
}

UserState UserGPIO::setSpeed(GPIOSpeed_TypeDef _speed) {
	if (!IS_GPIO_SPEED(_speed)) return FAIL;

	this -> params.GPIO_Speed = _speed;
	this -> init();
	return OK;
}

UserState UserGPIO::setHigh() {
	if (IS_GPIO_INPUT_MODE(this -> params.GPIO_Mode)) return FAIL;

	GPIO_SetBits(this -> port, this -> params.GPIO_Pin);
	return OK;
}

UserState UserGPIO::setLow() {
	if (IS_GPIO_INPUT_MODE(this -> params.GPIO_Mode)) return FAIL;

	GPIO_ResetBits(this -> port, this -> params.GPIO_Pin);
	return OK;
}

UserState UserGPIO::setState(BitAction _state) {
	if (IS_GPIO_INPUT_MODE(this -> params.GPIO_Mode) || !IS_GPIO_BIT_ACTION(_state)) return FAIL;

	GPIO_WriteBit(this -> port, this -> params.GPIO_Pin, _state);
	return OK;
}

UserState UserGPIO::toggleState() {
	return this -> setState((BitAction) !((bool) this -> getState()));
}

BitAction UserGPIO::getState() {
	if (IS_GPIO_INPUT_MODE(this -> params.GPIO_Mode)) {
		return (BitAction) GPIO_ReadInputDataBit(this -> port, this -> params.GPIO_Pin);
	} else {
		return (BitAction) GPIO_ReadOutputDataBit(this -> port, this -> params.GPIO_Pin);
	}
}
