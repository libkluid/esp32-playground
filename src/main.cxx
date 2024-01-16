#include "esp_log.h"
#include "pin.hxx"
#include "time.hxx"

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" int app_main(int const argc, char const *argv[])
{
    pin::reset(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    while (true)
    {
        ESP_LOGI("main", "HIGH");
        pin::write(GPIO_NUM_2, 1);
        time::delay(1000);
        ESP_LOGI("main", "LOW");
        pin::write(GPIO_NUM_2, 0);
        time::delay(1000);
    }

    return 0;
}
