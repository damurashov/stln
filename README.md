# Basic STM32F412-based application

## Functionality

The application makes use of

- USART1 at PA9 output pin
- STM32F4's RNG
- TIM2

TIM2's counter gets initialized w/ random value, and when its interrupt is
triggered, it puts a random character into a circular buffer, and enables
USART1 for further processing. USART1, in turn, spews the bytes from the
buffer into PA9 (see `usart1Isr`) at a pre-configured baudrate (see
`uartInitialize`) from the buffer, or gets disabled, if the buffer is empty.

## Quirks

TIM2's and USART1's ISR are configured to have the same priority to ensure
mutual exclusion over circular buffer.

# Building

## Linux

Prerequisites:

- [Non-EABI ARM GCC toolchain](https://developer.arm.com/downloads/-/gnu-rm)
- GNU Make
- CMake>=V3.12
- CMake

Optional

- [QEMU xPack](https://xpack.github.io/dev-tools/qemu-arm/install/)

## Process

Set environment path so it includes the downloaded toolchain

```bash
export PATH=<PATH-TO-GCC>:$PATH
```

Specify the target you want to build the project for

```bash
export USE_<TARGET_NAME>_TARGET=1
```

Available targets

- `stm32f407ig`
- `stm32f412`

Run

```
make -j4
```

## Prepping an image

To get flashable binary, run

```bash
make image
```

The output binary will be placed at `build/src/common/application.bin`

# Debugging under QEMU

[Standard QEMU](https://www.qemu.org/docs/master/system/arm/stm32.html)
distribution does not support STM32F412xx. Use
[xPack](https://xpack.github.io/dev-tools/qemu-arm/install/)
disto instead. [This fella](https://aperles.blogs.upv.es/2020/04/15/simulation-emulation-of-the-stm32f4-discovery-board/)
provides somewhat satisfactory manual that might give one some hints.
