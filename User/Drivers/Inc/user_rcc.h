//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_RCC_H_
#define _USER_RCC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_typedef.h"
#include "user_gpio.h"

class UserRCC {
public:
	static UserState EnableGPIOClock(GPIO_TypeDef *_port);
	static UserState EnableTIMClock(TIM_TypeDef *_tim);
};

#ifdef __cplusplus
}
#endif

#endif
