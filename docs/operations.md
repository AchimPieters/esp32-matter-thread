# Operations Runbook

## Prerequisites

- Docker installed and working
- USB access to ESP32-C6 board
- Thread Border Router for full Matter-over-Thread validation

## Health check

```bash
./scripts/doctor.sh /dev/ttyUSB0
```

## Build / Flash / Monitor

```bash
./scripts/build.sh examples/led esp32c6
./scripts/flash.sh examples/led /dev/ttyUSB0
./scripts/monitor.sh /dev/ttyUSB0 examples/led
```

## Failure handling

- If Docker missing: install Docker Desktop / Docker Engine.
- If serial port missing: check cable, permissions, and dmesg.
- If build fails after deps change: `./scripts/clean.sh examples/led` then rebuild.
