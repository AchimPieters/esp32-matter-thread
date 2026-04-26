# LED Matter + Thread Example

Dit voorbeeld is de minimale validatie voor de basis van `esp32-matter-thread`.

## Wat doet dit voorbeeld?

- Initialiseerd ESP-Matter.
- Maakt een **On/Off Light** endpoint.
- Koppelt de Matter `OnOff` attribute aan een fysieke LED GPIO.
- Is bedoeld als quick check voor build/flash/monitor en Matter initialisatie op ESP32-C6.

## GPIO aanpassen

Standaard staat de LED op GPIO `8`.

Pas in `main/main.cpp` de waarde van `kDefaultLedGpio` aan.

## Build en flash

Vanaf repository root:

```bash
./scripts/build.sh examples/led esp32c6
./scripts/flash.sh examples/led /dev/ttyUSB0
./scripts/monitor.sh /dev/ttyUSB0 examples/led
```

## Let op

Voor volledige Matter-over-Thread end-to-end tests heb je een Thread Border Router nodig.
