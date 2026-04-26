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
