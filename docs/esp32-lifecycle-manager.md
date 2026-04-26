# Integratie met `esp32-lifecycle-manager`

Deze repository ondersteunt packaging die compatibel is met de firmware-distributieflow van `esp32-lifecycle-manager`.

## Output contract

Voor lifecycle-manager distributie verwacht deze repo onder `examples/<example>/dist/`:

- `main.bin` (app firmware)
- `main.bin.sig` (optioneel, als private key is meegegeven)
- `manifest.json` (metadata: naam, sha256, grootte, timestamp)

## Package genereren

1. Build firmware:

```bash
./scripts/build.sh examples/led esp32c6
```

2. Maak lifecycle package (zonder signatuur):

```bash
./scripts/lifecycle_package.sh examples/led
```

3. Maak lifecycle package met signatuur:

```bash
./scripts/lifecycle_package.sh examples/led ./keys/lifecycle_private.pem
```

## Signatuurformaat

Als een private key is opgegeven:

- `main.bin.sig` wordt gemaakt met `SHA-384` signing via OpenSSL.
- Daarna wordt de firmwaregrootte als 4-byte hex suffix toegevoegd (compatibel met bestaande lifecycle-flow).

## CI / release

Tag-based release workflow (`v*`) bouwt de LED firmware en produceert lifecycle artifacts voor distributie.


## Signature verify

```bash
./scripts/verify_lifecycle_signature.sh examples/led/dist ./keys/lifecycle_public.pem
```
