#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "time.hxx"

namespace time
{
    void delay(TickType_t ms)
    {
        return vTaskDelay(ms / portTICK_PERIOD_MS);
    }
}
