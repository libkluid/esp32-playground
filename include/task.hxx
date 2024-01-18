#ifndef __TASK_HXX__
#define __TASK_HXX__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace task
{
    void delay(TickType_t ms);

    BaseType_t spawn(
        TaskFunction_t fn,
        char const *name,
        int stack_size,
        void *arg,
        UBaseType_t priority,
        TaskHandle_t *handle,
        BaseType_t const core);

    void terminate(TaskHandle_t handle);
}

#endif // __TASK_HXX__
