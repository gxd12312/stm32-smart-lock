#ifndef LOCK_STATE_H
#define LOCK_STATE_H

/* Door lock state machine.
 *
 * LOCK_SLEEP is the resting state: MCU in STOP mode, all peripheral
 * rails gated off by their load switches. Any wake interrupt moves the
 * machine to LOCK_WAKE, authentication runs in LOCK_AUTH, and the bolt
 * is only driven inside the LOCK_UNLOCKING window supervised by the
 * motor task. After the open timeout the lock re-locks itself.
 */
typedef enum {
    LOCK_SLEEP,      /* stop mode, peripherals gated off */
    LOCK_WAKE,       /* interrupt wake, rails on          */
    LOCK_AUTH,       /* fingerprint / nfc / passcode      */
    LOCK_UNLOCKING,  /* motor drive window                */
    LOCK_OPEN,
    LOCK_RELOCK
} lock_state_t;

typedef enum {
    EVT_WAKE_TOUCH,
    EVT_WAKE_FINGER,
    EVT_WAKE_NFC_FIELD,
    EVT_AUTH_OK,
    EVT_AUTH_FAIL,
    EVT_MOTOR_DONE,
    EVT_OPEN_TIMEOUT,
    EVT_BLE_UNLOCK_CMD
} lock_event_t;

void LockState_Init(void);
void LockState_Dispatch(lock_event_t evt);
lock_state_t LockState_Current(void);

#endif /* LOCK_STATE_H */
