#!/usr/bin/env bash
set -euo pipefail

if ! command -v clang-format >/dev/null 2>&1; then
  echo "clang-format not found"
  exit 1
fi

FILES=$(find components examples -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \))

if [[ -z "$FILES" ]]; then
  echo "No source files found"
  exit 0
fi

clang-format --dry-run --Werror $FILES
echo "Format check passed"
