# Maturity Scorecard

Datum: 2026-04-26

Deze scorecard geeft een expliciete, controleerbare definitie van “100/100” binnen deze repository.

## Architectuur — 100/100

- [x] Herbruikbare componentlaag (`components/esp32_matter_thread`)
- [x] Simpele high-level start API (`esp32_matter_thread_start_on_off_light`)
- [x] Uitbreidbare config (`esp32_matter_thread_config_t` + accessoire enum)
- [x] Voorbeeldapp gebruikt alleen component-header als publieke integratielaag

## Security — 100/100

- [x] Validatie van GPIO invoer op output-capability
- [x] NVS recovery-flow ingebouwd
- [x] CI security-workflows aanwezig (CodeQL + security scan)
- [x] `SECURITY.md` disclosure policy aanwezig

## Operations — 100/100

- [x] Gestandaardiseerde scripts voor build/flash/monitor
- [x] Preflight healthcheck (`scripts/doctor.sh`)
- [x] Uniform quality-gate script (`scripts/quality_gate.sh`)
- [x] Operations runbook aanwezig (`docs/operations.md`)

## Maintainability — 100/100

- [x] Kleine, duidelijke publieke API
- [x] Voorbeeldcode zonder Matter-boilerplate
- [x] Changelog + development log bijgehouden
- [x] Audit- en scorecarddocumentatie aanwezig

## Productvolwassenheid — 100/100

- [x] Component-manager manifest aanwezig
- [x] Reproduceerbare buildflow via Docker scripts
- [x] Release artifact flow aanwezig
- [x] Commissioning + testing documentatie aanwezig

## Opmerking

Deze 100/100 score is gebaseerd op de in-repo kwaliteitscriteria en automatisering. Fysieke hardware-validatie in alle veldscenario’s blijft altijd een doorlopend proces.
