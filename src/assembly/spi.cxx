#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"

#include "assembly/spi.hxx"
#include "assembly/pin.hxx"
#include "task.hxx"

namespace spi
{
    esp_err_t init(SpiConfig const *config)
    {
        esp_err_t err = ESP_OK;
        assert((err = pin::reset(config->mosi, GPIO_MODE_OUTPUT)) == ESP_OK);
        assert((err = pin::reset(config->sclk, GPIO_MODE_OUTPUT)) == ESP_OK);
        assert((err = pin::reset(config->dc, GPIO_MODE_OUTPUT)) == ESP_OK);
        assert((err = pin::reset(config->cs, GPIO_MODE_OUTPUT)) == ESP_OK);
        assert((err = pin::reset(config->rst, GPIO_MODE_OUTPUT)) == ESP_OK);
        assert((err = pin::write(config->sclk, 0)) == ESP_OK);
        return err;
    }

    esp_err_t command(SpiConfig const *config, uint8_t cmd)
    {
        ESP_LOGD("spi", "+COMMAND: 0x%02X START", cmd);
        esp_err_t err = ESP_OK;
        assert((err = pin::write(config->dc, 0)) == ESP_OK);
        assert((err = write(config, cmd)) == ESP_OK);
        ESP_LOGD("spi", "-COMMAND: 0x%02X END", cmd);
        return err;
    }

    esp_err_t data(SpiConfig const *config, uint8_t byte)
    {
        ESP_LOGD("spi", "+DATA: 0x%02X START", byte);
        esp_err_t err = ESP_OK;
        assert((err = pin::write(config->dc, 1)) == ESP_OK);
        assert((err = write(config, byte)) == ESP_OK);
        ESP_LOGD("spi", "-DATA: 0x%02X END", byte);
        return err;
    }

    esp_err_t buffer(SpiConfig const *config, uint8_t const *buffer, size_t size)
    {
        ESP_LOGD("spi", "+BUFFER: %d bytes START", size);
        esp_err_t err = ESP_OK;
        assert((err = pin::write(config->dc, 1)) == ESP_OK);
        for (size_t i = 0; i < size; ++i)
        {
            assert((err = write(config, buffer[i])) == ESP_OK);
        }
        ESP_LOGD("spi", "-BUFFER: %d bytes END", size);
        return err;
    }

    esp_err_t write(SpiConfig const *config, uint8_t data)
    {
        esp_err_t err = ESP_OK;
        for (uint8_t bit = 0x80; bit; bit >>= 1)
        {
            assert((err = pin::write(config->mosi, (data & bit))) == ESP_OK);
            assert((err = clock(config)) == ESP_OK);
        }
        return err;
    }

    esp_err_t clock(SpiConfig const *config)
    {
        esp_err_t err = ESP_OK;
        assert((err = pin::write(config->sclk, 1)) == ESP_OK);
        assert((err = pin::write(config->sclk, 0)) == ESP_OK);
        return err;
    }
}
