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

#define USER_GPIO_PORT_DEFAULT GPIOA
#define USER_GPIO_PIN_DEFAULT GPIO_Pin_0
#define USER_GPIO_MODE_DEFAULT GPIO_Mode_Out_PP
#define USER_GPIO_SPEED_DEFAULT GPIO_Speed_50MHz

class UserGPIO {
private:
	GPIO_InitTypeDef params{};
	GPIO_TypeDef *port;

public:
	UserGPIO(GPIO_TypeDef *_port = USER_GPIO_PORT_DEFAULT, uint32_t _pin = USER_GPIO_PIN_DEFAULT, GPIOMode_TypeDef _mode = USER_GPIO_MODE_DEFAULT, GPIOSpeed_TypeDef _speed = USER_GPIO_SPEED_DEFAULT);
	explicit UserGPIO(const char *_label, GPIOMode_TypeDef _mode = USER_GPIO_MODE_DEFAULT, GPIOSpeed_TypeDef _speed = USER_GPIO_SPEED_DEFAULT);

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
	UserState toggleState();

	BitAction getState();
};

#ifdef __cplusplus
}
#endif

#endif
