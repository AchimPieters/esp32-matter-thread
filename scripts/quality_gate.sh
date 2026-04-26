#!/usr/bin/env bash
set -euo pipefail

echo "[quality] shell syntax"
bash -n scripts/*.sh

echo "[quality] code format"
./scripts/check_format.sh

echo "[quality] required docs"
test -f docs/architecture.md
test -f docs/operations.md
test -f docs/testing.md
test -f SECURITY.md

echo "[quality] required component files"
test -f components/esp32_matter_thread/include/esp32_matter_thread.h
test -f components/esp32_matter_thread/src/esp32_matter_thread.cpp
test -f components/esp32_matter_thread/idf_component.yml

echo "[quality] PASS"
