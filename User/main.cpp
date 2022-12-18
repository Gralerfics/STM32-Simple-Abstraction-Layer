#include "main.h"

#include "user_gpio.h"
#include "user_tim.h"
#include "user_led.h"
#include "user_key.h"
#include "user_delayer.h"

#include "stm32f10x_it.h"

UserLED led(UserGPIO("B0"));
UserKey key(UserGPIO("C13"), true);

void Example_LED_Alternating() {
	while (true) {
		led.toggle();
		Delayer::ms(500);
	}
}

void Example_Controlled_LED() {
	bool active = false, active_last = false;
	while (true) {
		active_last = active;
		active = key.isActive(20);

		if (!active_last && active) {
			led.toggle();
		}

		Delayer::ms(1);
	}
}

void Example_Timer() {
	UserTIM tim(TIM2, 72000 - 1, 10000 - 1);
	while (true) {}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		led.toggle();
	}
}

void Main() {
	Example_Timer();
}
