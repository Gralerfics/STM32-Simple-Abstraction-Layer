//
// Created by Gralerfics on 2022/12/18.
//

#include "user_delayer.h"

void Delayer::byFactor(uint32_t _t, uint32_t _factor) {
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

	SysTick -> LOAD = _t * _factor;
	SysTick -> VAL = 0x0;
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;
	uint32_t tmp;
	do { tmp = SysTick -> CTRL; } while ((tmp & 0x1) && !(tmp & 0x10000));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick -> VAL = 0x0;
}

void Delayer::s(uint32_t _t) {
	byFactor(_t, SystemCoreClock / 8);
}

void Delayer::ms(uint32_t _t) {
	byFactor(_t, SystemCoreClock / 8000);
}

void Delayer::us(uint32_t _t) {
	byFactor(_t, SystemCoreClock / 8000000);
}
