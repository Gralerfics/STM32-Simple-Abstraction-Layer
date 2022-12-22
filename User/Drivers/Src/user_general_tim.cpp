//
// Created by Gralerfics on 2022/12/23.
//

#include "user_general_tim.h"

static UserTIMCallbackTypeDef tim2_irqHandler = nullptr;
static UserTIMCallbackTypeDef tim3_irqHandler = nullptr;
static UserTIMCallbackTypeDef tim4_irqHandler = nullptr;
static UserTIMCallbackTypeDef tim5_irqHandler = nullptr;

UserGeneralTIM::UserGeneralTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per) : UserBasicTIM(_tim, _psc, _per) {
	this -> clk_src = UserTIMClockSource::Internal;
}

UserGeneralTIM::UserGeneralTIM(TIM_TypeDef *_tim, uint32_t _val, char *_unit) : UserBasicTIM(_tim, _val, _unit) {
	this -> clk_src = UserTIMClockSource::Internal;
}

UserState UserGeneralTIM::registerHandler(UserTIMCallbackTypeDef ptr) {
	if (this -> tim == TIM2) {
		tim2_irqHandler = ptr;
	} else if (this -> tim == TIM3) {
		tim3_irqHandler = ptr;
	} else if (this -> tim == TIM4) {
		tim4_irqHandler = ptr;
	} else if (this -> tim == TIM5) {
		tim5_irqHandler = ptr;
	} else {
		return UserState::RESERVE;
	}
	return UserState::OK;
}

UserState UserGeneralTIM::setClockSource(UserTIMClockSource _clk_src, uint16_t etr_trgprescaler, uint16_t etr_trgpolarity, uint16_t etr_trgfilter) {
	this -> clk_src = _clk_src;
	switch (this -> clk_src) {
		case UserTIMClockSource::Internal:
			TIM_InternalClockConfig(this -> tim);
			break;
		case UserTIMClockSource::External_2:
			TIM_ETRClockMode2Config(this -> tim, etr_trgprescaler, etr_trgpolarity, etr_trgfilter);
			break;
	}
	return UserState::OK;
}

/* +====================================+
 * |            IRQ Handlers            |
 * +====================================+ */

#include "stm32f10x_it.h"

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		if (tim2_irqHandler != nullptr) tim2_irqHandler();
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
	}
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		if (tim3_irqHandler != nullptr) tim3_irqHandler();
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
	}
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		if (tim4_irqHandler != nullptr) tim4_irqHandler();
		TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
	}
}

void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
		if (tim5_irqHandler != nullptr) tim5_irqHandler();
		TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);
	}
}
