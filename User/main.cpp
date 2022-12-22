#include "main.h"

#include "usart.h"

#include "user_led.h"
#include "user_general_tim.h"

#define OUTPUT_FREQ 100
#define WINDOW_WIDTH 200

UserGPIO io_out("A4");
UserGPIO io_in("D2", GPIO_Mode_IN_FLOATING);

UserBasicTIM tim6(TIM6, OUTPUT_FREQ * 2, "Hz");
UserGeneralTIM tim2(TIM2, WINDOW_WIDTH, "ms");
UserGeneralTIM tim3(TIM3, 0, 0xFFFE);

int cnt = 0;

void toggleOut() {
	io_out.toggleState();
}

void sampleCounter() {
	cnt = tim3.getCounter();
	TIM_SetCounter(TIM3,0);
}

void Main() {
	tim6.registerHandler(&toggleOut);
	tim6.initInterrupt();
	tim6.start();

	tim2.registerHandler(&sampleCounter);
	tim2.initInterrupt();
	tim2.start();

	tim3.setClockSource(UserTIMClockSource::External_2);
	tim3.start();

	USART_Config();
	while (true) {
		char txt[50] = {0};
		sprintf(txt, "Current Frequency: %.2lf Hz.\n", cnt * 1000.0 / WINDOW_WIDTH);
		Usart_SendString(DEBUG_USARTx, txt);
	}
}
