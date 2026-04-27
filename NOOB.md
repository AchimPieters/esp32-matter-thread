# NOOB.md — Stap-voor-stap (ESP32 Matter LED + iPhone)

Dit document is voor beginners. Volg alles letterlijk.

---

## 0) Wat je nodig hebt

1. **Computer met Docker** (Mac/Linux/Windows met WSL2).
2. **ESP32-C6 board** + USB kabel.
3. **iPhone** met de **Woning (Home) app**.
4. **Thread Border Router** (bijv. HomePod mini of Apple TV 4K met Thread).
5. Deze repository lokaal gekloond.

> Zonder Thread Border Router kun je Matter-over-Thread niet volledig koppelen in Apple Home.

---

## 1) Repository openen

Open terminal in de root van deze repo.

Voorbeeld:

```bash
cd /pad/naar/esp32-matter-thread
```

Controleer of je op de juiste plek staat:

```bash
pwd
```

Je moet mapnamen zien zoals `examples`, `scripts`, `docker`.

---

## 2) Naar LED voorbeeld-map gaan (Optie A)

```bash
cd examples/led
```

## 3) Preflight check

Run:

```bash
../../scripts/doctor.sh
```

Als dit faalt met `docker not found`:
- installeer Docker
- herstart terminal
- run opnieuw

---

## 4) Bouw de firmware (LED voorbeeld)

Run:

```bash
idf.py set-target esp32c6
idf.py build
```

Wacht tot de build klaar is.

---

## 5) Zoek je seriële poort

### Linux

```bash
ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null
```

### macOS

```bash
ls /dev/cu.usb* /dev/tty.usb*
```

Kies de juiste poort (voorbeeld: `/dev/ttyUSB0` of `/dev/cu.usbserial-0001`).

---

## 6) Flash naar ESP32-C6

Gebruik jouw poort:

```bash
idf.py -p /dev/ttyUSB0 flash
```

Als flash faalt:
- druk BOOT knop in tijdens reset (board-afhankelijk)
- probeer opnieuw

---

## 7) Open serial monitor

```bash
idf.py -p /dev/ttyUSB0 monitor
```

In de logs moet je o.a. onboarding info zien:
- Matter QR onboarding payload
- Manual pairing code

Laat deze terminal open.

---

## 8) Koppelen met iPhone (Apple Home)

1. Open **Woning (Home)** app.
2. Tik op **+** → **Voeg accessoire toe**.
3. Scan de Matter QR-code.
   - Als je geen visuele QR hebt, gebruik de **manual code** uit de serial logs.
4. Volg wizard (ruimte kiezen, naam kiezen).
5. Na koppelen verschijnt het apparaat als **lamp** (On/Off).

---

## 9) Testen of het werkt

In Home app:
- Zet lamp **aan** → LED moet aan.
- Zet lamp **uit** → LED moet uit.

Als omgekeerd gedrag:
- zet `CONFIG_EXAMPLE_LED_ACTIVE_LOW=y` via menuconfig.

---

## 10) LED GPIO veranderen (optioneel)

Run:

```bash
idf.py menuconfig
```

Ga naar:
- `LED Matter Example Configuration -> LED GPIO`
- `LED Matter Example Configuration -> LED is active-low`

Sla op, build opnieuw, flash opnieuw.

---

## 11) Snelle foutoplossing

- **docker not found** → Docker installeren.
- **serial port not found** → andere kabel/poort proberen.
- **pairing timeout** → check Thread Border Router en netwerk.
- **geen QR/manual code in log** → monitor opnieuw starten, board resetten.

Zie ook: `docs/troubleshooting.md`.

---

## 12) Volledige beginner workflow (copy/paste)

> Vervang `/dev/ttyUSB0` door jouw poort.

```bash
cd examples/led
../../scripts/doctor.sh
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB0 monitor
```

Daarna: koppelen in iPhone Home app.
