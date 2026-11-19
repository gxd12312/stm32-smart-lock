#include "lock_state.h"

static lock_state_t s_state = LOCK_SLEEP;

void LockState_Init(void)
{
    s_state = LOCK_SLEEP;
}

lock_state_t LockState_Current(void)
{
    return s_state;
}

void LockState_Dispatch(lock_event_t evt)
{
    switch (s_state) {
    case LOCK_SLEEP:
        if (evt == EVT_WAKE_TOUCH || evt == EVT_WAKE_FINGER ||
            evt == EVT_WAKE_NFC_FIELD) {
            s_state = LOCK_WAKE;   /* power task enables the rails */
        } else if (evt == EVT_BLE_UNLOCK_CMD) {
            s_state = LOCK_AUTH;   /* token already checked by BLE task */
        }
        break;

    case LOCK_WAKE:
        s_state = LOCK_AUTH;
        break;

    case LOCK_AUTH:
        if (evt == EVT_AUTH_OK) {
            s_state = LOCK_UNLOCKING;
        } else if (evt == EVT_AUTH_FAIL) {
            s_state = LOCK_SLEEP;  /* failed attempts are counted + logged */
        }
        break;

    case LOCK_UNLOCKING:
        if (evt == EVT_MOTOR_DONE) {
            s_state = LOCK_OPEN;
        }
        break;

    case LOCK_OPEN:
        if (evt == EVT_OPEN_TIMEOUT) {
            s_state = LOCK_RELOCK;
        }
        break;

    case LOCK_RELOCK:
        if (evt == EVT_MOTOR_DONE) {
            s_state = LOCK_SLEEP;
        }
        break;
    }
}
