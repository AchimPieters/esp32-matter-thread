# Architecture

## Goals

- Reusable ESP-IDF component base for Matter + Thread accessories.
- ESP32-C6 as first-class target.
- Docker-first developer workflow.

## Layers

1. `components/esp32_matter_thread`
   - hardware-adjacent reusable logic (e.g. LED driver)
2. `examples/<accessory>`
   - product composition, Matter endpoints, callbacks
3. `scripts/`
   - operational entrypoints for build/flash/monitor
4. `docker/`
   - pinned reproducible toolchain container

## Design principles

- Keep component API small and stable.
- Examples show integration patterns, not framework complexity.
- Security and operations defaults should be safe and explicit.
