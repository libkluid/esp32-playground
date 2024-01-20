#ifndef __SSD1316_HXX__
#define __SSD1316_HXX__

#include "assembly/assembly.hxx"

namespace module::ssd1316
{
    struct Config
    {
        spi::SpiConfig spi_config;
    };

    esp_err_t init(Config const *config);
    esp_err_t draw8x8(Config const *config, uint8_t page, uint8_t column, uint8_t const *buffer);
    esp_err_t set_cursor(Config const *config, uint8_t page, uint8_t column);
    esp_err_t draw_text(Config const *config, char const *str);
    esp_err_t display(Config const *config, uint8_t const *buffer, size_t length);
}

#endif // __SSD1316_HXX__
