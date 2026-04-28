# esp32-matter-thread

`esp32-matter-thread` is een herbruikbare basis voor het bouwen van **Matter + Thread accessoires op ESP32** met ESP-IDF.

Deze repository is bewust opgezet als **foundation/library component-structuur**, niet als demo-verzameling. Het eerste minimale voorbeeld is een LED-accessoire onder `examples/led`.

## Gebruik als dependency in een externe ESP-IDF repo

Net als `esp32-homekit` kun je deze repository als component-afhankelijkheid gebruiken via de IDF Component Manager.

In jouw project (bijv. `main/idf_component.yml`):

```yaml
dependencies:
  achimpieters/esp32-matter-thread: ">=0.1.0"
```

Daarna kun je in je code direct gebruiken:

```cpp
#include "esp32_matter_thread.h"
```

En onboarding (QR + manual code) automatisch printen met:

```cpp
esp32_matter_thread_config_t cfg = esp32_matter_thread_default_config();
cfg.accessory_type = ESP32_MATTER_THREAD_ACCESSORY_ON_OFF_LIGHT;
cfg.primary_gpio = 8;
cfg.primary_gpio_active_low = false;
cfg.print_onboarding_codes = true;
ESP_ERROR_CHECK(esp32_matter_thread_start(&cfg));
```

## Doel van deze repository

- Basiscomponent: `esp32_matter_thread`
- Eerste target: **ESP32-C6**
- Voorbereid op **Matter over Thread**
- Makkelijk uit te breiden met nieuwe accessoires (switch, sensor, outlet, button, etc.)

## Vereisten

- Docker
- Toegang tot USB-seriële poort (bijv. `/dev/ttyUSB0`)
- ESP32-C6 board
- Voor echte Matter-over-Thread tests: een Thread Border Router

## Ondersteunde ESP-IDF versies

- **Primair ondersteund:** ESP-IDF `5.4.x` (CI bouwt met `espressif/idf:v5.4.2`, `esp_matter==1.4.0` en lokale compat-override voor `esp_encrypted_img@2.1.0`).
- **ESP-IDF `6.0`:** experimenteel in CI; gebruikt een lokale compat component `components/json` (backed by `cjson`) en managed `espressif/mqtt` voor legacy dependency-naamresolutie in deze buildflow.
- **< 5.4:** niet ondersteund door de huidige LED-example minimumconstraint (`idf >=5.4`).

> Je hoeft lokaal geen ESP-IDF, Python dependencies of Matter toolchain te installeren.

## Repositorystructuur

```text
esp32-matter-thread/
  components/
    esp32_matter_thread/
      CMakeLists.txt
      include/
        esp32_matter_thread.h
      src/
        esp32_matter_thread.cpp
  examples/
    led/
      CMakeLists.txt
      main/
        CMakeLists.txt
        idf_component.yml
        main.cpp
      sdkconfig.defaults
      README.md
  docker/
    Dockerfile
  scripts/
    _docker.sh
    build.sh
    flash.sh
    monitor.sh
    menuconfig.sh
    clean.sh
  CMakeLists.txt
  README.md
  LICENSE
  CHANGELOG.md
  .gitignore
```

## Docker workflow

De scripts bouwen automatisch de image `esp32-matter-thread-idf:latest` op basis van `docker/Dockerfile` (indien nog niet aanwezig), en voeren daarna de IDF-commands uit in de container.

## Build, flash, monitor

Vanaf repository root:

```bash
./scripts/build.sh examples/led esp32c6
./scripts/flash.sh examples/led /dev/ttyUSB0
./scripts/monitor.sh /dev/ttyUSB0 examples/led
./scripts/noob_led.sh /dev/ttyUSB0
```

Extra:

```bash
./scripts/menuconfig.sh examples/led esp32c6
./scripts/clean.sh examples/led
./scripts/check_format.sh
./scripts/quality_gate.sh
./scripts/lifecycle_package.sh examples/led
./scripts/verify_lifecycle_signature.sh examples/led/dist ./keys/lifecycle_public.pem
./scripts/new_example.sh my_accessory
```


## CI

GitHub Actions draait een basis CI-pipeline die controleert:

- verplichte structuur (incl. `examples/led`)
- shell script syntax
- Docker build van `examples/led` voor `esp32c6`

Workflowbestand: `.github/workflows/ci.yml`.

## LED voorbeeld

Het LED voorbeeld onder `examples/led`:

- Maakt een Matter `On/Off Light` endpoint
- Koppelt de `OnOff` attribute aan een fysieke GPIO LED
- Is bedoeld als functionele baseline voor build/flash/monitor en Matter init op ESP32-C6
- Print automatisch QR/Matter onboarding code in serial output na startup

GPIO en polarity zijn configureerbaar via `menuconfig`:

- `LED Matter Example Configuration -> LED GPIO`
- `LED Matter Example Configuration -> LED is active-low`

Standaardwaarden:

- `CONFIG_EXAMPLE_LED_GPIO=8`
- `CONFIG_EXAMPLE_LED_ACTIVE_LOW=n`

## Nieuwe accessoires toevoegen

Aanpak voor volgende accessoires:

1. Voeg hardware-driver/logica toe in `components/esp32_matter_thread` (of subcomponenten)
2. Voeg een nieuw example toe onder `examples/<accessory>`
3. Maak Matter endpoint + attributes in dat example
4. Koppel attribute callbacks naar de device driver

Houd de eerste implementaties klein en functioneel; breid abstrahering pas uit wanneer meerdere accessoires dezelfde patronen delen.


## Ontwikkelvoortgang

Voor voortgang en openstaande taken, zie `development.log`.

## Validatie

Lokale checks:

```bash
bash -n scripts/*.sh
```

CI checks (`.github/workflows/ci.yml`):

- structuurchecks (incl. `examples/led`)
- shell syntax check
- Dockerized `idf.py build` voor `examples/led` op `esp32c6`


## Architecture

Architectuurdocumentatie staat in `docs/architecture.md`.

## Security

Zie `SECURITY.md` voor responsible disclosure en security-baseline.

## Operations

Zie `docs/operations.md` voor runbook en incident handling.
Gebruik `./scripts/doctor.sh` als snelle preflight check.

## Maintainability

- `development.log` houdt voortgang en backlog actueel.
- `CONTRIBUTING.md` beschrijft contribution workflow.
- CI valideert structuur, shellkwaliteit en Dockerized build.

## Productvolwassenheid (huidige status)

Deze repository is nu een sterke en bruikbare basis. Voor echte productievolwassenheid op 100/100 zijn blijvende hardware-validatie, release signing en langdurige veldtesten nog nodig.


## Commissioning

Zie `docs/commissioning.md` voor chip-tool onboarding en command voorbeelden.

## Code audit

Zie `docs/code-audit.md` voor een uitgebreide deep-dive audit en concrete verbeter/roadmap voor volledig automatische consumptie van dit component in andere repositories.

## Maturity scorecard

Zie `docs/maturity-scorecard.md` voor de 100/100 kwaliteitscriteria en status per domein (architectuur/security/operations/maintainability/productvolwassenheid).

## Testing

Zie `docs/testing.md` voor static/build/hardware teststrategie.

## Releases

- Tag releases als `vX.Y.Z` om de release-build workflow te triggeren.
- Wijzigingen worden bijgehouden in `CHANGELOG.md`.


## Compatibiliteit met esp32-lifecycle-manager

Deze repository kan lifecycle-compatible firmware artifacts genereren (`main.bin`, `manifest.json`, optioneel `main.bin.sig`) voor distributie via `esp32-lifecycle-manager`.

Zie `docs/esp32-lifecycle-manager.md` voor de volledige flow.


## Troubleshooting

Zie `docs/troubleshooting.md` voor veelvoorkomende fouten en oplossingen.


## Beginner handleiding

Voor een volledige stap-voor-stap uitleg (build, flash, monitor en koppelen met iPhone Home), zie `NOOB.md`.
