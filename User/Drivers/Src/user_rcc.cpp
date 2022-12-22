//
// Created by Gralerfics on 2022/12/18.
//

#include "user_rcc.h"

UserState UserRCC::EnableGPIOClock(GPIO_TypeDef *_port) {
	uint32_t periph = 0x1 << ((reinterpret_cast<uint32_t>(_port) & 0xFFFF) >> 10);
	RCC_APB2PeriphClockCmd(periph, ENABLE);
	return UserState::OK;
}

UserState UserRCC::EnableTIMClock(TIM_TypeDef *_tim) {
	if (IS_TIM_LIST1_PERIPH(_tim)) {
		/* TIM 1, 8 */
		if (_tim == TIM1) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		} else if (_tim == TIM8) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		}
	} else if (IS_TIM_ALL_PERIPH(_tim)) {
		/* TIM 2, 3, 4, 5, 6, 7 */
		uint32_t periph = 0x1 << ((reinterpret_cast<uint32_t>(_tim) & 0xFFFF) >> 10);
		RCC_APB1PeriphClockCmd(periph, ENABLE);
	} else {
		/* Not TIM */
		return UserState::FAIL;
	}
	return UserState::OK;
}
