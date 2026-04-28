# Troubleshooting

## Docker

### `docker: command not found`
- Installeer Docker Engine/Desktop.
- Heropen shell sessie.
- Controleer met: `docker --version`.

### Permission denied op Docker socket
- Voeg gebruiker toe aan docker groep (`sudo usermod -aG docker $USER`).
- Log uit/in.

## Build

### `Build directory not found`
- Run eerst: `./scripts/build.sh examples/led esp32c6`.

### esp_matter dependency resolve errors
- Controleer internettoegang in container.
- Draai clean: `./scripts/clean.sh examples/led`.
- Build opnieuw.

## Flash / serial

### `/dev/ttyUSB0` bestaat niet
- Controleer USB-kabel en board power.
- Controleer poort met `dmesg | tail` of `ls /dev/ttyUSB*`.

### Flash timeout
- Houd BOOT knop ingedrukt tijdens reset/flash (board-afhankelijk).

## Matter / Thread

### Pairing timeout
- Controleer Thread Border Router health.
- Controleer dataset/passcode/discriminator.

### Commands werken, LED reageert niet
- Controleer `CONFIG_EXAMPLE_LED_GPIO`.
- Controleer `CONFIG_EXAMPLE_LED_ACTIVE_LOW`.

### `#error "REQUIRED: CHIP_SYSTEM_CONFIG_USE_LWIP ..."`
- Oorzaak: CHIP system backend macro niet actief tijdens build van `connectedhomeip`.
- Fix in deze repo:
  - `examples/led/CMakeLists.txt` forceert `CHIP_SYSTEM_CONFIG_USE_LWIP=1` via `idf_build_set_property(COMPILE_DEFINITIONS ...)`.
  - dependency geüpdatet naar `espressif/esp_matter ==1.4.2~1`.

### `std::to_underlying` compile errors
- Oorzaak: bekende incompatibiliteit in oudere `esp_matter` componentversies met C++23 builds.
- Fix in deze repo:
  - upgrade naar `espressif/esp_matter ==1.4.2~1` (patchlijn bevat fix voor `to_underlying` regressie in `1.4.0~1` changelog en latere 1.4.x updates).

Aanbevolen schone reproduceerflow:

```bash
idf.py fullclean
idf.py set-target esp32c6
idf.py build
```
