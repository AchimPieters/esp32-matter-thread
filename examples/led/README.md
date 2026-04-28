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

## Build en flash (Optie A: direct in `examples/led`)

Ga naar deze map en gebruik direct `idf.py`:

```bash
cd examples/led
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB0 monitor
```

Of gebruik de lokale helper:

```bash
cd examples/led
./noob.sh all /dev/ttyUSB0 esp32c6
```

Voor losse stappen:

```bash
./noob.sh build "" esp32c6
./noob.sh flash /dev/ttyUSB0
./noob.sh monitor /dev/ttyUSB0
```

## Matter over Thread

Voor volledige end-to-end tests heb je een Thread Border Router nodig.

## ESP-IDF compatibiliteit

Deze example gebruikt:

- `idf >= 5.4`
- `espressif/esp_matter == 1.4.0`

Dit is de gestabiliseerde combinatie voor CI (`espressif/idf:v5.4.2`). ESP-IDF `6.0` staat in CI als experimenteel/allowed-failure totdat een aparte, bewezen compatibele dependencyset is vastgelegd.

Aanbevolen schone build-sequentie:

```bash
idf.py fullclean
idf.py set-target esp32c6
idf.py build
```
