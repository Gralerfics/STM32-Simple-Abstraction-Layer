# STM32-Simple-Abstraction-Layer

Some boring, simplification-oriented abstraction for STM32F1xx.

写给 F1 的玩具，基于标准库粗糙的二次封装练习。

---

An example ```main.cpp``` (Light up an LED):
```c++
#include "main.h"

#include "user_gpio.h"
#include "user_led.h"
#include "user_delayer.h"

void Main() {
    UserLED led(UserGPIO("B0"));
    while (true) {
        led.toggle();
        Delayer::ms(500);
    }
}
```

An example for user_key.h (Press the key to toggle the state of the LED):
```c++
#include "main.h"

#include "user_gpio.h"
#include "user_led.h"
#include "user_key.h"
#include "user_delayer.h"

void Main() {
    UserLED led(UserGPIO("B0"));
    UserKey key(UserGPIO("C13"), true);
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
```

Another example for TIM (basic & general) and NVIC (Generate a square wave; Detecting the frequency of the input square wave):
```c++
#include "main.h"

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
    tim6.enableInterrupt();
    tim6.start();
    
    tim2.registerHandler(&sampleCounter);
    tim2.enableInterrupt();
    tim2.start();
    
    tim3.setClockSource(UserTIMClockSource::External_2);
    tim3.start();
    
    USART_Config();
    while (true) {
        printf("Current Frequency: %.2lf Hz.\n", cnt * 1000.0 / WINDOW_WIDTH);
    }
}
```

---

Thanks for reading.
