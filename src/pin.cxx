#include "pin.hxx"

namespace pin
{
    esp_err_t reset(gpio_num_t pin, gpio_mode_t mode)
    {
        esp_err_t err = ESP_OK;
        if ((err = gpio_reset_pin(pin)) != ESP_OK)
        {
            return err;
        }

        if ((err = gpio_set_direction(pin, mode)) != ESP_OK)
        {
            return err;
        }

        return err;
    }

    esp_err_t write(gpio_num_t pin, uint32_t value)
    {
        esp_err_t err = ESP_OK;
        if ((err = gpio_set_level(pin, value)) != ESP_OK)
        {
            return err;
        }

        return err;
    }
}
