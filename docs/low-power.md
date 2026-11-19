# Low-power architecture

Principle: **nothing polls; everything is event-driven.**

- The STM32 sits in **STOP mode** with FreeRTOS **tickless idle**
  (`configUSE_TICKLESS_IDLE = 1`).
- Every hungry peripheral is behind its own **load switch** —
  fingerprint sensor, NFC frontend, BLE module, motor rail — all
  physically powered off by default.
- Wake-up sources are **interrupts only**:
  - capacitive touch keypad (wake on finger proximity),
  - fingerprint module wake pin,
  - NFC frontend in **low-power card detection (LPCD)** mode: microamp
    sniffing pulses every few hundred ms instead of a continuous RF
    field; full field only when a card is present.
- BLE is duty-cycled the same way: long advertising intervals, radio
  asleep between them, wakes on connection.

Idle budget: a few microamps of sleep current plus battery
self-discharge, until a human touches the lock. A full wake cycle —
authenticate, drive motor, log — completes in under a second, then the
system returns to LOCK_SLEEP and all rails drop.
