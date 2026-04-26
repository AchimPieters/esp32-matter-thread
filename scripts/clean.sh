#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <example-path>"
  echo "Example: $0 examples/led"
  exit 1
fi

EXAMPLE_PATH="$1"

# shellcheck source=scripts/_docker.sh
source "$(dirname "$0")/_docker.sh"

run_idf "$EXAMPLE_PATH" bash -lc "idf.py fullclean"
