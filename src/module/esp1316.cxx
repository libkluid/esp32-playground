#include "esp_log.h"
#include "module/ssd1316.hxx"
#include "assembly/assembly.hxx"
#include "task.hxx"

char const static *TAG = "ssd1316";

namespace module::ssd1316
{
    esp_err_t cs_enable(spi::SpiConfig const *spi_config)
    {
        ESP_LOGD(TAG, "SPI CS ENABLE");
        return pin::write(spi_config->cs, 0);
    }

    esp_err_t cs_disable(spi::SpiConfig const *spi_config)
    {
        ESP_LOGD(TAG, "SPI CS DISABLE");
        return pin::write(spi_config->cs, 1);
    }

    esp_err_t reset(spi::SpiConfig const *spi_config)
    {
        ESP_LOGD(TAG, "RESET");
        esp_err_t err = ESP_OK;
        assert((err = pin::write(spi_config->rst, 0)) == ESP_OK);
        task::delay(100);
        assert((err = pin::write(spi_config->rst, 1)) == ESP_OK);
        task::delay(100);
        return err;
    }

    esp_err_t init(Config const *config)
    {
        esp_err_t err = ESP_OK;
        spi::SpiConfig const *spi_config = &config->spi_config;

        ESP_LOGD(TAG, "init & reset");
        assert((err = spi::init(spi_config)) == ESP_OK);
        assert((err = reset(spi_config)) == ESP_OK);

        assert((err = cs_enable(spi_config)) == ESP_OK);

        ESP_LOGD(TAG, "SET NORMAL DISPLAY");
        assert((err = spi::command(spi_config, 0xA6)) == ESP_OK);

        ESP_LOGD(TAG, "SET COM SCAN DIRECTION & SEGMENT RE-MAP");
        assert((err = spi::command(spi_config, 0xC8)) == ESP_OK);
        assert((err = spi::command(spi_config, 0xA0 | 0x01)) == ESP_OK);

        ESP_LOGD(TAG, "SET ADDRESSING MODE");
        assert((err = spi::command(spi_config, 0x20)) == ESP_OK);
        assert((err = spi::command(spi_config, 0x00)) == ESP_OK);

        ESP_LOGD(TAG, "SET DISPLAY OFFSET");
        assert((err = spi::command(spi_config, 0xD3)) == ESP_OK);
        assert((err = spi::command(spi_config, 0x00)) == ESP_OK);

        ESP_LOGD(TAG, "SET CHARGE PUMP & DISPLAY ON");
        assert((err = spi::command(spi_config, 0x8D)) == ESP_OK);
        assert((err = spi::command(spi_config, 0x14)) == ESP_OK);
        assert((err = spi::command(spi_config, 0xAF)) == ESP_OK);

        assert((err = cs_disable(spi_config)) == ESP_OK);

        return err;
    }

    esp_err_t display(Config const *config, uint8_t const *buffer, size_t length)
    {
        esp_err_t err = ESP_OK;
        spi::SpiConfig const *spi_config = &config->spi_config;

        assert((err = cs_enable(spi_config)) == ESP_OK);

        // SET PAGE ADDRESS
        assert((err = spi::command(spi_config, 0x22)) == ESP_OK);
        assert((err = spi::command(spi_config, 0x00)) == ESP_OK);
        assert((err = spi::command(spi_config, 0xFF)) == ESP_OK);

        // SET COLUMN ADDRESS
        assert((err = spi::command(spi_config, 0x21)) == ESP_OK);
        assert((err = spi::command(spi_config, 0x00)) == ESP_OK);
        assert((err = spi::command(spi_config, 0xFF)) == ESP_OK);

        // write data
        assert((err = spi::buffer(spi_config, buffer, length)) == ESP_OK);

        assert((err = cs_disable(spi_config)) == ESP_OK);

        return err;
    }
}
