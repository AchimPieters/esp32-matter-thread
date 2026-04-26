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
