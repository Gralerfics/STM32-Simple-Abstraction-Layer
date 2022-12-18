# STM32-Simple-Abstraction-Layer

Some boring, simplification-oriented abstraction.

---

An example ```main.cpp```:
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

Another example:
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

---

Thanks for reading.
