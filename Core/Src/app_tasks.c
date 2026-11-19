#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS task layout.
 *
 * Priorities are deliberate: the motor task is highest because the bolt
 * drive window is time-critical and must never be preempted mid-drive.
 * The power task is lowest — it mostly sleeps alongside the kernel's
 * tickless idle and only acts on state transitions.
 */
void AppTasks_Create(void)
{
    xTaskCreate(vFingerprintTask, "finger", 512, NULL, 3, NULL);
    xTaskCreate(vNfcTask,         "nfc",    384, NULL, 2, NULL);
    xTaskCreate(vKeypadTask,      "keypad", 256, NULL, 2, NULL);
    xTaskCreate(vMotorTask,       "motor",  256, NULL, 4, NULL);
    xTaskCreate(vPowerTask,       "power",  256, NULL, 1, NULL); /* tickless idle + load switches */
}
