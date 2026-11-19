#include "lock_state.h"

/* Power management.
 *
 * Every power-hungry peripheral sits behind its own load switch:
 *   RAIL_FINGER  - fingerprint sensor
 *   RAIL_NFC     - NFC frontend
 *   RAIL_BLE     - BLE module
 *   RAIL_MOTOR   - motor H-bridge
 * All rails are OFF by default. The power task enables a rail only
 * while the state machine is outside LOCK_SLEEP, and drops them all
 * on the transition back.
 *
 * The NFC frontend never polls at full power: in sleep it runs
 * low-power card detection (LPCD), sniffing with microamp pulses
 * every few hundred ms, and only energises the full RF field when a
 * card is actually present (EVT_WAKE_NFC_FIELD).
 *
 * Kernel side: configUSE_TICKLESS_IDLE = 1, MCU enters STOP mode
 * whenever all tasks are blocked.
 */

typedef enum {
    RAIL_FINGER,
    RAIL_NFC,
    RAIL_BLE,
    RAIL_MOTOR
} power_rail_t;

static void Rail_Set(power_rail_t rail, int on)
{
    /* TODO: drive the load-switch GPIO for this rail */
    (void)rail; (void)on;
}

void Power_OnWake(void)
{
    Rail_Set(RAIL_FINGER, 1);
    Rail_Set(RAIL_NFC, 1);
    Rail_Set(RAIL_BLE, 1);
}

void Power_OnSleep(void)
{
    Rail_Set(RAIL_FINGER, 0);
    Rail_Set(RAIL_NFC, 0);
    Rail_Set(RAIL_BLE, 0);
    Rail_Set(RAIL_MOTOR, 0);
}

void Power_MotorRail(int on)
{
    Rail_Set(RAIL_MOTOR, on);
}
