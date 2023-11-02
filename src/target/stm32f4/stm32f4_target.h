//
// target_stm32f4.h
//
// Created on: Oct 31, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#ifndef TARGET_STM32F4_TARGET_STM32F4_H_
#define TARGET_STM32F4_TARGET_STM32F4_H_

/// Default frequency of HSI clock source
#define TARGET_STM32F4_HSI_FREQUENCY_HZ (16000000)

/// \brief returns UART clock frequency as it is configured in RCC
unsigned long targetStm32f4GetUartClockFrequencyHz();

#endif // TARGET_STM32F4_TARGET_STM32F4_H_
