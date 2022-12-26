//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_TIM_H_
#define _USER_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_typedef.h"

class UserBasicTIM {
protected:
	TIM_TypeDef *tim;
	TIM_TimeBaseInitTypeDef base_params;

public:
	UserBasicTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per);
	UserBasicTIM(TIM_TypeDef *_tim, uint32_t _val, UserTimeUnit _unit);

	UserState enableInterrupt();
	UserState enableInterrupt(UserCallbackFunc callbackFuncPtr);
	virtual UserState registerHandler(UserCallbackFunc ptr);

	UserState start();
	UserState stop();

	uint16_t getCounter();

	UserState setPrescaler(uint16_t psc);
	UserState setPeriod(uint16_t per);
	UserState setCounter(uint16_t val);

	UserState initTimeBase();
};

#ifdef __cplusplus
}
#endif

#endif
