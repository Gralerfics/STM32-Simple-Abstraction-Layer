//
// Created by Gralerfics on 2022/12/18.
//

#include "user_nvic.h"

UserState UserNVIC::EnableTIMInterrupt(TIM_TypeDef *_tim) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructure;
	if (_tim == TIM2) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	} else if (_tim == TIM3) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	} else if (_tim == TIM4) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	} else if (_tim == TIM5) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	} else if (_tim == TIM6) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	} else if (_tim == TIM7) {
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	} else {
		return UserState::RESERVE;
	}

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

	return UserState::OK;
}
