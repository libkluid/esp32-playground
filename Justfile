environment := "esp32dev"

default: upload monitor

init:
    pio init --board {{environment}}

build:
    pio run --environment {{environment}}

upload:
    # build followed by upload
    just run upload

monitor:
    just run monitor

size:
    just run size

config:
    just run menuconfig

run target:
    pio run --target {{target}} --environment {{environment}}
