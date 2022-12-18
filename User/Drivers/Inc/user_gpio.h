//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_GPIO_H_
#define _USER_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_state.h"

class UserGPIO {
private:
	GPIO_InitTypeDef params{};
	GPIO_TypeDef *port;

public:
	UserGPIO();
	UserGPIO(GPIO_TypeDef *_port, uint32_t _pin);
	UserGPIO(GPIO_TypeDef *_port, uint32_t _pin, GPIOMode_TypeDef _mode);
	UserGPIO(GPIO_TypeDef *_port, uint32_t _pin, GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed);
	explicit UserGPIO(const char *_label);

	UserState init();

	GPIO_TypeDef *getPort() const;
	uint32_t getPin() const;
	GPIOMode_TypeDef getMode() const;
	GPIOSpeed_TypeDef getSpeed() const;

	UserState setPin(GPIO_TypeDef *_port, uint32_t _pin);
	UserState setMode(GPIOMode_TypeDef _mode);
	UserState setSpeed(GPIOSpeed_TypeDef _speed);

	UserState setHigh();
	UserState setLow();
	UserState setState(BitAction _state);

	BitAction getState();
};

#ifdef __cplusplus
}
#endif

#endif
