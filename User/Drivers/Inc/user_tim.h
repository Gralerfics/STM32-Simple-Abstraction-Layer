//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_TIM_H_
#define _USER_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_state.h"

/* Uncompleted, only for TIM2 Base Interrupt */

class UserTIM {
private:
	TIM_TypeDef *tim;
	TIM_TimeBaseInitTypeDef base_params;

public:
	UserTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per);

	UserState init();
};

#ifdef __cplusplus
}
#endif

#endif
