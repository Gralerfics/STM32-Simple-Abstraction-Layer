//
// Created by Gralerfics on 2022/12/18.
//

#include "user_tim.h"

#define CLOCKDIVISION_DEFAULT TIM_CKD_DIV1
#define COUNTERMODE_DEFAULT TIM_CounterMode_Up
#define REPETITIONCOUNTER_DEFAULT 0

UserTIM::UserTIM(TIM_TypeDef *_tim, uint16_t _psc, uint16_t _per) {
	this -> tim = _tim;
	this -> base_params.TIM_Prescaler = _psc;
	this -> base_params.TIM_Period = _per;
	this -> base_params.TIM_ClockDivision = CLOCKDIVISION_DEFAULT;
	this -> base_params.TIM_CounterMode = COUNTERMODE_DEFAULT;
	this -> base_params.TIM_RepetitionCounter = REPETITIONCOUNTER_DEFAULT;
	this -> init();
}

UserState UserTIM::init() {
	if (this -> tim == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		TIM_InternalClockConfig(this -> tim);

		TIM_TimeBaseInit(this -> tim, &this -> base_params);

		TIM_ITConfig(this -> tim, TIM_IT_Update, ENABLE);

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStructure);

		TIM_Cmd(this -> tim, ENABLE);

		return USER_STATE_OK;
	} else {
		// TODO.
		return USER_STATE_RESERVE;
	}
}
