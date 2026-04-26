# Commissioning Guide (Matter over Thread)

## Benodigd

- ESP32-C6 board met deze firmware
- Thread Border Router (bijv. HomePod mini, Nest Hub, OpenThread BR)
- Controller met `chip-tool`

## Device opstarten

1. Flash de firmware:
   ```bash
   ./scripts/build.sh examples/led esp32c6
   ./scripts/flash.sh examples/led /dev/ttyUSB0
   ./scripts/monitor.sh /dev/ttyUSB0 examples/led
   ```
2. Wacht op commissioning-ready logs in serial output.

## Pairing (voorbeeld met chip-tool)

> Vervang setup passcode/discriminator met de waarden uit jouw device-output.

### Thread onboarding

```bash
chip-tool pairing code-thread 0x1234 <SETUP_CODE> <OPERATIONAL_DATASET_HEX>
```

### On/Off cluster testen

```bash
chip-tool onoff on 0x1234 1
chip-tool onoff off 0x1234 1
chip-tool onoff toggle 0x1234 1
```

## Troubleshooting

- Pairing timeout:
  - controleer Border Router status
  - controleer dataset
- Device niet vindbaar:
  - reboot device
  - factory reset commissioning state
- Attribute updates zichtbaar, LED reageert niet:
  - check `CONFIG_EXAMPLE_LED_GPIO`
  - check `CONFIG_EXAMPLE_LED_ACTIVE_LOW`
