#include "pin.hxx"

namespace pin
{
    esp_err_t reset(gpio_num_t pin, gpio_mode_t mode)
    {
        esp_err_t err = ESP_OK;
        ESP_ERROR_CHECK(err = gpio_reset_pin(pin));
        ESP_ERROR_CHECK(err = gpio_set_direction(pin, mode));
        return err;
    }

    esp_err_t write(gpio_num_t pin, uint32_t value)
    {
        esp_err_t err = ESP_OK;
        ESP_ERROR_CHECK(err = gpio_set_level(pin, value));
        return err;
    }

    int read(gpio_num_t pin)
    {
        return gpio_get_level(pin);
    }
}
