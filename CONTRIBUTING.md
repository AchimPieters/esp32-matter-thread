# Contributing

## Workflow

1. Update `development.log` before and after meaningful changes.
2. Keep changes small and focused.
3. Run local checks before opening a PR.

## Local checks

```bash
bash -n scripts/*.sh
./scripts/doctor.sh
```

## Coding rules

- Keep naming consistent with `esp32_matter_thread`.
- Do not over-engineer abstractions before real reuse exists.
- Prefer explicit error handling and clear logs.

## Pull requests

Include:

- what changed
- why
- validation output
- known limitations
