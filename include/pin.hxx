#ifndef __PIN_HXX__
#define __PIN_HXX__

#include <esp_err.h>
#include "driver/gpio.h"

namespace pin
{
    esp_err_t reset(gpio_num_t pin, gpio_mode_t mode);
    esp_err_t write(gpio_num_t pin, uint32_t value);
}

#endif // __PIN_HXX__
