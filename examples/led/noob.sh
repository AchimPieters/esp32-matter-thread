#!/usr/bin/env bash
set -euo pipefail

if ! command -v idf.py >/dev/null 2>&1; then
  echo "[error] idf.py niet gevonden in PATH."
  echo "Run eerst: source \$IDF_PATH/export.sh"
  exit 127
fi

CMD="${1:-all}"
PORT="${2:-}"
TARGET="${3:-esp32c6}"

case "$CMD" in
  build)
    idf.py set-target "$TARGET"
    idf.py build
    ;;
  flash)
    if [[ -z "$PORT" ]]; then
      echo "Usage: $0 flash <serial-port> [target]"
      exit 1
    fi
    idf.py -p "$PORT" flash
    ;;
  monitor)
    if [[ -z "$PORT" ]]; then
      echo "Usage: $0 monitor <serial-port>"
      exit 1
    fi
    idf.py -p "$PORT" monitor
    ;;
  all)
    if [[ -z "$PORT" ]]; then
      echo "Usage: $0 all <serial-port> [target]"
      exit 1
    fi
    idf.py set-target "$TARGET"
    idf.py build
    idf.py -p "$PORT" flash
    idf.py -p "$PORT" monitor
    ;;
  *)
    echo "Usage:"
    echo "  $0 build [unused-port] [target]"
    echo "  $0 flash <serial-port> [target]"
    echo "  $0 monitor <serial-port>"
    echo "  $0 all <serial-port> [target]"
    exit 1
    ;;
esac
