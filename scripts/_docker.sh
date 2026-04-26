#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
IMAGE_NAME="esp32-matter-thread-idf:latest"

_docker_tty_args() {
  if [[ -t 0 && -t 1 ]]; then
    echo "-it"
  fi
}

ensure_image() {
  if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo "[docker] Building image: $IMAGE_NAME"
    docker build -f "$REPO_ROOT/docker/Dockerfile" -t "$IMAGE_NAME" "$REPO_ROOT"
  fi
}

run_idf() {
  local example_path="$1"
  shift

  ensure_image

  docker run --rm $(_docker_tty_args) \
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

  ensure_image

  docker run --rm $(_docker_tty_args) \
    -u "$(id -u):$(id -g)" \
    --device "$serial_port" \
    -v "$REPO_ROOT:/workspace" \
    -w "/workspace/$example_path" \
    "$IMAGE_NAME" \
    "$@"
}
