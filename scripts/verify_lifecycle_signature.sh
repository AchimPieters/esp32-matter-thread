#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 2 ]]; then
  echo "Usage: $0 <dist-dir> <public-key.pem>"
  echo "Example: $0 examples/led/dist ./keys/lifecycle_public.pem"
  exit 1
fi

DIST_DIR="$1"
PUBLIC_KEY="$2"
BIN="$DIST_DIR/main.bin"
SIG="$DIST_DIR/main.bin.sig"

if [[ ! -f "$BIN" ]]; then
  echo "[error] Missing firmware: $BIN"
  exit 2
fi
if [[ ! -f "$SIG" ]]; then
  echo "[error] Missing signature: $SIG"
  exit 3
fi
if [[ ! -f "$PUBLIC_KEY" ]]; then
  echo "[error] Missing public key: $PUBLIC_KEY"
  exit 4
fi

BIN_SIZE=$(wc -c < "$BIN")
SIG_SIZE=$(wc -c < "$SIG")

if [[ "$SIG_SIZE" -le 4 ]]; then
  echo "[error] Signature file too small"
  exit 5
fi

SIZE_HEX=$(tail -c 4 "$SIG" | xxd -p -c 4)
SIZE_FROM_SIG=$((16#$SIZE_HEX))

if [[ "$SIZE_FROM_SIG" -ne "$BIN_SIZE" ]]; then
  echo "[error] Size suffix mismatch: sig=$SIZE_FROM_SIG bin=$BIN_SIZE"
  exit 6
fi

TMP_SIG=$(mktemp)
head -c -4 "$SIG" > "$TMP_SIG"

openssl dgst -sha384 -verify "$PUBLIC_KEY" -signature "$TMP_SIG" "$BIN"
rm -f "$TMP_SIG"

echo "[ok] Signature verified and size suffix valid"
