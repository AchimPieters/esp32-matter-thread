# LED Matter + Thread Example

Dit voorbeeld is de minimale maar functionele validatie van `esp32-matter-thread` op ESP32-C6.

## Functionaliteit

- Initialiseert ESP-Matter + NVS
- Doet dit volledig via `#include "esp32_matter_thread.h"` + `esp32_matter_thread_start(...)`
- Maakt een **Matter On/Off Light** endpoint
- Verbindt de Matter `OnOff` attribute met een fysieke LED GPIO
- Werkt voor active-high en active-low LED wiring
- Print automatisch QR/Matter onboarding code in serial log na boot

## Configuratie

Instelbaar via menuconfig:

- `LED Matter Example Configuration -> LED GPIO`
- `LED Matter Example Configuration -> LED is active-low`

Defaults staan in `sdkconfig.defaults`:

- `CONFIG_EXAMPLE_LED_GPIO=8`
- `CONFIG_EXAMPLE_LED_ACTIVE_LOW=n`

## Build en flash

Vanaf repository root:

```bash
./scripts/build.sh examples/led esp32c6
./scripts/flash.sh examples/led /dev/ttyUSB0
./scripts/monitor.sh /dev/ttyUSB0 examples/led
```

## Matter over Thread

Voor volledige end-to-end tests heb je een Thread Border Router nodig.
