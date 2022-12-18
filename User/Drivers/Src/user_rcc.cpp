//
// Created by Gralerfics on 2022/12/18.
//

#include "user_rcc.h"

void UserRCC::EnableGPIOClock(GPIO_TypeDef *_port) {
	uint32_t periph = 0x1 << (((reinterpret_cast<uint32_t>(_port) & 0xFFFF) >> 10));
	RCC_APB2PeriphClockCmd(periph, ENABLE);
}
