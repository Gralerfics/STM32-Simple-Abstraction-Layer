//
// Created by Gralerfics on 2022/12/18.
//

#include "user_basic_tim.h"

#include "cmath"
#include "cstring"

#include "user_rcc.h"
#include "user_nvic.h"

#define PSC_DEFAULT 72
#define PER_DEFAULT 1000
#define CLOCKDIVISION_DEFAULT TIM_CKD_DIV1
#define COUNTERMODE_DEFAULT TIM_CounterMode_Up
#define REPETITIONCOUNTER_DEFAULT 0

static UserTIMCallbackTypeDef tim6_irqHandler = nullptr;
static UserTIMCallbackTypeDef tim7_irqHandler = nullptr;

UserBasicTIM::UserBasicTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per) {
	this -> tim = _tim;
	this -> base_params.TIM_Prescaler = _psc;
	this -> base_params.TIM_Period = _per;
	this -> base_params.TIM_ClockDivision = CLOCKDIVISION_DEFAULT;
	this -> base_params.TIM_CounterMode = COUNTERMODE_DEFAULT;
	this -> base_params.TIM_RepetitionCounter = REPETITIONCOUNTER_DEFAULT;
	this -> initTimeBase();
}

UserBasicTIM::UserBasicTIM(TIM_TypeDef *_tim, uint32_t _val, char *_unit) {
	double target_freq;
	if (strlen(_unit) == 1 && _unit[0] == 's') {
		target_freq = 1.0 / _val;
	} else if (strlen(_unit) == 2 && _unit[0] == 'm' && _unit[1] == 's') {
		target_freq = 1000.0 / _val;
	} else if (strlen(_unit) == 2 && _unit[0] == 'u' && _unit[1] == 's') {
		target_freq = 1000000.0 / _val;
	} else if (strlen(_unit) == 2 && _unit[0] == 'H' && _unit[1] == 'z') {
		target_freq = _val;
	} else if (strlen(_unit) == 3 && _unit[0] == 'k' && _unit[1] == 'H' && _unit[2] == 'z') {
		target_freq = 1000.0 * _val;
	} else {
		target_freq = 1000.0;
	}

	uint32_t psc = 0, per = 0;
	double min_diff = SystemCoreClock, eps = 1e-5;
	uint16_t psc_divs[12] = {1, 2, 3, 4, 6, 8, 9, 12, 18, 24, 36, 72};
	for (int8_t i = 11; i >= 0; i --) {
		uint32_t psc_peek = psc_divs[i];
		for (uint8_t j = 0; j < 5 && psc_peek < 65536; j ++, psc_peek *= 10) {
			auto per_peek = (uint32_t) (1.0 * SystemCoreClock / psc_peek / target_freq);
			if (per_peek >= 65536) continue;
			double diff = fabs(target_freq * psc_peek * per_peek - SystemCoreClock);
			if (diff < min_diff) {
				min_diff = diff;
				psc = psc_peek;
				per = per_peek;
			}
			if (min_diff < eps) break;
		}
		if (min_diff < eps) break;
	}

	if (psc == 0 || per == 0) {
		psc = PSC_DEFAULT;
		per = PER_DEFAULT;
	}

	this -> tim = _tim;
	this -> base_params.TIM_Prescaler = psc - 1;
	this -> base_params.TIM_Period = per - 1;
	this -> base_params.TIM_ClockDivision = CLOCKDIVISION_DEFAULT;
	this -> base_params.TIM_CounterMode = COUNTERMODE_DEFAULT;
	this -> base_params.TIM_RepetitionCounter = REPETITIONCOUNTER_DEFAULT;
	this -> initTimeBase();
}

UserState UserBasicTIM::initTimeBase() {
	UserRCC::EnableTIMClock(this -> tim);
	TIM_InternalClockConfig(this -> tim);
	TIM_TimeBaseInit(this -> tim, &this -> base_params);
	return UserState::OK;
}

UserState UserBasicTIM::initInterrupt() {
	TIM_ITConfig(this -> tim, TIM_IT_Update, ENABLE);
	UserNVIC::EnableTIMInterrupt(this -> tim);
	TIM_ClearFlag(this -> tim, TIM_FLAG_Update);
	return UserState::OK;
}

UserState UserBasicTIM::registerHandler(UserTIMCallbackTypeDef ptr) {
	if (this -> tim == TIM6) {
		tim6_irqHandler = ptr;
	} else if (this -> tim == TIM7) {
		tim7_irqHandler = ptr;
	} else {
		return UserState::RESERVE;
	}
	return UserState::OK;
}

UserState UserBasicTIM::start() {
	this -> setCounter(0);
	TIM_Cmd(this -> tim, ENABLE);
	return UserState::OK;
}

UserState UserBasicTIM::stop() {
	TIM_Cmd(this -> tim, DISABLE);
	return UserState::OK;
}

uint16_t UserBasicTIM::getCounter() {
	return TIM_GetCounter(this -> tim);
}

UserState UserBasicTIM::setPrescaler(uint16_t psc) {
	this -> base_params.TIM_Prescaler = psc;
	this -> initTimeBase();
	return UserState::OK;
}

UserState UserBasicTIM::setPeriod(uint16_t per) {
	this -> base_params.TIM_Period = per;
	this -> initTimeBase();
	return UserState::OK;
}

UserState UserBasicTIM::setCounter(uint16_t val) {
	TIM_SetCounter(this -> tim, val);
	return UserState::OK;
}

/* +====================================+
 * |            IRQ Handlers            |
 * +====================================+ */

#include "stm32f10x_it.h"

void TIM6_IRQHandler(void) {
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
		if (tim6_irqHandler != nullptr) tim6_irqHandler();
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);
	}
}

void TIM7_IRQHandler(void) {
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
		if (tim7_irqHandler != nullptr) tim7_irqHandler();
		TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);
	}
}
