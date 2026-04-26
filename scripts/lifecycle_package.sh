#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <example-path> [private-key.pem]"
  echo "Example: $0 examples/led ./keys/lifecycle_private.pem"
  exit 1
fi

EXAMPLE_PATH="$1"
PRIVATE_KEY="${2:-}"
BUILD_DIR="$EXAMPLE_PATH/build"
DIST_DIR="$EXAMPLE_PATH/dist"

if [[ ! -d "$BUILD_DIR" ]]; then
  echo "[error] Build directory not found: $BUILD_DIR"
  echo "Run build first: ./scripts/build.sh $EXAMPLE_PATH esp32c6"
  exit 2
fi

mkdir -p "$DIST_DIR"

APP_BIN=$(find "$BUILD_DIR" -maxdepth 1 -type f -name '*.bin' \
  ! -name 'bootloader.bin' \
  ! -name 'partition-table.bin' \
  ! -name 'ota_data_initial.bin' \
  -printf '%s %p\n' | sort -nr | head -n 1 | awk '{print $2}')

if [[ -z "$APP_BIN" ]]; then
  echo "[error] Could not locate application binary in $BUILD_DIR"
  exit 3
fi

cp "$APP_BIN" "$DIST_DIR/main.bin"

SHA256=$(sha256sum "$DIST_DIR/main.bin" | awk '{print $1}')
SIZE=$(wc -c < "$DIST_DIR/main.bin")

cat > "$DIST_DIR/manifest.json" <<JSON
{
  "name": "$(basename "$EXAMPLE_PATH")",
  "binary": "main.bin",
  "sha256": "$SHA256",
  "size": $SIZE,
  "generated_at_utc": "$(date -u +%Y-%m-%dT%H:%M:%SZ)"
}
JSON

if [[ -n "$PRIVATE_KEY" ]]; then
  if [[ ! -f "$PRIVATE_KEY" ]]; then
    echo "[error] Private key not found: $PRIVATE_KEY"
    exit 4
  fi

  openssl dgst -sha384 -sign "$PRIVATE_KEY" -out "$DIST_DIR/main.bin.sig" "$DIST_DIR/main.bin"
  printf "%08x" "$SIZE" | xxd -r -p >> "$DIST_DIR/main.bin.sig"
  echo "[ok] Signed firmware: $DIST_DIR/main.bin.sig"
else
  echo "[warn] No private key provided. Skipping signature generation."
fi

echo "[ok] Lifecycle package created in $DIST_DIR"
ls -lh "$DIST_DIR"
