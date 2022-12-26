//
// Created by Gralerfics on 2022/12/23.
//

#ifndef _USER_GENERAL_TIM_H_
#define _USER_GENERAL_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "user_typedef.h"

#include "user_basic_tim.h"

#define USER_TIM_ETR_TRGPRESCALER_DEFAULT TIM_ExtTRGPSC_OFF
#define USER_TIM_ETR_TRGPOLARITY_DEFAULT TIM_ExtTRGPolarity_NonInverted
#define USER_TIM_ETR_TRGFILTER_DEFAULT 0x00

typedef enum {
	Internal = 0,
	External_2
} UserTIMClockSource;

class UserGeneralTIM: public UserBasicTIM {
protected:
	UserTIMClockSource clk_src;

public:
	UserGeneralTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per);
	UserGeneralTIM(TIM_TypeDef *_tim, uint32_t _val, UserTimeUnit _unit);

	UserState registerHandler(UserCallbackFunc ptr) override;

	UserState setClockSource(UserTIMClockSource _clk_src, uint16_t etr_trgprescaler = USER_TIM_ETR_TRGPRESCALER_DEFAULT, uint16_t etr_trgpolarity = USER_TIM_ETR_TRGPOLARITY_DEFAULT, uint16_t etr_trgfilter = USER_TIM_ETR_TRGFILTER_DEFAULT);
};

#ifdef __cplusplus
}
#endif

#endif
