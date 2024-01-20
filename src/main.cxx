#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "esp_log.h"
#include "task.hxx"
#include "assembly/assembly.hxx"
#include "module/ssd1316.hxx"

extern "C" int
app_main(int const argc, char const *argv[])
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
    free(buffer);
    buffer = nullptr;

    char const *str = "libkluid";
    module::ssd1316::set_cursor(&ssd1316_config, 4, 4);
    module::ssd1316::draw_text(&ssd1316_config, str);

    return 0;
}
