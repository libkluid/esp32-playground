#ifndef __SPI_HXX__
#define __PID_HXX__

#include <cstdint>
#include "driver/gpio.h"
#include "esp_err.h"

namespace spi
{
    struct SpiConfig
    {
        gpio_num_t mosi;
        gpio_num_t sclk;
        gpio_num_t dc;
        gpio_num_t cs;
        gpio_num_t rst;
    };

    esp_err_t init(SpiConfig const *config);
    esp_err_t command(SpiConfig const *config, uint8_t data);
    esp_err_t buffer(SpiConfig const *config, uint8_t const *buffer, size_t size);
    esp_err_t data(SpiConfig const *config, uint8_t data);
    esp_err_t write(SpiConfig const *config, uint8_t data);
    esp_err_t clock(SpiConfig const *config);
}

#endif // __PID_HXX__
