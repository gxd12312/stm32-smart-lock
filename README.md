# STM32 Smart Door Lock

A smart door lock built on STM32 + FreeRTOS, replicating and extending an
open-source professional design. BOM is locked; firmware in active development.

## Features

- Fingerprint unlock (sensor module keeps templates on-device; MCU only
  receives match / no-match)
- NFC card unlock (13.56 MHz frontend, low-power card detection)
- Passcode keypad (capacitive touch, wake-on-touch)
- Motor-driven bolt with lock state machine supervision
- Access logging on-device

## Roadmap

- **BLE phone-as-key** (in progress): LE Secure Connections pairing,
  short-lived single-use unlock tokens, unlock logs and one-time guest
  passcodes synced to a phone app

## Architecture

- `Core/Inc/lock_state.h` — lock state machine (`lock_state_t`)
- `Core/Src/app_tasks.c` — FreeRTOS task layout
- `Core/Src/power.c` — power management: STOP mode, tickless idle,
  per-peripheral load switches
- `docs/low-power.md` — low-power architecture notes
- `docs/security.md` — BLE + on-device security model

## Low-power design (summary)

Nothing polls. The MCU sleeps in STOP mode under FreeRTOS tickless idle;
every power-hungry peripheral sits behind its own load switch and is
physically off by default. Wake-up is interrupt-only: touch keypad,
fingerprint wake pin, and NFC low-power card detection (microamp sniffing
pulses instead of a continuous RF field). Idle budget is a few microamps
plus battery self-discharge.
