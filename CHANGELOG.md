# Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog.

## [Unreleased]

### Added
- Base `esp32_matter_thread` component and LED example.
- Docker-first scripts for build/flash/monitor/menuconfig/clean.
- CI with structure, shell, format and Dockerized build checks.
- Security automation (CodeQL + Trivy + Dependabot).
- Architecture, operations, testing and commissioning docs.
- `development.log` for progress tracking.
- Deep-dive code audit document (`docs/code-audit.md`) with external-consumer roadmap.
- `components/esp32_matter_thread/idf_component.yml` for component-manager consumption.
- Reusable onboarding helpers in component API:
  - `esp32_matter_thread_init_nvs()`
  - `esp32_matter_thread_print_onboarding_codes_thread()`
  - `esp32_matter_thread_default_config()`
  - `esp32_matter_thread_start()`
  - `esp32_matter_thread_start_on_off_light()`
- `scripts/quality_gate.sh` for one-command local quality checks.
- `docs/maturity-scorecard.md` with explicit 100/100 quality criteria/status.

### Changed
- Pinned `espressif/esp_matter` to `1.4.0` for LED example/component compatibility with ESP-IDF v5.4.2.
- Removed obsolete `CONFIG_CHIP_ENABLE_OPENTHREAD` from `examples/led/sdkconfig.defaults`.
- Updated Docker ESP-IDF base image to `espressif/idf:v5.4.2` for CI/runtime alignment.
