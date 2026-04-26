# Testing Strategy

## 1. Static checks

- `bash -n scripts/*.sh`
- `shellcheck scripts/*.sh`
- `clang-format --dry-run --Werror` op C/C++ sources

## 2. Build checks

- Dockerized build van `examples/led` op `esp32c6`

## 3. Hardware smoke tests

- flash + monitor
- commissioning op Thread netwerk
- on/off command tests via `chip-tool`

## 4. Regression checklist

- LED toggles betrouwbaar
- reboot persistence (NVS init)
- monitor logs bevatten geen critical errors
