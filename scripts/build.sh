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

run_idf "$EXAMPLE_PATH" bash -lc "export HOME=\"\${HOME:-/tmp/esp-home}\"; mkdir -p \"\$HOME\"; touch \"\$HOME/.gitconfig\"; git config --global --add safe.directory /opt/esp/idf || true; git config --global --add safe.directory /opt/esp/idf/components/openthread/openthread || true; git config --global --add safe.directory /workspace || true; idf.py set-target $TARGET && idf.py build"
