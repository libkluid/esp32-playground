environment := "esp32dev"

default: build upload monitor

init:
    pio init --board {{environment}}

build:
    pio run --environment {{environment}}

upload:
    just run upload

monitor:
    just run monitor

size:
    just run size

config:
    just run menuconfig

run target:
    pio run --target {{target}} --environment {{environment}}
