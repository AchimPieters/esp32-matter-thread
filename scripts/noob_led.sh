#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <serial-port>"
  echo "Example: $0 /dev/ttyUSB0"
  exit 1
fi

PORT="$1"

echo "[1/4] Running doctor check"
./scripts/doctor.sh

echo "[2/4] Building examples/led for esp32c6"
./scripts/build.sh examples/led esp32c6

echo "[3/4] Flashing to $PORT"
./scripts/flash.sh examples/led "$PORT"

echo "[4/4] Starting monitor"
./scripts/monitor.sh "$PORT" examples/led
