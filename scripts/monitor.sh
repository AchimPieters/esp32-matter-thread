#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <serial-port> [example-path]"
  echo "Example: $0 /dev/ttyUSB0 examples/led"
  exit 1
fi

SERIAL_PORT="$1"
EXAMPLE_PATH="${2:-examples/led}"

# shellcheck source=scripts/_docker.sh
source "$(dirname "$0")/_docker.sh"

run_idf_with_device "$EXAMPLE_PATH" "$SERIAL_PORT" \
  bash -lc "idf.py -p $SERIAL_PORT monitor"
