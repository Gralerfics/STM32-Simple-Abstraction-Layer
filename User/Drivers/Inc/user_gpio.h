//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_GPIO_H_
#define _USER_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_typedef.h"

#define USER_GPIO_PORT_DEFAULT GPIOA
#define USER_GPIO_PIN_DEFAULT GPIO_Pin_0
#define USER_GPIO_MODE_DEFAULT GPIO_Mode_Out_PP
#define USER_GPIO_SPEED_DEFAULT GPIO_Speed_50MHz

typedef enum {
	PA0 = 0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
	PB0 = 100, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
	PC0 = 200, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
	PD0 = 300, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
	PE0 = 400, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,
	PF0 = 500, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15,
	PG0 = 600, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15
} UserPin;

class UserGPIO {
private:
	GPIO_InitTypeDef params{};
	GPIO_TypeDef *port;

public:
	UserGPIO(GPIO_TypeDef *_port = USER_GPIO_PORT_DEFAULT, uint32_t _pin = USER_GPIO_PIN_DEFAULT, GPIOMode_TypeDef _mode = USER_GPIO_MODE_DEFAULT, GPIOSpeed_TypeDef _speed = USER_GPIO_SPEED_DEFAULT);
	UserGPIO(UserPin _label, GPIOMode_TypeDef _mode = USER_GPIO_MODE_DEFAULT, GPIOSpeed_TypeDef _speed = USER_GPIO_SPEED_DEFAULT);

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
