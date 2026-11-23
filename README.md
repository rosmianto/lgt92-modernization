# LGT92 LoRaWAN firmware

This repository builds the LGT92 firmware for the STM32L072 target with an SX1276MB1LAS radio using Arm GNU GCC and CMake. The active LoRaWAN region is EU868.

## Prerequisites

- CMake 3.20 or newer
- Arm GNU Embedded Toolchain with `arm-none-eabi-gcc` and `arm-none-eabi-objcopy` on `PATH`
- A native build tool supported by CMake (the default Unix Makefiles generator on macOS uses `make`)

## Build

Run these commands from the repository root:

```sh
cmake -S . -B build/lgt92 \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake
cmake --build build/lgt92
```

The firmware artifacts are generated under `build/lgt92/`:

- `lgt92.elf` — linked firmware image
- `lgt92.hex` — Intel HEX image
- `lgt92.map` — linker map for inspection

To rebuild from scratch, remove only the generated build directory and repeat the configure/build commands:

```sh
rm -rf build/lgt92
cmake -S . -B build/lgt92 \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake
cmake --build build/lgt92
```

The build does not flash a device. The shared LoRaWAN sources remain in `Middlewares/Third_Party/Lora`; this firmware target compiles the EU868 region implementation.
