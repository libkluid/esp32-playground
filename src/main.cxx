#include <cstdio>
#include "esp_log.h"
#include "pin.hxx"
#include "task.hxx"
#include "wifi.hxx"

#include "nvs_flash.h"

int static run_looop = 0;

void app_task(void *arg)
{
    int value = 0;
    while (run_looop)
    {
        pin::write(GPIO_NUM_2, value);
        task::delay(1000);
        value = !value;

        pin::write(GPIO_NUM_2, value);
        task::delay(200);
        value = !value;
    }
}

extern "C" int app_main(int const argc, char const *argv[])
{
    run_looop = 1;
    pin::reset(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    task::spawn(app_task, "up", 2048, nullptr, 1, nullptr, 1);
    return 0;
}
