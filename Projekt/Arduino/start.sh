set -e

pio run --target upload --target compiledb
pio device monitor
