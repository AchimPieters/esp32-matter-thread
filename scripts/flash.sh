#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 2 ]]; then
  echo "Usage: $0 <example-path> <serial-port>"
  echo "Example: $0 examples/led /dev/ttyUSB0"
  exit 1
fi

EXAMPLE_PATH="$1"
SERIAL_PORT="$2"

# shellcheck source=scripts/_docker.sh
source "$(dirname "$0")/_docker.sh"

run_idf_with_device "$EXAMPLE_PATH" "$SERIAL_PORT" \
  bash -lc "idf.py -p $SERIAL_PORT flash"
