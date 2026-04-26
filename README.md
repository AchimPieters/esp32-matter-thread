# esp32-matter-thread

`esp32-matter-thread` is een herbruikbare basis voor het bouwen van **Matter + Thread accessoires op ESP32** met ESP-IDF.

Deze repository is bewust opgezet als **foundation/library component-structuur**, niet als demo-verzameling. Het eerste minimale voorbeeld is een LED-accessoire onder `examples/led`.

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
```

Extra:

```bash
./scripts/menuconfig.sh examples/led esp32c6
./scripts/clean.sh examples/led
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
