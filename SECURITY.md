# Security Policy

## Supported scope

This project currently supports the `main` branch and latest release tag.

## Reporting a vulnerability

Please do **not** open public issues for security vulnerabilities.

Report via private disclosure to the repository owner, including:

- affected commit/tag
- impact
- reproduction steps
- possible fix

We aim to acknowledge reports within 7 days.

## Security baseline

- Dockerized build environment to reduce host toolchain drift.
- CI includes static shell checks and CodeQL for C/C++.
- Docker runs with `--security-opt=no-new-privileges` in helper scripts.
- Serial device access is explicit and opt-in via `--device`.

## Current limitations

- Hardware security validation is not yet automated.
- No signed release artifacts yet.
