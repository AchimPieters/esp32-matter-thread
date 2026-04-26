#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 2 ]]; then
  echo "Usage: $0 <example-path> <target>"
  echo "Example: $0 examples/led esp32c6"
  exit 1
fi

EXAMPLE_PATH="$1"
TARGET="$2"

# shellcheck source=scripts/_docker.sh
source "$(dirname "$0")/_docker.sh"

run_idf "$EXAMPLE_PATH" bash -lc "idf.py set-target $TARGET && idf.py build"
