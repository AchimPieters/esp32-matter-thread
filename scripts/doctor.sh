#!/usr/bin/env bash
set -euo pipefail

SERIAL_PORT="${1:-}"

echo "[doctor] Checking docker"
if command -v docker >/dev/null 2>&1; then
  echo "[ok] docker: $(docker --version)"
else
  echo "[fail] docker not found"
  exit 1
fi

echo "[doctor] Checking repository layout"
test -d examples/led && echo "[ok] examples/led exists"
test -f examples/led/main/main.cpp && echo "[ok] examples/led/main/main.cpp exists"

echo "[doctor] Checking shell scripts"
bash -n scripts/*.sh
echo "[ok] bash syntax"

if [[ -n "$SERIAL_PORT" ]]; then
  echo "[doctor] Checking serial port: $SERIAL_PORT"
  if [[ -e "$SERIAL_PORT" ]]; then
    echo "[ok] serial port found"
  else
    echo "[warn] serial port not found"
  fi
fi
