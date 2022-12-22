//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_NVIC_H_
#define _USER_NVIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_state.h"

class UserNVIC {
public:
	static UserState EnableTIMInterrupt(TIM_TypeDef *_tim);
};

#ifdef __cplusplus
}
#endif

#endif
