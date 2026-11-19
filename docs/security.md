# Security model

## BLE phone-as-key

- **LE Secure Connections only**: ECDH pairing, AES-CCM link
  encryption. No legacy pairing, no static passkeys.
- The phone never holds a permanent credential. Unlock tokens are
  **short-lived, single-use**, and protected against replay with a
  monotonic counter.
- Guest passcodes **expire**; failed attempts are rate-limited and
  then locked out.

## On-device

- Keys stored in **write-protected flash**; debug port locked down.
- Firmware updates are **signature-checked** — unsigned images do not
  boot.
- Fingerprint templates **never leave the sensor module**; the MCU
  only ever sees match / no-match.
- Failed authentication attempts are counted and written to the
  on-device access log.
