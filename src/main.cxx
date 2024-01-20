#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "esp_log.h"
#include "task.hxx"
#include "assembly/assembly.hxx"
#include "module/ssd1316.hxx"

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

void scan_wifi(void *)
{
    wifi::init();
    task::terminate(nullptr);
}

extern "C" int app_main(int const argc, char const *argv[])
{
    spi::SpiConfig config = {
        .mosi = GPIO_NUM_5,
        .sclk = GPIO_NUM_18,
        .dc = GPIO_NUM_21,
        .cs = GPIO_NUM_19,
        .rst = GPIO_NUM_2,
    };

    module::ssd1316::Config ssd1316_config = {
        .spi_config = config,
    };

    module::ssd1316::init(&ssd1316_config);

    uint8_t *buffer = (uint8_t *)malloc(1024);
    memset(buffer, 0x00, 1024);
    module::ssd1316::display(&ssd1316_config, buffer, 1024);

    uint8_t(*matrix)[128] = (uint8_t(*)[128])buffer;
    for (uint8_t row = 0;; row = (row + 1) % 8)
    {
        for (uint8_t col = 0; col < 128; col += 1)
        {
            matrix[row][col] = ~matrix[row][col];
            module::ssd1316::display(&ssd1316_config, buffer, 1024);
        }
    }

    return 0;
}
