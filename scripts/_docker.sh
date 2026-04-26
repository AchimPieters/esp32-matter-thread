#!/usr/bin/env bash
set -euo pipefail

readonly REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readonly IMAGE_NAME="esp32-matter-thread-idf:latest"

_docker_tty_args() {
  if [[ -t 0 && -t 1 ]]; then
    echo "-it"
  fi
}

require_docker() {
  if ! command -v docker >/dev/null 2>&1; then
    echo "[error] docker binary not found. Install Docker first." >&2
    exit 127
  fi
}

validate_example_path() {
  local example_path="$1"
  if [[ ! -d "$REPO_ROOT/$example_path" ]]; then
    echo "[error] example path not found: $example_path" >&2
    exit 2
  fi
}

ensure_image() {
  require_docker
  if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo "[docker] Building image: $IMAGE_NAME"
    docker build -f "$REPO_ROOT/docker/Dockerfile" -t "$IMAGE_NAME" "$REPO_ROOT"
  fi
}

run_idf() {
  local example_path="$1"
  shift

  validate_example_path "$example_path"
  ensure_image

  docker run --rm $(_docker_tty_args) \
    --security-opt=no-new-privileges \
    -u "$(id -u):$(id -g)" \
    -v "$REPO_ROOT:/workspace" \
    -w "/workspace/$example_path" \
    "$IMAGE_NAME" \
    "$@"
}

run_idf_with_device() {
  local example_path="$1"
  local serial_port="$2"
  shift 2

  validate_example_path "$example_path"

  if [[ ! -e "$serial_port" ]]; then
    echo "[error] serial device not found: $serial_port" >&2
    exit 3
  fi

  ensure_image

  docker run --rm $(_docker_tty_args) \
    --security-opt=no-new-privileges \
    -u "$(id -u):$(id -g)" \
    --device "$serial_port" \
    -v "$REPO_ROOT:/workspace" \
    -w "/workspace/$example_path" \
    "$IMAGE_NAME" \
    "$@"
}
