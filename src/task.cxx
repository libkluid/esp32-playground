#include "task.hxx"

#include "esp_log.h"
#include "freertos/task.h"

char const static *TAG = "TASK";

namespace task
{
    void delay(TickType_t ms)
    {
        return vTaskDelay(ms / portTICK_PERIOD_MS);
    }

    BaseType_t spawn(
        TaskFunction_t fn,
        char const *name,
        int stack_size,
        void *arg,
        UBaseType_t priority,
        TaskHandle_t *const handle,
        BaseType_t const core)
    {
        assert(fn != nullptr);
        assert(name != nullptr);
        assert(stack_size > 0);
        ESP_LOGI(TAG, "Spawn task '%s' on core %d.", name, static_cast<BaseType_t>(core));
        return xTaskCreatePinnedToCore(fn, name, stack_size, arg, priority, (TaskHandle_t *)handle, core);
    }

    void terminate(TaskHandle_t handle)
    {
        ESP_LOGI(TAG, "Terminate task.");
        return vTaskDelete(handle);
    }
}
