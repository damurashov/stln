# Basic STM32F412-based application

# Building

## Linux

Prerequisites:

- [Non-EABI ARM GCC toolchain](https://developer.arm.com/downloads/-/gnu-rm)

### Process

Set environment path so it includes the downloaded toolchain

```bash
export PATH=<PATH-TO-GCC>:$PATH
```

Set the target name you want to build the project for

```bash
export USE_<TARGET_NAME>_TARGET=1
```

Available targets

- `stm32f407zg`
- `stm32f412`

# Debugging under QEMU

[Standard QEMU](https://www.qemu.org/docs/master/system/arm/stm32.html)
distribution does not support STM32F412xx. Use
[xPack](https://xpack.github.io/dev-tools/qemu-arm/install/)
disto instead. [This fella](https://aperles.blogs.upv.es/2020/04/15/simulation-emulation-of-the-stm32f4-discovery-board/)
provides somewhat satisfactory manual that might give one some hints.

## STM32F407ZG

QEMU does not provide support for STM32F412. In fact, there is only a few STM32
MCUs supported by the official QEMU release. This project can be debugged w/
QEMU on a "close enough" STM32F407ZG and then, hopefully, successfully ported
onto STM32F412.

